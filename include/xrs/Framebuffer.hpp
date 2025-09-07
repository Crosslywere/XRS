#pragma once

#ifndef _FRAMEBUFFER_HPP_
#define _FRAMEBUFFER_HPP_

#include <vector>

namespace xrs
{

  enum class BufferConfigFlags
  {
    NONE                        = 0,
    DEPTH_TEXTURE_BUFFER        = 0x1,
    DEPTH_RENDER_BUFFER         = 0x2,
    STENCIL_RENDER_BUFFER       = 0x4,
    DEPTH_STENCIL_RENDER_BUFFER = DEPTH_RENDER_BUFFER | STENCIL_RENDER_BUFFER,
    DEPTH_TEXTURE_3D_BUFFER     = 0x8,
  };

  inline BufferConfigFlags operator|(BufferConfigFlags lhs, BufferConfigFlags rhs)
  {
    return static_cast<BufferConfigFlags>(static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs));
  }

  class Framebuffer
  {
    friend class Renderer;
  public:
    Framebuffer(int width, int height, unsigned int colorBufferCount = 1, BufferConfigFlags bufferConfigFlags = BufferConfigFlags::NONE);
    Framebuffer(const Framebuffer &) = delete;
    Framebuffer(const Framebuffer &&) = delete;
    Framebuffer &operator=(const Framebuffer &) = delete;
    ~Framebuffer();
    void Bind() const;
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
  private:
    const size_t m_ColorBufferCount;
    const BufferConfigFlags m_BufferConfigFlags;
    int m_Width{}, m_Height{};
    unsigned m_FramebufferObject{};
    std::vector<unsigned> m_RenderTextures;
    std::vector<unsigned> m_RenderBuffers;
    bool m_HasDepthBuffer{false};
  };

} // namespace xrs

#endif // _FRAMEBUFFER_HPP_