void SetNextRobotStateInAutomaticMode() {
    unsigned char obstacleMask = 0;

    // Conversion des capteurs en masque binaire
    if (robotState.distanceTelemetreXtrmGauche < 15) obstacleMask |= 0b10000;
    if (robotState.distanceTelemetreGauche < 20) obstacleMask |= 0b01000;
    if (robotState.distanceTelemetreCentre < 25) obstacleMask |= 0b00100;
    if (robotState.distanceTelemetreDroit < 20) obstacleMask |= 0b00010;
    if (robotState.distanceTelemetreXtrmDroit < 15) obstacleMask |= 0b00001;

    // Déterminer la position de l'obstacle
    unsigned char positionObstacle = DetermineObstaclePosition(obstacleMask);

    // Déterminer l'état du robot
    nextStateRobot = DetermineNextState(positionObstacle);

    // Transition de l'état
    if (nextStateRobot != stateRobot - 1)
        stateRobot = nextStateRobot;
}

unsigned char DetermineObstaclePosition(unsigned char mask) {
    switch (mask) {
        case 0b00000: return PAS_D_OBSTACLE; 
        case 0b00001: return OBSTACLE_A_XTRM_DROITE; 
        case 0b00010: return OBSTACLE_EN_FACE;   
        case 0b00011: return OBSTACLE_A_XTRM_DROITE;   
        case 0b00100: return DEVANT;       
        case 0b00101: return OBSTACLE_A_DROITE;  
        case 0b00110: return OBSTACLE_A_DROITE;      
        case 0b00111: return OBSTACLE_A_DROITE;  
        case 0b01000: return OBSTACLE_EN_FACE2;   
        case 0b01001: return OBSTACLE_EN_FACE;       
        case 0b01010: return DEVANT;   
        case 0b01011: return OBSTACLE_EN_FACE;           
        case 0b01100: return OBSTACLE_A_GAUCHE;          
        case 0b01101: return OBSTACLE_EN_FACE;      
        case 0b01110: return DEVANT;         
        case 0b01111: return OBSTACLE_EN_FACE;          
        case 0b10000: return OBSTACLE_A_XTRM_GAUCHE;      
        case 0b10001: return PAS_D_OBSTACLE;     
        case 0b10010: return OBSTACLE_EN_FACE2;        
        case 0b10011: return OBSTACLE_EN_FACE;          
        case 0b10100: return OBSTACLE_A_GAUCHE;     
        case 0b10101: return DEVANT;              
        case 0b10110: return OBSTACLE_EN_FACE2;              
        case 0b10111: return OBSTACLE_EN_FACE;           
        case 0b11000: return OBSTACLE_A_XTRM_GAUCHE;        
        case 0b11001: return OBSTACLE_EN_FACE;        
        case 0b11010: return OBSTACLE_EN_FACE2;       
        case 0b11011: return DEVANT;        
        case 0b11100: return OBSTACLE_EN_FACE2;               
        case 0b11101: return OBSTACLE_EN_FACE2;               
        case 0b11110: return OBSTACLE_EN_FACE2;    
        case 0b11111: return DEVANT;            
        default: return PAS_D_OBSTACLE;                       
    }
}

unsigned char DetermineNextState(unsigned char positionObstacle) {
    switch (positionObstacle) {
        case PAS_D_OBSTACLE: return STATE_AVANCE;
        case DEVANT: return STATE_RECULE;
        case OBSTACLE_A_DROITE: return STATE_TOURNE_GAUCHE;
        case OBSTACLE_A_GAUCHE: return STATE_TOURNE_DROITE;
        case OBSTACLE_EN_FACE: return STATE_TOURNE_SUR_PLACE_GAUCHE;
        case OBSTACLE_EN_FACE2: return STATE_TOURNE_SUR_PLACE_DROITE;
        case OBSTACLE_A_XTRM_DROITE: return STATE_TOURNE_zbi_GAUCHE;
        case OBSTACLE_A_XTRM_GAUCHE: return STATE_TOURNE_zbi_DROITE;
        default: return STATE_STOP; // État par défaut si non défini
    }
}
