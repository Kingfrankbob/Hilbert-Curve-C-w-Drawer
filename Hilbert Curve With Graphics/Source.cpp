#include <iostream>
#include <fstream>
//#include "graphics.h"
//#pragma comment(lib,"graphics.lib")
#include <math.h>
#pragma warning(disable : 4996)


long int ycoor[10000000] = { 0 },xcoorop[10000000], xcoor[10000000] = { 0 }, LO = 0;
int yCheck, xCheck, SPACE;
char f;


void move(int j, int h, int& x, int& y)
{

	if (j == 1) y -= h;
	else if (j == 2) x += h;
	else if (j == 3) y += h;
    else if (j == 4) x -= h;

	//std::cout << x << ' ' << y << ' ';

//lineto(x, y);

xcoor[LO] += x;
ycoor[LO] += y;
std::cout << x << ", " << y << '\n';

LO++;

}


void hilbert(int r, int d, int t, int u, int i, int h, int& x, int& y)
{
	if (i > 0)
	{
		i--;
		hilbert(d, r, u, t, i, h, x, y);
		move(r, h, x, y);
		hilbert(r, d, t, u, i, h, x, y);
		move(d, h, x, y);
		hilbert(r, d, t, u, i, h, x, y);
		move(t, h, x, y);
		hilbert(u, t, d, r, i, h, x, y);
	}
}

void main()
{
	std::ofstream Cfile;
	Cfile.open("COOR.txt", std::ios::app); //app is append which means it will put the text at the end

	for (long int test = 0; test < 1000; test++) { // Initiate the first 1000 places of the arrays. 
		xcoor[test] = 0;
		ycoor[test] = 0;
	}

	int n, xl, yl;
	int xO = 0, yO = 0, x, y, h = 2, r = 2, d = 3, t = 4, u = 1;  // X and Y Starting; H is how far it moves; r = rotation?; d, t, u Dosent matter;
	//int driver = DETECT, mode = 0; // Essential Varibales; All of this is from the Graphics.h Im not going to claim I know greatly how to use it as I dont own it xD;
	char LOOP = ' '; // Essential Varibales;

	//initwindow(1000, 1000);

	//initgraph(&driver, &mode, &LOOP); // Initiate the graph we will be using;

	std::cout << "Give the value of n:"; // What iteration we are going to use;

	std::cin >> n; // Read the user input;

	std::cout << "Do you want it written to a text file? y/n \n";

	std::cin >> f;

	x = xO; y = yO; // Yes!

	//moveto(x, y); // Move to the starting X & Y;

	hilbert(r, d, t, u, n, h, x, y); // Start the Recursive alg;

	if (f == 'y') {

		Cfile << '\n' << " ~ Iteration number:" << n << " ~ Moving @" << h << " per" << '\n' << "{"; // Beginning of the Coord File

		/***********************************************
		Print the x coordinates
		below it assigns the digits until the given matrix is
		back to 0, 0 for each of them
		***********************************************/

		for (long int lol = 0; lol < 1000; lol++) { // SIT 1; x = 5, y = 10; SIT 2; x = 10, y = 5; SIT 3; x = 100, y = 5

			int xy = xcoor[lol];
			int yx = ycoor[lol];


			yCheck = int(log10(yx) + 1);
			xCheck = int(log10(xy) + 1);

			if (ycoor[lol] == 0 || yCheck < 0) yCheck = 1;
			if (xcoor[lol] == 0 || xCheck < 0) xCheck = 1;

			if (yCheck > xCheck) SPACE = yCheck - xCheck;
			else if (xCheck > yCheck) SPACE = 99;
			else if (xCheck == yCheck) SPACE = 99;
			else SPACE = 3;

			std::cout << "X = " << (log10(xcoor[lol]) + 1) << " Coord " << xcoor[lol] << " Y = " << (log10(ycoor[lol]) + 1) << " Coord " << ycoor[lol] << " SPACE = " << SPACE << '\n';

			if (SPACE == 99) Cfile << xcoor[lol] << ", ";
			else if (SPACE == 1) Cfile << " " << xcoor[lol] << ", ";
			else if (SPACE == 2) Cfile << "  " << xcoor[lol] << ", ";
			else if (SPACE == 3) Cfile << "   " << xcoor[lol] << ", ";

			if (lol > 20 && xcoor[lol] == 0 && ycoor[lol] == 0) break;

			yCheck, xCheck = 0;
		}

		Cfile << "}" << "// XCOOR" << '\n' << '{'; // End the x array and begin the y array


		/****************************************
		Print the y coordinates, above it begins the array bracket
		below it assigns the digits until the given matrix is
		back to 0, 0 for each of them
		****************************************/


		for (long int lol = 0; lol < 1000; lol++) {

			int xy = xcoor[lol];
			int yx = ycoor[lol];

			yCheck = int(log10(yx) + 1);
			xCheck = int(log10(xy) + 1);

			if (ycoor[lol] == 0 || yCheck < 0) yCheck = 1;
			if (xcoor[lol] == 0 || xCheck < 0) xCheck = 1;

			if (xCheck > yCheck) SPACE = xCheck - yCheck;
			else if (yCheck > xCheck) SPACE = 99;
			else if (xCheck == yCheck) SPACE = 99;
			else SPACE = 99;

			std::cout << "X = " << int(log10(xcoor[lol]) + 1) << " Coord " << xcoor[lol] << " Y = " << int(log10(ycoor[lol]) + 1) << " Coord " << ycoor[lol] << " SPACE = " << SPACE << '\n';

			if (SPACE == 99) Cfile << ycoor[lol] << ", ";
			else if (SPACE == 1) Cfile << " " << ycoor[lol] << ", ";
			else if (SPACE == 2) Cfile << "  " << ycoor[lol] << ", ";
			else if (SPACE == 3) Cfile << "   " << xcoor[lol] << ", ";

			if (lol > 20 && xcoor[lol] == 0 && ycoor[lol] == 0) break;
			yCheck, xCheck = 0;
		}

		Cfile << "}" << "// YCOOR" << '\n';// End array and make a new line;
	
		Cfile.close(); // Close the file;

	}

	//getch(); // ESSENTIAL GRAHIPCS.H LINE;

	//restorecrtmode; // No idea to be honest;
}






