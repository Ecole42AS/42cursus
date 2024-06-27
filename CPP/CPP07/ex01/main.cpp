#include "iter.hpp"

int main() {
    int intArray[] = {1, 2, 3, 4, 5};
    size_t intArraySize = sizeof(intArray) / sizeof(intArray[0]);

    std::string strArray[] = {"one", "two", "three", "four"};
    size_t strArraySize = sizeof(strArray) / sizeof(strArray[0]);

    // Test with printElement
    std::cout << "Printing intArray:" << std::endl;
    iter(intArray, intArraySize, print<int>);
    
    std::cout << "Printing strArray:" << std::endl;
    iter(strArray, strArraySize, print<std::string>);

    // Test with increment
    std::cout << "Incrementing intArray:" << std::endl;
    iter(intArray, intArraySize, increment<int>);
    iter(intArray, intArraySize, print<int>);

    return 0;
}