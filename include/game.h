#pragma once
#include "Common.h"
#include "Containers.h"
#include "Ability.h"
#include <array>
#include <optional>

namespace hr {

enum class Phase { Draw, Main, Combat, End };

struct Rules {
    int startingHealth{50};
    int startingHand{5};
    int drawPerTurn{3};
    int maxTradeRow{5};
    std::vector<CardId> startingDeckFor(PlayerClass) const { return {}; }
};

struct Market {
    std::vector<CardId> tradeRow;
    std::vector<CardId> marketDeck;
    std::vector<CardId> fireGems;
    void refillUntil(int n) { (void)n; }
    CardId buyFromRow(int idx) { if (idx<0||idx>=(int)tradeRow.size()) return -1; auto id=tradeRow[idx]; tradeRow.erase(tradeRow.begin()+idx); return id; }
    CardId buyFireGem() { if (fireGems.empty()) return -1; CardId id=fireGems.back(); fireGems.pop_back(); return id; }
    bool canBuy(int cost,int goldPool) const { return goldPool>=cost; }
};

struct Player {
    std::string name;
    int health{0};
    Deck drawPile;
    Discard discard;
    Hand hand;
    Board board;
    int goldPool{0};
    int combatPool{0};

    void draw(int n) {
        for (int i=0;i<n;++i) { auto id = drawPile.drawOne(); if (id>=0) {} }
    }
    void gainHealth(int n){ health += n; }
    void addGold(int n){ goldPool += n; }
    void addCombat(int n){ combatPool += n; }
    void play(const CardRef&){ }
    void prepareNewTurn(){ goldPool=0; combatPool=0; }
    void discardHandAndDrawNewHand(){ hand.cards.clear(); }
    bool hasLost() const { return health<=0; }
};

struct Game {
    uint32_t seed{};
    Rules rules;
    Market market;
    std::array<Player,2> players;
    size_t activeIndex{0};
    Phase phase{Phase::Draw};

    void start() { for (auto &p: players) p.health = rules.startingHealth; }
    void nextTurn() { activeIndex = (activeIndex+1)%2; }
    bool isOver() const { return players[0].hasLost() || players[1].hasLost(); }
    int winner() const { if (players[0].hasLost()) return 1; if (players[1].hasLost()) return 0; return -1; }
};

} // namespace hr
