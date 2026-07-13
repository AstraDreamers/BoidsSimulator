#include "../manager_entity.h++"
#include "components.h++"

void manager_entity::update_position(const float time_dt) {
    // Update position and wrapping entities around the screen
    registry_.view<components::velocity, components::position>().each(
        [&](const components::velocity &velocity, components::position &position) -> void {
            position.x += velocity.x * time_dt;
            position.y += velocity.y * time_dt;

            while (position.x > static_cast<float>(window_size_.x) + 10.f) {
                position.x -= static_cast<float>(window_size_.x);
                position.x -= 20.f;
            }

            while (position.y > static_cast<float>(window_size_.y) + 10.f) {
                position.y -= static_cast<float>(window_size_.y);
                position.y -= 20.f;
            }

            while (position.x <= -10.f) {
                position.x += static_cast<float>(window_size_.x);
                position.x += 20.f;
            }

            while (position.y <= -10.f) {
                position.y += static_cast<float>(window_size_.y);
                position.y += 20.f;
            }
        });

    registry_.view<components::position, components::drawable::circle>().each(
        [](components::position &p, components::drawable::circle &circle) -> void {
            circle.shape.setPosition({p.x, p.y});
        });
}