//
// Created by toxic on 8/08/2023.
//

#include "Button.h"
#include "raylib.h"

Button::Button(Vector2 pos, std::string text, Texture texture)
: Renderable{Rectangle{pos.x, pos.y, 100.0, 50.0}},
    m_text{text}, m_texture{texture}, m_onClick{nullptr}{}

void Button::render(){
    Vector2 textPos = {m_rect.x + m_rect.width/2, m_rect.y +m_rect.height/2};
    DrawTexture(m_texture, m_rect.x,m_rect.y, WHITE);
    DrawText(m_text.c_str(), textPos.x, textPos.y, 10, GRAY);
}

bool Button::isClicked(Vector2 mousePos){
    return CheckCollisionPointRec(mousePos, this->m_rect) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void Button::setOnClick(std::function<void()> callback) {
    m_onClick = callback;
}

bool Button::onMouseButtonPressed(const MouseButtonPressedEvent& event) {
    if (event.getButton() == MOUSE_BUTTON_LEFT &&
        CheckCollisionPointRec(event.getPosition(), this->m_rect)) {
        if (m_onClick) {
            m_onClick();
        }
        return true; // Event handled
    }
    return false;
}