//
// Created by Htrap19 on 12/10/21.
//

#include "OpenGLTexture.h"
#include <glad/glad.h>
#include <stb_image.h>

#include "Freesia/Core/Assert.h"

namespace Freesia
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path, bool flip)
        : m_Path(path)
    {
        int width, height, nChannels;
        stbi_set_flip_vertically_on_load(flip);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &nChannels, 0);
        FS_CORE_ASSERT(data, "Failed to load texture!");
        m_Width = width;
        m_Height = height;

        GLenum internalFormat = GL_NONE, dataFormat = GL_NONE;
        if (nChannels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (nChannels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }
        FS_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");
        m_InternalFormat = internalFormat;
        m_DataFormat = dataFormat;

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, (GLint)internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
        : m_Width(width), m_Height(height)
    {
        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::SetData(void* data, size_t size)
    {
        uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
        FS_CORE_ASSERT(size == m_Width * m_Height * bpp, "Entire texture must be loaded!");
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        glTexImage2D(GL_TEXTURE_2D, 0, (GLint)m_InternalFormat, (GLsizei)m_Width, (GLsizei)m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }

    void* OpenGLTexture2D::GetData()
    {
        GLvoid* imgData = nullptr;
        glGetTexImage(GL_TEXTURE_2D, 0, m_DataFormat, GL_UNSIGNED_BYTE, imgData);
        return imgData;
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }
}