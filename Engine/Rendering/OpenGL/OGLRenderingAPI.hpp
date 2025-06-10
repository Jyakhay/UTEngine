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

        virtual void CreateBuffer(uint32_t Size, BufferHandle* OutHandle) override;
        virtual void SetBufferData(BufferHandle& InHandle, uint32_t DataSize, uint32_t Offset, void* DataPointer);
        virtual void DestroyBuffer(BufferHandle& InHandle) override;

        virtual void RefreshDisplay() override;

        virtual const std::string GetRenderAPIName() override;

    private:

        static void DebugLogCallback(uint32_t Source, uint32_t Type, uint32_t ID, uint32_t Severity, int Length, const char* Message, const void* UserParams);
        static std::string OpenGLSourceToString(uint32_t Source);
        static std::string OpenGLMessageTypeToString(uint32_t Type);
        static ELogSeverity OpenGLSeverityToLogSeverity(uint32_t Severity);

        static uint32_t GetOpenGLVertexDataType(EVertexDataType DataType);

        GLTypes::OpenGLState GraphicsState;

    };

}