#include <iostream>
#include <string>

unsigned int customHash(const std::string& input) {
    unsigned int hash = 5381;

    for (char c : input) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

int main() {
    std::string input; 
    std::cin >> input; 
    unsigned int hashedValue = customHash(input);
    std::cout << "Hashed value of \"" << input << "\" is: " << hashedValue << std::endl;
    return 0;
}