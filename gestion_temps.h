#ifndef GESTION_TEMPS_H
#define GESTION_TEMPS_H

#define ADR_IDT 0x1000
#define CONST_TRAIT 0x8E00
#define MASQUE_DONNEES 0x021
#define QUARTZ 0x1234DD
#define CLOCKFREQ 50

#include <inttypes.h>
#include <cpu.h>
#include <stdbool.h>
#include "segment.h"
#include "gestion_ecran.h"

extern void traitant_IT_32(void);


void reglage_horloge();
void affiche_haut_droite(char *chaine);
void tic_PIT(void);
void init_traitant_IT(int32_t num_IT, void (*traitant)(void));
void masque_IRQ(uint32_t num_IRQ, bool masque);

#endif /*GESTION_TEMPS_H_*/
