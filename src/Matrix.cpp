#include "Matrix.hpp"

Matrix::Matrix()
{
	this->_dims = 4;
	this->_arr = new float[4 * 4 ];
	for (size_t i = 0; i < 4 * 4; i++)
		this->_arr[i] = 0;
}

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
	if (this->_arr)
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

int Matrix::get_dims() const
{
	return this->_dims;
}

Matrix Matrix::operator+(Matrix right)
{
	std::vector<float> res_arr;
	float* v1_arr = this->value_ptr();
	float* v2_arr = right.value_ptr();
	float length = this->_dims * this->_dims;

	if (this->_dims != right.get_dims())
		throw std::string("Matrix::operator+(Matrix right): Different sizes");

	for (size_t i = 0; i < length; i++)
		res_arr.push_back(v1_arr[i] + v2_arr[i]);

	Matrix newVect(this->get_dims(), res_arr);
	return newVect;
}

Matrix Matrix::operator-(Matrix right)
{
	std::vector<float> res_arr;
	float* v1_arr = this->value_ptr();
	float* v2_arr = right.value_ptr();
	float length = this->_dims * this->_dims;

	if (this->_dims != right.get_dims())
		throw std::string("Matrix::operator+(Matrix right): Different sizes");

	for (size_t i = 0; i < length; i++)
		res_arr.push_back(v1_arr[i] - v2_arr[i]);

	Matrix newVect(this->get_dims(), res_arr);
	return newVect;
}

Matrix Matrix::operator=(Matrix right)
{
	float *vect = right.value_ptr();
	int size = right.get_dims();

	this->_dims = size;
	this->_arr = new float[size];
	size *= size;
	for (size_t i = 0; i < size; i++)
		this->_arr[i] = vect[i];

	return *this;
}

Matrix::Matrix(const Matrix &right)
{
	float *vect = right.value_ptr();
	int size = right.get_dims();
	
	this->_dims = size;
	size *= size;
	this->_arr = new float[size];
	for (size_t i = 0; i < size; i++)
		this->_arr[i] = vect[i];
}