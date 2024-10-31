//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//This header contains the core class of the engine.

#ifndef __CORE_H__
#define __CORE_H__ 1

#include <memory>

#include "engine/entity_manager.h"
#include "engine/components/camera_component.h"
#include "engine/engine_input.h"

static float delta_time;

namespace OpenGLEngine {

  namespace Engine {

    class Core {
    public:

      Core();
      ~Core();

      bool InitializeCore();
      void DeinitializeCore();

      void* GetWindow() const;

      bool RunningState() const;

      void BufferHandler();
      void EventsHandler();
      void Update();
      void Render();
      void FPS();

      static std::unique_ptr<EntityManager> entity_manager_;
      static std::shared_ptr<CameraComponent> camera_;

    private:             
      struct CoreData;
      std::unique_ptr<CoreData> data_;
    };

    extern std::unique_ptr<Core> core;
  }

  int main(int argc, char** argv);
}
#endif
