#include "OGLRenderingAPI.hpp"

#include <glad/glad.h>
#include "OGLDataTypes.hpp"

namespace UTE
{
    void OGLRenderingAPI::InitializeAPI(ApplicationWindow *OwningWindow)
    {

    }

    void OGLRenderingAPI::SetupWindowFlags()
    {
    }

    void OGLRenderingAPI::CreateBuffer(uint32_t Size, RenderHandle* OutHandle)
    {
        OpenGLBuffer* NewBuffer = new OpenGLBuffer();

        glCreateBuffers(1, &NewBuffer->BufferID);
        glNamedBufferStorage(NewBuffer->BufferID, Size, nullptr, GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
        NewBuffer->BufferSize = Size;

        *OutHandle = RenderHandle(NewBuffer);
    }

    void OGLRenderingAPI::DestroyBuffer(RenderHandle& InHandle)
    {
    }
}
