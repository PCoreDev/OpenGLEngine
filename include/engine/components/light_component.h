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
  LightComponent(const LightComponent&) = default;
  ~LightComponent();

  void SetLightType(LightType type);
  void SetAmbient(glm::vec3 ambient);
  void SetDiffuse(glm::vec3 diffuse);
  void SetSpecular(glm::vec3 specular);
  void SetLightColor(glm::vec3 color);

  LightType GetLightType() const;
  glm::vec3 GetLightColor() const;


private:
  std::unique_ptr<class LightData> data_;
};

#endif // !__LIGHT_COMPONENT_H__