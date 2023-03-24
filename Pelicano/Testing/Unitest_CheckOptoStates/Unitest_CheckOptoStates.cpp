#include <gtest/gtest.h>
#include "../ValidatorPelicano.hpp"

ValidatorPelicano::PelicanoClass PelicanoObject;

int TestFunctionPass1(){

    int Response = -1;
    PelicanoObject.ConnectSerial(0);
    Response = PelicanoObject.CheckOptoStates();
    return Response;
}

int TestFunctionFail1(){

    int Response = -1;
    PelicanoObject.ConnectSerial(0);
    Response = PelicanoObject.CheckOptoStates();  
    return Response;
}

int TestFunctionFail2(){

    int Response = -1;
    PelicanoObject.ConnectSerial(0);
    Response = PelicanoObject.CheckOptoStates();  
    return Response;
}

int TestFunctionFail3(){

    int Response = -1;
    PelicanoObject.ConnectSerial(0);
    Response = PelicanoObject.CheckOptoStates();  
    return Response;
}

int TestFunctionFail4(){

    int Response = -1;
    PelicanoObject.ConnectSerial(0);
    Response = PelicanoObject.CheckOptoStates();  
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
  EXPECT_EQ(TestFunctionFail1(), 2);
}

TEST(UnitTest, TestFail3) {
  // Expect equality.
  EXPECT_EQ(TestFunctionFail1(), -1);
}

TEST(UnitTest, TestFail4) {
  // Expect equality.
  EXPECT_EQ(TestFunctionFail1(), -2);
}