#pragma once

namespace Ebony {

/**
 * @class Timer
 * @brief Provides frame timing, delta time, and FPS tracking.
 *
 * Designed to be called once per frame via Tick(), and exposes utility methods
 * to retrieve frame delta, total elapsed time, and FPS value for rendering engines.
 */
class Timer {
public:
    /// Constructs a new Timer, setting the initial time reference.
    Timer();

    /// Updates internal timing values. Should be called once per frame.
    void Tick();

    /// Returns the time (in seconds) between the last two frames.
    [[nodiscard]] double GetDeltaTime() const;

    /// Returns the total elapsed time (in seconds) since the Timer was created.
    [[nodiscard]] double GetElapsedTime() const;

    /**
     * @brief Determines whether one second has passed since last FPS update.
     *
     * Use this to conditionally update window title or other FPS displays.
     * @return true if a second has passed, and FPS should be updated.
     * @return false otherwise.
     */
    bool ShouldUpdateFPS();

    /// Returns the last computed frames per second (updated every second).
    [[nodiscard]] int GetFPS() const;

private:
    double lastTime;    ///< Time at the last frame.
    double currentTime; ///< Current time during this frame.
    double deltaTime;   ///< Time difference between frames.

    double fpsTimer; ///< Accumulated time since last FPS update.
    int frameCount;  ///< Number of frames counted in the current FPS window.
    int fps;         ///< Cached FPS value.
};

} // namespace Ebony
