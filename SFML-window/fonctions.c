#include "header.h"

///// Functions using the SFML Library //////
#pragma region SFML Functions

sfSprite* createSprite(char* _path)
{
	//_path correspond au chemin d'acc�es de la texture
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

//check if the Ball is on another sprite and if so change the sprite colour
int SpriteIsOver(char *_window, char *_spritePerso, char *_spriteObject)
{
	sfFloatRect boundingBox_spriteObject = sfSprite_getGlobalBounds(_spriteObject);

	sfFloatRect boundingBox_spritePerso = sfSprite_getGlobalBounds(_spritePerso);


	if ((boundingBox_spritePerso.left >= boundingBox_spriteObject.left + boundingBox_spriteObject.width) // cot� gauche perso plus � droite que le cot� droit de l'objet
		|| ((boundingBox_spritePerso.left + boundingBox_spritePerso.width) <= boundingBox_spriteObject.left) // cot� droit perso plus � gauche que le cot� gauche de l'objet
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

void loadTowerSlots(t_List* _ListTowerSlot, int _levelNumber)
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
		fscanf_s(file, "vPosX=%f,vPosY=%f\n", &newElement->TowerSlot->vPos.x, &newElement->TowerSlot->vPos.y);
		newElement->TowerSlot->IsBuild = sfFalse;
		newElement->TowerSlot->IsClicked = sfFalse;
	}

	fclose(file);
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

/*m�thode liste chain�e*/

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
//		/*parcours dans la boucle pour trouver l'�l�ment a supprimer*/
//		while (CurrentElement != NULL)
//		{
//			/*si le prochain �l�ment est celuis que l'on veut supprimer on attache le previous et le next avant de supprimer l'�l�ment en question*/
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


/*m�thode liste doublement chain�e*/

sfBool DeleteElementById(t_List* _List, int _IdElementToDelete)
{
	/*Delete de l'�l�ment restant dans la liste*/
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
		/*parcours dans la boucle pour trouver l'�l�ment a supprimer*/
		t_EnnemyElement* CurrentElement = _List->FirstElement;
		while (CurrentElement != NULL)
		{
			/*si le prochain �l�ment est celuis que l'on veut supprimer on attache le previous et le next avant de supprimer l'�l�ment en question*/
			if (CurrentElement->Id == _IdElementToDelete)
			{
				t_EnnemyElement* ElementToDelete = CurrentElement;
				/*je raccorde le next element de l'�l�ment pr�c�dent a l'�l�ment suivant de celui que je veut supprimer*/
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
	/*Delete de l'�l�ment restant dans la liste*/
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
		/*parcours dans la boucle pour trouver l'�l�ment a supprimer*/
		t_TowerSlotElement* CurrentElement = _List->FirstElement;
		while (CurrentElement != NULL)
		{
			/*si le prochain �l�ment est celuis que l'on veut supprimer on attache le previous et le next avant de supprimer l'�l�ment en question*/
			if (CurrentElement->Id == _IdElementToDelete)
			{
				t_TowerSlotElement* ElementToDelete = CurrentElement;
				/*je raccorde le next element de l'�l�ment pr�c�dent a l'�l�ment suivant de celui que je veut supprimer*/
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
	/*Delete de l'�l�ment restant dans la liste*/
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
		/*parcours dans la boucle pour trouver l'�l�ment a supprimer*/
		t_TowerElement* CurrentElement = _List->FirstElement;
		while (CurrentElement != NULL)
		{
			/*si le prochain �l�ment est celuis que l'on veut supprimer on attache le previous et le next avant de supprimer l'�l�ment en question*/
			if (CurrentElement->Id == _IdElementToDelete)
			{
				t_TowerElement* ElementToDelete = CurrentElement;
				/*je raccorde le next element de l'�l�ment pr�c�dent a l'�l�ment suivant de celui que je veut supprimer*/
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
	/*Delete de l'�l�ment restant dans la liste*/
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
		/*parcours dans la boucle pour trouver l'�l�ment a supprimer*/
		t_TowerBulletElement* CurrentElement = _List->FirstElement;
		while (CurrentElement != NULL)
		{
			/*si le prochain �l�ment est celuis que l'on veut supprimer on attache le previous et le next avant de supprimer l'�l�ment en question*/
			if (CurrentElement->Id == _IdElementToDelete)
			{
				t_TowerBulletElement* ElementToDelete = CurrentElement;
				/*je raccorde le next element de l'�l�ment pr�c�dent a l'�l�ment suivant de celui que je veut supprimer*/
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

/*d�truire tous les �l�ments d'une liste sans d�truire la liste*/

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

/*renvoie true si l'entit� est en collision*/
sfBool manageEnnemi(t_EnnemyElement* currentElement, sfImage* testMask, float fTimeSinceLastFrame)
{
	currentElement->Ennemy->fTimeCurrentVertex = (float)clock() / CLOCKS_PER_SEC;
	currentElement->Ennemy->fTimeSinceVertex = currentElement->Ennemy->fTimeCurrentVertex - currentElement->Ennemy->fTimeStartVertex;
	currentElement->Ennemy->vNormalizeDirection = normalizeVector(currentElement->Ennemy->vCurrentDirection);
	currentElement->Ennemy->vControlPoint.x = currentElement->Ennemy->vNormalizeDirection.x  * (CONTROL_RADIUS / 2);
	currentElement->Ennemy->vControlPoint.y = currentElement->Ennemy->vNormalizeDirection.y * (CONTROL_RADIUS / 2);
	currentElement->Ennemy->vControlPoint.x += currentElement->Ennemy->vCurrentPosition.x;
	currentElement->Ennemy->vControlPoint.y += currentElement->Ennemy->vCurrentPosition.y;
	/*currentElement->Ennemy->fAngleSprite = GetAngleDegreeFromVector(currentElement->Ennemy->vCurrentDirection);*/

	currentElement->Ennemy->vLeftStartPoint.x = currentElement->Ennemy->vCurrentPosition.x - ((GUARD_RADIUS + 5) * sin(DegToRad(-currentElement->Ennemy->fAngleSprite)));
	currentElement->Ennemy->vLeftStartPoint.y = currentElement->Ennemy->vCurrentPosition.y - ((GUARD_RADIUS + 5) * cos(DegToRad(-currentElement->Ennemy->fAngleSprite)));

	currentElement->Ennemy->vRightStartPoint.x = currentElement->Ennemy->vCurrentPosition.x + (GUARD_RADIUS + 5) * sin(DegToRad(-currentElement->Ennemy->fAngleSprite));
	currentElement->Ennemy->vRightStartPoint.y = currentElement->Ennemy->vCurrentPosition.y + (GUARD_RADIUS + 5) * cos(DegToRad(-currentElement->Ennemy->fAngleSprite));

	/*exemple pour calculer les points devant*/ //(a garder au cas ou)
	currentElement->Ennemy->vRightControlPoint.x = currentElement->Ennemy->vNormalizeDirection.x  * (CONTROL_RADIUS / 3);
	currentElement->Ennemy->vRightControlPoint.y = currentElement->Ennemy->vNormalizeDirection.y * (CONTROL_RADIUS / 3);
	currentElement->Ennemy->vRightControlPoint.x += currentElement->Ennemy->vRightStartPoint.x;
	currentElement->Ennemy->vRightControlPoint.y += currentElement->Ennemy->vRightStartPoint.y;

	currentElement->Ennemy->vLeftControlPoint.x = currentElement->Ennemy->vNormalizeDirection.x  * (CONTROL_RADIUS / 3);
	currentElement->Ennemy->vLeftControlPoint.y = currentElement->Ennemy->vNormalizeDirection.y * (CONTROL_RADIUS / 3);
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