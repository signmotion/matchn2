#include "../../../include/stdafx.h"
#include "../../../include/ge/container/Container.h"
#include "../../../include/ge/world/World.h"


namespace matchn {


void
WaitContainer::operator()() {
    // # ¬ случае разрушени€ мира завершаем работу потока.
    for ( ; actuality() && !mElement.expired() && world(); ) {
        Console::instance() << "\n(WaitContainer " <<
            element()->logicCoord() << ")\n";

        // # јктивное событие может служить признаком, какой спрайт рисовать.

        verifyPlaceAbove();

        // #! ƒолжен быть boost::sleep(), если хотим корректно
        //    отработать interrupt() при завершении потока-родител€
        boost::this_thread::sleep( HALF_SECOND );
        boost::this_thread::yield();

    } // for ( ; ; )

    Console::instance() << "\n(WaitContainer " <<
        element()->logicCoord() << " closed)\n";
}




void
WaitContainer::verifyPlaceAbove() {

    boost::mutex::scoped_lock  lock( element()->mtx );

    const auto lc = element()->logicCoord();
    const auto w = world();
    const auto shift = w->isc( 3 );
    const auto above = lc + shift;
    if (lc.y > w->minCoord().y) {
        // скажем контейнеру падать
        protocolDataEvent_t  data;
        data[ "duration" ] = 2;
        element()->addEvent< DropContainer >( data );

        // событие отметим как неактуальное, чтобы не нагружать систему
        dropActuality();
    }
}


} // matchn
