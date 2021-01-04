#include "MAT.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

//Constructor
mat::mat(int row, int col)
{
	m = row;
	n = col;
	matrix.assign(m * n, 0);
};

//Return value at index
double mat::operator()(int row, int col)
{
	return matrix[row * n + col];
}

//Assign new values
void mat::operator=(const std::vector<double> &arr)
{
	matrix.assign(std::begin(arr), std::end(arr));
}

void mat::operator=(const mat& m1)
{
	matrix.assign(std::begin(m1.matrix), std::end(m1.matrix));
}

mat operator+(const mat& m1, const mat& m2)
{
	//Check if both matrices have the same dimensions
	if (m1.m == m2.m && m1.n == m2.n)
	{
		//Create result matrix
		mat m3(m1.m, m1.n);
		int m3_sz = m3.size();

		//Loop over the result matrix col->row
		for (int i = 0; i < m3_sz; i++)
		{
			m3.matrix[i] = m1.matrix[i] + m2.matrix[i];
		}

		return m3;
	}
	else
	{
		std::cout << "Matrix dimensions must agree" << std::endl;
		throw - 1;
	}
}

mat operator*(const mat& m1, const mat& m2)
{
	//Check if both matrices have the same dimensions
	if (m1.n == m2.m)
	{
		//Create result matrix
		mat m3(m1.m, m2.n);
		int m3_sz = m3.size();
		int m_crr = 0, n_crr = 0;

		//Read m2.row as int value for length limit in second loop
		int lmt = m2.m;

		//Loop over the result matrix col->row
		for (int i = 0; i < m3_sz; i++)
		{
			//Calculate the current row and column
			m_crr = i / m3.n;
			n_crr = i % m3.n;
			double res = 0;
			
			for (int j = 0; j < lmt; j++)
			{
				//Sum up values at current index i
				res += m1.matrix[m_crr * m1.n + j] * m2.matrix[j * m2.n + n_crr];
			}

			m3.matrix[i] = res;

		}

		return m3;
	}
	else
	{
		std::cout << "Number of Matrix 1 columns must agree with number of Matrix 2 rows." << std::endl;
		throw - 1;
	}
}

//Display the matrix
void mat::show()
{
	std::cout.precision(4);

	int mat_sz = matrix.size();
	for (int i = 0; i < mat_sz; i++)
	{
		std::cout << std::right << std::setw(12) << std::fixed << matrix[i];

		if ((i+1) % n == 0)
		{
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

double mat::det()
{
	//Check if the matrix is quadratic
	if (m == n)
	{
		//Make a temporary calculation copy of the original matrix
		mat tmp(m, n);
		tmp.matrix = matrix;

		//Loop over each column
		double det_fact = 1;
		int swap_ct = 0;
		int pv_idx = 0;

		for (int i = 0; i < n; i++)
		{
			//Display all elements starting from the pivot element
			pv_idx = (i * n) + i;

			//Number of elements in current col = m - i
			std::vector <double> col;

			//Extract current column
			for (int j = 0; j < (m-i); j++)
			{
				//Row index in current column
				int pv_col_idx = 0;
				pv_col_idx = pv_idx + j * n;
				col.push_back(std::abs(tmp.matrix[pv_col_idx]));
			}

			//Extract the maximum absolute value
			std::vector<double>::iterator max_it;
			int col_idx = 0;
			int row_idx = 0;
			max_it = std::max_element(col.begin(),col.end());
			col_idx = max_it - col.begin();
			row_idx = (col_idx)*n + pv_idx;

			//Pivot element is not the same as the max_elem -> swap necessary
			if (tmp.matrix[pv_idx] != *max_it)
			{
				swap_ct++;
				for (int j = 0; j < (n - i); j++)
				{
					//Swap the rows so that max value is the new pivot element
					std::swap(tmp.matrix[pv_idx + j], tmp.matrix[row_idx + j]);
				}
			}

			//Calculate the triangle matrix
			//Loop over row values in pivot element column but not including the pivot element
			for (int j = 1; j < (m - i); j++)
			{
				if (tmp.matrix[pv_idx + j * n] == 0)
				{
					//Element in pivot column is zero -> skip
					continue;
				}
				else
				{
					//Caclulate the factor to reach zero after addition
					double fact = -(tmp.matrix[pv_idx]) / (tmp.matrix[pv_idx + j * n]);
					det_fact *= fact;

					//Recalculate the non zero row
					for (int k = 0; k < (n - i); k++)
					{
						int crr_idx = (pv_idx + j * n) + k;
						tmp.matrix[crr_idx] = tmp.matrix[crr_idx] * fact + tmp.matrix[pv_idx + k];
					}
				}
			}
		}

		//Calculate the determinant
		double det = 1;
		for (int i = 0; i < n; i++)
		{
			int pv_idx = 0;
			pv_idx = (i * n) + i;
			det *= tmp.matrix[pv_idx];
		}

		det = det / det_fact;

		if (swap_ct % 2 != 0)
		{
			det = -det;
		}

		return det;
	}
	else
	{
		std::cout << "Matrix is not quadratic." << std::endl;
		throw -1;
	}
}

mat mat::inv()
{
	//Check if the matrix is quadratic
	if (m == n)
	{
		//Create the unity matrix and the temporary calculation matrix
		mat tmp(m, n);
		tmp.matrix = matrix;

		mat unity_mat(m, n);
		int pv_idx = 0;
		for (int i = 0; i < n; i++)
		{
			pv_idx = (i * n) + i;
			unity_mat.matrix[pv_idx] = 1;
		}

		//Loop over each column
		double det_fact = 1;
		int swap_ct = 0;
		for (int i = 0; i < n; i++)
		{
			//Display all elements starting from the pivot element
			pv_idx = (i * n) + i;

			//Number of elements in current col = m - i
			std::vector <double> col;

			//Extract current column
			for (int j = 0; j < (m - i); j++)
			{
				//Row index in current column
				int pv_col_idx = 0;
				pv_col_idx = pv_idx + j * n;
				col.push_back(std::abs(tmp.matrix[pv_col_idx]));
			}

			//Extract the maximum absolute value
			std::vector<double>::iterator max_it;
			int col_idx = 0;
			int row_idx = 0;

			max_it = std::max_element(col.begin(), col.end());
			col_idx = max_it - col.begin();
			row_idx = (col_idx)*n + pv_idx;

			//Pivot element is not the same as the max_elem -> swap necessary
			if (tmp.matrix[pv_idx] != *max_it)
			{
				swap_ct++;
				for (int j = 0; j < n; j++)
				{
					//Swap the complete row so that max value is the new pivot element
					std::swap(tmp.matrix[i * n + j], tmp.matrix[(i + col_idx) * n + j]);
					std::swap(unity_mat.matrix[i * n + j], unity_mat.matrix[(i + col_idx) * n + j]);
				}
			}

			//Calculate the triangle matrix
			//Loop over row values in pivot element column but not including the pivot element
			for (int j = 1; j < (m - i); j++)
			{
				if (tmp.matrix[pv_idx + j * n] == 0)
				{
					//Element in pivot column is zero -> skip
					continue;
				}
				else
				{
					double fact = -(tmp.matrix[pv_idx]) / (tmp.matrix[pv_idx + j * n]);
					det_fact *= fact;

					//Recalculate the non zero row in current matrix and in the unity matrix
					//for the complete row
					for (int k = 0; k < n; k++)
					{
						//std::swap(matrix[i * n + j], matrix[(i + col_idx) * n + j]);
						int crr_idx = (i + j) * n + k;
						tmp.matrix[crr_idx] = tmp.matrix[crr_idx] * fact + tmp.matrix[i * n + k];
						unity_mat.matrix[crr_idx] = unity_mat.matrix[crr_idx] * fact + unity_mat.matrix[i * n + k];
					}
				}
			}
		}

		//Calculate the determinant
		double det = 1;
		for (int i = 0; i < n; i++)
		{
			int pv_idx = 0;
			pv_idx = (i * n) + i;
			det *= tmp.matrix[pv_idx];
		}

		det = det / det_fact;

		if (swap_ct % 2 != 0)
		{
			det = -det;
		}

		if (det != 0)
		{
			//double res_rev_fact = 0;
			double rev_fact = 0;
			/////////////////////////////////////////////////////////////////////////////////////
			//Calculate the inverse
			for (int i = 0; i < m; i++)
			{
				//Extract the pivot element of each row
				pv_idx = (i * n) + i;
				double pv_elem = tmp.matrix[pv_idx];

				//Transform the current main diagonal element to "one" for every column
				for (int j = 0; j < n; j++)
				{
					tmp.matrix[i * n + j] = tmp.matrix[i *n + j] / pv_elem;
					unity_mat.matrix[i * n + j] = unity_mat.matrix[i * n + j] / pv_elem;
				}
			}

			//Step up the triangle matrix backwards
			for (int i = m - 1; i >= 0; i--)
			{
				//Transform every row above the current row
				//Extract the pivot element of each row
				pv_idx = (i * n) + i;
				double pv_elem = tmp.matrix[pv_idx];

				//Transform every row above the current row
				for (int j = 1; j <= i; j++)
				{
					rev_fact = tmp.matrix[pv_idx - j * n];

					for (int k = 0; k < n; k++)
					{
						tmp.matrix[(i - j) * n + k] = tmp.matrix[(i - j) * n + k] - tmp.matrix[i * n + k] * rev_fact;
						unity_mat.matrix[(i - j) * n + k] = unity_mat.matrix[(i - j) * n + k] - unity_mat.matrix[i * n + k] * rev_fact;
					}
				}
			}

			//Perform check for negative zeros
			for (int i = 0; i < m*n; i++)
			{
				if (abs(unity_mat.matrix[i]) <= 1e-12)
				{
					unity_mat.matrix[i] = 0;
				}
			}

			for (int i = 0; i < m * n; i++)
			{
				if (abs(tmp.matrix[i]) <= 1e-12)
				{
					tmp.matrix[i] = 0;
				}
			}

			return unity_mat;
		}
		else
		{
			std::cout << "Matrix has no inverse." << std::endl;
			throw - 1;
		}
	}
	else
	{
		std::cout << "Matrix is not quadratic." << std::endl;
		throw -1;
	}
}

//Get matrix size
int mat::size()
{
	return matrix.size();
}

//Deconstructor
mat::~mat()
{
}
