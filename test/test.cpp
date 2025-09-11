#include <xrs/Renderer.hpp>
#include <GLFW/glfw3.h>

void processInputs(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main(void)
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  auto window = glfwCreateWindow(800, 600, "Testing Window", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  auto renderer = xrs::Renderer::Initialize(true, (xrs::Renderer::GLLoaderFunc)glfwGetProcAddress);
  while (!glfwWindowShouldClose(window))
  {
    renderer.BeginFrame();
    renderer.EndFrame();
    glfwPollEvents();
    glfwSwapBuffers(window);
    processInputs(window);
  }
  renderer.Shutdown();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}