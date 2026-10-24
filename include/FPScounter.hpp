
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

    bool Update()
    {
        ++m_frameCount;

        const auto now = Clock::now();
        const double elapsed =
            std::chrono::duration<double>(
                now - m_lastUpdate)
                .count();

        if (elapsed < m_updateInterval)
            return false;

        m_fps = static_cast<double>(m_frameCount) / elapsed;
        m_frameTime = 1000.0 / m_fps;

        m_frameCount = 0;
        m_lastUpdate = now;

        return true;
    }

    double GetFPS() const
    {
        return m_fps;
    }

    double GetFrameTime() const
    {
        return m_frameTime;
    }

private:
    double m_updateInterval;
    Clock::time_point m_lastUpdate;

    std::uint64_t m_frameCount = 0;

    double m_fps = 0.0;
    double m_frameTime = 0.0;
};
