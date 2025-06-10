#pragma once

#include <cstdint>
#include <memory>

#include "Rendering/VertexLayout.hpp"
#include "Platform/ApplicationWindow.hpp"

namespace UTE::GLTypes
{

    struct OpenGLState
    {
        std::weak_ptr<ApplicationWindow> WindowContext;
        uint32_t VertexArrayObject = UINT32_MAX;
        VertexLayout CurrentVertexLayout;
    };

    struct OpenGLBuffer
    {
        uint32_t BufferID = UINT32_MAX;
        uint32_t BufferSize = 0;
    };

}