#include <Servo.h> //impor bibli servoMoteurs
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <OSCBundle.h>
#include <OSCBoards.h>
#include <Wire.h> //communication avec le shield
#include <Adafruit_MotorShield.h> // !!!! A telecharger + modif en fonction du shield utilisé !!!!
#include<Time.h>

#define MOTEUR_AVANCE 1
#define MOTEUR_RECULE 0


void setupReseau() {
	Serial.println("Connexion au reseau");
	Ethernet.begin(mac,ip);
}

void setup() {
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}
	Serial.println("Serial setup");
	mockPaupieres();
	//setupMoteurs();
	//setupReseau();
}

void loop() {
	//getOSCMessages();
	//loopMoteurs();
	loopPaupieres();
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
			//ENGRENAGE GOLEM
			bundleIN.dispatch("/golem/toggleEngrenage", toggleEngrenage);
			bundleIN.dispatch("/golem/sensEngrenage", toggleEngrenage);
			bundleIN.dispatch("/golem/vitesseEngrenage", toggleEngrenage);
			//ANGLE YEUX
			bundleIN.dispatch("/golem/angleOeilGauche", changeAngleOeilGauche);
			bundleIN.dispatch("/golem/angleOeilDroit", changeAngleOeilDroit);

			//POSITION YEUX
			bundleIN.dispatch("/golem/positionPaupiereGauche", changePositionPaupiereGauche);
			bundleIN.dispatch("/golem/positionPaupiereDroite", changePositionPaupiereDroite);

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
	//Pin rupteurs paupières
	pinMode(stopHautGauche, INPUT);
	pinMode(stopHautDroite, INPUT);
	pinMode(stopBasDroite, INPUT);
	pinMode(stopBasGauche, INPUT);

	setupPaupieres();
}

void loopMoteurs() {
	// engrenage ---------------------------------------------------------------------
	if (activEngrenage) {        //Si engrenage activé
		if (sensEngrenage == MOTEUR_AVANCE)      // Si sens engrenage = 0 => sens arrière
			moteurEngrenage->run(FORWARD);
		else if (sensEngrenage == MOTEUR_RECULE)                          // sinon sens avant
			moteurEngrenage->run(BACKWARD);
		else
			moteurEngrenage->run(RELEASE);
	}
	else {                             // Si engrenage désactivé => stop
		moteurEngrenage->run(RELEASE);
	}

	int speedEngrenage = map(vitesseEngrenage,0,1,0,255); //map de la vitesse d'une valeur float à une valeur int entre O et 255
	moteurEngrenage->setSpeed(speedEngrenage);  // envoie de la vitesse au moteur

	// servomoteur --------------------------------------------------------------------

	int aG=map(angleOeilGauche,0,1,0,179); //map de la valeur Angle gauche qui est en float => valeur int angle
	int aD=map(angleOeilDroit,0,1,0,179);   // """"

	servoGauche.write(aG); // Envoie de l'angle aux servos moteurs
	servoDroit.write(aD);
}

void setupPaupieres() {
	while(stopHautGauche == HIGH) {
		moteurPaupGauche->run(BACKWARD);
	}
	timeOeilGauche = millis();
	while(stopBasGauche == HIGH) {
		moteurPaupGauche->run(FORWARD);
	}
	timeOeilGauche = millis() - timeOeilGauche;

	while(stopHautDroite == HIGH) {
		moteurPaupDroit->run(BACKWARD);
	}
	timeOeilDroit = millis();
	while(stopBasDroite == HIGH) {
		moteurPaupDroit->run(FORWARD);
	}
	timeOeilDroit = millis() - timeOeilDroit;
	setupFinished = true;
}

void loopPaupieres() {
	String debug = "";
	if(setupFinished && stopHautGauche != LOW && stopBasGauche != LOW && GOMoteurGauche) {
		if(!paupiereGaucheBouge) {
			float pourcentageDestination = 0;
			if(lastPourcentagePositionOeilGauche < pourcentagePositionPaupiereGauche)
			{
				paupiereGaucheAvance = true;
				Serial.println("Le moteur avance");
				pourcentageDestination = pourcentagePositionPaupiereGauche - lastPourcentagePositionOeilGauche;
			}
			else {
				paupiereGaucheAvance = false;
				Serial.println("Le moteur recule");
				pourcentageDestination = lastPourcentagePositionOeilGauche - pourcentagePositionPaupiereGauche;
			}
			tempsMouvOeilGauche = timeOeilGauche * pourcentagePositionPaupiereGauche;
			timerMouvOeilGauche = millis();
			debug = "Debut du mouvement de l'oeil gauche ; Temps mouv oeil gauche = ";
			Serial.println(debug + tempsMouvOeilGauche);
			debug = "Pourcentage destination : ";
			Serial.println(debug + pourcentageDestination);
			paupiereGaucheBouge = true;
		}
		if (paupiereGaucheAvance)
			;
		//moteurPaupGauche->run(FORWARD);
		else
			;
		//moteurPaupGauche->run(BACKWARD);
		float tempsPasse = millis() - timerMouvOeilGauche;
		if(tempsPasse >= tempsMouvOeilGauche) {
			//moteurPaupGauche->run(RELEASE);
			Serial.println("STOP Oeil Gauche");
			paupiereGaucheBouge = false;
			GOMoteurGauche = false;
			lastPourcentagePositionOeilGauche = pourcentagePositionPaupiereGauche;
		}
	}
}










