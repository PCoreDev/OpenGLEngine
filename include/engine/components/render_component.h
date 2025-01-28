/*****************************************************************//**
 * \file   render_component.h
 * \brief  
 * 
 * \author Pablo "Pau" Core Palmero
 * \mail p.core.dev@outlook.com
 * \date   May 2024
 *********************************************************************/

#ifndef __RENDER_COMPONENT__
#define __RENDER_COMPONENT__ 1

#include "engine/component.h"

//TODO: Change this to hide it in cpp file
struct RenderData {
  bool enabled;
};

class Shader;

class RenderComponent: public Component{
public:
  RenderComponent() = default;
  RenderComponent(std::weak_ptr<Entity> entity, bool enable = true); 
  RenderComponent(const RenderComponent& other); //Copy constructor
  RenderComponent(RenderComponent&& other) noexcept; //Move constructor
  RenderComponent& operator=(RenderComponent&& other) noexcept; //Move assignment operator
  void operator=(const RenderComponent& other); //Copy assignment operator

  ~RenderComponent() = default;


  bool IsEnabled();

  void SetEnabled(bool enabled);

  void Render();

  void RenderLights(std::shared_ptr<Shader> shader);

  void MatrixToShader(std::shared_ptr<Shader> shader);


private:
  std::unique_ptr<RenderData> data;
};



#endif // !__RENDER_COMPONENT__
