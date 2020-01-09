#pragma once


struct Variables
{
	Variables()
	{

	}
	struct
	{
		bool	Opened = false;
	} Menu;
	struct
	{
		bool	Enabled = true;
		bool	Box = true;
		bool	Health = true;
		bool	Skeleton = true;
		bool	Highlight = false;
		bool	Glow = false;
		bool	Weapon = false;
		bool	AimSpot = false;
		bool	Shield = true;
		bool	Name = true;
		bool	Distance = true;
		bool	PlayerEnable = true;
		bool	ItemEnable = true;
		bool	ItemWeapons = true;
		bool	ItemAmmo = true;
		bool	ItemHealing = false;
		bool	ItemShield = false;
		bool	ItemGrenades = false;
		bool	ItemScopes = false;
		bool	ItemAttachments = false;
		bool	AimWarning = false;
		bool	DrawFov = false;
		bool	Circular = false;
		float	MaxPlayerDis = 400.f;
		float	MaxItemDis = 50.f;
		float	MaxSpot = 3000.f;
		struct
		{
			bool	Enable = true;
			bool	EnemyOnly = true;
			bool	VisibleOnly = false;
			bool	ViewCheck = true;
			int		Alpha = 255;
			float	Zoom = 1.5f;
			int		Type = 0;
			bool	NextResetRadar = false;
			float	MaxDis = 250.f;
		} Radar;
	} Visuals;
	struct
	{
		bool	Enabled = true;
		bool	EnabledAimbot = true;
		bool	EnableAimBotKey = true;
		bool	Silent = false;
		bool	AutoShot = false;
		bool	BaimShotGun = true;
		bool	VisualCheck = true;
		float	FOV = 30.f;
		int		AimBotKey = 2;
		int		TargetMethod = 1;
		bool	Hitboxs[5];
		bool	ExtrapolateTick = false;
		bool	Predict = true;
		bool	OneShot = true;
		float	MaxAutoShotDis = 110.f;
		float	MaxDis = 110.f;
		struct
		{
			bool	Enable = false;
			bool	AtPlayer = true;
			bool	AutoHead = true;
			int		Pitch = 0;
			int		Yaw = 3;
			//int		FakeYaw = 1;
			float	MinDis = 90.f;
		} AntiAim;
		struct
		{
			bool	EnableLegit = false;
			int		BaimAfterXshot = 5;
			int		StopAfterXshot = 10;
			int		BaimLowHP = 10;
			int		Soomth = 50;
		}Legit;
	} Rage;
	struct
	{
		float	Speed = 2.f;
		bool	EnableSpeedHack = false;
		bool	FakeLagSpeedHack = false;
		bool	Bhop = false;
		bool	AutoDuck = true;
		bool	AutoPistol = false;
		bool	NoSpread = false;
		bool	AdaptiveFakeLag = false;
		bool	ForwareTrack = false;
		bool	NoSway = false;
		int		SpeedHackKey = 0;
		int		FakeLag = 0;
		int		AutoDuckLimit = 2;
		bool	FakeDuck = true;
	} Misc;
	bool RageMode = false;
};

extern Variables Vars;