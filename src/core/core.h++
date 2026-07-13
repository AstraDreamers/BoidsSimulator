#pragma once

#include "../manager/manager_entity.h++"
#include "../manager/manager_ui.h++"
#include "boids_packet.h++"

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
    sf::RenderWindow window_;
    sf::Vector2u window_size_;

    std::unique_ptr<manager_entity> manager_entity_;
    std::unique_ptr<manager_ui> manager_ui_;

    sf::Clock clock_;
    float dt_;

    boids_packet m_boids_packet;
};