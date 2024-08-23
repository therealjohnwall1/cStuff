#include <iostream>
#include <cstddef>

class freqNode {
	public:
		int frequency;
		char symbol;		
        //std::byte huffCode; // change later, usually store bits not int (8bit not good);
        // children
        freqNode* left;
        freqNode* right;

        freqNode(int freq, char sym) {
           frequency = freq;
           symbol = sym; 
        }

        //~freqNode() {
            // delete tree from root node should only be called once
            //std::cout << "starting destructor \n";
            // do later
        //}

};

class compareNode {
    public: 
        bool operator()(const freqNode &n1, const freqNode &n2) {
            if (n1.frequency == n2.frequency) {
                return true;
            }

            // will make the queue in increasing order
            return n1.frequency > n2.frequency;
        }
};



