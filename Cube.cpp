#include "Cube.h"

using namespace std;

Cube::Cube(Mesh* mesh, Texture2D* text, float x, float y, float z) : SceneObject(mesh)
{

	_position = Vector3(x, y, z);
	_texture = text;

}

void Cube::Update()
{
	//_rotation += 0.1f;
}

void Cube::Draw()
{

	if (_mesh->indexedVertices != nullptr && _mesh->indexedColors != nullptr && _mesh->indices != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glScalef(1, 1, 1);
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 0.0f, 1.0f, 0.0f);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->indexedVertices);
		glColorPointer(3, GL_FLOAT, 0, _mesh->indexedColors);

		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);
		glPushMatrix();
		glDrawElements(GL_TRIANGLES, _mesh->numIndices, GL_UNSIGNED_SHORT, _mesh->indices);
		glPopMatrix();

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glTranslatef(0, 0, 0);
	}
}


Cube::~Cube()
{

}