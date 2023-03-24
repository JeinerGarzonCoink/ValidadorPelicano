#include <gtest/gtest.h>
#include "../ValidatorPelicano.hpp"

ValidatorPelicano::PelicanoClass PelicanoObject;

int TestFunctionPass1(){

    int Response = -1;
    PelicanoObject.ConnectSerial(0);
    PelicanoObject.SimplePoll();
    PelicanoObject.SelfCheck();
    PelicanoObject.CheckOptoStates();
    Response = PelicanoObject.StCheck();
    return Response;
}

int TestFunctionFail1(){

    int Response = -1;
    PelicanoObject.ConnectSerial(0);
    PelicanoObject.SimplePoll();
    PelicanoObject.SelfCheck();
    PelicanoObject.CheckOptoStates();
    Response = PelicanoObject.StCheck();    
    return Response;
}

int TestFunctionFail2(){

    int Response = -1;
    PelicanoObject.ConnectSerial(0);
    PelicanoObject.SimplePoll();
    PelicanoObject.SelfCheck();
    PelicanoObject.CheckOptoStates();
    Response = PelicanoObject.StCheck();    
    return Response;
}

TEST(UnitTest, TestPass1) {
  // Expect equality.
  EXPECT_EQ(TestFunctionPass1(), 0);
}

TEST(UnitTest, TestFail1) {
  // Expect equality.
  EXPECT_EQ(TestFunctionFail1(), -1);
}

TEST(UnitTest, TestFail2) {
  // Expect equality.
  EXPECT_EQ(TestFunctionFail2(), 2);
}
