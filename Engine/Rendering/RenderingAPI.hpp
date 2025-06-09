#pragma once

#include <cstdint>

namespace UTE
{
    class ApplicationWindow;

    struct RenderHandle
    {
    public:

        RenderHandle(void* DataPointer)
        {
            mInternalData = DataPointer;
        }

    private:

        void* mInternalData = nullptr;

    };

    class RenderingAPI
    {

    public:

        virtual void InitializeAPI(ApplicationWindow* OwningWindow) = 0;
        virtual void SetupWindowFlags() = 0;

        virtual void CreateBuffer(uint32_t Size, RenderHandle* OutHandle) = 0;
        virtual void DestroyBuffer(RenderHandle& InHandle) = 0;


    };

}