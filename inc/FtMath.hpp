#ifndef __FTMATH__H__
#define __FTMATH__H__
#include "Vector.hpp"

namespace ftm
{
	float radians(float degrees)
	{
		return degrees / 180 * 3.142;
	}

	/**
	 * Dot product of two vectors
	*/
	float dot(Vector v1, Vector v2)
	{
		float res = 0;
		float* v1_arr = v1.value_ptr();
		float* v2_arr = v2.value_ptr();

		if (v1.get_dims() != v2.get_dims())
			throw "ftm::dot(Vector v1, Vector v2): Different sizes";

		for (size_t i = 0; i < v1.get_dims(); i++)
			res += v1_arr[i] * v2_arr[i];

		return res;
	}

	/**
	 * 	normalizes a vector, changes all magnitutde relative to 1
	*/
	Vector normalize(Vector vect)
	{
		if (vect.get_dims() != 3)
			throw std::string("normalize(Vector vect): Cant normalize non length 3 vector");
		
		float x = vect.value_ptr()[0];
		float y = vect.value_ptr()[1];
		float z = vect.value_ptr()[2];
		float length_of_v = sqrt((x * x) + (y * y) + (z * z));
		std::vector<float> new_mags = {x / length_of_v, y / length_of_v, z / length_of_v};

   		return Vector(3, new_mags);
	}

	/**
	 * Cross product of two vectors
	*/
	Vector cross(Vector v1, Vector v2)
	{
		if (v1.get_dims() != 3 || v2.get_dims() != 3)
			throw std::string("cross(Vector v1, Vector v2): Cant compute if vector sizes not 3");
		
		float x1 = v1.value_ptr()[0];
		float y1 = v1.value_ptr()[1];
		float z1 = v1.value_ptr()[2];
		
		float x2 = v2.value_ptr()[0];
		float y2 = v2.value_ptr()[1];
		float z2 = v2.value_ptr()[2];

		std::vector<float> new_mags = { y1 * z2 - z1 * y2, z1 * x2 - x1 * z2, x1 * y2 - y1 * x2};
		return Vector(3, new_mags);
	}

	/**
	 * Gets the view matrix given the vectors
	*/
	Matrix lookAt(Vector position, Vector target, Vector up)
	{
		std::vector<float> new_mags;
		Vector Z = normalize(position - target);
		Vector X = normalize(cross(normalize(up), Z));
		Vector Y = cross(Z, X);
		float *Zptr = Z.value_ptr();
		float *Xptr = X.value_ptr();
		float *Yptr = Y.value_ptr();

		new_mags.push_back(Xptr[0]);
		new_mags.push_back(Yptr[0]);
		new_mags.push_back(Zptr[0]);
		new_mags.push_back(0);

		new_mags.push_back(Xptr[1]);
		new_mags.push_back(Yptr[1]);
		new_mags.push_back(Zptr[1]);
		new_mags.push_back(0);

		new_mags.push_back(Xptr[2]);
		new_mags.push_back(Yptr[2]);
		new_mags.push_back(Zptr[2]);
		new_mags.push_back(0);

		new_mags.push_back(- dot(X, position));
		new_mags.push_back(- dot(Y, position));		
		new_mags.push_back(- dot(Z, position));		
		new_mags.push_back(1);

		return Matrix(4, new_mags);
	}
}//ftm


#endif  //!__FTMATH__H__