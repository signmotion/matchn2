#include "../include/stdafx.h"
#include "../include/Incarnate.h"
#include "../include/ge/world/World.h"


namespace matchn {


std::unique_ptr< ManagerEvent >  Incarnate::mManagerEvent( new ManagerEvent() );




Incarnate::Incarnate(
    std::shared_ptr< World >     w,
    const typelib::coord2Int_t&  logicCoord,
    int  order
) :
    GE( w ),
    LIncarnate( logicCoord ),
    // для World w не передаётся
    VIncarnate(
        w
          ? w->visualByLogicCoordContainer( logicCoord )
          : typelib::coord2Int_t::ZERO(),
        order
    )
{
}




Incarnate::~Incarnate() {
}


} // matchn
