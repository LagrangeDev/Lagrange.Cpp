#include "Test.h"
#include <Windows.h>
int main()
{
    auto Core = LoadLibraryA("./Lagrange.Core.dll");
    if (Core)
    {
        auto CoreFunction = (void(*)())GetProcAddress(Core, "Core");
        if (CoreFunction)
        {
            CoreFunction();
        }
    }
    return 0;
}