#pragma once

#include "../colors.h++"
#include "../manager/manager_entity.h++"
#include "../manager/manager_ui.h++"

/// @brief Entry point
class core {
  public:
    core();
    ~core() = default;

    /// @brief Start the program
    void run();

  private:
    void handle_events();
    void update();
    void render();

  private:
    sf::RenderWindow m_window;
    sf::Vector2u m_window_size;

    std::unique_ptr<manager_entity> m_manager_entity;
    std::unique_ptr<manager_ui> m_manager_ui;

    sf::Clock m_clock;
    float m_dt;

    /// @brief Separation weight
    float m_ws = 10.f;

    /// @brief Alignment weight
    float m_wa = 1.f;

    /// @brief Cohesion weight
    float m_wc = 0.5f;

    /// @brief Vision range of entities (radius)
    float m_vision = 100.f;
};