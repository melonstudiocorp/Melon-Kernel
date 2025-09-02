// shell.c
// ================
// =====HEADERS=====
#include <stdint.h>
#include "../krnl/krnl.h"
#include "../../fun/games.h"
// ================

void smain() {
    char buffer[128];

    outline("Welcome To Rain-Shell!\n");
    outline("Type \"help\" to see available commands.\n");
    // ==================
    // =====MAIN CYCLE=====
    while (1) {
        outline("> ");
        readline(buffer, sizeof(buffer));

        if (strcmp(buffer, "clear") == 0) {
            clearline();
        } else if (strcmp(buffer, "stars") == 0) {
            starfall();
        } else if (strcmp(buffer, "spin") == 0) {
            spinner();
        } else if (strcmp(buffer, "reboot") == 0) {
            reboot();
        } else if (strcmp(buffer, "help") == 0) {
            outline("=====================\n");
            outline("Commands: \n");
            outline("      help - View Commands\n");
            outline("      reboot - Restarting System\n");
            outline("      stars - Secret\n");
            outline("      spin - Secret too\n");
            outline("      clear - clearing terminal\n");
            outline("=====================\n");
        } else {
            outline("Unknown command. Type 'help' to see list.\n");
        }
    }
    // ==================
}