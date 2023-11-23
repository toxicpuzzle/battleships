//
// Created by toxic on 7/08/2023.
//

#include "raylib.h"
#include "Renderables.h"
#include <algorithm>
#include <iostream>
// Dimensions - x = width, y = height.
Renderable::Renderable(Rectangle r) :
    m_id{nextId++}, m_rect {r}, m_toRender{true}{}

Renderer::Renderer() {}

bool Renderable::operator == (const Renderable& other) const{
    return this->m_id == other.m_id;
}

int Renderer::addObj(Renderable *g)
{
    toRender.push_back(g);
}

int Renderable::getId(){return m_id;}

void Renderer::render()
{
    for (Renderable *obj: toRender) {
        if (obj->shouldRender()) obj->render();
    }
}

void Renderer::removeObj(int objId){
    std::cout << this->toRender.size() << "\n";
    int idx = -1;
    int curr = 0;
    for (Renderable* r: toRender){
        std::cout << r->getId() << ", ";
        if (r->getId() == objId) {
            idx = curr;
            break;
        };
        curr++;
    }
    if (idx == -1) throw new std::runtime_error("no idx for obj");
    toRender.erase(toRender.begin() + idx);

//    std::remove_if(toRender.begin(), toRender.end(), [&objId](Renderable* r){
//        return r->getId() == objId;
//    });
//    std::cout << this->toRender.size() << "\n";
}

void Renderable::removeFrom(Renderer* r){
    r->removeObj(m_id);
}

int Renderable::nextId = 0;

Renderable::Renderable(Rectangle r, bool m_toRender):
    m_rect{r}, m_toRender{m_toRender}
{
}

