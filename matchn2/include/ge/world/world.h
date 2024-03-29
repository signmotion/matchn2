#pragma once

#include "../../Incarnate.h"
#include "wait-world-event.h"


namespace matchn {


/**
* ����� ��� ������ � ������� �����.
* ������ � ������ ��� ���� ����: ����������, ����������, ����� � ��..
*/
class World :
    public Incarnate
{
public:
    /**
    * ��� ����� ���������� ���������� ��� ������ ��������� �������.
    */
    enum COMMAND {
        /**
        * ������� �� ����������.
        */
        UNDEFINED = 0,

        /**
        * ��������� ������ ��������� ������ ��������� (�����).
        */
        DECREASE_CHAIN,

        /**
        * ������������� ��� � .
        */
        DECREASE_TERRITORY,

        /**
        * ��������� ������ ��������� ������ ��������� (�������).
        */
        INCREASE_CHAIN,

        /**
        * ������������� ��� � ������� ����������������.
        */
        INCREASE_TERRITORY,

        /**
        * ��������� ������.
        */
        QUIT
    };


    /**
    * @todo extend ������� ����� ���������� ���������. ��� ���
    *       �������� � ���� JSON-�������.
    */
    typedef typelib::json::Variant                variant_t;
    typedef std::pair< enum COMMAND, variant_t >  command_t;


    /**
    * ����������� � ���� ��������.
    * # �������� ����������� � ������� ���������.
    */
    typedef std::list< std::shared_ptr< Incarnate > >  incarnateSet_t;



    /**
    * ���-�� ���������� ������ ��������� � ������ ����.
    *
    * # ������ ��������� �����������, ����� �� ������� gett'���.
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
    // ��� ������������� this->shared_from_this()
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
        // # ������ ���� �� �����: �������� ���� ��� ����������.
        return typelib::size2Int_t( WINDOW_WIDTH, WINDOW_HEIGHT );
    }




    /**
    * @return ���������� ��� ��������� shared_ptr �� ���� ������.
    */
    std::shared_ptr< const World > shared() const {
        return std::static_pointer_cast< const World >( this->shared_from_this() );
    }

    std::shared_ptr< World > shared() {
        return std::static_pointer_cast< World >( this->shared_from_this() );
    }




    /**
    * @return ���� ����.
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
    * ��������� � ���� �������� ������� ����.
    */
    void incarnateBackground( const std::string&  name );

    void incarnateContainer(
        const uidContainer_t&        name,
        const typelib::coord2Int_t&  logicCoord
    );




    /**
    * �������� ���.
    *
    * @return ������� ����.
    */
	command_t go();




    /**
    * @return ���������� �����. ���������� �� ����������.
    */
    typelib::coord2Int_t visualByLogicCoordContainer(
        const typelib::coord2Int_t&  lc
    ) const;




    /**
    * @return ��������� �� ������� � �������� ������ ���� ��� ��������� ��
    *         ����� ������ incarnateSet(), ���� ������ �������� ���.
    */
    std::shared_ptr< Incarnate > element(
        const typelib::coord2Int_t&  logicCoord
    );




    /**
    * @return ������� ����� � ����, ��.
    */
    inline int currentTime() const {
        return mCurrentTime;
    }




    // @todo ������� � ��������� ����� typelib.
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
            && "����������� 2D ���������� ����� �� ��������� �������� �����." );

        return c;
    }


    static inline typelib::coord2Int_t isc( size_t cell ) {
        using namespace typelib;
        assert( (cell < 9)
            && "������� �������� ������ �� ��������� 2D-������������." );
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
    * ��������� ������� ����������� ����.
    */
	void onMouseDown( const CL_InputEvent&, const CL_InputState& );
	void onMouseMove( const CL_InputEvent&, const CL_InputState& );
	void onKeyboardDown( const CL_InputEvent&, const CL_InputState& );
	void onWindowClose();




    /**
    * @return ����� � ������� (Frame Per Second).
    */
    static size_t World::calcFPS( size_t frameTime );




private:
    /**
    * ������������ ���.
    */
    std::unique_ptr< CL_DisplayWindow >  mVisualWorld;


    /**
    * ����������� � ���� ��������.
    * # ��� World (���� ������� �������) ��� ����� ������.
    */
    incarnateSet_t  mIncarnateSet;


    /**
    * ������� �� ������.
    */
    CL_Slot  mSlotMouseDown;
    CL_Slot  mSlotMouseMove;
    CL_Slot  mSlotKeyboardDown;
    CL_Slot  mSlotWindowClose;


    /**
    * ������� �����, ��.
    * ����� �������������� ��� ����������� ��������.
    */
    int mCurrentTime;
};



} // matchn
