// Includes
#include "../../../include/Game/Cartes/Carte.hpp"
#include "../../../include/Game/Cartes/CarteData.hpp"
#include "../../../include/Game/Cartes/Champion.hpp"
#include "../../../include/Game/Cartes/Action.hpp"
#include "../../../include/Game/Cartes/Objet.hpp"
#include "../../../include/Game/Systeme/Faction.hpp"
#include "../../../include/Game/Systeme/Effet.hpp"
#include <vector>
#include <memory>

using Game::Cartes::Carte;
using Game::Cartes::Champion;
using Game::Cartes::Action;
using Game::Cartes::Objet;
using Game::Systeme::Faction;
using Game::Systeme::FactionType;
using Game::Systeme::Effet;

namespace HeroRealms {

// Fonction pour créer toutes les cartes du Base Set
std::vector<std::shared_ptr<Game::Cartes::Carte>> CreerCartesBaseSet() {
    std::vector<std::shared_ptr<Game::Cartes::Carte>> cartes;
    
    // ==================== FACTION IMPÉRIALE ====================
    
    // Arkus, IMPERIAL Dragon (8 gold, 6 defense, Guard)
    auto arkus = std::make_shared<Champion>(
        "Arkus, IMPERIAL Dragon",
        FactionType::IMPERIAL,
        8,
        6,
        true  // Guard
    );
    // Capacités: {Expend}: {Gain 5 combat} Draw a card. {IMPERIAL Ally}: {Gain 6 health}
    arkus->ajouterEffet(Effet("combat", 5, "aucune", "", "expend"));
    arkus->ajouterEffet(Effet("pioche", 1, "aucune", "", "expend"));
    arkus->ajouterEffet(Effet("soin", 6, "ally", "IMPERIAL", "ally"));
    cartes.push_back(arkus);
    
    // Close Ranks (3 gold)
    auto closeRanks = std::make_shared<Action>(
        "Close Ranks",
        FactionType::IMPERIAL,
        3
    );
    // Capacités: {Gain 5 combat} +{2 combat} for each champion you have in play. {IMPERIAL Ally}: {Gain 6 health}
    closeRanks->ajouterEffet(Effet("combat", 5, "aucune", "", "immediate"));
    // Note: +2 combat par champion nécessite logique spéciale dans le moteur de jeu
    closeRanks->ajouterEffet(Effet("soin", 6, "ally", "IMPERIAL", "ally"));
    cartes.push_back(closeRanks);
    
    // Command (5 gold)
    auto command = std::make_shared<Action>(
        "Command",
        FactionType::IMPERIAL,
        5
    );
    // Capacités: {Gain 2 gold} {Gain 3 combat} {Gain 4 health} Draw a card.
    command->ajouterEffet(Effet("or", 2, "aucune", "", "immediate"));
    command->ajouterEffet(Effet("combat", 3, "aucune", "", "immediate"));
    command->ajouterEffet(Effet("soin", 4, "aucune", "", "immediate"));
    command->ajouterEffet(Effet("pioche", 1, "aucune", "", "immediate"));
    cartes.push_back(command);
    
    // Darian, War Mage (4 gold, 5 defense)
    auto darian = std::make_shared<Champion>(
        "Darian, War Mage",
        FactionType::IMPERIAL,
        4,
        5,
        false
    );
    // Capacités: {Expend}: {Gain 3 combat} or {Gain 4 health}
    darian->ajouterEffet(Effet("choix", 0, "aucune", "", "expend")); // choix entre combat:3 et soin:4
    cartes.push_back(darian);
    
    // Domination (7 gold)
    auto domination = std::make_shared<Action>(
        "Domination",
        FactionType::IMPERIAL,
        7
    );
    // Capacités: {Gain 6 combat} {Gain 6 health} Draw a card. {IMPERIAL Ally}: Prepare a champion.
    domination->ajouterEffet(Effet("combat", 6, "aucune", "", "immediate"));
    domination->ajouterEffet(Effet("soin", 6, "aucune", "", "immediate"));
    domination->ajouterEffet(Effet("pioche", 1, "aucune", "", "immediate"));
    domination->ajouterEffet(Effet("prepare", 1, "ally", "IMPERIAL", "ally"));
    cartes.push_back(domination);
    
    // Cristov, the Just (5 gold, 5 defense, Guard)
    auto cristov = std::make_shared<Champion>(
        "Cristov, the Just",
        FactionType::IMPERIAL,
        5,
        5,
        true
    );
    // Capacités: {Expend}: {Gain 2 combat} {Gain 3 health} {IMPERIAL Ally}: Draw a card.
    cristov->ajouterEffet(Effet("combat", 2, "aucune", "", "expend"));
    cristov->ajouterEffet(Effet("soin", 3, "aucune", "", "expend"));
    cristov->ajouterEffet(Effet("pioche", 1, "ally", "IMPERIAL", "ally"));
    cartes.push_back(cristov);
    
    // Kraka, High Priest (6 gold, 6 defense)
    auto kraka = std::make_shared<Champion>(
        "Kraka, High Priest",
        FactionType::IMPERIAL,
        6,
        6,
        false
    );
    // Capacités: {Expend}: {Gain 2 health} Draw a card. {IMPERIAL Ally}: Gain {2 health} for each champion you have in play.
    kraka->ajouterEffet(Effet("soin", 2, "aucune", "", "expend"));
    kraka->ajouterEffet(Effet("pioche", 1, "aucune", "", "expend"));
    // Note: +2 health par champion nécessite logique spéciale
    cartes.push_back(kraka);
    
    // Man-at-Arms (3 gold, 4 defense, Guard) x2
    for(int i = 0; i < 2; i++) {
        auto manAtArms = std::make_shared<Champion>(
            "Man-at-Arms",
            FactionType::IMPERIAL,
            3,
            4,
            true
        );
        // Capacités: {Expend}: {Gain 2 combat} +{1 combat} for each other guard you have in play.
        manAtArms->ajouterEffet(Effet("combat", 2, "aucune", "", "expend"));
        // Note: +1 combat par guard nécessite logique spéciale
        cartes.push_back(manAtArms);
    }
    
    // Master Weyan (4 gold, 4 defense, Guard)
    auto masterWeyan = std::make_shared<Champion>(
        "Master Weyan",
        FactionType::IMPERIAL,
        4,
        4,
        true
    );
    // Capacités: {Expend}: {Gain 3 combat} +{1 combat} for each other champion you have in play.
    masterWeyan->ajouterEffet(Effet("combat", 3, "aucune", "", "expend"));
    // Note: +1 combat par champion nécessite logique spéciale
    cartes.push_back(masterWeyan);
    
    // Rally the Troops (4 gold)
    auto rallyTroops = std::make_shared<Action>(
        "Rally the Troops",
        FactionType::IMPERIAL,
        4
    );
    // Capacités: {Gain 5 combat} {Gain 5 health} {IMPERIAL Ally}: Prepare a champion.
    rallyTroops->ajouterEffet(Effet("combat", 5, "aucune", "", "immediate"));
    rallyTroops->ajouterEffet(Effet("soin", 5, "aucune", "", "immediate"));
    rallyTroops->ajouterEffet(Effet("prepare", 1, "ally", "IMPERIAL", "ally"));
    cartes.push_back(rallyTroops);
    
    // Recruit (2 gold) x3
    for(int i = 0; i < 3; i++) {
        auto recruit = std::make_shared<Action>(
            "Recruit",
            FactionType::IMPERIAL,
            2
        );
        // Capacités: {Gain 2 gold} {Gain 3 health} +{1 health} for each champion you have in play. {IMPERIAL Ally}: {Gain 1 gold}
        recruit->ajouterEffet(Effet("or", 2, "aucune", "", "immediate"));
        recruit->ajouterEffet(Effet("soin", 3, "aucune", "", "immediate"));
        // Note: +1 health par champion nécessite logique spéciale
        recruit->ajouterEffet(Effet("or", 1, "ally", "IMPERIAL", "ally"));
        cartes.push_back(recruit);
    }
    
    // Tithe Priest (2 gold, 3 defense) x2
    for(int i = 0; i < 2; i++) {
        auto tithePriest = std::make_shared<Champion>(
            "Tithe Priest",
            FactionType::IMPERIAL,
            2,
            3,
            false
        );
        // Capacités: {Expend}: {Gain 1 gold} or Gain {1 health} for each champion you have in play.
        tithePriest->ajouterEffet(Effet("choix", 0, "aucune", "", "expend")); // choix entre or:1 ou soin par champion
        cartes.push_back(tithePriest);
    }
    
    // Taxation (1 gold) x3
    for(int i = 0; i < 3; i++) {
        auto taxation = std::make_shared<Action>(
            "Taxation",
            FactionType::IMPERIAL,
            1
        );
        // Capacités: {Gain 2 gold} {IMPERIAL Ally}: {Gain 6 health}
        taxation->ajouterEffet(Effet("or", 2, "aucune", "", "immediate"));
        taxation->ajouterEffet(Effet("soin", 6, "ally", "IMPERIAL", "ally"));
        cartes.push_back(taxation);
    }
    
    // Word of Power (6 gold)
    auto wordOfPower = std::make_shared<Action>(
        "Word of Power",
        FactionType::IMPERIAL,
        6
    );
    // Capacités: Draw two cards. {IMPERIAL Ally}: {Gain 5 health} {Sacrifice}: {Gain 5 combat}
    wordOfPower->ajouterEffet(Effet("pioche", 2, "aucune", "", "immediate"));
    wordOfPower->ajouterEffet(Effet("soin", 5, "ally", "IMPERIAL", "ally"));
    wordOfPower->ajouterEffet(Effet("combat", 5, "aucune", "", "sacrifice"));
    cartes.push_back(wordOfPower);
    
    // ==================== FACTION GUILD ====================
    
    // Borg, Ogre Mercenary (6 gold, 6 defense, Guard)
    auto borg = std::make_shared<Champion>(
        "Borg, Ogre Mercenary",
        FactionType::GUILD,
        6,
        6,
        true
    );
    // Capacités: {Expend}: {Gain 4 combat}
    borg->ajouterEffet(Effet("combat", 4, "aucune", "", "expend"));
    cartes.push_back(borg);
    
    // Bribe (3 gold) x3
    for(int i = 0; i < 3; i++) {
        auto bribe = std::make_shared<Action>(
            "Bribe",
            FactionType::GUILD,
            3
        );
        // Capacités: {Gain 3 gold} {GUILD Ally}: Put the next action you acquire this turn on top of your deck.
        bribe->ajouterEffet(Effet("or", 3, "aucune", "", "immediate"));
        // Note: effet spécial "carte sur dessus deck" nécessite logique spéciale
        cartes.push_back(bribe);
    }
    
    // Death Threat (3 gold)
    auto deathThreat = std::make_shared<Action>(
        "Death Threat",
        FactionType::GUILD,
        3
    );
    // Capacités: {Gain 1 combat} Draw a card. {GUILD Ally}: Stun target champion.
    deathThreat->ajouterEffet(Effet("combat", 1, "aucune", "", "immediate"));
    deathThreat->ajouterEffet(Effet("pioche", 1, "aucune", "", "immediate"));
    deathThreat->ajouterEffet(Effet("stun", 1, "ally", "GUILD", "ally"));
    cartes.push_back(deathThreat);
    
    // Deception (5 gold)
    auto deception = std::make_shared<Action>(
        "Deception",
        FactionType::GUILD,
        5
    );
    // Capacités: {Gain 2 gold} Draw a card. {GUILD Ally}: Put the next card you acquire this turn into your hand.
    deception->ajouterEffet(Effet("or", 2, "aucune", "", "immediate"));
    deception->ajouterEffet(Effet("pioche", 1, "aucune", "", "immediate"));
    // Note: effet spécial "carte en main" nécessite logique spéciale
    cartes.push_back(deception);
    
    // Fire Bomb (8 gold)
    auto fireBomb = std::make_shared<Action>(
        "Fire Bomb",
        FactionType::GUILD,
        8
    );
    // Capacités: {Gain 8 combat} Stun target champion. Draw a card. {Sacrifice}: {Gain 5 combat}
    fireBomb->ajouterEffet(Effet("combat", 8, "aucune", "", "immediate"));
    fireBomb->ajouterEffet(Effet("stun", 1, "aucune", "", "immediate"));
    fireBomb->ajouterEffet(Effet("pioche", 1, "aucune", "", "immediate"));
    fireBomb->ajouterEffet(Effet("combat", 5, "aucune", "", "sacrifice"));
    cartes.push_back(fireBomb);
    
    // Hit Job (4 gold)
    auto hitJob = std::make_shared<Action>(
        "Hit Job",
        FactionType::GUILD,
        4
    );
    // Capacités: {Gain 7 combat} {GUILD Ally}: Stun target champion.
    hitJob->ajouterEffet(Effet("combat", 7, "aucune", "", "immediate"));
    hitJob->ajouterEffet(Effet("stun", 1, "ally", "GUILD", "ally"));
    cartes.push_back(hitJob);
    
    // Intimidation (2 gold) x2
    for(int i = 0; i < 2; i++) {
        auto intimidation = std::make_shared<Action>(
            "Intimidation",
            FactionType::GUILD,
            2
        );
        // Capacités: {Gain 5 combat} {GUILD Ally}: {Gain 2 gold}
        intimidation->ajouterEffet(Effet("combat", 5, "aucune", "", "immediate"));
        intimidation->ajouterEffet(Effet("or", 2, "ally", "GUILD", "ally"));
        cartes.push_back(intimidation);
    }
    
    // Myros, GUILD Mage (5 gold, 3 defense, Guard)
    auto myros = std::make_shared<Champion>(
        "Myros, GUILD Mage",
        FactionType::GUILD,
        5,
        3,
        true
    );
    // Capacités: {Expend}: {Gain 3 gold} {GUILD Ally}: {Gain 4 combat}
    myros->ajouterEffet(Effet("or", 3, "aucune", "", "expend"));
    myros->ajouterEffet(Effet("combat", 4, "ally", "GUILD", "ally"));
    cartes.push_back(myros);
    
    // Parov, the Enforcer (5 gold, 5 defense, Guard)
    auto parov = std::make_shared<Champion>(
        "Parov, the Enforcer",
        FactionType::GUILD,
        5,
        5,
        true
    );
    // Capacités: {Expend}: {Gain 3 combat} {GUILD Ally}: Draw a card.
    parov->ajouterEffet(Effet("combat", 3, "aucune", "", "expend"));
    parov->ajouterEffet(Effet("pioche", 1, "ally", "GUILD", "ally"));
    cartes.push_back(parov);
    
    // Profit (1 gold) x3
    for(int i = 0; i < 3; i++) {
        auto profit = std::make_shared<Action>(
            "Profit",
            FactionType::GUILD,
            1
        );
        // Capacités: {Gain 2 gold} {GUILD Ally}: {Gain 4 combat}
        profit->ajouterEffet(Effet("or", 2, "aucune", "", "immediate"));
        profit->ajouterEffet(Effet("combat", 4, "ally", "GUILD", "ally"));
        cartes.push_back(profit);
    }
    
    // Rake, Master Assassin (7 gold, 7 defense)
    auto rake = std::make_shared<Champion>(
        "Rake, Master Assassin",
        FactionType::GUILD,
        7,
        7,
        false
    );
    // Capacités: {Expend}: {Gain 4 combat} You may stun target champion.
    rake->ajouterEffet(Effet("combat", 4, "aucune", "", "expend"));
    rake->ajouterEffet(Effet("stun", 1, "aucune", "", "expend")); // optionnel
    cartes.push_back(rake);
    
    // Rasmus, the Smuggler (4 gold, 5 defense)
    auto rasmus = std::make_shared<Champion>(
        "Rasmus, the Smuggler",
        FactionType::GUILD,
        4,
        5,
        false
    );
    // Capacités: {Expend}: {Gain 2 gold} {GUILD Ally}: Put the next card you acquire this turn on top of your deck.
    rasmus->ajouterEffet(Effet("or", 2, "aucune", "", "expend"));
    // Note: effet spécial "carte sur dessus deck" nécessite logique spéciale
    cartes.push_back(rasmus);
    
    // Smash and Grab (6 gold)
    auto smashGrab = std::make_shared<Action>(
        "Smash and Grab",
        FactionType::GUILD,
        6
    );
    // Capacités: {Gain 6 combat} You may put a card from your discard pile on top of your deck.
    smashGrab->ajouterEffet(Effet("combat", 6, "aucune", "", "immediate"));
    // Note: effet spécial défausse vers dessus deck nécessite logique spéciale
    cartes.push_back(smashGrab);
    
    // Street Thug (3 gold, 4 defense) x2
    for(int i = 0; i < 2; i++) {
        auto streetThug = std::make_shared<Champion>(
            "Street Thug",
            FactionType::GUILD,
            3,
            4,
            false
        );
        // Capacités: {Expend}: {Gain 1 gold} or {Gain 2 combat}
        streetThug->ajouterEffet(Effet("choix", 0, "aucune", "", "expend")); // choix entre or:1 et combat:2
        cartes.push_back(streetThug);
    }
    
    // ==================== FACTION NECROS ====================
    
    // Cult Priest (3 gold, 4 defense) x2
    for(int i = 0; i < 2; i++) {
        auto cultPriest = std::make_shared<Champion>(
            "Cult Priest",
            FactionType::NECROS,
            3,
            4,
            false
        );
        // Capacités: {Expend}: {Gain 1 gold} or {Gain 1 combat} {Necros Ally}: {Gain 4 combat}
        cultPriest->ajouterEffet(Effet("choix", 0, "aucune", "", "expend")); // choix entre or:1 et combat:1
        cultPriest->ajouterEffet(Effet("combat", 4, "ally", "NECROS", "ally"));
        cartes.push_back(cultPriest);
    }
    
    // Dark Energy (4 gold)
    auto darkEnergy = std::make_shared<Action>(
        "Dark Energy",
        FactionType::NECROS,
        4
    );
    // Capacités: {Gain 7 combat} {Necros Ally}: Draw a card.
    darkEnergy->ajouterEffet(Effet("combat", 7, "aucune", "", "immediate"));
    darkEnergy->ajouterEffet(Effet("pioche", 1, "ally", "NECROS", "ally"));
    cartes.push_back(darkEnergy);
    
    // Dark Reward (5 gold)
    auto darkReward = std::make_shared<Action>(
        "Dark Reward",
        FactionType::NECROS,
        5
    );
    // Capacités: {Gain 3 gold} You may sacrifice a card in your hand or discard pile. {Necros Ally}: {Gain 6 combat}
    darkReward->ajouterEffet(Effet("or", 3, "aucune", "", "immediate"));
    darkReward->ajouterEffet(Effet("sacrifice", 1, "aucune", "", "immediate")); // optionnel
    darkReward->ajouterEffet(Effet("combat", 6, "ally", "NECROS", "ally"));
    cartes.push_back(darkReward);
    
    // Death Cultist (2 gold, 3 defense, Guard) x2
    for(int i = 0; i < 2; i++) {
        auto deathCultist = std::make_shared<Champion>(
            "Death Cultist",
            FactionType::NECROS,
            2,
            3,
            true
        );
        // Capacités: {Expend}: {Gain 2 combat}
        deathCultist->ajouterEffet(Effet("combat", 2, "aucune", "", "expend"));
        cartes.push_back(deathCultist);
    }
    
    // Death Touch (1 gold) x3
    for(int i = 0; i < 3; i++) {
        auto deathTouch = std::make_shared<Action>(
            "Death Touch",
            FactionType::NECROS,
            1
        );
        // Capacités: {Gain 2 combat} You may sacrifice a card in your hand or discard pile. {Necros Ally}: {Gain 2 combat}
        deathTouch->ajouterEffet(Effet("combat", 2, "aucune", "", "immediate"));
        deathTouch->ajouterEffet(Effet("sacrifice", 1, "aucune", "", "immediate")); // optionnel
        deathTouch->ajouterEffet(Effet("combat", 2, "ally", "NECROS", "ally"));
        cartes.push_back(deathTouch);
    }
    
    // Rayla, Endweaver (4 gold, 4 defense)
    auto rayla = std::make_shared<Champion>(
        "Rayla, Endweaver",
        FactionType::NECROS,
        4,
        4,
        false
    );
    // Capacités: {Expend}: {Gain 3 combat} {Necros Ally}: Draw a card.
    rayla->ajouterEffet(Effet("combat", 3, "aucune", "", "expend"));
    rayla->ajouterEffet(Effet("pioche", 1, "ally", "NECROS", "ally"));
    cartes.push_back(rayla);
    
    // Influence (2 gold) x3
    for(int i = 0; i < 3; i++) {
        auto influence = std::make_shared<Action>(
            "Influence",
            FactionType::NECROS,
            2
        );
        // Capacités: {Gain 3 gold} {Sacrifice}: {Gain 3 combat}
        influence->ajouterEffet(Effet("or", 3, "aucune", "", "immediate"));
        influence->ajouterEffet(Effet("combat", 3, "aucune", "", "sacrifice"));
        cartes.push_back(influence);
    }
    
    // Krythos, Master Vampire (7 gold, 6 defense)
    auto krythos = std::make_shared<Champion>(
        "Krythos, Master Vampire",
        FactionType::NECROS,
        7,
        6,
        false
    );
    // Capacités: {Expend}: {Gain 3 combat} You may sacrifice a card in your hand or discard pile. If you do, gain an additional {3 combat}.
    krythos->ajouterEffet(Effet("combat", 3, "aucune", "", "expend"));
    krythos->ajouterEffet(Effet("sacrifice", 1, "aucune", "", "expend")); // optionnel, +3 combat si fait
    cartes.push_back(krythos);
    
    // Life Drain (6 gold)
    auto lifeDrain = std::make_shared<Action>(
        "Life Drain",
        FactionType::NECROS,
        6
    );
    // Capacités: {Gain 8 combat} You may sacrifice a card in your hand or discard pile. {Necros Ally}: Draw a card.
    lifeDrain->ajouterEffet(Effet("combat", 8, "aucune", "", "immediate"));
    lifeDrain->ajouterEffet(Effet("sacrifice", 1, "aucune", "", "immediate")); // optionnel
    lifeDrain->ajouterEffet(Effet("pioche", 1, "ally", "NECROS", "ally"));
    cartes.push_back(lifeDrain);
    
    // Lys, the Unseen (6 gold, 5 defense, Guard)
    auto lys = std::make_shared<Champion>(
        "Lys, the Unseen",
        FactionType::NECROS,
        6,
        5,
        true
    );
    // Capacités: {Expend}: {Gain 2 combat} You may sacrifice a card in your hand or discard pile. If you do, gain an additional {2 combat}.
    lys->ajouterEffet(Effet("combat", 2, "aucune", "", "expend"));
    lys->ajouterEffet(Effet("sacrifice", 1, "aucune", "", "expend")); // optionnel, +2 combat si fait
    cartes.push_back(lys);
    
    // The Rot (3 gold) x2
    for(int i = 0; i < 2; i++) {
        auto theRot = std::make_shared<Action>(
            "The Rot",
            FactionType::NECROS,
            3
        );
        // Capacités: {Gain 4 combat} You may sacrifice a card in your hand or discard pile. {Necros Ally}: {Gain 3 combat}
        theRot->ajouterEffet(Effet("combat", 4, "aucune", "", "immediate"));
        theRot->ajouterEffet(Effet("sacrifice", 1, "aucune", "", "immediate")); // optionnel
        theRot->ajouterEffet(Effet("combat", 3, "ally", "NECROS", "ally"));
        cartes.push_back(theRot);
    }
    
    // Tyrannor, the Devourer (8 gold, 6 defense, Guard)
    auto tyrannor = std::make_shared<Champion>(
        "Tyrannor, the Devourer",
        FactionType::NECROS,
        8,
        6,
        true
    );
    // Capacités: {Expend}: {Gain 4 combat} You may sacrifice up to two cards in your hand and/or discard pile. {Necros Ally}: Draw a card.
    tyrannor->ajouterEffet(Effet("combat", 4, "aucune", "", "expend"));
    tyrannor->ajouterEffet(Effet("sacrifice", 2, "aucune", "", "expend")); // optionnel, jusqu'à 2
    tyrannor->ajouterEffet(Effet("pioche", 1, "ally", "NECROS", "ally"));
    cartes.push_back(tyrannor);
    
    // Varrick, the Necromancer (5 gold, 3 defense)
    auto varrick = std::make_shared<Champion>(
        "Varrick, the Necromancer",
        FactionType::NECROS,
        5,
        3,
        false
    );
    // Capacités: {Expend}: Take a champion from your discard pile and put it on top of your deck. {Necros Ally}: Draw a card.
    // Note: effet spécial champion de défausse vers dessus deck nécessite logique spéciale
    varrick->ajouterEffet(Effet("pioche", 1, "ally", "NECROS", "ally"));
    cartes.push_back(varrick);
    
    // ==================== FACTION WILD ====================
    
    // Broelyn, Loreweaver (4 gold, 6 defense)
    auto broelyn = std::make_shared<Champion>(
        "Broelyn, Loreweaver",
        FactionType::WILD,
        4,
        6,
        false
    );
    // Capacités: {Expend}: {Gain 2 gold} {WILD Ally}: Target opponent discards a card.
    broelyn->ajouterEffet(Effet("or", 2, "aucune", "", "expend"));
    broelyn->ajouterEffet(Effet("defausse_adversaire", 1, "ally", "WILD", "ally"));
    cartes.push_back(broelyn);
    
    // Cron, the Berserker (6 gold, 6 defense)
    auto cron = std::make_shared<Champion>(
        "Cron, the Berserker",
        FactionType::WILD,
        6,
        6,
        false
    );
    // Capacités: {Expend}: {Gain 5 combat} {WILD Ally}: Draw a card.
    cron->ajouterEffet(Effet("combat", 5, "aucune", "", "expend"));
    cron->ajouterEffet(Effet("pioche", 1, "ally", "WILD", "ally"));
    cartes.push_back(cron);
    
    // Dire Wolf (5 gold, 5 defense, Guard)
    auto direWolf = std::make_shared<Champion>(
        "Dire Wolf",
        FactionType::WILD,
        5,
        5,
        true
    );
    // Capacités: {Expend}: {Gain 3 combat} {WILD Ally}: {Gain 4 combat}
    direWolf->ajouterEffet(Effet("combat", 3, "aucune", "", "expend"));
    direWolf->ajouterEffet(Effet("combat", 4, "ally", "WILD", "ally"));
    cartes.push_back(direWolf);
    
    // Elven Curse (3 gold) x2
    for(int i = 0; i < 2; i++) {
        auto elvenCurse = std::make_shared<Action>(
            "Elven Curse",
            FactionType::WILD,
            3
        );
        // Capacités: {Gain 6 combat} Target opponent discards a card. {WILD Ally}: {Gain 3 combat}
        elvenCurse->ajouterEffet(Effet("combat", 6, "aucune", "", "immediate"));
        elvenCurse->ajouterEffet(Effet("defausse_adversaire", 1, "aucune", "", "immediate"));
        elvenCurse->ajouterEffet(Effet("combat", 3, "ally", "WILD", "ally"));
        cartes.push_back(elvenCurse);
    }
    
    // Elven Gift (2 gold) x3
    for(int i = 0; i < 3; i++) {
        auto elvenGift = std::make_shared<Action>(
            "Elven Gift",
            FactionType::WILD,
            2
        );
        // Capacités: {Gain 2 gold} You may draw a card. If you do, discard a card. {WILD Ally}: {Gain 4 combat}
        elvenGift->ajouterEffet(Effet("or", 2, "aucune", "", "immediate"));
        // Note: pioche conditionnelle + défausse nécessite logique spéciale
        elvenGift->ajouterEffet(Effet("combat", 4, "ally", "WILD", "ally"));
        cartes.push_back(elvenGift);
    }
    
    // Grak, Storm Giant (8 gold, 7 defense, Guard)
    auto grak = std::make_shared<Champion>(
        "Grak, Storm Giant",
        FactionType::WILD,
        8,
        7,
        true
    );
    // Capacités: {Expend}: {Gain 6 combat} You may draw a card. If you do, discard a card. {WILD Ally}: Draw a card, then discard a card.
    grak->ajouterEffet(Effet("combat", 6, "aucune", "", "expend"));
    // Note: pioche conditionnelle + défausse nécessite logique spéciale
    cartes.push_back(grak);
    
    // Nature's Bounty (4 gold)
    auto naturesBounty = std::make_shared<Action>(
        "Nature's Bounty",
        FactionType::WILD,
        4
    );
    // Capacités: {Gain 4 gold} {WILD Ally}: Target opponent discards a card. {Sacrifice}: {Gain 4 combat}
    naturesBounty->ajouterEffet(Effet("or", 4, "aucune", "", "immediate"));
    naturesBounty->ajouterEffet(Effet("defausse_adversaire", 1, "ally", "WILD", "ally"));
    naturesBounty->ajouterEffet(Effet("combat", 4, "aucune", "", "sacrifice"));
    cartes.push_back(naturesBounty);
    
    // Orc Grunt (3 gold, 3 defense, Guard) x2
    for(int i = 0; i < 2; i++) {
        auto orcGrunt = std::make_shared<Champion>(
            "Orc Grunt",
            FactionType::WILD,
            3,
            3,
            true
        );
        // Capacités: {Expend}: {Gain 2 combat} {WILD Ally}: Draw a card.
        orcGrunt->ajouterEffet(Effet("combat", 2, "aucune", "", "expend"));
        orcGrunt->ajouterEffet(Effet("pioche", 1, "ally", "WILD", "ally"));
        cartes.push_back(orcGrunt);
    }
    
    // Rampage (6 gold)
    auto rampage = std::make_shared<Action>(
        "Rampage",
        FactionType::WILD,
        6
    );
    // Capacités: {Gain 6 combat} You may draw up to two cards, then discard that many cards.
    rampage->ajouterEffet(Effet("combat", 6, "aucune", "", "immediate"));
    // Note: pioche conditionnelle jusqu'à 2 + défausse nécessite logique spéciale
    cartes.push_back(rampage);
    
    // Torgen Rocksplitter (7 gold, 7 defense, Guard)
    auto torgen = std::make_shared<Champion>(
        "Torgen Rocksplitter",
        FactionType::WILD,
        7,
        7,
        true
    );
    // Capacités: {Expend}: {Gain 4 combat} Target opponent discards a card.
    torgen->ajouterEffet(Effet("combat", 4, "aucune", "", "expend"));
    torgen->ajouterEffet(Effet("defausse_adversaire", 1, "aucune", "", "expend"));
    cartes.push_back(torgen);
    
    // Spark (1 gold) x3
    for(int i = 0; i < 3; i++) {
        auto spark = std::make_shared<Action>(
            "Spark",
            FactionType::WILD,
            1
        );
        // Capacités: {Gain 3 combat} Target opponent discards a card. {WILD Ally}: {Gain 2 combat}
        spark->ajouterEffet(Effet("combat", 3, "aucune", "", "immediate"));
        spark->ajouterEffet(Effet("defausse_adversaire", 1, "aucune", "", "immediate"));
        spark->ajouterEffet(Effet("combat", 2, "ally", "WILD", "ally"));
        cartes.push_back(spark);
    }
    
    // Wolf Form (5 gold)
    auto wolfForm = std::make_shared<Action>(
        "Wolf Form",
        FactionType::WILD,
        5
    );
    // Capacités: {Gain 8 combat} Target opponent discards a card. {Sacrifice}: Target opponent discards a card.
    wolfForm->ajouterEffet(Effet("combat", 8, "aucune", "", "immediate"));
    wolfForm->ajouterEffet(Effet("defausse_adversaire", 1, "aucune", "", "immediate"));
    wolfForm->ajouterEffet(Effet("defausse_adversaire", 1, "aucune", "", "sacrifice"));
    cartes.push_back(wolfForm);
    
    // Wolf Shaman (2 gold, 4 defense) x2
    for(int i = 0; i < 2; i++) {
        auto wolfShaman = std::make_shared<Champion>(
            "Wolf Shaman",
            FactionType::WILD,
            2,
            4,
            false
        );
        // Capacités: {Expend}: {Gain 2 combat} +{1 combat} for each other {WILD} card you have in play.
        wolfShaman->ajouterEffet(Effet("combat", 2, "aucune", "", "expend"));
        // Note: +1 combat par carte WILD nécessite logique spéciale
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
            FactionType::NEUTRAL,
            2
        );
        // Capacités: {Gain 2 gold} {Sacrifice}: {Gain 3 combat}
        gem->ajouterEffet(Effet("or", 2, "aucune", "", "immediate"));
        gem->ajouterEffet(Effet("combat", 3, "aucune", "", "sacrifice"));
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
            FactionType::NEUTRAL,
            0  // Pas de coût car carte de départ
        );
        // Capacités: {Gain 1 gold}
        gold->ajouterEffet(Effet("or", 1, "aucune", "", "immediate"));
        deck.push_back(gold);
    }
    
    // 1 Ruby
    auto ruby = std::make_shared<Objet>(
        "Ruby",
        FactionType::NEUTRAL,
        0
    );
    // Capacités: {Gain 2 gold}
    ruby->ajouterEffet(Effet("or", 2, "aucune", "", "immediate"));
    deck.push_back(ruby);
    
    // 1 Dagger
    auto dagger = std::make_shared<Objet>(
        "Dagger",
        FactionType::NEUTRAL,
        0
    );
    // Capacités: {Gain 1 combat}
    dagger->ajouterEffet(Effet("combat", 1, "aucune", "", "immediate"));
    deck.push_back(dagger);
    
    // 1 Shortsword
    auto shortsword = std::make_shared<Objet>(
        "Shortsword",
        FactionType::NEUTRAL,
        0
    );
    // Capacités: {Gain 2 combat}
    shortsword->ajouterEffet(Effet("combat", 2, "aucune", "", "immediate"));
    deck.push_back(shortsword);
    
    return deck;
}

} // namespace HeroRealms
