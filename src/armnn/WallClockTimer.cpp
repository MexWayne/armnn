//
// Copyright © 2017 Arm Ltd. All rights reserved.
// See LICENSE file in the project root for full license information.
//

#include "WallClockTimer.hpp"

namespace armnn
{

const std::string WallClockTimer::WALL_CLOCK_TIME      ("Wall clock time");
const std::string WallClockTimer::WALL_CLOCK_TIME_START(WallClockTimer::WALL_CLOCK_TIME + " (Start)");
const std::string WallClockTimer::WALL_CLOCK_TIME_STOP (WallClockTimer::WALL_CLOCK_TIME + " (Stop)");

const char* WallClockTimer::GetName() const
{
    return "WallClockTimer";
}

void WallClockTimer::Start()
{
    m_Start = clock::now();
}

void WallClockTimer::Stop()
{
    m_Stop = clock::now();
}

std::vector<Measurement> WallClockTimer::GetMeasurements() const
{
    const auto delta       = std::chrono::duration<double, std::milli>(m_Stop - m_Start);
    const auto startTimeMs = std::chrono::duration<double, std::milli>(m_Start.time_since_epoch());
    const auto stopTimeMs  = std::chrono::duration<double, std::milli>(m_Stop.time_since_epoch());

    return { { WALL_CLOCK_TIME,       delta.count(),       Measurement::Unit::TIME_MS },
             { WALL_CLOCK_TIME_START, startTimeMs.count(), Measurement::Unit::TIME_MS },
             { WALL_CLOCK_TIME_STOP,  stopTimeMs.count(),  Measurement::Unit::TIME_MS } };
}

} //namespace armnn
