#pragma once

#ifndef _SceneObject
#define _SceneObject

#ifndef _hStructs
#include "Structures.h"
#endif

	class SceneObject
	{
	protected:
		Mesh* _mesh;

	public:
		SceneObject(Mesh* mesh);
		virtual ~SceneObject();

		virtual void Update();
		virtual void Draw();

		GLfloat _rotation = 0;
		Vector3 _position;

		char name[64];

	};


#endif // !_SceneObject