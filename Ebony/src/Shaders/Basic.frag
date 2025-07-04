#version 410 core

out vec4 FragColor;
in vec2 fragCoord;

#define MAX_SPHERES 32
#define FLOAT_MAX 1e20

uniform float u_AspectRatio;
uniform uvec2 u_ImageDimensions;

uniform uint u_MaxBounceCount;
uniform uint u_RaysPerPixel;

uniform vec3 u_SkyColorHorizon = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 u_SkyColorZenith = vec3(0.5f, 0.7f, 1.0f);
uniform vec3 u_GroundColor = vec3(0.25f, 0.25f, 0.25f);
uniform vec3 u_SunLightDirection = vec3(1.0f, 1.0f, -1.0f);
uniform float u_SunFocus = 10;
uniform float u_SunIntensity = 1;

uniform uint u_NumRenderedFrames;

// Camera Setup
uniform float u_CameraFocalLength = 3.5f;
uniform float u_ViewPortSize = 2.0f;

vec2 viewPortDimensions = vec2(u_ViewPortSize * u_AspectRatio, u_ViewPortSize);
vec3 cameraCenter = vec3(0.0f, 0.0f, 0.0f);
vec3 viewPort = vec3(viewPortDimensions.x, -viewPortDimensions.y, 0.0f);
vec3 viewPortUpperLeft = cameraCenter - vec3(0.0f, 0.0f, u_CameraFocalLength) - (viewPort / 2.0f);

struct Ray {
    vec3 origin;
    vec3 dir;
};

struct RayTracingMaterial {
    vec4 color;
    vec3 emission;
    float emissionStrength;
};

struct HitInfo {
    bool didHit;
    float distance;
    vec3 hitPoint;
    vec3 normal;
    RayTracingMaterial material;
};

struct Sphere {
    vec3 center;
    float radius;
    RayTracingMaterial material;
};

uniform int u_SphereCount;
uniform Sphere u_Spheres[MAX_SPHERES];

// source: https://www.reedbeta.com/blog/hash-functions-for-gpu-rendering/
uint pcg_hash(inout uint state) {
    state = state * 747796405u + 2891336453u;
    uint word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
    return (word >> 22u) ^ word;
}

float RandomValue(inout uint state) {
    return float(pcg_hash(state)) / 0xFFFFFFFFu;
}

float RandomValue(inout uint state, float min, float max) {
    return RandomValue(state) * (max - min) + min;
}

float RandomValueNormalDistribution(inout uint state) {
    float theta = 2.0f * 3.14159f * RandomValue(state);
    float rho = sqrt(-2 * log(RandomValue(state)));
    return rho * cos(theta);
}

// This is not uniformly distributed !!
// vec3 RandomDirection(inout uint state) {
//     // while (true) // Dangerous
//     for (int i = 0; i < 100; i++) {
//         float x = RandomValue(state, -1.0f, 1.0f);
//         float y = RandomValue(state, -1.0f, 1.0f);
//         float z = RandomValue(state, -1.0f, 1.0f);
//         vec3 pointInCube = vec3(x, y, z);
//         float distFromCenterSquared = dot(pointInCube, pointInCube);
//         if (distFromCenterSquared <= 1) {
//             return pointInCube / sqrt(distFromCenterSquared);
//         }
//     }
//
//     return vec3(0);
// }

vec3 RandomDirection(inout uint state) {
    float x = RandomValueNormalDistribution(state);
    float y = RandomValueNormalDistribution(state);
    float z = RandomValueNormalDistribution(state);

    return normalize(vec3(x, y, z));
}

vec3 RandomHemisphereDirection(vec3 normal, inout uint state) {
    vec3 dir = RandomDirection(state);
    return dir * sign(dot(normal, dir));
    // invert the dir, if it is outside the hemisphere
    // then it will be inside.
}

HitInfo RaySphere(Ray ray, vec3 sphereCenter, float sphereRadius) {
    HitInfo hitInfo = HitInfo(false, 0.0f, vec3(0), vec3(0), RayTracingMaterial(vec4(0), vec3(0), 0));

    // Q = ray origin
    // d = ray direction
    // t = time
    // C = center of sphere
    // r = radius of sphere
    //
    // t^2(d.d) - 2td.(C-Q) + (C-Q).(C-Q) - r^2 = 0
    //
    // a = (d.d)
    // b = - 2(d).(C-Q)
    // c = (C-Q).(C-Q) - r^2
    // D = b^2 - 4ac >= 0

    vec3 offestRayOrigin = sphereCenter - ray.origin;
    float a = dot(ray.dir, ray.dir); // assuming unit vector (a = 1)
    float b = -2.0f * dot(offestRayOrigin, ray.dir);
    float c = dot(offestRayOrigin, offestRayOrigin) - sphereRadius * sphereRadius;

    // using quadratic formula
    float discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        // distance/time to the nearest intersection point (from quadratic formula)
        float t = (-b - sqrt(discriminant)) / (2 * a);

        // Ignore intersections that occur behind the ray (see the hitInfo.hitPoint calc)
        if (t >= 0) {
            hitInfo.didHit = true;
            hitInfo.distance = t;
            hitInfo.hitPoint = ray.origin + ray.dir * t;
            hitInfo.normal = normalize(hitInfo.hitPoint - sphereCenter);
        }
    }

    return hitInfo;
}

HitInfo CalculateRayCollision(Ray ray) {
    HitInfo closestHit = HitInfo(false, 0.0f, vec3(0), vec3(0), RayTracingMaterial(vec4(0), vec3(0), 0));
    closestHit.distance = FLOAT_MAX;

    // can be optimised to check only those
    // spheres which are infront of the camera.
    for (int i = 0; i < u_SphereCount; i++) {
        Sphere sphere = u_Spheres[i];
        HitInfo hit = RaySphere(ray, sphere.center, sphere.radius);
        if (hit.didHit && hit.distance < closestHit.distance) {
            closestHit = hit;
            closestHit.material = sphere.material;
        }
    }

    return closestHit;
}

vec3 GetEnvironmentLight(Ray ray) {
    // Sky gradient
    float skyGradientT = pow(smoothstep(0.0, 0.4, ray.dir.y), 0.35);
    vec3 skyGradient = mix(u_SkyColorHorizon, u_SkyColorZenith, skyGradientT);

    // Sun calculation
    float sun = pow(max(0.0, dot(ray.dir, -u_SunLightDirection)), u_SunFocus) * u_SunIntensity;

    // Ground blending
    float groundToSkyT = smoothstep(-0.01, 0.0, ray.dir.y);
    float sunMask = step(1.0, groundToSkyT); // Equivalent to (groundToSkyT >= 1 ? 1.0 : 0.0)

    // Final blending
    return mix(u_GroundColor, skyGradient, groundToSkyT) + sun * sunMask;

    // vec3 unitDir = normalize(ray.dir);
    // float a = 0.5 * (unitDir.y + 1.0);
    // return mix(u_SkyColorHorizon, u_SkyColorZenith, a);
}

vec3 Trace(Ray ray, inout uint state) {
    vec3 incomingLight = vec3(0);
    vec3 rayColor = vec3(1); // initially white

    for (int i = 0; i < u_MaxBounceCount; i++) {
        HitInfo hitInfo = CalculateRayCollision(ray);
        if (hitInfo.didHit) {
            ray.origin = hitInfo.hitPoint; // In the next iteration, the ray will bounce off of the hitPoint
            ray.dir = RandomHemisphereDirection(hitInfo.normal, state); // in a random direction w.r.t its normal

            //
            // Modify the ray color based on what it has collided with
            //
            RayTracingMaterial material = hitInfo.material;
            vec3 emmitedLight = material.emission * material.emissionStrength; // if the material is emmisive
            incomingLight += emmitedLight * rayColor; // we add this to the incomming Light tinting it as the current ray color
            // irrespective of emmision, ray is going to bounce off accomodating
            // the color of the current material
            rayColor *= material.color.xyz;

            // // Lambertian reflection weight
            // float cosTheta = max(0.0, dot(hitInfo.normal, ray.dir));
            // float pdf = 1.0 / (2.0 * 3.14159); // uniform hemisphere
            //
            // rayColor *= (cosTheta / pdf) * material.color.xyz;
        } else {
            // ray hasnt collided with anything!
            // so we can either break the loop right away (then incomming light will be zero i.e. black environment)
            //
            // OR, we can add environment light if ray hasnt collided with anything
            // if the ray bounces off something to the void, environment light gets multiplied to it
            incomingLight += GetEnvironmentLight(ray) * rayColor;
            break;
        }
    }

    return incomingLight;
}

void main() {
    vec3 pixelCenter = viewPortUpperLeft + vec3(fragCoord.x * viewPort.x, fragCoord.y * viewPort.y, 0.0f);
    // not adding 0.5 * pixelDelta becuase fragCoord is already normalized

    Ray ray;
    ray.origin = vec3(0.0f, 0.0f, 0.0f);
    ray.dir = pixelCenter - cameraCenter;

    uvec2 pixelCoord = uvec2(fragCoord * u_ImageDimensions);
    uint pixelIndex = pixelCoord.y * u_ImageDimensions.x + pixelCoord.x;

    // For progessive rendering
    uint rngState = pixelIndex + u_NumRenderedFrames * 836239u + 589387u;
    rngState ^= rngState << 13;

    vec3 totalIncomingLight = vec3(0);
    for (int rayIndex = 0; rayIndex < u_RaysPerPixel; rayIndex++) {
        totalIncomingLight += Trace(ray, rngState);
    }

    vec3 averageIncomingLight = totalIncomingLight / u_RaysPerPixel;
    if (any(isnan(averageIncomingLight)) || any(isinf(averageIncomingLight))) {
        averageIncomingLight = vec3(1.0f, 0.0f, 1.0f); // or some fallback averageIncomingLight
    }
    FragColor = vec4(averageIncomingLight, 1.0f);
}
