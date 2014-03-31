#include "../include/stdafx.h"
#include "../include/GE.h"
#include "../include/ge/world/World.h"
#include "../include/ManagerEvent.h"


namespace matchn {


uidElement_t GE::nextFreeUID = 0;




GE::GE(
    std::shared_ptr< World >  w
) :
    mWorld( w ),
    mUID( nextUID() ),
    mDeleted( false )
{
    /* - Мир - тоже элемент игры. Для него допустимо значение nullptr.
    assert( !mWorld.expired()
        && "Получен разрушенный мир." );
    */
    assert( ( !w || ( mWorld.lock() && mWorld.lock()->visual() ) )
        && "Визуальный мир должен быть инициализирован." );
}




GE::~GE() {
}




std::shared_ptr< World >
GE::world() const {
    return mWorld.lock();
}




std::shared_ptr< World >
GE::world() {
    return mWorld.lock();
}


} // matchn
