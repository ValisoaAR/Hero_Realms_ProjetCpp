#pragma once
#include <string>

namespace Game::Utils {
    
    // Codes ANSI pour les couleurs
    namespace Couleurs {
        // Couleurs de base
        const std::string RESET = "\033[0m";
        const std::string NOIR = "\033[30m";
        const std::string ROUGE = "\033[31m";
        const std::string VERT = "\033[32m";
        const std::string JAUNE = "\033[33m";
        const std::string BLEU = "\033[34m";
        const std::string MAGENTA = "\033[35m";
        const std::string CYAN = "\033[36m";
        const std::string BLANC = "\033[37m";
        
        // Couleurs vives/claires
        const std::string ROUGE_CLAIR = "\033[91m";
        const std::string VERT_CLAIR = "\033[92m";
        const std::string JAUNE_CLAIR = "\033[93m";
        const std::string BLEU_CLAIR = "\033[94m";
        const std::string MAGENTA_CLAIR = "\033[95m";
        const std::string CYAN_CLAIR = "\033[96m";
        const std::string BLANC_CLAIR = "\033[97m";
        
        // Styles de texte
        const std::string GRAS = "\033[1m";
        const std::string SOULIGNE = "\033[4m";
        
        // Couleurs de fond
        const std::string FOND_ROUGE = "\033[41m";
        const std::string FOND_VERT = "\033[42m";
        const std::string FOND_JAUNE = "\033[43m";
        const std::string FOND_BLEU = "\033[44m";
        
        // Couleurs spécifiques pour le jeu
        const std::string JOUEUR1 = BLEU_CLAIR + GRAS;
        const std::string JOUEUR2 = ROUGE_CLAIR + GRAS;
        const std::string MARCHE = JAUNE_CLAIR;
        const std::string COMBAT = ROUGE;
        const std::string OR = JAUNE;
        const std::string SOIN = VERT_CLAIR;
        const std::string CHAMPION = MAGENTA;
        const std::string ERREUR = ROUGE_CLAIR + GRAS;
        const std::string SUCCES = VERT_CLAIR + GRAS;
        const std::string INFO = CYAN;
        const std::string TITRE = CYAN_CLAIR + GRAS;
        
        // Couleurs pour les factions
        const std::string GUILD = JAUNE_CLAIR + GRAS;      // Jaune pour Guild
        const std::string IMPERIAL = BLEU_CLAIR + GRAS;    // Bleu pour Imperial
        const std::string NECROS = MAGENTA_CLAIR + GRAS;   // Magenta pour Necros
        const std::string WILD = VERT_CLAIR + GRAS;        // Vert pour Wild
    }
    
} // namespace Game::Utils
