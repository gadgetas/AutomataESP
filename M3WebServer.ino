/******************************************************************************/
/*************************** MÓDULO DE SERVIDOR WEB ***************************/
/******************************************************************************/
/** Este módulo creamos un servidor web usando la biblioteca ESP8266WebServer**/
/** como desventaja solo atiende un cliente a la vez, así como peticiones GET**/
/** y POST. Por defecto se levanta en el puerto 80.                          **/
/**                                                                          **/
/** La raíz de los archivos públicos web, se deben almacenar en la memoria   **/
/** FLASH dentro de la carpeta public. Se debe tener precaución que el nombre**/
/** más la ruta del archivo no pase de 31 caracteres (Limitado por SPIFFS)   **/
/**                                                                          **/
/** Se deben de configurar las rutas de petición, los métodos disponibles que**/
/** son HTTP_ANY, HTTP_GET, HTTP_HEAD, HTTP_POST, HTTP_PUT, HTTP_PATCH,      **/
/** HTTP_DELETE, HTTP_OPTIONS y la forma de tratar estas peticiones          **/
/**                                                                          **/
/******************************************************************************/

/******************************************************************************/
/******************** TERMINALES USADAS POR EL MÓDULO WIFI ********************/
/******************************************************************************/
// No se usan terminales

/******************************************************************************/
/************** VARIABLES GLOBALES PARA LA CONEXIÓN POR DEFECTO ***************/
/******************************************************************************/
ESP8266WebServer webServer(80);
File fsUploadFile;
const char* www_username = "admin";
const char* www_password = "admin";

/******************************************************************************/
/*************** CONFIGURACIÓN INICIAL DE TERMINALES Y VARIABLES **************/
/******************************************************************************/
void M3ConfWebServer() {
  // Configuramos los datos de nuestra red WiFi
  log(F("(WebServer)Configurando"), logNoticia);

  // Rutas con autorización básica
  webServer.on("/", []() {
    if (!M3UsuarioAutenticado())
      return;
    if (!M3LeerArchivoWeb("/web/dash.html"))
      M3RecursoNoEncontrado();
  });

  webServer.on("/login", M3Login);

  webServer.on("/js/bootstrap.bundle.min.js.map", HTTP_GET, []() {
    if (!M3LeerArchivoWeb("/web/js/bootstrap.map"))
      webServer.send(404, "text/plain", "FileNotFound");
  });

  webServer.on("/css/bootstrap.min.css.map", HTTP_GET, []() {
    if (!M3LeerArchivoWeb("/web/css/bootstrap.map"))
      webServer.send(404, "text/plain", "FileNotFound");
  });

  log(F("(WebServer)Agregando rutas estaticas"), logInfo);
  webServer.serveStatic("/js", LittleFS, "/web/js", "max-age=86400");
  webServer.serveStatic("/css", LittleFS, "/web/css", "max-age=86400");
  webServer.serveStatic("/img", LittleFS, "/web/img", "max-age=86400");

  // Configuración de rutas y métodos por defecto
  // Cuando no existe una ruta definida,lo busca en el sistema de archivos
  webServer.onNotFound([]() {
    // Si no lo encuentra en la memoria flash, envía un error 404
    if (!M3LeerArchivoWeb("/web" + webServer.uri())) {
      M3RecursoNoEncontrado();
    }
  });

  // Lista de cabecera a ser registrada
  const char * headerkeys[] = {"User-Agent", "Cookie"} ;
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
  // ask server to track these headers
  webServer.collectHeaders(headerkeys, headerkeyssize);
}

/******************************************************************************/
/**************************************||**************************************/
/******************************************************************************/
bool M3StartWebServer() {
  log(F("(WebServer)Iniciando..."), logInfo);
  // Debe ser ejecutada despues de que haya conectado a una red.
  if (WiFi.status() != WL_CONNECTED) {
    log(F("(WebServer)Debe estar conectado a una red WiFi"), logError);
    return false;
  }
  // Se inicia el servicio
  webServer.begin();
  return true;
}

/******************************************************************************/
/**************************************||**************************************/
/******************************************************************************/
void M3RecursoNoEncontrado() {
  // Se dispara cuando no existe la ruta del recurso pedido
  log(F("(WebServer)Recurso no encontrado"), webServer.uri(), logError );
  String mensaje = "Archivo no encontrado\n\nURI: ";
  mensaje += webServer.uri();
  mensaje += "\nMethod: ";
  mensaje += (webServer.method() == HTTP_GET) ? "GET" : "POST";
  mensaje += "\nArguments: ";
  mensaje += webServer.args();
  mensaje += "\n";
  for (uint8_t i = 0; i < webServer.args(); i++) {
    mensaje += " " + webServer.argName(i) + ": " + webServer.arg(i) + "\n";
  }
  webServer.send(404, "text/plain", mensaje);
}

bool M3LeerArchivoWeb(String path) {
  log(F("(WebServer)Obteniendo archivo"), path, logInfo);
  if (path.endsWith("/")) {
    path += "index.html";
  }
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if (LittleFS.exists(pathWithGz) || LittleFS.exists(path)) {
    if (LittleFS.exists(pathWithGz)) {
      path += ".gz";
    }
    File file = LittleFS.open(path, "r");
    webServer.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}

void M3SubirArchivoWeb() {
  HTTPUpload& upload = webServer.upload();
  if (upload.status == UPLOAD_FILE_START) {
    String filename = upload.filename;
    if (!filename.startsWith("/")) {
      filename = "/" + filename;
    }
    //Se guardan por defecto en public
    filename = "/public" + filename;
    log(F("(WebServer)Subiendo archivo al servidor"), filename, logInfo);
    // El nombre del archivo no debe superar 31 caracteres
    // if(filename.length()) TODO
    fsUploadFile = LittleFS.open(filename, "w");
    filename = String();
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    //DBG_OUTPUT_PORT.print("handleFileUpload Data: "); DBG_OUTPUT_PORT.println(upload.currentSize);
    if (fsUploadFile) {
      fsUploadFile.write(upload.buf, upload.currentSize);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (fsUploadFile) {
      fsUploadFile.close();
    }
    log(F("(WebServer)Tamaño archivo subido:"), upload.totalSize, logInfo);
  }
}

void M3BorrarArchivoWeb() {
  if (webServer.args() == 0) {
    return webServer.send(500, "text/plain", "BAD ARGS");
  }
  String path = webServer.arg(0);
  //DBG_OUTPUT_PORT.println("handleFileDelete: " + path);
  if (path == "/") {
    return webServer.send(500, "text/plain", "BAD PATH");
  }
  if (!LittleFS.exists(path)) {
    return webServer.send(404, "text/plain", "FileNotFound");
  }
  LittleFS.remove(path);
  webServer.send(200, "text/plain", "");
  path = String();
}

void M3CrearArchivoWeb() {
  if (webServer.args() == 0) {
    return webServer.send(500, "text/plain", "BAD ARGS");
  }
  String path = webServer.arg(0);
  //DBG_OUTPUT_PORT.println("handleFileCreate: " + path);
  if (path == "/") {
    return webServer.send(500, "text/plain", "BAD PATH");
  }
  if (LittleFS.exists(path)) {
    return webServer.send(500, "text/plain", "FILE EXISTS");
  }
  File file = LittleFS.open(path, "w");
  if (file) {
    file.close();
  } else {
    return webServer.send(500, "text/plain", "CREATE FAILED");
  }
  webServer.send(200, "text/plain", "");
  path = String();
}

/******************************************************************************/
/****************************** HELPER FUNCTIONS ******************************/
/******************************************************************************/
String formatBytes(size_t bytes) {
  if (bytes < 1024) {
    return String(bytes) + "B";
  } else if (bytes < (1024 * 1024)) {
    return String(bytes / 1024.0) + "KB";
  } else if (bytes < (1024 * 1024 * 1024)) {
    return String(bytes / 1024.0 / 1024.0) + "MB";
  } else {
    return String(bytes / 1024.0 / 1024.0 / 1024.0) + "GB";
  }
}

String getContentType(String filename) {
  if (webServer.hasArg("download")) {
    return "application/octet-stream";
  } else if (filename.endsWith(".htm")) {
    return "text/html";
  } else if (filename.endsWith(".html")) {
    return "text/html";
  } else if (filename.endsWith(".css")) {
    return "text/css";
  } else if (filename.endsWith(".js")) {
    return "application/javascript";
  } else if (filename.endsWith(".png")) {
    return "image/png";
  } else if (filename.endsWith(".gif")) {
    return "image/gif";
  } else if (filename.endsWith(".jpg")) {
    return "image/jpeg";
  } else if (filename.endsWith(".ico")) {
    return "image/x-icon";
  } else if (filename.endsWith(".xml")) {
    return "text/xml";
  } else if (filename.endsWith(".pdf")) {
    return "application/x-pdf";
  } else if (filename.endsWith(".zip")) {
    return "application/x-zip";
  } else if (filename.endsWith(".gz")) {
    return "application/x-gzip";
  }
  return "text/plain";
}

/******************************************************************************/
/**************************************||**************************************/
/******************************************************************************/
bool M3UsuarioAutenticado() {
  log(F("(WebServer)Verificando si usuario esta autenticado"), logInfo);
  if (webServer.hasHeader("Cookie")) {
    String cookie = webServer.header("Cookie");
    log(F("(WebServer)Cookie encontrada:"), cookie, logInfo);
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      log(F("(WebServer)Usuario Autenticado"), logInfo);
      return true;
    }
  }
  log(F("(WebServer)Fallo autenticacion"), logError);
  webServer.sendHeader("Location", "/login.html");
  webServer.sendHeader("Cache-Control", "no-cache");
  webServer.send(301);
  return false;
}


//login page, also called for disconnect
void M3Login() {
  String msg;
  if (webServer.hasHeader("Cookie")) {
    Serial.print("Found cookie: ");
    String cookie = webServer.header("Cookie");
    Serial.println(cookie);
  }
  if (webServer.hasArg("DISCONNECT")) {
    Serial.println("Disconnection");
    webServer.sendHeader("Location", "/login");
    webServer.sendHeader("Cache-Control", "no-cache");
    webServer.sendHeader("Set-Cookie", "ESPSESSIONID=0");
    webServer.send(301);
    return;
  }
  if (webServer.hasArg("usuario") && webServer.hasArg("clave")) {
    if (webServer.arg("usuario") == "admin" &&  webServer.arg("clave") == "admin") {
      webServer.sendHeader("Location", "/");
      webServer.sendHeader("Cache-Control", "no-cache");
      webServer.sendHeader("Set-Cookie", "ESPSESSIONID=1");
      webServer.send(301);
      Serial.println("Log in Successful");
      return;
    }
    msg = "Wrong username/password! try again.";
    Serial.println("Log in Failed");
  }
  if (!M3LeerArchivoWeb("/web/login.html")) {
    // Si no lo encuentra, construimos la página
    String content = "<html><body><form action='/login' method='POST'>To log in, please use : admin/admin<br>";
    content += "User:<input type='text' name='USERNAME' placeholder='user name'><br>";
    content += "Password:<input type='password' name='PASSWORD' placeholder='password'><br>";
    content += "<input type='submit' name='SUBMIT' value='Submit'></form>" + msg + "<br>";
    content += "You also can go <a href='/inline'>here</a></body></html>";
    webServer.send(200, "text/html", content);
  }
}
