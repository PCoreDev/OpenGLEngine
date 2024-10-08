//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//Entity manager controls the entities.

#pragma once

#include <memory>

class EntityManager {

public:
  EntityManager();
  ~EntityManager();

  std::shared_ptr<class Entity> CreateEntity();
  size_t GetNumberOfEntities() const;


  private:
  std::unique_ptr<class EntityManagerData> data_;

};
