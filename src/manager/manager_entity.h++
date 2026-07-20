#pragma once

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
    sf::Vector2u           window_size_{0U, 0U};
    simulation_parameters *simulation_parameters_{nullptr};
};