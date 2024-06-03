//Author: Pablo "Pau" Core Palmero
//Date: 28-May-2024
//Email: p.core.dev@outlook.com
//This header contains the window class that genereate the main window.
#ifndef __WINDOW_H__
#define __WINDOW_H__ 1

#include <memory>

namespace OpenGLEngine {

	struct WData;

	class Window {

	public:
		Window();
		~Window();

		int InitWindow(const char* title, int width, int height, bool fullscreen = false);
		void* GetWindow() const;

	private:

		std::unique_ptr<WData> wdata_;

	};
}




#endif // !__WINDOW_H__
