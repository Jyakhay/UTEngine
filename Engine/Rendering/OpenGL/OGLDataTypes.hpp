#pragma once

#include <cstdint>
#include <memory>

#include "Rendering/RenderingAPI.hpp"
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

    struct OpenGLTexture1D
    {
        uint32_t TextureID = UINT32_MAX;
        uint32_t Size = 0;
        uint32_t Levels = 0;
        ETextureFormat Format = ETextureFormat::RGB_8;
    };

    struct OpenGLTexture2D
    {
        uint32_t TextureID = UINT32_MAX;
        uint32_t Width = 0;
        uint32_t Height = 0;
        uint32_t Levels = 0;
        ETextureFormat Format = ETextureFormat::RGB_8;
    };

    struct OpenGLTexture3D
    {
        uint32_t TextureID = UINT32_MAX;
        uint32_t Width = 0;
        uint32_t Height = 0;
        uint32_t Depth = 0;
        uint32_t Levels = 0;
        ETextureFormat Format = ETextureFormat::RGB_8;
    };

}