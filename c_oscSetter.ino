void toggleEngrenage(OscMessage &msg){
	Serial.println("Toggle engrenage");
	if (msg.isInt(0)){
		int result = msg.getInt(0);
		if (result == 1)
			activEngrenage = true;
		else
			activEngrenage = false;
	}
}
void toggleEngrenageTest(OscMessage &msg, int test){
	Serial.println("Toggle engrenage");
	if (msg.isInt(0)){
		int result = msg.getInt(0);
		if (result == 1)
			activEngrenage = true;
		else
			activEngrenage = false;
	}
}

void changeSensEngrenage(OscMessage &msg){
	Serial.println("Toggle sens engrenage");
	if (msg.isInt(0)){
		sensEngrenage = msg.getInt(0);
	} else {
		Serial.println("WARNING : Erreur lors du toggle engrenage");
	}
}

void changeVitaesseEngrenage(OscMessage &msg){
	Serial.println("Changement vitesse engrenage");
	if (msg.isFloat(0)){
		vitesseEngrenage = msg.getFloat(0);
	} else {
		Serial.println("WARNING : Erreur lors du changement de la vitesse engrenage");
	}
}

void changeAngleOeilGauche(OscMessage &msg){
	Serial.println("Changement angle oeil gauche");
	if (msg.isFloat(0)){
		angleOeilGauche = map(msg.getFloat(0),0,1,0,180);
	} else {
		Serial.println("WARNING : Erreur lors du changement d'angle de l'oeil gauche");
	}
}

void changeAngleOeilDroit(OscMessage &msg){
	Serial.println("Changement angle oeil droit");
	if (msg.isFloat(0)){
		angleOeilDroit = map(msg.getFloat(0),0,1,0,180);
	} else {
		Serial.println("WARNING : Erreur lors du changement d'angle de l'oeil droit");
	}
}

void changePositionPaupiereGauche(OscMessage &msg){
	if(!paupiereGaucheBouge) {
		Serial.println("Changement position paupiere gauche");
		if (msg.isInt(0)){
			pourcentagePositionPaupiereGauche = msg.getInt(0) / 100;
		} else {
			Serial.println("WARNING : Erreur lors du changement d'angle de position paupiere gauche");
		}
	}
}

void changePositionPaupiereDroite(OscMessage &msg){
	if(!paupiereDroiteBouge) {
		Serial.println("Changement position paupiere droite");
		if (msg.isInt(0)){
			pourcentagePositionPaupiereDroite = msg.getInt(0) / 100;
		} else {
			Serial.println("WARNING : Erreur lors du changement de position paupiere droite");
		}
	}
}
