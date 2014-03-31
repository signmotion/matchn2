#include "../include/stdafx.h"
#include "../include/Event.h"


namespace matchn {


const boost::posix_time::milliseconds  Event::HALF_SECOND( 500 );
const boost::posix_time::milliseconds  Event::SECOND( 1000 );
const boost::posix_time::milliseconds  Event::TWO_SECOND( 2000 );




Event::Event(
    std::shared_ptr< Incarnate >   element,
    const typelib::json::Variant&  rawData
) :
    mElement( element ),
    mRawData( rawData )
{
    /* - Может быть nullptr: создаём пустышки для получения uid/group
         по шаблону. См. ManagerEvent::uid/group().
    assert( element );
    */

    // распознаём данные
    const auto start = ManagerEvent::time();
    const auto duration = data< float >( "duration", 1.0f ) * 1000.0f;
    const auto stop = start + duration;

    const DataEvent t = {
        static_cast< timeMS_t >( start ),
        static_cast< timeMS_t >( duration ),
        static_cast< timeMS_t >( stop )
    };
    mData = t;
}




Event::~Event() {
}


} // matchn
