#include "Pch.h"
#include "Drawing.h"
#include "Globals.h"
#include "Camera.h"
#include "ActorEntity.h"
#include "Engine.h"
#include "PlayerEsp.h"
#include "ConfigUtilities.h"

std::shared_ptr<CheatFunction> UpdatePlayers = std::make_shared<CheatFunction>(10, [] {
	if (!EngineInstance)
		return;
	EngineInstance->UpdatePlayers();
});

void DrawPlayerEsp()
{

	if (!EngineInstance)
		return;
	for (auto entity : EngineInstance->GetActors())
	{
		if (entity->GetPosition() == Vector3(0, 0, 0))
			continue;

		ViewMatrixStruct matrix = EngineInstance->GetViewMatrix();

		Vector2 screenpos = Camera::WorldToScreen(matrix, entity->GetPosition());
		if (screenpos == Vector2::Zero())
			continue;
		int health_int = entity->GetHealth();
		if (health_int <= 0)
			continue;

		if (entity->m_Dormant != -65536) 
		{
			bone_struct pbones = entity->GetBones();

			std::map<int, Vector2> bone_c;
			m3x4 bone_t[] = {pbones.Head1, pbones.Spine4, pbones.L_UpperArm, pbones.R_UpperArm, pbones.Pelvis, pbones.L_Calf, pbones.R_Calf, pbones.L_Foot, pbones.R_Foot, pbones.L_Forearm, pbones.R_Forearm, pbones.L_Hand, pbones.R_Hand };

			int index = 0;
			for (m3x4 i : bone_t)
			{
				bone_c[index] = Camera::WorldToScreen(matrix, Vector3(i._4, i._8, i._12));
				++index;
			}

			std::map<int, int> connect = {
				{0, 1},
				{2, 1},
				{3, 1},
				{4, 1},
				{5, 4},
				{6, 4},
				{5, 4},
				{6, 4},
				{7, 5},
				{8, 6},
				{9, 2},
				{10, 3},
				{11, 9},
				{12, 10}
			};

			int diff = screenpos.y - bone_c[0].y + 12;
			for (int ind = 0; ind < 13; ++ind)
			{
				Vector2 bone = bone_c[ind];
				Vector2 bone_p = bone_c[connect[ind]];
				if (Vector2::Distance(bone, bone_p) > diff)
					continue;

				if (bone.IsZero() or bone_p.IsZero())
					continue;

				FilledLineAliased(bone.x, bone.y, bone_p.x, bone_p.y, 1, Configs.Player.TextColour);
			}

			/*if (Keyboard::IsKeyDown(0x46))
			{
				//std::cout << hand.x << "/" << hand.y << "\n";
				//std::cout << ang.x << "//" << ang.y << "\n";

				//Vector2 view_ang = TargetProcess.Read<Vector2>(EngineInstance->LocalPlayer + 0x5CCEDC);
				//Vector3 head = Vector3(pbones.Spine4._4, pbones.Spine4._8, pbones.Spine4._12);
				Vector3 cam_pos = TargetProcess.Read<Vector3>(EngineInstance->LocalPlayer + 0x308);

				auto direction = entity->GetPosition() - cam_pos;


				auto angles = direction;
				Vector3 ang = Vector3::ToAngles(direction);
				AnglesNormalize(ang);
				ang.y = ang.y;
				//AnglesNormalize(angles);
				//angles.z = 0.0f;
				//angles.y = angles.y + 65;

				std::cout << ang.x << "/" << ang.y << "\n";
				EngineInstance->SetAngle(ang);
			}*/
		}

		//Vector3 campos = Vector3(matrix._4, matrix._8, matrix._12);
		//float distance = (Vector3::Distance(campos, entity->GetPosition()));

		//if (distance < 0)
		//	continue;

		//std::wstring wdistance = Configs.Player.Distance ? L"[" + std::to_wstring((int)distance) + L"m]" : L"";
		std::wstring whealth = Configs.Player.Health ? L" [" + std::to_wstring((int)entity->GetHealth()) + L"]" : L"";
		//std::wstring wstamina = Configs.Player.Health ? L"[" + std::to_wstring((int)entity->GetStamina()) + L"]" : L"";
		std::wstring name = Configs.Player.Name ? entity->GetName() : L"";
		//if (distance > Configs.Player.MaxDistance)
		//	continue;
		int y_off = 14;

		//DrawText(screenpos.x, screenpos.y, name + wdistance, LIT("Verdana"), Configs.Player.FontSize, Configs.Player.TextColour, CentreCentre);
		DrawText(screenpos.x, screenpos.y + 4, name + whealth, LIT("Verdana"), Configs.Player.FontSize, Colour(255 - (health_int*2.55), health_int*2.55, 0, 255), CentreCentre);

		//DrawText(screenpos.x, screenpos.y+y_off, wstamina, LIT("Verdana"), Configs.Player.FontSize, Configs.Player.TextColour, CentreCentre);
	}
	
}