#pragma once

#ifndef _MeshLoader
#define _MeshLoader

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>


#ifndef _hStructs
#include "Structures.h"
#endif

	namespace MeshLoader
	{
		Mesh* Load(char* path);
	};



#endif // !_MeshLoader
