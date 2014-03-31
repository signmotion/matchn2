#pragma once

#include "../../Event.h"


namespace matchn {


/**
* Здесь мир обрабатывает события.
*/
class WaitWorld :
    public WaitEvent
{
public:
    inline WaitWorld(
        std::shared_ptr< Incarnate >  e,
        const protocolDataEvent_t&    data
    ) : WaitEvent( e, data ) {
    }

    inline ~WaitWorld() {
    }

    virtual void operator()();

    virtual inline uidEvent_t uid() const { return group() + "-world"; };


private:
    void run();
};


} // matchn
