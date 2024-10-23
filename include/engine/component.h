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
  ComponentType_Material,
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
    int parent_id;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::mat4 m_traslation;
    glm::mat4 m_rotation;
    glm::mat4 m_scale;
    //glm::mat4 m_model;
  };

	struct TransformComponent : public Component {
	public:

    //TODO: review the component transformations.

    TransformComponent() = default;
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
    void SetParent(class Entity entity);

    //TODO:Make local transformations

		//Getters

    glm::vec3 GetPosition() const;
    glm::vec3 GetRotation() const;
    glm::vec3 GetScale() const;
    glm::mat4 GetTraslationMatrix() const;
    glm::mat4 GetScaleMatrix() const;
    glm::mat4 GetRotationMatrix() const;
    glm::mat4 GetModelMatrix() const;

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
    std::vector<float> uv_data;
    std::vector<unsigned int> index_data;
    int n_vertex = 0;
    unsigned int vao, vbo, ibo, nbo, ubo;
    void Bind();
  };
	    
  struct MeshComponent : public Component {
    MeshComponent() = default;
    MeshComponent(int id);
    MeshComponent(const MeshComponent&) = default;
    void operator=(const MeshComponent& other);
    void Triangle();
    void Square();
    void Cube();
    void LoadOBJ(const std::string& path);
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
    void SetUniforms(class Entity& entity);
    int GetShaderProgram();

    std::unique_ptr<ShaderData> data;
  };

  struct CameraData{
    glm::vec3 camera_position;
    glm::vec3 camera_target;
    glm::vec3 camera_direction;
    glm::vec3 camera_front;
    glm::vec3 camera_up;
    glm::vec3 camera_right;
    glm::mat4 camera_view_matrix;

    float fov;
    float aspect_ratio;
    float near_plane;
    float far_plane;

    glm::mat4 projection_matrix;
    glm::mat4 ortho_matrix;
  };

  struct CameraComponent : public Component{
    CameraComponent() = default;
    CameraComponent(int id);
    void operator=(const CameraComponent& other);
    void SetTarget(glm::vec3 target);
    void SetFOV(float fov);
    void SetAspectRatio(float aspect_ratio);
    void SetNearPlane(float near_plane);
    void SetFarPlane(float far_plane);
    void SetMainCamera();

    glm::vec3 GetTarget();
    glm::vec3 GetDirection();
    glm::vec3 GetUp();
    glm::vec3 GetRight();
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
    glm::mat4 GetOrthoMatrix();
    float GetFOV();
    float GetAspectRatio();
    float GetNearPlane();
    float GetFarPlane();

    void UpdateMatrices();



    std::unique_ptr<CameraData> data;
  };

  struct Texture {
    unsigned int texture;
    int width, height, n_channels;
    unsigned char* data;
    float border_color[4];
  };

  struct MaterialData {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    Texture m_texture;
  };

  struct MaterialComponent : public Component {
    MaterialComponent() = default;
    MaterialComponent(int id);
    MaterialComponent(const MaterialComponent&) = default;
    void operator=(const MaterialComponent& other);
    void LoadTexture(const std::string& path);
    unsigned int GetTexture();

    void Process();

    std::unique_ptr<MaterialData> data;
  };


#endif // !__COMPONENT_H__
