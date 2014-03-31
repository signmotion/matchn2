#include "../../../include/stdafx.h"
#include "../../../include/ge/world/wait-world-event.h"
#include "../../../include/ge/world/World.h"
#include "../../../include/ge/container/Container.h"


namespace matchn {


void
WaitWorld::operator()() {
    // # В случае разрушения мира завершаем работу потока.
    for ( ; !mElement.expired(); ) {
        Console::instance() << "\n(WaitWorld)\n";

        run();

        // #! Должен быть boost::sleep(), если хотим корректно
        //    отработать interrupt() при завершении потока-родителя
        boost::this_thread::sleep( HALF_SECOND );
        boost::this_thread::yield();

    } // for ( ; ; )

    Console::instance() << "\n(WaitWorld closed)\n";
}




void
WaitWorld::run() {

    auto w = std::static_pointer_cast< World >( mElement.lock() );
    boost::mutex::scoped_lock  lock( w->mtx );

    // проверяем наличие контейнеров в верхних ячейках и
    // создаём на месте пустых ячеек новые конейнеры
    // # Здесь не можем использовать this->world().
    const auto is = w->incarnateSet();
    typelib::coord2Int_t cc( 0, w->maxCoord().y );
    for (cc.x = w->minCoord().x; cc.x <= w->maxCoord().x; ++cc.x) {
        const std::shared_ptr< Incarnate > container = w->element( cc );
        if ( container ) {
            // место по этой координате занято
            continue;
        }

        // место по этой координате пустует
        const uidContainer_t uc = Container::nextRandom();
        w->incarnateContainer( uc, cc );

    } // for (cc.x = ...


    // отслеживаем события у других элементов мира, координируем
    for (auto itr = is.begin(); itr != is.end(); ++itr) {
        //auto& ie = ( *itr )->
        //Console::instance() << *itr << std::endl;
    }

}


} // matchn
