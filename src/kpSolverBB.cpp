//********* kpSolverBB.cpp *********

#include "kpSolverBB.hpp"
#include "kpSolverDP.hpp"
#include "kpSolverHeurDP.hpp"
#include <math.h>
#include <stdlib.h>
#include <time.h>


double KpSolverBB::getUpperBound() {
	upperBoundOPT=costSolution;
	for (std::deque<NodeBB*>::iterator it = nodes.begin() ; it != nodes.end(); ++it)
		upperBoundOPT=max(upperBoundOPT,(*it)->getNodeUpperBound());
	return upperBoundOPT;
}


void KpSolverBB::printStatus() {
	getUpperBound();
	cout  << "nbNodes: " << nbNodes;
	cout  << " remaining Nodes: " << nodes.size();
	cout  << " LB: " << costSolution;
	cout  << " UB: " << upperBoundOPT;
	cout << " gap : " << (floor(upperBoundOPT)- (double)costSolution) /( (double)costSolution) * 100 << "%" << endl;
/*
	cout  << "nodes UB: ";
	for (std::deque<NodeBB*>::iterator it = nodes.begin() ; it != nodes.end(); ++it)
		cout  << (*it)->getNodeUpperBound() << " ";
	cout  << endl;
*/
}

//TODO: rajouter heuristique de programmation dynamique
void KpSolverBB::init() {
    nbNodes= 0;
    nodes.clear();
    NodeBB* node0 = new NodeBB();
    node0->init(nbItems);
    node0->solveUpperBound(knapsackBound, nbItems, weights, values);
    if (withPrimalHeuristics) {
    	node0->primalHeuristic(knapsackBound, nbItems, weights, values);
    	costSolution=node0->getNodePrimalBound();
    	node0->copyPrimalSolution(&solution);
    }
    else {
    	costSolution=0;
    	solution.resize(nbItems);
    	for (int i = 0; i < nbItems; i++) solution[i]=false;
    }

    nodes.push_back(node0);

		if (withDPinitPrimalHeuristic) {
        KpSolverHeurDP SolverHeurDp;
        SolverHeurDp.setNeighborhood(sizeDPheur, sizeDPheur);
        SolverHeurDp.solve();
        for (int i = 0; i < nbItems; ++i) {
            solution[i] = SolverHeurDp.isSelected(i);
            costSolution = solution[i] * values[i];
        }
        SolverHeurDp.clearInstance();
    }

    //TODO: rajouter heuristique de programmation dynamique


}

NodeBB* KpSolverBB::selectNodeRandom() {

	  srand (time(NULL));

	  int n = nodes.size() ;
	  int id= rand() % n ;

	  swap(nodes[0],nodes[id]);//On faire une echange entre la premnier node et la id-eme node

	NodeBB* node = nodes.front();//la node est sélectionner aléatoirement
	nodes.pop_front();//retirer cette node dans la deque

	return node;

}

NodeBB* KpSolverBB::selectNode() {

	if(branchingStrategy == Random) return selectNodeRandom();//Utiliser la fonction precedent pour avoir une node aléatoire
	if(branchingStrategy == BestBound){
	std::sort(nodes.begin(), nodes.end(),
			[](NodeBB* i, NodeBB* j) {return i->getNodeUpperBound() < j->getNodeUpperBound();}
	);
	}

	if(branchingStrategy == BFS){//par largeur car il prend la premiere node
		NodeBB* node = nodes.front();//prendre la premiere node
		nodes.pop_front();
		return node;
	}

	NodeBB* nod = nodes.back();//prendre la derniere node
	nodes.pop_back();
	return nod;
}

void KpSolverBB::insertNode(NodeBB *nod) {
	// la solution courant est supérieur que la maximum local ou  il n'y pas d'objet pour prendre dans la node


	if ((nod->canBeRemoved()) || nod->getNodeUpperBound()<costSolution + 1) {
		delete nod;
	}
	else nodes.push_back(nod);//ajoute cette node
}

void KpSolverBB::insertNodes(NodeBB *nod1, NodeBB *nod2) {

	if(branchingStrategy == DFS01) {
		insertNode(nod1);
		insertNode(nod2);
	}
	else {
		insertNode(nod2);
		insertNode(nod1);
	}
}



//TODO
void KpSolverBB::solve() {
	init();
	//TODO
	int nb=0;

	while(!nodes.empty()&& nbNodes<nbMaxNodeBB){
	int entier=floor(getUpperBound());
		NodeBB *node=selectNode();
		node -> solveUpperBound(knapsackBound,nbItems,weights,values);
		if(withPrimalHeuristics||node->getCriticalIndex()==-1){
			node->primalHeuristic(knapsackBound,nbItems,weights,values);
			if(costSolution<node->getNodePrimalBound()){
				costSolution=node->getNodePrimalBound();
				node->copyPrimalSolution(&solution);
			}
			if(node->getCriticalIndex()==-1)continue;
		}
		if(costSolution==entier) break;
		NodeBB *nod1=new NodeBB(*node);
		NodeBB *nod2=new NodeBB(*node);
		nod1->fixVariable(node->getCriticalIndex(),false);
		nod1->solveUpperBound(knapsackBound,nbItems,weights,values);
		nod2->fixVariable(node->getCriticalIndex(),true);
		nod2->solveUpperBound(knapsackBound,nbItems,weights,values);
		insertNodes(nod1,nod2);

		if(verboseMode) printStatus();
	}
	upperBoundOPT=getUpperBound();
}
