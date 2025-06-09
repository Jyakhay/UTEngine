#pragma once

#include "Rendering/RenderingAPI.hpp"

namespace UTE
{

    class OGLRenderingAPI : public RenderingAPI
    {

    public:

        virtual void InitializeAPI(ApplicationWindow* OwningWindow) override;
        virtual void SetupWindowFlags() override;

        virtual void CreateBuffer(uint32_t Size, RenderHandle *OutHandle) override;
        virtual void DestroyBuffer(RenderHandle &InHandle) override;

    };

}