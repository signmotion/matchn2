#include "../include/stdafx.h"
#include "../include/VIncarnate.h"
#include "../include/ge/world/World.h"
#include "../include/ManagerSprite.h"


namespace matchn {


std::unique_ptr< ManagerSprite >  VIncarnate::mManagerSprite(
    new ManagerSprite()
);




VIncarnate::VIncarnate(
    const typelib::coord2Int_t&  vc,
    int  order
) :
    mCoord( vc ),
    mRotation( 0 ),
    mAlpha( 1.0f ),
    mOrder( order ),
    mSprite( new sprite_t() )
{
}




VIncarnate::~VIncarnate() {
}




CL_Sprite*
VIncarnate::sprite( const uidEvent_t& e ) const {
    auto ftr = mSprite->find( e );
    if (ftr != mSprite->end()) {
        return ftr->second.get();
    }

    // спрайт для этого события не найден, вернём образ по умолчанию
    static const uidEvent_t eDef = "default";
    ftr = mSprite->find( eDef );
    assert( (ftr != mSprite->end())
        && "Спрайт не найден." );
    return ftr->second.get();
}




void
VIncarnate::drawSprite(
    std::shared_ptr< World >  w,
    const uidEvent_t&  e
) const {
    auto s = sprite( e );
    assert( s
        && "Спрайт для заданного события не найден." );

    auto gc = w->visual()->get_gc();
    s->set_angle( CL_Angle( visualRotation< float >(), cl_degrees ) );
    s->set_alpha( visualAlpha() );
    s->draw( gc, visualCoord().x, visualCoord().y );
    //Console::instance() << visualCoord() << std::endl;
    s->update();
}




void
VIncarnate::addSprite( std::shared_ptr< World > w,  const std::string&  path ) {
#ifdef _DEBUG
    std::cout << "\nСканируем '" << path << "'\n";
#endif

    // собираем фреймы для спрайта
    // # Фреймы спрайта сгруппированы по папкам событий.
    std::set< std::string >  event;
    // учитываем события из папок
    // # В папке default лежит спрайт по умолчанию.
    typelib::file::listFolder( &event, path );
    assert( !event.empty()
        && "Для спрайта не указано ни одного события."
           " Визуальный образ не может быть собран." );
    assert( (event.find( "default" ) != event.cend())
        && "Не найден спрайт для события 'default'."
           " Могут возникнуть проблемы при визуализации событий." );

    // собираем спрайты по фреймам из папок
    for (auto etr = event.cbegin(); etr != event.cend(); ++etr) {
        const uidEvent_t& e = *etr;
        // @todo fine Проверять допустимость UID события.
        if ( boost::starts_with( e, "-" ) ) {
            // папки, начинающиеся на '-', игнорируем
            continue;
        }

#ifdef _DEBUG
        std::cout << "\nПодготавливаем спрайт для события '" << e << "'\n";
#endif

        // фреймы для визуального образа
        CL_SpriteDescription ds;
        std::set< std::string >  frame;
        std::string pathEvent = path + "/" + e;
        typelib::file::listFile( &frame, pathEvent, "png" );
        typelib::file::listFile( &frame, pathEvent, "jpg" );
        assert( !frame.empty()
            && "Для спрайта не найдено ни одного фрейма. "
               " Визуальный образ не может быть собран." );
        for (auto ftr = frame.cbegin(); ftr != frame.cend(); ++ftr) {
            const std::string& f = *ftr;
            const std::string pathFrame = pathEvent + "/" + f;
            const auto image = mManagerSprite->frame( pathFrame );
            ds.add_frame( *image );
        }

        // сам виз. образ для события 'e'
        std::unique_ptr< CL_Sprite >  sprite(
            new CL_Sprite( w->visual()->get_gc(),  ds )
        );

        // @todo Конфигурируем спрайт.

        // начало координат для спрайта - по центру
        const int cx = sprite->get_width()  / 2;
        const int cy = sprite->get_height() / 2;
        sprite->set_alignment( origin_center );

        // задаём масштаб
        // # Учитываем существующий масштаб спрайта.
        const auto nvs = needVisualSize();
        float fixSX, fixSY;
        sprite->get_scale( fixSX, fixSY );
        const typelib::size2_t  scale(
            nvs.x / static_cast< float >( sprite->get_width()  ) * fixSX,
            nvs.y / static_cast< float >( sprite->get_height() ) * fixSY
        );
        sprite->set_scale( scale.x, scale.y );


        sprite->update();


        // запоминаем собранный спрайт
        addSprite( e,  std::move( sprite ) );

#ifdef _DEBUG
        std::cout << "Спрайт для события '" << e << "' собран.\n";
#endif

    } // for (auto etr = event.cbegin(); ...
}

    
    
    
void
VIncarnate::addSprite( const uidEvent_t&  e,  std::unique_ptr< CL_Sprite >  s ) {

    assert( (mSprite->find( e ) == mSprite->end())
        && "Такое событие уже есть. Дубликаты запрещены." );

    mSprite->insert( std::make_pair( e,  std::move( s ) ) );
}




void VIncarnate::load(
    std::shared_ptr< World >  w,
    const std::string&        kind,
    const std::string&        name
) {
    const std::string path = PATH_MEDIA + "/" + kind + "/" + name;
    addSprite( w, path );
}


} // matchn
