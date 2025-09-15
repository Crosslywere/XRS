#include <glad/glad.h>
#include "xrs/Texture.hpp"
#include <stb_image.h>
#include <assert.h>

namespace xrs
{

  unsigned int Texture::CreateEmptyTexture2D(int width, int height, int internalFormat, unsigned int format, unsigned int datatype)
  {
    unsigned texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, datatype, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
  }

  Texture::Texture(const std::string &pathToFile)
      : m_Target{GL_TEXTURE_2D}
  {
    int channels;
    auto data = stbi_load(pathToFile.c_str(), &m_Width, &m_Height, &channels, 0);
    assert(data && "Could not load Texture file!");
    glGenTextures(1, &m_TextureObject);
    glBindTexture(m_Target, m_TextureObject);
    glTextureParameteri(m_Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GLenum format;
    switch (channels)
    {
    case 1:
      format = GL_RED;
      break;
    case 2:
      format = GL_RG;
      break;
    case 3:
      format = GL_RGB;
      break;
    default:
      format = GL_RGBA;
    }
    glTexImage2D(m_Target, 0, GL_RGBA, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(m_Target);
    stbi_image_free(data);
    glBindTexture(m_Target, 0);
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
