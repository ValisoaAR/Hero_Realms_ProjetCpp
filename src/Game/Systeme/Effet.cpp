#include "../../../include/Game/Systeme/Effet.hpp"

namespace Game::Systeme {

Effet::Effet(const std::string& type, int valeur,
             const std::string& condition_type,
             const std::string& condition_valeur,
             const std::string& activation)
    : type(type), valeur(valeur),
      condition_type(condition_type),
      condition_valeur(condition_valeur),
      activation(activation) {}

} // namespace Game::Systeme