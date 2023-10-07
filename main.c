/* Created by John �kerblom 10/26/2014 */

#include <windows.h>
#include <commctrl.h>

#include "downslib.h"
#include "dialog.h"
#include "dyn_comctl.h"
#include "resource.h"

#define URL "https://eternallybored.org/misc/wget/1.21.4/64/wget.exe"
#define FILENAME "gfnget.exe"

DWORD WINAPI DownloadThreadProc(LPVOID lpParameter)
{
    int ret = downslib_download(URL, FILENAME, 0, "downslib", 250, update_dialog_cb);

    ExitThread(ret);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShow)
{
    int ret = 0;
    MSG msg = { 0 };
    
    comctl_init();
    
    downslib_init();

    CreateDialogParamW(NULL, MAKEINTRESOURCEW(IDD_DIALOG1), NULL, DownloadDlgProc, (LPARAM)GetCurrentThreadId());

    CloseHandle(CreateThread(NULL, 0, DownloadThreadProc, NULL, 0, NULL));

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        if (msg.message == WM_QUIT) {
            break;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    downslib_exit();

    ExitProcess(0);
}

