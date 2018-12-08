#pragma once
#define _SCENES_
/*--------------------ADD SCENES HERE--------------------*/

/*~~~~~HEADER FILES~~~~*/
#include "Singame.h"
#include "Singame2.h"
#include"Singame3.h"

struct GLSceneInfo
{
	std::string name;
	GLScene*	pScene;
	bool		bInitAtStart{ true };
};

/*~~~~~~~SCENES~~~~~~~*/
const GLSceneInfo SCENES[] =
{
	{"Ingame", new Singame2, true},

};

/*~~~STARTING SCENE~~~*/
const std::string STARTING_SCENE{ "Ingame" };
/*-------------------------------------------------------*/
