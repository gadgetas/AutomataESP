/******************************************************************************/
/*********************** MÓDULO DE BITACORA Y MENSAJES ************************/
/******************************************************************************/
/** Funcionalidad para depuracion de código auxiliar                         **/
/** en la generación de mensajes considerando grados                         **/
/** de severidad, de acuerdo a RFC5424                                       **/
/**  0     Emergencia: ESP no es funcional system is unusable                **/
/**  1     Alerta: Se deben tomar acciones inmediatas                        **/
/**  2     Critico: Surgen condiciones de funcionamiento critico             **/
/**  3     Error: Surgen condiciones de errores                              **/
/**  4     Advertencia: Surgen condiciones de advertencia (warning)          **/
/**  5     Noticia: Infomación normal pero relevante                         **/
/**  6     Informacion: Mensajes informativos                                **/
/**  7     Debug: Mensajes de depuración y desarrollo del programa           **/
/******************************************************************************/
#define logEmergencia 0
#define logAlerta 1
#define logCritico 2
#define logError 3
#define logAdvertencia 4
#define logNoticia 5
#define logInfo 6
#define logDebug 7

/******************************************************************************/
/********************* VARIABLES GLOBALES PARA DEPURACIÓN *********************/
/******************************************************************************/
String logMsj;
int verbosidadAnt;

/******************************************************************************/
/******** CONFIGURACIÓN INICIAL DE TERMINALES Y VARIABLES **********/
/******************************************************************************/
void A2ConfLog() {
  // Modo desarrollo: 7
  // Modo producción: 3
  Datos.verbosidad = logDebug;
  verbosidadAnt = logDebug;
  logMsj = String(F("!LOG"));
}

/******************************************************************************/
/******************************************************************************/
void A2LogInfo() {
  Serie.print(F("!Verbosidad="));
  Serie.println(Datos.verbosidad);
}

/******************************************************************************/
/********** ENVIA UN MENSAJE POR EL PUERTO DE VALORES DE VARIABLES ************/
/******************************************************************************/
void log(String msj, int grado) {
  if (grado > Datos.verbosidad)
    return;
  SerialLog.println(logMsj + grado + "-" + msj);
}

void log(String msj, String valor, int grado) {
  if (grado > Datos.verbosidad)
    return;
  SerialLog.println(logMsj + grado + "-" + msj + valor);
}

void log(String msj, int valor, int grado) {
  if (grado > Datos.verbosidad)
    return;
  SerialLog.print(logMsj + grado + "-" + msj);
  SerialLog.println(valor);
}


/******************************************************************************/
/******************* Define el grado de verbosidad en el log ******************/
/******************************************************************************/
void LogComando()
{
  // Leemos los grados Celcius
  String parametro = Serie.readStringUntil('\n');
  // Convertimos de texto a entero
  int valor = parametro.toInt();
  SetVerbosidad(valor);
}

/******************************************************************************/
/**************************************||**************************************/
/******************************************************************************/
void SetVerbosidad(int grado) {
  verbosidadAnt = grado;  //Auxiliar para la función LogDebug()
  Datos.verbosidad = grado;
  if (Datos.verbosidad > logDebug)
    Datos.verbosidad = logDebug;
  if (Datos.verbosidad < logEmergencia)
    Datos.verbosidad = logEmergencia;
  Serie.println(logMsj + "=" + Datos.verbosidad);
}

/******************************************************************************/
/******************** CAMBIO RÁPIDO Y TEMPORAL A MODO DEBUG *******************/
/******************************************************************************/
void LogDebug() {
  //Switchea entre los mensajes debug y el que tiene establecido
  if (Datos.verbosidad != logDebug) {
    Datos.verbosidad = logDebug;
    Serie.println(F("----------- MODO DEPURACION ------------"));
  }
  else {
    Datos.verbosidad = verbosidadAnt;
    Serie.println(F("--------- FIN MODO DEPURACION ----------"));
  }
}
/**************************************||**************************************/
