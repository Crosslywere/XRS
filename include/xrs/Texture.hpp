#pragma once

#ifndef _XRS_TEXTURE_HPP_
#define _XRS_TEXTURE_HPP_

#include <GL/gl.h>
#include <string>

namespace xrs
{

  class Texture
  {
    friend class Renderer;

  public:
    /**
     * @brief Creates an empty texture based on specified parameters
     * @param width the width of the image to be created
     * @param height the height of the image to be created
     * @param target the texture's target type. Defaults to GL_TEXTURE_2D
     * @param format the texture's data format. Defaults to GL_RGB
     * @returns The GPU texture object
     */
    static unsigned int CreateTexture(int width, int height, GLenum target = GL_TEXTURE_2D, GLenum format = GL_RGB, GLenum datatype = GL_UNSIGNED_BYTE);
    /**
     * @brief Constructor that uploads the specified by the path to the GPU
     */
    Texture(const std::string &pathToFile);
    ~Texture();
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    void Bind(unsigned int index) const;

  private:
    Texture(const Texture &) = delete;
    Texture(const Texture &&) = delete;
    Texture &operator=(const Texture &) = delete;
    const GLenum m_Target;
    int m_Width{}, m_Height{};
    unsigned m_TextureObject{};
  };

}

#endif // _XRS_TEXTURE_HPP_