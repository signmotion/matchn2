#pragma once

#include "GE.h"


namespace matchn {


class World;
class ManagerSprite;


/**
* Объект, зарегистрированный в визуальном движке (в мире).
* # В качестве виз. движка используется ClanLib.
*
* @see http://clanlib.org
*/
class VIncarnate {
public:
    /**
    * Спрайты сгруппированы по событиям.
    * Каждое событие может иметь один спрайт (образ для визуализации).
    */
    typedef std::map<
        uidEvent_t,
        std::unique_ptr< CL_Sprite >
    > sprite_t;




protected:
    VIncarnate(
        const typelib::coord2Int_t&  coord,
        int  order
    );



    virtual ~VIncarnate();




public:
    /**
    * Визуализирует элемент.
    */
    virtual void draw( std::shared_ptr< World > ) const = 0;




    inline sprite_t const* sprite() const {
        return mSprite.get();
    }




    /**
    * @return Спрайт для события 'E'.
    *         nullptr, если спрайт для события не найден.
    */
    CL_Sprite* sprite( const uidEvent_t& ) const;




    /**
    * Отображает спрайт для заданного события.
    */
    void drawSprite( std::shared_ptr< World >, const uidEvent_t& ) const;




    /**
    * Добавляет спрайты, собирая их по фреймам из 'path'.
    *
    * # Фреймы спрайтов сгруппированы по папкам событий - см. допустимые
    *   названия в ManagerEvent::uid< T >().
    * # Фреймы спрайтов должны быть одного размера.
    */
    void addSprite( std::shared_ptr< World >,  const std::string&  path );




    /**
    * Добавляет спрайт для события.
    */
    void addSprite( const uidEvent_t&,  std::unique_ptr< CL_Sprite > );




    /**
    * @return Размер образа в пкс, который нужно показать на экране.
    *         Спрайт будет подогнан под этот размер.
    */
    virtual typelib::size2Int_t needVisualSize() const = 0;




    /**
    * @return Координаты образа.
    *
    * # Названа с приставкой, чтобы проще получать доступ из элементов игры.
    */
    template< typename T1, typename T2 >
    inline void visualCoord( T1 x, T1 y ) {
        visualCoord( coord2Int_t( x, y ) );
    };


    inline const typelib::coord2Int_t& visualCoord() const {
        return mCoord;
    };


    inline void visualCoord( const typelib::coord2Int_t& c ) {
        mCoord = c;
    };




    /**
    * @return Угол поворота элемента в градусах.
    */
    template< typename T >
    inline void visualRotation( T a ) {
        mRotation = static_cast< int >( a );
    };


    template< typename T >
    inline T visualRotation() const {
        return static_cast< T >( mRotation );
    };


    inline int visualRotation() const {
        return mRotation;
    };




    /**
    * @return Прозрачность элемента [0.0; 1.0].
    */
    template< typename T >
    inline void visualAlpha( T a ) {
        mAlpha = static_cast< float >( a );
    };


    inline float visualAlpha() const {
        return mAlpha;
    };




    /**
    * @return Порядок отрисовки элемента. Меньше - раньше.
    */
    inline int visualOrder() const {
        return mOrder;
    }




    void load(
        std::shared_ptr< World >,
        const std::string&  kind,
        const std::string&  name
    );




private:
    typelib::coord2Int_t  mCoord;
    int                   mRotation;
    float                 mAlpha;

    /**
    * Порядок отрисовки элемента. Меньше - раньше.
    */
    int  mOrder;

    /**
    * Спрайты элемента, сгруппированные по событиям.
    */
    std::unique_ptr< sprite_t >  mSprite;

    static std::unique_ptr< ManagerSprite >  mManagerSprite;
};



} // matchn
