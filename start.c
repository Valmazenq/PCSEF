#include <cpu.h>
#include <inttypes.h>
#include "gestion_ecran.h"
#include "gestion_temps.h"
#include "processus.h"
#include "stdio.h"

extern void traitant_IT_32(void);

// on peut s'entrainer a utiliser GDB avec ce code de base
// par exemple afficher les valeurs de x, n et res avec la commande display

// une fonction bien connue
uint32_t fact(uint32_t n)
{
    uint32_t res;
    if (n <= 1) {
        res = 1;
    } else {
        res = fact(n - 1) * n;
    }
    return res;
}

void kernel_start(void)
{
  //uint32_t x = fact(5);
    // quand on saura gerer l'ecran, on pourra afficher x
  //(void)x;
  reglage_horloge();
  efface_ecran();
  init_traitant_IT(32,traitant_IT_32);
  masque_IRQ(0,false);
  //sti();
  init_process();
  idle();
  
  
  // on ne doit jamais sortir de kernel_start
  while (1) {
    
    // cette fonction arrete le processeur
    hlt();
    }
}

