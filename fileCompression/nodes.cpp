#include <iostream>
#include <cstddef>
#include "nodes.h"

freqNode::freqNode(int freq, char sym) {
   frequency = freq;
   symbol = sym; 
}
freqNode::freqNode(char sym) {
	symbol = sym;
}

//~freqNode() {
    // delete tree from root node should only be called once
    //std::cout << "starting destructor \n";
    // do later
//}


bool compareNode::operator()(const freqNode &n1, const freqNode &n2) {
    if (n1.frequency == n2.frequency) {
        return true;
    }

    // will make the queue in increasing order
    return n1.frequency > n2.frequency;
}



