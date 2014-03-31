#include "include/stdafx.h"
#include "include/configure.h"
#include "include/ge/world/World.h"




void run();




/**
* Переписанная через потоки демо-версия MatchN.
*
* -> См. MatchN3.
*/
int
main( int argc, char** argv ) {

    using namespace matchn;

            
    setlocale( LC_ALL, "Russian" );
    setlocale( LC_NUMERIC, "C" );


    // создаём мир
    try {
        run();

	} catch ( const CL_Exception& ex ) {
		CL_ConsoleWindow  console( "Console", 100, 200 );
		CL_Console::write_line(
            "(!) Exception caught: " + ex.get_message_and_stack_trace()
        );
		console.display_close_message();
        std::cin.ignore();
		return -1;

    } catch ( const std::exception& ex ) {
        std::cerr << std::endl << ex.what() << std::endl;
        std::cin.ignore();
        return -2;

    } catch ( ... ) {
        std::cerr << std::endl << "(!) Unknown exception." << std::endl;
        std::cin.ignore();
        return -100;
    }


}; // main()








inline void
run() {

    using namespace matchn;

    std::shared_ptr< World >  w;
    for (auto command = World::command_t();
         command.first != World::QUIT;
    ) {
        // отрабатываем некоторые команды мира
        size_t K = w ? w->K : 3;
        size_t S = w ? w->N : 5;
        switch ( command.first ) {
            case World::DECREASE_CHAIN :
                K = w->K - 1;
                K = (K < 2) ? 2 : K;
                break;

            case World::DECREASE_TERRITORY :
                S = w->N - 2;
                S = (S < 3) ? 3 : S;
                break;

            case World::INCREASE_CHAIN :
                K = w->K + 1;
                K = (K > 10) ? 10 : K;
                break;

            case World::INCREASE_TERRITORY :
                S = w->N + 2;
                S = (S > 15) ? 15 : S;
                break;
        }

        w = World::valueOf( K, S, S );
        command = w->go();

        if (command.first == World::QUIT) {
            // завершаем работу с миром
            break;
        }

    } // for (auto command = ...

}
