Nome: Debora
 
Cognome: Damiani

Matricola: 325436 

Nel mio progetto Sabbie ci sono alcune aggiunte rispetto alla traccia originale.
La prima aggiunta è la presenza di un puntatore in più nella creazione delle caverne, tale puntatore non serve per tornare indietro ma ha utilità meramente strutturale (per semplificarmi la funzione di cancellazione dei nodi ad esempio).
Ci sono poi varie variabili globali, due per tener traccia del numero di caverne create (in modo tale da non poter uscire dalla creazione mappa se esse sono infieriori a 10), due invece tengono conto di eventuali crolli all'interno delle grotte (impedendoti di avanzare nel caso si sia verificato un crollo) e l'ultima è semplicemente una variabile mappa, modificata dalla funzione chiudi cunicoli (se ci sono 10 caverne a giocatore, mappa passa a 1).
Ho creato il progetto per far sì che si possa rientrare (prima di giocare!) quante volte si voglia nella creazione e aggiungere o cancellare altre caverne, tuttavia se si scende sotto le 10 caverne a giocatore viene preclusa nuovamente la possibilità di uscire dalla creazione.
C'è poi un campo in più in struct Scavatrice rappresentato dall'uscita, utilizzato nel caso la scavatrice esca dal cunicolo.
Un piccola modifica nel caso di attacco del baco è un piccolo easter egg, viene randomicamente lanciato un dado e, se si ha fortuna, la sorellanza delle Rubbioni Gesserit interverrà nell'attacco, permettendoti di sopravvivere.
Nel caso un giocatore provasse a uscire in una caverna senza uscite, aggirare senza un crollo eccetera il mio progetto lo "costringe" a fare la scelta giusta invocando la funzione corretta, in modo tale da non "perdere" il turno.
Non esiste la funzione termina_gioco(), la deallocazione della memoria viene chiamata automaticamente alla fine di gioca()
 e vengono stampate tutte le caverne cancellate per ogni giocatore.
Il combattimento finale si svolge con un piccolo scontro a turni basati sul tiro di dado, dove si ha la possibilità di attaccare l'avversario, rubargli l'energia dal serbatoio oppure di invocare il Sommo per provare a distruggere la scavatrice avversaria. Lo scontro si conclude appena una delle due scavatrici scende a zero di energia.
