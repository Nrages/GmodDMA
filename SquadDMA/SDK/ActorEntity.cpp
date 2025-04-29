#include "Pch.h"
#include "ActorEntity.h"
#include "Camera.h"
#include "Globals.h"
#include <cmath>

std::wstring GetString(uint64_t add) {
	wchar_t buffer[512];
	auto result = TargetProcess.Read(add, &buffer, 512);
	//std::string str(buffer, 128);
	//if (str == "")
	//	return;
	return std::wstring(buffer);
}

ActorEntity::ActorEntity(uint64_t address,VMMDLL_SCATTER_HANDLE handle)
{
	Class = address;
	if(!address)
		return;

	//Name = GetString(address + PlayerName);
	TargetProcess.AddScatterReadRequest(handle, Class + m_vecOrigin,reinterpret_cast<void*>(&UEPosition), sizeof(UEVector));
	TargetProcess.AddScatterReadRequest(handle, Class + m_iHealth,reinterpret_cast<void*>(&Health), sizeof(int));
	TargetProcess.AddScatterReadRequest(handle, Class + m_MaxHealth,reinterpret_cast<void*>(&MaxHealth), sizeof(int));
	TargetProcess.AddScatterReadRequest(handle, Class + m_BoneMatrix,reinterpret_cast<void*>(&m_BoneMatrix), sizeof(uint64_t));
}

std::wstring ActorEntity::GetName()
{
	return Name;
}

Vector3 ActorEntity::GetPosition()
{
	Position = Vector3(UEPosition.x, UEPosition.y, UEPosition.z);
	return Position;
}

void ActorEntity::UpdatePosition(VMMDLL_SCATTER_HANDLE handle)
{
	if (!Class)
		return;

	TargetProcess.AddScatterReadRequest(handle, Class + m_vecOrigin, reinterpret_cast<void*>(&UEPosition), sizeof(UEVector));
	TargetProcess.AddScatterReadRequest(handle, Class + m_DormantOffset, reinterpret_cast<void*>(&m_Dormant), sizeof(int));
}

void ActorEntity::UpdateBones(VMMDLL_SCATTER_HANDLE handle)
{
	if (!Class)
		return;

	TargetProcess.AddScatterReadRequest(handle, m_BoneMatrix,reinterpret_cast<void*>(&bonelist), sizeof(bone_struct));
}

void ActorEntity::UpdateHealth(VMMDLL_SCATTER_HANDLE handle)
{
	if (!Class)
		return;
	
	TargetProcess.AddScatterReadRequest(handle, Class + m_iHealth,reinterpret_cast<void*>(&Health), sizeof(int));
}

uint64_t ActorEntity::GetClass()
{
	return Class;
}

float ActorEntity::GetHealth()
{
	return Health;
}

float ActorEntity::GetMaxHealth()
{
	return MaxHealth;
}

bone_struct ActorEntity::GetBones()
{
	return bonelist;
}