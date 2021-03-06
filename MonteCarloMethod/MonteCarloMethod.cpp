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

	Particle() {
		x = 0;
		y = 0;
		z = 0;
		E = 0;
	}
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

// Headers
double function(Particle* a, Particle* b);

// Calculate the value of our given function using input of two W/Z bosons
double function(Particle* a, Particle* b) {
	// k_0^2 - (k_x^2 + k_y^2 + k_z^2) - .25
	double aL = pow(a->E, 2) - (pow(a->x, 2) + pow(a->y, 2) + pow(a->z, 2)) - .25;
	double bL = pow(b->E, 2) - (pow(b->x, 2) + pow(b->y, 2) + pow(b->z, 2)) - .25;

	double eq = (1 / (pow(aL, 2) + .01)) + (1 / (pow(bL, 2) + .01));
	return eq;
}

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

	// Create random number generator to generate doubles between -1 and 1
	double lowerBound = -1, upperBound = 1;
	uniform_real_distribution<double> unif(lowerBound, upperBound);
	default_random_engine RNG;
	
	// Seed the random number generator with the time in seconds since the Unix Epoch
	RNG.seed(time(0));

	//create output file
	ofstream fileOut;
	fileOut.open("momentums.txt");

	//loop until 10000 points meeting the criteria are generated
	int numPoints = 0;
	double p[4][4]; // p[0,1,2,3][] are the 4 momentum for each outgoing fermion 
	while (numPoints < 100000) {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				p[i][j] = unif(RNG); // Loop over first 3 fermions and their x,y,z momentum and assign random values on [-1,1]
		for (int i = 0; i < 3; i++)
			p[3][i] = -1 * (p[0][i] + p[1][i] + p[2][i]); // Calculate 4th fermion momentum based on conservation laws
		if (p[3][0] < 1 && p[3][0] > -1 && p[3][1] < 1 && p[3][1] > -1 && p[3][2] < 1 && p[3][2] > -1) { // Check if momentum falls within acceptable bounds
			numPoints++;
			for (int i = 0; i < 4; i++) {
				p[i][3] = sqrt((p[i][0] * p[i][0]) + (p[i][1] * p[i][1]) + (p[i][2] * p[i][2]));		
			}
			double p0 = p[0][3] + p[1][3] + p[2][3] + p[3][3];
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					p[i][j] = p[i][j] / (p0); // Scale for enregy
					fileOut << p[i][j] << ' ';
				}
				fileOut << '\n';
			}
			
			//toStr(p); // Test print statement
			
		}
	}
	fileOut.close();
	return 0;
}

// Calculates integral of function f using Monte Carlo integration
double monteCarlo() {
	ifstream fileIn;
	fileIn.open("momentums.txt");
	
	double I = 0;
	Particle* kA = new Particle();
	Particle* kB = new Particle();
	double a, b, c, d, e, f, g, h;
	while (!fileIn.eof()) {
		fileIn >> a;
		fileIn >> b;
		fileIn >> c;
		fileIn >> d;
		fileIn >> e;
		fileIn >> f;
		fileIn >> g;
		fileIn >> h;
		kA->setX(a + e);
		kA->setY(b + f);
		kA->setZ(c + g);
		kA->setE(d + h);
		fileIn >> a;
		fileIn >> b;
		fileIn >> c;
		fileIn >> d;
		fileIn >> e;
		fileIn >> f;
		fileIn >> g;
		fileIn >> h;
		kB->setX(a + e);
		kB->setY(b + f);
		kB->setZ(c + g);
		kB->setE(d + h);
		I += function(kA, kB);
	}
	I /= 100000;
	cout << "Integral Result: " << I << endl;
	
	fileIn.close();
	return I;
}

// Main method
int main()
{
	// Take user input on how many times to run the simultion
	double avg = 0;
	int lcv;
	cout << "How many simulations?" << endl;
	cin >> lcv;
	for (int i = 0; i < lcv; i++) {
		generatePoints();
		avg += monteCarlo();
	}
	avg /= (double)lcv;
	cout << "Average Result: " << avg << endl;
}