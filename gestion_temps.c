/*PARTIE 2 : GESTION DU TEMPS */


#include <inttypes.h>
#include <cpu.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <debug.h>

#include "gestion_ecran.h"
#include "gestion_temps.h"

uint8_t HH = 0;
uint8_t MM = 0;
uint8_t SS = 0;
uint32_t compteur = 0;

extern void traitant_IT_32(void);

void affiche_haut_droite(char *chaine) {
  place_curseur(0,COL_MAX - strlen(chaine) +1);
  console_putbytes(chaine,strlen(chaine));
}

void tic_PIT(void) {
  //Signalement au controleur d'IT
  outb(0x20,0x20);

  //Mise à jour du compteur
  compteur += 1/(CLOCKFREQ*0.001);
  
  if (compteur >= 1000) {
    compteur = 0;
    SS += 1;
    if (SS == 60){
      SS = 0;
      MM += 1;
      if (MM == 60){
	MM = 0;
	HH += 1;
      }
    }
  }

  //Ecriture nouveau temps
  char temps[8];
  sprintf(temps, "%d:%d:%d", HH, MM, SS);
  affiche_haut_droite(temps);
    
}
  
void init_traitant_IT(int32_t num_IT, void (*traitant)(void)) {
  uint32_t *Adrss1 = (uint32_t *) (0x1000 + 8*num_IT);
  uint32_t *Adrss2 = (uint32_t *) (0x1000 + 8*num_IT + 4);
  
  //Construction mot à écrire
  uint32_t Premier = ((uint32_t)KERNEL_CS << 16) | (0xFFFF & (int)(traitant));
  uint32_t Deuxieme = ((int)(traitant) & 0xFFFF0000) | 0x8E00;

  //Ecriture
  *Adrss1 = Premier;
  *Adrss2 = Deuxieme;
}


void masque_IRQ(uint32_t num_IRQ, bool masque) {
  uint8_t MasqueActuelle = inb(0x21);
  uint8_t A = 1 << num_IRQ;
  if (masque) {
    MasqueActuelle = MasqueActuelle | A;
  } else {
    MasqueActuelle = MasqueActuelle & ~A;
  }
  outb(MasqueActuelle,0x21);
}

void reglage_horloge() {
  outb(0x34,0x43); //Indique à l'horloge qu'on va envoyer la valeur de réglage

  outb((QUARTZ / CLOCKFREQ) % 256,0x40); //8 bits de poids faible
  outb((QUARTZ / CLOCKFREQ) >> 8,0x40); //8 bits de poids fort
}


