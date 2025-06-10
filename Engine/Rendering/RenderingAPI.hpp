#pragma once

#include <cstdint>
#include <string>
#include <functional>
#include <memory>

namespace UTE
{
    class ApplicationWindow;
    struct VertexLayout;

    struct RenderHandle
    {
    public:

        RenderHandle(void* DataPointer, std::function<void(RenderHandle& InHandle)> Deletor)
        {
            mInternalData = DataPointer;
        }

        template<class T>
        T* Cast()
        {
            return static_cast<T*>(mInternalData);
        }

        void DestroyObject()
        {
            mDeletorFunction(*this);
            mDeletorFunction = nullptr;
        }

    private:

        void* mInternalData = nullptr;
        std::function<void(RenderHandle& Deletor)> mDeletorFunction;

    };

    typedef RenderHandle BufferHandle;
    typedef RenderHandle TextureHandle;

    class UTENGINE_API RenderingAPI
    {

    public:

        virtual bool InitializeAPI(std::weak_ptr<ApplicationWindow>& OwningWindow) = 0;
        virtual void SetupWindowFlags() = 0;

        virtual void SetCurrentVertexLayout(VertexLayout& NewLayout) = 0;
        virtual const VertexLayout& GetCurrentVertexLayout() = 0;

        virtual void CreateBuffer(uint32_t Size, BufferHandle* OutHandle) = 0;
        virtual void DestroyBuffer(BufferHandle& InHandle) = 0;

        virtual void RefreshDisplay() = 0;

        virtual const std::string GetRenderAPIName() = 0;;

    };

}