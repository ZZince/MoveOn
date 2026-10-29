#pragma once

#include <chrono>
#include <cstdint>

class FPSCounter
{
public:
    using Clock = std::chrono::steady_clock;

    explicit FPSCounter(double updateInterval = 1.0)
        : m_updateInterval(updateInterval),
          m_lastUpdate(Clock::now())
    {
    }

    bool Update();

    double GetFPS() const;

    double GetFrameTime() const;

private:
    double m_updateInterval;
    Clock::time_point m_lastUpdate;

    std::uint64_t m_frameCount = 0;

    double m_fps = 0.0;
    double m_frameTime = 0.0;
};
