//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//This header contains the window class that genereate the main window.
#ifndef __WINDOW_H__
#define __WINDOW_H__ 1

#include <memory>
#include <string>

namespace OpenGLEngine {


	struct WData;

	class Window {

	public:
		Window();
		Window(std::string name, int width, int height);
		~Window();

		void SetWindowData(std::string name, int width, int height);
		bool InitWindow();
		void* GetWindow() const;
		void SwapBuffers();
		bool CloseWindow();
    int GetWidth() const;
    int GetHeight() const;
    unsigned int GetFBO() const;
    void Update();

    void FullScreen();




	private:
		void CreateFrameBuffer();
		std::unique_ptr<WData> wdata_;

	};
}




#endif // !__WINDOW_H__
