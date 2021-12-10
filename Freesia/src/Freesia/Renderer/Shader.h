//
// Created by Htrap19 on 12/8/21.
//

#ifndef FREESIA_SHADER_H
#define FREESIA_SHADER_H

#include <glm/glm.hpp>

#include "Freesia/Core/Core.h"

namespace Freesia
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetInt(const std::string& name, int value) = 0;
        virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
        virtual void SetFloat(const std::string& name, float value) = 0;
        virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
        virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
        virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

        virtual const std::string& GetName() const = 0;

        static Ref<Shader> Create(const std::string& filepath);
        static Ref<Shader> Create(std::string name, const std::string& vertSrc, const std::string& fragSrc);
    };
}

#endif //FREESIA_SHADER_H
