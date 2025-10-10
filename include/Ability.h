#pragma once
#include "Common.h"
#include "Effects.h"
#include <vector>

namespace hr {

struct ResolutionContext;

struct Ability {
    std::vector<std::shared_ptr<Effect>> effects;
    void resolve(ResolutionContext& ctx) {
        for (auto &e : effects) if (e) e->apply(ctx);
    }
};

struct ResolutionContext {
    // references to relevant objects kept as pointers for simplicity
    struct Game* game = nullptr;
    struct Player* self = nullptr;
    struct Player* opponent = nullptr;
    struct Rules* rules = nullptr;
};

} // namespace hr
