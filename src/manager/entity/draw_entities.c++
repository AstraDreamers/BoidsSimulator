#include "../manager_entity.h++"

void manager_entity::draw_entities(sf::RenderWindow &window) {
    m_registry.view<components::Drawable::Circle>().each(
        [&window](components::Drawable::Circle &circle) { window.draw(circle.shape); });
}