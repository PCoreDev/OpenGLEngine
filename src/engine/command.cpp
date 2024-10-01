//Author: Pablo "Pau" Core Palmero
//Date: 4-June-2024
//Email: p.core.dev@outlook.com
//This header contains the primitive class of the engine to render objectes.


#include "engine/command.h"

namespace gml{
    struct Vec4;
}

class Primitive;


struct Command{
   virtual void Execute() = 0;
};

struct ClearCommand : public Command{
    ClearCommand(gml::Vec4 color);
    void Execute() override;
};

struct DrawCommand : public Command{
    DrawCommand(Primitive* primitive);
    void Execute() override;
};

struct ShaderCommand : public Command{
    ShaderCommand(const char* vertexPath, const char* fragmentPath);
    void Execute() override;
};
