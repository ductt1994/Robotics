#ifndef MAT
#define MAT

#include <vector>

class mat
{
private:
	int m;
	int n;
	std::vector<double> matrix;

public:
	mat(int row, int col);

	double operator () (int row, int col);
	friend mat operator + (const mat& m1, const mat& m2);
	friend mat operator * (const mat& m1, const mat& m2);
	void operator = (const std::vector<double>& arr);
	void operator = (const mat& m1);

	void show();
	double det();
	mat inv();

	int size();
	~mat();
};

#endif