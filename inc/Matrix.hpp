#ifndef __MATRIX__H__
#define __MATRIX__H__
#include <string>
#include <vector>

/**
 * Square matrix
*/
class Matrix
{
private:
	float	*_arr;
	int		_dims;

public:
	Matrix(int size, std::vector<float> matrix);
	Matrix(int size, float init_value);
	~Matrix();

	std::string to_string();
	float *value_ptr() const;
	int	get_dims();
};

#endif  //!__MATRIX__H__