//********* knapsackheurDP.cpp *********

#include "kpSolverHeurDP.hpp"
#include "kpSolverDP.hpp"


void KpSolverHeurDP::solveUpperBound() {
        //les objets sont triee (ci/mi decroissant)
	//TODO
	upperBoundOPT = 0.;
	int bound = knapsackBound;
	for(int i=0;i<nbItems;i++){
		if(bound>0){
			if(bound<weights[i]){
				upperBoundOPT+=values[i]*((double)bound)/((double)weights[i]);
				bound=0;
			}else{
				upperBoundOPT+=values[i];
				bound-=weights[i];
			}
		}else{
			lastIndex=i;
			return;
		}
	}
}

void KpSolverHeurDP::solve() {
	 solveUpperBound();
	 int fixedCost=0;
	 int bound=knapsackBound;
	 costSolution=0.;
	 for(int i=0;i<lastIndex-nbSelectedReopt;i++){
	   costSolution+=values[i];
		 bound-=weights[i];
	 }
	 extractSubInstance(lastIndex-nbSelectedReopt,lastIndex+nbUnselectedReopt+1);

	 KpSolverDP KpSolverDP;

	 KpSolverDP.setMemoizedVersion(false);

	 KpSolverDP.getExtractedSubInstance(nbItems,weights,values,bound);
	 KpSolverDP.setVerboseMode(false);
	 KpSolverDP.solve();

	 costSolution+=KpSolverDP.getSolutionCost();
	 solution=KpSolverDP.getSolution();
	 KpSolverDP.clearInstance();

}

void KpSolverHeurDP::setNeighborhood(int nbSelectedOpt, int nbUnselectedOpt) {
	nbUnselectedReopt = nbUnselectedOpt;
	nbSelectedReopt = nbSelectedOpt;
}
