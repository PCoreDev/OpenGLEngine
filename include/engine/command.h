//Author: Pablo "Pau" Core Palmero
//Date: 4-June-2024
//Email: p.core.dev@outlook.com
//This header contains the primitive class of the engine to render objectes.
#ifndef __COMMAND_H__
#define __COMMAND_H__ 1

#include <memory>
#include <list>

#include "engine/entity.h"
#include "engine/shader.h"
#include "engine/entity_manager.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


struct Command {
  virtual void Execute() = 0;
};

struct ClearCommand : public Command {
  ClearCommand(float R, float G, float B, float A = 1.0f) : r(R), g(G), b(B), a(A) {};
  //ClearCommand(gml::Vec4 color);
  void Execute() override;
  float r, g, b, a;
};

//struct DrawCommand : public Command{
//  DrawCommand(Entity& e) : entity(std::make_shared<Entity>(e)) {};
//  void Execute() override;
//  std::shared_ptr<Entity> entity;
// };

struct DrawRenderBufferCommand : public Command {
  DrawRenderBufferCommand(EntityManager& manager, Shader& s, unsigned int fbo, unsigned int fb_texture, unsigned int quad_vao, unsigned int quad_ibo);
  void BindUniforms();
  void Execute() override;
  std::shared_ptr<Shader> shader;
  std::shared_ptr<EntityManager> entity_manager;
  unsigned int screen_quad_vao;
  unsigned int screen_quad_ibo;
  unsigned int framebuffer_texture;
  unsigned int framebuffer;
};

class DisplayList {
  public:
    DisplayList() = default;
    DisplayList(const DisplayList& other) = delete;
    DisplayList(DisplayList&& other) noexcept;
    DisplayList& operator=(const DisplayList& other) = delete;
    DisplayList& operator=(DisplayList&& other) noexcept;
    ~DisplayList();

    bool IsEmpty() const;
    void Clear();
    void Swap(DisplayList& other);


    void AddClearCommand(float r, float g, float b, float a);
    //void AddDrawCommand(Entity& entity);
    void AddDrawRenderBufferCommand(EntityManager& manager, Shader& s, unsigned int fbo, unsigned int fb_texture, unsigned int quad_vao, unsigned int quad_ibo);



    void Execute();
  private:
    std::list<std::unique_ptr<Command>> commands_;
};



#endif // !__COMMAND_H__
