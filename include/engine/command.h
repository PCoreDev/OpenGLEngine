//Author: Pablo "Pau" Core Palmero
//Date: 4-June-2024
//Email: p.core.dev@outlook.com
//This header contains the primitive class of the engine to render objectes.
#ifndef __COMMAND_H__
#define __COMMAND_H__ 1

#include <memory>
#include <list>

#include "engine/entity.h"
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



struct DrawCommand : public Command{
  DrawCommand(Entity& e);
  void Execute() override;
  std::shared_ptr<Entity> entity;
 };

struct DrawRenderBufferCommand : public Command {
  DrawRenderBufferCommand();
  void BindUniforms();
  void Execute() override;
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
    void AddDrawCommand(Entity& entity);
    void AddDrawRenderBufferCommand();



    void Execute();
  private:
    std::list<std::unique_ptr<Command>> commands_;
};



#endif // !__COMMAND_H__
