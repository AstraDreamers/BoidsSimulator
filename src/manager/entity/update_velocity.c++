#include "../manager_entity.h++"
#include "components.h++"

void manager_entity::update_velocity(float dt) {
    registry_.view<components::acceleration, components::velocity>().each(
        [dt](const components::acceleration &acceleration, components::velocity &velocity) {
            velocity.x += acceleration.x * dt;
            velocity.y += acceleration.y * dt;
        });
}