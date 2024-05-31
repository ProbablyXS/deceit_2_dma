#include "Pch.h"
#include "ActorEntity.h"
#include "Camera.h"
#include "Globals.h"
#include <string>

ActorEntity::ActorEntity(uint64_t address,VMMDLL_SCATTER_HANDLE handle)
{
	Class = address;
	if(!address)
		return;  //Class = AActor
	 TargetProcess.AddScatterReadRequest(handle, Class + PlayerState, reinterpret_cast<void*>(&PlayerState), sizeof(uint64_t));
	 TargetProcess.AddScatterReadRequest(handle,Class + AcknowledgedPawn, reinterpret_cast<void*>(&AcknowledgedPawn),sizeof(uint64_t));
	 TargetProcess.AddScatterReadRequest(handle, Class + RootComponent, reinterpret_cast<void*>(&RootComponent), sizeof(uint64_t));

	
}

void ActorEntity::SetUp1(VMMDLL_SCATTER_HANDLE handle)
{
	if (!Class)
		return;
	if (!RootComponent)
		return;
	//if (!AcknowledgedPawn && PlayerState) // players aren't pawns
	//if (PlayerState) // players aren't pawns
	//{
	TargetProcess.AddScatterReadRequest(handle, PlayerState + GameRole, reinterpret_cast<void*>(&PlayerRole), sizeof(EPlayerRole));
	TargetProcess.AddScatterReadRequest(handle, PlayerState + GameCharacterName, reinterpret_cast<void*>(&CharacterNameId), sizeof(EDeceitCharacter));
	TargetProcess.AddScatterReadRequest(handle, PlayerState + GamePlayerNameOffset, reinterpret_cast<void*>(&PlayerNameAddress), sizeof(64));
	//}
}


std::wstring ReadStringFromMemory(uint64_t address) {
	std::wstring result;
	wchar_t character;

	// Loop to read each character until the null terminator is found
	while (true) {
		character = TargetProcess.Read<wchar_t>(address);
		if (character == L'\0') {
			break;
		}
		result += character;
		address += sizeof(wchar_t); // Move to the next character
	}

	return result;
}

void ActorEntity::SetUp2()
{

	if (!Class)
		return;
	if (!RootComponent)
		return;
	//if (!AcknowledgedPawn && PlayerState) // players aren't pawns
	if (AcknowledgedPawn && PlayerState) // players aren't pawns
	{
		 //by this point we should only have our surviors and killers
		//if (PlayerRole != EPlayerRole::EDeceitRole__Human && PlayerRole != EPlayerRole::EDeceitRole__Terror)
		/*if (PlayerRole == EPlayerRole::EDeceitRole__Human || PlayerRole == EPlayerRole::EDeceitRole__Invalid)
			return;*/

		if (PlayerRole != EPlayerRole::EDeceitRole__Invalid)
			return;

		CharacterName = GetPlayerNameById(CharacterNameId);
		//PlayerName = ReadStringFromMemory(PlayerNameAddress);

		//PLAYER NAME
		//uint64_t test = TargetProcess.Read<uint64_t>(PlayerName); // APlayerState

		uint64_t test = TargetProcess.Read<uint64_t>(PlayerState + GamePlayerNameOffset); // APlayerState
		TerrorCosmetic = TargetProcess.Read<int>(PlayerState + TerrorCosmeticOffset); // APlayerState
		std::wstring playerName = ReadStringFromMemory(test); // Read the full player name
		PlayerName = playerName;
		//std::wcout << L"Player name: " << CharacterName + L" : " << std::boolalpha << (isInfected) << std::endl;

		if (TerrorCosmetic)
			std::wcout << L"Player name: " << CharacterName + L" : " << std::boolalpha << (TerrorCosmetic) << std::endl;

		//PLAYER NAME

		//std::cout << "test : " << test << std::endl;


		//uint64_t test = PlayerState;
		//char32_t test = TargetProcess.Read<char32_t>(PlayerState + 0x330);

		//test = TargetProcess.Read<char>(test); //APlayerState
		//test = test + 0x0;
		//UINT64 test = TargetProcess.Read<UINT64>(Class);

		//std::cout << "test: " << std::boolalpha << test << std::endl;
		//std::cout << "test : " << static_cast<int>(test) << std::endl;
		//std::string result = "test : " + std::to_string(test);
		//std::cout << "test : " << std::hex << static_cast<uint64_t>(test) << std::endl;
		//std::cout << "test : " << std::to_string(test) << std::endl;

		UEPosition = TargetProcess.Read<UEVector>(RootComponent + RelativeLocation);
		Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
	}

}

bool ActorEntity::GetPlayerRole()
{
	return TerrorCosmetic;
}

EDeceitCharacter ActorEntity::GetCharacterNameId()
{
	return CharacterNameId;
}

uint64_t ActorEntity::GetClass()
{
	return Class;
}

std::wstring ActorEntity::GetCharacterName()
{
	return CharacterName;
}

std::wstring ActorEntity::GetPlayerName()
{
	return PlayerName;
}

Vector3 ActorEntity::GetPosition()
{
	Position = Vector3(UEPosition.X, UEPosition.Y, UEPosition.Z);
	return Position;
}

void ActorEntity::UpdatePosition(VMMDLL_SCATTER_HANDLE handle)
{
	if (!Class)
		return;
	if (!RootComponent)
		return;
	if (!PlayerState)
		return;
	if (!AcknowledgedPawn) // players aren't pawns
		return;
	/*if (PlayerRole != EPlayerRole::EDeceitRole__Human && PlayerRole != EPlayerRole::EDeceitRole__Terror)
		return;*/
	/*if (PlayerRole != EPlayerRole::EDeceitRole__Invalid)
		return;*/
	TargetProcess.AddScatterReadRequest(handle, RootComponent + RelativeLocation, reinterpret_cast<void*>(&UEPosition), sizeof(UEVector));
}