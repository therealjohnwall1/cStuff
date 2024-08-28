#include <string>

class freqNode {
public:
  int frequency;
  char symbol;
  std::string code;
  freqNode *left;
  freqNode *right;

  freqNode();
  freqNode(char sym);
  freqNode(int freq, char sym);
  //~freqNode()
};

class compareNode {
public:
  bool operator()(const freqNode &n1, const freqNode &n2);
};
