#include <iostream>
#include <vector>
#include "MAT.h"
constexpr auto PI = 3.14159265;

int main()
{

	//Exercise 1
	////////////////////////////////////////////////////////////////////////////////////
	//a)
	double theta = 90 * PI / 180;
	double D_x = 0;
	double D_y = 1;

	mat g_T_x1(3,3);
	g_T_x1 = { cos(theta), -sin(theta), D_x,
			   sin(theta),	cos(theta), D_y,
					    0,			 0,   1 };;

	mat x1_p1(3, 1);

	x1_p1 = { 2,
			 -2,
			  1 };;

	mat gl_p1(3, 1);
	gl_p1 = g_T_x1 * x1_p1;

	std::cout << "p1 in global: " << std::endl;
	gl_p1.show();

	////////////////////////////////////////////////////////////////////////////////////
	//b)
	mat x1_T_g(3, 3);
	x1_T_g = g_T_x1.inv();

	gl_p1 = { 2,
			  3,
			  1 };;

	x1_p1 = x1_T_g * gl_p1;

	std::cout << "p1 in x1: " << std::endl;
	x1_p1.show();

	////////////////////////////////////////////////////////////////////////////////////
	//d)

	x1_T_g = { cos(-90 * PI / 180), -sin(-90 * PI / 180), -1,
			   sin(-90 * PI / 180),  cos(-90 * PI / 180),  0,
								 0,					   0,  1 };
	
	mat x2_T_x1(3, 3);
	x2_T_x1 = { cos(-180 * PI / 180), -sin(-180 * PI / 180), -2,
				sin(-180 * PI / 180),  cos(-180 * PI / 180),  1,
								   0,					  0,  1 };;

	gl_p1 = { 2,
			  3,
			  1 };


	mat x2_p1(3, 1);

	x2_p1 = x2_T_x1 * x1_T_g * gl_p1;

	std::cout << "x2_T_x1: " << std::endl;

	x2_p1.show();

	return 0;
}