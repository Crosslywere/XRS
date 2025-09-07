#include "xrs/Renderer.hpp"
#include <glad/glad.h>
#include <cstdio>
#include <cassert>

namespace xrs
{

  Renderer &Renderer::Initialize(bool loadGL, const GLLoaderFunc &loader)
  {
    static auto renderer = new Renderer{loadGL, loader};
    return *renderer;
  }

  void Renderer::Shutdown()
  {
  }

  void Renderer::Begin() const
  {
    // TODO Bind framebuffer if one is available
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void Renderer::End() const
  {
    // TODO Unbind framebuffer if one was bound
  }

  Renderer::Renderer(bool loadGL, const GLLoaderFunc &loader)
  {
    if (loadGL)
    {
      int success = loader ? gladLoadGLLoader(loader) : gladLoadGL();
      assert(success && "Failed to load OpenGL functions!");
      std::printf("Loaded OpenGL Version :: %s\n", glGetString(GL_VERSION));
    }
  }

} // namespace xrs