#include "xrs/Renderer.hpp"
#include <glad/glad.h>
#include <cstdio>
#include <cassert>

namespace xrs
{
  Renderer &Renderer::Initialize(bool loadGL, const GLLoader &loader)
  {
    static auto renderer = new Renderer{loadGL, loader};
    return *renderer;
  }

  void Renderer::Shutdown()
  {
  }

  Renderer::Renderer(bool loadGL, const GLLoader &loader) noexcept
  {
    if (loadGL)
    {
      int success = loader ? gladLoadGLLoader(loader) : gladLoadGL();
      assert(success && "Failed to load OpenGL functions!");
    }
  }
}