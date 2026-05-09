#include "../manager_entity.h++"

void manager_entity::update_boids() {
  // TODO: This is O(n^2) and must be optimized in the future.
  // TODO: Maybe use a spatial partitioning structure like a quadtree or a grid
  // TODO: to reduce the number of comparisons.

  auto view =
      m_registry
          .view<Components::Movement::Position, Components::Movement::Velocity,
                Components::Movement::Acceleration>();
  float vision_square = (*m_vision) * (*m_vision);

  view.each([&](entt::entity this_entity,
                Components::Movement::Position &this_position,
                Components::Movement::Velocity &this_velocity,
                Components::Movement::Acceleration &this_acceleration) {
    sf::Vector2f vector_s = {0.f, 0.f};
    sf::Vector2f vector_a = {0.f, 0.f};
    sf::Vector2f vector_c = {0.f, 0.f};
    uint32_t neighbor_count = 0;

    for (auto other_entity : view) {
      if (this_entity == other_entity) {
        continue;
      }

      Components::Movement::Position &other_position =
          view.get<Components::Movement::Position>(other_entity);
      Components::Movement::Velocity &other_velocity =
          view.get<Components::Movement::Velocity>(other_entity);

      float delta_x = other_position.x - this_position.x;
      float delta_y = other_position.y - this_position.y;
      float distance_square = delta_x * delta_x + delta_y * delta_y;

      if (distance_square < vision_square && distance_square > 0.01f) {
        float distance = std::sqrtf(distance_square);

        vector_s.x -= delta_x / distance;
        vector_s.y -= delta_y / distance;

        vector_a.x += other_velocity.x;
        vector_a.y += other_velocity.y;

        vector_c.x += other_position.x;
        vector_c.y += other_position.y;

        neighbor_count++;
      }
    }

    if (neighbor_count > 0) {
      float neighbor_count_invert = 1.f / static_cast<float>(neighbor_count);

      // vector_s *= neighbor_count_invert;
      vector_a *= neighbor_count_invert;
      vector_c *= neighbor_count_invert;

      vector_c -= {this_position.x, this_position.y};

      vector_s *= (*m_ws);
      vector_a *= (*m_wa);
      vector_c *= (*m_wc);

      this_acceleration.x =
          vector_s.x + vector_a.x + vector_c.x - this_velocity.x;
      this_acceleration.y =
          vector_s.y + vector_a.y + vector_c.y - this_velocity.y;
    } else {
      this_acceleration = {0.f, 0.f};
    }
  });
}