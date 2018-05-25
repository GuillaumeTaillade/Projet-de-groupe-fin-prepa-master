#include <SFML\Graphics.h>
#include <SFML\Audio.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <math.h>

#pragma region Defines

#ifndef PI
#define PI 3.14159265358979323846264338327
#endif

#ifndef FRAMERATE 60
#define FRAMERATE 60
#endif // !FRAMERATE 60

#ifndef WINDOW_WIDTH 1920
#define WINDOW_WIDTH 1920
#endif // !WINDOW_WIDTH 1920

#ifndef WINDOW_HEIGHT 1080
#define WINDOW_HEIGHT 1080
#endif // !WINDOW_HEIGHT 1080

#ifndef BUILD_OPENING_RADIUS 100
#define BUILD_OPENING_RADIUS 100
#endif // !BUILD_OPENING_RADIUS 100

#ifndef BUILD_SPEED_FACTOR 200
#define BUILD_SPEED_FACTOR 200
#endif // !BUILD_SPEED_FACTOR 200

#ifndef BUILD_SPEED_FACTOR 200
#define BUILD_SPEED_FACTOR 200
#endif // !BUILD_SPEED_FACTOR 200

#ifndef TOWER_WIDTH 80
#define TOWER_WIDTH 80
#endif // !TOWER_WIDTH 80

#ifndef TOWER_HEIGHT 160
#define TOWER_HEIGHT 160
#endif // !TOWER_HEIGHT 160

#define SIZE_TEXT 25

#define WHITE_CELL_SPD_FACTOR 2

#define MAX_LIST_ENNEMY_PATH_POINT 2

#pragma region ENNEMY

#pragma region ENNEMY BULLET

#define CHOLESTEROL_BULLET_SPEED 300
#define CHOLESTEROL_BULLET_ACCELERATION 10

#pragma endregion ENNEMY BULLET

#pragma region BARRE DE VIE ENNEMI

#define LIFEBAR_MAX_SIZE_X 60
#define LIFEBAR_SIZE_Y 6

#pragma endregion BARRE DE VIE ENNEMI

#pragma region ANIMATION

#define CHOLESTEROL_WIDTH 75
#define CHOLESTEROL_HEIGHT 120
#define CHOLESTEROL_TIME_BETWEEN_ANIMATION 0.5f
#define CHOLESTEROL_NBR_FRAME_X 1
#define CHOLESTEROL_NBR_FRAME_Y 4

#define CANCER_WIDTH 30
#define CANCER_HEIGHT 36
#define CANCER_TIME_BETWEEN_ANIMATION 0.5f
#define CANCER_NBR_FRAME_X 4
#define CANCER_NBR_FRAME_Y 1

#define CAILLOT_WIDTH 100
#define CAILLOT_HEIGHT 123
#define CAILLOT_TIME_BETWEEN_ANIMATION 0.5f
#define CAILLOT_NBR_FRAME_X 4
#define CAILLOT_NBR_FRAME_Y 1

#pragma endregion ANIMATION

#pragma region STATS

#define CHOLESTEROL_SPEED 125
#define CHOLESTEROL_DEG 5 // dégats quand il est gros
#define CHOLESTEROL_HP 10
#define CHOLESTEROL_MONEY_VALUE 125

#define CANCER_SPEED 200
#define CANCER_DEG 1
#define CANCER_HP 2
#define CANCER_MONEY_VALUE 25

#define CAILLOT_SPEED 75
#define CAILLOT_DEG 10
#define CAILLOT_HP 25
#define CAILLOT_MONEY_VALUE 250

#pragma endregion STATS

#define CAILLOT_TIME_BETWEEN_ATTACK 5 //temps minimun entre chaque attaque
#define CHOLESTEROL_TIME_BETWEEN_ATTACK 5 //temps minimun entre chaque attaque

#define CAILLOT_NBR_TOWER_BETWEEN_ATTACK 2 // Nombre de tour a passer avant de pouvoir attaquer
#define CHOLESTEROL_NBR_TOWER_BETWEEN_ATTACK 2 // Nombre de tour a passer avant de pouvoir attaquer

#define CAILLOT_CONTROL_RADIUS 80
#define CAILLOT_GUARD_RADIUS 15
#define CANCER_CONTROL_RADIUS 80
#define CANCER_GUARD_RADIUS 15
#define CHOLESTEROL_CONTROL_RADIUS 80
#define CHOLESTEROL_GUARD_RADIUS 15

#define TIME_BETWEEN_WAVE 5

#define DETECTION_SLOT_RADIUS 40
#define DETECTION_POSITION_RADIUS 150
#define CONTROL_RADIUS 80
#define GUARD_RADIUS 25

#define ENNEMY_VARIANT_SPAWN 10

#define ENNEMY_ACCELERATION 5 // ACCELERATION EN PIXEL DE L'ENNEMI
#define ANGLE_ROTATION 30 // angle de rotation lorsque l'ennemi veut esquiver un obstacle

#define ANGLE_HAUT_DROIT 315
#define ANGLE_HAUT_GAUCHE 225
#define ANGLE_BAS_GAUCHE 135
#define ANGLE_BAS_DROIT 45

#define ANGLE_VARIANT_ISO 17 // correction iso applique aux ngles de bases
#define ANGLE_VARIATION 15 // angle de la zone situé devant l'entité
#define ANGLE_INCREASE 10

#define ENNEMY_TIME_SINCE_LAST_ANIMATION 0.5f // temps entre chaque frame d'animation d'un ennemie
#define ENNEMY_WIDTH 60 // Largeur de l'ennemi
#define ENNEMY_HEIGHT 50 // Hauteur de l'ennemi

#define TIME_BETWEEN_VARIATION 1

#define TIME_BETWEEN_ENNEMY_SPAWN 0.2

#define ENNEMY_DIST_FROM_TARGET_TO_DELETE 100

#pragma endregion ENNEMY

#pragma region ENNEMY PATH POINT

#define SIZE_PATH_POINT 10

#pragma endregion ENNEMY PATH POINT

#pragma region WHITE_CELLS

#define WHITE_CELL_WIDTH 52
#define WHITE_CELL_HEIGHT 50
#define WHITE_CELL_FRAMES 15
#define WHITE_CELL_ANIM_SPEED 0.03
#define WHITE_CELL_FIELD_OF_VIEW_RADIUS 350
#define WHITE_CELL_AREA_DAMAGE_RADIUS 150
#define WHITE_CELL_CREATE_COOLDOWN 2

#pragma endregion WHITE_CELLS

#pragma region TOWERS

#define TOWER1_DAMAGES 0.5
#define TOWER2_DAMAGES 0.2
#define TOWER3_DAMAGES 5

#define TOWER1_HP 100
#define TOWER2_HP 100
#define TOWER3_HP 100

#define TOWER1_WIDTH 100
#define TOWER1_HEIGHT 102

#define TOWER2_WIDTH 83
#define TOWER2_HEIGHT 74
#define DOT_FREQUENCY 1

#define TOWER3_WIDTH 88
#define TOWER3_HEIGHT 86

#define TOWER1_COST 100
#define TOWER1_UPGRADE_COST 180

#define TOWER2_COST 150
#define TOWER2_UPGRADE_COST 270

#define TOWER3_COST 250
#define TOWER3_UPGRADE_COST 450

#define RESELL_FACTOR 0.6f

#define SLOWING_FACTOR 0.5f

#pragma endregion TOWERS

#pragma region BUTTONS

#define BUTTON_SPRITE_SIZE 60
#define MUSIC_BUTTON_DISTANCE 70
#define FX_BUTTON_DISTANCE 140
#define PAUSE_BUTTON_DISTANCE 210
#define BUTTON_SPEED 5

#pragma endregion BUTTONS

#pragma region MENU

#define LABEL_MASK_WIDTH 440
#define LABEL_MASK_HEIGHT 640

#pragma endregion MENU

#pragma endregion Defines

#pragma region enum
typedef enum e_NameLevel t_NameLevel;
enum e_NameLevel
{
	TEST = 0,
	ESTOMAC,
	COEUR
};

typedef enum e_EnnemyPathPointType t_EnnemyPathPointType;
enum e_EnnemyPathPointType
{
	SIMPLE = 0,
	PATH1 = 1,
	PATH2 = 2,
	RANDOM = 3,
	UNI = 4
};

typedef enum e_TowerType t_TowerType;
enum e_TowerType
{
	TYPE1 = 1,
	TYPE2,
	TYPE3,
	NONE = 99,
};

typedef enum e_TowerLevel t_TowerLevel;

enum e_TowerLevel
{
	NORMAL = 0,
	UPGRADED,
};

typedef enum e_EnemyType t_EnemyType;

enum e_EnemyType
{
	CANCER = 1,
	CHOLESTEROL,
	CAILLOT
};

typedef enum e_EnemySize t_EnemySize;

enum e_EnemySize
{
	BIG = 0,
	MEDIUM,
	SMALL
};

typedef enum e_DIRECTION DIRECTION;

enum e_DIRECTION
{
	DOWN_RIGHT,
	DOWN_LEFT,
	UP_LEFT,
	UP_RIGHT
};

typedef enum e_inGameMenuState t_inGameMenuState;

enum e_inGameMenuState
{
	IS_CLOSED = 0,
	IS_OPENING,
	IS_OPENED,
	IS_CLOSING,
};

typedef enum e_buttonState t_buttonState;

enum e_buttonState
{
	IS_OFF = 0,
	IS_ON,
};

typedef enum e_GameState t_GameState;

enum e_GameState
{
	MENU = 0,
	SAVE_SELECTOR,
	LEVEL_SELECTOR,
	GAME,
	VICTORY,
	DEFEAT,
	INTRO,
};

typedef enum e_mainMenuState t_mainMenuState;

enum e_mainMenuState
{
	ON_LOGO = 0,
	ON_LOGO_TRANSITION,
	ON_START,
	ON_START_TRANSITION,
	ON_START_LEVEL_SELECTOR,
	ON_CREDITS,
	ON_EXIT,
};

typedef enum e_introState t_introState;

enum e_introState
{
	IS_GAME_MOVING = 0,
	IS_ACADEMY_MOVING,
	IS_LOGO_GROWING,
	IS_LOGO_BEATING,
};

#pragma endregion enum

#pragma region structures

#pragma region ENNEMY

typedef struct s_Ennemy t_Ennemy;
struct s_Ennemy
{
	int iMoneyValue;

	sfSprite* sp_Ennemy; // sprite de l'entité
	sfVector2f vScale; // sert principalement pour le cholesterol
	sfVector2f vOrigin; // origin de l'ennemi
	sfVector2f vCurrentPosition; // position de l'ennemi
	sfVector2f vSeek; // le seek 
	sfVector2f vSteering; // le steering
	sfVector2f vCurrentVelocity; // vélocité de l'ennemi
	sfVector2f vNextPosToTarget; // point suivant que l'ennemi doit viser (maps actuelles)
	sfVector2f vTargetPostion; // position visé par l'ennemi
	sfVector2f vSpawnPosition; // Position de spawn de l'ennemi
	float fAngleSprite; // angle du sprite
	float fCurrentAngleDirection; // angle de direction actuel
	float fDesiredAngleDirection; // angle de direction voulue
	float fSpeed;
	float fSpeedMax;
	int iNextPosToTarget;

	int iRandSpawnDirectionVariation; // variable aléatoire sur l'ajout de posiiton de spawn
	int iRandSpawnValueVariation; // variation de la position de l'ennemi quand il spawn
	int iStartPos; // choix de la position de départ de l'ennemi

				   /*despawn*/
	int iDespawn;
	float fTimeSinceStartDespawn;

	/*manage collision*/
	float fControlRadius;
	float fGuardRadius;
	float fTimeCurrentVertex;
	float fTimeSinceVertex;
	float fTimeStartVertex;
	sfVector2f vCurrentDirection;
	sfVector2f vNormalizeDirection;
	sfVector2f vControlPoint;
	sfVector2f vLeftStartPoint;
	sfVector2f vRightStartPoint;
	sfVector2f vLeftControlPoint;
	sfVector2f vRightControlPoint;
	sfVector2f vSideRightControlPoint;
	sfVector2f vSideLeftControlPoint;
	int iIsColliding;
	int iCollideControl;
	int iCollideControlLeft;
	int iCollideControlRight;
	int iCollideControlSideLeft;
	int iCollideControlSideRight;
	float fCollideIncrementation;

	/*gestion animation*/
	sfIntRect animRect; // Rectnagle d'animation de l'ennemi
	DIRECTION dirState; // direction de l'ennemie, gère l'axe y dans la découpe de la texture (voir enum ENNEMY_DIRECTION)
	float fTimeSinceLastAnimation; // temps depuis la dernière frame d'animation
	float fTimeBetweenAnimation; //Temps entre chaque frame d'animation définit pour l'ennemi en question
	int iNbrFrameX; // nombre d'images dans la texture en x
	int iNbrFrameY; // nombre d'images dans la texture en y
	int iAnimationFrameX; // frame d'animation en x
	int iAnimationFrameY; // frame d'animation en y

	sfColor Color_ToCheck;
	int iOrientation; // Variable permettant de régler l'orientation de l'ennemi en fonnction de la couleur
	int iRandDirection; // utiliser pour déterminer la direction aléatoire de l'ennemi
	int iRandDirectionIsChosen;
	int iRandVariation; // choisit de quel coté va s'orienter l'ennemi a chaque frame

	int Type; // type de l'ennemie
	float Hp; // vie
	float HpMax; // nombre max de pv 
	int Deg; // Points de dégats
	int Def; // résistance physique

	int iSize; // taille de l'ennemi (cholesterol)


			   /*fond noir barre*/
	sfRectangleShape* RectangleShapeBack;
	sfVector2f vSizeRectangleShapeBack;
	sfVector2f vPositionRectangleShapeBack;
	sfVector2f vOriginRectangleShapeBack;

	/*barre de vie*/
	sfRectangleShape* RectangleShape;
	sfVector2f vSizeRectangleShape;
	sfVector2f vPositionRectangleShape;
	sfVector2f vOriginRectangleShape;

	sfFloatRect boundingBox;

	float fWanderAngle;
	float fTimeSinceLastVariation;
	sfVector2f vWanderCenter;
	sfVector2f vWanderDirection;

	/*facteur de vitesse*/
	float fSpeedFactor;

	/*dommages tour 2*/
	float tStartDOT;
	float tSinceDOT;
	float tCurrentDOT;
	/*ATTAQUE*/ //GUILLAUME

	int iIsAttack; // actif si l'ennemi est en train d'attaquer
	int iTowerToAttackId;
	int iTowerIsChosen;
	sfVector2f vPosTowerToAttack;
	sfVector2f vDistToTowerDetectionPos; // distance entre l'ennemi et la position de détection du slot
	sfBool EnnemyIsInTheDetectionZone; // actif si l'ennemi est présent dans la zone de détection
	int iNbrTowerBetweenAttack; // Nombre de tour que l'ennemi passe entre chaque attaque
	int iNbrTowerSinceLastAttack; // Nombre de tour passe depuis la dernière attaque
	float fTimeBetweenAttack; // Temps entre chaque attaque
	float fTimeSinceLastAttack; // Temps depuis la dernière attaque
	int iCurrentTowerDetectionZoneId; //Id de la tour possédant la zone dans laquelle se situe l'ennemi

	/*choix du chemin a suivre*/
	t_EnnemyPathPointType PathToFollow;
	sfVector2f vPosPathToTarget; // point suivant que l'ennemi doit viser (maps actuelles)
	int iPosPathToTarget;

	sfBool isHit;
	float tStartLifeBarDisplay;
	float tCurrentLifeBarDisplay;
	float tSinceLifeBarDisplay;
};


typedef struct s_EnnemyElement t_EnnemyElement;
struct s_EnnemyElement
{
	int Id;
	t_Ennemy* Ennemy;
	t_EnnemyElement* NextElement;
	t_EnnemyElement* PreviousElement;
};


typedef struct s_List t_List;
struct s_List
{
	int count;
	t_EnnemyElement* FirstElement;
	t_EnnemyElement* LastElement;
};

typedef struct s_EnnemyBullet t_EnnemyBullet;

#pragma endregion ENNEMY 

#pragma region ENNEMY BULLET

struct s_EnnemyBullet
{
	sfSprite* sprite;
	sfVector2f vPos;
	sfVector2f vOrigin;
	sfVector2f vCurrentVelocity;
	sfVector2f vCurrentDirection;
	sfFloatRect boundingBox;
	float fAngleSprite;
	float fSpeed; // vitesse
	float fSpeedMax; // vitesse
	int iTowerToTargetId; // Id de la tour ciblé

	int Deg; // les dégats correspondent aux dégats de l'ennemi
	int iHP; // permet de delete la balle quand elle rentre en collision avec une tower
};

typedef struct s_EnnemyBulletElement t_EnnemyBulletElement;

struct s_EnnemyBulletElement
{
	int Id;
	t_EnnemyBullet* EnnemyBullet;
	t_EnnemyBulletElement* NextElement;
	t_EnnemyBulletElement* PreviousElement;
};

typedef struct s_ListEnnemyBullet t_ListEnnemyBullet;

struct s_ListEnnemyBullet
{
	t_EnnemyBulletElement* FirstElement;
	t_EnnemyBulletElement* LastElement;
};

#pragma endregion ENNEMY BULLET

#pragma region ENNEMY WAVE

typedef struct s_EnnemyWave t_EnnemyWave;

struct s_EnnemyWave
{
	int iNumWave;
	int iMaxWave; // nombre total de vague
	int iNbrTotal; // nombre total d'ennemi pendant la vague
	int iNbrCholesterol;
	int iNbrCancer;
	int iNbrCaillot;
};

typedef struct s_EnnemyWaveElement t_EnnemyWaveElement;

struct s_EnnemyWaveElement
{
	int Id;
	t_EnnemyWave* EnnemyWave;
	t_EnnemyWaveElement* NextElement;
	t_EnnemyWaveElement* PreviousElement;
};

typedef struct s_ListEnnemyWave t_ListEnnemyWave;

struct s_ListEnnemyWave
{
	t_EnnemyWaveElement* FirstElement;
	t_EnnemyWaveElement* LastElement;
};

#pragma endregion ENNEMY WAVE

#pragma region TOWER SLOT

typedef struct s_TowerSlot t_TowerSlot;
struct s_TowerSlot
{
	sfVector2f vPos;
	sfVector2f vSpawnPos;
	sfVector2f vOrigin;
	sfBool IsClicked;
	sfBool IsBuild;
	t_TowerType BuildedType;
	int TowerBuildId; // id de la tour qui est posée dessus
};

typedef struct s_TowerSlotElement t_TowerSlotElement;
struct s_TowerSlotElement
{
	int Id;
	t_TowerSlot* TowerSlot;
	t_TowerSlotElement* NextElement;
	t_TowerSlotElement* PreviousElement;
};

typedef struct s_ListTowerSlot t_ListTowerSlot;
struct s_ListTowerSlot
{
	t_TowerSlotElement* FirstElement;
	t_TowerSlotElement* LastElement;
};

#pragma endregion TOWER SLOT

#pragma region ENNEMY PATH POINT

typedef struct s_EnnemyPathPoint t_EnnemyPathPoint;
struct s_EnnemyPathPoint
{
	sfSprite* sprite;
	sfVector2f vPos;
	sfVector2f vOrigin;
	int Num;
	int Type; //type du point
	sfFloatRect* GlobalBounds;
};

typedef struct s_EnnemyPathPointElement t_EnnemyPathPointElement;
struct s_EnnemyPathPointElement
{
	int Id;
	t_EnnemyPathPoint* EnnemyPathPoint;
	t_EnnemyPathPointElement* NextElement;
	t_EnnemyPathPointElement* PreviousElement;
};

typedef struct s_ListEnnemyPathPoint t_ListEnnemyPathPoint;
struct s_ListEnnemyPathPoint
{
	t_EnnemyPathPointElement* FirstElement;
	t_EnnemyPathPointElement* LastElement;
};

#pragma endregion ENNEMY PATH POINT

#pragma region TOWER

typedef struct s_Tower t_Tower;

struct s_Tower
{
	sfSprite* sprite;
	sfSprite* fieldSpr;
	sfVector2f vPos;
	sfVector2f vOrigin;
	t_TowerType TowerType;
	sfIntRect animRect;
	t_TowerLevel TowerLevel;
	sfFloatRect boundingBox;
	int iSlotId;
	float tStartShoot;
	float tSinceShoot;
	float tCurrentShoot;
	float tStartSpawnWhiteCell;
	float tSinceSpawnWhiteCell;
	float tCurrentSpawnWhiteCell;
	sfFloatRect fieldBB;
	float bulletSpeed;
	sfBool isOn;
	sfBool iIsWhiteCellAlive;
	sfBool isFirstBuild;
	DIRECTION dirState;

	int iHP;
	int iHPMax;

	/*fond noir barre*/
	sfRectangleShape* RectangleShapeBack;
	sfVector2f vSizeRectangleShapeBack;
	sfVector2f vPositionRectangleShapeBack;
	sfVector2f vOriginRectangleShapeBack;

	/*barre de vie*/
	sfRectangleShape* RectangleShape;
	sfVector2f vSizeRectangleShape;
	sfVector2f vPositionRectangleShape;
	sfVector2f vOriginRectangleShape;

	int cost;
	int upgradeCost;
};

typedef struct s_TowerElement t_TowerElement;

struct s_TowerElement
{
	int Id;
	t_Tower* Tower;
	t_TowerElement* NextElement;
	t_TowerElement* PreviousElement;
};

typedef struct s_ListTower t_ListTower;
struct s_ListTower
{
	int count;
	t_TowerElement* FirstElement;
	t_TowerElement* LastElement;
};

#pragma endregion TOWER

#pragma region TOWER CREATION BOUTON

typedef struct s_TowerCreationBtn t_TowerCreationBtn;

struct s_TowerCreationBtn
{
	sfSprite* sprite;
	sfVector2f vPos;
	sfVector2f vOrigin;
	t_TowerType TowerType;
	sfVector2f vDir;
	sfBool isOver;
};

#pragma endregion TOWER CREATION BOUTON

#pragma region TOWER BULLET

typedef struct s_TowerBullet t_TowerBullet;

struct s_TowerBullet
{
	sfSprite* sprite;
	sfVector2f pos;
	sfVector2f dir;
	sfFloatRect boundingBox;
	float angle;
	float bulletSpeed;
	int towerFromId;
};

typedef struct s_TowerBulletElement t_TowerBulletElement;

struct s_TowerBulletElement
{
	int Id;
	t_TowerBullet* TowerBullet;
	t_TowerBulletElement* NextElement;
	t_TowerBulletElement* PreviousElement;
};

typedef struct s_ListBullet t_ListBullet;

struct s_ListBullet
{
	t_TowerBulletElement* FirstElement;
	t_TowerBulletElement* LastElement;
};

#pragma endregion TOWER BULLET

#pragma region WHITE CELL

typedef struct s_whiteCell t_whiteCell;

struct s_whiteCell
{
	sfSprite* sprite;
	sfVector2f vPos;
	sfFloatRect boundingBox;
	sfIntRect animRect;
	sfVector2f vDir;
	float fSpeed;
	sfBool isWalking;
	int iTowerId;
	float tStartAnim;
	float tSinceAnim;
	float tCurrentAnim;
	int animFrame;
	DIRECTION dirState;// direction du globule blanc, gère l'axe y dans la découpe de la texture (voir enum ENNEMY_DIRECTION)
	sfVector2f distanceVector;

	/*choix du chemin a suivre*/
	sfBool isSearchingForPathToFollow; // false si le globule blanc n'a pas trouver de chemin a suivre
	t_EnnemyPathPointType PathToFollow;
	sfVector2f vPosPathToTarget; // point suivant que la cellule doit viser doit viser (maps actuelles)
	sfVector2f vDirectionPosPathToTarget;
	int iPosPathToTarget;

	int Hp; // sert pour le delete
};

typedef struct s_whiteCellElement t_whiteCellElement;

struct s_whiteCellElement
{
	int Id;
	t_whiteCell* whiteCell;
	t_whiteCellElement* NextElement;
	t_whiteCellElement* PreviousElement;
};

typedef struct s_ListWhiteCell t_ListWhiteCell;

struct s_ListWhiteCell
{
	int count;
	t_whiteCellElement* FirstElement;
	t_whiteCellElement* LastElement;
};

#pragma endregion WHITE CELL

#pragma region MENU

typedef struct s_inGameMenu t_inGameMenu;

struct s_inGameMenu
{
	sfSprite* menuButton;
	sfSprite* musicButton;
	sfSprite* fxButton;
	sfSprite* pauseButton;
	sfVector2f vOrigin;
	sfVector2f vPos_menuButton;
	sfVector2f vPos_musicButton;
	sfVector2f vPos_fxButton;
	sfVector2f vPos_pauseButton;
	t_buttonState musicButtonFrame;
	t_buttonState fxButtonFrame;
	t_inGameMenuState menuState;
	sfIntRect rect_musicButton;
	sfIntRect rect_fxButton;
	sfFloatRect menuButtonBB;
	sfFloatRect musicButtonBB;
	sfFloatRect fxButtonBB;
	sfFloatRect pauseButtonBB;
	sfBool isOverPause;
	sfBool isOverFx;
	sfBool isOverMusic;
	sfBool isOverMenuBtn;
};


typedef struct s_gameMenu t_gameMenu;

struct s_gameMenu
{
	sfSprite* background;
	sfSprite* play;
	sfSprite* credits;
	sfSprite* quit;
	sfVector2f vPos_play;
	sfVector2f vPos_credits;
	sfVector2f vPos_quit;
	sfVector2f vOrigin_play;
	sfVector2f vOrigin_credits;
	sfVector2f vOrigin_quit;
	sfFloatRect fRect_playBB;
	sfFloatRect fRect_creditsBB;
	sfFloatRect fRect_quitBB;
};

typedef struct s_gameMenuSave t_gameMenuSave;

struct s_gameMenuSave
{
	sfSprite* background;
	sfSprite* slot1;
	sfSprite* slot2;
	sfSprite* slot3;
	sfVector2f vPos_slot1;
	sfVector2f vPos_slot2;
	sfVector2f vPos_slot3;
	sfVector2f vOrigin_slot1;
	sfVector2f vOrigin_slot2;
	sfVector2f vOrigin_slot3;
	sfFloatRect fRect_slot1BB;
	sfFloatRect fRect_slot2BB;
	sfFloatRect fRect_slot3BB;
	int unLockedLevelsSlot1;
	int unLockedLevelsSlot2;
	int unLockedLevelsSlot3;
	sfSprite* slot1MiniMap;
	sfSprite* slot2MiniMap;
	sfSprite* slot3MiniMap;
};


typedef struct s_gameMenuLevel t_gameMenuLevel;

struct s_gameMenuLevel
{
	sfSprite* background;
	sfSprite* level1;
	sfSprite* level2;
	sfVector2f vPos_level1;
	sfVector2f vPos_level2;
	sfVector2f vOrigin_level1;
	sfVector2f vOrigin_level2;
	sfFloatRect fRect_level1BB;
	sfFloatRect fRect_level2BB;

};


typedef struct s_MainMenuElement t_MainMenuElement;

struct s_MainMenuElement
{
	sfSprite* sprite;
	sfVector2f vPos;
	sfVector2f vOrigin;
	sfFloatRect boundingBox;
};


typedef struct s_MainMenu t_MainMenu;

struct s_MainMenu
{
	t_MainMenuElement paperClip;
	t_MainMenuElement LogoSheet;
	t_MainMenuElement startLabel;
	t_MainMenuElement startSheet;
	t_MainMenuElement startSheetLS;
	t_MainMenuElement saveSlot1;
	t_MainMenuElement saveSlot2;
	t_MainMenuElement saveSlot3;
	t_MainMenuElement creditsLabel;
	t_MainMenuElement creditsSheet;
	t_MainMenuElement exitLabel;
	t_MainMenuElement exitSheet;
	t_MainMenuElement exitYes;
	t_MainMenuElement exitNo;
	t_MainMenuElement miniMapSlot1;
	t_MainMenuElement miniMapSlot2;
	t_MainMenuElement miniMapSlot3;
	t_MainMenuElement level1Icon;
	t_MainMenuElement level2Icon;
	t_MainMenuElement background;
	t_MainMenuElement brain;
	sfImage* labelMask;
	sfImage* levelMask;
	sfImage* saveMask;
	sfImage* exitMask;
};
#pragma endregion MENU

#pragma region HUD

typedef struct s_HudElement t_HudElement;

struct s_HudElement
{
	sfSprite* sprite;
	sfVector2f vPos;
	sfVector2f vOrigin;
};

typedef struct s_Hud t_Hud;

struct s_Hud
{
	t_HudElement lifePoints;
	t_HudElement money;
	t_HudElement waves;
};

#pragma endregion HUD

#pragma region CURRENT LEVEL

typedef struct s_CurrentLevelAssets t_CurrentLevelAssets;

struct s_CurrentLevelAssets
{
	sfSprite* map;
	sfImage* mapMask;
	int iNbrEnnemyPath; // nombre de chemins ennemis présent dans le niveau
	t_ListEnnemyWave* ListEnnemyWave;
	t_ListEnnemyPathPoint* TabListEnnemyPathPoint[MAX_LIST_ENNEMY_PATH_POINT]; // tableau de 

};
#pragma endregion CURRENT LEVEL

#pragma region INTRO
typedef struct s_introElement t_introElement;

struct s_introElement
{
	sfSprite* sprite;
	sfVector2f vPos;
	sfVector2f vOrigin;
	sfVector2f vSize;
};

typedef struct s_intro t_intro;

struct s_intro
{
	t_introElement game;
	t_introElement academy;
	t_introElement logo;
	t_introState state;
	sfVector2f vSizeMax;
};


#pragma endregion INTRO

#pragma endregion structures

#pragma region Functions Declarations

/*SFML Functions*/

/*set a texture to a sprite*/
sfSprite* createSprite(char* _path);

sfSound* createSound(char* _path);

/*set a font to a text*/
sfText* createText(char* _path);

/*draw the textbox & the text*/
sfText* DrawTextInTextBox(sfRenderWindow* window, char* _text, const sfSprite* _TextBox);

/*draw the text*/
sfText* DrawTextWindow(sfRenderWindow* window, char* _text, sfVector2f _vPositionText);

/*check if the mouse is on anothe sprite and if so change the sprite colour*/
int MouseIsOverSprite(char *_window, sfVector2f _vPositionSprite, sfVector2f _vOriginSprite);

int MouseIsOverText(char *_window, char *_text);

int SpriteIsOver(char *_spritePerso, char *_spriteObject);
int SpriteIsOverPosition(sfVector2f _vPositionPerso, sfVector2f _vOriginPerso, sfVector2f _vPositionObject, sfVector2f _vOriginObject);


//void Collider(sfImage* _collid, Player* player);

void loadTowerSlots(t_ListTowerSlot* _ListTowerSlot, int _levelNumber);
int loadEnnemyNbrPath(int _levelNumber);
t_ListEnnemyPathPoint* loadEnnemyPathPoint(t_ListEnnemyPathPoint* _ListEnnemyPathPoint, int _levelNumber, int _NumPath);
t_ListEnnemyWave* loadEnnemyWave(t_ListEnnemyWave* _ListEnnemyWave, int _levelNumber);
void manageInGameMenu(t_inGameMenu* _inGameMenu);
void loadSaveForSaveSlots(t_gameMenuSave* _gameMenuSave);
void loadGameFromLevelNumber(t_NameLevel _iCurrentLevel, t_CurrentLevelAssets* _CurrentLevelAssets, t_List* _ListEnnemy, t_ListBullet* _ListBullet, t_ListEnnemyBullet* _ListEnnemyBullet,
	t_ListTower* _ListTower, t_ListTowerSlot* _ListTowerSlot, t_ListWhiteCell* _ListWhiteCell);

t_EnnemyElement* AddElementBeginList(t_List* _List);
t_EnnemyBulletElement* AddElementBeginListEnnemyBullet(t_ListEnnemyBullet* _List);
t_EnnemyWaveElement* AddElementBeginListEnnemyWave(t_ListEnnemyWave* _List);
t_EnnemyPathPointElement* AddElementBeginListEnnemyPathPoint(t_ListEnnemyPathPoint* _List);
t_TowerSlotElement* AddElementBeginListTowerSlot(t_ListTowerSlot* _List);
t_TowerElement* AddElementBeginListTower(t_ListTower* _List);
t_TowerBulletElement* AddElementBeginListTowerBullet(t_ListBullet* _List);
t_whiteCellElement* AddElementBeginListWhiteCell(t_ListWhiteCell* _List);

sfBool DeleteElementById(t_List* _List, int _IdElementToDelete);
sfBool DeleteElementByIdEnnemyBullet(t_ListEnnemyBullet* _List, int _IdElementToDelete);
sfBool DeleteElementByIdEnnemyWave(t_ListEnnemyWave* _List, int _IdElementToDelete);
sfBool DeleteElementByIdEnnemyPathPoint(t_ListEnnemyPathPoint* _List, int _IdElementToDelete);
sfBool DeleteElementByIdTowerSlot(t_ListTowerSlot* _List, int _IdElementToDelete);
sfBool DeleteElementByIdTower(t_ListTower* _List, int _IdElementToDelete);
sfBool DeleteElementByIdBullet(t_ListBullet* _List, int _IdElementToDelete);
sfBool DeleteElementByIdWhiteCell(t_ListWhiteCell* _List, int _IdElementToDelete);

sfBool DeleteAllElementInList(t_List* _List);
sfBool DeleteAllElementInListEnnemyBullet(t_ListEnnemyBullet* _List);
sfBool DeleteAllElementInListEnnemyWave(t_ListEnnemyWave* _List);
sfBool DeleteAllElementInListEnnemyPathPoint(t_ListEnnemyPathPoint* _List);
sfBool DeleteAllElementInListTowerSlot(t_ListTowerSlot* _List);
sfBool DeleteAllElementInListTower(t_ListTower* _List);
sfBool DeleteAllElementInListTowerBullet(t_ListBullet* _List);
sfBool DeleteAllElementInListWhiteCell(t_ListWhiteCell* _List);

sfBool SortTowerByPos(t_ListTower *_list);
sfBool SortEnnemyByPos(t_List *_list);
sfBool DeleteEntityWithID(t_ListTower*_list, int _id);
sfBool DeleteEnemyWithID(t_List*_list, int _id);

#pragma region FORCES

sfVector2f GetDirectionFromAngleDegrees(float _angleDegrees);
sfVector2f GetDirectionFromAngleRadians(double _angleRadians);
float GetAngleRadiansBetweenPoints(sfVector2f _pointA, sfVector2f _pointB);
float GetAngleRadiansBetweenPointAndMouse(sfVector2f _pointA, sfVector2i _pointB);
float GetAngleRadiansFromVector(sfVector2f _vector);
float GetAngleDegreeFromVector(sfVector2f _vector);
double DegToRad(float _degrees);
float RadToDeg(double _radians);
sfVector2f Normalize(sfVector2f _vector);
float Magnitude(sfVector2f _vector);
sfVector2f Truncate(sfVector2f _vector, float _max);

#pragma endregion FORCES

sfVector2f normalizeVector(sfVector2f _vector);
sfBool manageEnnemi(t_EnnemyElement* currentElement, sfImage* testMask, float fTimeSinceLastFrame);

void SetLineBetweenPoints(sfVertexArray* _vertexArray, sfVertex* _vertex, sfVector2f _startPoint, sfVector2f _destPoint, sfColor _color);
#pragma endregion Functions Declarations