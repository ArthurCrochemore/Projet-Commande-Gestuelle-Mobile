# Projet Commande Gestuelle Mobile

## Description
Cette application mobile en C++ utilise le framework Qt et la caméra du dispositif pour détecter et interpréter des gestes de la main afin de déclencher des actions spécifiques.

## Fonctionnalités principales
Développement d'une application mobile utilisant la caméra comme capteur pour la reconnaissance de gestes manuels et le déclenchement d'actions spécifiques.
 - Entraîner un modèle pour reconnaître les gestes de main et les associer à des actions définies
 - Implémenter un traitement en temps réel pour assurer une réactivité optimale entre les gestes capturés et les actions déclenchées
 - Appliquer des principes de conception orientés objet pour refactoriser le code et garantir une organisation solide des classes

## Technologies utilisées
- Langage : C++
- Framework : Qt

## Design Pattern
Pour la version orienté objet de ce projet, j'ai choisi d'implémenter 6 différents design patterns :
 - Factory : Création des objets ServiceIdentifyAction via une classe Factory.
 - Command : Encapsulisation de l'action dans ExecuteActionCommand.
 - Adapter : Conversion d'image en donnée numérique pour l'apprentissage et la prédiction.
 - Observer : Implementation d'Observer dans les pré-traitements des données afin de facilement faire évoluer le code
 - Strategy : Implémentation d'une stratégie de reconnaissance dans IServiceIdentifyAction afin de facilement faire évoluer le code.
 - Dependancy injection : Injection de IServiceIdentifyAction* dans ActionProcessor plutôt que de créer une action.