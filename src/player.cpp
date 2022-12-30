#include <iostream>
#include <string>

#include "player.h"

// Constructor
Player::Player() : m_username("none"), m_race("none"), m_class("none")
{
    // Create the seed
    srand(time(0));
}

void Player::set_username(std::string s)
{
    m_username = s;
}

std::string Player::get_username()
{
    return m_username;
}

void Player::set_race(std::string s)
{
    m_race = s;
}

std::string Player::get_race()
{
    return m_race;
}

void Player::set_class(std::string s)
{
    m_class = s;
}

std::string Player::get_class()
{
    return m_class;
}


/* // Only keeping this around to compile just player.cpp + player.h
int main()
{
    return 0;
}
*/
