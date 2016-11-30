/*PARTIE 3 : PROCESSUS */

#include <cpu.h>
//#include <stdlib.h>
#include "processus.h"
#include <malloc.c.h>

extern void ctx_sw(int32_t * A, int32_t * B);
void ordonnance(void);


struct processus idleP;
struct processus proc1P;

struct processus *actif;
 
char *mon_nom(void){
  char * name = &actif->nom;
  return name;
}

int32_t mon_pid(void){
  return actif->PID;
}


void idle(void) {
  for (;;){
    printf("[%s] pid = %i\n",  mon_nom(), mon_pid());
    ordonnance();
  }
}


void proc1(void){
  for (;;) {
    printf("[%s] pid = %i\n",  mon_nom(), mon_pid());
    ordonnance();
  }
}

void init_process(void) {

  idleP.PID = 0;
  strcpy(&idleP.nom,"idle");
  idleP.etat = ELU;
  proc1P.PID = 1;
  strcpy(&proc1P.nom,"proc1");
  proc1P.etat = ACTIVABLE;

  proc1P.registres[1] = (int32_t)&proc1P.pile[TAILLE_PILE-1];
  proc1P.pile[TAILLE_PILE-1] = (int32_t)&proc1;

  tableProc[0] = &idleP;
  tableProc[1] = &proc1P;

  actif = tableProc[0];
}

void ordonnance(void){
  int k = 0;
  int indiceAncien = -1;
  int indiceNouveau = -1;
  while (k<NB_PROCESSUS && (indiceAncien == -1 || indiceNouveau == -1)){
    if (tableProc[k]->etat == ACTIVABLE){
      indiceNouveau = k;
    } else if (tableProc[k]->etat == ELU){
      indiceAncien = k;
    }
    k++;
  }

  if (indiceNouveau == -1 || indiceAncien == -1){
    printf("Erreur\n");
  } else {

    actif->etat = ACTIVABLE;
    tableProc[indiceNouveau]->etat = ELU;
    actif = tableProc[indiceNouveau];
    
    ctx_sw(tableProc[indiceAncien]->registres, tableProc[indiceNouveau]->registres);


    
  }
}
