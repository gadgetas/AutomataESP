/******************************************************************************/
/**** MÓDULO DE ASIGNACIÓN DE DOMINIO LOCAL Y DESCUBRIMIENTO DE SERVICIOS *****/
/******************************************************************************/
/** El protocolo mDNS (multiCast DNS) ayuda a resolver nombres locales de    **/
/** de dominio, en redes que no incluyen un servidor de nombres. Tales como  **/
/** las redes privadas de casa.                                              **/
/**                                                                          **/
/** mDNS es un servicio Zeroconf que, esencialmente, emplea un funcionamiento**/
/** similar a las DNS. Este protocolo se basa en el RFC 6762, y usa multicast**/
/** de paquetes UDP. Es compatible y trabaja con los servidores DNS.         **/
/**                                                                          **/
/** Cuando un cliente mDNS necesita resolver un nombre de host, envía un     **/
/** mensaje multicast preguntando a los equipos de red que al host que tenga **/
/** ese nombre que se identifique. Esa máquina de destino luego transmite un **/
/** mensaje que incluye su dirección IP. Todas las máquinas en esa subred    **/
/** pueden usar esa información para actualizar sus cachés mDNS.             **/
/**                                                                          **/
/** De manera predeterminada, mDNS resuelve única y exclusivamente los       **/
/** nombres de host que terminan con el dominio de nivel superior (TLD)      **/
/** .local. por lo que solo responde mensajes multicast DNS solicitando      **/
/** nombres de dominios locales como “foo.local”.                            **/
/**                                                                          **/
/** Adicionalmente contien un mecanismo para descubrir servicios (SD).       **/
/******************************************************************************/

/******************************************************************************/
/******************** TERMINALES USADAS POR EL MÓDULO WIFI ********************/
/******************************************************************************/
// No se usan terminales

/******************************************************************************/
/************** VARIABLES GLOBALES PARA LA CONEXIÓN POR DEFECTO ***************/
/******************************************************************************/

/******************************************************************************/
/*********************** CONFIGURACIÓN INICIAL DEL MÓDULO *********************/
/******************************************************************************/
void M2ConfmDNS() {
  // Configuramos los datos del servicio de descubrimiento mDNS
  log(F("(mDNS-SD)Configurando"), logInfo);
  // Creamos el dominio por defecto, este lo va a sobreescribir el modulo de
  // de configuración si existe en el archivo config.json
  String dominio = modelo + ESP.getChipId();
  dominio.toLowerCase();
  // Establece el nombre del dominio
  strlcpy(Datos.dominio, dominio.c_str(), 64);
  // Nombre del servicio ofrecido

  // Puerto donde se ofrece el servicio

}

/******************************************************************************/
/*************************** INICIAR EL SERVICIO MDNS *************************/
/******************************************************************************/
boolean M2StartmDNS() {
  // Configuramos los datos de nuestra red WiFi
  log(F("(mDNS-SD)Iniciando..."), logInfo);
  // Debe ser ejecutada despues de que haya conectado a una red.
  if (WiFi.status() != WL_CONNECTED) {
    log(F("(mDNS-SD)Debe estar conectado a una red WiFi"), logError);
    return false;
  }
  // Inicializa el servicio con el dominio guardado en datos
  if (!MDNS.begin(Datos.dominio)) {
    log(F("(mDNS-SD)Fallo al iniciar mDNS responder"), logError);
    return false;
  }
  else {
    log(F("(mDNS-SD)Dominio local asignado "), Datos.dominio, logNoticia);
  }
  // Announce esp tcp service on port 8080
  MDNS.addService("Gld-Unadin", "tcp", 3000);
  return true;
}

/******************************************************************************/
/**************************************||**************************************/
/******************************************************************************/
void M2mDNSInfo() {
  Serie.println(F("------mDNS DISCOVERY SERVICE------"));
  Serie.print(F("!Domain="));
  Serie.print(Datos.dominio);
  Serie.println(".local");
}

/******************************************************************************/
/**************************************||**************************************/
/******************************************************************************/
void M2mDnsComando(){  
  String nvoDominio = Serial.readStringUntil('\n');
  M2mDnsDominio(nvoDominio);
}

/******************************************************************************/
/**************************************||**************************************/
/******************************************************************************/
void M2mDnsDominio(String nuevoDominio) {
  // Verifica si tiene menos de 64 caracteres
  if (nuevoDominio.length() <= sizeof(Datos.dominio)) {
    /*Como copiar un string*/
    strlcpy(Datos.dominio,                  // <- destination
            nuevoDominio.c_str(),  // <- source
            sizeof(Datos.dominio));         // <- destination's capacity
    Serie.print(F("!Domain="));
    Serie.print(Datos.dominio);
    Serie.println(".local");
    log(F("(mDNS-SD)Salva y reinicia para aplicar cambios"), logAdvertencia);
  } else {
    log(F("(mDNS-SD)Dominio mayor a 64 caracteres"), logError);
  }
}
