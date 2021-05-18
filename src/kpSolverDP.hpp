//********* kpSolver.hpp *********

#ifndef KPSOLVERDP_HPP
#define KPSOLVERDP_HPP

#include "kpSolver.hpp"

class  KpSolverDP : public KpSolver {

private:

    int** matrixDP; //matrice de taille nbitems*(knapsackBound+1)

    bool memoizedVersion;
    bool verboseMode;


    void solveIter();
    int solveMemoized(int i , int m);

    void backtrack();

    void createMatrixDP();
    void deleteMatrixDP();
    void printMatrixDP();

    void fillFirstColumnDP();

public:



    void solve();

    void setMemoizedVersion(bool memoizedVersion);
    void setVerboseMode(bool verbosemode);
    void setKpBound (int newKpBound);
    int getKpBound(){return knapsackBound;}

};

#endif
