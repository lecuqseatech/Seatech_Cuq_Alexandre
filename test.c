void SetNextRobotStateInAutomaticMode() {
    unsigned char positionObstacle = PAS_D_OBSTACLE;
    //éDtermination de la position des obstacles en fonction des ééètlmtres
    if (robotState.distanceTelemetreDroit < 30 &&
            robotState.distanceTelemetreCentre > 20 &&
            robotState.distanceTelemetreGauche > 30) //Obstacle àdroite
        positionObstacle = OBSTACLE_A_DROITE;
    else if (robotState.distanceTelemetreDroit < 30 &&
            robotState.distanceTelemetreCentre < 20 &&
            robotState.distanceTelemetreGauche < 30)
        positionObstacle = DEVANT;
    else if (robotState.distanceTelemetreDroit > 30 &&
            robotState.distanceTelemetreCentre > 20 &&
            robotState.distanceTelemetreGauche < 30) //Obstacle un peu àgauche
        positionObstacle = OBSTACLE_A_GAUCHE;
    else if (robotState.distanceTelemetreCentre < 20 &&
            robotState.distanceTelemetreDroit < 30 &&
            robotState.distanceTelemetreXtrmDroit < 15 ) //Obstacle en face et a doite
        positionObstacle = OBSTACLE_EN_FACE;
    else if (robotState.distanceTelemetreCentre < 20 &&
            robotState.distanceTelemetreGauche < 30 &&
            robotState.distanceTelemetreXtrmGauche < 15 ) //Obstacle en face et a gauche
        positionObstacle = OBSTACLE_EN_FACE2;
    else if (robotState.distanceTelemetreDroit > 30 &&
            robotState.distanceTelemetreCentre > 20 &&
            robotState.distanceTelemetreGauche > 30) //pas d?obstacle
        positionObstacle = PAS_D_OBSTACLE;
    else if (robotState.distanceTelemetreGauche < 30 &&
            robotState.distanceTelemetreXtrmGauche < 15)
        positionObstacle = OBSTACLE_A_XTRM_GAUCHE; //a créer!!!!!!!!!!!!!!!!!! 
    else if (robotState.distanceTelemetreDroit < 30 &&
            robotState.distanceTelemetreXtrmDroit < 15)
        positionObstacle = OBSTACLE_A_XTRM_GAUCHE;
    else if (robotState.distanceTelemetreDroit > 30 &&
            robotState.distanceTelemetreCentre < 20 &&
            robotState.distanceTelemetreGauche > 30)
        positionObstacle = DEVANT;
        else if (robotState.distanceTelemetreDroit < 30 &&
            robotState.distanceTelemetreCentre > 20 &&
            robotState.distanceTelemetreGauche > 30 &&
            robotState.distanceTelemetreXtrmGauche > 15 &&
            robotState.distanceTelemetreXtrmGauche > 15)        
        positionObstacle = OBSTACLE_A_DROITE;
    else if (robotState.distanceTelemetreDroit > 30 &&
            robotState.distanceTelemetreCentre > 20 &&
            robotState.distanceTelemetreGauche > 30 &&
            robotState.distanceTelemetreXtrmGauche < 15 &&
            robotState.distanceTelemetreXtrmGauche < 15)        
        positionObstacle = PAS_D_OBSTACLE;
    else if (robotState.distanceTelemetreDroit < 30 &&
            robotState.distanceTelemetreCentre < 20 &&
            robotState.distanceTelemetreGauche > 30 &&
            robotState.distanceTelemetreXtrmGauche > 15 &&
            robotState.distanceTelemetreXtrmGauche > 15)        
        positionObstacle = OBSTACLE_A_DROITE;
    else if (robotState.distanceTelemetreDroit > 30 &&
            robotState.distanceTelemetreCentre < 20 &&
            robotState.distanceTelemetreGauche < 30 &&
            robotState.distanceTelemetreXtrmGauche > 15 &&
            robotState.distanceTelemetreXtrmGauche > 15)        
        positionObstacle = OBSTACLE_A_GAUCHE;
    
    //éDtermination de l'état à venir du robot
    if (positionObstacle == PAS_D_OBSTACLE)
        nextStateRobot = STATE_AVANCE;
    else if (positionObstacle == DEVANT)
        nextStateRobot = STATE_RECULE;
    else if (positionObstacle == OBSTACLE_A_DROITE)
        nextStateRobot = STATE_TOURNE_GAUCHE;
    else if (positionObstacle == OBSTACLE_A_GAUCHE)
        nextStateRobot = STATE_TOURNE_DROITE;
    else if (positionObstacle == OBSTACLE_EN_FACE)
        nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
    else if (positionObstacle == OBSTACLE_EN_FACE2)
        nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
    else if (positionObstacle == OBSTACLE_A_XTRM_DROITE) //de la a la faut modif 
        nextStateRobot = STATE_TOURNE_zbi_GAUCHE;
    else if (positionObstacle == OBSTACLE_A_XTRM_GAUCHE)
        nextStateRobot = STATE_TOURNE_zbi_DROITE;              //à la en fait 
    //Si l?on n?est pas dans la transition de lé?tape en cours
    if (nextStateRobot != stateRobot - 1)
        stateRobot = nextStateRobot;
}






void SetNextRobotStateInAutomaticMode() {
    unsigned char positionObstacle = PAS_D_OBSTACLE;
    //ou est l'obstacle








