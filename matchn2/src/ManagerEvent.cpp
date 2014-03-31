#include "../include/stdafx.h"
#include "../include/ManagerEvent.h"
#include "../include/Event.h"
#include "../include/ge/background/wait-background-event.h"
#include "../include/ge/container/wait-container-event.h"


namespace matchn {


ManagerEvent::ManagerEvent() :
    mPool( COUNT_THREAD )
{
}




ManagerEvent::~ManagerEvent() {
#ifdef _DEBUG
    Console::instance() << "\n\n\nОжидаем завершения потоков..." << std::endl;
#endif
    boost::mutex::scoped_lock  lock( mtx );
    mPool.interruptAll();
    // гарантируем завершение всех потоков
    //mPool.joinAll();
}




void
ManagerEvent::push( std::shared_ptr< Event >  e ) {

    boost::mutex::scoped_lock  lock( mtx );

    // добавим уникальное событие в пул потоков
    const PoolThread::uid_t ue = e->hash();
    const auto& ts = mPool.getTasks();
    // @todo optimize Ускорить поиск.
    const auto ftr = std::find_if(
        ts.cbegin(),
        ts.cend(),
        [ &ue ] ( const PoolThread::task_t& a ) {
            return (a.first == ue);
    } );
    if (ftr == ts.cend()) {
        mPool.enqueue< void >( ue,  [ e ] () {
            // # Событие само позаботится о целостности цепочки.
            ( *e )();
        } );

        Console::instance() << "Added " << e << " " <<
            typeid( *e ).name() <<
            " for " << typeid( *e->element() ).name() << " " <<
             e->element()->logicCoord() << "." << std::endl;

    } else {
        Console::instance() << "Passed " << e << " " <<
            typeid( *e ).name() <<
            " for " << typeid( *e->element() ).name() << " " <<
             e->element()->logicCoord() << "." << std::endl;
    }
}




int
ManagerEvent::time() {
    /* - Заменено на таймер от ClanLib. См. ниже.
    using namespace boost::gregorian;
    using namespace boost::local_time;
    using namespace boost::posix_time;

    static boost::mutex  mtxThis;
    boost::mutex::scoped_lock  lock( mtxThis );

    static const ptime  epoch( date( 1970, 1, 1 ) );
    const ptime  now = microsec_clock::local_time();
    const time_duration  diff = now - epoch;

    return static_cast< long >( diff.total_milliseconds() );
    */

    return static_cast< int >( CL_System::get_time() );
}




size_t
ManagerEvent::random() {
    static boost::mutex  mtxThis;
    boost::mutex::scoped_lock  lock( mtxThis );

    static boost::mt19937  gen( 12345 );
    static boost::uniform_int<>  uni( 0, INT_MAX );
    static boost::variate_generator< boost::mt19937&, boost::uniform_int<> >
        rg( gen, uni );

    return rg();
}


} // matchn
