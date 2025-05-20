#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
Shader::Shader(const std::string& filepath)
	:m_filePath(filepath)
{
	ShaderProgramSource src = Shader::ParseShader(m_filePath);
	unsigned int shader = CreateShader(src.vertexShader, src.fragmentShader);
	m_RendererID = shader;
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

ShaderProgramSource Shader::ParseShader(const std::string& path)
{
	std::ifstream stream(path);
	std::string line;
	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};
	ShaderType type = ShaderType::NONE;
	std::stringstream ss[2];
	while (getline(stream, line))
	{
		if (line.find("shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str() , ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string source)
{
	//Create Shader Obj and replace src code
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//Error Handling
	int status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		//get log string length
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		//create log message buffer
		char* message = (char*)alloca(length * sizeof(char));

		//get message
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Error: Failed to Compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " Shader" << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string vertexShader, const std::string fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	glValidateProgram(program);
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::SetUniform4f(std::string uniform_name, float v1 , float v2 , float v3 , float v4)
{
	Bind();
	int location = GetUniformLocation(uniform_name);
	glUniform4f(location, v1, v2, v3, v4);
}

void Shader::SetUniform1f(std::string uniform_name, float v1)
{
	Bind();
	int location = GetUniformLocation(uniform_name);
	glUniform1f(location, v1);
}

void Shader::SetUniform1i(std::string uniform_name, int v)
{
	Bind();
	int location = GetUniformLocation(uniform_name);
	glUniform1i(location, v);
}


int Shader::GetUniformLocation(std::string uniform_name)
{
 	if(m_uniform_cache.find(uniform_name) != m_uniform_cache.end())
 		return m_uniform_cache[uniform_name];
	
	int location = glGetUniformLocation(m_RendererID, uniform_name.c_str());
	return m_uniform_cache[uniform_name] = location;
}
