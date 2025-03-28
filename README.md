# Projet Commande Gestuelle Mobile

## Description
Cette application mobile en C++ utilise le framework Qt et la caméra du dispositif pour détecter et interpréter des gestes de la main afin de déclencher des actions spécifiques.

## Versionnage
Ce projet étant réalisé dans le cadre de deux cours distincts, il existe deux versions :  
- **Cours IFT785-51** : L'objectif principal est l'assurance qualité, avec une structure orientée objet refactorisée, l'intégration de divers design patterns et des tests. Le traitement des images se fait par capture photo. Cette version est disponible dans les branches `main` et `oriente-objet`.  
- **Cours IFT729-51** : L'objectif est une approche en temps réel, avec un code optimisé et une captation d'images en continu. Cette version est disponible dans la branche `temps-reel`.  

## **Fonctionnalités principales**
L'application repose sur l'utilisation de la caméra comme capteur pour la reconnaissance des gestes manuels et leur association à des actions définies.  
- Entraînement d'un modèle capable de reconnaître différents gestes et de les associer à des actions précises.  
- Implémentation d'un traitement en temps réel pour garantir une réactivité optimale entre les gestes capturés et les actions déclenchées.  
- Application des principes de conception orientés objet afin d'assurer une architecture robuste et évolutive du code.

## **Design Patterns**
Pour la version orientée objet du projet, j'ai choisi d'implémenter six design patterns :  
- **Factory** : Création des objets `ServiceIdentifyAction` via une classe Factory.  
- **Command** : Encapsulation des actions dans `ExecuteActionCommand`.  
- **Adapter** : Conversion des images en données numériques pour l’apprentissage et la prédiction.  
- **Observer** : Implémentation du pattern Observer dans le prétraitement des données pour faciliter l'évolution du code.  
- **Strategy** : Mise en place d’une stratégie de reconnaissance dans `IServiceIdentifyAction` pour rendre le code plus modulable.  
- **Dependency Injection** : Injection de `IServiceIdentifyAction*` dans `ActionProcessor` plutôt que d'instancier directement une action.

---

## **Projet Application (IFT785-51)**
### **Technologies utilisées**
- **Langage** : C++  
- **Framework** : Qt 5.15.18 pour Android (Installation via QtCreator : [Qt Download](https://www.qt.io/download-dev))  
- **JDK** : 17.0.13  

### **Configuration du projet**
1. **Configuration du projet sous QtCreator**  
   - Cible : `arm64-v8a`  

2. **Configuration d'Android**  
   - Ajouter la localisation du JDK dans QtCreator.  
   - Configurer le SDK Android.  
   - Télécharger et configurer OpenSSL.  

3. **Création d'un AVD (Android Virtual Device)**  
   - Ajouter un nouvel appareil Android sous architecture CPU `x86_64`.  

4. **Paramétrage du projet**  
   - Dans les "Build Steps" de QtCreator, définir `qmake ABI` pour les architectures `x86_64` et `arm64-v8a`.  

---

## **Projet Learning (IFT729-51)**
### **Technologies utilisées**
- **Langage** : C++ (Compilation via Visual Studio 17 2022)  
- **Framework** : Qt 5.15.18 (Version `msvc2019_64`) – [Installation via QtCreator](https://www.qt.io/download-dev)  
- **Bibliothèques** : PyTorch (Stable 2.6 for Windows, package LibTorch pour C++ / Java, compute platform CPU – [Téléchargement](https://pytorch.org/get-started/locally/))  

### **Configuration du projet**
1. Ouvrir une console de commande dans le dossier `debug` et exécuter la commande suivante :  
   ```sh
   mkdir build
   cd build
   cmake -DCMAKE_PREFIX_PATH="/path/to/libtorch;/path/to/Qt5.15" ..