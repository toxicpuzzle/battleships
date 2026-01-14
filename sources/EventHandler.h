//
// EventHandler - Interface for components that handle events
//

#ifndef BATTLESHIPS_EVENTHANDLER_H
#define BATTLESHIPS_EVENTHANDLER_H

#include "Event.h"

// Interface for event handlers
class EventHandler {
public:
    virtual ~EventHandler() = default;

    // Handle different event types
    // Return true if the event was handled and should not propagate further
    virtual bool onMouseButtonPressed(const MouseButtonPressedEvent& event) { return false; }
    virtual bool onMouseButtonReleased(const MouseButtonReleasedEvent& event) { return false; }
    virtual bool onMouseMoved(const MouseMovedEvent& event) { return false; }
    virtual bool onKeyPressed(const KeyPressedEvent& event) { return false; }
    virtual bool onKeyReleased(const KeyReleasedEvent& event) { return false; }
};

#endif //BATTLESHIPS_EVENTHANDLER_H
