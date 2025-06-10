#include "OGLRenderingAPI.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Platform/ApplicationWindow.hpp"
#include "Rendering/RenderManager.hpp"

namespace UTE
{

    UTENGINE_DEFINE_LOG_SOURCE(LogOpenGLAPI, "OpenGL")

    bool OGLRenderingAPI::InitializeAPI(std::weak_ptr<ApplicationWindow>& OwningWindow)
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            UTENGINE_LOG(LogOpenGLAPI, ELogSeverity::Error, "Failed to initialize OpenGL context.");
            return false;
        }

        GraphicsState.WindowContext = OwningWindow;
        glCreateVertexArrays(1, &GraphicsState.VertexArrayObject);
        glBindVertexArray(GraphicsState.VertexArrayObject);

        glEnable(GL_DEPTH_TEST);

        /*TODO - Debug Output should be optional.*/
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        glDebugMessageCallback(&OGLRenderingAPI::DebugLogCallback, nullptr);

        return true;
    }

    void OGLRenderingAPI::SetupWindowFlags()
    {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    }

    void OGLRenderingAPI::SetCurrentVertexLayout(VertexLayout& NewLayout)
    {
        GraphicsState.CurrentVertexLayout = NewLayout;

        for (uint32_t i = 0; i < NewLayout.GetNumElements(); i++)
        {
            const VertexElement& CurrentElement = NewLayout.GetElementAtIndex(i);

            glEnableVertexArrayAttrib(GraphicsState.VertexArrayObject, i);
            glVertexArrayAttribFormat(GraphicsState.VertexArrayObject, i, CurrentElement.Components, GetOpenGLVertexDataType(CurrentElement.DataType), GL_FALSE, CurrentElement.Offset);
            glVertexArrayAttribBinding(GraphicsState.VertexArrayObject, i, 0);
        }
    }

    const VertexLayout& OGLRenderingAPI::GetCurrentVertexLayout()
    {
        return GraphicsState.CurrentVertexLayout;
    }

    void OGLRenderingAPI::CreateBuffer(uint32_t Size, BufferHandle* OutHandle)
    {
        GLTypes::OpenGLBuffer* NewBuffer = new GLTypes::OpenGLBuffer();

        glCreateBuffers(1, &NewBuffer->BufferID);
        glNamedBufferStorage(NewBuffer->BufferID, Size, nullptr, GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
        NewBuffer->BufferSize = Size;

        *OutHandle = BufferHandle
        (
            NewBuffer, 
            [&](RenderHandle& InHandle) 
            {
                RenderManager::GetRenderingAPI()->DestroyBuffer(InHandle); 
            }
        );
    }

    void OGLRenderingAPI::SetBufferData(BufferHandle& InHandle, uint32_t DataSize, uint32_t Offset, void* DataPointer)
    {
        GLTypes::OpenGLBuffer* Buffer = InHandle.Cast<GLTypes::OpenGLBuffer>();
        glNamedBufferSubData(Buffer->BufferID, Offset, DataSize, DataPointer);
    }

    void OGLRenderingAPI::DestroyBuffer(BufferHandle& InHandle)
    {
        GLTypes::OpenGLBuffer* Buffer = InHandle.Cast<GLTypes::OpenGLBuffer>();
        glDeleteBuffers(1, &Buffer->BufferID);

        delete Buffer;
    }

    void OGLRenderingAPI::RefreshDisplay()
    {
        glfwSwapBuffers(GraphicsState.WindowContext.lock()->GetInternalWindow());
    }

    const std::string OGLRenderingAPI::GetRenderAPIName()
    {
        return "OpenGL";
    }

    void OGLRenderingAPI::DebugLogCallback(uint32_t Source, uint32_t Type, uint32_t ID, uint32_t Severity, int Length, const char* Message, const void* UserParams)
    {
        /*TODO - Allow user to specifiy a minimum severity.*/
        UTENGINE_LOGFMT(LogOpenGLAPI, OpenGLSeverityToLogSeverity(Severity), "[Source: {} | Type: {}] {}", OpenGLSourceToString(Source), OpenGLMessageTypeToString(Type), Message);
    }

    std::string OGLRenderingAPI::OpenGLSourceToString(uint32_t Source)
    {
        switch (Source)
        {
            case GL_DEBUG_SOURCE_API:
            {
                return "API";
            }

            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            {
                return "WindowSystem";
            }

            case GL_DEBUG_SOURCE_SHADER_COMPILER:
            {
                return "ShaderCompiler";
            }

            case GL_DEBUG_SOURCE_THIRD_PARTY:
            {
                return "ThirdParty";
            }

            case GL_DEBUG_SOURCE_APPLICATION:
            {
                return "Application";
            }

            case GL_DEBUG_SOURCE_OTHER:
            {
                return "Other";
            }
        }

        return std::string();
    }

    std::string OGLRenderingAPI::OpenGLMessageTypeToString(uint32_t Type)
    {
        switch (Type)
        {
            case GL_DEBUG_TYPE_ERROR:
            {
                return "Error";
            }

            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            {
                return "Deprecated";
            }

            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            {
                return "Undefined";
            }

            case GL_DEBUG_TYPE_PORTABILITY:
            {
                return "Portability";
            }

            case GL_DEBUG_TYPE_PERFORMANCE:
            {
                return "Performance";
            }

            case GL_DEBUG_TYPE_MARKER:
            {
                return "Marker";
            }

            case GL_DEBUG_TYPE_PUSH_GROUP:
            {
                return "Push Group";
            }

            case GL_DEBUG_TYPE_POP_GROUP:
            {
                return "Pop Group";
            }

            case GL_DEBUG_TYPE_OTHER:
            {
                return "Other";
            }
        }

        return std::string();
    }

    ELogSeverity OGLRenderingAPI::OpenGLSeverityToLogSeverity(uint32_t Severity)
    {
        switch (Severity)
        {
            case GL_DEBUG_SEVERITY_HIGH:
            {
                return ELogSeverity::Error;
            }

            case GL_DEBUG_SEVERITY_MEDIUM:
            {
                return ELogSeverity::Warning;
            }

            case GL_DEBUG_SEVERITY_LOW:
            {
                return ELogSeverity::Message;
            }

            case GL_DEBUG_SEVERITY_NOTIFICATION:
            {
                return ELogSeverity::Warning;
            }
        }

        return ELogSeverity::Message;
    }

    uint32_t OGLRenderingAPI::GetOpenGLVertexDataType(EVertexDataType DataType)
    {
        switch (DataType)
        {
        case EVertexDataType::Byte:
        {
            return GL_BYTE;
        }

        case EVertexDataType::Short:
        {
            return GL_SHORT;
        }

        case EVertexDataType::Int:
        {
            return GL_INT;
        }

        case EVertexDataType::Float:
        {
            return GL_FLOAT;
        }

        case EVertexDataType::Double:
        {
            return GL_DOUBLE;
        }
        }

        return 0;
    }
}
