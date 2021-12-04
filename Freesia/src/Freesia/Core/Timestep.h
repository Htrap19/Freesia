//
// Created by Htrap19 on 12/4/21.
//

#ifndef FREESIA_TIMESTEP_H
#define FREESIA_TIMESTEP_H

namespace Freesia
{
    class TimeStep
    {
    public:
        TimeStep(float time)
            : m_Time(time)
        {}

        operator float() const { return m_Time; }

        inline float GetSeconds() const { return m_Time; }
        inline float GetMilliSeconds() const { return m_Time * 1000.0f; }

    private:
        float m_Time;
    };
}

#endif //FREESIA_TIMESTEP_H
