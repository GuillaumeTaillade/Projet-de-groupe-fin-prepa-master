#include "header.h"

int main()
{
	/*initialisation du srand*/
	srand(time(NULL));

#pragma region LIST

	t_List* ListEnnemy = malloc(sizeof(t_List));
	ListEnnemy->FirstElement = NULL;
	ListEnnemy->LastElement = NULL;
	t_EnnemyElement* CurrentEnnemy = NULL;
	t_EnnemyElement* CurrentEnnemy2 = NULL;
	t_EnnemyElement* NewEnnemy = NULL;

	t_ListEnnemyBullet* ListEnnemyBullet = malloc(sizeof(t_ListEnnemyBullet));
	ListEnnemyBullet->FirstElement = NULL;
	ListEnnemyBullet->LastElement = NULL;
	t_EnnemyBulletElement* CurrentEnnemyBullet = NULL;
	t_EnnemyBulletElement* NewEnnemyBullet = NULL;

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
	int iGameState = PLAY; // état de jeu
	int iCurrentLevel = 2;
	int iDebug = 0;
	int iTowerId = 0;
	float fSpeedFactor = 1;

	#pragma endregion C VARS

	#pragma region CSFML VARS //SEB
	sfSprite* Sp_map = createSprite("resources/textures/map.jpg");
	sfSprite* Sp_TowerSlot = createSprite("resources/textures/Socle.png");
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
	sfSprite* Sp_tower1 = createSprite("resources/textures/tour1.png");
	sfSprite* Sp_tower2 = createSprite("resources/textures/tour2.png");
	sfSprite* Sp_tower3 = createSprite("resources/textures/tour3.png");
	sfSprite* Sp_towerActual = NULL;
	vOrigin_tower.x = TOWER_WIDTH / 2;
	vOrigin_tower.y = TOWER_HEIGHT - 15;
	sfSprite_setOrigin(Sp_tower1, vOrigin_tower);
	sfSprite_setOrigin(Sp_tower2, vOrigin_tower);
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
	sfSprite* Sp_bullet3 = createSprite("resources/textures/bullet3.png");
	sfVector2f vOrigin_bullet = { 10,10 };
	sfSprite_setOrigin(Sp_bullet1, vOrigin_bullet);
	sfSprite_setOrigin(Sp_bullet2, vOrigin_bullet);
	sfSprite_setOrigin(Sp_bullet3, vOrigin_bullet);
	sfSprite* spawnCross = createSprite("resources/textures/cross.png");
	sfVector2f vOrigin_spawnCross = { sfSprite_getGlobalBounds(spawnCross).width / 2, sfSprite_getGlobalBounds(spawnCross).height / 2 };
	sfSprite_setOrigin(spawnCross, vOrigin_spawnCross);
	sfSprite* Spr_whiteCell = createSprite("resources/textures/whiteCell.png");
	sfVector2f vOrigin_whiteCell = { 150,156 };
	sfSprite_setOrigin(Spr_whiteCell, vOrigin_whiteCell);


	#pragma endregion CSFML VARS //SEB

	#pragma region TIME VARIABLES

	int iFirstFrameIsPassed = 0; // permet de ne pas comptabiliser la première frame pour les timers
	float currentTime = 0; // Temps actuel depuis le début du programme
	float timeSinceLastFrame = 0; // Temps depuis la dernière frame
	float lastFrameTime = 0; // Temps de la dernière frame

	#pragma endregion TIME VARIABLES

#pragma endregion VARIABLES

#pragma region WINDOW

	sfVideoMode Mode = { WINDOW_WIDTH, WINDOW_HEIGHT, 32 };
	sfRenderWindow* window;
	sfEvent event;

	/* Create the main window */
	window = sfRenderWindow_create(Mode, "Tower Defense", sfResize | sfClose/*sfFullscreen*/, NULL);
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

	/*VIE OBJECTIF*/
	int iGoalHp = 100;

	/*GESTION VAGUES*/
	int iWaveMax = 1; // maximum de vagues pour la partie
	int iWave = 0; // Numéro de vague actuel
	int iWaveIsActive = 0; // actif quand une vague est en cours (reste des ennemis) non actif quand il n'y a pas de vague en cours (début de partie ou ennemis de la vague précédente au max)
	float fTimeSinceLastWave = TIME_BETWEEN_WAVE; // Temps depuis la dernière vague
	int iWaveEnnemyMaxNbr = 15; // Nombre d'ennemi max (20 pour la première puis évolue aprés chaque vagues)
	int iWaveEnnemyNbr = 0; // Nombre actuel d'ennemis apparus sur la map
	int iWaveEnnemyDead = 0; // Nombre d'ennemis morts dans la vague
	float fTimeSinceLastEnnemySpawn = 0; // Temps depuis le dernier ennemi apparut
	float fTimeBetweenEnnemySpawn = 0; // Temps entre ennemi (varie pour que l'apparition des ennemis soit variée)

									   /*View*/
	sfView* View = sfView_create();
	sfVector2f vSize_View = { WINDOW_WIDTH, WINDOW_HEIGHT };
	sfView_setSize(View, vSize_View);
	sfVector2f vPosition_View = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };

	/*text*/
	char* cText = malloc(50);
	sfText* Text = createText("resources/fonts/Fluo Gums.ttf");
	sfText_setCharacterSize(Text, SIZE_TEXT);
	sfText_setFillColor(Text, sfCyan);
	sfVector2f vPositionText = { 0, 0 };
	sfVector2f vOriginText = { 0, 0 };

#pragma region BOUTONS

	t_TowerCreationBtn* btn1 = malloc(sizeof(t_TowerCreationBtn));
	btn1->sprite = createSprite("resources/textures/tour1_btn.png");
	btn1->vOrigin.x = sfSprite_getGlobalBounds(btn1->sprite).width / 2;
	btn1->vOrigin.y = sfSprite_getGlobalBounds(btn1->sprite).height / 2;
	sfSprite_setOrigin(btn1->sprite, btn1->vOrigin);
	btn1->vDir.x = -0.5;
	btn1->vDir.y = -0.5;
	sfSprite_setScale(btn1->sprite, vBtnScale);
	btn1->isOver = sfFalse;

	t_TowerCreationBtn* btn2 = malloc(sizeof(t_TowerCreationBtn));
	btn2->sprite = createSprite("resources/textures/tour2_btn.png");
	btn2->vOrigin.x = sfSprite_getGlobalBounds(btn2->sprite).width / 2;
	btn2->vOrigin.y = sfSprite_getGlobalBounds(btn2->sprite).height / 2;
	sfSprite_setOrigin(btn2->sprite, btn2->vOrigin);
	btn2->vDir.x = 0;
	btn2->vDir.y = -0.7;
	sfSprite_setScale(btn2->sprite, vBtnScale);
	btn2->isOver = sfFalse;

	t_TowerCreationBtn* btn3 = malloc(sizeof(t_TowerCreationBtn));
	btn3->sprite = createSprite("resources/textures/tour3_btn.png");
	btn3->vOrigin.x = sfSprite_getGlobalBounds(btn3->sprite).width / 2;
	btn3->vOrigin.y = sfSprite_getGlobalBounds(btn3->sprite).height / 2;
	sfSprite_setOrigin(btn3->sprite, btn3->vOrigin);
	btn3->vDir.x = 0.5;
	btn3->vDir.y = -0.5;
	sfSprite_setScale(btn3->sprite, vBtnScale);
	btn3->isOver = sfFalse;

	t_TowerCreationBtn* btnUpgrade = malloc(sizeof(t_TowerCreationBtn));
	btnUpgrade->sprite = createSprite("resources/textures/upgrade_btn.png");
	btnUpgrade->vOrigin.x = sfSprite_getGlobalBounds(btnUpgrade->sprite).width / 2;
	btnUpgrade->vOrigin.y = sfSprite_getGlobalBounds(btnUpgrade->sprite).height / 2;
	sfSprite_setOrigin(btnUpgrade->sprite, btnUpgrade->vOrigin);
	btnUpgrade->vDir.x = -0.3;
	btnUpgrade->vDir.y = -0.7;
	sfSprite_setScale(btnUpgrade->sprite, vBtnScale2);
	btnUpgrade->isOver = sfFalse;

	t_TowerCreationBtn* btnSell = malloc(sizeof(t_TowerCreationBtn));
	btnSell->sprite = createSprite("resources/textures/sell_btn.png");
	btnSell->vOrigin.x = sfSprite_getGlobalBounds(btnSell->sprite).width / 2;
	btnSell->vOrigin.y = sfSprite_getGlobalBounds(btnSell->sprite).height / 2;
	sfSprite_setOrigin(btnSell->sprite, btnSell->vOrigin);
	btnSell->vDir.x = 0.3;
	btnSell->vDir.y = -0.7;
	sfSprite_setScale(btnSell->sprite, vBtnScale2);
	btnSell->isOver = sfFalse;

	
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
	sfSprite* Sp_Ennemy1 = createSprite("resources/textures/blue iso petit.png"); // CANCER
	sfSprite* Sp_Ennemy2 = createSprite("resources/textures/cho iso.png"); // CHOLESTEROL
	sfSprite* Sp_Ennemy3 = createSprite("resources/textures/roesd2.png"); // CAILLOT
	sfSprite* Sp_Map2 = createSprite("resources/textures/Level Test.jpg");
	sfSprite* Sp_MapMask2 = createSprite("resources/textures/Collision Mask Test.jpg");
	sfImage* Image_Map2 = sfImage_createFromFile("resources/textures/Collision Mask Test.psd");
#pragma endregion CREATE SPRITES

	sfColor Color_Blue = sfColor_fromRGB(0, 0, 255);
	sfColor Color_Green = sfColor_fromRGB(0, 255, 0);
	sfColor Color_Black_transp = { 0,0,0,150 };

#pragma region DEBUG

	sfVertexArray* VertexArray = sfVertexArray_create();
	sfVertex* Vertex = malloc(sizeof(Vertex));

#pragma endregion DEBUG

	/*charge les slots de tours depuis un fichier txt*/
	loadTowerSlots(ListTowerSlot, iCurrentLevel);
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
		/*Affiche la map*/
		sfRenderWindow_drawSprite(window, Sp_map, NULL);

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

		if (iGameState == PLAY)
		{

#pragma region ADD ENNEMY WAVES // GUILLAUME

			if (iWaveEnnemyDead >= iWaveEnnemyMaxNbr)
			{
				iWaveIsActive = sfFalse;
			}

			if (iWaveIsActive == 0)
			{
				fTimeSinceLastWave += timeSinceLastFrame;
				if (fTimeSinceLastWave > TIME_BETWEEN_WAVE)
				{
					iWaveIsActive = 1;
					fTimeSinceLastWave = 0;
					iWave++;
					iWaveEnnemyMaxNbr += 5;
					iWaveEnnemyNbr = 0;
					iWaveEnnemyDead = 0;
					fTimeBetweenEnnemySpawn = 1;
				}
			}

#pragma region ADD ENNEMY //GUILLAUME

			/*if (SpaceButtonIsButtonPressed == sfTrue && iSpaceButtonIsButtonPressedCheck == 0)*/
			if (iWaveIsActive == 1)
			{
				fTimeSinceLastEnnemySpawn += timeSinceLastFrame;
				if (fTimeSinceLastEnnemySpawn > fTimeBetweenEnnemySpawn)
				{
					fTimeSinceLastEnnemySpawn = 0;
					if (iWaveEnnemyNbr < iWaveEnnemyMaxNbr)
					{
						if (sfKeyboard_isKeyPressed(sfKeyD) == sfTrue)
						{
							printf("debug");
						}
						iWaveEnnemyNbr++;

						NewEnnemy = AddElementBeginList(ListEnnemy);
						NewEnnemy->Ennemy = malloc(sizeof(t_Ennemy));

						/*GESTION EN FONCTION DU TYPE*/

#pragma region GESTION EN FONCTION DU TYPE //GUILLAUME

						NewEnnemy->Ennemy->Type = rand() % 3 + 1;
						//printf("%d\n", NewEnnemy->Ennemy->Type);
						if (NewEnnemy->Ennemy->Type == CANCER)
						{
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
						}
						else if (NewEnnemy->Ennemy->Type == CAILLOT)
						{
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
						}
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
							//return EXIT_FAILURE;
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
							NewEnnemy->Ennemy->iDirection = 0;
							fscanf_s(file, "vPosX=%f,vPosY=%f,iDir=%d\n", &NewEnnemy->Ennemy->vSpawnPosition.x, &NewEnnemy->Ennemy->vSpawnPosition.y, &NewEnnemy->Ennemy->iDirection);
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

					/*cible de l'ennemi*/
						NewEnnemy->Ennemy->vTargetPostion.x = 1540;
						NewEnnemy->Ennemy->vTargetPostion.y = 40;

						/*SEEK*/
						NewEnnemy->Ennemy->vSeek.x = NewEnnemy->Ennemy->vTargetPostion.x - NewEnnemy->Ennemy->vCurrentPosition.x;
						NewEnnemy->Ennemy->vSeek.y = NewEnnemy->Ennemy->vTargetPostion.y - NewEnnemy->Ennemy->vCurrentPosition.y;

						/*QUAND J'AJOUTE L'ENNEMI IL EST ORIENTE VERS L'OBJECTIF*/
						NewEnnemy->Ennemy->fCurrentAngleDirection = GetAngleDegreeFromVector(NewEnnemy->Ennemy->vSeek);
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

#pragma endregion INITIALISATION PARAMETRES ENNEMIS

						/*BARRE DE VIE*/

#pragma region BARRE DE VIE ENNEMI//GUILLAUME

					/*rectangle de fond*/
						NewEnnemy->Ennemy->RectangleShapeBack = sfRectangleShape_create();
						sfRectangleShape_setFillColor(NewEnnemy->Ennemy->RectangleShapeBack, sfRed);
						NewEnnemy->Ennemy->vSizeRectangleShapeBack.x = SIZE_HP_X;
						NewEnnemy->Ennemy->vSizeRectangleShapeBack.y = SIZE_HP_Y;
						sfRectangleShape_setSize(NewEnnemy->Ennemy->RectangleShapeBack, NewEnnemy->Ennemy->vSizeRectangleShapeBack);
						NewEnnemy->Ennemy->vOriginRectangleShapeBack.x = sfRectangleShape_getGlobalBounds(NewEnnemy->Ennemy->RectangleShapeBack).width / 2;
						NewEnnemy->Ennemy->vOriginRectangleShapeBack.y = sfRectangleShape_getGlobalBounds(NewEnnemy->Ennemy->RectangleShapeBack).height / 2;
						sfRectangleShape_setOrigin(NewEnnemy->Ennemy->RectangleShapeBack, NewEnnemy->Ennemy->vOriginRectangleShapeBack);
						NewEnnemy->Ennemy->vPositionRectangleShapeBack.x = 0;
						NewEnnemy->Ennemy->vPositionRectangleShapeBack.y = 0;
						sfRectangleShape_setOutlineThickness(NewEnnemy->Ennemy->RectangleShapeBack, 1);
						sfRectangleShape_setOutlineColor(NewEnnemy->Ennemy->RectangleShapeBack, sfBlack);

						/*rectangle de vie*/
						NewEnnemy->Ennemy->RectangleShape = sfRectangleShape_create();
						sfRectangleShape_setFillColor(NewEnnemy->Ennemy->RectangleShape, sfGreen);
						NewEnnemy->Ennemy->vSizeRectangleShape.x = SIZE_HP_X;
						NewEnnemy->Ennemy->vSizeRectangleShape.y = SIZE_HP_Y;
						sfRectangleShape_setSize(NewEnnemy->Ennemy->RectangleShape, NewEnnemy->Ennemy->vSizeRectangleShape);
						NewEnnemy->Ennemy->vOriginRectangleShape.x = sfRectangleShape_getGlobalBounds(NewEnnemy->Ennemy->RectangleShape).width / 2;
						NewEnnemy->Ennemy->vOriginRectangleShape.y = sfRectangleShape_getGlobalBounds(NewEnnemy->Ennemy->RectangleShape).height / 2;
						sfRectangleShape_setOrigin(NewEnnemy->Ennemy->RectangleShape, NewEnnemy->Ennemy->vOriginRectangleShape);
						NewEnnemy->Ennemy->vPositionRectangleShape.x = 0;
						NewEnnemy->Ennemy->vPositionRectangleShape.y = 0;

#pragma endregion BARRE DE VIE ENNEMI //GUILLAUME

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

			CurrentEnnemy = ListEnnemy->FirstElement;
			while (CurrentEnnemy != NULL)
			{
				/*GESTION DE DIRECTION*/

#pragma region GESTION DIRECTION  //GUILLAUME

			/*J'OBTIENS LA COULEUR SITUE SOUS L'ENNEMI*/
				if (CurrentEnnemy->Ennemy->vCurrentPosition.x > 0 && CurrentEnnemy->Ennemy->vCurrentPosition.x < WINDOW_WIDTH
					&& CurrentEnnemy->Ennemy->vCurrentPosition.y > 0 && CurrentEnnemy->Ennemy->vCurrentPosition.y < WINDOW_HEIGHT)
				{
					CurrentEnnemy->Ennemy->Color_ToCheck = sfImage_getPixel(Image_Map2, CurrentEnnemy->Ennemy->vCurrentPosition.x, CurrentEnnemy->Ennemy->vCurrentPosition.y);
				}

				if (manageEnnemi(CurrentEnnemy, Image_Map2, timeSinceLastFrame) == sfFalse)
				{

#pragma region ANGLE EN FONCTION DE LA COULEUR //GUILLAUME

					/*COULEUR BLEU (HAUT-DROITE)*/
					if (CurrentEnnemy->Ennemy->Color_ToCheck.b == 255)
					{
						CurrentEnnemy->Ennemy->iDirection = UP_RIGHT;
					}
					/*COULEUR VERTE (HAUT-GAUCHE)*/
					if (CurrentEnnemy->Ennemy->Color_ToCheck.g == 255)
					{
						CurrentEnnemy->Ennemy->iDirection = UP_LEFT;
					}
					/*COULEUR JAUNE (BAS_DROITE)*/
					if (CurrentEnnemy->Ennemy->Color_ToCheck.r == 150 && CurrentEnnemy->Ennemy->Color_ToCheck.g == 150)
					{
						CurrentEnnemy->Ennemy->iDirection = DOWN_RIGHT;
					}
					/*COULEUR BLEU CLAIR (BAS_GAUCHE)*/
					if (CurrentEnnemy->Ennemy->Color_ToCheck.g == 150 && CurrentEnnemy->Ennemy->Color_ToCheck.b == 150)
					{
						CurrentEnnemy->Ennemy->iDirection = DOWN_LEFT;
					}
					/*COULEUR BLANCHE (DIRECTION ALEATOIRE)*/
					if (CurrentEnnemy->Ennemy->Color_ToCheck.g == 255 && CurrentEnnemy->Ennemy->Color_ToCheck.b == 255 && CurrentEnnemy->Ennemy->Color_ToCheck.r == 255)
					{
						if (CurrentEnnemy->Ennemy->iRandDirectionIsChosen == 0)
						{
							CurrentEnnemy->Ennemy->iRandDirection = rand() % 2 + 1;
							CurrentEnnemy->Ennemy->iRandDirectionIsChosen = 1;
						}
						if (CurrentEnnemy->Ennemy->iRandDirection == 1)
						{
							CurrentEnnemy->Ennemy->iDirection = UP_RIGHT;
						}
						else if (CurrentEnnemy->Ennemy->iRandDirection == 2)
						{
							CurrentEnnemy->Ennemy->iDirection = UP_LEFT;
						}
					}

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


#pragma endregion ANGLE EN FONCTION DE LA COULEUR //GUILLAUME

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
				else if (manageEnnemi(CurrentEnnemy, Image_Map2, timeSinceLastFrame) == sfTrue)
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
						if (sfImage_getPixel(Image_Map2, CurrentEnnemy->Ennemy->vSideLeftControlPoint.x, CurrentEnnemy->Ennemy->vSideLeftControlPoint.y).r == 255 && sfImage_getPixel(Image_Map2, CurrentEnnemy->Ennemy->vSideLeftControlPoint.x, CurrentEnnemy->Ennemy->vSideLeftControlPoint.y).g == 0
							&& sfImage_getPixel(Image_Map2, CurrentEnnemy->Ennemy->vSideLeftControlPoint.x, CurrentEnnemy->Ennemy->vSideLeftControlPoint.y).b == 0 && sfImage_getPixel(Image_Map2, CurrentEnnemy->Ennemy->vSideLeftControlPoint.x, CurrentEnnemy->Ennemy->vSideLeftControlPoint.y).a == 255)
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
						if (sfImage_getPixel(Image_Map2, CurrentEnnemy->Ennemy->vSideRightControlPoint.x, CurrentEnnemy->Ennemy->vSideRightControlPoint.y).r == 255 && sfImage_getPixel(Image_Map2, CurrentEnnemy->Ennemy->vSideRightControlPoint.x, CurrentEnnemy->Ennemy->vSideRightControlPoint.y).g == 0
							&& sfImage_getPixel(Image_Map2, CurrentEnnemy->Ennemy->vSideRightControlPoint.x, CurrentEnnemy->Ennemy->vSideRightControlPoint.y).b == 0 && sfImage_getPixel(Image_Map2, CurrentEnnemy->Ennemy->vSideRightControlPoint.x, CurrentEnnemy->Ennemy->vSideRightControlPoint.y).a == 255)
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


#pragma endregion GESTION DIRECTION //GUILLAUME

#pragma region DIRECTION ATTAQUE CAILLOT DE SANG

				if (CurrentEnnemy->Ennemy->Type == CAILLOT)
				{
					CurrentEnnemy->Ennemy->fTimeSinceLastAttack += timeSinceLastFrame;
					if (CurrentEnnemy->Ennemy->fTimeSinceLastAttack > 5)
					{
						/*je parcours la liste des tours pour repérer celle qui est le plus proche du caillot de sang*/
						CurrentTower = ListTower->FirstElement;
						while (CurrentTower != NULL)
						{

							if (sfFloatRect_contains(&CurrentTower->Tower->fieldBB, CurrentEnnemy->Ennemy->vCurrentPosition.x, CurrentEnnemy->Ennemy->vCurrentPosition.y))
							{

								if (CurrentEnnemy->Ennemy->iIsAttack == sfFalse)
								{
									CurrentEnnemy->Ennemy->iIsAttack = sfTrue;
									CurrentEnnemy->Ennemy->iTowerToAttackId = CurrentTower->Id;
								}
							}


							if (CurrentEnnemy->Ennemy->iIsAttack == sfTrue)
							{
								if (CurrentTower->Id == CurrentEnnemy->Ennemy->iTowerToAttackId)
								{
									CurrentEnnemy->Ennemy->vPosTowerToAttack.x = CurrentTower->Tower->vPos.x;
									CurrentEnnemy->Ennemy->vPosTowerToAttack.y = CurrentTower->Tower->vPos.y;
									CurrentEnnemy->Ennemy->vCurrentDirection.x = CurrentEnnemy->Ennemy->vPosTowerToAttack.x - CurrentEnnemy->Ennemy->vCurrentPosition.x;
									CurrentEnnemy->Ennemy->vCurrentDirection.y = CurrentEnnemy->Ennemy->vPosTowerToAttack.y - CurrentEnnemy->Ennemy->vCurrentPosition.y;
									CurrentEnnemy->Ennemy->fDesiredAngleDirection = GetAngleDegreeFromVector(CurrentEnnemy->Ennemy->vCurrentDirection);
									CurrentEnnemy->Ennemy->fCurrentAngleDirection = CurrentEnnemy->Ennemy->fDesiredAngleDirection;
									CurrentEnnemy->Ennemy->vCurrentDirection = GetDirectionFromAngleDegrees(CurrentEnnemy->Ennemy->fCurrentAngleDirection);
									if (SpriteIsOverPosition(CurrentEnnemy->Ennemy->vCurrentPosition, CurrentEnnemy->Ennemy->vOrigin, CurrentTower->Tower->vPos, CurrentEnnemy->Ennemy->vOrigin))
									{
										CurrentEnnemy->Ennemy->fTimeSinceLastAttack = 0;
										/*dégats sur la tour*/

										CurrentEnnemy->Ennemy->iIsAttack = sfFalse;
									}
								}
							}

							CurrentTower = CurrentTower->NextElement;
						}
					}
				}

#pragma endregion DIRECTION ATTAQUE CAILLOT DE SANG

#pragma region ATTAQUE CHOLESTEROL

				if (CurrentEnnemy->Ennemy->Type == CHOLESTEROL)
				{
					CurrentEnnemy->Ennemy->fTimeSinceLastAttack += timeSinceLastFrame;
					if (CurrentEnnemy->Ennemy->fTimeSinceLastAttack > 5)
					{
						/*je parcours la liste des tours pour repérer celle qui est le plus proche du caillot de sang*/
						CurrentTower = ListTower->FirstElement;
						while (CurrentTower != NULL)
						{
							if (sfFloatRect_contains(&CurrentTower->Tower->fieldBB, CurrentEnnemy->Ennemy->vCurrentPosition.x, CurrentEnnemy->Ennemy->vCurrentPosition.y))
							{
								if (CurrentEnnemy->Ennemy->iIsAttack == sfFalse)
								{
									CurrentEnnemy->Ennemy->iIsAttack = sfTrue;
									CurrentEnnemy->Ennemy->iTowerToAttackId = CurrentTower->Id;
								}
							}
							CurrentTower = CurrentTower->NextElement;

						}
					}
				}

#pragma endregion ATTAQUE CHOLESTEROL

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
				CurrentEnnemy->Ennemy->animRect.top = CurrentEnnemy->Ennemy->animRect.height * CurrentEnnemy->Ennemy->iDirection;
				

#pragma endregion ANIMATION

#pragma region CALCUL VIE ENNEMI

				/*RECTANGLE SHAPE BACK*/
				CurrentEnnemy->Ennemy->vPositionRectangleShapeBack.x = CurrentEnnemy->Ennemy->vCurrentPosition.x;
				CurrentEnnemy->Ennemy->vPositionRectangleShapeBack.y = CurrentEnnemy->Ennemy->vCurrentPosition.y - CurrentEnnemy->Ennemy->vOrigin.y;
				sfRectangleShape_setPosition(CurrentEnnemy->Ennemy->RectangleShapeBack, CurrentEnnemy->Ennemy->vPositionRectangleShapeBack);

				/*RECTANGLE SHAPE*/
				CurrentEnnemy->Ennemy->vSizeRectangleShape.x = SIZE_HP_X / (CurrentEnnemy->Ennemy->HpMax / CurrentEnnemy->Ennemy->Hp);
				CurrentEnnemy->Ennemy->vSizeRectangleShape.y = SIZE_HP_Y;
				sfRectangleShape_setSize(CurrentEnnemy->Ennemy->RectangleShape, CurrentEnnemy->Ennemy->vSizeRectangleShape);
				CurrentEnnemy->Ennemy->vOriginRectangleShape.x = sfRectangleShape_getGlobalBounds(CurrentEnnemy->Ennemy->RectangleShape).width / 2;
				CurrentEnnemy->Ennemy->vOriginRectangleShape.y = sfRectangleShape_getGlobalBounds(CurrentEnnemy->Ennemy->RectangleShape).height / 2;
				sfRectangleShape_setOrigin(CurrentEnnemy->Ennemy->RectangleShape, CurrentEnnemy->Ennemy->vOriginRectangleShape);
				CurrentEnnemy->Ennemy->vPositionRectangleShape.x = sfRectangleShape_getGlobalBounds(CurrentEnnemy->Ennemy->RectangleShapeBack).left + CurrentEnnemy->Ennemy->vOriginRectangleShape.x + sfRectangleShape_getOutlineThickness(CurrentEnnemy->Ennemy->RectangleShapeBack);
				CurrentEnnemy->Ennemy->vPositionRectangleShape.y = CurrentEnnemy->Ennemy->vPositionRectangleShapeBack.y;
				sfRectangleShape_setPosition(CurrentEnnemy->Ennemy->RectangleShape, CurrentEnnemy->Ennemy->vPositionRectangleShape);

#pragma endregion CALCUL VIE ENNEMI

#pragma region GESTION CHOLESTEROL

				if (CurrentEnnemy->Ennemy->Type == CHOLESTEROL)
				{
					if (CurrentEnnemy->Ennemy->Hp < (CurrentEnnemy->Ennemy->HpMax * 0.7))
					{
						CurrentEnnemy->Ennemy->iSize = MEDIUM;
						CurrentEnnemy->Ennemy->Deg = CHOLESTEROL_DEG * 0.7;
						CurrentEnnemy->Ennemy->fSpeedMax = CHOLESTEROL_SPEED * 1.5;
						CurrentEnnemy->Ennemy->vScale.x = 0.6;
						CurrentEnnemy->Ennemy->vScale.y = 0.6;

					}

					if (CurrentEnnemy->Ennemy->Hp < (CurrentEnnemy->Ennemy->HpMax * 0.3))
					{
						CurrentEnnemy->Ennemy->iSize = SMALL;
						CurrentEnnemy->Ennemy->Deg = CHOLESTEROL_DEG * 0.3;
						CurrentEnnemy->Ennemy->fSpeedMax = CHOLESTEROL_SPEED * 2;
						CurrentEnnemy->Ennemy->vScale.x = 0.3;
						CurrentEnnemy->Ennemy->vScale.y = 0.3;
					}
				}

#pragma endregion GESTION CHOLESTEROL

#pragma region PERTE DE PV OBJECTIF

				if (CurrentEnnemy->Ennemy->vCurrentPosition.x < CurrentEnnemy->Ennemy->vTargetPostion.x + 50
					&& CurrentEnnemy->Ennemy->vCurrentPosition.x > CurrentEnnemy->Ennemy->vTargetPostion.x - 50
					&& CurrentEnnemy->Ennemy->vCurrentPosition.y < CurrentEnnemy->Ennemy->vTargetPostion.y + 50
					&& CurrentEnnemy->Ennemy->vCurrentPosition.y > CurrentEnnemy->Ennemy->vTargetPostion.y - 50)
				{
					CurrentEnnemy->Ennemy->iDespawn = 1;
				}

				if (CurrentEnnemy->Ennemy->iDespawn == 1)
				{
					CurrentEnnemy->Ennemy->fTimeSinceStartDespawn += timeSinceLastFrame;
				}
				if (CurrentEnnemy->Ennemy->fTimeSinceStartDespawn > 1)
				{
					if (iGoalHp > 0)
					{
						iGoalHp -= CurrentEnnemy->Ennemy->Deg;
					}
					else
					{
						iGoalHp = 0;
					}
					CurrentEnnemy->Ennemy->Hp = 0;
				}
				CurrentEnnemy = CurrentEnnemy->NextElement;


#pragma endregion PERTE DE PV OBJECTIF

				//printf("ANGLE SPRITE : %.2f | CURRENT ANGLE : %.2f\n", CurrentEnnemy->Ennemy->fAngleSprite, CurrentEnnemy->Ennemy->fCurrentAngleDirection);
				//CurrentEnnemy->Ennemy->fAngleSprite = GetAngleDegreeFromVector(CurrentEnnemy->Ennemy->vCurrentVelocity);

				//printf("DIRECTION X : %.2f | DIRECTION Y : %.2f\n", CurrentEnnemy->Ennemy->vCurrentDirection.x, CurrentEnnemy->Ennemy->vCurrentDirection.y);
				//printf("VELOCITY X : %.2f | VELOCITY Y : %.2f\n", CurrentEnnemy->Ennemy->vCurrentVelocity.x, CurrentEnnemy->Ennemy->vCurrentVelocity.y);
				//printf("COLLIDE : %d\n", CurrentEnnemy->Ennemy->iIsColliding);
			}

#pragma endregion READ LIST ENNEMY CALCUL //GUILLAUME

		}

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
				vMousePointToCheck.y = (sfSprite_getGlobalBounds(CurrentTower->Tower->sprite).height- 15) - (CurrentTower->Tower->vPos.y - vMousePosToFloat.y);
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
					NewWhiteCell->whiteCell->dirState = UP_LEFT;
					NewWhiteCell->whiteCell->sprite = Spr_whiteCell;
					NewWhiteCell->whiteCell->animRect.left = NewWhiteCell->whiteCell->animFrame * WHITE_CELL_WIDTH;
					NewWhiteCell->whiteCell->animRect.top = NewWhiteCell->whiteCell->dirState * WHITE_CELL_HEIGHT;
					NewWhiteCell->whiteCell->animRect.width = WHITE_CELL_WIDTH;
					NewWhiteCell->whiteCell->animRect.height = WHITE_CELL_HEIGHT;
					sfSprite_setTextureRect(NewWhiteCell->whiteCell->sprite, NewWhiteCell->whiteCell->animRect);

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
					sfSprite_setTextureRect(NewWhiteCell->whiteCell->sprite, NewWhiteCell->whiteCell->animRect);
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

		isSearchingForDead = sfTrue;
		
		while (isSearchingForDead)
		{
			CurrentEnnemy = ListEnnemy->FirstElement;
			while (CurrentEnnemy != NULL)
			{
				asBreak = sfFalse;
				if (CurrentEnnemy->Ennemy->Hp <= 0)
				{
					iWaveEnnemyDead++;
					DeleteElementById(ListEnnemy, CurrentEnnemy->Id);
					
					asBreak = sfTrue;
					break;
				}
				else
				{
					CurrentEnnemy = CurrentEnnemy->NextElement;
				}
			}
			if (!asBreak)
			{
				isSearchingForDead = sfFalse;
				break;
			}
			break;

		}

#pragma endregion LECTURE DESTRUCTION ENNEMIS MORTS //SEB

#pragma region LECTURE TRAITEMENT GLOBULES BLANCS //SEB

		CurrentWhiteCell = ListWhiteCell->FirstElement;
		while (CurrentWhiteCell != NULL)
		{
			CurrentWhiteCell->whiteCell->boundingBox.left = CurrentWhiteCell->whiteCell->vPos.x - 30;
			CurrentWhiteCell->whiteCell->boundingBox.top = CurrentWhiteCell->whiteCell->vPos.y - 130;
			CurrentWhiteCell->whiteCell->boundingBox.width = 45;
			CurrentWhiteCell->whiteCell->boundingBox.height = 146;
			if (!CurrentWhiteCell->whiteCell->isWalking)
			{

				asBreak = sfFalse;
				//printf_s("posX :%.2f,posY: %.2f\n", CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y);
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


				if (sfImage_getPixel(Image_Map2, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).b == 255)
				{
					//printf_s("Bas Gauche\n");
					CurrentWhiteCell->whiteCell->dirState = DOWN_LEFT;
				}
				else if (sfImage_getPixel(Image_Map2, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).g == 255)
				{
					//printf_s("Bas Droite\n");
					CurrentWhiteCell->whiteCell->dirState = DOWN_RIGHT;
				}
				else if (sfImage_getPixel(Image_Map2, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).r == 150
					&& sfImage_getPixel(Image_Map2, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).g == 150)
				{
					//printf_s("Haut Gauche\n");
					CurrentWhiteCell->whiteCell->dirState = UP_LEFT;
				}
				else if (sfImage_getPixel(Image_Map2, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).g == 150
					&& sfImage_getPixel(Image_Map2, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).b == 150)
				{
					//printf_s("Haut Doite\n");
					CurrentWhiteCell->whiteCell->dirState = UP_RIGHT;
				}
			}
			else if (CurrentWhiteCell->whiteCell->isWalking && CurrentWhiteCell->whiteCell->vPos.x >= 0 && CurrentWhiteCell->whiteCell->vPos.x <= 1920
				&& CurrentWhiteCell->whiteCell->vPos.y >= 0 && CurrentWhiteCell->whiteCell->vPos.y <= 1080)
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

				if (sfImage_getPixel(Image_Map2, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).b == 255)
				{
					//printf_s("Bas Gauche\n");
					CurrentWhiteCell->whiteCell->dirState = DOWN_LEFT;
					CurrentWhiteCell->whiteCell->vDir = GetDirectionFromAngleDegrees(150 + 3);
					CurrentWhiteCell->whiteCell->vDir = normalizeVector(CurrentWhiteCell->whiteCell->vDir);
					CurrentWhiteCell->whiteCell->vPos.x += CurrentWhiteCell->whiteCell->vDir.x * WHITE_CELL_SPD_FACTOR;
					CurrentWhiteCell->whiteCell->vPos.y += CurrentWhiteCell->whiteCell->vDir.y * WHITE_CELL_SPD_FACTOR;
				}
				else if (sfImage_getPixel(Image_Map2, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).g == 255)
				{
					//printf_s("Bas Droite\n");
					CurrentWhiteCell->whiteCell->dirState = DOWN_RIGHT;
					CurrentWhiteCell->whiteCell->vDir = GetDirectionFromAngleDegrees(30 - 3);
					CurrentWhiteCell->whiteCell->vDir = normalizeVector(CurrentWhiteCell->whiteCell->vDir);
					CurrentWhiteCell->whiteCell->vPos.x += CurrentWhiteCell->whiteCell->vDir.x * WHITE_CELL_SPD_FACTOR;
					CurrentWhiteCell->whiteCell->vPos.y += CurrentWhiteCell->whiteCell->vDir.y * WHITE_CELL_SPD_FACTOR;
				}
				else if (sfImage_getPixel(Image_Map2, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).r == 150 
					&& sfImage_getPixel(Image_Map2, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).g == 150)
				{
					//printf_s("Haut Gauche\n");
					CurrentWhiteCell->whiteCell->dirState = UP_LEFT;
					CurrentWhiteCell->whiteCell->vDir = GetDirectionFromAngleDegrees(210 - 3);
					CurrentWhiteCell->whiteCell->vDir = normalizeVector(CurrentWhiteCell->whiteCell->vDir);
					CurrentWhiteCell->whiteCell->vPos.x += CurrentWhiteCell->whiteCell->vDir.x * WHITE_CELL_SPD_FACTOR;
					CurrentWhiteCell->whiteCell->vPos.y += CurrentWhiteCell->whiteCell->vDir.y * WHITE_CELL_SPD_FACTOR;
				}
				else if (sfImage_getPixel(Image_Map2, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).g == 150
					&& sfImage_getPixel(Image_Map2, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).b == 150)
				{
					//printf_s("Haut Doite\n");
					CurrentWhiteCell->whiteCell->dirState = UP_RIGHT;
					CurrentWhiteCell->whiteCell->vDir = GetDirectionFromAngleDegrees(330 + 3);
					CurrentWhiteCell->whiteCell->vDir = normalizeVector(CurrentWhiteCell->whiteCell->vDir);
					CurrentWhiteCell->whiteCell->vPos.x += CurrentWhiteCell->whiteCell->vDir.x * WHITE_CELL_SPD_FACTOR;
					CurrentWhiteCell->whiteCell->vPos.y += CurrentWhiteCell->whiteCell->vDir.y * WHITE_CELL_SPD_FACTOR;
				}
				else if (sfImage_getPixel(Image_Map2, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).r == 255 && sfImage_getPixel(Image_Map2, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).g == 255
					&& sfImage_getPixel(Image_Map2, CurrentWhiteCell->whiteCell->vPos.x, CurrentWhiteCell->whiteCell->vPos.y).b == 255)
				{
					//printf_s("Random dir\n");
				}
				else
				{
					CurrentWhiteCell->whiteCell->vPos.x += CurrentWhiteCell->whiteCell->vDir.x * WHITE_CELL_SPD_FACTOR;
					CurrentWhiteCell->whiteCell->vPos.y += CurrentWhiteCell->whiteCell->vDir.y * WHITE_CELL_SPD_FACTOR;
					//printf_s("Not In\n");
				}

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
				DeleteElementByIdWhiteCell(ListWhiteCell,CurrentWhiteCell->Id);
				
				break;
			}


			CurrentWhiteCell = CurrentWhiteCell->NextElement;
		}

#pragma endregion LECTURE TRAITEMENT GLOBULES BLANCS //SEB

#pragma region LECTURE AFFICHAGE DES GLOBULES BLANCS //SEB

		CurrentWhiteCell = ListWhiteCell->FirstElement;
		while (CurrentWhiteCell != NULL)
		{
			CurrentWhiteCell->whiteCell->animRect.left = CurrentWhiteCell->whiteCell->animFrame * WHITE_CELL_WIDTH;
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

		CurrentTower = ListTower->FirstElement;
		while (CurrentTower != NULL)
		{
			CurrentEnnemy = ListEnnemy->FirstElement;
			while (CurrentEnnemy != NULL)
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
						case TYPE2 :
							CurrentEnnemy->Ennemy->fSpeedFactor = 0.5;

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
						//printf_s("Out of colision!!\n");
						CurrentEnnemy->Ennemy->fSpeedFactor = 1.2;
					}
				}
				else
				{
					//CurrentEnnemy->Ennemy->fSpeedFactor = 1.2;
					sfSprite_setColor(CurrentTower->Tower->fieldSpr, sfWhite);
				}
				CurrentEnnemy = CurrentEnnemy->NextElement;
			}


			CurrentTower = CurrentTower->NextElement;
		}




#pragma endregion LECTURE CONTROLE COLISION TOURS //SEB

#pragma region GESTION MENU CONSTRUCTION //SEB

		/*animation ouverture menu construction*/
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

		/*Mode construction ouvert*/
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
				if (sfFloatRect_contains(&Rect_TowerSlotBtnBB, vMousePosToFloat.x, vMousePosToFloat.y))
				{
					sfSprite_setPosition(Sp_fieldOfView, ActualTowerSlot->TowerSlot->vPos);
					sfRenderWindow_drawSprite(window, Sp_fieldOfView, NULL);

					sfSprite_setColor(btn1->sprite, sfYellow);
					btn1->isOver = sfTrue;
					if (sfMouse_isButtonPressed(sfMouseLeft) && !isMousePressed)
					{
						isMousePressed = sfTrue;
						NewTower = AddElementBeginListTower(ListTower);
						NewTower->Tower = malloc(sizeof(t_Tower));
						NewTower->Tower->vPos.x = ActualTowerSlot->TowerSlot->vPos.x;
						NewTower->Tower->vPos.y = ActualTowerSlot->TowerSlot->vPos.y;
						NewTower->Tower->TowerType = TYPE1;
						NewTower->Tower->sprite = Sp_tower1;
						NewTower->Tower->TowerLevel = NORMAL;
						NewTower->Tower->animRect.left = 0;
						NewTower->Tower->animRect.top = NewTower->Tower->TowerLevel * TOWER_HEIGHT;
						NewTower->Tower->animRect.width = TOWER_WIDTH;
						NewTower->Tower->animRect.height = TOWER_HEIGHT;
						NewTower->Tower->tStartShoot = (float)clock() / CLOCKS_PER_SEC;
						NewTower->Tower->tSinceShoot = 0;
						NewTower->Tower->tCurrentShoot = 0;
						NewTower->Tower->fieldSpr = createSprite("resources/textures/tower_field_of_view.png");
						NewTower->Tower->bulletSpeed = 0.5;
						NewTower->Tower->iSlotId = ActualTowerSlot->Id;
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
				if (sfFloatRect_contains(&Rect_TowerSlotBtnBB, vMousePosToFloat.x, vMousePosToFloat.y))
				{
					sfSprite_setPosition(Sp_fieldOfView, ActualTowerSlot->TowerSlot->vPos);
					sfRenderWindow_drawSprite(window, Sp_fieldOfView, NULL);
					sfSprite_setColor(btn2->sprite, sfYellow);
					btn2->isOver = sfTrue;
					if (sfMouse_isButtonPressed(sfMouseLeft) && !isMousePressed)
					{
						isMousePressed = sfTrue;
						NewTower = AddElementBeginListTower(ListTower);
						NewTower->Tower = malloc(sizeof(t_Tower));
						NewTower->Tower->vPos.x = ActualTowerSlot->TowerSlot->vPos.x;
						NewTower->Tower->vPos.y = ActualTowerSlot->TowerSlot->vPos.y;
						NewTower->Tower->TowerType = TYPE2;
						NewTower->Tower->sprite = Sp_tower2;
						NewTower->Tower->TowerLevel = NORMAL;
						NewTower->Tower->animRect.left = 0;
						NewTower->Tower->animRect.top = NewTower->Tower->TowerLevel * TOWER_HEIGHT;
						NewTower->Tower->animRect.width = TOWER_WIDTH;
						NewTower->Tower->animRect.height = TOWER_HEIGHT;
						//NewTower->Tower->tStartShoot = (float)clock() / CLOCKS_PER_SEC;
						//NewTower->Tower->tSinceShoot = 0;
						//NewTower->Tower->tCurrentShoot = 0;
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
				if (sfFloatRect_contains(&Rect_TowerSlotBtnBB, vMousePosToFloat.x, vMousePosToFloat.y))
				{
					sfSprite_setColor(btn3->sprite, sfYellow);
					btn3->isOver = sfTrue;
					if (sfMouse_isButtonPressed(sfMouseLeft) && !isMousePressed)
					{
						isMousePressed = sfTrue;
						NewTower = AddElementBeginListTower(ListTower);
						NewTower->Tower = malloc(sizeof(t_Tower));
						NewTower->Tower->vPos.x = ActualTowerSlot->TowerSlot->vPos.x;
						NewTower->Tower->vPos.y = ActualTowerSlot->TowerSlot->vPos.y;
						NewTower->Tower->TowerType = TYPE3;
						NewTower->Tower->sprite = Sp_tower3;
						NewTower->Tower->TowerLevel = NORMAL;
						NewTower->Tower->animRect.left = 0;
						NewTower->Tower->animRect.top = NewTower->Tower->TowerLevel * TOWER_HEIGHT;
						NewTower->Tower->animRect.width = TOWER_WIDTH;
						NewTower->Tower->animRect.height = TOWER_HEIGHT;
						NewTower->Tower->tStartShoot = (float)clock() / CLOCKS_PER_SEC;
						NewTower->Tower->tSinceShoot = 0;
						NewTower->Tower->tCurrentShoot = 0;
						NewTower->Tower->iSlotId = ActualTowerSlot->Id;
						NewTower->Tower->iIsWhiteCellAlive = sfFalse;
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
		}

#pragma endregion GESTION MENU CONSTRUCTION //SEB

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
			sfSprite_setTextureRect(CurrentTower->Tower->sprite, CurrentTower->Tower->animRect);
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

#pragma region GESTION MENU UP/SELL //SEB

		/*animation menu up/sell*/
		if (isBuildedChoice && !isBuildedOpened)
		{

			vDistanceBetween.x = btnUpgrade->vPos.x - ActualTower->Tower->vPos.x;
			vDistanceBetween.y = btnUpgrade->vPos.y - ActualTower->Tower->vPos.y +50;
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
								CurrentTowerSlot->TowerSlot->IsBuild = 0;
								CurrentTowerSlot->TowerSlot->IsClicked = 0;
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
				if (sfFloatRect_contains(&Rect_TowerSlotBtnBB, vMousePosToFloat.x, vMousePosToFloat.y))
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
					DeleteElementByIdBullet(ListTowerBullet,CurrentTowerBullet->Id);
					asBreak =sfTrue;
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
			sfRectangleShape_setPosition(CurrentEnnemy->Ennemy->RectangleShapeBack, CurrentEnnemy->Ennemy->vPositionRectangleShapeBack);
			sfRenderWindow_drawRectangleShape(window, CurrentEnnemy->Ennemy->RectangleShapeBack, NULL);
			sfRectangleShape_setPosition(CurrentEnnemy->Ennemy->RectangleShapeBack, CurrentEnnemy->Ennemy->vPositionRectangleShape);
			sfRenderWindow_drawRectangleShape(window, CurrentEnnemy->Ennemy->RectangleShape, NULL);

			/*CurrentEnnemy->Ennemy->vPositionRectangleShapeBack.x = CurrentEnnemy->Ennemy->vCurrentPosition.x - CurrentEnnemy->Ennemy->vOrigin.x;
			CurrentEnnemy->Ennemy->vPositionRectangleShapeBack.y = CurrentEnnemy->Ennemy->vCurrentPosition.y - CurrentEnnemy->Ennemy->vOrigin.y - 8;
			CurrentEnnemy->Ennemy->vPositionRectangleShape.x = CurrentEnnemy->Ennemy->vCurrentPosition.x - CurrentEnnemy->Ennemy->vOrigin.x;
			CurrentEnnemy->Ennemy->vPositionRectangleShape.y = CurrentEnnemy->Ennemy->vCurrentPosition.y - CurrentEnnemy->Ennemy->vOrigin.y - 8;
			sfRectangleShape_setPosition(CurrentEnnemy->Ennemy->RectangleShapeBack, CurrentEnnemy->Ennemy->vPositionRectangleShapeBack);
			sfRectangleShape_setPosition(CurrentEnnemy->Ennemy->RectangleShape, CurrentEnnemy->Ennemy->vPositionRectangleShape);
			CurrentEnnemy->Ennemy->vSizeRectangleShape.x =(CurrentEnnemy->Ennemy->Hp / CurrentEnnemy->Ennemy->HpMax) * LIFEBAR_MAX_SIZE_X;
			if (CurrentEnnemy->Ennemy->vSizeRectangleShape.x <= 0)
			{
			CurrentEnnemy->Ennemy->vSizeRectangleShape.x = 0;
			}
			sfRectangleShape_setSize(CurrentEnnemy->Ennemy->RectangleShape, CurrentEnnemy->Ennemy->vSizeRectangleShape);
			sfRenderWindow_drawRectangleShape(window, CurrentEnnemy->Ennemy->RectangleShapeBack, NULL);
			sfRenderWindow_drawRectangleShape(window, CurrentEnnemy->Ennemy->RectangleShape, NULL);*/

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

		/*affichage pv objectif*/
		sfText_setFillColor(Text, sfCyan);
		sprintf_s(cText, 50, "PV : %d", iGoalHp);
		sfText_setString(Text, cText);
		vOriginText.x = sfText_getGlobalBounds(Text).width / 2;
		vOriginText.y = sfText_getGlobalBounds(Text).height / 2;
		sfText_setOrigin(Text, vOriginText);
		vPositionText.x = vWindowCenter.x;
		vPositionText.y = 50;
		sfText_setPosition(Text, vPositionText);
		sfRenderWindow_drawText(window, Text, NULL);

		/*affichage numéro de vague*/
		sfText_setFillColor(Text, sfBlack);
		sprintf_s(cText, 50, "VAGUE : %d", iWave);
		sfText_setString(Text, cText);
		vOriginText.x = sfText_getGlobalBounds(Text).width / 2;
		vOriginText.y = sfText_getGlobalBounds(Text).height / 2;
		sfText_setOrigin(Text, vOriginText);
		vPositionText.x = 200;
		vPositionText.y = 50;
		sfText_setPosition(Text, vPositionText);
		sfRenderWindow_drawText(window, Text, NULL);
		//printf("GOALHP : %d\n", iGoalHp);

		if (iGameState == PLAY)
		{
			/*affichage nomber d'ennemis de la vague*/
			sfText_setFillColor(Text, sfBlack);
			sprintf_s(cText, 50, "APPARITIONS ENNEMIS %d : %d", iWaveEnnemyNbr, iWaveEnnemyMaxNbr);
			sfText_setString(Text, cText);
			vOriginText.x = sfText_getGlobalBounds(Text).width / 2;
			vOriginText.y = sfText_getGlobalBounds(Text).height / 2;
			sfText_setOrigin(Text, vOriginText);
			vPositionText.x = 325;
			vPositionText.y = 150;
			sfText_setPosition(Text, vPositionText);
			sfRenderWindow_drawText(window, Text, NULL);

			/*affichage nomber d'ennemis de la vague*/
			sfText_setFillColor(Text, sfBlack);
			sprintf_s(cText, 50, "ENNEMIS RESTANTS %d : %d", iWaveEnnemyDead, iWaveEnnemyMaxNbr);
			sfText_setString(Text, cText);
			vOriginText.x = sfText_getGlobalBounds(Text).width / 2;
			vOriginText.y = sfText_getGlobalBounds(Text).height / 2;
			sfText_setOrigin(Text, vOriginText);
			vPositionText.x = 300;
			vPositionText.y = 225;
			sfText_setPosition(Text, vPositionText);
			sfRenderWindow_drawText(window, Text, NULL);
		}

#pragma endregion AFFICHAGE HUD //GUILLAUME

#pragma region VICTOIRE ET DEFAITE //GUILLAUME

		/*conditions de victoire*/
		if (iWave > iWaveMax)
		{
			iGameState = VICTORY;
		}

		/*conditions de victoire*/
		if (iGoalHp <= 0)
		{
			iGameState = DEFEAT;
		}

		if (iGameState == DEFEAT)
		{
			sfText_setFillColor(Text, sfRed);
			sprintf_s(cText, 50, "DEFAITE");
			sfText_setString(Text, cText);
			vOriginText.x = sfText_getGlobalBounds(Text).width / 2;
			vOriginText.y = sfText_getGlobalBounds(Text).height / 2;
			sfText_setOrigin(Text, vOriginText);
			vPositionText.x = vWindowCenter.x;
			vPositionText.y = vWindowCenter.y;
			sfText_setPosition(Text, vPositionText);
			sfRenderWindow_drawText(window, Text, NULL);
		}
		if (iGameState == VICTORY)
		{
			sfText_setFillColor(Text, sfCyan);
			sprintf_s(cText, 50, "VICTOIRE");
			sfText_setString(Text, cText);
			vOriginText.x = sfText_getGlobalBounds(Text).width / 2;
			vOriginText.y = sfText_getGlobalBounds(Text).height / 2;
			sfText_setOrigin(Text, vOriginText);
			vPositionText.x = vWindowCenter.x;
			vPositionText.y = vWindowCenter.y;
			sfText_setPosition(Text, vPositionText);
			sfRenderWindow_drawText(window, Text, NULL);
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


		/* Update the window */
		sfRenderWindow_display(window);
	}
	/* Cleanup resources */
	sfRenderWindow_destroy(window);

	return 0;
}