#pragma once

#include "../../Incarnate.h"
#include "wait-background-event.h"


namespace matchn {


class World;


/**
* Фон мира.
*/
class Background :
    public Incarnate
{
protected:
    Background(
        std::shared_ptr< World >,
        const std::string&  name
    );




public:
    static std::shared_ptr< Background >  valueOf(
        std::shared_ptr< World >,
        const std::string&  name
    );




    virtual ~Background();




    /**
    * @virtual VIncarnate
    */
    virtual void draw( std::shared_ptr< World > ) const;




    inline std::string const& name() const {
        return mName;
    }




    /**
    * @virtual VIncarnate
    */
    virtual inline typelib::size2Int_t needVisualSize() const {
        // фон должен заполнить всё игровую область (всё окно)
        return typelib::size2Int_t( WINDOW_WIDTH, WINDOW_HEIGHT );
    }




protected:
    /**
    * Название фона для однозначной идентификации.
    */
    const std::string  mName;
};


} // matchn
