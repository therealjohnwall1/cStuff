#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include "nodes.cpp"

using std::string;
using std::fstream;
using std::unordered_map;
using std::cout;
using std::priority_queue;
using std::vector;

priority_queue<freqNode,vector<freqNode>,compareNode> countFrequencies(string filePath) {
    fstream file(filePath, std::ios::in);
    unordered_map<char, int> freqMap; 
    
    string line;
    if (file.is_open()) {
        while (getline(file, line)) { 
            //cout << line << "\n"; // Print the current line 
            for (int i = 0; i < (int)line.size();i++) {
                // not contained in dict
                if (freqMap.find(line[i]) == freqMap.end()) {
                    freqMap.insert({line[i], 1});
                }
                else {
                    //freqMap[line[i]] = freqMap[line[i]] + 1;
                    freqMap[line[i]]++ ;
                }
            }
        }
    }

    else {
        printf("failed to open file\n");
    }

   //for (const auto& pair : freqMap) {
        //cout << "Key: " << pair.first << ", Value: " << pair.second << "\n";
    //} 
	
	// create frequency table(prior queue)
     priority_queue<freqNode,vector<freqNode>,compareNode> freqQueue;
     return freqQueue;
}


void buildTree(priority_queue<freqNode,vector<freqNode>,compareNode> queue) {
// pass

}



int main() {
    string path = "huffman.cpp";
    countFrequencies(path);
}


