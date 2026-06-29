#include "../manager_entity.h++"

void manager_entity::update_position(float dt) {
    // Update position and wrapping entities around the screen
    m_registry.view<Components::Movement::Velocity, Components::Movement::Position>().each(
        [&](Components::Movement::Velocity &v, Components::Movement::Position &p) {
            p.x += v.x * dt;
            p.y += v.y * dt;

            while (p.x > static_cast<float>(m_window_size.x) + 10.f) {
                p.x -= static_cast<float>(m_window_size.x);
                p.x -= 20.f;
            }

            while (p.y > static_cast<float>(m_window_size.y) + 10.f) {
                p.y -= static_cast<float>(m_window_size.y);
                p.y -= 20.f;
            }

            while (p.x <= -10.f) {
                p.x += static_cast<float>(m_window_size.x);
                p.x += 20.f;
            }

            while (p.y <= -10.f) {
                p.y += static_cast<float>(m_window_size.y);
                p.y += 20.f;
            }
        });

    // Update the position of the circles, and add a rotation for fun
    m_registry.view<Components::Movement::Position, Components::Drawable::Circle>().each(
        [](Components::Movement::Position &p, Components::Drawable::Circle &circle) {
            circle.shape.setPosition({p.x, p.y});
            circle.shape.rotate(sf::degrees(5.f));
        });
}