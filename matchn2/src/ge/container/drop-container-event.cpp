#include "../../../include/stdafx.h"
#include "../../../include/ge/container/Container.h"
#include "../../../include/ge/world/World.h"


namespace matchn {


void
DropContainer::operator()() {
    // # В случае разрушения мира или потерей событием актуальности
    //   завершаем работу потока.
    for ( ; actuality() && !mElement.expired() && world(); ) {
        Console::instance() << "\n(DropContainer " <<
            element()->logicCoord() << ")\n";

        // меняем координаты спрайта
        changeVisualCoord();

        // #! Должен быть boost::sleep(), если хотим корректно
        //    отработать interrupt() при завершении потока-родителя
        boost::this_thread::sleep( HALF_SECOND );
        boost::this_thread::yield();

    } // for ( ; ; )

    Console::instance() << "\n(DropContainer  " <<
        element()->logicCoord() << " closed)\n";

    // меняем логическую координату
    changeLogicCoord();

    {
        boost::mutex::scoped_lock  lock( element()->mtx );
        // заботимся, чтобы цепочка событий сохранилась
        element()->addEvent< WaitContainer >();
    }
}




void
DropContainer::changeVisualCoord() {

    const auto nepper = nepperDeltatime();
    const auto height = static_cast< float >( element()->needVisualSize().y );
    const auto shift = nepper * height;
    {
        boost::mutex::scoped_lock  lock( element()->mtx );
        const auto lc = element()->logicCoord();
        const auto vc = world()->visualByLogicCoordContainer( lc );
        element()->visualCoord( typelib::coord2Int_t( vc.x,  vc.y + shift ) );
    }
}




void
DropContainer::changeLogicCoord() {

    boost::mutex::scoped_lock  lock( element()->mtx );
    const auto& lc = element()->logicCoord();
    if (lc.y > world()->minCoord().y) {
        element()->logicCoord( typelib::coord2Int_t( lc.x,  lc.y - 1 ) );
    }
}


} // matchn
