#ifndef _IBLAST_
# define _IBLAST_

#define NAME "! iBlast !"
#define SHOT 1
#define SHOTMOB 2
#define MAZZELTOF 3
#define PEPELOUNI 4
#define EXPLOSION 5
#define BACKG 6
#define PLAYER 7

namespace IBLAST
{
	enum{	
		WIDTH = 800,
		HEIGHT = 600, 
		BITPIXEL = 32,
		BLIFE = 90,
		KeyUp = 293,
		KeyDown = 294,
		KeyLeft = 291,
		KeyRight = 292,
		KeySpace = 277,
		KeyR = 114,
	};
	enum	PACKS_ROOM { _CONNECTION = 1, _DISCONNECTION = 3, _OKKO = 5, _NEW_PLAYER = 7, _PLAYER = 9 , _PLAYER_LEAVE = 11};
	enum	PACKS_GAME { _LAUNCH_GAME = 13, _LEAVE_GAME = 15, _END_GAME = 17, _NEW_MASTER = 19 };
	enum	PACKS_MOB { _POS_HERO = 21, _POS_SHOT = 23, _POS_ENN_I = 25, _POS_ENN_II = 27, _COLL_MOB_SHOT = 29, _COLL_MOB_HERO = 31, _COLL_HERO_SHOT = 33, _SCORE = 35, _POS_SHOT_MOB = 37 };
	enum	MACROS { _MAX_BUFF_LEN = 512, _MAX_PLAYER = 4, _MAX_TH = 2, _MAX_NAME_LEN = 16 };
	enum	ERRORS { _MAX_ERROR_LEN = 47, _ERR_LAUNCHED_LEN = 30, _ERR_NAME_TAKEN_LEN = 38 };

/////////////////////////////////////////
// Definition des differents paquets ROOM

	// Packets Client

	typedef struct	PackConnection
	{
		int			_type;
		char		_playerName[_MAX_NAME_LEN];
	}				PackConnection;

	typedef struct	PackDisconnection
	{
		int			_type;
		char		_playerName[_MAX_NAME_LEN];
	}				PackDisconnection;

	typedef struct	PackPlayerLeave
	{
		int			_type;
		char		_playerName[_MAX_NAME_LEN];
	}				PackPlayerLeave;

	// Packets Serveur

	typedef struct	PackOkKo
	{
		int			_type;
		bool		_ok;
		bool		_master;
		char		_mess[_MAX_ERROR_LEN];
	}				PackOkKo;

	typedef struct	PackNewPlayer
	{
		int			_type;
		char		_playerName[_MAX_NAME_LEN];
	}				PackNewPlayer;

	typedef struct	PackPlayer
	{
		int			_type;
		bool		_master;
		char		_playerName[_MAX_NAME_LEN];
	}				PackPlayer;

	typedef struct	PackNewMaster
	{
		int			_type;
		char		_playerName[_MAX_NAME_LEN];
	}				PackNewMaster;

/////////////////////////////////////////
// Definition des differents paquets GAME

	// Packets Clients

	typedef struct	PackLaunchGame
	{
		int			_type;
		char		_playerName[_MAX_NAME_LEN];
	}				PackLaunchGame;

	typedef struct	PackLeaveGame
	{
		int			_type;
		char		_playerName[_MAX_NAME_LEN];
	}				PackLeaveGame;

	typedef struct	PackEndGame
	{
		int			_type;
		char		_playerName[_MAX_NAME_LEN];
	}				PackEndGame;

	// Packets Mobs

	typedef struct	PackPosHero
	{
		int			_type;
		char		_playerName[_MAX_NAME_LEN];
		int			_weapon;
		float		_x;
		float		_y;
		int			_life;
	}				PackPosHero;

	typedef struct	PackPosShot
	{
		int			_type;
		int			_id;
		char		_playerName[_MAX_NAME_LEN];
		int			_x;
		int			_y;
	}				PackPosShot;

	typedef struct	PackPosShotMob
	{
		int			_type;
		int			_typeMob;
		int			_id;
		int			_idMob;
		int			_x;
		int			_y;
	}				PackPosShotMob;

	typedef struct	PackPosEnnI
	{
		int			_type;
		int			_id;
		float		_x;
		float		_y;
		int			_hp;
	}				PackPosEnn1;

	typedef struct	PackPosEnnII
	{
		int			_type;
		int			_id;
		float		_x;
		float		_y;
		int			_hp;
	}				PackPosEnn2;

	typedef struct	PackCollMobShot
	{
		int			_type;
		int			_idMob;
		int			_idShot;
		char		_playerName[_MAX_NAME_LEN];
	}				PackCollMobShot;

	typedef struct	PackCollHeroShot
	{
		int			_type;
		int			_idMob;
		int			_idShot;
		int			_playerName[_MAX_NAME_LEN];
	}				PackCollHeroShot;

	typedef struct	PackCollMobHero
	{
		int			_type;
		int			_idMob;
		char		_playerName[_MAX_NAME_LEN];
	}				PackCollMobHero;

	typedef struct	PackScore
	{
		int			_type;
		int			_score;
		char		_playerName[_MAX_NAME_LEN];
	}				PackScore;

};

#endif
