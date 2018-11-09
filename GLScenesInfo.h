#pragma once
#define _SCENES_
/*--------------------ADD SCENES HERE--------------------*/

/*~~~~~HEADER FILES~~~~*/
#include "Singame.h"

struct GLSceneInfo
{
	std::string name;
	GLScene*	pScene;
	bool		bInitAtStart{ true };
};

/*~~~~~~~SCENES~~~~~~~*/
const GLSceneInfo SCENES[] =
{
	{"Ingame", new Singame, false}
};

/*~~~STARTING SCENE~~~*/
const std::string STARTING_SCENE{ "Tutorial" };
/*-------------------------------------------------------*/
