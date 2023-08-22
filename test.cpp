#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

int main(int argC, char **argV)
{
    uint64_t a = std::stoi(argV[1]);
    std::vector<uint8_t> bytes = {};
    for (int i = 0; i < sizeof(uint64_t); i++)
    {
        bytes.insert(bytes.begin(), static_cast<uint8_t>(a >> (i * 8)));
    }

    std::cout << "bytes: ";
    for (int i = 0; i < sizeof(uint64_t); i++)
    {
        uint8_t b = bytes[i];
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(b) << " ";
    }

    std::ofstream file("test.bin", std::ios::binary);
    file << a;
    file.close();
}