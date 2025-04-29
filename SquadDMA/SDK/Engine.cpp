#include "Pch.h"
#include "Engine.h"
#include "ActorEntity.h"
#include "Globals.h"
#include "EngineStructs.h"

Engine::Engine()
{
	std::cout << "==============================" << '\n';
	printf(LIT("Client.dll: %p\n"), client_dll);
	printf(LIT("Engine.dll: %p\n"), engine_dll);
	LocalPlayer = TargetProcess.Read<uint64_t>(client_dll + LocalPlayerOffset);
	printf(LIT("LocalPlayer: %p\n"), LocalPlayer);
	//SlotNum = TargetProcess.Read<int>(engine_dll + SlotNumOffset);
	SlotNum = 128;
	printf(LIT("SlotNum: %d\n"), SlotNum);
	ViewMatrixBase = TargetProcess.Read<uint64_t>(engine_dll + ViewMatrixOffset) + ViewMatrixOffset2;
	printf(LIT("ViewMatrixBase: %p\n"), ViewMatrixBase);
	std::cout << "==============================" << '\n';
}

void Engine::Cache()
{
	LocalPlayer = TargetProcess.Read<uint64_t>(client_dll + LocalPlayerOffset);
	if (LocalPlayer == 0)
		return;

	std::vector<uint64_t> entitylist;
	for (int i = 0; i < SlotNum; i++)
	{
		uint64_t temp = TargetProcess.Read<uint64_t>(client_dll + EntityList + i * 0x20);
		//std::cout << temp << "\n";
		entitylist.push_back(temp);
	}

	std::cout << "EntityList Size: " << entitylist.size() << "\n";
	std::list<std::shared_ptr<ActorEntity>> actors;
	auto handle = TargetProcess.CreateScatterHandle();
	for (uint64_t address : entitylist)
	{
		uintptr_t actor = address;
		if (!actor)
			continue;
		
			std::shared_ptr<ActorEntity> entity = std::make_shared<ActorEntity>(actor, handle);
			actors.push_back(entity);
		
	}

	std::cout << "Pre-Actors Size: " << actors.size() << "\n";

	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);
	
	std::vector<std::shared_ptr<ActorEntity>> playerlist;
	for (std::shared_ptr<ActorEntity> entity : actors)
	{
		if(entity->GetHealth() < 1 or entity->GetMaxHealth() != 100)
			continue;

		Vector3 pos = entity->GetPosition();
		
		if (pos == Vector3::Zero())
			continue;

		playerlist.push_back(entity);
	}
	std::cout << "Valid Actors Size: " << playerlist.size() << "\n";
	ActorMutex.lock();
	Actors = playerlist;
	ActorMutex.unlock();
}
void Engine::UpdatePlayers()
{

	auto handle = TargetProcess.CreateScatterHandle();
	std::vector<std::shared_ptr<ActorEntity>> tempactors;
	ActorMutex.lock();
	tempactors = Actors;
	ActorMutex.unlock();

	for (std::shared_ptr<ActorEntity> entity : tempactors)
	{
		entity->UpdatePosition(handle);
		entity->UpdateBones(handle);
		entity->UpdateHealth(handle);
	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);
	ActorMutex.lock();
	Actors = tempactors;
	ActorMutex.unlock();
}

void Engine::RefreshViewMatrix(VMMDLL_SCATTER_HANDLE handle)
{
	TargetProcess.AddScatterReadRequest(handle, ViewMatrixBase, reinterpret_cast<void*>(&ViewMatrix),sizeof(ViewMatrixStruct));
}

void Engine::UpdateLocalPlayerPos(VMMDLL_SCATTER_HANDLE handle)
{
	TargetProcess.AddScatterReadRequest(handle, LocalPlayer + m_vecOrigin, reinterpret_cast<void*>(&LocalPlayerPos),sizeof(Vector3));
}

ViewMatrixStruct Engine::GetViewMatrix()
{
	return ViewMatrix;
}

std::vector<std::shared_ptr<ActorEntity>> Engine::GetActors()
{
	std::vector<std::shared_ptr<ActorEntity>> tempactors;
	ActorMutex.lock();
	tempactors = Actors;
	ActorMutex.unlock();
	return tempactors;
}

int Engine::GetActorSize()
{
	return SlotNum;
}