#pragma once
#include "ActorEntity.h"
#include "EngineStructs.h"

class Engine
{
private:
	uint64_t LocalPlayerOffset = 0x942250;
	uint64_t EntityList = 0x964428;

	//uint64_t ViewMatrixOffset = 0x4A3AD8;
	uint64_t ViewMatrixOffset = 0x7bf668;
	uint64_t ViewMatrixOffset2 = 0x2D4;

	uint64_t m_vecOrigin = 0x308;
	uint64_t m_iHealth = 0xC8;
	uint64_t m_iTeamNum = 0xD4;
	uint64_t m_fFlags = 0x440;
	uint64_t m_DormantOffset = 0xB4;
	uint64_t PlayerName = 0x3744;
	uint64_t LocalPlayerPosOffset = 0x892558;

	int SlotNum;

	std::vector<std::shared_ptr<ActorEntity>> Actors;

	uint64_t ViewMatrixBase;
	ViewMatrixStruct ViewMatrix;
public:
	Engine();
	void Cache();
	void UpdatePlayers();
	std::vector<std::shared_ptr<ActorEntity>> GetActors();
	ViewMatrixStruct GetViewMatrix();
	void RefreshViewMatrix(VMMDLL_SCATTER_HANDLE handle);
	void UpdateLocalPlayerPos(VMMDLL_SCATTER_HANDLE handle);
	void UpdatePunchAngle(VMMDLL_SCATTER_HANDLE handle);
	int GetActorSize();
	Vector3 GetHand();
	void SetAngle(Vector3 vec);
	Vector3 GetHandAngle();
	uint64_t LocalPlayer;
	Vector3 LocalPlayerPos;
	Vector3 PunchAngle;
	std::mutex ActorMutex;
};