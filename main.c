#include "glib2d.h"
#include <pspdebug.h>
#include <pspkernel.h>

PSP_MODULE_INFO("psp-hello", 0, 1, 0);

int exit_callback(int arg1, int arg2, void *common) {
    sceKernelExitGame();
    return 0;
}

int CallbackThread(SceSize args, void *argp) {
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();

    return 0;
}

int SetupCallbacks(void) {
    int thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11,
                                     0xFA0, 0, 0);
    if (thid >= 0) sceKernelStartThread(thid, 0, 0);
    return thid;
}

int main() {
    SetupCallbacks();
    GFX_init();

    while (1) {
        GFX_clear(0x202020ff);

        GFX_draw_rect(10, 10, 30, 30, 0xFF00FFFF);

        GFX_swap_buffers();
        sceDisplayWaitVblankStart();
    }
}