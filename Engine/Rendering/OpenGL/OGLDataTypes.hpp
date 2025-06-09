#pragma once
#include <cstdint>

namespace UTE
{

    struct OpenGLBuffer
    {
        uint32_t BufferID = UINT32_MAX;
        uint32_t BufferSize = 0;
    };

}