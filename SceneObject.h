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

	};


#endif // !_SceneObject