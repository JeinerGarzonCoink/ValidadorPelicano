/**
 * @file Funciones validador.cpp
 * @author Oscar Pineda (o.pineda@dcoink.com)
 * @brief Funciones principales del Validador Pelicano
 * @version 0.1
 * @date 2023-03-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

// --------------- LOGGER FUNCTIONS --------------------//

/**
 * @brief Funcion que busca el nivel de logging de spdlog de acuerdo a un codigo
 * @param Code Codigo de logging entero que va desde 0 hasta 6
 * @return SpdlogLevels_t Estructura que contiene un codigo y un mensaje
 */
SpdlogLevels_t SearchSpdlogLevel(int Code);

/**
 * @brief Funcion que establece el nivel de logging general de acuerdo a la variable global LoggerLevel
 */
void SetSpdlogLevel();

// --------------- SEARCH FUNCTIONS --------------------//

/**
 * @brief Funcion que busca el mensaje de error que retorna la funcion ExecuteCommand usando el codigo de error asociado
 * @param Code Codigo de error entero que va desde -6 hasta 6
 * @return ErrorCodeExComm_t Estructura que contiene un codigo y un mensaje
 */
ErrorCodeExComm_t SearchErrorCodeExComm (int Code);

/**
 * @brief Funcion que busca la moneda asociada al canal ingresado
 * @param Channel Canal de moneda que informa el validador
 * @return CoinPolling_t Estructura que contiene un canal y un valor de moneda entero
 */
CoinPolling_t SearchCoin (int Channel);

/**
 * @brief Funcion que busca un mensaje de error, una bandera de rechazo y una bandera de error critico en el polling de acuerdo al codigo ingresado
 * @param Code Codigo de error en polling
 * @return CoinPolling_t Estructura que contiene un codigo, un mensaje, una bandera de rechazo y una bandera de error critico
 */
ErrorCodePolling_t SearchErrorCodePolling (int Code);

/**
 * @brief Funcion que busca un codigo de fallo para el header 232 de CCtalk
 * @param Code Codigo de fallo
 * @return CoinPolling_t Estructura que contiene un codigo de fallo y un mensaje
 */
FaultCode_t PelicanoClass::SearchFaultCode (int Code); ---> HandleResponseError

// --------------- STATES OF MACHINE STATE (FUNCTIONS) --------------------//

/**
* @brief Primer estado de la maquina de estados, configura el logger de spdlog
* @return int - Retorna 0 siempre
*/
int StIdle();

/**
* @brief Segundo estado, escanea los puertos, envia un comando simplepoll al validador y se conecta al puerto que le responda exitosamente
* @return int - Retorna 0 si se pudo conectar al puerto
* @return int - Retorna 1 si no se pudo conectar al puerto
*/
int StConnect();

/**
* @brief Tercer estado, revisa la comunicacion, corre revision inicial y lee los opto estados
* @return int - Retorna 0 si pudo correr las 3 anteriores funciones exitosamente
* @return int - Retorna 1 si no se pudo correr alguna de las 3 funciones anteriores o si hubo algun codigo de falla grave
* @return int - Retorna 2 si hay algo en la bandeja o si la puerta esta abierta
*/
int StCheck();

/**
* @brief Cuarto estado, habilita las monedas, revisa que el evento este en cero y pone a correr el motor
* @return int - Retorna 0 si pudo correr las 3 anteriores funciones exitosamente
* @return int - Retorna 1 si no se pudo correr alguna de las 3 funciones anteriores o si el evento no esta en cero
*/
int StEnable()

/**
* @brief Quinto estado, hace una revision de los ultimos 5 eventos sucedidos en el validador
* @return Si retorna -2 -> [SC] Hubo un error haciendo el polling
* @return Si retorna -1 -> [SC] Hubo un error grave enviando el comando
* @return Si retorna  0 -> [SC] Todo funciona correctamente
* @return Si retorna  1 -> [SC] Hay que repetir el envio del comando, ya que el validador no lo pudo reconocer
* @return Si retorna  2 -> [SC] No ejecuto el comando
*/
int StPolling();

/**
* @brief Sexto estado, corre rutina de limpiado de bowl, detiene el motor y lee opto estados
* @return int - Retorna 0 si pudo correr las 3 anteriores funciones exitosamente
* @return int - Retorna 1 si no se pudo correr alguna de las 3 funciones anteriores o si hubo algun codigo de falla grave
* @return int - Retorna 2 si hay algo en la bandeja o si la puerta esta abierta
*/
int StCleanBowl();

/**
* @brief Septimo estado, resetea el validador y corre una revision de los canales para revisar que el evento se haya reseteado a 0
* @return int - Retorna 0 si pudo correr las 2 anteriores funciones exitosamente
* @return int - Retorna 1 si no se pudo correr alguna de las 2 funciones anteriores o si el evento no esta en cero
*/
int StReset();

/**
* @brief Estado de error, revisa la conexion 
* @return int - Retorna 0 si la conexion esta bien
* @return int - Retorna 1 si el validador no responde bien al comando simplepoll
*/
int StError();

// --------------- MAIN FUNCTIONS --------------------//

/**
* @brief Se conecta al puerto con las caracteristicas definidas en la hoja de datos del dispensador
* @brief Cambia bandera de conexion exitosa/fallida
* @brief [Solo deberia correrse una vez]
* @param Port Puerto a conectar entero igual o mayor que cero
* @return int - Retorna 0 si la conexion fue exitosa
* @return int - Retorna 1 si el puerto es invalido
* @return int - Retorna 2 si no puede leer los parametros actuales del puerto
* @return int - Retorna 3 si no puede escribir los nuevos parametros del puerto
* @return int - Retorna 4 si no se pudo conectar al puerto
*/
int ConnectSerial(int Port);

/**
* @brief Corre la funcion ConnectSerial(n) y luego la funcion InitDispenser() en cada puerto, 
* @brief si logra correr las dos sin errores devuelve el numero de puerto n
* @brief [Solo deberia correrse una vez]
* @return int - Retorna el numero de puerto desde 0 en adelante si encontro, en otro caso devuelve -1
*/
int ScanPorts();

/**
* @brief Maneja la respuesta de Execute command para que solo sean 5 respuestas
* @param Comm Comando a escribir en el puerto
* @param Xlen Longitud del comando en bytes
* @return Si retorna -2 -> [SC] Hubo un error haciendo el polling
* @return Si retorna -1 -> [SC] Hubo un error grave enviando el comando
* @return Si retorna  0 -> [SC] Todo funciona correctamente
* @return Si retorna  1 -> [SC] Hay que repetir el envio del comando, ya que el validador no lo pudo reconocer
* @return Si retorna  2 -> [SC] No ejecuto el comando
*/
int SendingCommand(unsigned char* Comm, int Xlen);

/**
* @brief Escribe el comando Comm en el puerto, luego lee la respuesta. 
* @brief Si la respuesta no es mayor o igual que la longitud del comando escrito, envia codigo diferente de 0
* @brief Si la longitud de la respuesta es igual a la longitud del comando escrito menos uno (longitud real), quiere decir que no reconoce el comando o la direccion de destino 
* @param Comm Comando a escribir en el puerto
* @param Xlen Longitud del comando en bytes
* @return Si retorna -6 -> [EC|HR|HRP|HRI] No ejecuto el comando EC|HR|HRP|HRI
* @return Si retorna -5 -> [EC] Hubo un error de escritura de comando
* @return Si retorna -4 -> [EC|HRI] Hubo un error de lectura de respuesta
* @return Si retorna -3 -> [EC] El validador no responde, tiempo de espera agotado
* @return Si retorna -2 -> [HR] El validador esta ocupado
* @return Si retorna -1 -> [HR] ACK negativo recibido
* @return Si retorna  0 -> [HR] Respuesta de exito identificada
* @return Si retorna  1 -> [HR] Dato desconocido en posicion de ACK
* @return Si retorna  2 -> [HR] El mensaje no se recibio completo
* @return Si retorna  3 -> [HRP] Los datos que recibe del polling son incorrectos, tal vez hay que resetear el validador
* @return Si retorna  4 -> [HRP] El validador detecto un error en el polling
* @return Si retorna  5 -> [EC] La respuesta llego muy corta, no se dio el tiempo de espera suficiente para leer
* @return Si retorna  6 -> [EC] La respuesta es la misma que el comando, el validador no reconoce el comando
 */
 int ExecuteCommand(unsigned char* Comm, int Xlen);

/**
* @brief Maneja la respuesta que llega, asegura la integridad de los datos, clasifica la respuesta en exito o fallo y envia ACK de confirmacion
* @param Response Respuesta que envia el validador
* @param Rdlen Longitud de la respuesta
* @param Xlen Longitud del comando
* @return Si retorna -6 -> [HR] No ejecuto el comando
* @return Si retorna -2 -> [HR] El validador esta ocupado
* @return Si retorna -1 -> [HR] ACK negativo recibido
* @return Si retorna  0 -> [HR] Respuesta de exito identificada
* @return Si retorna  1 -> [HR] Dato desconocido en posicion de ACK
* @return Si retorna  2 -> [HR] El mensaje no se recibio completo
*/
int HandleResponse(unsigned char* Response, int Rdlen, int Xlen);

/**
* @brief Maneja la respuesta que llega, detecta el ACK, calsifica la respuesta en polling, info o las demas
* @param Response Respuesta que envia el validador
* @param Rdlen Longitud de la respuesta
* @return Si retorna -6 -> [HRP] No ejecuto el comando
* @return Si retorna  0 -> [HRP] El comando de polling corrio exitosamente
* @return Si retorna  3 -> [HRP] Los datos que recibe del polling son incorrectos, tal vez hay que resetear el validador
* @return Si retorna  4 -> [HRP] El validador detecto un error en el polling
*/
int HandleResponsePolling(unsigned char* Response, int Rdlen);

/**
* @brief Maneja la respuesta del comando self check o de read opto states
* @param Response Respuesta que envia el validador
* @param Rdlen Longitud de la respuesta
* @return Si retorna -6 -> [HRI] No ejecuto el comando
* @return Si retorna -4 -> [EC|HRI] Hubo un error de lectura de respuesta
* @return Si retorna  0 -> [HRI] El comando pudo ser identificado y las variables importantes fueron extraidas
*/
int HandleResponseInfo(unsigned char* Response, int Rdlen); ---> HandleResponseSuccess

/**
 * @brief Corre el comando CMDREADOPTOST para saber 4 cosas, si hay algo en la bandeja, si la puerta esta abierta y si los dos sensores de monedas estan bien
 * @return Si retorna -2 -> Hay que repetir el comando, ya que no lo pudo ejecutar
 * @return Si retorna -1 -> Error grave enviando el comando
 * @return Si retorna  0 -> Todo corrio exitosamente, las 4 cosas tienen estado OK
 * @return Si retorna  1 -> Alguno de los 2 sensores esta bloqueado
 * @return Si retorna  2 -> Hay algo en la bandeja o la puerta de basura esta abierta
 */
int CheckOptoStates(); ---> CheckDevice

/**
 * @brief Corre el comando CMDSIMPLEPOLL para revisar la comunicacion y verificar que el validador retorne ACK
 * @return Si retorna -1 -> Error grave enviando el comando, el validador no retorno ACK
 * @return Si retorna  0 -> Todo corrio exitosamente, validador retorna ACK
 */
int SimplePoll(); ---> ChangeRotational

/**
 * @brief Corre el comando CMDSELFCHECK para saber cual es el estado de falla del validador
 * @return Si retorna -2 -> Hay que repetir el comando, ya que no lo pudo ejecutar
 * @return Si retorna -1 -> Error grave enviando el comando
 * @return Si retorna  0 -> Todo corrio exitosamente, las 4 cosas tienen estado OK
 * @return Si retorna  1 -> Validador esta bloqueado
 * @return Si retorna  2 -> Error de hardware (interno del validador)
 * @return Si retorna  3 -> Error de software (interno del validador)
 */
int SelfCheck();

/**
 * @brief Corre el comando CMDENABLE para habilitar los canales del validador
 * @return Si retorna -1 -> Error grave enviando el comando, el validador no pudo habilitar los canales
 * @return Si retorna  0 -> Todo corrio exitosamente, validador habilito los canales
 */
int EnableChannels();

/**
 * @brief Corre el comando CMDSTARTMOTOR para poner en funcionamiento el motor del disco
 * @return Si retorna -1 -> Error grave enviando el comando, el motor puede que no este activado
 * @return Si retorna  0 -> Todo corrio exitosamente, validador activo el motor
 */
int StartMotor(); ---> MovingMotor

/**
 * @brief Corre el comando CMDSTARTPOLL para verificar que el evento se haya reseteado
 * @return Si retorna -2 -> Hay que repetir el comando, ya que no lo pudo ejecutar
 * @return Si retorna -1 -> Error grave enviando el comando
 * @return Si retorna  0 -> El evento esta borrado y listo
 * @return Si retorna  1 -> El evento no se reseteo
 */
int CheckEventReset(); ---> Polling

/**
 * @brief Corre el comando CMDCLEANBOWL para correr la rutina de vaciado de basura en la bandeja, se espera 7 segundos a que acabe
 * @return Si retorna -1 -> Error grave, no pudo correr rutina de vaciado de bandeja
 * @return Si retorna  0 -> Rutina de vaciado de basura corrio exitosamente
 */
int CleanBowl();

/**
 * @brief Corre el comando CMDSTOPMOTOR para detener el motor del disco
 * @return Si retorna -1 -> Error grave enviando el comando, el motor puede que siga corriendo
 * @return Si retorna  0 -> Todo corrio exitosamente, validador detuvo el motor
 */
int StopMotor();

/**
 * @brief Corre el comando CMDRESETDEVICE para reiniciar el dispositivo
 * @return Si retorna -1 -> Error grave enviando el comando, no se pudo reiniciar el dispositivo
 * @return Si retorna  0 -> Todo corrio exitosamente, validador reiniciado
 */
int ResetDevice();

//////////// Otras funciones que faltan por agregar

void GetSpeed();
void SetSpeed();
void ChangeRotational();
void FixDiskBlocked();