// Includes
#include "../../../include/Game/Cartes/Carte.hpp"
#include "../../../include/Game/Cartes/CarteData.hpp"
#include "../../../include/Game/Cartes/Champion.hpp"
#include "../../../include/Game/Cartes/Action.hpp"
#include "../../../include/Game/Cartes/Objet.hpp"
#include "../../../include/Game/Systeme/Faction.hpp"
#include <vector>
#include <memory>

using Game::Cartes::Carte;
using Game::Cartes::Champion;
using Game::Cartes::Action;
using Game::Cartes::Objet;
using Game::Systeme::Faction;

namespace HeroRealms {

// Fonction pour créer toutes les cartes du Base Set
std::vector<std::shared_ptr<Game::Cartes::Carte>> CreerCartesBaseSet() {
    std::vector<std::shared_ptr<Game::Cartes::Carte>> cartes;
    
    // ==================== FACTION IMPÉRIALE ====================
    
    // Arkus, Imperial Dragon (8 gold, 6 defense, Guard)
    auto arkus = std::make_shared<Champion>(
        "Arkus, Imperial Dragon",
        Faction::IMPERIAL,
        8,
        6,
        true  // Guard
    );
    // Capacités: {Expend}: {Gain 5 combat} Draw a card. {Imperial Ally}: {Gain 6 health}
    cartes.push_back(arkus);
    
    // Close Ranks (3 gold)
    auto closeRanks = std::make_shared<Action>(
        "Close Ranks",
        Faction::IMPERIAL,
        3
    );
    // Capacités: {Gain 5 combat} +{2 combat} for each champion you have in play. {Imperial Ally}: {Gain 6 health}
    cartes.push_back(closeRanks);
    
    // Command (5 gold)
    auto command = std::make_shared<Action>(
        "Command",
        Faction::IMPERIAL,
        5
    );
    // Capacités: {Gain 2 gold} {Gain 3 combat} {Gain 4 health} Draw a card.
    cartes.push_back(command);
    
    // Darian, War Mage (4 gold, 5 defense)
    auto darian = std::make_shared<Champion>(
        "Darian, War Mage",
        Faction::IMPERIAL,
        4,
        5,
        false
    );
    // Capacités: {Expend}: {Gain 3 combat} or {Gain 4 health}
    cartes.push_back(darian);
    
    // Domination (7 gold)
    auto domination = std::make_shared<Action>(
        "Domination",
        Faction::IMPERIAL,
        7
    );
    // Capacités: {Gain 6 combat} {Gain 6 health} Draw a card. {Imperial Ally}: Prepare a champion.
    cartes.push_back(domination);
    
    // Cristov, the Just (5 gold, 5 defense, Guard)
    auto cristov = std::make_shared<Champion>(
        "Cristov, the Just",
        Faction::IMPERIAL,
        5,
        5,
        true
    );
    // Capacités: {Expend}: {Gain 2 combat} {Gain 3 health} {Imperial Ally}: Draw a card.
    cartes.push_back(cristov);
    
    // Kraka, High Priest (6 gold, 6 defense)
    auto kraka = std::make_shared<Champion>(
        "Kraka, High Priest",
        Faction::IMPERIAL,
        6,
        6,
        false
    );
    // Capacités: {Expend}: {Gain 2 health} Draw a card. {Imperial Ally}: Gain {2 health} for each champion you have in play.
    cartes.push_back(kraka);
    
    // Man-at-Arms (3 gold, 4 defense, Guard) x2
    for(int i = 0; i < 2; i++) {
        auto manAtArms = std::make_shared<Champion>(
            "Man-at-Arms",
            Faction::IMPERIAL,
            3,
            4,
            true
        );
        // Capacités: {Expend}: {Gain 2 combat} +{1 combat} for each other guard you have in play.
        cartes.push_back(manAtArms);
    }
    
    // Master Weyan (4 gold, 4 defense, Guard)
    auto masterWeyan = std::make_shared<Champion>(
        "Master Weyan",
        Faction::IMPERIAL,
        4,
        4,
        true
    );
    // Capacités: {Expend}: {Gain 3 combat} +{1 combat} for each other champion you have in play.
    cartes.push_back(masterWeyan);
    
    // Rally the Troops (4 gold)
    auto rallyTroops = std::make_shared<Action>(
        "Rally the Troops",
        Faction::IMPERIAL,
        4
    );
    // Capacités: {Gain 5 combat} {Gain 5 health} {Imperial Ally}: Prepare a champion.
    cartes.push_back(rallyTroops);
    
    // Recruit (2 gold) x3
    for(int i = 0; i < 3; i++) {
        auto recruit = std::make_shared<Action>(
            "Recruit",
            Faction::IMPERIAL,
            2
        );
        // Capacités: {Gain 2 gold} {Gain 3 health} +{1 health} for each champion you have in play. {Imperial Ally}: {Gain 1 gold}
        cartes.push_back(recruit);
    }
    
    // Tithe Priest (2 gold, 3 defense) x2
    for(int i = 0; i < 2; i++) {
        auto tithePriest = std::make_shared<Champion>(
            "Tithe Priest",
            Faction::IMPERIAL,
            2,
            3,
            false
        );
        // Capacités: {Expend}: {Gain 1 gold} or Gain {1 health} for each champion you have in play.
        cartes.push_back(tithePriest);
    }
    
    // Taxation (1 gold) x3
    for(int i = 0; i < 3; i++) {
        auto taxation = std::make_shared<Action>(
            "Taxation",
            Faction::IMPERIAL,
            1
        );
        // Capacités: {Gain 2 gold} {Imperial Ally}: {Gain 6 health}
        cartes.push_back(taxation);
    }
    
    // Word of Power (6 gold)
    auto wordOfPower = std::make_shared<Action>(
        "Word of Power",
        Faction::IMPERIAL,
        6
    );
    // Capacités: Draw two cards. {Imperial Ally}: {Gain 5 health} {Sacrifice}: {Gain 5 combat}
    cartes.push_back(wordOfPower);
    
    // ==================== FACTION GUILDE ====================
    
    // Borg, Ogre Mercenary (6 gold, 6 defense, Guard)
    auto borg = std::make_shared<Champion>(
        "Borg, Ogre Mercenary",
        Faction::GUILD,
        6,
        6,
        true
    );
    // Capacités: {Expend}: {Gain 4 combat}
    cartes.push_back(borg);
    
    // Bribe (3 gold) x3
    for(int i = 0; i < 3; i++) {
        auto bribe = std::make_shared<Action>(
            "Bribe",
            Faction::GUILD,
            3
        );
        // Capacités: {Gain 3 gold} {Guild Ally}: Put the next action you acquire this turn on top of your deck.
        cartes.push_back(bribe);
    }
    
    // Death Threat (3 gold)
    auto deathThreat = std::make_shared<Action>(
        "Death Threat",
        Faction::GUILD,
        3
    );
    // Capacités: {Gain 1 combat} Draw a card. {Guild Ally}: Stun target champion.
    cartes.push_back(deathThreat);
    
    // Deception (5 gold)
    auto deception = std::make_shared<Action>(
        "Deception",
        Faction::GUILD,
        5
    );
    // Capacités: {Gain 2 gold} Draw a card. {Guild Ally}: Put the next card you acquire this turn into your hand.
    cartes.push_back(deception);
    
    // Fire Bomb (8 gold)
    auto fireBomb = std::make_shared<Action>(
        "Fire Bomb",
        Faction::GUILD,
        8
    );
    // Capacités: {Gain 8 combat} Stun target champion. Draw a card. {Sacrifice}: {Gain 5 combat}
    cartes.push_back(fireBomb);
    
    // Hit Job (4 gold)
    auto hitJob = std::make_shared<Action>(
        "Hit Job",
        Faction::GUILD,
        4
    );
    // Capacités: {Gain 7 combat} {Guild Ally}: Stun target champion.
    cartes.push_back(hitJob);
    
    // Intimidation (2 gold) x2
    for(int i = 0; i < 2; i++) {
        auto intimidation = std::make_shared<Action>(
            "Intimidation",
            Faction::GUILD,
            2
        );
        // Capacités: {Gain 5 combat} {Guild Ally}: {Gain 2 gold}
        cartes.push_back(intimidation);
    }
    
    // Myros, Guild Mage (5 gold, 3 defense, Guard)
    auto myros = std::make_shared<Champion>(
        "Myros, Guild Mage",
        Faction::GUILD,
        5,
        3,
        true
    );
    // Capacités: {Expend}: {Gain 3 gold} {Guild Ally}: {Gain 4 combat}
    cartes.push_back(myros);
    
    // Parov, the Enforcer (5 gold, 5 defense, Guard)
    auto parov = std::make_shared<Champion>(
        "Parov, the Enforcer",
        Faction::GUILD,
        5,
        5,
        true
    );
    // Capacités: {Expend}: {Gain 3 combat} {Guild Ally}: Draw a card.
    cartes.push_back(parov);
    
    // Profit (1 gold) x3
    for(int i = 0; i < 3; i++) {
        auto profit = std::make_shared<Action>(
            "Profit",
            Faction::GUILD,
            1
        );
        // Capacités: {Gain 2 gold} {Guild Ally}: {Gain 4 combat}
        cartes.push_back(profit);
    }
    
    // Rake, Master Assassin (7 gold, 7 defense)
    auto rake = std::make_shared<Champion>(
        "Rake, Master Assassin",
        Faction::GUILD,
        7,
        7,
        false
    );
    // Capacités: {Expend}: {Gain 4 combat} You may stun target champion.
    cartes.push_back(rake);
    
    // Rasmus, the Smuggler (4 gold, 5 defense)
    auto rasmus = std::make_shared<Champion>(
        "Rasmus, the Smuggler",
        Faction::GUILD,
        4,
        5,
        false
    );
    // Capacités: {Expend}: {Gain 2 gold} {Guild Ally}: Put the next card you acquire this turn on top of your deck.
    cartes.push_back(rasmus);
    
    // Smash and Grab (6 gold)
    auto smashGrab = std::make_shared<Action>(
        "Smash and Grab",
        Faction::GUILD,
        6
    );
    // Capacités: {Gain 6 combat} You may put a card from your discard pile on top of your deck.
    cartes.push_back(smashGrab);
    
    // Street Thug (3 gold, 4 defense) x2
    for(int i = 0; i < 2; i++) {
        auto streetThug = std::make_shared<Champion>(
            "Street Thug",
            Faction::GUILD,
            3,
            4,
            false
        );
        // Capacités: {Expend}: {Gain 1 gold} or {Gain 2 combat}
        cartes.push_back(streetThug);
    }
    
    // ==================== FACTION NÉCROS ====================
    
    // Cult Priest (3 gold, 4 defense) x2
    for(int i = 0; i < 2; i++) {
        auto cultPriest = std::make_shared<Champion>(
            "Cult Priest",
            Faction::NECROS,
            3,
            4,
            false
        );
        // Capacités: {Expend}: {Gain 1 gold} or {Gain 1 combat} {Necros Ally}: {Gain 4 combat}
        cartes.push_back(cultPriest);
    }
    
    // Dark Energy (4 gold)
    auto darkEnergy = std::make_shared<Action>(
        "Dark Energy",
        Faction::NECROS,
        4
    );
    // Capacités: {Gain 7 combat} {Necros Ally}: Draw a card.
    cartes.push_back(darkEnergy);
    
    // Dark Reward (5 gold)
    auto darkReward = std::make_shared<Action>(
        "Dark Reward",
        Faction::NECROS,
        5
    );
    // Capacités: {Gain 3 gold} You may sacrifice a card in your hand or discard pile. {Necros Ally}: {Gain 6 combat}
    cartes.push_back(darkReward);
    
    // Death Cultist (2 gold, 3 defense, Guard) x2
    for(int i = 0; i < 2; i++) {
        auto deathCultist = std::make_shared<Champion>(
            "Death Cultist",
            Faction::NECROS,
            2,
            3,
            true
        );
        // Capacités: {Expend}: {Gain 2 combat}
        cartes.push_back(deathCultist);
    }
    
    // Death Touch (1 gold) x3
    for(int i = 0; i < 3; i++) {
        auto deathTouch = std::make_shared<Action>(
            "Death Touch",
            Faction::NECROS,
            1
        );
        // Capacités: {Gain 2 combat} You may sacrifice a card in your hand or discard pile. {Necros Ally}: {Gain 2 combat}
        cartes.push_back(deathTouch);
    }
    
    // Rayla, Endweaver (4 gold, 4 defense)
    auto rayla = std::make_shared<Champion>(
        "Rayla, Endweaver",
        Faction::NECROS,
        4,
        4,
        false
    );
    // Capacités: {Expend}: {Gain 3 combat} {Necros Ally}: Draw a card.
    cartes.push_back(rayla);
    
    // Influence (2 gold) x3
    for(int i = 0; i < 3; i++) {
        auto influence = std::make_shared<Action>(
            "Influence",
            Faction::NECROS,
            2
        );
        // Capacités: {Gain 3 gold} {Sacrifice}: {Gain 3 combat}
        cartes.push_back(influence);
    }
    
    // Krythos, Master Vampire (7 gold, 6 defense)
    auto krythos = std::make_shared<Champion>(
        "Krythos, Master Vampire",
        Faction::NECROS,
        7,
        6,
        false
    );
    // Capacités: {Expend}: {Gain 3 combat} You may sacrifice a card in your hand or discard pile. If you do, gain an additional {3 combat}.
    cartes.push_back(krythos);
    
    // Life Drain (6 gold)
    auto lifeDrain = std::make_shared<Action>(
        "Life Drain",
        Faction::NECROS,
        6
    );
    // Capacités: {Gain 8 combat} You may sacrifice a card in your hand or discard pile. {Necros Ally}: Draw a card.
    cartes.push_back(lifeDrain);
    
    // Lys, the Unseen (6 gold, 5 defense, Guard)
    auto lys = std::make_shared<Champion>(
        "Lys, the Unseen",
        Faction::NECROS,
        6,
        5,
        true
    );
    // Capacités: {Expend}: {Gain 2 combat} You may sacrifice a card in your hand or discard pile. If you do, gain an additional {2 combat}.
    cartes.push_back(lys);
    
    // The Rot (3 gold) x2
    for(int i = 0; i < 2; i++) {
        auto theRot = std::make_shared<Action>(
            "The Rot",
            Faction::NECROS,
            3
        );
        // Capacités: {Gain 4 combat} You may sacrifice a card in your hand or discard pile. {Necros Ally}: {Gain 3 combat}
        cartes.push_back(theRot);
    }
    
    // Tyrannor, the Devourer (8 gold, 6 defense, Guard)
    auto tyrannor = std::make_shared<Champion>(
        "Tyrannor, the Devourer",
        Faction::NECROS,
        8,
        6,
        true
    );
    // Capacités: {Expend}: {Gain 4 combat} You may sacrifice up to two cards in your hand and/or discard pile. {Necros Ally}: Draw a card.
    cartes.push_back(tyrannor);
    
    // Varrick, the Necromancer (5 gold, 3 defense)
    auto varrick = std::make_shared<Champion>(
        "Varrick, the Necromancer",
        Faction::NECROS,
        5,
        3,
        false
    );
    // Capacités: {Expend}: Take a champion from your discard pile and put it on top of your deck. {Necros Ally}: Draw a card.
    cartes.push_back(varrick);
    
    // ==================== FACTION SAUVAGE ====================
    
    // Broelyn, Loreweaver (4 gold, 6 defense)
    auto broelyn = std::make_shared<Champion>(
        "Broelyn, Loreweaver",
        Faction::WILD,
        4,
        6,
        false
    );
    // Capacités: {Expend}: {Gain 2 gold} {Wild Ally}: Target opponent discards a card.
    cartes.push_back(broelyn);
    
    // Cron, the Berserker (6 gold, 6 defense)
    auto cron = std::make_shared<Champion>(
        "Cron, the Berserker",
        Faction::WILD,
        6,
        6,
        false
    );
    // Capacités: {Expend}: {Gain 5 combat} {Wild Ally}: Draw a card.
    cartes.push_back(cron);
    
    // Dire Wolf (5 gold, 5 defense, Guard)
    auto direWolf = std::make_shared<Champion>(
        "Dire Wolf",
        Faction::WILD,
        5,
        5,
        true
    );
    // Capacités: {Expend}: {Gain 3 combat} {Wild Ally}: {Gain 4 combat}
    cartes.push_back(direWolf);
    
    // Elven Curse (3 gold) x2
    for(int i = 0; i < 2; i++) {
        auto elvenCurse = std::make_shared<Action>(
            "Elven Curse",
            Faction::WILD,
            3
        );
        // Capacités: {Gain 6 combat} Target opponent discards a card. {Wild Ally}: {Gain 3 combat}
        cartes.push_back(elvenCurse);
    }
    
    // Elven Gift (2 gold) x3
    for(int i = 0; i < 3; i++) {
        auto elvenGift = std::make_shared<Action>(
            "Elven Gift",
            Faction::WILD,
            2
        );
        // Capacités: {Gain 2 gold} You may draw a card. If you do, discard a card. {Wild Ally}: {Gain 4 combat}
        cartes.push_back(elvenGift);
    }
    
    // Grak, Storm Giant (8 gold, 7 defense, Guard)
    auto grak = std::make_shared<Champion>(
        "Grak, Storm Giant",
        Faction::WILD,
        8,
        7,
        true
    );
    // Capacités: {Expend}: {Gain 6 combat} You may draw a card. If you do, discard a card. {Wild Ally}: Draw a card, then discard a card.
    cartes.push_back(grak);
    
    // Nature's Bounty (4 gold)
    auto naturesBounty = std::make_shared<Action>(
        "Nature's Bounty",
        Faction::WILD,
        4
    );
    // Capacités: {Gain 4 gold} {Wild Ally}: Target opponent discards a card. {Sacrifice}: {Gain 4 combat}
    cartes.push_back(naturesBounty);
    
    // Orc Grunt (3 gold, 3 defense, Guard) x2
    for(int i = 0; i < 2; i++) {
        auto orcGrunt = std::make_shared<Champion>(
            "Orc Grunt",
            Faction::WILD,
            3,
            3,
            true
        );
        // Capacités: {Expend}: {Gain 2 combat} {Wild Ally}: Draw a card.
        cartes.push_back(orcGrunt);
    }
    
    // Rampage (6 gold)
    auto rampage = std::make_shared<Action>(
        "Rampage",
        Faction::WILD,
        6
    );
    // Capacités: {Gain 6 combat} You may draw up to two cards, then discard that many cards.
    cartes.push_back(rampage);
    
    // Torgen Rocksplitter (7 gold, 7 defense, Guard)
    auto torgen = std::make_shared<Champion>(
        "Torgen Rocksplitter",
        Faction::WILD,
        7,
        7,
        true
    );
    // Capacités: {Expend}: {Gain 4 combat} Target opponent discards a card.
    cartes.push_back(torgen);
    
    // Spark (1 gold) x3
    for(int i = 0; i < 3; i++) {
        auto spark = std::make_shared<Action>(
            "Spark",
            Faction::WILD,
            1
        );
        // Capacités: {Gain 3 combat} Target opponent discards a card. {Wild Ally}: {Gain 2 combat}
        cartes.push_back(spark);
    }
    
    // Wolf Form (5 gold)
    auto wolfForm = std::make_shared<Action>(
        "Wolf Form",
        Faction::WILD,
        5
    );
    // Capacités: {Gain 8 combat} Target opponent discards a card. {Sacrifice}: Target opponent discards a card.
    cartes.push_back(wolfForm);
    
    // Wolf Shaman (2 gold, 4 defense) x2
    for(int i = 0; i < 2; i++) {
        auto wolfShaman = std::make_shared<Champion>(
            "Wolf Shaman",
            Faction::WILD,
            2,
            4,
            false
        );
        // Capacités: {Expend}: {Gain 2 combat} +{1 combat} for each other {Wild} card you have in play.
        cartes.push_back(wolfShaman);
    }
    
    return cartes;
}

// Fonction pour créer les Fire Gems (16 exemplaires)
std::vector<std::shared_ptr<Game::Cartes::Carte>> CreerFireGems() {
    std::vector<std::shared_ptr<Game::Cartes::Carte>> gems;
    for(int i = 0; i < 16; i++) {
        auto gem = std::make_shared<Objet>(
            "Fire Gem",
            Faction::NEUTRE,
            2
        );
        // Capacités: {Gain 2 gold} {Sacrifice}: {Gain 3 combat}
        gems.push_back(gem);
    }
    return gems;
}

// Fonction pour créer le deck de départ d'un joueur
std::vector<std::shared_ptr<Game::Cartes::Carte>> CreerDeckDepart() {
    std::vector<std::shared_ptr<Game::Cartes::Carte>> deck;
    
    // 7 Gold
    for(int i = 0; i < 7; i++) {
        auto gold = std::make_shared<Objet>(
            "Gold",
            Faction::NEUTRE,
            0  // Pas de coût car carte de départ
        );
        // Capacités: {Gain 1 gold}
        deck.push_back(gold);
    }
    
    // 1 Ruby
    auto ruby = std::make_shared<Objet>(
        "Ruby",
        Faction::NEUTRE,
        0
    );
    // Capacités: {Gain 2 gold}
    deck.push_back(ruby);
    
    // 1 Dagger
    auto dagger = std::make_shared<Objet>(
        "Dagger",
        Faction::NEUTRE,
        0
    );
    // Capacités: {Gain 1 combat}
    deck.push_back(dagger);
    
    // 1 Shortsword
    auto shortsword = std::make_shared<Objet>(
        "Shortsword",
        Faction::NEUTRE,
        0
    );
    // Capacités: {Gain 2 combat}
    deck.push_back(shortsword);
    
    return deck;
}

} // namespace HeroRealms