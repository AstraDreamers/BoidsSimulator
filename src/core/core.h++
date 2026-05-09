#pragma once

#include "../manager/manager_entity.h++"
#include "../manager/manager_ui.h++"

class core {
public:
  core();
  ~core() = default;

  void run();

private:
  void handle_events();
  void update();
  void render();

private:
  sf::RenderWindow m_window;
  sf::Vector2u m_window_size;
  sf::RectangleShape m_clearscreen_shape;

  std::unique_ptr<manager_entity> m_manager_entity;
  std::unique_ptr<manager_ui> m_manager_ui;

  sf::Clock m_clock;
  float m_dt;

  float m_ws = 10.f;
  float m_wa = 1.f;
  float m_wc = 0.5f;
  float m_vision = 100.f;
};