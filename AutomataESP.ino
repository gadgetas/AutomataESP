/******************************************************************************/
/**************************** NOMBRE DEL PROYECTO *****************************/
/******************************************************************************/
/** Aquí redacta la descripción del programa, esta debe ser concisa, un      **/
/** resumen general que explique el alcance y finalidad del programa         **/
/**   Placa Hardware:      ESP8266 Generico || Para que hardware se programa **/
/**   Versión IDE Arduino: 1.8.9            || Versión con que se desarrolla **/
/******************************************************************************/
/** Version 0.1.190729 || Esta es la versión actual, se usa la semántica para
/**                       los dos primero números y en el último la fecha AAMMDD
/**
/** Última revisión:   || Ultima revisión o actualización, solo la última
/** 19/03/06 Augusto - Agregan leds de monitoreo
/******************************************************************************/
const String modelo = "Atm01";
const String firmware = "0.1.1";
const String numSerie = "000001";

// Definimos puerto serial para Comunicación
#define Serie Serial
#define SerialLog_bps 115200

// Definimos puerto serial para LOG
#define SerialLog Serial
#define SerialLog_bps 115200

/******************************************************************************/
/*************************** DECLARACIÓN DE ESTADOS ***************************/
/******************************************************************************/
const int estadoPrueba = -2;      // Estado usado para pruebas
const int estadoError = -1;       // Estado principal de manejo de errores
const int estadoSinEstado = 0;    // Usado para error en declaración de estado
const int estadoConfiguracion = 1;// Estado de configuración inicial
const int estadoConexionWiFi = 2; // Estado de conexión a un AP
const int estadoEspera = 3;       // Estado de espera
int Estado; // Variable global que contiene el estado actual

/******************************************************************************/
/*************************** INICIALIZACIÓN GENERAL ***************************/
/******************************************************************************/
void setup() {
  /****SI ES DIFERENTE EL PUERTO DEL LOG***/
  SerialLog.begin(SerialLog_bps);
  A1Informacion();
  Estado = estadoConfiguracion;
  CambiarEstado(estadoConfiguracion);
}

/******************************************************************************/
/*************** ESTRUCTURA PRINCIPAL DE LA MÁQUINA DE ESTADOS ****************/
/******************************************************************************/
void loop() {
  LeerIndicaciones();
  switch (Estado) {
    case estadoPrueba:
      EstadoPrueba();
      break;
    case estadoError:
      EstadoError();
      break;
    case estadoConfiguracion:
      EstadoConfiguracion();
      break;
    case estadoConexionWiFi:
      EstadoConexionWiFi();
      break;
    case estadoEspera:
      EstadoEspera();
      break;
    default:
      CambiarEstado(estadoSinEstado);
      break;
  }
}
/**************************************||**************************************/
