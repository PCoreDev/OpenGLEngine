//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//Entity manager controls the entities.

#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__ 1

#include <memory>
#include <vector>

class EntityManager {

public:
  EntityManager();
  ~EntityManager();

  std::shared_ptr<class Entity> CreateEntity();
  size_t GetNumberOfEntities() const;

  std::vector<std::weak_ptr<class Entity>> GetEntities() const;


  private:
  std::unique_ptr<class EntityManagerData> data_;

};

#endif // !__ENTITY_MANAGER_H__
