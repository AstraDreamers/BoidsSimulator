#include "../manager_entity.h++"
#include "components.h++"

auto manager_entity::update_velocity(const float time_dt) -> void {
    registry_.view<components::acceleration, components::velocity>().each(
        [time_dt](const components::acceleration &acceleration, components::velocity &velocity) -> void {
            velocity.x += acceleration.x * time_dt;
            velocity.y += acceleration.y * time_dt;
        });
}