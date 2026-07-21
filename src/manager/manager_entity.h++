#pragma once

#include "../config/simulation_config.h++"
#include "../core/simulation_parameters.h++"

/// @brief Managing the entities in the simulation.
class manager_entity {
  public:
    /// @brief Construct a new manager_entity object.
    /// @param window_size The size of the window.
    /// @param boids_packet The variable packets for boids.
    manager_entity(sf::Vector2u window_size, simulation_parameters &simulation_parameters);
    ~manager_entity();

    manager_entity(const manager_entity &)                         = delete;
    auto operator=(const manager_entity &) -> manager_entity &     = delete;
    manager_entity(manager_entity &&) noexcept                     = delete;
    auto operator=(manager_entity &&) noexcept -> manager_entity & = delete;

    /// @brief Update the simulation.
    /// @param time_dt The delta time since the last update.
    auto update(float time_dt) -> void;

    /// @brief Render the simulation.
    /// @param window The window to render to.
    auto render(sf::RenderWindow &window) -> void;

  private:
    [[nodiscard]] static auto wrap_position(const float pos, const float max_bounds) noexcept -> float {
        return pos - (max_bounds * std::floor(pos / max_bounds));
    }

    sf::Vector2u           window_size_{0U, 0U};
    sf::Vector2f           window_size_float_{0.F, 0.F};
    simulation_parameters *simulation_parameters_{nullptr};

    sf::CircleShape    render_object_;
    std::random_device random_device_;
    std::mt19937_64    random_engine_{random_device_()};

    std::array<float, simulation_config::init_object_count> simul_pos_x_{};
    std::array<float, simulation_config::init_object_count> simul_pos_y_{};
    std::array<float, simulation_config::init_object_count> simul_velo_x_{};
    std::array<float, simulation_config::init_object_count> simul_velo_y_{};
    std::array<float, simulation_config::init_object_count> simul_accel_x_{};
    std::array<float, simulation_config::init_object_count> simul_accel_y_{};
};