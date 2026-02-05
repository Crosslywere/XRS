#include <glad/glad.h>
#include "xrs/Renderer.hpp"
#include <cstdio>
#include <cassert>

namespace xrs
{
  static Framebuffer *g_Framebuffer = nullptr;
  static Mesh *g_Mesh = nullptr;
  static Shader *g_Shader = nullptr;

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
    g_Mesh->Draw(*g_Shader);
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
      // g_Framebuffer = new Framebuffer(viewport[2], viewport[3], 1, BufferConfigFlag::DEPTH_RENDER_BUFFER);
      g_Mesh = new Mesh();
      g_Shader = new Shader({
        Shader::CompileShaderSource(
          R"(#version 330 core
          layout (location = 0) in vec2 aPosition;
          void main() {
          gl_Position = vec4(aPosition, 0.0, 1.0);
          })",
          GL_VERTEX_SHADER
        ),
        Shader::CompileShaderSource(
          R"(#version 330 core
          void main() {
          gl_FragColor = vec4(1.0);
          })",
          GL_FRAGMENT_SHADER
        )
      });
    }
  }

} // namespace xrs