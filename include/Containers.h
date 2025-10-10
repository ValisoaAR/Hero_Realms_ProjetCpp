#pragma once
#include "Common.h"
#include "Card.h"
#include <vector>
#include <algorithm>

namespace hr {

struct CardRef { std::shared_ptr<Card> ptr; };
struct ChampionRef { std::shared_ptr<Champion> ptr; };

struct Deck {
    std::vector<CardId> stack;
    IRandom* rng{nullptr};
    bool empty() const { return stack.empty(); }
    CardId drawOne() {
        if (stack.empty()) return -1;
        CardId id = stack.back(); stack.pop_back(); return id;
    }
    void shuffleIn(const std::vector<CardId>& ids) {
        for (auto id : ids) stack.push_back(id);
        // no real RNG shuffle for stub
    }
};

struct Discard {
    std::vector<CardId> pile;
    void add(CardId id) { pile.push_back(id); }
    std::vector<CardId> takeAll() { auto r = pile; pile.clear(); return r; }
    bool empty() const { return pile.empty(); }
};

struct Hand {
    std::vector<CardRef> cards;
    void add(const CardRef& c) { cards.push_back(c); }
    void remove(const CardRef& c) {
        cards.erase(std::remove_if(cards.begin(), cards.end(), [&](const CardRef& x){ return x.ptr==c.ptr; }), cards.end());
    }
    size_t size() const { return cards.size(); }
};

struct Board {
    std::vector<ChampionRef> champions;
    std::vector<CardRef> actionsPlayedThisTurn;
    void enterChampion(const ChampionRef& c) { champions.push_back(c); }
    void readyChampions() { for (auto &c : champions) if (c.ptr) c.ptr->exhausted = false; }
    std::vector<ChampionRef> championsWithGuard() const {
        std::vector<ChampionRef> r;
        for (auto &c : champions) if (c.ptr && c.ptr->guard) r.push_back(c);
        return r;
    }
};

} // namespace hr
