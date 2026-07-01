#include "../manager_entity.h++"

void manager_entity::update_position(float dt) {
    // Update position and wrapping entities around the screen
    m_registry.view<components::velocity, components::position>().each(
        [&](const components::velocity &velocity, components::position &position) {
            position.x += velocity.x * dt;
            position.y += velocity.y * dt;

            while (position.x > static_cast<float>(m_window_size.x) + 10.f) {
                position.x -= static_cast<float>(m_window_size.x);
                position.x -= 20.f;
            }

            while (position.y > static_cast<float>(m_window_size.y) + 10.f) {
                position.y -= static_cast<float>(m_window_size.y);
                position.y -= 20.f;
            }

            while (position.x <= -10.f) {
                position.x += static_cast<float>(m_window_size.x);
                position.x += 20.f;
            }

            while (position.y <= -10.f) {
                position.y += static_cast<float>(m_window_size.y);
                position.y += 20.f;
            }
        });

    // Update the position of the circles, and add a rotation for fun
    m_registry.view<components::position, components::Drawable::Circle>().each(
        [](components::position &p, components::Drawable::Circle &circle) {
            circle.shape.setPosition({p.x, p.y});
            circle.shape.rotate(sf::degrees(5.f));
        });
}