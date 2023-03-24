/**
 * @file ValidatorPelicano.hpp
 * @author Oscar Pineda (o.pineda@coink.com)
 * @brief Header de las funciones del validador Pelicano
 * @version 0.1
 * @date 2023-03-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef VALIDATORPELICANO
#define VALIDATORPELICANO

#include <stdio.h>
#include <cstring> // To include strerror
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // To include errno
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <sys/ioctl.h> //To use flush
#include <bitset> //To use bitset in HandleResponseInfo

//#include "spdlog/spdlog.h" //Logging library
//#include "spdlog/sinks/daily_file_sink.h" //Logging library - daily file

namespace ValidatorPelicano{

    struct SpdlogLevels_t{
        int Code;
        std::string Message;
    };

    struct ErrorCodePolling_t{
        int Code;
        std::string Message;
        int Rejected;
        int Critical;
    };

    struct CoinPolling_t{
        int Channel;
        int Coin;
    };

    struct ErrorCodeExComm_t{
        int Code;
        std::string Message;
    };

    struct FaultCode_t{
        int Code;
        std::string Message;
    };

    class PelicanoClass{
        public:

            // --------------- EXTERNAL VARIABLES --------------------//

            /**
             * @brief Descriptor de archivo del puerto del validador
             */
            int SerialPort;

            /**
             * @brief Bandera que incica si fue exitosa la conexion al puerto serial del validador
             */
            bool SuccessConnect;

            /**
             * @brief Nivel de logging de la libreria Spdlog
             */
            int LoggerLevel;

            /**
             * @brief Este puerto es el resultante del escaneo de la funcion ScanPorts
             */

            int PortO;

            /**
             * @brief Evento actual en el validador (Funcion StPolling)
             */
            int CoinEvent;

            /**
             * @brief Evento anterior en el validador (Funcion StPolling)
             */
            int CoinEventPrev;

            int CoinCinc;
            int CoinCien;
            int CoinDosc;
            int CoinQuin;
            int CoinMil;
            
            /**
             * @brief Bandera que indica si sucedio un error (Funcion StPolling)
             */
            bool ErrorHappened;

            /**
             * @brief Bandera que indica si sucedio un error critico en alguno de los 5 eventos (Funcion StPolling)
             */
            bool CriticalError;

            /**
             * @brief Codigo de error de polling
             */
            int ErrorOCode;

            /**
             * @brief Mensaje de error de polling
             */
            const char * ErrorOMsg;

            /**
             * @brief Indica si la moneda fue rechazada mientras corria 'polling'
             */
            int ErrorORejected;

            /**
             * @brief Indica si el error es tan critico como para cerrar el proceso
             */
            int ErrorOCritical;
            
            int FaultOCode;
            const char * FaultOMsg;

            bool CoinPresent;
            bool TrashDoorOpen;
            bool LowerSensorBlocked;
            bool UpperSensorBlocked;

            /**
             * @brief Ultima moneda reconocida
             */
            int ActOCoin;
            /**
             * @brief Ultimo canal detectado asociado a la moneda reconocida
             */
            int ActOChannel;

            // --------------- CONSTRUCTOR FUNCTIONS --------------------//

            /**
             * @brief Constructor de la clase PelicanoClass
             */
            PelicanoClass();
            
            /**
             * @brief Destructor de la clase PelicanoClass
             */
            ~PelicanoClass();

            // --------------- LOGGER FUNCTIONS --------------------//

            /**
            * @brief Busca el nivel de logging Splog
            * @param Code Nivel de logging entero que va desde 0 hasta 6
            * @return SpdlogLevels_t Devuelve el codigo de logging y la palabra correspondiente al nivel
            */
            //SpdlogLevels_t SearchSpdlogLevel(int Code);

            /**
             * @brief Establece el nivel de Logging de acuerdo a la variable externa "LoggerLevel"
             */
            //void SetSpdlogLevel();

            // --------------- SEARCH FUNCTIONS --------------------//

            /**
            * @brief Busca el codigo de error entero que devuelve la funcion ExecuteCommand
            * @param Code Codigo de error entero que va desde -6 hasta 6
            * @return ErrorCodeExComm_t Estructura que tiene el codigo y el mensaje de ExecuteCommand
            */
            ErrorCodeExComm_t SearchErrorCodeExComm (int Code);

            /**
            * @brief Busca la moneda asociada al ultimo evento registrado
            * @param Channel Canal asociado al ultimo evento registrado
            * @return CoinPolling_t Estructura que tiene el canal, la moneda y el camino de clasificacion por cada moneda registrada
            */
            CoinPolling_t SearchCoin (int Channel);

            /**
            * @brief Busca el codigo de error asociado al ultimo evento registrado
            * @param Code Codigo de error registrado en le ultimo evento
            * @return ErrorCodePolling_t Estructura que tiene el codigo de error y el mensaje asociado
            */
            ErrorCodePolling_t SearchErrorCodePolling (int Code);

            FaultCode_t SearchFaultCode (int Code);

            // --------------- STATES OF MACHINE STATE (FUNCTIONS) --------------------//

            int StIdle();
            int StConnect();
            int StCheck();
            int StEnable();
            int StPolling();
            int StCleanBowl();
            int StReset();
            int StError();

            // --------------- MAIN FUNCTIONS --------------------//
            
            int ConnectSerial(int Port);
            int ScanPorts();
            int SendingCommand(unsigned char* Comm, int Xlen);
            int ExecuteCommand(unsigned char* Comm, int Xlen);
            int HandleResponse(unsigned char* Response, int Rdlen, int Xlen);
            int HandleResponsePolling(unsigned char* Response, int Rdlen);
            int HandleResponseInfo(unsigned char* Response, int Rdlen);
            int CheckOptoStates();
            int SimplePoll();
            int SelfCheck();
            int EnableChannels();
            int StartMotor();
            int CheckEventReset();
            int CleanBowl();
            int StopMotor();
            int ResetDevice();
    };
}

#endif /* VALIDATORPELICANO */