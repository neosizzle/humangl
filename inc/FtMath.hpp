#ifndef __FTMATH__H__
#define __FTMATH__H__
#include "Matrix.hpp"
#include "Vector.hpp"
#include <iostream>
#include <cmath>

namespace ftm
{
	float radians(float degrees);

	/**
	 * Dot product of two vectors
	*/
	float dot(Vector v1, Vector v2);

	/**
	 * 	normalizes a vector, changes all magnitutde relative to 1
	*/
	Vector normalize(Vector vect);

	/**
	 * Cross product of two vectors
	*/
	Vector cross(Vector v1, Vector v2);

	/**
	 * Gets the view matrix given the vectors
	*/
	Matrix lookAt(Vector position, Vector target, Vector up);

	/**
	 * generates perspective matrix
	*/
	Matrix perspective(float fovY, float aspect, float near, float far);

	/**
	 * Apply scale transformation to original matrix using
	 * The vector as scales
	*/
	Matrix scale(Matrix original, Vector scales);

	/**
	 * Apply translate transformation to original matrix using
	 * The vector as steps
	*/
	Matrix translate(Matrix original, Vector steps);

	/**
	 * Apply rotate transformation to original matrix
	*/
	Matrix rotate(Matrix original, float angle, Vector axis);

}//ftm


#endif  //!__FTMATH__H__