#ifndef ASW_MARINEPROFILE_H
#define ASW_MARINEPROFILE_H
#pragma once

#include "asw_shareddefs.h"
#include "asw_marine_skills.h"
#include "responserules/response_types.h"

// This class describes all the fixed data about a particular marine profile
// e.g. the marine's name, class, voice, portraits, chatter lines, etc.

#define CHATTER_STRING_SIZE 64

#define NUM_SUB_CHATTERS 18		// max variations allowed for a chatter line

extern const char *const g_szMarineClassLabel[NUM_MARINE_CLASSES];
extern const char *const g_szMarineClassImage[NUM_MARINE_CLASSES];

enum ASW_Voice_Type
{
	ASW_VOICE_SARGE,
	ASW_VOICE_JAEGER,
	ASW_VOICE_WILDCAT,
	ASW_VOICE_WOLFE,
	ASW_VOICE_FAITH,
	ASW_VOICE_BASTILLE,
	ASW_VOICE_CRASH,
	ASW_VOICE_FLYNN,
	ASW_VOICE_VEGAS,

	ASW_VOICE_TYPE_TOTAL
};
ASW_Voice_Type GetASWVoiceType( const char *szVoiceType );
const char* GetVoiceShortName( ASW_Voice_Type voice );

// different chatter lines
enum {
	CHATTER_SELECTION = 0,
	CHATTER_SELECTION_INJURED = 1,
	CHATTER_USE = 2,
	CHATTER_IDLE = 3,
	CHATTER_FRIENDLY_FIRE = 4,
	CHATTER_FIRING_AT_ALIEN = 5,
	CHATTER_FOLLOW_ME = 6,
	CHATTER_HOLD_POSITION = 7,
	CHATTER_NEED_AMMO = 8,
	CHATTER_NO_AMMO = 9,
	CHATTER_MEDIC = 10,
	CHATTER_RELOADING = 11,
	CHATTER_SENTRY = 12,
	CHATTER_AMMO = 13,
	CHATTER_MEDKIT = 14,
	CHATTER_THANKS = 15,
	CHATTER_QUESTION = 16,
	CHATTER_SARGE = 17,
	CHATTER_JAEGER = 18,
	CHATTER_WILDCAT = 19,
	CHATTER_WOLFE = 20,
	CHATTER_FAITH = 21,
	CHATTER_BASTILLE = 22,
	CHATTER_CRASH = 23,
	CHATTER_FLYNN = 24,
	CHATTER_VEGAS = 25,
	CHATTER_SUPPLIES = 26,
	CHATTER_SUPPLIES_AMMO = 27,
	CHATTER_LOCKED_TERMINAL = 28,
	CHATTER_LOCKED_TERMINAL_CRASH = 29,
	CHATTER_LOCKED_TERMINAL_FLYNN = 30,
	CHATTER_LOCKED_TERMINAL_VEGAS = 31,
	CHATTER_HOLDING_POSITION = 32,
	CHATTER_HOLDING_NORTH = 33,
	CHATTER_HOLDING_SOUTH = 34,
	CHATTER_HOLDING_EAST = 35,
	CHATTER_HOLDING_WEST = 36,
	CHATTER_GOT_POINT = 37,
	CHATTER_GOT_REAR = 38,
	CHATTER_REQUEST_SEAL_DOOR = 39,
	CHATTER_REQUEST_CUT_DOOR = 40,
	CHATTER_REQUEST_SHOOT_DOOR = 41,
	CHATTER_CUTTING_DOOR = 42,
	CHATTER_SEALING_DOOR = 43,
	CHATTER_BIOMASS = 44,
	CHATTER_TIME_TO_LEAVE = 45,
	CHATTER_WATCH_OUT = 46,
	CHATTER_SHIELDBUG = 47,
	CHATTER_SHIELDBUG_HINT = 48,
	CHATTER_PARASITE = 49,
	CHATTER_INFESTED = 50,
	CHATTER_EGGS = 51,
	CHATTER_GRENADE = 52,
	CHATTER_ALIEN_TOO_CLOSE = 53,
	CHATTER_MAD_FIRING = 54,
	CHATTER_BREACHED_DOOR = 55,
	CHATTER_MARINE_DOWN = 56,
	CHATTER_PAIN_SMALL = 57,
	CHATTER_PAIN_LARGE = 58,
	CHATTER_DIE = 59,
	CHATTER_ON_FIRE = 60,
	CHATTER_COMPLIMENTS = 61,
	CHATTER_STIM_NOW = 62,
	CHATTER_IMPATIENCE = 63,

	CHATTER_COMPLIMENTS_JAEGER = 64,	// sarge only
	CHATTER_COMPLIMENTS_SARGE = 65,	// jaeger only
	CHATTER_COMPLIMENTS_WILDCAT = 66,	// wolfe only
	CHATTER_COMPLIMENTS_WOLFE = 67,	// wildcat only
	CHATTER_COMPLIMENTS_CRASH = 68,	// wildcat only

	CHATTER_HEALING = 69,										// class specific..
	CHATTER_MEDS_LOW = 70,
	CHATTER_MEDS_NONE = 71,

	CHATTER_HACK_STARTED = 72,
	CHATTER_HACK_LONG_STARTED = 73,
	CHATTER_HACK_HALFWAY = 74,
	CHATTER_HACK_FINISHED = 75,
	CHATTER_HACK_BUTTON_FINISHED = 76,

	CHATTER_SCANNER = 77,
	CHATTER_SCANNER_MULTIPLE = 78,

	CHATTER_MINE_DEPLOYED = 79,

	CHATTER_SYNUP_SPOTTED = 80,		// crash/vegas only			// conversations...
	CHATTER_SYNUP_REPLY = 81,		// faith/bastille only
	CHATTER_CRASH_COMPLAIN = 82,
	CHATTER_CRASH_COMPLAIN_REPLY = 83,
	CHATTER_MEDIC_COMPLAIN = 84,
	CHATTER_MEDIC_COMPLAIN_REPLY = 85,
	CHATTER_HEALING_CRASH = 86,		// bastille only
	CHATTER_HEALING_CRASH_REPLY = 87,
	CHATTER_TEQUILA_START = 88,		// Vegas only
	CHATTER_TEQUILA_REPLY = 89,
	CHATTER_TEQUILA_REPLY_SARGE = 90, // Vegas only
	CHATTER_TEQUILA_REPLY_JAEGER = 91, // Vegas only
	CHATTER_TEQUILA_REPLY_WILDCAT = 92, // Vegas only
	CHATTER_TEQUILA_REPLY_WOLFE = 93, // Vegas only
	CHATTER_TEQUILA_REPLY_FAITH = 94, // Vegas only
	CHATTER_TEQUILA_REPLY_BASTILLE = 95, // Vegas only
	CHATTER_CRASH_IDLE = 96,		// crash only
	CHATTER_CRASH_IDLE_REPLY = 97,	// sarge/crash only
	CHATTER_SERIOUS_INJURY = 98,		// faith/bastille only
	CHATTER_SERIOUS_INJURY_REPLY = 99,		// all marines
	CHATTER_SERIOUS_INJURY_FOLLOW_UP = 100,   // faith/bastille only
	CHATTER_STILL_BREATHING = 101,		// jaeger only
	CHATTER_STILL_BREATHING_REPLY = 102,
	CHATTER_SARGE_IDLE = 103,		// sarge only
	CHATTER_SARGE_IDLE_REPLY = 104,
	CHATTER_BIG_ALIEN_DEAD = 105,		// crash only
	CHATTER_BIG_ALIEN_REPLY = 106,
	CHATTER_AUTOGUN = 107,	// wildcat/wolfe only
	CHATTER_AUTOGUN_REPLY = 108,
	CHATTER_WOLFE_BEST = 109,	// wolfe only
	CHATTER_WOLFE_BEST_REPLY = 110,	// wolfe only
	CHATTER_FIRST_BLOOD_START = 111,	// vegas only
	CHATTER_FIRST_BLOOD_WIN = 112,	// vegas only
	CHATTER_SARGE_JAEGER_CONV_1 = 113,
	CHATTER_SARGE_JAEGER_CONV_1_REPLY = 114,
	CHATTER_SARGE_JAEGER_CONV_2 = 115,
	CHATTER_SARGE_JAEGER_CONV_2_REPLY = 116,
	CHATTER_WILDCAT_KILL = 117,
	CHATTER_WILDCAT_KILL_REPLY_AHEAD = 118,
	CHATTER_WILDCAT_KILL_REPLY_BEHIND = 119,
	CHATTER_WOLFE_KILL = 120,
	CHATTER_WOLFE_KILL_REPLY_AHEAD = 121,
	CHATTER_WOLFE_KILL_REPLY_BEHIND = 122,			// 123rd chatter line

	CHATTER_MISC = 123,								// 124th chatter line

	NUM_CHATTER_LINES = 124,
};

enum ASW_Pronouns
{
	ASW_PRONOUNS_HE,
	ASW_PRONOUNS_SHE,
	ASW_PRONOUNS_IT_ROBOT,
	ASW_PRONOUNS_IT_ANIMAL,
};

class CASW_Marine_Profile
{
public:
	// this profile's position in the list of profiles
	int m_ProfileIndex;
	ASW_Marine_Class m_iMarineClass;
	ASW_Voice_Type m_VoiceType;
	int m_iDefaultLoadoutIndex;

	// Accessors
	inline bool CanHack( void );						///< Can this character type hack computers? (In general -- the marine may be unable to do it at this moment due to combat, distance, etc)
	inline bool CanScanner( void );						///< Does this character type have a scanner?
	inline bool CanUseTechWeapons( void );				///< Can use tech-specific weapons
	inline bool HasHackSkill( void );					///< Can hack faster than a normal marine and you can do GetSkillBasedValueByMarine to find out the skill score
	inline bool HasTechIcon( void );
	inline bool CanUseFirstAid( void );
	inline bool CanUseAutogun( void );

	void SetMarineClass( ASW_Marine_Class marineClass );
	ASW_Marine_Class GetMarineClass();

	// personnel data
	const char *GetShortName() { return m_ShortName; }

	char	m_RankName[24];
	char	m_Bio[24];
	char	m_FirstName[24];
	char	m_LastName[24];
	char	m_ShortName[24];
	// name used for  portrait vmt files
	char	m_PortraitName[24];
	// is the shortname a nickname to be put in quotes between 1st and last?
	bool	m_bNickname;
	int		m_Age;
	ASW_Pronouns m_Pronouns;
	// used for the "who" fact
	char	m_ResponseRulesName[24];

	// model
	const char *GetModelName() { return m_ModelName; }
	int GetSkinNum() { return m_SkinNum; }
	char	m_ModelName[64];
	int		m_SkinNum;

	// portraits
	int m_nPortraitTextureID{ -1 }; // regular small portrait texture ID
	int m_nPortraitLitTextureID{ -1 };
	int m_nClassTextureID{ -1 }; // class icon

	// chatter stuff
	ASW_Voice_Type GetVoiceType();
	void SetVoiceType( ASW_Voice_Type vt );
	char m_Chatter[NUM_CHATTER_LINES][CHATTER_STRING_SIZE];
	void InitChatterNames( const char *szMarineName );
	int m_iChatterCount[NUM_CHATTER_LINES];	// how many speech lines this marine has for each chatter type
#ifndef CLIENT_DLL
	void PrecacheSpeech( CBaseEntity *pEnt );
	float m_fChatterChance[NUM_CHATTER_LINES];
	float m_fChatterDuration[NUM_CHATTER_LINES][NUM_SUB_CHATTERS];	// how long each sub chatter line is
	void SaveSpeechDurations( CBaseEntity *pEnt );
	ResponseRules::CriteriaSet::CritSymbol_t m_nResponseRulesName;
#endif

	ASW_Skill GetSkillMapping( int nSkillSlot );
	int GetStaticSkillPoints( int nSkillSlot );

	void LoadTextures();	// loads the portrait textures
};

class CASW_Marine_ProfileList
{
public:
	void PrecacheSpeech(CBaseEntity* pEnt);
#ifndef CLIENT_DLL
	void SaveSpeechDurations(CBaseEntity *pEnt);
#endif

	CASW_Marine_Profile *GetProfile( int i )
	{
		if ( i >= 0 && i < ASW_NUM_MARINE_PROFILES )
			return &m_Profiles[i];

		return NULL;
	}

	CASW_Marine_Profile m_Profiles[ASW_NUM_MARINE_PROFILES];
	bool m_bInitOnce{ false };
};

extern CASW_Marine_ProfileList* MarineProfileList();

inline bool CASW_Marine_Profile::CanHack( void )
{
	extern ConVar rd_hackall;
	return GetMarineClass() == MARINE_CLASS_TECH || rd_hackall.GetBool();
}

inline bool CASW_Marine_Profile::HasHackSkill( void )
{
	return GetMarineClass() == MARINE_CLASS_TECH;
}

inline bool CASW_Marine_Profile::CanScanner( void )
{
	return GetMarineClass() == MARINE_CLASS_TECH;
}

inline bool CASW_Marine_Profile::CanUseTechWeapons( void )
{
	return GetMarineClass() == MARINE_CLASS_TECH;
}

inline bool CASW_Marine_Profile::HasTechIcon( void ) 
{
	return GetMarineClass() == MARINE_CLASS_TECH;
}

inline bool CASW_Marine_Profile::CanUseFirstAid( void ) 
{
	return GetMarineClass() == MARINE_CLASS_MEDIC;
}

inline bool CASW_Marine_Profile::CanUseAutogun( void )
{
	return GetMarineClass() == MARINE_CLASS_SPECIAL_WEAPONS;
}
#endif /* ASW_MARINEPROFILE_H */
