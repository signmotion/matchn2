#pragma once

#include "../../Event.h"


namespace matchn {


/**
* Контейнер падает.
*
* @todo fine? Выделить класс Action[Element]. Множественное наследование.
*/
class DropContainer :
    public WaitEvent
{
public:
    inline DropContainer(
        std::shared_ptr< Incarnate >  e,
        const protocolDataEvent_t&    data
    ) : WaitEvent( e, data ) {
    }

    inline ~DropContainer() {
    }

    virtual void operator()();

    virtual inline uidEvent_t uid() const { return group() + "-container"; };


private:
    void changeVisualCoord();
    void changeLogicCoord();
};


} // matchn
