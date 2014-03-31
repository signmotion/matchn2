#pragma once

#include "configure.h"


namespace matchn {


/**
* ”правл€ет спрайтами игры.
*/
class ManagerSprite {
public:
    /**
    * »звестные менеджеру фреймы спрайтов.
    */
    typedef boost::unordered_map<
        std::string,
        std::unique_ptr< CL_PixelBuffer >
    >  knownFrame_t;




    ManagerSprite();




public:
    virtual ~ManagerSprite();




    /**
    * @return ”казатель на загруженный по указанному пути фрейм
    *         в формате ClanLib.
    *         nullptr, если фрейм загрузить на удалось.
    */
    CL_PixelBuffer* frame( const std::string& path );




private:
    knownFrame_t  mKnownFrame;
};


} // matchn
