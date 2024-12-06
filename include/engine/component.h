//Author: Pablo "Pau" Core Palmero
//Date: 5-June-2024
//Email: p.core.dev@outlook.com
//This header contains the component class of the engine to add differents properties to the objects.
#ifndef __COMPONENT_H__
#define __COMPONENT_H__ 1

#include <memory>
#include <vector>
#include <string>
#include "glm/glm.hpp"

//#include "engine/entity.h"



	class Component {
  public:

    enum ComponentType {
      ComponentType_Invalid = 0,
      ComponentType_Render,
      ComponentType_Transform,
      ComponentType_Physics,
      ComponentType_Shader,
      ComponentType_Node,
      ComponentType_Sound,
      ComponentType_Light,
      ComponentType_Camera,
      ComponentType_Mesh,
      ComponentType_Material,
      ComponentType_SkyBox,
      ComponentType_MAX,
    };

	protected:
    Component();
		Component(const Component&) = default;
    virtual ~Component() = default;

		int id;
		ComponentType type;
    std::weak_ptr<class Entity> entity;

	public:
		inline int GetId() const { return id; }
    inline ComponentType GetType() const { return type; }
	};
   
#endif // !__COMPONENT_H__
