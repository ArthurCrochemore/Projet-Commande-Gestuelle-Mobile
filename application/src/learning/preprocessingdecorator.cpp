#include <iostream>
#include "preprocessingdecorator.h"

/**
 * Classe de prétraitement des données d'entrée pour la normalisation
 * 
 * @param data : données à normaliser
 * @return : void
 */
void NormalizationPreprocessor::process(picture_vector& data) {
    for (auto& row : data) {
        for (auto& pixel : row) {
            pixel = static_cast<greyscale_value>(pixel) / (greyscale_value) 255.0; // Normalisation entre 0 et 1
        }
    }
}

