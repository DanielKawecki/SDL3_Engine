
#ifndef	BACKEND_H
#define	BACKEND_H

#include <SDL3/SDL.h>

class BackEnd {

private:
	SDL_Window* _window;

	int _screenWidth;
	int _screenHeight;

public:

	BackEnd();
	~BackEnd();

	void Initialize();
	void CreateWindow();
	bool IsWindowOpen() const;
	void ForceCloseWindow();
	SDL_Window* GetWindowPointer() const;
	void CleanUp();
	int GetScreenWidth() const;
	int GetScreenHeight() const;
};

#endif // !BACKEND_H
