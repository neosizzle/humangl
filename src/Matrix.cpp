#include "Matrix.hpp"

Matrix::Matrix(int size, std::vector<float> matrix) : _dims(size) {
	int length = size * size;
	this->_arr = new float[length];
	
	for (size_t i = 0; i < length; i++)
		this->_arr[i] = matrix[i];
}

Matrix::Matrix(int size, float init_value) : _dims(size) {
	int length = size * size;
	this->_arr = new float[length];
	int size_ctr = size;

	for (size_t i = 0; i < length; i++)
	{
		if (size_ctr == size)
			this->_arr[i] = init_value;
		else
			this->_arr[i] = 0;

		if (size_ctr == 0)
			size_ctr = size;
		else
			--size_ctr;
	}
}

Matrix::~Matrix()
{
	delete this->_arr;
}

float *Matrix::value_ptr() const
{
	return this->_arr;
}

std::string Matrix::to_string()
{
	std::string res;
	int length = this->_dims * this->_dims;
	int size_ctr = 1;

	// for (size_t i = 0; i < this->_dims; i++)
	// {
	// 	for (size_t j = 0; j < this->_dims; j++)
	// 	{
	// 		res += std::to_string(this->_arr[i][j]);
	// 		res += ", ";
	// 	}
	// 	res += "\n";
	// }
	for (size_t i = 0; i < length; i++)
	{
		res += std::to_string(this->_arr[i]);
		if (size_ctr != this->_dims)
			res += ", ";
		else
			res += "\n";

		if (size_ctr == this->_dims)
			size_ctr = 1;
		else
			++size_ctr;	
	}
	

	return res;
}

int Matrix::get_dims()
{
	return this->_dims;
}