
long distanceLeft,distanceMiddle,distanceRight; // variabili contenenti le distanze rilevate dai 3 sonar 
boolean someone = FALSE; // booleano che indica la presenza o meno dell'utente

void setup() {
  
  // Inizializzazione dei motori e dei vari componenti
  // Settaggio dei pin di OUTPUT ed INPUT

}

void loop() {

  cin_cin_dance(); 
  cin_cin_engagement();
  if(someone)
    cin_cin_menu();
  if(someone)
    cin_cin_selfie();  
}

void cin_cin_dance(){

  // Funzione che fa ballare Cin Cin con musica cinese di sottofondo
  // Mentre balla rileva se passa qualcuno entro 2 metri c.a.
  // Quando rileva qualcuno si fermano i motori, la musica e la funzione ritorna dopo aver settato il flag someone a TRUE 
  
}

void cin_cin_engagement(){

  // Funzione che fa compiere la prima interazione con l'utente
  // Cin Cin chiama verso di se l'utente e se rileva un avvicinamento si presenta per poi fare un inchino
  // Se l'utente è ancora lì allora la funzione ritorna, altrimenti viene settato il flag somene a FALSE prima di ritornare
  
}

void cin_cin_menu(){

  // Funzione che fa presentare il ristorante e offrire il menù all'utente
  // Cin Cin presenta il ristorante all'utente per poi invitarlo a dare un'occhiata al menù facendo un inchino
  // Se l'utente non prende il menù allora Cin Cin si rialza e verifica che l'utente sia ancora lì, ed eventualmente setta il flag someone a FALSE prima di ritornare
  // Se l'utente è ancora lì riprova ad offrirgli il menù, se non viene preso nemmeno questa volta la funzione ritorna
  // Se l'utente prende il menù Cin Cin resta inchinato fino a che non viene rimesso a posto, per poi ritornare dopo aver eventualmente settato il flag someone
  
}

void cin_cin_selfie(){

  // Funzione che fa scattare un selfie con l'utente ed invia la foto in cassa tramite Wi-Fi
  // Cin Cin chiede all'utente di scattarsi un selfie con lui e si gira alzando il bambù, invitandolo a premere il cappello per scattare la foto
  // Se l'utente non preme il cappello allora Cin Cin lo invita nuovamente a schiacciare il cappello non appena è pronto
  // Sia che l'utente prema o non prema il cappello, Cin Cin si rimette in posizione normale ed eventualmente setta il flag someone a FALSE prima di ritornare
  
}

// -------------- HELPER FUNCTIONS --------------

void bow_down(){

  // Funzione che fa inchinare Cin Cin
  
}

void bow_up(){

  // Funzione che fa rialzare Cin Cin dall'inchino
  
}

void selfie_rotation(){

 // Funzione che alza il braccio e fa ruotare Cin Cin per scattare il selfie 
  
}

void get_distance(){

  // Funzione che rileva le distanze percepite dai sonar e le colloca nelle apposite variabili globali
  
}

void is_there_someone(){

  // Funzione che setta il booleano di presenza utente someone
  
}



