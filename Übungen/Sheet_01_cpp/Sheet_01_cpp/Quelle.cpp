#include <iostream>
#include <vector>
#include "MAT.h"

#include <string>
#include <sstream>
#include <fstream>
constexpr auto PI = 3.14159265;

int main()
{

	//Exercise 1
	////////////////////////////////////////////////////////////////////////////////////
	//a)
	double theta = 90 * PI / 180;
	double D_x = 0;
	double D_y = 1;

	mat g_T_x1(3, 3);
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
								   0,					  0,  1 };

	gl_p1 = { 2,
			  3,
			  1 };


	mat x2_p1(3, 1);

	x2_p1 = x2_T_x1 * x1_T_g * gl_p1;

	std::cout << "x2_T_x1: " << std::endl;

	x2_p1.show();

	////////////////////////////////////////////////////////////////////////////////////
	//Exercise 2

	//Write a program that reads a txt file as an input and returns the sum of each row
	//Create a string stream
	std::ifstream inpstream("laserscan.dat.txt");
	if (inpstream.is_open() == false)
	{
		std::cout << "Failed to open file" << std::endl;
		return 1;
	}

	//Create a line to write all data into
	std::string line;
	std::string elem_str;
	double elem = 0;
	int i = 1;

	//Create a vector for the laser_data
	std::vector<double> laser_data;

	//Read one line from file
	while (std::getline(inpstream, line))
	{
		//Write that line into a string stream
		std::stringstream ss(line);

		/*std::cout << line << std::endl;*/

		//Read the line until end of line/end of file
		while (ss.eof() == false)
		{
			//Split the string stream at " "
			std::getline(ss, elem_str, ' ');

			//Convert the read elemet to integer
			if (elem_str != "\0")
			{
				elem = std::stod(elem_str);
			}

			//Add the input to the laser_data vector
			laser_data.push_back(elem);
		}

	}

	//Get the number of data points
	int num_pts;
	num_pts = laser_data.size();

	//Create the vector for the angle values
	std::vector<double> angles;
	double ang = -PI / 2;

	for (int i = 0; i < num_pts; i++)
	{
		ang += PI / num_pts;
		angles.push_back(ang);
	}

	////////////////////////////////////////////////////////////////////////////////////
	//a)
	//Calculate and plot all points w.r.t. local frame
	std::vector<double> x_local, y_local;
	double x, y, l;

	for (int i = 0; i < num_pts; i++)
	{
		l = laser_data[i];
		ang = angles[i];
		x = cos(ang) * l;
		y = sin(ang) * l;

		x_local.push_back(x);
		y_local.push_back(y);
	}

	//Write x_local and y_local to a file
	std::ofstream out_local("xy_local.txt");
	if (out_local.is_open() == false)
	{
		std::cout << "Failed to open file" << std::endl;
		return 1;
	}
	else
	{
		for (int i = 0; i < num_pts; i++)
		{
			out_local << x_local[i] << " " << y_local[i] << std::endl;
		}
		out_local.close();
	}

	////////////////////////////////////////////////////////////////////////////////////
	//c)
	//Calculate and plot all points w.r.t. global frame
	//Calculate the transformation matrix from the range finder to the local reference
	mat L_T_Rf(3, 3);
	double x_rf, y_rf, ang_rf;
	x_rf = 0.2;
	y_rf = 0;
	ang_rf = PI;

	L_T_Rf = { cos(ang_rf), -sin(ang_rf),  x_rf,
			   sin(ang_rf),  cos(ang_rf),  y_rf,
						0,			   0,	  1 };


	mat G_T_L(3, 3);
	double x_gl, y_gl, ang_gl;
	x_gl = 1;
	y_gl = 0.5;
	ang_gl = PI / 4;

	G_T_L = { cos(ang_gl), -sin(ang_gl),  x_gl,
			  sin(ang_gl),  cos(ang_gl),  y_gl,
						0,			  0,	 1 };

	//Calculate the measurements w.r.t global
	std::vector<double> x_global, y_global;
	mat rf_p(3, 1);
	mat gl_p(3, 1);

	for (int i = 0; i < num_pts; i++)
	{
		l = laser_data[i];
		ang = angles[i];

		rf_p = { cos(ang) * l ,
				 sin(ang) * l ,
							1 };

		gl_p = G_T_L * L_T_Rf * rf_p;

		x_global.push_back(gl_p(0, 0));
		y_global.push_back(gl_p(1, 0));

	}

	//Add the center of the robot and the center of the range finder to the solution
	mat pos_robot(3, 1);
	mat pos_rngfd(3, 1);
	mat gl_robot(3, 1);
	mat gl_rngfd(3, 1);

	pos_robot = { 0,0,1 };
	pos_rngfd = { x_rf,
				  y_rf,
					 1 };

	gl_robot = G_T_L * pos_robot;
	gl_rngfd = G_T_L * pos_rngfd;

	//Write x_global and y_gobal to a file
	std::ofstream out_global("xy_global.txt");
	if (out_global.is_open() == false)
	{
		std::cout << "Failed to open file" << std::endl;
		return 1;
	}
	else
	{
		for (int i = 0; i < num_pts; i++)
		{
			out_global << x_global[i] << " " << y_global[i] << std::endl;
		}
		//out_global.close();
	}

	//Add the coordinates of the robot and the rangefinder
	out_global << gl_robot(0, 0) << " " << gl_robot(1, 0) << std::endl;
	out_global << gl_rngfd(0, 0) << " " << gl_rngfd(1, 0) << std::endl;
	out_global.close();

	return 0;
}