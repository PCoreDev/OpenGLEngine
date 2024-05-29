//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//This header contains the core class of the engine.

#ifndef __CORE_H__
#define __CORE_H__ 1

#include <memory>

namespace OpenGLEngine {

  namespace Engine {

    class Core {
    public:

      Core();
      ~Core();

      bool InitializeCore();
      void DeinitializeCore();

    private:
      struct CoreData;
      std::unique_ptr<CoreData> data;
    };

    extern std::unique_ptr<Core> core;
  }

  int main(int argc, char** argv);
}
#endif
