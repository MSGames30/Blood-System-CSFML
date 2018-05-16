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
	t_EnnemyElement* NewEnnemy = NULL;

	t_ListTowerSlot* ListTowerSlot = malloc(sizeof(t_List));
	ListTowerSlot->FirstElement = NULL;
	ListTowerSlot->LastElement = NULL;
	t_TowerSlotElement* CurrentTowerSlot = NULL;
	t_TowerSlotElement* NewTowerSlot = NULL;
	t_TowerSlotElement* ActualTowerSlot = NULL;

	t_ListTower* ListTower = malloc(sizeof(t_List));
	ListTower->FirstElement = NULL;
	ListTower->LastElement = NULL;
	t_TowerElement* CurrentTower = NULL;
	t_TowerElement* NewTower = NULL;
	t_TowerElement* ActualTower = NULL;

	t_ListBullet* ListTowerBullet = malloc(sizeof(t_List));
	ListTowerBullet->FirstElement = NULL;
	ListTowerBullet->LastElement = NULL;
	t_TowerBulletElement* CurrentTowerBullet = NULL;
	t_TowerBulletElement* NewTowerBullet = NULL;

#pragma endregion LIST

#pragma region SOUND

#pragma endregion SOUND

#pragma region VARIABLES

	sfBool isMousePressed = sfFalse;
	sfBool isWindowActive = sfTrue;
	sfBool isInBuildChoice = sfFalse;
	sfBool isBuildedChoice = sfFalse;
	sfBool isMoving = sfFalse;
	sfBool isOpened = sfFalse;
	sfBool isBuildedOpened = sfFalse;

	#pragma region VARIABLES DE TOUCHES

	sfBool SpaceButtonIsButtonPressed = sfFalse;

	int iSpaceButtonIsButtonPressedCheck = 0;

	#pragma endregion VARIABLES DE TOUCHES

	#pragma region C VARS
	int iCurrentLevel = 2;
	int iDebug = 0;
	#pragma endregion C VARS

	#pragma region CSFML VARS
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
	window = sfRenderWindow_create(Mode, "Tower Defense", /*sfResize | sfClose*/sfFullscreen, NULL);
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

	sfSprite* Sp_Map2 = createSprite("resources/textures/level design niveau 2.jpg");
	sfSprite* Sp_MapMask2 = createSprite("resources/textures/Mask Collision Map 2.jpg");
	sfImage* Image_Map2 = sfImage_createFromFile("resources/textures/level design niveau 2.psd");

#pragma endregion CREATE SPRITES

	sfColor Color_Blue = sfColor_fromRGB(0, 0, 255);
	sfColor Color_Green = sfColor_fromRGB(0, 255, 0);

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
		timeSinceLastFrame = currentTime - lastFrameTime; // temps depuis la dernière frame
#pragma endregion TIME CONTROL

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

#pragma region ADD ENNEMY //GUILLAUME

		if (SpaceButtonIsButtonPressed == sfTrue && iSpaceButtonIsButtonPressedCheck == 0)
		{

			iDebug++;
			if (iDebug > 3)
			{
				//printf("debug");
			}
			NewEnnemy = AddElementBeginList(ListEnnemy);
			NewEnnemy->Ennemy = malloc(sizeof(t_Ennemy));
			/*GESTION EN FONCTION DU TYPE*/

#pragma region GESTION EN FONCTION DU TYPE //GUILLAUME

			NewEnnemy->Ennemy->Type = rand() % 3 + 1;
			printf("%d\n", NewEnnemy->Ennemy->Type);
			if (NewEnnemy->Ennemy->Type == 1)
			{
				NewEnnemy->Ennemy->sp_Ennemy = createSprite("resources/textures/ennemi 1.png");
				NewEnnemy->Ennemy->Deg = 0;
				NewEnnemy->Ennemy->Hp = 0;
				NewEnnemy->Ennemy->HpMax = 0;
				NewEnnemy->Ennemy->iMoneyValue = 0;
			}
			else if (NewEnnemy->Ennemy->Type == 2)
			{
				NewEnnemy->Ennemy->sp_Ennemy = createSprite("resources/textures/ennemi 2.png");
				NewEnnemy->Ennemy->Deg = 0;
				NewEnnemy->Ennemy->Hp = 0;
				NewEnnemy->Ennemy->HpMax = 0;
				NewEnnemy->Ennemy->iMoneyValue = 0;
			}
			else if (NewEnnemy->Ennemy->Type == 3)
			{
				NewEnnemy->Ennemy->sp_Ennemy = createSprite("resources/textures/ennemi 3.png");
				NewEnnemy->Ennemy->Deg = 0;
				NewEnnemy->Ennemy->Hp = 0;
				NewEnnemy->Ennemy->HpMax = 0;
				NewEnnemy->Ennemy->iMoneyValue = 0;
			}
			NewEnnemy->Ennemy->vOrigin.x = sfSprite_getGlobalBounds(NewEnnemy->Ennemy->sp_Ennemy).width / 2;
			NewEnnemy->Ennemy->vOrigin.y = sfSprite_getGlobalBounds(NewEnnemy->Ennemy->sp_Ennemy).height / 2;
			sfSprite_setOrigin(NewEnnemy->Ennemy->sp_Ennemy, NewEnnemy->Ennemy->vOrigin);

#pragma endregion GESTION EN FONCTION DU TYPE ENNEMIE //GUILLAUME

#pragma region GESTION SPAWN //GUILLAUME

			NewEnnemy->Ennemy->iRandSpawnValueVariation = rand() % ENNEMY_VARIANT_SPAWN + 0;
			NewEnnemy->Ennemy->iStartPos = rand() % 2 + 1;
			if (NewEnnemy->Ennemy->iStartPos == 1)
			{
				/*gestion x*/
				NewEnnemy->Ennemy->iRandSpawnDirectionVariation = rand() % 2 + 1;
				if (NewEnnemy->Ennemy->iRandSpawnDirectionVariation == 1)
				{
					NewEnnemy->Ennemy->vCurrentPosition.x = 70 + ENNEMY_VARIANT_SPAWN;
				}
				else if (NewEnnemy->Ennemy->iRandSpawnDirectionVariation == 2)
				{
					NewEnnemy->Ennemy->vCurrentPosition.x = 70 - ENNEMY_VARIANT_SPAWN;
				}

				/*gestion y*/
				NewEnnemy->Ennemy->iRandSpawnDirectionVariation = rand() % 2 + 1;
				if (NewEnnemy->Ennemy->iRandSpawnDirectionVariation == 1)
				{
					NewEnnemy->Ennemy->vCurrentPosition.y = 1035 + ENNEMY_VARIANT_SPAWN;
				}
				else if (NewEnnemy->Ennemy->iRandSpawnDirectionVariation == 2)
				{
					NewEnnemy->Ennemy->vCurrentPosition.y = 1035 - ENNEMY_VARIANT_SPAWN;
				}
			}
			else if (NewEnnemy->Ennemy->iStartPos == 2)
			{
				/*gestion x*/
				NewEnnemy->Ennemy->iRandSpawnDirectionVariation = rand() % 2 + 1;
				if (NewEnnemy->Ennemy->iRandSpawnDirectionVariation == 1)
				{
					NewEnnemy->Ennemy->vCurrentPosition.x = 1860 + ENNEMY_VARIANT_SPAWN;
				}
				else if (NewEnnemy->Ennemy->iRandSpawnDirectionVariation == 2)
				{
					NewEnnemy->Ennemy->vCurrentPosition.x = 1860 - ENNEMY_VARIANT_SPAWN;
				}

				/*gestion y*/
				NewEnnemy->Ennemy->iRandSpawnDirectionVariation = rand() % 2 + 1;
				if (NewEnnemy->Ennemy->iRandSpawnDirectionVariation == 1)
				{
					NewEnnemy->Ennemy->vCurrentPosition.y = 510 + ENNEMY_VARIANT_SPAWN;
				}
				else if (NewEnnemy->Ennemy->iRandSpawnDirectionVariation == 2)
				{
					NewEnnemy->Ennemy->vCurrentPosition.y = 510 - ENNEMY_VARIANT_SPAWN;
				}
			}

			sfSprite_setPosition(NewEnnemy->Ennemy->sp_Ennemy, NewEnnemy->Ennemy->vCurrentPosition);

#pragma endregion GESTION SPAWN //GUILLAUME

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

			/*variables d'animation*/
			NewEnnemy->Ennemy->iDirection = 0;
			NewEnnemy->Ennemy->iAnimationFrameX = 0;

			/*STATISTIQUES DE L'ENNEMI*/ // a placer lorsqu'on choisit le type d'ennemie

#pragma region STATISTIQUES ENNEMIE //GUILLAUME

			NewEnnemy->Ennemy->Def = 0;
			NewEnnemy->Ennemy->Deg = 0;
			NewEnnemy->Ennemy->Hp = 0;
			NewEnnemy->Ennemy->HpMax = 0;

#pragma endregion STATISTIQUES ENNEMIE //GUILLAUME

			/*BARRE DE VIE*/

#pragma region BARRE DE VIE //GUILLAUME

			/*rectangle de fond noir*/
			NewEnnemy->Ennemy->RectangleShapeBack = sfRectangleShape_create();

			/*rectangle de vie*/
			NewEnnemy->Ennemy->RectangleShape = sfRectangleShape_create();
			iSpaceButtonIsButtonPressedCheck = 1;

#pragma endregion BARRE DE VIE //GUILLAUME
		}

#pragma endregion ADD ENNEMY //GUILLAUME

#pragma region READ LIST ENNEMY CALCUL //GUILLAUME

		CurrentEnnemy = ListEnnemy->FirstElement;
		while (CurrentEnnemy != NULL)
		{

#pragma region ANCIENNE METHODE STEERING //GUILLAUME

			/*STEERING*/
			/*CurrentEnnemy->Ennemy->vSteering.x = CurrentEnnemy->Ennemy->vSeek.x - CurrentEnnemy->Ennemy->vCurrentVelocity.x;
			CurrentEnnemy->Ennemy->vSteering.y = CurrentEnnemy->Ennemy->vSeek.y - CurrentEnnemy->Ennemy->vCurrentVelocity.y;*/
			//CurrentEnnemy->Ennemy->vSteering = Truncate(CurrentEnnemy->Ennemy->vSteering, 5);

			///*si il y a collision je gère la vélocité avec la direction de l'entité*/
			//if (CurrentEnnemy->Ennemy->iIsColliding == 0)
			//{
			//	/*VELOCITE*/
			//	/*CurrentEnnemy->Ennemy->vCurrentVelocity.x += CurrentEnnemy->Ennemy->vSteering.x;
			//	CurrentEnnemy->Ennemy->vCurrentVelocity.y += CurrentEnnemy->Ennemy->vSteering.y;*/
			//	CurrentEnnemy->Ennemy->vCurrentVelocity.x += ENNEMY_SPEED;
			//	CurrentEnnemy->Ennemy->vCurrentVelocity.y += ENNEMY_SPEED;
			//}
			//else if (CurrentEnnemy->Ennemy->iIsColliding == 1)
			//{
			//	CurrentEnnemy->Ennemy->vCurrentVelocity.x += CurrentEnnemy->Ennemy->vNormalizeDirection.x;
			//	CurrentEnnemy->Ennemy->vCurrentVelocity.y += CurrentEnnemy->Ennemy->vNormalizeDirection.y;
			//}

			/*SEEK*/
			/*CurrentEnnemy->Ennemy->vSeek.x = CurrentEnnemy->Ennemy->vTargetPostion.x - CurrentEnnemy->Ennemy->vCurrentPosition.x;
			CurrentEnnemy->Ennemy->vSeek.y = CurrentEnnemy->Ennemy->vTargetPostion.y - CurrentEnnemy->Ennemy->vCurrentPosition.y;*/

			/*je veut obtenir l'angle de direction de mon entité en fonction de la direction de mon objectif*/
			//CurrentEnnemy->Ennemy->fDesiredAngleDirection = GetAngleDegreeFromVector(CurrentEnnemy->Ennemy->vSeek);

#pragma endregion ANCIENNE METHODE STERRING //GUILLAUME

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
					CurrentEnnemy->Ennemy->fDesiredAngleDirection = ANGLE_HAUT_DROIT + ANGLE_VARIANT_ISO;
					CurrentEnnemy->Ennemy->fAngleSprite = ANGLE_HAUT_DROIT + ANGLE_VARIANT_ISO;
				}
				/*COULEUR VERTE (HAUT-GAUCHE)*/
				if (CurrentEnnemy->Ennemy->Color_ToCheck.g == 255)
				{
					CurrentEnnemy->Ennemy->fDesiredAngleDirection = ANGLE_HAUT_GAUCHE - ANGLE_VARIANT_ISO;
					CurrentEnnemy->Ennemy->fAngleSprite = ANGLE_HAUT_GAUCHE - ANGLE_VARIANT_ISO;

				}
				/*COULEUR JAUNE (BAS_DROITE)*/
				if (CurrentEnnemy->Ennemy->Color_ToCheck.r == 150 && CurrentEnnemy->Ennemy->Color_ToCheck.g == 150)
				{
					CurrentEnnemy->Ennemy->fDesiredAngleDirection = ANGLE_BAS_DROIT - ANGLE_VARIANT_ISO;
					CurrentEnnemy->Ennemy->fAngleSprite = ANGLE_BAS_DROIT - ANGLE_VARIANT_ISO;
				}
				/*COULEUR BLEU CLAIR (BAS_GAUCHE)*/
				if (CurrentEnnemy->Ennemy->Color_ToCheck.g == 150 && CurrentEnnemy->Ennemy->Color_ToCheck.b == 150)
				{
					CurrentEnnemy->Ennemy->fDesiredAngleDirection = ANGLE_BAS_GAUCHE + ANGLE_VARIANT_ISO;
					CurrentEnnemy->Ennemy->fAngleSprite = ANGLE_BAS_GAUCHE + ANGLE_VARIANT_ISO;

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
						CurrentEnnemy->Ennemy->fDesiredAngleDirection = ANGLE_HAUT_DROIT + ANGLE_VARIANT_ISO;
					}
					else if (CurrentEnnemy->Ennemy->iRandDirection == 2)
					{
						CurrentEnnemy->Ennemy->fDesiredAngleDirection = ANGLE_HAUT_GAUCHE - ANGLE_VARIANT_ISO;
					}
				}

#pragma endregion ANGLE EN FONCTION DE LA COULEUR //GUILLAUME

#pragma region VARIATION LEGERE //GUILLAUME

				CurrentEnnemy->Ennemy->iRandVariation = rand() % 2 + 1;
				if (CurrentEnnemy->Ennemy->iRandVariation == 1)
				{
					CurrentEnnemy->Ennemy->fDesiredAngleDirection += ANGLE_INCREASE;
				}
				else if (CurrentEnnemy->Ennemy->iRandVariation == 2)
				{
					CurrentEnnemy->Ennemy->fDesiredAngleDirection -= ANGLE_INCREASE;
				}

#pragma endregion VARIATION LEGERE //GUILLAUME

				CurrentEnnemy->Ennemy->fCurrentAngleDirection = CurrentEnnemy->Ennemy->fDesiredAngleDirection;
				//printf("ANGLE : %.2f\n", CurrentEnnemy->Ennemy->fCurrentAngleDirection);
				/*la direction actuel du personnage est calculé par rapport a l'angle désirer*/
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

				CurrentEnnemy->Ennemy->vSideLeftControlPoint.x = CurrentEnnemy->Ennemy->vNormalizeDirection.x - (((CONTROL_RADIUS / 10) * sin(DegToRad(-CurrentEnnemy->Ennemy->fAngleSprite))) * CurrentEnnemy->Ennemy->fCollideIncrementation);
				CurrentEnnemy->Ennemy->vSideLeftControlPoint.y = CurrentEnnemy->Ennemy->vNormalizeDirection.y - (((CONTROL_RADIUS / 10) * cos(DegToRad(-CurrentEnnemy->Ennemy->fAngleSprite))) * CurrentEnnemy->Ennemy->fCollideIncrementation);
				CurrentEnnemy->Ennemy->vSideLeftControlPoint.x += CurrentEnnemy->Ennemy->vLeftStartPoint.x;
				CurrentEnnemy->Ennemy->vSideLeftControlPoint.y += CurrentEnnemy->Ennemy->vLeftStartPoint.y;

				CurrentEnnemy->Ennemy->vSideRightControlPoint.x = CurrentEnnemy->Ennemy->vNormalizeDirection.x + (((CONTROL_RADIUS / 10)* sin(DegToRad(-CurrentEnnemy->Ennemy->fAngleSprite))) * CurrentEnnemy->Ennemy->fCollideIncrementation);
				CurrentEnnemy->Ennemy->vSideRightControlPoint.y = CurrentEnnemy->Ennemy->vNormalizeDirection.y + (((CONTROL_RADIUS / 10)* cos(DegToRad(-CurrentEnnemy->Ennemy->fAngleSprite))) * CurrentEnnemy->Ennemy->fCollideIncrementation);
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

			/*GESTION VELOCITE / VITESSE*/

#pragma region GESTION VELOCITE / VITESSE //GUILLAUME

			if (CurrentEnnemy->Ennemy->fSpeed < 0)
			{
				CurrentEnnemy->Ennemy->fSpeed = 0;
			}

			if (CurrentEnnemy->Ennemy->fSpeed < MAX_SPEED)
			{
				CurrentEnnemy->Ennemy->fSpeed += ENNEMY_ACCELERATION;
			}
			else if (CurrentEnnemy->Ennemy->fSpeed > MAX_SPEED)
			{
				CurrentEnnemy->Ennemy->fSpeed -= ENNEMY_ACCELERATION;
			}

#pragma endregion GESTION VELOCITE / VITESSE //GUILLAUME

			/*VELOCITE*/
			CurrentEnnemy->Ennemy->vCurrentVelocity.x = CurrentEnnemy->Ennemy->vCurrentDirection.x * CurrentEnnemy->Ennemy->fSpeed;
			CurrentEnnemy->Ennemy->vCurrentVelocity.y = CurrentEnnemy->Ennemy->vCurrentDirection.y * CurrentEnnemy->Ennemy->fSpeed;
			CurrentEnnemy->Ennemy->vCurrentVelocity = Truncate(CurrentEnnemy->Ennemy->vCurrentVelocity, MAX_SPEED);

			/*POSIITON*/
			CurrentEnnemy->Ennemy->vCurrentPosition.x += CurrentEnnemy->Ennemy->vCurrentVelocity.x * timeSinceLastFrame;
			CurrentEnnemy->Ennemy->vCurrentPosition.y += CurrentEnnemy->Ennemy->vCurrentVelocity.y * timeSinceLastFrame;
			sfSprite_setPosition(CurrentEnnemy->Ennemy->sp_Ennemy, CurrentEnnemy->Ennemy->vCurrentPosition);

			/*ORIENTATION DU SPRITE*/
			printf("ANGLE SPRITE : %.2f | CURRENT ANGLE : %.2f\n", CurrentEnnemy->Ennemy->fAngleSprite, CurrentEnnemy->Ennemy->fCurrentAngleDirection);
			//CurrentEnnemy->Ennemy->fAngleSprite = GetAngleDegreeFromVector(CurrentEnnemy->Ennemy->vCurrentVelocity);
			sfSprite_setRotation(CurrentEnnemy->Ennemy->sp_Ennemy, CurrentEnnemy->Ennemy->fAngleSprite);

			//printf("DIRECTION X : %.2f | DIRECTION Y : %.2f\n", CurrentEnnemy->Ennemy->vCurrentDirection.x, CurrentEnnemy->Ennemy->vCurrentDirection.y);
			//printf("VELOCITY X : %.2f | VELOCITY Y : %.2f\n", CurrentEnnemy->Ennemy->vCurrentVelocity.x, CurrentEnnemy->Ennemy->vCurrentVelocity.y);
			//printf("COLLIDE : %d\n", CurrentEnnemy->Ennemy->iIsColliding);
			//printf("POSITION X : %.2f | POSITION Y : %2f\n", CurrentEnnemy->Ennemy->vCurrentPosition.x, CurrentEnnemy->Ennemy->vCurrentPosition.y);

			CurrentEnnemy = CurrentEnnemy->NextElement;
		}

#pragma endregion READ LIST ENNEMY CALCUL //GUILLAUME

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
			if (sfFloatRect_contains(&Rect_TowerSlotBB, vMousePosToFloat.x, vMousePosToFloat.y) && !isInBuildChoice && !CurrentTowerSlot->TowerSlot->IsBuild)
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
			CurrentTowerSlot = CurrentTowerSlot->NextElement;
		}
#pragma endregion LECTURE TRAITEMENT AFFICHAGE SLOTS TOURS //SEB

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
						NewTower->Tower->bulletSpeed = 1;
						sfSprite_setOrigin(NewTower->Tower->fieldSpr, vOrigin_fieldOfView);
						sfSprite_setPosition(NewTower->Tower->fieldSpr, NewTower->Tower->vPos);
						NewTower->Tower->fieldBB = sfSprite_getGlobalBounds(NewTower->Tower->fieldSpr);
						sfSprite_setTextureRect(NewTower->Tower->sprite, NewTower->Tower->animRect);
						sfSprite_setPosition(NewTower->Tower->sprite, NewTower->Tower->vPos);
						NewTower->Tower->boundingBox = sfSprite_getGlobalBounds(NewTower->Tower->sprite);
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
						sfSprite_setColor(btn1->sprite, sfWhite);
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
						NewTower->Tower->tStartShoot = (float)clock() / CLOCKS_PER_SEC;
						NewTower->Tower->tSinceShoot = 0;
						NewTower->Tower->tCurrentShoot = 0;
						NewTower->Tower->fieldSpr = createSprite("resources/textures/tower_field_of_view.png");
						sfSprite_setOrigin(NewTower->Tower->fieldSpr, vOrigin_fieldOfView);
						sfSprite_setPosition(NewTower->Tower->fieldSpr, NewTower->Tower->vPos);
						NewTower->Tower->fieldBB = sfSprite_getGlobalBounds(NewTower->Tower->fieldSpr);
						sfSprite_setTextureRect(NewTower->Tower->sprite, NewTower->Tower->animRect);
						sfSprite_setPosition(NewTower->Tower->sprite, NewTower->Tower->vPos);
						NewTower->Tower->boundingBox = sfSprite_getGlobalBounds(NewTower->Tower->sprite);
						NewTower->Tower->bulletSpeed = 0.7;
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
						sfSprite_setColor(btn2->sprite, sfWhite);
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
						NewTower->Tower->fieldSpr = createSprite("resources/textures/tower_field_of_view.png");
						sfSprite_setOrigin(NewTower->Tower->fieldSpr, vOrigin_fieldOfView);
						sfSprite_setPosition(NewTower->Tower->fieldSpr, NewTower->Tower->vPos);
						NewTower->Tower->fieldBB = sfSprite_getGlobalBounds(NewTower->Tower->fieldSpr);
						sfSprite_setTextureRect(NewTower->Tower->sprite, NewTower->Tower->animRect);
						sfSprite_setPosition(NewTower->Tower->sprite, NewTower->Tower->vPos);
						NewTower->Tower->boundingBox = sfSprite_getGlobalBounds(NewTower->Tower->sprite);
						NewTower->Tower->bulletSpeed = 0.5;
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
						sfSprite_setColor(btn3->sprite, sfWhite);
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


		//affichage du champ de vision de la tour selectionnée
		//if (isBuildedChoice)
		//{
		//	sfSprite_setPosition(Sp_fieldOfView, ActualTower->Tower->vPos);
		//	sfRenderWindow_drawSprite(window, Sp_fieldOfView, NULL);
		//}
#pragma endregion LECTURE TRAITEMENT DES TOURS //SEB

#pragma region READ LIST ENNEMY AFFICHAGE //GUILLAUME

		CurrentEnnemy = ListEnnemy->FirstElement;
		while (CurrentEnnemy != NULL)
		{
			sfRenderWindow_drawSprite(window, CurrentEnnemy->Ennemy->sp_Ennemy, NULL);

			/*AFFICHAGE DES VERTEX*/

#pragma region AFFICHAGE DES VERTEX

			/*CONTROL POINT*/
			SetLineBetweenPoints(VertexArray, Vertex, CurrentEnnemy->Ennemy->vCurrentPosition, CurrentEnnemy->Ennemy->vControlPoint, sfBlack);
			sfRenderWindow_drawVertexArray(window, VertexArray, NULL);

			/*RIGHT POINT*/
			SetLineBetweenPoints(VertexArray, Vertex, CurrentEnnemy->Ennemy->vRightStartPoint, CurrentEnnemy->Ennemy->vRightControlPoint, sfBlack);
			sfRenderWindow_drawVertexArray(window, VertexArray, NULL);

			/*LEFT POINT*/
			SetLineBetweenPoints(VertexArray, Vertex, CurrentEnnemy->Ennemy->vLeftStartPoint, CurrentEnnemy->Ennemy->vLeftControlPoint, sfBlack);
			sfRenderWindow_drawVertexArray(window, VertexArray, NULL);

			/*SIDE RIGHT POINT*/
			SetLineBetweenPoints(VertexArray, Vertex, CurrentEnnemy->Ennemy->vRightStartPoint, CurrentEnnemy->Ennemy->vSideRightControlPoint, sfBlack);
			sfRenderWindow_drawVertexArray(window, VertexArray, NULL);

			/*SIDE LEFT POINT*/
			SetLineBetweenPoints(VertexArray, Vertex, CurrentEnnemy->Ennemy->vLeftStartPoint, CurrentEnnemy->Ennemy->vSideLeftControlPoint, sfBlack);
			sfRenderWindow_drawVertexArray(window, VertexArray, NULL);

			/*velocity*/
			/*VertexArray = GetLine(CurrentEnnemy->Ennemy->vRightStartPoint, CurrentEnnemy->Ennemy->vRightControlPoint, sfBlack);
			sfRenderWindow_drawVertexArray(window, VertexArray, NULL);*/

#pragma endregion AFFICHAGE DES VERTEX

			CurrentEnnemy = CurrentEnnemy->NextElement;
		}

#pragma endregion READ LIST ENNEMY AFFICHAGE //GUILLAUME

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
			sfRenderWindow_drawSprite(window, CurrentTower->Tower->fieldSpr, NULL);
			sfRenderWindow_drawSprite(window, CurrentTower->Tower->sprite, NULL);
			CurrentTower = CurrentTower->NextElement;

		}
#pragma endregion LECTURE AFFICHAGE DES TOURS //SEB

#pragma region LECTURE CONTROLE COLISION TOURS //SEB

		/*Lecture de liste tour pour le controle de colision champ de vision, et tir des tours*/

		CurrentTower = ListTower->FirstElement;

		while (CurrentTower != NULL)
		{
			if (sfFloatRect_contains(&CurrentTower->Tower->fieldBB, vPos_player.x, vPos_player.y))
			{
				vPlayerPointToCheck.x = (vOrigin_fieldOfView.x) - (CurrentTower->Tower->vPos.x - vPos_player.x);
				vPlayerPointToCheck.y = (vOrigin_fieldOfView.y) - (CurrentTower->Tower->vPos.y - vPos_player.y);
				if (sfImage_getPixel(Img_fieldMask, vPlayerPointToCheck.x, vPlayerPointToCheck.y).r == 255 && sfImage_getPixel(Img_fieldMask, vPlayerPointToCheck.x, vPlayerPointToCheck.y).g == 0
					&& sfImage_getPixel(Img_fieldMask, vPlayerPointToCheck.x, vPlayerPointToCheck.y).b == 0 && sfImage_getPixel(Img_fieldMask, vPlayerPointToCheck.x, vPlayerPointToCheck.y).a == 255)
				{
					CurrentTower->Tower->tCurrentShoot = (float)clock() / CLOCKS_PER_SEC;
					CurrentTower->Tower->tSinceShoot = CurrentTower->Tower->tCurrentShoot - CurrentTower->Tower->tStartShoot;
					if (CurrentTower->Tower->tSinceShoot > 2 * CurrentTower->Tower->bulletSpeed)
					{
						printf_s("Bullet !!!\n");
						CurrentTower->Tower->tStartShoot = CurrentTower->Tower->tCurrentShoot;
						NewTowerBullet = AddElementBeginListTowerBullet(ListTowerBullet);
						NewTowerBullet->TowerBullet = malloc(sizeof(t_TowerBullet));
						NewTowerBullet->TowerBullet->pos.x = CurrentTower->Tower->vPos.x;
						NewTowerBullet->TowerBullet->pos.y = CurrentTower->Tower->vPos.y - CurrentTower->Tower->boundingBox.height;
						switch (CurrentTower->Tower->TowerType)
						{
						case TYPE1:
							NewTowerBullet->TowerBullet->sprite = Sp_bullet1;
							NewTowerBullet->TowerBullet->bulletSpeed = 1;
							break;
						case TYPE2:
							NewTowerBullet->TowerBullet->sprite = Sp_bullet2;
							NewTowerBullet->TowerBullet->bulletSpeed = 2;
							break;
						case TYPE3:
							NewTowerBullet->TowerBullet->sprite = Sp_bullet3;
							NewTowerBullet->TowerBullet->bulletSpeed = 3;
							break;
						default:
							break;
						}
					}
					sfSprite_setColor(CurrentTower->Tower->fieldSpr, sfRed);
				}
			}
			else
			{
				sfSprite_setColor(CurrentTower->Tower->fieldSpr, sfWhite);
			}
			CurrentTower = CurrentTower->NextElement;
		}

#pragma endregion LECTURE CONTROLE COLISION TOURS //SEB

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
							Rect_TowerSlotBB.left = CurrentTowerSlot->TowerSlot->vPos.x - vOrigin_TowerSlot.x;
							Rect_TowerSlotBB.top = CurrentTowerSlot->TowerSlot->vPos.y - vOrigin_TowerSlot.y;
							Rect_TowerSlotBB.width = vOrigin_TowerSlot.x * 2;
							Rect_TowerSlotBB.height = vOrigin_TowerSlot.y * 2;
							sfFloatRect test = sfSprite_getGlobalBounds(ActualTower->Tower->sprite);
							if (sfFloatRect_intersects(&ActualTower->Tower->boundingBox, &Rect_TowerSlotBB, NULL))
							{
								CurrentTowerSlot->TowerSlot->IsBuild = 0;
								CurrentTowerSlot->TowerSlot->IsClicked = 0;
								break;
							}
							CurrentTowerSlot = CurrentTowerSlot->NextElement;
						}
						DeleteElementById(ListTower, ActualTower->Id);
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

		while (CurrentTowerBullet != NULL)
		{
			CurrentTowerBullet->TowerBullet->dir.x = vPos_player.x - CurrentTowerBullet->TowerBullet->pos.x;
			CurrentTowerBullet->TowerBullet->dir.y = vPos_player.y - CurrentTowerBullet->TowerBullet->pos.y;
			CurrentTowerBullet->TowerBullet->dir = Normalize(CurrentTowerBullet->TowerBullet->dir);
			CurrentTowerBullet->TowerBullet->pos.x += CurrentTowerBullet->TowerBullet->dir.x ;
			CurrentTowerBullet->TowerBullet->pos.y += CurrentTowerBullet->TowerBullet->dir.y;
			sfSprite_setPosition(CurrentTowerBullet->TowerBullet->sprite, CurrentTowerBullet->TowerBullet->pos);
			Rect_playerBB = sfCircleShape_getGlobalBounds(player);
			CurrentTowerBullet->TowerBullet->boundingBox.left = CurrentTowerBullet->TowerBullet->pos.x - 20;
			CurrentTowerBullet->TowerBullet->boundingBox.top = CurrentTowerBullet->TowerBullet->pos.y - 20;
			CurrentTowerBullet->TowerBullet->boundingBox.width = 40;
			CurrentTowerBullet->TowerBullet->boundingBox.height = 40;
			if (sfFloatRect_intersects(&Rect_playerBB, &CurrentTowerBullet->TowerBullet->boundingBox, NULL))
			{
				DeleteElementByIdBullet(ListTowerBullet,CurrentTowerBullet->Id);
				break;
			}
			CurrentTowerBullet = CurrentTowerBullet->NextElement;
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

		/////////////////////////////////////MATTIA SEBASTIEN FIN CODE CONSTRUCTION TOURS + SLOTS ///////////////////////////////////////////////////////

#pragma region TRAITEMENT AFFICHAGE JOUEUR TEST

		////////////////////////////////PLAYER TEST///////////////////////////////////////
		if (sfKeyboard_isKeyPressed(sfKeyDown))
		{
			vPos_player.y += 200 * timeSinceLastFrame;
		}
		else if (sfKeyboard_isKeyPressed(sfKeyUp))
		{
			vPos_player.y -= 200 * timeSinceLastFrame;
		}
		else if (sfKeyboard_isKeyPressed(sfKeyLeft))
		{
			vPos_player.x -= 200 * timeSinceLastFrame;
		}
		else if (sfKeyboard_isKeyPressed(sfKeyRight))
		{
			vPos_player.x += 200 * timeSinceLastFrame;
		}


		sfCircleShape_setPosition(player, vPos_player);
		sfRenderWindow_drawCircleShape(window, player, NULL);

#pragma endregion TRAITEMENT AFFICHAGE JOUEUR TEST
		/////////////////////////////FIN PLAYER TEST/////////////////////////////////////


		/* Update the window */
		sfRenderWindow_display(window);
	}
	/* Cleanup resources */
	sfRenderWindow_destroy(window);

	return 0;
}