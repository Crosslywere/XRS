#include "xrs/Framebuffer.hpp"
#include <glad/glad.h>
#include <cstdio>

namespace xrs
{

  inline int operator&(BufferConfigFlags lhs, BufferConfigFlags rhs)
  {
    return static_cast<unsigned>(lhs) & static_cast<unsigned>(rhs);
  }

  Framebuffer::Framebuffer(int width, int height, unsigned int colorBufferCount, const BufferConfigFlags bufferConfigFlags)
      : m_ColorBufferCount{colorBufferCount}, m_BufferConfigFlags{bufferConfigFlags},
      m_Width{width}, m_Height{height},
      m_HasDepthBuffer{bufferConfigFlags & (BufferConfigFlags::DEPTH_RENDER_BUFFER | BufferConfigFlags::DEPTH_TEXTURE_BUFFER | BufferConfigFlags::DEPTH_TEXTURE_3D_BUFFER)}
  {
    if (m_HasDepthBuffer)
      std::printf("Framebuffer created has depth buffer!");
  }

  Framebuffer::~Framebuffer()
  {
  }

  void Framebuffer::Bind() const
  {
  }

} // namespace xrs
