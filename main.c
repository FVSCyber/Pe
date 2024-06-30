#include <stdio.h>
#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <sbv_patches.h>
#include <gsKit.h>
#include <dmaKit.h>
#include <gsToolkit.h>

// Fungsi untuk setiap menu
void copy() {
    printf("Copy selected\n");
}

void paste() {
    printf("Paste selected\n");
}

void delete() {
    printf("Delete selected\n");
}

void about() {
    printf("This is a simple PS2 menu application\n");
}

int main(int argc, char *argv[]) {
    // Inisialisasi PS2
    SifInitRpc(0);
    SifLoadFileInit();
    sbv_patch_enable_lmb();
    sbv_patch_disable_prefix_check();
    SifInitIopHeap();
    SifLoadModule("rom0:SIO2MAN", 0, NULL);
    SifLoadModule("rom0:MCMAN", 0, NULL);
    SifLoadModule("rom0:MCSERV", 0, NULL);

    // Inisialisasi GS (Graphic Synthesizer)
    dmaKit_init(D_CTRL_RELE_OFF, D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
                D_CTRL_STD_OFF, D_CTRL_STD_OFF);
    gsKit_init_global();
    GSGLOBAL *gsGlobal = gsKit_init_global();
    gsKit_mode_switch(gsGlobal, GS_ONESHOT);

    // Buat menu
    char *menu[] = {"Copy", "Paste", "Delete", "About"};
    int menu_count = 4;
    int selected = 0;

    while (1) {
        printf("Select an option:\n");
        for (int i = 0; i < menu_count; i++) {
            if (i == selected) {
                printf("> %s\n", menu[i]);
            } else {
                printf("  %s\n", menu[i]);
            }
        }

        // Baca input dari pengguna
        char input = getchar();
        switch (input) {
            case 'w':
                selected = (selected - 1 + menu_count) % menu_count;
                break;
            case 's':
                selected = (selected + 1) % menu_count;
                break;
            case '\n':
                switch (selected) {
                    case 0:
                        copy();
                        break;
                    case 1:
                        paste();
                        break;
                    case 2:
                        delete();
                        break;
                    case 3:
                        about();
                        break;
                }
                break;
            default:
                break;
        }

        // Bersihkan layar (untuk terminal emulator)
        printf("\033[H\033[J");
    }

    return 0;
}
