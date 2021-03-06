#include "pyramid.h"

using namespace std;

Pyramid::Pyramid(Mesh* mesh, Texture2D* texture, float x, float y, float z, int _id) : SceneObject(mesh)
{

	id = _id;

	r = ((_id & 0x000000FF) >> 0);
	g = ((_id & 0x0000FF00) >> 8);
	b = ((_id & 0x00FF0000) >> 16);

	_position = Vector3(x, y, z);
	_texture = texture;

	_material = new material();
	_material->ambient.x = 0.8; _material->ambient.y = 0.8; _material->ambient.z = 0.8; _material->ambient.w = 1.0;
	_material->diffuse.x = 0.8; _material->diffuse.y = 0.8; _material->diffuse.z = 0.8; _material->diffuse.w = 1.0;
	_material->specular.x = 0.1; _material->specular.y = 0.1; _material->specular.z = 0.1; _material->specular.w = 0.1;
	_material->shininess = 1.0f;

}

void Pyramid::Update()
{
	_rotation += 0.1f;
}

void Pyramid::Draw()
{

	if (_mesh->indexedVertices != nullptr && _mesh->indexedNormals != nullptr && _mesh->indices != nullptr)
	{
		glColor3ub(255,255,255);
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glScalef(1, 1, 1);
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_rotation, 0.0f, 1.0f, 0.0f);

		glEnable(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, _mesh->indexedNormals);

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, _mesh->indexedVertices);

		glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->ambient.x));
		glMaterialf(GL_FRONT, GL_SHININESS, _material->shininess);

		glTexCoordPointer(2, GL_FLOAT, 0, _mesh->TexCoords);
		glPushMatrix();
		glDrawElements(GL_TRIANGLES, _mesh->numIndices, GL_UNSIGNED_SHORT, _mesh->indices);
		glPopMatrix();

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glTranslatef(0, 0, 0);
	}
}


Pyramid::~Pyramid()
{

}