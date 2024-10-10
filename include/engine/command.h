//Author: Pablo "Pau" Core Palmero
//Date: 4-June-2024
//Email: p.core.dev@outlook.com
//This header contains the primitive class of the engine to render objectes.
#ifndef __COMMAND_H__
#define __COMMAND_H__ 1


struct Command
{
    virtual void execute() = 0;
};

struct ClearCommand : public Command
{
  void Clear(float R, float G, float B, float A = 1.0f);
  //ClearCommand(gml::Vec4 color);
  void execute() override;
  float r, g, b, a;
};

struct DrawCommand : public Command
{
  void Draw();
  void BindUniforms();
  void execute() override;
};

struct DrawRenderBufferCommand : public Command
{
  void DrawRenderBuffer();
  void BindUniforms();
  void execute() override;
};



#endif // !__COMMAND_H__
