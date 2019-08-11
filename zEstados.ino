/******************************************************************************/
/************** FUNCIÓN PARA CAMBIAR DE ESTADO Y MOSTRAR MSJS *****************/
/******************************************************************************/
void CambiarEstado(int sigEstado) {
  switch (sigEstado) {
    case estadoPrueba:
      log(F("EdoPrueba"), logNoticia);
      break;
    case estadoError:
      log(F("EdoError"), logNoticia);
      break;
    case estadoConfiguracion:
      log(F("EdoConfiguracion"), logNoticia);
      break;
    case estadoConexionWiFi:
      log(F("EdoConexionWiFi"), logNoticia);
      break;
    case estadoEspera:
      log(F("EdoEspera"), logNoticia);
      break;
    case estadoSinEstado:
    default:  //Llamado de un Estado que no existe
      log(F("EdoNoDeclarado"), logError);
      sigEstado = estadoError;
  }
  Estado = sigEstado;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void EstadoPrueba() {
  // Espera 5 segundos
  if (millis() - tiempoAnt > 5000) {
    tiempoAnt = millis();
    CambiarEstado(estadoEspera);
  }
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void EstadoError() {
  // Esperar 5 segundos
  if (millis() - tiempoAnt > 4500) {
    tiempoAnt = millis();
    CambiarEstado(estadoError);
  }
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
void EstadoConfiguracion() {
  A1ConfGeneral();
  A2ConfLog();
  A3Config();
  M1ConfWiFiManager();
  CambiarEstado(estadoConexionWiFi);
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void EstadoEspera() {  
  if (millis() - tSegAnt > 5000) {
    segundos++;
    log(F("(EdoEspera)."), logNoticia);
    tSegAnt = millis();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void EstadoConexionWiFi() {
  // Si no esta conectado
  if (WiFi.status() != WL_CONNECTED) {
    //Iniciamos la conexion con WiFiManager
    if (!wm.autoConnect()) {
      // Si no se conecto
      log(F("(EdoConexionWiFi)Se reinicia para intentar de nuevo"), logError);
      //Resetea y se intenta de nuevo
      ESP.reset();
      delay(1000);
    }
  }
  // Si llegó aquí es esta conectado, cambiamos de estado
  CambiarEstado(estadoEspera);
}
