#include <stdio.h>
#include "gamelib.h"
#include <stdlib.h>
#include <time.h> //random


static int conta_caverne_arv=0;
static int conta_caverne_hart=0;
static int crollo_a=0;
static int crollo_h=0; //controllo dei crolli
static int turno = 0; // contatore del turno
static int mappa =0; //controllo della creazione mappa
static void inserisci_caverna(Grotto** primo, Grotto** ultimo, int* conta_caverne);
static void stampa_cunicolo(Grotto* primo, int conta_caverne);
static void canc_caverna(Grotto** primo, Grotto** ultimo, int* conta_caverne);
static void tipo_caverna(struct Scavatrice* controllo);
static void cancella_mappa(Grotto** primo, Grotto** ultimo, int* conta);
static void battaglia(struct Scavatrice* arv, struct Scavatrice* hart);
static void esci(struct Scavatrice* fuga);
static void chiudi_cunicoli();
static void aggira(struct Scavatrice* luogo, int* massi);
static void avanza(struct Scavatrice* Scav, int* crollo);
static void abbatti(struct Scavatrice* check);
static Grotto* primo_cunicolo_arvais = NULL;
static Grotto* primo_cunicolo_hartornen = NULL;
static Grotto* last_cunicolo_arvais = NULL;
static Grotto* last_cunicolo_hartornen = NULL;
static struct Scavatrice scavatrice_arvais;
static struct Scavatrice scavatrice_hartornen;


void crea_cunicoli(){
      int a;
      do {
        printf ("Creazione della mappa di gioco\nInserisci 1 per inserire una caverna\nInserisci 2 per cancellare una caverna\nInserisci 3 per stampare\nInserisci 4 per chiudere i cunicoli\n");
        scanf("%d", &a);
        switch (a)
        {
            case 1: {int b;
                    do {
                        printf("Ciao giocatore! Sei il giocatore 1(Arvais) o il giocatore 2(Hartornen)?\nInserisci 1 o 2 per la tua scelta\n");
                        scanf("%d",&b);
                        if (b==1) 
                            inserisci_caverna(&primo_cunicolo_arvais, &last_cunicolo_arvais, &conta_caverne_arv);
                        else if (b==2) 
                            inserisci_caverna(&primo_cunicolo_hartornen,&last_cunicolo_hartornen, &conta_caverne_hart);
                        else    
                            printf("I valori consentiti sono 1 o 2!\n");
                    } while (b!=1 && b!=2);}
                break;
            case 2:{int b;
                    do {
                        printf("Ciao! Per quale giocatore vuoi cancellare una caverna?\nInserisci 1(Arvais) o 2(Hartornen) per la tua scelta\n");
                        scanf("%d",&b);
                        if (b==1) canc_caverna(&primo_cunicolo_arvais, &last_cunicolo_arvais, &conta_caverne_arv);
                        else if (b==2) canc_caverna(&primo_cunicolo_hartornen,&last_cunicolo_hartornen, &conta_caverne_hart);
                        else    
                        printf("I valori consentiti sono 1 o 2!\n");
                      
                    } while (b!=1 && b!=2);}
                break;
            case 3: {int c;
                    do { 
                        printf("Ciao! Quale mappa vuoi stampare?\nScegli 1 per il cunicolo Arvais\nScegli 2 per il cunicolo Hartornen\n");
                        scanf("%d", &c);
                        if(c==1)
                            stampa_cunicolo(primo_cunicolo_arvais, conta_caverne_arv);
                        else if (c==2)
                            stampa_cunicolo(primo_cunicolo_hartornen, conta_caverne_hart);
                        else 
                            printf("Devi inserire 1 o 2");
                    } while (c!=2 && c!=1);}
                break;
            case 4: chiudi_cunicoli();
                break;
            default: printf("Devi inserire un valore indicato\n");
                break;
        }
    }while (mappa!=1 || a!=4); //controllo sulla flag della mappa
return; 
}


void inserisci_caverna(Grotto** primo, Grotto** ultimo, int* conta_caverne){
    Grotto* ins = (Grotto*)malloc(sizeof(Grotto));
    ins->indietro = NULL;
    ins->avanti = NULL;
    ins->destra = NULL;
    ins->sinistra= NULL;
    int dado = rand()%100+1;
    if (dado<=50)
        ins->imprevisto = nessun_imprevisto;
    else if (dado>50 && dado<=85)
        ins->imprevisto = crollo;
    else if (dado>85) 
        ins->imprevisto=baco;
    dado = rand()%100+1;
    if (dado<=50)
        ins->melassa=nessuna;
    else if (dado>50 && dado<=80)
        ins->melassa=poca;
    else if (dado>80)
        ins->melassa=molta;
    printf("Inserisci un valore per il tipo della caverna.\n1 per una caverna normale\n2 per una caverna speciale\n3 per una caverna accidentata\n");
    int b;    
        do {
            scanf("%d", &b);
            if (b==1)
                ins->type_caverna=normale;
            else if (b==2)
                ins->type_caverna=speciale;
            else if (b==3)
                ins->type_caverna=accidentata;
            else
                printf("Inserisci un valore valido per il tipo di caverna!\n");
        } while (b!=1 && b!=2 && b!=3);
    
    if (*primo == NULL){
            *primo = ins;
            *ultimo = ins;
            *conta_caverne=1;
    }
    else{
        int a;
        printf("Inserisci 1 per mettere la caverna avanti\nInserisci 2 per mettere la caverna a destra\nInserisci 3 per mettere la caverna a sinistra\n");
        do {
            scanf("%d", &a);
            if (a==1){
                    ins->indietro=*ultimo; //puntatore alla cav precedente
                    (*ultimo)->avanti=ins;
                    *ultimo=ins;
                    ++(*conta_caverne);}
            else if(a==2){
                    ins->indietro=*ultimo;
                    (*ultimo)->destra=ins;
                    *ultimo=ins;
                    ++(*conta_caverne);}
            else if (a==3){
                    ins->indietro=*ultimo;
                    (*ultimo)->sinistra=ins;
                    *ultimo=ins;
                    ++(*conta_caverne);}
            else
                    printf("Devi inserire uno di quei valori!\n");
        } while (a!=1 && a!=2 && a!=3);
    }
    return;
}

void stampa_cunicolo(Grotto* primo, int conta_caverne){
    if (primo==NULL)
        printf("Non c'è nessuna mappa!\n\n");
    else{ 
        Grotto* Scan = primo;
        do {
            printf("L'indirizzo della caverna è %p\n", Scan);
            printf("La quantità di melassa è %d\n", Scan->melassa);
            printf("Il tipo di caverna è %d\n", Scan->type_caverna);
            printf("Il tipo di imprevisto è %d\n", Scan->imprevisto);
            if(Scan->avanti!=NULL){
                Scan=Scan->avanti;
                printf("Il collegamento con la caverna successiva è avanti\n");
                printf("La caverna successiva è %p\n\n", Scan);}
            else if(Scan->destra!=NULL){
                Scan=Scan->destra;
                printf("Il collegamento con la caverna successiva è a destra\n");
                printf("La caverna successiva è %p\n\n", Scan);}
            else if(Scan->sinistra!=NULL){
                Scan=Scan->sinistra;
                printf("Il collegamento con la caverna successiva è a sinistra\n");
                printf("La caverna successiva è %p\n\n", Scan);}
            else{
                printf("Questa è l'ultima grotta!\n\n");
                Scan= NULL;}
        }while (Scan!= NULL);
    printf("Il numero di caverne create è: %d\n\n", conta_caverne);
    }
return;
}

void canc_caverna(Grotto** primo, Grotto** ultimo, int* conta_caverne){
    if (*ultimo==NULL)
        printf("Non ci sono grotte nella mappa\n\n");
    else if (*ultimo != *primo){
        Grotto* Bomba = *ultimo;
        printf("La coda si trova a %p\n", *ultimo);
        *ultimo= (*ultimo)->indietro;
        free(Bomba);
        (*ultimo)->avanti = NULL;
        (*ultimo)->destra = NULL;
        (*ultimo)->sinistra = NULL;
        --(*conta_caverne);
        printf("La coda adesso si trova a %p, la caverna precendente è stata eliminata correttamente\n", *ultimo);
        printf("Il numero di caverne rimaste è %d\n\n", *conta_caverne);}
    else {
        *primo = NULL;
        free(*ultimo);
        *ultimo = NULL;
        --(*conta_caverne);
        printf("E' stata cancellata l'unica caverna in lista\n\n");
    }
return;
}

void chiudi_cunicoli(){
    if (conta_caverne_arv >= 10 && conta_caverne_hart >= 10) {
        mappa = 1;
        printf("Ci sono abbastanza caverne per giocare!\n\n");}
    else {
        printf ("Ci vogliono almeno 10 caverne a giocatore per poter cominciare la partita!\n\n");
        mappa = 0;
    }
return;
} // Fine delle funzioni per la creazione della mappa

void gioca(){
    if(mappa==0){
        printf("Per poter giocare devi prima aver creato una mappa!\n\n");
        return;}
    else{
        scavatrice_arvais.posizione=primo_cunicolo_arvais;
        scavatrice_arvais.serbatoio=4;
        scavatrice_arvais.scorta=0; 
        scavatrice_hartornen.posizione=primo_cunicolo_hartornen;
        scavatrice_hartornen.serbatoio=4;
        scavatrice_hartornen.scorta=0;
        scavatrice_arvais.uscita = 0;
        scavatrice_hartornen.uscita = 0;
        crollo_a= 0;
        crollo_h= 0;
        printf("Comincia la partita!\n\n");
            do{ 
                if(scavatrice_arvais.uscita == 1 || scavatrice_hartornen.uscita ==1)
                    turno = 0;
                else
                    ++turno;
                int dado = rand()%100+1;
                int scontro =3*turno;
                if (dado<=scontro)
                    battaglia(&scavatrice_arvais,&scavatrice_hartornen);
                else{   
                        if(scavatrice_arvais.uscita == 0){
                            int scelta;
                            printf ("Turno Arvais!\nScrivi 1 per avanzare\n2 per abbattere\n3 per aggirare \n4 per uscire.\n\nAttenzione! Puoi aggirare solo nel caso di un crollo e uscire solo in una caverna con l'uscita!\n\n");
                            printf ("Il numero di energia nel tuo serbatoio è:%d\nLa tua melassa raccolta è %d\n\n", scavatrice_arvais.serbatoio, scavatrice_arvais.scorta);
                            scanf("%d", &scelta);
                            switch (scelta)
                            {      
                                case 1: if(crollo_a==0)
                                            avanza(&scavatrice_arvais,&crollo_a);
                                        else{
                                            printf("Non puoi avanzare! Il collegamento è crollato!\nVerrà automaticamente aggirato il crollo\n\n");
                                            aggira(&scavatrice_arvais,&crollo_a);
                                    }
                                    break;
                                case 2: if(crollo_a==0)
                                            abbatti(&scavatrice_arvais);
                                        else {
                                            printf("Non puoi avanzare! Il collegamento è crollato!\nVerrà automaticamente aggirato il crollo\n\n");
                                            aggira(&scavatrice_arvais,&crollo_a);
                                        }
                                    break;
                                case 3: if(crollo_a==1)
                                            aggira(&scavatrice_arvais,&crollo_a);
                                        else{
                                            printf("Non c'è nessun crollo! Forze misteriose ti fanno avanzare!\n\n");
                                            avanza(&scavatrice_arvais,&crollo_a);
                                        }
                                    break;
                                case 4: if((scavatrice_arvais.posizione)->type_caverna==uscita)
                                            esci(&scavatrice_arvais);
                                        else{
                                            printf("Non puoi uscire da una caverna senza uscite!\nForze misteriose ti fanno avanzare!\n\n");
                                            avanza(&scavatrice_arvais,&crollo_a);
                                        }
                                    break;
                                default: printf("Puoi inserire solo uno dei valori consentiti!\n");
                                    break;
                            }
                }
                        if(scavatrice_hartornen.uscita ==0){
                            printf("Turno Hartornen!\nScrivi 1 per avanzare\n2 per abbattere\n3 per aggirare\n4 per uscire.\n\nAttenzione! Puoi aggirare solo nel caso di un crollo e uscire solo in una caverna con l'uscita!\n\n");
                            printf ("Il numero di energia nel tuo serbatoio è:%d\nLa tua melassa raccolta è %d\n\n", scavatrice_hartornen.serbatoio, scavatrice_hartornen.scorta);
                            int scelta;
                            scanf("%d", &scelta);
                            switch (scelta)
                            {   
                                case 1: if(crollo_h==0) 
                                            avanza(&scavatrice_hartornen,&crollo_h);
                                        else{
                                            printf("Non puoi avanzare! Il collegamento è crollato!\nVerrà automaticamente aggirato il crollo\n\n");
                                            aggira(&scavatrice_hartornen,&crollo_h);
                                        }
                                    break;
                                case 2: if(crollo_h==0)
                                            abbatti(&scavatrice_hartornen);
                                        else{
                                            printf("Non puoi abbattere! Il collegamento è crollato!\nVerrà automaticamente aggirato il crollo\n\n");
                                            aggira(&scavatrice_hartornen,&crollo_h);
                                        }
                                    break;
                                case 3: if(crollo_h==1)
                                            aggira(&scavatrice_hartornen,&crollo_h);
                                        else{
                                            printf("Non c'è nessun crollo! Forze misteriose ti fanno avanzare!\n\n");
                                            avanza(&scavatrice_hartornen,&crollo_h);
                                        }
                                    break;
                                case 4: if((scavatrice_hartornen.posizione)->type_caverna == uscita)
                                            esci(&scavatrice_hartornen);
                                        else{
                                            printf("Non puoi uscire da una caverna senza uscite!\nForze misteriose ti fanno avanzare!\n\n");
                                            avanza(&scavatrice_hartornen,&crollo_h);
                                        }
                                    break;
                                default: printf("Puoi inserire solo uno dei valori consentiti!\n");
                                    break;} 
                } 
            } 
        } while(scavatrice_hartornen.serbatoio!=0 && scavatrice_arvais.serbatoio != 0 && (scavatrice_hartornen.uscita != 1 || scavatrice_arvais.uscita !=1));
    if(scavatrice_arvais.uscita == 1 && scavatrice_hartornen.uscita ==1){
        if(scavatrice_arvais.scorta>scavatrice_hartornen.scorta)
            printf("Gli Arvais hanno raccolto più melassa degli Hartornen!\nVincono gli Arvais!\n\n");
        else if(scavatrice_arvais.scorta<scavatrice_hartornen.scorta)
            printf("Gli Hartornen hanno raccolto più melassa degli Arvais!\nVincono gli Hartornen!\n\n");
        else
            printf("Entrambe le scavatrici hanno raccolto la stessa melassa!\nPareggio!\n\n");}
    
    printf("Prima di cominciare una nuova partita sarà cancellata la mappa\n");
    cancella_mappa(&primo_cunicolo_arvais, &last_cunicolo_arvais, &conta_caverne_arv);
    cancella_mappa(&primo_cunicolo_hartornen, &last_cunicolo_hartornen, &conta_caverne_hart);
    mappa = 0; //reset del contatore della mappa

return;}
}

void avanza(struct Scavatrice* Scav, int* crollo){ //avanza dovrà prendere come parametro la scavatrice arvais o hartornen
    int dado = rand()%100+1;
    if ((Scav->posizione)->avanti!= NULL){
        if (dado <= 25){
             *crollo = 1;
             printf("La caverna è crollata! Sei impossibilitato ad avanzare!\nPer continuare dovrai usare aggira\n\n");
             return; //Check di crollo, in caso positivo esci dalla funzione
        }
        else{
             printf ("La scavatrice si è spostata in avanti!\n");
             (Scav->posizione)=(Scav->posizione)->avanti;
             tipo_caverna(Scav);
            }
        }
    else if ((Scav->posizione)->destra != NULL){
            if(dado <=25){
                *crollo = 1;
                printf("La caverna è crollata! Sei impossibilitato ad avanzare!\nPer continuare dovrai usare aggira\n\n");
                return;
                }
            else{
                printf("La scavatrice si è spostata a destra!\n");
                (Scav->posizione)=(Scav->posizione)->destra;
                tipo_caverna(Scav);
                }
        }
    else if ((Scav->posizione)->sinistra != NULL){
            if(dado<=25){
                *crollo=1;
                printf("La caverna è crollata! Sei impossibilitato ad avanzare!\nPer continuare dovrai usare aggira\n\n");
                return;
                }
            else{
                printf("La scavatrice si è spostata a sinistra!\n");
                (Scav->posizione)=(Scav->posizione)->sinistra;
                tipo_caverna(Scav);
                }
        }
    else{
        printf("Questa caverna non ha collegamenti! Verrà ora chiamata la funzione abbatti!\n");
        abbatti(Scav);
    }      
return;
}

void tipo_caverna(struct Scavatrice* controllo){ //funzione per i controlli sul tipo della caverna, melassa eccetera
    if ((controllo->posizione)->imprevisto == baco){
            int dado = rand()%100+1;
                if(dado>=75){
                    printf("Un tremore inquietante anticipa il tuo destino, è apparso un baco delle sabbie e non c'è più niente che tu possa fare!\n\nHai perso!\n\n");
                    (controllo->serbatoio)=0;
                    (controllo->scorta)=0;
                return;
            }
                else
                    printf("Proprio quando pensavi di essere spacciato, un canto amichevole calma il baco, che torna indietro pacificamente (per ora!)\nLa sorellanza delle Rubbioni Gesserit è venuta a salvarti!\nDopo aver ascoltato discorsi riguardanti un certo profeta e la bellezza della matematica, riparti alla ricerca dell'uscita nelle grotte\nSempre che il baco non ti trovi di nuovo...\n");
    }
    else if ((controllo->posizione)->imprevisto == crollo){
        --(controllo->serbatoio);
        printf("La caverna ti crolla addosso! Per riuscire a liberarti sei costretto a consumare un'unità di energia!\n");}
    else
         printf ("Le pareti della caverna sono stabili e sicure\n");
    
    if ((controllo->posizione)->type_caverna == speciale){
            printf("Appena entrato nella caverna provi una sensazione strana ma piacevole, guadagni un'unità di energia!\n");
            ++(controllo->serbatoio);
        }
    else if ((controllo->posizione)->type_caverna == accidentata){
            printf("La tua scavatrice arranca malamente sul terreno accidentato, sei costretto ad usare un'unità di energia per avanzare!\n");
            --(controllo->serbatoio);
        }
    else if ((controllo->posizione)->type_caverna == normale)
            printf("La caverna non ha né pericoli né vantaggi\n");
    else
        printf("Congratulazioni! Questa caverna ha un'uscita!\nInvoca la funzione esci per uscire!\n");
    if ((controllo->posizione)->melassa == nessuna)
        printf("Questa caverna non contiene melassa\n\n");
    else if ((controllo->posizione)->melassa == poca){
            printf("La caverna contiene un'unità di melassa, dove vorresti metterla? Inserisci 1 per il serbatoio di energia o 2 per il serbatoio della raccolta:\n");
            int a;
            do {
                scanf("%d", &a);
                if (a == 1)
                    ++(controllo->serbatoio);
                else if (a ==2)
                    ++(controllo->scorta);
                else
                    printf("Per favore, inserisci soltanto 1 o 2\n");
        }  while (a!= 1 && a!=2);
    }
    else{
        printf("La caverna contiene tantissima melassa! Ben 3 unità! Dove vorresti metterla? Inserisci 1 per il serbatoio dell'energia o 2 per il serbatoio della raccolta:\n");
        int b;
        do {
            scanf("%d", &b);
            if (b == 1)
               (controllo->serbatoio)=(controllo->serbatoio)+3;
            else if (b ==2)
                (controllo->scorta)=(controllo->scorta)+3;
            else
                printf("Per favore, inserisci soltanto 1 o 2\n");
        }
        while (b!= 1 && b!=2);   
    }   
return;
}

void aggira(struct Scavatrice* luogo, int* massi){
    Grotto* inserimento = (Grotto*)malloc(sizeof(Grotto));
    Grotto* arrivo = NULL;
    inserimento->indietro =(luogo->posizione);
    inserimento->avanti=NULL;
    inserimento->destra=NULL;
    inserimento->sinistra=NULL;
    *massi = 0;
    int dado = rand()%100+1;
        if (dado<=50)
            inserimento->imprevisto = nessun_imprevisto;
        else if (dado>50 && dado<=85)
            inserimento->imprevisto = crollo;
        else if (dado>85) 
            inserimento->imprevisto=baco;
    dado = rand()%100+1;
        if (dado<=50)
            inserimento->melassa=nessuna;
        else if (dado>50 && dado<=80)
            inserimento->melassa=poca;
        else if (dado>80)
            inserimento->melassa=molta;
    dado = rand()%100+1;
        if (dado<=20)
            inserimento->type_caverna = accidentata;
        else if (dado>20 && dado<=60)
            inserimento->type_caverna = normale;
        else if (dado>60)
            inserimento->type_caverna = speciale;
        if ((luogo->posizione)->avanti != NULL){
            arrivo = (luogo->posizione)->avanti;
            (luogo->posizione)->avanti = inserimento;
        }
        else if ((luogo->posizione)->destra != NULL){
            arrivo = (luogo->posizione)->destra;
            (luogo->posizione)->destra = inserimento;
        }
        else if ((luogo->posizione)->sinistra != NULL){
            arrivo = (luogo->posizione)->sinistra;
            (luogo->posizione)->sinistra = inserimento;
        }
    (arrivo->indietro) = inserimento;
    inserimento->avanti = arrivo;
    luogo->posizione = inserimento;
    tipo_caverna(luogo);
return;
}
    
void abbatti(struct Scavatrice* check){
if ((check->posizione)-> avanti == NULL || (check->posizione)-> sinistra == NULL || (check->posizione)-> destra == NULL){
    Grotto* inserimento = (Grotto*)malloc(sizeof(Grotto));
    inserimento->indietro = (check->posizione);
    inserimento->avanti=NULL;
    inserimento->destra=NULL;
    inserimento->sinistra=NULL;
    --(check->serbatoio);
    int key = 0;
    int dado = rand()%100+1;
        if (dado<=40)
            inserimento->imprevisto = nessun_imprevisto;
        else if (dado>40 && dado<=80)
            inserimento->imprevisto = crollo;
        else if (dado>80) 
            inserimento->imprevisto=baco;
    dado = rand()%100+1;
        if (dado<=40)
            inserimento->melassa=nessuna;
        else if (dado>40 && dado<=80)
            inserimento->melassa=poca;
        else if (dado>80)
            inserimento->melassa=molta;
    int z = 20;
    int w = 5*turno;
    int b = z+w;
    int u = 100-b;
    int c = u/2;
    int d = z+w+c;
    dado = rand()%100+1;
        if (dado<=20)
            inserimento->type_caverna= accidentata;
        else if (dado>20 && dado<= b)
            inserimento->type_caverna= uscita;
        else if(dado>b && dado<= d)
            inserimento->type_caverna= normale;
        else 
            inserimento->type_caverna = speciale; //Sono tutte per il settaggio del tipo caverna con l'uscita.
do{
   printf("Hai deciso di abbattere una parete! Ricordati che non puoi abbattere in una direzione già aperta!\nInserisci 1 per abbattere avanti, 2 per destra e 3 per sinistra!\n\n");
   scanf("%d", &key);
   switch(key){
       case 1: 
              if((check->posizione)->avanti == NULL){
                  (check->posizione)->avanti = inserimento;
                  (check->posizione)=(check->posizione)->avanti;
                  tipo_caverna(check);
              }
              else{
                  printf("Questa direzione è già aperta!Non puoi abbattere!\n\n");
                  key = 4; //modifico key per non uscire dal ciclo
              }
           break;
       case 2: if((check->posizione)->destra == NULL){
                    (check->posizione)->destra = inserimento;
                    (check->posizione)=(check->posizione)->destra;
                    tipo_caverna(check); //questa è la funzione per le conseguenze degli imprevisti
       }
                else{
                  printf("Questa direzione è già aperta!Non puoi abbattere!\n\n");
                  key = 4;  
                }
           break;
       case 3: if((check->posizione)->sinistra == NULL){
                    (check->posizione)->sinistra = inserimento;
                    (check->posizione)=(check->posizione)->sinistra;
                    tipo_caverna(check);
       }
                else{
                  printf("Questa direzione è già aperta!Non puoi abbattere!\n\n");
                  key = 4;
                }
           break;
   }
}
while(key != 1 && key != 2 && key != 3);    
}
else{
    printf("La caverna ha già tutti i collegamenti possibili aperti\n");
    return;
    }
return;
}
    
void battaglia(struct Scavatrice* arv, struct Scavatrice* hart){
    printf("Le due scavatrici hanno incrociato il loro cammino!\nInizia lo scontro!\n\n");
    do{
        int scelta;
        int dado;
        printf("Turno Arvais!\n\nScegli 1 per attaccare\n2 per provare a rubare 1 un'unità di melassa\n3 per tentare un colpo distruttivo!\n");
        printf("Il numero di energia in tuo possesso è: %d\n", arv->serbatoio);
        scanf("%d", &scelta);
       do{ 
           switch (scelta)
        {
            case 1: dado= rand()%100+1;
                    if(dado<= 50){
                        printf("Hai colpito la scavatrice nemica!\n\n");
                        --(hart->serbatoio);
                    }
                    else
                        printf("Purtroppo il tuo colpo manca il bersaglio!\n\n");
                break;
            case 2: dado = rand()%100+1;
                    if(dado<=35){
                        printf("Il tuo furto va a segno! Rubi un'unità di energia al tuo avversario!\n\n");
                        ++(arv->serbatoio);
                        --(hart->serbatoio); 
                    }
                    else
                        printf("Hai tentato di rubare della melassa ma purtroppo hai fallito!\n\n");
                break;
            case 3: printf("Cominci a pregare il signore del codice, il professor Santini!");
                    dado = rand()%100+1;
                    if(dado<=15){
                        printf("Il sommo Santini ha ascoltato le tue preghiere! Mentre commenta il codice, dereferenzia due volte un puntatore a puntatore per azzerare di nascosto l'energia avversaria!\n\n");
                        hart->serbatoio=0;
                    }
                    else{
                        printf("Il sommo Santini ha ascoltato le tue preghiere! Mentre commenta il codice, dereferenzia due volte un puntatore a puntatore per azzerare di nascosto l'energia avversaria!\nPeccato che a causa di una distrazione del programmatore del gioco l'ultimo puntatore puntasse alla TUA scavatrice!\nHai perso\n\n");
                        arv->serbatoio=0;
                    }
                break;
            default: printf("Inserisci soltanto uno dei valori consentiti!\n");
                     scelta = 4;
                break;}
       } while(scelta != 1 && scelta != 2 && scelta != 3);
        if(hart->serbatoio == 0 || arv->serbatoio ==0)
                break;
        printf("Turno Hartornen!\n\nScegli 1 per attaccare\n2 per provare a rubare 1 un'unità di melassa\n3 per tentare un colpo distruttivo!\n");
        printf("Il numero di energia in tuo possesso è: %d\n", hart->serbatoio);
        scanf("%d", &scelta);
        do{
           switch (scelta)
        {
            case 1: dado= rand()%100+1;
                    if(dado<= 50){
                        printf("Hai colpito la scavatrice nemica!\n\n");
                        --(arv->serbatoio);
                    }
                    else
                        printf("Purtroppo il tuo colpo manca il bersaglio!\n\n");
                break;
            case 2: dado = rand()%100+1;
                    if(dado<=35){
                        printf("Il tuo furto va a segno! Rubi un'unità di energia al tuo avversario!\n\n");
                        ++(hart->serbatoio);
                        --(arv->serbatoio); 
                    }
                    else
                        printf("Hai tentato di rubare della melassa ma purtroppo hai fallito!\n\n");
                break;
            case 3: printf("Cominci a pregare il signore del codice, il professor Santini!\n");
                    dado = rand()%100+1;
                    if(dado<=15){
                        printf("Il sommo Santini ha ascoltato le tue preghiere! Mentre commenta il codice, dereferenzia due volte un puntatore a puntatore per azzerare dii nascosto l'energia avversaria!\n\n");
                        arv->serbatoio=0;
                    }
                    else{
                        printf("Il sommo Santini ha ascoltato le tue preghiere! Mentre commenta il codice, dereferenzia due volte un puntatore a puntatore per azzerare di nascosto l'energia avversaria!\nPeccato che a causa di una distrazione del programmatore del gioco l'ultimo puntatore puntasse alla TUA scavatrice!\nHai perso\n\n");
                        hart->serbatoio=0;
                    }
                break;
            default: printf("Inserisci soltanto uno dei valori consentiti!");
                     scelta = 4;
                break;}
       } while (scelta != 1 && scelta != 2 && scelta != 3);
    } while(arv->serbatoio!=0 && hart->serbatoio!=0);
      printf("Una delle due scavatrici è stata distrutta!\nGame over!\n\n");
return;
} 

void esci(struct Scavatrice* fuga){
    fuga->posizione=NULL;
    fuga->uscita=1;
    printf("Sei riuscito ad uscire dalle grotte, salvandoti dai mille pericoli dei cunicoli di Sabbie!\n\n");
return;
}

void cancella_mappa(Grotto** primo, Grotto** ultimo, int* conta){
    do{ 
        do{ 
            if((*ultimo)->avanti != NULL)
                *ultimo = (*ultimo)->avanti;
            if((*ultimo)->destra != NULL)
                *ultimo = (*ultimo)->destra;
            if((*ultimo)->sinistra != NULL)
                *ultimo= (*ultimo)->sinistra;
        } while((*ultimo)->avanti != NULL || (*ultimo)->destra != NULL || (*ultimo)->sinistra != NULL);
        
        Grotto* bomba = *ultimo;
        *ultimo = (*ultimo)-> indietro;
            if((*ultimo)->avanti == bomba)
                (*ultimo)->avanti = NULL;
            else if ((*ultimo)->destra == bomba)
                (*ultimo)->destra = NULL;
            else if ((*ultimo)->sinistra == bomba)
                (*ultimo)->sinistra = NULL;
        printf("La caverna %p sta per essere distrutta\n", bomba);
        free(bomba);
        bomba = NULL;
    } while((*primo)->avanti != NULL || (*primo)->destra != NULL || (*primo)->sinistra !=NULL);
    *ultimo = NULL;
    printf("Verrà ora abbattuta la testa %p\n", *primo);
    free(*primo);
    *primo = NULL;
    *conta = 0;  
    printf("Il cunicolo è stato correttamente cancellato!\n\n");
return;    
}