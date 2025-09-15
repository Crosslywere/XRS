#pragma once

#ifndef _XRS_TEXTURE_HPP_
#define _XRS_TEXTURE_HPP_

#include <GL/gl.h>
#include <string>

namespace xrs
{

  class Texture
  {
  public:
    /**
     * @brief Creates an empty texture based on specified parameters
     * @param width the width of the image to be created
     * @param height the height of the image to be created
     * @param target the texture's target type. Defaults to GL_TEXTURE_2D
     * @param format the texture's data format. Defaults to GL_RGB
     * @returns The GPU texture object
     */
    static unsigned int CreateEmptyTexture2D(int width, int height, int internalFormat = GL_RGBA8, unsigned int format = GL_RGBA, unsigned int datatype = GL_UNSIGNED_BYTE);

    /**
     * @brief Constructor that uploads the specified by the path to the GPU
     * @param pathToFile the path to the texture file from workspace directory
     */
    Texture() = default;
    Texture(const std::string &pathToFile);
    ~Texture();
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    void Bind(unsigned int index) const;

  private:
    const GLenum m_Target{};
    int m_Width{}, m_Height{};
    unsigned m_TextureObject{};
  };

}

#endif // _XRS_TEXTURE_HPP_