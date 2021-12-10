//
// Created by Htrap19 on 12/8/21.
//

#ifndef FREESIA_OPENGLVERTEXARRAY_H
#define FREESIA_OPENGLVERTEXARRAY_H

#include "Freesia/Renderer/VertexArray.h"

namespace Freesia
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray() override;

        void Bind() const override;
        void Unbind() const override;
        void AddVertexBuffer(const Ref<Freesia::VertexBuffer>& vertexBuffer) override;
        void SetIndexBuffer(const Ref<Freesia::IndexBuffer>& indexBuffer) override;
        inline const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
        inline const Ref<Freesia::IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

    private:
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;

        uint32_t m_RendererID;
        uint32_t m_VertexIndexOffset = 0;
    };
}

#endif //FREESIA_OPENGLVERTEXARRAY_H
