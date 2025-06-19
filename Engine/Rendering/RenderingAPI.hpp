#pragma once

#include <cstdint>
#include <string>
#include <functional>
#include <memory>

namespace UTE
{
    class ApplicationWindow;
    struct VertexLayout;

    enum class ETextureFormat
    {
        R_8,
        R_16,
        RG_8,
        RG_16,
        RGB_8,
        RGBA_8,
        RGBA_16
    };

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
    typedef RenderHandle Texture1DHandle;
    typedef RenderHandle Texture2DHandle;
    typedef RenderHandle Texture3DHandle;

    class UTENGINE_API RenderingAPI
    {

    public:

        virtual bool InitializeAPI(std::weak_ptr<ApplicationWindow>& OwningWindow) = 0;
        virtual void SetupWindowFlags() = 0;

        virtual void SetCurrentVertexLayout(VertexLayout& NewLayout) = 0;
        virtual const VertexLayout& GetCurrentVertexLayout() = 0;

        virtual void BufferCreate(uint32_t Size, BufferHandle* OutHandle) = 0;
        virtual void BufferSetData(BufferHandle& InHandle, uint32_t DataSize, uint32_t Offset, void* DataPointer) = 0;
        virtual void BufferDestroy(BufferHandle& InHandle) = 0;

        virtual void Texture1DCreate(ETextureFormat Format, uint32_t Size, uint32_t Levels, Texture1DHandle* OutTexture) = 0;
        virtual void Texture2DCreate(ETextureFormat Format, uint32_t Width, uint32_t Height, uint32_t Levels, Texture2DHandle* OutTexture) = 0;
        virtual void Texture3DCreate(ETextureFormat Format, uint32_t Width, uint32_t Height, uint32_t Depth, uint32_t Levels, Texture3DHandle* OutTexture) = 0;

        virtual void Texture1DSetData(Texture1DHandle& InHandle, std::vector<unsigned char>& ImageData, uint32_t Offset) = 0;
        virtual void Texture2DSetData(Texture2DHandle& InHandle, std::vector<unsigned char>& ImageData, uint32_t XOffset, uint32_t YOffset, uint32_t Width, uint32_t Height) = 0;
        virtual void Texture3DSetData(Texture3DHandle& InHandle, std::vector<unsigned char>& ImageData, uint32_t XOffset, uint32_t YOffset, uint32_t ZOffset, uint32_t Width, uint32_t Height, uint32_t Depth) = 0;

        virtual void Texture1DDestroy(Texture1DHandle& InHandle) = 0;
        virtual void Texture2DDestroy(Texture2DHandle& InHandle) = 0;
        virtual void Texture3DDestroy(Texture3DHandle& InHandle) = 0;

        virtual void RefreshDisplay() = 0;

        virtual const std::string GetRenderAPIName() = 0;;

    };

}