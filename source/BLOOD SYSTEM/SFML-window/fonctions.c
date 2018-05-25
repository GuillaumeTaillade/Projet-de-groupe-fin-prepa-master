#include "header.h"

///// Functions using the SFML Library //////
#pragma region SFML Functions

sfSprite* createSprite(char* _path)
{
	//_path correspond au chemin d'accées de la texture
	/* Load a sprite to display */
	sfTexture *texture = sfTexture_createFromFile(_path, NULL);
	if (!texture)
	{
		printf("Fail to Load The sprite\n");
		return NULL; // ne pas faire un ewit mais retourne null (annonce que le sprite n'a pas charger)
	}
	sfSprite *sprite = sfSprite_create();
	sfSprite_setTexture(sprite, texture, sfTrue);
	return sprite;
}

sfSound* createSound(char* _path)
{
	sfSoundBuffer* SoundBuffer = sfSoundBuffer_createFromFile(_path);
	if (!SoundBuffer)
	{
		printf("Fail to load the sound");
	}
	sfSound* Sound = sfSound_create();
	sfSound_setBuffer(Sound, SoundBuffer);

	return Sound;
}

sfText* createText(char* _path)
{
	sfFont *Font = sfFont_createFromFile(_path, NULL);
	if (!Font)
		return NULL;
	sfText * Text = sfText_create();
	sfText_setFont(Text, Font, sfTrue);
	return Text;
}

/*draw the textbox & the text*/
sfText* DrawTextInTextBox(sfRenderWindow* window, char* _text, const sfSprite* _TextBox)
{
	/*get the position of the textbox*/
	sfFloatRect rect_spGame_TextBox = sfSprite_getGlobalBounds(_TextBox);

	/*set the position of the text in the center of the textbox*/
	sfVector2f vPositionText;
	vPositionText.x = rect_spGame_TextBox.left + rect_spGame_TextBox.width / 2;
	vPositionText.y = rect_spGame_TextBox.top + rect_spGame_TextBox.height / 2;
	sfText_setPosition(_text, vPositionText);

	/*display of the texts*/
	sfRenderWindow_drawSprite(window, _TextBox, NULL);
	sfRenderWindow_drawText(window, _text, NULL);
}

/*draw the text*/
sfText* DrawTextWindow(sfRenderWindow* window, char* _text, sfVector2f _vPositionText)
{
	/*set the position of the text in the center of the textbox*/
	sfText_setPosition(_text, _vPositionText);
	/*display of the text*/
	sfRenderWindow_drawText(window, _text, NULL);
}

/*check if the mouse is on anothe sprite and if so change the sprite colour*/
int MouseIsOverSprite(char *_window, sfVector2f _vPositionSprite, sfVector2f _vOriginSprite)
{
	sfVector2i mousePos = sfMouse_getPosition(_window);

	if (mousePos.x > _vPositionSprite.x - _vOriginSprite.x && mousePos.x < _vPositionSprite.x + _vOriginSprite.x
		&& mousePos.y > _vPositionSprite.y - _vOriginSprite.y && mousePos.y < _vPositionSprite.y + _vOriginSprite.y)
	{
		return 1;
	}
	return 0;
}

/*check if the mouse is on a text and if so change the sprite colour*/
int MouseIsOverText(char *_window, char *_text)
{
	sfFloatRect boundingBox = sfText_getGlobalBounds(_text);

	sfVector2i mousePos = sfMouse_getPosition(_window);

	if (mousePos.x > boundingBox.left && mousePos.x < (boundingBox.left + boundingBox.width)
		&& mousePos.y > boundingBox.top && mousePos.y < (boundingBox.top + boundingBox.height))
	{
		return 1;
	}
	return 0;
}

int SpriteIsOver(char *_spritePerso, char *_spriteObject)
{
	sfFloatRect boundingBox_spriteObject = sfSprite_getGlobalBounds(_spriteObject);

	sfFloatRect boundingBox_spritePerso = sfSprite_getGlobalBounds(_spritePerso);


	if ((boundingBox_spritePerso.left >= boundingBox_spriteObject.left + boundingBox_spriteObject.width) // coté gauche perso plus à droite que le coté droit de l'objet
		|| ((boundingBox_spritePerso.left + boundingBox_spritePerso.width) <= boundingBox_spriteObject.left) // coté droit perso plus à gauche que le coté gauche de l'objet
		|| (boundingBox_spritePerso.top >= boundingBox_spriteObject.top + boundingBox_spriteObject.height) // haut du perso plus bas que le bas de l'objet
		|| (boundingBox_spritePerso.top + boundingBox_spritePerso.height <= boundingBox_spriteObject.top)) // bas du perso au dessus du haut de l'objet

																										   // si ses conditions sont remplis alors le perso est hors de l'objet
	{
		return 0;
		sfSprite_setColor(_spriteObject, sfColor_fromRGBA(255, 255, 255, 255));

	}

	// si le personnage est sur l'objet
	sfSprite_setColor(_spriteObject, sfColor_fromRGBA(255, 0, 255, 255));
	return 1;
}

int SpriteIsOverPosition(sfVector2f _vPositionPerso, sfVector2f _vOriginPerso, sfVector2f _vPositionObject, sfVector2f _vOriginObject)
{
	if ((_vPositionPerso.x - _vOriginPerso.x >= _vPositionObject.x + _vOriginObject.x) // coté gauche perso plus à droite que le coté droit de l'objet
		|| (_vPositionPerso.x + _vOriginPerso.x <= _vPositionObject.x - _vOriginObject.x) // coté droit perso plus à gauche que le coté gauche de l'objet
		|| (_vPositionPerso.y - _vOriginPerso.y >= _vPositionObject.y + _vOriginObject.y) // coté gauche perso plus à droite que le coté droit de l'objet
		|| (_vPositionPerso.y + _vOriginPerso.y <= _vPositionObject.y - _vOriginObject.y)) // bas du perso au dessus du haut de l'objet
																						   // si ses conditions sont remplis alors le perso est hors de l'objet
	{
		return 0;
	}
	// si le personnage est sur l'objet
	return 1;
}

int SpriteIsOverGlobalBounds(sfFloatRect _GlobalBoundsPerso, sfFloatRect _GlobalBoundsObject)
{
	if ((_GlobalBoundsPerso.left >= _GlobalBoundsObject.left + _GlobalBoundsObject.width) // coté gauche perso plus à droite que le coté droit de l'objet
		|| (_GlobalBoundsPerso.left + _GlobalBoundsPerso.width <= _GlobalBoundsObject.left) // coté droit perso plus à gauche que le coté gauche de l'objet
		|| (_GlobalBoundsPerso.top >= _GlobalBoundsObject.top + _GlobalBoundsObject.height) // coté gauche perso plus à droite que le coté droit de l'objet
		|| (_GlobalBoundsPerso.top + _GlobalBoundsPerso.height <= _GlobalBoundsObject.top)) // bas du perso au dessus du haut de l'objet
																							// si ses conditions sont remplis alors le perso est hors de l'objet
	{
		return 0;
	}
	// si le personnage est sur l'objet
	return 1;
}

//void Collider(sfImage* _collid, Player* player)
//{
//
//	sfColor down_left = sfImage_getPixel(_collid, player->vPos.x - (PLAYER_SIZE_WIDTH / 2), player->vPos.y + (PLAYER_SIZE_HEIGHT / 2) + 5);
//	sfColor down_middle = sfImage_getPixel(_collid, player->vPos.x, player->vPos.y + (PLAYER_SIZE_HEIGHT / 2) + 5);
//	sfColor down_right = sfImage_getPixel(_collid, player->vPos.x + (PLAYER_SIZE_WIDTH / 2), player->vPos.y + (PLAYER_SIZE_HEIGHT / 2) + 5);
//
//	if (sfColor_toInteger(down_middle) == COLOR_COLLID || sfColor_toInteger(down_left) == COLOR_COLLID || sfColor_toInteger(down_right) == COLOR_COLLID)
//	{
//		player->vPos.y -= 1;
//		player->iDownCollid = 1;
//	}
//	else
//	{
//
//		player->iDownCollid = 0;
//	}
//
//	sfColor up_left = sfImage_getPixel(_collid, player->vPos.x - (PLAYER_SIZE_WIDTH / 2), player->vPos.y - (PLAYER_SIZE_HEIGHT / 2) - 5);
//	sfColor up_middle = sfImage_getPixel(_collid, player->vPos.x, player->vPos.y - (PLAYER_SIZE_HEIGHT / 2) - 5);
//	sfColor up_right = sfImage_getPixel(_collid, player->vPos.x + (PLAYER_SIZE_WIDTH / 2), player->vPos.y - (PLAYER_SIZE_HEIGHT / 2) - 5);
//
//	if (sfColor_toInteger(up_middle) == COLOR_COLLID || sfColor_toInteger(up_left) == COLOR_COLLID || sfColor_toInteger(up_right) == COLOR_COLLID)
//	{
//
//
//		player->iUpCollid += 1;
//		player->iUpCollid = 1;
//	}
//	else
//	{
//
//		player->iUpCollid = 0;
//	}
//
//	sfColor left_up = sfImage_getPixel(_collid, player->vPos.x - (PLAYER_SIZE_WIDTH / 2) - 5, player->vPos.y - (PLAYER_SIZE_HEIGHT / 2));
//	sfColor left_middle = sfImage_getPixel(_collid, player->vPos.x - (PLAYER_SIZE_WIDTH / 2) - 5, player->vPos.y);
//	sfColor left_down = sfImage_getPixel(_collid, player->vPos.x - (PLAYER_SIZE_WIDTH / 2) - 5, player->vPos.y + (PLAYER_SIZE_HEIGHT / 2));
//
//	if (sfColor_toInteger(left_down) == COLOR_COLLID && sfColor_toInteger(left_middle) != COLOR_COLLID && sfColor_toInteger(left_up) != COLOR_COLLID)
//	{
//		player->iQMovement = 1;
//	}
//	else
//	{
//		player->iQMovement = 0;
//	}
//
//	if (sfColor_toInteger(left_middle) == COLOR_COLLID || sfColor_toInteger(left_down) == COLOR_COLLID || sfColor_toInteger(left_up) == COLOR_COLLID)
//	{
//
//
//		player->iLeftCollid = 1;
//	}
//	else
//	{
//
//		player->iLeftCollid = 0;
//	}
//
//	sfColor right_up = sfImage_getPixel(_collid, player->vPos.x + (PLAYER_SIZE_WIDTH / 2) + 5, player->vPos.y - (PLAYER_SIZE_HEIGHT / 2));
//	sfColor right_middle = sfImage_getPixel(_collid, player->vPos.x + (PLAYER_SIZE_WIDTH / 2) + 5, player->vPos.y);
//	sfColor right_down = sfImage_getPixel(_collid, player->vPos.x + (PLAYER_SIZE_WIDTH / 2) + 5, player->vPos.y + (PLAYER_SIZE_HEIGHT / 2));
//
//	if (sfColor_toInteger(right_down) == COLOR_COLLID && sfColor_toInteger(right_middle) != COLOR_COLLID && sfColor_toInteger(right_up) != COLOR_COLLID)
//	{
//		player->iDMovement = 1;
//	}
//	else
//	{
//		player->iDMovement = 0;
//	}
//
//
//	if (sfColor_toInteger(right_middle) == COLOR_COLLID || sfColor_toInteger(right_up) == COLOR_COLLID || sfColor_toInteger(right_down) == COLOR_COLLID)
//	{
//
//
//		player->iRightCollid = 1;
//	}
//	else
//	{
//
//		player->iRightCollid = 0;
//	}
//}

t_ListEnnemyWave* loadEnnemyWave(t_ListEnnemyWave* _ListEnnemyWave, int _levelNumber)
{
	t_EnnemyWaveElement* newElement = malloc(sizeof(t_EnnemyWaveElement));

	FILE* file = NULL;
	char* filePath = malloc(50);
	int iNbrWave = 0; // nombre de vaggue du niveau
	

	sprintf_s(filePath, 50, "resources/datas/ennemyWave1.txt", _levelNumber);
	fopen_s(&file, filePath, "r");

	if (file == NULL)
	{
		printf_s("Erreur d'ouverture du fichier EnnemyWave\n");
		return EXIT_FAILURE;
	}
	fscanf_s(file, "iNbrWave=%d\n", &iNbrWave);

	for (int i = 0; i < iNbrWave; i++)
	{
		newElement = AddElementBeginListEnnemyPathPoint(_ListEnnemyWave);
		newElement->EnnemyWave = malloc(sizeof(t_EnnemyWave));
		newElement->EnnemyWave->iMaxWave = iNbrWave;
		newElement->EnnemyWave->iNumWave = 0; // numéro de la vague
		newElement->EnnemyWave->iNbrCholesterol = 0; // nombre d'ennemis Cholesterol pendant la vague
		newElement->EnnemyWave->iNbrCancer = 0; // nombre d'ennemis Cancer pendant la vague
		newElement->EnnemyWave->iNbrCaillot = 0; // nombre d'ennemis Caillot pendant la vague
		newElement->EnnemyWave->iNbrTotal = 0; // nombre total d'ennemis
		fscanf_s(file, "Wave=%d,NbrCholesterol=%d,NbrCancer=%d,NbrCaillot=%d,NbrTotal=%d\n", &newElement->EnnemyWave->iNumWave, &newElement->EnnemyWave->iNbrCholesterol, &newElement->EnnemyWave->iNbrCancer, &newElement->EnnemyWave->iNbrCaillot, &newElement->EnnemyWave->iNbrTotal);
		printf("WAVENUM : %d\t NBR CHO : %d\t NBR CAN : %d\t NBR CAI : %d\t NBR TOT : %d\t\n", newElement->EnnemyWave->iNumWave, newElement->EnnemyWave->iNbrCholesterol, newElement->EnnemyWave->iNbrCancer, newElement->EnnemyWave->iNbrCaillot, newElement->EnnemyWave->iNbrTotal);
	}

	fclose(file);

	return _ListEnnemyWave;
}

t_ListEnnemyPathPoint* loadEnnemyPathPoint(t_ListEnnemyPathPoint* _ListEnnemyPathPoint, int _levelNumber, int _NumPath)
{
	t_EnnemyPathPointElement* newElement = malloc(sizeof(t_EnnemyPathPointElement));

	FILE* file = NULL;
	char* filePath = malloc(50);
	int iEnnemyPathPointNbr = 0;
	sprintf_s(filePath, 50, "resources/datas/ennemyPath%d-%d.txt", _levelNumber, _NumPath);
	fopen_s(&file, filePath, "r");

	if (file == NULL)
	{
		printf_s("Erreur d'ouverture du fichier EnnemyPathPoint\n");
		return EXIT_FAILURE;
	}
	fscanf_s(file, "iEnnemyPathNbr=%d\n", &iEnnemyPathPointNbr);

	for (int i = 0; i < iEnnemyPathPointNbr; i++)
	{
		newElement = AddElementBeginListEnnemyPathPoint(_ListEnnemyPathPoint);
		newElement->EnnemyPathPoint = malloc(sizeof(t_EnnemyPathPoint));
		fscanf_s(file, "Num=%d,vPosX=%f,vPosY=%f\n", &newElement->EnnemyPathPoint->Num, &newElement->EnnemyPathPoint->vPos.x, &newElement->EnnemyPathPoint->vPos.y);
		printf("NUM : %d\t\n", newElement->EnnemyPathPoint->Num);
		newElement->EnnemyPathPoint->vOrigin.x = SIZE_PATH_POINT / 2;
		newElement->EnnemyPathPoint->vOrigin.y = SIZE_PATH_POINT / 2;

	}

	fclose(file);

	return _ListEnnemyPathPoint;
}

/*charge le nombre de chemin présent dans le niveau*/
int loadEnnemyNbrPath(int _levelNumber)
{
	FILE* file = NULL;
	char* filePath = malloc(50);
	int iEnnemyPathNbr = 0;
	sprintf_s(filePath, 50, "resources/datas/ennemyNbrPath%d.txt", _levelNumber);
	fopen_s(&file, filePath, "r");

	if (file == NULL)
	{
		printf_s("Erreur d'ouverture du fichier EnnemyNbrPath\n");
		return EXIT_FAILURE;
	}
	fscanf_s(file, "iNbrPath=%d", &iEnnemyPathNbr);

	fclose(file);
	return iEnnemyPathNbr;
}

void loadTowerSlots(t_ListTowerSlot* _ListTowerSlot, int _levelNumber)
{
	t_TowerSlotElement* newElement = malloc(sizeof(t_TowerSlotElement));

	FILE* file = NULL;
	char* filePath = malloc(50);
	int iTowerSlotsNbr = 0;
	sprintf_s(filePath, 50, "resources/datas/towerSlots%d.txt", _levelNumber);
	fopen_s(&file, filePath, "r");

	if (file == NULL)
	{
		printf_s("Erreur d'ouverture du fichier TowerSlot\n");
		return EXIT_FAILURE;
	}
	fscanf_s(file, "iSlotNbr=%d,\n", &iTowerSlotsNbr);

	for (int i = 0; i < iTowerSlotsNbr; i++)
	{
		newElement = AddElementBeginListTowerSlot(_ListTowerSlot);
		newElement->TowerSlot = malloc(sizeof(t_TowerSlot));
		fscanf_s(file, "vPosX=%f,vPosY=%f,vSPosX=%f,vSPosY=%f\n", &newElement->TowerSlot->vPos.x, &newElement->TowerSlot->vPos.y, &newElement->TowerSlot->vSpawnPos.x, &newElement->TowerSlot->vSpawnPos.y);
		newElement->TowerSlot->IsBuild = sfFalse;
		newElement->TowerSlot->IsClicked = sfFalse;
		newElement->TowerSlot->BuildedType = NONE;
	}

	fclose(file);
}

void manageInGameMenu(t_inGameMenu* _inGameMenu)
{
	if (_inGameMenu->menuState == IS_OPENING)
	{
		if ((_inGameMenu->vPos_menuButton.y - _inGameMenu->vPos_musicButton.y) < MUSIC_BUTTON_DISTANCE)
		{
			_inGameMenu->vPos_musicButton.y -= BUTTON_SPEED;
			sfSprite_setPosition(_inGameMenu->musicButton, _inGameMenu->vPos_musicButton);
		}
		if ((_inGameMenu->vPos_menuButton.y - _inGameMenu->vPos_fxButton.y) < FX_BUTTON_DISTANCE)
		{
			_inGameMenu->vPos_fxButton.y -= BUTTON_SPEED;
			sfSprite_setPosition(_inGameMenu->fxButton, _inGameMenu->vPos_fxButton);
		}
		if ((_inGameMenu->vPos_menuButton.y - _inGameMenu->vPos_pauseButton.y) < PAUSE_BUTTON_DISTANCE)
		{
			_inGameMenu->vPos_pauseButton.y -= BUTTON_SPEED;
			sfSprite_setPosition(_inGameMenu->pauseButton, _inGameMenu->vPos_pauseButton);
		}
		else
		{
			_inGameMenu->musicButtonBB = sfSprite_getGlobalBounds(_inGameMenu->musicButton);
			_inGameMenu->fxButtonBB = sfSprite_getGlobalBounds(_inGameMenu->fxButton);
			_inGameMenu->pauseButtonBB = sfSprite_getGlobalBounds(_inGameMenu->pauseButton);
			_inGameMenu->menuState = IS_OPENED;
		}
	}
	else if (_inGameMenu->menuState == IS_CLOSING)
	{
		if ((_inGameMenu->vPos_menuButton.y - _inGameMenu->vPos_musicButton.y) > 0)
		{
			_inGameMenu->vPos_musicButton.y += BUTTON_SPEED;
			sfSprite_setPosition(_inGameMenu->musicButton, _inGameMenu->vPos_musicButton);
		}
		if ((_inGameMenu->vPos_menuButton.y - _inGameMenu->vPos_fxButton.y) > 0)
		{
			_inGameMenu->vPos_fxButton.y += BUTTON_SPEED;
			sfSprite_setPosition(_inGameMenu->fxButton, _inGameMenu->vPos_fxButton);
		}
		if ((_inGameMenu->vPos_menuButton.y - _inGameMenu->vPos_pauseButton.y) > 0)
		{
			_inGameMenu->vPos_pauseButton.y += BUTTON_SPEED;
			sfSprite_setPosition(_inGameMenu->pauseButton, _inGameMenu->vPos_pauseButton);
		}
		else
		{
			_inGameMenu->menuState = IS_CLOSED;
		}
	}
}

void loadSaveForSaveSlots(t_gameMenuSave* _gameMenuSave)
{
	FILE* file = NULL;

	fopen_s(&file, "resources/datas/saves/save_slot1.txt", "r");
	if (file == NULL)
	{
		printf_s("erreur ouverture save\n");
	}
	fscanf_s(file, "unlockedLevels=%d", &_gameMenuSave->unLockedLevelsSlot1);
	printf_s("unlocked levels 1: %d\n", _gameMenuSave->unLockedLevelsSlot1);
	fclose(file);
	switch (_gameMenuSave->unLockedLevelsSlot1)
	{
	case 0:
		_gameMenuSave->slot1MiniMap = createSprite("resources/textures/level_selector/miniMap_Level0.png");
		break;
	case 1:
		_gameMenuSave->slot1MiniMap = createSprite("resources/textures/level_selector/miniMap_Level1.png");
		break;
	case 2:
		_gameMenuSave->slot1MiniMap = createSprite("resources/textures/level_selector/miniMap_Level2.png");
		break;
	default:
		break;
	}

	fopen_s(&file, "resources/datas/saves/save_slot2.txt", "r");
	if (file == NULL)
	{
		printf_s("erreur ouverture save\n");
	}
	fscanf_s(file, "unlockedLevels=%d", &_gameMenuSave->unLockedLevelsSlot2);
	printf_s("unlocked levels 2: %d\n", _gameMenuSave->unLockedLevelsSlot2);
	fclose(file);
	switch (_gameMenuSave->unLockedLevelsSlot2)
	{
	case 0:
		_gameMenuSave->slot2MiniMap = createSprite("resources/textures/level_selector/miniMap_Level0.png");
		break;
	case 1:
		_gameMenuSave->slot2MiniMap = createSprite("resources/textures/level_selector/miniMap_Level1.png");
		break;
	case 2:
		_gameMenuSave->slot2MiniMap = createSprite("resources/textures/level_selector/miniMap_Level2.png");
		break;
	default:
		break;
	}

	fopen_s(&file, "resources/datas/saves/save_slot3.txt", "r");
	if (file == NULL)
	{
		printf_s("erreur ouverture save\n");
	}
	fscanf_s(file, "unlockedLevels=%d", &_gameMenuSave->unLockedLevelsSlot3);
	printf_s("unlocked levels 3: %d\n", _gameMenuSave->unLockedLevelsSlot3);
	fclose(file);
	switch (_gameMenuSave->unLockedLevelsSlot3)
	{
	case 0:
		_gameMenuSave->slot3MiniMap = createSprite("resources/textures/level_selector/miniMap_Level0.png");
		break;
	case 1:
		_gameMenuSave->slot3MiniMap = createSprite("resources/textures/level_selector/miniMap_Level1.png");
		break;
	case 2:
		_gameMenuSave->slot3MiniMap = createSprite("resources/textures/level_selector/miniMap_Level2.png");
		break;
	default:
		break;
	}



}

/*charge les fichiers correspondantr au niveau et vide les listes utilisés*/
void loadGameFromLevelNumber(t_NameLevel _iCurrentLevel, t_CurrentLevelAssets* _CurrentLevelAssets, t_List* _ListEnnemy, t_ListBullet* _ListBullet, t_ListEnnemyBullet* _ListEnnemyBullet,
	t_ListTower* _ListTower, t_ListTowerSlot* _ListTowerSlot, t_ListWhiteCell* _ListWhiteCell)
{
	/*SUPPRESION DES ELEMENTS DES LISTES*/
	if (_ListEnnemy->FirstElement != NULL)
	{
		printf_s("Vidage liste ennemis\n");
		DeleteAllElementInList(_ListEnnemy);
	}
	if (_ListBullet->FirstElement != NULL)
	{
		printf_s("Vidage liste bullet\n");
		DeleteAllElementInList(_ListBullet);
	}
	if (_ListEnnemyBullet->FirstElement != NULL)
	{
		printf_s("Vidage liste bulletEnnemy\n");
		DeleteAllElementInList(_ListEnnemyBullet);
	}
	if (_ListTower->FirstElement != NULL)
	{
		printf_s("Vidage liste tower\n");
		DeleteAllElementInList(_ListTower);
	}
	if (_ListTowerSlot->FirstElement != NULL)
	{
		printf_s("Vidage liste tower slot\n");
		DeleteAllElementInList(_ListTowerSlot);
	}
	if (_ListWhiteCell->FirstElement != NULL)
	{
		printf_s("Vidage liste white cell\n");
		DeleteAllElementInList(_ListWhiteCell);
	}
	/*if (_CurrentLevelAssets->ListEnnemyWave->FirstElement != NULL)
	{
		printf_s("Vidage liste vagues ennemis\n");
		DeleteAllElementInList(_CurrentLevelAssets->ListEnnemyWave);
	}
	printf("Vidage du tableau de liste des chemins ennemis");
	for (int i = 0; i < MAX_LIST_ENNEMY_PATH_POINT; i++)
	{
		printf_s("Vidage liste chemin ennemi %d\n", i);
		DeleteAllElementInList(_CurrentLevelAssets->TabListEnnemyPathPoint[i]);
	}*/

	/*CHARGEMENT DES FICHIERS DU NIVEAU*/
	char* path = malloc(100);
	/*map et masque de collision*/
	sprintf_s(path, 100, "resources/textures/maps/map%d.jpg", _iCurrentLevel);
	_CurrentLevelAssets->map = createSprite(path);
	sprintf_s(path, 100, "resources/textures/maps/mapMask%d.psd", _iCurrentLevel);
	_CurrentLevelAssets->mapMask = sfImage_createFromFile(path);

	/*FICHIER VAGUE ENNEMI*/
	_CurrentLevelAssets->ListEnnemyWave = malloc(sizeof(t_ListEnnemyWave));
	_CurrentLevelAssets->ListEnnemyWave->FirstElement = NULL;
	_CurrentLevelAssets->ListEnnemyWave->LastElement = NULL;
	_CurrentLevelAssets->ListEnnemyWave = loadEnnemyWave(_CurrentLevelAssets->ListEnnemyWave, _iCurrentLevel);

	/*CREATTION D'UN TABLEAU DE LISTE*/
	_CurrentLevelAssets->iNbrEnnemyPath = loadEnnemyNbrPath(_iCurrentLevel);

	/*FICHIER CHEMIN A PRACOURIR*/
	for (int i = 0; i < _CurrentLevelAssets->iNbrEnnemyPath; i++)
	{
		/*chaque case du tableau pointe sur une liste*/
		_CurrentLevelAssets->TabListEnnemyPathPoint[i] = malloc(sizeof(t_ListEnnemyPathPoint));
		_CurrentLevelAssets->TabListEnnemyPathPoint[i]->FirstElement = NULL;
		_CurrentLevelAssets->TabListEnnemyPathPoint[i]->LastElement = NULL;
		_CurrentLevelAssets->TabListEnnemyPathPoint[i] = loadEnnemyPathPoint(_CurrentLevelAssets->TabListEnnemyPathPoint[i], _iCurrentLevel, i + 1);
	}

}
#pragma endregion SFML Functions

#pragma region LIST FUNCTIONS

t_EnnemyElement* AddElementBeginList(t_List* _List)
{
	t_EnnemyElement* NewElement = malloc(sizeof(t_EnnemyElement));

	if (_List == NULL || NewElement == NULL)
	{
		exit(EXIT_FAILURE);
	}


	if (_List->FirstElement == NULL)
	{
		NewElement->NextElement = _List->FirstElement;
		NewElement->PreviousElement = NULL;
		_List->FirstElement = NewElement;
		_List->LastElement = NewElement;
		//NewElement->Id = 0;
	}
	else
	{
		NewElement->NextElement = _List->FirstElement;
		NewElement->NextElement->PreviousElement = NewElement;
		NewElement->PreviousElement = NULL;
		_List->FirstElement = NewElement;
		//NewElement->Id = NewElement->NextElement->Id + 1;
	}
	NewElement->Id = _List->count;
	_List->count++;
	//printf("NEW ELEMENT IS ADD\n");
	return NewElement;
}

t_EnnemyBulletElement* AddElementBeginListEnnemyBullet(t_ListEnnemyBullet* _List)
{
	t_EnnemyBulletElement* NewElement = malloc(sizeof(t_EnnemyBulletElement));

	if (_List == NULL || NewElement == NULL)
	{
		exit(EXIT_FAILURE);
	}


	if (_List->FirstElement == NULL)
	{
		NewElement->NextElement = _List->FirstElement;
		NewElement->PreviousElement = NULL;
		_List->FirstElement = NewElement;
		_List->LastElement = NewElement;
		NewElement->Id = 0;
	}
	else
	{
		NewElement->NextElement = _List->FirstElement;
		NewElement->NextElement->PreviousElement = NewElement;
		NewElement->PreviousElement = NULL;
		_List->FirstElement = NewElement;
		NewElement->Id = NewElement->NextElement->Id + 1;
	}

	//printf("NEW ELEMENT IS ADD\n");
	return NewElement;
}

t_EnnemyWaveElement* AddElementBeginListEnnemyWave(t_ListEnnemyWave* _List)
{
	t_EnnemyWaveElement* NewElement = malloc(sizeof(t_EnnemyWaveElement));

	if (_List == NULL || NewElement == NULL)
	{
		exit(EXIT_FAILURE);
	}


	if (_List->FirstElement == NULL)
	{
		NewElement->NextElement = _List->FirstElement;
		NewElement->PreviousElement = NULL;
		_List->FirstElement = NewElement;
		_List->LastElement = NewElement;
		NewElement->Id = 0;
	}
	else
	{
		NewElement->NextElement = _List->FirstElement;
		NewElement->NextElement->PreviousElement = NewElement;
		NewElement->PreviousElement = NULL;
		_List->FirstElement = NewElement;
		NewElement->Id = NewElement->NextElement->Id + 1;
	}

	//printf("NEW ELEMENT IS ADD\n");
	return NewElement;
}

t_EnnemyPathPointElement* AddElementBeginListEnnemyPathPoint(t_ListEnnemyPathPoint* _List)
{
	t_EnnemyPathPointElement* NewElement = malloc(sizeof(t_EnnemyPathPointElement));

	if (_List == NULL || NewElement == NULL)
	{
		exit(EXIT_FAILURE);
	}


	if (_List->FirstElement == NULL)
	{
		NewElement->NextElement = _List->FirstElement;
		NewElement->PreviousElement = NULL;
		_List->FirstElement = NewElement;
		_List->LastElement = NewElement;
		NewElement->Id = 0;
	}
	else
	{
		NewElement->NextElement = _List->FirstElement;
		NewElement->NextElement->PreviousElement = NewElement;
		NewElement->PreviousElement = NULL;
		_List->FirstElement = NewElement;
		NewElement->Id = NewElement->NextElement->Id + 1;
	}

	//printf("NEW ELEMENT IS ADD\n");
	return NewElement;
}

t_TowerSlotElement* AddElementBeginListTowerSlot(t_ListTowerSlot* _List)
{
	t_TowerSlotElement* NewElement = malloc(sizeof(t_TowerSlotElement));

	if (_List == NULL || NewElement == NULL)
	{
		exit(EXIT_FAILURE);
	}


	if (_List->FirstElement == NULL)
	{
		NewElement->NextElement = _List->FirstElement;
		NewElement->PreviousElement = NULL;
		_List->FirstElement = NewElement;
		_List->LastElement = NewElement;
		NewElement->Id = 0;
	}
	else
	{
		NewElement->NextElement = _List->FirstElement;
		NewElement->NextElement->PreviousElement = NewElement;
		NewElement->PreviousElement = NULL;
		_List->FirstElement = NewElement;
		NewElement->Id = NewElement->NextElement->Id + 1;
	}

	//printf("NEW ELEMENT IS ADD\n");
	return NewElement;
}

t_TowerElement* AddElementBeginListTower(t_ListTower* _List)
{
	t_TowerElement* NewElement = malloc(sizeof(t_TowerSlotElement));

	if (_List == NULL || NewElement == NULL)
	{
		exit(EXIT_FAILURE);
	}


	if (_List->FirstElement == NULL)
	{
		NewElement->NextElement = _List->FirstElement;
		NewElement->PreviousElement = NULL;
		_List->FirstElement = NewElement;
		_List->LastElement = NewElement;
		//NewElement->Id = 0;
	}
	else
	{
		NewElement->NextElement = _List->FirstElement;
		NewElement->NextElement->PreviousElement = NewElement;
		NewElement->PreviousElement = NULL;
		_List->FirstElement = NewElement;
		//NewElement->Id = NewElement->NextElement->Id + 1;
	}
	NewElement->Id = _List->count;
	_List->count++;
	//printf("NEW ELEMENT IS ADD\n");
	return NewElement;
}

t_TowerBulletElement* AddElementBeginListTowerBullet(t_ListBullet* _List)
{
	t_TowerBulletElement* NewElement = malloc(sizeof(t_TowerSlotElement));

	if (_List == NULL || NewElement == NULL)
	{
		exit(EXIT_FAILURE);
	}


	if (_List->FirstElement == NULL)
	{
		NewElement->NextElement = _List->FirstElement;
		NewElement->PreviousElement = NULL;
		_List->FirstElement = NewElement;
		_List->LastElement = NewElement;
		NewElement->Id = 0;
	}
	else
	{
		NewElement->NextElement = _List->FirstElement;
		NewElement->NextElement->PreviousElement = NewElement;
		NewElement->PreviousElement = NULL;
		_List->FirstElement = NewElement;
		NewElement->Id = NewElement->NextElement->Id + 1;
	}

	//printf("NEW ELEMENT IS ADD\n");
	return NewElement;
}

t_whiteCellElement* AddElementBeginListWhiteCell(t_ListWhiteCell* _List)
{
	t_whiteCellElement* NewElement = malloc(sizeof(t_whiteCellElement));

	if (_List == NULL || NewElement == NULL)
	{
		exit(EXIT_FAILURE);
	}


	if (_List->FirstElement == NULL)
	{
		NewElement->NextElement = _List->FirstElement;
		NewElement->PreviousElement = NULL;
		_List->FirstElement = NewElement;
		_List->LastElement = NewElement;
		//NewElement->Id = 0;
	}
	else
	{
		NewElement->NextElement = _List->FirstElement;
		NewElement->NextElement->PreviousElement = NewElement;
		NewElement->PreviousElement = NULL;
		_List->FirstElement = NewElement;
		//NewElement->Id = NewElement->NextElement->Id + 1;
	}
	NewElement->Id = _List->count;
	_List->count++;
	//printf("NEW ELEMENT IS ADD\n");
	return NewElement;
}

/*méthode liste chainée*/

//sfBool DeleteElementById(List* _List, int _IdElementToDelete)
//{
//	Element* CurrentElement = _List->FirstElement;
//	/*Delete First Element*/
//	if (CurrentElement->Id == _IdElementToDelete)
//	{
//		Element* ElementToDelete = CurrentElement;
//		_List->FirstElement = CurrentElement->NextElement;
//		free(ElementToDelete);
//		printf("DELETE ID %d\n", _IdElementToDelete);
//
//		return sfTrue;
//	}
//	else
//	{
//		/*parcours dans la boucle pour trouver l'élément a supprimer*/
//		while (CurrentElement != NULL)
//		{
//			/*si le prochain élément est celuis que l'on veut supprimer on attache le previous et le next avant de supprimer l'élément en question*/
//			if (CurrentElement->NextElement->Id == _IdElementToDelete)
//			{
//				Element* ElementToDelete = CurrentElement->NextElement;
//				if (CurrentElement->NextElement != NULL)
//				{
//					CurrentElement->NextElement = CurrentElement->NextElement->NextElement;
//				}
//				free(ElementToDelete);
//
//				printf("DELETE ID %d\n", _IdElementToDelete);
//				return sfTrue;
//			}
//			else
//			{
//				CurrentElement = CurrentElement->NextElement;
//			}
//		}
//	}
//	printf("FAIL TO DELETE ID %d\n", _IdElementToDelete);
//	return sfFalse;
//}


/*méthode liste doublement chainée*/

sfBool DeleteElementById(t_List* _List, int _IdElementToDelete)
{
	/*Delete de l'élément restant dans la liste*/
	if (_List->FirstElement == _List->LastElement)
	{
		t_EnnemyElement* ElementToDelete = _List->FirstElement;

		/*je reset les 2 pointeurs de ma liste a NULL*/
		_List->FirstElement = NULL;
		_List->LastElement = NULL;

		free(ElementToDelete);
		printf("DELETE THE SURVIVOR ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}

	/*Delete First Element*/
	if (_List->FirstElement->Id == _IdElementToDelete)
	{

		t_EnnemyElement* ElementToDelete = _List->FirstElement;
		if (_List->FirstElement->NextElement != NULL)
		{
			_List->FirstElement->NextElement->PreviousElement = NULL;
		}
		_List->FirstElement = _List->FirstElement->NextElement;

		free(ElementToDelete);
		printf("DELETE FIRST ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}
	/*Delete Last Element*/
	else if (_List->LastElement->Id == _IdElementToDelete)
	{
		t_EnnemyElement* ElementToDelete = _List->LastElement;
		if (_List->LastElement->PreviousElement != NULL)
		{
			_List->LastElement->PreviousElement->NextElement = NULL;
		}
		_List->LastElement = _List->LastElement->PreviousElement;
		free(ElementToDelete);
		printf("DELETE LAST ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}
	/*delete another element*/
	else
	{
		/*parcours dans la boucle pour trouver l'élément a supprimer*/
		t_EnnemyElement* CurrentElement = _List->FirstElement;
		while (CurrentElement != NULL)
		{
			/*si le prochain élément est celuis que l'on veut supprimer on attache le previous et le next avant de supprimer l'élément en question*/
			if (CurrentElement->Id == _IdElementToDelete)
			{
				t_EnnemyElement* ElementToDelete = CurrentElement;
				/*je raccorde le next element de l'élément précédent a l'élément suivant de celui que je veut supprimer*/
				if (CurrentElement->NextElement != NULL && CurrentElement->PreviousElement != NULL)
				{
					CurrentElement->PreviousElement->NextElement = CurrentElement->NextElement;
					CurrentElement->NextElement->PreviousElement = CurrentElement->PreviousElement;
				}
				free(ElementToDelete);

				printf("DELETE ELEMENT %d\n", _IdElementToDelete);
				return sfTrue;
			}
			else
			{
				CurrentElement = CurrentElement->NextElement;
			}
		}
	}

	printf("FAIL TO DELETE ELEMENT %d\n", _IdElementToDelete);
	return sfFalse;
}

sfBool DeleteElementByIdEnnemyBullet(t_ListEnnemyBullet* _List, int _IdElementToDelete)
{
	/*Delete de l'élément restant dans la liste*/
	if (_List->FirstElement == _List->LastElement)
	{
		t_EnnemyBulletElement* ElementToDelete = _List->FirstElement;

		/*je reset les 2 pointeurs de ma liste a NULL*/
		_List->FirstElement = NULL;
		_List->LastElement = NULL;

		free(ElementToDelete);
		printf("DELETE THE SURVIVOR ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}

	/*Delete First Element*/
	if (_List->FirstElement->Id == _IdElementToDelete)
	{

		t_EnnemyBulletElement* ElementToDelete = _List->FirstElement;
		if (_List->FirstElement->NextElement != NULL)
		{
			_List->FirstElement->NextElement->PreviousElement = NULL;
		}
		_List->FirstElement = _List->FirstElement->NextElement;

		free(ElementToDelete);
		printf("DELETE FIRST ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}
	/*Delete Last Element*/
	else if (_List->LastElement->Id == _IdElementToDelete)
	{
		t_EnnemyBulletElement* ElementToDelete = _List->LastElement;
		if (_List->LastElement->PreviousElement != NULL)
		{
			_List->LastElement->PreviousElement->NextElement = NULL;
		}
		_List->LastElement = _List->LastElement->PreviousElement;
		free(ElementToDelete);
		printf("DELETE LAST ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}
	/*delete another element*/
	else
	{
		/*parcours dans la boucle pour trouver l'élément a supprimer*/
		t_EnnemyBulletElement* CurrentElement = _List->FirstElement;
		while (CurrentElement != NULL)
		{
			/*si le prochain élément est celuis que l'on veut supprimer on attache le previous et le next avant de supprimer l'élément en question*/
			if (CurrentElement->Id == _IdElementToDelete)
			{
				t_EnnemyBulletElement* ElementToDelete = CurrentElement;
				/*je raccorde le next element de l'élément précédent a l'élément suivant de celui que je veut supprimer*/
				if (CurrentElement->NextElement != NULL && CurrentElement->PreviousElement != NULL)
				{
					CurrentElement->PreviousElement->NextElement = CurrentElement->NextElement;
					CurrentElement->NextElement->PreviousElement = CurrentElement->PreviousElement;
				}
				free(ElementToDelete);

				printf("DELETE ELEMENT %d\n", _IdElementToDelete);
				return sfTrue;
			}
			else
			{
				CurrentElement = CurrentElement->NextElement;
			}
		}
	}

	printf("FAIL TO DELETE ELEMENT %d\n", _IdElementToDelete);
	return sfFalse;
}

sfBool DeleteElementByIdEnnemyWave(t_ListEnnemyWave* _List, int _IdElementToDelete)
{
	/*Delete de l'élément restant dans la liste*/
	if (_List->FirstElement == _List->LastElement)
	{
		t_EnnemyWaveElement* ElementToDelete = _List->FirstElement;

		/*je reset les 2 pointeurs de ma liste a NULL*/
		_List->FirstElement = NULL;
		_List->LastElement = NULL;

		free(ElementToDelete);
		printf("DELETE THE SURVIVOR ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}

	/*Delete First Element*/
	if (_List->FirstElement->Id == _IdElementToDelete)
	{

		t_EnnemyWaveElement* ElementToDelete = _List->FirstElement;
		if (_List->FirstElement->NextElement != NULL)
		{
			_List->FirstElement->NextElement->PreviousElement = NULL;
		}
		_List->FirstElement = _List->FirstElement->NextElement;

		free(ElementToDelete);
		printf("DELETE FIRST ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}
	/*Delete Last Element*/
	else if (_List->LastElement->Id == _IdElementToDelete)
	{
		t_EnnemyWaveElement* ElementToDelete = _List->LastElement;
		if (_List->LastElement->PreviousElement != NULL)
		{
			_List->LastElement->PreviousElement->NextElement = NULL;
		}
		_List->LastElement = _List->LastElement->PreviousElement;
		free(ElementToDelete);
		printf("DELETE LAST ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}
	/*delete another element*/
	else
	{
		/*parcours dans la boucle pour trouver l'élément a supprimer*/
		t_EnnemyWaveElement* CurrentElement = _List->FirstElement;
		while (CurrentElement != NULL)
		{
			/*si le prochain élément est celuis que l'on veut supprimer on attache le previous et le next avant de supprimer l'élément en question*/
			if (CurrentElement->Id == _IdElementToDelete)
			{
				t_EnnemyWaveElement* ElementToDelete = CurrentElement;
				/*je raccorde le next element de l'élément précédent a l'élément suivant de celui que je veut supprimer*/
				if (CurrentElement->NextElement != NULL && CurrentElement->PreviousElement != NULL)
				{
					CurrentElement->PreviousElement->NextElement = CurrentElement->NextElement;
					CurrentElement->NextElement->PreviousElement = CurrentElement->PreviousElement;
				}
				free(ElementToDelete);

				printf("DELETE ELEMENT %d\n", _IdElementToDelete);
				return sfTrue;
			}
			else
			{
				CurrentElement = CurrentElement->NextElement;
			}
		}
	}

	printf("FAIL TO DELETE ELEMENT %d\n", _IdElementToDelete);
	return sfFalse;
}

sfBool DeleteElementByIdEnnemyPathPoint(t_ListEnnemyPathPoint* _List, int _IdElementToDelete)
{
	/*Delete de l'élément restant dans la liste*/
	if (_List->FirstElement == _List->LastElement)
	{
		t_EnnemyPathPointElement* ElementToDelete = _List->FirstElement;

		/*je reset les 2 pointeurs de ma liste a NULL*/
		_List->FirstElement = NULL;
		_List->LastElement = NULL;

		free(ElementToDelete);
		printf("DELETE THE SURVIVOR ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}

	/*Delete First Element*/
	if (_List->FirstElement->Id == _IdElementToDelete)
	{

		t_EnnemyPathPointElement* ElementToDelete = _List->FirstElement;
		if (_List->FirstElement->NextElement != NULL)
		{
			_List->FirstElement->NextElement->PreviousElement = NULL;
		}
		_List->FirstElement = _List->FirstElement->NextElement;

		free(ElementToDelete);
		printf("DELETE FIRST ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}
	/*Delete Last Element*/
	else if (_List->LastElement->Id == _IdElementToDelete)
	{
		t_EnnemyPathPointElement* ElementToDelete = _List->LastElement;
		if (_List->LastElement->PreviousElement != NULL)
		{
			_List->LastElement->PreviousElement->NextElement = NULL;
		}
		_List->LastElement = _List->LastElement->PreviousElement;
		free(ElementToDelete);
		printf("DELETE LAST ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}
	/*delete another element*/
	else
	{
		/*parcours dans la boucle pour trouver l'élément a supprimer*/
		t_EnnemyPathPointElement* CurrentElement = _List->FirstElement;
		while (CurrentElement != NULL)
		{
			/*si le prochain élément est celuis que l'on veut supprimer on attache le previous et le next avant de supprimer l'élément en question*/
			if (CurrentElement->Id == _IdElementToDelete)
			{
				t_EnnemyPathPointElement* ElementToDelete = CurrentElement;
				/*je raccorde le next element de l'élément précédent a l'élément suivant de celui que je veut supprimer*/
				if (CurrentElement->NextElement != NULL && CurrentElement->PreviousElement != NULL)
				{
					CurrentElement->PreviousElement->NextElement = CurrentElement->NextElement;
					CurrentElement->NextElement->PreviousElement = CurrentElement->PreviousElement;
				}
				free(ElementToDelete);

				printf("DELETE ELEMENT %d\n", _IdElementToDelete);
				return sfTrue;
			}
			else
			{
				CurrentElement = CurrentElement->NextElement;
			}
		}
	}

	printf("FAIL TO DELETE ELEMENT %d\n", _IdElementToDelete);
	return sfFalse;
}

sfBool DeleteElementByIdTowerSlot(t_ListTowerSlot* _List, int _IdElementToDelete)
{
	/*Delete de l'élément restant dans la liste*/
	if (_List->FirstElement == _List->LastElement)
	{
		t_TowerSlotElement* ElementToDelete = _List->FirstElement;

		/*je reset les 2 pointeurs de ma liste a NULL*/
		_List->FirstElement = NULL;
		_List->LastElement = NULL;

		free(ElementToDelete);
		printf("DELETE THE SURVIVOR ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}

	/*Delete First Element*/
	if (_List->FirstElement->Id == _IdElementToDelete)
	{

		t_TowerSlotElement* ElementToDelete = _List->FirstElement;
		if (_List->FirstElement->NextElement != NULL)
		{
			_List->FirstElement->NextElement->PreviousElement = NULL;
		}
		_List->FirstElement = _List->FirstElement->NextElement;

		free(ElementToDelete);
		printf("DELETE FIRST ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}
	/*Delete Last Element*/
	else if (_List->LastElement->Id == _IdElementToDelete)
	{
		t_TowerSlotElement* ElementToDelete = _List->LastElement;
		if (_List->LastElement->PreviousElement != NULL)
		{
			_List->LastElement->PreviousElement->NextElement = NULL;
		}
		_List->LastElement = _List->LastElement->PreviousElement;
		free(ElementToDelete);
		printf("DELETE LAST ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}
	/*delete another element*/
	else
	{
		/*parcours dans la boucle pour trouver l'élément a supprimer*/
		t_TowerSlotElement* CurrentElement = _List->FirstElement;
		while (CurrentElement != NULL)
		{
			/*si le prochain élément est celuis que l'on veut supprimer on attache le previous et le next avant de supprimer l'élément en question*/
			if (CurrentElement->Id == _IdElementToDelete)
			{
				t_TowerSlotElement* ElementToDelete = CurrentElement;
				/*je raccorde le next element de l'élément précédent a l'élément suivant de celui que je veut supprimer*/
				if (CurrentElement->NextElement != NULL && CurrentElement->PreviousElement != NULL)
				{
					CurrentElement->PreviousElement->NextElement = CurrentElement->NextElement;
					CurrentElement->NextElement->PreviousElement = CurrentElement->PreviousElement;
				}
				free(ElementToDelete);

				printf("DELETE ELEMENT %d\n", _IdElementToDelete);
				return sfTrue;
			}
			else
			{
				CurrentElement = CurrentElement->NextElement;
			}
		}
	}

	printf("FAIL TO DELETE ELEMENT %d\n", _IdElementToDelete);
	return sfFalse;
}

sfBool DeleteElementByIdTower(t_ListTower* _List, int _IdElementToDelete)
{
	/*Delete de l'élément restant dans la liste*/
	if (_List->FirstElement == _List->LastElement)
	{
		t_TowerElement* ElementToDelete = _List->FirstElement;

		/*je reset les 2 pointeurs de ma liste a NULL*/
		_List->FirstElement = NULL;
		_List->LastElement = NULL;

		free(ElementToDelete);
		printf("DELETE THE SURVIVOR ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}

	/*Delete First Element*/
	if (_List->FirstElement->Id == _IdElementToDelete)
	{

		t_TowerElement* ElementToDelete = _List->FirstElement;
		if (_List->FirstElement->NextElement != NULL)
		{
			_List->FirstElement->NextElement->PreviousElement = NULL;
		}
		_List->FirstElement = _List->FirstElement->NextElement;

		free(ElementToDelete);
		printf("DELETE FIRST ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}
	/*Delete Last Element*/
	else if (_List->LastElement->Id == _IdElementToDelete)
	{
		t_TowerElement* ElementToDelete = _List->LastElement;
		if (_List->LastElement->PreviousElement != NULL)
		{
			_List->LastElement->PreviousElement->NextElement = NULL;
		}
		_List->LastElement = _List->LastElement->PreviousElement;
		free(ElementToDelete);
		printf("DELETE LAST ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}
	/*delete another element*/
	else
	{
		/*parcours dans la boucle pour trouver l'élément a supprimer*/
		t_TowerElement* CurrentElement = _List->FirstElement;
		while (CurrentElement != NULL)
		{
			/*si le prochain élément est celuis que l'on veut supprimer on attache le previous et le next avant de supprimer l'élément en question*/
			if (CurrentElement->Id == _IdElementToDelete)
			{
				t_TowerElement* ElementToDelete = CurrentElement;
				/*je raccorde le next element de l'élément précédent a l'élément suivant de celui que je veut supprimer*/
				if (CurrentElement->NextElement != NULL && CurrentElement->PreviousElement != NULL)
				{
					CurrentElement->PreviousElement->NextElement = CurrentElement->NextElement;
					CurrentElement->NextElement->PreviousElement = CurrentElement->PreviousElement;
				}
				free(ElementToDelete);

				printf("DELETE ELEMENT %d\n", _IdElementToDelete);
				return sfTrue;
			}
			else
			{
				CurrentElement = CurrentElement->NextElement;
			}
		}
	}

	printf("FAIL TO DELETE ELEMENT %d\n", _IdElementToDelete);
	return sfFalse;
}

sfBool DeleteElementByIdBullet(t_ListBullet* _List, int _IdElementToDelete)
{
	/*Delete de l'élément restant dans la liste*/
	if (_List->FirstElement == _List->LastElement)
	{
		t_TowerBulletElement* ElementToDelete = _List->FirstElement;

		/*je reset les 2 pointeurs de ma liste a NULL*/
		_List->FirstElement = NULL;
		_List->LastElement = NULL;

		free(ElementToDelete);
		printf("DELETE THE SURVIVOR ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}

	/*Delete First Element*/
	if (_List->FirstElement->Id == _IdElementToDelete)
	{

		t_TowerBulletElement* ElementToDelete = _List->FirstElement;
		if (_List->FirstElement->NextElement != NULL)
		{
			_List->FirstElement->NextElement->PreviousElement = NULL;
		}
		_List->FirstElement = _List->FirstElement->NextElement;

		free(ElementToDelete);
		printf("DELETE FIRST ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}
	/*Delete Last Element*/
	else if (_List->LastElement->Id == _IdElementToDelete)
	{
		t_TowerBulletElement* ElementToDelete = _List->LastElement;
		if (_List->LastElement->PreviousElement != NULL)
		{
			_List->LastElement->PreviousElement->NextElement = NULL;
		}
		_List->LastElement = _List->LastElement->PreviousElement;
		free(ElementToDelete);
		printf("DELETE LAST ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}
	/*delete another element*/
	else
	{
		/*parcours dans la boucle pour trouver l'élément a supprimer*/
		t_TowerBulletElement* CurrentElement = _List->FirstElement;
		while (CurrentElement != NULL)
		{
			/*si le prochain élément est celuis que l'on veut supprimer on attache le previous et le next avant de supprimer l'élément en question*/
			if (CurrentElement->Id == _IdElementToDelete)
			{
				t_TowerBulletElement* ElementToDelete = CurrentElement;
				/*je raccorde le next element de l'élément précédent a l'élément suivant de celui que je veut supprimer*/
				if (CurrentElement->NextElement != NULL && CurrentElement->PreviousElement != NULL)
				{
					CurrentElement->PreviousElement->NextElement = CurrentElement->NextElement;
					CurrentElement->NextElement->PreviousElement = CurrentElement->PreviousElement;
				}
				free(ElementToDelete);

				printf("DELETE ELEMENT %d\n", _IdElementToDelete);
				return sfTrue;
			}
			else
			{
				CurrentElement = CurrentElement->NextElement;
			}
		}
	}

	printf("FAIL TO DELETE ELEMENT %d\n", _IdElementToDelete);
	return sfFalse;
}

sfBool DeleteElementByIdWhiteCell(t_ListWhiteCell* _List, int _IdElementToDelete)
{
	/*Delete de l'élément restant dans la liste*/
	if (_List->FirstElement == _List->LastElement)
	{
		t_whiteCellElement* ElementToDelete = _List->FirstElement;

		/*je reset les 2 pointeurs de ma liste a NULL*/
		_List->FirstElement = NULL;
		_List->LastElement = NULL;

		free(ElementToDelete);
		printf("DELETE THE SURVIVOR ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}

	/*Delete First Element*/
	if (_List->FirstElement->Id == _IdElementToDelete)
	{

		t_whiteCellElement* ElementToDelete = _List->FirstElement;
		if (_List->FirstElement->NextElement != NULL)
		{
			_List->FirstElement->NextElement->PreviousElement = NULL;
		}
		_List->FirstElement = _List->FirstElement->NextElement;

		free(ElementToDelete);
		printf("DELETE FIRST ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}
	/*Delete Last Element*/
	else if (_List->LastElement->Id == _IdElementToDelete)
	{
		t_whiteCellElement* ElementToDelete = _List->LastElement;
		if (_List->LastElement->PreviousElement != NULL)
		{
			_List->LastElement->PreviousElement->NextElement = NULL;
		}
		_List->LastElement = _List->LastElement->PreviousElement;
		free(ElementToDelete);
		printf("DELETE LAST ELEMENT %d\n", _IdElementToDelete);

		return sfTrue;
	}
	/*delete another element*/
	else
	{
		/*parcours dans la boucle pour trouver l'élément a supprimer*/
		t_whiteCellElement* CurrentElement = _List->FirstElement;
		while (CurrentElement != NULL)
		{
			/*si le prochain élément est celuis que l'on veut supprimer on attache le previous et le next avant de supprimer l'élément en question*/
			if (CurrentElement->Id == _IdElementToDelete)
			{
				t_whiteCellElement* ElementToDelete = CurrentElement;
				/*je raccorde le next element de l'élément précédent a l'élément suivant de celui que je veut supprimer*/
				if (CurrentElement->NextElement != NULL && CurrentElement->PreviousElement != NULL)
				{
					CurrentElement->PreviousElement->NextElement = CurrentElement->NextElement;
					CurrentElement->NextElement->PreviousElement = CurrentElement->PreviousElement;
				}
				free(ElementToDelete);

				printf("DELETE ELEMENT %d\n", _IdElementToDelete);
				return sfTrue;
			}
			else
			{
				CurrentElement = CurrentElement->NextElement;
			}
		}
	}

	printf("FAIL TO DELETE ELEMENT %d\n", _IdElementToDelete);
	return sfFalse;
}


/*détruire tous les éléments d'une liste sans détruire la liste*/

sfBool DeleteAllElementInList(t_List* _List)
{
	t_EnnemyElement* CurrentElement = _List->FirstElement;
	while (CurrentElement != NULL)
	{
		if (CurrentElement != NULL)
		{
			if (CurrentElement->NextElement != NULL)
			{
				CurrentElement = CurrentElement->NextElement;
				DeleteElementById(_List, CurrentElement->PreviousElement->Id);
			}
			else
			{
				DeleteElementById(_List, CurrentElement->Id);
				printf("THE LAST ELEMENT OF THE LIST HAVE BEEN DELETED\n");
				return sfTrue;
			}
		}
		else
			CurrentElement = CurrentElement->NextElement;
	}

	printf("FAIL TO DELETE ALL THE LIST\n");
	return sfFalse;
}

sfBool DeleteAllElementInListEnnemyBullet(t_ListEnnemyBullet* _List)
{

	t_EnnemyBulletElement* CurrentElement = _List->FirstElement;
	while (CurrentElement != NULL)
	{
		if (CurrentElement != NULL)
		{
			if (CurrentElement->NextElement != NULL)
			{
				CurrentElement = CurrentElement->NextElement;
				DeleteElementById(_List, CurrentElement->PreviousElement->Id);
			}
			else
			{
				DeleteElementById(_List, CurrentElement->Id);
				printf("THE LAST ELEMENT OF THE LIST HAVE BEEN DELETED\n");
				return sfTrue;
			}
		}
		else
			CurrentElement = CurrentElement->NextElement;
	}

	printf("FAIL TO DELETE ALL THE LIST\n");
	return sfFalse;
}

sfBool DeleteAllElementInListEnnemyWave(t_ListEnnemyWave* _List)
{

	t_EnnemyWaveElement* CurrentElement = _List->FirstElement;
	while (CurrentElement != NULL)
	{
		if (CurrentElement != NULL)
		{
			if (CurrentElement->NextElement != NULL)
			{
				CurrentElement = CurrentElement->NextElement;
				DeleteElementById(_List, CurrentElement->PreviousElement->Id);
			}
			else
			{
				DeleteElementById(_List, CurrentElement->Id);
				printf("THE LAST ELEMENT OF THE LIST HAVE BEEN DELETED\n");
				return sfTrue;
			}
		}
		else
			CurrentElement = CurrentElement->NextElement;
	}

	printf("FAIL TO DELETE ALL THE LIST\n");
	return sfFalse;
}

sfBool DeleteAllElementInListEnnemyPathPoint(t_ListEnnemyPathPoint* _List)
{

	t_EnnemyPathPointElement* CurrentElement = _List->FirstElement;
	while (CurrentElement != NULL)
	{
		if (CurrentElement != NULL)
		{
			if (CurrentElement->NextElement != NULL)
			{
				CurrentElement = CurrentElement->NextElement;
				DeleteElementById(_List, CurrentElement->PreviousElement->Id);
			}
			else
			{
				DeleteElementById(_List, CurrentElement->Id);
				printf("THE LAST ELEMENT OF THE LIST HAVE BEEN DELETED\n");
				return sfTrue;
			}
		}
		else
			CurrentElement = CurrentElement->NextElement;
	}

	printf("FAIL TO DELETE ALL THE LIST\n");
	return sfFalse;
}

sfBool DeleteAllElementInListTowerSlot(t_ListTowerSlot* _List)
{

	t_TowerSlotElement* CurrentElement = _List->FirstElement;
	while (CurrentElement != NULL)
	{
		if (CurrentElement != NULL)
		{
			if (CurrentElement->NextElement != NULL)
			{
				CurrentElement = CurrentElement->NextElement;
				DeleteElementById(_List, CurrentElement->PreviousElement->Id);
			}
			else
			{
				DeleteElementById(_List, CurrentElement->Id);
				printf("THE LAST ELEMENT OF THE LIST HAVE BEEN DELETED\n");
				return sfTrue;
			}
		}
		else
			CurrentElement = CurrentElement->NextElement;
	}

	printf("FAIL TO DELETE ALL THE LIST\n");
	return sfFalse;
}

sfBool DeleteAllElementInListTower(t_ListTower* _List)
{

	t_TowerElement* CurrentElement = _List->FirstElement;
	while (CurrentElement != NULL)
	{
		if (CurrentElement != NULL)
		{
			if (CurrentElement->NextElement != NULL)
			{
				CurrentElement = CurrentElement->NextElement;
				DeleteElementById(_List, CurrentElement->PreviousElement->Id);
			}
			else
			{
				DeleteElementById(_List, CurrentElement->Id);
				printf("THE LAST ELEMENT OF THE LIST HAVE BEEN DELETED\n");
				return sfTrue;
			}
		}
		else
			CurrentElement = CurrentElement->NextElement;
	}

	printf("FAIL TO DELETE ALL THE LIST\n");
	return sfFalse;
}

sfBool DeleteAllElementInListTowerBullet(t_ListBullet* _List)
{

	t_TowerBulletElement* CurrentElement = _List->FirstElement;
	while (CurrentElement != NULL)
	{
		if (CurrentElement != NULL)
		{
			if (CurrentElement->NextElement != NULL)
			{
				CurrentElement = CurrentElement->NextElement;
				DeleteElementById(_List, CurrentElement->PreviousElement->Id);
			}
			else
			{
				DeleteElementById(_List, CurrentElement->Id);
				printf("THE LAST ELEMENT OF THE LIST HAVE BEEN DELETED\n");
				return sfTrue;
			}
		}
		else
			CurrentElement = CurrentElement->NextElement;
	}

	printf("FAIL TO DELETE ALL THE LIST\n");
	return sfFalse;
}

sfBool DeleteAllElementInListWhiteCell(t_ListWhiteCell* _List)
{

	t_whiteCellElement* CurrentElement = _List->FirstElement;
	while (CurrentElement != NULL)
	{
		if (CurrentElement != NULL)
		{
			if (CurrentElement->NextElement != NULL)
			{
				CurrentElement = CurrentElement->NextElement;
				DeleteElementById(_List, CurrentElement->PreviousElement->Id);
			}
			else
			{
				DeleteElementById(_List, CurrentElement->Id);
				printf("THE LAST ELEMENT OF THE LIST HAVE BEEN DELETED\n");
				return sfTrue;
			}
		}
		else
			CurrentElement = CurrentElement->NextElement;
	}

	printf("FAIL TO DELETE ALL THE LIST\n");
	return sfFalse;
}

sfBool SortTowerByPos(t_ListTower *_list)
{
	t_TowerElement *currentElement = _list->FirstElement;
	t_TowerElement *tempElement;
	sfBool listSorted = sfTrue;

	if (currentElement->NextElement->Tower->vPos.y < _list->FirstElement->Tower->vPos.y)
	{
		tempElement = _list->FirstElement;

		_list->FirstElement = currentElement->NextElement;
		tempElement->NextElement = _list->FirstElement->NextElement;
		_list->FirstElement->NextElement = tempElement;
		listSorted = sfFalse;

		currentElement = _list->FirstElement;
	}

	while (currentElement->NextElement != NULL && currentElement->NextElement->NextElement != NULL)
	{
		if (currentElement->NextElement->NextElement->Tower->vPos.y < currentElement->NextElement->Tower->vPos.y)
		{
			tempElement = currentElement->NextElement;

			currentElement->NextElement = tempElement->NextElement;
			tempElement->NextElement = tempElement->NextElement->NextElement;
			currentElement->NextElement->NextElement = tempElement;
			listSorted = sfFalse;
		}

		currentElement = currentElement->NextElement;
	}

	return listSorted;
}

sfBool SortEnnemyByPos(t_List *_list)
{
	t_EnnemyElement *currentElement = _list->FirstElement;
	t_EnnemyElement *tempElement;
	sfBool listSorted = sfTrue;

	if (currentElement->NextElement->Ennemy->vCurrentPosition.y < _list->FirstElement->Ennemy->vCurrentPosition.y)
	{
		tempElement = _list->FirstElement;

		_list->FirstElement = currentElement->NextElement;
		tempElement->NextElement = _list->FirstElement->NextElement;
		_list->FirstElement->NextElement = tempElement;
		listSorted = sfFalse;

		currentElement = _list->FirstElement;
	}

	while (currentElement->NextElement != NULL && currentElement->NextElement->NextElement != NULL)
	{
		if (currentElement->NextElement->NextElement->Ennemy->vCurrentPosition.y < currentElement->NextElement->Ennemy->vCurrentPosition.y)
		{
			tempElement = currentElement->NextElement;

			currentElement->NextElement = tempElement->NextElement;
			tempElement->NextElement = tempElement->NextElement->NextElement;
			currentElement->NextElement->NextElement = tempElement;
			listSorted = sfFalse;
		}

		currentElement = currentElement->NextElement;
	}

	return listSorted;
}

sfBool DeleteEntityWithID(t_ListTower*_list, int _id)
{
	t_TowerElement *currentElement = _list->FirstElement;
	if (currentElement->Id == _id)
	{
		t_TowerElement *deletedElement = currentElement;
		_list->FirstElement = currentElement->NextElement;

		free(deletedElement);
		//printf("Bullet with id %d has been deleted\n", _id);
		return sfTrue;
	}
	else
	{
		while (currentElement->NextElement != NULL)
		{
			if (currentElement->NextElement->Id == _id)
			{
				t_TowerElement *deletedElement = currentElement->NextElement;
				if (currentElement->NextElement != NULL)
					currentElement->NextElement = currentElement->NextElement->NextElement;

				free(deletedElement);
				printf("Bullet with id %d has been deleted\n", _id);
				return sfTrue;
			}
			else
			{
				currentElement = currentElement->NextElement;
			}
		}
	}
	printf("Unable to delete Bullet with id %d\n", _id);
	return sfFalse;
}

sfBool DeleteEnemyWithID(t_List*_list, int _id)
{
	t_EnnemyElement *currentElement = _list->FirstElement;
	if (currentElement->Id == _id)
	{
		t_EnnemyElement *deletedElement = currentElement;
		_list->FirstElement = currentElement->NextElement;

		free(deletedElement);
		//printf("Bullet with id %d has been deleted\n", _id);
		return sfTrue;
	}
	else
	{
		while (currentElement->NextElement != NULL)
		{
			if (currentElement->NextElement->Id == _id)
			{
				t_EnnemyElement *deletedElement = currentElement->NextElement;
				if (currentElement->NextElement != NULL)
					currentElement->NextElement = currentElement->NextElement->NextElement;

				free(deletedElement);
				printf("enemy %d has been deleted\n", _id);
				return sfTrue;
			}
			else
			{
				currentElement = currentElement->NextElement;
			}
		}
	}
	printf("Unable to delete enemy %d\n", _id);
	return sfFalse;
}
#pragma endregion LIST FUNCTIONS

#pragma region FORCES

sfVector2f GetDirectionFromAngleDegrees(float _angleDegrees)
{
	return GetDirectionFromAngleRadians(DegToRad(_angleDegrees));
}

sfVector2f GetDirectionFromAngleRadians(double _angleRadians)
{
	//printf("Angle = %.2f - Radians = %.2f\n", _angleDegree, angleRadians);
	sfVector2f direction;

	direction.x = cos(_angleRadians);
	direction.y = sin(_angleRadians);

	//printf("Direction : %.2f, %.2f\n", direction.x, direction.y);
	return direction;
}

float GetAngleRadiansBetweenPoints(sfVector2f _pointA, sfVector2f _pointB)
{
	return atan2(_pointB.y - _pointA.y, _pointB.x - _pointA.x);
}

float GetAngleRadiansBetweenPointAndMouse(sfVector2f _pointA, sfVector2i _pointB)
{
	return atan2(_pointB.y - _pointA.y, _pointB.x - _pointA.x);
}

float GetAngleRadiansFromVector(sfVector2f _vector)
{
	return atan2(_vector.y, _vector.x);
}

float GetAngleDegreeFromVector(sfVector2f _vector)
{
	float angleRadians = atan2(_vector.y, _vector.x);

	return RadToDeg(angleRadians);
}

double DegToRad(float _degrees)
{
	return (_degrees * PI) / 180;
}

float RadToDeg(double _radians)
{
	return _radians * (180 / PI);
}

sfVector2f Normalize(sfVector2f _vector)
{
	double length = Magnitude(_vector);
	//printf("Magnitude = %f\n", length);

	sfVector2f newVector;
	newVector.x = _vector.x / length;
	newVector.y = _vector.y / length;
	//printf("Vector normalized, x = %f, y = %f\n", newVector.x, newVector.y);

	return newVector;
}

float Magnitude(sfVector2f _vector)
{
	return sqrt(_vector.x*_vector.x + _vector.y*_vector.y);
}

sfVector2f Truncate(sfVector2f _vector, float _max)
{
	if (Magnitude(_vector) > _max)
	{
		_vector = Normalize(_vector);

		_vector.x *= _max;
		_vector.y *= _max;
	}
	return _vector;
}

#pragma endregion FORCES

sfVector2f normalizeVector(sfVector2f _vector)
{
	double length = Magnitude(_vector);
	sfVector2f newVector;
	newVector.x = _vector.x / length;
	newVector.y = _vector.y / length;

	return newVector;
}

/*renvoie true si l'entité est en collision*/
/*renvoie true si l'entité est en collision*/
sfBool manageEnnemi(t_EnnemyElement* currentElement, sfImage* testMask, float fTimeSinceLastFrame)
{
	currentElement->Ennemy->fTimeCurrentVertex = (float)clock() / CLOCKS_PER_SEC;
	currentElement->Ennemy->fTimeSinceVertex = currentElement->Ennemy->fTimeCurrentVertex - currentElement->Ennemy->fTimeStartVertex;
	currentElement->Ennemy->vNormalizeDirection = normalizeVector(currentElement->Ennemy->vCurrentDirection);
	currentElement->Ennemy->vControlPoint.x = currentElement->Ennemy->vNormalizeDirection.x  * (currentElement->Ennemy->fControlRadius / 2);
	currentElement->Ennemy->vControlPoint.y = currentElement->Ennemy->vNormalizeDirection.y * (currentElement->Ennemy->fControlRadius / 2);
	currentElement->Ennemy->vControlPoint.x += currentElement->Ennemy->vCurrentPosition.x;
	currentElement->Ennemy->vControlPoint.y += currentElement->Ennemy->vCurrentPosition.y;
	/*currentElement->Ennemy->fAngleSprite = GetAngleDegreeFromVector(currentElement->Ennemy->vCurrentDirection);*/

	/*je cherche mes points par rapport a l'angle de direction au lieu de l'angle du sprite*/
	currentElement->Ennemy->vLeftStartPoint.x = currentElement->Ennemy->vCurrentPosition.x - ((currentElement->Ennemy->fGuardRadius + 5) * sin(DegToRad(-currentElement->Ennemy->fCurrentAngleDirection)));
	currentElement->Ennemy->vLeftStartPoint.y = currentElement->Ennemy->vCurrentPosition.y - ((currentElement->Ennemy->fGuardRadius + 5) * cos(DegToRad(-currentElement->Ennemy->fCurrentAngleDirection)));

	currentElement->Ennemy->vRightStartPoint.x = currentElement->Ennemy->vCurrentPosition.x + (currentElement->Ennemy->fGuardRadius + 5) * sin(DegToRad(-currentElement->Ennemy->fCurrentAngleDirection));
	currentElement->Ennemy->vRightStartPoint.y = currentElement->Ennemy->vCurrentPosition.y + (currentElement->Ennemy->fGuardRadius + 5) * cos(DegToRad(-currentElement->Ennemy->fCurrentAngleDirection));

	/*exemple pour calculer les points devant*/ //(a garder au cas ou)
	currentElement->Ennemy->vRightControlPoint.x = currentElement->Ennemy->vNormalizeDirection.x  * (currentElement->Ennemy->fControlRadius / 3);
	currentElement->Ennemy->vRightControlPoint.y = currentElement->Ennemy->vNormalizeDirection.y * (currentElement->Ennemy->fControlRadius / 3);
	currentElement->Ennemy->vRightControlPoint.x += currentElement->Ennemy->vRightStartPoint.x;
	currentElement->Ennemy->vRightControlPoint.y += currentElement->Ennemy->vRightStartPoint.y;

	currentElement->Ennemy->vLeftControlPoint.x = currentElement->Ennemy->vNormalizeDirection.x  * (currentElement->Ennemy->fControlRadius / 3);
	currentElement->Ennemy->vLeftControlPoint.y = currentElement->Ennemy->vNormalizeDirection.y * (currentElement->Ennemy->fControlRadius / 3);
	currentElement->Ennemy->vLeftControlPoint.x += currentElement->Ennemy->vLeftStartPoint.x;
	currentElement->Ennemy->vLeftControlPoint.y += currentElement->Ennemy->vLeftStartPoint.y;

	//currentElement->Ennemy->vSideLeftControlPoint.x = currentElement->Ennemy->vNormalizeDirection.x - ((CONTROL_RADIUS / 3) * sin(DegToRad(-currentElement->Ennemy->fAngleSprite)));
	//currentElement->Ennemy->vSideLeftControlPoint.y = currentElement->Ennemy->vNormalizeDirection.y - ((CONTROL_RADIUS / 3) * cos(DegToRad(-currentElement->Ennemy->fAngleSprite)));
	//currentElement->Ennemy->vSideLeftControlPoint.x += currentElement->Ennemy->vLeftStartPoint.x;
	//currentElement->Ennemy->vSideLeftControlPoint.y += currentElement->Ennemy->vLeftStartPoint.y;

	//currentElement->Ennemy->vSideRightControlPoint.x = currentElement->Ennemy->vNormalizeDirection.x + ((CONTROL_RADIUS / 3)* sin(DegToRad(-currentElement->Ennemy->fAngleSprite)));
	//currentElement->Ennemy->vSideRightControlPoint.y = currentElement->Ennemy->vNormalizeDirection.y + ((CONTROL_RADIUS / 3)* cos(DegToRad(-currentElement->Ennemy->fAngleSprite)));
	//currentElement->Ennemy->vSideRightControlPoint.x += currentElement->Ennemy->vRightStartPoint.x;
	//currentElement->Ennemy->vSideRightControlPoint.y += currentElement->Ennemy->vRightStartPoint.y;

	

	/*POINT SITUE DEVANT L'ENTITE*/
	if (currentElement->Ennemy->vControlPoint.x > 0 && currentElement->Ennemy->vControlPoint.x < WINDOW_WIDTH
		&& currentElement->Ennemy->vControlPoint.y > 0 && currentElement->Ennemy->vControlPoint.y < WINDOW_HEIGHT)
	{
		if (sfImage_getPixel(testMask, currentElement->Ennemy->vControlPoint.x, currentElement->Ennemy->vControlPoint.y).r == 255 && sfImage_getPixel(testMask, currentElement->Ennemy->vControlPoint.x, currentElement->Ennemy->vControlPoint.y).g == 0
			&& sfImage_getPixel(testMask, currentElement->Ennemy->vControlPoint.x, currentElement->Ennemy->vControlPoint.y).b == 0 && sfImage_getPixel(testMask, currentElement->Ennemy->vControlPoint.x, currentElement->Ennemy->vControlPoint.y).a == 255)
		{
			//printf("COLLISION CENTRALE\n");
			currentElement->Ennemy->iCollideControl = 1;
		}
		else
		{
			currentElement->Ennemy->iCollideControl = 0;
		}
	}
	

	/*POINT SITUE SUR LA GAUCHE DE L'ENTITE*/
	if (currentElement->Ennemy->vLeftControlPoint.x > 0 && currentElement->Ennemy->vLeftControlPoint.x < WINDOW_WIDTH
		&& currentElement->Ennemy->vLeftControlPoint.y > 0 && currentElement->Ennemy->vLeftControlPoint.y < WINDOW_HEIGHT)
	{
		if (sfImage_getPixel(testMask, currentElement->Ennemy->vLeftControlPoint.x, currentElement->Ennemy->vLeftControlPoint.y).r == 255 && sfImage_getPixel(testMask, currentElement->Ennemy->vLeftControlPoint.x, currentElement->Ennemy->vLeftControlPoint.y).g == 0
			&& sfImage_getPixel(testMask, currentElement->Ennemy->vLeftControlPoint.x, currentElement->Ennemy->vLeftControlPoint.y).b == 0 && sfImage_getPixel(testMask, currentElement->Ennemy->vLeftControlPoint.x, currentElement->Ennemy->vLeftControlPoint.y).a == 255)
		{
			//printf("COLLISION GAUCHE\n");
			currentElement->Ennemy->iCollideControlLeft = 1;
		}
		else
		{
			currentElement->Ennemy->iCollideControlLeft = 0;
		}
	}

	/*POINT SITUE SUR LA DROITE DE L'ENTITE*/
	if (currentElement->Ennemy->vRightControlPoint.x > 0 && currentElement->Ennemy->vRightControlPoint.x < WINDOW_WIDTH
		&& currentElement->Ennemy->vRightControlPoint.y > 0 && currentElement->Ennemy->vRightControlPoint.y < WINDOW_HEIGHT)
	{

		if (sfImage_getPixel(testMask, currentElement->Ennemy->vRightControlPoint.x, currentElement->Ennemy->vRightControlPoint.y).r == 255 && sfImage_getPixel(testMask, currentElement->Ennemy->vRightControlPoint.x, currentElement->Ennemy->vRightControlPoint.y).g == 0
			&& sfImage_getPixel(testMask, currentElement->Ennemy->vRightControlPoint.x, currentElement->Ennemy->vRightControlPoint.y).b == 0 && sfImage_getPixel(testMask, currentElement->Ennemy->vRightControlPoint.x, currentElement->Ennemy->vRightControlPoint.y).a == 255)
		{
			//printf("COLLISION DROITE\n");
			currentElement->Ennemy->iCollideControlRight = 1;
		}
		else
		{
			currentElement->Ennemy->iCollideControlRight = 0;
		}
	}

	///*POINT D'INCREMENTATION A GAUCHE DE L'ENTITE*/
	//if (currentElement->Ennemy->vSideLeftControlPoint.x > 0 && currentElement->Ennemy->vSideLeftControlPoint.x < WINDOW_WIDTH
	//	&& currentElement->Ennemy->vSideLeftControlPoint.y > 0 && currentElement->Ennemy->vSideLeftControlPoint.y < WINDOW_HEIGHT)
	//{

	//	if (sfImage_getPixel(testMask, currentElement->Ennemy->vSideLeftControlPoint.x, currentElement->Ennemy->vSideLeftControlPoint.y).r == 255 && sfImage_getPixel(testMask, currentElement->Ennemy->vSideLeftControlPoint.x, currentElement->Ennemy->vSideLeftControlPoint.y).g == 0
	//		&& sfImage_getPixel(testMask, currentElement->Ennemy->vSideLeftControlPoint.x, currentElement->Ennemy->vSideLeftControlPoint.y).b == 0 && sfImage_getPixel(testMask, currentElement->Ennemy->vSideLeftControlPoint.x, currentElement->Ennemy->vSideLeftControlPoint.y).a == 255)
	//	{
	//		//printf("COLLISION DROITE\n");
	//		currentElement->Ennemy->iCollideControlSideLeft = 1;
	//	}
	//	else
	//	{
	//		currentElement->Ennemy->iCollideControlSideLeft = 0;
	//	}
	//}

	///*POINT D'INCREMENTATION A DROITE DE L'ENTITE*/
	//if (currentElement->Ennemy->vSideRightControlPoint.x > 0 && currentElement->Ennemy->vSideRightControlPoint.x < WINDOW_WIDTH
	//	&& currentElement->Ennemy->vSideRightControlPoint.y > 0 && currentElement->Ennemy->vSideRightControlPoint.y < WINDOW_HEIGHT)
	//{

	//	if (sfImage_getPixel(testMask, currentElement->Ennemy->vSideRightControlPoint.x, currentElement->Ennemy->vSideRightControlPoint.y).r == 255 && sfImage_getPixel(testMask, currentElement->Ennemy->vSideRightControlPoint.x, currentElement->Ennemy->vSideRightControlPoint.y).g == 0
	//		&& sfImage_getPixel(testMask, currentElement->Ennemy->vSideRightControlPoint.x, currentElement->Ennemy->vSideRightControlPoint.y).b == 0 && sfImage_getPixel(testMask, currentElement->Ennemy->vSideRightControlPoint.x, currentElement->Ennemy->vSideRightControlPoint.y).a == 255)
	//	{
	//		//printf("COLLISION DROITE\n");
	//		currentElement->Ennemy->iCollideControlSideRight = 1;
	//	}
	//	else
	//	{
	//		currentElement->Ennemy->iCollideControlSideRight = 0;
	//	}
	//}

	/*attention cette variable*/
	if (currentElement->Ennemy->iCollideControlRight == sfTrue || currentElement->Ennemy->iCollideControlLeft == sfTrue || currentElement->Ennemy->iCollideControl == sfTrue)
	{
		currentElement->Ennemy->iIsColliding = 1;
		return sfTrue;
	}
	else
	{
		currentElement->Ennemy->iIsColliding = 0;
		return sfFalse;
	}
	if (!(currentElement->Ennemy->vControlPoint.x > 0 && currentElement->Ennemy->vControlPoint.x < WINDOW_WIDTH
		&& currentElement->Ennemy->vControlPoint.y > 0 && currentElement->Ennemy->vControlPoint.y < WINDOW_HEIGHT))
	{
		currentElement->Ennemy->iIsColliding = 0;
		return sfFalse;
	}

}

sfVertexArray* GetLine(sfVector2f _startPoint, sfVector2f _direction, sfColor _Color)
{
	/*Vertex Array Creation*/
	sfVertexArray *vertexArray = sfVertexArray_create();
	sfVertexArray_setPrimitiveType(vertexArray, sfLines);

	/*Vertex Creation*/
	sfVertex *newVertex = malloc(sizeof(sfVertex));

	/*set the color*/
	newVertex->color = _Color;

	/*set the first vertex*/
	newVertex->position = _startPoint;

	/*add the vertex to the vertex array*/
	sfVertexArray_append(vertexArray, *newVertex);

	/*set the second vertex*/
	newVertex->position.x = _startPoint.x + _direction.x;
	newVertex->position.y = _startPoint.y + _direction.y;

	/*add the second vertex to the array*/
	sfVertexArray_append(vertexArray, *newVertex);

	return vertexArray;
}

void SetLineBetweenPoints(sfVertexArray* _vertexArray, sfVertex* _vertex, sfVector2f _startPoint, sfVector2f _destPoint, sfColor _color)
{
	// Vertex array creation
	sfVertexArray_clear(_vertexArray);
	sfVertexArray_setPrimitiveType(_vertexArray, sfLines);
	// Set the vertex color
	_vertex->color = _color;
	// Set the first vertex position
	_vertex->position = _startPoint;
	// Add the vertex to the vertex array
	sfVertexArray_append(_vertexArray, *_vertex);
	// Set the second vertex position
	_vertex->position = _destPoint;
	// Add the second vertex to the array
	sfVertexArray_append(_vertexArray, *_vertex);
}


