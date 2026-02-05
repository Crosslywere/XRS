#include "xrs/Transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace xrs
{

  Transform::Transform(const Vector3f &position, const Vector3f &rotation, const Vector3f &scale)
      : m_Position{position}, m_Rotation{rotation}, m_Scale{scale}
  {
  }

  const Matrix Transform::GetModelMatrix() const
  {
  // glm::lookAt
    auto rotation = glm::quat({glm::radians(m_Rotation.x), glm::radians(m_Rotation.y), glm::radians(m_Rotation.z)});
    auto matrix = glm::translate(glm::mat4(1), {m_Position.x, m_Position.y, m_Position.z});
    matrix *= glm::toMat4(rotation);
    matrix = glm::scale(matrix, {m_Position.x, m_Position.y, m_Position.z});
    return Matrix(glm::value_ptr(matrix), 4, 4);
  }

} // namespace xrs