/* Implémentation de console_putbytes */

#include <inttypes.h>
#include <cpu.h>
#include <stdio.h>
#include "string.h"
#include "gestion_ecran.h"


uint16_t *ptr_mem(uint32_t lig, uint32_t col) {
  return (uint16_t *) (0xB8000 + 2*(lig*80 + col));
}

void ecrit_car(uint32_t lig, uint32_t col, char c, uint8_t fond_color, uint8_t txt_color) {

  if (32<=c && c<=126){ //Le reste est ignoré

    uint16_t mot = 0;
    
    mot = (fond_color << 4) + txt_color;
    mot = mot << 8;
  
    mot = mot + (uint8_t) c;   

    //envoi caractère
    uint16_t *curseur = ptr_mem(lig,col);
    *curseur = mot;

  }
}

void efface_ecran(void) {

  uint16_t espace = 0;
  uint16_t *curseur = 0;
  espace = ( 0b00001111 << 8 ) + 32;
  
  for (int l=0;l<25;l++){
    for (int c=0;c<80;c++){
      curseur = ptr_mem(l,c);
      *curseur = espace;
      
    }
  }
}

void place_curseur(uint32_t lig, uint32_t col) {
  uint16_t pos = col + 80*lig;
  outb(0x0F,0x3D4); //Partie basse
  outb(0xFF & pos,0x3D5);

  outb(0x0E,0x3D4); //Partie haute
  outb(pos>>8,0x3D5);
}





void traite_car(char c) {

  //lecture position du curseur
  uint16_t pos;
  outb(0x0E,0x3D4);
  pos = inb(0x3D5) << 8;
  outb(0x0F,0x3D4);
  pos = pos + inb(0x3D5);
  uint16_t lig = pos/80;
  uint16_t col = pos - lig*80;
  
  if (32<=c && c<=126) { //Caractère à afficher
    ecrit_car(lig,col,c,0,15);
    if (col == 79) {
      col = 0;
      lig = lig + 1; // REVENIR POUR lig = 24
    } else {
      col = col +1;
    }

  }else{ //Caractère commande
    switch(c){

    case '\b': // recule 1 case
      if (col != 0) {
	col = col -1;
      }
      break;

    case '\t': // avance 1 tabulation
      if (col <=71) {
	col = col + 8;
      }
      break;

    case '\n':
      lig = lig +1; //REVENIR POUR lig = 24
      col = 0;
      break;
      
    case '\f': //efface et revient à (0,0)
      efface_ecran();
      lig = 0;
      col = 0;
      break;

    case '\r': //retour début de ligne
      col = 0;
      break;

    default: //caractère inconnu -> fin de fonction
      return;

    }
  }
  //Cas lig = 25 (hors de l'écran)
  if (lig == 25){
    defilement();
    lig = 24;
  }
  
  
  //Enregistrement nouvelle position du curseur
  place_curseur(lig,col);
}


      
void defilement(void){
  
  for (int l=1;l<25;l++) {
    for (int c=0;c<80;c++) {
      memmove(ptr_mem(l-1,c), ptr_mem(l,c), 16);
    }
  }

  /* Remarque : le curseur reste à sa place */

}      

void console_putbytes(char *chaine, int32_t taille) {
  for (int k=0; k< taille; k++){
    traite_car(chaine[k]);
  }
}
  

    

  
