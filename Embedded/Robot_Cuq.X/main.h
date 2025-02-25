#ifndef MAIN_H
#define	MAIN_H

#define STATE_ATTENTE 0
#define STATE_ATTENTE_EN_COURS 1
#define STATE_AVANCE 2
#define STATE_AVANCE_EN_COURS 3
#define STATE_TOURNE_GAUCHE 4
#define STATE_TOURNE_GAUCHE_EN_COURS 5
#define STATE_TOURNE_zbi_GAUCHE 41
#define STATE_TOURNE_zbi_GAUCHE_EN_COURS 51
#define STATE_TOURNE_DROITE 6
#define STATE_TOURNE_DROITE_EN_COURS 7
#define STATE_TOURNE_zbi_DROITE 61
#define STATE_TOURNE_zbi_DROITE_EN_COURS 71
#define STATE_TOURNE_SUR_PLACE_GAUCHE 8
#define STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS 9
#define STATE_TOURNE_SUR_PLACE_DROITE 10
#define STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS 11
#define STATE_ARRET 12
#define STATE_ARRET_EN_COURS 13
#define STATE_RECULE 14
#define STATE_RECULE_EN_COURS 15
#define STATE_TOURNE_MID_GAUCHE 87
#define STATE_TOURNE__MID_GAUCHE_EN_COURS 88
#define STATE_TOURNE_MID_DROITE 98
#define STATE_TOURNE_MID_DROITE_EN_COURS 99

void OperatingSystemLoop(void);
void SetNextRobotStateInAutomaticMode();

#endif	/* MAIN_H */

