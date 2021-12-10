//
// Created by Htrap19 on 12/8/21.
//

#ifndef FREESIA_OPENGLSHADER_H
#define FREESIA_OPENGLSHADER_H

#include <string>
#include <unordered_map>

#include "Freesia/Renderer/Shader.h"

namespace Freesia
{
    class OpenGLShader : public Shader
    {
    public:
        explicit OpenGLShader(const std::string &filepath);
        OpenGLShader(std::string name, const std::string &vertSrc, const std::string &fragSrc);
        ~OpenGLShader() override;

        void Bind() const override;
        void Unbind() const override;

        void SetInt(const std::string &name, int value) override;
        void SetIntArray(const std::string &name, int *values, uint32_t count) override;
        void SetFloat(const std::string &name, float value) override;
        void SetFloat3(const std::string &name, const glm::vec3 &value) override;
        void SetFloat4(const std::string &name, const glm::vec4 &value) override;
        void SetMat4(const std::string &name, const glm::mat4 &value) override;

        inline const std::string& GetName() const override { return m_Name; }

    private:
        std::string ReadFile(const std::string &filepath);
        std::unordered_map<std::string, std::string> PreProcess(const std::string &source);
        void Compile(const std::unordered_map<std::string, std::string> &shaderSources);

    private:
        std::string m_Name;

        uint32_t m_RendererID;
    };
}

#endif //FREESIA_OPENGLSHADER_H
