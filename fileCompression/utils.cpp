#include "utils.h"
struct freqSorted{
    bool operator()(const std::pair <char, int> &a, const std::pair <char, int> &b) {
       if (a.second == b.second) {
           return a.first < b.first;
       }
       return a.second < b.second;
    }
};

 std::vector<std::pair<char, int>> sorting(std::map<char,int> sortedMap) {
     std::vector<std::pair<char, int>> mapVector(sortedMap.begin(), sortedMap.end());

     std::sort(mapVector.begin(), mapVector.end(), freqSorted());
     //for (const auto& pair : mapVector) {
         //std::cout << (char)pair.first << ": " << pair.second << std::endl;
      //}
     return mapVector;
}
