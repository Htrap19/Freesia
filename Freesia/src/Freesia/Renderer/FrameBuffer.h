//
// Created by htrap19 on 12/15/21.
//

#ifndef FREESIA_FRAMEBUFFER_H
#define FREESIA_FRAMEBUFFER_H

#include "Freesia/Core/Core.h"

namespace Freesia
{
    struct FrameBufferSpecification
    {
        uint32_t Width = 0, Height = 0;
        uint32_t Samples = 1;
        bool SwapChainTarget = false;
    };

    class FrameBuffer
    {
    public:
        virtual ~FrameBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void Resize(uint32_t width, uint32_t height) = 0;

        virtual uint32_t GetColorAttachmentRendererID() const = 0;
        virtual const FrameBufferSpecification& GetSpecification() const = 0;

        static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);
    };
}

#endif //FREESIA_FRAMEBUFFER_H
