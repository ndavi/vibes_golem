void toggleEngrenage(OSCMessage &msg){
	if (msg.isFloat(0)){
		int result = msg.getFloat(0);
		if (result == 1)
			activEngrenage = true;
		else
			activEngrenage = false;
		Serial.println("Toggle engrenage : ");
		Serial.println(activEngrenage);
	}  else {
		Serial.println("WARNING : Erreur lors du toggle engrenage");
	}
}
void changeSensEngrenage(OSCMessage &msg){
	Serial.println("Toggle sens engrenage");
	if (msg.isFloat(0)){
		sensEngrenage = msg.getFloat(0);
	} else {
		Serial.println("WARNING : Erreur lors du toggle sens engrenage");
	}
}

void changeVitesseEngrenage(OSCMessage &msg){
	Serial.println("Changement vitesse engrenage");
	if (msg.isFloat(0)){
		vitesseEngrenage = msg.getFloat(0);
	} else {
		Serial.println("WARNING : Erreur lors du changement de la vitesse engrenage");
	}
}

void changeAngleOeilGauche(OSCMessage &msg){
	Serial.println("Changement angle oeil gauche");
	if (msg.isFloat(0)){
		angleOeilGauche = map(msg.getFloat(0),0,1,0,180);
	} else {
		Serial.println("WARNING : Erreur lors du changement d'angle de l'oeil gauche");
	}
}

void changeAngleOeilDroit(OSCMessage &msg){
	Serial.println("Changement angle oeil droit");
	if (msg.isFloat(0)){
		angleOeilDroit = map(msg.getFloat(0),0,1,0,180);
	} else {
		Serial.println("WARNING : Erreur lors du changement d'angle de l'oeil droit");
	}
}

void changePositionPaupiereGauche0(OSCMessage &msg){
	Serial.println("Changement position paupiere gauche to 0");
	pourcentagePositionPaupiereGauche = 0;
}
void changePositionPaupiereGauche25(OSCMessage &msg){
	Serial.println("Changement position paupiere gauche to 25");
	pourcentagePositionPaupiereGauche = 0.25;
}void changePositionPaupiereGauche50(OSCMessage &msg){
	Serial.println("Changement position paupiere gauche to 50");
	pourcentagePositionPaupiereGauche = 0.50;
}void changePositionPaupiereGauche75(OSCMessage &msg){
	Serial.println("Changement position paupiere gauche to 75");
	pourcentagePositionPaupiereGauche = 0.75;
}

void changePositionPaupiereDroite0(OSCMessage &msg){
	Serial.println("Changement position paupiere droite to 0");
	pourcentagePositionPaupiereDroite = 0;
}
void changePositionPaupiereDroite25(OSCMessage &msg){
	Serial.println("Changement position paupiere droite to 25");
	pourcentagePositionPaupiereDroite = 0.25;
}void changePositionPaupiereDroite50(OSCMessage &msg){
	Serial.println("Changement position paupiere droite to 50");
	pourcentagePositionPaupiereDroite = 0.50;
}void changePositionPaupiereDroite75(OSCMessage &msg){
	Serial.println("Changement position paupiere droite to 75");
	pourcentagePositionPaupiereDroite = 0.75;
}
