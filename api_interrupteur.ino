/*
 ESP8266 MQTT - DashBouton, Bouton poussoir ou détecteur d'ouverture de porte
 Création Dominique PAUL.
 Dépot Github : https://github.com/DomoticDIY/MQTT-API_Interrupteur
 Chaine YouTube du Tuto Vidéo : https://www.youtube.com/c/DomoticDIY

 Dans IDE : Faire Croquis / inclure une bibliothéque / Gérer les bibliothèques, et ajouter :
  - ESP8266Wifi.
 Installer le gestionnaire de carte ESP8266 version 2.5.0 
 Si besoin : URL à ajouter pour le Bord manager : http://arduino.esp8266.com/stable/package_esp8266com_index.json
 
 Pour prise en compte du matériel :
 Installer si besoin le Driver USB CH340G : https://wiki.wemos.cc/downloads
 dans Outils -> Type de carte : generic ESP8266 module
  Flash mode 'QIO' (régle générale, suivant votre ESP, si cela ne fonctionne pas, tester un autre mode.
  Flash size : 1M (no SPIFFS)
  Port : Le port COM de votre ESP vu par windows dans le gestionnaire de périphériques.
*/

// Inclure les librairies.
#include <ESP8266WiFi.h>


// Déclaration des constantes, données à adapter à votre réseau.
// ------------------------------------------------------------
const char* ssid = "_MON_SSID_";                  // SSID du réseau Wifi
const char* password = "_MOT_DE_PASSE_WIFI_";     // Mot de passe du réseau Wifi.
const char* ipDomoticz = "192.168.1.26";          // Adresse IP ou DNS du serveur Domoticz.
const int portDomoticz = 8080;                    // Port de connexion à Domoticz.
// ------------------------------------------------------------
// Variables application :
int oldValeur = 0;                                // On sauvegarde le dernier état connu.
int buttonEtat = 0;                               // Variable contenant le stockage de la lecture de la valeur.
const int buttonPin = 0;                          // GPIO sur lequel est connecté le bouton.
String messageOut = "";                           // message api envoyé.
// ------------------------------------------------------------
// Variables et constantes utilisateur :
int idxDevice = 27;                               // Index du Device à actionner.
// ------------------------------------------------------------

WiFiClient client;


// SETUP
// *****
void setup() {
  Serial.begin(115200);                       // On initialise la vitesse de transmission de la console.
  pinMode(buttonPin, INPUT);                  // Initialisation du GPIO bouton en entrée.
  setup_wifi();                               // Connexion au Wifi
}

// BOUCLE DE TRAVAIL
// *****************
void loop() {
  buttonEtat = digitalRead(buttonPin);        // Lecture de l'état du bouton.
  // On vérifie si l'état a changé.
  if (buttonEtat != oldValeur) {
    // La valeur a changé, on la stock comme dernière valeur lu.
    oldValeur = buttonEtat;
    // Envoi de l'information via API Domoticz
    SendData();
  }
}


// CONNEXION WIFI
// **************
void setup_wifi() {
  // Connexion au réseau Wifi
  Serial.println();
  Serial.print("Connection au réseau : ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    // Tant que l'on est pas connecté, on boucle.
    delay(500);
    Serial.print(".");
  }
  // Initialise la séquence Random
  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connecté");
  Serial.print("Addresse IP : ");
  Serial.println(WiFi.localIP());
}


// ENVOI DES DATAS.
// ***************
void SendData () {
  // Initialisation de la valeur.
  // Suivant le résultat lu, Création du lien qui sera envoyé à l'API.
  if (buttonEtat == 0) {
    // Attention, nous sommes connecté en Pull-Up, il faut donc inverser l'ordre reçu : 0 = contact fermé.
    messageOut = "/json.htm?type=command&param=switchlight&idx=" + String(idxDevice) + "&switchcmd=On";
  } else {
    messageOut = "/json.htm?type=command&param=switchlight&idx=" + String(idxDevice) + "&switchcmd=Off";
  }
  // On log en console
  Serial.print("Message à envoyer : ");
  Serial.println(messageOut);
  
  // Envoi de la requete à Domoticz.
  if (client.connect(ipDomoticz, portDomoticz)) {    // On se connecte au serveur Domoticz
    client.println(String("GET ") + messageOut + " HTTP/1.1");
    client.println("Connection: close");             // On ferme la connexion.
    client.println();
    // Pause de 1/2 secondes
    delay(500);
    Serial.println("Message envoyé à Domoticz");
  } 
}