#pragma once

#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include <functional>

typedef void *(*GLLoader)(const char *);

namespace xrs
{
  class Renderer
  {
  public:
    /**
     * @brief Initializes OpenGL based on the render context's version.
     * @param loadGL weather or not the renderer should load the opengl functions
     * @param loader a function pointer used to load opengl functions. Defaults to true.
     * @returns A reference to the instance of the Renderer. Defaults to a null pointer.
     */
    static Renderer &Initialize(bool loadGL = true, const GLLoader &loader = nullptr);

    /**
     * @brief Destroys renderer managed objects
     */
    void Shutdown();

    // Explicit declarations
    Renderer(const Renderer &) = default;
    ~Renderer() = default;
    Renderer &operator=(const Renderer &) = default;

  private:
    Renderer() = default;
    Renderer(bool, const GLLoader &) noexcept;
    Renderer(const Renderer &&) = delete;
  };
}

#endif // _RENDERER_HPP_