#include "../manager_entity.h++"
#include "components.h++"

void manager_entity::draw_entities(sf::RenderWindow &window) {
    registry_.view<components::drawable::circle>().each(
        [&window](components::drawable::circle &circle) -> void { window.draw(circle.shape); });
}