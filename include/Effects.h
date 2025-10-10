#pragma once
#include "Common.h"
#include <vector>

namespace hr {

struct ResolutionContext;

struct Effect {
    virtual ~Effect() = default;
    virtual void apply(ResolutionContext& ctx) = 0;
};

struct EffGold : Effect { int amount{0}; void apply(ResolutionContext&) override {} };
struct EffCombat : Effect { int amount{0}; void apply(ResolutionContext&) override {} };
struct EffHeal : Effect { int amount{0}; void apply(ResolutionContext&) override {} };
struct EffDraw : Effect { int cards{0}; void apply(ResolutionContext&) override {} };
struct EffDiscard : Effect { int cards{0}; void apply(ResolutionContext&) override {} };
struct EffScrapFromHandOrDiscard : Effect { /*predicate omitted*/ void apply(ResolutionContext&) override {} };
struct EffStunChampion : Effect { void apply(ResolutionContext&) override {} };
struct EffAcquireTopdeck : Effect { void apply(ResolutionContext&) override {} };
struct EffRecycle : Effect { void apply(ResolutionContext&) override {} };

} // namespace hr
