#pragma once

#include "entity/components.h++"

/// @brief Managing the entities in the simulation.
class manager_entity {
public:
  /// @brief Construct a new manager_entity object.
  /// @param window_size The size of the window.
  /// @param ws The weight of the separation behavior.
  /// @param wa The weight of the alignment behavior.
  /// @param wc The weight of the cohesion behavior.
  /// @param vision The vision radius of the boids.
  manager_entity(sf::Vector2u window_size, float &ws, float &wa, float &wc, float &vision);
  ~manager_entity() = default;

  /// @brief Handle the events of the simulation.
  /// @param event The event to handle.
  void handle_events(const std::optional<sf::Event> &event);

  /// @brief Update the simulation.
  /// @param dt The delta time since the last update.
  void update(float dt);

  /// @brief Render the simulation.
  /// @param window The window to render to.
  void render(sf::RenderWindow &window);

private:
  void update_boids();
  void update_velocity(float dt);
  void update_position(float dt);
  void draw_entities(sf::RenderWindow &window);

private:
  sf::Vector2u m_window_size;
  entt::registry m_registry;

  float *m_ws = nullptr;
  float *m_wa = nullptr;
  float *m_wc = nullptr;
  float *m_vision = nullptr;
};