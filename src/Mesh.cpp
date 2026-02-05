#include <glad/glad.h>
#include <xrs/Mesh.hpp>

namespace xrs
{
  static float g_Verts[] = {
    0, .5, -.5, -.5, .5, -.5
  };

  Mesh::Mesh()
  {
    glGenVertexArrays(1, &m_MeshObject);
    glBindVertexArray(m_MeshObject);
    unsigned vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_Verts), g_Verts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, 0);
  }

  Mesh::~Mesh()
  {
    glDeleteVertexArrays(1, &m_MeshObject);
  }

  void Mesh::Bind() const
  {
    glBindVertexArray(m_MeshObject);
  }

  void Mesh::Draw(Shader &shader) const
  {
    shader.Use();
    shader.SetMatrix("uModel", m_Transform.GetModelMatrix());
    Bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

} // namespace xrs