********************************************************************************
/* NOMBRE DEL PROYECTO
 *  
 *  En esta parte esta la descripción del programa, debemos ser concisos, 
 *  redactar un resumen general que explique el alcance y finalidad del programa
 *  
 *  Version 0.1.190729 || Esta es la versión semántica para los dos primero nú-
 *                        meros y en el último la fecha AAMMDD
 *  Placa Arduino: Arduino Pro Mini || Para que hardware se programa
 *
 *  Última revisión:   || Ultima revisión o actualización, solo la última
 *  19/03/06 Augusto - Agregan leds de monitoreo  
 */
const String modelo="Atm01";
const String firmware="0.1.1";
const String numSerie="1";

// Definimos puerto serial para Comunicación
#define Serie Serial
#define SerialLog_bps 9600

// Definimos puerto serial para LOG
#define SerialLog Serial
#define SerialLog_bps 9600

// Definición de estados
const int estadoPrueba=-3;        // Estado usado para pruebas
const int estadoError=-2;         // Estado usado para pruebas
const int estadoDesconectado = -1;// Estado de puerto serial desconectad
// Modulo Alcancia
const int estadoConfiguracion = 0;// Estado Abriendo el mecanismo
const int estadoConexionWiFi = 1; // Estado inicial
const int estadoEspera = 2;       // Estado Cerrando el mecanismo

int Estado;

void setup() {
  /****SI ES DIFERENTE EL PUERTO DEL LOG***/
  SerialLog.begin(SerialLog_bps);
  A1Informacion();
  Estado = estadoConfiguracion;
  CambiarEstado(estadoConfiguracion);
}

void loop() {
  LeerIndicaciones();  
  switch (Estado) {
    case estadoPrueba:
      EstadoPrueba();
      break;
    case estadoError:
      EstadoError();
      break;
    case estadoDesconectado:
      EstadoDesconectado();
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
      // if nothing else matches, do the default
      // default is optional
      break;
  }
}
