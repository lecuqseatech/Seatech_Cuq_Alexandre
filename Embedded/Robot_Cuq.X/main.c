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
void SetNextRobotStateInAutomaticMode() 
{
    unsigned char positionObstacle = PAS_D_OBSTACLE;

    // Où est l'obstacle ?
    if (robotState.distanceTelemetreXtrmGauche < 15) // 10000
    {
        if (robotState.distanceTelemetreGauche < 20)  // 01000
        {
            if (robotState.distanceTelemetreCentre < 25) // 00100
            {
                if (robotState.distanceTelemetreDroit < 20) // 00010
                {
                    if (robotState.distanceTelemetreXtrmDroit < 15) // 00001
                    {
                        positionObstacle = PAS_D_OBSTACLE;
                    } 
                    else // distanceTelemetreXtrmDroit > 15
                    {
                        positionObstacle = OBSTACLE_A_XTRM_DROITE;
                    }
                } 
                else // distanceTelemetreDroit > 20
                {
                    if (robotState.distanceTelemetreXtrmDroit < 15) 
                    {
                        positionObstacle = OBSTACLE_EN_FACE;
                    } 
                    else 
                    {
                        positionObstacle = OBSTACLE_A_XTRM_DROITE;
                    }
                }
            }
            else // distanceTelemetreCentre > 25
            {
                if (robotState.distanceTelemetreDroit < 20) 
                {
                    if (robotState.distanceTelemetreXtrmDroit < 15) 
                    {
                        positionObstacle = DEVANT;
                    } 
                    else // distanceTelemetreXtrmDroit > 15
                    {
                        positionObstacle = OBSTACLE_A_DROITE;
                    }
                } 
                else // distanceTelemetreDroit > 20
                {
                    if (robotState.distanceTelemetreXtrmDroit < 15) 
                    {
                        positionObstacle = OBSTACLE_A_DROITE;
                    } 
                    else 
                    {
                        positionObstacle = OBSTACLE_A_DROITE;
                    }
                }
            }
        }
        if (robotState.distanceTelemetreGauche > 20) 
        {
            if (robotState.distanceTelemetreCentre < 25) 
            {
                if (robotState.distanceTelemetreDroit < 20) 
                {
                    if (robotState.distanceTelemetreXtrmDroit < 15) 
                    {
                        positionObstacle = OBSTACLE_EN_FACE2;      
                    } 
                    else // distanceTelemetreXtrmDroit > 15
                    {
                        positionObstacle = OBSTACLE_EN_FACE;
                    }
                } 
                else // distanceTelemetreDroit > 20
                {
                    if (robotState.distanceTelemetreXtrmDroit < 15) 
                    {
                        positionObstacle = DEVANT;
                    } 
                    else 
                    {
                        positionObstacle = OBSTACLE_EN_FACE;           
                    }
                }
            }
            else // distanceTelemetreCentre > 25
            {
                if (robotState.distanceTelemetreDroit < 20) 
                {
                    if (robotState.distanceTelemetreXtrmDroit < 15) 
                    {
                        positionObstacle = OBSTACLE_A_GAUCHE;                         
                    } 
                    else // distanceTelemetreXtrmDroit > 15
                    {
                        positionObstacle = OBSTACLE_EN_FACE;   
                    }
                } 
                else // distanceTelemetreDroit > 20
                {
                    if (robotState.distanceTelemetreXtrmDroit < 15) 
                    {
                        positionObstacle = DEVANT;
                    } 
                    else 
                    {
                        positionObstacle = OBSTACLE_EN_FACE;
                    }
                }
            }
        }                                         
    }
    if (robotState.distanceTelemetreXtrmGauche > 15) // 10000
    {
        if (robotState.distanceTelemetreGauche < 20)  // 01000
        {
            if (robotState.distanceTelemetreCentre < 25) // 00100
            {
                if (robotState.distanceTelemetreDroit < 20) // 00010
                {
                    if (robotState.distanceTelemetreXtrmDroit < 15) // 00001
                    {
                        positionObstacle = OBSTACLE_A_XTRM_GAUCHE;
                    } 
                    else // distanceTelemetreXtrmDroit > 15
                    {
                        positionObstacle = PAS_D_OBSTACLE;
                    }
                } 
                else // distanceTelemetreDroit > 20
                {
                    if (robotState.distanceTelemetreXtrmDroit < 15) 
                    {
                        positionObstacle = OBSTACLE_EN_FACE2; 
                    } 
                    else 
                    {
                        positionObstacle = OBSTACLE_EN_FACE; 
                    }
                }
            }
            else // distanceTelemetreCentre > 25
            {
                if (robotState.distanceTelemetreDroit < 20) 
                {
                    if (robotState.distanceTelemetreXtrmDroit < 15) 
                    {
                        positionObstacle = OBSTACLE_A_GAUCHE;  
                    } 
                    else // distanceTelemetreXtrmDroit > 15
                    {
                        positionObstacle = DEVANT;
                    }
                } 
                else // distanceTelemetreDroit > 20
                {
                    if (robotState.distanceTelemetreXtrmDroit < 15) 
                    {
                        positionObstacle = OBSTACLE_EN_FACE2;  
                    } 
                    else 
                    {
                        positionObstacle = OBSTACLE_EN_FACE;       
                    }
                }
            }
        }
        if (robotState.distanceTelemetreGauche > 20) 
        {
            if (robotState.distanceTelemetreCentre < 25) 
            {
                if (robotState.distanceTelemetreDroit < 20) 
                {
                    if (robotState.distanceTelemetreXtrmDroit < 15) 
                    {
                        positionObstacle = OBSTACLE_A_XTRM_GAUCHE;  
                    } 
                    else // distanceTelemetreXtrmDroit > 15
                    {
                        positionObstacle = OBSTACLE_EN_FACE;   
                    }
                } 
                else // distanceTelemetreDroit > 20
                {
                    if (robotState.distanceTelemetreXtrmDroit < 15) 
                    {
                        positionObstacle = OBSTACLE_EN_FACE2;  
                    } 
                    else 
                    {
                        positionObstacle = DEVANT;       
                    }
                }
            }
            else // distanceTelemetreCentre > 25
            {
                if (robotState.distanceTelemetreDroit < 20) 
                {
                    if (robotState.distanceTelemetreXtrmDroit < 15) 
                    {
                        positionObstacle = OBSTACLE_EN_FACE2;                   
                    } 
                    else // distanceTelemetreXtrmDroit > 15
                    {
                        positionObstacle = OBSTACLE_EN_FACE2;      
                    }
                } 
                else // distanceTelemetreDroit > 20
                {
                    if (robotState.distanceTelemetreXtrmDroit < 15) 
                    {
                        positionObstacle = OBSTACLE_EN_FACE2;
                    } 
                    else 
                    {
                        positionObstacle = DEVANT;
                    }
                }
            }
        }
    }
  
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
