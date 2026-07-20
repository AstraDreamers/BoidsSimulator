#include "manager_entity.h++"
#include "../config/simulation_config.h++"
#include "../config/theme_config.h++"

manager_entity::manager_entity(sf::Vector2u window_size, simulation_parameters &simulation_parameters)
    : window_size_(window_size), simulation_parameters_(&simulation_parameters) {}

manager_entity::~manager_entity() = default;

auto manager_entity::update(const float time_dt) -> void {}

auto manager_entity::render(sf::RenderWindow &window) -> void {}