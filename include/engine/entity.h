#pragma once

#include <memory>

class Entity{

public:
  Entity();
  Entity(int id);
  Entity(const Entity& entity);
  Entity(Entity&& entity);
  Entity& operator=(const Entity& entity);
  ~Entity();

  //Getters
  int ID();

  std::shared_ptr<class MeshComponent>  GetMeshComponent();

  //Setters
  void AddRenderComponent();
  void AddTransformComponent();
 // void AddPhysicsComponent();
 // void AddNodeComponent();
 // void AddSoundComponent();
 // void AddLightComponent();
 // void AddCameraComponent();
  void AddMeshComponent();
  //void AddMaterialComponent();

private:
  std::unique_ptr<class EntityData> data_;

};

