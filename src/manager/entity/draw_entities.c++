#include "../manager_entity.h++"
#include "components.h++"

auto manager_entity::draw_entities(sf::RenderWindow &window) -> void {
    registry_.view<components::position>().each([&](components::position &position) -> void {
        boids_.setPosition({position.x, position.y});
        window.draw(boids_);
    });
}