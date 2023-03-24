#include <gtest/gtest.h>
#include "../ValidatorPelicano.hpp"

ValidatorPelicano::PelicanoClass PelicanoObject;

int TestFunctionPass1(){

    int Response = -1;
    
    PelicanoObject.ConnectSerial(0);
    PelicanoObject.StConnect();
    PelicanoObject.CleanBowl();
    PelicanoObject.StopMotor();
    PelicanoObject.CheckOptoStates();
    Response = PelicanoObject.StCleanBowl();

    return Response;
}

int TestFunctionFail1(){

    int Response = -1;

    PelicanoObject.ConnectSerial(0);
    PelicanoObject.StConnect();
    PelicanoObject.CleanBowl();
    PelicanoObject.StopMotor();
    PelicanoObject.CheckOptoStates();
    Response = PelicanoObject.StCleanBowl();
    
    return Response;
}

int TestFunctionFail2(){

    int Response = -1;

    PelicanoObject.ConnectSerial(0);
    PelicanoObject.StConnect();
    PelicanoObject.CleanBowl();
    PelicanoObject.StopMotor();
    PelicanoObject.CheckOptoStates();
    Response = PelicanoObject.StCleanBowl();
    
    return Response;
}

int TestFunctionFail3(){

    int Response = -1;

    PelicanoObject.ConnectSerial(0);
    PelicanoObject.CleanBowl();
    PelicanoObject.StopMotor();
    PelicanoObject.CheckOptoStates();
    Response = PelicanoObject.StCleanBowl();
    
    return Response;
}

TEST(UnitTest, TestPass1) {
  // Expect equality.
  EXPECT_EQ(TestFunctionPass1(), 0);
}

TEST(UnitTest, TestFail1) {
  // Expect equality.
  EXPECT_EQ(TestFunctionFail1(), 1);
}

TEST(UnitTest, TestFail2) {
  // Expect equality.
  EXPECT_EQ(TestFunctionFail2(), 2);
}