#ifndef PROCESSUS_H_
#define PROCESSUS_H_

#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>

#define TAILLE_PILE 512

enum etat {ELU,ACTIVABLE,ENDORMI};

struct processus {
  int32_t PID;
  char nom[20];
  enum etat etat;
  int32_t *registres[5];
  int32_t pile[TAILLE_PILE];
};

struct processus tableProc[2];

void idle(void);
void proc1(void);
void init_process(void);
  
#endif /*PROCESSUS_H_*/
  
