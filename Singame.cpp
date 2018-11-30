@@ - 191, 3 + 191, 116 @@ void Singame::computeMatricesFromInputs(int x, int y, int key, int pressed) {
}




//////////////////////////////////////////////////////////////////////
GLuint texture[6];

GLuint LoadTexture(const char * filename, int width, int height)
{
	GLuint texture;
	unsigned char * data;
	FILE* file;

	file = fopen(filename, "rb");
	if (file == NULL) return 0;
	data = (unsigned char *)malloc(width * height * 3 + 54);
	fread(data, width * height * 3 + 54, 1, file);
	fclose(file);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data + 54);
	free(data);
	return texture;
}

void initTexture()
{
	texture[0] = LoadTexture("Back.bmp", 512, 512); //load the texture
	texture[1] = LoadTexture("Front.bmp", 512, 512); //load the texture
	texture[2] = LoadTexture("Left.bmp", 512, 512); //load the texture
	texture[3] = LoadTexture("Right.bmp", 512, 512); //load the texture
	texture[4] = LoadTexture("Bottom.bmp", 512, 512); //load the texture
	texture[5] = LoadTexture("Top.bmp", 512, 512); //load the texture
}

void skybox(void)
{
	float x = 0;
	float y = 0;
	float z = 0;
	float width = 5000;
	float height = 5000;
	float length = 5000;

	// Center the skybox

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
	//glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(1.0f, 0.0f);   glVertex3f(width, height, -length);   // Top Right Of The Quad (Top)
	glTexCoord2d(1.0f, 1.0f);   glVertex3f(-width, height, -length);   // Top Left Of The Quad (Top)
	glTexCoord2d(0.0, 1.0f);   glVertex3f(-width, height, length);   // Bottom Left Of The Quad (Top)
	glTexCoord2d(0.0, 0.0f);   glVertex3f(width, height, length);   // Bottom Right Of The Quad (Top)
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	//glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2d(0.0f, 0.0f);   glVertex3f(width, height, length);   // Top Right Of The Quad (Front)
	glTexCoord2d(1.0f, 0.0f);   glVertex3f(-width, height, length);   // Top Left Of The Quad (Front)
	glTexCoord2d(1.0f, 1.0f);   glVertex3f(-width, -height, length);   // Bottom Left Of The Quad (Front)
	glTexCoord2d(0.0f, 1.0f);   glVertex3f(width, -height, length);   // Bottom Right Of The Quad (Front)
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	//glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2d(0.0f, 1.0f);   glVertex3f(width, -height, -length);   // Bottom Left Of The Quad (Back)
	glTexCoord2d(1.0f, 1.0f);   glVertex3f(-width, -height, -length);   // Bottom Right Of The Quad (Back)
	glTexCoord2d(1.0f, 0.0f);   glVertex3f(-width, height, -length);   // Top Right Of The Quad (Back)
	glTexCoord2d(0.0f, 0.0f);   glVertex3f(width, height, -length);   // Top Left Of The Quad (Back)
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	//glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2d(1.0f, 0.0f);   glVertex3f(-width, height, -length);   // Top Right Of The Quad (Left)
	glTexCoord2d(1.0f, 1.0f);   glVertex3f(-width, -height, -length);   // Top Left Of The Quad (Left)
	glTexCoord2d(0.0f, 1.0f);   glVertex3f(-width, -height, length);   // Bottom Left Of The Quad (Left)
	glTexCoord2d(0.0f, 0.0f);   glVertex3f(-width, height, length);   // Bottom Right Of The Quad (Left)
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);
	//glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f);   glVertex3f(width, height, -length);   // Top Right Of The Quad (Right)
	glTexCoord2d(1.0f, 0.0f);   glVertex3f(width, height, length);   // Top Left Of The Quad (Right)
	glTexCoord2d(1.0f, 1.0f);   glVertex3f(width, -height, length);   // Bottom Left Of The Quad (Right)
	glTexCoord2d(0.0f, 1.0f);   glVertex3f(width, -height, -length);   // Bottom Right Of The Quad (Right)
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
	//glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2d(1.0f, 0.0f);   glVertex3f(-width, -height, length);   // Top Right Of The Quad (Top)
	glTexCoord2d(1.0f, 1.0f);   glVertex3f(width, -height, length);   // Top Left Of The Quad (Top)
	glTexCoord2d(0.0, 1.0f);   glVertex3f(width, -height, -length);   // Bottom Left Of The Quad (Top)
	glTexCoord2d(0.0, 0.0f);   glVertex3f(-width, -height, -length);   // Bottom Right Of The Quad (Top)
	glEnd();

}

void FreeTexture(GLuint texture)
{
	glDeleteTextures(1, &texture);
}