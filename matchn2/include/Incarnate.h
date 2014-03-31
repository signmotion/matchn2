#pragma once

#include "GE.h"
#include "LIncarnate.h"
#include "VIncarnate.h"
#include "ManagerEvent.h"


namespace matchn {


class Incarnate :
    public std::enable_shared_from_this< Incarnate >,
    public GE,
    public LIncarnate,
    public VIncarnate
{
protected:
    Incarnate(
        std::shared_ptr< World >,
        const typelib::coord2Int_t&  logicCoord,
        int  visualOrder
    );




public:
    virtual ~Incarnate();




    /**
    * Создаёт и добавляет новое событие.
    */
    template< class A >
    inline void addEvent(
        const protocolDataEvent_t& data = protocolDataEvent_t()
    ) {
        auto& w = this->shared_from_this();
        std::shared_ptr< A >  a( new A( w, data ) );
        mManagerEvent->push( a );
    }



    
private:
    static std::unique_ptr< ManagerEvent >  mManagerEvent;




public:
    /**
    * Блокирует весь элемент.
    */
    boost::mutex  mtx;
};


} // matchn
