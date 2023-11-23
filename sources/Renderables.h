//
// Created by toxic on 7/08/2023.
//

#ifndef VISUALISER_RENDERABLES_H
#define VISUALISER_RENDERABLES_H
#include <vector>
#include "raylib.h"

class Renderable;
class Renderer;

class Renderable {

protected:
    static int nextId;
    int m_id;
    Rectangle m_rect;
    bool m_toRender;

public:
    explicit Renderable(Rectangle r);

    explicit Renderable(Rectangle r, bool m_toRender);

    virtual void render() {};

    void removeFrom(Renderer* r);

    Rectangle rect(){ return m_rect; }

    int getId();

    Vector2 coords(){ return Vector2{m_rect.x, m_rect.y};}

    bool operator == (const Renderable& other) const;

    bool shouldRender(){ return m_toRender; }

    void setRenderStatus(bool status){ m_toRender = status; }
};

class Renderer {
    std::vector<Renderable *> toRender{}; // cannot have pointers to references

public:
    Renderer();

    int addObj(Renderable *g);

    void removeObj(int objId);

    void render();
};

#endif //VISUALISER_RENDERABLES_H
