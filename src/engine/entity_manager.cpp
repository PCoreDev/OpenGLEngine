//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//Entity manager manage the entities.

#include "engine/entity_manager.h"
#include "engine/entity.h"

#include <memory>
#include <vector>

struct EntityManagerData {
  unsigned int n_entities = 0;
  std::vector<std::shared_ptr<Entity>> entities;
};

EntityManager::EntityManager() {
  data_ = std::make_unique<EntityManagerData>();
}

EntityManager::~EntityManager() {}

std::shared_ptr<Entity> EntityManager::CreateEntity() {
  std::shared_ptr<Entity> entity = std::make_shared<Entity>(data_->n_entities);
  
  data_->entities.push_back(entity);
  data_->n_entities++;

  return entity;
}

size_t EntityManager::GetNumberOfEntities() const {
  return data_->n_entities;
}

std::vector<std::weak_ptr<Entity>> EntityManager::GetEntities() const {
  std::vector<std::weak_ptr<Entity>> weak_entities;
  for (auto entity : data_->entities) {
    weak_entities.push_back(entity);
  }
  return weak_entities;
}
