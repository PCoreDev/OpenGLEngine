//Author: Pablo "Pau" Core Palmero
//Date: 5-June-2024
//Email: p.core.dev@outlook.com
//This header contains the component class of the engine to add differents properties to the objects.
#ifndef __COMPONENT_H__
#define __COMPONENT_H__ 1

#include <memory>
#include "glm/glm.hpp"

namespace OpenGLEngine {

	struct Component{

	protected:
		Component() = default;
		Component(const Component&) = default;

		int id;
		enum ComponentType type;

	public:
		int GetId() const { return id; }
	};

	struct TransformComponent : public Component {
	public:
    TransformComponent() = default;
    TransformComponent(const TransformComponent&) = default;
		TransformComponent(int id);

		void operator=(const TransformComponent& other);

		//Setters
		void SetPosition(float x, float y, float z);
		void SetPosition(float position[3]);
		void SetPosition(glm::vec3 position);

		void SetRotation(float x, float y, float z);
		void SetRotation(float rotation[3]);
		void SetRotation(glm::vec3 rotation);

		void SetScale(float x, float y, float z);
		void SetScale(float scale[3]);
		void SetScale(glm::vec3 scale);

		//Getters

	private:

		std::unique_ptr<class TransformData> data;

  };

}

#endif // !__COMPONENT_H__