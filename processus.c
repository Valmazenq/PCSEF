/*PARTIE 3 : PROCESSUS */

#include <cpu.h>
#include <stdlib.h>
#include "processus.h"

extern void ctx_sw(int x, int y);

void idle(void) {
  printf("[idle] je tente de passer la main a proc1...\n");
  ctx_sw(1,3);
}

void proc1(void){
  printf("[proc1] idle m’a donne la main\n");
  printf("[proc1] j’arrete le systeme\n");
  hlt();
}

void init_process(void) {
  struct processus idleP;
  struct processus proc1P;
  idleP.PID = 0;
  idleP.etat = ELU;
  proc1P.PID = 1;
  proc1P.etat = ACTIVABLE;
  proc1P.registres[0] = &proc1P.pile[0];
  proc1P.pile[0] = (int)proc1;
  
}
