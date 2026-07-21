#include "manager_entity.h++"
#include "../config/theme_config.h++"

manager_entity::manager_entity(sf::Vector2u window_size, simulation_parameters &simulation_parameters)
    : window_size_(window_size), simulation_parameters_(&simulation_parameters) {

    window_size_float_.x = static_cast<float>(window_size_.x);
    window_size_float_.y = static_cast<float>(window_size_.y);

    render_object_.setPointCount(simulation_config::object_render_point_count);
    render_object_.setRadius(simulation_config::object_render_radius);
    render_object_.setOrigin({simulation_config::object_render_radius, simulation_config::object_render_radius});
    render_object_.setFillColor(theme_config::boids);

    std::uniform_real_distribution<float> random_x(0.F, static_cast<float>(window_size_.x));
    std::uniform_real_distribution<float> random_y(0.F, static_cast<float>(window_size_.y));
    std::uniform_real_distribution<float> random_v(-simulation_config::init_velocity_range,
                                                   simulation_config::init_velocity_range);

    for (auto &&[pos_x, pos_y, vel_x, vel_y, acc_x, acc_y] :
         std::views::zip(simul_pos_x_, simul_pos_y_, simul_velo_x_, simul_velo_y_, simul_accel_x_, simul_accel_y_)) {
        acc_x = 0;
        acc_y = 0;

        vel_x = random_v(random_engine_);
        vel_y = random_v(random_engine_);

        pos_x = random_x(random_engine_);
        pos_y = random_y(random_engine_);
    }
}

manager_entity::~manager_entity() = default;

auto manager_entity::update(const float time_dt) -> void {
    render_object_.rotate(sf::degrees(simulation_config::object_rotation_per_second));

    for (auto &&[pos_x, pos_y, vel_x, vel_y, acc_x, acc_y] :
         std::views::zip(simul_pos_x_, simul_pos_y_, simul_velo_x_, simul_velo_y_, simul_accel_x_, simul_accel_y_)) {

        /// ? Velocity Update
        vel_x = vel_x + (acc_x * time_dt);
        vel_y = vel_y + (acc_y * time_dt);

        /// ? Position Update
        pos_x = pos_x + (vel_x * time_dt);
        pos_y = pos_y + (vel_y * time_dt);

        /// ? Position Wrapping
        pos_x = wrap_position(pos_x, window_size_float_.x);
        pos_y = wrap_position(pos_y, window_size_float_.y);

        /// ? Resetting Acceleration
        acc_x = 0;
        acc_y = 0;
    }
}

auto manager_entity::render(sf::RenderWindow &window) -> void {
    for (auto &&[pos_x, pos_y] : std::views::zip(simul_pos_x_, simul_pos_y_)) {
        render_object_.setPosition({pos_x, pos_y});
        window.draw(render_object_);
    }
}