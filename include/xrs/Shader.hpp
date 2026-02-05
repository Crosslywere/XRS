#pragma once

#ifndef _XRS_SHADER_HPP_
#define _XRS_SHADER_HPP_

#include <unordered_map>
#include <string>
#include <GL/gl.h>
#include "Vector.hpp"
#include "Matrix.hpp"

namespace xrs
{

  class Shader
  {
  public:
    static unsigned int CompileShaderSource(const std::string &source, GLenum type);
    static unsigned int CompileShaderFile(const std::string &pathToFile, GLenum type);
    Shader(const std::initializer_list<unsigned int> &shaderParts);
    ~Shader();
    Shader() = default;
    void Use() const;
    void SetInt(const std::string &uniform, int v);
    void SetFloat(const std::string &uniform, float v);
    void SetFloat2(const std::string &uniform, const Vector2f &v2f);
    void SetFloat3(const std::string &uniform, const Vector3f &v3f);
    void SetFloat4(const std::string &uniform, const Vector4f &v4f);
    void SetMatrix(const std::string &uniform, const Matrix &mat);
  private:
    int GetUniformLocation(const std::string &);
    std::unordered_map<std::string, int> m_UniformCache;
    unsigned int m_ProgramObject{};
  };

} // namespace xrs

#endif // _XRS_SHADER_HPP_