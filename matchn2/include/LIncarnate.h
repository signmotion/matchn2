#pragma once

#include "GE.h"


namespace matchn {


class World;

    
class LIncarnate {
protected:
    LIncarnate(
        const typelib::coord2Int_t&  coord
    );




    virtual ~LIncarnate();




public:
    inline typelib::coord2Int_t const&  logicCoord() const {
        return mCoord;
    };




    template< typename T1, typename T2 >
    inline void logicCoord( T1 x, T2 y ) {
        logicCoord( typelib::coord2Int_t( x, y ) );
    };




    inline void logicCoord( const typelib::coord2Int_t& c ) {
        mCoord = c;
    };




protected:
    typelib::coord2Int_t  mCoord;
};


} // matchn
