#pragma once
#include <string>
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Maths.h>

static struct ShaderProgramSource {
	std::string vertexShader;
	std::string fragmentShader;
};

class Shader {
private:
	std::string m_filePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_uniform_cache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;


	ShaderProgramSource ParseShader(const std::string& path);
	unsigned int CompileShader(unsigned int type, const std::string source);
	unsigned int CreateShader(const std::string vertexShader, const std::string fragmentShader);

	void SetUniform4f(std::string uniform_name, float v1, float v2, float v3, float v4);
	void SetUniform1f(std::string uniform_name, float v1);
	void SetUniform1i(std::string uniform_name, int v);
	void SetUniform4mat(std::string uniform_name, mat4 v);
	int GetUniformLocation(std::string uniform_name);
};