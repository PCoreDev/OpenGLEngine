#pragma once

#include <memory>

class Entity
{
public:
    ~Entity();
    //Getters
    int ID();
    //Setters
    void AddComponent(const class Component& component);
private:
    Entity();
    std::unique_ptr<class EntityData> data_;
};

