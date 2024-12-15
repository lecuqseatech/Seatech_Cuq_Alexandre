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

    // Détermination de l'état à venir du robot
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
    else if (positionObstacle == OBSTACLE_A_XTRM_DROITE)
        nextStateRobot = STATE_TOURNE_zbi_GAUCHE;
    else if (positionObstacle == OBSTACLE_A_XTRM_GAUCHE)
        nextStateRobot = STATE_TOURNE_zbi_DROITE;

    // Si l'on n'est pas dans la transition de l'étape en cours
    if (nextStateRobot != stateRobot - 1)
        stateRobot = nextStateRobot;
}

