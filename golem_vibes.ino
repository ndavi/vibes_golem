#include <Servo.h> //impor bibli servoMoteurs
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <OSCBundle.h>
#include <OSCBoards.h>
#include <Wire.h> //communication avec le shield
#include <Adafruit_MotorShield.h> // !!!! A telecharger + modif en fonction du shield utilisé !!!!


Servo servoGauche; //décla objet servo oeil gauche
Servo servoDroit; //décla objet servo oeil droit

int pinServoGauche=0; //décla pin servo gauche !!!! A DEFINIR !!!!
int pinServoDroit=0; //décla pin servo droit !!!! A DEFINIR !!!!

//+++++++++++engrenage+++++++++++
// !!!!!! VALABLE UNIQUEMENT SI SHIELD ADAFRUIT !!!!!!!!

Adafruit_MotorShield shieldMotor = Adafruit_MotorShield();
Adafruit_DCMotor *moteurEngrenage = shieldMotor.getMotor(1);

//++++++++++++paupiere+++++++++++++

Adafruit_DCMotor *moteurPaupGauche = shieldMotor.getMotor(2);
Adafruit_DCMotor *moteurPaupDroit = shieldMotor.getMotor(3);

//On défini les variables des microrupteurs

int pinSHG = 0; // pin microrupteur haut gauche !!!!! A DEFINIR !!!!!
int stopHautGauche = 1; //signal Microrupteur haut gauche

int pinSBG = 0; //pin microrupteur bas gauche  !!!!! A DEFINIR !!!!!!
int stopBasGauche = 1; //signal microrupteur bas droit

int pinSHD = 0; //pin microrupteur haut droit !!!!! A DEFINIR !!!!!
int stopHautDroit = 1; //signal microrupteur haut droit

int pinSBD = 0; //pin microrupteur bas droit !!!!! A DEFINIR !!!!!
int stopBasDroit = 1; //signal microrupteur bas droit

// les signaux de microrupteur sont par défaut sur 1. Quand microrupteur activé = 0.
// Si panne ou arrachement de cable le microrupteur sur mettra sur 0 et le système s'arrete = meilleur sécu

unsigned int localPort = 8888;      // local port to listen for UDP packets

EthernetUDP Udp;
byte mac[] = {
		0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // you can find this written on the board of some Arduino Ethernets or shields

//the Arduino's IP
IPAddress ip(192, 168, 0, 155);

//Variable OSC
int activEngrenage = 0; //VALEUR OSC ACTIV ENGRENAGE; // Valeur OSC à recup ( int )
int sensEngrenage = 0; //Valeur OSC SENS ENGRENAGE, // Valeur OSC à recup ( int )
float vitesseEngrenage = 0; //Valeur OSC VITTESSE ENGRENAGE //Valeur OSC à recup ( float )

float angleGauche = 0; //VALEUR OSC A RECUP; //Valeur OSC Angle oeil gauche en float
float angleDroit = 0; //Valeur OSC A RECUP; //Valeur OSC angle oeil droit en float

void routeTone(OSCMessage &msg, int addrOffset ){
	Serial.println("Tone received");

}

void setupReseau() {
	Serial.println("Connexion au reseau");
	Ethernet.begin(mac,ip);
}

void setup() {
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}
	setupMoteurs();
	setupReseau();
}

void loop() {
	getOSCMessages();
	loopMoteurs();
}

void getOSCMessages() {
	// wait to see if a reply is available
	OSCBundle bundleIN;
	int size;
	if((size = Udp.parsePacket())>0)	{

		while(size--) {
			bundleIN.fill(Udp.read());
		}

		if(!bundleIN.hasError()) {
			OSCMessage osc = bundleIN.getOSCMessage(0);
			Serial.println("Received OSC" + osc.getType(0));
			bundleIN.route("/tone", routeTone);
		}
		else {
			OSCErrorCode errorCode = bundleIN.getError();
			Serial.println(errorCode);
		}
	}
}

void setupMoteurs() {
	Serial.println("Initialisation des moteurs");
	//ServoMoteurs
	servoGauche.attach(pinServoGauche); //mode output servo gauche
	servoDroit.attach(pinServoDroit); //mode output servo droit

	//engrenage + paupiere lancement de la com entre le arduino et le shield motor
	shieldMotor.begin();

	//mise en mode input des pins des microrupteurs
	pinMode(pinSHG, INPUT);
	pinMode(pinSBG, INPUT);
	pinMode(pinSHD, INPUT);
	pinMode(pinSBD, INPUT);


	// initialisation paupière ----------------

	// A ecrire
}

void loopMoteurs() {
	// engrenage ---------------------------------------------------------------------


	if (activEngrenage == 1){        //Si engrenage activé
		if ("Sens Engrenage" == 0)      // Si sens engrenage = 0 => sens arrière
			moteurEngrenage->run(BACKWARD);
		else                              // sinon sens avant
			moteurEngrenage->run(FORWARD);
	}
	else {                             // Si engrenage désactivé => stop
		moteurEngrenage->run(RELEASE);
	}

	int speedEngrenage = map(vitesseEngrenage,0,1,0,255); //map de la vitesse d'une valeur float à une valeur int entre O et 255
	moteurEngrenage->setSpeed(speedEngrenage);  // envoie de la vitesse au moteur

	// servomoteur --------------------------------------------------------------------

	int aG=map(angleGauche,0,1,0,179); //map de la valeur Angle gauche qui est en float => valeur int angle
	int aD=map(angleDroit,0,1,0,179);   // """"

	servoGauche.write(aG); // Envoie de l'angle aux servos moteurs
	servoDroit.write(aD);

	//Paupière ------------------------------------------------------------------------
}










