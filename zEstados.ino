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
    default:  //Llamano un Estado que no existe 
      log(F("EdoNoDeclarado"), logError);      
      // Cambiamos a un estado de error
      log(F("EdoError"), logNoticia);
      sigEstado=estadoError;
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
  A2ConfLog();
  A1ConfGeneral();
  M1ConfWiFiManager();
  CambiarEstado(estadoConexionWiFi);
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void EstadoEspera() {
  // En este estado espera los comandos del Arduino
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void EstadoConexionWiFi() {
  // Si esta conectado, cambiamos de estado
  if (wifiMulti.run() == WL_CONNECTED) {
    log(F("(WiFi)Conectado a WiFi"), logNoticia);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("IP:\t");
    Serial.println(WiFi.localIP());
    CambiarEstado(estadoEspera);
  }
  if (millis() - tSegAnt > 1000) {
    segundos++;
    log(F("(WiFi)."), logDebug);
    tSegAnt = millis();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(20);
    digitalWrite(LED_BUILTIN, LOW);
  }
}
