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

#pragma region ENNEMY


#pragma region BARRE DE VIE ENNEMI

#define SIZE_HP_X 75
#define SIZE_HP_Y 2

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

#define CHOLESTEROL_SPEED 75
#define CHOLESTEROL_DEG 5 // dégats quand il est gros
#define CHOLESTEROL_HP 10
#define CHOLESTEROL_MONEY_VALUE 25

#define CANCER_SPEED 125
#define CANCER_DEG 1
#define CANCER_HP 2
#define CANCER_MONEY_VALUE 5

#define CAILLOT_SPEED 50
#define CAILLOT_DEG 10
#define CAILLOT_HP 20
#define CAILLOT_MONEY_VALUE 50

#pragma endregion STATS

#define CAILLOT_CONTROL_RADIUS 80
#define CAILLOT_GUARD_RADIUS 25
#define CANCER_CONTROL_RADIUS 80
#define CANCER_GUARD_RADIUS 15
#define CHOLESTEROL_CONTROL_RADIUS 80
#define CHOLESTEROL_GUARD_RADIUS 30

#define TIME_BETWEEN_WAVE 5

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

#define LIFEBAR_MAX_SIZE_X 60
#define LIFEBAR_SIZE_Y 6

#define DOT_FREQUENCY 2

#pragma endregion ENNEMY

#pragma region WHITE_CELLS

#define WHITE_CELL_WIDTH 299
#define WHITE_CELL_HEIGHT 240
#define WHITE_CELL_FRAMES 15
#define WHITE_CELL_ANIM_SPEED 0.03
#define WHITE_CELL_FIELD_OF_VIEW_RADIUS 250
#define WHITE_CELL_AREA_DAMAGE_RADIUS 500
#define WHITE_CELL_CREATE_COOLDOWN 2

#pragma endregion WHITE_CELLS

#pragma region TOWERS

#define TOWER1_DAMAGES 2
#define TOWER2_DAMAGES 2
#define TOWER3_DAMAGES 10

#pragma endregion TOWERS

#pragma endregion Defines

#pragma region enum
typedef enum e_GameState t_GameState;
enum e_GameState
{
	PLAY = 0,
	VICTORY,
	DEFEAT
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

typedef enum e_ENNEMY_DIRECTION ENNEMY_DIRECTION;

enum e_ENNEMY_DIRECTION
{
	DOWN_RIGHT,
	DOWN_LEFT,
	UP_LEFT,
	UP_RIGHT
};
#pragma endregion enum

#pragma region structures

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
	sfVector2f vTargetPostion; // position visé par l'ennemi
	sfVector2f vSpawnPosition; // Position de spawn de l'ennemi
	float fAngleSprite; // angle du sprite
	float fCurrentAngleDirection; // angle de direction actuel
	float fDesiredAngleDirection; // angle de direction voulue
	float fSpeed;
	float fSpeedMax;

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
	int iDirection; // direction de l'ennemie, gère l'axe y dans la découpe de la texture (voir enum ENNEMY_DIRECTION)
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

	/*gestion attaque Caillot*/
	int iIsAttack; // actif si l'ennemi est en train d'attaquer
	int iTowerToAttackId;
	sfVector2f vPosTowerToAttack;
	float fTimeSinceLastAttack;

	/*dommages tour 2*/
	float tStartDOT;
	float tSinceDOT;
	float tCurrentDOT;
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
	t_EnnemyElement* FirstElement;
	t_EnnemyElement* LastElement;
};


typedef struct s_TowerSlot t_TowerSlot;
struct s_TowerSlot
{
	sfVector2f vPos;
	sfVector2f vSpawnPos;
	sfVector2f vOrigin;
	sfBool IsClicked;
	sfBool IsBuild;
	t_TowerType BuildedType;
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

typedef struct s_Tower t_Tower;

struct s_Tower
{
	sfSprite* sprite;
	sfSprite* fieldSpr;
	sfVector2f vPos;
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

	int iHP;
	int iHPMax;

};

typedef struct s_EnnemyBullet t_EnnemyBullet;

struct s_EnnemyBullet
{
	sfSprite* sprite;
	sfVector2f pos;
	sfVector2f dir;
	sfFloatRect boundingBox;
	float angle;
	float bulletSpeed;
	int towerFromId;
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
	ENNEMY_DIRECTION dirState;
	sfVector2f distanceVector;
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

t_EnnemyElement* AddElementBeginList(t_List* _List);
t_EnnemyBulletElement* AddElementBeginListEnnemyBullet(t_ListEnnemyBullet* _List);
t_TowerSlotElement* AddElementBeginListTowerSlot(t_ListTowerSlot* _List);
t_TowerElement* AddElementBeginListTower(t_ListTower* _List);
t_TowerBulletElement* AddElementBeginListTowerBullet(t_ListBullet* _List);
t_whiteCellElement* AddElementBeginListWhiteCell(t_ListWhiteCell* _List);

sfBool DeleteElementById(t_List* _List, int _IdElementToDelete);
sfBool DeleteElementByIdEnnemyBullet(t_ListEnnemyBullet* _List, int _IdElementToDelete);
sfBool DeleteElementByIdTowerSlot(t_ListTowerSlot* _List, int _IdElementToDelete);
sfBool DeleteElementByIdTower(t_ListTower* _List, int _IdElementToDelete);
sfBool DeleteElementByIdBullet(t_ListBullet* _List, int _IdElementToDelete);
sfBool DeleteElementByIdWhiteCell(t_ListWhiteCell* _List, int _IdElementToDelete);

sfBool DeleteAllElementInList(t_List* _List);

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

sfBool SortTowerByPos(t_ListTower *_list);

sfBool DeleteEntityWithID(t_ListTower*_list, int _id);
#pragma endregion Functions Declarations