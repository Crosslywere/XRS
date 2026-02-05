#pragma once

#ifndef _XRS_MESH_HPP_
#define _XRS_MESH_HPP_

#include "Transform.hpp"
#include "Shader.hpp"

namespace xrs
{

  class Mesh
  {
  public:
    Mesh();
    ~Mesh();
    void Bind() const;
    void Draw(Shader& shader) const;
  private:
    unsigned int m_MeshObject;
    Transform m_Transform;
  };

} // namespace xrs

#endif // _XRS_MESH_HPP_