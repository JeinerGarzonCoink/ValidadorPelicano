/**
 * @file main.cpp
 * @author Oscar Pineda (o.pineda@coink.com)
 * @brief Archivo principal que llama a las funciones del validador Pelicano
 * @version 0.1
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include <iostream>

#include "StateMachine.hpp"
#include "ValidatorPelicano.hpp"

using namespace StateMachine;

int main() {
    
    using namespace ValidatorPelicano;

    int Response = -1;
    printf("main() called.\r\n");

    PelicanoClass PelicanoObject;
    PelicanoClass* PelicanoPointer = &PelicanoObject;
    SMClass SMObject(PelicanoPointer);

    PelicanoObject.LoggerLevel = 0;

    std::cout<<"[MAIN] Iniciando maquina de estados"<<std::endl;
    SMObject.InitStateMachine();

    std::cout<<"[MAIN] Estado actual: "<<SMObject.StateMachineGetStateName(SMObject.SM.CurrState)<<std::endl;

    std::cout<<"[MAIN] Cambio de estado ST_IDLE ---> ST_CONNECT"<<std::endl;
    Response = SMObject.StateMachineRun(SMClass::EV_ANY);

    std::cout<<"[MAIN] Estado actual: "<<SMObject.StateMachineGetStateName(SMObject.SM.CurrState)<<std::endl;

    if (Response != 0){
        std::cout<<"[MAIN] No se pudo conectar a ningun puerto"<<std::endl;
        std::cout<<"[MAIN] Cambio de estado ST_CONNECT ---> ST_ERROR"<<std::endl;
        std::cout<<"[MAIN] Estado actual: "<<SMObject.StateMachineGetStateName(SMObject.SM.CurrState)<<std::endl;
        Response = SMObject.StateMachineRun(SMClass::EV_ERROR);
        return 1;
    }

    std::cout<<"[MAIN] Cambio de estado ST_CONNECT ---> ST_CHECK"<<std::endl;
    Response = SMObject.StateMachineRun(SMClass::EV_SUCCESS_CONN);
    std::cout<<"[MAIN] Estado actual: "<<SMObject.StateMachineGetStateName(SMObject.SM.CurrState)<<std::endl;

    if (Response == 1){
        std::cout<<"[MAIN] Error grave, bloqueo o error grave de HW/SW"<<std::endl;
        std::cout<<"[MAIN] Cambio de estado ST_CHECK ---> ST_ERROR"<<std::endl;
        Response = SMObject.StateMachineRun(SMClass::EV_ERROR);
        std::cout<<"[MAIN] Estado actual: "<<SMObject.StateMachineGetStateName(SMObject.SM.CurrState)<<std::endl;
        return 1;
    }
    else if (Response == 2){
        std::cout<<"[MAIN] Hay algo en la bandeja o la puerta de vaciado de basura esta abierta"<<std::endl;
        std::cout<<"[MAIN] Cambio de estado ST_CHECK ---> ST_CLEANBOWL"<<std::endl;
        Response = SMObject.StateMachineRun(SMClass::EV_TRASH);
        std::cout<<"[MAIN] Estado actual: "<<SMObject.StateMachineGetStateName(SMObject.SM.CurrState)<<std::endl;
    }
    
    if(strcmp(SMObject.StateMachineGetStateName(SMObject.SM.CurrState), "ST_CLEANBOWL") == 0){

        std::cout<<"[MAIN] Cambio de estado ST_CLEANBOWL ---> ST_RESET"<<std::endl;
        Response = SMObject.StateMachineRun(SMClass::EV_EMPTY);
        std::cout<<"[MAIN] Estado actual: "<<SMObject.StateMachineGetStateName(SMObject.SM.CurrState)<<std::endl;

        if (Response != 0){
            std::cout<<"[MAIN] No pudo reiniciar el validador"<<std::endl;
        }

        std::cout<<"[MAIN] Cambio de estado ST_RESET ---> ST_CHECK"<<std::endl;
        Response = SMObject.StateMachineRun(SMClass::EV_LOOP);
        std::cout<<"[MAIN] Estado actual: "<<SMObject.StateMachineGetStateName(SMObject.SM.CurrState)<<std::endl;

        if (Response != 0){
            std::cout<<"[MAIN] El validador no pudo limpiarse o hay problemas de comunicacion"<<std::endl;
            return 1;
        }
    }
    
    std::cout<<"[MAIN] Cambio de estado ST_CHECK ---> ST_ENABLE"<<std::endl;
    Response = SMObject.StateMachineRun(SMClass::EV_CALL_POLLING);
    std::cout<<"[MAIN] Estado actual: "<<SMObject.StateMachineGetStateName(SMObject.SM.CurrState)<<std::endl;

    if ((Response != 0)&(PelicanoObject.ErrorOCode != 0)){
        std::cout<<"[MAIN] Error grave"<<std::endl;
        std::cout<<"[MAIN] Cambio de estado ST_ENABLE ---> ST_ERROR"<<std::endl;
        Response = SMObject.StateMachineRun(SMClass::EV_ERROR);
        std::cout<<"[MAIN] Estado actual: "<<SMObject.StateMachineGetStateName(SMObject.SM.CurrState)<<std::endl;
        return 1;
    }

    std::cout<<"[MAIN] Cambio de estado ST_ENABLE ---> ST_POLLING"<<std::endl;
    Response = SMObject.StateMachineRun(SMClass::EV_READY);
    std::cout<<"[MAIN] Estado actual: "<<SMObject.StateMachineGetStateName(SMObject.SM.CurrState)<<std::endl;

    std::cout<<"Listo para monedas"<<std::endl;

    int CoinEventPrev = 0;
    Response = -1;
    int i = 0;
    while (i<100){
        
        SMObject.StateMachineRun(SMClass::EV_POLL);

        if(PelicanoObject.CoinEvent != CoinEventPrev){

            if(PelicanoObject.ErrorHappened){
                std::cout<<"[MAIN] ----------> Error happened!"<<std::endl;
                std::cout<<"[MAIN] Coin Event: "<<PelicanoObject.CoinEvent<<std::endl;
                std::cout<<"[MAIN] Error code: "<<PelicanoObject.ErrorOCode<<std::endl;
                std::cout<<"[MAIN] Error message: "<<PelicanoObject.ErrorOMsg<<std::endl;
                std::cout<<"[MAIN] Error rejected: "<<PelicanoObject.ErrorORejected<<std::endl;
            }
            else{
                std::cout<<"[MAIN] ----------> Coin Detected!"<<std::endl;
                std::cout<<"[MAIN] Coin Event: "<<PelicanoObject.CoinEvent<<std::endl;
                std::cout<<"[MAIN] Coin: "<<PelicanoObject.ActOCoin<<std::endl;
                std::cout<<"[MAIN] Channel: "<<PelicanoObject.ActOChannel<<std::endl;
            }

            CoinEventPrev = PelicanoObject.CoinEvent;
        }
        
        i++;

        Response = PelicanoObject.CheckOptoStates();

        if (Response == 2){
            i = 0;
        }
    }
   
    std::cout<<"Termina conteo para monedas"<<std::endl;

    std::cout<<"[MAIN] Cambio de estado ST_POLLING ---> ST_CLEAN_BOWL"<<std::endl;
    Response = SMObject.StateMachineRun(SMClass::EV_FINISH_POLL);
    std::cout<<"[MAIN] Estado actual: "<<SMObject.StateMachineGetStateName(SMObject.SM.CurrState)<<std::endl;

    std::cout<<"[MAIN] Cambio de estado ST_CLEANBOWL ---> ST_RESET"<<std::endl;
    Response = SMObject.StateMachineRun(SMClass::EV_EMPTY);
    std::cout<<"[MAIN] Estado actual: "<<SMObject.StateMachineGetStateName(SMObject.SM.CurrState)<<std::endl;

    std::cout<<"[MAIN] Cambio de estado ST_RESET ---> ST_CHECK"<<std::endl;
    Response = SMObject.StateMachineRun(SMClass::EV_LOOP);
    std::cout<<"[MAIN] Estado actual: "<<SMObject.StateMachineGetStateName(SMObject.SM.CurrState)<<std::endl;

    std::cout<<"[MAIN] Test corrido exitosamente"<<std::endl;

    return 0;
}