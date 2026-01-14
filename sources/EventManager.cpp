//
// EventManager Implementation
//

#include "EventManager.h"

EventManager::EventManager() : m_lastMousePosition({0, 0}) {}

void EventManager::addHandler(EventHandler* handler) {
    m_handlers.push_back(handler);
}

void EventManager::removeHandler(EventHandler* handler) {
    m_handlers.erase(
        std::remove(m_handlers.begin(), m_handlers.end(), handler),
        m_handlers.end()
    );
}

void EventManager::clearHandlers() {
    m_handlers.clear();
}

void EventManager::dispatchEvent(Event& event) {
    for (auto* handler : m_handlers) {
        if (event.isHandled()) {
            break; // Event was handled, stop propagation
        }

        bool handled = false;
        switch (event.getType()) {
            case EventType::MOUSE_BUTTON_PRESSED:
                handled = handler->onMouseButtonPressed(
                    static_cast<const MouseButtonPressedEvent&>(event));
                break;
            case EventType::MOUSE_BUTTON_RELEASED:
                handled = handler->onMouseButtonReleased(
                    static_cast<const MouseButtonReleasedEvent&>(event));
                break;
            case EventType::MOUSE_MOVED:
                handled = handler->onMouseMoved(
                    static_cast<const MouseMovedEvent&>(event));
                break;
            case EventType::KEY_PRESSED:
                handled = handler->onKeyPressed(
                    static_cast<const KeyPressedEvent&>(event));
                break;
            case EventType::KEY_RELEASED:
                handled = handler->onKeyReleased(
                    static_cast<const KeyReleasedEvent&>(event));
                break;
            default:
                break;
        }

        if (handled) {
            event.setHandled(true);
        }
    }
}

void EventManager::pollEvents() {
    // Poll mouse button events
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        MouseButtonPressedEvent event(mousePos, MOUSE_BUTTON_LEFT);
        dispatchEvent(event);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        Vector2 mousePos = GetMousePosition();
        MouseButtonPressedEvent event(mousePos, MOUSE_BUTTON_RIGHT);
        dispatchEvent(event);
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
        Vector2 mousePos = GetMousePosition();
        MouseButtonPressedEvent event(mousePos, MOUSE_BUTTON_MIDDLE);
        dispatchEvent(event);
    }

    // Poll mouse movement
    Vector2 currentMousePos = GetMousePosition();
    if (currentMousePos.x != m_lastMousePosition.x ||
        currentMousePos.y != m_lastMousePosition.y) {
        MouseMovedEvent event(currentMousePos);
        dispatchEvent(event);
        m_lastMousePosition = currentMousePos;
    }

    // Poll keyboard events - check commonly used keys
    // You can expand this to check more keys as needed
    if (IsKeyPressed(KEY_R)) {
        KeyPressedEvent event(KEY_R);
        dispatchEvent(event);
    }

    // Add more key checks as needed for your game
    if (IsKeyPressed(KEY_SPACE)) {
        KeyPressedEvent event(KEY_SPACE);
        dispatchEvent(event);
    }

    if (IsKeyPressed(KEY_ENTER)) {
        KeyPressedEvent event(KEY_ENTER);
        dispatchEvent(event);
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        KeyPressedEvent event(KEY_ESCAPE);
        dispatchEvent(event);
    }
}
