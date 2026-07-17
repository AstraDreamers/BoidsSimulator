#include "../manager_entity.h++"
#include "components.h++"

auto manager_entity::update_position(const float time_dt) -> void {
    registry_.view<components::velocity, components::position>().each(
        [&](const components::velocity &velocity, components::position &position) -> void {
            position.x += velocity.x * time_dt;
            position.y += velocity.y * time_dt;

            while (position.x > static_cast<float>(window_size_.x)) {
                position.x -= static_cast<float>(window_size_.x);
            }

            while (position.y > static_cast<float>(window_size_.y)) {
                position.y -= static_cast<float>(window_size_.y);
            }

            while (position.x <= 0.F) {
                position.x += static_cast<float>(window_size_.x);
            }

            while (position.y <= 0.F) {
                position.y += static_cast<float>(window_size_.y);
            }
        });
}