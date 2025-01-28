/*****************************************************************//**
 * \file   light_component.h
 * \brief  
 * 
 * \author pablo
 * \date   January 2025
 *********************************************************************/
#ifndef __LIGHT_COMPONENT_H__
#define __LIGHT_COMPONENT_H__ 1

#include "engine/component.h"
#include "engine/entity.h"

class LightComponent : public Component {
public:

  enum LightType {
    NONE = -1,
    Directional,
    Point,
    Spot,
    MAX
  };

  LightComponent();
  LightComponent(std::weak_ptr<Entity> entity);
  LightComponent(const LightComponent& other);
  LightComponent(LightComponent&& other) noexcept;
  void operator=(LightComponent&& other) noexcept;
  void operator=(const LightComponent& other);
  ~LightComponent();

  void SetLightType(LightType type);
  void SetDirection(glm::vec3 direction);
  void SetAmbient(glm::vec3 ambient);
  void SetDiffuse(glm::vec3 diffuse);
  void SetSpecular(glm::vec3 specular);
  void SetConstant(float constant);
  void SetLinear(float linear);
  void SetQuadratic(float quadratic);
  void SetCutOff(float angle);
  void SetLightColor(glm::vec3 color);

  LightType GetLightType() const;
  glm::vec3 GetDirection() const;
  glm::vec3 GetAmbient() const;
  glm::vec3 GetDiffuse() const;
  glm::vec3 GetSpecular() const;
  float GetConstant() const;
  float GetLinear() const;
  float GetQuadratic() const;
  float GetCutOff() const;
  glm::vec3 GetLightColor() const;

  void ShowStats();

private:
  std::unique_ptr<class LightData> data_;
};

#endif // !__LIGHT_COMPONENT_H__