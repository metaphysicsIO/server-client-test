#include <iostream>
#include <bitset>

int main()
{
    // Set stage.
    char text = 'a';
    int i = int(text);
    std::bitset<16> x(text);

    std::cout << "[Begin]" << std::endl;

    std::cout << "Value: " << text << "\n"
              << "INT: " << i << "\n"
              << "BIN: " << x << std::endl;
    std::cout << std::endl;

    // invert bit.
    text = (~i);
    i = int(text);
    std::bitset<16> y(text);

    std::cout << "Value: " << text << "\n"
              << "INT: " << i << "\n"
              << "BIN: " << y << std::endl;
    std::cout << std::endl;

    // invert back.
    text = (~i);
    i = int(text);
    std::bitset<16> z(text);

    std::cout << "Value: " << text << "\n"
              << "INT: " << i << "\n"
              << "BIN: " << z << std::endl;


    return 0;
}
