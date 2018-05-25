#include "header.h"

int main()
{
	/*initialisation du srand*/
	srand(time(NULL));

	float testincreaseX = 1;
	float testincreaseY = 1;

	int unLockedLevelsSolt1 = 0;
	int unLockedLevelsSolt2 = 0;
	int unLockedLevelsSolt3 = 0;

#pragma region LIST

	t_List* ListEnnemy = malloc(sizeof(t_List));
	ListEnnemy->FirstElement = NULL;
	ListEnnemy->LastElement = NULL;
	ListEnnemy->count = 0;
	t_EnnemyElement* CurrentEnnemy = NULL;
	t_EnnemyElement* CurrentEnnemy2 = NULL;
	t_EnnemyElement* NewEnnemy = NULL;

	t_ListEnnemyBullet* ListEnnemyBullet = malloc(sizeof(t_ListEnnemyBullet));
	ListEnnemyBullet->FirstElement = NULL;
	ListEnnemyBullet->LastElement = NULL;
	t_EnnemyBulletElement* CurrentEnnemyBullet = NULL;
	t_EnnemyBulletElement* NewEnnemyBullet = NULL;

	t_ListEnnemyWave* ListEnnemyWave = malloc(sizeof(t_ListEnnemyWave));
	ListEnnemyWave->FirstElement = NULL;
	ListEnnemyWave->LastElement = NULL;
	t_EnnemyWaveElement* CurrentEnnemyWave = NULL;
	t_EnnemyWaveElement* NewEnnemyWave = NULL;

	/*en phase de test*/
	t_EnnemyPathPointElement* CurrentEnnemyPathPoint = NULL;
	t_EnnemyPathPointElement* NewEnnemyPathPoint = NULL;

	t_ListTowerSlot* ListTowerSlot = malloc(sizeof(t_ListTowerSlot));
	ListTowerSlot->FirstElement = NULL;
	ListTowerSlot->LastElement = NULL;
	t_TowerSlotElement* CurrentTowerSlot = NULL;
	t_TowerSlotElement* NewTowerSlot = NULL;
	t_TowerSlotElement* ActualTowerSlot = NULL;

	t_ListTower* ListTower = malloc(sizeof(t_ListTower));
	ListTower->count = 0;
	ListTower->FirstElement = NULL;
	ListTower->LastElement = NULL;
	t_TowerElement* CurrentTower = NULL;
	t_TowerElement* NewTower = NULL;
	t_TowerElement* ActualTower = NULL;

	t_ListBullet* ListTowerBullet = malloc(sizeof(t_ListBullet));
	ListTowerBullet->FirstElement = NULL;
	ListTowerBullet->LastElement = NULL;
	t_TowerBulletElement* CurrentTowerBullet = NULL;
	t_TowerBulletElement* NewTowerBullet = NULL;

	t_ListWhiteCell* ListWhiteCell = malloc(sizeof(t_ListWhiteCell));
	ListWhiteCell->count = 0;
	ListWhiteCell->FirstElement = NULL;
	ListWhiteCell->LastElement = NULL;
	t_whiteCellElement* CurrentWhiteCell = NULL;
	t_whiteCellElement* NewWhiteCell = NULL;

#pragma endregion LIST

#pragma region SOUND

#pragma endregion SOUND

#pragma region VARIABLES

	t_GameState GameState = MENU;
	t_mainMenuState mainMenuState = ON_LOGO;
	t_mainMenuState mainMenuNextState = ON_LOGO;

	sfBool gamePause = sfFalse;
	sfBool isMousePressed = sfFalse;
	sfBool isWindowActive = sfTrue;
	sfBool isInBuildChoice = sfFalse;
	sfBool isBuildedChoice = sfFalse;
	sfBool isMoving = sfFalse;
	sfBool isOpened = sfFalse;
	sfBool isBuildedOpened = sfFalse;
	sfBool asBreak = sfFalse;
	sfBool isSearchingForDead = sfTrue;

#pragma region VARIABLES DE TOUCHES

	sfBool SpaceButtonIsButtonPressed = sfFalse;

	int iSpaceButtonIsButtonPressedCheck = 0;

#pragma endregion VARIABLES DE TOUCHES

#pragma region C VARS
	int MenuState = MENU;
	int iCurrentLevel = ESTOMAC;
	int iDebug = 0;
	int iTowerId = 0;
	int unlockedLevels = 0;
#pragma endregion C VARS

#pragma region CSFML VARS //SEB
	sfSprite* Sp_EnnemyPathPoint = createSprite("resources/textures/EnnemyPathPoint.png");
	sfSprite* Sp_MapTest = createSprite("resources/textures/map.jpg");
	sfSprite* Sp_MaskMapTest = createSprite("resources/textures/Collision Mask Test.jpg");
	sfImage* Image_MaskMapTest = sfImage_createFromFile("resources/textures/Collision Mask Test.psd");
	sfSprite* Sp_MapEstomac = createSprite("resources/textures/Level Estomac.jpg");
	sfSprite* Sp_MaskMapEstomac = createSprite("resources/textures/Collision Mask Estomac.jpg");
	sfImage* Image_MaskMapEstomac = sfImage_createFromFile("resources/textures/maps/mapMask1.psd");

	sfSprite* Sp_TowerSlot = createSprite("resources/textures/socle.png");
	sfVector2f vOrigin_TowerSlot = { sfSprite_getGlobalBounds(Sp_TowerSlot).width / 2,sfSprite_getGlobalBounds(Sp_TowerSlot).height / 2 };
	sfSprite_setOrigin(Sp_TowerSlot, vOrigin_TowerSlot);
	sfImage* Img_TowerSlotMask = sfImage_createFromFile("resources/textures/SocleMask.psd");
	sfImage* Img_TowerMask = sfImage_createFromFile("resources/textures/towerMask.psd");
	sfVector2i vMousePos = { 0,0 };
	sfVector2f vMousePosToFloat = { 0,0 };
	sfVector2f vMousePointToCheck = { 0,0 };
	sfVector2f vDistanceBetween = { 0,0 };
	sfFloatRect Rect_TowerSlotBB;
	sfFloatRect Rect_TowerBB;
	sfFloatRect Rect_TowerSlotBtnBB;
	sfVector2f vBtnScale = { 0,0 };
	sfVector2f vBtnScale2 = { 0,0 };
	sfVector2f vOrigin_tower;
	sfSprite* Sp_tower1 = createSprite("resources/textures/tours/Tour 1.png");
	sfSprite* Sp_tower2 = createSprite("resources/textures/tours/tour2.png");
	sfSprite* Sp_tower3 = createSprite("resources/textures/tours/tour3.png");
	sfSprite* Sp_towerActual = NULL;
	vOrigin_tower.x = TOWER1_WIDTH / 2;
	vOrigin_tower.y = TOWER1_HEIGHT - 15;
	sfSprite_setOrigin(Sp_tower1, vOrigin_tower);
	vOrigin_tower.x = TOWER2_WIDTH / 2 + 20;
	vOrigin_tower.y = TOWER2_HEIGHT + 30;
	sfSprite_setOrigin(Sp_tower2, vOrigin_tower);
	vOrigin_tower.x = TOWER3_WIDTH / 2;
	vOrigin_tower.y = TOWER3_HEIGHT - 15;
	sfSprite_setOrigin(Sp_tower3, vOrigin_tower);
	sfSprite* Sp_fieldOfViewDisplay = createSprite("resources/textures/fieldMask.png");
	sfSprite* Sp_fieldOfView = createSprite("resources/textures/tower_field_of_view.png");
	sfVector2f vOrigin_fieldOfView;
	vOrigin_fieldOfView.x = sfSprite_getGlobalBounds(Sp_fieldOfView).width / 2;
	vOrigin_fieldOfView.y = sfSprite_getGlobalBounds(Sp_fieldOfView).height / 2;
	sfSprite_setOrigin(Sp_fieldOfView, vOrigin_fieldOfView);
	sfSprite_setOrigin(Sp_fieldOfViewDisplay, vOrigin_fieldOfView);
	sfVector2f vPlayerPointToCheck = { 0,0 };
	sfImage* Img_fieldMask = sfImage_createFromFile("resources/textures/fieldMask.psd");
	sfSprite* Sp_bullet1 = createSprite("resources/textures/bullet1.png");
	sfSprite* Sp_bullet2 = createSprite("resources/textures/bullet2.png");
	sfSprite* Sp_bullet3 = createSprite("resources/textures/tours/Tir 1.png");
	sfVector2f vOrigin_bullet = { 10,10 };
	sfSprite_setOrigin(Sp_bullet1, vOrigin_bullet);
	sfSprite_setOrigin(Sp_bullet2, vOrigin_bullet);
	sfSprite_setOrigin(Sp_bullet3, vOrigin_bullet);
	sfSprite* spawnCross = createSprite("resources/textures/cross.png");
	sfVector2f vOrigin_spawnCross = { sfSprite_getGlobalBounds(spawnCross).width / 2, sfSprite_getGlobalBounds(spawnCross).height / 2 };
	sfSprite_setOrigin(spawnCross, vOrigin_spawnCross);
	sfSprite* Spr_whiteCell = createSprite("resources/textures/tours/tir3.png");
	sfVector2f vOrigin_whiteCell = { WHITE_CELL_WIDTH/2,WHITE_CELL_HEIGHT /2 };
	sfSprite_setOrigin(Spr_whiteCell, vOrigin_whiteCell);

	sfSprite* Sp_Ennemy1 = createSprite("resources/textures/enemis/blue iso petit.png"); // CANCER
	sfSprite* Sp_Ennemy2 = createSprite("resources/textures/enemis/cho iso.png"); // CHOLESTEROL
	sfSprite* Sp_Ennemy3 = createSprite("resources/textures/enemis/roesd2.png"); // CAILLOT
	sfSprite* Sp_EnnemyBullet = createSprite("resources/textures/enemis/tir refait.png"); // PROJECTILE CHOLESTEROL

	sfSprite* Sp_MenuVictoire = createSprite("resources/textures/Vic-Def/victoire/victoire.png");
	sfSprite* Sp_MenuDefaite = createSprite("resources/textures/Vic-Def/defaite/defaite.png");
	sfSprite* Sp_BoutonRetour = createSprite("resources/textures/Vic-Def/bouton retour.png");

	sfSprite* Sp_Tower1_Panel = createSprite("resources/textures/HUD_tower/tower1_panel.png");
	sfSprite* Sp_Tower2_Panel = createSprite("resources/textures/HUD_tower/tower2_panel.png");
	sfSprite* Sp_Tower3_Panel = createSprite("resources/textures/HUD_tower/tower3_panel.png");


#pragma endregion CSFML VARS //SEB

#pragma region TIME VARIABLES

	int iFirstFrameIsPassed = 0; // permet de ne pas comptabiliser la première frame pour les timers
	float currentTime = 0; // Temps actuel depuis le début du programme
	float timeSinceLastFrame = 0; // Temps depuis la dernière frame
	float lastFrameTime = 0; // Temps de la dernière frame

#pragma endregion TIME VARIABLES

#pragma region STRUCTURE MENU INGAME //SEB

	t_inGameMenu inGameMenu;
	inGameMenu.vOrigin.x = BUTTON_SPRITE_SIZE / 2;
	inGameMenu.vOrigin.y = BUTTON_SPRITE_SIZE / 2;
	inGameMenu.menuButton = createSprite("resources/textures/menu_ingame.png");
	sfSprite_setOrigin(inGameMenu.menuButton, inGameMenu.vOrigin);
	inGameMenu.vPos_menuButton.x = 1850;
	inGameMenu.vPos_menuButton.y = 1010;
	sfSprite_setPosition(inGameMenu.menuButton, inGameMenu.vPos_menuButton);
	//
	inGameMenu.pauseButton = createSprite("resources/textures/pause.png");
	sfSprite_setOrigin(inGameMenu.pauseButton, inGameMenu.vOrigin);
	inGameMenu.vPos_pauseButton.x = inGameMenu.vPos_menuButton.x;
	inGameMenu.vPos_pauseButton.y = inGameMenu.vPos_menuButton.y;
	sfSprite_setPosition(inGameMenu.pauseButton, inGameMenu.vPos_pauseButton);
	//
	inGameMenu.musicButton = createSprite("resources/textures/music.png");
	sfSprite_setOrigin(inGameMenu.musicButton, inGameMenu.vOrigin);
	inGameMenu.vPos_musicButton.x = inGameMenu.vPos_menuButton.x;
	inGameMenu.vPos_musicButton.y = inGameMenu.vPos_menuButton.y;
	sfSprite_setPosition(inGameMenu.musicButton, inGameMenu.vPos_musicButton);
	inGameMenu.musicButtonFrame = IS_OFF;
	inGameMenu.rect_musicButton.left = inGameMenu.musicButtonFrame * BUTTON_SPRITE_SIZE;
	inGameMenu.rect_musicButton.top = 0;
	inGameMenu.rect_musicButton.width = BUTTON_SPRITE_SIZE;
	inGameMenu.rect_musicButton.height = BUTTON_SPRITE_SIZE;
	sfSprite_setTextureRect(inGameMenu.musicButton, inGameMenu.rect_musicButton);
	//
	inGameMenu.fxButton = createSprite("resources/textures/fx.png");
	sfSprite_setOrigin(inGameMenu.fxButton, inGameMenu.vOrigin);
	inGameMenu.vPos_fxButton.x = inGameMenu.vPos_menuButton.x;
	inGameMenu.vPos_fxButton.y = inGameMenu.vPos_menuButton.y;
	sfSprite_setPosition(inGameMenu.fxButton, inGameMenu.vPos_fxButton);
	inGameMenu.fxButtonFrame = IS_OFF;
	inGameMenu.rect_fxButton.left = inGameMenu.fxButtonFrame * BUTTON_SPRITE_SIZE;
	inGameMenu.rect_fxButton.top = 0;
	inGameMenu.rect_fxButton.width = BUTTON_SPRITE_SIZE;
	inGameMenu.rect_fxButton.height = BUTTON_SPRITE_SIZE;
	sfSprite_setTextureRect(inGameMenu.fxButton, inGameMenu.rect_fxButton);

	inGameMenu.menuState = IS_CLOSED;


	t_CurrentLevelAssets CurrentLevelAssets;

#pragma endregion STRUCTURE MENU INGAME //SEB

#pragma region MENU DU JEU //SEB
	t_gameMenu gameMenu;
	gameMenu.background = createSprite("resources/textures/menu/menu_back.png");
	//
	gameMenu.play = createSprite("resources/textures/menu/menu_jouer.png");
	gameMenu.vOrigin_play.x = sfSprite_getGlobalBounds(gameMenu.play).width / 2;
	gameMenu.vOrigin_play.y = sfSprite_getGlobalBounds(gameMenu.play).height / 2;
	sfSprite_setOrigin(gameMenu.play, gameMenu.vOrigin_play);
	gameMenu.vPos_play.x = 678;
	gameMenu.vPos_play.y = 438;
	sfSprite_setPosition(gameMenu.play, gameMenu.vPos_play);
	gameMenu.fRect_playBB = sfSprite_getGlobalBounds(gameMenu.play);
	//
	gameMenu.credits = createSprite("resources/textures/menu/menu_credits.png");
	gameMenu.vOrigin_credits.x = sfSprite_getGlobalBounds(gameMenu.credits).width / 2;
	gameMenu.vOrigin_credits.y = sfSprite_getGlobalBounds(gameMenu.credits).height / 2;
	sfSprite_setOrigin(gameMenu.credits, gameMenu.vOrigin_credits);
	gameMenu.vPos_credits.x = 462;
	gameMenu.vPos_credits.y = 698;
	sfSprite_setPosition(gameMenu.credits, gameMenu.vPos_credits);
	gameMenu.fRect_creditsBB = sfSprite_getGlobalBounds(gameMenu.credits);
	//
	gameMenu.quit = createSprite("resources/textures/menu/menu_quitter.png");
	gameMenu.vOrigin_quit.x = sfSprite_getGlobalBounds(gameMenu.quit).width / 2;
	gameMenu.vOrigin_quit.y = sfSprite_getGlobalBounds(gameMenu.quit).height / 2;
	sfSprite_setOrigin(gameMenu.quit, gameMenu.vOrigin_quit);
	gameMenu.vPos_quit.x = 770;
	gameMenu.vPos_quit.y = 942;
	sfSprite_setPosition(gameMenu.quit, gameMenu.vPos_quit);
	gameMenu.fRect_quitBB = sfSprite_getGlobalBounds(gameMenu.quit);


#pragma endregion MENU DU JEU //SEB

#pragma region MENU CHOIX SAVE //SEB
	t_gameMenuSave gameMenuSave;
	gameMenuSave.background = createSprite("resources/textures/save_selector/save_selector_back.png");
	//
	gameMenuSave.slot1 = createSprite("resources/textures/save_selector/save_selector_slot1.png");
	gameMenuSave.vOrigin_slot1.x = sfSprite_getGlobalBounds(gameMenuSave.slot1).width / 2;
	gameMenuSave.vOrigin_slot1.y = sfSprite_getGlobalBounds(gameMenuSave.slot1).height / 2;
	sfSprite_setOrigin(gameMenuSave.slot1, gameMenuSave.vOrigin_slot1);
	gameMenuSave.vPos_slot1.x = 678;
	gameMenuSave.vPos_slot1.y = 438;
	sfSprite_setPosition(gameMenuSave.slot1, gameMenuSave.vPos_slot1);
	gameMenuSave.fRect_slot1BB = sfSprite_getGlobalBounds(gameMenuSave.slot1);
	//
	gameMenuSave.slot2 = createSprite("resources/textures/save_selector/save_selector_slot2.png");
	gameMenuSave.vOrigin_slot2.x = sfSprite_getGlobalBounds(gameMenuSave.slot2).width / 2;
	gameMenuSave.vOrigin_slot2.y = sfSprite_getGlobalBounds(gameMenuSave.slot2).height / 2;
	sfSprite_setOrigin(gameMenuSave.slot2, gameMenuSave.vOrigin_slot2);
	gameMenuSave.vPos_slot2.x = 462;
	gameMenuSave.vPos_slot2.y = 698;
	sfSprite_setPosition(gameMenuSave.slot2, gameMenuSave.vPos_slot2);
	gameMenuSave.fRect_slot2BB = sfSprite_getGlobalBounds(gameMenuSave.slot2);
	//
	gameMenuSave.slot3 = createSprite("resources/textures/save_selector/save_selector_slot3.png");
	gameMenuSave.vOrigin_slot3.x = sfSprite_getGlobalBounds(gameMenuSave.slot3).width / 2;
	gameMenuSave.vOrigin_slot3.y = sfSprite_getGlobalBounds(gameMenuSave.slot3).height / 2;
	sfSprite_setOrigin(gameMenuSave.slot3, gameMenuSave.vOrigin_slot3);
	gameMenuSave.vPos_slot3.x = 770;
	gameMenuSave.vPos_slot3.y = 942;
	sfSprite_setPosition(gameMenuSave.slot3, gameMenuSave.vPos_slot3);
	gameMenuSave.fRect_slot3BB = sfSprite_getGlobalBounds(gameMenuSave.slot3);


#pragma endregion MENU CHOIX SAVE //SEB

#pragma region MENU CHOIX LEVEL //SEB
	t_gameMenuLevel gameMenuLevel;
	gameMenuLevel.background = createSprite("resources/textures/level_selector/level_selector_back.png");
	//
	gameMenuLevel.level1 = createSprite("resources/textures/level_selector/level_selector_level1.png");
	gameMenuLevel.vOrigin_level1.x = sfSprite_getGlobalBounds(gameMenuLevel.level1).width / 2;
	gameMenuLevel.vOrigin_level1.y = sfSprite_getGlobalBounds(gameMenuLevel.level1).height / 2;
	sfSprite_setOrigin(gameMenuLevel.level1, gameMenuLevel.vOrigin_level1);
	gameMenuLevel.vPos_level1.x = 984;
	gameMenuLevel.vPos_level1.y = 676;
	sfSprite_setPosition(gameMenuLevel.level1, gameMenuLevel.vPos_level1);
	gameMenuLevel.fRect_level1BB = sfSprite_getGlobalBounds(gameMenuLevel.level1);
	//
	gameMenuLevel.level2 = createSprite("resources/textures/level_selector/level_selector_level2.png");
	gameMenuLevel.vOrigin_level2.x = sfSprite_getGlobalBounds(gameMenuLevel.level2).width / 2;
	gameMenuLevel.vOrigin_level2.y = sfSprite_getGlobalBounds(gameMenuLevel.level2).height / 2;
	sfSprite_setOrigin(gameMenuLevel.level2, gameMenuLevel.vOrigin_level2);
	gameMenuLevel.vPos_level2.x = 1088;
	gameMenuLevel.vPos_level2.y = 402;
	sfSprite_setPosition(gameMenuLevel.level2, gameMenuLevel.vPos_level2);
	gameMenuLevel.fRect_level2BB = sfSprite_getGlobalBounds(gameMenuLevel.level2);

#pragma endregion MENU CHOIX LEVEL //SEB

#pragma endregion VARIABLES

#pragma region WINDOW

	sfVideoMode Mode = { WINDOW_WIDTH, WINDOW_HEIGHT, 32 };
	sfRenderWindow* window;
	sfEvent event;

	/* Create the main window */
	window = sfRenderWindow_create(Mode, "Tower Defense",sfResize | sfClose /*sfFullscreen*/, NULL);
	if (!window)
	{
		return -1;
	}

	/*set the Framerate*/
	sfRenderWindow_setFramerateLimit(window, FRAMERATE);

	// attribute the Window size to a vector
	sfVector2u vWindowSize = sfWindow_getSize(window);

	// create window center vector
	sfVector2f vWindowCenter = { vWindowSize.x / 2, vWindowSize.y / 2 };

#pragma endregion WINDOW

	/*Argent*/
	int iPlayerMoney = 1000;

	/*VIE OBJECTIF*/
	int iGoalHp = 100;

	/*GESTION VAGUES*/
	int iWaveMax = 0; // maximum de vagues pour la partie
	int iCurrentWave = 1; // vague actuelle
	int iWaveIsActive = sfTrue; // actif quand une vague est en cours (reste des ennemis) non actif quand il n'y a pas de vague en cours (début de partie ou ennemis de la vague précédente au max)
	float fTimeSinceLastWave = 0; // Temps depuis la dernière vague
	//int iWaveEnnemyMaxNbr = 15; // Nombre d'ennemi max (20 pour la première puis évolue aprés chaque vagues)
	int iWaveEnnemyNbr = 0; // Nombre actuel d'ennemis apparus sur la map
	int iWaveEnnemyDead = 0; // Nombre d'ennemis morts dans la vague
	float fTimeBetweenEnnemySpawn = 0; // Temps entre ennemi (varie pour que l'apparition des ennemis soit variée)

									   /*View*/
	sfView* View = sfView_create();
	sfVector2f vSize_View = { WINDOW_WIDTH, WINDOW_HEIGHT };
	sfView_setSize(View, vSize_View);
	sfVector2f vPosition_View = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };

	/*text*/
	char* cText = malloc(50);
	sfText* Text = createText("resources/fonts/Children Stories.otf");
	sfText_setCharacterSize(Text, SIZE_TEXT);
	sfText_setFillColor(Text, sfCyan);
	sfVector2f vPositionText = { 0, 0 };
	sfVector2f vOriginText = { 0, 0 };

#pragma region BOUTONS

	t_TowerCreationBtn* btn1 = malloc(sizeof(t_TowerCreationBtn));
	btn1->sprite = createSprite("resources/textures/HUD_tower/tour1_btn.png");
	btn1->vOrigin.x = sfSprite_getGlobalBounds(btn1->sprite).width / 2;
	btn1->vOrigin.y = sfSprite_getGlobalBounds(btn1->sprite).height / 2;
	sfSprite_setOrigin(btn1->sprite, btn1->vOrigin);
	btn1->vDir.x = -0.5;
	btn1->vDir.y = -0.5;
	sfSprite_setScale(btn1->sprite, vBtnScale);
	btn1->isOver = sfFalse;

	t_TowerCreationBtn* btn2 = malloc(sizeof(t_TowerCreationBtn));
	btn2->sprite = createSprite("resources/textures/HUD_tower/tour2_btn.png");
	btn2->vOrigin.x = sfSprite_getGlobalBounds(btn2->sprite).width / 2;
	btn2->vOrigin.y = sfSprite_getGlobalBounds(btn2->sprite).height / 2;
	sfSprite_setOrigin(btn2->sprite, btn2->vOrigin);
	btn2->vDir.x = 0;
	btn2->vDir.y = -0.7;
	sfSprite_setScale(btn2->sprite, vBtnScale);
	btn2->isOver = sfFalse;

	t_TowerCreationBtn* btn3 = malloc(sizeof(t_TowerCreationBtn));
	btn3->sprite = createSprite("resources/textures/HUD_tower/tour3_btn.png");
	btn3->vOrigin.x = sfSprite_getGlobalBounds(btn3->sprite).width / 2;
	btn3->vOrigin.y = sfSprite_getGlobalBounds(btn3->sprite).height / 2;
	sfSprite_setOrigin(btn3->sprite, btn3->vOrigin);
	btn3->vDir.x = 0.5;
	btn3->vDir.y = -0.5;
	sfSprite_setScale(btn3->sprite, vBtnScale);
	btn3->isOver = sfFalse;

	t_TowerCreationBtn* btnUpgrade = malloc(sizeof(t_TowerCreationBtn));
	btnUpgrade->sprite = createSprite("resources/textures/HUD_tower/upgrade_btn.png");
	btnUpgrade->vOrigin.x = sfSprite_getGlobalBounds(btnUpgrade->sprite).width / 2;
	btnUpgrade->vOrigin.y = sfSprite_getGlobalBounds(btnUpgrade->sprite).height / 2;
	sfSprite_setOrigin(btnUpgrade->sprite, btnUpgrade->vOrigin);
	btnUpgrade->vDir.x = -0.3;
	btnUpgrade->vDir.y = -0.7;
	sfSprite_setScale(btnUpgrade->sprite, vBtnScale2);
	btnUpgrade->isOver = sfFalse;

	t_TowerCreationBtn* btnSell = malloc(sizeof(t_TowerCreationBtn));
	btnSell->sprite = createSprite("resources/textures/HUD_tower/sell_btn.png");
	btnSell->vOrigin.x = sfSprite_getGlobalBounds(btnSell->sprite).width / 2;
	btnSell->vOrigin.y = sfSprite_getGlobalBounds(btnSell->sprite).height / 2;
	sfSprite_setOrigin(btnSell->sprite, btnSell->vOrigin);
	btnSell->vDir.x = 0.3;
	btnSell->vDir.y = -0.7;
	sfSprite_setScale(btnSell->sprite, vBtnScale2);
	btnSell->isOver = sfFalse;

	sfSprite* TowerCreationCircle = createSprite("resources/textures/HUD_tower/circle.png");
	sfVector2f vOrigin_TowerCreationCircle = { sfSprite_getGlobalBounds(TowerCreationCircle).width / 2,sfSprite_getGlobalBounds(TowerCreationCircle).height / 2 };
	sfSprite_setOrigin(TowerCreationCircle, vOrigin_TowerCreationCircle);
	sfVector2f vPos_TowerCreationCircle = { 0,0 };
	sfSprite_setPosition(TowerCreationCircle, vPos_TowerCreationCircle);
	sfVector2f vScale_TowerCreationCircle = { 0,0 };
	sfSprite_setScale(TowerCreationCircle, vScale_TowerCreationCircle);

	/*Player test*/
	sfCircleShape* player = sfCircleShape_create();
	sfVector2f vPos_player = { 50,1030 };
	sfCircleShape_setRadius(player, 20);
	sfVector2f vOrigin_player = { 20,20 };
	sfCircleShape_setOrigin(player, vOrigin_player);
	sfCircleShape_setFillColor(player, sfBlue);
	sfFloatRect Rect_playerBB;

	///////////////
#pragma endregion BOUTONS

#pragma region CREATE SPRITES




#pragma endregion CREATE SPRITES

	sfColor Color_Blue = sfColor_fromRGB(0, 0, 255);
	sfColor Color_Green = sfColor_fromRGB(0, 255, 0);
	sfColor Color_Black_transp = { 0,0,0,150 };

#pragma region INIT MENU NEW //SEB

	t_MainMenu MainMenu;
	//
	MainMenu.exitSheet.sprite = createSprite("resources/textures/menuBS/menu_quitterF.png");
	MainMenu.exitSheet.vPos.x = 1148;
	MainMenu.exitSheet.vPos.y = 545;
	sfSprite_setPosition(MainMenu.exitSheet.sprite, MainMenu.exitSheet.vPos);
	MainMenu.exitSheet.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.exitSheet.sprite).width / 2;
	MainMenu.exitSheet.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.exitSheet.sprite).height / 2;
	sfSprite_setOrigin(MainMenu.exitSheet.sprite, MainMenu.exitSheet.vOrigin);
	MainMenu.exitSheet.boundingBox = sfSprite_getGlobalBounds(MainMenu.exitSheet.sprite);

	//
	MainMenu.exitLabel.sprite = createSprite("resources/textures/menuBS/menu_quitter.png");
	MainMenu.exitLabel.vPos.x = 394.5;
	MainMenu.exitLabel.vPos.y = 553.5;
	sfSprite_setPosition(MainMenu.exitLabel.sprite, MainMenu.exitLabel.vPos);
	MainMenu.exitLabel.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.exitLabel.sprite).width / 2;
	MainMenu.exitLabel.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.exitLabel.sprite).height / 2;
	sfSprite_setOrigin(MainMenu.exitLabel.sprite, MainMenu.exitLabel.vOrigin);
	MainMenu.exitLabel.boundingBox = sfSprite_getGlobalBounds(MainMenu.exitLabel.sprite);

	//
	MainMenu.exitNo.sprite = createSprite("resources/textures/menuBS/menu_quitter_non.png");
	MainMenu.exitNo.vPos.x = 1131.5;
	MainMenu.exitNo.vPos.y = 759.5;
	sfSprite_setPosition(MainMenu.exitNo.sprite, MainMenu.exitNo.vPos);
	MainMenu.exitNo.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.exitNo.sprite).width / 2;
	MainMenu.exitNo.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.exitNo.sprite).height / 2;
	sfSprite_setOrigin(MainMenu.exitNo.sprite, MainMenu.exitNo.vOrigin);
	MainMenu.exitNo.boundingBox = sfSprite_getGlobalBounds(MainMenu.exitNo.sprite);

	//
	MainMenu.exitYes.sprite = createSprite("resources/textures/menuBS/menu_quitter_oui.png");
	MainMenu.exitYes.vPos.x = 1105.5;
	MainMenu.exitYes.vPos.y = 447;
	sfSprite_setPosition(MainMenu.exitYes.sprite, MainMenu.exitYes.vPos);
	MainMenu.exitYes.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.exitYes.sprite).width / 2;
	MainMenu.exitYes.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.exitYes.sprite).height / 2;
	sfSprite_setOrigin(MainMenu.exitYes.sprite, MainMenu.exitYes.vOrigin);
	MainMenu.exitYes.boundingBox = sfSprite_getGlobalBounds(MainMenu.exitYes.sprite);

	//
	MainMenu.creditsSheet.sprite = createSprite("resources/textures/menuBS/menu_creditsF.png");
	MainMenu.creditsSheet.vPos.x = 1129;
	MainMenu.creditsSheet.vPos.y = 551;
	sfSprite_setPosition(MainMenu.creditsSheet.sprite, MainMenu.creditsSheet.vPos);
	MainMenu.creditsSheet.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.creditsSheet.sprite).width / 2;
	MainMenu.creditsSheet.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.creditsSheet.sprite).height / 2;
	sfSprite_setOrigin(MainMenu.creditsSheet.sprite, MainMenu.creditsSheet.vOrigin);
	MainMenu.creditsSheet.boundingBox = sfSprite_getGlobalBounds(MainMenu.creditsSheet.sprite);

	//
	MainMenu.creditsLabel.sprite = createSprite("resources/textures/menuBS/menu_credits.png");
	MainMenu.creditsLabel.vPos.x = 315;
	MainMenu.creditsLabel.vPos.y = 375;
	sfSprite_setPosition(MainMenu.creditsLabel.sprite, MainMenu.creditsLabel.vPos);
	MainMenu.creditsLabel.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.creditsLabel.sprite).width / 2;
	MainMenu.creditsLabel.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.creditsLabel.sprite).height / 2;
	sfSprite_setOrigin(MainMenu.creditsLabel.sprite, MainMenu.creditsLabel.vOrigin);
	MainMenu.creditsLabel.boundingBox = sfSprite_getGlobalBounds(MainMenu.creditsLabel.sprite);

	//
	MainMenu.startSheet.sprite = createSprite("resources/textures/menuBS/menu_commencerF.png");
	MainMenu.startSheet.vPos.x = 1127.5;
	MainMenu.startSheet.vPos.y = 567;
	sfSprite_setPosition(MainMenu.startSheet.sprite, MainMenu.startSheet.vPos);
	MainMenu.startSheet.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.startSheet.sprite).width / 2;
	MainMenu.startSheet.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.startSheet.sprite).height / 2;
	sfSprite_setOrigin(MainMenu.startSheet.sprite, MainMenu.startSheet.vOrigin);
	MainMenu.startSheet.boundingBox = sfSprite_getGlobalBounds(MainMenu.startSheet.sprite);

	//
	MainMenu.startLabel.sprite = createSprite("resources/textures/menuBS/menu_commencer.png");
	MainMenu.startLabel.vPos.x = 267.5;
	MainMenu.startLabel.vPos.y = 201;
	sfSprite_setPosition(MainMenu.startLabel.sprite, MainMenu.startLabel.vPos);
	MainMenu.startLabel.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.startLabel.sprite).width / 2;
	MainMenu.startLabel.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.startLabel.sprite).height / 2;
	sfSprite_setOrigin(MainMenu.startLabel.sprite, MainMenu.startLabel.vOrigin);
	MainMenu.startLabel.boundingBox = sfSprite_getGlobalBounds(MainMenu.startLabel.sprite);

	//
	MainMenu.saveSlot1.sprite = createSprite("resources/textures/menuBS/menu_slot_save1.png");
	MainMenu.saveSlot1.vPos.x = 1022;
	MainMenu.saveSlot1.vPos.y = 307.5;
	sfSprite_setPosition(MainMenu.saveSlot1.sprite, MainMenu.saveSlot1.vPos);
	MainMenu.saveSlot1.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.saveSlot1.sprite).width / 2;
	MainMenu.saveSlot1.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.saveSlot1.sprite).height / 2;
	sfSprite_setOrigin(MainMenu.saveSlot1.sprite, MainMenu.saveSlot1.vOrigin);
	MainMenu.saveSlot1.boundingBox = sfSprite_getGlobalBounds(MainMenu.saveSlot1.sprite);

	//
	MainMenu.saveSlot2.sprite = createSprite("resources/textures/menuBS/menu_slot_save2.png");
	MainMenu.saveSlot2.vPos.x = 1024;
	MainMenu.saveSlot2.vPos.y = 570.5;
	sfSprite_setPosition(MainMenu.saveSlot2.sprite, MainMenu.saveSlot2.vPos);
	MainMenu.saveSlot2.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.saveSlot2.sprite).width / 2;
	MainMenu.saveSlot2.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.saveSlot2.sprite).height / 2;
	sfSprite_setOrigin(MainMenu.saveSlot2.sprite, MainMenu.saveSlot2.vOrigin);
	MainMenu.saveSlot2.boundingBox = sfSprite_getGlobalBounds(MainMenu.saveSlot2.sprite);

	//
	MainMenu.saveSlot3.sprite = createSprite("resources/textures/menuBS/menu_slot_save3.png");
	MainMenu.saveSlot3.vPos.x = 1012;
	MainMenu.saveSlot3.vPos.y = 834.5;
	sfSprite_setPosition(MainMenu.saveSlot3.sprite, MainMenu.saveSlot3.vPos);
	MainMenu.saveSlot3.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.saveSlot3.sprite).width / 2;
	MainMenu.saveSlot3.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.saveSlot3.sprite).height / 2;
	sfSprite_setOrigin(MainMenu.saveSlot3.sprite, MainMenu.saveSlot3.vOrigin);
	MainMenu.saveSlot3.boundingBox = sfSprite_getGlobalBounds(MainMenu.saveSlot3.sprite);

	//
	MainMenu.LogoSheet.sprite = createSprite("resources/textures/menuBS/menu_logo.png");
	MainMenu.LogoSheet.vPos.x = 1151;
	MainMenu.LogoSheet.vPos.y = 561.5;
	sfSprite_setPosition(MainMenu.LogoSheet.sprite, MainMenu.LogoSheet.vPos);
	MainMenu.LogoSheet.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.LogoSheet.sprite).width / 2;
	MainMenu.LogoSheet.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.LogoSheet.sprite).height / 2;
	sfSprite_setOrigin(MainMenu.LogoSheet.sprite, MainMenu.LogoSheet.vOrigin);
	MainMenu.LogoSheet.boundingBox = sfSprite_getGlobalBounds(MainMenu.LogoSheet.sprite);

	//
	MainMenu.paperClip.sprite = createSprite("resources/textures/menuBS/menu_trombone.png");
	MainMenu.paperClip.vPos.x = 956.5;
	MainMenu.paperClip.vPos.y = 58.5;
	sfSprite_setPosition(MainMenu.paperClip.sprite, MainMenu.paperClip.vPos);
	MainMenu.paperClip.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.paperClip.sprite).width / 2;
	MainMenu.paperClip.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.paperClip.sprite).height / 2;
	sfSprite_setOrigin(MainMenu.paperClip.sprite, MainMenu.paperClip.vOrigin);
	MainMenu.paperClip.boundingBox = sfSprite_getGlobalBounds(MainMenu.paperClip.sprite);

	//
	MainMenu.startSheetLS.sprite = createSprite("resources/textures/menuBS/menu_commencerF2.png");
	MainMenu.startSheetLS.vPos.x = 1150;
	MainMenu.startSheetLS.vPos.y = 561.5;
	sfSprite_setPosition(MainMenu.startSheetLS.sprite, MainMenu.startSheetLS.vPos);
	MainMenu.startSheetLS.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.startSheetLS.sprite).width / 2;
	MainMenu.startSheetLS.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.startSheetLS.sprite).height / 2;
	sfSprite_setOrigin(MainMenu.startSheetLS.sprite, MainMenu.startSheetLS.vOrigin);
	MainMenu.startSheetLS.boundingBox = sfSprite_getGlobalBounds(MainMenu.startSheetLS.sprite);

	MainMenu.labelMask = sfImage_createFromFile("resources/textures/menuBS/menu_mask.psd");
	MainMenu.levelMask = sfImage_createFromFile("resources/textures/menuBS/menu_mask_level.psd");
	MainMenu.exitMask = sfImage_createFromFile("resources/textures/menuBS/menu_mask_quitter.psd");
	MainMenu.saveMask = sfImage_createFromFile("resources/textures/menuBS/menu_mask_save.psd");

	FILE* savFile;
	fopen_s(&savFile, "resources/datas/saves/save_slot1.txt", "r");
	if (savFile == NULL)
	{
		printf_s("erreur ouverture save\n");
	}
	fscanf_s(savFile, "unlockedLevels=%d", &unLockedLevelsSolt1);
	fclose(savFile);
	fopen_s(&savFile, "resources/datas/saves/save_slot2.txt", "r");
	if (savFile == NULL)
	{
		printf_s("erreur ouverture save\n");
	}
	fscanf_s(savFile, "unlockedLevels=%d", &unLockedLevelsSolt2);
	fclose(savFile);
	fopen_s(&savFile, "resources/datas/saves/save_slot3.txt", "r");
	if (savFile == NULL)
	{
		printf_s("erreur ouverture save\n");
	}
	fscanf_s(savFile, "unlockedLevels=%d", &unLockedLevelsSolt3);
	fclose(savFile);

	/*slot 1*/
	if (unLockedLevelsSolt1 == 0)
	{
		MainMenu.miniMapSlot1.sprite = createSprite("resources/textures/level_selector/miniMap_Level0.png");
		MainMenu.miniMapSlot1.vPos.x = 1668;
		MainMenu.miniMapSlot1.vPos.y = 317.5;
		sfSprite_setPosition(MainMenu.miniMapSlot1.sprite, MainMenu.miniMapSlot1.vPos);
		MainMenu.miniMapSlot1.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.miniMapSlot1.sprite).width / 2;
		MainMenu.miniMapSlot1.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.miniMapSlot1.sprite).height / 2;
		sfSprite_setOrigin(MainMenu.miniMapSlot1.sprite, MainMenu.miniMapSlot1.vOrigin);
		MainMenu.miniMapSlot1.boundingBox = sfSprite_getGlobalBounds(MainMenu.miniMapSlot1.sprite);
	}
	else if (unLockedLevelsSolt1 == 1)
	{
		MainMenu.miniMapSlot1.sprite = createSprite("resources/textures/level_selector/miniMap_Level1.png");
		MainMenu.miniMapSlot1.vPos.x = 1668;
		MainMenu.miniMapSlot1.vPos.y = 317.5;
		sfSprite_setPosition(MainMenu.miniMapSlot1.sprite, MainMenu.miniMapSlot1.vPos);
		MainMenu.miniMapSlot1.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.miniMapSlot1.sprite).width / 2;
		MainMenu.miniMapSlot1.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.miniMapSlot1.sprite).height / 2;
		sfSprite_setOrigin(MainMenu.miniMapSlot1.sprite, MainMenu.miniMapSlot1.vOrigin);
		MainMenu.miniMapSlot1.boundingBox = sfSprite_getGlobalBounds(MainMenu.miniMapSlot1.sprite);
	}
	else if (unLockedLevelsSolt1 == 2)
	{
		MainMenu.miniMapSlot1.sprite = createSprite("resources/textures/level_selector/miniMap_Level2.png");
		MainMenu.miniMapSlot1.vPos.x = 1668;
		MainMenu.miniMapSlot1.vPos.y = 317.5;
		sfSprite_setPosition(MainMenu.miniMapSlot1.sprite, MainMenu.miniMapSlot1.vPos);
		MainMenu.miniMapSlot1.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.miniMapSlot1.sprite).width / 2;
		MainMenu.miniMapSlot1.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.miniMapSlot1.sprite).height / 2;
		sfSprite_setOrigin(MainMenu.miniMapSlot1.sprite, MainMenu.miniMapSlot1.vOrigin);
		MainMenu.miniMapSlot1.boundingBox = sfSprite_getGlobalBounds(MainMenu.miniMapSlot1.sprite);
	}

	/*slot 2*/
	if (unLockedLevelsSolt2 == 0)
	{
		MainMenu.miniMapSlot2.sprite = createSprite("resources/textures/level_selector/miniMap_Level0.png");
		MainMenu.miniMapSlot2.vPos.x = 1661;
		MainMenu.miniMapSlot2.vPos.y = 576.5;
		sfSprite_setPosition(MainMenu.miniMapSlot2.sprite, MainMenu.miniMapSlot2.vPos);
		MainMenu.miniMapSlot2.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.miniMapSlot2.sprite).width / 2;
		MainMenu.miniMapSlot2.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.miniMapSlot2.sprite).height / 2;
		sfSprite_setOrigin(MainMenu.miniMapSlot2.sprite, MainMenu.miniMapSlot2.vOrigin);
		MainMenu.miniMapSlot2.boundingBox = sfSprite_getGlobalBounds(MainMenu.miniMapSlot2.sprite);
	}
	else if (unLockedLevelsSolt2 == 1)
	{
		MainMenu.miniMapSlot2.sprite = createSprite("resources/textures/level_selector/miniMap_Level1.png");
		MainMenu.miniMapSlot2.vPos.x = 1661;
		MainMenu.miniMapSlot2.vPos.y = 576.5;
		sfSprite_setPosition(MainMenu.miniMapSlot2.sprite, MainMenu.miniMapSlot2.vPos);
		MainMenu.miniMapSlot2.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.miniMapSlot2.sprite).width / 2;
		MainMenu.miniMapSlot2.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.miniMapSlot2.sprite).height / 2;
		sfSprite_setOrigin(MainMenu.miniMapSlot2.sprite, MainMenu.miniMapSlot2.vOrigin);
		MainMenu.miniMapSlot2.boundingBox = sfSprite_getGlobalBounds(MainMenu.miniMapSlot2.sprite);
	}
	else if (unLockedLevelsSolt2 == 2)
	{
		MainMenu.miniMapSlot2.sprite = createSprite("resources/textures/level_selector/miniMap_Level2.png");
		MainMenu.miniMapSlot2.vPos.x = 1661;
		MainMenu.miniMapSlot2.vPos.y = 576.5;
		sfSprite_setPosition(MainMenu.miniMapSlot2.sprite, MainMenu.miniMapSlot2.vPos);
		MainMenu.miniMapSlot2.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.miniMapSlot2.sprite).width / 2;
		MainMenu.miniMapSlot2.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.miniMapSlot2.sprite).height / 2;
		sfSprite_setOrigin(MainMenu.miniMapSlot2.sprite, MainMenu.miniMapSlot2.vOrigin);
		MainMenu.miniMapSlot2.boundingBox = sfSprite_getGlobalBounds(MainMenu.miniMapSlot2.sprite);
	}

	/*slot3*/
	if (unLockedLevelsSolt3 == 0)
	{
		MainMenu.miniMapSlot3.sprite = createSprite("resources/textures/level_selector/miniMap_Level0.png");
		MainMenu.miniMapSlot3.vPos.x = 1658;
		MainMenu.miniMapSlot3.vPos.y = 850;
		sfSprite_setPosition(MainMenu.miniMapSlot3.sprite, MainMenu.miniMapSlot3.vPos);
		MainMenu.miniMapSlot3.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.miniMapSlot3.sprite).width / 2;
		MainMenu.miniMapSlot3.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.miniMapSlot3.sprite).height / 2;
		sfSprite_setOrigin(MainMenu.miniMapSlot3.sprite, MainMenu.miniMapSlot3.vOrigin);
		MainMenu.miniMapSlot3.boundingBox = sfSprite_getGlobalBounds(MainMenu.miniMapSlot3.sprite);
	}
	else if (unLockedLevelsSolt3 == 1)
	{
		MainMenu.miniMapSlot3.sprite = createSprite("resources/textures/level_selector/miniMap_Level1.png");
		MainMenu.miniMapSlot3.vPos.x = 1658;
		MainMenu.miniMapSlot3.vPos.y = 850;
		sfSprite_setPosition(MainMenu.miniMapSlot3.sprite, MainMenu.miniMapSlot3.vPos);
		MainMenu.miniMapSlot3.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.miniMapSlot3.sprite).width / 2;
		MainMenu.miniMapSlot3.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.miniMapSlot3.sprite).height / 2;
		sfSprite_setOrigin(MainMenu.miniMapSlot3.sprite, MainMenu.miniMapSlot3.vOrigin);
		MainMenu.miniMapSlot3.boundingBox = sfSprite_getGlobalBounds(MainMenu.miniMapSlot3.sprite);
	}
	else if (unLockedLevelsSolt3 == 2)
	{
		MainMenu.miniMapSlot3.sprite = createSprite("resources/textures/level_selector/miniMap_Level2.png");
		MainMenu.miniMapSlot3.vPos.x = 1658;
		MainMenu.miniMapSlot3.vPos.y = 850;
		sfSprite_setPosition(MainMenu.miniMapSlot3.sprite, MainMenu.miniMapSlot3.vPos);
		MainMenu.miniMapSlot3.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.miniMapSlot3.sprite).width / 2;
		MainMenu.miniMapSlot3.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.miniMapSlot3.sprite).height / 2;
		sfSprite_setOrigin(MainMenu.miniMapSlot3.sprite, MainMenu.miniMapSlot3.vOrigin);
		MainMenu.miniMapSlot3.boundingBox = sfSprite_getGlobalBounds(MainMenu.miniMapSlot3.sprite);
	}

	//
	MainMenu.level1Icon.sprite = createSprite("resources/textures/menuBS/menu_level1.png");
	MainMenu.level1Icon.vPos.x = 1187.74;
	MainMenu.level1Icon.vPos.y = 721.5;
	sfSprite_setPosition(MainMenu.level1Icon.sprite, MainMenu.level1Icon.vPos);
	MainMenu.level1Icon.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.level1Icon.sprite).width / 2;
	MainMenu.level1Icon.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.level1Icon.sprite).height / 2;
	sfSprite_setOrigin(MainMenu.level1Icon.sprite, MainMenu.level1Icon.vOrigin);
	MainMenu.level1Icon.boundingBox = sfSprite_getGlobalBounds(MainMenu.level1Icon.sprite);

	//
	MainMenu.level2Icon.sprite = createSprite("resources/textures/menuBS/menu_level2.png");
	MainMenu.level2Icon.vPos.x = 1213.5;
	MainMenu.level2Icon.vPos.y = 517;
	sfSprite_setPosition(MainMenu.level2Icon.sprite, MainMenu.level2Icon.vPos);
	MainMenu.level2Icon.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.level2Icon.sprite).width / 2;
	MainMenu.level2Icon.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.level2Icon.sprite).height / 2;
	sfSprite_setOrigin(MainMenu.level2Icon.sprite, MainMenu.level2Icon.vOrigin);
	MainMenu.level2Icon.boundingBox = sfSprite_getGlobalBounds(MainMenu.level2Icon.sprite);

	//
	MainMenu.brain.sprite = createSprite("resources/textures/menuBS/menu_pierrot.png");
	MainMenu.brain.vPos.x = 236;
	MainMenu.brain.vPos.y = 929;
	sfSprite_setPosition(MainMenu.brain.sprite, MainMenu.brain.vPos);
	MainMenu.brain.vOrigin.x = sfSprite_getGlobalBounds(MainMenu.brain.sprite).width / 2;
	MainMenu.brain.vOrigin.y = sfSprite_getGlobalBounds(MainMenu.brain.sprite).height / 2;
	sfSprite_setOrigin(MainMenu.brain.sprite, MainMenu.brain.vOrigin);
	MainMenu.brain.boundingBox = sfSprite_getGlobalBounds(MainMenu.brain.sprite);

	MainMenu.background.sprite = createSprite("resources/textures/menuBS/menu_background.png");

#pragma endregion INIT MENU NEW //SEB

#pragma region HUD INIT //SEB

	t_Hud Hud;

	//
	Hud.lifePoints.sprite = createSprite("resources/textures/HUD/Cerveau.png");
	Hud.lifePoints.vOrigin.x = sfSprite_getLocalBounds(Hud.lifePoints.sprite).width / 2;
	Hud.lifePoints.vOrigin.y = sfSprite_getLocalBounds(Hud.lifePoints.sprite).height / 2;
	sfSprite_setOrigin(Hud.lifePoints.sprite, Hud.lifePoints.vOrigin);
	Hud.lifePoints.vPos.x = 96;
	Hud.lifePoints.vPos.y = 91;
	sfSprite_setPosition(Hud.lifePoints.sprite, Hud.lifePoints.vPos);
	printf_s("origin x : %.2f ,y : %.2f\n", Hud.lifePoints.vOrigin.x, Hud.lifePoints.vOrigin.y);

	//
	Hud.money.sprite = createSprite("resources/textures/HUD/Globule_Rouge.png");
	Hud.money.vOrigin.x = sfSprite_getLocalBounds(Hud.money.sprite).width / 2;
	Hud.money.vOrigin.y = sfSprite_getLocalBounds(Hud.money.sprite).height / 2;
	sfSprite_setOrigin(Hud.money.sprite, Hud.money.vOrigin);
	Hud.money.vPos.x = 1826;
	Hud.money.vPos.y = 105;
	sfSprite_setPosition(Hud.money.sprite, Hud.money.vPos);

	//
	Hud.waves.sprite = createSprite("resources/textures/HUD/Affichage_Vague.png");
	Hud.waves.vOrigin.x = sfSprite_getLocalBounds(Hud.waves.sprite).width / 2;
	Hud.waves.vOrigin.y = sfSprite_getLocalBounds(Hud.waves.sprite).height / 2;
	sfSprite_setOrigin(Hud.waves.sprite, Hud.waves.vOrigin);
	Hud.waves.vPos.x = 103;
	Hud.waves.vPos.y = 215;
	sfSprite_setPosition(Hud.waves.sprite, Hud.waves.vPos);

#pragma endregion HUD INIT //SEB

#pragma region INTRO INIT //SEB

	t_intro intro;

	intro.academy.sprite = createSprite("resources/textures/intro/academy.png");
	intro.academy.vOrigin.x = sfSprite_getGlobalBounds(intro.academy.sprite).width / 2;
	intro.academy.vOrigin.y = sfSprite_getGlobalBounds(intro.academy.sprite).height / 2;
	sfSprite_setOrigin(intro.academy.sprite, intro.academy.vOrigin);
	intro.academy.vPos.x = 2343;
	intro.academy.vPos.y = 999.5;
	sfSprite_setPosition(intro.academy.sprite, intro.academy.vPos);

	intro.game.sprite = createSprite("resources/textures/intro/game.png");
	intro.game.vOrigin.x = sfSprite_getGlobalBounds(intro.game.sprite).width / 2;
	intro.game.vOrigin.y = sfSprite_getGlobalBounds(intro.game.sprite).height / 2;
	sfSprite_setOrigin(intro.game.sprite, intro.game.vOrigin);
	intro.game.vPos.x = -430;
	intro.game.vPos.y = 816;
	sfSprite_setPosition(intro.game.sprite, intro.game.vPos);

	intro.logo.sprite = createSprite("resources/textures/intro/logo.png");
	intro.logo.vOrigin.x = sfSprite_getGlobalBounds(intro.logo.sprite).width / 2;
	intro.logo.vOrigin.y = sfSprite_getGlobalBounds(intro.logo.sprite).height / 2;
	sfSprite_setOrigin(intro.logo.sprite, intro.logo.vOrigin);
	intro.logo.vPos.x = 960;
	intro.logo.vPos.y = 344;
	sfSprite_setPosition(intro.logo.sprite, intro.logo.vPos);
	intro.logo.vSize.x = 0;
	intro.logo.vSize.y = 0;
	sfSprite_setScale(intro.logo.sprite, intro.logo.vSize);

	intro.vSizeMax.x = 1.2;
	intro.vSizeMax.y = 1.2;

	int beatCount = 0;
	int dir = 0;
	intro.state = IS_GAME_MOVING;


#pragma endregion INTRO INIT //SEB

#pragma region DEBUG

	sfVertexArray* VertexArray = sfVertexArray_create();
	sfVertex* Vertex = malloc(sizeof(Vertex));

#pragma endregion DEBUG

#pragma region VARIABLES ADD ENNEMY //GUILLAUME
	int iNbrCancer = 0;
	int iNbrCholesterol = 0;
	int iNbrCaillot = 0;
	int iNbrTotal = 0;
	int iCurrentNbrCancer = 0;
	int iCurrentNbrCholesterol = 0;
	int iCurrentNbrCaillot = 0;
#pragma endregion VARIABLES ADD ENNEMY //GUILLAUME

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////// GAME LOOP ///////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while (sfRenderWindow_isOpen(window))
	{
		/* Process events */
		while (sfRenderWindow_pollEvent(window, &event))
		{
			/* Close window : exit */
			if (event.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue)
				sfRenderWindow_close(window);
			// The window got the focus
			else if (event.type == sfEvtGainedFocus)
				isWindowActive = sfTrue;
			// The window lost the focus
			else if (event.type == sfEvtLostFocus)
				isWindowActive = sfFalse;
		}
		/* Clear the screen */
		sfRenderWindow_clear(window, sfBlack);


		//////////////////////// GAME STATE //////////////////////

		switch (GameState)
		{

#pragma region CASE INTRO
		case INTRO:
			if (intro.state == IS_GAME_MOVING)
			{

				if (intro.game.vPos.x < 960)
				{
					intro.game.vPos.x += 20;
				}
				else
				{
					intro.game.vPos.x = 960;
					intro.state = IS_ACADEMY_MOVING;

				}
				sfSprite_setPosition(intro.game.sprite, intro.game.vPos);
			}
			if (intro.state == IS_ACADEMY_MOVING)
			{
				if (intro.academy.vPos.x > 960)
				{
					printf_s("Game move\n");
					intro.academy.vPos.x -= 20;
				}
				else
				{
					intro.academy.vPos.x = 960;
					intro.state = IS_LOGO_GROWING;
				}
				sfSprite_setPosition(intro.academy.sprite, intro.academy.vPos);
			}

			if (intro.state == IS_LOGO_GROWING)
			{
				if (intro.logo.vSize.x < 1)
				{
					intro.logo.vSize.x += 0.01;
					intro.logo.vSize.y += 0.01;
				}
				else
				{
					intro.logo.vSize.x = 1;
					intro.logo.vSize.y = 1;
					intro.state = IS_LOGO_BEATING;
				}
				sfSprite_setScale(intro.logo.sprite, intro.logo.vSize);
			}

			if (intro.state == IS_LOGO_BEATING)
			{
				if (dir == 0)
				{
					if (intro.logo.vSize.x < intro.vSizeMax.x  && intro.logo.vSize.y < intro.vSizeMax.y)
					{
						intro.logo.vSize.x += 0.01;
						intro.logo.vSize.y += 0.01;
					}
					else
					{
						intro.logo.vSize = intro.vSizeMax;
						dir = 1;
					}
				}
				if (dir == 1)
				{
					if (intro.logo.vSize.x > 1 && intro.logo.vSize.y > 1)
					{
						intro.logo.vSize.x -= 0.005;
						intro.logo.vSize.y -= 0.005;
					}
					else
					{
						beatCount++;
						intro.logo.vSize.x = 1;
						intro.logo.vSize.y = 1;
						dir = 0;
					}
				}
				if (beatCount == 5)
				{
					GameState = MENU;
				}

				sfSprite_setScale(intro.logo.sprite, intro.logo.vSize);
			}
			sfRenderWindow_drawSprite(window, intro.game.sprite, NULL);
			sfRenderWindow_drawSprite(window, intro.logo.sprite, NULL);
			sfRenderWindow_drawSprite(window, intro.academy.sprite, NULL);
			break;
#pragma endregion CASE INTRO

#pragma region CASE MENU
		case MENU:
			vMousePos = sfMouse_getPosition(window);
			vMousePosToFloat.x = (float)vMousePos.x;
			vMousePosToFloat.y = (float)vMousePos.y;
			sfRenderWindow_drawSprite(window, MainMenu.background.sprite, NULL);
			switch (mainMenuState)
			{

#pragma region ON_LOGO
			case ON_LOGO:

				if (vMousePos.x >= 0 && vMousePos.x <= LABEL_MASK_WIDTH && vMousePos.y >= 0 && vMousePos.y <= LABEL_MASK_HEIGHT)
				{
					/*Commencer*/
					if (sfFloatRect_contains(&MainMenu.startLabel.boundingBox, vMousePos.x, vMousePos.y))
					{
						if (sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).r == 255 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).g == 0
							&& sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).b == 0 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).a == 255)
						{
							sfSprite_setColor(MainMenu.startLabel.sprite, sfRed);
							if (sfMouse_isButtonPressed(sfMouseLeft && !isMousePressed))
							{
								isMousePressed = sfTrue;
								mainMenuNextState = ON_START;
								mainMenuState = ON_LOGO_TRANSITION;
								sfSprite_setColor(MainMenu.startLabel.sprite, sfWhite);
							}
						}
						else
						{
							sfSprite_setColor(MainMenu.startLabel.sprite, sfWhite);
						}
					}
					else
					{
						sfSprite_setColor(MainMenu.startLabel.sprite, sfWhite);
					}

					/*Credits*/
					if (sfFloatRect_contains(&MainMenu.creditsLabel.boundingBox, vMousePos.x, vMousePos.y))
					{
						if (sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).r == 255 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).g == 0
							&& sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).b == 0 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).a == 255)
						{
							sfSprite_setColor(MainMenu.creditsLabel.sprite, sfRed);
							if (sfMouse_isButtonPressed(sfMouseLeft && !isMousePressed))
							{
								isMousePressed = sfTrue;
								mainMenuNextState = ON_CREDITS;
								mainMenuState = ON_LOGO_TRANSITION;
								sfSprite_setColor(MainMenu.creditsLabel.sprite, sfWhite);
							}
						}
						else
						{
							sfSprite_setColor(MainMenu.creditsLabel.sprite, sfWhite);
						}
					}
					else
					{
						sfSprite_setColor(MainMenu.creditsLabel.sprite, sfWhite);
					}
					/*Quitter*/
					if (sfFloatRect_contains(&MainMenu.exitLabel.boundingBox, vMousePos.x, vMousePos.y))
					{
						if (sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).r == 255 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).g == 0
							&& sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).b == 0 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).a == 255)
						{
							sfSprite_setColor(MainMenu.exitLabel.sprite, sfRed);
							if (sfMouse_isButtonPressed(sfMouseLeft && !isMousePressed))
							{
								isMousePressed = sfTrue;
								mainMenuNextState = ON_EXIT;
								mainMenuState = ON_LOGO_TRANSITION;
								sfSprite_setColor(MainMenu.exitLabel.sprite, sfWhite);
							}
						}
						else
						{
							sfSprite_setColor(MainMenu.exitLabel.sprite, sfWhite);
						}
					}
					else
					{
						sfSprite_setColor(MainMenu.exitLabel.sprite, sfWhite);
					}
				}

				sfRenderWindow_drawSprite(window, MainMenu.exitSheet.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.exitLabel.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.creditsSheet.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.creditsLabel.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.startSheetLS.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.startSheet.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.startLabel.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.LogoSheet.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.paperClip.sprite, NULL);
				break;

#pragma endregion ON_LOGO

#pragma region ON_LOGO_TRANSITION
			case ON_LOGO_TRANSITION:
				if (MainMenu.paperClip.vPos.y > -60 || MainMenu.LogoSheet.vPos.y < 1840)
				{
					if (MainMenu.paperClip.vPos.y > -60)
					{
						MainMenu.paperClip.vPos.x -= 3;
						MainMenu.paperClip.vPos.y -= 5;
						sfSprite_setPosition(MainMenu.paperClip.sprite, MainMenu.paperClip.vPos);
					}
					else if (MainMenu.LogoSheet.vPos.y < 1840)
					{
						MainMenu.LogoSheet.vPos.x += 2 * testincreaseX;
						MainMenu.LogoSheet.vPos.y += 6 * testincreaseY;
						testincreaseX += 0.05;
						testincreaseY += 00.1;
						sfSprite_setPosition(MainMenu.LogoSheet.sprite, MainMenu.LogoSheet.vPos);
					}
				}
				else
				{
					mainMenuState = mainMenuNextState;
				}
				switch (mainMenuNextState)
				{
				case ON_START:
					MainMenu.startSheet.vPos.x = 1127.5;
					MainMenu.startSheet.vPos.y = 567;
					MainMenu.saveSlot1.vPos.x = 1022;
					MainMenu.saveSlot1.vPos.y = 307.5;
					MainMenu.saveSlot2.vPos.x = 1024;
					MainMenu.saveSlot2.vPos.y = 570.5;
					MainMenu.saveSlot3.vPos.x = 1012;
					MainMenu.saveSlot3.vPos.y = 834.5;
					MainMenu.miniMapSlot1.vPos.x = 1668;
					MainMenu.miniMapSlot1.vPos.y = 317.5;
					MainMenu.miniMapSlot2.vPos.x = 1661;
					MainMenu.miniMapSlot2.vPos.y = 576.5;
					MainMenu.miniMapSlot3.vPos.x = 1658;
					MainMenu.miniMapSlot3.vPos.y = 850;
					sfSprite_setPosition(MainMenu.miniMapSlot1.sprite, MainMenu.miniMapSlot1.vPos);
					sfSprite_setPosition(MainMenu.miniMapSlot2.sprite, MainMenu.miniMapSlot2.vPos);
					sfSprite_setPosition(MainMenu.miniMapSlot3.sprite, MainMenu.miniMapSlot3.vPos);
					sfSprite_setPosition(MainMenu.startSheet.sprite, MainMenu.startSheet.vPos);
					sfSprite_setPosition(MainMenu.saveSlot1.sprite, MainMenu.saveSlot1.vPos);
					sfSprite_setPosition(MainMenu.saveSlot2.sprite, MainMenu.saveSlot2.vPos);
					sfSprite_setPosition(MainMenu.saveSlot3.sprite, MainMenu.saveSlot3.vPos);
					sfRenderWindow_drawSprite(window, MainMenu.exitSheet.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.exitLabel.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.creditsSheet.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.creditsLabel.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.startSheetLS.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.startSheet.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.miniMapSlot1.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.miniMapSlot2.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.miniMapSlot3.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.startLabel.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.saveSlot1.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.saveSlot2.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.saveSlot3.sprite, NULL);
					break;
				case ON_CREDITS:
					sfRenderWindow_drawSprite(window, MainMenu.startSheetLS.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.startSheet.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.startLabel.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.exitSheet.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.exitLabel.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.creditsSheet.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.creditsLabel.sprite, NULL);
					break;
				case ON_EXIT:
					sfRenderWindow_drawSprite(window, MainMenu.startSheetLS.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.startSheet.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.startLabel.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.creditsSheet.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.creditsLabel.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.exitSheet.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.exitLabel.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.exitYes.sprite, NULL);
					sfRenderWindow_drawSprite(window, MainMenu.exitNo.sprite, NULL);
					break;
				default:
					break;
				}
				sfRenderWindow_drawSprite(window, MainMenu.LogoSheet.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.paperClip.sprite, NULL);
				break;

#pragma endregion ON_LOGO_TRANSITION

#pragma region ON_START
			case ON_START:

				if (vMousePos.x >= 0 && vMousePos.x <= LABEL_MASK_WIDTH && vMousePos.y >= 0 && vMousePos.y <= LABEL_MASK_HEIGHT)
				{
					/*Credits*/
					if (sfFloatRect_contains(&MainMenu.creditsLabel.boundingBox, vMousePos.x, vMousePos.y))
					{
						if (sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).r == 255 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).g == 0
							&& sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).b == 0 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).a == 255)
						{
							sfSprite_setColor(MainMenu.creditsLabel.sprite, sfRed);
							if (sfMouse_isButtonPressed(sfMouseLeft && !isMousePressed))
							{
								isMousePressed = sfTrue;
								mainMenuState = ON_CREDITS;
								sfSprite_setColor(MainMenu.creditsLabel.sprite, sfWhite);
							}
						}
						else
						{
							sfSprite_setColor(MainMenu.creditsLabel.sprite, sfWhite);
						}
					}
					else
					{
						sfSprite_setColor(MainMenu.creditsLabel.sprite, sfWhite);
					}
					/*Quitter*/
					if (sfFloatRect_contains(&MainMenu.exitLabel.boundingBox, vMousePos.x, vMousePos.y))
					{
						if (sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).r == 255 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).g == 0
							&& sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).b == 0 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).a == 255)
						{
							sfSprite_setColor(MainMenu.exitLabel.sprite, sfRed);
							if (sfMouse_isButtonPressed(sfMouseLeft && !isMousePressed))
							{
								isMousePressed = sfTrue;
								mainMenuState = ON_EXIT;
								sfSprite_setColor(MainMenu.exitLabel.sprite, sfWhite);
							}
						}
						else
						{
							sfSprite_setColor(MainMenu.exitLabel.sprite, sfWhite);
						}
					}
					else
					{
						sfSprite_setColor(MainMenu.exitLabel.sprite, sfWhite);
					}
				}


				if (vMousePos.x >= 0 && vMousePos.x <= 1920 && vMousePos.y >= 0 && vMousePos.y <= 1080)
				{
					/*Slot1*/
					if (sfFloatRect_contains(&MainMenu.saveSlot1.boundingBox, vMousePos.x, vMousePos.y))
					{
						if (sfImage_getPixel(MainMenu.saveMask, vMousePosToFloat.x, vMousePosToFloat.y).r == 255 && sfImage_getPixel(MainMenu.saveMask, vMousePosToFloat.x, vMousePosToFloat.y).g == 0
							&& sfImage_getPixel(MainMenu.saveMask, vMousePosToFloat.x, vMousePosToFloat.y).b == 0 && sfImage_getPixel(MainMenu.saveMask, vMousePosToFloat.x, vMousePosToFloat.y).a == 255)
						{
							sfSprite_setColor(MainMenu.saveSlot1.sprite, sfRed);
							if (sfMouse_isButtonPressed(sfMouseLeft) && !isMousePressed)
							{
								isMousePressed = sfTrue;
								testincreaseX = 1;
								testincreaseY = 1;
								mainMenuState = ON_START_TRANSITION;
								unlockedLevels = unLockedLevelsSolt1;
								sfSprite_setColor(MainMenu.saveSlot1.sprite, sfWhite);
							}
						}
						else
						{
							sfSprite_setColor(MainMenu.saveSlot1.sprite, sfWhite);
						}
					}
					else
					{
						sfSprite_setColor(MainMenu.saveSlot1.sprite, sfWhite);
					}

					/*Slot2*/
					if (sfFloatRect_contains(&MainMenu.saveSlot2.boundingBox, vMousePos.x, vMousePos.y))
					{
						if (sfImage_getPixel(MainMenu.saveMask, vMousePosToFloat.x, vMousePosToFloat.y).r == 255 && sfImage_getPixel(MainMenu.saveMask, vMousePosToFloat.x, vMousePosToFloat.y).g == 0
							&& sfImage_getPixel(MainMenu.saveMask, vMousePosToFloat.x, vMousePosToFloat.y).b == 0 && sfImage_getPixel(MainMenu.saveMask, vMousePosToFloat.x, vMousePosToFloat.y).a == 255)
						{
							sfSprite_setColor(MainMenu.saveSlot2.sprite, sfRed);
							if (sfMouse_isButtonPressed(sfMouseLeft) && !isMousePressed)
							{
								//isMousePressed = sfTrue;
								//mainMenuState = ON_START;
								testincreaseX = 1;
								testincreaseY = 1;
								mainMenuState = ON_START_TRANSITION;
								unlockedLevels = unLockedLevelsSolt2;
								sfSprite_setColor(MainMenu.saveSlot2.sprite, sfWhite);
							}
						}
						else
						{
							sfSprite_setColor(MainMenu.saveSlot2.sprite, sfWhite);
						}
					}
					else
					{
						sfSprite_setColor(MainMenu.saveSlot2.sprite, sfWhite);
					}

					/*Slot3*/
					if (sfFloatRect_contains(&MainMenu.saveSlot3.boundingBox, vMousePos.x, vMousePos.y))
					{
						if (sfImage_getPixel(MainMenu.saveMask, vMousePosToFloat.x, vMousePosToFloat.y).r == 255 && sfImage_getPixel(MainMenu.saveMask, vMousePosToFloat.x, vMousePosToFloat.y).g == 0
							&& sfImage_getPixel(MainMenu.saveMask, vMousePosToFloat.x, vMousePosToFloat.y).b == 0 && sfImage_getPixel(MainMenu.saveMask, vMousePosToFloat.x, vMousePosToFloat.y).a == 255)
						{
							sfSprite_setColor(MainMenu.saveSlot3.sprite, sfRed);
							if (sfMouse_isButtonPressed(sfMouseLeft) && !isMousePressed)
							{
								//isMousePressed = sfTrue;
								//mainMenuState = ON_START;
								testincreaseX = 1;
								testincreaseY = 1;
								mainMenuState = ON_START_TRANSITION;
								unlockedLevels = unLockedLevelsSolt3;
								sfSprite_setColor(MainMenu.saveSlot3.sprite, sfWhite);
							}
						}
						else
						{
							sfSprite_setColor(MainMenu.saveSlot3.sprite, sfWhite);
						}
					}
					else
					{
						sfSprite_setColor(MainMenu.saveSlot3.sprite, sfWhite);
					}
				}


				sfRenderWindow_drawSprite(window, MainMenu.exitSheet.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.exitLabel.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.creditsSheet.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.creditsLabel.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.startSheetLS.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.startSheet.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.miniMapSlot1.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.miniMapSlot2.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.miniMapSlot3.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.startLabel.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.saveSlot1.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.saveSlot2.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.saveSlot3.sprite, NULL);
				break;

#pragma endregion ON_START

#pragma region ON_START_TRANSITION
			case ON_START_TRANSITION:
				//printf_s("START TRANSITION !!!!!\n");
				
				if (MainMenu.startSheet.vPos.y < 1840)
				{
					
					MainMenu.startSheet.vPos.x += 2 * testincreaseX;
					MainMenu.startSheet.vPos.y += 6 * testincreaseY;
					MainMenu.saveSlot1.vPos.x += 2 * testincreaseX;
					MainMenu.saveSlot2.vPos.x += 2 * testincreaseX;
					MainMenu.saveSlot3.vPos.x += 2 * testincreaseX;
					MainMenu.saveSlot1.vPos.y += 6 * testincreaseY;
					MainMenu.saveSlot2.vPos.y += 6 * testincreaseY;
					MainMenu.saveSlot3.vPos.y += 6 * testincreaseY;
					MainMenu.miniMapSlot1.vPos.x += 2 * testincreaseX;
					MainMenu.miniMapSlot1.vPos.y += 6 * testincreaseY;
					MainMenu.miniMapSlot2.vPos.x += 2 * testincreaseX;
					MainMenu.miniMapSlot2.vPos.y += 6 * testincreaseY;
					MainMenu.miniMapSlot3.vPos.x += 2 * testincreaseX;
					MainMenu.miniMapSlot3.vPos.y += 6 * testincreaseY;
					testincreaseX += 0.05;
					testincreaseY += 00.1;
					sfSprite_setPosition(MainMenu.miniMapSlot1.sprite, MainMenu.miniMapSlot1.vPos);
					sfSprite_setPosition(MainMenu.miniMapSlot2.sprite, MainMenu.miniMapSlot2.vPos);
					sfSprite_setPosition(MainMenu.miniMapSlot3.sprite, MainMenu.miniMapSlot3.vPos);
					sfSprite_setPosition(MainMenu.startSheet.sprite, MainMenu.startSheet.vPos);
					sfSprite_setPosition(MainMenu.saveSlot1.sprite, MainMenu.saveSlot1.vPos);
					sfSprite_setPosition(MainMenu.saveSlot2.sprite, MainMenu.saveSlot2.vPos);
					sfSprite_setPosition(MainMenu.saveSlot3.sprite, MainMenu.saveSlot3.vPos);
				}
				else
				{
					testincreaseX = 1;
					testincreaseY = 1;
					mainMenuState = ON_START_LEVEL_SELECTOR;
				}

				sfRenderWindow_drawSprite(window, MainMenu.exitSheet.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.exitLabel.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.creditsSheet.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.creditsLabel.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.startSheetLS.sprite, NULL);
				if (unlockedLevels >= 0)
				{
					sfRenderWindow_drawSprite(window, MainMenu.level1Icon.sprite, NULL);
				}
				if (unlockedLevels >= 2)
				{
					sfRenderWindow_drawSprite(window, MainMenu.level2Icon.sprite, NULL);
				}
				sfRenderWindow_drawSprite(window, MainMenu.startSheet.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.miniMapSlot1.sprite,NULL);
				sfRenderWindow_drawSprite(window, MainMenu.miniMapSlot2.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.miniMapSlot3.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.startLabel.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.saveSlot1.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.saveSlot2.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.saveSlot3.sprite, NULL);


				break;

#pragma endregion ON_START_TRANSITION

#pragma region ON_START_LEVEL_SELECTOR
			case ON_START_LEVEL_SELECTOR:
				printf_s("Unlocked levels :%d\n", unlockedLevels);
				if (vMousePos.x >= 0 && vMousePos.x <= LABEL_MASK_WIDTH && vMousePos.y >= 0 && vMousePos.y <= LABEL_MASK_HEIGHT)
				{

					/*Credits*/
					if (sfFloatRect_contains(&MainMenu.creditsLabel.boundingBox, vMousePos.x, vMousePos.y))
					{
						if (sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).r == 255 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).g == 0
							&& sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).b == 0 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).a == 255)
						{
							sfSprite_setColor(MainMenu.creditsLabel.sprite, sfRed);
							if (sfMouse_isButtonPressed(sfMouseLeft && !isMousePressed))
							{
								isMousePressed = sfTrue;
								mainMenuState = ON_CREDITS;
								sfSprite_setColor(MainMenu.creditsLabel.sprite, sfWhite);
							}
						}
						else
						{
							sfSprite_setColor(MainMenu.creditsLabel.sprite, sfWhite);
						}
					}
					else
					{
						sfSprite_setColor(MainMenu.creditsLabel.sprite, sfWhite);
					}
					/*Quitter*/
					if (sfFloatRect_contains(&MainMenu.exitLabel.boundingBox, vMousePos.x, vMousePos.y))
					{
						if (sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).r == 255 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).g == 0
							&& sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).b == 0 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).a == 255)
						{
							sfSprite_setColor(MainMenu.exitLabel.sprite, sfRed);
							if (sfMouse_isButtonPressed(sfMouseLeft && !isMousePressed))
							{
								isMousePressed = sfTrue;
								mainMenuState = ON_EXIT;
								sfSprite_setColor(MainMenu.exitLabel.sprite, sfWhite);
							}
						}
						else
						{
							sfSprite_setColor(MainMenu.exitLabel.sprite, sfWhite);
						}
					}
					else
					{
						sfSprite_setColor(MainMenu.exitLabel.sprite, sfWhite);
					}
				}
				sfRenderWindow_drawSprite(window, MainMenu.exitSheet.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.exitLabel.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.creditsSheet.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.creditsLabel.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.startSheetLS.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.startLabel.sprite, NULL);


				/*level 1*/
				if (sfFloatRect_contains(&MainMenu.level1Icon.boundingBox, vMousePos.x, vMousePos.y) && unlockedLevels >= 0)
				{
					if (sfImage_getPixel(MainMenu.levelMask, vMousePosToFloat.x, vMousePosToFloat.y).r == 255 && sfImage_getPixel(MainMenu.levelMask, vMousePosToFloat.x, vMousePosToFloat.y).g == 0
						&& sfImage_getPixel(MainMenu.levelMask, vMousePosToFloat.x, vMousePosToFloat.y).b == 0 && sfImage_getPixel(MainMenu.levelMask, vMousePosToFloat.x, vMousePosToFloat.y).a == 255)
					{
						sfSprite_setColor(MainMenu.level1Icon.sprite, sfRed);
						if (sfMouse_isButtonPressed(sfMouseLeft) && !isMousePressed)
						{
							isMousePressed = sfTrue;
							iCurrentLevel = ESTOMAC;
							loadGameFromLevelNumber(iCurrentLevel, &CurrentLevelAssets, ListEnnemy, ListTowerBullet, ListEnnemyBullet, ListTower, ListTowerSlot, ListWhiteCell);
							/*chargement du chemin des ennemis (la map estomac en possède 2*/
							/*loadEnnemyPathPoint(ListEnnemyPathPoint1, iCurrentLevel, 1);
							loadEnnemyPathPoint(ListEnnemyPathPoint2, iCurrentLevel, 2);*/

							///*chargement de la vague*/
							//loadEnnemyWave(ListEnnemyWave, iCurrentLevel);

							/*chargement des emplacements des socles*/
							loadTowerSlots(ListTowerSlot, iCurrentLevel);
							
							iGoalHp = 100;
							GameState = GAME;
							sfSprite_setColor(MainMenu.level1Icon.sprite, sfWhite);
						}

					}
					else
					{
						sfSprite_setColor(MainMenu.level1Icon.sprite, sfWhite);
					}
				}
				else
				{
					sfSprite_setColor(MainMenu.level1Icon.sprite, sfWhite);
				}

				/*level 2*/
				if (sfFloatRect_contains(&MainMenu.level2Icon.boundingBox, vMousePos.x, vMousePos.y) && unlockedLevels >= 2)
				{
					if (sfImage_getPixel(MainMenu.levelMask, vMousePosToFloat.x, vMousePosToFloat.y).r == 255 && sfImage_getPixel(MainMenu.levelMask, vMousePosToFloat.x, vMousePosToFloat.y).g == 0
						&& sfImage_getPixel(MainMenu.levelMask, vMousePosToFloat.x, vMousePosToFloat.y).b == 0 && sfImage_getPixel(MainMenu.levelMask, vMousePosToFloat.x, vMousePosToFloat.y).a == 255)
					{
						sfSprite_setColor(MainMenu.level2Icon.sprite, sfRed);
						if (sfMouse_isButtonPressed(sfMouseLeft) && !isMousePressed)
						{
							isMousePressed = sfTrue;
							iCurrentLevel = COEUR;
							loadGameFromLevelNumber(iCurrentLevel, &CurrentLevelAssets, ListEnnemy, ListTowerBullet, ListEnnemyBullet, ListTower, ListTowerSlot, ListWhiteCell);
							
							iGoalHp = 100;
							GameState = GAME;
							sfSprite_setColor(MainMenu.level2Icon.sprite, sfWhite);
						}
					}
					else
					{
						sfSprite_setColor(MainMenu.level2Icon.sprite, sfWhite);
					}
				}
				else
				{
					sfSprite_setColor(MainMenu.level2Icon.sprite, sfWhite);
				}

				if (unlockedLevels >= 0)
				{
					sfRenderWindow_drawSprite(window, MainMenu.level1Icon.sprite, NULL);
				}
				if (unlockedLevels >= 2)
				{
					sfRenderWindow_drawSprite(window, MainMenu.level2Icon.sprite, NULL);
				}

				break;

#pragma endregion ON_START_LEVEL_SELECTOR

#pragma region ON_CREDITS
			case ON_CREDITS:

				if (vMousePos.x >= 0 && vMousePos.x <= LABEL_MASK_WIDTH && vMousePos.y >= 0 && vMousePos.y <= LABEL_MASK_HEIGHT)
				{
					/*Commencer*/
					if (sfFloatRect_contains(&MainMenu.startLabel.boundingBox, vMousePos.x, vMousePos.y))
					{
						if (sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).r == 255 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).g == 0
							&& sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).b == 0 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).a == 255)
						{
							sfSprite_setColor(MainMenu.startLabel.sprite, sfRed);
							if (sfMouse_isButtonPressed(sfMouseLeft && !isMousePressed))
							{
								isMousePressed = sfTrue;
								mainMenuState = ON_START;
								MainMenu.startSheet.vPos.x = 1127.5;
								MainMenu.startSheet.vPos.y = 567;
								MainMenu.saveSlot1.vPos.x = 1022;
								MainMenu.saveSlot1.vPos.y = 307.5;
								MainMenu.saveSlot2.vPos.x = 1024;
								MainMenu.saveSlot2.vPos.y = 570.5;
								MainMenu.saveSlot3.vPos.x = 1012;
								MainMenu.saveSlot3.vPos.y = 834.5;
								MainMenu.miniMapSlot1.vPos.x = 1668;
								MainMenu.miniMapSlot1.vPos.y = 317.5;
								MainMenu.miniMapSlot2.vPos.x = 1661;
								MainMenu.miniMapSlot2.vPos.y = 576.5;
								MainMenu.miniMapSlot3.vPos.x = 1658;
								MainMenu.miniMapSlot3.vPos.y = 850;
								sfSprite_setPosition(MainMenu.miniMapSlot1.sprite, MainMenu.miniMapSlot1.vPos);
								sfSprite_setPosition(MainMenu.miniMapSlot2.sprite, MainMenu.miniMapSlot2.vPos);
								sfSprite_setPosition(MainMenu.miniMapSlot3.sprite, MainMenu.miniMapSlot3.vPos);
								sfSprite_setPosition(MainMenu.startSheet.sprite, MainMenu.startSheet.vPos);
								sfSprite_setPosition(MainMenu.saveSlot1.sprite, MainMenu.saveSlot1.vPos);
								sfSprite_setPosition(MainMenu.saveSlot2.sprite, MainMenu.saveSlot2.vPos);
								sfSprite_setPosition(MainMenu.saveSlot3.sprite, MainMenu.saveSlot3.vPos);
								sfSprite_setColor(MainMenu.startLabel.sprite, sfWhite);
							}
						}
						else
						{
							sfSprite_setColor(MainMenu.startLabel.sprite, sfWhite);
						}
					}
					else
					{
						sfSprite_setColor(MainMenu.startLabel.sprite, sfWhite);
					}
					/*Quitter*/
					if (sfFloatRect_contains(&MainMenu.exitLabel.boundingBox, vMousePos.x, vMousePos.y))
					{
						if (sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).r == 255 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).g == 0
							&& sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).b == 0 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).a == 255)
						{
							sfSprite_setColor(MainMenu.exitLabel.sprite, sfRed);
							if (sfMouse_isButtonPressed(sfMouseLeft && !isMousePressed))
							{
								isMousePressed = sfTrue;
								mainMenuState = ON_EXIT;
								sfSprite_setColor(MainMenu.exitLabel.sprite, sfWhite);
							}
						}
						else
						{
							sfSprite_setColor(MainMenu.exitLabel.sprite, sfWhite);
						}
					}
					else
					{
						sfSprite_setColor(MainMenu.exitLabel.sprite, sfWhite);
					}
				}

				sfRenderWindow_drawSprite(window, MainMenu.startSheetLS.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.startSheet.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.startLabel.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.exitSheet.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.exitLabel.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.creditsSheet.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.creditsLabel.sprite, NULL);
				break;

#pragma endregion ON_CREDITS

#pragma region ON_EXIT
			case ON_EXIT:

				if (vMousePos.x >= 0 && vMousePos.x <= LABEL_MASK_WIDTH && vMousePos.y >= 0 && vMousePos.y <= LABEL_MASK_HEIGHT)
				{
					/*Commencer*/
					if (sfFloatRect_contains(&MainMenu.startLabel.boundingBox, vMousePos.x, vMousePos.y))
					{
						if (sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).r == 255 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).g == 0
							&& sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).b == 0 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).a == 255)
						{
							sfSprite_setColor(MainMenu.startLabel.sprite, sfRed);
							if (sfMouse_isButtonPressed(sfMouseLeft && !isMousePressed))
							{
								isMousePressed = sfTrue;
								mainMenuState = ON_START;
								MainMenu.startSheet.vPos.x = 1127.5;
								MainMenu.startSheet.vPos.y = 567;
								MainMenu.saveSlot1.vPos.x = 1022;
								MainMenu.saveSlot1.vPos.y = 307.5;
								MainMenu.saveSlot2.vPos.x = 1024;
								MainMenu.saveSlot2.vPos.y = 570.5;
								MainMenu.saveSlot3.vPos.x = 1012;
								MainMenu.saveSlot3.vPos.y = 834.5;
								MainMenu.miniMapSlot1.vPos.x = 1668;
								MainMenu.miniMapSlot1.vPos.y = 317.5;
								MainMenu.miniMapSlot2.vPos.x = 1661;
								MainMenu.miniMapSlot2.vPos.y = 576.5;
								MainMenu.miniMapSlot3.vPos.x = 1658;
								MainMenu.miniMapSlot3.vPos.y = 850;
								sfSprite_setPosition(MainMenu.miniMapSlot1.sprite, MainMenu.miniMapSlot1.vPos);
								sfSprite_setPosition(MainMenu.miniMapSlot2.sprite, MainMenu.miniMapSlot2.vPos);
								sfSprite_setPosition(MainMenu.miniMapSlot3.sprite, MainMenu.miniMapSlot3.vPos);
								sfSprite_setPosition(MainMenu.startSheet.sprite, MainMenu.startSheet.vPos);
								sfSprite_setPosition(MainMenu.saveSlot1.sprite, MainMenu.saveSlot1.vPos);
								sfSprite_setPosition(MainMenu.saveSlot2.sprite, MainMenu.saveSlot2.vPos);
								sfSprite_setPosition(MainMenu.saveSlot3.sprite, MainMenu.saveSlot3.vPos);
								sfSprite_setColor(MainMenu.startLabel.sprite, sfWhite);
							}
						}
						else
						{
							sfSprite_setColor(MainMenu.startLabel.sprite, sfWhite);
						}
					}
					else
					{
						sfSprite_setColor(MainMenu.startLabel.sprite, sfWhite);
					}

					/*Credits*/
					if (sfFloatRect_contains(&MainMenu.creditsLabel.boundingBox, vMousePos.x, vMousePos.y))
					{
						if (sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).r == 255 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).g == 0
							&& sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).b == 0 && sfImage_getPixel(MainMenu.labelMask, vMousePosToFloat.x, vMousePosToFloat.y).a == 255)
						{
							sfSprite_setColor(MainMenu.creditsLabel.sprite, sfRed);
							if (sfMouse_isButtonPressed(sfMouseLeft && !isMousePressed))
							{
								isMousePressed = sfTrue;
								mainMenuState = ON_CREDITS;
								sfSprite_setColor(MainMenu.creditsLabel.sprite, sfWhite);
							}
						}
						else
						{
							sfSprite_setColor(MainMenu.creditsLabel.sprite, sfWhite);
						}
					}
					else
					{
						sfSprite_setColor(MainMenu.creditsLabel.sprite, sfWhite);
					}
				}
				if (vMousePos.x >= 0 && vMousePos.x <= 1920 && vMousePos.y >= 0 && vMousePos.y <= 1080)
				{
					/*quitter oui*/
					if (sfFloatRect_contains(&MainMenu.exitYes.boundingBox, vMousePos.x, vMousePos.y))
					{
						if (sfImage_getPixel(MainMenu.exitMask, vMousePosToFloat.x, vMousePosToFloat.y).r == 255 && sfImage_getPixel(MainMenu.exitMask, vMousePosToFloat.x, vMousePosToFloat.y).g == 0
							&& sfImage_getPixel(MainMenu.exitMask, vMousePosToFloat.x, vMousePosToFloat.y).b == 0 && sfImage_getPixel(MainMenu.exitMask, vMousePosToFloat.x, vMousePosToFloat.y).a == 255)
						{
							sfSprite_setColor(MainMenu.exitYes.sprite, sfRed);
							if (sfMouse_isButtonPressed(sfMouseLeft && !isMousePressed))
							{
								isMousePressed = sfTrue;
								sfRenderWindow_close(window);
								sfSprite_setColor(MainMenu.exitYes.sprite, sfWhite);
							}
						}
						else
						{
							sfSprite_setColor(MainMenu.exitYes.sprite, sfWhite);
						}
					}
					else
					{
						sfSprite_setColor(MainMenu.exitYes.sprite, sfWhite);
					}

					/*quitter non*/
					if (sfFloatRect_contains(&MainMenu.exitNo.boundingBox, vMousePos.x, vMousePos.y))
					{
						if (sfImage_getPixel(MainMenu.exitMask, vMousePosToFloat.x, vMousePosToFloat.y).r == 255 && sfImage_getPixel(MainMenu.exitMask, vMousePosToFloat.x, vMousePosToFloat.y).g == 0
							&& sfImage_getPixel(MainMenu.exitMask, vMousePosToFloat.x, vMousePosToFloat.y).b == 0 && sfImage_getPixel(MainMenu.exitMask, vMousePosToFloat.x, vMousePosToFloat.y).a == 255)
						{
							sfSprite_setColor(MainMenu.exitNo.sprite, sfRed);
							if (sfMouse_isButtonPressed(sfMouseLeft && !isMousePressed))
							{
								isMousePressed = sfTrue;
								mainMenuState = ON_START;
								MainMenu.startSheet.vPos.x = 1127.5;
								MainMenu.startSheet.vPos.y = 567;
								MainMenu.saveSlot1.vPos.x = 1022;
								MainMenu.saveSlot1.vPos.y = 307.5;
								MainMenu.saveSlot2.vPos.x = 1024;
								MainMenu.saveSlot2.vPos.y = 570.5;
								MainMenu.saveSlot3.vPos.x = 1012;
								MainMenu.saveSlot3.vPos.y = 834.5;
								MainMenu.miniMapSlot1.vPos.x = 1668;
								MainMenu.miniMapSlot1.vPos.y = 317.5;
								MainMenu.miniMapSlot2.vPos.x = 1661;
								MainMenu.miniMapSlot2.vPos.y = 576.5;
								MainMenu.miniMapSlot3.vPos.x = 1658;
								MainMenu.miniMapSlot3.vPos.y = 850;
								sfSprite_setPosition(MainMenu.miniMapSlot1.sprite, MainMenu.miniMapSlot1.vPos);
								sfSprite_setPosition(MainMenu.miniMapSlot2.sprite, MainMenu.miniMapSlot2.vPos);
								sfSprite_setPosition(MainMenu.miniMapSlot3.sprite, MainMenu.miniMapSlot3.vPos);
								sfSprite_setPosition(MainMenu.startSheet.sprite, MainMenu.startSheet.vPos);
								sfSprite_setPosition(MainMenu.saveSlot1.sprite, MainMenu.saveSlot1.vPos);
								sfSprite_setPosition(MainMenu.saveSlot2.sprite, MainMenu.saveSlot2.vPos);
								sfSprite_setPosition(MainMenu.saveSlot3.sprite, MainMenu.saveSlot3.vPos);
								sfSprite_setColor(MainMenu.exitNo.sprite, sfWhite);
							}
						}
						else
						{
							sfSprite_setColor(MainMenu.exitNo.sprite, sfWhite);
						}
					}
					else
					{
						sfSprite_setColor(MainMenu.exitNo.sprite, sfWhite);
					}
				}


				sfRenderWindow_drawSprite(window, MainMenu.startSheetLS.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.startSheet.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.startLabel.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.creditsSheet.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.creditsLabel.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.exitSheet.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.exitLabel.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.exitYes.sprite, NULL);
				sfRenderWindow_drawSprite(window, MainMenu.exitNo.sprite, NULL);

				break;

#pragma endregion ON_EXIT
				default:
					break;
			}
			sfRenderWindow_drawSprite(window, MainMenu.brain.sprite, NULL);
			if (!sfMouse_isButtonPressed(sfMouseLeft))
			{
				isMousePressed = sfFalse;
			}
			break;
#pragma endregion CASE MENU

#pragma region CASE GAME
		case GAME:
				/*Affiche la map*/

	#pragma region AFFICHAGE MAP

				if (sfKeyboard_isKeyPressed(sfKeyNum0))
				{
					iCurrentLevel = TEST;
				}
				if (sfKeyboard_isKeyPressed(sfKeyNum1))
				{
					iCurrentLevel = ESTOMAC;
				}
				if (sfKeyboard_isKeyPressed(sfKeyNum2))
				{
					iCurrentLevel = COEUR;
				}
				sfRenderWindow_drawSprite(window, CurrentLevelAssets.map, NULL);
				//sfRenderWindow_drawSprite(window, Sp_MaskMapTest, NULL);

				//switch (iCurrentLevel)
				//{
				//case TEST:
				//	CurrentLevelAssets.mapMask = Image_MaskMapTest;
				//	sfRenderWindow_drawSprite(window, Sp_MapTest, NULL);
				//	sfRenderWindow_drawSprite(window, Sp_MaskMapTest, NULL);

				//	break;
				//case ESTOMAC:
				//	CurrentLevelAssets.mapMask = Image_MaskMapEstomac;
				//	sfRenderWindow_drawSprite(window, Sp_MapEstomac, NULL);
				//	sfRenderWindow_drawSprite(window, Sp_MaskMapEstomac, NULL);

				//	break;
				//case COEUR: 
				//	//sfRenderWindow_drawSprite(window, Sp_MapCoeur, NULL);
				//	////sfRenderWindow_drawSprite(window, Sp_MaskMapCoeur, NULL);

				//	break;
				//default:

				//	break;
				//}


	#pragma endregion AFFICHAGE MAP

	#pragma region TIME CONTROL
				lastFrameTime = currentTime; // sauvegarde du temps (le temps de la dernière frame)
				currentTime = (float)clock() / CLOCKS_PER_SEC; // temps actuel
				if (iFirstFrameIsPassed == 1)
				{
					timeSinceLastFrame = currentTime - lastFrameTime; // temps depuis la dernière frame
				}
				iFirstFrameIsPassed = 1; // permet de ne pas comptabiliser la première frame pour les timers

	#pragma endregion TIME CONTROL

	#pragma region GESTION VIEW // GUILLAUME

				if (sfKeyboard_isKeyPressed(sfKeyQ) == sfTrue)
				{
					vPosition_View.x -= 50;
				}
				if (sfKeyboard_isKeyPressed(sfKeyD) == sfTrue)
				{
					vPosition_View.x += 50;
				}
				if (sfKeyboard_isKeyPressed(sfKeyZ) == sfTrue)
				{
					vPosition_View.y -= 50;
				}
				if (sfKeyboard_isKeyPressed(sfKeyS) == sfTrue)
				{
					vPosition_View.y += 50;
				}
				sfView_setCenter(View, vPosition_View);
				sfRenderWindow_setView(window, View);

	#pragma endregion GESTION VIEW // GUILLAUME

	#pragma region GESTION DES BOUTONS //GUILLAUME

				/*Bouton espace*/
				if (sfKeyboard_isKeyPressed(sfKeySpace) == sfTrue && SpaceButtonIsButtonPressed == sfFalse)
				{
					SpaceButtonIsButtonPressed = sfTrue;
					iSpaceButtonIsButtonPressedCheck = 0;
				}
				else if (sfKeyboard_isKeyPressed(sfKeySpace) == sfFalse)
				{
					SpaceButtonIsButtonPressed = sfFalse;
				}
				//printf("space button : %d | iSpace : %d\n", SpaceButtonIsButtonPressed,  iSpaceButtonIsButtonPressedCheck);


	#pragma endregion GESTION DES BOUTONS //GUILLAUME

	#pragma region ADD ENNEMY WAVES // GUILLAUME

				if (iWaveIsActive == sfFalse)
				{

					fTimeSinceLastWave += timeSinceLastFrame;
					if (fTimeSinceLastWave > TIME_BETWEEN_WAVE)
					{
						if (sfKeyboard_isKeyPressed(sfKeyG) == sfTrue)
						{
							printf("debug");
						}
						iWaveIsActive = sfTrue;
						fTimeSinceLastWave = 0;
						iCurrentWave++;
						iCurrentNbrCancer = 0;
						iCurrentNbrCholesterol = 0;
						iCurrentNbrCaillot = 0;
						iNbrTotal = 0;
						iWaveEnnemyNbr = 0;
						iWaveEnnemyDead = 0;
						fTimeBetweenEnnemySpawn = TIME_BETWEEN_ENNEMY_SPAWN;
					}
				}

				/*LECTURE DANS LA LISTE DES VAGUES*/
				CurrentEnnemyWave = CurrentLevelAssets.ListEnnemyWave->LastElement;
				while (CurrentEnnemyWave != NULL)
				{
					/*je repère la vague actuelle*/
					if (iCurrentWave == CurrentEnnemyWave->EnnemyWave->iNumWave)
					{
						iNbrCancer = CurrentEnnemyWave->EnnemyWave->iNbrCancer;
						iNbrCholesterol = CurrentEnnemyWave->EnnemyWave->iNbrCholesterol;
						iNbrCaillot = CurrentEnnemyWave->EnnemyWave->iNbrCaillot;
						iNbrTotal = CurrentEnnemyWave->EnnemyWave->iNbrTotal;
						iWaveMax = CurrentEnnemyWave->EnnemyWave->iMaxWave;
					}
					
					CurrentEnnemyWave = CurrentEnnemyWave->PreviousElement;
				}

				
				//printf("CUURENTWAVE : %d\t\n", iCurrentWave);
				if (iWaveIsActive == sfTrue)
				{
					/*condition pour arreter la vague*/
					if (iWaveEnnemyDead >= iNbrTotal)
					{
						/*si le nombre d'ennemis mort attaint le nombre d'ennemis total de la vague alors elle se finit*/
						iWaveIsActive = sfFalse;
						
					}

	#pragma region ADD ENNEMY //GUILLAUME

					fTimeBetweenEnnemySpawn += timeSinceLastFrame;
					if (fTimeBetweenEnnemySpawn >= TIME_BETWEEN_ENNEMY_SPAWN)
					{
						fTimeBetweenEnnemySpawn = 0;
						/*ajout d'ennemi si le nombre d'ennemi de la vague n'est pas encore atteint*/
						if (iWaveEnnemyNbr < iNbrTotal)
						{
							iWaveEnnemyNbr++;

							NewEnnemy = AddElementBeginList(ListEnnemy);
							NewEnnemy->Ennemy = malloc(sizeof(t_Ennemy));

#pragma region SELECTION ENNEMI EN FONCTION DE LA LISTE

							/*aléatoire tant que toutes les catégories n'ont pas atteint leurs nombre max*/
							if (iCurrentNbrCancer < iNbrCancer && iCurrentNbrCholesterol < iNbrCholesterol && iCurrentNbrCaillot < iNbrCaillot)
							{
								NewEnnemy->Ennemy->Type = rand() % CAILLOT + CANCER; // random sur les 3
							}
							/*si tous les cancers ont spawn*/
							else if (iCurrentNbrCancer >= iNbrCancer && iCurrentNbrCholesterol < iNbrCholesterol && iCurrentNbrCaillot < iNbrCaillot)
							{
								NewEnnemy->Ennemy->Type = rand() % CAILLOT + CHOLESTEROL;
							}
							/*si tous les cholesterol ont spawn*/
							else if (iCurrentNbrCancer < iNbrCancer && iCurrentNbrCholesterol >= iNbrCholesterol && iCurrentNbrCaillot < iNbrCaillot)
							{
								NewEnnemy->Ennemy->Type = rand() % 2 + 1;
								if (NewEnnemy->Ennemy->Type == 2)
								{
									NewEnnemy->Ennemy->Type = CANCER;
								}
								if (NewEnnemy->Ennemy->Type == 1)
								{
									NewEnnemy->Ennemy->Type = CAILLOT;
								}
							}
							/*si tous les caillot ont spawn*/
							else if (iCurrentNbrCancer < iNbrCancer && iCurrentNbrCholesterol < iNbrCholesterol && iCurrentNbrCaillot >= iNbrCaillot)
							{
								NewEnnemy->Ennemy->Type = rand() % CHOLESTEROL + CANCER;
							}
							/*si tous les CAILLOT & CHOLESTEROL ont spawn*/
							else if (iCurrentNbrCancer < iNbrCancer && iCurrentNbrCholesterol >= iNbrCholesterol && iCurrentNbrCaillot >= iNbrCaillot)
							{
								NewEnnemy->Ennemy->Type = CANCER;
							}
							/*si tous les CAILLOT & CANCER ont spawn*/
							else if (iCurrentNbrCancer >= iNbrCancer && iCurrentNbrCholesterol < iNbrCholesterol && iCurrentNbrCaillot >= iNbrCaillot)
							{
								NewEnnemy->Ennemy->Type = CHOLESTEROL;
							}
							/*si tous les CANCER & CHOLESTEROL ont spawn*/
							else if (iCurrentNbrCancer >= iNbrCancer && iCurrentNbrCholesterol >= iNbrCholesterol && iCurrentNbrCaillot < iNbrCaillot)
							{
								NewEnnemy->Ennemy->Type = CAILLOT;
							}

#pragma endregion SELECTION ENNEMI EN FONCTION DE LA LISTE
							
							/*GESTION EN FONCTION DU TYPE*/

#pragma region GESTION EN FONCTION DU TYPE //GUILLAUME

							
							printf("%d\n", NewEnnemy->Ennemy->Type);
							if (NewEnnemy->Ennemy->Type == CANCER)
							{
								/*incrémentation du compteur de cancer*/
								iCurrentNbrCancer++;

								NewEnnemy->Ennemy->sp_Ennemy = Sp_Ennemy1;

								NewEnnemy->Ennemy->fControlRadius = CANCER_CONTROL_RADIUS;
								NewEnnemy->Ennemy->fGuardRadius = CANCER_GUARD_RADIUS;

								/*anim*/
								NewEnnemy->Ennemy->animRect.width = CANCER_WIDTH;
								NewEnnemy->Ennemy->animRect.height = CANCER_HEIGHT;
								NewEnnemy->Ennemy->animRect.left = 0;
								NewEnnemy->Ennemy->animRect.top = 0;
								NewEnnemy->Ennemy->iNbrFrameX = CANCER_NBR_FRAME_X;
								NewEnnemy->Ennemy->iNbrFrameY = CANCER_NBR_FRAME_Y;
								NewEnnemy->Ennemy->fTimeBetweenAnimation = CANCER_TIME_BETWEEN_ANIMATION;
								NewEnnemy->Ennemy->fTimeSinceLastAnimation = 0;

								/*stats*/
								NewEnnemy->Ennemy->fSpeedMax = CANCER_SPEED;
								NewEnnemy->Ennemy->Deg = CANCER_DEG;
								NewEnnemy->Ennemy->HpMax = CANCER_HP;
								NewEnnemy->Ennemy->Hp = CANCER_HP;
								NewEnnemy->Ennemy->iMoneyValue = CANCER_MONEY_VALUE;
							}
							else if (NewEnnemy->Ennemy->Type == CHOLESTEROL)
							{
								/*incrémentation du compteur de cholesterol*/
								iCurrentNbrCholesterol++;

								NewEnnemy->Ennemy->sp_Ennemy = Sp_Ennemy2;

								/*gestion de taille*/
								NewEnnemy->Ennemy->iSize = BIG;

								NewEnnemy->Ennemy->fControlRadius = CHOLESTEROL_CONTROL_RADIUS;
								NewEnnemy->Ennemy->fGuardRadius = CHOLESTEROL_GUARD_RADIUS;

								/*anim*/
								NewEnnemy->Ennemy->animRect.width = CHOLESTEROL_WIDTH;
								NewEnnemy->Ennemy->animRect.height = CHOLESTEROL_HEIGHT;
								NewEnnemy->Ennemy->animRect.left = 0;
								NewEnnemy->Ennemy->animRect.top = 0;
								NewEnnemy->Ennemy->iNbrFrameX = CHOLESTEROL_NBR_FRAME_X;
								NewEnnemy->Ennemy->iNbrFrameY = CHOLESTEROL_NBR_FRAME_Y;
								NewEnnemy->Ennemy->fTimeBetweenAnimation = CHOLESTEROL_TIME_BETWEEN_ANIMATION;
								NewEnnemy->Ennemy->fTimeSinceLastAnimation = 0;

								/*stats*/
								NewEnnemy->Ennemy->fSpeedMax = CHOLESTEROL_SPEED;
								NewEnnemy->Ennemy->Deg = CHOLESTEROL_DEG;
								NewEnnemy->Ennemy->HpMax = CHOLESTEROL_HP;
								NewEnnemy->Ennemy->Hp = CHOLESTEROL_HP;
								NewEnnemy->Ennemy->iMoneyValue = CHOLESTEROL_MONEY_VALUE;

								NewEnnemy->Ennemy->iNbrTowerBetweenAttack = CHOLESTEROL_NBR_TOWER_BETWEEN_ATTACK;
								NewEnnemy->Ennemy->fTimeBetweenAttack = CHOLESTEROL_TIME_BETWEEN_ATTACK;
							}
							else if (NewEnnemy->Ennemy->Type == CAILLOT)
							{
								/*incrémentation du compteur de caillot*/
								iCurrentNbrCaillot++;

								NewEnnemy->Ennemy->sp_Ennemy = Sp_Ennemy3;

								NewEnnemy->Ennemy->fControlRadius = CAILLOT_CONTROL_RADIUS;
								NewEnnemy->Ennemy->fGuardRadius = CAILLOT_GUARD_RADIUS;

								/*anim*/
								NewEnnemy->Ennemy->animRect.width = CAILLOT_WIDTH;
								NewEnnemy->Ennemy->animRect.height = CAILLOT_HEIGHT;
								NewEnnemy->Ennemy->animRect.left = 0;
								NewEnnemy->Ennemy->animRect.top = 0;
								NewEnnemy->Ennemy->iNbrFrameX = CAILLOT_NBR_FRAME_X;
								NewEnnemy->Ennemy->iNbrFrameY = CAILLOT_NBR_FRAME_Y;
								NewEnnemy->Ennemy->fTimeBetweenAnimation = CAILLOT_TIME_BETWEEN_ANIMATION;
								NewEnnemy->Ennemy->fTimeSinceLastAnimation = 0;

								/*stats*/
								NewEnnemy->Ennemy->fSpeedMax = CAILLOT_SPEED;
								NewEnnemy->Ennemy->Deg = CAILLOT_DEG;
								NewEnnemy->Ennemy->HpMax = CAILLOT_HP;
								NewEnnemy->Ennemy->Hp = CAILLOT_HP;
								NewEnnemy->Ennemy->iMoneyValue = CAILLOT_MONEY_VALUE;

								NewEnnemy->Ennemy->iNbrTowerBetweenAttack = CAILLOT_NBR_TOWER_BETWEEN_ATTACK;
								NewEnnemy->Ennemy->fTimeBetweenAttack = CAILLOT_TIME_BETWEEN_ATTACK;
							}
							NewEnnemy->Ennemy->iTowerIsChosen = 0;
							NewEnnemy->Ennemy->iTowerToAttackId = -1;
							NewEnnemy->Ennemy->iIsAttack = sfFalse;
							NewEnnemy->Ennemy->fTimeSinceLastAttack = 0;

							/*variables d'animation*/
							NewEnnemy->Ennemy->iAnimationFrameX = 0;
							NewEnnemy->Ennemy->iAnimationFrameY = 0;

							NewEnnemy->Ennemy->vScale.x = 1;
							NewEnnemy->Ennemy->vScale.y = 1;

							NewEnnemy->Ennemy->vOrigin.x = NewEnnemy->Ennemy->animRect.width / 2;
							NewEnnemy->Ennemy->vOrigin.y = NewEnnemy->Ennemy->animRect.height / 2;
							sfSprite_setOrigin(NewEnnemy->Ennemy->sp_Ennemy, NewEnnemy->Ennemy->vOrigin);

							NewEnnemy->Ennemy->fSpeed = 0;
							NewEnnemy->Ennemy->fSpeedFactor = 1;

#pragma endregion GESTION EN FONCTION DU TYPE ENNEMIE //GUILLAUME

							/*GESTION SPAWN*/

#pragma region GESTION SPAWN //GUILLAUME

#pragma region LECTURE DANS LE FICHIER DE SPAWN

							FILE* file = NULL;
							char* filePath = malloc(50);
							int iEnnemySpawnNbr = 0;
							sprintf_s(filePath, 50, "resources/datas/ennemySpawns%d.txt", iCurrentLevel);
							fopen_s(&file, filePath, "r");

							if (file == NULL)
							{
								printf("erreur ouverture de fichier ennemySpawn\n");
								return EXIT_FAILURE;
							}

							fscanf_s(file, "iEnnemySpawnNbr=%d\n", &iEnnemySpawnNbr);
							NewEnnemy->Ennemy->vTargetPostion.x = 0;
							NewEnnemy->Ennemy->vTargetPostion.y = 0;
							fscanf_s(file, "vTarX=%f,vTarY=%f\n", &NewEnnemy->Ennemy->vTargetPostion.x, &NewEnnemy->Ennemy->vTargetPostion.y);
							//printf("ENNEMYSPAWN : %d | TAR X=%.2f | TAR Y=%.2f\n", iEnnemySpawnNbr, NewEnnemy->Ennemy->vTargetPostion.x, NewEnnemy->Ennemy->vTargetPostion.y);
							NewEnnemy->Ennemy->iStartPos = 0;
							NewEnnemy->Ennemy->iStartPos = rand() % iEnnemySpawnNbr + 1; // choix de la ligne a lire
							for (int i = 0; i < NewEnnemy->Ennemy->iStartPos; i++)
							{
								NewEnnemy->Ennemy->vSpawnPosition.x = 0;
								NewEnnemy->Ennemy->vSpawnPosition.y = 0;
								NewEnnemy->Ennemy->dirState = 0;
								fscanf_s(file, "vPosX=%f,vPosY=%f,iDir=%d\n", &NewEnnemy->Ennemy->vSpawnPosition.x, &NewEnnemy->Ennemy->vSpawnPosition.y, &NewEnnemy->Ennemy->dirState);
								//printf("X : %.2f |Y : %.2f | Dir : %d\n", NewEnnemy->Ennemy->vSpawnPosition.x, NewEnnemy->Ennemy->vSpawnPosition.y, NewEnnemy->Ennemy->iDirection);
							}

							NewEnnemy->Ennemy->iRandSpawnValueVariation = rand() % ENNEMY_VARIANT_SPAWN + 0;

							/*gestion x*/
							NewEnnemy->Ennemy->iRandSpawnDirectionVariation = rand() % 2 + 1;
							if (NewEnnemy->Ennemy->iRandSpawnDirectionVariation == 1)
							{
								NewEnnemy->Ennemy->vSpawnPosition.x += ENNEMY_VARIANT_SPAWN;
							}
							else if (NewEnnemy->Ennemy->iRandSpawnDirectionVariation == 2)
							{
								NewEnnemy->Ennemy->vSpawnPosition.x -= ENNEMY_VARIANT_SPAWN;
							}
							/*gestion y*/
							NewEnnemy->Ennemy->iRandSpawnDirectionVariation = rand() % 2 + 1;
							if (NewEnnemy->Ennemy->iRandSpawnDirectionVariation == 1)
							{
								NewEnnemy->Ennemy->vSpawnPosition.y += ENNEMY_VARIANT_SPAWN;
							}
							else if (NewEnnemy->Ennemy->iRandSpawnDirectionVariation == 2)
							{
								NewEnnemy->Ennemy->vSpawnPosition.y -= ENNEMY_VARIANT_SPAWN;
							}
							fclose(file);

#pragma endregion LECTURE DANS LE FICHIER DE SPAWN

							NewEnnemy->Ennemy->vCurrentPosition = NewEnnemy->Ennemy->vSpawnPosition;
							sfSprite_setPosition(NewEnnemy->Ennemy->sp_Ennemy, NewEnnemy->Ennemy->vCurrentPosition);


#pragma endregion GESTION SPAWN //GUILLAUME

							/*INITIALISATION PARAMETRES ENNEMIS*/

#pragma region INITIALISATION PARAMETRES ENNEMIS

							NewEnnemy->Ennemy->iPosPathToTarget = 1;
							NewEnnemy->Ennemy->vPosPathToTarget.x = 0;
							NewEnnemy->Ennemy->vPosPathToTarget.y = 0;

							/*QUAND J'AJOUTE L'ENNEMI IL EST ORIENTE VERS L'OBJECTIF*/
							NewEnnemy->Ennemy->fCurrentAngleDirection = 0;
							NewEnnemy->Ennemy->fCollideIncrementation = 1;

							NewEnnemy->Ennemy->fAngleSprite = 0;

							NewEnnemy->Ennemy->iRandDirection = 0;
							NewEnnemy->Ennemy->iRandDirectionIsChosen = 0;

							/*varaibles de variation de direction*/
							NewEnnemy->Ennemy->fTimeSinceLastVariation = 0;
							NewEnnemy->Ennemy->fWanderAngle = 0;
							NewEnnemy->Ennemy->vWanderCenter.x = 0;
							NewEnnemy->Ennemy->vWanderCenter.y = 0;
							NewEnnemy->Ennemy->vWanderDirection.x = 0;
							NewEnnemy->Ennemy->vWanderDirection.y = 0;

							/*despawn*/
							NewEnnemy->Ennemy->iDespawn = 0;
							NewEnnemy->Ennemy->fTimeSinceStartDespawn = 0;

							/*ATTAQUE*/
							NewEnnemy->Ennemy->vDistToTowerDetectionPos.x = 0;
							NewEnnemy->Ennemy->vDistToTowerDetectionPos.y = 0;
							NewEnnemy->Ennemy->EnnemyIsInTheDetectionZone = sfFalse;
							NewEnnemy->Ennemy->iNbrTowerSinceLastAttack = 0;
							NewEnnemy->Ennemy->fTimeSinceLastAttack = 0;
							NewEnnemy->Ennemy->iCurrentTowerDetectionZoneId = -1;

							/*random du chemin asuivre sur le nombre de chemins présennt dans le niveau*/
							NewEnnemy->Ennemy->PathToFollow = rand() % CurrentLevelAssets.iNbrEnnemyPath;
							
							NewEnnemy->Ennemy->isHit = sfFalse;
							NewEnnemy->Ennemy->tCurrentLifeBarDisplay = 0;
							NewEnnemy->Ennemy->tStartLifeBarDisplay = 0;
							NewEnnemy->Ennemy->tSinceLifeBarDisplay = 0;


#pragma endregion INITIALISATION PARAMETRES ENNEMIS
							
							/*BARRE DE VIE*/

#pragma region BARRE DE VIE //SEB

							/*rectangle de fond noir*/
							NewEnnemy->Ennemy->RectangleShapeBack = sfRectangleShape_create();
							NewEnnemy->Ennemy->vSizeRectangleShapeBack.x = LIFEBAR_MAX_SIZE_X;
							NewEnnemy->Ennemy->vSizeRectangleShapeBack.y = LIFEBAR_SIZE_Y;
							sfRectangleShape_setSize(NewEnnemy->Ennemy->RectangleShapeBack, NewEnnemy->Ennemy->vSizeRectangleShapeBack);
							NewEnnemy->Ennemy->vOriginRectangleShapeBack.x = NewEnnemy->Ennemy->vSizeRectangleShapeBack.x / 2;
							NewEnnemy->Ennemy->vOriginRectangleShapeBack.y = NewEnnemy->Ennemy->vSizeRectangleShapeBack.y / 2;
							sfRectangleShape_setOrigin(NewEnnemy->Ennemy->RectangleShapeBack, NewEnnemy->Ennemy->vOriginRectangleShapeBack);
							sfRectangleShape_setFillColor(NewEnnemy->Ennemy->RectangleShapeBack, Color_Black_transp);
							sfRectangleShape_setOutlineThickness(NewEnnemy->Ennemy->RectangleShapeBack, 2);
							sfRectangleShape_setOutlineColor(NewEnnemy->Ennemy->RectangleShapeBack, sfBlack);
							//NewEnnemy->Ennemy->vOriginRectangleShapeBack.x = sfRectangleShape_getGlobalBounds(NewEnnemy->Ennemy->RectangleShapeBack).width / 2;
							//NewEnnemy->Ennemy->vOriginRectangleShapeBack.y = sfRectangleShape_getGlobalBounds(NewEnnemy->Ennemy->RectangleShapeBack).height / 2;
							//sfRectangleShape_setOrigin(NewEnnemy->Ennemy->RectangleShapeBack, NewEnnemy->Ennemy->vOriginRectangleShapeBack);

							/*rectangle de vie*/
							NewEnnemy->Ennemy->RectangleShape = sfRectangleShape_create();
							NewEnnemy->Ennemy->vSizeRectangleShape.x = LIFEBAR_MAX_SIZE_X;
							NewEnnemy->Ennemy->vSizeRectangleShape.y = LIFEBAR_SIZE_Y;
							sfRectangleShape_setSize(NewEnnemy->Ennemy->RectangleShape, NewEnnemy->Ennemy->vSizeRectangleShape);
							sfRectangleShape_setFillColor(NewEnnemy->Ennemy->RectangleShape, sfRed);
							//NewEnnemy->Ennemy->vOriginRectangleShape.x = sfRectangleShape_getGlobalBounds(NewEnnemy->Ennemy->RectangleShape).width / 2;
							//NewEnnemy->Ennemy->vOriginRectangleShape.y = sfRectangleShape_getGlobalBounds(NewEnnemy->Ennemy->RectangleShape).height / 2;
							//sfRectangleShape_setOrigin(NewEnnemy->Ennemy->RectangleShape, NewEnnemy->Ennemy->vOriginRectangleShapeBack);
							iSpaceButtonIsButtonPressedCheck = 1;

#pragma endregion BARRE DE VIE //SEB

#pragma region TIMER DOMMAGES TOUR 2 //SEB

							NewEnnemy->Ennemy->tStartDOT = (float)clock() / CLOCKS_PER_SEC;
							NewEnnemy->Ennemy->tCurrentDOT = 0;
							NewEnnemy->Ennemy->tSinceDOT = 0;

#pragma endregion TIMER DOMMAGES TOUR 2 //SEB

						}
						
					}
				}


	#pragma endregion ADD ENNEMY //GUILLAUME

	#pragma endregion ADD ENNEMY WAVES

	#pragma region READ LIST ENNEMY CALCUL //GUILLAUME
				if (sfKeyboard_isKeyPressed(sfKeyD) == sfTrue)
				{
					printf("debug");
				}
				CurrentEnnemy = ListEnnemy->FirstElement;
				while (CurrentEnnemy != NULL)
				{
					/*GESTION DE DIRECTION*/

					

	#pragma region GESTION DEPLACEMENTS  //GUILLAUME

						/*J'OBTIENS LA COULEUR SITUE SOUS L'ENNEMI*/
						if (CurrentEnnemy->Ennemy->vCurrentPosition.x > 0 && CurrentEnnemy->Ennemy->vCurrentPosition.x < WINDOW_WIDTH
							&& CurrentEnnemy->Ennemy->vCurrentPosition.y > 0 && CurrentEnnemy->Ennemy->vCurrentPosition.y < WINDOW_HEIGHT)
						{
							CurrentEnnemy->Ennemy->Color_ToCheck = sfImage_getPixel(CurrentLevelAssets.mapMask, CurrentEnnemy->Ennemy->vCurrentPosition.x, CurrentEnnemy->Ennemy->vCurrentPosition.y);
						}

						if (manageEnnemi(CurrentEnnemy, CurrentLevelAssets.mapMask, timeSinceLastFrame) == sfFalse)
						{

		#pragma region DIRECTION SPRITE EN FONCTION DE LA COULEUR //GUILLAUME

							/*COULEUR BLEU (HAUT-DROITE)*/
							if (CurrentEnnemy->Ennemy->Color_ToCheck.b == 255)
							{
								CurrentEnnemy->Ennemy->dirState = UP_RIGHT;
							}
							/*COULEUR VERTE (HAUT-GAUCHE)*/
							if (CurrentEnnemy->Ennemy->Color_ToCheck.g == 255)
							{
								CurrentEnnemy->Ennemy->dirState = UP_LEFT;
							}
							/*COULEUR JAUNE (BAS_DROITE)*/
							if (CurrentEnnemy->Ennemy->Color_ToCheck.r == 150 && CurrentEnnemy->Ennemy->Color_ToCheck.g == 150)
							{
								CurrentEnnemy->Ennemy->dirState = DOWN_LEFT;
							}
							/*COULEUR BLEU CLAIR (BAS_GAUCHE)*/
							if (CurrentEnnemy->Ennemy->Color_ToCheck.g == 150 && CurrentEnnemy->Ennemy->Color_ToCheck.b == 150)
							{
								CurrentEnnemy->Ennemy->dirState = DOWN_RIGHT;
							}

		#pragma endregion DIRECTION SPRITE EN FONCTION DE LA COULEUR //GUILLAUME

		#pragma region DIRECTION SPRITE EN FONCTION DE LA DIRECTION //GUILLAUME

							CurrentEnnemy->Ennemy->fCurrentAngleDirection = GetAngleDegreeFromVector(CurrentEnnemy->Ennemy->vCurrentDirection);
							//if (CurrentEnnemy->Ennemy->fCurrentAngleDirection >= 0 && CurrentEnnemy->Ennemy->fCurrentAngleDirection <= 360)
							//{
							//	/*HAUT-DROITE*/
							//	if (CurrentEnnemy->Ennemy->fCurrentAngleDirection <= 360 && CurrentEnnemy->Ennemy->fCurrentAngleDirection >= 270)
							//	{
							//		CurrentEnnemy->Ennemy->iDirection = UP_RIGHT;
							//	}
							//	/*HAUT-GAUCHE*/
							//	if (CurrentEnnemy->Ennemy->fCurrentAngleDirection <= 270 && CurrentEnnemy->Ennemy->fCurrentAngleDirection >= 180)
							//	{
							//		CurrentEnnemy->Ennemy->iDirection = UP_LEFT;
							//	}
							//	/*BAS_DROITE*/
							//	if (CurrentEnnemy->Ennemy->fCurrentAngleDirection <= 90 && CurrentEnnemy->Ennemy->fCurrentAngleDirection >= 0)
							//	{
							//		CurrentEnnemy->Ennemy->iDirection = DOWN_RIGHT;
							//	}
							//	/*BAS_GAUCHE*/
							//	if (CurrentEnnemy->Ennemy->fCurrentAngleDirection <= 180 && CurrentEnnemy->Ennemy->fCurrentAngleDirection >= 90)
							//	{
							//		CurrentEnnemy->Ennemy->iDirection = DOWN_LEFT;
							//	}
							//}
							//else
							//{
							//	//printf("ENEMY %dIS NOT IN THE ANGLE SETTINGS\t\n", CurrentEnnemy->Id);
							//}

							///*HAUT-DROITE*/
							//if (CurrentEnnemy->Ennemy->vNormalizeDirection.x > 0 && CurrentEnnemy->Ennemy->vNormalizeDirection.y > 0)
							//{
							//	CurrentEnnemy->Ennemy->dirState = DOWN_RIGHT;
							//}
							///*HAUT-GAUCHE*/
							//if (CurrentEnnemy->Ennemy->vNormalizeDirection.x > 0 && CurrentEnnemy->Ennemy->vNormalizeDirection.y < 0)
							//{
							//	CurrentEnnemy->Ennemy->dirState = UP_RIGHT;
							//}
							///*BAS_DROITE*/
							//if (CurrentEnnemy->Ennemy->vNormalizeDirection.x < 0 && CurrentEnnemy->Ennemy->vNormalizeDirection.y > 0)
							//{
							//	CurrentEnnemy->Ennemy->dirState = DOWN_LEFT;
							//}
							///*BAS_GAUCHE*/
							//if (CurrentEnnemy->Ennemy->vNormalizeDirection.x < 0 && CurrentEnnemy->Ennemy->vNormalizeDirection.y < 0)
							//{
							//	CurrentEnnemy->Ennemy->dirState = UP_LEFT;
							//}

							if (CurrentEnnemy->Id == 0)
							{
								printf("vNormalizeDirection.x %.2f\t", CurrentEnnemy->Ennemy->vNormalizeDirection.x);
								printf("vNormalizeDirection.y %.2f\t\n", CurrentEnnemy->Ennemy->vNormalizeDirection.y);
							}

		#pragma endregion DIRECTION SPRITE EN FONCTION DE LA DIRECTION //GUILLAUME

		#pragma region DEPLACEMENT PAR COULEUR TEST

							/*if (iCurrentLevel == TEST)
							{
								if (CurrentEnnemy->Ennemy->iDirection == UP_RIGHT)
								{
									CurrentEnnemy->Ennemy->fDesiredAngleDirection = ANGLE_HAUT_DROIT + ANGLE_VARIANT_ISO;
								}
								if (CurrentEnnemy->Ennemy->iDirection == UP_LEFT)
								{
									CurrentEnnemy->Ennemy->fDesiredAngleDirection = ANGLE_HAUT_GAUCHE - ANGLE_VARIANT_ISO;
								}
								if (CurrentEnnemy->Ennemy->iDirection == DOWN_RIGHT)
								{
									CurrentEnnemy->Ennemy->fDesiredAngleDirection = ANGLE_BAS_DROIT - ANGLE_VARIANT_ISO;
								}
								if (CurrentEnnemy->Ennemy->iDirection == DOWN_LEFT)
								{
									CurrentEnnemy->Ennemy->fDesiredAngleDirection = ANGLE_BAS_GAUCHE + ANGLE_VARIANT_ISO;
								}
							}*/

		#pragma endregion DEPLACEMENT PAR COULEUR TEST

		#pragma region DEPLACEMENT PAR POINT

							
								/*PROCHAIN POINT QUE DOIT VISER L'ENNEMI*/

								/*JE LIS LA LISTE DE POINT DU NIVEAU*/
								
								CurrentEnnemyPathPoint = CurrentLevelAssets.TabListEnnemyPathPoint[CurrentEnnemy->Ennemy->PathToFollow]->LastElement;
								while (CurrentEnnemyPathPoint != NULL)
								{
									/*LE POINT VISE*/
									if (CurrentEnnemy->Ennemy->iPosPathToTarget == CurrentEnnemyPathPoint->EnnemyPathPoint->Num)
									{
										CurrentEnnemy->Ennemy->vPosPathToTarget.x = CurrentEnnemyPathPoint->EnnemyPathPoint->vPos.x;
										CurrentEnnemy->Ennemy->vPosPathToTarget.y = CurrentEnnemyPathPoint->EnnemyPathPoint->vPos.y;
										CurrentEnnemy->Ennemy->vCurrentDirection.x = CurrentEnnemy->Ennemy->vPosPathToTarget.x - CurrentEnnemy->Ennemy->vCurrentPosition.x;
										CurrentEnnemy->Ennemy->vCurrentDirection.y = CurrentEnnemy->Ennemy->vPosPathToTarget.y - CurrentEnnemy->Ennemy->vCurrentPosition.y;
										CurrentEnnemy->Ennemy->fDesiredAngleDirection = GetAngleDegreeFromVector(CurrentEnnemy->Ennemy->vCurrentDirection);

										/*si il y a magnitude avec le point je change de cible*/
										if (Magnitude(CurrentEnnemy->Ennemy->vCurrentDirection) < 50)
										{
											if (CurrentEnnemyPathPoint->PreviousElement != NULL)
											{
												CurrentEnnemy->Ennemy->iPosPathToTarget = CurrentEnnemyPathPoint->PreviousElement->EnnemyPathPoint->Num;
											}
										}
									}

									CurrentEnnemyPathPoint = CurrentEnnemyPathPoint->PreviousElement;
								}

		#pragma endregion DEPLACEMENT PAR POINT

		#pragma region VARIATION LEGERE //GUILLAUME

							/*méthode avec random*/
							/*CurrentEnnemy->Ennemy->fTimeSinceLastVariation += timeSinceLastFrame;

							if (CurrentEnnemy->Ennemy->fTimeSinceLastVariation > TIME_BETWEEN_VARIATION)
							{
							CurrentEnnemy->Ennemy->fTimeSinceLastVariation = 0;
							CurrentEnnemy->Ennemy->iRandVariation = rand() % 2 + 1;
							if (CurrentEnnemy->Ennemy->iRandVariation == 1)
							{
							CurrentEnnemy->Ennemy->fDesiredAngleDirection += ANGLE_INCREASE;
							}
							else if (CurrentEnnemy->Ennemy->iRandVariation == 2)
							{
							CurrentEnnemy->Ennemy->fDesiredAngleDirection -= ANGLE_INCREASE;
							}
							}*/

		#pragma endregion VARIATION LEGERE //GUILLAUME

							CurrentEnnemy->Ennemy->fCurrentAngleDirection = CurrentEnnemy->Ennemy->fDesiredAngleDirection;
							CurrentEnnemy->Ennemy->vCurrentDirection = GetDirectionFromAngleDegrees(CurrentEnnemy->Ennemy->fCurrentAngleDirection);
						}

		#pragma region CAS DE COLLISION //GUILLAUME

						/*GESTION COLLISION*/
						else if (manageEnnemi(CurrentEnnemy, CurrentLevelAssets.mapMask, timeSinceLastFrame) == sfTrue)
						{
							if (sfKeyboard_isKeyPressed(sfKeyD) == sfTrue)
							{
								printf("debug");
							}

							/*incrémentation pour les 2 vecteurs sur les cotés*/
							CurrentEnnemy->Ennemy->fCollideIncrementation += timeSinceLastFrame;

							CurrentEnnemy->Ennemy->vSideLeftControlPoint.x = CurrentEnnemy->Ennemy->vNormalizeDirection.x - (((CurrentEnnemy->Ennemy->fControlRadius / 10) * sin(DegToRad(-CurrentEnnemy->Ennemy->fAngleSprite))) * CurrentEnnemy->Ennemy->fCollideIncrementation);
							CurrentEnnemy->Ennemy->vSideLeftControlPoint.y = CurrentEnnemy->Ennemy->vNormalizeDirection.y - (((CurrentEnnemy->Ennemy->fControlRadius / 10) * cos(DegToRad(-CurrentEnnemy->Ennemy->fAngleSprite))) * CurrentEnnemy->Ennemy->fCollideIncrementation);
							CurrentEnnemy->Ennemy->vSideLeftControlPoint.x += CurrentEnnemy->Ennemy->vLeftStartPoint.x;
							CurrentEnnemy->Ennemy->vSideLeftControlPoint.y += CurrentEnnemy->Ennemy->vLeftStartPoint.y;

							CurrentEnnemy->Ennemy->vSideRightControlPoint.x = CurrentEnnemy->Ennemy->vNormalizeDirection.x + (((CurrentEnnemy->Ennemy->fControlRadius / 10)* sin(DegToRad(-CurrentEnnemy->Ennemy->fAngleSprite))) * CurrentEnnemy->Ennemy->fCollideIncrementation);
							CurrentEnnemy->Ennemy->vSideRightControlPoint.y = CurrentEnnemy->Ennemy->vNormalizeDirection.y + (((CurrentEnnemy->Ennemy->fControlRadius / 10)* cos(DegToRad(-CurrentEnnemy->Ennemy->fAngleSprite))) * CurrentEnnemy->Ennemy->fCollideIncrementation);
							CurrentEnnemy->Ennemy->vSideRightControlPoint.x += CurrentEnnemy->Ennemy->vRightStartPoint.x;
							CurrentEnnemy->Ennemy->vSideRightControlPoint.y += CurrentEnnemy->Ennemy->vRightStartPoint.y;

							/*POINT DE VERIFICATION A GAUCHE DE L'ENTITE*/
							if (CurrentEnnemy->Ennemy->vSideLeftControlPoint.x > 0 && CurrentEnnemy->Ennemy->vSideLeftControlPoint.x < WINDOW_WIDTH
								&& CurrentEnnemy->Ennemy->vSideLeftControlPoint.y > 0 && CurrentEnnemy->Ennemy->vSideLeftControlPoint.y < WINDOW_HEIGHT)
							{
								if (sfImage_getPixel(CurrentLevelAssets.mapMask, CurrentEnnemy->Ennemy->vSideLeftControlPoint.x, CurrentEnnemy->Ennemy->vSideLeftControlPoint.y).r == 255 && sfImage_getPixel(CurrentLevelAssets.mapMask, CurrentEnnemy->Ennemy->vSideLeftControlPoint.x, CurrentEnnemy->Ennemy->vSideLeftControlPoint.y).g == 0
									&& sfImage_getPixel(CurrentLevelAssets.mapMask, CurrentEnnemy->Ennemy->vSideLeftControlPoint.x, CurrentEnnemy->Ennemy->vSideLeftControlPoint.y).b == 0 && sfImage_getPixel(CurrentLevelAssets.mapMask, CurrentEnnemy->Ennemy->vSideLeftControlPoint.x, CurrentEnnemy->Ennemy->vSideLeftControlPoint.y).a == 255)
								{
									//printf("COLLISION DROITE\n");
									CurrentEnnemy->Ennemy->iCollideControlSideLeft = 1;
								}
								else
								{
									CurrentEnnemy->Ennemy->iCollideControlSideLeft = 0;
								}
							}

							/*POINT DE VERIFICATION A DROITE DE L'ENTITE*/
							if (CurrentEnnemy->Ennemy->vSideRightControlPoint.x > 0 && CurrentEnnemy->Ennemy->vSideRightControlPoint.x < WINDOW_WIDTH
								&& CurrentEnnemy->Ennemy->vSideRightControlPoint.y > 0 && CurrentEnnemy->Ennemy->vSideRightControlPoint.y < WINDOW_HEIGHT)
							{
								if (sfImage_getPixel(CurrentLevelAssets.mapMask, CurrentEnnemy->Ennemy->vSideRightControlPoint.x, CurrentEnnemy->Ennemy->vSideRightControlPoint.y).r == 255 && sfImage_getPixel(CurrentLevelAssets.mapMask, CurrentEnnemy->Ennemy->vSideRightControlPoint.x, CurrentEnnemy->Ennemy->vSideRightControlPoint.y).g == 0
									&& sfImage_getPixel(CurrentLevelAssets.mapMask, CurrentEnnemy->Ennemy->vSideRightControlPoint.x, CurrentEnnemy->Ennemy->vSideRightControlPoint.y).b == 0 && sfImage_getPixel(CurrentLevelAssets.mapMask, CurrentEnnemy->Ennemy->vSideRightControlPoint.x, CurrentEnnemy->Ennemy->vSideRightControlPoint.y).a == 255)
								{
									//printf("COLLISION DROITE\n");
									CurrentEnnemy->Ennemy->iCollideControlSideRight = 1;
								}
								else
								{
									CurrentEnnemy->Ennemy->iCollideControlSideRight = 0;
								}
							}

							/*je change la direction de mon entité*/
							/*CONTACT DROIT*/
							if (CurrentEnnemy->Ennemy->iCollideControlSideRight == 1)
							{
								CurrentEnnemy->Ennemy->fDesiredAngleDirection -= ANGLE_ROTATION;
								CurrentEnnemy->Ennemy->fCollideIncrementation = 1; // reset a 1 pour redémarrer l'incrémentation
							}
							/*CONTACT GAUCHE*/
							else if (CurrentEnnemy->Ennemy->iCollideControlSideLeft == 1)
							{
								CurrentEnnemy->Ennemy->fDesiredAngleDirection += ANGLE_ROTATION;
								CurrentEnnemy->Ennemy->fCollideIncrementation = 1; // reset a 1 pour redémarrer l'incrémentation
							}

							CurrentEnnemy->Ennemy->fCurrentAngleDirection = CurrentEnnemy->Ennemy->fDesiredAngleDirection;
							/*la direction actuel du personnage est calculé par rapport a l'angle désirer*/
							CurrentEnnemy->Ennemy->vCurrentDirection = GetDirectionFromAngleDegrees(CurrentEnnemy->Ennemy->fCurrentAngleDirection);
						}

		#pragma endregion CAS DE COLLISION //GUILLAUME


	#pragma endregion GESTION DEPLACEMENTS //GUILLAUME

					/*DETECTION DU NOMBRE DE VEINE PASSER PAR L'ENNEMI*/

	#pragma region GESTION COMPTEUR DE VEINE PASSE PAR ENNEMI

					CurrentTowerSlot = ListTowerSlot->FirstElement;
					while (CurrentTowerSlot != NULL)
					{
						if (CurrentEnnemy->Ennemy->EnnemyIsInTheDetectionZone == sfFalse)
						{
							CurrentEnnemy->Ennemy->vDistToTowerDetectionPos.x = CurrentTowerSlot->TowerSlot->vSpawnPos.x - CurrentEnnemy->Ennemy->vCurrentPosition.x;
							CurrentEnnemy->Ennemy->vDistToTowerDetectionPos.y = CurrentTowerSlot->TowerSlot->vSpawnPos.y - CurrentEnnemy->Ennemy->vCurrentPosition.y;
							/*Veine actuelle dans laquelle se situe l'ennemi*/
							if (Magnitude(CurrentEnnemy->Ennemy->vDistToTowerDetectionPos) < DETECTION_POSITION_RADIUS)
							{

								CurrentEnnemy->Ennemy->iCurrentTowerDetectionZoneId = CurrentTowerSlot->Id;
								CurrentEnnemy->Ennemy->EnnemyIsInTheDetectionZone = sfTrue;

							}
						}

						/*je fais mon calcul pour définir que l'ennemi a passer la veine seulement avec la veine que je sauvegarde*/
						if (CurrentEnnemy->Ennemy->iCurrentTowerDetectionZoneId == CurrentTowerSlot->Id)
						{
							CurrentEnnemy->Ennemy->vDistToTowerDetectionPos.x = CurrentTowerSlot->TowerSlot->vSpawnPos.x - CurrentEnnemy->Ennemy->vCurrentPosition.x;
							CurrentEnnemy->Ennemy->vDistToTowerDetectionPos.y = CurrentTowerSlot->TowerSlot->vSpawnPos.y - CurrentEnnemy->Ennemy->vCurrentPosition.y;
							if (Magnitude(CurrentEnnemy->Ennemy->vDistToTowerDetectionPos) > DETECTION_POSITION_RADIUS + 20
								&& CurrentEnnemy->Ennemy->EnnemyIsInTheDetectionZone == sfTrue)
							{
								CurrentEnnemy->Ennemy->EnnemyIsInTheDetectionZone = sfFalse;
								CurrentEnnemy->Ennemy->iNbrTowerSinceLastAttack++;
								CurrentEnnemy->Ennemy->vDistToTowerDetectionPos.x = 0;
								CurrentEnnemy->Ennemy->vDistToTowerDetectionPos.y = 0;
							}

						}

						CurrentTowerSlot = CurrentTowerSlot->NextElement;
					}

					/*CONDITIONS POUR QU'UN ENNEMI ATTAQUE*/
					if (CurrentEnnemy->Ennemy->iIsAttack == sfFalse)
					{
						CurrentEnnemy->Ennemy->fTimeSinceLastAttack += timeSinceLastFrame;
						if (CurrentEnnemy->Ennemy->fTimeSinceLastAttack > CurrentEnnemy->Ennemy->fTimeBetweenAttack
							&& CurrentEnnemy->Ennemy->iNbrTowerSinceLastAttack >= CurrentEnnemy->Ennemy->iNbrTowerBetweenAttack)
						{
							CurrentEnnemy->Ennemy->iTowerToAttackId = -1;
							CurrentEnnemy->Ennemy->iTowerIsChosen = 0;
							CurrentEnnemy->Ennemy->iIsAttack = sfTrue;
						}
					}

	#pragma endregion GESTION COMPTEUR DE VEINE PASSE PAR ENNEMI

	#pragma region ATTAQUE CAILLOT DE SANG



					if (CurrentEnnemy->Ennemy->Type == CAILLOT)
					{
						/*attaque du cholesterol*/
						if (CurrentEnnemy->Ennemy->iIsAttack == sfTrue)
						{
							/*repérage tour le plus proche grâce a la magnitude*/
							CurrentTowerSlot = ListTowerSlot->FirstElement;
							while (CurrentTowerSlot != NULL)
							{
								/*si une tour est construite je calcule la distance entre le point de spawn des globules blancs
								qui correspond donc a la position de la zone de détection*/
								if (CurrentTowerSlot->TowerSlot->IsBuild == sfTrue)
								{
									CurrentEnnemy->Ennemy->vDistToTowerDetectionPos.x = CurrentTowerSlot->TowerSlot->vSpawnPos.x - CurrentEnnemy->Ennemy->vCurrentPosition.x;
									CurrentEnnemy->Ennemy->vDistToTowerDetectionPos.y = CurrentTowerSlot->TowerSlot->vSpawnPos.y - CurrentEnnemy->Ennemy->vCurrentPosition.y;
									if (Magnitude(CurrentEnnemy->Ennemy->vDistToTowerDetectionPos) < DETECTION_POSITION_RADIUS)
									{
										/*la tour a attaquer possède l'id du slot*/

										if (CurrentEnnemy->Ennemy->iTowerIsChosen == 0)
										{
											CurrentEnnemy->Ennemy->iTowerToAttackId = CurrentTowerSlot->TowerSlot->TowerBuildId;
											CurrentEnnemy->Ennemy->vPosTowerToAttack.x = CurrentTowerSlot->TowerSlot->vPos.x;
											CurrentEnnemy->Ennemy->vPosTowerToAttack.y = CurrentTowerSlot->TowerSlot->vPos.y;
											CurrentEnnemy->Ennemy->iTowerIsChosen = 1;
										}
									}
								}
								CurrentTowerSlot = CurrentTowerSlot->NextElement;
							}

							CurrentTower = ListTower->FirstElement;
							while (CurrentTower != NULL)
							{
								if (CurrentEnnemy->Ennemy->iTowerIsChosen == 1)
								{
									//printf("debug");
									/*la tour visé*/
									if (CurrentEnnemy->Ennemy->iTowerToAttackId == CurrentTower->Id)
									{
										CurrentEnnemy->Ennemy->vCurrentDirection.x = CurrentEnnemy->Ennemy->vPosTowerToAttack.x - CurrentEnnemy->Ennemy->vCurrentPosition.x;
										CurrentEnnemy->Ennemy->vCurrentDirection.y = CurrentEnnemy->Ennemy->vPosTowerToAttack.y - CurrentEnnemy->Ennemy->vCurrentPosition.y;
										//if (Magnitude(CurrentEnnemy->Ennemy->vCurrentDirection) < DETECTION_SLOT_RADIUS)
										if (CurrentEnnemy->Ennemy->Color_ToCheck.r == 255)
										{
											CurrentEnnemy->Ennemy->fTimeSinceLastAttack = 0;
											CurrentEnnemy->Ennemy->iNbrTowerSinceLastAttack = 0;
											/*dégats sur la tour*/
											CurrentTower->Tower->iHP -= CurrentEnnemy->Ennemy->Deg;
											CurrentEnnemy->Ennemy->iIsAttack = sfFalse;
											CurrentEnnemy->Ennemy->fTimeSinceLastAttack = 0;
										}
									}
								}
								CurrentTower = CurrentTower->NextElement;
							}
						}
					}

					if (CurrentEnnemy->Id == 0)
					{
						//printf("NBR TOWER SINCE LAST ATTACK : %d\n", CurrentEnnemy->Ennemy->iNbrTowerSinceLastAttack);
					}

	#pragma endregion ATTAQUE CAILLOT DE SANG

	#pragma region ATTAQUE CHOLESTEROL

					if (CurrentEnnemy->Ennemy->Type == CHOLESTEROL)
					{


						/*attaque du cholesterol*/
						if (CurrentEnnemy->Ennemy->iIsAttack == sfTrue)
						{
							/*repérage tour le plus proche grâce a la magnitude*/
							CurrentTowerSlot = ListTowerSlot->FirstElement;
							while (CurrentTowerSlot != NULL)
							{
								/*si une tour est construite je calcule la distance entre le point de spawn des globules blancs
								qui correspond donc a la position de la zone de détection*/
								if (CurrentTowerSlot->TowerSlot->IsBuild == sfTrue)
								{
									CurrentEnnemy->Ennemy->vDistToTowerDetectionPos.x = CurrentTowerSlot->TowerSlot->vSpawnPos.x - CurrentEnnemy->Ennemy->vCurrentPosition.x;
									CurrentEnnemy->Ennemy->vDistToTowerDetectionPos.y = CurrentTowerSlot->TowerSlot->vSpawnPos.y - CurrentEnnemy->Ennemy->vCurrentPosition.y;
									if (Magnitude(CurrentEnnemy->Ennemy->vDistToTowerDetectionPos) < DETECTION_POSITION_RADIUS)
									{
										/*la tour a attaquer possède l'id du slot*/

										if (CurrentEnnemy->Ennemy->iTowerIsChosen == 0)
										{
											CurrentEnnemy->Ennemy->iTowerToAttackId = CurrentTowerSlot->TowerSlot->TowerBuildId;
											CurrentEnnemy->Ennemy->iTowerIsChosen = 1;
										}
									}
								}
								CurrentTowerSlot = CurrentTowerSlot->NextElement;
							}

							CurrentTower = ListTower->FirstElement;
							while (CurrentTower != NULL)
							{
								if (CurrentEnnemy->Ennemy->iTowerIsChosen == 1)
								{
									printf("debug");
									/*la tour visé*/
									if (CurrentEnnemy->Ennemy->iTowerToAttackId == CurrentTower->Id)
									{
										CurrentEnnemy->Ennemy->vPosTowerToAttack.x = CurrentTower->Tower->vPos.x;
										CurrentEnnemy->Ennemy->vPosTowerToAttack.y = CurrentTower->Tower->vPos.y;

										/*création d'une balle*/
	#pragma region CHOLESTEROL BULLET

										NewEnnemyBullet = AddElementBeginListEnnemyBullet(ListEnnemyBullet);
										NewEnnemyBullet->EnnemyBullet = malloc(sizeof(t_EnnemyBullet));

										NewEnnemyBullet->EnnemyBullet->iTowerToTargetId = CurrentEnnemy->Ennemy->iTowerToAttackId;
										NewEnnemyBullet->EnnemyBullet->sprite = Sp_EnnemyBullet;
										NewEnnemyBullet->EnnemyBullet->Deg = CurrentEnnemy->Ennemy->Deg;
										NewEnnemyBullet->EnnemyBullet->fSpeedMax = CHOLESTEROL_BULLET_SPEED;
										NewEnnemyBullet->EnnemyBullet->fSpeed = 0;
										NewEnnemyBullet->EnnemyBullet->iHP = 1;

										NewEnnemyBullet->EnnemyBullet->vOrigin.x = sfSprite_getGlobalBounds(NewEnnemyBullet->EnnemyBullet->sprite).width / 2;
										NewEnnemyBullet->EnnemyBullet->vOrigin.y = sfSprite_getGlobalBounds(NewEnnemyBullet->EnnemyBullet->sprite).height / 2;
										sfSprite_setOrigin(NewEnnemyBullet->EnnemyBullet->sprite, NewEnnemyBullet->EnnemyBullet->vOrigin);
										NewEnnemyBullet->EnnemyBullet->vPos.x = CurrentEnnemy->Ennemy->vCurrentPosition.x;
										NewEnnemyBullet->EnnemyBullet->vPos.y = CurrentEnnemy->Ennemy->vCurrentPosition.y;
										sfSprite_setPosition(NewEnnemyBullet->EnnemyBullet->sprite, NewEnnemyBullet->EnnemyBullet->vPos);
										NewEnnemyBullet->EnnemyBullet->vCurrentDirection.x = CurrentTower->Tower->vPos.x - NewEnnemyBullet->EnnemyBullet->vPos.x;
										NewEnnemyBullet->EnnemyBullet->vCurrentDirection.y = CurrentTower->Tower->vPos.y - NewEnnemyBullet->EnnemyBullet->vPos.y;
										NewEnnemyBullet->EnnemyBullet->fAngleSprite = GetAngleDegreeFromVector(NewEnnemyBullet->EnnemyBullet->vCurrentDirection);
										sfSprite_setRotation(NewEnnemyBullet->EnnemyBullet->sprite, NewEnnemyBullet->EnnemyBullet->fAngleSprite);

	#pragma endregion CHOLESTEROL BULLET
										CurrentEnnemy->Ennemy->iIsAttack = sfFalse;
										CurrentEnnemy->Ennemy->fTimeSinceLastAttack = 0;
									}
								}

								CurrentTower = CurrentTower->NextElement;
							}
						}
					}

	#pragma endregion ATTAQUE CHOLESTEROL

	#pragma region GESTION CHOLESTEROL

					if (CurrentEnnemy->Ennemy->Type == CHOLESTEROL)
					{
						if (CurrentEnnemy->Ennemy->Hp < (CurrentEnnemy->Ennemy->HpMax * 0.7))
						{
							CurrentEnnemy->Ennemy->iSize = MEDIUM;
							CurrentEnnemy->Ennemy->Deg = 3;
							CurrentEnnemy->Ennemy->fSpeedMax = CHOLESTEROL_SPEED * 1.5;
							CurrentEnnemy->Ennemy->vScale.x = 0.6;
							CurrentEnnemy->Ennemy->vScale.y = 0.6;
						}

						if (CurrentEnnemy->Ennemy->Hp < (CurrentEnnemy->Ennemy->HpMax * 0.3))
						{
							CurrentEnnemy->Ennemy->iSize = SMALL;
							CurrentEnnemy->Ennemy->Deg = 1;
							CurrentEnnemy->Ennemy->fSpeedMax = CHOLESTEROL_SPEED * 2;
							CurrentEnnemy->Ennemy->vScale.x = 0.3;
							CurrentEnnemy->Ennemy->vScale.y = 0.3;
						}
					}

	#pragma endregion GESTION CHOLESTEROL

					/*GESTION VELOCITE / VITESSE*/

	#pragma region GESTION VELOCITE / VITESSE //GUILLAUME

					if (CurrentEnnemy->Ennemy->fSpeed < 0)
					{
						CurrentEnnemy->Ennemy->fSpeed = 0;
					}

					if (CurrentEnnemy->Ennemy->fSpeed < CurrentEnnemy->Ennemy->fSpeedMax)
					{
						CurrentEnnemy->Ennemy->fSpeed += ENNEMY_ACCELERATION;
					}
					else if (CurrentEnnemy->Ennemy->fSpeed > CurrentEnnemy->Ennemy->fSpeedMax)
					{
						CurrentEnnemy->Ennemy->fSpeed -= ENNEMY_ACCELERATION;
					}

	#pragma endregion GESTION VELOCITE / VITESSE //GUILLAUME

	#pragma region POSITION & VELOCITE

					/*VELOCITY*/
					CurrentEnnemy->Ennemy->vCurrentVelocity.x = CurrentEnnemy->Ennemy->vCurrentDirection.x * (CurrentEnnemy->Ennemy->fSpeed*CurrentEnnemy->Ennemy->fSpeedFactor);
					CurrentEnnemy->Ennemy->vCurrentVelocity.y = CurrentEnnemy->Ennemy->vCurrentDirection.y *(CurrentEnnemy->Ennemy->fSpeed*CurrentEnnemy->Ennemy->fSpeedFactor);
					CurrentEnnemy->Ennemy->vCurrentVelocity = Truncate(CurrentEnnemy->Ennemy->vCurrentVelocity, CurrentEnnemy->Ennemy->fSpeedMax);

					/*POSIITON*/
					CurrentEnnemy->Ennemy->vCurrentPosition.x += CurrentEnnemy->Ennemy->vCurrentVelocity.x * timeSinceLastFrame;
					CurrentEnnemy->Ennemy->vCurrentPosition.y += CurrentEnnemy->Ennemy->vCurrentVelocity.y * timeSinceLastFrame;

	#pragma endregion POSITION & VELOCITE

	#pragma region ANIMATION

					CurrentEnnemy->Ennemy->fTimeSinceLastAnimation += timeSinceLastFrame;
					if (CurrentEnnemy->Ennemy->fTimeSinceLastAnimation > CurrentEnnemy->Ennemy->fTimeBetweenAnimation)
					{
						CurrentEnnemy->Ennemy->fTimeSinceLastAnimation = 0;
						/*if (CurrentEnnemy->Ennemy->iAnimationFrameX < CurrentEnnemy->Ennemy->iNbrFrameX - 1)
						{
						CurrentEnnemy->Ennemy->iAnimationFrameX++;
						}
						else
						CurrentEnnemy->Ennemy->iAnimationFrameX = 0;*/

					}

					CurrentEnnemy->Ennemy->animRect.left = CurrentEnnemy->Ennemy->animRect.width * CurrentEnnemy->Ennemy->iAnimationFrameX;
					CurrentEnnemy->Ennemy->animRect.top = CurrentEnnemy->Ennemy->animRect.height * CurrentEnnemy->Ennemy->dirState;


	#pragma endregion ANIMATION

	#pragma region PERTE DE PV OBJECTIF

					if (CurrentEnnemy->Ennemy->vCurrentPosition.x < CurrentEnnemy->Ennemy->vTargetPostion.x + ENNEMY_DIST_FROM_TARGET_TO_DELETE
						&& CurrentEnnemy->Ennemy->vCurrentPosition.x > CurrentEnnemy->Ennemy->vTargetPostion.x - ENNEMY_DIST_FROM_TARGET_TO_DELETE
						&& CurrentEnnemy->Ennemy->vCurrentPosition.y < CurrentEnnemy->Ennemy->vTargetPostion.y + ENNEMY_DIST_FROM_TARGET_TO_DELETE
						&& CurrentEnnemy->Ennemy->vCurrentPosition.y > CurrentEnnemy->Ennemy->vTargetPostion.y - ENNEMY_DIST_FROM_TARGET_TO_DELETE)
					{
						CurrentEnnemy->Ennemy->iDespawn = 1;
					}

					if (CurrentEnnemy->Ennemy->iDespawn == 1)
					{
						if (iGoalHp > 0)
						{
							iGoalHp -= CurrentEnnemy->Ennemy->Deg;
						}
						else
						{
							iGoalHp = 0;
						}
						/*PIROUETTE*/
						CurrentEnnemy->Ennemy->Hp = -200;
					}


	#pragma endregion PERTE DE PV OBJECTIF

					//printf("ANGLE SPRITE : %.2f | CURRENT ANGLE : %.2f\n", CurrentEnnemy->Ennemy->fAngleSprite, CurrentEnnemy->Ennemy->fCurrentAngleDirection);
					//CurrentEnnemy->Ennemy->fAngleSprite = GetAngleDegreeFromVector(CurrentEnnemy->Ennemy->vCurrentVelocity);

					//printf("DIRECTION X : %.2f | DIRECTION Y : %.2f\n", CurrentEnnemy->Ennemy->vCurrentDirection.x, CurrentEnnemy->Ennemy->vCurrentDirection.y);
					//printf("VELOCITY X : %.2f | VELOCITY Y : %.2f\n", CurrentEnnemy->Ennemy->vCurrentVelocity.x, CurrentEnnemy->Ennemy->vCurrentVelocity.y);
					//printf("COLLIDE : %d\n", CurrentEnnemy->Ennemy->iIsColliding);
					CurrentEnnemy = CurrentEnnemy->NextElement;

				}

	#pragma endregion READ LIST ENNEMY CALCUL //GUILLAUME

	#pragma region CALCUL LIST ENNEMY BULLET //GUILLAUME

				CurrentEnnemyBullet = ListEnnemyBullet->FirstElement;
				while (CurrentEnnemyBullet != NULL)
				{
					/*VITESSE DE LA BALLE*/
					if (CurrentEnnemyBullet->EnnemyBullet->fSpeed < 0)
					{
						CurrentEnnemyBullet->EnnemyBullet->fSpeed = 0;
					}

					if (CurrentEnnemyBullet->EnnemyBullet->fSpeed < CurrentEnnemyBullet->EnnemyBullet->fSpeedMax)
					{
						CurrentEnnemyBullet->EnnemyBullet->fSpeed += CHOLESTEROL_BULLET_ACCELERATION;
					}
					else if (CurrentEnnemyBullet->EnnemyBullet->fSpeed > CurrentEnnemyBullet->EnnemyBullet->fSpeedMax)
					{
						CurrentEnnemyBullet->EnnemyBullet->fSpeed -= CHOLESTEROL_BULLET_ACCELERATION;
					}

					/*DIRECTION DE LA BALLE*/
					/*VELOCITY*/
					CurrentEnnemyBullet->EnnemyBullet->vCurrentVelocity.x = CurrentEnnemyBullet->EnnemyBullet->vCurrentDirection.x * CurrentEnnemyBullet->EnnemyBullet->fSpeed;
					CurrentEnnemyBullet->EnnemyBullet->vCurrentVelocity.y = CurrentEnnemyBullet->EnnemyBullet->vCurrentDirection.y * CurrentEnnemyBullet->EnnemyBullet->fSpeed;
					CurrentEnnemyBullet->EnnemyBullet->vCurrentVelocity = Truncate(CurrentEnnemyBullet->EnnemyBullet->vCurrentVelocity, CurrentEnnemyBullet->EnnemyBullet->fSpeedMax);

					/*POSIITON*/
					CurrentEnnemyBullet->EnnemyBullet->vPos.x += CurrentEnnemyBullet->EnnemyBullet->vCurrentVelocity.x * timeSinceLastFrame;
					CurrentEnnemyBullet->EnnemyBullet->vPos.y += CurrentEnnemyBullet->EnnemyBullet->vCurrentVelocity.y * timeSinceLastFrame;

					/*COLLISION AVEC UNE TOWER*/
					CurrentTower = ListTower->FirstElement;
					while (CurrentTower != NULL)
					{
						if (CurrentTower->Id == CurrentEnnemyBullet->EnnemyBullet->iTowerToTargetId)
						{
							if (SpriteIsOverPosition(CurrentEnnemyBullet->EnnemyBullet->vPos, CurrentEnnemyBullet->EnnemyBullet->vOrigin, CurrentTower->Tower->vPos, CurrentEnnemyBullet->EnnemyBullet->vOrigin))
							{
								CurrentTower->Tower->iHP -= CurrentEnnemyBullet->EnnemyBullet->Deg;
								CurrentEnnemyBullet->EnnemyBullet->iHP = 0;
							}
						}
						CurrentTower = CurrentTower->NextElement;
					}
					if (CurrentEnnemyBullet->EnnemyBullet->iHP <= 0)
					{
						DeleteElementByIdEnnemyBullet(ListEnnemyBullet, CurrentEnnemyBullet->Id);
						break;
					}
					else
						CurrentEnnemyBullet = CurrentEnnemyBullet->NextElement;
				}

	#pragma endregion CALCUL LIST ENNEMY BULLET //GUILLAUME

	#pragma region LECTURE TRAITEMENT AFFICHAGE SLOTS TOURS //SEB
				/*Lecture de liste pour le traitement/affichage des slot de tours*/
				CurrentTowerSlot = ListTowerSlot->FirstElement;
				while (CurrentTowerSlot != NULL)
				{
					vMousePos = sfMouse_getPosition(window);
					vMousePosToFloat.x = (float)vMousePos.x;
					vMousePosToFloat.y = (float)vMousePos.y;
					Rect_TowerSlotBB.left = CurrentTowerSlot->TowerSlot->vPos.x - vOrigin_TowerSlot.x;
					Rect_TowerSlotBB.top = CurrentTowerSlot->TowerSlot->vPos.y - vOrigin_TowerSlot.y;
					Rect_TowerSlotBB.width = vOrigin_TowerSlot.x * 2;
					Rect_TowerSlotBB.height = vOrigin_TowerSlot.y * 2;
					if (sfFloatRect_contains(&Rect_TowerSlotBB, vMousePosToFloat.x, vMousePosToFloat.y) && !isInBuildChoice
						&& !isBuildedChoice && !CurrentTowerSlot->TowerSlot->IsBuild)
					{
						vMousePointToCheck.x = vOrigin_TowerSlot.x - (CurrentTowerSlot->TowerSlot->vPos.x - vMousePosToFloat.x);
						vMousePointToCheck.y = vOrigin_TowerSlot.y - (CurrentTowerSlot->TowerSlot->vPos.y - vMousePosToFloat.y);
						if (sfImage_getPixel(Img_TowerSlotMask, vMousePointToCheck.x, vMousePointToCheck.y).r == 255 && sfImage_getPixel(Img_TowerSlotMask, vMousePointToCheck.x, vMousePointToCheck.y).g == 0
							&& sfImage_getPixel(Img_TowerSlotMask, vMousePointToCheck.x, vMousePointToCheck.y).b == 0 && sfImage_getPixel(Img_TowerSlotMask, vMousePointToCheck.x, vMousePointToCheck.y).a == 255)
						{
							sfSprite_setColor(Sp_TowerSlot, sfRed);
							if (sfMouse_isButtonPressed(sfMouseLeft) && !isMousePressed
								&& !isInBuildChoice && !CurrentTowerSlot->TowerSlot->IsBuild)
							{
								isInBuildChoice = sfTrue;
								isMousePressed = sfTrue;
								ActualTowerSlot = CurrentTowerSlot;
								btn1->vPos = CurrentTowerSlot->TowerSlot->vPos;
								btn2->vPos = CurrentTowerSlot->TowerSlot->vPos;
								btn3->vPos = CurrentTowerSlot->TowerSlot->vPos;
							}
							else if (!sfMouse_isButtonPressed(sfMouseLeft))
							{
								isMousePressed = sfFalse;
							}
						}
						else
						{
							sfSprite_setColor(Sp_TowerSlot, sfWhite);
						}
					}
					else
					{
						sfSprite_setColor(Sp_TowerSlot, sfWhite);
					}
					sfSprite_setPosition(Sp_TowerSlot, CurrentTowerSlot->TowerSlot->vPos);

					sfRenderWindow_drawSprite(window, Sp_TowerSlot, NULL);
					//if (btn1->isOver /*&& CurrentTowerSlot->TowerSlot->IsClicked*/)
					//{
					//	sfSprite_setPosition(Sp_fieldOfView, CurrentTowerSlot->TowerSlot->vPos);
					//	sfRenderWindow_drawSprite(window, Sp_fieldOfView, NULL);
					//}
					CurrentTowerSlot = CurrentTowerSlot->NextElement;
				}
	#pragma endregion LECTURE TRAITEMENT AFFICHAGE SLOTS TOURS //SEB

	#pragma region AFFICHAGE SPAWN TOUR 3 //SEB

				CurrentTowerSlot = ListTowerSlot->FirstElement;
				while (CurrentTowerSlot != NULL)
				{
					if (CurrentTowerSlot->TowerSlot->IsBuild && CurrentTowerSlot->TowerSlot->BuildedType == TYPE3)
					{
						//printf_s("slot x : %.2f,y : %.2f\n", CurrentTowerSlot->TowerSlot->vSpawnPos.x, CurrentTowerSlot->TowerSlot->vSpawnPos.y);
						sfSprite_setPosition(spawnCross, CurrentTowerSlot->TowerSlot->vSpawnPos);
						sfRenderWindow_drawSprite(window, spawnCross, NULL);
					}

					CurrentTowerSlot = CurrentTowerSlot->NextElement;
				}

	#pragma endregion AFFICHAGE SPAWN TOUR 3 POSEE //SEB

	#pragma region LECTURE TRAITEMENT DES TOURS //SEB

				/*Lecture de boucle TOUR pour le traitement*/
				CurrentTower = ListTower->FirstElement;
				while (CurrentTower != NULL)
				{
					vMousePos = sfMouse_getPosition(window);
					vMousePosToFloat.x = (float)vMousePos.x;
					vMousePosToFloat.y = (float)vMousePos.y;

					if (sfFloatRect_contains(&CurrentTower->Tower->boundingBox, vMousePosToFloat.x, vMousePosToFloat.y) && !isBuildedChoice)
					{

						vMousePointToCheck.x = (sfSprite_getGlobalBounds(CurrentTower->Tower->sprite).width / 2) - (CurrentTower->Tower->vPos.x - vMousePosToFloat.x);
						vMousePointToCheck.y = (sfSprite_getGlobalBounds(CurrentTower->Tower->sprite).height - 15) - (CurrentTower->Tower->vPos.y - vMousePosToFloat.y);
						if (sfImage_getPixel(Img_TowerMask, vMousePointToCheck.x, vMousePointToCheck.y).r == 255 && sfImage_getPixel(Img_TowerMask, vMousePointToCheck.x, vMousePointToCheck.y).g == 0
							&& sfImage_getPixel(Img_TowerMask, vMousePointToCheck.x, vMousePointToCheck.y).b == 0 && sfImage_getPixel(Img_TowerMask, vMousePointToCheck.x, vMousePointToCheck.y).a == 255)
						{
							if (sfMouse_isButtonPressed(sfMouseLeft) && !isMousePressed)
							{
								isMousePressed = sfTrue;
								isBuildedChoice = sfTrue;
								ActualTower = CurrentTower;
								btnUpgrade->vPos = ActualTower->Tower->vPos;
								btnSell->vPos = ActualTower->Tower->vPos;
							}
							else if (!sfMouse_isButtonPressed(sfMouseLeft))
							{
								isMousePressed = sfFalse;
							}
						}
					}

					/*delete de la tour //Guillaume*/
					if (CurrentTower->Tower->iHP <= 0)
					{
						CurrentTowerSlot = ListTowerSlot->FirstElement;
						while (CurrentTowerSlot != NULL)
						{
							if (CurrentTowerSlot->Id == CurrentTower->Tower->iSlotId)
							{
								CurrentTowerSlot->TowerSlot->IsBuild = sfFalse;
								CurrentTowerSlot->TowerSlot->IsClicked = sfFalse;
								break;
							}
							//Rect_TowerSlotBB.left = CurrentTowerSlot->TowerSlot->vPos.x - vOrigin_TowerSlot.x;
							//Rect_TowerSlotBB.top = CurrentTowerSlot->TowerSlot->vPos.y - vOrigin_TowerSlot.y;
							//Rect_TowerSlotBB.width = vOrigin_TowerSlot.x * 2;
							//Rect_TowerSlotBB.height = vOrigin_TowerSlot.y * 2;
							//sfFloatRect test = sfSprite_getGlobalBounds(ActualTower->Tower->sprite);
							//if (sfFloatRect_intersects(&ActualTower->Tower->boundingBox, &Rect_TowerSlotBB, NULL))
							//{
							//	CurrentTowerSlot->TowerSlot->IsBuild = 0;
							//	CurrentTowerSlot->TowerSlot->IsClicked = 0;
							//	break;
							//}
							CurrentTowerSlot = CurrentTowerSlot->NextElement;
						}
						DeleteEntityWithID(ListTower, CurrentTower->Id);
						break;
					}
					else
						CurrentTower = CurrentTower->NextElement;
				}

				////affichage du champ de vision de la tour selectionnée
				if (isBuildedChoice)
				{
					sfSprite_setPosition(Sp_fieldOfView, ActualTower->Tower->vPos);
					sfRenderWindow_drawSprite(window, Sp_fieldOfView, NULL);
				}
	#pragma endregion LECTURE TRAITEMENT DES TOURS //SEB

	#pragma region LECTURE TRAITEMENT SPAWN DES GLOBULES BLANCS //SEB

				CurrentTower = ListTower->FirstElement;
				while (CurrentTower != NULL)
				{
					if (CurrentTower->Tower->TowerType == TYPE3)
					{
						CurrentTower->Tower->tCurrentSpawnWhiteCell = (float)clock() / CLOCKS_PER_SEC;
						CurrentTower->Tower->tSinceSpawnWhiteCell = CurrentTower->Tower->tCurrentSpawnWhiteCell - CurrentTower->Tower->tStartSpawnWhiteCell;
						//printf_s("iIsWhiteCellAlive : %d,tSinceSpawnWhiteCell : %.2f,CurrentTower->Tower->isFirstBuild : %d\n", CurrentTower->Tower->iIsWhiteCellAlive, CurrentTower->Tower->tSinceSpawnWhiteCell, CurrentTower->Tower->isFirstBuild);
						if (!CurrentTower->Tower->iIsWhiteCellAlive && CurrentTower->Tower->isFirstBuild)
						{
							NewWhiteCell = AddElementBeginListWhiteCell(ListWhiteCell);
							NewWhiteCell->whiteCell = malloc(sizeof(t_whiteCell));
							NewWhiteCell->whiteCell->isWalking = sfFalse;
							NewWhiteCell->whiteCell->iTowerId = CurrentTower->Id;
							NewWhiteCell->whiteCell->tStartAnim = (float)clock() / CLOCKS_PER_SEC;
							NewWhiteCell->whiteCell->tSinceAnim = 0;
							NewWhiteCell->whiteCell->tCurrentAnim = 0;
							NewWhiteCell->whiteCell->animFrame = 0;
							NewWhiteCell->whiteCell->dirState = DOWN_RIGHT;
							NewWhiteCell->whiteCell->sprite = Spr_whiteCell;
							NewWhiteCell->whiteCell->animRect.left = NewWhiteCell->whiteCell->animFrame * WHITE_CELL_WIDTH;
							NewWhiteCell->whiteCell->animRect.top = NewWhiteCell->whiteCell->dirState * WHITE_CELL_HEIGHT;
							NewWhiteCell->whiteCell->animRect.width = WHITE_CELL_WIDTH;
							NewWhiteCell->whiteCell->animRect.height = WHITE_CELL_HEIGHT;
							//sfSprite_setTextureRect(NewWhiteCell->whiteCell->sprite, NewWhiteCell->whiteCell->animRect);

							/*deplacment par point*/
							NewWhiteCell->whiteCell->vDirectionPosPathToTarget.x = 0;
							NewWhiteCell->whiteCell->vDirectionPosPathToTarget.y = 0;
							NewWhiteCell->whiteCell->vPosPathToTarget.x = 0;
							NewWhiteCell->whiteCell->vPosPathToTarget.y = 0;
							NewWhiteCell->whiteCell->iPosPathToTarget = 0;
							NewWhiteCell->whiteCell->isSearchingForPathToFollow = sfTrue;
							NewWhiteCell->whiteCell->PathToFollow = 0;

							NewWhiteCell->whiteCell->Hp = 1;
							
							CurrentTower->Tower->isFirstBuild = sfFalse;
							CurrentTowerSlot = ListTowerSlot->FirstElement;
							while (CurrentTowerSlot != NULL)
							{
								if (CurrentTowerSlot->Id == CurrentTower->Tower->iSlotId)
								{
									NewWhiteCell->whiteCell->vPos = CurrentTowerSlot->TowerSlot->vSpawnPos;
									CurrentTower->Tower->iIsWhiteCellAlive = sfTrue;
									break;
								}
								CurrentTowerSlot = CurrentTowerSlot->NextElement;
							}
						}
						else if (!CurrentTower->Tower->iIsWhiteCellAlive && CurrentTower->Tower->tSinceSpawnWhiteCell > WHITE_CELL_CREATE_COOLDOWN
							&& !CurrentTower->Tower->isFirstBuild)
						{
							NewWhiteCell = AddElementBeginListWhiteCell(ListWhiteCell);
							NewWhiteCell->whiteCell = malloc(sizeof(t_whiteCell));
							NewWhiteCell->whiteCell->isWalking = sfFalse;
							NewWhiteCell->whiteCell->iTowerId = CurrentTower->Id;
							NewWhiteCell->whiteCell->tStartAnim = (float)clock() / CLOCKS_PER_SEC;
							NewWhiteCell->whiteCell->tSinceAnim = 0;
							NewWhiteCell->whiteCell->tCurrentAnim = 0;
							NewWhiteCell->whiteCell->animFrame = 0;
							NewWhiteCell->whiteCell->dirState = UP_LEFT;
							NewWhiteCell->whiteCell->sprite = Spr_whiteCell;
							NewWhiteCell->whiteCell->animRect.left = NewWhiteCell->whiteCell->animFrame * WHITE_CELL_WIDTH;
							NewWhiteCell->whiteCell->animRect.top = NewWhiteCell->whiteCell->dirState * WHITE_CELL_HEIGHT;
							NewWhiteCell->whiteCell->animRect.width = WHITE_CELL_WIDTH;
							NewWhiteCell->whiteCell->animRect.height = WHITE_CELL_HEIGHT;
							//sfSprite_setTextureRect(NewWhiteCell->whiteCell->sprite, NewWhiteCell->whiteCell->animRect);

							/*deplacment par point*/
							NewWhiteCell->whiteCell->vDirectionPosPathToTarget.x = 0;
							NewWhiteCell->whiteCell->vDirectionPosPathToTarget.y = 0;
							NewWhiteCell->whiteCell->vPosPathToTarget.x = 0;
							NewWhiteCell->whiteCell->vPosPathToTarget.y = 0;
							NewWhiteCell->whiteCell->iPosPathToTarget = 0;
							NewWhiteCell->whiteCell->isSearchingForPathToFollow = sfTrue;
							NewWhiteCell->whiteCell->PathToFollow = 0;

							NewWhiteCell->whiteCell->Hp = 1;

							CurrentTowerSlot = ListTowerSlot->FirstElement;
							while (CurrentTowerSlot != NULL)
							{
								if (CurrentTowerSlot->Id == CurrentTower->Tower->iSlotId)
								{
									NewWhiteCell->whiteCell->vPos = CurrentTowerSlot->TowerSlot->vSpawnPos;
									CurrentTower->Tower->iIsWhiteCellAlive = sfTrue;
									break;
								}
								CurrentTowerSlot = CurrentTowerSlot->NextElement;
							}
						}
					}
					CurrentTower = CurrentTower->NextElement;
				}

	#pragma endregion LECTURE TRAITEMENT SPAWN DES GLOBULES BLANCS //SEB

	#pragma region LECTURE DESTRUCTION ENNEMIS MORTS //SEB

				/*isSearchingForDead = sfTrue;

				while (isSearchingForDead)
				{*/
				CurrentEnnemy = ListEnnemy->FirstElement;
				while (CurrentEnnemy != NULL)
				{
					//asBreak = sfFalse;
					if (CurrentEnnemy->Ennemy->Hp <= 0 || CurrentEnnemy->Ennemy->vCurrentPosition.y > WINDOW_HEIGHT + 200)
					{
						if (CurrentEnnemy == ListEnnemy->FirstElement && CurrentEnnemy == ListEnnemy->LastElement)
						{
							printf("debug");
						}
						if (CurrentEnnemy->Ennemy->Hp != -200)
						{
							iPlayerMoney += CurrentEnnemy->Ennemy->iMoneyValue;
						}
						iWaveEnnemyDead++;
						DeleteEnemyWithID(ListEnnemy, CurrentEnnemy->Id);
						//DeleteElementById(ListEnnemy, CurrentEnnemy->Id);
						//asBreak = sfTrue;
						break;
					}
					else
					{
						CurrentEnnemy = CurrentEnnemy->NextElement;
					}
				}
				/*if (!asBreak)
				{
					isSearchingForDead = sfFalse;
				}*/

				//}

	#pragma endregion LECTURE DESTRUCTION ENNEMIS MORTS //SEB

	#pragma region LECTURE TRAITEMENT GLOBULES BLANCS //SEB

				CurrentWhiteCell = ListWhiteCell->FirstElement;
				while (CurrentWhiteCell != NULL)
				{
					CurrentWhiteCell->whiteCell->boundingBox.left = CurrentWhiteCell->whiteCell->vPos.x - 30;
					CurrentWhiteCell->whiteCell->boundingBox.top = CurrentWhiteCell->whiteCell->vPos.y - 130;
					CurrentWhiteCell->whiteCell->boundingBox.width = 45;
					CurrentWhiteCell->whiteCell->boundingBox.height = 146;
					/*GLOBULE BLANC NON-ACTIF*/
					if (!CurrentWhiteCell->whiteCell->isWalking)
					{

						asBreak = sfFalse;
						//printf_s("posX :%.2f,posY: %.2f\n", CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y);
						/*DETECTION DE L'ENNEMI*/
						CurrentEnnemy = ListEnnemy->FirstElement;
						while (CurrentEnnemy != NULL)
						{
							CurrentWhiteCell->whiteCell->distanceVector.x = CurrentEnnemy->Ennemy->vCurrentPosition.x - CurrentWhiteCell->whiteCell->vPos.x;
							CurrentWhiteCell->whiteCell->distanceVector.y = CurrentEnnemy->Ennemy->vCurrentPosition.y - CurrentWhiteCell->whiteCell->vPos.y;
							//printf_s("Cell x :%.2f, Cell y :%.2f, Ennemi X :%.2f, Ennemi Y :%.2f, Magnitude %.2f\n", CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y, CurrentEnnemy->Ennemy->vCurrentPosition.x, CurrentEnnemy->Ennemy->vCurrentPosition.y, Magnitude(CurrentWhiteCell->whiteCell->distanceVector));
							if (Magnitude(CurrentWhiteCell->whiteCell->distanceVector) < WHITE_CELL_FIELD_OF_VIEW_RADIUS)
							{
								CurrentWhiteCell->whiteCell->isWalking = sfTrue;
							}


							CurrentEnnemy = CurrentEnnemy->NextElement;
						}
					}
					/*GLOBULE BLANC ACTIF (& DANS LA FENETRE)*/
					else if (CurrentWhiteCell->whiteCell->isWalking 
						&& CurrentWhiteCell->whiteCell->vPos.x >= 0 && CurrentWhiteCell->whiteCell->vPos.x <= WINDOW_WIDTH
						&& CurrentWhiteCell->whiteCell->vPos.y >= 0 && CurrentWhiteCell->whiteCell->vPos.y <= WINDOW_HEIGHT)
					{
						CurrentEnnemy = ListEnnemy->FirstElement;
						while (CurrentEnnemy != NULL)
						{
							CurrentEnnemy->Ennemy->boundingBox.left = CurrentEnnemy->Ennemy->vCurrentPosition.x - CurrentEnnemy->Ennemy->vOrigin.x;
							CurrentEnnemy->Ennemy->boundingBox.top = CurrentEnnemy->Ennemy->vCurrentPosition.y - CurrentEnnemy->Ennemy->vOrigin.y;
							CurrentEnnemy->Ennemy->boundingBox.width = CurrentEnnemy->Ennemy->vOrigin.x * 2;
							CurrentEnnemy->Ennemy->boundingBox.height = CurrentEnnemy->Ennemy->vOrigin.y * 2;
							//printf_s("Wc BB ,L:%.2f,T:%.2f,W:%.2f,H:%.2f\nEn BB ,L:%.2f,T:%.2f,W:%.2f,H:%.2f\n", CurrentWhiteCell->whiteCell->boundingBox.left, CurrentWhiteCell->whiteCell->boundingBox.top, CurrentWhiteCell->whiteCell->boundingBox.width, CurrentWhiteCell->whiteCell->boundingBox.height,
							//CurrentEnnemy->Ennemy->boundingBox.left, CurrentEnnemy->Ennemy->boundingBox.top, CurrentEnnemy->Ennemy->boundingBox.width, CurrentEnnemy->Ennemy->boundingBox.height);
							if (sfFloatRect_intersects(&CurrentWhiteCell->whiteCell->boundingBox, &CurrentEnnemy->Ennemy->boundingBox, NULL) && CurrentWhiteCell->whiteCell->isWalking)
							{
								//printf_s("Delete !!!! !! \n");
								CurrentTower = ListTower->FirstElement;
								while (CurrentTower != NULL)
								{
									//printf_s("Id :%d,iTowerId:%d\n", CurrentTower->Id, CurrentWhiteCell->whiteCell->iTowerId);
									if (CurrentTower->Id == CurrentWhiteCell->whiteCell->iTowerId)
									{
										CurrentTower->Tower->iIsWhiteCellAlive = sfFalse;
										CurrentTower->Tower->tStartSpawnWhiteCell = (float)clock() / CLOCKS_PER_SEC;
										break;
									}
									CurrentTower = CurrentTower->NextElement;
								}
								CurrentEnnemy2 = ListEnnemy->FirstElement;
								while (CurrentEnnemy2 != NULL)
								{
									CurrentWhiteCell->whiteCell->distanceVector.x = CurrentEnnemy2->Ennemy->vCurrentPosition.x - CurrentWhiteCell->whiteCell->vPos.x;
									CurrentWhiteCell->whiteCell->distanceVector.y = CurrentEnnemy2->Ennemy->vCurrentPosition.y - CurrentWhiteCell->whiteCell->vPos.y;
									if (Magnitude(CurrentWhiteCell->whiteCell->distanceVector) < WHITE_CELL_AREA_DAMAGE_RADIUS)
									{
										CurrentEnnemy2->Ennemy->Hp -= TOWER3_DAMAGES;
									}

									CurrentEnnemy2 = CurrentEnnemy2->NextElement;
								}
								DeleteElementByIdWhiteCell(ListWhiteCell, CurrentWhiteCell->Id);
								asBreak = sfTrue;
								break;
							}
							CurrentEnnemy = CurrentEnnemy->NextElement;
						}
						if (asBreak)
						{
							asBreak = sfFalse;
							break;
						}

						/*ORIENTATION DU SPRITE PAR RAPPORT A LA COULEUR DU MASQUE DE COLLISION*/

		#pragma region ORIENTATION GLOBULE BLANC COULEUR

						/*BAS GAUCHE*/
						if (sfImage_getPixel(Image_MaskMapTest, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).b == 255)
						{
							CurrentWhiteCell->whiteCell->dirState = UP_RIGHT; // INVERSE
						}
						/*BAS DROITE*/
						else if (sfImage_getPixel(Image_MaskMapTest, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).g == 255)
						{
							CurrentWhiteCell->whiteCell->dirState = UP_LEFT; // INVERSE
						}
						/*HAUT GAUCHE*/
						else if (sfImage_getPixel(Image_MaskMapTest, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).r == 150
							&& sfImage_getPixel(Image_MaskMapTest, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).g == 150)
						{
							CurrentWhiteCell->whiteCell->dirState = DOWN_RIGHT; // INVERSE
							
						}
						/*HAUT DROITE*/
						else if (sfImage_getPixel(Image_MaskMapTest, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).g == 150
							&& sfImage_getPixel(Image_MaskMapTest, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).b == 150)
						{
							CurrentWhiteCell->whiteCell->dirState = DOWN_LEFT; // INVERSE
						}

		#pragma endregion ORIENTATION GLOBULE BLANC COULEUR

						/*DEPLACEMENT GLOBULE BLANC*/


						/*METHODE PAR POINT*/

		#pragma region DEPLACEMENT PAR POINT

						/*Pour le globule blanc la lecture de liste se fait dans le sens inverse car il prend le chemin inverse des ennemis*/

						/*CHERCHE LE CHEMIN LE PLUS PROCHE DE LA CELLULE SI ELLE N'EN POSSEDE PAS*/
						if (CurrentWhiteCell->whiteCell->isSearchingForPathToFollow == sfTrue)
						{
							/*JE CHECK LE POINT LE PLUS PROCHE DU GLOBULE QUAND IL EST POSEE*/
							for (int i = 0; i < CurrentLevelAssets.iNbrEnnemyPath; i++)
							{
								/*CHECK LIST*/
								CurrentEnnemyPathPoint = CurrentLevelAssets.TabListEnnemyPathPoint[i]->FirstElement;
								while (CurrentEnnemyPathPoint != NULL)
								{
									/*calcule avec la magnitude du point le plus proche dans la liste*/
									CurrentWhiteCell->whiteCell->vPosPathToTarget.x = CurrentEnnemyPathPoint->EnnemyPathPoint->vPos.x;
									CurrentWhiteCell->whiteCell->vPosPathToTarget.y = CurrentEnnemyPathPoint->EnnemyPathPoint->vPos.y;
									CurrentWhiteCell->whiteCell->vDirectionPosPathToTarget.x = CurrentWhiteCell->whiteCell->vPosPathToTarget.x - CurrentWhiteCell->whiteCell->vPos.x;
									CurrentWhiteCell->whiteCell->vDirectionPosPathToTarget.y = CurrentWhiteCell->whiteCell->vPosPathToTarget.y - CurrentWhiteCell->whiteCell->vPos.y;
									/*DETECTION DU POINT LE PLUS PROCHE*/
									if (Magnitude(CurrentWhiteCell->whiteCell->vDirectionPosPathToTarget) < 150)
									{
										/*le globule blanc suit le chemin correspondant*/
										CurrentWhiteCell->whiteCell->iPosPathToTarget = CurrentEnnemyPathPoint->EnnemyPathPoint->Num;
										CurrentWhiteCell->whiteCell->PathToFollow = i;
										CurrentWhiteCell->whiteCell->isSearchingForPathToFollow = sfFalse;
									}
									CurrentEnnemyPathPoint = CurrentEnnemyPathPoint->NextElement;
								}
							}
						}
						else if (CurrentWhiteCell->whiteCell->isSearchingForPathToFollow == sfFalse)
						{
							/*JE CHECK LE POINT LE PLUS PROCHE DU GLOBULE QUAND IL EST POSEE*/
							CurrentEnnemyPathPoint = CurrentLevelAssets.TabListEnnemyPathPoint[CurrentWhiteCell->whiteCell->PathToFollow]->FirstElement;
							while (CurrentEnnemyPathPoint != NULL)
							{
								/*LE GLOBULE BLANC SE DIRIGE VERS LE POINT LE POINT QU'IL VISE*/
								if (CurrentEnnemyPathPoint->EnnemyPathPoint->Num == CurrentWhiteCell->whiteCell->iPosPathToTarget)
								{
									CurrentWhiteCell->whiteCell->vPosPathToTarget.x = CurrentEnnemyPathPoint->EnnemyPathPoint->vPos.x;
									CurrentWhiteCell->whiteCell->vPosPathToTarget.y = CurrentEnnemyPathPoint->EnnemyPathPoint->vPos.y;
									CurrentWhiteCell->whiteCell->vDirectionPosPathToTarget.x = CurrentWhiteCell->whiteCell->vPosPathToTarget.x - CurrentWhiteCell->whiteCell->vPos.x;
									CurrentWhiteCell->whiteCell->vDirectionPosPathToTarget.y = CurrentWhiteCell->whiteCell->vPosPathToTarget.y - CurrentWhiteCell->whiteCell->vPos.y;

									CurrentWhiteCell->whiteCell->vPos.x += Normalize(CurrentWhiteCell->whiteCell->vDirectionPosPathToTarget).x * WHITE_CELL_SPD_FACTOR;
									CurrentWhiteCell->whiteCell->vPos.y += Normalize(CurrentWhiteCell->whiteCell->vDirectionPosPathToTarget).y * WHITE_CELL_SPD_FACTOR;
								}
								/*si il y a magnitude avec le point je change de cible*/
								if (Magnitude(CurrentWhiteCell->whiteCell->vDirectionPosPathToTarget) < 50)
								{
									if (CurrentEnnemyPathPoint->NextElement != NULL)
									{
										CurrentWhiteCell->whiteCell->iPosPathToTarget = CurrentEnnemyPathPoint->NextElement->EnnemyPathPoint->Num;
									}
									else
									{
										/*delete*/
										CurrentWhiteCell->whiteCell->Hp = 0;
									}
								}
								CurrentEnnemyPathPoint = CurrentEnnemyPathPoint->NextElement;
							}
						}

		#pragma endregion DEPLACEMENT PAR POINT

						/*METHODE COULEUR*/

		#pragma region DEPLACMENT PAR COULEUR (TEST)
						
						///*BAS GAUCHE*/
						//if (sfImage_getPixel(Image_MaskMapTest, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).b == 255)
						//{
						//	//printf_s("Bas Gauche\n");
						//	CurrentWhiteCell->whiteCell->dirState = UP_RIGHT; // INVERSE
						//	CurrentWhiteCell->whiteCell->vDir = GetDirectionFromAngleDegrees(150 + 3);
						//	CurrentWhiteCell->whiteCell->vDir = normalizeVector(CurrentWhiteCell->whiteCell->vDir);
						//	CurrentWhiteCell->whiteCell->vPos.x += CurrentWhiteCell->whiteCell->vDir.x * WHITE_CELL_SPD_FACTOR;
						//	CurrentWhiteCell->whiteCell->vPos.y += CurrentWhiteCell->whiteCell->vDir.y * WHITE_CELL_SPD_FACTOR;
						//}
						///*BAS DROITE*/
						//else if (sfImage_getPixel(Image_MaskMapTest, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).g == 255)
						//{
						//	//printf_s("Bas Droite\n");
						//	CurrentWhiteCell->whiteCell->dirState = UP_LEFT; // INVERSE
						//	CurrentWhiteCell->whiteCell->vDir = GetDirectionFromAngleDegrees(30 - 3);
						//	CurrentWhiteCell->whiteCell->vDir = normalizeVector(CurrentWhiteCell->whiteCell->vDir);
						//	CurrentWhiteCell->whiteCell->vPos.x += CurrentWhiteCell->whiteCell->vDir.x * WHITE_CELL_SPD_FACTOR;
						//	CurrentWhiteCell->whiteCell->vPos.y += CurrentWhiteCell->whiteCell->vDir.y * WHITE_CELL_SPD_FACTOR;
						//}
						///*HAUT GAUCHE*/
						//else if (sfImage_getPixel(Image_MaskMapTest, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).r == 150
						//	&& sfImage_getPixel(Image_MaskMapTest, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).g == 150)
						//{
						//	//printf_s("Haut Gauche\n");
						//	CurrentWhiteCell->whiteCell->dirState = DOWN_RIGHT; // INVERSE
						//	CurrentWhiteCell->whiteCell->vDir = GetDirectionFromAngleDegrees(210 - 3);
						//	CurrentWhiteCell->whiteCell->vDir = normalizeVector(CurrentWhiteCell->whiteCell->vDir);
						//	CurrentWhiteCell->whiteCell->vPos.x += CurrentWhiteCell->whiteCell->vDir.x * WHITE_CELL_SPD_FACTOR;
						//	CurrentWhiteCell->whiteCell->vPos.y += CurrentWhiteCell->whiteCell->vDir.y * WHITE_CELL_SPD_FACTOR;
						//}
						///*HAUT DROITE*/
						//else if (sfImage_getPixel(Image_MaskMapTest, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).g == 150
						//	&& sfImage_getPixel(Image_MaskMapTest, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).b == 150)
						//{
						//	//printf_s("Haut Doite\n");
						//	CurrentWhiteCell->whiteCell->dirState = DOWN_LEFT; // INVERSE
						//	CurrentWhiteCell->whiteCell->vDir = GetDirectionFromAngleDegrees(330 + 3);
						//	CurrentWhiteCell->whiteCell->vDir = normalizeVector(CurrentWhiteCell->whiteCell->vDir);
						//	CurrentWhiteCell->whiteCell->vPos.x += CurrentWhiteCell->whiteCell->vDir.x * WHITE_CELL_SPD_FACTOR;
						//	CurrentWhiteCell->whiteCell->vPos.y += CurrentWhiteCell->whiteCell->vDir.y * WHITE_CELL_SPD_FACTOR;
						//}
						//else if (sfImage_getPixel(Image_MaskMapTest, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).r == 255 && sfImage_getPixel(Image_MaskMapTest, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).g == 255
						//	&& sfImage_getPixel(Image_MaskMapTest, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).b == 255)
						//{
						//	//printf_s("Random dir\n");
						//}
						//else
						//{
						//	CurrentWhiteCell->whiteCell->vPos.x += CurrentWhiteCell->whiteCell->vDir.x * WHITE_CELL_SPD_FACTOR;
						//	CurrentWhiteCell->whiteCell->vPos.y += CurrentWhiteCell->whiteCell->vDir.y * WHITE_CELL_SPD_FACTOR;
						//	//printf_s("Not In\n");
						//}

		#pragma endregion DEPLACMENT PAR COULEUR (TEST)

						/*ANIMATION GLOBULE BLANC*/

		#pragma region ANIMATION GLOBULE BLANC

						CurrentWhiteCell->whiteCell->tCurrentAnim = (float)clock() / CLOCKS_PER_SEC;
						CurrentWhiteCell->whiteCell->tSinceAnim = CurrentWhiteCell->whiteCell->tCurrentAnim - CurrentWhiteCell->whiteCell->tStartAnim;

						if (CurrentWhiteCell->whiteCell->tSinceAnim > WHITE_CELL_ANIM_SPEED)
						{
							CurrentWhiteCell->whiteCell->tStartAnim = CurrentWhiteCell->whiteCell->tCurrentAnim;

							if (CurrentWhiteCell->whiteCell->animFrame < WHITE_CELL_FRAMES - 1)
							{
								CurrentWhiteCell->whiteCell->animFrame++;
							}
							else
							{
								CurrentWhiteCell->whiteCell->animFrame = 0;
							}

						}

		#pragma endregion ANIMATION GLOBULE BLANC


					}
					else
					{
						CurrentTower = ListTower->FirstElement;
						while (CurrentTower != NULL)
						{
							if (CurrentTower->Id == CurrentWhiteCell->whiteCell->iTowerId)
							{
								CurrentTower->Tower->iIsWhiteCellAlive = sfFalse;
								CurrentTower->Tower->tStartSpawnWhiteCell = (float)clock() / CLOCKS_PER_SEC;
								break;
							}
							CurrentTower = CurrentTower->NextElement;
						}
						DeleteElementByIdWhiteCell(ListWhiteCell, CurrentWhiteCell->Id);

						break;
					}



					CurrentWhiteCell = CurrentWhiteCell->NextElement;
				}

				/*LECTURE DELETE DES GLOBULES BLANCS*/

		#pragma region SUPPRESSION GLOBULE BLANCS AVEC LA VIE

				CurrentWhiteCell = ListWhiteCell->FirstElement;
				while (CurrentWhiteCell != NULL)
				{
					if (CurrentWhiteCell->whiteCell->Hp <= 0)
					{
						DeleteElementByIdWhiteCell(ListWhiteCell, CurrentWhiteCell->Id);
						break;
					}
					else
						CurrentWhiteCell = CurrentWhiteCell->NextElement;
				}

		#pragma endregion SUPPRESSION DES GLOBULES BLANCS AVEC LA VIE

	#pragma endregion LECTURE TRAITEMENT GLOBULES BLANCS //SEB

	#pragma region LECTURE AFFICHAGE DES GLOBULES BLANCS //SEB

				CurrentWhiteCell = ListWhiteCell->FirstElement;
				while (CurrentWhiteCell != NULL)
				{
					//CurrentWhiteCell->whiteCell->animRect.left = CurrentWhiteCell->whiteCell->animFrame * WHITE_CELL_WIDTH;
					CurrentWhiteCell->whiteCell->animRect.top = CurrentWhiteCell->whiteCell->dirState * WHITE_CELL_HEIGHT;
					sfSprite_setTextureRect(CurrentWhiteCell->whiteCell->sprite, CurrentWhiteCell->whiteCell->animRect);
					sfSprite_setPosition(CurrentWhiteCell->whiteCell->sprite, CurrentWhiteCell->whiteCell->vPos);
					sfRenderWindow_drawShape(window, CurrentWhiteCell->whiteCell->sprite, NULL);
					//sfCircleShape_setPosition(player, CurrentWhiteCell->whiteCell->vPos );
					//sfRenderWindow_drawCircleShape(window, player, NULL);
					CurrentWhiteCell = CurrentWhiteCell->NextElement;
				}

	#pragma endregion LECTURE AFFICHAGE DES GLOBULES BLANCS //SEB

	#pragma region LECTURE CONTROLE COLISION TOURS //SEB

				/*Lecture de liste tour pour le controle de colision champ de vision, et tir des tours*/


				CurrentEnnemy = ListEnnemy->FirstElement;
				while (CurrentEnnemy != NULL)
				{
					CurrentTower = ListTower->FirstElement;
					while (CurrentTower != NULL)
					{

						//printf_s("CurrentTower %d , bbL :%.2f, bbT :%.2f, bbW :%.2f, bbH :%.2f\n",CurrentTower->Id, CurrentTower->Tower->fieldBB.left, CurrentTower->Tower->fieldBB.top, CurrentTower->Tower->fieldBB.width, CurrentTower->Tower->fieldBB.height);
						if (sfFloatRect_contains(&CurrentTower->Tower->fieldBB, CurrentEnnemy->Ennemy->vCurrentPosition.x, CurrentEnnemy->Ennemy->vCurrentPosition.y))
						{
							vPlayerPointToCheck.x = (vOrigin_fieldOfView.x) - (CurrentTower->Tower->vPos.x - CurrentEnnemy->Ennemy->vCurrentPosition.x);
							vPlayerPointToCheck.y = (vOrigin_fieldOfView.y) - (CurrentTower->Tower->vPos.y - CurrentEnnemy->Ennemy->vCurrentPosition.y);
							if (sfImage_getPixel(Img_fieldMask, vPlayerPointToCheck.x, vPlayerPointToCheck.y).r == 255 && sfImage_getPixel(Img_fieldMask, vPlayerPointToCheck.x, vPlayerPointToCheck.y).g == 0
								&& sfImage_getPixel(Img_fieldMask, vPlayerPointToCheck.x, vPlayerPointToCheck.y).b == 0 && sfImage_getPixel(Img_fieldMask, vPlayerPointToCheck.x, vPlayerPointToCheck.y).a == 255)
							{
								switch (CurrentTower->Tower->TowerType)
								{
								case TYPE2:
									switch (CurrentEnnemy->Ennemy->Type)
									{
									case CANCER:
										if (CurrentTower->Id != 0)
										{
											//printf_s("Ralentissement cancer\n");
										}
										CurrentEnnemy->Ennemy->fSpeedMax = CANCER_SPEED * SLOWING_FACTOR;
										break;
									case CHOLESTEROL:
										if (CurrentTower->Id != 0)
										{
											//printf_s("Ralentissement cholesterol\n");
										}
										CurrentEnnemy->Ennemy->fSpeedMax = CHOLESTEROL_SPEED * SLOWING_FACTOR;
										break;
									case CAILLOT:
										if (CurrentTower->Id != 0)
										{
											//printf_s("Ralentissement caillot\n");
										}
										CurrentEnnemy->Ennemy->fSpeedMax = CAILLOT_SPEED * SLOWING_FACTOR;
										break;
									default:
										break;
									}
									CurrentEnnemy->Ennemy->tCurrentDOT = (float)clock() / CLOCKS_PER_SEC;
									CurrentEnnemy->Ennemy->tSinceDOT = CurrentEnnemy->Ennemy->tCurrentDOT - CurrentEnnemy->Ennemy->tStartDOT;
									if (CurrentEnnemy->Ennemy->tSinceDOT > DOT_FREQUENCY)
									{
										CurrentEnnemy->Ennemy->tStartDOT = CurrentEnnemy->Ennemy->tCurrentDOT;
										CurrentEnnemy->Ennemy->Hp -= TOWER2_DAMAGES;
									}

									break;
								case TYPE1:
									CurrentTower->Tower->tCurrentShoot = (float)clock() / CLOCKS_PER_SEC;
									CurrentTower->Tower->tSinceShoot = CurrentTower->Tower->tCurrentShoot - CurrentTower->Tower->tStartShoot;
									if (CurrentTower->Tower->tSinceShoot > 2 * CurrentTower->Tower->bulletSpeed)
									{
										//printf_s("Bullet !!!\n");
										CurrentTower->Tower->tStartShoot = CurrentTower->Tower->tCurrentShoot;
										NewTowerBullet = AddElementBeginListTowerBullet(ListTowerBullet);
										NewTowerBullet->TowerBullet = malloc(sizeof(t_TowerBullet));
										NewTowerBullet->TowerBullet->towerFromId = CurrentTower->Id;
										NewTowerBullet->TowerBullet->pos.x = CurrentTower->Tower->vPos.x;
										NewTowerBullet->TowerBullet->pos.y = CurrentTower->Tower->vPos.y - CurrentTower->Tower->boundingBox.height;
										NewTowerBullet->TowerBullet->dir.x = CurrentEnnemy->Ennemy->vCurrentPosition.x - NewTowerBullet->TowerBullet->pos.x;
										NewTowerBullet->TowerBullet->dir.y = CurrentEnnemy->Ennemy->vCurrentPosition.y - NewTowerBullet->TowerBullet->pos.y;
										NewTowerBullet->TowerBullet->dir = Normalize(NewTowerBullet->TowerBullet->dir);
										NewTowerBullet->TowerBullet->sprite = Sp_bullet3;
										NewTowerBullet->TowerBullet->bulletSpeed = 30;
									}
									break;
								default:
									break;
								}
								sfSprite_setColor(CurrentTower->Tower->fieldSpr, sfRed);
							}
							else
							{
								if (CurrentTower->Tower->TowerType == TYPE2)
								{
									//printf_s("OUT !!!!!\n");
									switch (CurrentEnnemy->Ennemy->Type)
									{
									case CANCER:
										CurrentEnnemy->Ennemy->fSpeedMax = CANCER_SPEED;
										break;
									case CHOLESTEROL:
										CurrentEnnemy->Ennemy->fSpeedMax = CHOLESTEROL_SPEED;
										break;
									case CAILLOT:
										CurrentEnnemy->Ennemy->fSpeedMax = CAILLOT_SPEED;
										break;
									default:
										break;
									}
								}
							}
						}
						else
						{
							//CurrentEnnemy->Ennemy->fSpeedFactor = 1.2;
							sfSprite_setColor(CurrentTower->Tower->fieldSpr, sfWhite);
						}
						CurrentTower = CurrentTower->NextElement;
					}


					CurrentEnnemy = CurrentEnnemy->NextElement;
				}



	#pragma endregion LECTURE CONTROLE COLISION TOURS //SEB

	#pragma region AFFICHAGE ENNEMY PATH POINT //GUILLAUME

				/*CurrentEnnemyPathPoint = ListEnnemyPathPoint1->FirstElement;
				while (CurrentEnnemyPathPoint != NULL)
				{
					sfSprite_setColor(Sp_EnnemyPathPoint, sfBlack);
					sfSprite_setPosition(Sp_EnnemyPathPoint, CurrentEnnemyPathPoint->EnnemyPathPoint->vPos);
					sfRenderWindow_drawSprite(window, Sp_EnnemyPathPoint, NULL);

					CurrentEnnemyPathPoint = CurrentEnnemyPathPoint->NextElement;
				}

				CurrentEnnemyPathPoint = ListEnnemyPathPoint2->FirstElement;
				while (CurrentEnnemyPathPoint != NULL)
				{
					sfSprite_setColor(Sp_EnnemyPathPoint, sfWhite);
					sfSprite_setPosition(Sp_EnnemyPathPoint, CurrentEnnemyPathPoint->EnnemyPathPoint->vPos);
					sfRenderWindow_drawSprite(window, Sp_EnnemyPathPoint, NULL);

					CurrentEnnemyPathPoint = CurrentEnnemyPathPoint->NextElement;
				}*/

	#pragma endregion AFFICHAGE ENNEMY PATH POINT //GUILLAUME

	#pragma region AFFICHAGE ENNEMY //GUILLAUME

				CurrentEnnemy = ListEnnemy->FirstElement;
				while (CurrentEnnemy != NULL)
				{
					/*AFFICHAGE ENNEMI*/
					sfSprite_setTextureRect(CurrentEnnemy->Ennemy->sp_Ennemy, CurrentEnnemy->Ennemy->animRect);
					sfSprite_setScale(CurrentEnnemy->Ennemy->sp_Ennemy, CurrentEnnemy->Ennemy->vScale);
					sfSprite_setPosition(CurrentEnnemy->Ennemy->sp_Ennemy, CurrentEnnemy->Ennemy->vCurrentPosition);
					sfSprite_setRotation(CurrentEnnemy->Ennemy->sp_Ennemy, CurrentEnnemy->Ennemy->fAngleSprite);
					sfRenderWindow_drawSprite(window, CurrentEnnemy->Ennemy->sp_Ennemy, NULL);

					/*AFFICHAGE BARRE DE VIE*/
					CurrentEnnemy->Ennemy->tCurrentLifeBarDisplay = (float)clock() / CLOCKS_PER_SEC;
					CurrentEnnemy->Ennemy->tSinceLifeBarDisplay = CurrentEnnemy->Ennemy->tCurrentLifeBarDisplay - CurrentEnnemy->Ennemy->tStartLifeBarDisplay;

					if (CurrentEnnemy->Ennemy->isHit && CurrentEnnemy->Ennemy->tSinceLifeBarDisplay < 2)
					{
						CurrentEnnemy->Ennemy->vPositionRectangleShapeBack.x = CurrentEnnemy->Ennemy->vCurrentPosition.x;
						CurrentEnnemy->Ennemy->vPositionRectangleShapeBack.y = CurrentEnnemy->Ennemy->vCurrentPosition.y - CurrentEnnemy->Ennemy->vOrigin.y;
						sfRectangleShape_setPosition(CurrentEnnemy->Ennemy->RectangleShapeBack, CurrentEnnemy->Ennemy->vPositionRectangleShapeBack);
						CurrentEnnemy->Ennemy->vPositionRectangleShape.x = CurrentEnnemy->Ennemy->vPositionRectangleShapeBack.x - CurrentEnnemy->Ennemy->vOriginRectangleShapeBack.x;
						CurrentEnnemy->Ennemy->vPositionRectangleShape.y = CurrentEnnemy->Ennemy->vPositionRectangleShapeBack.y - CurrentEnnemy->Ennemy->vOriginRectangleShapeBack.y;
						sfRectangleShape_setPosition(CurrentEnnemy->Ennemy->RectangleShape, CurrentEnnemy->Ennemy->vPositionRectangleShape);
						CurrentEnnemy->Ennemy->vSizeRectangleShape.x = (CurrentEnnemy->Ennemy->Hp / CurrentEnnemy->Ennemy->HpMax) * LIFEBAR_MAX_SIZE_X;
						if (CurrentEnnemy->Ennemy->vSizeRectangleShape.x <= 0)
						{
							CurrentEnnemy->Ennemy->vSizeRectangleShape.x = 0;
						}
						sfRectangleShape_setSize(CurrentEnnemy->Ennemy->RectangleShape, CurrentEnnemy->Ennemy->vSizeRectangleShape);
						sfRenderWindow_drawRectangleShape(window, CurrentEnnemy->Ennemy->RectangleShapeBack, NULL);
						sfRenderWindow_drawRectangleShape(window, CurrentEnnemy->Ennemy->RectangleShape, NULL);

					}
					else if (CurrentEnnemy->Ennemy->isHit && CurrentEnnemy->Ennemy->tSinceLifeBarDisplay > 2)
					{
						CurrentEnnemy->Ennemy->isHit = sfFalse;
					}

					/*AFFICHAGE DES VERTEX*/

	#pragma region AFFICHAGE DES VERTEX

					///*CONTROL POINT*/
					//SetLineBetweenPoints(VertexArray, Vertex, CurrentEnnemy->Ennemy->vCurrentPosition, CurrentEnnemy->Ennemy->vControlPoint, sfBlack);
					//sfRenderWindow_drawVertexArray(window, VertexArray, NULL);

					///*RIGHT POINT*/
					//SetLineBetweenPoints(VertexArray, Vertex, CurrentEnnemy->Ennemy->vRightStartPoint, CurrentEnnemy->Ennemy->vRightControlPoint, sfBlack);
					//sfRenderWindow_drawVertexArray(window, VertexArray, NULL);

					///*LEFT POINT*/
					//SetLineBetweenPoints(VertexArray, Vertex, CurrentEnnemy->Ennemy->vLeftStartPoint, CurrentEnnemy->Ennemy->vLeftControlPoint, sfBlack);
					//sfRenderWindow_drawVertexArray(window, VertexArray, NULL);

					///*SIDE RIGHT POINT*/
					//SetLineBetweenPoints(VertexArray, Vertex, CurrentEnnemy->Ennemy->vRightStartPoint, CurrentEnnemy->Ennemy->vSideRightControlPoint, sfBlack);
					//sfRenderWindow_drawVertexArray(window, VertexArray, NULL);

					///*SIDE LEFT POINT*/
					//SetLineBetweenPoints(VertexArray, Vertex, CurrentEnnemy->Ennemy->vLeftStartPoint, CurrentEnnemy->Ennemy->vSideLeftControlPoint, sfBlack);
					//sfRenderWindow_drawVertexArray(window, VertexArray, NULL);

					//////DRAW WANDER CIRCLE//////
					//circleDirection.x = CurrentEnnemy->Ennemy->vWanderCenter.x - CurrentEnnemy->Ennemy->vCurrentPosition.x;
					//circleDirection.y = CurrentEnnemy->Ennemy->vWanderCenter.y - CurrentEnnemy->Ennemy->vCurrentPosition.y;

					//sfCircleShape_setPosition(circleWander, CurrentEnnemy->Ennemy->vWanderCenter);
					//sfRenderWindow_drawCircleShape(window, circleWander, NULL);

					///*POUR LE WANDER*/
					//SetLineBetweenPoints(VertexArray, Vertex, CurrentEnnemy->Ennemy->vCurrentPosition, CurrentEnnemy->Ennemy->vWanderCenter, sfCyan);
					//sfRenderWindow_drawVertexArray(window, VertexArray, NULL);

					//VertexArray = GetLine(CurrentEnnemy->Ennemy->vWanderCenter, CurrentEnnemy->Ennemy->vWanderDirection, sfYellow);
					//sfRenderWindow_drawVertexArray(window, VertexArray, NULL);

					///*steering*/
					//VertexArray = GetLine(CurrentEnnemy->Ennemy->vCurrentPosition, CurrentEnnemy->Ennemy->vSteering, sfGreen);
					//sfRenderWindow_drawVertexArray(window, VertexArray, NULL);

					/*velocity*/
					/*VertexArray = GetLine(CurrentEnnemy->Ennemy->vRightStartPoint, CurrentEnnemy->Ennemy->vRightControlPoint, sfBlack);
					sfRenderWindow_drawVertexArray(window, VertexArray, NULL);*/

	#pragma endregion AFFICHAGE DES VERTEX

					CurrentEnnemy = CurrentEnnemy->NextElement;
				}

	#pragma endregion AFFICHAGE ENNEMY //GUILLAUME

	#pragma region AFFICHAGE TIRS ENNEMY //GUILLAUME

				CurrentEnnemyBullet = ListEnnemyBullet->FirstElement;
				while (CurrentEnnemyBullet != NULL)
				{
					sfSprite_setPosition(CurrentEnnemyBullet->EnnemyBullet->sprite, CurrentEnnemyBullet->EnnemyBullet->vPos);
					sfSprite_setRotation(CurrentEnnemyBullet->EnnemyBullet->sprite, CurrentEnnemyBullet->EnnemyBullet->fAngleSprite);
					sfRenderWindow_drawSprite(window, CurrentEnnemyBullet->EnnemyBullet->sprite, NULL);

					CurrentEnnemyBullet = CurrentEnnemyBullet->NextElement;
				}

	#pragma endregion AFFICHAGE TIRS ENNEMY //GUILLAUME

	#pragma region LECTURE AFFICHAGE DES TOURS //SEB

				/*Lecture de liste TOUR pour l'affichage*/

				CurrentTower = ListTower->FirstElement;

				while (CurrentTower != NULL)
				{

					sfSprite_setPosition(CurrentTower->Tower->sprite, CurrentTower->Tower->vPos);
					vMousePos = sfMouse_getPosition(window);
					vMousePosToFloat.x = (float)vMousePos.x;
					vMousePosToFloat.y = (float)vMousePos.y;

					if (sfFloatRect_contains(&CurrentTower->Tower->boundingBox, vMousePosToFloat.x, vMousePosToFloat.y) && !isBuildedChoice)
					{
						vMousePointToCheck.x = (sfSprite_getGlobalBounds(CurrentTower->Tower->sprite).width / 2) - (CurrentTower->Tower->vPos.x - vMousePosToFloat.x);
						vMousePointToCheck.y = (sfSprite_getGlobalBounds(CurrentTower->Tower->sprite).height - 15) - (CurrentTower->Tower->vPos.y - vMousePosToFloat.y);
						if (sfImage_getPixel(Img_TowerMask, vMousePointToCheck.x, vMousePointToCheck.y).r == 255 && sfImage_getPixel(Img_TowerMask, vMousePointToCheck.x, vMousePointToCheck.y).g == 0
							&& sfImage_getPixel(Img_TowerMask, vMousePointToCheck.x, vMousePointToCheck.y).b == 0 && sfImage_getPixel(Img_TowerMask, vMousePointToCheck.x, vMousePointToCheck.y).a == 255)
						{
							sfSprite_setColor(CurrentTower->Tower->sprite, sfGreen);
						}
					}
					else
					{
						sfSprite_setColor(CurrentTower->Tower->sprite, sfWhite);
					}
					CurrentTower->Tower->animRect.left = 0;
					CurrentTower->Tower->animRect.top = CurrentTower->Tower->TowerLevel * TOWER_HEIGHT;
					//sfSprite_setTextureRect(CurrentTower->Tower->sprite, CurrentTower->Tower->animRect);
					//if (btn1->isOver || btn2->isOver)
					//{
					//	printf_s("btn 1 ou 2\n");
					//	sfRenderWindow_drawSprite(window, CurrentTower->Tower->fieldSpr, NULL);
					//}
					/*if (CurrentTower->Tower->TowerType != TYPE3)
					{
					sfRenderWindow_drawSprite(window, CurrentTower->Tower->fieldSpr, NULL);
					}*/
					sfRenderWindow_drawSprite(window, CurrentTower->Tower->sprite, NULL);
					CurrentTower = CurrentTower->NextElement;

				}
	#pragma endregion LECTURE AFFICHAGE DES TOURS //SEB

	#pragma region GESTION MENU CONSTRUCTION //SEB

				/*ANIMATION OUVERTURE MENU CONSTRUCTION*/

		#pragma region ANIMATION OUVERTURE MENU CONSTRUCTION
				if (isInBuildChoice && !isOpened)
				{
					vDistanceBetween.x = btn1->vPos.x - ActualTowerSlot->TowerSlot->vPos.x;
					vDistanceBetween.y = btn1->vPos.y - ActualTowerSlot->TowerSlot->vPos.y;
					if (Magnitude(vDistanceBetween) < BUILD_OPENING_RADIUS)
					{
						btn1->vPos.x += btn1->vDir.x * BUILD_SPEED_FACTOR * timeSinceLastFrame;
						btn1->vPos.y += btn1->vDir.y * BUILD_SPEED_FACTOR * timeSinceLastFrame;
						sfSprite_setPosition(btn1->sprite, btn1->vPos);
					}
					vDistanceBetween.x = btn2->vPos.x - ActualTowerSlot->TowerSlot->vPos.x;
					vDistanceBetween.y = btn2->vPos.y - ActualTowerSlot->TowerSlot->vPos.y;
					if (Magnitude(vDistanceBetween) < BUILD_OPENING_RADIUS)
					{
						btn2->vPos.x += btn2->vDir.x * BUILD_SPEED_FACTOR * timeSinceLastFrame;
						btn2->vPos.y += btn2->vDir.y * BUILD_SPEED_FACTOR * timeSinceLastFrame;
						sfSprite_setPosition(btn2->sprite, btn2->vPos);
					}
					vDistanceBetween.x = btn3->vPos.x - ActualTowerSlot->TowerSlot->vPos.x;
					vDistanceBetween.y = btn3->vPos.y - ActualTowerSlot->TowerSlot->vPos.y;
					if (Magnitude(vDistanceBetween) < BUILD_OPENING_RADIUS)
					{
						btn3->vPos.x += btn3->vDir.x * BUILD_SPEED_FACTOR * timeSinceLastFrame;
						btn3->vPos.y += btn3->vDir.y * BUILD_SPEED_FACTOR * timeSinceLastFrame;
						sfSprite_setPosition(btn3->sprite, btn3->vPos);
					}

					if (vBtnScale.x < 1 && vBtnScale.y < 1)
					{
						vBtnScale.x += 1.34 * timeSinceLastFrame;
						vBtnScale.y += 1.34 * timeSinceLastFrame;
						sfSprite_setScale(btn1->sprite, vBtnScale);
						sfSprite_setScale(btn2->sprite, vBtnScale);
						sfSprite_setScale(btn3->sprite, vBtnScale);
					}
					else
					{
						isOpened = sfTrue;
					}

				}

		#pragma endregion ANIMATION OUVERTURE MENU CONSTRUCTION

				/*MENU CONSTRUCTION OUVERT*/

		#pragma region MENU CONSTRUCTION OUVERT

				if (isInBuildChoice)
				{
					if (isOpened)
					{
						vMousePos = sfMouse_getPosition(window);
						vMousePosToFloat.x = (float)vMousePos.x;
						vMousePosToFloat.y = (float)vMousePos.y;

						Rect_TowerSlotBtnBB.left = btn1->vPos.x - btn1->vOrigin.x;
						Rect_TowerSlotBtnBB.top = btn1->vPos.y - btn1->vOrigin.y;
						Rect_TowerSlotBtnBB.width = btn1->vOrigin.x * 2;
						Rect_TowerSlotBtnBB.height = btn1->vOrigin.y * 2;
						if (sfFloatRect_contains(&Rect_TowerSlotBtnBB, vMousePosToFloat.x, vMousePosToFloat.y) && TOWER1_COST < iPlayerMoney)
						{
							sfSprite_setPosition(Sp_fieldOfView, ActualTowerSlot->TowerSlot->vPos);
							sfRenderWindow_drawSprite(window, Sp_fieldOfView, NULL);

							sfSprite_setColor(btn1->sprite, sfYellow);
							btn1->isOver = sfTrue;
							if (sfMouse_isButtonPressed(sfMouseLeft) && !isMousePressed)
							{
								isMousePressed = sfTrue;
								iPlayerMoney -= TOWER1_COST;
								NewTower = AddElementBeginListTower(ListTower);
								NewTower->Tower = malloc(sizeof(t_Tower));
								ActualTowerSlot->TowerSlot->TowerBuildId = NewTower->Id;
								NewTower->Tower->vPos.x = ActualTowerSlot->TowerSlot->vPos.x;
								NewTower->Tower->vPos.y = ActualTowerSlot->TowerSlot->vPos.y;
								NewTower->Tower->TowerType = TYPE1;
								NewTower->Tower->upgradeCost = TOWER1_UPGRADE_COST;
								NewTower->Tower->cost = TOWER1_COST;
								NewTower->Tower->sprite = Sp_tower1;
								NewTower->Tower->TowerLevel = NORMAL;
								NewTower->Tower->animRect.left = 0;
								NewTower->Tower->animRect.top = NewTower->Tower->TowerLevel * TOWER1_HEIGHT;
								NewTower->Tower->animRect.width = TOWER1_WIDTH;
								NewTower->Tower->animRect.height = TOWER1_HEIGHT;
								NewTower->Tower->tStartShoot = (float)clock() / CLOCKS_PER_SEC;
								NewTower->Tower->tSinceShoot = 0;
								NewTower->Tower->tCurrentShoot = 0;
								NewTower->Tower->fieldSpr = createSprite("resources/textures/tower_field_of_view.png");
								NewTower->Tower->bulletSpeed = 0.5;
								NewTower->Tower->iSlotId = ActualTowerSlot->Id;
								NewTower->Tower->iHP = TOWER1_HP;
								NewTower->Tower->iHPMax = TOWER1_HP;
								//NewTower->Tower->iIsWhiteCellAlive = sfFalse;
								sfSprite_setOrigin(NewTower->Tower->fieldSpr, vOrigin_fieldOfView);
								sfSprite_setPosition(NewTower->Tower->fieldSpr, NewTower->Tower->vPos);
								NewTower->Tower->fieldBB = sfSprite_getGlobalBounds(NewTower->Tower->fieldSpr);
								sfSprite_setTextureRect(NewTower->Tower->sprite, NewTower->Tower->animRect);
								sfSprite_setPosition(NewTower->Tower->sprite, NewTower->Tower->vPos);
								NewTower->Tower->boundingBox = sfSprite_getGlobalBounds(NewTower->Tower->sprite);
								//NewTower->Tower->isOn = sfTrue;
								isOpened = sfFalse;
								isInBuildChoice = sfFalse;
								/*mettre en fonction*/
								vBtnScale.x = 0;
								vBtnScale.y = 0;
								sfSprite_setScale(btn1->sprite, vBtnScale);
								sfSprite_setScale(btn2->sprite, vBtnScale);
								sfSprite_setScale(btn3->sprite, vBtnScale);
								/**/
								ActualTowerSlot->TowerSlot->IsBuild = sfTrue;
								ActualTowerSlot->TowerSlot->BuildedType = NewTower->Tower->TowerType;
								sfSprite_setColor(btn1->sprite, sfWhite);
								if (ListTower->FirstElement->NextElement != NULL)
								{
									while (!SortTowerByPos(ListTower)) {}
								}
							}
							else if (!sfMouse_isButtonPressed(sfMouseLeft))
							{
								isMousePressed = sfFalse;
							}
						}
						else
						{
							sfSprite_setColor(btn1->sprite, sfWhite);
							btn1->isOver = sfFalse;
						}
						Rect_TowerSlotBtnBB.left = btn2->vPos.x - btn2->vOrigin.x;
						Rect_TowerSlotBtnBB.top = btn2->vPos.y - btn2->vOrigin.y;
						Rect_TowerSlotBtnBB.width = btn2->vOrigin.x * 2;
						Rect_TowerSlotBtnBB.height = btn2->vOrigin.y * 2;
						if (sfFloatRect_contains(&Rect_TowerSlotBtnBB, vMousePosToFloat.x, vMousePosToFloat.y) && TOWER2_COST < iPlayerMoney)
						{
							sfSprite_setPosition(Sp_fieldOfView, ActualTowerSlot->TowerSlot->vPos);
							sfRenderWindow_drawSprite(window, Sp_fieldOfView, NULL);
							sfSprite_setColor(btn2->sprite, sfYellow);
							btn2->isOver = sfTrue;
							if (sfMouse_isButtonPressed(sfMouseLeft) && !isMousePressed)
							{
								isMousePressed = sfTrue;
								iPlayerMoney -= TOWER2_COST;
								NewTower = AddElementBeginListTower(ListTower);
								NewTower->Tower = malloc(sizeof(t_Tower));
								ActualTowerSlot->TowerSlot->TowerBuildId = NewTower->Id;
								NewTower->Tower->vPos.x = ActualTowerSlot->TowerSlot->vPos.x;
								NewTower->Tower->vPos.y = ActualTowerSlot->TowerSlot->vPos.y;
								NewTower->Tower->TowerType = TYPE2;
								NewTower->Tower->upgradeCost = TOWER2_UPGRADE_COST;
								NewTower->Tower->cost = TOWER2_COST;
								NewTower->Tower->sprite = Sp_tower2;
								NewTower->Tower->TowerLevel = NORMAL;
								NewTower->Tower->animRect.left = 0;
								NewTower->Tower->animRect.top = NewTower->Tower->TowerLevel * TOWER2_HEIGHT;
								NewTower->Tower->animRect.width = TOWER2_WIDTH;
								NewTower->Tower->animRect.height = TOWER2_HEIGHT;
								//NewTower->Tower->tStartShoot = (float)clock() / CLOCKS_PER_SEC;
								//NewTower->Tower->tSinceShoot = 0;
								//NewTower->Tower->tCurrentShoot = 0;
								NewTower->Tower->iHP = TOWER2_HP;
								NewTower->Tower->iHPMax = TOWER2_HP;
								NewTower->Tower->iSlotId = ActualTowerSlot->Id;
								NewTower->Tower->fieldSpr = createSprite("resources/textures/tower_field_of_view.png");
								sfSprite_setOrigin(NewTower->Tower->fieldSpr, vOrigin_fieldOfView);
								sfSprite_setPosition(NewTower->Tower->fieldSpr, NewTower->Tower->vPos);
								NewTower->Tower->fieldBB = sfSprite_getGlobalBounds(NewTower->Tower->fieldSpr);
								sfSprite_setTextureRect(NewTower->Tower->sprite, NewTower->Tower->animRect);
								sfSprite_setPosition(NewTower->Tower->sprite, NewTower->Tower->vPos);
								NewTower->Tower->boundingBox = sfSprite_getGlobalBounds(NewTower->Tower->sprite);
								//NewTower->Tower->bulletSpeed = 0.7;
								//NewTower->Tower->isOn = sfTrue;
								isOpened = sfFalse;
								isInBuildChoice = sfFalse;
								/*mettre en fonction*/
								vBtnScale.x = 0;
								vBtnScale.y = 0;
								sfSprite_setScale(btn1->sprite, vBtnScale);
								sfSprite_setScale(btn2->sprite, vBtnScale);
								sfSprite_setScale(btn3->sprite, vBtnScale);
								/**/
								ActualTowerSlot->TowerSlot->IsBuild = sfTrue;
								ActualTowerSlot->TowerSlot->BuildedType = NewTower->Tower->TowerType;
								sfSprite_setColor(btn2->sprite, sfWhite);
								if (ListTower->FirstElement->NextElement != NULL)
								{
									while (!SortTowerByPos(ListTower)) {}
								}
							}
							else if (!sfMouse_isButtonPressed(sfMouseLeft))
							{
								isMousePressed = sfFalse;
							}
						}
						else
						{
							sfSprite_setColor(btn2->sprite, sfWhite);
							btn2->isOver = sfFalse;
						}
						Rect_TowerSlotBtnBB.left = btn3->vPos.x - btn3->vOrigin.x;
						Rect_TowerSlotBtnBB.top = btn3->vPos.y - btn3->vOrigin.y;
						Rect_TowerSlotBtnBB.width = btn3->vOrigin.x * 2;
						Rect_TowerSlotBtnBB.height = btn3->vOrigin.y * 2;
						if (sfFloatRect_contains(&Rect_TowerSlotBtnBB, vMousePosToFloat.x, vMousePosToFloat.y) && TOWER3_COST < iPlayerMoney)
						{
							sfSprite_setColor(btn3->sprite, sfYellow);
							btn3->isOver = sfTrue;
							if (sfMouse_isButtonPressed(sfMouseLeft) && !isMousePressed)
							{
								isMousePressed = sfTrue;
								iPlayerMoney -= TOWER3_COST;
								NewTower = AddElementBeginListTower(ListTower);
								NewTower->Tower = malloc(sizeof(t_Tower));
								NewTower->Tower->vPos.x = ActualTowerSlot->TowerSlot->vPos.x;
								NewTower->Tower->vPos.y = ActualTowerSlot->TowerSlot->vPos.y;
								NewTower->Tower->TowerType = TYPE3;
								NewTower->Tower->upgradeCost = TOWER3_UPGRADE_COST;
								NewTower->Tower->cost = TOWER3_COST;
								NewTower->Tower->sprite = Sp_tower3;
								NewTower->Tower->TowerLevel = NORMAL;
								NewTower->Tower->animRect.left = 0;
								NewTower->Tower->animRect.top = NewTower->Tower->TowerLevel * TOWER3_HEIGHT;
								NewTower->Tower->animRect.width = TOWER3_WIDTH;
								NewTower->Tower->animRect.height = TOWER3_HEIGHT;
								NewTower->Tower->tStartShoot = (float)clock() / CLOCKS_PER_SEC;
								NewTower->Tower->tSinceShoot = 0;
								NewTower->Tower->tCurrentShoot = 0;
								NewTower->Tower->iSlotId = ActualTowerSlot->Id;
								NewTower->Tower->iIsWhiteCellAlive = sfFalse;
								NewTower->Tower->iHP = TOWER3_HP;
								NewTower->Tower->iHPMax = TOWER3_HP;
								NewTower->Tower->fieldSpr = createSprite("resources/textures/tower_field_of_view.png");
								sfSprite_setOrigin(NewTower->Tower->fieldSpr, vOrigin_fieldOfView);
								sfSprite_setPosition(NewTower->Tower->fieldSpr, NewTower->Tower->vPos);
								NewTower->Tower->fieldBB = sfSprite_getGlobalBounds(NewTower->Tower->fieldSpr);
								sfSprite_setTextureRect(NewTower->Tower->sprite, NewTower->Tower->animRect);
								sfSprite_setPosition(NewTower->Tower->sprite, NewTower->Tower->vPos);
								NewTower->Tower->boundingBox = sfSprite_getGlobalBounds(NewTower->Tower->sprite);
								NewTower->Tower->bulletSpeed = 1;
								NewTower->Tower->isOn = sfFalse;
								NewTower->Tower->tStartSpawnWhiteCell = 0;
								NewTower->Tower->tCurrentSpawnWhiteCell = 0;
								NewTower->Tower->tSinceSpawnWhiteCell = 0;
								NewTower->Tower->isFirstBuild = sfTrue;
								isOpened = sfFalse;
								isInBuildChoice = sfFalse;
								/*mettre en fonction*/
								vBtnScale.x = 0;
								vBtnScale.y = 0;
								sfSprite_setScale(btn1->sprite, vBtnScale);
								sfSprite_setScale(btn2->sprite, vBtnScale);
								sfSprite_setScale(btn3->sprite, vBtnScale);
								/**/
								ActualTowerSlot->TowerSlot->IsBuild = sfTrue;
								ActualTowerSlot->TowerSlot->BuildedType = NewTower->Tower->TowerType;
								sfSprite_setColor(btn3->sprite, sfWhite);
								if (ListTower->FirstElement->NextElement != NULL)
								{
									while (!SortTowerByPos(ListTower)) {}
								}
							}
							else if (!sfMouse_isButtonPressed(sfMouseLeft))
							{
								isMousePressed = sfFalse;
							}
						}
						else
						{
							sfSprite_setColor(btn3->sprite, sfWhite);
							btn3->isOver = sfFalse;
						}
						if (sfMouse_isButtonPressed(sfMouseLeft) && !btn1->isOver
							&& !btn2->isOver && !btn3->isOver && !isMousePressed)
						{
							isMousePressed = sfTrue;
							isOpened = sfFalse;
							isInBuildChoice = sfFalse;
							/*mettre en fonction*/
							vBtnScale.x = 0;
							vBtnScale.y = 0;
							sfSprite_setScale(btn1->sprite, vBtnScale);
							sfSprite_setScale(btn2->sprite, vBtnScale);
							sfSprite_setScale(btn3->sprite, vBtnScale);
							/**/
						}
						else if (!sfMouse_isButtonPressed(sfMouseLeft))
						{
							isMousePressed = sfFalse;
						}
					}
					sfRenderWindow_drawSprite(window, btn1->sprite, NULL);
					sfRenderWindow_drawSprite(window, btn2->sprite, NULL);
					sfRenderWindow_drawSprite(window, btn3->sprite, NULL);

					if (btn1->isOver)
					{
						sfSprite_setPosition(Sp_Tower1_Panel, vMousePosToFloat);
						sfRenderWindow_drawSprite(window, Sp_Tower1_Panel, NULL);
					}
					else if (btn2->isOver)
					{
						sfSprite_setPosition(Sp_Tower2_Panel, vMousePosToFloat);
						sfRenderWindow_drawSprite(window, Sp_Tower2_Panel, NULL);
					}
					else if (btn3->isOver)
					{
						sfSprite_setPosition(Sp_Tower3_Panel, vMousePosToFloat);
						sfRenderWindow_drawSprite(window, Sp_Tower3_Panel, NULL);
					}
				}

		#pragma endregion MENU CONSTRUCTION OUVERT

	#pragma endregion GESTION MENU CONSTRUCTION //SEB
				
	#pragma region GESTION MENU UP/SELL //SEB

				/*animation menu up/sell*/
				if (isBuildedChoice && !isBuildedOpened)
				{

					vDistanceBetween.x = btnUpgrade->vPos.x - ActualTower->Tower->vPos.x;
					vDistanceBetween.y = btnUpgrade->vPos.y - ActualTower->Tower->vPos.y + 50;
					if (Magnitude(vDistanceBetween) < BUILD_OPENING_RADIUS)
					{
						btnUpgrade->vPos.x += btnUpgrade->vDir.x * BUILD_SPEED_FACTOR * timeSinceLastFrame;
						btnUpgrade->vPos.y += btnUpgrade->vDir.y * BUILD_SPEED_FACTOR * timeSinceLastFrame;
						sfSprite_setPosition(btnUpgrade->sprite, btnUpgrade->vPos);
					}
					vDistanceBetween.x = btnSell->vPos.x - ActualTower->Tower->vPos.x;
					vDistanceBetween.y = btnSell->vPos.y - ActualTower->Tower->vPos.y + 50;
					if (Magnitude(vDistanceBetween) < BUILD_OPENING_RADIUS)
					{
						btnSell->vPos.x += btnSell->vDir.x * BUILD_SPEED_FACTOR * timeSinceLastFrame;
						btnSell->vPos.y += btnSell->vDir.y * BUILD_SPEED_FACTOR * timeSinceLastFrame;
						sfSprite_setPosition(btnSell->sprite, btnSell->vPos);
					}
					if (vBtnScale2.x < 1 && vBtnScale2.y < 1)
					{
						vBtnScale2.x += 1.34 * timeSinceLastFrame;
						vBtnScale2.y += 1.34 * timeSinceLastFrame;
						sfSprite_setScale(btnSell->sprite, vBtnScale2);
						sfSprite_setScale(btnUpgrade->sprite, vBtnScale2);
					}
					else
					{
						isBuildedOpened = sfTrue;
					}
				}

				/*menu up/sell ouvert*/
				if (isBuildedChoice)
				{
					if (isBuildedOpened)
					{
						vMousePos = sfMouse_getPosition(window);
						vMousePosToFloat.x = (float)vMousePos.x;
						vMousePosToFloat.y = (float)vMousePos.y;

						Rect_TowerSlotBtnBB.left = btnSell->vPos.x - btnSell->vOrigin.x;
						Rect_TowerSlotBtnBB.top = btnSell->vPos.y - btnSell->vOrigin.y;
						Rect_TowerSlotBtnBB.width = btnSell->vOrigin.x * 2;
						Rect_TowerSlotBtnBB.height = btnSell->vOrigin.y * 2;
						if (sfFloatRect_contains(&Rect_TowerSlotBtnBB, vMousePosToFloat.x, vMousePosToFloat.y))
						{
							sfSprite_setColor(btnSell->sprite, sfYellow);
							btnSell->isOver = sfTrue;
							if (sfMouse_isButtonPressed(sfMouseLeft) && !isMousePressed)
							{
								if (ActualTower->Tower->TowerLevel == NORMAL)
								{
									iPlayerMoney += ActualTower->Tower->cost * RESELL_FACTOR;
								}
								else if (ActualTower->Tower->TowerLevel == UPGRADED)
								{
									iPlayerMoney += (ActualTower->Tower->cost + ActualTower->Tower->upgradeCost) * RESELL_FACTOR;
								}
								isMousePressed = sfTrue;
								vBtnScale2.x = 0;
								vBtnScale2.y = 0;
								sfSprite_setScale(btnSell->sprite, vBtnScale2);
								sfSprite_setScale(btnUpgrade->sprite, vBtnScale2);
								isBuildedChoice = sfFalse;
								isBuildedOpened = sfFalse;
								sfSprite_setColor(btnSell->sprite, sfWhite);
								CurrentTowerSlot = ListTowerSlot->FirstElement;
								while (CurrentTowerSlot != NULL)
								{
									if (CurrentTowerSlot->Id == ActualTower->Tower->iSlotId)
									{
										CurrentTowerSlot->TowerSlot->IsBuild = sfFalse;
										CurrentTowerSlot->TowerSlot->IsClicked = sfFalse;
										break;
									}
									//Rect_TowerSlotBB.left = CurrentTowerSlot->TowerSlot->vPos.x - vOrigin_TowerSlot.x;
									//Rect_TowerSlotBB.top = CurrentTowerSlot->TowerSlot->vPos.y - vOrigin_TowerSlot.y;
									//Rect_TowerSlotBB.width = vOrigin_TowerSlot.x * 2;
									//Rect_TowerSlotBB.height = vOrigin_TowerSlot.y * 2;
									//sfFloatRect test = sfSprite_getGlobalBounds(ActualTower->Tower->sprite);
									//if (sfFloatRect_intersects(&ActualTower->Tower->boundingBox, &Rect_TowerSlotBB, NULL))
									//{
									//	CurrentTowerSlot->TowerSlot->IsBuild = 0;
									//	CurrentTowerSlot->TowerSlot->IsClicked = 0;
									//	break;
									//}
									CurrentTowerSlot = CurrentTowerSlot->NextElement;
								}
								DeleteEntityWithID(ListTower, ActualTower->Id);
								//DeleteElementByIdTower(ListTower, ActualTower->Id);
								//printf_s("in delete !!!!!\n");
							}
							else if (!sfMouse_isButtonPressed(sfMouseLeft))
							{
								isMousePressed = sfFalse;
							}
						}
						else
						{
							sfSprite_setColor(btnSell->sprite, sfWhite);
							btnSell->isOver = sfFalse;
						}

						vMousePos = sfMouse_getPosition(window);
						vMousePosToFloat.x = (float)vMousePos.x;
						vMousePosToFloat.y = (float)vMousePos.y;

						Rect_TowerSlotBtnBB.left = btnUpgrade->vPos.x - btnUpgrade->vOrigin.x;
						Rect_TowerSlotBtnBB.top = btnUpgrade->vPos.y - btnUpgrade->vOrigin.y;
						Rect_TowerSlotBtnBB.width = btnUpgrade->vOrigin.x * 2;
						Rect_TowerSlotBtnBB.height = btnUpgrade->vOrigin.y * 2;
						if (sfFloatRect_contains(&Rect_TowerSlotBtnBB, vMousePosToFloat.x, vMousePosToFloat.y) && ActualTower->Tower->upgradeCost < iPlayerMoney)
						{
							sfSprite_setColor(btnUpgrade->sprite, sfYellow);
							btnUpgrade->isOver = sfTrue;
							if (sfMouse_isButtonPressed(sfMouseLeft) && !isMousePressed)
							{
								isMousePressed = sfTrue;
								vBtnScale2.x = 0;
								vBtnScale2.y = 0;
								sfSprite_setScale(btnSell->sprite, vBtnScale2);
								sfSprite_setScale(btnUpgrade->sprite, vBtnScale2);
								isBuildedChoice = sfFalse;
								isBuildedOpened = sfFalse;
								sfSprite_setColor(btnUpgrade->sprite, sfWhite);
								ActualTower->Tower->TowerLevel = UPGRADED;
								iPlayerMoney -= ActualTower->Tower->upgradeCost;

							}
							else if (!sfMouse_isButtonPressed(sfMouseLeft))
							{
								isMousePressed = sfFalse;
							}
						}
						else
						{
							sfSprite_setColor(btnUpgrade->sprite, sfWhite);
							btnUpgrade->isOver = sfFalse;
						}
						if (sfMouse_isButtonPressed(sfMouseLeft) && !btnUpgrade->isOver
							&& !btnSell->isOver && !isMousePressed)
						{
							isMousePressed = sfTrue;
							vBtnScale2.x = 0;
							vBtnScale2.y = 0;
							sfSprite_setScale(btnSell->sprite, vBtnScale2);
							sfSprite_setScale(btnUpgrade->sprite, vBtnScale2);
							isBuildedChoice = sfFalse;
							isBuildedOpened = sfFalse;
							sfSprite_setColor(btnSell->sprite, sfWhite);
						}
						else if (!sfMouse_isButtonPressed(sfMouseLeft))
						{
							isMousePressed = sfFalse;
						}
					}
					sfRenderWindow_drawSprite(window, btnUpgrade->sprite, NULL);
					sfRenderWindow_drawSprite(window, btnSell->sprite, NULL);
				}

	#pragma endregion GESTION MENU UP / SELL //SEB

#pragma region LECTURE TRAITEMENT TIRS //SEB

				CurrentTowerBullet = ListTowerBullet->FirstElement;
				asBreak = sfFalse;
				while (CurrentTowerBullet != NULL)
				{
					CurrentTowerBullet->TowerBullet->pos.x += CurrentTowerBullet->TowerBullet->dir.x * CurrentTowerBullet->TowerBullet->bulletSpeed;
					CurrentTowerBullet->TowerBullet->pos.y += CurrentTowerBullet->TowerBullet->dir.y * CurrentTowerBullet->TowerBullet->bulletSpeed;;
					sfSprite_setPosition(CurrentTowerBullet->TowerBullet->sprite, CurrentTowerBullet->TowerBullet->pos);
					Rect_playerBB = sfCircleShape_getGlobalBounds(player);
					CurrentTowerBullet->TowerBullet->boundingBox.left = CurrentTowerBullet->TowerBullet->pos.x - vOrigin_bullet.x;
					CurrentTowerBullet->TowerBullet->boundingBox.top = CurrentTowerBullet->TowerBullet->pos.y - vOrigin_bullet.y;
					CurrentTowerBullet->TowerBullet->boundingBox.width = vOrigin_bullet.x * 2;
					CurrentTowerBullet->TowerBullet->boundingBox.height = vOrigin_bullet.y * 2;
					CurrentEnnemy = ListEnnemy->FirstElement;
					while (CurrentEnnemy != NULL)
					{
						CurrentEnnemy->Ennemy->boundingBox.left = CurrentEnnemy->Ennemy->vCurrentPosition.x - CurrentEnnemy->Ennemy->vOrigin.x;
						CurrentEnnemy->Ennemy->boundingBox.top = CurrentEnnemy->Ennemy->vCurrentPosition.y - CurrentEnnemy->Ennemy->vOrigin.y;
						CurrentEnnemy->Ennemy->boundingBox.width = CurrentEnnemy->Ennemy->vOrigin.x * 2;
						CurrentEnnemy->Ennemy->boundingBox.height = CurrentEnnemy->Ennemy->vOrigin.y * 2;


						if (sfFloatRect_intersects(&CurrentEnnemy->Ennemy->boundingBox, &CurrentTowerBullet->TowerBullet->boundingBox, NULL))
						{
							CurrentEnnemy->Ennemy->Hp -= TOWER1_DAMAGES;
							CurrentEnnemy->Ennemy->isHit = sfTrue;
							CurrentEnnemy->Ennemy->tStartLifeBarDisplay = (float)clock() / CLOCKS_PER_SEC;
							CurrentEnnemy->Ennemy->tCurrentLifeBarDisplay = 0;
							CurrentEnnemy->Ennemy->tSinceLifeBarDisplay = 0;
							DeleteElementByIdBullet(ListTowerBullet, CurrentTowerBullet->Id);
							asBreak = sfTrue;
							break;
						}
						CurrentEnnemy = CurrentEnnemy->NextElement;
					}
					if (!asBreak)
					{
						CurrentTowerBullet = CurrentTowerBullet->NextElement;
					}
					else
					{
						break;
					}
				}

#pragma endregion LECTURE TRAITEMENT TIRS //SEB

	#pragma region LECTURE AFFICHAGE TIRS //SEB

				CurrentTowerBullet = ListTowerBullet->FirstElement;

				while (CurrentTowerBullet != NULL)
				{
					sfSprite_setPosition(CurrentTowerBullet->TowerBullet->sprite, CurrentTowerBullet->TowerBullet->pos);
					sfRenderWindow_drawSprite(window, CurrentTowerBullet->TowerBullet->sprite, NULL);
					CurrentTowerBullet = CurrentTowerBullet->NextElement;
				}

	#pragma endregion LECTURE AFFICHAGE TIRS //SEB

	#pragma region AFFICHAGE HUD //GUILLAUME

				/*affichage des sprites du hud*/
				sfRenderWindow_drawSprite(window, Hud.lifePoints.sprite, NULL);
				sfRenderWindow_drawSprite(window, Hud.money.sprite, NULL);
				//sfRenderWindow_drawSprite(window, Hud.waves.sprite, NULL);

				/*affichage pv objectif*/
				sfText_setCharacterSize(Text, 50);
				sfText_setFillColor(Text, sfBlue);
				sprintf_s(cText, 50, "%d", iGoalHp);
				sfText_setString(Text, cText);
				vPositionText.x = 182;
				vPositionText.y = 91 - 25;
				sfText_setPosition(Text, vPositionText);
				sfText_setOutlineColor(Text, sfWhite);
				sfText_setOutlineThickness(Text, 2);
				sfRenderWindow_drawText(window, Text, NULL);

				/*affichage numéro de vague*/
				sfText_setCharacterSize(Text, 30);
				sfText_setFillColor(Text, sfBlack);
				sprintf_s(cText, 50, "VAGUD : %d", iCurrentWave);
				sfText_setString(Text, cText);
				vPositionText.x = 26;
				vPositionText.y = 196;
				sfText_setPosition(Text, vPositionText);
				sfText_setOutlineColor(Text, sfWhite);
				sfText_setOutlineThickness(Text, 0.75);
				sfRenderWindow_drawText(window, Text, NULL);

				/*affichage nomber d'ennemis de la vague*/
				sfText_setCharacterSize(Text, 30);
				sfText_setFillColor(Text, sfBlack);
				sprintf_s(cText, 50, "DNNDMIS RDSTANTS %d / %d", (iNbrTotal - iWaveEnnemyDead), iNbrTotal);
				sfText_setString(Text, cText);
				vPositionText.x = 26;
				vPositionText.y = 230;
				sfText_setPosition(Text, vPositionText);
				sfText_setOutlineColor(Text, sfWhite);
				sfText_setOutlineThickness(Text, 0.75);
				sfRenderWindow_drawText(window, Text, NULL);

				/*affichage argent*/
				sfText_setCharacterSize(Text, 50);
				sfText_setFillColor(Text, sfBlue);
				sprintf_s(cText, 50, "%d", iPlayerMoney);
				sfText_setString(Text, cText);
				vPositionText.x = 1767 - sfText_getGlobalBounds(Text).width;
				vPositionText.y = 91 - 25;
				sfText_setPosition(Text, vPositionText);
				sfText_setOutlineColor(Text, sfWhite);
				sfText_setOutlineThickness(Text, 2);
				sfRenderWindow_drawText(window, Text, NULL);

	#pragma endregion AFFICHAGE HUD //GUILLAUME

	#pragma region AFFICHAGE MENU INGAME //SEB
				vMousePos = sfMouse_getPosition(window);

				inGameMenu.menuButtonBB = sfSprite_getGlobalBounds(inGameMenu.menuButton);


				if (sfFloatRect_contains(&inGameMenu.menuButtonBB, vMousePos.x, vMousePos.y) && inGameMenu.menuState == IS_CLOSED)
				{
					if (sfMouse_isButtonPressed(sfMouseLeft) && !isMousePressed)
					{
						isMousePressed = sfTrue;
						inGameMenu.menuState = IS_OPENING;
						sfSprite_setColor(inGameMenu.menuButton, sfWhite);
					}
					sfSprite_setColor(inGameMenu.menuButton, sfYellow);
				}
				else if (sfFloatRect_contains(&inGameMenu.menuButtonBB, vMousePos.x, vMousePos.y) && inGameMenu.menuState == IS_OPENED)
				{
					if (sfMouse_isButtonPressed(sfMouseLeft) && !isMousePressed)
					{
						isMousePressed = sfTrue;
						inGameMenu.menuState = IS_CLOSING;
						sfSprite_setColor(inGameMenu.menuButton, sfWhite);
					}
					sfSprite_setColor(inGameMenu.menuButton, sfYellow);
				}
				else
				{
					sfSprite_setColor(inGameMenu.menuButton, sfWhite);
				}

				if (inGameMenu.menuState == IS_OPENED)
				{
					if (sfFloatRect_contains(&inGameMenu.musicButtonBB, vMousePos.x, vMousePos.y))
					{
						sfSprite_setColor(inGameMenu.musicButton, sfYellow);
						inGameMenu.isOverMusic = sfTrue;
						if (sfMouse_isButtonPressed(sfMouseLeft) && !isMousePressed)
						{
							isMousePressed = sfTrue;
							if (inGameMenu.musicButtonFrame == IS_OFF)
							{
								inGameMenu.musicButtonFrame = IS_ON;
							}
							else
							{
								inGameMenu.musicButtonFrame = IS_OFF;
							}
							inGameMenu.rect_musicButton.left = inGameMenu.musicButtonFrame * BUTTON_SPRITE_SIZE;
							sfSprite_setTextureRect(inGameMenu.musicButton, inGameMenu.rect_musicButton);
						}
					}
					else
					{
						inGameMenu.isOverMusic = sfFalse;
						sfSprite_setColor(inGameMenu.musicButton, sfWhite);
					}
					if (sfFloatRect_contains(&inGameMenu.fxButtonBB, vMousePos.x, vMousePos.y))
					{
						sfSprite_setColor(inGameMenu.fxButton, sfYellow);
						inGameMenu.isOverFx = sfTrue;
						if (sfMouse_isButtonPressed(sfMouseLeft) && !isMousePressed)
						{
							isMousePressed = sfTrue;
							if (inGameMenu.fxButtonFrame == IS_OFF)
							{
								inGameMenu.fxButtonFrame = IS_ON;
							}
							else
							{
								inGameMenu.fxButtonFrame = IS_OFF;
							}
							inGameMenu.rect_fxButton.left = inGameMenu.fxButtonFrame * BUTTON_SPRITE_SIZE;
							sfSprite_setTextureRect(inGameMenu.fxButton, inGameMenu.rect_fxButton);
						}
					}
					else
					{
						inGameMenu.isOverFx = sfFalse;
						sfSprite_setColor(inGameMenu.fxButton, sfWhite);
					}
					if (sfFloatRect_contains(&inGameMenu.pauseButtonBB, vMousePos.x, vMousePos.y))
					{
						inGameMenu.isOverPause = sfTrue;
						sfSprite_setColor(inGameMenu.pauseButton, sfYellow);
					}
					else
					{
						inGameMenu.isOverPause = sfFalse;
						sfSprite_setColor(inGameMenu.pauseButton, sfWhite);
					}
				}



				if (inGameMenu.menuState == IS_OPENING || inGameMenu.menuState == IS_CLOSING)
				{
					manageInGameMenu(&inGameMenu);
				}


				if (!sfMouse_isButtonPressed(sfMouseLeft))
				{
					isMousePressed = sfFalse;
				}

				if (inGameMenu.menuState == IS_OPENED)
				{
					if (sfMouse_isButtonPressed(sfMouseLeft) && !isMousePressed && !inGameMenu.isOverFx && !inGameMenu.isOverMusic && !inGameMenu.isOverPause)
					{
						isMousePressed = sfTrue;
						inGameMenu.menuState = IS_CLOSING;
					}
				}
				if (inGameMenu.menuState != IS_CLOSED)
				{
					sfRenderWindow_drawSprite(window, inGameMenu.pauseButton, NULL);
					sfRenderWindow_drawSprite(window, inGameMenu.fxButton, NULL);
					sfRenderWindow_drawSprite(window, inGameMenu.musicButton, NULL);
				}
				sfRenderWindow_drawSprite(window, inGameMenu.menuButton, NULL);

	#pragma endregion AFFICHAGE MENU INGAME //SEB

	#pragma region VICTOIRE ET DEFAITE //GUILLAUME

				/*conditions de victoire*/
				if (iCurrentWave > iWaveMax)
				{
					GameState = VICTORY;
				}

				/*conditions de victoire*/
				if (iGoalHp <= 0)
				{
					GameState = DEFEAT;
				}

	#pragma endregion VICTOIRE ET DEFAITE //GUILLAUME

				////////////////////////////////////
				CurrentTower = ListTower->FirstElement;

	#pragma region AFFICHAGE SPAWN TOUR 3 //SEB

				CurrentTowerSlot = ListTowerSlot->FirstElement;
				while (CurrentTowerSlot != NULL)
				{
					if (btn3->isOver && ActualTowerSlot->Id == CurrentTowerSlot->Id && !ActualTowerSlot->TowerSlot->IsBuild && isOpened)
					{
						//printf_s("slot x : %.2f,y : %.2f\n", CurrentTowerSlot->TowerSlot->vSpawnPos.x, CurrentTowerSlot->TowerSlot->vSpawnPos.y);
						sfSprite_setPosition(spawnCross, CurrentTowerSlot->TowerSlot->vSpawnPos);
						sfRenderWindow_drawSprite(window, spawnCross, NULL);
					}
					CurrentTowerSlot = CurrentTowerSlot->NextElement;
				}

	#pragma endregion AFFICHAGE SPAWN TOUR 3 //SEB

	#pragma region TRI LIST ENNEMIS //SEB

				if (ListEnnemy->FirstElement != NULL && ListEnnemy->FirstElement->NextElement != NULL)
				{
					while (!SortEnnemyByPos(ListEnnemy)) {}
				}

	#pragma endregion TRI LIST ENNEMIS //SEB

			break;
#pragma endregion CASE GAME

#pragma region CASE VICTORY

		case VICTORY:

			/*AFFICHAGE FENETRE VICTOIRE*/
			sfRenderWindow_drawSprite(window, Sp_MenuVictoire, NULL);
			sfRenderWindow_drawSprite(window, Sp_BoutonRetour, NULL);

			/*sfText_setFillColor(Text, sfCyan);
			sprintf_s(cText, 50, "VICTOIRE");
			sfText_setString(Text, cText);
			vOriginText.x = sfText_getGlobalBounds(Text).width / 2;
			vOriginText.y = sfText_getGlobalBounds(Text).height / 2;
			sfText_setOrigin(Text, vOriginText);
			vPositionText.x = vWindowCenter.x;
			vPositionText.y = vWindowCenter.y;
			sfText_setPosition(Text, vPositionText);
			sfRenderWindow_drawText(window, Text, NULL);*/

			break;

#pragma endregion CASE VICTORY

#pragma region CASE DEFEAT

		case DEFEAT:

			/*AFFICHAGE FENETRE VICTOIRE*/
			sfRenderWindow_drawSprite(window, Sp_MenuDefaite, NULL);
			sfRenderWindow_drawSprite(window, Sp_BoutonRetour, NULL);

			/*sfText_setFillColor(Text, sfRed);
			sprintf_s(cText, 50, "DEFAITE");
			sfText_setString(Text, cText);
			vOriginText.x = sfText_getGlobalBounds(Text).width / 2;
			vOriginText.y = sfText_getGlobalBounds(Text).height / 2;
			sfText_setOrigin(Text, vOriginText);
			vPositionText.x = vWindowCenter.x;
			vPositionText.y = vWindowCenter.y;
			sfText_setPosition(Text, vPositionText);
			sfRenderWindow_drawText(window, Text, NULL);*/

			break;

#pragma endregion CASE DEFEAT

		default:
			break;
		}

		/* Update the window */
		sfRenderWindow_display(window);
	}
	/* Cleanup resources */
	sfRenderWindow_destroy(window);

	return 0;
}