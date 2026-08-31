/*

BoidsSimulator - A simple flocking simulation.
Copyright (C) 2026  AstraDreamers

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#include "manager/ui/slider.h++"

slider::slider(float &value, std::pair<float, float> clamp)
    : value_(&value), value_clamp_min_(clamp.first), value_clamp_max_(clamp.second) {
    if (value_ == nullptr) {
        throw std::runtime_error("Fatal error: slider: received control value is nullptr.");
    }

    if (value_clamp_max_ < value_clamp_min_) {
        std::swap(value_clamp_max_, value_clamp_min_);
    }

    value_internal_ = (*value_ - value_clamp_min_) / (value_clamp_max_ - value_clamp_min_);
}

auto slider::set_position(sf::Vector2f position) -> void { position_ = position; }

auto slider::set_size(sf::Vector2f size) -> void { size_ = size; }

auto slider::set_color_inactive(sf::Color color) -> void { color_inactive_ = color; }

auto slider::set_color_active(sf::Color color) -> void { color_active_ = color; }

auto slider::set_color_background(sf::Color color) -> void {
    circle_right_.setFillColor(color);
    rectangle_background_.setFillColor(color);
}

auto slider::update(sf::Vector2f mouse_position, bool mouse_clicked) -> void {
    circle_left_.setPosition(position_);
    circle_right_.setPosition({position_.x + size_.x, position_.y});
    rectangle_background_.setPosition(position_);
    rectangle_foreground_.setPosition(position_);

    circle_left_.setRadius(size_.y / 2.F);
    circle_right_.setRadius(size_.y / 2.F);
    rectangle_background_.setSize(size_);

    circle_left_.setOrigin({circle_left_.getRadius(), circle_left_.getRadius()});
    circle_right_.setOrigin({circle_right_.getRadius(), circle_right_.getRadius()});
    rectangle_background_.setOrigin({0.F, size_.y / 2.F});
}

auto slider::render(sf::RenderWindow &window) const -> void {
    window.draw(rectangle_background_);
    window.draw(circle_left_);
    window.draw(circle_right_);
    window.draw(rectangle_foreground_);
    window.draw(circle_knob_);
}