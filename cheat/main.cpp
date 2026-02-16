#include "memory.h"
#include <thread>
#include <Windows.h>
#include <iostream>

namespace offsets
{
	constexpr auto PlayerCount = 0x0018AC0C;
	constexpr auto localPlayer = 0x0018AC00;
	constexpr auto EntityList = 0x0018AC04;
	
	constexpr auto PPosX = 0x28;
	constexpr auto PPosY = 0x2c;
	constexpr auto PPosZ = 0x30;

	constexpr auto HeadPosX = 0x04;
	constexpr auto HeadPosY = 0x08;
	constexpr auto HeadPosZ = 0x0C;

	constexpr auto PovX = 0x34;
	constexpr auto PovY = 0x38;
	
	constexpr auto health = 0xEC;
	constexpr auto name = 0x205;
	constexpr auto armor = 0xf0;
	constexpr auto kills = 0x1dc;
	constexpr auto deaths = 0x1e4;

	constexpr auto PistolMag = 0x108;
	constexpr auto SubmashineMag = 0x114;
	constexpr auto SniperMag = 0x118;
	constexpr auto AssaultRifleMag = 0x11c;
	constexpr auto DoublePistolMag = 0x124;
	constexpr auto PistolAmmo = 0x12c;
	constexpr auto SubmashineAmmo = 0x138;
	constexpr auto SniperAmmo = 0x13c;
	constexpr auto AssaultRifleAmmo = 0x140;
	constexpr auto Grenades = 0x144;
	constexpr auto DoublePistolAmmo = 0x148;

	constexpr auto EnableDoublePistol = 0x100;

	constexpr auto OnGround = 0x5D;
	constexpr auto ClimbingLadder = 0x5E;
	constexpr auto Crouching = 0x61;
	constexpr auto IsNotMoving = 0x65;
	constexpr auto ADown = 0x80;
	constexpr auto DDown = 0x81;
	constexpr auto WDown = 0x82;
	constexpr auto SDown = 0x83;

	constexpr auto ForwardSpeed = 0x74;//1-10 merge fata; 255-245 spate
	constexpr auto SidewaySpeed = 0x75;//1-10 merge stanga; 255-245 dreapta
	constexpr auto EnableFly = 0x76;//00 - off 04-- on

	constexpr auto AssaultRifleWaitTime = 0x164;
	constexpr auto WeaponHolsterWaitTime = 0x310;
	constexpr auto AirTime = 0x48;
	constexpr auto PlayerName = 0x205;
}


// ESP
// Aimbot <---------
// Triggerbot
// ImGUI
// Infinite Ammo



bool Aimbot = false;
bool Triggerbot = false;
bool ESP = false;
bool InfiniteAmmo = false;
bool WalkSpeed = false;
bool HealthHack = false;
bool RapidFire = false;



int WSpeed = 5;



int main() 
{
	auto mem = Memory("ac_client.exe");

	const auto client = mem.GetModuleAddress("ac_client.exe");


	auto playercount = mem.Read<uintptr_t>(client + offsets::PlayerCount);

	const auto localPlayer = mem.Read<uintptr_t>(client + offsets::localPlayer);

	const auto PlayerList = mem.Read<uintptr_t>(client + offsets::EntityList);
	



	std::cout << "Assault Cube Hack alpha 1.1" << std::endl;
	std::cout << std::endl;
	std::cout << "F1 -> WalkSpeed" << std::endl;
	std::cout << "F2 -> Infinite Health" << std::endl;
	std::cout << "F3 -> Infinite Ammo" << std::endl;
	std::cout << "F4 -> Rapid Fire" << std::endl;



	while (true)
	{
		
		//F1 Toggle WalkSpeed

		if (GetAsyncKeyState(VK_F1) & 0x8000)
		{
			WalkSpeed = !WalkSpeed;
			std::cout << "WalkSpeed: " << (WalkSpeed ? "ON" : "OFF") << std::endl;
			if (WalkSpeed)
				std::cout << "F5 -> Increase Speed   ||   F6 -> Decrease Speed" << std::endl;
			Sleep(200);
			
		}

		//F2 Toggle Health Hack

		if (GetAsyncKeyState(VK_F2) & 0x8000)
		{
			HealthHack = !HealthHack;
			std::cout << "Infinite Health: " << (HealthHack ? "ON" : "OFF") << std::endl;
			Sleep(200);
		}



		//F3 Toggle Infinite Ammo

		if (GetAsyncKeyState(VK_F3) & 0x8000) {
			InfiniteAmmo = !InfiniteAmmo;
			std::cout << "Infinite Ammo: " << (InfiniteAmmo ? "ON" : "OFF") << std::endl;
			Sleep(200);
		}


		//F4 Toggle Rapid Fire

		if (GetAsyncKeyState(VK_F4) & 0x8000)
		{
			RapidFire = !RapidFire;
			std::cout << "Rapid Fire: " << (RapidFire ? "ON" : "OFF") << std::endl;
			Sleep(200);
		}



		// ============== Feature Implementation ================

		//WalkSpeed
		
		if (GetAsyncKeyState(VK_F5) & 0x8000)
		{
			if (WalkSpeed && WSpeed<10) 
			{
				WSpeed++;
				std::cout << "WalkSpeed increased to " << WSpeed << std::endl;
				Sleep(200);
			}
		}

		if (GetAsyncKeyState(VK_F6) & 0x8000)
		{
			if (WalkSpeed && WSpeed>1)
			{
				WSpeed--;
				std::cout << "WalkSpeed decreased to " << WSpeed << std::endl;
				Sleep(200);
			}
		}

		if (WalkSpeed)
		{
			if (mem.Read<BYTE>(localPlayer + offsets::WDown) != 0) {
				mem.Write<BYTE>(localPlayer + offsets::ForwardSpeed, WSpeed);
			}
			else if (mem.Read<BYTE>(localPlayer + offsets::SDown) != 0) {
				mem.Write<BYTE>(localPlayer + offsets::ForwardSpeed, 256 - WSpeed);
			}
			else {
				mem.Write<BYTE>(localPlayer + offsets::ForwardSpeed, 0);
			}
			if (mem.Read<BYTE>(localPlayer + offsets::ADown) != 0)
				mem.Write<BYTE>(localPlayer + offsets::SidewaySpeed, WSpeed);
			else if (mem.Read<BYTE>(localPlayer + offsets::DDown) != 0)
				mem.Write<BYTE>(localPlayer + offsets::SidewaySpeed, 256 - WSpeed);
			else
				mem.Write<BYTE>(localPlayer + offsets::SidewaySpeed, 0);
		}

			

		// Health Hack


		if (HealthHack)
		{
			mem.Write<WORD>(localPlayer + offsets::health, 999);
		}
		

		// Infinite Ammo


		if (InfiniteAmmo)
		{
			mem.Write<WORD>(localPlayer + offsets::AssaultRifleAmmo, 999);
			mem.Write<WORD>(localPlayer + offsets::SubmashineAmmo, 999);
			mem.Write<WORD>(localPlayer + offsets::SniperAmmo, 999);
			mem.Write<BYTE>(localPlayer + offsets::Grenades, 99);
			mem.Write<WORD>(localPlayer + offsets::DoublePistolAmmo, 999);
			mem.Write<WORD>(localPlayer + offsets::PistolAmmo, 999);
		}

		//RapidFire

		if (RapidFire) 
		{
			mem.Write<BYTE>(localPlayer + offsets::AssaultRifleWaitTime, 0);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}