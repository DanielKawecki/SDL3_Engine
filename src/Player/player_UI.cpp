#include "player.h"
#include "../Game/game.h"
#include "../UI/ui_backend.h"
#include "../Game/scene.h"
#include <string>

void Player::UpdateUI() {

	if (Game::IsDebugVisible()) {
		WeaponInfo* info = _equipedWeapon->GetWeaponInfo();
		std::string text = "";
		text += "Equiped Weapon: " + info->name + "\n";
		text += "Reload Time: " + std::to_string(info->reloadTime) + "\n";
		UIBackEnd::BlitText(text, 10.f, 10.f);

		Scene::DisplayDebug();
	}
}