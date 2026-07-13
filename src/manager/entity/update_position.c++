#include "../manager_entity.h++"
#include "components.h++"

void manager_entity::update_position(float dt) {
    // Update position and wrapping entities around the screen
    registry_.view<components::velocity, components::position>().each(
        [&](const components::velocity &velocity, components::position &position) {
            position.x += velocity.x * dt;
            position.y += velocity.y * dt;

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

    // Update the position of the circles, and add a rotation for fun
    registry_.view<components::position, components::drawable::circle>().each(
        [](components::position &p, components::drawable::circle &circle) {
            circle.shape.setPosition({p.x, p.y});
            circle.shape.rotate(sf::degrees(5.f));
        });
}