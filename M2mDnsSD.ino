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
boolean M2ConfmDNS() {
  // Configuramos los datos de nuestra red WiFi
  log(F("(mDNS-SD)Configurando"), logInfo);
  // Debe ser ejecutada despues de que haya conectado a una red.
  if (WiFi.status() != WL_CONNECTED) {
    log(F("(mDNS-SD)Debe estar conectado a una red WiFi"), logError);
    return false;
  }
  // Establece el nombre del dominio
  // String dominio = modelo + String(ESP.getChipId());
  char dominio[16] = {0};
  sprintf(dominio, "ESP_%06X", ESP.getChipId());
  if (!MDNS.begin(dominio)) {
    log(F("(mDNS-SD)Fallo al iniciar mDNS responder"), logError);
    return false;
  }
  else {
    log(F("(mDNS-SD)Dominio local asignado"), logError);
  }
  // Announce esp tcp service on port 8080
  MDNS.addService("Gld-device", "tcp", 8080);
  return true;
}
