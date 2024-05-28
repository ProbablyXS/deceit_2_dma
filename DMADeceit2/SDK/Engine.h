#pragma once
#include "ActorEntity.h"
#include "EngineStructs.h"

// For these offsets just 7 dumper the game and open Engine_Classes
class Engine
{

private:
	uint64_t OwningActorOffset = 0x98; // NetConnection -> OwningActor //DONE
	uint64_t MaxPacketOffset = 0xa0; // NetConnection -> MaxPacket //DONE
	uint64_t OwningActor;
	uint64_t MaxPacket;
	uint64_t OwningGameInstance = 0x1b8; // World -> OwningGameInstance // DONE
	uint64_t PersistentLevel = 0x30; // World  -> PersistentLevel //DONE
	uint64_t GWorld = 0x8c86248; // DONE
	uint64_t LocalPlayers = 0x38; // GameInstance -> LocalPlayers //DONE
	uint64_t PlayerController = 0x30; // Player -> PlayerController //DONE
	uint64_t AcknowledgedPawn = 0x340; //DONE


	uint64_t CameraManager = 0x350; // PlayerController -> PlayerCameraManager //DONE
	uint64_t CameraCachePrivate = 0x0; // PlayerCameraManager -> CameraCachePrivate //DONE
	uint64_t CameraCachePrivateOffset = 0x1320; // PlayerCameraManager -> CameraCachePrivate //DONE


	CameraCacheEntry CameraEntry; // ScriptStruct Engine.CameraCacheEntry //DONE
	MinimalViewInfo CameraViewInfo; // ScriptStruct Engine.MinimalViewInfo //DONE
	std::vector<std::shared_ptr<ActorEntity>> Actors;
public:
	Engine();
	void Cache();
	void UpdatePlayers();
	std::vector<std::shared_ptr<ActorEntity>> GetActors();
	CameraCacheEntry GetCameraCache();
	void RefreshViewMatrix(VMMDLL_SCATTER_HANDLE handle);
	uint32_t GetActorSize();

};