#pragma once

#include "GL\freeglut.h"
#include <math.h>

#ifndef _hStructs
#define _hStructs

	struct Vector3
	{
		float x, y, z;

		Vector3() : x(0), y(0), z(0) {}

		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

		void normalize()
		{
			int len = sqrt(x * x + y * y + z * z);

			if (len != 0.)
			{
				x /= len;
				y /= len;
				z /= len;
			}
		}

		Vector3 operator - (const Vector3& p)  const { return Vector3(x - p.x, y - p.y, z - p.z); }
		Vector3 operator -= (const Vector3& p)  const { return Vector3(x - p.x, y - p.y, z - p.z); }
		Vector3 operator += (const Vector3& p)  const { return Vector3(x + p.x, y + p.y, z + p.z); }
		Vector3 operator *= (int size)  const { return Vector3(x * size, y * size, z * size); }
		Vector3 operator * (int size)  const { return Vector3(x * size, y * size, z * size); }

		Vector3 Cross(Vector3 v_B) {
			Vector3 c_P;
			c_P.x = y * v_B.z - z * v_B.y;
			c_P.y = -(x * v_B.z - z * v_B.x);
			c_P.z = x * v_B.z - z * v_B.x;

			return c_P;
		}

		Vector3 inverse()
		{
			Vector3 c_P;

			c_P.x = -x;
			c_P.y = -y;
			c_P.z = -z;

			return c_P;
		}

	};

	struct Vector4
	{
		float x, y, z, w;

		Vector4() : x(0), y(0), z(0), w(0) {}

		Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
	};

	struct Camera
	{
		Vector3 eye, center, up;
	};

	struct Color
	{
		GLfloat r, g, b;
	};

	struct Vertex
	{
		GLfloat	x, y, z;
	};

	struct TexCoord
	{
		GLfloat u, v;
	};

	struct lighting
	{
		Vector4 ambient, diffuse, specular;
	};

	struct material
	{
		Vector4 ambient, diffuse, specular;
		GLfloat shininess;
	};

	struct Mesh
	{
		Vertex* indexedVertices;
		//Color* indexedColors;
		Vector3* indexedNormals;
		GLushort* indices;
		TexCoord* TexCoords;
		int numVertices, numNormals, numIndices, numTexCoords;
	};


#endif // !_hStructs