#pragma once

#ifndef _XRS_FRAMEBUFFER_HPP_
#define _XRS_FRAMEBUFFER_HPP_

#include <vector>

namespace xrs
{

  enum BufferConfigFlag
  {
    NONE                        = 0,
    DEPTH_TEXTURE_BUFFER        = 0x01,
    DEPTH_RENDER_BUFFER         = 0x02,
    STENCIL_RENDER_BUFFER       = 0x04,
    DEPTH_STENCIL_RENDER_BUFFER = DEPTH_RENDER_BUFFER | STENCIL_RENDER_BUFFER,
    DEPTH_TEXTURE_3D_BUFFER     = 0x08,
    COLOR_TEXTURE_3D_BUFFER     = 0x10,
  };

  inline BufferConfigFlag operator|(BufferConfigFlag lhs, BufferConfigFlag rhs)
  {
    return static_cast<BufferConfigFlag>(static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs));
  }

  class Framebuffer
  {
    friend class Renderer;

  public:
    Framebuffer() = default;
    /**
     * @brief Constructor that creates a framebuffer based on the specifications made
     * @param width the target width
     * @param height the target height
     * @param colorBufferCount the number of color textures to attach
     * @param bufferConfigFlags specifies the buffers/textures to create
     */
    Framebuffer(int width, int height, unsigned int colorBufferCount = 1, BufferConfigFlag bufferConfigFlags = BufferConfigFlag::NONE);

    /**
     * @brief Destructor deletes the framebuffer object along with any texture and renderbuffer
     */
    ~Framebuffer();

    /**
     * @brief Binds the framebuffer as the render target
     */
    void Bind() const;
    bool RequiresConfig(BufferConfigFlag flag) const;
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }

  private:
    void Configure();
    const size_t m_ColorBufferCount{};
    const BufferConfigFlag m_BufferConfigFlags{};
    int m_Width{}, m_Height{};
    unsigned m_FramebufferObject{};
    std::vector<unsigned> m_RenderTextures;
    std::vector<unsigned> m_Renderbuffers;
    bool m_HasDepthBuffer{false};
  };

} // namespace xrs

#endif // _XRS_FRAMEBUFFER_HPP_