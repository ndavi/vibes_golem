#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>

#define MOTEUR_AVANCE 1
#define MOTEUR_RECULE 0


void setupReseau() {
	Serial.println("Connexion au reseau");
	Ethernet.begin(mac,ip);
	Udp.begin(localPort);
	// print Arduino's IP
	Serial.println(Ethernet.localIP());
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
	loopEngrenages();
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
			Serial.println("Oeil gauche recule");
			changePositionPaupiere(0, "RECULE");
		} else if(receivedBytes[1] == 1) {
			Serial.println("Oeil gauche avance");
			changePositionPaupiere(0, "AVANCE");
		} else if(receivedBytes[2] == 1) {
			Serial.println("Oeil droit recule");
			changePositionPaupiere(1, "RECULE");
		} else if(receivedBytes[3] == 1) {
			Serial.println("Oeil droit avance");
			changePositionPaupiere(1, "AVANCE");
		} else if (receivedBytes[4] == 0 && receivedBytes[5] == 0) {
			Serial.println("Engrenage desactive");
			toggleEngrenage(false);
		}
		else if(receivedBytes[4] == 1) {
			Serial.println("Engrenage avance");
			toggleEngrenage(true);
			changeSensEngrenage(true);
		}  else if(receivedBytes[5] == 1) {
			Serial.println("Engrenage recule");
			toggleEngrenage(true);
			changeSensEngrenage(false);
		}
		else if(receivedBytes[6] == 1) {
			Serial.println("Stop");
			GOMoteurGauche[0] = false;
			GOMoteurGauche[1] = false;
			toggleEngrenage(false);
			//asm volatile ("  jmp 0");
		}
	}
}

void sendPacket(byte bytes[]) {
	// send a reply to the IP address that sended us the first udp packet on the selected port in config
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
	Serial.println(String(stopHaut[0]) + String(stopHaut[1]));
	Serial.println(String(stopBas[0]) + String(stopBas[1]));
	//byte packet[] = {stopHaut[0],stopBas[0],stopHaut[1],stopBas[1]};
	//sendPacket(packet);

}

void setupMoteurs() {
	Serial.println("Initialisation des moteurs");
	shieldMotor.begin();
	moteurEngrenage->setSpeed(255);
	//ServoMoteurs
	//servoGauche.attach(pinServoGauche, 900, 2100); //mode output servo gauche
	//servoDroit.attach(pinServoDroit, 900, 2100); //mode output servo gauche


	//engrenage + paupiere lancement de la com entre le arduino et le shield motor

	//mise en mode input des pins des microrupteurs
	pinMode(pinSHG, INPUT);
	pinMode(pinSBG, INPUT);
	pinMode(pinSHD, INPUT);
	pinMode(pinSBD, INPUT);

	//Initialisation moteur engrenage
}

void loopEngrenages() {
	// engrenage ---------------------------------------------------------------------
	if (activEngrenage) {
		if(engrenageAvance) {
			moteurPaupDroit->run(FORWARD);
		} else {
			moteurPaupDroit->run(BACKWARD);
		}
		//Si engrenage activé
	}
	else {
		moteurPaupDroit->run(RELEASE);// Si engrenage désactivé => stop
	}
}


void setupPaupieres() {
	Serial.println("Debut du setup paupiere gauche");
	moteurPaupGauche->setSpeed(255);
	while(stopHaut[0] == HIGH) {
		Serial.println(stopHaut[0]);
		Serial.println("Go paupiere gauche");
		moteurPaupGauche->run(BACKWARD);
		readRupteurs();
		delay(15);
	}
	moteurPaupGauche->run(RELEASE);
	moteurPaupGauche->setSpeed(0);
	Serial.println("Debut du setup paupiere droite");
	moteurPaupDroit->setSpeed(255);
	while(stopHaut[1] == HIGH) {
		Serial.println("Go paupiere droite");
		moteurPaupDroit->run(BACKWARD);
		readRupteurs();
		delay(15);
	}
	moteurPaupDroit->run(RELEASE);
	moteurPaupDroit->setSpeed(0);
	Serial.println("Setup termine");

	setupFinished = true;
}

void loopPaupieres() {
	while(!setupFinished) {
		delay(15);
	}
	for (int i=0; i <= 1; i++) {
		if(GOMoteurGauche[i]) {
			if (paupiereGaucheAvance[i]) {
				if(stopBas[i] == HIGH) {
					if(i == 0) {
						moteurPaupGauche->setSpeed(255);
						moteurPaupGauche->run(FORWARD);

					} else if (i == 1) {
						moteurPaupDroit->setSpeed(255);
						moteurPaupDroit->run(FORWARD);
					}
				} else {
					GOMoteurGauche[i] = false;
				}
			}
			else { // La paupiere recule
				if(stopHaut[i] == HIGH) {
					if(i == 0) {
						moteurPaupGauche->setSpeed(255);
						moteurPaupGauche->run(BACKWARD);
					} else if (i == 1) {
						moteurPaupDroit->run(BACKWARD);
						moteurPaupDroit->setSpeed(255);
					}
				}  else {
					GOMoteurGauche[i] = false;
				}
			}
		} else if (!GOMoteurGauche[i]) {
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

unsigned long BtoI(int start, int numofbits, int bits[]){    //binary array to integer conversion
	unsigned long integer=0;
	unsigned long mask=1;
	for (int i = numofbits+start-1; i >= start; i--) {
		if (bits[i]) integer |= mask;
		mask = mask << 1;
	}
	return integer;
}







