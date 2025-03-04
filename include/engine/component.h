/*****************************************************************//**
 * \file   component.h
 * \brief  This header contains the component class of the engine to add differents properties to the objects.
 * 
 * \author Pablo "Pau" Core Palmero
 * \mail p.core.dev@outlook.com
 * \date   June 2025
 *********************************************************************/

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
    virtual void ShowStats() = 0;
	};
   
#endif // !__COMPONENT_H__
