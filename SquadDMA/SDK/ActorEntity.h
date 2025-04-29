#pragma once
#include "EngineStructs.h"
class ActorEntity
{
private:
	uint64_t Class = 0;
	uint64_t m_vecOrigin = 0x308;
	uint64_t m_iHealth = 0xC8;
	uint64_t m_iTeamNum = 0xD4;
	uint64_t m_fFlags = 0x440;
	uint64_t m_DormantOffset = 0xB4;
	uint64_t m_BoneMatrix = 0x1A98;
	uint64_t PlayerName = 0x3744;
	uint64_t m_MaxHealth = 0xCC;

	int Health = 0;
	int MaxHealth = 0;
	std::wstring Name = LIT(L"Enemy");
	UEVector UEPosition;
	Vector3 Position;
	bone_struct bonelist;
public:

	ActorEntity(uint64_t address, VMMDLL_SCATTER_HANDLE handle);
	uint64_t GetClass();
	std::wstring GetName();
	Vector3 GetPosition();
	void UpdatePosition(VMMDLL_SCATTER_HANDLE handle);
	void UpdateHealth(VMMDLL_SCATTER_HANDLE handle);
	void UpdateBones(VMMDLL_SCATTER_HANDLE handle);
	bone_struct GetBones();
	float GetHealth();
	float GetMaxHealth();
	int m_Dormant;
};