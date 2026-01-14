//
// Created by toxic on 8/08/2023.
//

#ifndef VISUALISER_BUTTON_H
#define VISUALISER_BUTTON_H

#include "Renderables.h"
#include "EventHandler.h"
#include <string>
#include <functional>
#include "raylib.h"

class Button : public Renderable, public EventHandler {
    std::string m_text;
    Texture m_texture;
    std::function<void()> m_onClick;

public:
    Button(Vector2 pos, std::string text, Texture texture);

    void render() override;

    bool isClicked(Vector2 mousePos);

    // Set click callback
    void setOnClick(std::function<void()> callback);

    // EventHandler override
    bool onMouseButtonPressed(const MouseButtonPressedEvent& event) override;
};


#endif //VISUALISER_BUTTON_H
