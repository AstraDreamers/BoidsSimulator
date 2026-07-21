#include "manager_entity.h++"
#include "../config/theme_config.h++"

manager_entity::manager_entity(sf::Vector2u window_size, simulation_parameters &simulation_parameters)
    : window_size_(window_size), simulation_parameters_(&simulation_parameters) {
    for (auto &&[pos_x, pos_y, vel_x, vel_y, acc_x, acc_y] :
         std::views::zip(simul_pos_x_, simul_pos_y_, simul_velo_x_, simul_velo_y_, simul_accel_x_, simul_accel_y_)) {
        acc_x = 0;
        acc_y = 0;

        vel_x = 0;
        vel_y = 0;

        pos_x = 0;
        pos_y = 0;
    }
}

manager_entity::~manager_entity() = default;

auto manager_entity::update(const float time_dt) -> void {

    for (auto &&[pos_x, pos_y, vel_x, vel_y, acc_x, acc_y] :
         std::views::zip(simul_pos_x_, simul_pos_y_, simul_velo_x_, simul_velo_y_, simul_accel_x_, simul_accel_y_)) {
        vel_x = vel_x + (acc_x * time_dt);
        vel_y = vel_y + (acc_y * time_dt);

        pos_x = pos_x + (vel_x * time_dt);
        pos_y = pos_y + (vel_y * time_dt);

        acc_x = 0;
        acc_y = 0;
    }
}

auto manager_entity::render(sf::RenderWindow &window) -> void {}