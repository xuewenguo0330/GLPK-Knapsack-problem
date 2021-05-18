//********* kpSolver.hpp *********

#ifndef KPSOLVER_HPP
#define KPSOLVER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

class KpSolver {

private:
	void sortKnapsack();


protected:

	// Items and knapsack properties.
	int nbItems; // Number of items.
	vector<int> weights; //weights of items
	vector<int> values; //values of items
	int knapsackBound;     // Knapsack bound (capacity)

	// Solution (items in the knapsack).
	vector<bool> solution;
	long costSolution;
	double upperBoundOPT;




public:


	// Reads instance data.
	void importInstance(const string& fileName);
	void printKnapsackInstance();
	void printKnapsackSolution(bool printSol);

	int getUpperBound(){return upperBoundOPT;};
	int getSolutionCost(){return costSolution;};
	int getKpBound(){return knapsackBound;}
	double getgap(){return (floor(upperBoundOPT)- (double)costSolution) /( (double)costSolution) * 0.001;};
	bool isSelected(int item){return solution[item];};

	void extractSubInstance(int idMin, int idMax);

	void clearInstance();

	int getNbItems() const {return nbItems;	};

	 //pour l'exo 7 and 11
	//KpSolverHeurDP n'est pas de type KpSolver??
	void getExtractedSubInstance(int nb, vector<int>weight,vector<int> prix, int bound);
	vector<bool> getSolution(){return solution;}


};

#endif
