#include "slpch.h"

#include <glad/glad.h>
#include <fstream>

#include "ShaderUtils.h"

namespace Solar
{
    namespace ShaderUtils
    {
        uint32_t CompileShader(uint32_t type, const std::string& source)
        {
            uint32_t id = glCreateShader(type);
            const char* src = source.c_str();
            glShaderSource(id, 1, &src, nullptr);
            glCompileShader(id);

            int result;
            glad_glGetShaderiv(id, GL_COMPILE_STATUS, &result);
            if (result == GL_FALSE)
            {
                int length;
                glad_glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
                //alloca - stack allocation
                char* message = (char*)_malloca(length * sizeof(char));
                glGetShaderInfoLog(id, length, &length, message);

                SL_CORE_ERROR("Failed to compile {0} shader", type);
                SL_CORE_ERROR("Error message: {0}", message);
                SL_CORE_ASSERT(false);

                glDeleteShader(id);
                return 0;
            }

            return id;
        }

        uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
        {
            uint32_t program = glCreateProgram();
            uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
            uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

            glAttachShader(program, vs);
            glAttachShader(program, fs);
            glLinkProgram(program);
            glValidateProgram(program);

            glDeleteShader(vs);
            glDeleteShader(fs);

            return program;
        }

        ShaderData ParseShader(const std::string& filePath)
        {
            if (!std::filesystem::exists(filePath))
            {
                SL_CORE_ERROR("Invalid Path: {0}", filePath);
                SL_CORE_ASSERT(false);
            }

            std::ifstream stream(filePath);
            std::stringstream ss[2];

            enum class ShaderType
            {
                NONE = -1,
                VERTEX = 0,
                FRAGMENT = 1
            };

            ShaderType type = ShaderType::NONE;

            std::string line;
            while (getline(stream, line))
            {
                if (line.find("#shader") != std::string::npos)
                {
                    if (line.find("vertex") != std::string::npos)
                        type = ShaderType::VERTEX;
                    else if (line.find("fragment") != std::string::npos)
                        type = ShaderType::FRAGMENT;
                }
                else
                {
                    ss[static_cast<int>(type)] << line << "\n";
                }
            }

            return { ss[0].str(), ss[1].str() };
        }
    }
}