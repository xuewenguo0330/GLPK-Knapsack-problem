//********* knapsackGreedy.cpp *********

#include "kpSolverGreedy.hpp"


void KpSolverGreedy::solveUpperBound() {
//Facon continue, on suppose les objets ont été triés
//suivant l’ordre ci/mi d´ecroissant.
  upperBoundOPT=0;//la value en opti
  int bound=knapsackBound;
  for (int i=0;i<nbItems;i++){
    if(bound>0){
      if(bound<weights[i]){
        upperBoundOPT+=values[i]*((double)bound)/((double)weights[i]);
        bound=0;
      }else{
        upperBoundOPT+=values[i];
        bound-=weights[i];
      }
    }
  }
 }


void KpSolverGreedy::solveLowerBound() {
  //les objets sont triee (ci/mi decroissant)
  //fonction entier
	//TODO
	solution.resize(nbItems);
	costSolution = 0.;
	int bound = knapsackBound;

	for(int i = 0; i < nbItems; i++){
	    if(weights[i] <= bound){
	       solution[i] = true;
	       costSolution += values[i];
	       bound -= weights[i];
	    }else{
        solution[i] = false;
	    }

	}

 }
void KpSolverGreedy::solve() {
	solveUpperBound();
	solveLowerBound();
}
