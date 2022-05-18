//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Tomas Behal <xbehal02@stud.fit.vutbr.cz>
// $Date:       $2022-02-20
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Tomas Behal
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find/GetHead ...
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "singly linked list", ktera bude splnovat dodane testy
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
    m_pHead = NULL;
}

PriorityQueue::~PriorityQueue()
{
    for(Element_t *element = GetHead(); element != NULL; )
    {
        Element_t *delElement = element;
        element = element->pNext;
        delete delElement;
    }
}

void PriorityQueue::Insert(int value)
{
    Element_t *newElement = new Element_t;
    newElement->pNext = NULL;
    newElement->value = value;
    Element_t *prevElement = new Element_t;

    for(Element_t *element = GetHead(); element != NULL; element = element->pNext)
    {
        //list ma alespon jeden prvek
        if (newElement->value >= element->value)
        {
            //zacatek listu
            if (m_pHead == element)
            {
                m_pHead = newElement;
                newElement->pNext = element;
            }
            //in between
            else if (prevElement->value >= newElement->value)
            {
                newElement->pNext = prevElement->pNext;
                prevElement->pNext = newElement;
            }
            return;
        }
        //list ma alespon jeden prvek, ale je vetsi jak insert value
        else if (newElement->value < element->value)
        {
            if (element->pNext == NULL)
            {
                element->pNext = newElement;
                return;
            }
            else
                prevElement = element;
        }
    }
    //empty
    if (m_pHead == NULL)
            m_pHead = newElement;

}   

bool PriorityQueue::Remove(int value)
{
    if(GetHead() != NULL)
    {
        Element_t *prevElement = new Element_t;
        prevElement->pNext = GetHead();
        prevElement->value = GetHead()->value;
        for(Element_t *element = GetHead(); element != NULL; element = element->pNext)
        {
            Element_t *RemoveElem = Find(value);
            if (RemoveElem != NULL)
            {    
                if (RemoveElem->value == element->value && m_pHead->value != element->value)
                {
                    prevElement->pNext = element->pNext;
                    delete element;
                    return true;
                }
                else if (m_pHead->value == value)
                {
                    if (element->pNext != NULL)
                        m_pHead = element->pNext;
                    else if(element->pNext == NULL)
                        m_pHead = NULL;

                    delete element;
                    return true;
                }
            }
            prevElement = element;
        }
    }
    return false;
}


PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    //list loop
    for(Element_t *element = GetHead(); element != NULL; element = element->pNext)
    {
        if (element->value == value)
        {
            //if element with value is present
            return element;
        }
    }
    //otherwise
    return NULL;
}

size_t PriorityQueue::Length()
{
	size_t len = 0; 
    for(Element_t *element = GetHead(); element != NULL; element = element->pNext)
    {
        len = len + 1;
    }
    return len;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/