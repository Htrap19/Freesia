//
// Created by Htrap19 on 12/8/21.
//

#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Freesia
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:
                return GL_FLOAT;
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
                return GL_INT;
            case ShaderDataType::Bool:
                return GL_BOOL;

            default:
                break;
        }

        FS_CORE_ASSERT(false);
        return GL_NONE;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &m_RendererID);
        glBindVertexArray(m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        FS_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");

        Bind();
        vertexBuffer->Bind();

        auto& layout = vertexBuffer->GetLayout();
        for (auto& element : layout)
        {
            switch (element.Type)
            {
                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4:
                {
                    glEnableVertexAttribArray(m_VertexIndexOffset);
                    glVertexAttribPointer(m_VertexIndexOffset,
                                          (GLint)element.GetComponentCount(),
                                          ShaderDataTypeToOpenGLBaseType(element.Type),
                                          (element.Normalized ? GL_TRUE : GL_FALSE),
                                          (GLsizei)layout.GetStride(),
                                          (const void*)element.Offset);
                    m_VertexIndexOffset++;
                    break;
                }
                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                case ShaderDataType::Bool:
                {
                    glEnableVertexAttribArray(m_VertexIndexOffset);
                    glVertexAttribIPointer(m_VertexIndexOffset,
                                          (GLint)element.GetComponentCount(),
                                          ShaderDataTypeToOpenGLBaseType(element.Type),
                                          (GLsizei)layout.GetStride(),
                                          (const void*)element.Offset);
                    m_VertexIndexOffset++;
                    break;
                }
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4:
                {
                    uint32_t count = (element.Type == ShaderDataType::Mat3) ? 3 : 4;
                    for (uint32_t i = 0; i < count; i++)
                    {
                        glEnableVertexAttribArray(m_VertexIndexOffset);
                        glVertexAttribPointer(m_VertexIndexOffset,
                                              (GLint)count,
                                              ShaderDataTypeToOpenGLBaseType(element.Type),
                                              (element.Normalized ? GL_TRUE : GL_FALSE),
                                              (GLsizei)layout.GetStride(),
                                              (const void*)(element.Offset + sizeof(float) * count * i));
                        glVertexAttribDivisor(m_VertexIndexOffset, 1);
                        m_VertexIndexOffset++;
                    }
                    break;
                }

                default:
                    FS_CORE_ASSERT(false);
                    break;
            }
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        Bind();
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }
}