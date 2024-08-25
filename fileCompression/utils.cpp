#include "utils.h"

bool compare(std::pair <char, int> &a, std::pair <char, int> &b) {
   if (a.second == b.second) {
       return a.first < b.first;
   }

   return a.second < b.second;
}

std::map <char, int> sorting( std::map <char, int> inputMap ){
   std::vector<std::pair <char, int> > pairVec;
   std::map<char, int> sortedMap;
   
   for ( auto& it : inputMap ) {
      pairVec.push_back( it );
   }
   
   sort( pairVec.begin(), pairVec.end(), compare);
   
   return sortedMap;
}
