#pragma once
#include "ListNode.hpp"
#include <stdexcept>
#include <iostream>

class LinkedList
{
    private:
        ListNode *m_head;
        ListNode *m_current;//Aunque sea el nodo actual. Siempre apuntara al ultimo nodo.
        int m_size;

    public:
        LinkedList();

        LinkedList( const LinkedList &other ) = delete;

        LinkedList operator = ( const LinkedList &other ) = delete;

        ~LinkedList();

        int at( int index) const;

        void append(int newElement );

        void remove( int element );

        int pop( int index = -1 );

        int count( int element ) const;

        int length() const;

        void print() const;

};

LinkedList::LinkedList()
{
    //placeholder de donde inicia nuestra cabecera de la lista
    this->m_head = new ListNode(0);
    this->m_size = 0;
    m_current = m_head;
}

LinkedList::~LinkedList()
{
    if( m_head != nullptr )
    {
        delete m_head;
        m_head = nullptr;
    }
}

int LinkedList::at( int index) const
{
    if ( index >= m_size || index < -1 )
    {
        throw std::runtime_error("index out of range");
    }
    else if ( index == -1)
    {
        return m_current->value();
    }

    int i = 0;
    ListNode *node = m_head->nextNode();
    while( node != nullptr && i < index)
    {
        node = node->nextNode();
        ++i;
    }
    if ( node != nullptr )
    {
        return node->value();
    }
    return -1;

}

void LinkedList::append(int newElement )
{
    ListNode *newNode = new ListNode(newElement);
    m_current->setNextNode(newNode);
    m_current = newNode;
    ++m_size;
}

void LinkedList::remove( int element )
{
    ListNode *node = m_head->nextNode();
    ListNode *prev = m_head;
    while (node != nullptr && node->value() != element)
    {
        prev = node;//Guardamos el nodo previo al encontrado.
        node = node->nextNode();//Si existe aca se guardara el elemento pra una posterior eliminacion.
    }

    if( node != nullptr)
    {
        prev->setNextNode(node->nextNode());
        if( prev->nextNode() == nullptr )
        {
            m_current = prev;
        }

        //Es necesario indicar que su siguiente nodo es nulo. de lo contrario al eliminarlo comienza una reaccion en cadena eliminando todo.
        node->setNextNode(nullptr);
        delete node;

        --m_size;
    }
}

int LinkedList::pop( int index)
{

    if( index >= m_size || index < -1 )
    {
        throw std::runtime_error("index out of range");
        // return -1;
    } 
    else if ( index == -1 ) 
    {
        index = m_size - 1;
    } 

    int i = 0;
    ListNode *node = m_head->nextNode();
    ListNode *prev = m_head;
    while( node != nullptr && i < index )
    {
        ++i;
        prev = node;
        node = node->nextNode();
    }
    if ( node != nullptr )
    {
        int item = node->value();

        //Aca se borra el nodo de nuestra lista
        prev->setNextNode( node->nextNode() );
        if( prev->nextNode() == nullptr )
        {
            m_current = prev;
        }

        //Tambien cabe destacar que las suiguientes dos lineas son solo para limpiar memoria
        node->setNextNode( nullptr );
        delete node;
        --m_size;

        return item;
    }
    else
    {
        throw std::runtime_error("Contact me if this error occurs");
        // return -1;
    }
}

int LinkedList::count( int element ) const
{
    ListNode *node = m_head->nextNode();
    int counter = 0;

    while( node != nullptr )
    {
       if( node->value() == element )
       {
            ++counter;
       }
       node = node->nextNode();
    }
    return counter;
}

int LinkedList::length() const
{
    return m_size;
}

void LinkedList::print() const 
{
    for( int i = 0; i < m_size; i++)
    {
        std::cout << this->at(i) << " ";
    }
    std::cout << "\n";
}