#ifndef __SKYBOX_COMPONENT_H__
#define __SKYBOX_COMPONENT_H__ 1

#include "engine/component.h"

#include <memory>
#include <vector>
#include <string>


class SkyBoxComponent : public Component {


public:
  SkyBoxComponent() = default;
  SkyBoxComponent(std::weak_ptr<Entity> entity);
  SkyBoxComponent(const SkyBoxComponent& other);
  SkyBoxComponent(SkyBoxComponent&& other) noexcept;
  void operator=(const SkyBoxComponent& other);
  SkyBoxComponent& operator=(SkyBoxComponent&& other) noexcept;

  ~SkyBoxComponent();

  unsigned int GetSkyBoxID() const;

  void LoadSkyBox(std::vector<std::string> faces_path);

  void SendToShader();

private:
  std::unique_ptr<class SkyBoxData> data_;
};

#endif // !__SKYBOX_COMPONENT_H__
