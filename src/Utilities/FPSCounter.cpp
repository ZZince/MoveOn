#include "Utilities/FPSCounter.hpp"

bool FPSCounter::Update()
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

double FPSCounter::GetFPS() const
    {
        return m_fps;
    }

double FPSCounter::GetFrameTime() const
    {
        return m_frameTime;
    }