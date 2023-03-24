#include <gtest/gtest.h>
#include "../ValidatorPelicano.hpp"


//--------------CMDS----------//
unsigned char CMDSTARTPOLL[6]     = {"\x02\x00\x01\xE5\x18"};         // 5 + 16(add+data+add+ack+event+pair1+pair2+pair3+pair4+pair5+chk)

ValidatorPelicano::PelicanoClass PelicanoObject;

int TestFunctionPass1(){

    int Response = -1;
    PelicanoObject.ConnectSerial(0);
    PelicanoObject.ScanPorts();
    PelicanoObject.SendingCommand(CMDSTARTPOLL,6);
    Response = PelicanoObject.StPolling();
    return Response;
}

int TestFunctionFail1(){

    int Response = -3;
    PelicanoObject.ConnectSerial(0);
    PelicanoObject.ScanPorts();
    PelicanoObject.SendingCommand(CMDSTARTPOLL,6);
    Response = PelicanoObject.StPolling();   
    return Response;
}

int TestFunctionFail2(){

    int Response = -3;
    PelicanoObject.ConnectSerial(0);
    PelicanoObject.ScanPorts();
    PelicanoObject.SendingCommand(CMDSTARTPOLL,6);
    Response = PelicanoObject.StPolling();   
    return Response;
}

int TestFunctionFail3(){

    int Response = -3;
    PelicanoObject.ConnectSerial(0);
    PelicanoObject.ScanPorts();
    PelicanoObject.SendingCommand(CMDSTARTPOLL,6);
    Response = PelicanoObject.StPolling();   
    return Response;
}

int TestFunctionFail4(){

    int Response = -3;
    PelicanoObject.ConnectSerial(0);
    PelicanoObject.ScanPorts();
    PelicanoObject.SendingCommand(CMDSTARTPOLL,6);
    Response = PelicanoObject.StPolling();   
    return Response;
}

TEST(Unitest, TestPass1) {
  // Expect equality.
  EXPECT_EQ(TestFunctionPass1(), 0);
}

TEST(Unitest, TestFail1) {
  // Expect equality.
  EXPECT_EQ(TestFunctionFail1(), -2);
}

TEST(Unitest, TestFail2) {
  // Expect equality.
  EXPECT_EQ(TestFunctionFail1(), -1);
}

TEST(Unitest, TestFail3) {
  // Expect equality.
  EXPECT_EQ(TestFunctionFail1(), 1);
}

TEST(Unitest, TestFail4) {
  // Expect equality.
  EXPECT_EQ(TestFunctionFail1(), 2);
}
