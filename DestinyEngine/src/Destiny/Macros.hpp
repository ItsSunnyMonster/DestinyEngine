/*-------------------------------------
 - Copyright (c) ItsSunnyMonster 2022 -
 -------------------------------------*/

#ifdef DT_BUILD_STATIC_LIB
#   define DT_API
#else
#   ifdef DT_PLATFORM_WINDOWS
#       define DT_API __declspec(dllexport)
#   endif
#   ifdef DT_PLATFORM_UNIX
#       define DT_API __attribute__((visibility("default")))
#   endif
#endif