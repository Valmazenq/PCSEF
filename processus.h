#ifndef PROCESSUS_H_
#define PROCESSUS_H_

#include <stdio.h>
#include <inttypes.h>
#include <string.h>
//#include <stdlib.h>


#define TAILLE_PILE 512
#define NB_PROCESSUS 8

enum etat {ELU,ACTIVABLE,ENDORMI};

struct processus {
  int32_t PID;
  char nom;
  enum etat etat;
  int32_t registres[5];
  int32_t pile[TAILLE_PILE];
};

struct processus *tableProc[NB_PROCESSUS];

void idle(void);
void proc1(void);
void init_process(void);
  
#endif /*PROCESSUS_H_*/
  
