
Servo servoGauche; //décla objet servo oeil gauche
Servo servoDroit; //décla objet servo oeil droit

int pinServoGauche=9; //décla pin servo gauche !!!! A DEFINIR !!!!
int pinServoDroit=10; //décla pin servo droit !!!! A DEFINIR !!!!


//+++++++++++engrenage+++++++++++
// !!!!!! VALABLE UNIQUEMENT SI SHIELD ADAFRUIT !!!!!!!!

Adafruit_MotorShield shieldMotor = Adafruit_MotorShield();
Adafruit_DCMotor *moteurEngrenage = shieldMotor.getMotor(1);

//++++++++++++paupiere+++++++++++++

Adafruit_DCMotor *moteurPaupGauche = shieldMotor.getMotor(2);
Adafruit_DCMotor *moteurPaupDroit = shieldMotor.getMotor(3);




// les signaux de microrupteur sont par défaut sur 1. Quand microrupteur activé = 0.
// Si panne ou arrachement de cable le microrupteur sur mettra sur 0 et le système s'arrete = meilleur sécu

unsigned int localPort = 8888;      // local port to listen for UDP packets

EthernetUDP Udp;
OscUDP etherOSC;

byte mac[] = {
		0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // you can find this written on the board of some Arduino Ethernets or shields

//the Arduino's IP
IPAddress ip(192, 168, 0, 155);


//Variable OSC
bool activEngrenage = false; //VALEUR OSC ACTIV ENGRENAGE; // Valeur OSC à recup ( int )
int sensEngrenage = 0; //Valeur OSC SENS ENGRENAGE, // Valeur OSC à recup ( int )
float vitesseEngrenage = 0; //Valeur OSC VITTESSE ENGRENAGE //Valeur OSC à recup ( float )

float angleOeilGauche = 0; //VALEUR OSC A RECUP; //Valeur OSC Angle oeil gauche en float
float positionAngleOeilGauche = 0;
float angleOeilDroit = 0; //Valeur OSC A RECUP; //Valeur OSC angle oeil droit en float
float positionAngleOeilDroit = 0;
float lastMouvementOeil = 0;

/////DECLARATION VARIABLES PARTIE PAUPIERES

//STOP MOTEURS
//On défini les variables des microrupteurs

int pinSHG = 3; // pin microrupteur haut gauche !!!!! A DEFINIR !!!!!
int stopHautGauche = 1; //signal Microrupteur haut gauche

int pinSBG = 4; //pin microrupteur bas gauche  !!!!! A DEFINIR !!!!!!
int stopBasGauche = 1; //signal microrupteur bas droit

int pinSHD = 7; //pin microrupteur haut droit !!!!! A DEFINIR !!!!!
int stopHautDroite = 1; //signal microrupteur haut droit

int pinSBD = 8; //pin microrupteur bas droit !!!!! A DEFINIR !!!!!
int stopBasDroite = 1; //signal microrupteur bas droit



// VALEURS DE CALCUL LOOP PAUPIERES

//Setup des paupieres
bool setupFinished = false;

//Temps que mettent les moteurs à faire un aller
unsigned long timeOeilGauche;
unsigned long timeOeilGaucheInverse;
unsigned long timeOeilDroit;
unsigned long timeOeilDroitInverse;


float pourcentagePositionPaupiereGauche = 0;
float lastPourcentagePositionOeilGauche = 0;
bool paupiereGaucheBouge = false;
unsigned long tempsMouvOeilGauche = 0;
unsigned long timerMouvOeilGauche = 0;
bool GOMoteurGauche = false;
bool paupiereGaucheAvance = true;

float pourcentagePositionPaupiereDroite = 0;
float lastPourcentagePositionOeilDroit = 0;
bool paupiereDroiteBouge = false;

