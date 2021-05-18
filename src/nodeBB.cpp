//********* nodeBB.cpp *********

#include "nodeBB.hpp"
#include <iostream>
#include <fstream>

bool NodeBB::canBeRemoved() {
	return overCapacitated;
}

void NodeBB::init(int size){
	overCapacitated= false;
	isFixed.resize(size);
	isRemoved.resize(size);
	for(int i=0; i<size;i++){
		isFixed.push_back(false);
		isRemoved.push_back(false);
	}

    criticalIndex=-1;
    fractionalVariable=0;
    localLowerBound=0;
}

//TODO
void NodeBB::primalHeuristic(int kpBound, int nbItems, vector<int> & weights,  vector<int> & values) {
//solution discrete
	//TODO
	localLowerBound=0;
	primalSolution.resize(nbItems);
	for(int i=0;i<nbItems;i++){
		if(isFixed[i]){
			kpBound-=weights[i];
			localLowerBound+=values[i];
			primalSolution[i]=true;
		}
		if(isRemoved[i]==true){
			primalSolution[i]=false;
		}
	}
	if(kpBound<0){
		std::cout<<"Pas possile,trop d'objets imposes"<<std::endl;
		overCapacitated=true;
		return;
	}
	for(int i=0;i<nbItems;i++){
		if(not isFixed[i]&&not isRemoved[i]){
			if(weights[i]>kpBound){
				primalSolution[i]=false;
			}else{
				primalSolution[i]=true;
				kpBound-=weights[i];
				localLowerBound+=values[i];
			}
		}
	}
 }

/*
//TODO:
void NodeBB::solveUpperBound(int kpBound, int nbItems, vector<int> & weights,  vector<int> & values) {
//solution continue
	// kpBound: masse maximum de sac a dos
	// w: vector de masse
	// v:vector de valeur
	localUpperBound=0.;
	for(int i=0;i<nbItems;i++){
		if(isFixed[i]){
			kpBound-=weights[i];
			localUpperBound+=values[i];
		}
	}
	if(kpBound<0){
		std::cout<<"Pas possile,trop d'objets imposes"<<std::endl;
		overCapacitated=true;
		return;
	}
	for(int i=0;i<nbItems;i++){
		if(kpBound>0){
			if(not isFixed[i]&&not isRemoved[i]){
				if(kpBound<weights[i]){
					kpBound=0;
					criticalIndex=i;
					fractionalVariable=values[i]*((double)kpBound)/((double)weights[i]);
					localUpperBound+=fractionalVariable;
				}else{
					localUpperBound+=values[i];
					kpBound-=weights[i];
				}
			}
		}
	}
}*/
void NodeBB::solveUpperBound(int kpBound, int nbItems, vector<int> & weights,  vector<int> & values) {
    double sum_value = 0;
    int sum_weight = 0;

    for (int i = 0; i < nbItems; ++i) {
        sum_weight += isFixed[i] * weights[i];
        sum_value += isFixed[i] * values[i];
    }

    if (sum_weight > kpBound) {
        overCapacitated = true;
    } else {
        for (int i = 0; i < nbItems; ++i) {
            if (!isFixed[i] && !isRemoved[i]) {
                sum_weight += weights[i];
                if (sum_weight == kpBound) {
                    localUpperBound = sum_value + values[i];
                    return;
                }
                sum_value += values[i];
            }
        }
    }
 }
