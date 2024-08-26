#include <iostream>
#include <fstream>
#include <map>

int main() {
    std::ofstream ofs{"test.dat", std::ios::binary};
    unsigned int freqLength = 5;// Number of entries (should match on both read and write)
    ofs.write(reinterpret_cast<const char*>(&freqLength), sizeof(freqLength));
    std::cout << "serializing: " << freqLength << "\n";
    std::cout << "\n";
    
    ofs.close();

    std::ifstream ifs{"test.dat", std::ios::binary};
    unsigned int inputLen;
    ifs.read(reinterpret_cast<char*>(&inputLen), sizeof(freqLength));
    std::cout << "Frequency length: " << inputLen<< "\n";
    
    ifs.close();
  

}