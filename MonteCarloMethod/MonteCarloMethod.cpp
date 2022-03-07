// MonteCarloMethod.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <random>
#include <cmath>

using namespace std;

// Particle class for storing particle momentum and energy compactly
class Particle {
public:
	double x, y, z, E;

	Particle(double p0, double p1, double p2, double p3) {
		x = p0;
		y = p1;
		z = p2;
		E = p3;
	}

	void setX(double parameter) {
		x = parameter;
	}
	void setY(double parameter) {
		y = parameter;
	}
	void setZ(double parameter) {
		z = parameter;
	}
	void setE(double parameter) {
		E = parameter;
	}
	double getX() {
		return x;
	}
	double getY() {
		return y;
	}
	double getZ() {
		return z;
	}
	double getE() {
		return E;
	}
	void testPrint() {
		cout << "x: " << x << "\n";
		cout << "y: " << y << "\n";
		cout << "z: " << z << "\n";
		cout << "E: " << E << "\n";
	}
};

// Test print function for printing sets of 4 particles
int toStr(double in[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << in[i][j] << ' ';
		}
		cout << '\n';
	}
	return 0;
}

// Generates acceptable points and writes them to a file
int generatePoints() {
	//create random number generator
	double lowerBound = -1, upperBound = 1;
	uniform_real_distribution<double> unif(lowerBound, upperBound);
	default_random_engine RNG; //unif(RNG)

	//create output file
	ofstream fileOut;
	fileOut.open("momentums.txt");

	//loop until 10000 points meeting the criteria are generated
	int numPoints = 0;
	double p[4][4]; //p[0,1,2,3][] are the 4 momentum for each outgoing fermion 
	while (numPoints < 10000) {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				p[i][j] = unif(RNG); //loop over first 3 fermions and their x,y,z momentum and assign random values on [-1,1]
		for (int i = 0; i < 3; i++)
			p[3][i] = -1 * (p[0][i] + p[1][i] + p[2][i]); //calculate 4th fermion momentum based on conservation laws
		if (p[3][0] < 1 && p[3][0] > -1 && p[3][1] < 1 && p[3][1] > -1 && p[3][2] < 1 && p[3][2] > -1) { //check if momentum falls within acceptable bounds
			numPoints++;
			for (int i = 0; i < 4; i++) {
				p[i][3] = sqrt((p[i][0] * p[i][0]) + (p[i][1] * p[i][1]) + (p[i][2] * p[i][2]));
				for (int j = 0; j < 4; j++) {
					p[i][j] = p[i][j] / p[i][3]; //scale for enregy
					fileOut << p[i][j] << ' ';
				}
			}
			//toStr(p); //Test print statement
			fileOut << '\n';
		}
	}
	return 0;
}

// Calculates integral of function f using Monte Carlo integration
double monteCarlo() {
	ifstream fileIn;
	fileIn.open("momentums.txt");

	long double I;

	while (!fileIn.eof()) {

	}

	return 0;
}
double f(Particle a, Particle b) {
	// k_0^2 - (k_x^2 + k_y^2 + k_z^2) - .25
	double aL = pow(a.E, 2) - (pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2)) - .25;
	double bL = pow(b.E, 2) - (pow(b.x, 2) + pow(b.y, 2) + pow(b.z, 2)) - .25;

	double function = (1 / (pow(aL, 2) + .01)) + (1 / (pow(bL, 2) + .01));
	return function;
}

int main()
{
	generatePoints();
	
}