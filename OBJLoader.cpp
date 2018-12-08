#include "stdafx.h"
#include "OBJLoader.h"



OBJLoader::OBJLoader()
{
	
}


OBJLoader::~OBJLoader()
{
}

void OBJLoader::init()
{
	initTexture();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glColor3f(1, 1, 1);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}



bool OBJLoader::loadOBJ(
	const char * path,
	std::vector<Vector3> & out_vertices,
	std::vector<Vector2> & out_uvs,
	std::vector<Vector3> & out_normals
) {
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<Vector3> temp_vertices;
	std::vector<Vector2> temp_uvs;
	std::vector<Vector3> temp_normals;

	FILE * file;
	fopen_s(&file, path, "r");
	if (file == NULL) {
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while (1) {

		char lineHeader[256];
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader,sizeof(lineHeader));
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			Vector3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			Vector2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			Vector3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		Vector3 vertex = temp_vertices[vertexIndex - 1];
		Vector2 uv = temp_uvs[uvIndex - 1];
		Vector3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);

	}
	fclose(file);
	return true;
}

void OBJLoader::initTexture()
{
	texture[0] = LoadTexture("1_Back.bmp", 512, 512); //load the texture
	texture[1] = LoadTexture("1_Front.bmp", 512, 512); //load the texture
	texture[2] = LoadTexture("1_Left.bmp", 512, 512); //load the texture
	texture[3] = LoadTexture("1_Right.bmp", 512, 512); //load the texture
	texture[4] = LoadTexture("1_Bottom.bmp", 512, 512); //load the texture
	texture[5] = LoadTexture("1_Top.bmp", 512, 512); //load the texture
}

GLuint OBJLoader::LoadTexture(const char * filename, int width, int height)
{
	GLuint texture;
	unsigned char * data;
	FILE* file;

	fopen_s(&file, filename, "rb");
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

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data + 54);
	free(data);
	return texture;
}

void OBJLoader::skybox(Vector3 Eye)
{
	glPushMatrix();
	{
		glColor3f(1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, texture[6]);
		glBegin(GL_QUADS);
		glTexCoord2d(1.0f, 0.0f);   glVertex3f(25, 25, -25);   // Top Right Of The Quad (Top)
		glTexCoord2d(1.0f, 1.0f);   glVertex3f(-25, 25, -25);   // Top Left Of The Quad (Top)
		glTexCoord2d(0.0, 1.0f);   glVertex3f(-25, 25, 25);   // Bottom Left Of The Quad (Top)
		glTexCoord2d(0.0, 0.0f);   glVertex3f(25, 25, 25);   // Bottom Right Of The Quad (Top)
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[6]);
		glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 1.0f);   glVertex3f(25, 25, 25);   // Top Right Of The Quad (Front)
		glTexCoord2d(1.0f, 1.0f);   glVertex3f(-25, 25, 25);   // Top Left Of The Quad (Front)
		glTexCoord2d(1.0f, 0.0f);   glVertex3f(-25, -25, 25);   // Bottom Left Of The Quad (Front)
		glTexCoord2d(0.0f, 0.0f);   glVertex3f(25, -25, 25);   // Bottom Right Of The Quad (Front)
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[6]);
		glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 1.0f);   glVertex3f(25, -25, -25);   // Bottom Left Of The Quad (Back)
		glTexCoord2d(0.0f, 0.0f);   glVertex3f(-25, -25, -25);   // Bottom Right Of The Quad (Back)
		glTexCoord2d(1.0f, 0.0f);   glVertex3f(-25, 25, -25);   // Top Right Of The Quad (Back)
		glTexCoord2d(1.0f, 1.0f);   glVertex3f(25, 25, -25);   // Top Left Of The Quad (Back)
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[6]);
		glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);   glVertex3f(-25, 25, -25);   // Top Right Of The Quad (Left)
		glTexCoord2d(0.0f, 1.0f);   glVertex3f(-25, -25, -25);   // Top Left Of The Quad (Left)
		glTexCoord2d(1.0f, 1.0f);   glVertex3f(-25, -25, 25);   // Bottom Left Of The Quad (Left) 
		glTexCoord2d(1.0f, 0.0f);   glVertex3f(-25, 25, 25);   // Bottom Right Of The Quad (Left)
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[6]);
		glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 1.0f);   glVertex3f(25, 25, -25);   // Top Right Of The Quad (Right)
		glTexCoord2d(1.0f, 1.0f);   glVertex3f(25, 25, 25);   // Top Left Of The Quad (Right)
		glTexCoord2d(1.0f, 0.0f);   glVertex3f(25, -25, 25);   // Bottom Left Of The Quad (Right)
		glTexCoord2d(0.0f, 0.0f);   glVertex3f(25, -25, -25);   // Bottom Right Of The Quad (Right)
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[6]);
		glBegin(GL_QUADS);
		glTexCoord2d(1.0f, 0.0f);   glVertex3f(-25, -25, 25);   // Top Right Of The Quad (Top)
		glTexCoord2d(1.0f, 1.0f);   glVertex3f(25, -25, 25);   // Top Left Of The Quad (Top)
		glTexCoord2d(0.0, 1.0f);   glVertex3f(25, -25, -25);   // Bottom Left Of The Quad (Top)
		glTexCoord2d(0.0, 0.0f);   glVertex3f(-25, -25, -25);   // Bottom Right Of The Quad (Top)
		glEnd();
	}
	glPopMatrix();


	glColor3f(1, 1, 1);
	float x = Eye.x;
	float y = Eye.y;
	float z = Eye.z;

	float width = glutGet(GLUT_WINDOW_WIDTH);
	float height = glutGet(GLUT_WINDOW_HEIGHT);
	float length = 1000;

	// Center the skybox
	glPushMatrix();
	{

		glTranslatef(x, y, z);
		glBindTexture(GL_TEXTURE_2D, texture[5]);
		glBegin(GL_QUADS);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2d(1.0f, 0.0f);   glVertex3f(width, height, -length);   // Top Right Of The Quad (Top)
		glTexCoord2d(1.0f, 1.0f);   glVertex3f(-width, height, -length);   // Top Left Of The Quad (Top)
		glTexCoord2d(0.0, 1.0f);   glVertex3f(-width, height, length);   // Bottom Left Of The Quad (Top)
		glTexCoord2d(0.0, 0.0f);   glVertex3f(width, height, length);   // Bottom Right Of The Quad (Top)
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2d(0.0f, 1.0f);   glVertex3f(width, height, length);   // Top Right Of The Quad (Front)
		glTexCoord2d(1.0f, 1.0f);   glVertex3f(-width, height, length);   // Top Left Of The Quad (Front)
		glTexCoord2d(1.0f, 0.0f);   glVertex3f(-width, -height, length);   // Bottom Left Of The Quad (Front)
		glTexCoord2d(0.0f, 0.0f);   glVertex3f(width, -height, length);   // Bottom Right Of The Quad (Front)
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2d(0.0f, 1.0f);   glVertex3f(width, -height, -length);   // Bottom Left Of The Quad (Back)
		glTexCoord2d(0.0f, 0.0f);   glVertex3f(-width, -height, -length);   // Bottom Right Of The Quad (Back)
		glTexCoord2d(1.0f, 0.0f);   glVertex3f(-width, height, -length);   // Top Right Of The Quad (Back)
		glTexCoord2d(1.0f, 1.0f);   glVertex3f(width, height, -length);   // Top Left Of The Quad (Back)
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2d(0.0f, 0.0f);   glVertex3f(-width, height, -length);   // Top Right Of The Quad (Left)
		glTexCoord2d(0.0f, 1.0f);   glVertex3f(-width, -height, -length);   // Top Left Of The Quad (Left)
		glTexCoord2d(1.0f, 1.0f);   glVertex3f(-width, -height, length);   // Bottom Left Of The Quad (Left) 
		glTexCoord2d(1.0f, 0.0f);   glVertex3f(-width, height, length);   // Bottom Right Of The Quad (Left)
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[3]);
		glBegin(GL_QUADS);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2d(0.0f, 1.0f);   glVertex3f(width, height, -length);   // Top Right Of The Quad (Right)
		glTexCoord2d(1.0f, 1.0f);   glVertex3f(width, height, length);   // Top Left Of The Quad (Right)
		glTexCoord2d(1.0f, 0.0f);   glVertex3f(width, -height, length);   // Bottom Left Of The Quad (Right)
		glTexCoord2d(0.0f, 0.0f);   glVertex3f(width, -height, -length);   // Bottom Right Of The Quad (Right)
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(1.0f, 0.0f);   glVertex3f(-width, -height, length);   // Top Right Of The Quad (Top)
		glTexCoord2d(1.0f, 1.0f);   glVertex3f(width, -height, length);   // Top Left Of The Quad (Top)
		glTexCoord2d(0.0, 1.0f);   glVertex3f(width, -height, -length);   // Bottom Left Of The Quad (Top)
		glTexCoord2d(0.0, 0.0f);   glVertex3f(-width, -height, -length);   // Bottom Right Of The Quad (Top)
		glEnd();
	}
	glPopMatrix();
}

void OBJLoader::FreeTexture(GLuint texture)
{
	glDeleteTextures(1, &texture);
}
