//
// Event System - Base event classes and event type hierarchy
//

#ifndef BATTLESHIPS_EVENT_H
#define BATTLESHIPS_EVENT_H

#include "raylib.h"
#include <memory>

// Event types for identification
enum class EventType {
    NONE = 0,
    MOUSE_BUTTON_PRESSED,
    MOUSE_BUTTON_RELEASED,
    MOUSE_MOVED,
    KEY_PRESSED,
    KEY_RELEASED
};

// Base Event class
class Event {
protected:
    bool m_handled = false;
    EventType m_type;

public:
    Event(EventType type) : m_type(type) {}
    virtual ~Event() = default;

    EventType getType() const { return m_type; }
    bool isHandled() const { return m_handled; }
    void setHandled(bool handled) { m_handled = handled; }
};

// Mouse Button Event
class MouseButtonEvent : public Event {
protected:
    Vector2 m_position;
    int m_button;

public:
    MouseButtonEvent(EventType type, Vector2 position, int button)
        : Event(type), m_position(position), m_button(button) {}

    Vector2 getPosition() const { return m_position; }
    int getButton() const { return m_button; }
};

// Mouse Button Pressed Event
class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    MouseButtonPressedEvent(Vector2 position, int button)
        : MouseButtonEvent(EventType::MOUSE_BUTTON_PRESSED, position, button) {}
};

// Mouse Button Released Event
class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    MouseButtonReleasedEvent(Vector2 position, int button)
        : MouseButtonEvent(EventType::MOUSE_BUTTON_RELEASED, position, button) {}
};

// Mouse Moved Event
class MouseMovedEvent : public Event {
private:
    Vector2 m_position;

public:
    MouseMovedEvent(Vector2 position)
        : Event(EventType::MOUSE_MOVED), m_position(position) {}

    Vector2 getPosition() const { return m_position; }
};

// Key Event
class KeyEvent : public Event {
protected:
    int m_keyCode;

public:
    KeyEvent(EventType type, int keyCode)
        : Event(type), m_keyCode(keyCode) {}

    int getKeyCode() const { return m_keyCode; }
};

// Key Pressed Event
class KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(int keyCode)
        : KeyEvent(EventType::KEY_PRESSED, keyCode) {}
};

// Key Released Event
class KeyReleasedEvent : public KeyEvent {
public:
    KeyReleasedEvent(int keyCode)
        : KeyEvent(EventType::KEY_RELEASED, keyCode) {}
};

#endif //BATTLESHIPS_EVENT_H
