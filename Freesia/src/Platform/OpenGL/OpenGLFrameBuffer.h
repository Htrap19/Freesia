//
// Created by htrap19 on 12/15/21.
//

#ifndef FREESIA_OPENGLFRAMEBUFFER_H
#define FREESIA_OPENGLFRAMEBUFFER_H

#include "Freesia/Renderer/FrameBuffer.h"

namespace Freesia
{
    class OpenGLFrameBuffer : public FrameBuffer
    {
    public:
        explicit OpenGLFrameBuffer(const FrameBufferSpecification& spec);
        ~OpenGLFrameBuffer() override;

        void Invalidate();

        void Bind() const override;
        void Unbind() const override;

        void Resize(uint32_t width, uint32_t height) override;

        inline uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
        inline const FrameBufferSpecification& GetSpecification() const override { return m_Specification; }

    private:
        FrameBufferSpecification m_Specification;
        uint32_t m_ColorAttachment, m_DepthAttachment;

        uint32_t m_RendererID;
    };
}

#endif //FREESIA_OPENGLFRAMEBUFFER_H
