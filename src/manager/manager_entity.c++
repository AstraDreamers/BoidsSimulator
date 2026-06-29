#include "manager_entity.h++"

manager_entity::manager_entity(sf::Vector2u window_size, float &ws, float &wa, float &wc, float &vision) {
    m_window_size = window_size;
    m_ws = &ws;
    m_wa = &wa;
    m_wc = &wc;
    m_vision = &vision;

    for (uint16_t i = 0; i < 200; i++) {
        entt::entity entity = m_registry.create();

        m_registry.emplace<Components::Movement::Position>(entity, static_cast<float>(rand() % m_window_size.x),
                                                           static_cast<float>(rand() % m_window_size.y));
        m_registry.emplace<Components::Movement::Velocity>(entity, static_cast<float>(rand() % 400) - 200.f,
                                                           static_cast<float>(rand() % 400) - 200.f);
        m_registry.emplace<Components::Movement::Acceleration>(entity, 0.f, 0.f);
        m_registry.emplace<Components::Drawable::Circle>(entity);

        auto &circle = m_registry.get<Components::Drawable::Circle>(entity);
        circle.shape.setRadius(10.f);
        circle.shape.setOrigin({10.f, 10.f});
        circle.shape.setPointCount(5);
        circle.shape.setFillColor(color_palette::boids);
    }
}

void manager_entity::handle_events(const std::optional<sf::Event> &event) {}

void manager_entity::update(float dt) {
    update_boids();
    update_velocity(dt);
    update_position(dt);
}

void manager_entity::render(sf::RenderWindow &window) { draw_entities(window); }