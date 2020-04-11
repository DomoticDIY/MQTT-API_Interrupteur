# MQTT-API_Interrupteur
Création d'un objet connecté, detecteur d'ouverture de porte, de fenêtre, ou interrupteur.

Dans la suite des créations d'objets connectés, nous allons voir comment créer un déclencheur vers Domoticz. L’objet connecté est présenté sous deux formes, l'une via MQTT, et l'autre via les API Domoticz.
L'intéret de cet exemple est de créer une objet de type interrupteur, ou détecteur d'ouverture de fenêtre, ou d'ouverture de porte, et remonter l'information à Domoticz, soit par le protocol MQTT, soit en utilisant les API Domoticz.

# Explications et Tuto vidéo
Il y a trois fichiers INO, deux pour la connexion via MQQT, un avec la bibliothéque Arduino JSON 5.13.3, et l'autre avec la version 6.15.0. Le troisième fichier INO concerne la connexion via API Domoticz.

Soft et bibliothèques à installer (Rappel) :
- Driver USB CH340G : https://wiki.wemos.cc/downloads
- Logiciel Arduino IDE : https://www.arduino.cc/en/Main/Software
- URL à ajouter pour le Bord manager : http://arduino.esp8266.com/stable/package_esp8266com_index.json

Installer la prise en charge des cartes ESP8266

Bibliothéques (pour version MQTT):
 - pubsubclient : https://github.com/knolleary/pubsubclient
 - ArduinoJson v5.13.3 ou v6.15.0 : https://github.com/bblanchon/ArduinoJson
Dans IDE : Faire Croquis / inclure une bibliothéque / ajouter la bibliothèque ZIP.

## Adaptation pour reconnaissance dans Domoticz (pour MQTT) :
Dans le fichier PubSubClient.h : La valeur du paramètre doit être augmentée à 512 octets. Cette définition se trouve à la ligne 26 du fichier, sinon cela ne fonctionne pas avec Domoticz

# Tuto vidéo
Vidéo explicative sur YouTube : https://youtu.be/Fjn4VlwvAZ0
