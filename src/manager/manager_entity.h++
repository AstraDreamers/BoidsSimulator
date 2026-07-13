#pragma once

#include "../core/boids_packet.h++"

/// @brief Managing the entities in the simulation.
class manager_entity {
  public:
    /// @brief Construct a new manager_entity object.
    /// @param window_size The size of the window.
    /// @param boids_packet The variable packets for boids.
    manager_entity(const sf::Vector2u window_size, boids_packet &boids_packet);
    ~manager_entity() = default;

    /// @brief Update the simulation.
    /// @param dt The delta time since the last update.
    void update(const float dt);

    /// @brief Render the simulation.
    /// @param window The window to render to.
    void render(sf::RenderWindow &window);

  private:
    void update_boids();
    void update_velocity(float dt);
    void update_position(float dt);
    void draw_entities(sf::RenderWindow &window);

  private:
    sf::Vector2u window_size_{0, 0};
    boids_packet *boids_packet_{nullptr};

    entt::registry registry_{};
};