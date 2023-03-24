/**
 * @file ValidatorPelicano.cpp
 * @author Oscar Pineda (o.pineda@coink.com)
 * @brief Codigo fuente de las funciones del validador Pelicano
 * @version 0.1
 * @date 2023-03-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ValidatorPelicano.hpp"

namespace ValidatorPelicano{
    // --------------- EXTERNAL VARIABLES --------------------//

    int SerialPort;
    bool SuccessConnect;
    int LoggerLevel;
    int PortO;
    
    int CoinEvent;
    int CoinEventPrev;

    int CoinCinc;
    int CoinCien;
    int CoinDosc;
    int CoinQuin;
    int CoinMil;

    bool ErrorHappened;
    bool CriticalError;

    int ErrorOCode;
    const char * ErrorOMsg;
    int ErrorORejected;
    int ErrorOCritical;

    int FaultOCode;
    const char * FaultOMsg;

    bool CoinPresent;
    bool TrashDoorOpen;
    bool LowerSensorBlocked;
    bool UpperSensorBlocked;

    int ActOChannel;
    int ActOCoin;

    // --------------- INTERNAL VARIABLES --------------------//

    int MAXPORTS = 10;
    bool Scanning;

    /*
    'Factory_Disk_Motor_Off':           b'\x02\x04\x01\xff\x42\x56\x01\x10\x51',
    'Factory_Disk_Motor_Fwd':           b'\x02\x04\x01\xff\x42\x56\x01\x11\x50',
    'Factory_Disk_Motor_Rev':           b'\x02\x04\x01\xff\x42\x56\x01\x12\x4f',
    'Factory_Disk_Motor_Stop_Pos':      b'\x02\x04\x01\xff\x42\x56\x01\x15\x4c',
    'Factory_Trash_Motor_Off':          b'\x02\x04\x01\xff\x42\x56\x01\x20\x41',
    'Factory_Trash_Motor_Fwd':          b'\x02\x04\x01\xff\x42\x56\x01\x21\x40',
    'Factory_Trash_Motor_Rev':          b'\x02\x04\x01\xff\x42\x56\x01\x22\x3f',
    'Factory_Trash_Door_Small_Cycle':   b'\x02\x04\x01\xff\x42\x56\x01\x24\x3d',
    'Factory_Trash_Door_Comp_Cycle':    b'\x02\x04\x01\xff\x42\x56\x01\x25\x3c',
    */

    unsigned char CMDENABLE[8]        = {"\x02\x02\x01\xE7\xFF\xFF\x16"}; // 7 + 5 (add+data+add+ack+chk)
    unsigned char CMDINHIBIT50[8]     = {"\x02\x02\x01\xE7\xF7\xFE\x1F"}; // 7 + 5 (add+data+add+ack+chk)
    unsigned char CMDCLEANBOWL[7]     = {"\x02\x01\x01\xEF\x01\x0C"};     // 6 + 5 (add+data+add+ack+chk)
    unsigned char CMDSTARTMOTOR[7]    = {"\x02\x01\x01\xE4\x01\x17"};     // 6 + 5 (add+data+add+ack+chk)
    unsigned char CMDSTOPMOTOR[7]     = {"\x02\x01\x01\xE4\x00\x18"};     // 6 + 5 (add+data+add+ack+chk)
    unsigned char CMDSIMPLEPOLL[6]    = {"\x02\x00\x01\xFE\xFF"};         // 5 + 5 (add+data+add+ack+chk)
    unsigned char CMDSTARTPOLL[6]     = {"\x02\x00\x01\xE5\x18"};         // 5 + 16(add+data+add+ack+event+pair1+pair2+pair3+pair4+pair5+chk)
    unsigned char CMDRESETDEVICE[6]   = {"\x02\x00\x01\x01\xFC"};         // 5 + 5 (add+data+add+ack+chk)
    unsigned char CMDSELFCHECK[6]     = {"\x02\x00\x01\xE8\x15"};         // 5 + 6 (add+data+add+ack+mask+chk)
    unsigned char CMDREADOPTOST[6]    = {"\x02\x00\x01\xEC\x11"};         // 5 + 6 (add+data+add+ack+mask+chk)

    const char DEFAULTERROR[] = "Error por defecto";
    
    ErrorCodePolling_t ErrP;
    ErrorCodePolling_t ErrPPrev;

    FaultCode_t FaultC;

    CoinPolling_t ActCoin;

    //auto logger = spdlog::daily_logger_mt("ValidatorPelicano", "logs/Pelicano.log", 23, 59);

    static CoinPolling_t CoinPolling[] = {
        {0, 0},
        {1, 0},
        {2, 0},
        {3, 0},
        {4, 50},
        {5, 100},
        {6, 200},
        {7, 500},
        {8, 1000},
        {9, 50},
        {10,100},
        {11,200},
        {12,500},
        {13,0},
        {14,0},
        {15,0},
        {16,0},
    };

    static ErrorCodePolling_t ErrorCodePolling[] = {
        {0,"NULL event, no error / previous error solved",0,0},
        {1,"Uknown reject coin",1,0},
        {2,"Inhibited coin rejected",1,0},
        {3,"Multiple window",1,0},
        {4,"Wake-up timeout",2,0},
        {5,"Validation timeout",2,0},
        {6,"Credit sensor timeout",2,0},
        {7,"Sorter opto timeout",0,0},
        {8,"2nd close coin error",1,0},
        {9,"Accept gate not ready",1,0},
        {10,"Credit sensor not ready / Blocked rejectance path",1,1},
        {11,"Sorter not ready",1,0},
        {12,"Reject coin not cleared",1,1},
        {13,"Validation sensor not ready",1,1},
        {14,"Credit sensor blocked",1,1},
        {15,"Sorter opto blocked",1,1},
        {16,"Credit sequence error",0,0},
        {17,"Coin going backwards",0,0},
        {18,"Coin too fast",0,0},
        {19,"Coin too slow",0,0},
        {20,"C.O.S. mechanism activated",0,1},
        {21,"DCE opto timeout",2,0},
        {22,"DCE opto not seen",1,0},
        {23,"Credit sensor reached too early",0,0},
        {24,"Reject coin",1,0},
        {25,"Reject slug",1,0},
        {26,"Reject sensor blocked",0,1},
        {27,"Games overload",0,0},
        {28,"Max. coin meter pulses exceeded",0,0},
        {29,"Unexpected acceptance",0,1},
        {30,"Unexpected rejectance",1,1},
        {31,"Manifold opto timeout",0,0},
        {32,"Manifold opto blocked",1,1},
        {33,"Manifold not ready",1,0},
        {34,"Security status changed",2,0},
        {35,"Motor exception",2,0},
        {36,"Swallowed coin",0,0},
        {37,"Coin too fast",1,0},
        {38,"Coin too slow",1,0},
        {39,"Coin incorrectly sorted",0,0},
        {40,"External light attack",0,0},
        {117,"Acceptance path blocked",1,1},
        {121,"Acceptance path blocked",1,1},
        {128,"Inhibited coin",1,0},
        {129,"Inhibited coin",1,0},
        {130,"Inhibited coin",1,0},
        {131,"Inhibited coin",1,0},
        {132,"Inhibited coin",1,0},
        {133,"Inhibited coin",1,0},
        {134,"Inhibited coin",1,0},
        {135,"Inhibited coin",1,0},
        {136,"Inhibited coin",1,0},
        {137,"Inhibited coin",1,0},
        {138,"Inhibited coin",1,0},
        {139,"Inhibited coin",1,0},
        {140,"Inhibited coin",1,0},
        {141,"Inhibited coin",1,0},
        {142,"Inhibited coin",1,0},
        {143,"Inhibited coin",1,0},
        {144,"Inhibited coin",1,0},
        {145,"Inhibited coin",1,0},
        {146,"Inhibited coin",1,0},
        {147,"Inhibited coin",1,0},
        {148,"Inhibited coin",1,0},
        {149,"Inhibited coin",1,0},
        {150,"Inhibited coin",1,0},
        {151,"Inhibited coin",1,0},
        {152,"Inhibited coin",1,0},
        {153,"Inhibited coin",1,0},
        {154,"Inhibited coin",1,0},
        {155,"Inhibited coin",1,0},
        {156,"Inhibited coin",1,0},
        {157,"Inhibited coin",1,0},
        {158,"Inhibited coin",1,0},
        {159,"Inhibited coin",1,0},
        {253,"Data block request",0,0},
        {254,"Coin return mechanism activated",0,0},
        {255,"Unspecified alarm code",0,0},
    };

    static SpdlogLevels_t SpdlogLvl[] = {
        {0,"trace"},
        {1,"debug"},
        {2,"info"},
        {3,"warn"},
        {4,"error"},
        {5,"critical"},
        {6,"off"},
    };

    static ErrorCodeExComm_t ErrorCodesExComm[] = {
        {-6,"[] Function EC/HR/HRP/HRI was not executed"},
        {-5,"[EC] Writting error"},
        {-4,"[EC] Writing successful but cannot read"},
        {-3,"[EC] Timeout, acceptor not responding"},
        {-2,"[HR] Acceptor is busy"},
        {-1,"[HR] ACK Negative"},
        { 0,"[] No news is good news"},
        { 1,"[HR] Unknown data in ACK position"},
        { 2,"[HR] Message was not received completely"},
        { 3,"[HRP] Polling data is incorrect, please reset validator"},
        { 4,"[HRP] Polling error detected"},
        { 5,"[EC] Reading lenth is too short, sleep time is too short"},
        { 6,"[EC] Command not recognized or adress is wrong"},
    };

    static FaultCode_t FaultCodeM[] = {
        {  0,"OK"},
        {  1,"Firmware checksum corrupted"},
        {  2,"Fault on inductive coils"},
        {  3,"Fault on credit sensors"},
        { 30,"Datablock checksum corrupted"},
        {253,"Coin jam in measurement system"},
        {254,"Disk blocked, not able to resolve blockage"},
        {255,"Unspecified alarm code"},
    };

    PelicanoClass::PelicanoClass(){

        SerialPort = 0;
        SuccessConnect = false;
        Scanning = false;
        LoggerLevel = 0;
        PortO = 0;

        CoinEvent = 0;
        CoinEventPrev = 0;

        CoinCinc = 0;
        CoinCien = 0;
        CoinDosc = 0;
        CoinQuin = 0;
        CoinMil = 0;

        ErrorHappened = false;
        CriticalError = false;

        ErrorOCode = 0;
        ErrorOMsg = DEFAULTERROR;
        ErrorORejected = 0;
        ErrorOCritical = 0;

        FaultOCode = 0;
        FaultOMsg = DEFAULTERROR;

        ActOCoin = 0;
        ActOChannel = 0;

        CoinPresent = false;
        TrashDoorOpen = false;
        LowerSensorBlocked = false;
        UpperSensorBlocked = false;

        ActOChannel = 0;
        ActOCoin = 0;

        // SetSpdlogLevel();
    }

    PelicanoClass::~PelicanoClass(){}

    // --------------- LOGGER FUNCTIONS --------------------//

    /** SpdlogLevels_t PelicanoClass::SearchSpdlogLevel(int Code){
    //     SpdlogLevels_t SPLvl;
    //     SPLvl.Message = "SpdlogLvl not found!!!"; 

        for(long unsigned int i = 0; i < sizeof(SpdlogLvl)/sizeof(SpdlogLvl[0]); i++) {
            // if(SpdlogLvl[i].Code == Code) {
            //     SPLvl.Message = SpdlogLvl[i].Message;
            //     break;
            // }
        }
        
        //SPLvl.Code = Code;
        return SPLvl;
    }
    */
    /*void PelicanoClass::SetSpdlogLevel(){
        // spdlog::set_level(static_cast<spdlog::level::level_enum>(LoggerLevel)); // Set global log level
        //logger->set_level(spdlog::level::debug);
    }
    */
    // --------------- SEARCH FUNCTIONS --------------------//

    ErrorCodeExComm_t PelicanoClass::SearchErrorCodeExComm (int Code){
        
        ErrorCodeExComm_t Code_msg;
        
        Code_msg.Message = "ErrorCode not found!!!";
        
        for(long unsigned int i = 0; i < sizeof(ErrorCodesExComm)/sizeof(ErrorCodesExComm[0]); i++) {
            if(ErrorCodesExComm[i].Code == Code) {
                Code_msg.Message = ErrorCodesExComm[i].Message;
                break;
            }
        }
        
        Code_msg.Code = Code;

        return Code_msg;
    }

    CoinPolling_t PelicanoClass::SearchCoin (int Channel){
        
        CoinPolling_t ChannelCoin;
        
        ChannelCoin.Coin = 0;
        
        for(long unsigned int i = 0; i < sizeof(CoinPolling)/sizeof(CoinPolling[0]); i++) {
            if(CoinPolling[i].Channel == Channel) {
                ChannelCoin.Coin = CoinPolling[i].Coin;
                break;
            }
        }
        
        ChannelCoin.Channel = Channel;

        return ChannelCoin;
    }

    ErrorCodePolling_t PelicanoClass::SearchErrorCodePolling (int Code){
        
        ErrorCodePolling_t CodeMsgRej;
        
        CodeMsgRej.Message = "ErrorCode not found!!!";
        CodeMsgRej.Rejected = 3;
        CodeMsgRej.Critical = 0;
        
        for(long unsigned int i = 0; i < sizeof(ErrorCodePolling)/sizeof(ErrorCodePolling[0]); i++) {
            if(ErrorCodePolling[i].Code == Code) {
                CodeMsgRej.Message = ErrorCodePolling[i].Message;
                CodeMsgRej.Rejected = ErrorCodePolling[i].Rejected;
                CodeMsgRej.Critical = ErrorCodePolling[i].Critical;
                break;
            }
        }
        
        CodeMsgRej.Code = Code;

        return CodeMsgRej;
    }

    FaultCode_t PelicanoClass::SearchFaultCode (int Code){
        
        FaultCode_t FaultCodeMsg;
        
        FaultCodeMsg.Message = "FaultCode not found!!!";

        for(long unsigned int i = 0; i < sizeof(FaultCodeM)/sizeof(FaultCodeM[0]); i++) {
            if(FaultCodeM[i].Code == Code) {
                FaultCodeMsg.Message = FaultCodeM[i].Message;
                break;
            }
        }
        
        FaultCodeMsg.Code = Code;

        return FaultCodeMsg;
    }

        // --------------- STATES OF MACHINE STATE (FUNCTIONS) --------------------//

    int PelicanoClass::StIdle() {

        //SpdlogLevels_t SpdlogLvl;

        //SpdlogLvl = SearchSpdlogLevel(LoggerLevel);
        
        //SetSpdlogLevel();

        //logger->critical("[E0:STIDLE] Setting spdlog level in {}",SpdlogLvl.Message);

        //logger->trace("   [E0:STIDLE] --------------------------------------------------------------------------");
        //logger->debug("   [E0:STIDLE] --------------------------------------------------------------------------");
        //logger->info("    [E0:STIDLE] --------------------------------------------------------------------------");
        //logger->warn(" [E0:STIDLE] --------------------------------------------------------------------------");
        //logger->error("   [E0:STIDLE] --------------------------------------------------------------------------");
        //logger->critical("[E0:STIDLE] --------------------------------------------------------------------------");

        return 0;
    }

    int PelicanoClass::StConnect() {

        //logger->info("[E1:STCONNECT] Scanning ports");

        PortO = ScanPorts();

        if (PortO >= 0){
            //logger->info("[E1:STCONNECT] Port was found in /dev/ttyUSB{0:d}",PortO);
            return 0;
        }
        else{
            //logger->info("[E1:STCONNECT] Port was NOT found ......");
            return 1;
        }
    }
    
    int PelicanoClass::StCheck() {
        int Response = -1;

        Response = SimplePoll();
        
        if(Response == 0){
            //logger->debug("[E2:SelfCheck] communication working! ");
        }
        else{
            //logger->trace("[E2:SelfCheck] communication failure");
            return 1;
        }

        Response = SelfCheck();
        
        if(Response == 0){
            //logger->debug("[E2:SelfCheck] Initial review ok!!");
        }
        else{
            //logger->trace("[E2:SelfCheck] Failure in the initial review");
            return 1;
        }
        
        Response = CheckOptoStates();
        
        if (Response == 0){
            if ( CoinPresent | TrashDoorOpen ){
                //logger->warn("[E2:STCHECK] There is something in the bowl or trash door was opened ");
                Response = 2;
            }
            if ( LowerSensorBlocked | UpperSensorBlocked ){
                //logger->critical("[E2:STCHECK] Lower or upper sensor is blocked");
                Response = 1;
            }
        }
        else{
            if (Response != -1){
                //logger->error("[E2:STCHECK] Repeat command, command was not run successfully");
                Response = -2;
            }
            else{
                //logger->critical("[E2:STCHECK] Error sending command");
                Response = -1;
            }
        }

        //logger->trace("[E2:STCHECK] Optostates return: Everything is OK");
        return Response;
    }

    int PelicanoClass::StEnable() {

        int Response = 0;
        Response = EnableChannels();
        return Response;

        Response = CheckEventReset();
        if (Response != 0){
            return 1;            
        }

        Response = StartMotor();
        if (Response != 0){
            //logger->error("[StartMotor] Problem running start motor command!");
            return -1;
        }
        return 0;  
    }

    int PelicanoClass::StPolling() {
        int Response = 0;
        Response = SendingCommand(CMDSTARTPOLL,6);
        return Response; 
    }

    int PelicanoClass::StCleanBowl() {
        int Response = 0;

        Response = StopMotor();

        if (Response == 0){
            //logger->debug("[E5:STCLEANBOWL] engine stopped!!! ")
        }
        else{
            //logger->trace("[E5:STCLEANBOWL] There was an error, the motor did not stop")
            return 1;
        }

        Response = CleanBowl();

        if (Response == 0){
            //logger->debug("[E5:STCLEANBOWL] Bowl cleaning is done")
        }
        else{
            //logger->trace("[E5:STCLEANBOWL] The bowl was not cleaned")
            return 1;
        }

        Response = CheckOptoStates();
        // Revisar y colocar todos los estados de OptoStates
        if (Response == 0){
        if ( CoinPresent | TrashDoorOpen ){
            //logger->warn("[E5:CLEANBOWL] There is something in the bowl or trash door was opened ");
            Response = 2;
        }
        if ( LowerSensorBlocked | UpperSensorBlocked ){
            //logger->critical("[E5:CLEANBOWL] Lower or upper sensor is blocked");
            Response = 1;
        }
    }
    else{
        if (Response != -1){
            //logger->error("[E5:CLEANBOWL] Repeat command, command was not run successfully");
            Response = -2;
        }
        else{
            //logger->critical("[E5:CLEANBOWL] Error sending command");
            Response = -1;
        }
    }

    //logger->trace("[E5:CLEANBOWL] Optostates return: Everything is OK");
    return Response;
    }

    int PelicanoClass::StReset() {
        int Response = 0;
         //logger->debug("[E6:STRESET] Running CMDRESETDEVICE");
        Response = ResetDevice();

        if (Response !=0){
            //logger->error("[E6:STRESET] Running command Reset failed");
        }

        //logger->debug("[E6:STRESET] Running CMDSTARTPOLL");
        Response = CheckEventReset();

        if (Response != 0){
            return 1;            
        }

        return 0;  
    }

    int PelicanoClass::StError() {
        int Response = -1;

        Response = SimplePoll();

       if (Response != 0){
        //logger->debug("[E7: STERROR] Simple Poll Successfuly");
        return 1;
       }
       return 0;
    }

    // --------------- MAIN FUNCTIONS --------------------//

    //Connects to port /dev/ttyUSB% where % is the port number (Port)
    int PelicanoClass::ConnectSerial(int Port){

        if (Port<0){
            // logger->error("[ConnectSerial] Invalid port!");
            return 1;
        }
        else {
            // logger->debug("[ConnectSerial] Connecting to /dev/ttyUSB{0:d} port",Port);
            char DeviceName [50];
            sprintf (DeviceName,"/dev/ttyUSB%d",Port);
            SerialPort = open(DeviceName, O_RDWR | O_NOCTTY );

            if (SerialPort > 0){

                struct termios Tty;

                //Read existing settings, and handle any error
                if(tcgetattr(SerialPort, &Tty) != 0) {
                    // logger->error("[ConnectSerial] Error reading actual settings in this port. Error: {0:d}, from tcgetattr: {1}",errno,strerror(errno));
                    SuccessConnect = false;
                    return 2;
                }

                Tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
                Tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
                Tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size 
                Tty.c_cflag |= CS8; // 8 bits per byte (most common)
                Tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
                Tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

                Tty.c_cc[VTIME] = 10; // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
                Tty.c_cc[VMIN] = 0; // Wait from time 0

                cfsetispeed(&Tty, B9600); //Set IN baud rate in 9600
                cfsetospeed(&Tty, B9600); //Set OUT baud rate in 9600

                //Save existing settings, and handle any error
                if (tcsetattr(SerialPort, TCSANOW, &Tty) != 0) {
                    // logger->error("[ConnectSerial] Error writing new settings in this port. Error: {0:d}, from tcgetattr: {1}",errno,strerror(errno));
                    SuccessConnect = false;
                    return 3;
                }

                // logger->debug("[ConnectSerial] Successfully connected to /dev/ttyUSB{0:d}",Port);
                SuccessConnect = true;
                return 0;
            }
            else{
                // logger->debug("[ConnectSerial] Could no connect to /dev/ttyUSB{0:d}",Port);
                return 4;
            }
        }
    }

    //Scan all /dev/ttyUSB ports from 0 to MAXPORTS
    int PelicanoClass::ScanPorts(){
        int Port = -1;
        int Response = -1;

        for (int i=1;i<MAXPORTS;i++)
        {   
            // logger->debug("[ScanPorts] Trying connection to /dev/ttyUSB{0:d}",i-1);
            Response = ConnectSerial(i-1);

            if (Response==0)
            {   
                // logger->debug("[ScanPorts] Connection successfull");
                Response = -1;
                Scanning = true;
                // logger->debug("[ScanPorts] Sending simple poll Command (Checking connection)");

                Response = SimplePoll();

                if (Response == 0){
                    Port = i-1;
                    // logger->debug("[ScanPorts] Acceptor Pelicano found in port /dev/ttyUSB{0:d}",Port);
                    i=MAXPORTS;
                    Scanning = false;
                    return Port;
                }
                else{
                    // logger->warn("[ScanPorts] Error in writing/reading or acceptor Pelicano is NOT connected to /dev/ttyUSB{0:d} port",i-1);
                }

                // logger->debug("[ScanPorts] Clossing connection in /dev/ttyUSB{0:d}",i-1);
                close(SerialPort);            
            }
        }
        Scanning = false;
        // logger->error("[ScanPorts] Acceptor was not found in any port!");
        return Port;
    }

    int PelicanoClass::SendingCommand(unsigned char* Comm, int Xlen){

        int Response = 2;
        int Res = 1;

        Response = ExecuteCommand(Comm,Xlen);

        ErrorCodeExComm_t Err;
        Err = SearchErrorCodeExComm(Response);

        // logger->debug("[SendingCommand] Execute command returns: {0:d} with message: {1}",Err.Code,Err.Message);

        if(Response == 0){
            // logger->trace("[SendingCommand] Everything is OK");
            Res = 0;
        }
        else if((Response == -5)|(Response == -4)|(Response == 1)){
            // logger->debug("[SendingCommand] Error with comand");
            Res = -1;
        }
        else if(Response == 4){
            // logger->debug("[SendingCommand] Polling error");
            Res = -2;
        }
        else{
            // logger->debug("[SendingCommand] Repeat command");
            Res = 1;
        }

        return Res;

    }

    int PelicanoClass::ExecuteCommand(unsigned char* Comm, int Xlen){
        
        int Wrlen = -1;
        int Rdlen = -1;
        int Res = -6;
        unsigned char Buffer [100];

        // logger->trace("[ExecuteCommand] Writting command");
        Wrlen = write(SerialPort, Comm, Xlen);

        if(Wrlen!=Xlen){
            // logger->warn("[ExecuteCommand] Writting error, length expect/received: {0:d}/{1:d} Error: {2}",Xlen,Wrlen,strerror(errno));
            Res = -5;
        }
        else{
            // logger->trace("[ExecuteCommand] Length expected is the same: {0:d}",Wrlen);
            
            usleep(100000);

            // logger->trace("[ExecuteCommand] Reading response");
            Rdlen = read(SerialPort,Buffer,sizeof(Buffer));

            if(Rdlen > 0){

                // logger->debug("[ExecuteCommand] Reading length: {0:d}",Rdlen);

                if (Rdlen >= Xlen){
                    // logger->trace("[ExecuteCommand] Reading length greater or equal than {0}, handling response... ",Xlen);
                    Res = HandleResponse(Buffer,Rdlen,Xlen);
                }
                else if(Rdlen == Xlen-1){
                    // logger->warn("[ExecuteCommand] Reading length equal than {0}, not recognized... ",Xlen);
                    Res = 6;   
                }
                else{
                    // logger->warn("[ExecuteCommand] Reading length less than {0}, very little waiting time ",Xlen);
                    Res = 5;
                }
            }
            else if (Rdlen < 0){
                // logger->warn("[ExecuteCommand] Reading error, length expect: {0:d} Error: {1}",Rdlen,strerror(errno));
                Res = -4;
            }
            else {
               // logger->warn("[ExecuteCommand] Not responding, timeout!");
                Res = -3;
            }
        }

        if((Res!=0)&(Res!=4)){
            ioctl(SerialPort, TCFLSH, 2);
        }

        return Res;
    }

    int PelicanoClass::HandleResponse(unsigned char* Response, int Rdlen, int Xlen){

        unsigned char *Pointer;
        int Res = -6;

        if (Rdlen >= (Xlen+4)){
            // logger->trace("[HandleResponse] Message seems to be complete");
            Pointer = Response;
            Pointer = Pointer + Xlen + 2;
            if (*Pointer == 0){
                // logger->trace("[HandleResponse] ACK Received!");
                Pointer = Response;
                Pointer = Pointer + 3;
                if ((Rdlen >= Xlen+15)&((*Pointer == 229))){
                    // logger->trace("[HandleResponse] Polling detected, searching response error");
                    Res = HandleResponsePolling(Response,Rdlen);
                }
                else if((*Pointer == 236)|(*Pointer == 232)){
                    // logger->trace("[HandleResponse] Self check or Read opto states detected, searching more info");
                    Res = HandleResponseInfo(Response,Rdlen);
                }
                else if((*Pointer == 231)|(*Pointer == 239)|(*Pointer == 228)|(*Pointer == 254)|(*Pointer == 1)){
                    // logger->trace("[HandleResponse] No more information to check!");
                    Res = 0;
                }
                else{
                    // logger->warn("[HandleResponse] Polling response incomplete!");
                    Res = 2;
                }
            }
            else if(*Pointer == 5){
                // logger->warn("[HandleResponse] Negative ACK Received...");  
                Res = -1;
            }
            else if(*Pointer == 6){
                // logger->warn("[HandleResponse] Acceptor is BUSY!");  
                Res = -2;
            }
            else{
                // logger->error("[HandleResponse] Uknown code in ACK position!");  
                Res = 1;
            }
        }
        else{
            // logger->debug("[HandleResponse] Message is NOT complete!!!");
            Res = 2;
        }
        return Res;
    }

    int PelicanoClass::HandleResponsePolling(unsigned char* Response, int Rdlen){

        unsigned char *Pointer;
        CriticalError = false;
        int Remaining = 0;

        int Res = -6;

        CoinCinc = 0;
        CoinCien = 0;
        CoinDosc = 0;
        CoinQuin = 0;
        CoinMil = 0;

        int Data = 0;
        int k=1;

        Pointer = Response;

        ErrorHappened = false;

        Pointer = Pointer + 6;

        if (*Pointer == 11){

            // logger->trace("[HandleResponsePolling] Data is correct!");

            Pointer = Pointer + 3;
            CoinEvent = *Pointer;

            if(CoinEvent != CoinEventPrev){
                
                Remaining = CoinEvent-CoinEventPrev;

                // logger->debug("[HandleResponsePolling] CoinEvent: {0} CoinEventPrev: {1}",CoinEvent,CoinEventPrev);

                if (Remaining > 1){
                    // logger->debug("[HandleResponsePolling] Remaining events: {0}",Remaining);
                    for (int i = 0; i<2*Remaining; i++){
                        // logger->debug("[HandleResponsePolling] Counters, i:{0} k:{1}",i,k);
                        Pointer++;
                        Data = *Pointer;
                        // logger->debug("[HandleResponsePolling] Data: {0}",Data);
                        if( (Data == 0) & (i== 2*(k-1) ) ){
                            ErrorHappened = true;
                        }
                        else if( (Data > 0) & (Data <= 5) & (i== 2*(k-1)) ){
                            ActCoin = SearchCoin(Data);
                            // logger->debug("[HandleResponsePolling] Coin: {0}",ActCoin.Coin);
                            if (ActCoin.Coin == 50){
                                CoinCinc++;
                            }
                            else if(ActCoin.Coin == 100){
                                CoinCien++;
                            }
                            else if(ActCoin.Coin == 200){
                                CoinDosc++;
                            }
                            else if(ActCoin.Coin == 500){
                                CoinQuin++;
                            }
                            else if(ActCoin.Coin == 1000){
                                CoinMil++;
                            }
                            k++;
                        }

                        if( (i == ((2*k)-1)) & (ErrorHappened) ){
                            ErrPPrev = SearchErrorCodePolling(Data);
                            k++;
                            if(ErrPPrev.Critical == 1){
                                CriticalError = true;
                                ErrorHappened = true;
                                ErrP = ErrPPrev;
                                //i = 10;
                            }
                            if(CriticalError == false){
                                ErrP = ErrPPrev;
                            }
                        }
                    }
                }
                else{
                    for (int i = 0; i<10; i++){
                        Pointer++;
                        Data = *Pointer;

                        if((Data == 0)&(i==0)){
                            ErrorHappened = true;
                        }
                        else if(i==0){
                            ActCoin = SearchCoin(Data);
                        }

                        if((i==1)&(ErrorHappened)){
                            ErrP = SearchErrorCodePolling(Data);
                        }
                    } 
                }

                if(ErrorHappened|CriticalError){

                    ErrorOCode = ErrP.Code;
                    ErrorOMsg = ErrP.Message.c_str();
                    ErrorORejected = ErrP.Rejected;
                    ErrorOCritical = ErrP.Critical;
 
                    // logger->error("[HandleResponsePolling] ----------> Error happened!");
                    // logger->error("[HandleResponsePolling] Error code: {0}",ErrP.Code);
                    // logger->error("[HandleResponsePolling] Error message: {0}",ErrP.Message);
                    // logger->trace("[HandleResponsePolling] Error rejected: {0}",ErrP.Rejected);
                    // logger->trace("[HandleResponsePolling] Error critical: {0}",ErrP.Critical);

                    Res = 4;
                }
                else{

                    ActOCoin = ActCoin.Coin;
                    ActOChannel = ActCoin.Channel;

                    // logger->trace("[HandleResponsePolling] ----------> Coin detected");
                    // logger->debug("[HandleResponsePolling] Coin: {0}",ActCoin.Coin);
                    // logger->trace("[HandleResponsePolling] Coin Channel: {0}",ActCoin.Channel);

                    Res = 0;
                }
                
                Pointer = Response;
                Pointer = Pointer + 9;

                for (int i = 0; i<10; i++){
                    Pointer++;
                    // logger->debug("[HandleResponsePolling] Data: {0}",*Pointer);
                }

                CoinEventPrev = CoinEvent;
            }   
            else{
                // logger->trace("[HandleResponsePolling] Actual coin event is identical to coin event prev");
                Res = 0;
            }
        }
        else{
            // logger->debug("[HandleResponsePolling] Data is not correct!");
            Res = 3;
        }
        return Res;
    }

    int PelicanoClass::HandleResponseInfo(unsigned char* Response, int Rdlen){
        
        int Res = -6;

        unsigned char *Pointer;
        int FaultCode = 0;
        Pointer = Response;
        Pointer = Pointer + 3;

        if (*Pointer == 232){
            // logger->trace("[HandleResponseInfo] Self check detected, checking fault code");
            Pointer = Pointer + 6;
            int FaultCode = -1;
            FaultCode = *Pointer;
            FaultC = SearchFaultCode(FaultCode);
            FaultOCode = FaultC.Code;
            FaultOMsg = FaultC.Message.c_str();
        //    logger->debug("[HandleResponseInfo] Fault code: {0}",FaultC.Code);
        //    logger->debug("[HandleResponseInfo] Fault message: {0}",FaultC.Message);
            
            Res = 0;
        }
        else if(*Pointer == 236){
            // logger->trace("[HandleResponseInfo] Read opto states detected, checking bit mask");
            Pointer = Pointer + 6;
            int StateMask = 0;
            StateMask = *Pointer;

            std::bitset<4> Bits(StateMask);

            CoinPresent = Bits[0];
            TrashDoorOpen = Bits[1];
            LowerSensorBlocked = Bits[2];
            UpperSensorBlocked = Bits[3];

            if (errno == 0){
                if(CoinPresent){
                    // logger->trace("[HandleResponseInfo] There is something in bowl");
                }
                else{
                    // logger->trace("[HandleResponseInfo] Bowl is empty!");
                }

                if(TrashDoorOpen){
                    // logger->trace("[HandleResponseInfo] Trash door is open");
                }
                else{
                    // logger->trace("[HandleResponseInfo] Trash door is close");
                }

                if(LowerSensorBlocked){
                    // logger->trace("[HandleResponseInfo] Lower sensor (Accept & Reject path) is blocked");
                }
                else{
                    // logger->trace("[HandleResponseInfo] Lower sensor (Accept & Reject path) is clear");
                }

                if(UpperSensorBlocked){
                    // logger->trace("[HandleResponseInfo] Upper sensor (Accept path) is blocked");
                }
                else{
                    // logger->trace("[HandleResponseInfo] Upper sensor (Accept path) is clear");
                }

                Res = 0;
            }
            else{
                // logger->warn("[ExecuteCommand] Reading error, Code error: {0} Error: {1}",errno,strerror(errno));
                Res = -4;
            }
            
        }

        return Res;
    }

    int PelicanoClass::CheckOptoStates(){

        int Response  = -2;

        // logger->debug("[CheckOptoStates] Reading opto states");
        // logger->trace("[CheckOptoStates] Running CMDREADOPTOST");
        
        Response = SendingCommand(CMDREADOPTOST,6);
        
        if (Response == 0){
            if ( CoinPresent | TrashDoorOpen ){
                // logger->warn("[CheckOptoStates] There is something in the bowl or trash door was opened ");
                Response = 2;
            }
            if ( LowerSensorBlocked | UpperSensorBlocked ){
                // logger->critical("[CheckOptoStates] Lower or upper sensor is blocked");
                Response = 1;
            }
        }
        else{
            if (Response != -1){
                // logger->error("[CheckOptoStates] Repeat command, command was not run successfully");
                Response = -2;
            }
            else{
                // logger->critical("[CheckOptoStates] Error sending command");
                Response = -1;
            }
        }

        // logger->trace("[CheckOptoStates] Optostates return: Everything is OK");
        return Response;
    }

    int PelicanoClass::SimplePoll(){

        int Response  = -1;

        // logger->debug("[SimplePoll] Checking communication");
        // logger->trace("[SimplePoll] Running CMDSIMPLEPOLL");
        
        Response = SendingCommand(CMDSIMPLEPOLL,6);

        if (Response == -1){
            // logger->error("[SimplePoll] Acceptor does not return ACK!");
            return -1;
        }
        else if(Response >= 1){
            // logger->warn("[SimplePoll] Running CMDSIMPLEPOLL again .......");
            Response = SendingCommand(CMDSIMPLEPOLL,6);
            if (Response != 0){
                // logger->error("[SimplePoll] Acceptor does not return ACK!");
                return -1;
            }
        }

        //logger->trace("[SimplePoll] Acceptor return ACK successfully");
        return 0;
    }

    int PelicanoClass::SelfCheck(){
        
        int Response = -1;

        // logger->debug("[SelfCheck] Running initial revision");
        // logger->trace("[SelfCheck] Running CMDSELFCHECK");
        
        Response = SendingCommand(CMDSELFCHECK,6);

        if (Response == 0){
            if ((FaultOCode == 253)|(FaultOCode == 254)){
                //logger->critical("[SelfCheck] Acceptor blocked, code: {0}",FaultOCode);
                return 1;
            }
            else if((FaultOCode == 2)|(FaultOCode == 3)){
                //logger->critical("[SelfCheck] Hardware error, code: {0}",FaultOCode);
                return 2;
            }
            else if((FaultOCode == 1)|(FaultOCode == 30)|(FaultOCode == 255)){
                //logger->critical("[SelfCheck] Software error, code: {0}",FaultOCode);
                return 3;
            }
        }
        else{
            if (Response != -1){
                //logger->error("[SelfCheck] Repeat command, command was not run successfully");
                return -2;
            }
            else{
                //logger->critical("[SelfCheck] Error sending command");
                return -1;
            }
        }

        //logger->trace("[SimplePoll] Acceptor return faultcode: OK");
        return 0;
    }

    int PelicanoClass::EnableChannels(){
        
        int Response  = -1;

        // logger->debug("[EnableChannels] Enabling coins");
        // logger->trace("[EnableChannels] Running CMDENABLE");

        Response = SendingCommand(CMDENABLE,8);

        if (Response != 0){
            //logger->error("[EnableChannels] Acceptor could not enable all coins!");
            return -1;
        }

        //logger->trace("[EnableChannels] Acceptor has all coins enabled");
        return 0;
    }

    int PelicanoClass::StartMotor(){

        int Response  = -1;

        // logger->debug("[StartMotor] Starting motor");
        // logger->trace("[StartMotor] Running CMDSTARTMOTOR");

        Response = SendingCommand(CMDSTARTMOTOR,7);

        if (Response != 0){
            //logger->error("[StartMotor] Problem running start motor command!");
            return -1;
        }

        //logger->trace("[EnableChannels] Motor is running");
        return 0;
    }

    int PelicanoClass::CheckEventReset(){
        
        int Response = 2;

        // logger->debug("[CheckEventReset] Reading coin event");
        // logger->trace("[CheckEventReset] Running CMDSTARTPOLL");

        Response = SendingCommand(CMDSTARTPOLL,6);

        if ((Response == 0)|(Response == -2)){
            if ((CoinEvent == 0)|(CoinEvent == 1)){
                //logger->debug("[CheckEventReset] CoinEvent is OK: {0}",CoinEvent);
            }
            else{
                //logger->error("[CheckEventReset] CoinEvent is not OK");
                return 1;
            }
        }
        else{
            if (Response != -1){
                //logger->error("[CheckEventReset] Repeat command, command was not run successfully");
                return -2;
            }
            else{
                //logger->critical("[CheckEventReset] Error sending command");
                return -1;
            }
        }

        //logger->trace("[CheckEventReset] Coin event is ready");
        return 0;
        
    }

    int PelicanoClass::CleanBowl(){

        int Response = 2;

        //logger->debug("[CleanBowl] Cleaning bowl");
        //logger->trace("[CleanBowl] Running CMDCLEANBOWL");

        Response = SendingCommand(CMDCLEANBOWL,7);
        
        sleep(7);

        if (Response != 0){
            //logger->error("[CleanBowl] Cleaning bowl failed");
            return -1;
        }

        sleep(7);

        //logger->trace("[CleanBowl] Cleaning bowl run successfully");

        return 0;
    }

    int PelicanoClass::StopMotor(){

        int Response  = -1;

        // logger->debug("[StopMotor] Starting motor");
        // logger->trace("[StopMotor] Running CMDSTARTMOTOR");

        Response = SendingCommand(CMDSTOPMOTOR,7);

        if (Response != 0){
           // logger->error("[StopMotor] Problem running stop motor command!");
            return -1;
        }

        // logger->trace("[StopMotor] Motor was stopped");

        return 0;
    }

    int PelicanoClass::ResetDevice(){

        int Response  = -1;

        // logger->debug("[ResetDevice] Reset device running");
        // logger->trace("[ResetDevice] Running CMDRESETDEVICE");

        Response = SendingCommand(CMDRESETDEVICE,6);

        if (Response !=0){
            //logger->error("[ResetDevice] Running command Reset failed");
            return -1;
        }
        
        //logger->trace("[StopMotor] Device was rebooted");

        return 0;
    }
}