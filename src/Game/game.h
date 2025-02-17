#pragma once

//#include "player.h"

namespace Game {

	void Create();
	//void create_players(int count);
	//player* get_player_by_id(int id);
	void Update();
	void UpdateEvents();
	void UpdateDeltaTime();
	void DisplayDebugText();
	void DisplayDebugLines();
	void DisplayConsole();
	void UpdateConsole();
	bool IsLoaded();
}