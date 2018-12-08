#pragma once
#define _SCENES_
/*--------------------ADD SCENES HERE--------------------*/

/*~~~~~HEADER FILES~~~~*/
#include "Singame.h"
#include "Singame2.h"
#include"Singame3.h"
#include"Singame4.h"

struct GLSceneInfo
{
	std::string name;
	GLScene*	pScene;
	bool		bInitAtStart{ true };
};

/*~~~~~~~SCENES~~~~~~~*/
const GLSceneInfo SCENES[] =
{
	{"Ingame1", new Singame, true},
	{"Ingame2", new Singame2, false},
	{"Ingame3", new Singame3, false},
	{"Ingame4", new Singame4, false}
};

/*~~~STARTING SCENE~~~*/
const std::string STARTING_SCENE{ "Ingame4" };
/*-------------------------------------------------------*/
