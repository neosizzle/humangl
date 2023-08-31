#include "Vector.hpp"
#include "Logger.hpp"
#include <exception>

Vector::Vector()
{
	this->_dims = 3;
	this->_arr = new float[3];
	for (size_t i = 0; i < 3; i++)
		this->_arr[i] = 0;
}

Vector::Vector(int size, std::vector<float> vect) : _dims(size) {
	this->_arr = new float[size];
	for (size_t i = 0; i < size; i++)
		this->_arr[i] = vect[i];
}

Vector::Vector(int size, int init_value) : _dims(size) {
	this->_arr = new float[size];
	for (size_t i = 0; i < size; i++)
		this->_arr[i] = init_value;
}

Vector::~Vector()
{
	if (this->_arr)
		delete this->_arr;
}

std::string Vector::to_string()
{
	std::string res;

	for (size_t i = 0; i < this->_dims; i++)
	{
		res += std::to_string(this->_arr[i]);
		res += ", \n";
	}

	return res;
}

float *Vector::value_ptr() const
{
	return this->_arr;
}

int Vector::get_dims() const
{
	return this->_dims;
}

Vector Vector::operator+(Vector right)
{
	std::vector<float> res_arr;
	float* v1_arr = this->value_ptr();
	float* v2_arr = right.value_ptr();

	if (this->_dims != right.get_dims())
		throw std::string("Vector::operator+(Vector right): Different sizes");

	for (size_t i = 0; i < this->_dims; i++)
		res_arr.push_back(v1_arr[i] + v2_arr[i]);

	Vector newVect(this->get_dims(), res_arr);
	return newVect;
}

Vector Vector::operator-(Vector right)
{
	std::vector<float> res_arr;
	float* v1_arr = this->value_ptr();
	float* v2_arr = right.value_ptr();

	if (this->_dims != right.get_dims())
		throw std::string("Vector::operator+(Vector right): Different sizes");

	for (size_t i = 0; i < this->_dims; i++)
		res_arr.push_back(v1_arr[i] - v2_arr[i]);

	Vector newVect(this->get_dims(), res_arr);
	return newVect;
}

Vector Vector::operator=(Vector right)
{
	float *vect = right.value_ptr();
	int size = right.get_dims();

	this->_dims = size;
	this->_arr = new float[size];
	for (size_t i = 0; i < size; i++)
		this->_arr[i] = vect[i];

	return *this;
}

Vector::Vector(const Vector &right)
{
	float *vect = right.value_ptr();
	int size = right.get_dims();

	this->_dims = size;
	this->_arr = new float[size];
	for (size_t i = 0; i < size; i++)
		this->_arr[i] = vect[i];
}