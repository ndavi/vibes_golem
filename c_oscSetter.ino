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
