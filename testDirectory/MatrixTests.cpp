//
// Created by Veronica Pecchioli on 19/01/19.
//

#include "gtest/gtest.h"

#include "../Matrix.h"



TEST(Matrix_Constructors, RowsCols_Constructor){

    Matrix<int> M(3,4);

    ASSERT_EQ(3,M.get_rows());
    ASSERT_EQ(4, M.get_col());

}

TEST(Matrix_Constructors, SquareMatrix_Constructor){

    Matrix<int> M(2);

    ASSERT_EQ(2, M.get_rows());
    ASSERT_EQ(2, M.get_col());

}

TEST(Matrix_Constructors,Vector_Costructor){

    Matrix<int> M (3, {1,2,3,4,5,6,7,8,9});

    ASSERT_EQ(1,M.getValue(0,0));
    ASSERT_EQ(2,M.getValue(0,1));
    ASSERT_EQ(3,M.getValue(0,2));
    ASSERT_EQ(4,M.getValue(1,0));
    ASSERT_EQ(5,M.getValue(1,1));
    ASSERT_EQ(6,M.getValue(1,2));
    ASSERT_EQ(7,M.getValue(2,0));
    ASSERT_EQ(8,M.getValue(2,1));
    ASSERT_EQ(9,M.getValue(2,2));
}

TEST(Matrix_Constructors,Vector_Exception_Costructor){

    ASSERT_THROW(Matrix<int>(3,3,{1,2,3,4}),invalid_argument);
}

TEST(Matrix_Constructors,RowsCols_Exception_Constructor){

    ASSERT_THROW(Matrix<int>(-2,-2),invalid_argument);
}

TEST(Matrix_Constructors,SquareMatrix_Exception_Constructor){

    ASSERT_THROW(Matrix<int>(-3),invalid_argument);
}

