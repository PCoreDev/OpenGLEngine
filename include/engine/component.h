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

	struct RenderComponent : public Component {

		RenderComponent() = default;
		RenderComponent(int id);
    RenderComponent(const RenderComponent&) = default;
    void operator=(const RenderComponent& other);
	};

	struct MaterialComponent : public Component {

    MaterialComponent() = default;
    MaterialComponent(int id);
    MaterialComponent(const MaterialComponent&) = default;
    void operator=(const MaterialComponent& other);
    //Setters******************************************************
    //TEXTURE
    void SetTexture(unsigned int texture_ID);
    //BASE COLOR
    void SetBaseColor(float R, float G, float B, float A = 255.0f);
    void SetBaseColor(glm::vec4 color);
    void SetBaseColor(float color[4]);
    //ALBEDO
    void SetAlbedo(float R, float G, float B);
    void SetAlbedo(glm::vec3 emissive);
    void SetAlbedo(float emissive[3]);
    //EMISSIVE
    void SetEmissive(float emissive);
    //ROUGHNESS
    void SetRoughness(float roughness);
    //METALLICNESS
    void SetMetallic(float metallic);
    //AMBIENT OCLUSSION
    void SetAmbientOclussion(float ambientOcclusion);
    //LIGHT
    void SetAffectedByLight(bool affected);
    //SHADOWS
    void SetCanCastShadows(bool can_cast_shadow);
    //MATERIAL PARAMETERS
    void SetMaterialParameters(std::shared_ptr<class MaterialParameters> material_parameters);

    //Getters******************************************************
    //TEXTURE
    unsigned int GetTextureID();
    //BASE COLOR
    std::unique_ptr <float[]> GetBaseColorfptr()const;
    glm::vec4 GetBaseColorAsVector4()const;
    //ALBEDO
    std::unique_ptr<float[]> GetAlbedoAfloatPointer()const;
    glm::vec3  GetAlbedoAsVector3()const;
    //EMISSIVE
    float GetEmissive()const;
    //ROUGHNESS
    float GetRoughness()const;
    //METALLICNESS
    float GetMetallic()const;
    //AMBIENT OCLUSSION
    float GetAmbientOclussion()const;
    //LIGHT
    bool GetAffectedByLight()const;
    //SHADOWS
    bool GetCanCastShadows()const;
    //MATERIAL PARAMETERS
    std::shared_ptr<class MaterialParameters> GetMaterialParameters()const;
  private:
        std::unique_ptr<class MaterialParameters> data;
  };
}

#endif // !__COMPONENT_H__