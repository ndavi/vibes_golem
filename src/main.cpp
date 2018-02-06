//
// Created by Nicolas David on 11/17/17.
//

#include <SPI.h>
#include <Ethernet.h>
#include <Adafruit_MotorShield.h>
#include <utility/w5100.h>
#include <ICMPPing.h>

#define MOTEUR_AVANCE 1
#define MOTEUR_RECULE 0

//Servo servoGauche; //décla objet servo oeil gauche
//Servo servoDroit; //décla objet servo oeil droit
int pinServoGauche = 9; //décla pin servo gauche !!!! A DEFINIR !!!!
int pinServoDroit = 10; //décla pin servo droit !!!! A DEFINIR !!!!

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
        0xDE, 0xAD, 0xBE, 0xEF, 0xFE,
        0xED}; // you can find this written on the board of some Arduino Ethernets or shields

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
int stopBas[] = {1, 1}; //signal microrupteur bas droit

int pinSHD = 7; //pin microrupteur haut droit !!!!! A DEFINIR !!!!!
int pinSBD = 8; //pin microrupteur bas droit !!!!! A DEFINIR !!!!!



// VALEURS DE CALCUL LOOP PAUPIERES

//Setup des paupieres
bool setupFinished = false;

bool paupiereGaucheBouge[] = {false, false};
bool GOMoteurGauche[] = {false, false};
bool paupiereGaucheAvance[] = {true, true};


int led_rouge = A0;
int led_verte = A1;

EthernetClient client;
IPAddress pingAddr(192, 168, 0, 1); // ip address to ping
unsigned long startTime = 0;

char buffer[256];
SOCKET pingSocket = 0;
ICMPPing ping(pingSocket, 1);


void setupReseau() {
    Serial.println("Connexion au reseau");
    Ethernet.begin(mac, ip);
    Udp.begin(localPort);
    // print Arduino's IP
    Serial.println(Ethernet.localIP());
}

void changePositionPaupiere(int numMotor, String sens) {
    if (sens == "AVANCE") {
        paupiereGaucheAvance[numMotor] = true;
    } else if (sens == "RECULE") {
        paupiereGaucheAvance[numMotor] = false;
    }
    if (!GOMoteurGauche[numMotor]) {
        GOMoteurGauche[numMotor] = true;
    }
}

void toggleEngrenage(bool run) {
    if (run) {
        activEngrenage = true;
    } else {
        activEngrenage = false;
    }
}

void changeSensEngrenage(bool avance) {
    if (avance) {
        engrenageAvance = true;
    } else {
        engrenageAvance = false;
    }

}


void readRupteurs() {
    stopHaut[0] = digitalRead(pinSBG);
    stopBas[0] = digitalRead(pinSHG);
    stopHaut[1] = digitalRead(pinSBD);
    stopBas[1] = digitalRead(pinSHD);
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

    Serial.println("Engrenage activé");

    //Initialisation moteur engrenage
}

void setupPaupieres() {
    moteurPaupGauche->setSpeed(255);
    while (stopHaut[0] == HIGH) {
        moteurPaupGauche->run(BACKWARD);
        readRupteurs();
        delay(15);

    }
    moteurPaupGauche->run(RELEASE);
    moteurPaupGauche->setSpeed(0);
    moteurPaupDroit->setSpeed(255);
    while (stopHaut[1] == HIGH) {
        moteurPaupDroit->run(BACKWARD);
        readRupteurs();
        delay(15);
    }
    moteurPaupDroit->run(RELEASE);
    moteurPaupDroit->setSpeed(0);
    Serial.println("Setup termine");

    setupFinished = true;
}

void setupLed() {


    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
}

void testReseau() {
    ICMPEchoReply echoReply = ping(pingAddr, 1);
    if (echoReply.status == SUCCESS) {
        digitalWrite(led_verte, LOW);
        digitalWrite(led_rouge, HIGH);
        sprintf(buffer,
                "Reply[%d] from: %d.%d.%d.%d: bytes=%d time=%ldms TTL=%d",
                echoReply.data.seq,
                echoReply.addr[0],
                echoReply.addr[1],
                echoReply.addr[2],
                echoReply.addr[3],
                REQ_DATASIZE,
                millis() - echoReply.data.time,
                echoReply.ttl);
        Serial.println(buffer);
    } else {
        Serial.println("Non connecté au routeur");
        digitalWrite(led_rouge, LOW);
        digitalWrite(led_verte, HIGH);
    }
}

void setup() {
    Serial.begin(9600);
    Serial.println("Serial setup");
    //readRupteurs();
    setupMoteurs();
    //setupPaupieres();
    setupReseau();
    //setupLed();
    //testReseau();
}

void receiveUDP() {
    int size;
    if ((size = Udp.parsePacket()) > 0) {
        if (!remote) {
            remote = Udp.remoteIP();
        }
        int receivedBytes[11];
        int byteIterator = 0;
        while (size--) {
            if (byteIterator < 11) {
                receivedBytes[byteIterator] = Udp.read();
                byteIterator++;
            }
        }
        if (receivedBytes[0] == 1) {
            Serial.println("Oeil gauche recule");
            changePositionPaupiere(0, "RECULE");
        } else if (receivedBytes[1] == 1) {
            Serial.println("Oeil gauche avance");
            changePositionPaupiere(0, "AVANCE");
        } else if (receivedBytes[2] == 1) {
            Serial.println("Oeil droit recule");
            changePositionPaupiere(1, "RECULE");
        } else if (receivedBytes[3] == 1) {
            Serial.println("Oeil droit avance");
            changePositionPaupiere(1, "AVANCE");
        } else if (receivedBytes[4] == 0 && receivedBytes[5] == 0) {
            Serial.println("Engrenage desactive");
            toggleEngrenage(false);
        } else if (receivedBytes[4] == 1) {
            Serial.println("Engrenage avance");
            toggleEngrenage(true);
            changeSensEngrenage(true);
        } else if (receivedBytes[5] == 1) {
            Serial.println("Engrenage recule");
            toggleEngrenage(true);
            changeSensEngrenage(false);
        } else if (receivedBytes[6] == 1) {
            Serial.println("Stop");
            GOMoteurGauche[0] = false;
            GOMoteurGauche[1] = false;
            toggleEngrenage(false);
            //asm volatile ("  jmp 0");
        }
    }
}

void loopPaupieres() {
    while (!setupFinished) {
        delay(15);
    }
    for (int i = 0; i <= 1; i++) {
        if (GOMoteurGauche[i]) {
            if (paupiereGaucheAvance[i]) {
                if (stopBas[i] == HIGH) {
                    if (i == 0) {
                        moteurPaupGauche->setSpeed(255);
                        moteurPaupGauche->run(FORWARD);

                    } else if (i == 1) {
                        moteurPaupDroit->setSpeed(255);
                        moteurPaupDroit->run(FORWARD);
                    }
                } else {
                    GOMoteurGauche[i] = false;
                }
            } else { // La paupiere recule
                if (stopHaut[i] == HIGH) {
                    if (i == 0) {
                        moteurPaupGauche->setSpeed(255);
                        moteurPaupGauche->run(BACKWARD);
                    } else if (i == 1) {
                        moteurPaupDroit->run(BACKWARD);
                        moteurPaupDroit->setSpeed(255);
                    }
                } else {
                    GOMoteurGauche[i] = false;
                }
            }
        } else if (!GOMoteurGauche[i]) {
            if (i == 0) {
                moteurPaupGauche->run(RELEASE);
                moteurPaupGauche->setSpeed(0);
            } else if (i == 1) {
                moteurPaupDroit->run(RELEASE);
                moteurPaupDroit->setSpeed(0);
            }
        }
    }
}

void loopEngrenages() {
    // engrenage ---------------------------------------------------------------------
    if (activEngrenage) {
        if (engrenageAvance) {
            moteurEngrenage->run(FORWARD);
        } else {
            moteurEngrenage->run(BACKWARD);
        }
        //Si engrenage activé
    } else {
        moteurEngrenage->run(RELEASE);// Si engrenage désactivé => stop
    }
}

void loop() {
    /*unsigned long loopTime = millis() - startTime; //Calculate the time since last time the cycle was completed
    if (loopTime > 5000) //If time is over 2000 millis, set the startTime to millis so the loop time will be reset to zero
    {
        startTime = millis();
        testReseau();
    }
    readRupteurs();*/
    receiveUDP();
    //loopPaupieres();
    loopEngrenages();
}

void sendPacket(byte bytes[]) {
    // send a reply to the IP address that sended us the first udp packet on the selected port in config
    if (remote) {
        Udp.beginPacket(remote, remotePort);
        Udp.write(bytes, 4);
        Udp.endPacket();
    }
}


unsigned long BtoI(int start, int numofbits, int bits[]) {    //binary array to integer conversion
    unsigned long integer = 0;
    unsigned long mask = 1;
    for (int i = numofbits + start - 1; i >= start; i--) {
        if (bits[i]) integer |= mask;
        mask = mask << 1;
    }
    return integer;
}

//void toggleEngrenage(){
//	if (msg.isFloat(0)){
//		int result = msg.getFloat(0);
//		if (result == 1)
//			activEngrenage = true;
//		else
//			activEngrenage = false;
//		Serial.println("Toggle engrenage : ");
//		Serial.println(activEngrenage);
//	}  else {
//		Serial.println("WARNING : Erreur lors du toggle engrenage");
//	}
//}
//void changeSensEngrenage(){
//	Serial.println("Toggle sens engrenage");
//	if (msg.isFloat(0)){
//		sensEngrenage = msg.getFloat(0);
//	} else {
//		Serial.println("WARNING : Erreur lors du toggle sens engrenage");
//	}
//}
//
//void changeVitesseEngrenage(){
//	Serial.println("Changement vitesse engrenage");
//	if (msg.isFloat(0)){
//		vitesseEngrenage = msg.getFloat(0);
//	} else {
//		Serial.println("WARNING : Erreur lors du changement de la vitesse engrenage");
//	}
//}
//
//void changeAngleOeilGauche(){
//	Serial.println("Changement angle oeil gauche");
//	if (msg.isFloat(0)){
//		angleOeilGauche = map(msg.getFloat(0),0,1,0,180);
//	} else {
//		Serial.println("WARNING : Erreur lors du changement d'angle de l'oeil gauche");
//	}
//}
//
//void changeAngleOeilDroit(){
//	Serial.println("Changement angle oeil droit");
//	if (msg.isFloat(0)){
//		angleOeilDroit = map(msg.getFloat(0),0,1,0,180);
//	} else {
//		Serial.println("WARNING : Erreur lors du changement d'angle de l'oeil droit");
//	}
//}
