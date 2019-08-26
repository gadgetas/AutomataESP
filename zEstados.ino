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
    case estadoConfigMDns:
      log(F("EstadoConfigMDns"), logNoticia);
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
  if (M3StartWebServer())
    CambiarEstado(estadoEspera);
  else
    CambiarEstado(estadoError);
  /*
    // Espera 5 segundos
    if (millis() - tiempoAnt > 10000) {
    tiempoAnt = millis();

    // Buscamos los dispositivos con el servicio
    // String servidores=M2mDnsDescubrirServicio("Gld-Unicon", "tcp");

    // Obtenemos el primero de ellos
    /*int pos=servidores.indexOf(",");
    if(pos==-1){ // Solo es uno

    }
    IPAddress ip;
    if (!WiFi.hostByName("AugusGamer.local", ip)) { // Get the IP address of the NTP server
      Serial.println("DNS lookup failed. Rebooting.");
    }
    else {
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      Serial.print("IP resuelta por hostByName ");
      Serie.println(ipStr);
    }
    }*/
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
  M1ConfWiFiManager();
  M2ConfmDNS();
  M3ConfWebServer();
  // Al último carga la configuración guardada de todos los módulos
  A3Config();
  CambiarEstado(estadoConexionWiFi);
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void EstadoEspera() {
  webServer.handleClient();
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);

  if (millis() - tSegAnt > 30000) {
    segundos++;
    log(F("(EdoEspera)."), logInfo);
    tSegAnt = millis();
  }
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void EstadoConexionWiFi() {
  // Si no esta conectado
  if (WiFi.status() != WL_CONNECTED) {
    String ssid = modelo + String(ESP.getChipId());
    // Iniciamos la conexion con WiFiManager, función bloqueante, Si no hay
    // nadie conectado y pasan 3 min se sale del portal de configuración
    if (!wm.autoConnect(ssid.c_str(), passwordAP.c_str())) {
      // Si no se conecto
      log(F("(EdoConexionWiFi)Se reinicia para intentar de nuevo"), logError);
      //Resetea y se intenta de nuevo
      ESP.reset();
      delay(1000);
    }
  }
  // Si llegó aquí ya esta conectado, cambiamos de estado
  CambiarEstado(estadoConfigMDns);
}


void EstadoConfigMDns() {
  // Si se configura correctamente pasa al siguiente estado
  if (M2StartmDNS())
    CambiarEstado(estadoPrueba);
  else
    CambiarEstado(estadoError);
}
