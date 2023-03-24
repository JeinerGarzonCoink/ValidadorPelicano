#include <gtest/gtest.h>
#include "../ValidatorPelicano.hpp"

ValidatorPelicano::PelicanoClass PelicanoObject;

int TestFunctionPass1(){

    int Response = -1;
    
    PelicanoObject.ConnectSerial(0);
    PelicanoObject.StConnect();

    Response = PelicanoObject.SelfCheck();

    return Response;
}

int TestFunctionFail1(){

    int Response = -1;

    PelicanoObject.ConnectSerial(1);
    Response = PelicanoObject.SelfCheck();
    
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
