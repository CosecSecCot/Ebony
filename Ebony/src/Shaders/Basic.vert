#version 410 core
layout(location = 0) in vec3 a_Position;
out vec2 fragCoord;

void main() {
    fragCoord = a_Position.xy * 0.5 + 0.5; // Convert from [-1,1] to [0,1]
    fragCoord.y = 1.0 - fragCoord.y;
    gl_Position = vec4(a_Position, 1.0);
}
