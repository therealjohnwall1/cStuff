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

priority_queue<freqNode,vector<freqNode>,compareNode>* countFrequencies(string filePath) {
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
                    freqMap[line[i]]++;

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
     //priority_queue<freqNode,vector<freqNode>,compareNode> freqQueue;
     priority_queue<freqNode,vector<freqNode>,compareNode> *freqQueue = new priority_queue<freqNode,vector<freqNode>,compareNode>;
        
     for(auto i: freqMap) {
         // char, freq
         // constructor takes frequency first
        freqNode toIns(i.second, i.first);
        freqQueue->push(toIns);
     }
     // need to delete after 
     return freqQueue;
}

freqNode* buildTree(priority_queue<freqNode,vector<freqNode>,compareNode> *queue) {
    // while queue length is geq 2
   //freqNode *root = new freqNode();
   freqNode *root = (freqNode*)malloc(sizeof(freqNode*));
    while(queue->size() >=  2) {
       freqNode *first = new freqNode(queue->top());
       queue->pop();
       freqNode *second= new freqNode(queue->top());
       queue->pop();

       // merge both of them into a new node
       // counting node no char should represent only frequency of kids
       freqNode toAdd(first->frequency + second->frequency, NULL);
       toAdd.left = first;
       toAdd.right = second;
       queue->push(toAdd);
       if (queue->size() == 2) {
           *root = queue->top();
       }
    }
    return root;
}

void generateCodes(freqNode* curr, string& str,unordered_map<char, std::string>& huffmanCode) {
    // gen codes for each char, store in dict we can write this to a file to encode, save the tree to decode
    //
    
    
}


int main() {
    // example prog
    string path = "huffman.cpp";
    priority_queue<freqNode,vector<freqNode>,compareNode> *test = countFrequencies(path);
    
    // build tree
    freqNode* root;
    root = buildTree(test);

}


