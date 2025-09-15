#include <glad/glad.h>
#include "xrs/Framebuffer.hpp"
#include "xrs/Texture.hpp"
#include <cstdio>
#include <cassert>

namespace xrs
{

  static inline unsigned CreateRenderbuffer(int width, int height, GLenum format)
  {
    unsigned int renderbuffer;
    glGenRenderbuffers(1, &renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    return renderbuffer;
  }

  static inline int operator&(BufferConfigFlag lhs, BufferConfigFlag rhs)
  {
    return static_cast<unsigned>(lhs) & static_cast<unsigned>(rhs);
  }

  inline bool Framebuffer::RequiresConfig(BufferConfigFlag flag) const
  {
    return m_BufferConfigFlags & flag;
  }

  Framebuffer::Framebuffer(int width, int height, unsigned int colorBufferCount, const BufferConfigFlag bufferConfigFlags)
      : m_ColorBufferCount{colorBufferCount}, m_BufferConfigFlags{bufferConfigFlags},
      m_Width{width}, m_Height{height},
      m_HasDepthBuffer{static_cast<bool>(bufferConfigFlags & (BufferConfigFlag::DEPTH_RENDER_BUFFER |
        BufferConfigFlag::DEPTH_TEXTURE_BUFFER | BufferConfigFlag::DEPTH_TEXTURE_3D_BUFFER))}
  {
    glGenFramebuffers(1, &m_FramebufferObject);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferObject);
    Configure();
    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE && "Framebuffer is incomplete!");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  Framebuffer::~Framebuffer()
  {
    glDeleteRenderbuffers(m_Renderbuffers.size(), m_Renderbuffers.data());
    glDeleteTextures(m_RenderTextures.size(), m_RenderTextures.data());
    glDeleteFramebuffers(1, &m_FramebufferObject);
  }

  void Framebuffer::Bind() const
  {
    glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferObject);
  }

  void Framebuffer::Configure()
  {
    assert(m_ColorBufferCount || m_BufferConfigFlags != BufferConfigFlag::NONE && "Failed to configure framebuffer!");
    for (size_t i = 0; i < m_ColorBufferCount; i++)
    {
      auto texture = Texture::CreateEmptyTexture2D(m_Width, m_Height);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, texture, 0);
      m_RenderTextures.push_back(texture);
    }
    if (m_BufferConfigFlags != BufferConfigFlag::NONE)
    {
      if (RequiresConfig(BufferConfigFlag::DEPTH_TEXTURE_BUFFER))
      {
        auto texture = Texture::CreateEmptyTexture2D(m_Width, m_Height, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_RenderTextures.size(), GL_TEXTURE_2D, texture, 0);
        m_RenderTextures.push_back(texture);
      }
      if (RequiresConfig(BufferConfigFlag::DEPTH_TEXTURE_3D_BUFFER))
      {
        assert(false && "Not implemented 3D depth texture");
      }
      if (RequiresConfig(BufferConfigFlag::COLOR_TEXTURE_3D_BUFFER))
      {
        assert(false && "Not implemented 3D color texture");
      }
      if (RequiresConfig(BufferConfigFlag::DEPTH_STENCIL_RENDER_BUFFER))
      {
        auto renderbuffer = CreateRenderbuffer(m_Width, m_Height, GL_DEPTH24_STENCIL8);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);
        m_Renderbuffers.push_back(renderbuffer);
      }
      else
      {
        if (RequiresConfig(BufferConfigFlag::DEPTH_RENDER_BUFFER))
        {
          auto renderbuffer = CreateRenderbuffer(m_Width, m_Height, GL_DEPTH_COMPONENT);
          glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);
          m_Renderbuffers.push_back(renderbuffer);
        }
        if (RequiresConfig(BufferConfigFlag::STENCIL_RENDER_BUFFER))
        {
          auto renderbuffer = CreateRenderbuffer(m_Width, m_Height, GL_STENCIL_COMPONENTS);
          glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);
          m_Renderbuffers.push_back(renderbuffer);
        }
      }
    }
  }

} // namespace xrs
