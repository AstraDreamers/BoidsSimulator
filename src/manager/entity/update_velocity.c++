#include "../manager_entity.h++"
#include "components.h++"

void manager_entity::update_velocity(const float time_dt) {
    registry_.view<components::acceleration, components::velocity>().each(
        [time_dt](const components::acceleration &acceleration, components::velocity &velocity) -> void {
            velocity.x += acceleration.x * time_dt;
            velocity.y += acceleration.y * time_dt;
        });
}