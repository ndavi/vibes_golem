
//Servo servoGauche; //décla objet servo oeil gauche
//Servo servoDroit; //décla objet servo oeil droit
int pinServoGauche=9; //décla pin servo gauche !!!! A DEFINIR !!!!
int pinServoDroit=10; //décla pin servo droit !!!! A DEFINIR !!!!
String debug;

//+++++++++++engrenage+++++++++++

// !!!!!! VALABLE UNIQUEMENT SI SHIELD ADAFRUIT !!!!!!!!

Adafruit_MotorShield shieldMotor = Adafruit_MotorShield();

//++++++++++++paupiere+++++++++++++
Adafruit_DCMotor *moteurEngrenage = shieldMotor.getMotor(1);
Adafruit_DCMotor *moteurPaupGauche = shieldMotor.getMotor(3);
Adafruit_DCMotor *moteurPaupDroit = shieldMotor.getMotor(2);




// les signaux de microrupteur sont par défaut sur 1. Quand microrupteur activé = 0.
// Si panne ou arrachement de cable le microrupteur sur mettra sur 0 et le système s'arrete = meilleur sécu

unsigned int localPort = 8888;      // local port to listen for UDP packets

EthernetUDP Udp;

byte mac[] = {
		0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // you can find this written on the board of some Arduino Ethernets or shields

//the Arduino's IP
IPAddress ip(192, 168, 0, 155);
IPAddress remote;
int remotePort = 7376;


//Variable OSC
bool activEngrenage = false; //VALEUR OSC ACTIV ENGRENAGE; // Valeur OSC à recup ( bool )
bool engrenageAvance = false;

/////DECLARATION VARIABLES PARTIE PAUPIERES

//STOP MOTEURS
//On défini les variables des microrupteurs

int pinSHG = 3; // pin microrupteur haut gauche !!!!! A DEFINIR !!!!!
int stopHaut[] = {1, 1}; //signal Microrupteur haut gauche

int pinSBG = 4; //pin microrupteur bas gauche  !!!!! A DEFINIR !!!!!!
int stopBas[] = {1 ,1}; //signal microrupteur bas droit

int pinSHD = 7; //pin microrupteur haut droit !!!!! A DEFINIR !!!!!
int pinSBD = 8; //pin microrupteur bas droit !!!!! A DEFINIR !!!!!



// VALEURS DE CALCUL LOOP PAUPIERES

//Setup des paupieres
bool setupFinished = false;

bool paupiereGaucheBouge[] = {false, false};
bool GOMoteurGauche[] = {false,false};
bool paupiereGaucheAvance[] = {true, true};

