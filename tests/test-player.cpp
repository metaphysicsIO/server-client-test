#include <iostream>
#include "../src/player.cpp"

void printline()
{
    std::cout << std::endl;
    std::cout << "-----------------------" << std::endl;
}

int main()
{
    std::cout << "Begin test for [player.cpp]" << std::endl;
    
    printline();
    
    std::cout << "[init test begin]" << std::endl;
    Player player;
    std::cout << "print default values:" << std::endl;
    std::cout << "\tusername: " << player.get_username() << std::endl;
    std::cout << "\trace: " << player.get_race() << std::endl;
    std::cout << "\tclass: " << player.get_class() << std::endl;
    // Add more as needed.
    
    std::cout << "[init test complete]" << std::endl;
    printline();

    std::cout << "[Setters / Getters test]" << std::endl;
    player.set_username("test-user-1234");
    player.set_race("Human");
    player.set_class("Adventurer");
    std::cout << "\tusername: " << player.get_username() << std::endl;
    std::cout << "\trace: " << player.get_race() << std::endl;
    std::cout << "\tclass: " << player.get_class() << std::endl;

    std::cout << "[Set/Get test complete]" << std::endl;
    printline();

    std::cout << "End test for [player.cpp]" << std::endl;
}
