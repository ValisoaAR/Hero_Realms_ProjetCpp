#pragma once
#include "Common.h"
#include <string>
#include <optional>
#include <vector>

namespace hr {

struct ResolutionContext;
struct Ability;

struct Card {
    virtual ~Card() = default;
    CardId id{};
    std::string name;
    int cost{};
    Faction faction{Faction::Neutral};
    CardType type{CardType::Action};
    std::shared_ptr<Ability> primary;
    std::shared_ptr<Ability> ally;
    std::shared_ptr<Ability> sacrifice;
};

struct ActionCard : Card {
};

struct Champion : Card {
    int defense{};
    bool guard{};
    bool exhausted{false};
    void ready() { exhausted = false; }
    void stun() { exhausted = true; }
};

} // namespace hr
