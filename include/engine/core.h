/*****************************************************************//**
 * \file   core.h
 * \brief  Core file of the engine.
 * 
 * \author Pablo "Pau" Core Palmero
 * \mail p.core.dev@outlook.com
 * \date   May 2024
 *********************************************************************/

#ifndef __CORE_H__
#define __CORE_H__ 1

#include <memory>

#include "engine/entity_manager.h"
#include "engine/components/camera_component.h"
#include "engine/engine_input.h"
#include "engine/shader.h"

static float delta_time;

namespace OpenGLEngine {

  namespace Engine {

    /** @brief Core class of the engine. */
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

      



      static std::shared_ptr<EntityManager> entity_manager_;
      static std::shared_ptr<CameraComponent> camera_;
      static std::shared_ptr<Shader> shader_;

    private:

      void CreateRenderTexture();
      void CreateRenderBufferObject();
      void CreateRenderQuad();


      void DebugCoreStats();

      struct CoreData;
      std::unique_ptr<CoreData> data_;
    };

    extern std::unique_ptr<Core> core;
  }

  int main(int argc, char** argv);
}
#endif
