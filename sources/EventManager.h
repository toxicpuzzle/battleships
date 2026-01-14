//
// EventManager - Polls input from raylib and dispatches events to handlers
//

#ifndef BATTLESHIPS_EVENTMANAGER_H
#define BATTLESHIPS_EVENTMANAGER_H

#include "Event.h"
#include "EventHandler.h"
#include "raylib.h"
#include <vector>
#include <memory>

class EventManager {
private:
    std::vector<EventHandler*> m_handlers;
    Vector2 m_lastMousePosition;

    // Dispatch an event to all registered handlers
    void dispatchEvent(Event& event);

public:
    EventManager();
    ~EventManager() = default;

    // Register an event handler
    void addHandler(EventHandler* handler);

    // Remove an event handler
    void removeHandler(EventHandler* handler);

    // Poll all input events from raylib and dispatch them
    void pollEvents();

    // Clear all handlers
    void clearHandlers();
};

#endif //BATTLESHIPS_EVENTMANAGER_H
