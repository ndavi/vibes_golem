#include <Servo.h> //impor bibli servoMoteurs
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Wire.h> //communication avec le shield
#include <Adafruit_MotorShield.h> // !!!! A telecharger + modif en fonction du shield utilisé !!!!
#include <Time.h>
#include <OSCBundle.h>
#include <OSCBoards.h>

#define MOTEUR_AVANCE 1
#define MOTEUR_RECULE 0


void setupReseau() {
	Serial.println("Connexion au reseau");
	Ethernet.begin(mac,ip);
	Udp.begin(localPort);
	Serial.println("Reception OSC activee");
}

void setup() {
	Serial.begin(9600);
	Serial.println("Serial setup");
	setupReseau();
	//mockPaupieres();
	//mockEngrenage();
	//setupMoteurs();
	//setupPaupieres();
	//setupMoteurs();
	//setupReseau();
}

void loop() {
	//for (int t=0; t < 180; t++) {
	//	servoGauche.write(t);
	//	Serial.println(t);
	//	delay(15);
	//}
	//for (int t=180; t > 0; t--) {
	//	servoGauche.write(t);
	//	delay(15);
	//}
	getOSCMessages();
	//readRupteurs();
	//loopMoteurs();
	//loopPaupieres();
}

void readRupteurs() {
	stopHautGauche = digitalRead(pinSHG);
	stopBasGauche = digitalRead(pinSBG);
	stopHautDroite = digitalRead(pinSHD);
	stopBasDroite = digitalRead(pinSBG);
}

void getOSCMessages() {
	// wait to see if a reply is available
	OSCBundle bundleIN;
		int size;
		if((size = Udp.parsePacket())>0) {

			while(size--) {
				bundleIN.fill(Udp.read());
			}

			if(!bundleIN.hasError()) {
				//ENGRENAGE GOLEM
				bundleIN.dispatch("/eT", toggleEngrenage);
				bundleIN.dispatch("/golem/engrenage/sens", changeSensEngrenage);
				bundleIN.dispatch("/golem/engrenage/vitesse", changeVitesseEngrenage);
				//ANGLE YEUX
				bundleIN.dispatch("/golem/oeilGauche/angle", changeAngleOeilGauche);
				bundleIN.dispatch("/golem/oeilDroit/angle", changeAngleOeilDroit);

				//POSITION YEUX
				bundleIN.dispatch("/golem/oeilGauche/paupiere", changePositionPaupiereGauche);
			bundleIN.dispatch("/golem/oeilDroit/paupiere", changePositionPaupiereDroite);

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
	servoGauche.attach(pinServoGauche, 900, 2100); //mode output servo gauche
	servoDroit.attach(pinServoDroit, 900, 2100); //mode output servo gauche


	//engrenage + paupiere lancement de la com entre le arduino et le shield motor
	shieldMotor.begin();

	//mise en mode input des pins des microrupteurs
	pinMode(pinSHG, INPUT);
	pinMode(pinSBG, INPUT);
	pinMode(pinSHD, INPUT);
	pinMode(pinSBD, INPUT);


	// initialisation paupière ----------------
	//Pin rupteurs paupières
	lastMouvementOeil = millis();
	positionAngleOeilGauche = 0;
	positionAngleOeilDroit = 0;
}

void loopServoAngle() {
	float tempsAvantDernierMouvementAngleOeil = millis() - lastMouvementOeil;
	// servomoteur --------------------------------------------------------------------
	if(tempsAvantDernierMouvementAngleOeil > 15)
	{
		lastMouvementOeil = millis();
		if(angleOeilGauche < positionAngleOeilGauche) {
			float prochainMouvementOeilGauche = positionAngleOeilGauche - 1;
			servoGauche.write(prochainMouvementOeilGauche);
		} else if (angleOeilGauche > positionAngleOeilGauche) {
			float prochainMouvementOeilGauche = positionAngleOeilGauche + 1;
			servoGauche.write(prochainMouvementOeilGauche);
		} else if (angleOeilGauche == positionAngleOeilDroit) {
			;
		}
		if(angleOeilDroit < positionAngleOeilDroit) {
			float prochainMouvementOeilDroit = positionAngleOeilDroit - 1;
			servoDroit.write(prochainMouvementOeilDroit);
		} else if (angleOeilDroit > positionAngleOeilDroit) {
			float prochainMouvementOeilDroit = positionAngleOeilDroit + 1;
			servoDroit.write(prochainMouvementOeilDroit);
		} else if (angleOeilGauche == positionAngleOeilDroit) {
			;
		}
	}
}

void loopEngrenages() {
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

	moteurEngrenage->setSpeed(255);  // envoie de la vitesse au moteur

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

	timeOeilGaucheInverse = millis();
	while(stopHautGauche == HIGH) {
		moteurPaupGauche->run(BACKWARD);
	}
	timeOeilGaucheInverse = millis() - timeOeilGaucheInverse;

	while(stopHautDroite == HIGH) {
		moteurPaupDroit->run(BACKWARD);
	}
	timeOeilDroit = millis();
	while(stopBasDroite == HIGH) {
		moteurPaupDroit->run(FORWARD);
	}
	timeOeilDroit = millis() - timeOeilDroit;

	timeOeilDroitInverse = millis();
	while(stopHautDroite == HIGH) {
		moteurPaupDroit->run(BACKWARD);
	}
	timeOeilDroitInverse = millis() - timeOeilDroitInverse;

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
			debug = "Pourcentage position pop gauche = ";
			Serial.println(debug + pourcentageDestination);
			tempsMouvOeilGauche = timeOeilGauche * pourcentageDestination;
			timerMouvOeilGauche = millis();
			debug = "Debut du mouvement de l'oeil gauche ; Temps mouv oeil gauche = ";
			Serial.println(debug + tempsMouvOeilGauche);
			debug = "Pourcentage destination : ";
			Serial.println(debug + pourcentageDestination);
			paupiereGaucheBouge = true;
		} else {
			float tempsPasse = millis() - timerMouvOeilGauche;
			//float pourcentageTempsRestant = 1 - ((tempsMouvOeilGauche - tempsPasse) / tempsMouvOeilGauche);
			//float tempsRestant = tempsMouvOeilGauche - tempsPasse;
			//debug = "Pourcentage temps restant : ";
			//Serial.println(debug + pourcentageTempsRestant);
			//float positionActuelle;
			if (paupiereGaucheAvance) {
				moteurPaupGauche->run(FORWARD);
				//positionActuelle = (lastPourcentagePositionOeilGauche + pourcentageTempsRestant);
			}
			else {
				moteurPaupGauche->run(BACKWARD);
				//positionActuelle = lastPourcentagePositionOeilGauche - pourcentageTempsRestant;
			}
			Serial.println(tempsPasse);
			if(tempsPasse >= tempsMouvOeilGauche) {
				//moteurPaupGauche->run(RELEASE);
				Serial.println("STOP Oeil Gauche");
				paupiereGaucheBouge = false;
				GOMoteurGauche = false;
				lastPourcentagePositionOeilGauche = pourcentagePositionPaupiereGauche;
			}
		}
	}
}
void mockPaupieres() {
	pourcentagePositionPaupiereGauche = 0.7;
	lastPourcentagePositionOeilGauche = 0.2;
	timeOeilGauche = 5000;
	setupFinished = true;
	stopHautGauche = HIGH;
	stopBasGauche = HIGH;
	GOMoteurGauche = true;
}
void mockEngrenage() {
	activEngrenage = true;
	vitesseEngrenage = 1;
	sensEngrenage = MOTEUR_AVANCE;
}







