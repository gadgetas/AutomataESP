/******************************************************************************/
/**************************************||**************************************/
/******************************************************************************/
void MenuComandos() {
  Serie.println(F("----------- MENU DE COMANDOS -----------"));
  Serie.println(F("X:(Modulo): Comando a ejecutar"));
  Serie.println(F("S:(Config): Salva los cambios en config.json"));
  if (Datos.verbosidad == logDebug)
    MenuComandosDesarrollo();
}

/******************************************************************************/
/**************************************||**************************************/
/******************************************************************************/
void MenuComandosDesarrollo() {
  Serie.println(F("I:(AYUDA)Obtiene ayuda del comando"));
  Serie.println(F("Ln:(LOG) Establece verbosidad"));
  Serie.println(F("*:(WiFiManager) Borra red guardada y reinicia"));
}

/******************************************************************************/
/**************************************||**************************************/
/******************************************************************************/
void MenuInformacion(){
  Serie.println(F("---- MENU DE INFORMACION DE VALORES ----"));
}
