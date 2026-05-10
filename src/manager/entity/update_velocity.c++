#include "../manager_entity.h++"

void manager_entity::update_velocity(float dt) {
  m_registry.view<Components::Movement::Acceleration, Components::Movement::Velocity>().each(
      [dt](Components::Movement::Acceleration &a, Components::Movement::Velocity &v) {
        v.x += a.x * dt;
        v.y += a.y * dt;
      });
}