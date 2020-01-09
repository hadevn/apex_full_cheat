#pragma once
#include "Cheat.h"
#include "math\VMatrix.hpp"
#include "Color.h"
#define TIME_TO_TICKS(dt) ((int)( 0.5f + (float)(dt) / I::Globals->interval_per_tick))
#define TICKS_TO_TIME(t) (I::Globals->interval_per_tick * (t) )
#define CONTENTS_EMPTY 0x0
#define	CONTENTS_SOLID 0x1
#define	CONTENTS_WINDOW 0x2
#define CONTENTS_AUX 0x4
#define	CONTENTS_GRATE 0x8
#define CONTENTS_SLIME 0x10
#define CONTENTS_WATER 0x20
#define CONTENTS_WINDOW_NOCOLLIDE 0x40
#define CONTENTS_OPAQUE 0x80
#define CONTENTS_TESTFOGVOLUME 0x100
#define CONTENTS_PHYSICSCLIP 0x200
#define CONTENTS_SOUNDTRIGGER 0x400
#define CONTENTS_NOGRAPPLE 0x800
#define CONTENTS_OCCLUDESOUND 0x1000
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000
#define CONTENTS_MOVEABLE 0x4000
#define CONTENTS_TEST_SOLID_BODY_SHOT	0x8000
#define CONTENTS_PLAYERCLIP 0x10000
#define CONTENTS_MONSTERCLIP 0x20000
#define CONTENTS_OPERATOR_FLOOR 0x40000
#define CONTENTS_BLOCKLOS 0x80000
#define CONTENTS_NOCLIMB 0x100000
#define CONTENTS_TITANCLIP 0x200000
#define CONTENTS_BULLETCLIP 0x400000
#define CONTENTS_OPERATORCLIP 0x800000
#define CONTENTS_NOAIRDROP 0x1000000
#define CONTENTS_MONSTER 0x2000000
#define CONTENTS_DEBRIS 0x4000000
#define CONTENTS_DETAIL 0x8000000
#define CONTENTS_TRANSLUCENT 0x10000000
#define CONTENTS_HITBOX 0x40000000

#define TRACE_CONTENTS_OPERATOR_FLOOR (CONTENTS_OPERATOR_FLOOR)
#define TRACE_MASK_SOLID (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_GRATE|CONTENTS_PHYSICSCLIP|CONTENTS_MOVEABLE|CONTENTS_MONSTER)
#define TRACE_MASK_PLAYERSOLID (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_GRATE|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_MONSTER)
#define TRACE_MASK_TITANSOLID (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_GRATE|CONTENTS_MOVEABLE|CONTENTS_TITANCLIP|CONTENTS_MONSTER)
#define TRACE_MASK_NPCSOLID (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_GRATE|CONTENTS_PHYSICSCLIP|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_MONSTER)
#define TRACE_MASK_NPCFLUID (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_MONSTER)
#define TRACE_MASK_SOLID_BRUSHONLY (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_GRATE|CONTENTS_PHYSICSCLIP|CONTENTS_MOVEABLE)
#define TRACE_MASK_PLAYERSOLID_BRUSHONLY (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_GRATE|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP)
#define TRACE_MASK_NPCSOLID_BRUSHONLY (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_GRATE|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP)
#define TRACE_MASK_WATER (CONTENTS_SLIME|CONTENTS_WATER)
#define TRACE_MASK_OPAQUE (CONTENTS_SOLID|CONTENTS_OPAQUE|CONTENTS_MOVEABLE)
#define TRACE_MASK_OPAQUE_AND_NPCS (CONTENTS_SOLID|CONTENTS_OPAQUE|CONTENTS_MOVEABLE|CONTENTS_MONSTER)
#define TRACE_MASK_BLOCKLOS (CONTENTS_SOLID|CONTENTS_OPAQUE|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
#define TRACE_MASK_BLOCKLOS_AND_NPCS (CONTENTS_SOLID|CONTENTS_OPAQUE|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS|CONTENTS_MONSTER)
#define TRACE_MASK_VISIBLE (CONTENTS_SOLID|CONTENTS_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE|CONTENTS_MOVEABLE)
#define TRACE_MASK_VISIBLE_AND_NPCS (CONTENTS_SOLID|CONTENTS_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE|CONTENTS_MOVEABLE|CONTENTS_MONSTER)
#define TRACE_MASK_SHOT (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_SLIME|CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_BULLETCLIP|CONTENTS_MONSTER|CONTENTS_DEBRIS|CONTENTS_HITBOX)
#define TRACE_MASK_SHOT_BRUSHONLY (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_SLIME|CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_BULLETCLIP|CONTENTS_DEBRIS)
#define TRACE_MASK_GRENADE (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_GRATE|CONTENTS_MOVEABLE|CONTENTS_BULLETCLIP|CONTENTS_MONSTER|CONTENTS_DEBRIS|CONTENTS_HITBOX)
#define TRACE_MASK_SHOT_HULL (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_GRATE|CONTENTS_MOVEABLE|CONTENTS_BULLETCLIP|CONTENTS_MONSTER|CONTENTS_DEBRIS)
#define TRACE_MASK_NPCWORLDSTATIC (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_GRATE|CONTENTS_MONSTERCLIP)
static const char* targetMode[] =
{
	"FOV",
	"Distance",
	"Threat"
};
static const char* AntiAim_X[] =
{
	"Down",
//	"Zero",
//	"UP",
//	"Mix",
	"Lisp Zero"
};
static const char* AntiAim_Y[] =
{
	"Backward",
	"SideWayL",
	"SideWayR",
	"FastSpin",
	"SlowSpin",
	"Jitter",
	"MixJitter",
	"Rand",
	"Lisp Fake"
};
static const char* keyNames[] =
{
	"",
	"Mouse 1",
	"Mouse 2",
	"Cancel",
	"Middle Mouse",
	"Mouse 4",
	"Mouse 5",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",

};
enum ButtonCode_t
{
	BUTTON_CODE_INVALID = -1,
	BUTTON_CODE_NONE = 0,

	KEY_FIRST = 0,

	KEY_NONE = KEY_FIRST,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_PAD_0,
	KEY_PAD_1,
	KEY_PAD_2,
	KEY_PAD_3,
	KEY_PAD_4,
	KEY_PAD_5,
	KEY_PAD_6,
	KEY_PAD_7,
	KEY_PAD_8,
	KEY_PAD_9,
	KEY_PAD_DIVIDE,
	KEY_PAD_MULTIPLY,
	KEY_PAD_MINUS,
	KEY_PAD_PLUS,
	KEY_PAD_ENTER,
	KEY_PAD_DECIMAL,
	KEY_LBRACKET,
	KEY_RBRACKET,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_BACKQUOTE,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_BACKSLASH,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_ENTER,
	KEY_SPACE,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_CAPSLOCK,
	KEY_NUMLOCK,
	KEY_ESCAPE,
	KEY_SCROLLLOCK,
	KEY_INSERT,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_BREAK,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LALT,
	KEY_RALT,
	KEY_LCONTROL,
	KEY_RCONTROL,
	KEY_LWIN,
	KEY_RWIN,
	KEY_APP,
	KEY_UP,
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_CAPSLOCKTOGGLE,
	KEY_NUMLOCKTOGGLE,
	KEY_SCROLLLOCKTOGGLE,

	KEY_LAST = KEY_SCROLLLOCKTOGGLE,
	KEY_COUNT = KEY_LAST - KEY_FIRST + 1,

	// Mouse
	MOUSE_FIRST = KEY_LAST + 1,

	MOUSE_LEFT = MOUSE_FIRST,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	MOUSE_4,
	MOUSE_5,
	MOUSE_WHEEL_UP,		// A fake button which is 'pressed' and 'released' when the wheel is moved up 
	MOUSE_WHEEL_DOWN,	// A fake button which is 'pressed' and 'released' when the wheel is moved down

	MOUSE_LAST = MOUSE_WHEEL_DOWN,
	MOUSE_COUNT = MOUSE_LAST - MOUSE_FIRST + 1,
};
typedef unsigned long CRC32_t;

struct CUserCmd {
	int32_t command_number; //0x0000 
	int32_t tick_count; //0x0004 
	float_t curtime; //0x0008 
	QAngle viewangles; //0x000C 
	char pad_0x0018[0xC]; //0x0018
	float_t forwardmove; //0x0024 
	float_t sidemove; //0x0028 
	float_t upmove; //0x002C 
	int32_t buttons; //0x0030 
	char pad_0x0034[0x150]; //0x0034
	int32_t randomseed; //0x0184 
	char pad_0x0188[0x8]; //0x0188
	Vector headposition; //0x0190 
	float_t maxpitch; //0x019C 
	char pad_0x01A0[0xE0]; //0x01A0
};//size 0x0280;

class CInput
{
public:
	virtual void Function0(); // 0
	virtual void Function1(); // 8
	virtual void Function2(); // 10
	virtual void Function3(); // 18
	virtual void Function4(); // 20
	virtual void Function5(); // 28
	virtual void Function6(); // 30
	virtual void Function7(); // 38
	virtual void Function8(); // 40
	virtual CUserCmd  *GetUserCmd(int uk, int sequence_number); //	48

	class CVerifiedUserCmd
	{
	public:
		CUserCmd	    m_cmd;
		CRC32_t         m_crc;
	};
};


struct cplane_t
{
	Vector			surfaceNormal;			//0x0000
	float			dist;					//0x000C
											//char			signbits;		// signx + (signy<<1) + (signz<<1)
											//char			pad[2];
}; //0x0010


struct csurface_t
{
	const char*		name;					//0x0000
	int				surfaceProp;			//0x0008
	unsigned short	flags;					//0x000A
}; //0x0010 (aligned)

struct trace_t
{
	Vector			start;						//0x0000
	int				unk000;					//0x000C
	Vector			endpos;						//0x0010
	char			_unk0x001C[0x4];			//0x001C
	cplane_t		plane;						//0x0020
	float			fraction;					//0x0030
	int				contents;					//0x0034
	bool			allSolid;					//0x0038
	bool			startSolid;					//0x0039
	char			_unk0x003A[0x6];			//0x003A
	csurface_t		surface;					//0x0040
	float			fractionleftsolid;			//0x0050
	int				hitgroup;					//0x0054
	short			physicsBone;				//0x0058
	char			_unk0x005A[0x6];			//0x005A
	CBaseEntity		*m_pEnt;					//0x0060
	int				hitbox;						//0x0068
	char			_unk0x006C[0x114];			//0x006C

}; //Size = 0x180
class Ray_t
{
public:


	Vector4D start_pos;			//0x000
	Vector4D delta_pos;			//0x010
	Vector4D m_StartOffset;		//0x020
	VectorAligned m_Extents;			//0x030
	char gap2C[0x10]; // probably contains m_Extents

	matrix3x4_t* m_pWorldAxisTransform;
	bool m_IsRay;
	bool m_IsSwept;

	//Ray_t() : m_pWorldAxisTransform(NULL) {}

	void Init(Vector vecStart, Vector vecEnd)
	{
		delta_pos = Vector4D((vecEnd - vecStart).ToVector4(0));
		m_IsSwept = (delta_pos.LengthSqr() != 0.f);
		m_Extents.Zero();
		m_pWorldAxisTransform = NULL;
		m_IsRay = true;
		m_StartOffset.Zero();
		start_pos = vecStart.ToVector4(0);

	}
}; //Size: 0x0168
class ITraceFilter;
class IEngineTrace
{
public:
	void ClipRayToEntity(Ray_t &ray, unsigned int fMask, CBaseEntity *pEnt, trace_t *pTrace);
	void TraceRay(Ray_t & ray, unsigned int fMask, trace_t * pTrace);
//	void TraceRay(Ray_t &ray, unsigned int fMask, CBaseEntity *pEnt, trace_t *pTrace);
	void fnTraceRay(Ray_t *ray, Vector form, Vector to);
};
enum WEAPONS_ID {
	BARE_HANDS = 14,
	WEAPONID_三重精准步枪 = 54,
	WEAPONID_专注轻机枪 = 40,
	WEAPONID_哈沃克 = 56,
	WEAPONID_充能步枪 = 58,
	WEAPONID_小帮手 = 55,
	WEAPONID_喷火机枪 = 53,
	WEAPONID_长弓精准步枪 = 41,
	WEAPONID_潜袭冲锋枪 = 49,
	WEAPONID_连发突击步枪 = 45,
	WEAPONID_VK47 = 43,
	WEAPONID_RE自动手枪 = 39,
	WEAPONID_P2020手枪 = 52,
	WEAPONID_R301 = 0,
	WEAPONID_R99 = 51,
	WEAPONID_转换者冲锋枪 = 38,
	WEAPONID_G7侦查枪 = 44,
	WEAPONID_薯片枪 = 48,
	WEAPONID_和平捍卫者 = 50,
	WEAPONID_自动连喷 = 42,
	WEAPONID_L_STAR = 57,
	WEAPONID_獒犬霰弹 = 47,
	WEAPONID_金狙 = 46,
};

enum ItemId {
	GOLD_KRABER = 1,
	GOLD_MASTIFF = 2,
	GOLD_LSTAR = 3,
	HAVOC = 4,
	GOLD_HAVOC = 5,
	DEVOTION = 6,
	TRIPLE_TAKE = 8,
	GOLD_TRIPLE_TAKE = 9,
	FLATLINE = 10,
	GOLD_FLATLINE = 11,
	HEMLOCK = 12,
	G7_SCOUT = 13,
	GOLD_G7_SCOUT = 14,
	ALTERNATOR = 15,
	GOLD_ALTERNATOR = 16,
	R_99 = 17,
	PROWLER = 18,
	GOLD_PROWLER = 19,
	LONGBOW = 20,
	GOLD_LONGBOW = 21,
	CHARGE_RIFLE = 22,
	GOLD_CHARGE_RIFLE = 23,
	SPITFIRE = 24,
	R_301 = 25,
	EVA_8_AUTO = 26,
	PEACEKEEPER = 29,
	GOLD_PEACEKEEPER = 30,
	MOZAMBIQUE = 31,
	GOLD_MOZAMBIQUE = 32,
	WINGMAN = 33,
	GOLD_WINGMAN = 34,
	P2020 = 35,
	GOLD_P2020 = 36,
	RE_45 = 37,
	GOLD_RE_45 = 38,

	LIGHT_ROUNDS = 39,
	ENERGY_AMMO = 40,
	SHOTGUN_SHELLS = 41,
	HEAVY_ROUNDS = 42,

	ULTIMATE_ACCELERANT = 43,
	PHOENIX_KIT = 44,
	MED_KIT = 45,
	SYRINGE = 46,
	SHIELD_BATTERY = 47,
	SHIELD_CELL = 48,

	HELMET_LV1 = 49,
	HELMET_LV2 = 50,
	HELMET_LV3 = 51,
	HELMET_LV4 = 52,
	BODY_ARMOR_LV1 = 53,
	BODY_ARMOR_LV2 = 54,
	BODY_ARMOR_LV3 = 55,
	BODY_ARMOR_LV4 = 56,
	KNOCKDOWN_SHIELD_LV1 = 57,
	KNOCKDOWN_SHIELD_LV2 = 58,
	KNOCKDOWN_SHIELD_LV3 = 59,
	KNOCKDOWN_SHIELD_LV4 = 60,
	BACKPACK_LV1 = 61,
	BACKPACK_LV2 = 62,
	BACKPACK_LV3 = 63,
	BACKPACK_LV4 = 64,

	THERMITE_GRENADE = 65,
	FRAG_GRENADE = 66,
	ARC_STAR = 67,

	HCOG_CLASSIC = 68,
	HCOG_BRUISER = 69,
	HOLO = 70,
	VARIABLE_HOLO = 71,
	DIGITAL_THREAT = 72,
	HCOG_RANGER = 73,
	VARIABLE_AOG = 74,
	SNIPER = 75,
	VARIABLE_SNIPER = 76,
	DIGITAL_SNIPER_THREAT = 77,

	BARREL_STABILIZER_LV1 = 78,
	BARREL_STABILIZER_LV2 = 79,
	BARREL_STABILIZER_LV3 = 80,
	BARREL_STABILIZER_LV4 = 81,
	LIGHT_MAGAZINE_LV1 = 82,
	LIGHT_MAGAZINE_LV2 = 83,
	LIGHT_MAGAZINE_LV3 = 84,
	HEAVY_MAGAZINE_LV1 = 85,
	HEAVY_MAGAZINE_LV2 = 86,
	HEAVY_MAGAZINE_LV3 = 87,
	ENERGY_MAGAZINE_LV1 = 88,
	ENERGY_MAGAZINE_LV2 = 89,
	ENERGY_MAGAZINE_LV3 = 90,
	SHOTGUN_BOLT_LV1 = 91,
	SHOTGUN_BOLT_LV2 = 92,
	SHOTGUN_BOLT_LV3 = 93,
	STANDARD_STOCK_LV1 = 94,
	STANDARD_STOCK_LV2 = 95,
	STANDARD_STOCK_LV3 = 96,
	SNIPER_STOCK_LV1 = 97,
	SNIPER_STOCK_LV2 = 98,
	SNIPER_STOCK_LV3 = 99,

	TURBOCHARGER = 100,
	SELECTFIRE_RECEIVER = 101,
	PRECISION_CHOKE = 102,
	anvilreceiver = 104,
	doubletaptrigger = 105,
	HAMMERPOINT_ROUNDS = 103,
};
enum SIGNONSTATE
{
	SIGNONSTATE_NONE = 0,
	SIGNONSTATE_CHALLENGE = 1,
	SIGNONSTATE_CONNECTED = 2,
	SIGNONSTATE_NEW = 3,
	SIGNONSTATE_PRESPAWN = 4,
	SIGNONSTATE_GETTINGDATA = 5,
	SIGNONSTATE_SPAWN = 6,
	SIGNONSTATE_FIRSTSNAP = 7,
	SIGNONSTATE_FULL = 8,
	SIGNONSTATE_CHANGELEVEL = 9,
};


namespace I // Interfaces
{
	extern IVEngineClient* Engine;
	extern IGlobalVarsBase* Globals;
	extern IClientEntityList* ClientEntList;
	extern IEngineTrace* EngineTrace;
}
namespace G
{
	extern CBaseEntity* LocalPlayer;
	extern CUserCmd* UserCmd;
	extern GColor* gc;
	extern bool PressedKeys[256];
	extern bool SendPacket;

}
namespace E
{
	extern CMiscellaneous*	Misc;
	extern CRageBot* RageBot;
}