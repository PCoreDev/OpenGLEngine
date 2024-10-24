#ifndef __ENTITY_H__
#define __ENTITY_H__ 1

#include <memory>
#include "engine/component.h"

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
  std::shared_ptr<class ShaderComponent> GetShaderComponent();
  std::shared_ptr<class TransformComponent> GetTransformComponent();
  std::shared_ptr<class CameraComponent> GetCameraComponent();
  std::shared_ptr<class MaterialComponent> GetMaterialComponent();
  std::shared_ptr<class RenderComponent> GetRenderComponent();


  //Setters
  void AddRenderComponent();
  void AddTransformComponent();
 // void AddPhysicsComponent();
 // void AddNodeComponent();
 // void AddSoundComponent();
 // void AddLightComponent();
  void AddCameraComponent();
  void AddMeshComponent();
  void AddShaderComponent();
  void AddMaterialComponent();

private:
  std::unique_ptr<class EntityData> data_;

};


#endif // !__ENTITY_H__
