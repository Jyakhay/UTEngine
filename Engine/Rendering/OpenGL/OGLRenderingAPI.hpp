#pragma once

#include "Rendering/RenderingAPI.hpp"
#include "Debug/DebugLog.hpp"
#include "OGLDataTypes.hpp"
namespace UTE
{

    class UTENGINE_API OGLRenderingAPI : public RenderingAPI
    {

    public:

        virtual bool InitializeAPI(std::weak_ptr<ApplicationWindow>& OwningWindow) override;
        virtual void SetupWindowFlags() override;

        virtual void SetCurrentVertexLayout(VertexLayout& NewLayout) override;
        virtual const VertexLayout& GetCurrentVertexLayout() override;

        virtual void BufferCreate(uint32_t Size, BufferHandle* OutHandle) override;
        virtual void BufferSetData(BufferHandle& InHandle, uint32_t DataSize, uint32_t Offset, void* DataPointer) override;
        virtual void BufferDestroy(BufferHandle& InHandle) override;

        virtual void Texture1DCreate(ETextureFormat Format, uint32_t Size, uint32_t Levels, Texture1DHandle* OutTexture) override;
        virtual void Texture2DCreate(ETextureFormat Format, uint32_t Width, uint32_t Height, uint32_t Levels, Texture2DHandle* OutTexture) override;
        virtual void Texture3DCreate(ETextureFormat Format, uint32_t Width, uint32_t Height, uint32_t Depth, uint32_t Levels, Texture3DHandle* OutTexture) override;

        virtual void Texture1DSetData(Texture1DHandle& InHandle, std::vector<unsigned char>& ImageData, uint32_t Offset) override;
        virtual void Texture2DSetData(Texture2DHandle& InHandle, std::vector<unsigned char>& ImageData, uint32_t XOffset, uint32_t YOffset, uint32_t Width, uint32_t Height) override;
        virtual void Texture3DSetData(Texture3DHandle& InHandle, std::vector<unsigned char>& ImageData, uint32_t XOffset, uint32_t YOffset, uint32_t ZOffset, uint32_t Width, uint32_t Height, uint32_t Depth) override;

        virtual void Texture1DDestroy(Texture1DHandle& InHandle) = 0;
        virtual void Texture2DDestroy(Texture2DHandle& InHandle) = 0;
        virtual void Texture3DDestroy(Texture3DHandle& InHandle) = 0;

        virtual void RefreshDisplay() override;

        virtual const std::string GetRenderAPIName() override;

    private:

        static void DebugLogCallback(uint32_t Source, uint32_t Type, uint32_t ID, uint32_t Severity, int Length, const char* Message, const void* UserParams);
        static std::string OpenGLSourceToString(uint32_t Source);
        static std::string OpenGLMessageTypeToString(uint32_t Type);
        static ELogSeverity OpenGLSeverityToLogSeverity(uint32_t Severity);

        uint32_t GetOpenGLVertexDataType(EVertexDataType DataType);

        uint32_t GetOpenGLInternalFormatType(ETextureFormat Format);
        uint32_t GetOpenGLFormatType(ETextureFormat Format);

        GLTypes::OpenGLState GraphicsState;

    };

}