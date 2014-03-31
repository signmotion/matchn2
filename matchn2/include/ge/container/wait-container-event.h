#pragma once

#include "../../Event.h"


namespace matchn {


/**
* Ќеподвижный контейнер.
*/
class WaitContainer :
    public WaitEvent
{
public:
    inline WaitContainer(
        std::shared_ptr< Incarnate >  e,
        const protocolDataEvent_t&    data
    ) : WaitEvent( e, data ) {
    }

    inline ~WaitContainer() {
    }

    virtual void operator()();

    virtual inline uidEvent_t uid() const { return group() + "-container"; };


private:
    /**
    * ѕровер€ет, есть ли под этим контейнером свободное место.
    */
    void verifyPlaceAbove();
};


} // matchn
