//
// Created by toxic on 8/08/2023.
//

#include "Button.h"
#include "raylib.h"

Button::Button(Vector2 pos, std::string text, Texture texture)
: Renderable{Rectangle{pos.x, pos.y, 100.0, 50.0}},
    m_text{text}, m_texture{texture}{}

void Button::render(){
    Vector2 textPos = {m_rect.x + m_rect.width/2, m_rect.y +m_rect.height/2};
    DrawTexture(m_texture, m_rect.x,m_rect.y, WHITE);
    DrawText(m_text.c_str(), textPos.x, textPos.y, 10, GRAY);
}

bool Button::isClicked(Vector2 mousePos){
    return CheckCollisionPointRec(mousePos, this->m_rect) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}