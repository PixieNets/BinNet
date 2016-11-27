//
// Created by Zal on 11/21/16.
//

#include "XnorNetwork.h"

XnorNetwork::XnorNetwork() {

}

XnorNetwork::~XnorNetwork() {

}

/*
 * This is for prototype testis purposes and needs to be changed
 * to Objective-C for loading in the iPhone
 */
void XnorNetwork::loadLabelsFromFile(std::string path) {
    std::ifstream labelsFile(path);

    if(!labelsFile.is_open()) {
        std::cout << "Could not open file " << path << std::endl;
        return;
    }

    std::string tmpLabel;
    for(int i=0; !labelsFile.eof(); ++i) {
        labelsFile >> tmpLabel;
        this->XN_labels.push_back(tmpLabel);
    }
    this->XN_totalLabels = this->XN_labels.size();
    std::cout << "Loaded " << this->XN_totalLabels << "labels" << std::endl;
}

VecStrDblPair XnorNetwork::getTopNLabels(int N, arma::vec outputVec) {
    VecStrDblPair rankedVec;

    return rankedVec;
}