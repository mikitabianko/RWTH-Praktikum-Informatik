//////////////////////////////////////////////////////////////////////////////
// Praktikum Informatik 1 MMXXVI
//////////////////////////////////////////////////////////////////////////////

#ifndef _LISTENELEMENT_H_
#define _LISTENELEMENT_H_

#include "Student.h"

/**
 * @brief Ein Element der doppelt verketteten Liste.
 */
class ListenElement
{
private:
    Student data;
    ListenElement* next;
    ListenElement* previous;

public:
    ListenElement(Student pData, ListenElement* pNext, ListenElement* pPrevious);

    void setData(Student pData);
    void setNext(ListenElement* pNext);
    void setPrevious(ListenElement* pPrevious);

    Student getData() const;
    ListenElement* getNext() const;
    ListenElement* getPrevious() const;
};

#endif
