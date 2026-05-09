#pragma once

#include "entity/components.h++"

class manager_entity {
public:
  manager_entity(sf::Vector2u window_size, float &ws, float &wa, float &wc,
                 float &vision);
  ~manager_entity() = default;

  void handle_events(const std::optional<sf::Event> &event);
  void update(float dt);
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