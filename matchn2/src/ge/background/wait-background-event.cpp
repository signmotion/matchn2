#include "../../../include/stdafx.h"
#include "../../../include/ge/background/Background.h"


namespace matchn {


void
WaitBackground::operator()() {
    // # ¬ случае разрушени€ мира завершаем работу потока.
    for ( ; !mElement.expired() && world(); ) {
        Console::instance() << "\n(WaitBackground)\n";

        // #! ƒолжен быть boost::sleep(), если хотим корректно
        //    отработать interrupt() при завершении потока-родител€
        boost::this_thread::sleep( TWO_SECOND );

    } // for ( ; ; )

    Console::instance() << "\n(WaitBackground closed)\n";
}


} // matchn
