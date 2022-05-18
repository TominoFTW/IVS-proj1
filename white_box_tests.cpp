//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

class MatrixTest : public ::testing::Test
{
protected:
    Matrix matrix;

    std::vector<std::vector< double > > array1x1 = { {1} };

    std::vector<std::vector< double > > array2x3 = {
                                            {1, 2, 3},
                                            {3, 2, 1},
                                            };

    std::vector<std::vector< double > > array3x2 = {
                                            {1, 2},
                                            {-1, 0},
                                            {0, -2},
                                            };



    std::vector<std::vector< double > > array4x4 = {
                                            {0, 1, 2, 3},
                                            {-1000, 1000, 0, 0},
                                            {-0.1, 0.1, 15.6, -15.6},
                                            {-1.1, 1.1, 2018, 111},
                                            };

};



TEST_F(MatrixTest, Construct)
{
    // matice lze vytvorit
    EXPECT_NO_THROW(Matrix());
    EXPECT_NO_THROW(Matrix(1, 1));
    EXPECT_NO_THROW(Matrix(100, 100));
    EXPECT_NO_THROW(Matrix(1234, 1234));
    
    // matice nelze vytvorit
    EXPECT_ANY_THROW(Matrix(0, 0));
    EXPECT_ANY_THROW(Matrix(-10, -10));
}


TEST_F(MatrixTest, setValue)
{
    matrix = Matrix(4,4);
    matrix.set(array4x4);

    EXPECT_TRUE(matrix.set(0, 0, 0));
    EXPECT_TRUE(matrix.set(3, 0, 3));
    EXPECT_TRUE(matrix.set(0, 3, -3));
    EXPECT_TRUE(matrix.set(3, 3, 123));


    EXPECT_FALSE(matrix.set(4, 4, 4));
    EXPECT_FALSE(matrix.set(0, 4, 4));
    EXPECT_FALSE(matrix.set(4, 0, 4));
    EXPECT_FALSE(matrix.set(-1, -1, -1));
}

TEST_F(MatrixTest, setVector1x1)
{
    matrix = Matrix();
    EXPECT_TRUE(matrix.set(array1x1));
    
    EXPECT_FALSE(matrix.set(array3x2));

}

TEST_F(MatrixTest, setVector2x3)
{
    matrix = Matrix(2,3);
    EXPECT_TRUE(matrix.set(array2x3));
    
    EXPECT_FALSE(matrix.set(array3x2));
    EXPECT_FALSE(matrix.set(array4x4));

}

TEST_F(MatrixTest, get)
{
    matrix = Matrix(4,4);
    matrix.set(array4x4);
    
    EXPECT_NO_THROW(matrix.get(0, 0));
    EXPECT_NO_THROW(matrix.get(3, 0));
    EXPECT_NO_THROW(matrix.get(0, 3));
    EXPECT_NO_THROW(matrix.get(3, 3));
    


    EXPECT_ANY_THROW(matrix.get(-1, -1));
    EXPECT_ANY_THROW(matrix.get(-1, 4));
    EXPECT_ANY_THROW(matrix.get(4, -1));
    EXPECT_ANY_THROW(matrix.get(4, 4));

}

/*** Konec souboru white_box_tests.cpp ***/
