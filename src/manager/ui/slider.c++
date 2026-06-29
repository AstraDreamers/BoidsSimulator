#include "slider.h++"

slider::slider(float &value, float clamp_min, float clamp_max)
    : m_vertices(sf::PrimitiveType::Triangles, 12 + (m_circle_segments * 3 * 3)) {
    m_value = &value;
    m_clamp_min = clamp_min;
    m_clamp_max = clamp_max;

    *m_value = std::clamp(*m_value, m_clamp_min, m_clamp_max);
    m_value_based = (*m_value - m_clamp_min) / (m_clamp_max - m_clamp_min);

    const float theta_step = (2.0f * M_PI) / m_circle_segments;
    for (size_t i = 0; i <= m_circle_segments; ++i) {
        m_lut_cos[i] = std::cos(i * theta_step);
        m_lut_sin[i] = std::sin(i * theta_step);
    }

    update_geometry();
}

void slider::set_position(sf::Vector2f position) {
    m_position = position;
    update_geometry();
}

void slider::set_size(sf::Vector2f size) {
    m_size = size;
    update_geometry();
}

void slider::set_color_inactive(sf::Color color) {
    m_color_inactive = color;
    update_geometry();
}

void slider::set_color_active(sf::Color color) {
    m_color_active = color;
    update_geometry();
}

void slider::set_color_background(sf::Color color) {
    m_color_background = color;
    update_geometry();
}

void slider::update() {
    sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition());

    float current_x = m_position.x + m_value_based * m_size.x;
    sf::Vector2f circle_position = {current_x, m_position.y};

    sf::Vector2f d = mouse_position - circle_position;
    float active_radius = m_size.y * (0.75f + 0.25f * m_size_fade);

    if (m_locked) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            m_value_based = (mouse_position.x - m_position.x) / m_size.x;
            m_value_based = std::clamp(m_value_based, 0.f, 1.f);
        } else {
            m_locked = false;
        }
    } else if (d.x * d.x + d.y * d.y <= active_radius * active_radius) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            m_value_based = (mouse_position.x - m_position.x) / m_size.x;
            m_value_based = std::clamp(m_value_based, 0.f, 1.f);
            m_locked = true;
        }
    }

    if (d.x * d.x + d.y * d.y <= active_radius * active_radius || m_locked) {
        m_size_fade = std::min(m_size_fade + 0.075f, 1.f);
    } else {
        m_size_fade = std::max(m_size_fade - 0.075f, 0.f);
    }

    if (m_locked) {
        m_color_fade = std::min(m_color_fade + 0.075f, 1.f);
    } else {
        m_color_fade = std::max(m_color_fade - 0.075f, 0.f);
    }

    *m_value = m_clamp_min + m_value_based * (m_clamp_max - m_clamp_min);

    update_geometry();
}

void slider::update_geometry() {
    sf::Color current_active_color = {
        static_cast<uint8_t>(m_color_inactive.r + m_color_fade * (m_color_active.r - m_color_inactive.r)),
        static_cast<uint8_t>(m_color_inactive.g + m_color_fade * (m_color_active.g - m_color_inactive.g)),
        static_cast<uint8_t>(m_color_inactive.b + m_color_fade * (m_color_active.b - m_color_inactive.b)),
        static_cast<uint8_t>(m_color_inactive.a + m_color_fade * (m_color_active.a - m_color_inactive.a))};

    float fill_width = m_value_based * m_size.x;
    float half_y = m_size.y / 2.f;
    size_t offset = 0;

    sf::Vector2f bg_tl = {m_position.x, m_position.y - half_y};
    sf::Vector2f bg_br = {m_position.x + m_size.x, m_position.y + half_y};

    m_vertices[offset++] = sf::Vertex(bg_tl, m_color_background);
    m_vertices[offset++] = sf::Vertex({bg_br.x, bg_tl.y}, m_color_background);
    m_vertices[offset++] = sf::Vertex(bg_br, m_color_background);
    m_vertices[offset++] = sf::Vertex(bg_tl, m_color_background);
    m_vertices[offset++] = sf::Vertex(bg_br, m_color_background);
    m_vertices[offset++] = sf::Vertex({bg_tl.x, bg_br.y}, m_color_background);

    sf::Vector2f fill_br = {m_position.x + fill_width, m_position.y + half_y};
    m_vertices[offset++] = sf::Vertex(bg_tl, current_active_color);
    m_vertices[offset++] = sf::Vertex({fill_br.x, bg_tl.y}, current_active_color);
    m_vertices[offset++] = sf::Vertex(fill_br, current_active_color);
    m_vertices[offset++] = sf::Vertex(bg_tl, current_active_color);
    m_vertices[offset++] = sf::Vertex(fill_br, current_active_color);
    m_vertices[offset++] = sf::Vertex({bg_tl.x, fill_br.y}, current_active_color);

    sf::Vector2f left_cap_center = m_position;
    for (size_t i = 0; i < m_circle_segments; ++i) {
        m_vertices[offset++] = sf::Vertex(left_cap_center, current_active_color);
        m_vertices[offset++] = sf::Vertex(left_cap_center + sf::Vector2f(m_lut_cos[i] * half_y, m_lut_sin[i] * half_y),
                                          current_active_color);
        m_vertices[offset++] = sf::Vertex(
            left_cap_center + sf::Vector2f(m_lut_cos[i + 1] * half_y, m_lut_sin[i + 1] * half_y), current_active_color);
    }

    sf::Vector2f right_cap_center = {m_position.x + m_size.x, m_position.y};
    for (size_t i = 0; i < m_circle_segments; ++i) {
        m_vertices[offset++] = sf::Vertex(right_cap_center, m_color_background);
        m_vertices[offset++] = sf::Vertex(right_cap_center + sf::Vector2f(m_lut_cos[i] * half_y, m_lut_sin[i] * half_y),
                                          m_color_background);
        m_vertices[offset++] = sf::Vertex(
            right_cap_center + sf::Vector2f(m_lut_cos[i + 1] * half_y, m_lut_sin[i + 1] * half_y), m_color_background);
    }

    sf::Vector2f thumb_center = {m_position.x + fill_width, m_position.y};
    float thumb_radius = m_size.y * (0.75f + 0.25f * m_size_fade);
    for (size_t i = 0; i < m_circle_segments; ++i) {
        m_vertices[offset++] = sf::Vertex(thumb_center, current_active_color);
        m_vertices[offset++] =
            sf::Vertex(thumb_center + sf::Vector2f(m_lut_cos[i] * thumb_radius, m_lut_sin[i] * thumb_radius),
                       current_active_color);
        m_vertices[offset++] =
            sf::Vertex(thumb_center + sf::Vector2f(m_lut_cos[i + 1] * thumb_radius, m_lut_sin[i + 1] * thumb_radius),
                       current_active_color);
    }
}

void slider::render(sf::RenderWindow &window) { window.draw(m_vertices); }