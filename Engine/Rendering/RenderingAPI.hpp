#pragma once

#include <cstdint>
#include <string>

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

        template<class T>
        T* Cast()
        {
            return static_cast<T*>(mInternalData);
        }

    private:

        void* mInternalData = nullptr;

    };

    typedef RenderHandle BufferHandle;
    typedef RenderHandle TextureHandle;

    class RenderingAPI
    {

    public:

        virtual bool InitializeAPI(ApplicationWindow* OwningWindow) = 0;
        virtual void SetupWindowFlags() = 0;

        virtual void CreateBuffer(uint32_t Size, BufferHandle* OutHandle) = 0;
        virtual void DestroyBuffer(BufferHandle& InHandle) = 0;

        virtual void RefreshDisplay() = 0;

        virtual const std::string GetRenderAPIName() = 0;;

    };

}