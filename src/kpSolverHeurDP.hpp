//********* kpSolverHeurDP.hpp *********

#ifndef KPSOLVERHEURDP_HPP
#define KPSOLVERHEURDP_HPP

#include "kpSolverGreedy.hpp"

class  KpSolverHeurDP : public KpSolverGreedy {

protected:
	int nbSelectedReopt;
	int nbUnselectedReopt;

	int lastIndex;
	int fixedCost;

public:

    void solveUpperBound();
    void solve();

    void setNeighborhood(int nbSelectedOpt, int nbUnselectedOpt);

};


#endif
