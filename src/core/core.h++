#pragma once

#include "../manager/manager_entity.h++"
#include "../manager/manager_ui.h++"
#include "boids_packet.h++"

/// @brief Entry point
class core {
  public:
    core();
    ~core() = default;

    core(const core &)                         = delete;
    auto operator=(const core &) -> core &     = delete;
    core(core &&) noexcept                     = default;
    auto operator=(core &&) noexcept -> core & = delete;

    /// @brief Start the program
    void run();

  private:
    void handle_events();
    void update();
    void render();

    sf::RenderWindow window_;
    sf::Vector2u     window_size_{0U, 0U};

    std::unique_ptr<manager_entity> manager_entity_;
    std::unique_ptr<manager_ui>     manager_ui_;

    sf::Clock clock_;
    float     dt_{0.F};

    boids_packet boids_packet_;
};