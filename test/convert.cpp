#include <iostream>
#include <string>
#include <cctype>



std::string encrypt(std::string s)
{
    std::string transformed;

    // Bit-shifting o the right.
    for(size_t i = 0; i < s.size(); ++i)
    {

        transformed.append(1, (s[i] << 1) | (s[i] >> 7)&0x01);
    }

    return transformed;
}

std::string decrypt(std::string s)
{
    std::string transformed;
    for(size_t i = 0; i < s.size(); ++i)
    {
        // Bit-shift back?
        transformed.append(1, (s[i] >> 1) | (s[i] << 7)&0x01);
    }
    return transformed;
}

int main()
{
    std::string plain;

    std::cout << "input msg: ";
    std::cin >> plain;
    std::cout << std::endl;

    std::cout << "PLAIN MSG: " << plain << std::endl;

    std::cout << "encrypted: " << encrypt(plain) << std::endl;

    std::cout << "decrypted: " << decrypt(encrypt(plain)) << std::endl;

    return 0;
}
