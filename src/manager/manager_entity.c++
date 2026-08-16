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

    render_object_.setPointCount(simulation_config::object_render_point_count);
    render_object_.setRadius(simulation_config::object_render_radius);
    render_object_.setOrigin({simulation_config::object_render_radius, simulation_config::object_render_radius});
    render_object_.setFillColor(theme_config::boids);

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
}

manager_entity::~manager_entity() = default;

auto manager_entity::update(const float time_dt) -> void {
    render_object_.rotate(sf::degrees(simulation_config::object_rotation_per_second));

    const float vision_range_square{simulation_parameters_->vision_range * simulation_parameters_->vision_range};
    const float gain_separation{simulation_parameters_->gain_separation};
    const float gain_alignment{simulation_parameters_->gain_alignment};
    const float gain_cohesion{simulation_parameters_->gain_cohesion};

    for (auto &&[px1, py1, vx1, vy1, ax1, ay1] :
         std::views::zip(array_position_x_, array_position_y_, array_velocity_x_, array_velocity_y_,
                         array_acceleration_x_, array_acceleration_y_)) {

        float force_separation_x{0.F};
        float force_separation_y{0.F};

        float force_alignment_x{0.F};
        float force_alignment_y{0.F};

        float force_cohesion_x{0.F};
        float force_cohesion_y{0.F};

        float target_position_x{0.F};
        float target_position_y{0.F};

        uint32_t neighbor_count{0U};

        for (auto &&[px2, py2, vx2, vy2, ax2, ay2] :
             std::views::zip(array_position_x_, array_position_y_, array_velocity_x_, array_velocity_y_,
                             array_acceleration_x_, array_acceleration_y_)) {

            const float distance_square{((px2 - px1) * (px2 - px1)) + ((py2 - py1) * (py2 - py1))};
            const float minimum_distance_square{0.01F};

            if (distance_square > minimum_distance_square) {
                if (distance_square <= vision_range_square) {
                    /// Add a neighbor to a count first
                    neighbor_count += 1U;

                    /// ? Separation
                    force_separation_x += (-(px2 - px1)) / distance_square;
                    force_separation_y += (-(py2 - py1)) / distance_square;

                    /// ? Alignment
                    force_alignment_x += vx2;
                    force_alignment_y += vy2;

                    /// ? Cohesion
                    target_position_x += px2;
                    target_position_y += py2;
                }
            }
        }

        if (neighbor_count > 0U) {
            const float neighbor_count_inverse{1.F / static_cast<float>(neighbor_count)};

            /// ? Separation
            force_separation_x *= neighbor_count_inverse;
            force_separation_y *= neighbor_count_inverse;

            /// ? Alignment
            force_alignment_x *= neighbor_count_inverse;
            force_alignment_y *= neighbor_count_inverse;

            /// ? Cohesion
            target_position_x *= neighbor_count_inverse;
            target_position_y *= neighbor_count_inverse;

            force_cohesion_x = target_position_x - px1;
            force_cohesion_y = target_position_y - py1;

            /// ? Final Calculation
            ax1 = (gain_separation * force_separation_x) + (gain_alignment * force_alignment_x) +
                  (gain_cohesion * force_cohesion_x) - vx1;
            ay1 = (gain_separation * force_separation_y) + (gain_alignment * force_alignment_y) +
                  (gain_cohesion * force_cohesion_y) - vy1;
        }
    }

    for (auto &&[px_, py_, vx_, vy_, ax_, ay_] :
         std::views::zip(array_position_x_, array_position_y_, array_velocity_x_, array_velocity_y_,
                         array_acceleration_x_, array_acceleration_y_)) {
        vx_ += ax_ * time_dt;
        vy_ += ay_ * time_dt;

        px_ += vx_ * time_dt;
        py_ += vy_ * time_dt;

        px_ = wrap_position(px_, window_size_float_.x);
        py_ = wrap_position(py_, window_size_float_.y);

        ax_ = 0.F;
        ay_ = 0.F;
    }
}

auto manager_entity::render(sf::RenderWindow &window) -> void {
    for (auto &&[px_, py_] : std::views::zip(array_position_x_, array_position_y_)) {
        render_object_.setPosition({px_, py_});
        window.draw(render_object_);
    }
}