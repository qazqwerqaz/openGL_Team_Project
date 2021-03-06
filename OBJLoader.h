#pragma once
#include "LinearMath.h"

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include "Mmsystem.h"
#include "Digitalv.h"

class OBJLoader
{
public:
	OBJLoader();
	~OBJLoader();

	void init();
	//OBJ 로드
	bool loadOBJ(const char * path,
		std::vector<Vector3> & out_vertices,
		std::vector<Vector2> & out_uvs,
		std::vector<Vector3> & out_normals);

	// Hud 
	void Hud();

	//Texture 로드
	void initTexture();
	GLuint LoadTexture(const char * filename, int width, int height);
	void skybox(Vector3 Eye);
	void FreeTexture(GLuint texture);

	DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave);
private:
	GLuint texture[7];

	// 사운드 로드
	MCI_OPEN_PARMS     mciOpenParms;
	MCI_PLAY_PARMS     mciPlayParms;
	MCI_STATUS_PARMS   mciStatus;

	UINT wDeviceID = 0;
};

