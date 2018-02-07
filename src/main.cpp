//
// Created by Nicolas David on 11/17/17.
//

#include <SPI.h>
#include <Ethernet.h>
#include <Adafruit_MotorShield.h>
#include <utility/w5100.h>
#include <ICMPPing.h>
#include <Servo.h>

#define MOTEUR_AVANCE 1
#define MOTEUR_RECULE 0

int pinServoHaut = 9;
int pinServoMilieu = 10;
int pinServoBas = 1;


Servo *servoHaut;
Servo *servoMilieu;
Servo *servoBas;

Servo moteursServo[3] = {*servoHaut, *servoMilieu, *servoBas};

Adafruit_MotorShield shieldMotor = Adafruit_MotorShield();

//++++++++++++paupiere+++++++++++++
Adafruit_DCMotor *moteurEngrenageBas = shieldMotor.getMotor(1);
Adafruit_DCMotor *moteurEngrenageMilieu = shieldMotor.getMotor(3);
Adafruit_DCMotor *moteurEngrenageHaut = shieldMotor.getMotor(2);

Adafruit_DCMotor moteursDC[3] = {*moteurEngrenageBas, *moteurEngrenageMilieu, *moteurEngrenageHaut};

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
bool activEngrenages[3] = {false, false, false};
bool engrenagesAvance[3] = {false, false, false};
bool activeMotorsDC[3] = {false, false, false};


int led_rouge = A0;
int led_verte = A1;

EthernetClient client;
IPAddress pingAddr(192, 168, 0, 1); // ip address to ping
unsigned long startTime = 0;

char buffer[256];
SOCKET pingSocket = 0;
ICMPPing ping(pingSocket, 1);

//MARK : Setup functions

void setupReseau() {
    Serial.println("Connexion au reseau");
    Ethernet.begin(mac, ip);
    Udp.begin(localPort);
    // print Arduino's IP
    Serial.println(Ethernet.localIP());
}

void toggleEngrenage(int moteurId, bool run) {
    if (run) {
        activEngrenages[moteurId] = true;
    } else {
        activEngrenages[moteurId] = false;
    }
}

void changeSensEngrenage(int moteurId, bool avance) {
    if (avance) {
        engrenagesAvance[moteurId] = true;
    } else {
        engrenagesAvance[moteurId] = false;
    }

}

void setupMoteursDC() {
    Serial.println("Initialisation des moteursDC");
    for (int i = 0; i < sizeof(moteursDC); i++) {
        moteursDC[i].setSpeed(255);
    }
    Serial.println("Moteurs DC activés");
}
void setupServo() {
    Serial.println("Initialisation des servo");
    for (int i = 0; i < sizeof(moteursDC); i++) {
        moteursDC[i].setSpeed(255);
    }
    Serial.println("Moteurs Servo activés");
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

//MARK: Setup

void setup() {
    Serial.begin(9600);
    Serial.println("Serial setup");
    setupMoteursDC();
    setupServo();
    setupReseau();
    shieldMotor.begin();
    //setupLed();
    //testReseau();
}

//MARK: Loop functions

void udpMotorsDC(const int receivedBytes[]) {
    if (receivedBytes[1] == 0 && receivedBytes[2] == 0) {
        Serial.println("Engrenage desactive");
        toggleEngrenage(1, false);
    }
    if (receivedBytes[1] == 1) {
        Serial.println("Engrenage avance");
        toggleEngrenage(1, true);
        changeSensEngrenage(4, true);
    }
    if (receivedBytes[2] == 1) {
        Serial.println("Engrenage recule");
        toggleEngrenage(1, true);
        changeSensEngrenage(5, false);
    }
    if (receivedBytes[3] == 0 && receivedBytes[4] == 0) {
        Serial.println("Engrenage desactive");
        toggleEngrenage(2, false);
    }
    if (receivedBytes[3] == 1) {
        Serial.println("Engrenage avance");
        toggleEngrenage(2, true);
        changeSensEngrenage(4, true);
    }
    if (receivedBytes[4] == 1) {
        Serial.println("Engrenage recule");
        toggleEngrenage(2, true);
        changeSensEngrenage(5, false);
    }
    if (receivedBytes[5] == 0 && receivedBytes[6] == 0) {
        Serial.println("Engrenage desactive");
        toggleEngrenage(3, false);
    }
    if (receivedBytes[5] == 1) {
        Serial.println("Engrenage avance");
        toggleEngrenage(3, true);
        changeSensEngrenage(4, true);
    }
    if (receivedBytes[6] == 1) {
        Serial.println("Engrenage recule");
        toggleEngrenage(3, true);
        changeSensEngrenage(5, false);
    }
}

unsigned long BtoI(int start, int numofbits, const int bits[]) {    //binary array to integer conversion
    unsigned long integer = 0;
    unsigned long mask = 1;
    for (int i = numofbits + start - 1; i >= start; i--) {
        if (bits[i]) integer |= mask;
        mask = mask << 1;
    }
    return integer;
}

void udpServo(const int receivedBytes[]) {
    for (int servoId = 0; servoId < sizeof(moteursServo) - 1; servoId++) {
        int pointer = 7;
        int speedBytes[] = {};
        for (int i = pointer; i < pointer + 9; i++) {
            int arrayPointer = i - pointer;
            speedBytes[arrayPointer] = receivedBytes[pointer];
        }
        unsigned long speed = BtoI(0, 9, speedBytes);
        //TODO : Check if long can fit in int
        moteursServo[servoId].write(speed);
    }
}

void receiveUDP() {
    int size;
    if ((size = Udp.parsePacket()) > 0) {
        if (!remote) {
            remote = Udp.remoteIP();
        }
        int receivedBytes[38];
        int byteIterator = 0;
        while (size--) {
            if (byteIterator < 38) {
                receivedBytes[byteIterator] = Udp.read();
                byteIterator++;
            }
        }
        udpMotorsDC(receivedBytes);
        udpServo(receivedBytes);
    }
}

void loopMotorDC() {
    for (int i = 0; i < sizeof(moteursDC) - 1; i++) {
        if (activeMotorsDC[i]) {
            if (engrenagesAvance[i]) {
                moteursDC[i].run(FORWARD);
            } else {
                moteursDC[i].run(BACKWARD);
            }
            //Si engrenage activé
        } else {
            moteursDC[i].run(RELEASE);
        }
    }
}

void loopMotorServo() {
    for (int i = 0; i < sizeof(moteursServo) - 1; i++) {
        if (activeMotorsDC[i]) {
            if (engrenagesAvance[i]) {
                moteursDC[i].run(FORWARD);
            } else {
                moteursDC[i].run(BACKWARD);
            }
            //Si engrenage activé
        } else {
            moteursDC[i].run(RELEASE);
        }
    }
}

//MARK: Loop Function

void loop() {
    /*unsigned long loopTime = millis() - startTime; //Calculate the time since last time the cycle was completed
    if (loopTime > 5000) //If time is over 2000 millis, set the startTime to millis so the loop time will be reset to zero
    {
        startTime = millis();
        testReseau();
    }*/

    receiveUDP();
    loopMotorDC();
    loopMotorServo();
}

//MARK : Tools // Unused

void sendPacket(byte bytes[]) {
    // send a reply to the IP address that sended us the first udp packet on the selected port in config
    if (remote) {
        Udp.beginPacket(remote, remotePort);
        Udp.write(bytes, 4);
        Udp.endPacket();
    }
}