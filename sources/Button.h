//
// Created by toxic on 8/08/2023.
//

#ifndef VISUALISER_BUTTON_H
#define VISUALISER_BUTTON_H

#include "Renderables.h"
#include <string>
#include "raylib.h"

class Button : public Renderable{
    std::string m_text;
    Texture m_texture;

public:
    Button(Vector2 pos, std::string text, Texture texture);

    void render() override;

    bool isClicked(Vector2 mousePos);
};


#endif //VISUALISER_BUTTON_H
