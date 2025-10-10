#pragma once
#include "Carte.hpp"

class Champion : public Carte {
public:
    int pv;
    bool active;
    bool garde;

    Champion(int id, const std::string& nom, int cout, const std::string& type, const std::string& faction, const std::string& description, int pv, bool active, bool garde);
};
