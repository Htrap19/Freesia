//
// Created by Htrap19 on 12/8/21.
//

#ifndef FREESIA_OPENGLBUFFER_H
#define FREESIA_OPENGLBUFFER_H

#include "Freesia/Renderer/Buffer.h"

namespace Freesia
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        explicit OpenGLVertexBuffer(size_t size);
        OpenGLVertexBuffer(float* vertices, size_t size);
        ~OpenGLVertexBuffer() override;

        void Bind() const override;
        void Unbind() const override;
        void SetData(const void* data, size_t size, size_t offset = 0) override;
        inline void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
        inline const BufferLayout& GetLayout() const override { return m_Layout; }

    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        explicit OpenGLIndexBuffer(uint32_t count);
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        ~OpenGLIndexBuffer() override;

        void Bind() const override;
        void Unbind() const override;
        void SetData(const void* data, uint32_t count, uint32_t offsetCount) override;
        inline uint32_t GetCount() const override { return m_Count; }

    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };
}

#endif //FREESIA_OPENGLBUFFER_H
