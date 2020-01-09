#pragma once
#include <vector>
#include "utils\ArrayBase.h"
#include "math\Vector.hpp"
using namespace std;

#define TYPE_PLAYER 0x100
#define TYPE_ITEM	0x101

#define TYPE_MODEL1	0x200	
#define TYPE_MODEL2	0x201
#define TYPE_MODEL3	0x202
#define TYPE_MODEL4	0x203
#define TYPE_MODEL5	0x204
#define TYPE_MODEL6	0x205
#define TYPE_MODEL7	0x206
#define TYPE_MODEL8	0x207
#define TYPE_MODEL9	0x208


#define ITEM_WEAPONS		0x300	
#define ITEM_AMMO			0x301
#define ITEM_HEALING		0x302
#define ITEM_SHIELD			0x303
#define ITEM_GRENADES		0x304
#define ITEM_SCOPES			0x305
#define ITEM_ATTACHMENTS	0x306

typedef struct
{
	DWORD64 dwPtr;
	DWORD id;
	DWORD nameid;
	bool isAlive;
	int health;
	int maxhealth;
	int shieldhealth;
	int shieldhealthmax;
	int teamid;
	string name;
	Vector orgin;
	Vector head;
	int type;
	int modeltype;
	int itemtpye;
}ACTOR_INFO, *PACTOR_INFO;


typedef struct
{
	int head;				//Í·
	int neck;				//²±×Ó
	int abdomen;			//¸¹²¿
	int Left_shoulder;		//×ó¼ç
	int Right_shoulder;		//ÓÒ¼ç
	int Left_arm;			//×ó±Û
	int Right_arm;			//ÓÒ±Û
	int Left_arm_1;			//×ó±Û1
	int Right_arm_1;		//ÓÒ±Û1
	int Left_arm_2;			//×ó±Û2
	int Right_arm_2;		//ÓÒ±Û2
	int Left_knee;			//×óÏ¥¸Ç
	int Right_knee;			//ÓÒÏ¥¸Ç
	int Left_foot;			//×ó½Å
	int Right_foot;			//ÓÒ½Å
}BONEIDBYMODEL;


enum BoneId {
	head = 10,	//	Í·
	neck = 9,	//	²±×Ó
	Left_shoulder = 39,//×ó¼ç
	Right_shoulder = 14,//ÓÒ¼ç
	Left_clavicle = 38,//×óËø¹Ç
	Right_clavicle = 13,//ÓÒËø¹Ç
	chest = 7,//ÐØ
	abdomen = 6,//¸¹²¿
	perineum = 5,//»áÒõ
	Left_arm = 41,//×ó±Û
	Left_arm_1 = 43,//×ó±Û1
	Left_arm_2 = 68,//×ó±Û2
	Left_arm_3 = 45,//×ó±Û3
	Right_arm = 16,//ÓÒ±Û
	Right_arm_1 = 18,//ÓÒ±Û1
	Right_arm_2 = 63,//ÓÒ±Û2
	Right_arm_3 = 20,//ÓÒ±Û3
	Left_knee = 70,//×óÏ¥¸Ç
	Right_knee = 65,//ÓÒÏ¥¸Ç
	Left_foot = 71,//×ó½Å
	Left_foot_1 = 72,//×ó½Å1
	Right_foot = 66,//ÓÒ½Å
	Right_foot_1 = 67,//ÓÒ½Å1
};//22



class CActorMgr
{
public:
	CActorMgr();
	~CActorMgr();

	//	void GetBone(DWORD64 dwEntry, Vector &EntityPos, Vector *pOutBoneArry);
public:
	void Update();
	ACTOR_INFO *GetLocalPlayer();
	TArrayMgr<ACTOR_INFO> *Get() { return &m_List; }
	DWORD64 GetWeaponPtr();
	int GetItemTpye(int id);
private:

	TArrayMgr<ACTOR_INFO> m_List;
};
