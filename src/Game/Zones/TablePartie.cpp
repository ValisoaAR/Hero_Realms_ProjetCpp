#include "Game/Zones/TablePartie.hpp"

namespace Game::Zones {

TablePartie::TablePartie()
    : nb_gemmes(0),
      marche(),
      deck_marche("deck_marche"),
      zone_sacrifice("sacrifice") {}

void TablePartie::modifierNbGemmes(int delta) {
    nb_gemmes += delta;
    if (nb_gemmes < 0) nb_gemmes = 0;
}

} // namespace Game::Zones