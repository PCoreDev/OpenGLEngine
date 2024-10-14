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
    TransformComponent(const TransformComponent&);
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
    std::vector<float> normal_data;
    int n_vertex = 0;
    std::vector<unsigned int> index_data;
    unsigned int vao, vbo, ibo;
    void Bind();
  };
	    
  struct MeshComponent : public Component {
    MeshComponent() = default;
    MeshComponent(int id);
    MeshComponent(const MeshComponent&);
    void operator=(const MeshComponent& other);
    void Triangle();
    void Square();
    float* GetVertexData();
    size_t GetVertexSizeb();
    size_t GetVertexCount();
    unsigned int GetVAO();
    unsigned int GetVBO();
    unsigned int GetIBO();
    std::unique_ptr<MeshData> data;
  };

  struct ShaderData {
    std::string vertex_shader_path;
    std::string fragment_shader_path;
    std::string geometry_shader_path;
    std::string vertex_shader_code;
    std::string fragment_shader_code;
    std::string geometry_shader_code;
    int vertex_shader;
    int fragment_shader;
    int geometry_shader;
    int shader_program;
  };

  struct ShaderComponent : public Component {
    //ShaderComponent() = default;
    ShaderComponent(int id);
    //ShaderComponent(const ShaderComponent&);
    //void operator=(const ShaderComponent& other);
    void SetVertexShaderPath(const std::string& path);
    void SetFragmentShaderPath(const std::string& path);
    void SetGeometryShaderPath(const std::string& path);
    std::string LoadShader(const std::string& path, std::string& shader_code);
    int ProcessShader();
    int GetShaderProgram();

    std::unique_ptr<ShaderData> data;
  };
#endif // !__COMPONENT_H__
