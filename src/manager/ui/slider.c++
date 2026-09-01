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

    value_clamp_range_ = value_clamp_max_ - value_clamp_min_;
    value_internal_    = (*value_ - value_clamp_min_) / value_clamp_range_;

    circle_knob_.setPointCount(4U);
}

auto slider::set_position(sf::Vector2f position) -> void {
    position_ = position;

    circle_left_.setPosition(position_);
    circle_right_.setPosition({position_.x + size_.x, position_.y});
    rectangle_background_.setPosition(position_);
    rectangle_foreground_.setPosition(position_);
}

auto slider::set_size(sf::Vector2f size) -> void {
    size_ = size;

    circle_right_.setPosition({position_.x + size_.x, position_.y});

    circle_left_.setRadius(half_of(size_.y));
    circle_right_.setRadius(half_of(size_.y));
    rectangle_background_.setSize(size_);

    circle_left_.setOrigin({circle_left_.getRadius(), circle_left_.getRadius()});
    circle_right_.setOrigin({circle_right_.getRadius(), circle_right_.getRadius()});
    rectangle_background_.setOrigin({0.F, half_of(size_.y)});
    rectangle_foreground_.setOrigin({0.F, half_of(size_.y)});
}

auto slider::set_color_inactive(sf::Color color) -> void { color_inactive_ = color; }

auto slider::set_color_active(sf::Color color) -> void { color_active_ = color; }

auto slider::set_color_background(sf::Color color) -> void {
    circle_right_.setFillColor(color);
    rectangle_background_.setFillColor(color);
}

auto slider::update(sf::Vector2f mouse_position, bool mouse_clicked) -> void {
    const float interpolated_length{value_internal_ * size_.x};
    const float interpolated_position_x{position_.x + interpolated_length};
    const float mouse_length{std::hypotf(interpolated_position_x - mouse_position.x, position_.y - mouse_position.y)};

    /// ? Set position of the knob and the bar based on interpolated length
    circle_knob_.setPosition({interpolated_position_x, position_.y});
    rectangle_foreground_.setSize({interpolated_length, size_.y});

    /// ? Resolving mouse clicking event
    if (mouse_length <= twice_of(size_.y) && mouse_clicked) {
        mouse_is_locked_ = true;
    }

    if (!mouse_clicked) {
        mouse_is_locked_ = false;
    }

    /// ? Resolving knob size scale
    if (mouse_length <= twice_of(size_.y) || mouse_is_locked_) {
        knob_scale_ += knob_scale_step;
    } else {
        knob_scale_ -= knob_scale_step;
    }

    knob_scale_ = std::clamp(knob_scale_, 0.F, 1.F);

    /// ? Resolving color interpolation scale, and changing internal value when clicked
    if (mouse_is_locked_) {
        color_scale_ += color_scale_step;
        value_internal_ = std::clamp((mouse_position.x - position_.x) / size_.x, 0.F, 1.F);
    } else {
        color_scale_ -= color_scale_step;
    }

    color_scale_ = std::clamp(color_scale_, 0.F, 1.F);

    /// ? Updating knob size and rotations
    circle_knob_.setRadius(size_.y + (knob_scale_ * half_of(size_.y)));
    circle_knob_.setOrigin({circle_knob_.getRadius(), circle_knob_.getRadius()});
    circle_knob_.rotate(sf::degrees(color_scale_ * knob_rotation_rate_degrees));

    const sf::Color interpolated_color{interpolate_color(color_inactive_, color_active_, color_scale_)};

    circle_left_.setFillColor(interpolated_color);
    circle_knob_.setFillColor(interpolated_color);
    rectangle_foreground_.setFillColor(interpolated_color);

    /// ? Updating provided value when changed
    if (value_internal_ != value_internal_last_) {
        *value_ = value_clamp_min_ + (value_internal_ * value_clamp_range_);
    }

    /// ? Updating last values
    value_internal_last_ = value_internal_;
    mouse_click_last_    = mouse_clicked;
}

auto slider::render(sf::RenderWindow &window) const -> void {
    window.draw(rectangle_background_);
    window.draw(circle_left_);
    window.draw(circle_right_);
    window.draw(rectangle_foreground_);
    window.draw(circle_knob_);
}