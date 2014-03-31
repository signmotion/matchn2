#pragma once

#include "Incarnate.h"


namespace matchn {


/**
* Событие элемента.
*/
class Event {
public:
    /**
    * Конфигурация события.
    */
    typedef int  timeMS_t;
    struct DataEvent {
        /**
        * Время начала события, мс.
        */
        timeMS_t  start;

        /**
        * Длительность события, мс.
        * # 0 или меньше, если событие не имеет длительности.
        */
        timeMS_t  duration;

        /**
        * Время завершения события, мс.
        */
        timeMS_t  stop;
    };



public:
    Event( std::shared_ptr< Incarnate >,  const protocolDataEvent_t& );

    virtual ~Event();

    virtual void operator()() = 0;


    /**
    * @return Группа и UID события. Используется для контроля уникальности
    *         при работе в потоках.
    */
    virtual groupEvent_t group() const = 0;

    virtual uidEvent_t uid() const = 0;


    inline const std::shared_ptr< Incarnate >  element() const {
        assert( !mElement.expired()
            && "Элемент уничтожен." );
        return mElement.lock();
    }

    inline std::shared_ptr< Incarnate >  element() {
        assert( !mElement.expired()
            && "Элемент уничтожен." );
        return mElement.lock();
    }


    template< typename T >
    inline T data( const std::string& name, const T& def = T() ) const {
        return mRawData.at< T >( name, def );
    };


    inline DataEvent const&  data() const {
        return mData;
    }


    inline const std::shared_ptr< World >  world() const {
        return world();
    }

    inline std::shared_ptr< World >  world() {
        return element()->world();
    }


    /**
    * @return Событие актуально на данный момент времени.
    *         Проверяется длительность события и текущее время.
    */
    inline bool actuality() const {
        const auto ct = ManagerEvent::time();
        return (ct < mData.stop);
    }


    /**
    * Делает событие неактуальным.
    */
    inline void dropActuality() {
        mData.stop = mData.start;
    }


    /**
    * @return Сколько времени в мс осталось до завершения этого события.
    *         Отрицательное число или 0 - событие завершилось.
    */
    inline int deltatime() const {
        return (mData.stop - ManagerEvent::time());
    }


    /**
    * @return Сколько в диапазоне  [ 0.0 (началось); 1.0 (завершено) )
    *         осталось до завершения этого события.
    */
    inline float nepperDeltatime() const {
        assert( (mData.duration != 0)
            && "Нарушено соглашение: Длительность события не может быть == 0." );
        const float u =
            1.0f -
            static_cast< float >( mData.stop - ManagerEvent::time() ) /
            static_cast< float >( mData.duration );
        return (u > 1.0f) ? 1.0f : (u < 0.0f) ? 0.0f : u;
    }


    /**
    * @return Хеш-код. Зависит от uid() и логических координат элемента.
    */
    inline size_t hash() const {
        size_t seed = boost::hash_value( uid() );
        const auto c = element()->logicCoord();
        boost::hash_combine( seed, c );
        return seed;
    }


protected:
    std::weak_ptr< Incarnate >  mElement;

    
    /**
    * Конфигурация события.
    */
    const protocolDataEvent_t  mRawData;

    /**
    * Распознанная из mRawData и дополненная конфигурация.
    * Используется для снижения нагрузки на CPU.
    */
    DataEvent  mData;


    /**
    * Время (для удобства работы).
    */
    static const boost::posix_time::milliseconds  HALF_SECOND;
    static const boost::posix_time::milliseconds  SECOND;
    static const boost::posix_time::milliseconds  TWO_SECOND;
};




/**
* Событие "Элемент ждёт".
*/
class WaitEvent :
    public Event
{
protected:
    inline WaitEvent(
        std::shared_ptr< Incarnate >  e,
        const protocolDataEvent_t&    data
    ) : Event( e, data ) {
    }

    inline ~WaitEvent() {
    }

    virtual inline groupEvent_t group() const { return "wait"; };
};




/**
* Событие "Элемент падает".
*/
class DropEvent :
    public Event
{
protected:
    inline DropEvent(
        std::shared_ptr< Incarnate >  e,
        const protocolDataEvent_t&    data
    ) : Event( e, data ) {
    }

    inline ~DropEvent() {
    }

    virtual inline groupEvent_t group() const { return "drop"; };
};


} // matchn
