#pragma once

#include <chrono>
#include <ctime>

namespace UTE
{

    /*---------------------------- struct TimeSpan ----------------------------*/
    /* Summary:                                                                */
    /* A representation of a duration or a specific time.                      */
    /*-------------------------------------------------------------------------*/
    struct TimeSpan
    {

    public:

        TimeSpan() = default;

        TimeSpan(const std::tm& Time)
        {
            Seconds = Time.tm_sec;
            Minutes = Time.tm_min;
            Hours = Time.tm_hour;
            Days = Time.tm_mday;
            Months = Time.tm_mon;
            Years = 1900 + Time.tm_year;
        }

        static TimeSpan GetSystemTime()
        {
            std::chrono::time_point CurrentTime = std::chrono::system_clock::now();
            std::time_t Time = std::chrono::system_clock::to_time_t(CurrentTime);

            std::tm TimeInfo;

#ifdef COMPILER_MSVC
                localtime_s(&TimeInfo, &Time);
#else
                localtime_r(&Time, &TimeInfo);
#endif

            return TimeSpan(TimeInfo);
        }

        int Compare(const TimeSpan& Other) const
        {
            std::tm TimeA{};
            TimeA.tm_sec = Seconds;
            TimeA.tm_min = Minutes;
            TimeA.tm_hour = Hours;
            TimeA.tm_mday = Days;
            TimeA.tm_mon = Months;
            TimeA.tm_year = Years - 1900;

            std::tm TimeB{};
            TimeB.tm_sec = Other.Seconds;
            TimeB.tm_min = Other.Minutes;
            TimeB.tm_hour = Other.Hours;
            TimeB.tm_mday = Other.Days;
            TimeB.tm_mon = Other.Months;
            TimeB.tm_yday = Other.Years;

            const std::time_t TimePointA = std::mktime(&TimeA);
            const std::time_t TimePointB = std::mktime(&TimeB);

            const double Difference = difftime(TimePointA, TimePointB);

            if(Difference == 0.0)
            {
                return 0;
            }
            else
            {
                if(Difference < 0.0f)
                {
                    return -1;
                }

                return 1;
            }
        }

        int Seconds = 0;
        int Minutes = 0;
        int Hours = 0;
        int Days = 0;
        int Months = 0;
        int Years = 0;

    };

}