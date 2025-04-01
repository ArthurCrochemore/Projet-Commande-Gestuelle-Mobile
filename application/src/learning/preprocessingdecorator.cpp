#include "preprocessingdecorator.h"

/**
 * Classe de prétraitement des données d'entrée pour la normalisation
 * 
 * @param data : données à normaliser
 * @return : void
 */
void NormalizationPreprocessor::process(std::vector<double>& data) {
    double max_val = *std::max_element(data.begin(), data.end());
    if (max_val == 0) return;  // Évite la division par zéro

    for (auto& val : data) {
        val /= max_val; // Normalisation entre 0 et 1
    }
}
