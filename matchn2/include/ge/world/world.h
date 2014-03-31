#pragma once

#include "../../Incarnate.h"
#include "wait-world-event.h"


namespace matchn {


/**
* Класс для работы с игровым миром.
* Создаёт и хранит все миры игры: физический, визуальный, аудио и пр..
*/
class World :
    public Incarnate
{
public:
    /**
    * Мир может возвращать вызвавшему его методу некоторые команды.
    */
    enum COMMAND {
        /**
        * Команда не определена.
        */
        UNDEFINED = 0,

        /**
        * Ожидается меньше собранных вместе элементов (легче).
        */
        DECREASE_CHAIN,

        /**
        * Перезапустить мир с .
        */
        DECREASE_TERRITORY,

        /**
        * Ожидается больше собранных вместе элементов (сложнее).
        */
        INCREASE_CHAIN,

        /**
        * Перезапустить мир с другими характеристиками.
        */
        INCREASE_TERRITORY,

        /**
        * Завершить работу.
        */
        QUIT
    };


    /**
    * @todo extend Команды могут возвращать параметры. Все они
    *       хранятся в виде JSON-объекта.
    */
    typedef typelib::json::Variant                variant_t;
    typedef std::pair< enum COMMAND, variant_t >  command_t;


    /**
    * Воплощённые в мире элементы.
    * # Элементы расположены в порядке отрисовки.
    */
    typedef std::list< std::shared_ptr< Incarnate > >  incarnateSet_t;



    /**
    * Кол-во собираемых вместе элементов и размер мира.
    *
    * # Делаем открытыми константами, чтобы не плодить gett'еры.
    */
    const size_t  K;
    const size_t  N;
    const size_t  M;




protected:
    /**
    * @exception CL_Exception
    */
    World( size_t K, size_t N, size_t M );




public:
    // Для инициализации this->shared_from_this()
    static std::shared_ptr< World > valueOf(
        size_t K = 3,
        size_t N = 5,
        size_t M = 5
    );




    virtual ~World();




    /**
    * @virtual VIncarnate
    */
    virtual void draw( std::shared_ptr< World > ) const;




    /**
    * @virtual VIncarnate
    */
    virtual inline typelib::size2Int_t needVisualSize() const {
        // # Размер мира не важен: рисуются лишь его содержимое.
        return typelib::size2Int_t( WINDOW_WIDTH, WINDOW_HEIGHT );
    }




    /**
    * @return Сокращение для получения shared_ptr на этот объект.
    */
    std::shared_ptr< const World > shared() const {
        return std::static_pointer_cast< const World >( this->shared_from_this() );
    }

    std::shared_ptr< World > shared() {
        return std::static_pointer_cast< World >( this->shared_from_this() );
    }




    /**
    * @return Миры мира.
    */
    inline const CL_DisplayWindow* visual() const {
        return mVisualWorld.get();
    }

    inline CL_DisplayWindow* visual() {
        return mVisualWorld.get();
    }




    inline incarnateSet_t const& incarnateSet() const {
        return mIncarnateSet;
    }

    inline incarnateSet_t& incarnateSet() {
        return mIncarnateSet;
    }




    /**
    * Воплощает в мире элементы разного вида.
    */
    void incarnateBackground( const std::string&  name );

    void incarnateContainer(
        const uidContainer_t&        name,
        const typelib::coord2Int_t&  logicCoord
    );




    /**
    * Оживляет мир.
    *
    * @return Команда мира.
    */
	command_t go();




    /**
    * @return Визуальные коорд. контейнера по логическим.
    */
    typelib::coord2Int_t visualByLogicCoordContainer(
        const typelib::coord2Int_t&  lc
    ) const;




    /**
    * @return Указатель на элемент в заданной ячейке мира или указатель на
    *         конец списка incarnateSet(), если такого элемента нет.
    */
    std::shared_ptr< Incarnate > element(
        const typelib::coord2Int_t&  logicCoord
    );




    /**
    * @return Текущее время в мире, мс.
    */
    inline int currentTime() const {
        return mCurrentTime;
    }




    // @todo Вынести в отдельный класс typelib.
    // @see typelib::DynamicMapContent2D
    inline typelib::size2Int_t size() const {
        return typelib::size2Int_t( N, M );
    }




    inline std::size_t volume() const {
        return N * M;
    }




    inline typelib::coord2Int_t minCoord() const {
        return -maxCoord();
    }


    inline typelib::coord2Int_t maxCoord() const {
        return static_cast< typelib::coord2Int_t >( (size() - 1) / 2 );
    }




    inline bool inside( const typelib::coord2Int_t& c ) const {
        const auto mi = minCoord();
        const auto ma = maxCoord();
        return (c.x >= mi.x) && (c.x <= ma.x)
            && (c.y >= mi.y) && (c.y <= ma.y);
    }


    inline bool inside( int x, int y ) const {
        return inside( typelib::coord2Int_t( x, y ) );
    }




    inline size_t ic( const typelib::coord2Int_t& c ) const {
        return ic( c.x, c.y );
    }


    inline size_t ic( int x, int y ) const {
        const auto max = maxCoord();
        const size_t i = (
            static_cast< std::size_t >(x + max.x)
          + static_cast< std::size_t >(y + max.y) * N
        );
        return i;
    }




    inline typelib::coord2Int_t ci( size_t i ) const {
        const size_t y = i / N;
        const size_t x = i - y * N;
        const typelib::coord2Int_t  c(
            static_cast< int >( x ) - maxCoord().x,
            static_cast< int >( y ) - maxCoord().y
        );

        assert( inside( c )
            && "Вычисленная 2D координата лежит за пределами заданной карты." );

        return c;
    }


    static inline typelib::coord2Int_t isc( size_t cell ) {
        using namespace typelib;
        assert( (cell < 9)
            && "Попытка получить доступ за пределами 2D-пространства." );
        const static coord2Int_t a[ 9 ] = {
            coord2Int_t(  0,   0 ),
            coord2Int_t(  0,  +1 ),
            coord2Int_t( +1,   0 ),
            coord2Int_t(  0,  -1 ),
            coord2Int_t( -1,   0 ),
            coord2Int_t( +1,  +1 ),
            coord2Int_t( +1,  -1 ),
            coord2Int_t( -1,  -1 ),
            coord2Int_t( -1,  +1 )
        };

        return a[ cell ];
    }




private:
    /**
    * Слушатели событий визуального мира.
    */
	void onMouseDown( const CL_InputEvent&, const CL_InputState& );
	void onMouseMove( const CL_InputEvent&, const CL_InputState& );
	void onKeyboardDown( const CL_InputEvent&, const CL_InputState& );
	void onWindowClose();




    /**
    * @return Кадры в секунду (Frame Per Second).
    */
    static size_t World::calcFPS( size_t frameTime );




private:
    /**
    * Отображаемый мир.
    */
    std::unique_ptr< CL_DisplayWindow >  mVisualWorld;


    /**
    * Воплощённые в мире элементы.
    * # Сам World (тоже игровой элемент) вне этого списка.
    */
    incarnateSet_t  mIncarnateSet;


    /**
    * События от игрока.
    */
    CL_Slot  mSlotMouseDown;
    CL_Slot  mSlotMouseMove;
    CL_Slot  mSlotKeyboardDown;
    CL_Slot  mSlotWindowClose;


    /**
    * Текущее время, мс.
    * Может использоваться для корректного тайминга.
    */
    int mCurrentTime;
};



} // matchn
