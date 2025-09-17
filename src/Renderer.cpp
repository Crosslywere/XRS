#include <glad/glad.h>
#include "xrs/Renderer.hpp"
#include <cstdio>
#include <cassert>

namespace xrs
{
  static Framebuffer *g_Framebuffer = nullptr;

  Renderer &Renderer::Initialize(bool loadGL, const GLLoaderFunc &loader)
  {
    static auto renderer = new Renderer{loadGL, loader};
    return *renderer;
  }

  void Renderer::Shutdown()
  {
    delete g_Framebuffer;
  }

  void Renderer::BeginFrame() const
  {
    if (g_Framebuffer)
    {
      g_Framebuffer->Bind();
      if (g_Framebuffer->RequiresConfig(DEPTH_RENDER_BUFFER | DEPTH_TEXTURE_3D_BUFFER | DEPTH_TEXTURE_BUFFER))
        glEnable(GL_DEPTH_TEST);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  }

  void Renderer::EndFrame() const
  {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  Renderer::Renderer(bool loadGL, const GLLoaderFunc &loader)
  {
    if (loadGL)
    {
      int success = loader ? gladLoadGLLoader(loader) : gladLoadGL();
      assert(success && "Failed to load OpenGL functions!");
      std::printf("Loaded OpenGL Version :: %s\n", glGetString(GL_VERSION));
      int viewport[4];
      glGetIntegerv(GL_VIEWPORT, viewport);
      g_Framebuffer = new Framebuffer(viewport[2], viewport[3], 1, BufferConfigFlag::DEPTH_RENDER_BUFFER);
    }
  }

} // namespace xrs