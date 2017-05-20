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
