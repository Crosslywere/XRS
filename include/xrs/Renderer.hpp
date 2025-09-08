#pragma once

#ifndef _RENDERER_HPP_
#define _XRS_RENDERER_HPP_

#include "Framebuffer.hpp"
#include "Texture.hpp"

namespace xrs
{

  class Renderer
  {
  public:
    /**
     * @brief A function pointer to a function that can load OpenGL functions eg. glfwGetProcAddress from glfw
     */
    typedef void *(*GLLoaderFunc)(const char *);

    /**
     * @brief Initializes OpenGL based on the render context's version.
     * @param loadGL weather or not the renderer should load the opengl functions
     * @param loader a function pointer used to load opengl functions. Defaults to true.
     * @returns A reference to the instance of the Renderer. Defaults to a null pointer.
     */
    static Renderer &Initialize(bool loadGL = true, const GLLoaderFunc &loader = nullptr);

    /**
     * @brief Destroys renderer managed objects
     */
    void Shutdown();

    /**
     * @brief Prepares the renderer for drawing objects.
     */
    void Begin() const;

    /**
     * @brief Ends the rendering phase.
     */
    void End() const;

    // Explicit declarations
    Renderer(const Renderer &) = default;
    Renderer(const Renderer &&) = delete;
    ~Renderer() = default;
    Renderer &operator=(const Renderer &) = default;

  private:
    Renderer() = default;
    Renderer(bool, const GLLoaderFunc &);
  };

} // namespace xrs

#endif // _XRS_RENDERER_HPP_