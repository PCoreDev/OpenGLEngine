/*****************************************************************//**
 * \file   entity.h
 * \brief  
 * 
 * \author Pablo "Pau" Core Palmero
 * \mail p.core.dev@outlook.com
 * \date   May 2024
 *********************************************************************/

#ifndef __ENTITY_H__
#define __ENTITY_H__ 1

#include <memory>
#include <string>

class Entity : public std::enable_shared_from_this<Entity>{

public:
  Entity() = default;
  Entity(int id);
  Entity(const Entity& entity); //Copy constructor
  Entity(Entity&& entity) noexcept; //Move constructor
  Entity& operator=(const Entity& entity); //Copy assignment operator
  void operator=(Entity&& entity) noexcept; //Move assignment operator
  ~Entity();

  //Getters
  int ID();
  std::string GetName() const;

  std::shared_ptr<class MeshComponent>  GetMeshComponent();
  std::shared_ptr<class ShaderComponent> GetShaderComponent();
  std::shared_ptr<class TransformComponent> GetTransformComponent();
  std::shared_ptr<class CameraComponent> GetCameraComponent();
  std::shared_ptr<class MaterialComponent> GetMaterialComponent();
  std::shared_ptr<class RenderComponent> GetRenderComponent();
  std::shared_ptr<class LightComponent> GetLightComponent();
  std::shared_ptr<class SkyBoxComponent> GetSkyBoxComponent();


  //Setters
  void AddRenderComponent();
  void AddTransformComponent();
 // void AddPhysicsComponent();
 // void AddSoundComponent();
  void AddLightComponent();
  void AddCameraComponent();
  void AddMeshComponent();
  void AddShaderComponent();
  void AddMaterialComponent();
  void AddSkyBoxComponent();

  void SetName(const std::string name);

  void ShowStats();

private:
  std::unique_ptr<class EntityData> data_;

};


#endif // !__ENTITY_H__
