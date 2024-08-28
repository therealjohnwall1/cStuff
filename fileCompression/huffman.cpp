#include <bit>
#include <bitset>
#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

// #include "nodes.h"
#include "huffman.h"
#include "utils.h"

using std::cout;
using std::fstream;
using std::priority_queue;
using std::string;
using std::unordered_map;
using std::vector;

typedef unsigned int uint;

priority_queue<freqNode, vector<freqNode>, compareNode> *
countFrequencies(string filePath) {
  fstream file(filePath, std::ios::in);
  unordered_map<char, int> freqMap;

  string line;
  if (file.is_open()) {
    while (getline(file, line)) {
      // cout << line << "\n"; // Print the current line
      for (int i = 0; i < (int)line.size(); i++) {
        // not contained in dict
        if (freqMap.find(line[i]) == freqMap.end()) {
          freqMap.insert({line[i], 1});
        }

        else {
          // freqMap[line[i]] = freqMap[line[i]] + 1;
          freqMap[line[i]]++;
        }
      }
    }
  }

  else {
    printf("failed to open file\n");
  }

  // for (const auto& pair : freqMap) {
  // cout << "Key: " << pair.first << ", Value: " << pair.second << "\n";
  //}

  // create frequency table(prior queue)
  // priority_queue<freqNode,vector<freqNode>,compareNode> freqQueue;
  priority_queue<freqNode, vector<freqNode>, compareNode> *freqQueue =
      new priority_queue<freqNode, vector<freqNode>, compareNode>;

  for (auto i : freqMap) {
    // char, freq
    // constructor takes frequency first
    freqNode toIns(i.second, i.first);
    freqQueue->push(toIns);
  }
  // need to delete after
  return freqQueue;
}

freqNode *
buildTree(priority_queue<freqNode, vector<freqNode>, compareNode> *queue) {
  // while queue length is geq 2
  // freqNode *root = new freqNode();
  // freqNode *root = (freqNode*)malloc(sizeof(freqNode));
  freqNode *root = new freqNode();
  while (queue->size() >= 2) {
    freqNode *first = new freqNode(queue->top());
    queue->pop();
    freqNode *second = new freqNode(queue->top());
    queue->pop();

    // merge both of them into a new node
    // counting node no char should represent only frequency of kids
    freqNode *toAdd = new freqNode(first->frequency + second->frequency, NULL);
    toAdd->left = first;
    toAdd->right = second;
    queue->push(*toAdd);

    // if (queue->size() == 2) {
    //*root = queue->top();
    //}
    if (queue->size() == 1) {
      root = new freqNode(queue->top());
    }
  }
  return root;
}

void generateCodes(freqNode *curr, string str,
                   unordered_map<char, std::string> &huffmanCode) {
  if (!curr) {
    return;
  }

  if (!curr->right && !curr->left) {
    // huffmanCode->insert({curr->symbol, huffmanCode});
    huffmanCode[curr->symbol] = str;
    curr->code = str;
  }

  generateCodes(curr->left, str + "1", huffmanCode);
  generateCodes(curr->right, str + "0", huffmanCode);
}

// turn to macro
uint calcByteSize(uint bitSize) { return 1 + ((bitSize - 1) / 8); }

void writeString(string encodedString, std::ostream &ofs) {
  unsigned char currByte = 0;
  uint bitCt = 0;
  for (char bit : encodedString) {
    currByte <<= 1;

    if (bit == '1') {
      currByte |= 1;
    }

    bitCt += 1;

    if (bitCt == 8) {
      ofs.put(currByte);
      bitCt = 0;
      currByte = 0;
    }
  }

  if (bitCt > 0) {
    currByte <<= (8 - bitCt);
    ofs.put(currByte);
  }
}

void serializeTree(unordered_map<char, string> freqMap, std::ostream &ofs) {
  // will use cannocial way of serializing it -> store the "frequency bit"
  // rather then entire tree
  std::map<char, int> sortedMap;
  for (auto i : freqMap) {
    sortedMap[i.first] = (int)i.second.size();
  }

  std::vector<std::pair<char, int>> sortVec = sorting(sortedMap);

  // also use cannocial codes instead of original ones
  for (auto i : sortVec) {
    freqMap[i.first] = i.second;
  }

  string bitSequence = "";

  for (auto i : sortVec) {
    // cout << i.first << ":" << i.second << " " << freqMap[i.first] << "\n";
    bitSequence.append(freqMap[i.first]);
  }

  // convert to bytes i think might be wrong ngl
  // freqLength = calcByteSize(freqLength);
  uint freqLength = freqMap.size();
  // freqLength = freqMap.size(); // not in bytes,just amt of entries(5 bytes
  // per)
  uint sequenceLen = calcByteSize(bitSequence.size());

  cout << "encoding " << freqLength << "," << sequenceLen << "\n";

  ofs.write(reinterpret_cast<const char *>(&freqLength), sizeof(uint));
  ofs.write(reinterpret_cast<const char *>(&sequenceLen), sizeof(uint));

  for (auto i : sortVec) {
    // cout << "symbol:" << i.first << " frequency: " << i.second << "\n";
    ofs.write(&i.first, sizeof(char));
    // to lazy to int->byte
    string toWrite = std::to_string(i.second);
    // writeString(toWrite, ofs);
    ofs.write(reinterpret_cast<const char *>(&i.second), sizeof(int));
  }

  // don't need to store the actual codes, can rebuild given order + len
  // writeString(bitSequence, ofs);
}

void compressFile(string path, freqNode *root) {
  std::ofstream ofs{"huffmanZip.dat", std::ios::binary};
  if (!ofs.good()) {
    cout << " ofs stream is bad will not work\n";
  }
  unordered_map<char, string> huffCodes;
  generateCodes(root, "", huffCodes);
  serializeTree(huffCodes, ofs);

  // write to string first
  string encodedString = "";
  fstream file(path, std::ios::in);
  string line;
  if (file.is_open()) {
    while (getline(file, line)) {
      // cout << line << "\n"; // Print the current line
      for (int i = 0; i < (int)line.size(); i++) {
        encodedString += huffCodes[line[i]];
      }
    }
  }
  file.close();
  writeString(encodedString, ofs);
  ofs.close();
}

// left(1), right(0)
void insertNode(freqNode *curr, string code, int itr) {
  if (itr == code.size()) {
    curr->code = code;
    return;
  }

  if (!curr) {
    curr = new freqNode();
  }

  char currChar = code.at(itr);
  cout << "char: " << currChar << "\n";

  if (currChar == '1') {
    insertNode(curr->left, code, itr + 1);
  }

  else {
    insertNode(curr->right, code, itr + 1);
  }
}

freqNode *rebuildTree(std::map<char, string> huffCodes) {
  freqNode *root = new freqNode();
  // root->code = 0;
  for (auto i : huffCodes) {
    cout << "hit" << i.first << " " << i.second << " \n";
    insertNode(root, i.second, 0);
  }

  return root;
}

void decompressFile(string path) {
  cout << path << "\n";

  std::ifstream ifs{path, std::ios::binary};
  if (!ifs) {
    cout << "invalid file \n";
    return;
  }

  // not in bytes, just entries(each is 5)
  uint freqLength;
  ifs.read(reinterpret_cast<char *>(&freqLength), sizeof(freqLength));
  cout << "freq length:" << freqLength << "\n";

  // size of cannoical codes
  uint sequenceLen;
  ifs.read(reinterpret_cast<char *>(&sequenceLen), sizeof(sequenceLen));
  cout << "sequence length:" << sequenceLen << "\n";

  // char + frequency, will change to char + actual codes
  std::map<char, int> freqMap;

  for (int i = 0; i < (int)freqLength; i++) {
    char sym;
    ifs.read(&sym, sizeof(sym));
    int frq;
    ifs.read(reinterpret_cast<char *>(&frq), sizeof(frq));
    freqMap[sym] = frq;
  }

  std::vector<std::pair<char, int>> sortVec = sorting(freqMap);

  // generate cannocial codes for each
  std::map<char, std::string> huffmanCodes;
  int currentCode = 0;
  int currentLength = sortVec[0].second;

  for (auto i : sortVec) {
    char character = i.first;
    int codeLength = i.second;

    if (codeLength > currentLength) {
      currentCode <<= (codeLength - currentLength);
      currentLength = codeLength;
    }

    huffmanCodes[character] =
        std::bitset<32>(currentCode).to_string().substr(32 - codeLength);
    // cout << character << " " << huffmanCodes[character] << "\n";
    currentCode++;
  }

  // rebuild tree
  freqNode *root = rebuildTree(huffmanCodes);
}

int main() {
  // example prog
  string path = "huffman.cpp";
  priority_queue<freqNode, vector<freqNode>, compareNode> *test =
      countFrequencies(path);

  freqNode *root;
  root = buildTree(test);
  compressFile(path, root);
  decompressFile("huffmanZip.dat");
}
