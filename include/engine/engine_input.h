#ifndef __ENGINE_INPUT_H__
#define __ENGINE_INPUT_H__ 1

#include <memory>

class EngineInput {
public:
  enum KeyNames {
    kKeyNames_Unknown = -1,
    kKeyNames_Space,
    kKeyNames_Apostrophe,
    kKeyNames_Comma,
    kKeyNames_Minus,
    kKeyNames_Period,
    kKeyNames_Slash,
    kKeyNames_Key0,
    kKeyNames_Key1,
    kKeyNames_Key2,
    kKeyNames_Key3,
    kKeyNames_Key4,
    kKeyNames_Key5,
    kKeyNames_Key6,
    kKeyNames_Key7,
    kKeyNames_Key8,
    kKeyNames_Key9,
    kKeyNames_Semicolon,
    kKeyNames_Equal,
    kKeyNames_KeyA,
    kKeyNames_KeyB,
    kKeyNames_KeyC,
    kKeyNames_KeyD,
    kKeyNames_KeyE,
    kKeyNames_KeyF,
    kKeyNames_KeyG,
    kKeyNames_KeyH,
    kKeyNames_KeyI,
    kKeyNames_KeyJ,
    kKeyNames_KeyK,
    kKeyNames_KeyL,
    kKeyNames_KeyM,
    kKeyNames_KeyN,
    kKeyNames_KeyO,
    kKeyNames_KeyP,
    kKeyNames_KeyQ,
    kKeyNames_KeyR,
    kKeyNames_KeyS,
    kKeyNames_KeyT,
    kKeyNames_KeyU,
    kKeyNames_KeyV,
    kKeyNames_KeyW,
    kKeyNames_KeyX,
    kKeyNames_KeyY,
    kKeyNames_KeyZ,
    kKeyNames_LeftBraquets,
    kKeyNames_Backslash,
    kKeyNames_RightBraquets,
    kKeyNames_GraveAccent,
    kKeyNames_World1,
    kKeyNames_World2,
    kKeyNames_Escape,
    kKeyNames_Enter,
    kKeyNames_Tab,
    kKeyNames_BackSpace,
    kKeyNames_Insert,
    kKeyNames_Delete,
    kKeyNames_Right,
    kKeyNames_Left,
    kKeyNames_Down,
    kKeyNames_Up,
    kKeyNames_PageUp,
    kKeyNames_PageDown,
    kKeyNames_Home,
    kKeyNames_End,
    kKeyNames_CapsLock,
    kKeyNames_ScrollLock,
    kKeyNames_NumLock,
    kKeyNames_PrintScreen,
    kKeyNames_Pause,
    kKeyNames_F1,
    kKeyNames_F2,
    kKeyNames_F3,
    kKeyNames_F4,
    kKeyNames_F5,
    kKeyNames_F6,
    kKeyNames_F7,
    kKeyNames_F8,
    kKeyNames_F9,
    kKeyNames_F10,
    kKeyNames_F11,
    kKeyNames_F12,
    kKeyNames_F13,
    kKeyNames_F14,
    kKeyNames_F15,
    kKeyNames_F16,
    kKeyNames_F17,
    kKeyNames_F18,
    kKeyNames_F19,
    kKeyNames_F20,
    kKeyNames_F21,
    kKeyNames_F22,
    kKeyNames_F23,
    kKeyNames_F24,
    kKeyNames_F25,
    kKeyNames_KeyPad_0,
    kKeyNames_KeyPad_1,
    kKeyNames_KeyPad_2,
    kKeyNames_KeyPad_3,
    kKeyNames_KeyPad_4,
    kKeyNames_KeyPad_5,
    kKeyNames_KeyPad_6,
    kKeyNames_KeyPad_7,
    kKeyNames_KeyPad_8,
    kKeyNames_KeyPad_9,
    kKeyNames_KeyPad_Decimal,
    kKeyNames_KeyPad_Divide,
    kKeyNames_KeyPad_Multiply,
    kKeyNames_KeyPad_Subtract,
    kKeyNames_KeyPad_Add,
    kKeyNames_KeyPad_Enter,
    kKeyNames_KeyPad_Equal,
    kKeyNames_LeftShift,
    kKeyNames_LeftControl,
    kKeyNames_LeftAlt,
    kKeyNames_LeftSuper,
    kKeyNames_RightShift,
    kKeyNames_RightControl,
    kKeyNames_RightAlt,
    kKeyNames_RightSuper,
    kKeyNames_Menu,
    kKeyNames_MAX
  };
  enum MouseButtons {
    kMouseButtons_Button1 = 0,
    kMouseButtons_Button2,
    kMouseButtons_Button3,
    kMouseButtons_Button4,
    kMouseButtons_Button5,
    kMouseButtons_Button6,
    kMouseButtons_Button7,
    kMouseButtons_Button8,
    kMouseButtons_MAX,
  };

  EngineInput();
  ~EngineInput();

  static bool IsKeyPressed(EngineInput::KeyNames key);
  static bool IsKeyReleased(EngineInput::KeyNames key);
  static bool IsMouseButtonPressed(EngineInput::MouseButtons button);
  static void GetMousePosition(double& x, double& y);

  void BindCallbacks(void* window);

  struct EngineInputData;
  static std::shared_ptr<EngineInputData> data_;

  static std::unique_ptr<EngineInput> input_;
};



#endif // __ENGINE_INPUT_H__
