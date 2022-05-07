#include "std_lib_facilities.h"
void swap_v(int a, int b)
{
	int temp; temp = a, a = b; b = temp;
}

void swap_r(int& a, int& b)
{
	int temp; temp = a, a = b; b = temp;
}

//The function can't compile because we can't assign values to constant variables.
/*
void swap_cr(const int& a, const int& b)
{
	int temp; temp = a, a = b; b = temp;
}
*/

int main()
{
	int x = 7;
	int y = 9;
	swap_v(x, y); //This function compiled but they were not swapped.
	swap_r(x, y); //This function compiled and they were swapped.
	swap_v(7, 9); //This function compiled but they were not swapped.
	swap_r(7, 9); //This function cannot be compiled.
	const int cx = 7;
	const int cy = 9;
	swap_v(cx, cy); //This function compiled but they were not swapped.
	swap_r(cx, cy);  //This function cannot be compiled.
	swap_v(7.7, 9.9); //This function compiled but they were not swapped.
	swap_r(7.7, 9.9); //This function cannot be compiled.
	double dx = 7.7;
	double dy = 9.9;
	swap_v(dx, dy); //This function compiled but they were not actually swapped.
	swap_r(dx, dy);  //This function cannot be compiled.
	swap_v(7.7, 9.9); //This function compiled but they were not swapped.
	swap_r(7.7, 9.9); //This function cannot be compiled.
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
	cout << "cx = " << cx << endl;
	cout << "cy = " << cy << endl;
	cout << "dx = " << dx << endl;
	cout << "dy = " << dy << endl;
	return 0;
}
