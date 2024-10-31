#ifndef __RENDER_COMPONENT__
#define __RENDER_COMPONENT__ 1

#include "engine/component.h"

struct RenderComponent : public Component {

  RenderComponent() = default;
  RenderComponent(std::weak_ptr<Entity> entity);
  RenderComponent(const RenderComponent& other);
  RenderComponent(RenderComponent&& other);
  ~RenderComponent() = default;
  RenderComponent& operator=(RenderComponent&& other);
  void operator=(const RenderComponent& other);
  bool IsEnabled();
  void SetEnabled(bool enabled);

  void Render();

  std::unique_ptr<class RenderData> data;
};



#endif // !__RENDER_COMPONENT__
