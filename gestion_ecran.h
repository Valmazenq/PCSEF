#ifndef GESTION_ECRAN_H_
#define GESTION_ECRAN_H_

#define COMMANDE_CURSEUR 0x3D4
#define DONNEES_CURSEUR 0x3D5
#define CURSEUR_BASSE 0x0F
#define CURSEUR_HAUTE 0x0E
#define COL_MAX 79
#define LIG_MAX 24

#include <inttypes.h>
#include <cpu.h>

uint16_t *ptr_mem(uint32_t lig, uint32_t col);
void ecrit_car(uint32_t lig, uint32_t col, char c, 
	       uint8_t fond_color, uint8_t txt_color);
void efface_ecran(void);
void place_curseur(uint32_t lig,uint32_t col);
void traite_car(char c);
void defilement(void);
void console_putbytes(char *chaine, int32_t taille);



#endif /*GESTION_ECRAN_H_*/
