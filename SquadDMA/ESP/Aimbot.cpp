#include "Pch.h"
#include "Globals.h"
#include "Camera.h"
#include "ActorEntity.h"
#include "Engine.h"
#include "Aimbot.h"
#include "ConfigUtilities.h"
#include "EngineStructs.h"
#include "Drawing.h"

std::shared_ptr<ActorEntity> AimbotTarget;
uint64_t Rotation = 0x65424C;
uint64_t LocalPlayerP_offset = 0x8914D8;
 
float AngleNormalize(float angle)
{
    while (angle < -180.0f)
        angle += 360.0f;
 
    while (angle > 180.0f)
        angle -= 360.0f;
 
    return angle;
}
 
void AnglesNormalize(Vector3& angles)
{
    angles.x = AngleNormalize(angles.x);
    angles.y = AngleNormalize(angles.y);
    angles.z = 0;
}
 
void SetRotation(Vector3 vec)
{
	try
	{
		TargetProcess.Write<Vector2>(engine_dll + Rotation, Vector2(vec.x, vec.y));
	}
	catch (std::exception ex)
	{
		std::cout << "ERROR While writing angle rotation\n";
	}
}
 
void GetBestTarget()
{
	if (!EngineInstance)
		return;
 
	std::shared_ptr<ActorEntity> temp_t;
	ViewMatrixStruct matrix = EngineInstance->GetViewMatrix();
	float temp_d = -1;
 
	for (auto entity : EngineInstance->GetActors())
	{
		if (entity->GetPosition() == Vector3(0, 0, 0))
			continue;
 
		Vector3 Head3D = Vector3(entity->GetBones().Head1._4, entity->GetBones().Head1._8, entity->GetBones().Head1._12);
		if (Head3D.IsZero())
			continue;
 
		Vector2 Head = Camera::WorldToScreen(matrix, Head3D);
 
		Vector2 screenpos = Camera::WorldToScreen(matrix, entity->GetPosition());
		if (screenpos == Vector2::Zero() or Head.IsZero())
			continue;
 
		if (entity->GetHealth() <= 0)
			continue;
 
		Vector2 cos = Vector2(Configs.Overlay.OverrideResolution ? Configs.Overlay.Width / 2 : GetSystemMetrics(SM_CXSCREEN) / 2, Configs.Overlay.OverrideResolution ? Configs.Overlay.Height / 2 : GetSystemMetrics(SM_CYSCREEN) / 2);
 
		float delta = Vector2::Distance(Head, cos);
 
		if (delta > Configs.Aimbot.Fov)
			continue;
 
		if (temp_d == -1 or (delta < temp_d)) {
			temp_t = entity;
			temp_d = delta;
			continue;
		}
	}
 
	AimbotTarget = temp_t;
}
 
void Aimbot()
{
	if (Configs.Aimbot.Enable == false)
		return;

	if (!Keyboard::IsKeyDown(Configs.Aimbot.Key))
		return;
 
	if (!EngineInstance)
		return;
 
	if (EngineInstance->LocalPlayer == 0)
		return;
 
	GetBestTarget();
 
	if (!AimbotTarget)
		return;

	ViewMatrixStruct matrix = EngineInstance->GetViewMatrix();

	Vector3 Head3D = Vector3(AimbotTarget->GetBones().Head1._4, AimbotTarget->GetBones().Head1._8, AimbotTarget->GetBones().Head1._12);
	Vector3 campos = TargetProcess.Read<Vector3>(engine_dll + LocalPlayerP_offset);
	std::cout << campos.x << "/" << campos.y << "\n";
	auto direction = Head3D - campos;
	auto angles = direction;
	Vector3 ang = Vector3::ToAngles(direction);
	AnglesNormalize(ang);
 
	//std::cout << ang.x << "/" << ang.y << "\n";
 
	SetRotation(ang);
}
 
std::shared_ptr<CheatFunction> ApplyAimbot = std::make_shared<CheatFunction>(10, [] {
	Aimbot();
});
 
void DrawFov()
{
	Vector2 cos = Vector2(Configs.Overlay.OverrideResolution ? Configs.Overlay.Width / 2 : GetSystemMetrics(SM_CXSCREEN) / 2, Configs.Overlay.OverrideResolution ? Configs.Overlay.Height / 2 : GetSystemMetrics(SM_CYSCREEN) / 2);
	if (Configs.Aimbot.DrawFov)
		OutlineCircle(cos.x, cos.y, Configs.Aimbot.Fov, 2, Colour(255,255,255));
}