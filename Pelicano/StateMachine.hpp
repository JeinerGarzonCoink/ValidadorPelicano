/**
 * @file StateMachine.hpp
 * @author Oscar Pineda (o.pineda@coink.com)
 * @brief Header de la maquina de estados
 * @version 0.1
 * @date 2023-03-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include "ValidatorPelicano.hpp"

namespace StateMachine{

    using namespace ValidatorPelicano;
    
    class SMClass{
        public:

            enum State_t{
                ST_IDLE,
                ST_CONNECT,  
                ST_CHECK,   
                ST_ENABLE,
                ST_POLLING,
                ST_CLEANBOWL,
                ST_RESET,
                ST_ERROR              
            };

            struct StateMachine_t{
                State_t CurrState;
            };

            enum Event_t{
                EV_ANY,
                EV_SUCCESS_CONN,
                EV_CALL_POLLING,
                EV_CHECK,
                EV_TRASH,
                EV_READY,
                EV_FINISH_POLL,
                EV_POLL,
                EV_EMPTY,
                EV_LOOP,
                EV_ERROR,
            };

            /**
             * @brief Construct a new SMClass object
             * @param _PelicanoClass_p Apuntador a la clase del archivo ValidatorPelicano.cpp
             */
            SMClass(ValidatorPelicano::PelicanoClass *_PelicanoClass_p);

            /**
             * @brief Estado actual de la maquina de estados
             */
            StateMachine_t SM;

            /**
             * @brief Evento actual que cambia el estado de la maquina de estados
             */
            Event_t Evento;

            /**
             * @brief Estado inicial de la maquina de estados
             */
            State_t Estado;

            /**
             * @brief Inicia la maquina de estados y corre la funcion asociada al estado actual
             */
            void InitStateMachine();

            /**
             * @brief Corre la maquina de estados dependiendo del evento ingresado y del estado que tenga actualmente
             * @param Event Evento que ingresa para hacer el cambio de estado
             * @return int Si la funcion asociada hizo el cambio de estado con exito retorna un 1 / -1, de lo contrario retorna 0
             */
            int StateMachineRun(Event_t Event);

            /**
             * @brief Funcion para conocer el nombre del estado actual de la maquina de estados
             * @param State Se introduce un enum del estado actual
             * @return const char* Regresa una cadena de caracteres con el nombre dele stado actual
             */
            const char * StateMachineGetStateName(State_t State);
    };
};

#endif /* STATEMACHINE_HPP */

