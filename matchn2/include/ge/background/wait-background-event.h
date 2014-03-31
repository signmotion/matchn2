#pragma once

#include "../../Event.h"


namespace matchn {


/**
* Неподвижный фон.
*/
class WaitBackground :
    public WaitEvent
{
public:
    inline WaitBackground(
        std::shared_ptr< Incarnate >  e,
        const protocolDataEvent_t&    data
    ) : WaitEvent( e, data ) {
    }

    inline ~WaitBackground() {
    }

    virtual void operator()();

    virtual inline uidEvent_t uid() const { return group() + "-background"; };
};


} // matchn
