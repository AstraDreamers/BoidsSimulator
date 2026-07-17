#include "../../config/simulation_config.h++"
#include "../manager_entity.h++"
#include "components.h++"

auto manager_entity::update_boids() -> void {
    // TODO: This is O(n^2) and must be optimized in the future.
    // TODO: Maybe use a spatial partitioning structure like a quadtree or a grid
    // TODO: to reduce the number of comparisons.

    const auto  view          = registry_.view<components::position, components::velocity, components::acceleration>();
    const float vision_square = boids_packet_->vision_range * boids_packet_->vision_range;

    view.each([&](const entt::entity this_entity, components::position &this_position,
                  const components::velocity &this_velocity, components::acceleration &this_acceleration) -> void {
        sf::Vector2f vector_s       = {0.F, 0.F};
        sf::Vector2f vector_a       = {0.F, 0.F};
        sf::Vector2f vector_c       = {0.F, 0.F};
        uint32_t     neighbor_count = 0;

        for (auto other_entity : view) {
            if (this_entity == other_entity) {
                continue;
            }

            components::position &other_position = view.get<components::position>(other_entity);
            components::velocity &other_velocity = view.get<components::velocity>(other_entity);

            float delta_x         = other_position.x - this_position.x;
            float delta_y         = other_position.y - this_position.y;
            float distance_square = (delta_x * delta_x) + (delta_y * delta_y);

            if (distance_square < vision_square && distance_square > simulation_config::minimum_distance_square) {
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
            float neighbor_count_invert = 1.F / static_cast<float>(neighbor_count);

            vector_a *= neighbor_count_invert;
            vector_c *= neighbor_count_invert;

            vector_c -= {this_position.x, this_position.y};

            vector_s *= (boids_packet_->gain_separation);
            vector_a *= (boids_packet_->gain_alignment);
            vector_c *= (boids_packet_->gain_cohesion);

            this_acceleration.x = vector_s.x + vector_a.x + vector_c.x - this_velocity.x;
            this_acceleration.y = vector_s.y + vector_a.y + vector_c.y - this_velocity.y;
        } else {
            this_acceleration = {.x = 0.F, .y = 0.F};
        }
    });
}