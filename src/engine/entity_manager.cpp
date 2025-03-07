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
  std::vector<std::shared_ptr<Entity>> lights;;
};

EntityManager::EntityManager() {
  data_ = std::make_unique<EntityManagerData>();
}

EntityManager::EntityManager(const EntityManager& other)
{
  data_ = std::make_unique<EntityManagerData>(*other.data_);
}

EntityManager::EntityManager(EntityManager&& other) noexcept
{
  data_ = std::move(other.data_);
  other.data_ = nullptr;
}

EntityManager::~EntityManager() {
  data_->entities.clear();
  data_->lights.clear();
  data_.reset();
}

EntityManager& EntityManager::operator=(const EntityManager& other)
{
  data_ = std::make_unique<EntityManagerData>(*other.data_);
  return *this;
}

void EntityManager::operator=(EntityManager&& other) noexcept
{
  data_ = std::move(other.data_);
  other.data_ = nullptr;
}

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

std::vector<std::weak_ptr<class Entity>> EntityManager::GetEntitiesWithLights() const {
  std::vector<std::weak_ptr<Entity>> weak_lights;
  for (auto entity : data_->entities) {
    if (entity->GetLightComponent() != nullptr) {
      weak_lights.push_back(entity);
    }
  }

  return weak_lights;
}