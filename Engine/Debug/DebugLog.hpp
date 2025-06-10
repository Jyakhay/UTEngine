#pragma once

#include "Math/TimeSpan.hpp"
#include <cstdint>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <format>

namespace UTE
{

    enum class ELogSeverity
    {
        Message,
        Warning,
        Error
    };

    class DebugLogger
    {

    public:

        /*Outputs a message to the console, and if a log session has begun, the log file.*/
        static void UTENGINE_API Log(const std::string& Source, ELogSeverity Severity, const std::string& Message);
        
        /*Outputs a message to the console, and if a log session has begun, the log file.*/
        template<class... Args>
        static void LogFmt(const std::string& Source, ELogSeverity Severity, const std::string& Message, Args... LogArgs)
        {
            std::string OutputMessage = std::format("[{}|{}] {}: {}\n", GetTimeCodeString(), Source, GetSeverityString(Severity), std::vformat(Message, std::make_format_args(LogArgs...)));
            std::cout << OutputMessage;

            if(mSessionActive)
            {
                mLogStream << OutputMessage;
            }
        }

        template<class... LogArgs>
        static std::string GetFormattedString(const std::string& FormatString, LogArgs&&... Args)
        {
            return std::vformat(FormatString, std::make_format_args(Args...));
        }
        
        //TODO - Allow log directory to be specified

        /*Creates a new log file and removes old log files if more than mMaxLogCount files exist.*/
        static bool UTENGINE_API BeginLogSession();

        /*Stops writing to the log file, if a session has begun.*/
        static bool UTENGINE_API EndLogSession();

    private:

        static TimeSpan GetLogFileTime(const std::filesystem::path& LogPath);
        static std::filesystem::path GetOldestLogFile();

        static std::filesystem::path GetNextLogFilePath();
        static std::string GetSeverityString(ELogSeverity Severity);
        static std::string GetTimeCodeString();

        static inline bool mSessionActive = false;
        static inline std::ofstream mLogStream;
        static inline uint8_t mMaxLogCount = 10;

    };

}

#define UTENGINE_LOG(Source, Severity, Message) UTE::DebugLogger::Log(Source, Severity, Message)
#define UTENGINE_LOGFMT(Source, Severity, Message, ...) UTE::DebugLogger::LogFmt(Source, Severity, Message, __VA_ARGS__)
#define UTENGINE_DEFINE_LOG_SOURCE(SourceName, DisplayText) static constexpr const char* SourceName = DisplayText;