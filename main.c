#include "networkData.h"
#include "connectedDevices.h"

#define esc 27

int main(void)
{
    char opt;

    system("cls");

    while (opt != 27)
    {
        connectionStatus();

        printf("\n\nMAIN MENU :\n\n");
        printf("Press N to manage networks.\n\n");
        //printf("Press C to manage clients.\n\n");
        //printf("Press S to manage networks.\n\n");
        //printf("Press D to manage connected network devices.\n\n");
        //printf("Press T to manage notifications.\n\n");
        //printf("Press V to manage virtual clients.\n\n");
        printf("Press Esc to exit.\n\n");

        opt = getche();
        opt = toupper(opt);

        switch (opt)
        {
            case 'N' :
                networkInterfaceMenu();
                break;
            /*case 'C' :
                listNetworks();
                break;
            case 'S' :
                searchNetwork();
                break;*/
            default :
                system("cls");
        }
    }

    system("cls");
    disconnectAllNetworks();
    printf("Terminating process...\n");
    Sleep(2000);
    printf("Process terminated.\n");

    exit(0);
}
