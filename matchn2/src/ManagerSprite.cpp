#include "../include/stdafx.h"
#include "../include/ManagerSprite.h"


namespace matchn {

    
ManagerSprite::ManagerSprite() :
    mKnownFrame()
{
}




ManagerSprite::~ManagerSprite() {
}




CL_PixelBuffer* ManagerSprite::frame( const std::string& path ) {
    assert( !path.empty()
        && "Путь к фрейму не указан." );

    // проверяем кеш
    auto ftr = mKnownFrame.find( path );
    if (ftr != mKnownFrame.end()) {
        return ftr->second.get();
    }

    // в кеше этого изображения нет, загружаем
#ifdef _DEBUG
        std::cout << "  Фрейм '" << path << "' .. ";
#endif
        const int posExtension = path.find_last_of( '.' );
        const std::string extension =
            (posExtension == std::string::npos)
                ? "" : path.substr( posExtension );
        const bool support =
            (extension == ".png")
         || (extension == ".jpg")
        ;
        if ( !support ) {
            assert( false
                && "Этот тип изображения не поддерживается." );
            return nullptr;
        }

        const auto image =
            (extension == ".png") ? CL_PNGProvider::load( path ) :
            (extension == ".jpg") ? CL_JPEGProvider::load( path ) :
            // #! Метод загрузки ниже не работает для ClanLib-2.3.6 / Windows 7.
            CL_ImageProviderFactory::load( path );
#ifdef _DEBUG
        std::cout << " OK" << std::endl;
#endif

        // кешируем
        std::unique_ptr< CL_PixelBuffer >
            imagePtr( new CL_PixelBuffer( image.copy() ) );
        ftr = mKnownFrame.insert(
            std::make_pair( path,  std::move( imagePtr ) )
        ).first;

        return ftr->second.get();
}


} // matchn
