#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <memory>

namespace hr {

using CardId = int;
using uint32_t = std::uint32_t;

enum class PlayerClass { Unknown };
enum class Faction { Neutral };
enum class CardType { Action, Champion };

class IRandom {
public:
    virtual ~IRandom() = default;
    virtual uint32_t nextU32() = 0;
};

} // namespace hr
