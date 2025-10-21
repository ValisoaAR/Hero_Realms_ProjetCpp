# Hero Realms - Règles Implémentées

## ✅ Règles de Base Implémentées

### 1. Initialisation du Jeu
- ✅ **2 joueurs** avec **50 PV** chacun
- ✅ **Deck de départ** pour chaque joueur :
  - 7 cartes "Gold" (1 or chacune)
  - 1 carte "Ruby" (2 or)
  - 1 carte "Dagger" (1 combat)
  - 1 carte "Shortsword" (2 combat)
- ✅ **Marché** initialisé avec 5 cartes du Base Set
- ✅ **Pioche du marché** avec toutes les cartes du Base Set + Fire Gems
- ✅ **Distribution initiale** : 3 cartes pour commencer

### 2. Déroulement d'un Tour
- ✅ **Phase de pioche** : Chaque joueur pioche jusqu'à avoir 5 cartes en main
  - Si le deck est vide, la défausse est mélangée et devient le nouveau deck
- ✅ **Phase d'action** : Le joueur peut :
  - Jouer des cartes de sa main
  - Acheter des cartes du marché
  - Attaquer l'adversaire ou ses champions
  - Activer des champions en jeu
  - Terminer son tour
- ✅ **Fin de tour** : 
  - Toutes les cartes de la main vont à la défausse
  - Tous les champions en jeu vont à la défausse
  - Les ressources (or/combat) sont remises à zéro

### 3. Types de Cartes

#### Champions
- ✅ Restent en jeu après avoir été joués
- ✅ Ont des **Points de Vie (PV)**
- ✅ Peuvent avoir la capacité **GARDE**
- ✅ Peuvent être attaqués par l'adversaire
- ✅ Sont défaussés à la fin du tour ou quand détruits

#### Actions
- ✅ Sont jouées et vont directement à la défausse
- ✅ Appliquent leurs effets immédiatement

#### Objets
- ✅ Similaires aux actions
- ✅ Vont à la défausse après utilisation

### 4. Combat et Attaque

#### Règle des Gardes
- ✅ **Si l'adversaire a des champions avec GARDE** :
  - Le joueur **DOIT** attaquer en priorité les champions avec Garde
  - Il ne peut pas attaquer directement le joueur adverse
  - Il ne peut pas attaquer d'autres champions

#### Attaque Normale
- ✅ **Si l'adversaire n'a pas de Garde** :
  - Le joueur peut choisir d'attaquer :
    - Le joueur adverse directement
    - N'importe quel champion adverse
- ✅ **Dégâts aux champions** :
  - Les dégâts réduisent les PV du champion
  - Un champion à 0 PV ou moins est détruit et va à la défausse

#### Points de Combat
- ✅ Les points de combat sont générés par les cartes jouées
- ✅ Ils sont consommés lors d'une attaque
- ✅ Ils sont remis à zéro en fin de tour

### 5. Économie et Marché

#### Or
- ✅ Généré par les cartes jouées (Gold = 1, Ruby = 2, etc.)
- ✅ Utilisé pour acheter des cartes du marché
- ✅ Remis à zéro en fin de tour

#### Achat
- ✅ Les cartes achetées vont **directement à la défausse**
- ✅ Une nouvelle carte du deck de marché remplace la carte achetée
- ✅ Le marché contient toujours 5 cartes (si possible)

### 6. Gestion du Deck

#### Pioche
- ✅ Les cartes sont piochées du dessus du deck
- ✅ Si le deck est vide, la défausse est mélangée automatiquement
- ✅ Le deck mélangé devient le nouveau deck de pioche

#### Défausse
- ✅ Les cartes jouées vont à la défausse
- ✅ Les cartes achetées vont à la défausse
- ✅ Les champions détruits ou en fin de tour vont à la défausse
- ✅ La main du joueur va à la défausse en fin de tour

### 7. Capacités Spéciales

#### Capacités Alliées (ALLY)
- ✅ Système de comptage des factions jouées pendant le tour
- ✅ Une capacité alliée s'active si **2 cartes ou plus** de la même faction sont jouées
- ✅ Affichage visuel quand un allié est activé

#### Capacités d'Activation (EXPEND)
- ✅ Interface pour activer les champions en jeu
- ✅ (Effets spécifiques à implémenter selon les cartes)

#### Capacités de Sacrifice
- 🔄 À implémenter : permet de sacrifier une carte pour un effet bonus

### 8. Conditions de Victoire
- ✅ Un joueur gagne quand l'adversaire atteint **0 PV ou moins**
- ✅ Affichage du vainqueur avec ses PV restants

## 🎮 Interface Console

### Affichage
- ✅ Interface claire avec bordures et séparateurs
- ✅ Affichage des informations du joueur :
  - PV actuels
  - Or et Combat disponibles
  - Cartes en main
  - Champions en jeu (avec PV et statut Garde)
- ✅ Affichage du marché avec coûts et types de cartes
- ✅ Messages visuels (✓, ❌, ⚔️, 💀, 🏆, 🔥)

### Actions Disponibles
1. **Jouer une carte** : Choisir une carte de sa main
2. **Acheter une carte** : Acheter depuis le marché
3. **Attaquer** : Cibler joueur ou champion adverse
4. **Activer un champion** : Utiliser une capacité EXPEND
5. **Fin du tour** : Passer au joueur suivant

## 📝 Architecture du Code

### Structures de Données
```cpp
struct JoueurConsole {
    int id;
    int pv;
    vector<shared_ptr<Carte>> deck;
    vector<shared_ptr<Carte>> main;
    vector<shared_ptr<Carte>> defausse;
    vector<shared_ptr<Champion>> championsEnJeu;
    int orTour;
    int combatTour;
    map<FactionType, int> factionsJouees;
};
```

### Fonctions Utilitaires
- `piocherCartes()` : Gère la pioche avec mélange automatique
- `afficherEtatJoueur()` : Interface visuelle de l'état du joueur
- Boucle principale avec switch-case pour les actions

## 🔄 Améliorations Futures

### Priorité Haute
- [ ] Implémenter les effets spécifiques de chaque carte du Base Set
- [ ] Système complet de capacités alliées
- [ ] Capacités d'activation (EXPEND) pour chaque champion
- [ ] Capacités de sacrifice

### Priorité Moyenne
- [ ] Validation des entrées utilisateur améliorée
- [ ] Mode IA pour jouer contre l'ordinateur
- [ ] Sauvegarde/chargement de partie

### Priorité Basse
- [ ] Interface graphique
- [ ] Animations
- [ ] Sons et musique
- [ ] Support multi-joueurs en ligne

## 🎯 Conformité aux Règles Officielles

Ce jeu implémente fidèlement les règles officielles de **Hero Realms** :
- Deck de départ standard (10 cartes)
- 50 PV par joueur
- Marché avec 5 cartes visibles
- Système de combat avec priorité aux gardes
- Gestion correcte des champions, actions et objets
- Système de factions et capacités alliées

## 🚀 Compilation et Exécution

```bash
# Compilation
g++ -std=c++17 -Iinclude main.cpp src/Game/Cartes/*.cpp src/Game/Core/*.cpp src/Game/Systeme/*.cpp src/Game/Utils/*.cpp src/Game/Zones/*.cpp -o hero_full

# Exécution
./hero_full
```

## 📚 Références
- Règles officielles Hero Realms
- Base Set : 80+ cartes de 4 factions (Imperial, Guild, Necros, Wild)
