#include "manager_entity.h++"
#include "../colors.h++"
#include "entity/components.h++"

manager_entity::manager_entity(sf::Vector2u window_size, boids_packet &boids_packet) {
    window_size_ = window_size;
    boids_packet_ = &boids_packet;

    for (uint16_t i = 0; i < 200; i++) {
        entt::entity entity = registry_.create();

        registry_.emplace<components::position>(entity, static_cast<float>(rand() % window_size_.x),
                                                static_cast<float>(rand() % window_size_.y));
        registry_.emplace<components::velocity>(entity, static_cast<float>(rand() % 400) - 200.f,
                                                static_cast<float>(rand() % 400) - 200.f);
        registry_.emplace<components::acceleration>(entity, 0.f, 0.f);
        registry_.emplace<components::drawable::circle>(entity);

        auto &circle = registry_.get<components::drawable::circle>(entity);
        circle.shape.setRadius(10.f);
        circle.shape.setOrigin({10.f, 10.f});
        circle.shape.setPointCount(5);
        circle.shape.setFillColor(color_palette::boids);
    }
}

void manager_entity::update(const float dt) {
    update_boids();
    update_velocity(dt);
    update_position(dt);
}

void manager_entity::render(sf::RenderWindow &window) { draw_entities(window); }