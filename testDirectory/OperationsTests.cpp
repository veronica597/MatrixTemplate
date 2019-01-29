//
// Created by Veronica Pecchioli on 25/01/19.
//

#include "gtest/gtest.h"
#include "../Matrix.h"

class MatrixOperations: public ::testing::Test {

public:

    Matrix<int> A;
    Matrix<int> B;

    MatrixOperations(): A(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}), B(3,3,{2,4,6,8,10,12,14,16,18}) {}

};

TEST_F(MatrixOperations, select_row) {
    Matrix<int> m(1, 3, {1, 2, 3});

    Matrix<int> row = A.select_row(0);

    ASSERT_EQ(row.get_rows(),1);
    ASSERT_EQ(row.get_col(), 3);

    ASSERT_EQ(row.getValue(0,0),m.getValue(0,0));
    ASSERT_EQ(row.getValue(0,1),m.getValue(0,1));
    ASSERT_EQ(row.getValue(0,2),m.getValue(0,2));
}

TEST_F(MatrixOperations,select_rowException){

    ASSERT_THROW(A.select_row(4), out_of_range);
}

TEST_F(MatrixOperations, select_col){
    Matrix <int> m(3,1,{1,4,7});

    Matrix<int> col = A.select_column(0);

    ASSERT_EQ(col.get_rows(),3);
    ASSERT_EQ(col.get_col(),1);

    ASSERT_EQ(col.getValue(0,0),m.getValue(0,0));
    ASSERT_EQ(col.getValue(1,0),m.getValue(1,0));
    ASSERT_EQ(col.getValue(2,0),m.getValue(2,0));
}

TEST_F(MatrixOperations, select_columnException){
    ASSERT_THROW(B.select_column(-1),out_of_range);
}

TEST_F(MatrixOperations, sum){
    Matrix<int> sum (3,3,{3,6,9,12,15,18,21,24,27});

    Matrix<int> s= A+B;

    ASSERT_EQ(s.getValue(0,0),sum.getValue(0,0));
    ASSERT_EQ(s.getValue(0,1),sum.getValue(0,1));
    ASSERT_EQ(s.getValue(0,2),sum.getValue(0,2));
    ASSERT_EQ(s.getValue(1,0),sum.getValue(1,0));
    ASSERT_EQ(s.getValue(1,1),sum.getValue(1,1));
    ASSERT_EQ(s.getValue(1,2),sum.getValue(1,2));
    ASSERT_EQ(s.getValue(2,0),sum.getValue(2,0));
    ASSERT_EQ(s.getValue(2,1),sum.getValue(2,1));
    ASSERT_EQ(s.getValue(2,2),sum.getValue(2,2));
}

TEST_F(MatrixOperations,SumException){
    Matrix <int> m(2);
    ASSERT_THROW(A+m,invalid_argument);
}

TEST_F(MatrixOperations, mul){
    Matrix<int> mul (3,3,{60,72,84,132,162,192,204,252,300});

    Matrix<int> p=A*B;

    ASSERT_EQ(p.getValue(0,0),mul.getValue(0,0));
    ASSERT_EQ(p.getValue(0,1),mul.getValue(0,1));
    ASSERT_EQ(p.getValue(0,2),mul.getValue(0,2));
    ASSERT_EQ(p.getValue(1,0),mul.getValue(1,0));
    ASSERT_EQ(p.getValue(1,1),mul.getValue(1,1));
    ASSERT_EQ(p.getValue(1,2),mul.getValue(1,2));
    ASSERT_EQ(p.getValue(2,0),mul.getValue(2,0));
    ASSERT_EQ(p.getValue(2,1),mul.getValue(2,1));
    ASSERT_EQ(p.getValue(2,2),mul.getValue(2,2));
}

TEST_F(MatrixOperations,MulException){
    Matrix<int>m(2);
    ASSERT_THROW(A*m,invalid_argument);
}

TEST_F(MatrixOperations,Det){
    Matrix<float>m(3,3,{1,3,5,7,8,9,11,2,14});

    ASSERT_EQ(m.det(),-273);
}

TEST_F(MatrixOperations, DetException){
    Matrix<int> m(2,3);
    ASSERT_THROW(m.det(), invalid_argument);
}

TEST_F(MatrixOperations,Rank){

    ASSERT_EQ(A.rank(),2);
    ASSERT_EQ(B.rank(),2);
}

TEST_F(MatrixOperations,Max){
    ASSERT_EQ(A.max(),9);
    ASSERT_EQ(B.max(),18);
}

TEST_F(MatrixOperations,Min){
    ASSERT_EQ(A.min(),1);
    ASSERT_EQ(B.min(),2);
}

TEST_F(MatrixOperations, Gauss){
    Matrix<int> m(3,3,{1,2,3,0,-3,-6,0,0,0});
    Matrix<int> gauss=A.Gauss();

    ASSERT_EQ(gauss.getValue(0,0),m.getValue(0,0));
    ASSERT_EQ(gauss.getValue(0,1),m.getValue(0,1));
    ASSERT_EQ(gauss.getValue(0,2),m.getValue(0,2));
    ASSERT_EQ(gauss.getValue(1,0),m.getValue(1,0));
    ASSERT_EQ(gauss.getValue(1,1),m.getValue(1,1));
    ASSERT_EQ(gauss.getValue(1,2),m.getValue(1,2));
    ASSERT_EQ(gauss.getValue(2,0),m.getValue(2,0));
    ASSERT_EQ(gauss.getValue(2,1),m.getValue(2,1));
    ASSERT_EQ(gauss.getValue(2,2),m.getValue(2,2));
}

TEST_F(MatrixOperations, GaussException){
    Matrix<int>m(2,3);
    ASSERT_THROW(m.Gauss(),invalid_argument);
}

TEST_F(MatrixOperations, Trasponse){

    Matrix<int> m(3,3,{1,4,7,2,5,8,3,6,9});
    Matrix<int> t=A.trasponse();

    ASSERT_EQ(t.getValue(0,0),m.getValue(0,0));
    ASSERT_EQ(t.getValue(0,1),m.getValue(0,1));
    ASSERT_EQ(t.getValue(0,2),m.getValue(0,2));
    ASSERT_EQ(t.getValue(1,0),m.getValue(1,0));
    ASSERT_EQ(t.getValue(1,1),m.getValue(1,1));
    ASSERT_EQ(t.getValue(1,2),m.getValue(1,2));
    ASSERT_EQ(t.getValue(2,0),m.getValue(2,0));
    ASSERT_EQ(t.getValue(2,1),m.getValue(2,1));
    ASSERT_EQ(t.getValue(2,2),m.getValue(2,2));
}
