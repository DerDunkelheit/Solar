#include "slpch.h"

#include <glad/glad.h>

#include "Shader.h"
#include "Utils/ShaderUtils.h"

namespace Solar
{
	Shader::Shader(ShaderData data)
	{
		mRendererId = ShaderUtils::CreateShader(data.VertexShader, data.FragmentShader);
	}

	void Shader::Bind() const
	{
		glUseProgram(mRendererId);
	}
	
	void Shader::UnBind() const
	{
		glUseProgram(0);
	}

	void Shader::setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(mRendererId, name.c_str()), value);
	}

	void Shader::SetInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(mRendererId, name.c_str()), value);
	}

	int Shader::GetLocation(const char* variableName) const
	{
		//TODO: assert for invalid location.
		const int location = glGetUniformLocation(mRendererId, variableName);
		glUniform4f(location, 0.4f, 0.2f, 0.8f, 1.0f);

		return location;
	}
}
