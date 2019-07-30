/*****************************************************************************/
/************** FUNCIÓN PARA CAMBIAR DE ESTADO Y MOSTRAR MSJS ****************/
/*****************************************************************************/
void CambiarEstado(int sigEstado) {
  switch (sigEstado) {
    case estadoPrueba:
      log(F("EdoPrueba"), logNoticia);
      break;
    case estadoError:
      log(F("EdoError"), logNoticia);
      break;
    case estadoDesconectado:
      log(F("EdoDesconectado"), logNoticia);
      break;
    case estadoConfiguracion:
      log(F("EdoConfiguracion"), logNoticia);
      break;
    case estadoConexionWiFi:
      log(F("EdoConexionWiFi"), logNoticia);
      log("(WiFi)Conectando a la red WiFi SF", logDebug);
      // Iniciamos un contador de segundos
      tSegAnt = millis();
      segundos = 0;
      break;
    case estadoEspera:
      log(F("EdoEspera"), logNoticia);
      break;
    default:
      log(F("Estado no valido"), logError);
      break;
  }
  Estado = sigEstado;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void EstadoPrueba() {
  // Esperar 5 segundos mostrando la pantalla de inicio
  if (millis() - tiempoAnt > 5000) {
    tiempoAnt = millis();
    CambiarEstado(estadoEspera);
  }
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void EstadoError() {
  // Si ya ha pasado 2 segundo, apaga el buzzer
  if (millis() - tiempoAnt > 2000) {
    //buzzer(false);
  }
  // Esperar 5 segundos mostrando la pantalla de inicio
  if (millis() - tiempoAnt > 4500) {
    tiempoAnt = millis();
    CambiarEstado(estadoError);
  }
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void EstadoDesconectado() {
  // Esperar 5 segundos mostrando la pantalla de inicio
  if (millis() - tiempoAnt > 5000) {
    tiempoAnt = millis();
    CambiarEstado(estadoEspera);
  }
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void EstadoConfiguracion() {
  A2ConfLog();
  A1ConfGeneral();
  ConfWiFi();
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
