#pragma once

struct SDL_FRect;

namespace Game {

	void Create();
	void Update();
	void UpdateViewport();
	void UpdateEvents();
	void UpdateDeltaTime();
	void DisplayDebugText();
	bool IsLoaded();
	bool IsDebugVisible();
	bool IsEditorOpen();
	SDL_FRect GetViewport();
}