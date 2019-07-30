/*****************************************************************************/
/******************* ESTRUCTURA DE PROPIEDADES DEL AUTOMATA ******************/
/*****************************************************************************/
struct DatosPuertaBot {
  /********************************** A2Log **********************************/
  int verbosidad;             // Nivel de verbosidad
  /************************* Descripción de variable *************************/
  // Espacio para definir variables
  unsigned long tiempoError;
};

/*****************************************************************************/
/************** CONFIGURACIÓN INICIAL DE TERMINALES Y VARIABLES **************/
/*****************************************************************************/
DatosPuertaBot Datos;    //Variable global de propiedades del Vochobot
unsigned long tiempoAnt;//(ms) Variable auxiliar para medir tiempo
unsigned long tEsperaAnt;//(ms) Variable auxiliar para medir tiempo
unsigned long tErrorAnt;//(ms) Variable auxiliar en medir tiempo de estado Error
unsigned long tSegAnt;  // Variable auxiliar para contar segundos
int segundos;           // Variable auxiliar para contar segundos


void A1ConfGeneral() {
  // Reiniciando variables
  tiempoAnt = millis();
  tSegAnt = millis();
  tEsperaAnt = millis();
  randomSeed(millis());
  Datos.tiempoError = 35000;
  Datos.verbosidad = 7;
}

// Envia información del automáta
void A1Informacion() {
  Serial.print(F("!Modelo:"));
  Serial.println(modelo);
  Serial.print(F("!Firmware:"));
  Serial.println(firmware);
  Serial.print(F("!Serie:"));
  Serial.println(numSerie);
}

// Envia la información de los datos del autómata
void InfoGeneral() {
  Serie.println(F("------INFO------"));
  Serie.print(F("!EdoActual="));
  Serie.println(Estado);
  InfoWiFi();
  Serie.println(F("------INFO------"));
}
