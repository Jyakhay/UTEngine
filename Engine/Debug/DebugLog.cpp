#include "DebugLog.hpp"
#include "Math/TimeSpan.hpp"
#include "Platform/Executable.hpp"
#include "Platform/FileSystem.hpp"

#include <sstream>
#include <vector>

namespace UTE
{

    void DebugLogger::Log(const std::string& Source, ELogSeverity Severity, const std::string& Message)
    {
        std::string OutputMessage = std::format("[{}|{}] {}: {}\n",
            GetTimeCodeString(),
            Source,
            GetSeverityString(Severity),
            Message
        );
        
        std::cout << OutputMessage;
        
        if(mSessionActive)
        {
            mLogStream << OutputMessage;
        }
    }

    bool DebugLogger::BeginLogSession()
    {
        if(mSessionActive)
        {
            return false;
        }

        uint32_t LogFileCount = FileSystem::GetDirectoryFileCount(FileSystem::GetLogDirectory());
        if(LogFileCount >= mMaxLogCount)
        {
            std::filesystem::remove(GetOldestLogFile());
        }

        mLogStream = std::ofstream(GetNextLogFilePath());

        if(!mLogStream.is_open())
        {
            return false;
        }

        mSessionActive = true;

        UTENGINE_LOG("DebugLogger", ELogSeverity::Message, "--------Debug Log Session Begin--------");
        return true;
    }

    bool DebugLogger::EndLogSession()
    {
        if(!mSessionActive)
        {
            return false;
        }

        UTENGINE_LOG("DebugLogger", ELogSeverity::Message, "--------Debug Log Session End--------");
        
        mSessionActive = false;
        mLogStream.close();

        return true;
    }

    TimeSpan DebugLogger::GetLogFileTime(const std::filesystem::path& LogPath)
    {
        
        TimeSpan ReturnValue;

        std::string LogFileName = LogPath.filename().string();
        std::string LogTimeSection = LogFileName.substr(1, LogFileName.find_last_of('-') - 3);

        const size_t DateTimeIndex = LogTimeSection.find(' ');
        
        const std::string Date = LogTimeSection.substr(0, DateTimeIndex);
        const std::string Time = LogTimeSection.substr(DateTimeIndex + 1, LogTimeSection.size() - LogTimeSection.find(']'));

        std::istringstream DateStream;
        DateStream.str(Date);

        std::string CurrentString;
        std::vector<int> DateValues;

        while(std::getline(DateStream, CurrentString, '-'))
        {
            DateValues.push_back(std::stoi(CurrentString));
        }

        std::istringstream TimeStream;
        TimeStream.str(Time);

        std::vector<int> TimeValues;
        while(std::getline(TimeStream, CurrentString, '.'))
        {
            TimeValues.push_back(std::stoi(CurrentString));
        }

        ReturnValue.Years = DateValues[0];
        ReturnValue.Months = DateValues[1];
        ReturnValue.Days = DateValues[2];
        ReturnValue.Hours = TimeValues[0];
        ReturnValue.Minutes = TimeValues[1];
        ReturnValue.Seconds = TimeValues[2];

        return ReturnValue;
    }

    std::filesystem::path DebugLogger::GetOldestLogFile()
    {
        std::vector<std::filesystem::path> Paths;

        for(auto& CurrentPath : std::filesystem::directory_iterator(FileSystem::GetLogDirectory()))
        {
            TimeSpan CreationTime = GetLogFileTime(CurrentPath);

            //TODO - Look for better algorithm for sorting.
            int Insertindex = 0;
            for(auto& OtherPath : Paths)
            {
                TimeSpan OtherCreationTime = GetLogFileTime(OtherPath);

                if(CreationTime.Compare(OtherCreationTime) == 1)
                {
                    Insertindex++;
                }
            }
        
            Paths.insert(Paths.begin() + Insertindex, CurrentPath);
        }

        return Paths.at(Paths.size() - 1);
    }

    std::filesystem::path DebugLogger::GetNextLogFilePath()
    {
        TimeSpan CurrentTime = TimeSpan::GetSystemTime();

        const std::string ParsedTime = std::format("[{}-{:02}-{:02} {:02}.{:02}.{:02}] - {}.log",
            CurrentTime.Years,
            CurrentTime.Months,
            CurrentTime.Days,
            CurrentTime.Hours,
            CurrentTime.Minutes,
            CurrentTime.Seconds,
            Executable::GetPath().stem().string()
        );

        return FileSystem::GetLogDirectory().append(ParsedTime);
    }

    std::string DebugLogger::GetSeverityString(ELogSeverity Severity)
    {
        switch(Severity)
        {
            case ELogSeverity::Message:
            {
                return "Message";
            }

            case ELogSeverity::Warning:
            {
                return "Warning";
            }

            case ELogSeverity::Error:
            {
                return "Error";
            }
        }

        return "";
    }

    std::string DebugLogger::GetTimeCodeString()
    {
        TimeSpan CurrentTime = TimeSpan::GetSystemTime();
        return std::format("{:02}:{:02}:{:02}", CurrentTime.Hours, CurrentTime.Minutes, CurrentTime.Seconds);
    }

}