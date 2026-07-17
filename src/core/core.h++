#pragma once

#include "../manager/manager_entity.h++"
#include "../manager/manager_ui.h++"
#include "SFML/Graphics/RenderWindow.hpp"
#include "boids_packet.h++"
#include <memory>

/// @brief Entry point of the whole program.
class core {
  public:
    core();
    ~core();

    core(const core &)                         = delete;
    auto operator=(const core &) -> core &     = delete;
    core(core &&) noexcept                     = default;
    auto operator=(core &&) noexcept -> core & = delete;

    /// @brief Start the program
    auto run() -> void;

  private:
    auto handle_events() -> void;
    auto update() -> void;
    auto render() -> void;

    sf::RenderWindow window_;
    sf::Vector2u     window_size_{0U, 0U};

    std::unique_ptr<manager_entity> manager_entity_;
    std::unique_ptr<manager_ui>     manager_ui_;

    sf::Clock clock_;
    sf::Time  dt_;

    boids_packet boids_packet_;
};