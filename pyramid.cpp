#include "pyramid.h"

using namespace std;

Pyramid::Pyramid(Mesh* mesh, float x, float y, float z) : SceneObject(mesh)
{

	_position = Vector3(x, y, z);

}

void Pyramid::Update()
{
	//_rotation += 0.1f;
}

void Pyramid::Draw()
{

	if (_mesh->indexedVertices != nullptr && _mesh->indexedColors != nullptr && _mesh->indices != nullptr)
	{
		glScalef(1,1,1);
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 1.0f, 0.0f, 0.0f);


		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->indexedVertices);
		glColorPointer(3, GL_FLOAT, 0, _mesh->indexedColors);

		glPushMatrix();
		glDrawElements(GL_TRIANGLES, _mesh->numIndices, GL_UNSIGNED_SHORT, _mesh->indices);
		glPopMatrix();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glTranslatef(0, 0, 0);
	}
}


Pyramid::~Pyramid()
{

}