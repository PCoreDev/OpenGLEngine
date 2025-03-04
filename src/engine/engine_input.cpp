#include "engine/engine_input.h"
#include "GLFW/glfw3.h"
#include <map>


#include "loguru/loguru.hpp"

std::shared_ptr<EngineInput::EngineInputData> EngineInput::data_ = std::make_shared<EngineInput::EngineInputData>();

struct EngineInput::EngineInputData {
  std::map<int, EngineInput::KeyNames> keyMap = {
    {GLFW_KEY_UNKNOWN, EngineInput::KeyNames::kKeyNames_Unknown},
    {GLFW_KEY_SPACE, EngineInput::KeyNames::kKeyNames_Space},
    {GLFW_KEY_APOSTROPHE, EngineInput::KeyNames::kKeyNames_Apostrophe},
    {GLFW_KEY_COMMA, EngineInput::KeyNames::kKeyNames_Comma},
    {GLFW_KEY_MINUS, EngineInput::KeyNames::kKeyNames_Minus},
    {GLFW_KEY_PERIOD, EngineInput::KeyNames::kKeyNames_Period},
    {GLFW_KEY_SLASH, EngineInput::KeyNames::kKeyNames_Slash},
    {GLFW_KEY_0, EngineInput::KeyNames::kKeyNames_Key0},
    {GLFW_KEY_1, EngineInput::KeyNames::kKeyNames_Key1},
    {GLFW_KEY_2, EngineInput::KeyNames::kKeyNames_Key2},
    {GLFW_KEY_3, EngineInput::KeyNames::kKeyNames_Key3},
    {GLFW_KEY_4, EngineInput::KeyNames::kKeyNames_Key4},
    {GLFW_KEY_5, EngineInput::KeyNames::kKeyNames_Key5},
    {GLFW_KEY_6, EngineInput::KeyNames::kKeyNames_Key6},
    {GLFW_KEY_7, EngineInput::KeyNames::kKeyNames_Key7},
    {GLFW_KEY_8, EngineInput::KeyNames::kKeyNames_Key8},
    {GLFW_KEY_9, EngineInput::KeyNames::kKeyNames_Key9},
    {GLFW_KEY_SEMICOLON, EngineInput::KeyNames::kKeyNames_Semicolon},
    {GLFW_KEY_EQUAL, EngineInput::KeyNames::kKeyNames_Equal},
    {GLFW_KEY_A, EngineInput::KeyNames::kKeyNames_KeyA},
    {GLFW_KEY_B, EngineInput::KeyNames::kKeyNames_KeyB},
    {GLFW_KEY_C, EngineInput::KeyNames::kKeyNames_KeyC},
    {GLFW_KEY_D, EngineInput::KeyNames::kKeyNames_KeyD},
    {GLFW_KEY_E, EngineInput::KeyNames::kKeyNames_KeyE},
    {GLFW_KEY_F, EngineInput::KeyNames::kKeyNames_KeyF},
    {GLFW_KEY_G, EngineInput::KeyNames::kKeyNames_KeyG},
    {GLFW_KEY_H, EngineInput::KeyNames::kKeyNames_KeyH},
    {GLFW_KEY_I, EngineInput::KeyNames::kKeyNames_KeyI},
    {GLFW_KEY_J, EngineInput::KeyNames::kKeyNames_KeyJ},
    {GLFW_KEY_K, EngineInput::KeyNames::kKeyNames_KeyK},
    {GLFW_KEY_L, EngineInput::KeyNames::kKeyNames_KeyL},
    {GLFW_KEY_M, EngineInput::KeyNames::kKeyNames_KeyM},
    {GLFW_KEY_N, EngineInput::KeyNames::kKeyNames_KeyN},
    {GLFW_KEY_O, EngineInput::KeyNames::kKeyNames_KeyO},
    {GLFW_KEY_P, EngineInput::KeyNames::kKeyNames_KeyP},
    {GLFW_KEY_Q, EngineInput::KeyNames::kKeyNames_KeyQ},
    {GLFW_KEY_R, EngineInput::KeyNames::kKeyNames_KeyR},
    {GLFW_KEY_S, EngineInput::KeyNames::kKeyNames_KeyS},
    {GLFW_KEY_T, EngineInput::KeyNames::kKeyNames_KeyT},
    {GLFW_KEY_U, EngineInput::KeyNames::kKeyNames_KeyU},
    {GLFW_KEY_V, EngineInput::KeyNames::kKeyNames_KeyV},
    {GLFW_KEY_W, EngineInput::KeyNames::kKeyNames_KeyW},
    {GLFW_KEY_X, EngineInput::KeyNames::kKeyNames_KeyX},
    {GLFW_KEY_Y, EngineInput::KeyNames::kKeyNames_KeyY},
    {GLFW_KEY_Z, EngineInput::KeyNames::kKeyNames_KeyZ},
    {GLFW_KEY_LEFT_BRACKET, EngineInput::KeyNames::kKeyNames_LeftBraquets},
    {GLFW_KEY_BACKSLASH, EngineInput::KeyNames::kKeyNames_Backslash},
    {GLFW_KEY_RIGHT_BRACKET, EngineInput::KeyNames::kKeyNames_RightBraquets},
    {GLFW_KEY_GRAVE_ACCENT, EngineInput::KeyNames::kKeyNames_GraveAccent},
    {GLFW_KEY_WORLD_1, EngineInput::KeyNames::kKeyNames_World1},
    {GLFW_KEY_WORLD_2, EngineInput::KeyNames::kKeyNames_World2},
    {GLFW_KEY_ESCAPE, EngineInput::KeyNames::kKeyNames_Escape},
    {GLFW_KEY_ENTER, EngineInput::KeyNames::kKeyNames_Enter},
    {GLFW_KEY_TAB, EngineInput::KeyNames::kKeyNames_Tab},
    {GLFW_KEY_BACKSPACE, EngineInput::KeyNames::kKeyNames_BackSpace},
    {GLFW_KEY_INSERT, EngineInput::KeyNames::kKeyNames_Insert},
    {GLFW_KEY_DELETE, EngineInput::KeyNames::kKeyNames_Delete},
    {GLFW_KEY_RIGHT, EngineInput::KeyNames::kKeyNames_Right},
    {GLFW_KEY_LEFT, EngineInput::KeyNames::kKeyNames_Left},
    {GLFW_KEY_DOWN, EngineInput::KeyNames::kKeyNames_Down},
    {GLFW_KEY_UP, EngineInput::KeyNames::kKeyNames_Up},
    {GLFW_KEY_PAGE_UP, EngineInput::KeyNames::kKeyNames_PageUp},
    {GLFW_KEY_PAGE_DOWN, EngineInput::KeyNames::kKeyNames_PageDown},
    {GLFW_KEY_HOME, EngineInput::KeyNames::kKeyNames_Home},
    {GLFW_KEY_END, EngineInput::KeyNames::kKeyNames_End},
    {GLFW_KEY_CAPS_LOCK, EngineInput::KeyNames::kKeyNames_CapsLock},
    {GLFW_KEY_SCROLL_LOCK, EngineInput::KeyNames::kKeyNames_ScrollLock},
    {GLFW_KEY_NUM_LOCK, EngineInput::KeyNames::kKeyNames_NumLock},
    {GLFW_KEY_PRINT_SCREEN, EngineInput::KeyNames::kKeyNames_PrintScreen},
    {GLFW_KEY_PAUSE, EngineInput::KeyNames::kKeyNames_Pause},
    {GLFW_KEY_F1, EngineInput::KeyNames::kKeyNames_F1},
    {GLFW_KEY_F2, EngineInput::KeyNames::kKeyNames_F2},
    {GLFW_KEY_F3, EngineInput::KeyNames::kKeyNames_F3},
    {GLFW_KEY_F4, EngineInput::KeyNames::kKeyNames_F4},
    {GLFW_KEY_F5, EngineInput::KeyNames::kKeyNames_F5},
    {GLFW_KEY_F6, EngineInput::KeyNames::kKeyNames_F6},
    {GLFW_KEY_F7, EngineInput::KeyNames::kKeyNames_F7},
    {GLFW_KEY_F8, EngineInput::KeyNames::kKeyNames_F8},
    {GLFW_KEY_F9, EngineInput::KeyNames::kKeyNames_F9},
    {GLFW_KEY_F10, EngineInput::KeyNames::kKeyNames_F10},
    {GLFW_KEY_F11, EngineInput::KeyNames::kKeyNames_F11},
    {GLFW_KEY_F12, EngineInput::KeyNames::kKeyNames_F12},
    {GLFW_KEY_F13, EngineInput::KeyNames::kKeyNames_F13},
    {GLFW_KEY_F14, EngineInput::KeyNames::kKeyNames_F14},
    {GLFW_KEY_F15, EngineInput::KeyNames::kKeyNames_F15},
    {GLFW_KEY_F16, EngineInput::KeyNames::kKeyNames_F16},
    {GLFW_KEY_F17, EngineInput::KeyNames::kKeyNames_F17},
    {GLFW_KEY_F18, EngineInput::KeyNames::kKeyNames_F18},
    {GLFW_KEY_F19, EngineInput::KeyNames::kKeyNames_F19},
    {GLFW_KEY_F20, EngineInput::KeyNames::kKeyNames_F20},
    {GLFW_KEY_F21, EngineInput::KeyNames::kKeyNames_F21},
    {GLFW_KEY_F22, EngineInput::KeyNames::kKeyNames_F22},
    {GLFW_KEY_F23, EngineInput::KeyNames::kKeyNames_F23},
    {GLFW_KEY_F24, EngineInput::KeyNames::kKeyNames_F24},
    {GLFW_KEY_F25, EngineInput::KeyNames::kKeyNames_F25},
    {GLFW_KEY_KP_0, EngineInput::KeyNames::kKeyNames_KeyPad_0},
    {GLFW_KEY_KP_1, EngineInput::KeyNames::kKeyNames_KeyPad_1},
    {GLFW_KEY_KP_2, EngineInput::KeyNames::kKeyNames_KeyPad_2},
    {GLFW_KEY_KP_3, EngineInput::KeyNames::kKeyNames_KeyPad_3},
    {GLFW_KEY_KP_4, EngineInput::KeyNames::kKeyNames_KeyPad_4},
    {GLFW_KEY_KP_5, EngineInput::KeyNames::kKeyNames_KeyPad_5},
    {GLFW_KEY_KP_6, EngineInput::KeyNames::kKeyNames_KeyPad_6},
    {GLFW_KEY_KP_7, EngineInput::KeyNames::kKeyNames_KeyPad_7},
    {GLFW_KEY_KP_8, EngineInput::KeyNames::kKeyNames_KeyPad_8},
    {GLFW_KEY_KP_9, EngineInput::KeyNames::kKeyNames_KeyPad_9},
    {GLFW_KEY_KP_DECIMAL, EngineInput::KeyNames::kKeyNames_KeyPad_Decimal},
    {GLFW_KEY_KP_DIVIDE, EngineInput::KeyNames::kKeyNames_KeyPad_Divide},
    {GLFW_KEY_KP_MULTIPLY, EngineInput::KeyNames::kKeyNames_KeyPad_Multiply},
    {GLFW_KEY_KP_SUBTRACT, EngineInput::KeyNames::kKeyNames_KeyPad_Subtract},
    {GLFW_KEY_KP_ADD, EngineInput::KeyNames::kKeyNames_KeyPad_Add},
    {GLFW_KEY_KP_ENTER, EngineInput::KeyNames::kKeyNames_KeyPad_Enter},
    {GLFW_KEY_KP_EQUAL, EngineInput::KeyNames::kKeyNames_KeyPad_Equal},
    {GLFW_KEY_LEFT_SHIFT, EngineInput::KeyNames::kKeyNames_LeftShift},
    {GLFW_KEY_LEFT_CONTROL, EngineInput::KeyNames::kKeyNames_LeftControl},
    {GLFW_KEY_LEFT_ALT, EngineInput::KeyNames::kKeyNames_LeftAlt},
    {GLFW_KEY_LEFT_SUPER, EngineInput::KeyNames::kKeyNames_LeftSuper},
    {GLFW_KEY_RIGHT_SHIFT, EngineInput::KeyNames::kKeyNames_RightShift},
    {GLFW_KEY_RIGHT_CONTROL, EngineInput::KeyNames::kKeyNames_RightControl},
    {GLFW_KEY_RIGHT_ALT, EngineInput::KeyNames::kKeyNames_RightAlt},
    {GLFW_KEY_RIGHT_SUPER, EngineInput::KeyNames::kKeyNames_RightSuper},
    {GLFW_KEY_MENU, EngineInput::KeyNames::kKeyNames_Menu}
  };
  std::map<int, EngineInput::MouseButtons> MouseKeyMap = {
    {GLFW_MOUSE_BUTTON_1, EngineInput::MouseButtons::kMouseButtons_Button1},
    {GLFW_MOUSE_BUTTON_2, EngineInput::MouseButtons::kMouseButtons_Button2},
    {GLFW_MOUSE_BUTTON_3, EngineInput::MouseButtons::kMouseButtons_Button3},
    {GLFW_MOUSE_BUTTON_4, EngineInput::MouseButtons::kMouseButtons_Button4},
    {GLFW_MOUSE_BUTTON_5, EngineInput::MouseButtons::kMouseButtons_Button5},
    {GLFW_MOUSE_BUTTON_6, EngineInput::MouseButtons::kMouseButtons_Button6},
    {GLFW_MOUSE_BUTTON_7, EngineInput::MouseButtons::kMouseButtons_Button7},
    {GLFW_MOUSE_BUTTON_8, EngineInput::MouseButtons::kMouseButtons_Button8}
  };

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
    auto it = data_->keyMap.find(key);
    if (it != data_->keyMap.end()) {
      int glfwKey = it->second;
      if (action == GLFW_PRESS) {
        EngineInput::data_->keys[glfwKey] = true;
      }
      else if (action == GLFW_RELEASE) {
        EngineInput::data_->keys[glfwKey] = false;
      }
    }
  }

  static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    auto it = data_->MouseKeyMap.find(button);
    if (it != data_->MouseKeyMap.end()) {
      int glfwButton = it->second;
      if (action == GLFW_PRESS) {
        EngineInput::data_->mouse_buttons[glfwButton] = true;
      }
      else if (action == GLFW_RELEASE) {
        EngineInput::data_->mouse_buttons[glfwButton] = false;
      }
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