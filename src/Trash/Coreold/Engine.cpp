#include "Engine.h"

#include <iostream>

Engine::Engine() : _isRunning(false) {

	_backend = std::make_unique<BackEnd>();
}

Engine::~Engine() {
	Shutdown();
}

void Engine::Run() {

	Initialize();

	while (_isRunning) {

		HandleInput();

		Update();

		Render();
	}

	Shutdown();
}

void Engine::Initialize() {

	std::cout << "Initializing Engine...\n";

	_backend->Initialize();

	_isRunning = true;
}

void Engine::HandleInput()
{
}

void Engine::Update()
{
}

void Engine::Render()
{
}

void Engine::Shutdown() {

	std::cout << "Shutting down engine...\n";
	_isRunning = false;
}
