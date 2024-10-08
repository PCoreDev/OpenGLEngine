//Author: Pablo "Pau" Core Palmero
//Date: 5-June-2024
//Email: p.core.dev@outlook.com
//This header contains the component class of the engine to add differents properties to the objects.
#ifndef __COMPONENT_H__
#define __COMPONENT_H__ 1

#include <memory>
#include <vector>
#include "glm/glm.hpp"


enum ComponentType {
  ComponentType_Invalid = 0,
  ComponentType_Render,
  ComponentType_Transform,
  ComponentType_Physics,
  ComponentType_Node,
  ComponentType_Sound,
  ComponentType_Light,
  ComponentType_Camera,
  ComponentType_Mesh,
  ComponentType_MAX,
};

	struct Component{

	protected:
		Component() = default;
		Component(const Component&) = default;

		int id;
		ComponentType type;

	public:
		int GetId() const { return id; }
    ComponentType GetType() const { return type; }
	};

  //TODO CHeck why I can't do a forward declaration of MeshData
  struct TransformData {
  public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
  private:

    glm::mat4 m_translation;
    glm::mat4 m_rotation;
    glm::mat4 m_scale;
    glm::mat4 m_model;
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

		std::unique_ptr<TransformData> data;

  };

	struct RenderComponent : public Component {

		RenderComponent() = default;
		RenderComponent(int id);
    RenderComponent(const RenderComponent&) = default;
    void operator=(const RenderComponent& other);
	};

  //TODO CHeck why I can't do a forward declaration of MeshData
  struct MeshData {
    std::vector<float> vertex_data;
    int n_vertex = 0;
    std::vector<unsigned int> index_data;
  };
	    
  struct MeshComponent : public Component {
    MeshComponent() = default;
    MeshComponent(int id);
    MeshComponent(const MeshComponent&) = default;
    void operator=(const MeshComponent& other);
    void Triangle();
    void Square();
    float* GetVertexData();
    size_t GetVertexSizeb();
    size_t GetVertexCount();
    std::unique_ptr<MeshData> data;
  };
#endif // !__COMPONENT_H__
