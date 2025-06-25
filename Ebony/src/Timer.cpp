#include "Timer.h"
#include <GLFW/glfw3.h>

namespace Ebony {

Timer::Timer() : lastTime(glfwGetTime()), currentTime(lastTime), deltaTime(0.0), fpsTimer(0.0), frameCount(0), fps(0) {}

void Timer::Tick() {
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    fpsTimer += deltaTime;
    frameCount++;
}

bool Timer::ShouldUpdateFPS() {
    if (fpsTimer >= 1.0) {
        fps = frameCount;
        frameCount = 0;
        fpsTimer = 0.0;
        return true;
    }
    return false;
}

double Timer::GetDeltaTime() const { return deltaTime; }

double Timer::GetElapsedTime() const { return currentTime; }

int Timer::GetFPS() const { return fps; }

} // namespace Ebony
