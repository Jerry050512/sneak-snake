#include <stdlib.h>
#include "menu.h"
#include "utils.h"
#include "structs.h"
#include "settings.h"

Config config;

int main()
{
#if defined(_WIN32)
    // Use UTF-8 encoding on Windows
    system("chcp 65001");
#endif
    hideCursor();
    read_config(&config);
    while (display_menu())
        ;
    showCursor();
    return 0;
}