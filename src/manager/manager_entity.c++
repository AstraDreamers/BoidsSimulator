/*

BoidsSimulator - A simple flocking simulation.
Copyright (C) 2026  AstraDreamers

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#include "manager/manager_entity.h++"
#include "config/theme_config.h++"

manager_entity::manager_entity(sf::Vector2u window_size, simulation_parameters &simulation_parameters)
    : window_size_(window_size), simulation_parameters_(&simulation_parameters) {

    window_size_float_.x = static_cast<float>(window_size_.x);
    window_size_float_.y = static_cast<float>(window_size_.y);

    std::random_device random_device;
    std::mt19937_64    random_engine{random_device()};

    std::uniform_real_distribution<float> random_x(0.F, static_cast<float>(window_size_.x));
    std::uniform_real_distribution<float> random_y(0.F, static_cast<float>(window_size_.y));
    std::uniform_real_distribution<float> random_v(-simulation_config::init_velocity_range,
                                                   simulation_config::init_velocity_range);

    for (auto &&[px_, py_, vx_, vy_, ax_, ay_] :
         std::views::zip(array_position_x_, array_position_y_, array_velocity_x_, array_velocity_y_,
                         array_acceleration_x_, array_acceleration_y_)) {
        ax_ = 0.F;
        ay_ = 0.F;

        vx_ = random_v(random_engine);
        vy_ = random_v(random_engine);

        px_ = random_x(random_engine);
        py_ = random_y(random_engine);
    }

    for (auto &indices : render_array_) {
        indices.color = theme_config::boids;
    }
}

manager_entity::~manager_entity() = default;

auto manager_entity::update(const float time_dt) -> void {
    const float vision_range_square{simulation_parameters_->vision_range * simulation_parameters_->vision_range};
    const float gain_separation{simulation_parameters_->gain_separation};
    const float gain_alignment{simulation_parameters_->gain_alignment};
    const float gain_cohesion{simulation_parameters_->gain_cohesion};

    /// ! The core code goes here
    /// ? This current problem is so complex that I can't even stand of it anymore (with me only). so I think that it's
    /// ? a good idea to pause the core development and clean up surrounding code.

    for (auto &&[px_, py_, vx_, vy_, ax_, ay_, indices] :
         std::views::zip(array_position_x_, array_position_y_, array_velocity_x_, array_velocity_y_,
                         array_acceleration_x_, array_acceleration_y_, render_array_)) {
        vx_ += ax_ * time_dt;
        vy_ += ay_ * time_dt;

        px_ += vx_ * time_dt;
        py_ += vy_ * time_dt;

        px_ = wrap_position(px_, window_size_float_.x);
        py_ = wrap_position(py_, window_size_float_.y);

        ax_ = 0.F;
        ay_ = 0.F;

        indices.position.x = px_;
        indices.position.y = py_;
    }
}

auto manager_entity::render(sf::RenderWindow &window) -> void { window.draw(render_array_); }