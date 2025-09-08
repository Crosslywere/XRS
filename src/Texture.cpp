#include <glad/glad.h>
#include "xrs/Texture.hpp"
#include <stb_image.h>

namespace xrs
{

  unsigned int Texture::CreateTexture(int width, int height, GLenum target, GLenum format, GLenum datatype)
  {
    unsigned texture;
    glGenTextures(1, &texture);
    glBindTexture(target, texture);
    glTextureParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(target, 0, 0);
    glTexImage2D(target, 0, format, width, height, 0, format, datatype, nullptr);
    glBindTexture(target, 0);
    return texture;
  }

  Texture::Texture(const std::string &pathToFile)
      : m_Target{GL_TEXTURE_2D}
  {
  }

  Texture::~Texture()
  {
    glDeleteTextures(1, &m_TextureObject);
  }

  void Texture::Bind(unsigned int index) const
  {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(m_Target, m_TextureObject);
  }

}
