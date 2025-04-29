#pragma once
#include "Pch.h"
#include "PlayerConfig.h"
#include "Overlay.h"
#include "AimbotConfig.h"
class ConfigInstances
{
public:
	PlayerConfig Player = PlayerConfig(LIT("Player"));
	AimbotConfig Aimbot = AimbotConfig(LIT("Aimbot"));
	OverlayConfig Overlay = OverlayConfig(LIT("Overlay"));
	json ToJson()
	{
		json jsoned;
		jsoned.merge_patch(Player.ToJson());
		jsoned.merge_patch(Overlay.ToJson());
		jsoned.merge_patch(Overlay.ToJson());
		return jsoned;
	}

	void FromJson(json jsoned)
	{
		Player.FromJson(jsoned);
		Overlay.FromJson(jsoned);
		Overlay.FromJson(jsoned);
	}
};