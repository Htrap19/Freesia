//
// Created by Htrap19 on 12/10/21.
//

#ifndef FREESIA_TEXTURE_H
#define FREESIA_TEXTURE_H

#include "Freesia/Core/Core.h"

namespace Freesia
{
    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual uint32_t GetRendererID() const = 0;
        virtual const std::string& GetPath() const = 0;

        virtual void SetData(void* data, size_t size) = 0;
        virtual void* GetData() = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;

        virtual bool operator==(const Texture& other) const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(uint32_t width, uint32_t height);
        static Ref<Texture2D> Create(const std::string& path, bool flip = true);
    };
}

#endif //FREESIA_TEXTURE_H
