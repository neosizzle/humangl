#ifndef __VECTOR__H__
#define __VECTOR__H__
#include <string>
#include <vector>

/**
 * 1 x size Vector
*/
class Vector
{
private:
	float	*_arr;
	int		_dims;

public:
	Vector();
	Vector(const Vector &other);
	Vector(int size, std::vector<float> vect);
	Vector(int size, int init_value);
	~Vector();

	std::string to_string();
	float *value_ptr() const;
	int	get_dims() const;

	
	Vector operator =(Vector right);
	Vector operator +(Vector right);
	Vector operator -(Vector right);
};

#endif  //!__VECTOR__H__