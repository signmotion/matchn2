// # В этот файл вынесены структуры, которые не дотягивают до класса,
//   но активно используются другими классами.


/**
* UID игрового элемента.
*/
typedef size_t  uidElement_t;




/**
* UID контейнера.
* @see Container
*/
typedef char  uidContainer_t;




/**
* Группа и UID события.
*/
typedef std::string  groupEvent_t;
typedef std::string  uidEvent_t;




/**
* Протокол обмена данными между событиями.
*/
typedef typelib::json::Variant  protocolDataEvent_t;
