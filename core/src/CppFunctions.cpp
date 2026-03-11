#include "CppFunctions.h"

int UltimateFunction(lua_State* pL)
{
    std::cout << "C++ Ultimate Function !!" << std::endl;

    return 0;  // returnで戻り値の数を返す。今回は何も返さないので0
}
