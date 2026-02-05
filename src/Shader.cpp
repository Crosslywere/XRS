#include <glad/glad.h>
#include "xrs/Shader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

namespace xrs
{

  static void ValidateShader(unsigned shader)
  {
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      char *infoLog = new char[1024];
      glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
      std::printf("Shader Compilation Error\n%s\n", infoLog);
    }
  }

  static void ValidateProgram(unsigned program)
  {
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
      char *infoLog = new char[1024];
      glGetProgramInfoLog(program, 1024, nullptr, infoLog);
      std::printf("Shader Program Linking Error\n%s\n", infoLog);
    }
  }

  unsigned int Shader::CompileShaderSource(const std::string &source, GLenum type)
  {
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    ValidateShader(shader);
    return shader;
  }

  unsigned int Shader::CompileShaderFile(const std::string &pathToFile, GLenum type)
  {
    std::fstream file;
    file.open(pathToFile);
    if (file.is_open())
    {
      std::stringstream ss;
      ss << file.rdbuf();
      file.close();
      return CompileShaderSource(ss.str(), type);
    }
    std::printf("Failed to find file located at '%s'", pathToFile.c_str());
    return 0;
  }

  Shader::Shader(const std::initializer_list<unsigned int> &shaderParts)
  {
    m_ProgramObject = glCreateProgram();
    for (auto part : shaderParts)
    {
      glAttachShader(m_ProgramObject, part);
    }
    glLinkProgram(m_ProgramObject);
    ValidateProgram(m_ProgramObject);
  }

  Shader::~Shader()
  {
    glDeleteProgram(m_ProgramObject);
  }

  void Shader::Use() const
  {
    glUseProgram(m_ProgramObject);
  }

  void Shader::SetInt(const std::string &uniform, int v)
  {
    glUniform1i(GetUniformLocation(uniform), v);
  }

  void Shader::SetFloat(const std::string &uniform, float v)
  {
    glUniform1f(GetUniformLocation(uniform), v);
  }

  void Shader::SetFloat2(const std::string &uniform, const Vector2f &v2f)
  {
    glUniform2fv(GetUniformLocation(uniform), 1, &v2f.x);
  }

  void Shader::SetFloat3(const std::string &uniform, const Vector3f &v3f)
  {
    glUniform3f(GetUniformLocation(uniform), v3f.x, v3f.y, v3f.z);
  }

  void Shader::SetFloat4(const std::string &uniform, const Vector4f &v4f)
  {
    glUniform4f(GetUniformLocation(uniform), v4f.x, v4f.y, v4f.z, v4f.w);
  }

  void Shader::SetMatrix(const std::string &uniform, const Matrix &mat)
  {
    glUniformMatrix4fv(GetUniformLocation(uniform), 1, false, mat.data.mem);
  }

  int Shader::GetUniformLocation(const std::string &uniform)
  {
    if (m_UniformCache.find(uniform) == m_UniformCache.end())
    {
      int loc = glGetUniformLocation(m_ProgramObject, uniform.c_str());
      m_UniformCache.emplace(std::make_pair(uniform, loc));
      if (loc < 0)
        std::printf("Uniform '%s' is not in use or is not decleared in the shader\n", uniform.c_str());
      return loc;
    }
    return m_UniformCache.at(uniform);
  }

} // namespace xrs
