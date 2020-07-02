enum Tipo_imprevisto {nessun_imprevisto, crollo, baco };
enum Quantita_melassa {nessuna, poca, molta=3};
enum Tipo_caverna {normale, speciale, accidentata, uscita};

void crea_cunicoli();
void gioca();

struct Caverna {
    struct Caverna* avanti;
    struct Caverna* destra;
    struct Caverna* sinistra;
    struct Caverna* indietro;
    enum Tipo_imprevisto imprevisto;
    enum Quantita_melassa melassa;
    enum Tipo_caverna type_caverna;
};

struct Scavatrice{
    struct Caverna* posizione;
    unsigned char serbatoio; //energia della scavatrice
    unsigned char scorta;
    int uscita; //flag per lo stato di uscita
};

typedef struct Caverna Grotto;

