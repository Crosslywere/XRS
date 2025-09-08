#include <xrs/Renderer.hpp>
#include <GLFW/glfw3.h>

int main(void)
{
  glfwInit();
  auto window = glfwCreateWindow(800, 600, "Testing Window", 0, 0);
  glfwMakeContextCurrent(window);
  auto renderer = xrs::Renderer::Initialize(true, (xrs::Renderer::GLLoaderFunc)glfwGetProcAddress);
  while (!glfwWindowShouldClose(window))
  {
    renderer.Begin();
    renderer.End();
    glfwPollEvents();
    glfwSwapBuffers(window);
  }
  renderer.Shutdown();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}