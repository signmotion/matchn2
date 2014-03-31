#pragma once

#include <ostream>
#include <boost/thread/recursive_mutex.hpp>


namespace matchn {


/**
* ѕотокобезопасна€ консоль.
*
* @example
*   mConsole << "Any info" << ...;
*/
class Console {
protected:
    inline Console( std::ostream* out = nullptr ) : mOut( out ) {
    }


public:
    static inline Console& instance() {
        boost::mutex::scoped_lock  lock( mtxInstance );
        if ( !mInstance ) {
            mInstance = new Console();
        }
        return *mInstance;
    }

    virtual inline ~Console() {
        boost::mutex::scoped_lock  lock( mtxInstance );
        delete mInstance;
        // блокировки снимутс€ при уничтожении всех объектов этого класса
    }

    inline std::ostream& out() {
        return (mOut ? *mOut : std::cout);
    }


    template< class T >
    inline Console& operator<<( const T& data ) {
        boost::recursive_mutex::scoped_lock  lock( mtx );
        out() << data;
        return *this;
    }

    // дл€ манипул€торов
    inline Console& operator<<( std::ostream& ( *pf )( std::ostream& ) ) {
        boost::recursive_mutex::scoped_lock  lock( mtx );
        out() << pf;
        return *this;
    }


private:
    std::ostream*  mOut;

    static Console*  mInstance;

    static boost::mutex  mtxInstance;
    static boost::recursive_mutex  mtx;
};


} // matchn
