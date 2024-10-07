#include "engine/entity.h"

struct EntityData {
    int id_;
    //std::Vector<Component> components_;
    EntityData() : id_(0) {}
};

Entity::Entity() {
}

Entity::~Entity() {
}

//Setters

int Entity::ID() {
    return data_->id_;
}

//Getters
void Entity::AddComponent(const class Component& component) {
    //data_->components_.push_back(component);
}
