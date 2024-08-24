#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <bitset>
#include <bit>

#include "nodes.h"
#include "huffman.h"

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

void generateCodes(freqNode* curr, string str,unordered_map<char, std::string>& huffmanCode) {
    if (!curr) {
        return;
    }

    if (!curr->right && !curr->left) {
        //huffmanCode->insert({curr->symbol, huffmanCode});
        huffmanCode[curr->symbol] = str;
    }

    generateCodes(curr->left, str+"1", huffmanCode);
    generateCodes(curr->right, str+"0", huffmanCode);
}

void serializeTree(freqNode* curr, std::ostream &ser) {
    if(!curr) {
        // store as null
        ser << "#";
    } 
    ser << curr->symbol << " ";
    serializeTree(curr->left, ser);
    serializeTree(curr->right, ser);
}

freqNode* deserializeTree(std:: istream &ser) {
	std::string val;
    ser >> val;

    if (val == "#") {
        return nullptr;  
    }

    freqNode* node = new freqNode(val[0]);  
    node->left = deserializeTree(ser);   
    node->right = deserializeTree(ser); 
    return node;
}

void compressFile(string path, unordered_map<char, string> huffCodes) {
    // write to string first
    string encodedString = "";
    fstream file(path, std::ios::in);
    string line;
    if (file.is_open()) {
        while (getline(file, line)) { 
            //cout << line << "\n"; // Print the current line 
            for (int i = 0; i < (int)line.size();i++) {
                encodedString += huffCodes[line[i]];
            }
        }
    }
    std::ofstream ofs{path+"_zipped.bin", std::ios::binary};
    
    unsigned char currByte = 0;
    int bitCt = 0;
    for (char bit: encodedString) {
        currByte <<= 1;

        if (bit == '1') {
            currByte |= 1;
        }

        bitCt += 1;

        if(bitCt == 8) {
            ofs.put(currByte);
            bitCt = 0;
            currByte = 0;
        }
    }
    if (bitCt > 0) {
        currByte <<=(8-bitCt);
        ofs.put(currByte);
    }

    ofs.close();
}


int main() {
    // example prog
    string path = "huffman.cpp";
    priority_queue<freqNode,vector<freqNode>,compareNode> *test = countFrequencies(path);
    
    freqNode* root;
    root = buildTree(test);

    unordered_map<char, std::string> huffCodes;
    generateCodes(root, "" ,huffCodes);
    compressFile(path, huffCodes);
    

    //for(const auto& code: huffCodes) {
        //cout << "char: " << code.first << " encoding: " << code.second << "\n";
    //}
}

