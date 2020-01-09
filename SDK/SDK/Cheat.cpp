#include "Cheat.h"
#include "ActorMgr.h"
#include "math\Vector2D.hpp"
#include "Color.h"
#include "hooks.h"
#include "D3dDraw.h"

//typedef bool(__fastcall *_GameWorldToSceen)(Vector location, Vector2D &out);
//_GameWorldToSceen world2screen;
Draw* D = new Draw;
CCheats *GetCheat()
{
	static CCheats m;
	return &m;
}

CCheats::CCheats()
{

	m_pActor = new CActorMgr;
}

CCheats::~CCheats()
{
	delete m_pActor;
}


void AddItemName(int id, char *pCN, char *pEN, char *pTexture)
{
	ITEM_NAME in;
	lstrcpyA(in.szCN, pCN);
	lstrcpyA(in.szEN, pEN);
	lstrcpyA(in.szTexture, pTexture);
	g_ItemHash[id] = in;
}

void InitItemName()
{
	//SEProtectStartMutation();
	g_ItemHash.clear();
	//Weapons
	AddItemName(GOLD_KRABER, "¿ËÀ×±´¶û¾Ñ»÷Ç¹", "Kraber", "ÊÕ");		//1
	AddItemName(GOLD_MASTIFF, "éáÈ®ö±µ¯Ç¹", "Mastiff", "²Ø");			//1
	AddItemName(GOLD_LSTAR, "L-Star EMG", "L-Star EMG", "A");
	AddItemName(GOLD_HAVOC, "¹þÎÖ¿Ë", "HowGun", "");
	AddItemName(DEVOTION, "×¨×¢Çá»úÇ¹", "Devotion", "ÖÂ");
	AddItemName(TRIPLE_TAKE, "ÈýÖØÊ½¾Ñ»÷Ç¹", "Triple Take", "½á");
	AddItemName(GOLD_TRIPLE_TAKE, "»Æ½ðÈýÖØÊ½¾Ñ»÷Ç¹", "Triple Take", "½á");
	AddItemName(FLATLINE, "VK-47Æ½ÐÐ²½Ç¹", "Flatline", "");
	AddItemName(GOLD_FLATLINE, "»Æ½ðVK-47Æ½ÐÐ²½Ç¹", "Flatline", "");
	AddItemName(HEMLOCK, "ºÕÄ·Âå¿ËÍ»»÷²½Ç¹", "Hemlok", "Èò");		//1
	AddItemName(G7_SCOUT, "G7Õì²éÇ¹", "G7 Scout", "Ñô");
	AddItemName(GOLD_G7_SCOUT, "»Æ½ðG7Õì²éÇ¹", "G7 Scout", "Ñô");
	AddItemName(ALTERNATOR, "×ª»»Õß³å·æÇ¹", "Alternator", "ÌÚ");
	AddItemName(GOLD_ALTERNATOR, "»Æ½ð×ª»»Õß³å·æÇ¹", "Alternator", "ÌÚ");
	AddItemName(R_99, "R-99³å·æÇ¹", "R-99", "ÂÉ");
	AddItemName(PROWLER, "Ç±Ï®³å·æÇ¹", "Prowler", "Ëª");
	AddItemName(GOLD_PROWLER, "»Æ½ðÇ±Ï®³å·æÇ¹", "Prowler", "Ëª");
	AddItemName(LONGBOW, "³¤¹­¾«È·²½Ç¹", "Longbow", "Óê");
	AddItemName(GOLD_LONGBOW, "»Æ½ð³¤¹­¾«È·²½Ç¹", "Longbow", "Óê");
	AddItemName(CHARGE_RIFLE, "³äÄÜ²½Ç¹", "EntGun", "");
	AddItemName(GOLD_CHARGE_RIFLE, "»Æ½ð³äÄÜ²½Ç¹", "EntGun", "");
	AddItemName(SPITFIRE, "M600Åç»ðÇá»úÇ¹", "Spitfire", "µ÷");
	AddItemName(R_301, "R-301¿¨±öÇ¹", "R-301", "Ëê");
	AddItemName(EVA_8_AUTO, "EVA-8×Ô¶¯ö±µ¯Ç¹", "EVA-8 Auto", "ÔÆ");	//1
	AddItemName(PEACEKEEPER, "ºÍÆ½º´ÎÀÕßö±µ¯Ç¹", "Peacekeeper", "¶¬");
	AddItemName(GOLD_PEACEKEEPER, "»Æ½ðºÍÆ½º´ÎÀÕßö±µ¯Ç¹", "Peacekeeper", "¶¬");
	AddItemName(MOZAMBIQUE, "ÄªÉ£±È¿Ëö±µ¯Ç¹", "Mozambique", "Îª");
	AddItemName(GOLD_MOZAMBIQUE, "»Æ½ðÄªÉ£±È¿Ëö±µ¯Ç¹", "Mozambique", "Îª");
	AddItemName(WINGMAN, "¸¨ÖúÊÖÇ¹", "Wingman", "Â¶");
	AddItemName(GOLD_WINGMAN, "»Æ½ð¸¨ÖúÊÖÇ¹", "Wingman", "Â¶");
	AddItemName(P2020, "P2020ÊÖÇ¹", "P2020", "ÂÀ");
	AddItemName(GOLD_P2020, "»Æ½ðP2020ÊÖÇ¹", "P2020", "ÂÀ");
	AddItemName(RE_45, "RE-45×Ô¶¯ÊÖÇ¹", "RE-45", "³É");
	AddItemName(GOLD_RE_45, "»Æ½ðRE-45×Ô¶¯ÊÖÇ¹", "RE-45", "³É");
	
	//Ammo
	AddItemName(LIGHT_ROUNDS, "ÇáÐÍµ¯Ò©", "Light Rounds", "");
	AddItemName(ENERGY_AMMO, "ÄÜÁ¿µ¯Ò©", "Energy Ammo", "");
	AddItemName(SHOTGUN_SHELLS, "ö±µ¯µ¯Ò©", "Shotgun Shells", "");
	AddItemName(HEAVY_ROUNDS, "ÖØÐÍµ¯Ò©", "Heavy Rounds", "");

	//Healing Items
	AddItemName(ULTIMATE_ACCELERANT, "¾øÕÐ¼ÓËÙ¼Á", "Ultimate Accelerant", "");
	AddItemName(PHOENIX_KIT, "·ï»ËÖÎÁÆ°ü", "Phoenix Kit", "½ð");
	AddItemName(MED_KIT, "Ò½ÁÆÏä", "Med Kit", "Ë®");
	AddItemName(SYRINGE, "×¢ÉäÆ÷", "Syringe", "Àö");
	AddItemName(SHIELD_BATTERY, "´óÐÍ»¤¶Üµç³Ø", "Shield Battery", "Óñ");
	AddItemName(SHIELD_CELL, "Ð¡ÐÍ»¤¶Üµç³Ø", "Shield Cell", "³ö");

	//Shield Items

	AddItemName(HELMET_LV1, "Í·¿ø(lv1)", "Helmet Level 1", "Éú lv1");
	AddItemName(HELMET_LV2, "Í·¿ø(lv2)", "Helmet Level 2", "Éú lv2");
	AddItemName(HELMET_LV3, "Í·¿ø(lv3)", "Helmet Level 3", "Éú lv3");
	AddItemName(HELMET_LV4, "Í·¿ø(lv4)", "Helmet Level 4", "Éú lv4");
	AddItemName(BODY_ARMOR_LV1, "·Àµ¯ÒÂ(lv1)", "Body Armor Level 1", "¸Ô lv1");
	AddItemName(BODY_ARMOR_LV2, "·Àµ¯ÒÂ(lv2)", "Body Armor Level 2", "¸Ô lv2");
	AddItemName(BODY_ARMOR_LV3, "·Àµ¯ÒÂ(lv3)", "Body Armor Level 3", "¸Ô lv3");
	AddItemName(BODY_ARMOR_LV4, "·Àµ¯ÒÂ(lv4)", "Body Armor Level 4", "¸Ô lv4");
	AddItemName(KNOCKDOWN_SHIELD_LV1, "»÷µ¹»¤¶Ü(lv1)", "Knockdown Shield Level 1", "ºÅ lv1");
	AddItemName(KNOCKDOWN_SHIELD_LV2, "»÷µ¹»¤¶Ü(lv2)", "Knockdown Shield Level 2", "ºÅ lv2");
	AddItemName(KNOCKDOWN_SHIELD_LV3, "»÷µ¹»¤¶Ü(lv3)", "Knockdown Shield Level 3", "ºÅ lv3");
	AddItemName(KNOCKDOWN_SHIELD_LV4, "»÷µ¹»¤¶Ü(lv4)", "Knockdown Shield Level 4", "ºÅ lv4");
	AddItemName(BACKPACK_LV1, "±³°ü(lv1)", "Backpack Level 1", "½£ lv1");
	AddItemName(BACKPACK_LV2, "±³°ü(lv2)", "Backpack Level 2", "½£ lv2");
	AddItemName(BACKPACK_LV3, "±³°ü(lv3)", "Backpack Level 3", "½£ lv3");
	AddItemName(BACKPACK_LV4, "±³°ü(lv4)", "Backpack Level 4", "½£ lv4");

	//Grenades
	AddItemName(THERMITE_GRENADE, "ÂÁÈÈ¼ÁÊÖÀ×", "Thermite Grenade", "");
	AddItemName(FRAG_GRENADE, "ÆÆÆ¬ÊÖÀ×", "Frag Grenade", "¾Þ");
	AddItemName(ARC_STAR, "·ÉïÚ", "Arc Star", "ãÚ");


	//Attachment Scopes
	AddItemName(HCOG_CLASSIC, "µ¥±¶È«Ï¢", "1x HCOG (Classic)", "Ó¯");
	AddItemName(HCOG_BRUISER, "2±¶È«Ï¢", "2x HCOG (Bruiser)", "Íù");
	AddItemName(HOLO, "µ¥±¶»ÃÓ°", "1x Holo", "ê¾");
	AddItemName(VARIABLE_HOLO, "1-2±¶»ÃÓ°", "1x-2x Variable Holo", "Ìì");
	AddItemName(DIGITAL_THREAT, "1±¶Êý×Ö»¯¾µ", "1x Digital Threat", "ÔÂ");
	AddItemName(HCOG_RANGER, "3±¶È«Ï¢", "3x HCOG (Ranger)", "Êî");
	AddItemName(VARIABLE_AOG, "2-4±¶Ãé×¼¾µ", "2x-4x Variable AOG", "Çï");
	AddItemName(SNIPER, "6±¶¾Ñ»÷Ãé×¼¾µ", "6x Sniper", "ÕÅ");
	AddItemName(VARIABLE_SNIPER, "4-8±¶Ãé×¼¾µ", "4x-8x Variable Sniper", "À´");
	AddItemName(DIGITAL_SNIPER_THREAT, "4-10±¶Ãé×¼¾µ", "4x-10x Digital Sniper Threat", "º®");

	//Attachments
	AddItemName(BARREL_STABILIZER_LV1, "Ç¹¹ÜÎÈ¶¨Æ÷(lv1)", "Barrel Stabilizer Level 1", "Öæ lv1");
	AddItemName(BARREL_STABILIZER_LV2, "Ç¹¹ÜÎÈ¶¨Æ÷(lv2)", "Barrel Stabilizer Level 2", "Öæ lv2");
	AddItemName(BARREL_STABILIZER_LV3, "Ç¹¹ÜÎÈ¶¨Æ÷(lv3)", "Barrel Stabilizer Level 3", "Öæ lv3");
	AddItemName(BARREL_STABILIZER_LV4, "Ç¹¹ÜÎÈ¶¨Æ÷(lv4)", "Barrel Stabilizer Level 4", "Öæ lv4");
	AddItemName(LIGHT_MAGAZINE_LV1, "¼Ó³¤Ê½ÇáÐÍµ¯Ï»lv1)", "Light Magazine Level 1", "ÈÕ lv1");
	AddItemName(LIGHT_MAGAZINE_LV2, "¼Ó³¤Ê½ÇáÐÍµ¯Ï»(lv2)", "Light Magazine Level 2", "ÈÕ lv2");
	AddItemName(LIGHT_MAGAZINE_LV3, "¼Ó³¤Ê½ÇáÐÍµ¯Ï»(lv3)", "Light Magazine Level 3", "ÈÕ lv3");
	AddItemName(HEAVY_MAGAZINE_LV1, "¼Ó³¤Ê½ÖØÐÍµ¯Ï»(lv1)", "Heavy Magazine Level 1", "»Ä lv1");
	AddItemName(HEAVY_MAGAZINE_LV2, "¼Ó³¤Ê½ÖØÐÍµ¯Ï»(lv2)", "Heavy Magazine Level 2", "»Ä lv2");
	AddItemName(HEAVY_MAGAZINE_LV3, "¼Ó³¤Ê½ÖØÐÍµ¯Ï»(lv3)", "Heavy Magazine Level 3", "»Ä lv3");

	AddItemName(ENERGY_MAGAZINE_LV1, "¼Ó³¤Ê½ÄÜÁ¿µ¯Ï»(lv1)", "ENERGY Magazine Level 1", "»Ä lv1");
	AddItemName(ENERGY_MAGAZINE_LV2, "¼Ó³¤Ê½ÄÜÁ¿µ¯Ï»(lv2)", "ENERGY Magazine Level 2", "»Ä lv2");
	AddItemName(ENERGY_MAGAZINE_LV3, "¼Ó³¤Ê½ÄÜÁ¿µ¯Ï»(lv3)", "ENERGY Magazine Level 3", "»Ä lv3");

	AddItemName(SHOTGUN_BOLT_LV1, "ö±µ¯Ç¹Ç¹Ë¨(lv1)", "Shotgun Bolt Level 1", "Óî lv1");
	AddItemName(SHOTGUN_BOLT_LV2, "ö±µ¯Ç¹Ç¹Ë¨(lv2)", "Shotgun Bolt Level 2", "Óî lv2");
	AddItemName(SHOTGUN_BOLT_LV3, "ö±µ¯Ç¹Ç¹Ë¨(lv3)", "Shotgun Bolt Level 3", "Óî lv3");
	AddItemName(STANDARD_STOCK_LV1, "±ê×¼Ç¹ÍÐ(lv1)", "Standard Stock Level 1", "³½ lv1");
	AddItemName(STANDARD_STOCK_LV2, "±ê×¼Ç¹ÍÐ(lv2)", "Standard Stock Level 2", "³½ lv2");
	AddItemName(STANDARD_STOCK_LV3, "±ê×¼Ç¹ÍÐ(lv3)", "Standard Stock Level 3", "³½ lv3");
	AddItemName(SNIPER_STOCK_LV1, "¾Ñ»÷Ç¹Ç¹ÍÐ(lv1)", "Sniper Stock Level 1", "ºé lv1");
	AddItemName(SNIPER_STOCK_LV2, "¾Ñ»÷Ç¹Ç¹ÍÐ(lv2)", "Sniper Stock Level 2", "ºé lv2");
	AddItemName(SNIPER_STOCK_LV3, "¾Ñ»÷Ç¹Ç¹ÍÐ(lv3)", "Sniper Stock Level 3", "ºé lv3");
	AddItemName(TURBOCHARGER, "ÎÐÂÖÔöÑ¹Æ÷", "Turbocharger", "»Æ");
	AddItemName(SELECTFIRE_RECEIVER, "Ñ¡ÔñÉä»÷Ä£Ê½Æ÷", "Selectfire Receiver", "µØ");
	AddItemName(PRECISION_CHOKE, "¾«×¼ÊøÆ÷", "Precision Choke", "ËÞ");
	AddItemName(anvilreceiver, "Disruptor Rounds", "Precision Choke", "ËÞ");
	AddItemName(doubletaptrigger, "Ë«ÉäÆ÷", "doubletaptrigger", "ËÞ");
	AddItemName(HAMMERPOINT_ROUNDS, "Hammerpoint Rounds", "Hammerpoint Rounds", "ËÞ");
	//AddItemName(89, "´©ÐÄÌÅÏß", "Skullpiercer Rifling", "ÁÐ");
	//Ðþ ÏûÑæÆ÷
	//SEProtectEnd();
}

BONEIDBYMODEL *GetBoneID(int ModelType)
{
	//SEProtectStartMutation();
	static BONEIDBYMODEL bone;

	if (ModelType == TYPE_MODEL1)				//Ñ°ÑªÁÔÈ®
	{
		bone.head = 10;					//Í·
		bone.neck = 9;					//²±×Ó
		bone.abdomen = 5;				//¸¹²¿
		bone.Left_shoulder = 49;		//×ó¼ç
		bone.Right_shoulder = 16;		//ÓÒ¼ç
		bone.Left_arm = 51;				//×ó±Û
		bone.Right_arm = 18;			//ÓÒ±Û
		bone.Left_arm_1 = 54;			//×ó±Û1
		bone.Right_arm_1 = 24;			//ÓÒ±Û1
		bone.Left_arm_2 = 93;			//×ó±Û2
		bone.Right_arm_2 = 88;			//ÓÒ±Û2
		bone.Left_knee = 94;			//×óÏ¥¸Ç
		bone.Right_knee = 90;			//ÓÒÏ¥¸Ç
		bone.Left_foot = 68;			//×ó½Å
		bone.Right_foot = 91;			//ÓÒ½Å

		return &bone;
	}

	else if (ModelType == TYPE_MODEL2)				//Ö±²¼ÂÞÍÓ
	{
		bone.head = 10;					//Í·
		bone.neck = 9;					//²±×Ó
		bone.abdomen = 5;				//¸¹²¿
		bone.Left_shoulder = 42;		//×ó¼ç
		bone.Right_shoulder = 15;		//ÓÒ¼ç
		bone.Left_arm = 46;				//×ó±Û
		bone.Right_arm = 19;			//ÓÒ±Û
		bone.Left_arm_1 = 49;			//×ó±Û1
		bone.Right_arm_1 = 21;			//ÓÒ±Û1
		bone.Left_arm_2 = 78;			//×ó±Û2
		bone.Right_arm_2 = 73;			//ÓÒ±Û2
		bone.Left_knee = 79;			//×óÏ¥¸Ç
		bone.Right_knee = 74;			//ÓÒÏ¥¸Ç
		bone.Left_foot = 81;			//×ó½Å
		bone.Right_foot = 76;			//ÓÒ½Å

		return &bone;
	}

	else if (ModelType == TYPE_MODEL3)				//ÃüÂö
	{
		bone.head = 10;					//Í·
		bone.neck = 9;					//²±×Ó
		bone.abdomen = 5;				//¸¹²¿
		bone.Left_shoulder = 39;		//×ó¼ç
		bone.Right_shoulder = 14;		//ÓÒ¼ç
		bone.Left_arm = 41;				//×ó±Û
		bone.Right_arm = 16;			//ÓÒ±Û
		bone.Left_arm_1 = 43;			//×ó±Û1
		bone.Right_arm_1 = 18;			//ÓÒ±Û1
		bone.Left_arm_2 = 68;			//×ó±Û2
		bone.Right_arm_2 = 63;			//ÓÒ±Û2
		bone.Left_knee = 70;			//×óÏ¥¸Ç
		bone.Right_knee = 65;			//ÓÒÏ¥¸Ç
		bone.Left_foot = 71;			//×ó½Å
		bone.Right_foot = 66;			//ÓÒ½Å

		return &bone;
	}

	else if (ModelType == TYPE_MODEL4)				//Ì½Â·Õß
	{
		bone.head = 10;					//Í·
		bone.neck = 9;					//²±×Ó
		bone.abdomen = 5;				//¸¹²¿
		bone.Left_shoulder = 27;		//×ó¼ç
		bone.Right_shoulder = 14;		//ÓÒ¼ç
		bone.Left_arm = 29;				//×ó±Û
		bone.Right_arm = 16;			//ÓÒ±Û
		bone.Left_arm_1 = 30;			//×ó±Û1
		bone.Right_arm_1 = 17;			//ÓÒ±Û1
		bone.Left_arm_2 = 70;			//×ó±Û2
		bone.Right_arm_2 = 66;			//ÓÒ±Û2
		bone.Left_knee = 71;			//×óÏ¥¸Ç
		bone.Right_knee = 67;			//ÓÒÏ¥¸Ç
		bone.Left_foot = 72;			//×ó½Å
		bone.Right_foot = 68;			//ÓÒ½Å

		return &bone;
	}

	else if (ModelType == TYPE_MODEL5)				//¶¯Á¦Ð¡×Ó(ÐèÒªÊÕ¼¯)
	{
		bone.head = 10;					//Í·
		bone.neck = 9;					//²±×Ó
		bone.abdomen = 5;				//¸¹²¿
		bone.Left_shoulder = 44;		//×ó¼ç
		bone.Right_shoulder = 15;		//ÓÒ¼ç
		bone.Left_arm = 46;				//×ó±Û
		bone.Right_arm = 17;			//ÓÒ±Û
		bone.Left_arm_1 = 48;			//×ó±Û1
		bone.Right_arm_1 = 19;			//ÓÒ±Û1
		bone.Left_arm_2 = 68;			//×ó±Û2
		bone.Right_arm_2 = 40;			//ÓÒ±Û2
		bone.Left_knee = 92;			//×óÏ¥¸Ç
		bone.Right_knee = 82;			//ÓÒÏ¥¸Ç
		bone.Left_foot = 89;			//×ó½Å
		bone.Right_foot = 84;			//ÓÒ½Å
		return &bone;
	}

	else if (ModelType == TYPE_MODEL6)				//¶ñÁé
	{
		bone.head = 10;					//Í·
		bone.neck = 9;					//²±×Ó
		bone.abdomen = 5;				//¸¹²¿
		bone.Left_shoulder = 40;		//×ó¼ç
		bone.Right_shoulder = 15;		//ÓÒ¼ç
		bone.Left_arm = 42;				//×ó±Û
		bone.Right_arm = 17;			//ÓÒ±Û
		bone.Left_arm_1 = 45;			//×ó±Û1
		bone.Right_arm_1 = 20;			//ÓÒ±Û1
		bone.Left_arm_2 = 96;			//×ó±Û2
		bone.Right_arm_2 = 91;			//ÓÒ±Û2
		bone.Left_knee = 97;			//×óÏ¥¸Ç
		bone.Right_knee = 92;			//ÓÒÏ¥¸Ç
		bone.Left_foot = 99;			//×ó½Å
		bone.Right_foot = 94;			//ÓÒ½Å

		return &bone;
	}

	else if (ModelType == TYPE_MODEL7)				//°à¼ÓÂÞ¶û
	{
		bone.head = 10;					//Í·
		bone.neck = 9;					//²±×Ó
		bone.abdomen = 5;				//¸¹²¿
		bone.Left_shoulder = 43;		//×ó¼ç
		bone.Right_shoulder = 15;		//ÓÒ¼ç
		bone.Left_arm = 46;				//×ó±Û
		bone.Right_arm = 18;			//ÓÒ±Û
		bone.Left_arm_1 = 49;			//×ó±Û1
		bone.Right_arm_1 = 20;			//ÓÒ±Û1
		bone.Left_arm_2 = 86;			//×ó±Û2
		bone.Right_arm_2 = 81;			//ÓÒ±Û2
		bone.Left_knee = 87;			//×óÏ¥¸Ç
		bone.Right_knee = 82;			//ÓÒÏ¥¸Ç
		bone.Left_foot = 89;			//×ó½Å
		bone.Right_foot = 84;			//ÓÒ½Å

		return &bone;
	}

	else if (ModelType == TYPE_MODEL8)				//ÇÖÊ´(ÐèÒªÊÕ¼¯)
	{
		bone.head = 10;					//Í·
		bone.neck = 9;					//²±×Ó
		bone.abdomen = 5;				//¸¹²¿
		bone.Left_shoulder = 39;		//×ó¼ç
		bone.Right_shoulder = 14;		//ÓÒ¼ç
		bone.Left_arm = 41;				//×ó±Û
		bone.Right_arm = 16;			//ÓÒ±Û
		bone.Left_arm_1 = 43;			//×ó±Û1
		bone.Right_arm_1 = 18;			//ÓÒ±Û1
		bone.Left_arm_2 = 68;			//×ó±Û2
		bone.Right_arm_2 = 63;			//ÓÒ±Û2
		bone.Left_knee = 70;			//×óÏ¥¸Ç
		bone.Right_knee = 65;			//ÓÒÏ¥¸Ç
		bone.Left_foot = 71;			//×ó½Å
		bone.Right_foot = 66;			//ÓÒ½Å

		return &bone;
	}

	else if (ModelType == TYPE_MODEL9)				//»ÃÏó
	{
		bone.head = 10;					//Í·
		bone.neck = 9;					//²±×Ó
		bone.abdomen = 5;				//¸¹²¿
		bone.Left_shoulder = 41;		//×ó¼ç
		bone.Right_shoulder = 14;		//ÓÒ¼ç
		bone.Left_arm = 43;				//×ó±Û
		bone.Right_arm = 16;			//ÓÒ±Û
		bone.Left_arm_1 = 45;			//×ó±Û1
		bone.Right_arm_1 = 19;			//ÓÒ±Û1
		bone.Left_arm_2 = 89;			//×ó±Û2
		bone.Right_arm_2 = 84;			//ÓÒ±Û2
		bone.Left_knee = 90;			//×óÏ¥¸Ç
		bone.Right_knee = 85;			//ÓÒÏ¥¸Ç
		bone.Left_foot = 92;			//×ó½Å
		bone.Right_foot = 87;			//ÓÒ½Å

		return &bone;
	}
	else
	{
		bone.head = 10;					//Í·
		bone.neck = 9;					//²±×Ó
		bone.abdomen = 5;				//¸¹²¿
		bone.Left_shoulder = 39;		//×ó¼ç
		bone.Right_shoulder = 14;		//ÓÒ¼ç
		bone.Left_arm = 41;				//×ó±Û
		bone.Right_arm = 16;			//ÓÒ±Û
		bone.Left_arm_1 = 43;			//×ó±Û1
		bone.Right_arm_1 = 18;			//ÓÒ±Û1
		bone.Left_arm_2 = 68;			//×ó±Û2
		bone.Right_arm_2 = 63;			//ÓÒ±Û2
		bone.Left_knee = 70;			//×óÏ¥¸Ç
		bone.Right_knee = 65;			//ÓÒÏ¥¸Ç
		bone.Left_foot = 71;			//×ó½Å
		bone.Right_foot = 66;			//ÓÒ½Å

		return &bone;
	}
	return NULL;
	//SEProtectEnd();
}

void CCheats::DrawBone(ACTOR_INFO *pAI)
{
	//SEProtectStartMutation();
	CBaseEntity* player = (CBaseEntity*)pAI->dwPtr;
	if (!player)
		return;
	Vector out[128];
	Vector2D out2D[128];
	GColor c;
	player->GetBoneMarx(out);
	c.SetGColor(0, 255, 255, 255);
	for (int i = 0; i < 128; i++)
	{
		I::Engine->W2S(out[i], out2D[i]);
	}
	BONEIDBYMODEL *bone = GetBoneID(pAI->modeltype);


	//	Í·->²±×Ó
	D->DrawLine(out2D[bone->head], out2D[bone->neck], c.GetRawGColor());

	//	×óÓÒËø¹Ç->×óÓÒ¼ç
	D->DrawLine(out2D[bone->neck], out2D[bone->Left_shoulder], c.GetRawGColor());
	D->DrawLine(out2D[bone->neck], out2D[bone->Right_shoulder], c.GetRawGColor());

	//	×óÓÒ¼ç->×óÓÒ±Û
	D->DrawLine(out2D[bone->Left_shoulder], out2D[bone->Left_arm], c.GetRawGColor());
	D->DrawLine(out2D[bone->Right_shoulder], out2D[bone->Right_arm], c.GetRawGColor());
	D->DrawLine(out2D[bone->Left_arm], out2D[bone->Left_arm_1], c.GetRawGColor());
	D->DrawLine(out2D[bone->Right_arm], out2D[bone->Right_arm_1], c.GetRawGColor());
	D->DrawLine(out2D[bone->Left_arm_1], out2D[bone->Left_arm_2], c.GetRawGColor());
	D->DrawLine(out2D[bone->Right_arm_1], out2D[bone->Right_arm_2], c.GetRawGColor());

	//	²±×Ó->¸¹²¿
	D->DrawLine(out2D[bone->neck], out2D[bone->abdomen], c.GetRawGColor());


	//	¸¹²¿->×óÓÒÏ¥¸Ç
	D->DrawLine(out2D[bone->abdomen], out2D[bone->Left_knee], c.GetRawGColor());
	D->DrawLine(out2D[bone->abdomen], out2D[bone->Right_knee], c.GetRawGColor());

	//	×óÓÒÏ¥¸Ç->×óÓÒ½Å
	D->DrawLine(out2D[bone->Left_knee], out2D[bone->Left_foot], c.GetRawGColor());
	D->DrawLine(out2D[bone->Right_knee], out2D[bone->Right_foot], c.GetRawGColor());
	D->DrawLine(out2D[bone->Left_foot], out2D[bone->Left_foot], c.GetRawGColor());
	D->DrawLine(out2D[bone->Right_foot], out2D[bone->Right_foot], c.GetRawGColor());

	//SEProtectEnd();


	/*
	Vector out[128];
	GetActor()->GetBone(pAI->dwPtr, pAI->orgin, out);
	Vector2D out2D[128];

	for (int i = 0; i < 128; i++)
	{
	if (world2screen(out[i], out2D[i]))
	{
	//GColor c;
	//c.SetGColor(0, 0, 0, 220);
	//DrawString(13, Vector2D(out2D[i].x, out2D[i].y), c.GetRawGColor(), true, true, "%d", i);
	}
	}


	GColor c;
	c.SetGColor(243, 107, 114, 255);

	//	Í·->²±×Ó
	D->DrawLine(out2D[BoneId::head], out2D[BoneId::neck], c.GetRawGColor());

	//	²±->×óÓÒËø¹Ç
	D->DrawLine(out2D[BoneId::neck], out2D[BoneId::Left_clavicle], c.GetRawGColor());
	D->DrawLine(out2D[BoneId::neck], out2D[BoneId::Right_clavicle], c.GetRawGColor());

	//	×óÓÒËø¹Ç->×óÓÒ¼ç
	D->DrawLine(out2D[BoneId::Left_clavicle], out2D[BoneId::Left_shoulder], c.GetRawGColor());
	D->DrawLine(out2D[BoneId::Right_clavicle], out2D[BoneId::Right_shoulder], c.GetRawGColor());

	//	×óÓÒ¼ç->×óÓÒ±Û
	D->DrawLine(out2D[BoneId::Left_shoulder], out2D[BoneId::Left_arm], c.GetRawGColor());
	D->DrawLine(out2D[BoneId::Right_shoulder], out2D[BoneId::Right_arm], c.GetRawGColor());
	D->DrawLine(out2D[BoneId::Left_arm], out2D[BoneId::Left_arm_1], c.GetRawGColor());
	D->DrawLine(out2D[BoneId::Right_arm], out2D[BoneId::Right_arm_1], c.GetRawGColor());
	D->DrawLine(out2D[BoneId::Left_arm_1], out2D[BoneId::Left_arm_3], c.GetRawGColor());
	D->DrawLine(out2D[BoneId::Right_arm_1], out2D[BoneId::Right_arm_3], c.GetRawGColor());

	//	²±×Ó->ÐØ
	D->DrawLine(out2D[BoneId::neck], out2D[BoneId::chest], c.GetRawGColor());

	//	ÐØ->¸¹²¿
	D->DrawLine(out2D[BoneId::chest], out2D[BoneId::abdomen], c.GetRawGColor());

	//	¸¹²¿->×óÓÒÏ¥¸Ç
	D->DrawLine(out2D[BoneId::abdomen], out2D[BoneId::Left_knee], c.GetRawGColor());
	D->DrawLine(out2D[BoneId::abdomen], out2D[BoneId::Right_knee], c.GetRawGColor());

	//	×óÓÒÏ¥¸Ç->×óÓÒ½Å
	D->DrawLine(out2D[BoneId::Left_knee], out2D[BoneId::Left_foot], c.GetRawGColor());
	D->DrawLine(out2D[BoneId::Right_knee], out2D[BoneId::Right_foot], c.GetRawGColor());
	D->DrawLine(out2D[BoneId::Left_foot], out2D[BoneId::Left_foot_1], c.GetRawGColor());
	D->DrawLine(out2D[BoneId::Right_foot], out2D[BoneId::Right_foot_1], c.GetRawGColor());
	*/
}

void CCheats::DrawHighlight(ACTOR_INFO *pAI, bool bIsVisible)
{
	//SEProtectStartMutation();
	static float fColor[3] = { 0.f, 1.f, 0.5f };
	if (bIsVisible)
	{
		fColor[0] = 0.f;
		fColor[1] = 250.f;
		fColor[2] = 154.f;
	}
	*(bool*)(pAI->dwPtr + 0x390) = true;
	*(bool*)(pAI->dwPtr + 0x310) = true;
	*(float*)(pAI->dwPtr + 0x2FC) = FLT_MAX;
	*(float**)(pAI->dwPtr + 0x1D0) = fColor;
	for (auto i = 0x2D0; i <= 0x2E8; i += 0x4)
		*(float*)(pAI->dwPtr + i) = FLT_MAX;
	//SEProtectEnd();
}

void BulletTrace(CBaseEntity* entity)
{
	//SEProtectStartMutation();
	Vector src3D, dst3D, forward;
	Vector2D  src, dst;
	trace_t tr;
	ZeroMemory(&tr, sizeof(tr));
	Ray_t ray;
	ZeroMemory(&ray, sizeof(ray));

	AngleVectors(entity->GetEyeAngles(), &forward);
	src3D = entity->GetBonePosition(10) - Vector(0, 0, 0);
	dst3D = src3D + (forward * Vars.Visuals.MaxSpot);
	ray.Init(src3D, dst3D);
	I::EngineTrace->TraceRay(ray, 0x640400B, &tr);
	//world2screen = (_GameWorldToSceen)(global::g_hGameImage + OFFSET::g_dwWorldToScreenEP);
	//if (!world2screen(src3D, src) || !world2screen(tr.endpos, dst))
	//	return;
	if (!I::Engine->W2S(src3D, src) || !I::Engine->W2S(tr.endpos, dst))
		return;
	GColor c;
	c.SetGColor(0, 255, 0, 255);
	D->DrawLine(src,dst, c.GetRawGColor());
	//D::DrawRect(dst.x - 3, dst.y - 3, 6, 6, color);
	//SEProtectEnd();
}
void DrawPlayerWeapon(CBaseEntity* entity)
{
	int id = entity->GetWeaponID();
	if (id == -1)
		return;
	string weapon = "unknown";
	switch (id)
	{
	case WEAPONID_G7Õì²éÇ¹:weapon = "G7"; break;
	case WEAPONID_R301:weapon = "R301"; break;
	}
}
void CCheats::ESP()
{
	//SEProtectStartMutation();

//	world2screen = (_GameWorldToSceen)(global::g_hGameImage + OFFSET::g_dwWorldToScreenEP);
	ACTOR_INFO *pLocalPlayer = GetActor()->GetLocalPlayer();
	if (pLocalPlayer == NULL)
		return;
	if (!Vars.Visuals.Enabled)
		return;

	for (int i = 0; i < GetActor()->Get()->GetCount(); i++)
	{
		ACTOR_INFO *pAI = GetActor()->Get()->GetData(i);
		if (pAI == NULL)
			continue;



		//	Íæ¼Ò
		if (pAI->type == TYPE_PLAYER && Vars.Visuals.PlayerEnable)
		{
			BONEIDBYMODEL *bone = GetBoneID(pAI->modeltype);
			if ((DWORD64)G::LocalPlayer == pAI->dwPtr)	//ÅÐ¶Ï×Ô¼º
				continue;
			if(!pAI->isAlive)
				continue;
			float fDis = (pAI->orgin - pLocalPlayer->orgin).Length() * 0.01905f;	//¾àÀë
			if (fDis > Vars.Visuals.MaxPlayerDis)
				continue;
			if (pAI->teamid == G::LocalPlayer->m_iTeamNum())
				continue;
			Vector2D screennike, screenHead;
			if (I::Engine->W2S(pAI->orgin, screennike) && I::Engine->W2S(pAI->head, screenHead))
			{
				//DbgPrintA("666666666666666666666666");
				GColor c;
				//	»­¿ò
				int iMiddle = (screennike.y - screenHead.y);
				int iWidth = iMiddle / 5;
				CBaseEntity* player = (CBaseEntity*)pAI->dwPtr;
				if (Vars.Visuals.Box)
				{
					/*
					Vector2D outHead;
					if (world2screen(player->GetBonePosition(BoneId::neck), outHead))
					{
					D->DrawCircle(outHead, 2, GColor::Red().GetRawGColor(), 16, 1);
					}
					*/
					if (fDis < 300)
					{
						if (player->IsVisible(10))
							c.SetGColor(243, 107, 114, 255);
						else
							c.SetGColor(255, 255, 0);

					}
					else
					{
						c.SetGColor(0, 128, 255);
					}
					

					D->DrawBox(Vector2D(screenHead.x - iWidth, screenHead.y), Vector2D(iWidth * 2, iMiddle), c.GetRawGColor(), 2.f);



					/*
					if (pAI->teamid == pLocalPlayer->teamid)
					{
					c.SetGColor(0, 128, 255);
					D->DrawBox(Vector2D(screenHead.x - iWidth, screenHead.y), Vector2D(iWidth * 2, iMiddle), c.GetRawGColor(), 2.f);
					}
					else
					{
					c.SetGColor(243, 107, 114, 255);
					D->DrawBox(Vector2D(screenHead.x - iWidth, screenHead.y), Vector2D(iWidth * 2, iMiddle), c.GetRawGColor(), 2.f);

					}*/

				}
				//¹Ç÷À
				if (Vars.Visuals.Skeleton)
				{
						DrawBone(pAI);
				}

				//·¢¹â
				if (Vars.Visuals.Glow)
				{
					DrawHighlight(pAI, player->IsVisible(bone->head));
				}

				//	Ãû×Ö

				if (Vars.Visuals.Name)
				{
					c.SetGColor(255, 255, 255, 220);
					D->DrawString(12, Vector2D(screennike.x, screennike.y - 35), c.GetRawGColor(), true, true, "%s", (pAI->name.c_str()));
				}

				//	»­ÑªÌõ
				if (Vars.Visuals.Health)
				{
					c.SetGColor(0, 0, 0, 220);
					D->DrawBox(Vector2D(screenHead.x + iWidth + 1, screenHead.y), Vector2D(4, iMiddle), c.GetRawGColor(), 1);
					c.SetGColor(181, 230, 29, 220);
					//	È¡°Ù·Ö±È
					float fHP = (float)pAI->health * 100 / (float)pAI->maxhealth;
					D->DrawFilledBox(Vector2D(screenHead.x + iWidth + 2, screenHead.y + 1 + (100 - fHP) / 100 * iMiddle), Vector2D(2, fHP / 100 * iMiddle - 1), c.GetRawGColor());

				}

				//»­¾àÀë
				if (Vars.Visuals.Distance)
				{
					c.SetGColor(255, 255, 255, 220);
					D->DrawString(12, Vector2D(screennike.x, screennike.y - 45), c.GetRawGColor(), true, true, "[%.fm]", fDis);
				}


				if (Vars.Visuals.Shield)
				{
					//	»­»¤¶Ü
					c.SetGColor(0, 0, 0, 220);
					D->DrawBox(Vector2D(screenHead.x + iWidth + 5, screenHead.y), Vector2D(4, iMiddle), c.GetRawGColor(), 1);
					c.SetGColor(0, 255, 255, 220);
					//	È¡°Ù·Ö±È
					float fFD = (float)pAI->shieldhealth * 100 / (float)pAI->shieldhealthmax;
					D->DrawFilledBox(Vector2D(screenHead.x + iWidth + 6, screenHead.y + 1 + (100 - fFD) / 100 * iMiddle), Vector2D(2, fFD / 100 * iMiddle - 1), c.GetRawGColor());
				}


				//	»­Ãé×¼µã
				if (Vars.Visuals.AimSpot)
					BulletTrace((CBaseEntity*)pAI->dwPtr);
			//	if (Vars.Visuals.Weapon)
			//		DrawPlayerWeapon((CBaseEntity*)pAI->dwPtr);
			}



		}
		//int centreX = m_rc.right / 2;
		//int centreY = m_rc.bottom / 2;

		//D->DrawCircle(Vector2D(centreX, centreY), Vars.Rage.FOV , GColor::White().GetRawGColor(), 16, 1);

		//	ÎïÆ·
		if (pAI->type == TYPE_ITEM && Vars.Visuals.ItemEnable)
		{
			float fDis = (pAI->orgin - pLocalPlayer->orgin).Length() * 0.01905f;	//¾àÀë
			if (fDis > Vars.Visuals.MaxItemDis)
				continue;
			Vector2D screen;
			float FontSize = 11.f;
			if (I::Engine->W2S(pAI->orgin, screen))
			{
				GColor c;
				
				
				if (pAI->itemtpye == ITEM_WEAPONS && Vars.Visuals.ItemWeapons)	//ÎäÆ÷
				{
					c.SetGColor(34, 177, 76, 220);
					if (g_ItemHash.count(pAI->nameid))
						D->DrawString(FontSize, Vector2D(screen.x, screen.y), c.GetRawGColor(), true, true, "[%.fm]%s", fDis, g_ItemHash[pAI->nameid].szCN);
					else
					{
						D->DrawString(FontSize, Vector2D(screen.x, screen.y), c.GetRawGColor(), true, true, "[%.fm]%d", fDis, pAI->nameid);
					}
				}
				if (pAI->itemtpye == ITEM_AMMO && Vars.Visuals.ItemAmmo)	//×Óµ¯
				{
					c.SetGColor(255, 127, 39, 220);
					if (g_ItemHash.count(pAI->nameid))
						D->DrawString(FontSize, Vector2D(screen.x, screen.y), c.GetRawGColor(), true, true, "[%.fm]%s", fDis, g_ItemHash[pAI->nameid].szCN);
					else
					{
						D->DrawString(FontSize, Vector2D(screen.x, screen.y), c.GetRawGColor(), true, true, "[%.fm]%d", fDis, pAI->nameid);
					}
				}

				if (pAI->itemtpye == ITEM_HEALING && Vars.Visuals.ItemHealing)	//ÖÎÁÆÎïÆ·
				{
					c.SetGColor(128, 255, 255, 220);
					if (g_ItemHash.count(pAI->nameid))
						D->DrawString(FontSize, Vector2D(screen.x, screen.y), c.GetRawGColor(), true, true, "[%.fm]%s", fDis, g_ItemHash[pAI->nameid].szCN);
					else
					{
						D->DrawString(FontSize, Vector2D(screen.x, screen.y), c.GetRawGColor(), true, true, "[%.fm]%d", fDis, pAI->nameid);
					}
				}

				if (pAI->itemtpye == ITEM_SHIELD && Vars.Visuals.ItemShield)	//·À»¤ÎïÆ·
				{
					c.SetGColor(128, 0, 255, 220);
					if (g_ItemHash.count(pAI->nameid))
						D->DrawString(FontSize, Vector2D(screen.x, screen.y), c.GetRawGColor(), true, true, "[%.fm]%s", fDis, g_ItemHash[pAI->nameid].szCN);
					else
					{
						D->DrawString(FontSize, Vector2D(screen.x, screen.y), c.GetRawGColor(), true, true, "[%.fm]%d", fDis, pAI->nameid);
					}
				}

				if (pAI->itemtpye == ITEM_GRENADES && Vars.Visuals.ItemGrenades)	//Í¶ÖÀÎïÆ·
				{
					c.SetGColor(255, 0, 0, 220);
					if (g_ItemHash.count(pAI->nameid))
						D->DrawString(FontSize, Vector2D(screen.x, screen.y), c.GetRawGColor(), true, true, "[%.fm]%s", fDis, g_ItemHash[pAI->nameid].szCN);
					else
					{
						D->DrawString(FontSize, Vector2D(screen.x, screen.y), c.GetRawGColor(), true, true, "[%.fm]%d", fDis, pAI->nameid);
					}
				}

				if (pAI->itemtpye == ITEM_SCOPES && Vars.Visuals.ItemScopes)	//Ãé×¼¾µ
				{
					c.SetGColor(255, 128, 192, 220);
					if (g_ItemHash.count(pAI->nameid))
						D->DrawString(FontSize, Vector2D(screen.x, screen.y), c.GetRawGColor(), true, true, "[%.fm]%s", fDis, g_ItemHash[pAI->nameid].szCN);
					else
					{
						D->DrawString(FontSize, Vector2D(screen.x, screen.y), c.GetRawGColor(), true, true, "[%.fm]%d", fDis, pAI->nameid);
					}
				}

				if (pAI->itemtpye == ITEM_ATTACHMENTS && Vars.Visuals.ItemAttachments)	//Åä¼þ
				{
					c.SetGColor(255, 255, 0, 220);
					if (g_ItemHash.count(pAI->nameid))
						D->DrawString(FontSize, Vector2D(screen.x, screen.y), c.GetRawGColor(), true, true, "[%.fm]%s", fDis, g_ItemHash[pAI->nameid].szCN);
					else
					{
						D->DrawString(FontSize, Vector2D(screen.x, screen.y), c.GetRawGColor(), true, true, "[%.fm]%d", fDis, pAI->nameid);
					}
				}
			}
		}
	}
	//SEProtectEnd();
}
void CCheats::Process()
{
//	//SEProtectStartMutation();
	if (I::Engine->IsInGame())
	{
		GetClientRect(global::g_hGameWnd, &m_rc);
		G::LocalPlayer = (CBaseEntity*)I::ClientEntList->GetClientEntity(I::Engine->GetLocalPlayerID());
		//G::LocalPlayer->GetEyePosition();
		DbgPrintA("LocalPlayer: %d %d %f ", G::LocalPlayer->IsReloading(), G::LocalPlayer->m_ammoInStockpile(), G::LocalPlayer->GetbulletSpeed());
		//DbgPrintA("LocalPlayer: %f %f %f ", G::LocalPlayer->GetEyePosition().x, G::LocalPlayer->GetEyePosition().y, G::LocalPlayer->GetEyePosition().z);
		//DbgPrintA("LocalPlayer2: %f %f %f ", G::LocalPlayer->GetViewAngles().x, G::LocalPlayer->GetViewAngles().y, G::LocalPlayer->GetViewAngles().z);
		GetActor()->Update();
		ESP();
	}
	else
		E::RageBot->m_ent = NULL;

//	//SEProtectEnd();
}
