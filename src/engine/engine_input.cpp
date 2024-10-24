#include "engine/engine_input.h"
#include "GLFW/glfw3.h"


#include "loguru/loguru.hpp"

std::shared_ptr<EngineInput::EngineInputData> EngineInput::data_ = std::make_shared<EngineInput::EngineInputData>();

struct EngineInput::EngineInputData {
  bool keys[(int)EngineInput::KeyNames::kKeyNames_MAX] = { false };
  bool mouse_buttons[(int)EngineInput::MouseButtons::kMouseButtons_MAX] = { false };
  double mouse_x, mouse_y;
  double mouse_wheel_x, mouse_wheel_y;

  EngineInputData() {
    mouse_x = 0.0;
    mouse_y = 0.0;
    mouse_wheel_x = 0.0;
    mouse_wheel_y = 0.0;
  }

  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    EngineInput::KeyNames Key = static_cast<EngineInput::KeyNames>(key);

    switch (Key)
    {
    case EngineInput::KeyNames::kKeyNames_Unknown:
      break;
    case EngineInput::KeyNames::kKeyNames_Space:
      if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Apostrophe:
      if (key == GLFW_KEY_APOSTROPHE && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_APOSTROPHE && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Comma:
      if (key == GLFW_KEY_COMMA && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_COMMA && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Minus:
      if (key == GLFW_KEY_MINUS && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_MINUS && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Period:
      if (key == GLFW_KEY_PERIOD && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_PERIOD && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Slash:
      if (key == GLFW_KEY_SLASH && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_SLASH && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Key0:
      if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_0 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Key1:
      if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_1 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Key2:
      if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_2 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Key3:
      if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_3 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Key4:
      if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_4 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Key5:
      if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_5 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Key6:
      if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_6 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Key7:
      if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_7 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Key8:
      if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_8 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Key9:
      if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_9 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Semicolon:
      if (key == GLFW_KEY_SEMICOLON && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_SEMICOLON && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Equal:
      if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_EQUAL && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyA:
      if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyB:
      if (key == GLFW_KEY_B && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_B && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyC:
      if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_C && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyD:
      if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyE:
      if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_E && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyF:
      if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyG:
      if (key == GLFW_KEY_G && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_G && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyH:
      if (key == GLFW_KEY_H && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_H && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyI:
      if (key == GLFW_KEY_I && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_I && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyJ:
      if (key == GLFW_KEY_J && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_J && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyK:
      if (key == GLFW_KEY_K && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_K && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyL:
      if (key == GLFW_KEY_L && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_L && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyM:
      if (key == GLFW_KEY_M && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_M && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyN:
      if (key == GLFW_KEY_N && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_N && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyO:
      if (key == GLFW_KEY_O && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_O && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyP:
      if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_P && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyQ:
      if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_Q && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyR:
      if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_R && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyS:
      if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyT:
      if (key == GLFW_KEY_T && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_T && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyU:
      if (key == GLFW_KEY_U && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_U && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyV:
      if (key == GLFW_KEY_V && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_V && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyW:
      if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyX:
      if (key == GLFW_KEY_X && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_X && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyY:
      if (key == GLFW_KEY_Y && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_Y && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyZ:
      if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_Z && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_LeftBraquets:
      if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Backslash:
      if (key == GLFW_KEY_BACKSLASH && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_BACKSLASH && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_RightBraquets:
      if (key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_GraveAccent:
      if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }

      break;
    case EngineInput::KeyNames::kKeyNames_World1:
      if (key == GLFW_KEY_WORLD_1 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_WORLD_1 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_World2:
      if (key == GLFW_KEY_WORLD_2 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_WORLD_2 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Escape:
      if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
        glfwSetWindowShouldClose(window, GLFW_TRUE);
      }
      else if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Enter:
      if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_ENTER && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Tab:
      if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_TAB && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_BackSpace:
      if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_BACKSPACE && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Insert:
      if (key == GLFW_KEY_INSERT && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_INSERT && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Delete:
      if (key == GLFW_KEY_DELETE && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_DELETE && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Right:
      if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Left:
      if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Down:
      if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Up:
      if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_PageUp:
      if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_PAGE_UP && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_PageDown:
      if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Home:
      if (key == GLFW_KEY_HOME && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_HOME && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_End:
      if (key == GLFW_KEY_END && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_END && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_CapsLock:
      if (key == GLFW_KEY_CAPS_LOCK && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_CAPS_LOCK && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_ScrollLock:
      if (key == GLFW_KEY_SCROLL_LOCK && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_SCROLL_LOCK && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_NumLock:
      if (key == GLFW_KEY_NUM_LOCK && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_NUM_LOCK && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_PrintScreen:
      if (key == GLFW_KEY_PRINT_SCREEN && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_PRINT_SCREEN && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Pause:
      if (key == GLFW_KEY_PAUSE && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_PAUSE && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F1:
      if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F1 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F2:
      if (key == GLFW_KEY_F2 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F2 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F3:
      if (key == GLFW_KEY_F3 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F3 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F4:
      if (key == GLFW_KEY_F4 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F4 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F5:
      if (key == GLFW_KEY_F5 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F5 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F6:
      if (key == GLFW_KEY_F6 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F6 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F7:
      if (key == GLFW_KEY_F7 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F7 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F8:
      if (key == GLFW_KEY_F8 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F8 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F9:
      if (key == GLFW_KEY_F9 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F9 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F10:
      if (key == GLFW_KEY_F10 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F10 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F11:
      if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F11 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F12:
      if (key == GLFW_KEY_F12 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F12 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F13:
      if (key == GLFW_KEY_F13 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F13 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F14:
      if (key == GLFW_KEY_F14 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F14 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F15:
      if (key == GLFW_KEY_F15 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F15 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F16:
      if (key == GLFW_KEY_F16 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F16 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F17:
      if (key == GLFW_KEY_F17 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F17 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F18:
      if (key == GLFW_KEY_F18 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F18 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F19:
      if (key == GLFW_KEY_F19 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F19 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F20:
      if (key == GLFW_KEY_F20 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F20 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F21:
      if (key == GLFW_KEY_F21 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F21 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F22:
      if (key == GLFW_KEY_F22 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F22 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F23:
      if (key == GLFW_KEY_F23 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F23 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F24:
      if (key == GLFW_KEY_F24 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F24 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_F25:
      if (key == GLFW_KEY_F25 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_F25 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyPad_0:
      if (key == GLFW_KEY_KP_0 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_KP_0 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyPad_1:
      if (key == GLFW_KEY_KP_1 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_KP_1 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyPad_2:
      if (key == GLFW_KEY_KP_2 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_KP_2 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyPad_3:
      if (key == GLFW_KEY_KP_3 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_KP_3 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyPad_4:
      if (key == GLFW_KEY_KP_4 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_KP_4 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyPad_5:
      if (key == GLFW_KEY_KP_5 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_KP_5 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyPad_6:
      if (key == GLFW_KEY_KP_6 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_KP_6 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyPad_7:
      if (key == GLFW_KEY_KP_7 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_KP_7 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyPad_8:
      if (key == GLFW_KEY_KP_8 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_KP_8 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyPad_9:
      if (key == GLFW_KEY_KP_9 && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_KP_9 && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyPad_Decimal:
      if (key == GLFW_KEY_KP_DECIMAL && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_KP_DECIMAL && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyPad_Divide:
      if (key == GLFW_KEY_KP_DIVIDE && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_KP_DIVIDE && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyPad_Multiply:
      if (key == GLFW_KEY_KP_MULTIPLY && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_KP_MULTIPLY && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyPad_Subtract:
      if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyPad_Add:
      if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_KP_ADD && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyPad_Enter:
      if (key == GLFW_KEY_KP_ENTER && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_KP_ENTER && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_KeyPad_Equal:
      if (key == GLFW_KEY_KP_EQUAL && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_KP_EQUAL && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_LeftShift:
      if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_LeftControl:
      if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_LeftAlt:
      if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_LEFT_ALT && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_LeftSuper:
      if (key == GLFW_KEY_LEFT_SUPER && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_LEFT_SUPER && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_RightShift:
      if (key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_RightControl:
      if (key == GLFW_KEY_RIGHT_CONTROL && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_RIGHT_CONTROL && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_RightAlt:
      if (key == GLFW_KEY_RIGHT_ALT && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_RIGHT_ALT && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_RightSuper:
      if (key == GLFW_KEY_RIGHT_SUPER && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_RIGHT_SUPER && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_Menu:
      if (key == GLFW_KEY_MENU && action == GLFW_PRESS) {
        EngineInput::data_->keys[Key] = true;
      }
      else if (key == GLFW_KEY_MENU && action == GLFW_RELEASE) {
        EngineInput::data_->keys[Key] = false;
      }
      break;
    case EngineInput::KeyNames::kKeyNames_MAX:
      break;
    default:
      break;
    }
  }

  static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

    EngineInput::MouseButtons Button = static_cast<EngineInput::MouseButtons>(button);

    switch (Button)
    {
    case EngineInput::MouseButtons::kMouseButtons_Button1:
      if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
        EngineInput::data_->mouse_buttons[Button] = true;
      }
      else {
        EngineInput::data_->mouse_buttons[Button] = false;
      }
      break;
    case EngineInput::MouseButtons::kMouseButtons_Button2:
      if (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS) {
        EngineInput::data_->mouse_buttons[Button] = true;
      }
      else {
        EngineInput::data_->mouse_buttons[Button] = false;
      }
      break;
    case EngineInput::MouseButtons::kMouseButtons_Button3:
      if (button == GLFW_MOUSE_BUTTON_3 && action == GLFW_PRESS) {
        EngineInput::data_->mouse_buttons[Button] = true;
      }
      else {
        EngineInput::data_->mouse_buttons[Button] = false;
      }
      break;
    case EngineInput::MouseButtons::kMouseButtons_Button4:
      if (button == GLFW_MOUSE_BUTTON_4 && action == GLFW_PRESS) {
        EngineInput::data_->mouse_buttons[Button] = true;
      }
      else {
        EngineInput::data_->mouse_buttons[Button] = false;
      }
      break;
    case EngineInput::MouseButtons::kMouseButtons_Button5:
      if (button == GLFW_MOUSE_BUTTON_5 && action == GLFW_PRESS) {
        EngineInput::data_->mouse_buttons[Button] = true;
      }
      else {
        EngineInput::data_->mouse_buttons[Button] = false;
      }
      break;
    case EngineInput::MouseButtons::kMouseButtons_Button6:
      if (button == GLFW_MOUSE_BUTTON_6 && action == GLFW_PRESS) {
        EngineInput::data_->mouse_buttons[Button] = true;
      }
      else {
        EngineInput::data_->mouse_buttons[Button] = false;
      }
      break;
    case EngineInput::MouseButtons::kMouseButtons_Button7:
      if (button == GLFW_MOUSE_BUTTON_7 && action == GLFW_PRESS) {
        EngineInput::data_->mouse_buttons[Button] = true;
      }
      else {
        EngineInput::data_->mouse_buttons[Button] = false;
      }
      break;
    case EngineInput::MouseButtons::kMouseButtons_Button8:
      if (button == GLFW_MOUSE_BUTTON_8 && action == GLFW_PRESS) {
        EngineInput::data_->mouse_buttons[Button] = true;
      }
      else {
        EngineInput::data_->mouse_buttons[Button] = false;
      }
      break;
    default:
      break;
    }
  }

  static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    EngineInput::data_->mouse_x = xpos;
    EngineInput::data_->mouse_y = ypos;
  }

  static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    EngineInput::data_->mouse_wheel_x = xoffset;
    EngineInput::data_->mouse_wheel_y = yoffset;
  }

  static void error_callback(int error, const char* message) {
    LOG_F(INFO, message);
  }
};

EngineInput::EngineInput() {}

EngineInput::~EngineInput() {}

bool EngineInput::IsKeyPressed(EngineInput::KeyNames key) {
  return data_->keys[(int)key];
}

bool EngineInput::IsKeyReleased(EngineInput::KeyNames key) {
  return !data_->keys[(int)key];
}

bool EngineInput::IsMouseButtonPressed(EngineInput::MouseButtons button) {
  return data_->mouse_buttons[(int)button];
}

void EngineInput::GetMousePosition(double& x, double& y) {
  x = data_->mouse_x;
  y = data_->mouse_y;
}

void EngineInput::BindCallbacks(void* window)
{
  GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(window);
  glfwSetKeyCallback(glfwWindow, EngineInputData::key_callback);
  glfwSetMouseButtonCallback(glfwWindow, EngineInputData::mouse_button_callback);
  glfwSetCursorPosCallback(glfwWindow, EngineInputData::cursor_position_callback);
  glfwSetScrollCallback(glfwWindow, EngineInputData::scroll_callback);
  glfwSetErrorCallback(EngineInputData::error_callback);
}
