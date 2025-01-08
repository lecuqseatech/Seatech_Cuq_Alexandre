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
    //InitTimer1();
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
            
            if(robotState.distanceTelemetreXtrmGauche <15)
                LED_BLANCHE_1 = 1;
            else
                LED_BLANCHE_1 = 0;
            if(robotState.distanceTelemetreGauche <20)
                LED_BLEUE_1 = 1;
            else
                LED_BLEUE_1 = 0;
                        if(robotState.distanceTelemetreCentre <25)
                LED_ORANGE_1 = 1;
            else
                LED_ORANGE_1 = 0;
                        if(robotState.distanceTelemetreDroit <20)
                LED_ROUGE_1 = 1;
            else
                LED_ROUGE_1 = 0;
                        if(robotState.distanceTelemetreXtrmDroit <15)
                LED_VERTE_1 = 1;
            else
                LED_VERTE_1 = 0;
        }//eux ils ont été mis a jour
    }
}

unsigned char stateRobot;
unsigned char nextStateRobot = 0;

void SetNextRobotStateInAutomaticMode() {
    unsigned char mask = 0;
    // Conversion des capteurs en masque binaire
    if (robotState.distanceTelemetreXtrmGauche < 15) mask |= 0b10000;
    if (robotState.distanceTelemetreGauche < 20) mask |= 0b01000;
    if (robotState.distanceTelemetreCentre < 25) mask |= 0b00100;
    if (robotState.distanceTelemetreDroit < 20) mask |= 0b00010;
    if (robotState.distanceTelemetreXtrmDroit < 15) mask |= 0b00001;
    
    switch (mask) {
        case 0b00000: nextStateRobot = STATE_AVANCE; 
        case 0b00001: nextStateRobot = STATE_TOURNE_MID_GAUCHE; 
        case 0b00010: nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;   
        case 0b00011: nextStateRobot = STATE_TOURNE_MID_GAUCHE;   
        case 0b00100: nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;       
        case 0b00101: nextStateRobot = STATE_TOURNE_GAUCHE;  
        case 0b00110: nextStateRobot = STATE_TOURNE_GAUCHE;      
        case 0b00111: nextStateRobot = STATE_TOURNE_GAUCHE;  
        case 0b01000:  nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;   
        case 0b01001:  nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;       
        case 0b01010:  nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;   
        case 0b01011:  nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;           
        case 0b01100:  nextStateRobot = STATE_TOURNE_DROITE;          
        case 0b01101:  nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;      
        case 0b01110:  nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;         
        case 0b01111:  nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;          
        case 0b10000:  nextStateRobot = STATE_TOURNE_MID_DROITE;      
        case 0b10001:  nextStateRobot = STATE_AVANCE;     
        case 0b10010:  nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;        
        case 0b10011:  nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;          
        case 0b10100:  nextStateRobot = STATE_TOURNE_DROITE;     
        case 0b10101:  nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;              
        case 0b10110:  nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;              
        case 0b10111:  nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;           
        case 0b11000:  nextStateRobot = STATE_TOURNE_MID_DROITE;        
        case 0b11001:  nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;        
        case 0b11010:  nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;       
        case 0b11011:  nextStateRobot = STATE_RECULE;        
        case 0b11100:  nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;               
        case 0b11101:  nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;               
        case 0b11110:  nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;    
        case 0b11111:  nextStateRobot = STATE_RECULE;            
        default:  nextStateRobot = STATE_AVANCE;                       
    }
    
    // Transition de l'état
    if (nextStateRobot != stateRobot - 1)
        stateRobot = nextStateRobot;
}

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
            stateRobot = STATE_AVANCE;
            break;
            
    }
}

