#include "manager_entity.h++"
#include "../config/simulation_config.h++"
#include "../config/theme_config.h++"
#include "entity/components.h++"

manager_entity::manager_entity(sf::Vector2u window_size, boids_packet &boids_packet)
    : window_size_(window_size), boids_packet_(&boids_packet) {}

manager_entity::~manager_entity() = default;

auto manager_entity::update(const float time_dt) -> void {}

auto manager_entity::render(sf::RenderWindow &window) -> void {}