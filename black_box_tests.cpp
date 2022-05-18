//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Tomas Behal <xbehal02@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class EmptyTree : public ::testing::Test
{
protected:
    BinaryTree tree;
};

class NonEmptyTree : public ::testing::Test
{
protected:
    virtual void SetUp() {
        int values[] = {1, 2, 5, 7, 8, 11, 14, 15, 16};

        for(int value : values)
            tree.InsertNode(value);
    }

    BinaryTree tree;
};

class TreeAxioms : public ::testing::Test
{
protected:
    virtual void SetUp() {
        int values[] = {1, 2, 5, 7, 8, 11, 14, 15, 16};

        for(int value : values)
            tree.InsertNode(value);
    }

    BinaryTree tree;
};

TEST_F(EmptyTree, InsertNode)
{
    EXPECT_TRUE(tree.GetRoot() == NULL);

    auto state = tree.InsertNode(10);
    auto node1 = state.second;

    ASSERT_FALSE(node1 == NULL);
    EXPECT_EQ(node1->key, 10);
    EXPECT_EQ(tree.GetRoot()->key, 10);

    state = tree.InsertNode(0);
    auto node2 = state.second;

    ASSERT_FALSE(node2 == NULL);
    EXPECT_EQ(node2->key, 0);
    EXPECT_EQ(node1->pRight->key, 0);

    state = tree.InsertNode(-10);
    auto node3 = state.second;

    ASSERT_FALSE(node3 == NULL);
    EXPECT_EQ(node3->key, -10);
    EXPECT_EQ(tree.GetRoot()->key, 0);
    EXPECT_EQ(tree.GetRoot()->color, BLACK);

    //PRAVY ma byt vetsi nez LEVY, child a RED
    EXPECT_EQ(tree.GetRoot()->pRight->key, 10);
    EXPECT_EQ(tree.GetRoot()->pRight->pParent, tree.GetRoot());
    EXPECT_EQ(tree.GetRoot()->pRight->color, RED);

    //LEVY ma byt mensi nez PRAVY, child a RED
    EXPECT_EQ(tree.GetRoot()->pLeft->key, -10);
    EXPECT_EQ(tree.GetRoot()->pLeft->pParent, tree.GetRoot());
    EXPECT_EQ(tree.GetRoot()->pRight->color, RED);
}

TEST_F(EmptyTree, DeleteNode)
{
    EXPECT_FALSE(tree.DeleteNode(10));

    EXPECT_FALSE(tree.DeleteNode(0));

    EXPECT_FALSE(tree.DeleteNode(-10));
}

TEST_F(EmptyTree, FindNode)
{
    EXPECT_TRUE(tree.FindNode(10) == NULL);

    EXPECT_TRUE(tree.FindNode(0) == NULL);

    EXPECT_TRUE(tree.FindNode(-10) == NULL);
}

TEST_F(NonEmptyTree, InsertNode)
{
    EXPECT_FALSE(tree.GetRoot() == NULL);

    auto state = tree.InsertNode(1);
    auto node1 = state.second;

    ASSERT_FALSE(node1 == NULL);
    EXPECT_FALSE(state.first);


    EXPECT_EQ(tree.GetRoot()->color, BLACK);
    EXPECT_EQ(tree.GetRoot()->pRight->color, RED);
    EXPECT_EQ(tree.GetRoot()->pLeft->color, RED);
    /* TODOOOO :sadcat:
    EXPECT_EQ(tree.GetRoot()->pRight->key, 11);
    EXPECT_EQ(tree.GetRoot()->pLeft->key, 2);
    EXPECT_EQ(tree.GetRoot()->pRight->color, RED);
    EXPECT_EQ(tree.GetRoot()->pLeft->color, RED);

    EXPECT_EQ(tree.GetRoot()->pRight->pRight->key, 15);
    EXPECT_EQ(tree.GetRoot()->pRight->pLeft->key, 8);
    EXPECT_EQ(tree.GetRoot()->pRight->pRight->color, BLACK);
    EXPECT_EQ(tree.GetRoot()->pRight->pLeft->color, BLACK);
    
    
    EXPECT_EQ(tree.GetRoot()->pLeft->pRight->key, 5);
    EXPECT_EQ(tree.GetRoot()->pLeft->pLeft->key, 1);
    EXPECT_EQ(tree.GetRoot()->pLeft->pRight->color, BLACK);
    EXPECT_EQ(tree.GetRoot()->pLeft->pLeft->color, BLACK);

    EXPECT_EQ(tree.GetRoot()->pRight->pRight->pRight->key, 16);
    EXPECT_EQ(tree.GetRoot()->pLeft->pRight->pRight->color, BLACK);*/
}

TEST_F(NonEmptyTree, DeleteNode)
{
    int values[] = {1, 2, 5, 7, 8, 11, 14, 15, 16};
    for (int value : values)
    {
        EXPECT_TRUE(tree.DeleteNode(value));
    }

    EXPECT_FALSE(tree.DeleteNode(0));

    EXPECT_FALSE(tree.DeleteNode(-10));

}

TEST_F(NonEmptyTree, FindNode)
{
    int values[] = {1, 2, 5, 7, 8, 11, 14, 15, 16};
    for (int value : values)
    {
        EXPECT_FALSE(tree.FindNode(value) == NULL);
    }

    EXPECT_TRUE(tree.FindNode(0) == NULL);

    EXPECT_TRUE(tree.FindNode(-10) == NULL);
}

TEST_F(TreeAxioms, Axiom1) // Vsechny listove uzly stromu jsou *VZDY* cerne
{
    std::vector<BinaryTree::Node_t *> leafNodes;
    tree.GetLeafNodes(leafNodes);

    for (auto node : leafNodes)
    {
        EXPECT_EQ(node->color, BLACK);
    }
}

TEST_F(TreeAxioms, Axiom2) // Kazdy cerveny uzel muze mit *POUZE* cerne potomky
{
    std::vector<BinaryTree::Node_t *> allNodes;
    tree.GetAllNodes(allNodes);

    for (auto node : allNodes)
    {
        if (node->color == RED)
        {
            ASSERT_FALSE(node->pLeft == NULL);
            ASSERT_FALSE(node->pRight == NULL);
            
            EXPECT_EQ(node->pLeft->color, BLACK);
            EXPECT_EQ(node->pRight->color, BLACK);
        }
    }
}

TEST_F(TreeAxioms, Axiom3) // Vsechny cesty od kazdeho listoveho uzlu ke koreni
{                          // stromu obsahuji *STEJNY* pocet cernych uzlu
    std::vector<BinaryTree::Node_t *> leafNodes;
    tree.GetLeafNodes(leafNodes);
    
    int prevNumOfBlackNodes = 0;
    int numOfBlackNodes = 0;
    int numLeaf = 0; //pocet projitych listu, pouze jako podminka pro radek 235

    BinaryTree::Node_t *loopNode; //uzel pro prochazeni stromem ve smycce 

    for (auto node : leafNodes)
    {
        loopNode = node;
        numOfBlackNodes = 0;

        for (;loopNode != NULL; loopNode = loopNode->pParent)
        {
            if (loopNode->color == BLACK)
                numOfBlackNodes++;
        }
        if (numLeaf++)
            EXPECT_EQ(prevNumOfBlackNodes, numOfBlackNodes);
        
        prevNumOfBlackNodes = numOfBlackNodes;
    }
}

/*** Konec souboru black_box_tests.cpp ***/
