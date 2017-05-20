#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Wire.h> //communication avec le shield
#include <Adafruit_MotorShield.h> // !!!! A telecharger + modif en fonction du shield utilisé !!!!

#define MOTEUR_AVANCE 1
#define MOTEUR_RECULE 0

char packetBuffer[UDP_TX_PACKET_MAX_SIZE];  //buffer to hold incoming packet,


void setupReseau() {
	Serial.println("Connexion au reseau");
	Ethernet.begin(mac,ip);
	Udp.begin(localPort);
	// print Arduino's IP
	Serial.println(Ethernet.localIP());
	Serial.println("Reception OSC activee");
}

void setup() {
	Serial.begin(9600);
	Serial.println("Serial setup");
	readRupteurs();
	setupMoteurs();
	setupPaupieres();
	setupReseau();
}

void loop() {
	readRupteurs();
	receiveUDP();
	loopPaupieres();
}

void receiveUDP() {
	int size;
	if((size = Udp.parsePacket())>0){
		if(!remote) {
			remote = Udp.remoteIP();
		}
		int receivedBytes[11];
		int byteIterator = 0;
		while(size--) {
			if(byteIterator < 11) {
				receivedBytes[byteIterator] = Udp.read();
				byteIterator++;
			}
		}
		if(receivedBytes[0] == 1) {
			changePositionPaupiereGaucheZero();
		} else if(receivedBytes[1] == 1) {
			changePositionPaupiereGaucheVinCinq();
		} else if(receivedBytes[2] == 1) {
			changePositionPaupiereGaucheCinquante();
		} else if(receivedBytes[3] == 1) {
			changePositionPaupiereGaucheSoixanteQuinze();
		} else if(receivedBytes[4] == 1) {
			changePositionPaupiereGaucheCent();
		} else if(receivedBytes[5] == 1) {
			changePositionPaupiereDroiteZero();
		} else if(receivedBytes[6] == 1) {
			changePositionPaupiereDroiteVinCinq();
		} else if(receivedBytes[7] == 1) {
			changePositionPaupiereDroiteCinquante();
		} else if(receivedBytes[8] == 1) {
			changePositionPaupiereDroiteSoixanteQuinze();
		} else if(receivedBytes[9] == 1) {
			changePositionPaupiereDroiteCent();
		} else if(receivedBytes[10] == 1) {
			asm volatile ("  jmp 0");
		}
	}
}

void sendPacket(byte bytes[]) {
	// send a reply to the IP address and port that sent us the packet we received
	if(remote) {
		Udp.beginPacket(remote, remotePort);
		Udp.write(bytes,4);
		Udp.endPacket();
	}
}

void readRupteurs() {
	stopHaut[0] = digitalRead(pinSBG);
	stopBas[0] = digitalRead(pinSHG);
	stopHaut[1] = digitalRead(pinSBD);
	stopBas[1] = digitalRead(pinSHD);
	byte packet[] = {stopHaut[0],stopBas[0],stopHaut[1],stopBas[1]};
	sendPacket(packet);


	// send a reply to the IP address and port that sent us the packet we received
	//	if(stopHaut[0] == HIGH) {
	//		byte packet[] = {1,0,0,0};
	//		sendPacket(packet);
	//	} else {
	//		byte packet[] = {0,0,0,0};
	//		sendPacket(packet);
	//	}
	//	if(stopBas[0] == HIGH) {
	//		byte packet[] = {0,1,0,0};
	//		sendPacket(packet);
	//	} else {
	//		byte packet[] = {0,0,0,0};
	//		sendPacket(packet);
	//	}
	//	if(stopHaut[1] == HIGH) {
	//		byte packet[] = {0,0,1,0};
	//		sendPacket(packet);
	//	} else {
	//		byte packet[] = {0,0,0,0};
	//		sendPacket(packet);
	//	}
	//	if(stopBas[1] == HIGH) {
	//		byte packet[] = {0,0,0,1};
	//		sendPacket(packet);
	//	} else {
	//		byte packet[] = {0,0,0,0};
	//		sendPacket(packet);
	//	}

}

void setupMoteurs() {
	Serial.println("Initialisation des moteurs");
	shieldMotor.begin();
	//ServoMoteurs
	//servoGauche.attach(pinServoGauche, 900, 2100); //mode output servo gauche
	//servoDroit.attach(pinServoDroit, 900, 2100); //mode output servo gauche


	//engrenage + paupiere lancement de la com entre le arduino et le shield motor

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

//void loopServoAngle() {
//	float tempsAvantDernierMouvementAngleOeil = millis() - lastMouvementOeil;
//	// servomoteur --------------------------------------------------------------------
//	if(tempsAvantDernierMouvementAngleOeil > 15)
//	{
//		lastMouvementOeil = millis();
//		if(angleOeilGauche < positionAngleOeilGauche) {
//			float prochainMouvementOeilGauche = positionAngleOeilGauche - 1;
//			servoGauche.write(prochainMouvementOeilGauche);
//		} else if (angleOeilGauche > positionAngleOeilGauche) {
//			float prochainMouvementOeilGauche = positionAngleOeilGauche + 1;
//			servoGauche.write(prochainMouvementOeilGauche);
//		} else if (angleOeilGauche == positionAngleOeilDroit) {
//			;
//		}
//		if(angleOeilDroit < positionAngleOeilDroit) {
//			float prochainMouvementOeilDroit = positionAngleOeilDroit - 1;
//			servoDroit.write(prochainMouvementOeilDroit);
//		} else if (angleOeilDroit > positionAngleOeilDroit) {
//			float prochainMouvementOeilDroit = positionAngleOeilDroit + 1;
//			servoDroit.write(prochainMouvementOeilDroit);
//		} else if (angleOeilGauche == positionAngleOeilDroit) {
//			;
//		}
//	}
//}

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
	Serial.println("Debut du setup paupiere");
	moteurPaupGauche->setSpeed(255);
	moteurPaupDroit->setSpeed(255);
	while(stopHaut[0] == HIGH) {
		moteurPaupGauche->run(BACKWARD);
		readRupteurs();
		delay(30);
	}
	Serial.println("STOP HAUT ACTIVE");
	timeOeilGauche[0] = millis();
	while(stopBas[0] == HIGH) {
		moteurPaupGauche->run(FORWARD);
		readRupteurs();
		delay(30);
	}
	timeOeilGauche[0] = millis() - timeOeilGauche[0];
	Serial.println("Temps aller paupiere gauche : ");
	Serial.print(timeOeilGauche[0]);
	timeOeilGaucheInverse[0] = millis();

	while(stopHaut[0] == HIGH) {
		moteurPaupGauche->run(BACKWARD);
		readRupteurs();
		delay(30);
	}
	timeOeilGaucheInverse[0] = millis() - timeOeilGaucheInverse[0];
	Serial.println("Temps retour paupiere gauche : ");
	Serial.print(timeOeilGaucheInverse[0]);
	moteurPaupGauche->run(RELEASE);
	moteurPaupGauche->setSpeed(0);

	Serial.println("Debut du setup paupiere droite");
	while(stopHaut[1] == HIGH) {
		moteurPaupDroit->run(BACKWARD);
		readRupteurs();
		delay(30);
	}
	timeOeilGauche[1] = millis();

	while(stopBas[1] == HIGH) {
		moteurPaupDroit->run(FORWARD);
		readRupteurs();
		delay(30);
	}
	timeOeilGauche[1] = millis() - timeOeilGauche[1];
	Serial.println("Temps aller paupiere droite : ");
	Serial.print(timeOeilGauche[1]);

	timeOeilGaucheInverse[1] = millis();
	while(stopHaut[1] == HIGH) {
		moteurPaupDroit->run(BACKWARD);
		readRupteurs();
		delay(30);
	}
	moteurPaupDroit->run(RELEASE);
	moteurPaupDroit->setSpeed(0);
	timeOeilGaucheInverse[1] = millis() - timeOeilGaucheInverse[1];
	Serial.println("Temps retour paupiere droite : ");
	Serial.print(timeOeilGaucheInverse[1]);

	Serial.println("Setup termine");

	setupFinished = true;
}

void loopPaupieres() {
	for (int i=0; i <= 1; i++) {
		if(setupFinished && GOMoteurGauche[i]) {
			if(!paupiereGaucheBouge[i]) {
				moteurPaupGauche->run(RELEASE);
				moteurPaupDroit->setSpeed(0);
				float pourcentageDestination = 0;
				if(lastPourcentagePositionOeilGauche[i] < pourcentagePositionPaupiereGauche[i])
				{
					paupiereGaucheAvance[i] = true;
					pourcentageDestination = pourcentagePositionPaupiereGauche[i] - lastPourcentagePositionOeilGauche[i];
				}
				else {
					paupiereGaucheAvance[i] = false;
					pourcentageDestination = lastPourcentagePositionOeilGauche[i] - pourcentagePositionPaupiereGauche[i];
				}
				if(paupiereGaucheAvance[i]){
					tempsMouvOeilGauche[i] = timeOeilGauche[i] * pourcentageDestination;
				} else {
					tempsMouvOeilGauche[i] = timeOeilGaucheInverse[i] * pourcentageDestination;
				}
				timerMouvOeilGauche[i] = millis();
				//debug = "Debut du mouvement de l'oeil  ; Temps mouv oeil gauche = ";
				//Serial.println(debug + tempsMouvOeilGauche[i]);
				//debug = "Pourcentage destination : ";
				//Serial.println(debug + pourcentageDestination);
				paupiereGaucheBouge[i] = true;
			} else {
				float tempsPasse = millis() - timerMouvOeilGauche[i];
				//float pourcentageTempsRestant = 1 - ((tempsMouvOeilGauche - tempsPasse) / tempsMouvOeilGauche);
				//float tempsRestant = tempsMouvOeilGauche - tempsPasse;
				//debug = "Pourcentage temps restant : ";
				//Serial.println(debug + pourcentageTempsRestant);
				//float positionActuelle;
				if (paupiereGaucheAvance[i]) {
					if(i == 0) {
						moteurPaupGauche->setSpeed(255);
						moteurPaupGauche->run(FORWARD);

					} else if (i == 1) {
						moteurPaupDroit->setSpeed(255);
						moteurPaupDroit->run(FORWARD);
					}
				}
				//positionActuelle = (lastPourcentagePositionOeilGauche + pourcentageTempsRestant);
				else {
					if(i == 0) {
						moteurPaupGauche->setSpeed(255);
						moteurPaupGauche->run(BACKWARD);
					} else if (i == 1) {
						moteurPaupDroit->run(BACKWARD);
						moteurPaupDroit->setSpeed(255);
					}				//positionActuelle = lastPourcentagePositionOeilGauche - pourcentageTempsRestant;
				}
				if(tempsPasse >= tempsMouvOeilGauche[i]) {
					if(i == 0) {
						moteurPaupGauche->run(RELEASE);
						moteurPaupGauche->setSpeed(0);

					} else if (i == 1) {
						moteurPaupDroit->run(RELEASE);
						moteurPaupDroit->setSpeed(0);

					}
					//Serial.println("STOP Oeil Gauche");
					//Serial.println(i);
					paupiereGaucheBouge[i] = false;
					GOMoteurGauche[i] = false;
					lastPourcentagePositionOeilGauche[i] = pourcentagePositionPaupiereGauche[i];
				}
			}
		} else if (GOMoteurGauche[i] == false) {
			//TODO : Revoir la logique d'erreur des pins
			if(stopBas[i] == LOW) {
				if(i == 0) {
					moteurPaupGauche->run(RELEASE);
					moteurPaupGauche->setSpeed(0);
				} else if (i == 1) {
					moteurPaupDroit->run(RELEASE);
					moteurPaupDroit->setSpeed(0);
				}
			} else if (stopHaut[i] == LOW) {
				if(i == 0) {
					moteurPaupGauche->run(RELEASE);
					moteurPaupGauche->setSpeed(0);
				} else if (i == 1) {
					moteurPaupDroit->run(RELEASE);
					moteurPaupDroit->setSpeed(0);

				}
			}
		}
	}
}

void mockPaupieres() {
	pourcentagePositionPaupiereGauche[0] = 0.7;
	lastPourcentagePositionOeilGauche[0] = 0.2;
	pourcentagePositionPaupiereGauche[1] = 0.7;
	lastPourcentagePositionOeilGauche[1] = 0.2;
	timeOeilGauche[0] = 5000;
	timeOeilGauche[1] = 5000;
	setupFinished = true;
	stopHaut[0] = HIGH;
	stopBas[0] = HIGH;
	stopHaut[1] = HIGH;
	stopBas[1] = HIGH;

	GOMoteurGauche[0] = true;
	GOMoteurGauche[1] = true;

}
void mockEngrenage() {
	activEngrenage = true;
	vitesseEngrenage = 1;
	sensEngrenage = MOTEUR_AVANCE;
}
void changePositionPaupiereGaucheZero(){
	if(!GOMoteurGauche[0]) {
		GOMoteurGauche[0] = true;
		Serial.println("Changement position paupiere gauche to 0");
		pourcentagePositionPaupiereGauche[0] = 0;
	}
}
void changePositionPaupiereGaucheVinCinq(){
	if(!GOMoteurGauche[0]) {
		GOMoteurGauche[0] = true;
		Serial.println("Changement position paupiere gauche to 25");
		pourcentagePositionPaupiereGauche[0] = 0.25;
	}
}
void changePositionPaupiereGaucheCinquante(){
	if(!GOMoteurGauche[0]) {
		GOMoteurGauche[0] = true;
		Serial.println("Changement position paupiere gauche to 50");
		pourcentagePositionPaupiereGauche[0] = 0.50;
	}
}
void changePositionPaupiereGaucheSoixanteQuinze(){
	if(!GOMoteurGauche[0]) {
		GOMoteurGauche[0] = true;
		Serial.println("Changement position paupiere gauche to 75");
		pourcentagePositionPaupiereGauche[0] = 0.75;
	}
}
void changePositionPaupiereGaucheCent(){
	if(!GOMoteurGauche[0]) {
		GOMoteurGauche[0] = true;
		Serial.println("Changement position paupiere gauche to 100");
		pourcentagePositionPaupiereGauche[0] = 1;
	}
}

void changePositionPaupiereDroiteZero(){
	if(!GOMoteurGauche[1]) {
		GOMoteurGauche[1] = true;
		Serial.println("Changement position paupiere droite to 0");
		pourcentagePositionPaupiereGauche[1] = 0;
	}
}
void changePositionPaupiereDroiteVinCinq(){
	if(!GOMoteurGauche[1]) {
		GOMoteurGauche[1] = true;
		Serial.println("Changement position paupiere droite to 25");
		pourcentagePositionPaupiereGauche[1] = 0.25;
	}
}
void changePositionPaupiereDroiteCinquante(){
	if(!GOMoteurGauche[1]) {
		GOMoteurGauche[1] = true;
		Serial.println("Changement position paupiere droite to 50");
		pourcentagePositionPaupiereGauche[1] = 0.50;
	}
}
void changePositionPaupiereDroiteSoixanteQuinze(){
	if(!GOMoteurGauche[1]) {
		GOMoteurGauche[1] = true;
		Serial.println("Changement position paupiere droite to 75");
		pourcentagePositionPaupiereGauche[1] = 0.75;
	}
}
void changePositionPaupiereDroiteCent(){
	if(!GOMoteurGauche[1]) {
		GOMoteurGauche[1] = true;
		Serial.println("Changement position paupiere droite to 100");
		pourcentagePositionPaupiereGauche[1] = 1;
	}
}







