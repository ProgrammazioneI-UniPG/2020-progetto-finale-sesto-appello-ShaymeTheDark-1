#include <stdio.h>
#include "gamelib.h"
#include <stdlib.h>
#include <time.h> //random

int main () {
    int a;
    time_t t;
    srand((unsigned) time(&t));
    printf("Benvenuto in Sabbie!\nUn po' di storia... La Arvais e la Hartornen sono due famiglie che si contendono da anni sul pianeta Sabbie l'estrazione della spez.. melassa, una preziosissima sostanza fondamentale per la struttura della società galattica.\nIl tuo compito è riuscire a sfuggire dai pericoli delle grotte di Sabbie, riuscendo al contempo a estrarre più melassa possibile!\n\n");
    do {
        printf ("Scrivi 1 per creare la mappa\nScrivi 2 per cominciare a giocare\nScrivi 3 per terminare il gioco\n");
        scanf("%d", &a);
        switch (a)
        {
            case 1: crea_cunicoli();
                break;
            case 2: gioca();
                break;
            case 3: printf("Grazie per aver giocato!\n"); //chiamata di deallocazione mappa
                break;
            default: printf("Devi inserire un valore del menù\n");
                break;
            
        } 
    }while (a!=3);  
    return 0;
}
