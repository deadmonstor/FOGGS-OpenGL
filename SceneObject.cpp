#include "SceneObject.h"

#include <iostream>

SceneObject::SceneObject(Mesh* mesh)
{
	_mesh = mesh;
}

SceneObject::~SceneObject()
{

}

void SceneObject::Update() 
{

}

void SceneObject::Draw() 
{

}

void SceneObject::DrawBasic()
{

	if (_mesh->indexedVertices != nullptr && _mesh->indexedNormals != nullptr && _mesh->indices != nullptr)
	{

		glScalef(1, 1, 1);
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 0.0f, 1.0f, 0.0f);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->indexedVertices);
		glShadeModel(GL_SMOOTH);

		glDisable(GL_TEXTURE_2D);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_DIFFUSE);
		glDisable(GL_LIGHTING);
		glColor3ub(r,g,b);

		glPushMatrix();
			glDrawElements(GL_TRIANGLES, _mesh->numIndices, GL_UNSIGNED_SHORT, _mesh->indices);
			glDisable(GL_COLOR_MATERIAL);
		glPopMatrix();

		glDisableClientState(GL_VERTEX_ARRAY);
		glTranslatef(0, 0, 0);
	}
}