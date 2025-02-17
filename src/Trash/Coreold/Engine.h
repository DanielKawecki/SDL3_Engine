
#include "BackEnd.h"
//#include "Input.h"
//#include "../Renderer/Renderer.h"

#include <memory>

#ifndef ENGINE_H
#define ENGINE_H

class Engine {

private:
	bool _isRunning;

	std::unique_ptr<BackEnd>	_backend;
	//std::unique_ptr<Renderer>	_renderer;
	//std::unique_ptr<Input>		_input;

public:
	Engine();
	~Engine();

	void Run();
	void Initialize();
	void HandleInput();
	void Update();
	void Render();
	void Shutdown();
};

#endif // !ENGINE_H

