#pragma once
#include <cstdint>

namespace UTE::GLTypes
{

    struct OpenGLState
    {
        ApplicationWindow* WindowContext = nullptr;
    };

    struct OpenGLBuffer
    {
        uint32_t BufferID = UINT32_MAX;
        uint32_t BufferSize = 0;
    };

}