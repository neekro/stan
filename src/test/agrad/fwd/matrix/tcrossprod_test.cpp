#include <stan/agrad/fwd/matrix/tcrossprod.hpp>
#include <gtest/gtest.h>
#include <stan/agrad/fwd/matrix/typedefs.hpp>
#include <stan/agrad/fwd/matrix/multiply.hpp>
#include <stan/math/matrix/transpose.hpp>

TEST(AgradFwdMatrix, tcrossprod_3x3_matrix) {
  using stan::agrad::matrix_fv;
  using stan::math::matrix_d;
  matrix_d Z(3,3);
  Z << 1, 0, 0,
    2, 3, 0,
    4, 5, 6;
  matrix_fv Y(3,3);
  Y << 1, 0, 0,
    2, 3, 0,
    4, 5, 6;
   Y(0,0).d_ = 2.0;
   Y(0,1).d_ = 2.0;
   Y(0,2).d_ = 2.0;
   Y(1,0).d_ = 2.0;
   Y(1,1).d_ = 2.0;
   Y(1,2).d_ = 2.0;
   Y(2,0).d_ = 2.0;
   Y(2,1).d_ = 2.0;
   Y(2,2).d_ = 2.0;
  matrix_d X = Z * Z.transpose();
  matrix_fv output = stan::agrad::tcrossprod(Y);
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++)
      EXPECT_FLOAT_EQ(X(i,j), output(i,j).val_);
  }

  EXPECT_FLOAT_EQ( 4,output(0,0).d_);
  EXPECT_FLOAT_EQ(12,output(0,1).d_);
  EXPECT_FLOAT_EQ(32,output(0,2).d_);
  EXPECT_FLOAT_EQ(12,output(1,0).d_);
  EXPECT_FLOAT_EQ(20,output(1,1).d_);
  EXPECT_FLOAT_EQ(40,output(1,2).d_);
  EXPECT_FLOAT_EQ(32,output(2,0).d_);
  EXPECT_FLOAT_EQ(40,output(2,1).d_);
  EXPECT_FLOAT_EQ(60,output(2,2).d_);
}
TEST(AgradFwdMatrix, tcrossprod_2x2_matrix) {
  using stan::agrad::matrix_fv;
  using stan::math::matrix_d;
  matrix_d Z(2,2);
  Z <<3, 0,
     4, -3;
  matrix_fv Y(2,2);
  Y << 3, 0,
     4, -3;
   Y(0,0).d_ = 2.0;
   Y(0,1).d_ = 2.0;
   Y(1,0).d_ = 2.0;
   Y(1,1).d_ = 2.0;
  matrix_d X = Z * Z.transpose();
  matrix_fv output = stan::agrad::tcrossprod(Y);
  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 2; j++)
      EXPECT_FLOAT_EQ(X(i,j), output(i,j).val_);
  }

  EXPECT_FLOAT_EQ(12,output(0,0).d_);
  EXPECT_FLOAT_EQ( 8,output(0,1).d_);
  EXPECT_FLOAT_EQ( 8,output(1,0).d_);
  EXPECT_FLOAT_EQ( 4,output(1,1).d_);
}
TEST(AgradFwdMatrix, tcrossprod_1x1_matrix) {
  using stan::agrad::matrix_fv;

  matrix_fv Y(1,1);
  Y << 3;
   Y(0,0).d_ = 2.0;
  matrix_fv output = stan::agrad::tcrossprod(Y);
  EXPECT_FLOAT_EQ( 9, output(0,0).val_);
  EXPECT_FLOAT_EQ(12, output(0,0).d_);
}
TEST(AgradFwdMatrix, tcrossprod_1x3_matrix) {
  using stan::agrad::matrix_fv;
  using stan::math::matrix_d;

  matrix_fv Y(1,3);
  Y << 1, 2,3;
   Y(0,0).d_ = 2.0;
   Y(0,1).d_ = 2.0;
   Y(0,2).d_ = 2.0;
  matrix_fv output = stan::agrad::tcrossprod(Y);

  EXPECT_FLOAT_EQ(14, output(0,0).val_); 
  EXPECT_FLOAT_EQ(24,output(0,0).d_);
}
TEST(AgradFwdMatrix, tcrossprod_2x3_matrix) {
  using stan::agrad::matrix_fv;
  using stan::math::matrix_d;

  matrix_fv Y(2,3);
  Y << 1, 2,3,
    -1, 4, -9;
   Y(0,0).d_ = 2.0;
   Y(0,1).d_ = 2.0;
   Y(0,2).d_ = 2.0;
   Y(1,0).d_ = 2.0;
   Y(1,1).d_ = 2.0;
   Y(1,2).d_ = 2.0;
  matrix_fv output = stan::agrad::tcrossprod(Y);

  EXPECT_FLOAT_EQ( 14, output(0,0).val_); 
  EXPECT_FLOAT_EQ(-20, output(0,1).val_); 
  EXPECT_FLOAT_EQ(-20, output(1,0).val_); 
  EXPECT_FLOAT_EQ( 98, output(1,1).val_);
  EXPECT_FLOAT_EQ( 24, output(0,0).d_); 
  EXPECT_FLOAT_EQ(  0, output(0,1).d_); 
  EXPECT_FLOAT_EQ(  0, output(1,0).d_); 
  EXPECT_FLOAT_EQ(-24, output(1,1).d_); 
}
TEST(AgradFwdMatrix, tcrossprod_3x2_matrix) {
  using stan::agrad::matrix_fv;
  using stan::math::matrix_d;

  matrix_fv Y(3,2);
  Y << 1, 2,3,
    -1, 4, -9;
   Y(0,0).d_ = 2.0;
   Y(0,1).d_ = 2.0;
   Y(1,0).d_ = 2.0;
   Y(1,1).d_ = 2.0;
   Y(2,0).d_ = 2.0;
   Y(2,1).d_ = 2.0;
  matrix_fv output = stan::agrad::tcrossprod(Y);

  EXPECT_FLOAT_EQ( 5, output(0,0).val_); 
  EXPECT_FLOAT_EQ( 1, output(0,1).val_); 
  EXPECT_FLOAT_EQ( 1, output(1,0).val_); 
  EXPECT_FLOAT_EQ(10, output(1,1).val_);
  EXPECT_FLOAT_EQ(12, output(0,0).d_); 
  EXPECT_FLOAT_EQ(10, output(0,1).d_); 
  EXPECT_FLOAT_EQ(10, output(1,0).d_); 
  EXPECT_FLOAT_EQ( 8, output(1,1).d_); 
}
