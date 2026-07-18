#include "manager_entity.h++"
#include "../config/simulation_config.h++"
#include "../config/theme_config.h++"
#include "entity/components.h++"

manager_entity::manager_entity(sf::Vector2u window_size, boids_packet &boids_packet)
    : window_size_(window_size), boids_packet_(&boids_packet) {

    std::uniform_real_distribution<float> random_x(0.F, static_cast<float>(window_size_.x));
    std::uniform_real_distribution<float> random_y(0.F, static_cast<float>(window_size_.y));
    std::uniform_real_distribution<float> random_v(-simulation_config::random_initialization_velocity_range,
                                                   simulation_config::random_initialization_velocity_range);

    for ([[maybe_unused]] const auto entity_index : std::views::iota(0U, simulation_config::boids_count)) {
        entt::entity entity = registry_.create();

        registry_.emplace<components::position>(entity, random_x(random_engine_), random_y(random_engine_));
        registry_.emplace<components::velocity>(entity, random_v(random_engine_), random_v(random_engine_));
        registry_.emplace<components::acceleration>(entity, 0.F, 0.F);
    }

    boids_.setPointCount(simulation_config::boids_point_count);
    boids_.setRadius(simulation_config::boids_radius);
    boids_.setOrigin({simulation_config::boids_radius, simulation_config::boids_radius});
    boids_.setFillColor(theme_config::boids);
}

manager_entity::~manager_entity() = default;

auto manager_entity::update(const float time_dt) -> void {
    update_boids();
    update_velocity(time_dt);
    update_position(time_dt);
}

auto manager_entity::render(sf::RenderWindow &window) -> void { draw_entities(window); }