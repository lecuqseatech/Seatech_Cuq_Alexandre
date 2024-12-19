#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "PWM.h"
#include "ADC.h"
#include "robot.h"
#include "main.h"

int main(void) {

    /**************************************************************************/
    //Initialisation oscillateur
    /**************************************************************************/
    InitOscillator();
    /***********************************************************************************************/
    // Configuration des input et output (IO)
    /***********************************************************************************************/
    InitIO();
    /**************************************************************************/
    //Initialisation PWM
    /**************************************************************************/
    InitPWM();
    /**************************************************************************/
    //Initialisation ADC
    /**************************************************************************/
    InitADC1();
    /**************************************************************************/
    //Initialisation timer
    /**************************************************************************/
    InitTimer1();
    //InitTimer23();
    InitTimer4();


    //robotState.acceleration=1;

    LED_BLANCHE_1 = 1;
    LED_BLEUE_1 = 1;
    LED_ORANGE_1 = 1;
    LED_ROUGE_1 = 1;
    LED_VERTE_1 = 1;

    LED_BLANCHE_2 = 1;
    LED_BLEUE_2 = 1;
    LED_ORANGE_2 = 1;
    LED_ROUGE_2 = 0;
    LED_VERTE_2 = 1;

    /***********************************************************************************************/
    // Boucle Principale
    /***********************************************************************************************/
    while (1) {
        if (ADCIsConversionFinished() == 1) {
            ADCClearConversionFinishedFlag();
            unsigned int * result = ADCGetResult();
            float volts = ((float) result [0])* 3.3 / 4096;
            robotState.distanceTelemetreXtrmGauche = 34 / volts - 5;
            volts = ((float) result [1])* 3.3 / 4096;
            robotState.distanceTelemetreGauche = 34 / volts - 5;
            volts = ((float) result [2])* 3.3 / 4096;
            robotState.distanceTelemetreCentre = 34 / volts - 5;
            volts = ((float) result [3])* 3.3 / 4096;
            robotState.distanceTelemetreDroit = 34 / volts - 5;
            volts = ((float) result [4])* 3.3 / 4096;
            robotState.distanceTelemetreXtrmDroit = 34 / volts - 5;
        }//eux ils ont été mis a jour
    }
}

unsigned char stateRobot;
unsigned char nextStateRobot = 0;
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



//operatin system loop

void OperatingSystemLoop(void) {
    switch (stateRobot) {
        case STATE_ATTENTE:
            timestamp = 0;
            PWMSetSpeedConsigne(0, MOTEUR_DROIT);
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
            stateRobot = STATE_ATTENTE_EN_COURS;
        case STATE_ATTENTE_EN_COURS:
            if (timestamp > 1000)
                stateRobot = STATE_AVANCE;
            break;
        case STATE_AVANCE:                                  //avance
            PWMSetSpeedConsigne(20, MOTEUR_DROIT);
            PWMSetSpeedConsigne(20, MOTEUR_GAUCHE);
            stateRobot = STATE_AVANCE_EN_COURS;
            break;
        case STATE_AVANCE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_TOURNE_MID_GAUCHE:                           //tourne mid gauche
            PWMSetSpeedConsigne(30, MOTEUR_DROIT);
            PWMSetSpeedConsigne(8, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_GAUCHE_EN_COURS;
            break;
        case STATE_TOURNE__MID_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_TOURNE_MID_DROITE:
            PWMSetSpeedConsigne(8, MOTEUR_DROIT);
            PWMSetSpeedConsigne(30, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_DROITE_EN_COURS;
            break;
        case STATE_TOURNE_MID_DROITE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_TOURNE_SUR_PLACE_GAUCHE:
            PWMSetSpeedConsigne(15, MOTEUR_DROIT);
            PWMSetSpeedConsigne(-15, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
            break;
        case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_TOURNE_SUR_PLACE_DROITE:
            PWMSetSpeedConsigne(-15, MOTEUR_DROIT);
            PWMSetSpeedConsigne(15, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS;
            break;
        case STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_RECULE:
            PWMSetSpeedConsigne(-18, MOTEUR_DROIT);
            PWMSetSpeedConsigne(-20, MOTEUR_GAUCHE);
            stateRobot = STATE_RECULE_EN_COURS;
            break;
        case STATE_RECULE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;    
        default:
            stateRobot = STATE_ATTENTE;
            break;
            
    }
}
