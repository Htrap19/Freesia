//
// Created by Htrap19 on 12/8/21.
//

#include "OpenGLShader.h"

#include <glad/glad.h>
#include <fstream>
#include <utility>
#include <glm/gtc/type_ptr.hpp>

#include "Freesia/Core/Assert.h"

namespace Freesia
{
    static GLenum ShaderTypeFromString(const std::string& type)
    {
        if (type == "vertex")
            return GL_VERTEX_SHADER;
        else if (type == "fragment" || type == "pixel")
            return GL_FRAGMENT_SHADER;

        return 0;
    }

    OpenGLShader::OpenGLShader(const std::string& filepath)
    {
        auto source = ReadFile(filepath);
        auto shaderSources = PreProcess(source);
        Compile(shaderSources);

        // Extract name from path
        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind('.');
        auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
        m_Name = filepath.substr(lastSlash, count);
    }

    OpenGLShader::OpenGLShader(std::string name, const std::string& vertSrc, const std::string& fragSrc)
        : m_Name(std::move(name))
    {
        std::unordered_map<std::string, std::string> shaders;
        shaders["vertex"] = vertSrc;
        shaders["fragment"] = fragSrc;
        Compile(shaders);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_RendererID);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::SetInt(const std::string& name, int value)
    {
        GLint location =  glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
    {
        GLint location =  glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1iv(location, (GLsizei)count, values);
    }

    void OpenGLShader::SetFloat(const std::string& name, float value)
    {
        GLint location =  glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
    {
        GLint location =  glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
    {
        GLint location =  glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
    {
        GLint location =  glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    std::string OpenGLShader::ReadFile(const std::string &filepath)
    {
        std::ifstream in(filepath, std::ios::in | std::ios::binary);
        std::string result;
        if (in)
        {
            in.seekg(0, std::ios::end);
            size_t size = in.tellg();
            if (size != -1)
            {
                result.resize(size);
                in.seekg(0, std::ios::beg);
                in.read(&result[0], (std::streamsize)result.size());
            }
            else
                FS_CORE_ERROR("Failed to read file: {0}", filepath.c_str());
        }
        else
            FS_CORE_ERROR("Failed to open file: {0}", filepath.c_str());

        return result;
    }

    std::unordered_map<std::string, std::string> OpenGLShader::PreProcess(const std::string& source)
    {
        std::unordered_map<std::string, std::string> shaderSource;

        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0);
        while (pos != std::string::npos)
        {
            size_t eo1 = source.find_first_of("\r\n", pos);
            FS_CORE_ASSERT(eo1 != std::string::npos, "Syntax error!");
            size_t begin = pos + typeTokenLength + 1;
            std::string type = source.substr(begin, eo1 - begin);
            FS_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified!");

            size_t nextLinePos = source.find_first_not_of("\r\n", eo1);
            pos = source.find(typeToken, nextLinePos);
            shaderSource[type] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
        }

        return shaderSource;
    }

    void OpenGLShader::Compile(const std::unordered_map<std::string, std::string>& shaderSources)
    {
        m_RendererID = glCreateProgram();
        FS_CORE_ASSERT((shaderSources.size() <= 2), "Only support 2 shaders!");

        std::array<GLuint, 2> shaderIds = {};
        int shaderIndex = 0;
        for (auto& [type, source] : shaderSources)
        {
            GLenum shaderType = ShaderTypeFromString(type);
            const std::string& src = source;

            GLuint shader = glCreateShader(shaderType);
            const GLchar* shaderSrcCStr = src.c_str();
            glShaderSource(shader, 1, &shaderSrcCStr, nullptr);
            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
                char* msg = (char*)alloca(maxLength * sizeof(GLchar));
                glGetShaderInfoLog(shader, maxLength, &maxLength, msg);

                glDeleteShader(shader);

                FS_CORE_ERROR("{0}", msg);
                FS_CORE_ASSERT(false, "Failed to compile shader!");
                break;
            }

            glAttachShader(m_RendererID, shader);
            shaderIds[shaderIndex++] = shader;
        }

        glLinkProgram(m_RendererID);

        GLint isLinked = 0;
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);

        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);
            char* msg = (char*)alloca(maxLength * sizeof(GLchar));
            glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, msg);

            glDeleteProgram(m_RendererID);

            for (auto& id : shaderIds)
                glDeleteShader(id);

            FS_CORE_ERROR("{0}", msg);
            FS_CORE_ASSERT(false, "Shader link failure!");
            return;
        }

        for (auto& id : shaderIds)
            glDetachShader(m_RendererID, id);
    }
}