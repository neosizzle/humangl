#ifndef __FTMATH__H__
#define __FTMATH__H__
#include "Vector.hpp"

namespace ftm
{
	Vector dot(Vector v1, Vector v2)
	{
		std::vector<float> res_arr;
		float* v1_arr = v1.value_ptr();
		float* v2_arr = v2.value_ptr();

		if (v1.get_dims() != v2.get_dims())
			throw "ftm::dot(Vector v1, Vector v2): Different sizes";

		for (size_t i = 0; i < v1.get_dims(); i++)
			res_arr.push_back(v1_arr[i] * v2_arr[i]);

		return Vector(v1.get_dims(), res_arr);
	}
}//ftm


#endif  //!__FTMATH__H__