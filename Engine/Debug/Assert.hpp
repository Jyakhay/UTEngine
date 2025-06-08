#pragma once

#include "Debug/DebugLog.hpp"
#include <cstdlib>
#include <cassert>

#define UTENGINE_ASSERT(Condition, Note, ...)\
if(!(Condition))\
{\
    std::string FormatString = UTE::DebugLogger::GetFormattedString(Note, ##__VA_ARGS__);\
    UTENGINE_LOGFMT("Assert", UTE::ELogSeverity::Error, "Assert condition in file \"{}\" at line {} has failed, aborting program! Condition: \"{}\" | Note: \"{}\"", __FILE__, __LINE__, #Condition, FormatString);\
    std::abort();\
}
