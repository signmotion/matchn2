#pragma once

#include "struct.h"
#include "PoolThread.h"


namespace matchn {


class Event;


class ManagerEvent {
public:
    ManagerEvent();

    virtual ~ManagerEvent();


    void push( std::shared_ptr< Event > );


    /**
    * @return Текущее время, доступное из разных потоков, мс.
    */
    static int time();


    /**
    * @return Случайные числа, доступные из разных потоков.
    */
    static size_t random();


    /**
    * @return Группа и UID события.
    */
    template< class T >
    static inline groupEvent_t group() {
        T e;
        return e.group();
    }


    template< class T >
    static inline uidEvent_t uid() {
        T  e( nullptr, protocolDataEvent_t() );
        return e.uid();
    }


private:
    PoolThread  mPool;




public:
    /**
    * Блокирует весь объект.
    */
    boost::mutex  mtx;
};


} // matchn
