#include "Matrix.hpp"
#include <iostream>

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
	
	for (int i = 0; i < length; i++)
		this->_arr[i] = matrix[i];
}

Matrix::Matrix(int size, float init_value) : _dims(size) {
	int length = size * size;
	this->_arr = new float[length];
	int size_ctr = size;

	for (int i = 0; i < length; i++)
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
		delete[] this->_arr;
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

	for (int i = 0; i < length; i++)
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

	Matrix newMat(this->get_dims(), res_arr);
	return newMat;
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

	Matrix newMat(this->get_dims(), res_arr);
	return newMat;
}

Matrix Matrix::operator=(Matrix right)
{
	float *vect = right.value_ptr();
	int size = right.get_dims();

	this->_dims = size;
	size *= size;
	if (this->_arr)
		delete[] this->_arr;
	this->_arr = new float[size];
		for (int i = 0; i < size; i++)
		this->_arr[i] = vect[i];

	return *this;
}

Matrix Matrix::operator*(float mag)
{
	std::vector<float> res_arr;
	float* v1_arr = this->value_ptr();
	float length = this->_dims * this->_dims;

	for (size_t i = 0; i < length; i++)
		res_arr.push_back(v1_arr[i] * mag);

	Matrix newMat(this->get_dims(), res_arr);
	return newMat;
}

Matrix Matrix::operator+=(Matrix right)
{
	Matrix newMat = *this + right;
	float *vect = newMat.value_ptr();
	int size = newMat.get_dims();

	// copy elements
	size *= size;
	for (int i = 0; i < size; i++)
		this->_arr[i] = vect[i];

	return *this;
}

Matrix Matrix::operator-=(Matrix right)
{
	Matrix newMat = *this - right;
	float *vect = newMat.value_ptr();
	int size = newMat.get_dims();

	// copy elements
	size *= size;
	for (int i = 0; i < size; i++)
		this->_arr[i] = vect[i];

	return *this;
}

Matrix Matrix::operator*(Matrix right)
{
	std::vector<float> res_arr;

	if (this->_dims != right.get_dims())
		throw std::string("Matrix::operator*(Matrix right): Different sizes");

	// generate rows
	for (int curr_row = 0; curr_row < this->_dims; curr_row++)
	{
		std::vector<float> res_row;
		// generate columns
		for (int curr_col = 0; curr_col < this->_dims; curr_col++)
		{
			float res_val = 0.0f;

			// get starting row index for mat A
			int curr_row_a = curr_row * this->_dims;

			// get starting col index for mat B
			int curr_col_b = curr_col;

			// do the dot product thingy on A's row and B's column
			for (int i = 0; i < this->_dims; i++)
			{
				res_val += this->_arr[curr_row_a] * right.value_ptr()[curr_col_b];
				++curr_row_a;
				curr_col_b += this->_dims;
			}
			res_row.push_back(res_val);
		}
		// add rows to res_arr
		for (size_t i = 0; i < res_row.size(); i++)
			res_arr.push_back(res_row[i]);
	}

	Matrix newMat(this->get_dims(), res_arr);
	return newMat;
}

Matrix::Matrix(const Matrix &right)
{
	float *vect = right.value_ptr();
	int size = right.get_dims();
	
	this->_dims = size;
	size *= size;
	this->_arr = new float[size];
	for (int i = 0; i < size; i++)
		this->_arr[i] = vect[i];
}