#include "../manager_entity.h++"
#include "components.h++"

auto manager_entity::draw_entities(sf::RenderWindow &window) -> void {
    registry_.view<components::drawable::circle>().each(
        [&window](components::drawable::circle &circle) -> void { window.draw(circle.shape); });
}