#pragma once

// Длина внутреннего имени объекта в компиляторе превысила максимальное значение, имя усечено
#pragma warning( disable : 4503 )

// Компилятор обнаружил функцию, которая была помечена как устаревшая — deprecated
// @see http://lists.boost.org/Archives/boost/2006/08/109338.php 
//#pragma warning( disable : 4996 )


// (!) Следующие предупреждения следует включать только если исп. чужие
//     библиотеки и они эти предупреждения выбрасывают.

// Виртуальная функция переопределяет "pcl::search::Search<PointT>::radiusSearch",
// предыдущие версии компилятора не выполняли переопределение, когда параметры
// отличались только квалификаторами const или volatile
//#pragma warning( disable : 4373 )

// Преобразование double в int, возможна потеря данных
//#pragma warning( disable : 4244 )


// Ускоряем компиляцию, отключив участки кода из библиотек Windows
#define WIN32_LEAN_AND_MEAN


// Подключаем некоторые функции из младших версий Windows
// (требуется для boost::asio 1.53)
#define _WIN32_WINNT 0x501



// Отключим вредный макрос в WinDef.h
#define NOMINMAX

// Используем математические константы
#define _USE_MATH_DEFINES


#include <assert.h>
#include <algorithm>
#include <climits>
#include <cstdio>
#include <ctime>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <istream>
#include <list>
#include <math.h>
#include <memory>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <typeinfo>
#include <vector>
#include <windows.h>

#include <boost/assign.hpp>
#include <boost/bimap.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/function.hpp>
#include <boost/functional/hash.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/numeric/interval.hpp>
#include <boost/thread.hpp>
#include <boost/unordered_map.hpp>


#include <ClanLib/core.h>
#include <ClanLib/application.h>
#include <ClanLib/display.h>
#include <ClanLib/sound.h>

// Choose the target renderer
//#define USE_OPENGL_2
//#define USE_OPENGL_1
#define USE_SOFTWARE_RENDERER

#ifdef USE_SOFTWARE_RENDERER
#include <ClanLib/swrender.h>
#endif

#ifdef USE_OPENGL_1
#include <ClanLib/gl1.h>
#endif

#ifdef USE_OPENGL_2
#include <ClanLib/gl.h>
#endif


#include <typelib/typelib.h>


#include "Console.h"
