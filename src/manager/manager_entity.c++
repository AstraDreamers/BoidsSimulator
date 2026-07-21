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

    for (auto &&[px_, py_, vx_, vy_, ax_, ay_] :
         std::views::zip(array_position_x_, array_position_y_, array_velocity_x_, array_velocity_y_,
                         array_acceleration_x_, array_acceleration_y_)) {
        ax_ = 0.F;
        ay_ = 0.F;

        vx_ = random_v(random_engine_);
        vy_ = random_v(random_engine_);

        px_ = random_x(random_engine_);
        py_ = random_y(random_engine_);
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
        float vector_separation_x{0.F};
        float vector_separation_y{0.F};

        float vector_alignment_x{0.F};
        float vector_alignment_y{0.F};

        float vector_cohesion_x{0.F};
        float vector_cohesion_y{0.F};

        uint32_t neighbor_count{0U};

        for (auto &&[px2, py2, vx2, vy2, ax2, ay2] :
             std::views::zip(array_position_x_, array_position_y_, array_velocity_x_, array_velocity_y_,
                             array_acceleration_x_, array_acceleration_y_)) {
            const float delta_x{px2 - px1};
            const float delta_y{py2 - py1};
            const float distance_square{(delta_x * delta_x) + (delta_y * delta_y)};

            if (distance_square <= vision_range_square && distance_square > simulation_config::min_length_square) {
                const float distance_reversed{1.F / std::sqrtf(distance_square)};

                vector_separation_x -= delta_x * distance_reversed;
                vector_separation_y -= delta_y * distance_reversed;

                vector_alignment_x += vx2;
                vector_alignment_y += vy2;

                vector_cohesion_x += px2;
                vector_cohesion_y += py2;

                neighbor_count += 1U;
            }
        }

        if (neighbor_count > 0U) {
            const float neighbor_count_invert = 1.F / static_cast<float>(neighbor_count);

            vector_alignment_x *= neighbor_count_invert;
            vector_alignment_y *= neighbor_count_invert;

            vector_cohesion_x *= neighbor_count_invert;
            vector_cohesion_y *= neighbor_count_invert;

            vector_cohesion_x -= px1;
            vector_cohesion_y -= py1;

            vector_separation_x *= gain_separation;
            vector_separation_y *= gain_separation;

            vector_alignment_x *= gain_alignment;
            vector_alignment_y *= gain_alignment;

            vector_cohesion_x *= gain_cohesion;
            vector_cohesion_y *= gain_cohesion;

            ax1 = vector_separation_x + vector_alignment_x + vector_cohesion_x - vx1;
            ay1 = vector_separation_y + vector_alignment_y + vector_cohesion_y - vy1;
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