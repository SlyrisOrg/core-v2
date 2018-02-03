//
// Created by doom on 12/10/17.
//

#ifdef WIN32
#define EXPORT_SYMBOL __declspec(dllexport)
#else
#define EXPORT_SYMBOL
#endif

EXPORT_SYMBOL extern int a_number;

int a_number = 42;

EXPORT_SYMBOL int double_this(int number)
{
    return number * 2;
}