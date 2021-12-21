//
// Created by Htrap19 on 12/10/21.
//

#ifndef FREESIA_OPENGLTEXTURE_H
#define FREESIA_OPENGLTEXTURE_H

#include <string>

#include "Freesia/Renderer/Texture.h"

namespace Freesia
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        explicit OpenGLTexture2D(const std::string& path, bool flip = true);
        OpenGLTexture2D(uint32_t width, uint32_t height);
        ~OpenGLTexture2D() override;

        inline uint32_t GetWidth() const override { return m_Width; }
        inline uint32_t GetHeight() const override { return m_Height; }
        inline uint32_t GetRendererID() const override { return m_RendererID; }
        inline const std::string& GetPath() const override { return m_Path; }

        void SetData(void *data, size_t size) override;
        void Bind(uint32_t slot = 0) const override;
        inline bool operator==(const Texture &other) const override { return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID; }

    private:
        uint32_t m_Width, m_Height;
        uint32_t m_RendererID;
        std::string m_Path;
        uint32_t m_InternalFormat, m_DataFormat;
    };
}

#endif //FREESIA_OPENGLTEXTURE_H
