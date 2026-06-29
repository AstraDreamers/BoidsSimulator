#include "../manager_entity.h++"

void manager_entity::draw_entities(sf::RenderWindow &window) {
    m_registry.view<Components::Drawable::Circle>().each(
        [&window](Components::Drawable::Circle &circle) { window.draw(circle.shape); });
}