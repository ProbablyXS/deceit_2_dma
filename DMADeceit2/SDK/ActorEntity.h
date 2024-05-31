#pragma once
#include "EngineStructs.h"
#include <iostream>
#include <string>

enum class EPlayerRole : uint8_t 
{ 
	EDeceitRole__Human = 0,
	EDeceitRole__Terror = 1, 
	EDeceitRole__Medic = 2,
	EDeceitRole__Warden = 3, 
	EDeceitRole__Inquisitor = 4,
	EDeceitRole__Mimic = 5, 
	EDeceitRole__Vector = 6,
	EDeceitRole__Invalid = 7
};

enum class EDeceitCharacter : uint8_t {
	Alex = 0,
	Lisa = 1,
	Chang = 2,
	Rachel = 3,
	Hans = 4,
	Nina = 5,
	Jak = 6,
	Priya = 7,
	Beck = 8,
	Last = 9
};

enum class EDeceitTerror : uint8_t {
	EDeceitTerror__Experiment = 0,
	EDeceitTerror__Werewolf = 1,
	EDeceitTerror__Last = 2
};

enum class EDeceitRole : uint8_t {
	EDeceitRole__Human = 0,
	EDeceitRole__Terror = 1,
	EDeceitRole__Medic = 2,
	EDeceitRole__Warden = 3,
	EDeceitRole__Inquisitor = 4,
	EDeceitRole__Mimic = 5,
	EDeceitRole__Vector = 6,
	EDeceitRole__Invalid = 7
};

 //Function to get the string name from the enum value
inline std::wstring GetPlayerNameById(EDeceitCharacter character) {
	switch (character) {
	case EDeceitCharacter::Alex: return L"Alex";
	case EDeceitCharacter::Lisa: return L"Lisa";
	case EDeceitCharacter::Chang: return L"Chang";
	case EDeceitCharacter::Rachel: return L"Rachel";
	case EDeceitCharacter::Hans: return L"Hans";
	case EDeceitCharacter::Nina: return L"Nina";
	case EDeceitCharacter::Jak: return L"Jak";
	case EDeceitCharacter::Priya: return L"Priya";
	case EDeceitCharacter::Beck: return L"Beck";
	case EDeceitCharacter::Last: return L"Last";
	default: return L"Unknown";
	}
}

class ActorEntity
{
private:
	uint64_t Class = 0;
	EPlayerRole PlayerRole;
	bool TerrorCosmetic;
	EDeceitCharacter CharacterNameId;
	uint64_t PlayerNameAddress;
	uint64_t PlayerState = 0x2b8; // Pawn -> PlayerState
	uint64_t AcknowledgedPawn = 0x340; // Pawn -> AcknowledgedPawn
	uint64_t RootComponent = 0x1a0; // Actor -> RootComponent
	uint64_t RelativeLocation = 0x128; // SceneComponent -> RelativeLocation
	uint64_t GameRole = 0x660; // ADeceitPlayerState -> ChosenRole
	uint64_t TerrorCosmeticOffset = 0x528; // is infected
	uint64_t GameCharacterName = 0x518; // ADeceitPlayerState -> Character
	uint64_t GamePlayerNameOffset = 0x330; // APlayerState -> PlayerNamePrivate
	std::wstring CharacterName = LIT(L"Entity");
	std::wstring PlayerName = LIT(L"Entity");
	UEVector UEPosition;
	Vector3 Position;
public:
	ActorEntity(uint64_t address, VMMDLL_SCATTER_HANDLE handle);
	void SetUp1(VMMDLL_SCATTER_HANDLE handle);
	void SetUp2();
	uint64_t GetClass();
	bool GetPlayerRole();
	EDeceitCharacter GetCharacterNameId();
	std::wstring GetCharacterName();
	std::wstring GetPlayerName();
	Vector3 GetPosition();
	void UpdatePosition(VMMDLL_SCATTER_HANDLE handle);

};