#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

class Player
{
    public:
        Player();
        std::string get_username();
        void set_username(std::string s);
        std::string get_race();
        void set_race(std::string s);
        std::string get_class();
        void set_class(std::string s);
    private:
        std::string m_username;
        std::string m_race;
        std::string m_class;
};

#endif
