// MonteCarloMethod.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <random>
#include <string>

using namespace std;

int toStr(double in[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << in[i][j] << ' ';
		}
		cout << '\n';
	}
	return 0;
}

int generatePoints() {
	//create random number generator
	double lowerBound = -1, upperBound = 1;
	uniform_real_distribution<double> unif(lowerBound, upperBound);
	default_random_engine RNG; //unif(RNG)

	//create output file
	ofstream fileOut;
	fileOut.open("momentums.dat");

	//loop until 10000 points meeting the criteria are generated
	int numPoints = 0;
	while (numPoints < 10) {
		double p[4][4]; //p[0,1,2,3][] are the 4 momentum for each outgoing fermion 
						//with p[][0,1,2] being the x, y, and z components and p[][3] being the energy component
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				p[i][j] = unif(RNG); //loop over first 3 fermions and their x,y,z momentum and assign random values on [-1,1]
			}
		}
		for (int i = 0; i < 3; i++) {
			p[3][i] = -1 * (p[0][i] + p[1][i] + p[2][i]); //calculate 4th fermion momentum based on conservation laws
		}
		if (p[3][0] < 1 && p[3][0] > -1 && p[3][1] < 1 && p[3][1] > -1 && p[3][2] < 1 && p[3][2] > -1) { //check if momentum falls within acceptable bounds
			numPoints++;
			for (int i = 0; i < 4; i++) {
				p[i][3] = sqrt((p[i][0] * p[i][0]) + (p[i][1] * p[i][1]) + (p[i][2] * p[i][2]));
				for (int j = 0; j < 4; j++) {
					p[i][j] = p[i][j] / p[i][3]; //scale for enregy
					fileOut << p[i][j] << '	';
				}
			}
			fileOut << '\n';
		}

	}
	return 0;
}

int main()
{
	generatePoints();
}