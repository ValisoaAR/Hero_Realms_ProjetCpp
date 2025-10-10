#pragma once
#include "Common.h"
#include <random>

namespace hr {

class SimpleRng : public IRandom {
public:
    SimpleRng(uint32_t s=0) { engine.seed(s); }
    uint32_t nextU32() override { return static_cast<uint32_t>(engine()); }
private:
    std::mt19937 engine;
};

}
