//
// Created by Htrap19 on 12/8/21.
//

#ifndef FREESIA_VERTEXARRAY_H
#define FREESIA_VERTEXARRAY_H

#include "Freesia/Core/Core.h"

#include "Freesia/Renderer/Buffer.h"

namespace Freesia
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

        virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

        static Ref<VertexArray> Create();
    };
}

#endif //FREESIA_VERTEXARRAY_H
