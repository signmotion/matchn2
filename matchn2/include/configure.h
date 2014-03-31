#pragma once

#include <string>
#include <typelib/include/coord2.h>
#include <typelib/include/vector2.h>


namespace matchn {


/**
* Количество уникальных элементов, участвующих в игре.
*
* @todo extend Определять по количеству папок в папке 'media/element'.
*/




/**
* Размер окна игры, согласно которому позиционируем элементы, пкс.
*/
static const int WINDOW_WIDTH  = 800;
static const int WINDOW_HEIGHT = 800;
static const float WINDOW_K_WIDTH_HEIGHT =
    static_cast< float >( WINDOW_WIDTH ) /
    static_cast< float >( WINDOW_HEIGHT );




/**
* Смещение центра координат визуального мира относительно логического, пкс.
*/
static const int CENTER_WINDOW_WIDTH  = WINDOW_WIDTH  / 2;
static const int CENTER_WINDOW_HEIGHT = WINDOW_HEIGHT / 2;




/**
* Максимальные и минимальные координаты визуального мира, пкс.
*/
static const int MIN_X_VISUAL_COORD = -WINDOW_WIDTH  / 2;
static const int MAX_X_VISUAL_COORD =  WINDOW_WIDTH  / 2;
static const int MIN_Y_VISUAL_COORD = -WINDOW_HEIGHT / 2;
static const int MAX_Y_VISUAL_COORD =  WINDOW_HEIGHT / 2;



/**
* Максимальное видимое расстояние от центра мира (от центра до угла).
*/
static const float MAX_VISUAL_CENTER_DISTANCE =
    typelib::vector2_t( MAX_X_VISUAL_COORD, MAX_Y_VISUAL_COORD ).length();




// # Ниже все координаты и размеры задаются относительно логического мира игры.
// # Направление координатных осей
//     - визуальный мир: X - вправо, Y - вниз
//     - логический мир: X - вправо, Y - вверх




/**
* Координаты центра области элементов, пкс.
* Задаются относит. логического мира игры - см. прим. выше.
*/
static const int ELEMENT_AREA_X = 0;
static const int ELEMENT_AREA_Y = 0;




/**
* Размер спрайта элемента (по умолчанию).
*/
static const typelib::size2Int_t  ELEMENT_SPRITE_SIZE( 270, 270 );



/**
* Пути к данным в файловой системе.
*/
static const std::string PATH_MEDIA = "media";




/**
* Количество потоков, запущенных игрой.
* # Для каждого воплощённого элемента открывается отдельный поток. Для игры
*   с размером поля 10 x 10 требуется 100 потоков + ~1% резервных потоков.
*/
static const size_t COUNT_THREAD = 15 * 15 + 20;
//static const size_t COUNT_THREAD = 4;




/**
* Для отладки.
*/
//#define _DEBUG_EVENT



} // matchn
