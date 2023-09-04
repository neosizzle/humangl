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

	/**
	 * generates perspective matrix
	*/
	Matrix perspective(float fovY, float aspect, float near, float far)
	{
		float tanHalfFovY = tan(fovY / 2);
		Matrix result(4, 0.0f);
		result.value_ptr()[0] = 1 / (aspect * tanHalfFovY);
		result.value_ptr()[5] = 1 / (tanHalfFovY);
		result.value_ptr()[10] = - (far / (far - near));
		result.value_ptr()[11] = -1;
		result.value_ptr()[14] = 2 * - ((far * near) / (far - near));
		return result;
	}

	/**
	 * Apply scale transformation to original matrix using
	 * The vector as scales
	*/
	Matrix scale(Matrix original, Vector scales)
	{
		if (original.get_dims() != 4 || scales.get_dims() != 3)
			throw std::string("scale(Matrix original, Vector scales): Invalid input");

		float *scales_arr = scales.value_ptr();
		float *original_arr = original.value_ptr();

		original_arr[0] *= scales_arr[0];
		original_arr[5] *= scales_arr[1];
		original_arr[10] *= scales_arr[2];

		return original;
	}

	/**
	 * Apply translate transformation to original matrix using
	 * The vector as steps
	*/
	Matrix translate(Matrix original, Vector steps)
	{
		if (original.get_dims() != 4 || steps.get_dims() != 3)
			throw std::string("translate(Matrix original, Vector steps): Invalid input");

		float *steps_arr = steps.value_ptr();
		float *original_arr = original.value_ptr();

		original_arr[12] = (steps_arr[0] * original_arr[0]);
		original_arr[13] = (steps_arr[1] * original_arr[5]);
		original_arr[14] = (steps_arr[2] * original_arr[10]);

		return original;
	}

	/**
	 * Apply rotate transformation to original matrix
	*/
	Matrix rotate(Matrix original, float angle, Vector axis)
	{
		if (original.get_dims() != 4 || axis.get_dims() != 3)
			throw std::string("rotate(Matrix original, float angle, Vector axis): Invalid input");

		Vector axis_normed = normalize(axis);
		float a = angle;
		float c = cos(a);
		float s = sin(a);
		Vector temp_matr = axis_normed * (1 - c);
		float *temp_arr = temp_matr.value_ptr();
		float *axis_arr = axis_normed.value_ptr();
		float *og_arr = original.value_ptr();
		int size = original.get_dims() * original.get_dims();
		std::vector<float> rotate_matrix;
		std::vector<float> result_matrix;

		// generate rotation matrix using axis
		rotate_matrix.push_back(c +  temp_arr[0] * axis_arr[0]);
		rotate_matrix.push_back(temp_arr[0] * axis_arr[1] + s * axis_arr[2]);
		rotate_matrix.push_back(temp_arr[0] * axis_arr[2] - s * axis_arr[1]);
		rotate_matrix.push_back(0);

		rotate_matrix.push_back(temp_arr[1] * axis_arr[0] - s * axis_arr[2]);
		rotate_matrix.push_back(c + temp_arr[1] * axis_arr[1]);
		rotate_matrix.push_back(temp_arr[1] * axis_arr[2] + s * axis_arr[0]);
		rotate_matrix.push_back(0);

		rotate_matrix.push_back(temp_arr[2] * axis_arr[0] + s * axis_arr[1]);
		rotate_matrix.push_back(temp_arr[2] * axis_arr[1] - s * axis_arr[0]);
		rotate_matrix.push_back(c + temp_arr[2] * axis_arr[2]);
		rotate_matrix.push_back(0);

		rotate_matrix.push_back(0.0f);
		rotate_matrix.push_back(0.0f);
		rotate_matrix.push_back(0.0f);
		rotate_matrix.push_back(0.0f);

		// apply rotation to og matrix
        std::vector<float> res_mags;
		// generate rows
		for (size_t curr_row = 0; curr_row < 3; curr_row++)
		{
			// for each row
			std::vector<float> res_row;
			for (size_t curr_col = 0; curr_col < 4; curr_col++)
			{
				// for each column
				res_row.push_back(0);
				// loop through curr row matrix B (rot matrix)
				for (size_t b_idx = 0, col_count = 0; b_idx < 4; b_idx++, col_count += 4)
				{
					// for each col in mat B, access index [colCount + currRow]
					// in matrix A (og matrix)
					int a_col = curr_col + col_count;
					int b_col = b_idx + (curr_row * 4);
					res_row[res_row.size() - 1] += og_arr[a_col] * rotate_matrix[b_col];
					
					// increment colCount by 4
				}
			}
			
			std::cout << "A " << og_matrix.to_string() << "\nB ";
			for (size_t i = 0; i < rotate_matrix.size(); i++)
			{
				std::cout << rotate_matrix[i] << " ";
			}
			

			// add to result matrix
			for (size_t i = 0; i < res_row.size(); i++)
				res_mags.push_back(res_row[i]);
		}

		// add last row to result values
		for (size_t i = 0; i < 4; i++)
		{
			res_mags.push_back(og_arr[i + (4 * 3)]);
		}
		
		
		return Matrix(4, res_mags);
	}

}//ftm


#endif  //!__FTMATH__H__