#pragma once

#include "configure.h"
#include "struct.h"


namespace matchn {


class World;


/**
* Элемент игры, с которым можно взаимодействовать.
* GE - сокр. от GameElement.
*/
class GE {
public:
    explicit GE( std::shared_ptr< World > );




    virtual ~GE();




    /**
    * @return UID этого элемента.
    */
    inline uidElement_t uid() const {
        return mUID;
    }



    /*
    * #! Элемент игры World возвращает nullptr.
    */
    std::shared_ptr< World >  world() const;
    std::shared_ptr< World >  world();




    /**
    * @return Элемент существует.
    */
    inline bool live() const {
        return !mDeleted;
    }




    /**
    * Помечает элемент на удаление.
    */
    inline void unlive() {
        mDeleted = true;;
    }




    inline bool operator==( const GE& b ) const {
        return (mUID == b.uid());
    }




private:
    /**
    * @return След. свободный UID для элемента.
    */
    static inline uidElement_t nextUID() {
        ++nextFreeUID;
        return nextFreeUID;
    }




private:
    std::weak_ptr< World >  mWorld;

    /**
    * UID элемента.
    */
    const uidElement_t  mUID;

    /**
    * Признак: элемент игры удалён из мира.
    */
    bool  mDeleted;


    /**
    * Счётчик для задания UID элементам.
    */
    static uidElement_t  nextFreeUID;
};


} // matchn
