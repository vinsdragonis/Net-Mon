#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

#define MAX_CH 14
#define esc 27

struct Network
{
    char ip[20];
    char encryption[5];
    char essid[30];
    int channel;
    float dataTransmissionRate;
    float dataCapacity;
    char key[25];
    int online;
};

float dataRate(float dataCapacity, int t);

void networkInterfaceMenu()
{
    char opr;

    system("cls");

    while (opr != 27)
    {
        connectionStatus();

        printf("\n\nMAIN MENU :\n\n");
        printf("Press A to create a new virtual network.\n\n");
        printf("Press L to list available virtual networks.\n\n");
        printf("Press S to search virtual network.\n\n");
        //printf("Press R to remove virtual network.\n\n");
        printf("Press M to manage virtual network.\n\n");
        printf("Press C to check connection status.\n\n");
        printf("Press I to connect to network.\n\n");
        //printf("Press T to manage notifications.\n\n");
        printf("Press Esc to return to Main Menu.\n\n");

        opr = getche();
        opr = toupper(opr);

        switch (opr)
        {
            case 'A' :
                addNetwork();
                break;
            case 'L' :
                listNetworks();
                break;
            case 'S' :
                searchNetwork();
                break;
            case 'M' :
                manageNetwork();
                break;
            case 'C' :
                connectedNetworkStatus();
                break;
            case 'I' :
                connectToNetwork();
                break;
            default :
                system("cls");
        }
    }

    system("cls");
}

void addNetwork()
{
    FILE *f;

    f = fopen("Networks.ojs", "ab+");

    int time;
    float dC;
    struct Network net;
    char dCap;

    if (f == 0)
    {
        f = fopen("Networks.ojs", "wb+");
        system("cls");
        printf("Configuring data....\n");
        Sleep(5000);
        printf("\nConfigurations complete....\nPress any key to continue.\n");
        _getch();
    }

    while (1)
    {
        system("cls");

        printf("Enter IP Address.\n");
        scanf("%s",&net.ip);
        fflush(stdin);

        printf("\nPress : \n\n1. To enter data in GBs. \n2. To enter data in MBs. \n3. To enter data in KBs. \n4. To enter data in Bytes. \n");
        dCap = getche();

        while (1)
        {
            if (dCap == '1')
            {
                printf("\nEnter maximum data capacity in GBs.\n");
                scanf("%f",&net.dataCapacity);
                break;
            }
            else if (dCap == '2')
            {
                printf("\nEnter maximum data capacity in MBs.\n");
                scanf("%f",&net.dataCapacity);
                break;
            }
            else if (dCap == '3')
            {
                printf("\nEnter maximum data capacity in KBs.\n");
                scanf("%f",&net.dataCapacity);
                break;
            }
            else if (dCap == '4')
            {
                printf("\nEnter maximum data capacity in Bytes.\n");
                scanf("%f",&net.dataCapacity);
                break;
            }
            else
            {
                printf("Invalid value. Please check the value you've entered.\n");
            }
        }

        printf("Enter number of days of validity.\n");
        scanf("%d",&time);

        switch(dCap)
        {
            case '1' :
                dC = net.dataCapacity * 1024;
                net.dataTransmissionRate = dataRate(dC, time);
                break;
            case '2' :
                dC = net.dataCapacity;
                net.dataTransmissionRate = dataRate(dC, time);
                net.dataCapacity = net.dataCapacity * 1024;
                break;
            case '3' :
                dC = net.dataCapacity / 1024;
                net.dataTransmissionRate = dataRate(dC, time);
                net.dataCapacity = net.dataCapacity / (1024 * 1024);
                break;
            case '4' :
                dC = net.dataCapacity / (1024 * 1024);
                net.dataTransmissionRate = dataRate(dC, time);
                net.dataCapacity = net.dataCapacity / (1024 * 1024 * 1024);
                break;
        }

        net.channel = rand() % (MAX_CH + 1);

        printf("Enter encryption.\n");
        scanf("%s",&net.encryption);
        fflush(stdin);

        printf("Enter ESSID.\n");
        scanf("%[^\n]",&net.essid);
        fflush(stdin);

        printf("Enter key.\n");
        scanf("%s",&net.key);
        fflush(stdin);

        net.online = 0;

        fwrite(&net, sizeof(net), 1, f);

        printf("\nSuccessfully created virtual network.\n");
        printf("Press any key to continue.\n");

        _getch();
        system("cls");

        fclose(f);
        break;
    }
}

float dataRate(float dataCapacity, int t)
{
    float dRate = dataCapacity / (t * 24);

    return dRate;
}

void listNetworks()
{
    FILE *f;
    struct Network net;
    int i;

    system("cls");

    if((f = fopen("Networks.ojs", "rb")) == NULL)
    {
        printf("No networks found.\n");
    }
    else
    {
        while (fread(&net, sizeof(net), 1, f) == 1)
        {
            printf("IP\t\t\tCH\tENC\tAUTH\tESSID\t\tDataCap\t\tDataRate\n");

            for (i = 0; i < 99; i++)
                printf("-");

            printf("\n%s\t%d\t%s\t%s\t%s\t%.1f GB\t%.2f MB/s\n", net.ip, net.channel, net.encryption, net.essid, net.dataCapacity, net.dataTransmissionRate);
            printf("\n\n");

            for (i = 0; i < 99; i++)
                printf("-");

            printf("\n");
        }
    }

    fclose(f);
    _getch();
    system("cls");
}

void searchNetwork()
{
    FILE *f;
    struct Network net;
    char ip[20];
    int i, flag = 1;

    system("cls");

    if((f = fopen("Networks.ojs", "rb")) == NULL)
    {
        printf("No networks found.\n");
    }
    else
    {
        printf("Enter IP Address.\n");
        scanf("%s",&ip);

        while (fread(&net, sizeof(net), 1, f) == 1)
        {
            if (strcmp(net.ip, ip) == 0)
            {
                printf("\n\nIP\t\t\tCH\tENC\tAUTH\tESSID\t\tDataCap\t\tDataRate\n");

                for (i = 0; i < 99; i++)
                    printf("-");

                printf("\n%s\t%d\t%s\t%s\t%s\t%.1f GB\t%.2f MB/s\n", net.ip, net.channel, net.encryption, net.essid, net.dataCapacity, net.dataTransmissionRate);
                printf("\n\n");

                for (i = 0; i < 99; i++)
                    printf("-");

                printf("\n");

                flag = 0;
                break;
            }
            else if (flag == 1)
            {
                system("cls");
                printf("Unknown or invalid IP.\n");
            }

            printf("\n");
        }
    }

    fclose(f);
    _getch();
    system("cls");
}

void manageNetwork()
{
    FILE *f;
    struct Network net;
    char ip[20];
    char key[25];
    char dCap;
    int flag = 1, time;
    long int Size = sizeof (net);
    float dC;

    if((f = fopen("Networks.ojs", "rb+")) == NULL)
    {
        system("cls");
        printf("No networks found.\n");
    }
    else
    {
        printf("Enter IP Address.\n");
        scanf("%[^\n]",&ip);

        printf("Enter key.\n");
        scanf("%s",&key);

        while (fread(&net, sizeof(net), 1, f) == 1)
        {
            if (strcmp(net.ip, ip) == 0 && strcmp(key, net.key) == 0)
            {
                system("cls");

                fflush(stdin);

                printf("Enter IP.\n");
                scanf("%s",&net.ip);
                fflush(stdin);

                printf("\nPress : \n\n1. To enter data in GBs. \n2. To enter data in MBs. \n3. To enter data in KBs. \n4. To enter data in Bytes. \n");
                dCap = getche();

                while (1)
                {
                    if (dCap == '1')
                    {
                        printf("\nEnter maximum data capacity in GBs.\n");
                        scanf("%f",&net.dataCapacity);
                        break;
                    }
                    else if (dCap == '2')
                    {
                        printf("\nEnter maximum data capacity in MBs.\n");
                        scanf("%f",&net.dataCapacity);
                        break;
                    }
                    else if (dCap == '3')
                    {
                        printf("\nEnter maximum data capacity in KBs.\n");
                        scanf("%f",&net.dataCapacity);
                        break;
                    }
                    else if (dCap == '4')
                    {
                        printf("\nEnter maximum data capacity in Bytes.\n");
                        scanf("%f",&net.dataCapacity);
                        break;
                    }
                    else
                    {
                        printf("Invalid value. Please check the value you've entered.\n");
                    }
                }

                printf("Enter number of days of validity.\n");
                scanf("%d",&time);

                switch(dCap)
                {
                    case '1' :
                        dC = net.dataCapacity * 1024;
                        net.dataTransmissionRate = dataRate(dC, time);
                        break;
                    case '2' :
                        dC = net.dataCapacity;
                        net.dataTransmissionRate = dataRate(dC, time);
                        net.dataCapacity = net.dataCapacity * 1024;
                        break;
                    case '3' :
                        dC = net.dataCapacity / 1024;
                        net.dataTransmissionRate = dataRate(dC, time);
                        net.dataCapacity = net.dataCapacity / (1024 * 1024);
                        break;
                    case '4' :
                        dC = net.dataCapacity / (1024 * 1024);
                        net.dataTransmissionRate = dataRate(dC, time);
                        net.dataCapacity = net.dataCapacity / (1024 * 1024 * 1024);
                        break;
                }

                net.channel = rand() % (MAX_CH + 1);

                printf("Enter encryption.\n");
                scanf("%s",&net.encryption);
                fflush(stdin);

                printf("Enter ESSID.\n");
                scanf("%[^\n]",&net.essid);
                fflush(stdin);

                printf("Enter key.\n");
                scanf("%s",&net.key);
                fflush(stdin);

                net.online = 0;

                fseek(f, -Size, SEEK_CUR);

                fwrite(&net, sizeof(net), 1, f);

                printf("\nSuccessfully updated virtual network.\n");
                printf("Press any key to continue.\n");

                flag = 0;
                break;
            }
            else if (flag == 1)
            {
                system("cls");
                printf("Unknown or invalid IP.\n");
            }

            printf("\n");
        }
    }

    fclose(f);
    _getch();
    system("cls");
}

void connectToNetwork()
{
    disconnectAllNetworks();

    FILE *f;
    struct Network net;
    char ip[20];
    char KEY[25];
    int connected = 0;
    long int Size = sizeof (net);
    float dC;

    system("cls");

    if((f = fopen("Networks.ojs", "rb+")) == NULL)
    {
        printf("No networks found.\n");
    }
    else
    {
        printf("Enter IP Address.\n");
        scanf("%[^\n]",&ip);

        printf("Enter key.\n");
        scanf("%s",&KEY);

        while (fread(&net, sizeof(net), 1, f) == 1)
        {
            if (strcmp(net.ip, ip) == 0 && strcmp(KEY, net.key) == 0)
            {
                system("cls");
                fflush(stdin);

                net.online = 1;
                fseek(f, -Size, SEEK_CUR);

                fwrite(&net, sizeof(net), 1, f);

                printf("Successfully connected to virtual network.\n");
                printf("Press any key to continue.\n");

                connected = 1;
                break;
            }
            else if (connected == 0)
            {
                fflush(stdin);

                system("cls");
                printf("Unknown or invalid IP.\n");
            }
        }
    }

    fclose(f);
    _getch();
    system("cls");
}

void disconnectAllNetworks()
{
    FILE *f;
    struct Network net;
    long int Size = sizeof (net);

    system("cls");

    if ((f = fopen("Networks.ojs", "rb+")) == NULL)
    {
        system("cls");
    }
    else
    {
        while (fread(&net, sizeof(net), 1, f) == 1)
        {
            if (net.online == 1)
            {
                net.online = 0;
                fwrite(&net, sizeof(net), 1, f);
            }
        }
    }

    fclose(f);
}

void connectionStatus()
{
    FILE *f;
    struct Network net;
    int connected = 0;

    if((f = fopen("Networks.ojs", "rb")) == NULL)
    {
        printf("Unable to find networks.\n");
    }
    else
    {
        while (fread(&net, sizeof(net), 1, f) == 1)
        {
            if (net.online == 1)
            {
                printf("Connected to : %s.\n", net.essid);
                connected = 1;
                break;
            }
            else if (connected == 0)
            {
                printf("You are currently offline...\n");
            }
        }
    }

    fclose(f);
}

void connectedNetworkStatus()
{
    FILE *f;
    struct Network net;
    int connected = 0;

    system("cls");

    if((f = fopen("Networks.ojs", "rb")) == NULL)
    {
        printf("You are currently offline...\n");
    }
    else
    {
        while (fread(&net, sizeof(net), 1, f) == 1)
        {
            if (net.online == 1)
            {
                printf("Connection Status : \n\n\n");
                printf("Connected to : %s.\n\n", net.essid);
                printf("IP : %s.\n\n", net.ip);
                printf("CH : %d.\n\n", net.channel);
                connected = 1;
                break;
            }
            else if (connected == 0)
            {
                printf("You are currently offline...\n");
            }
        }
    }

    fclose(f);
    _getch();
    system("cls");
}
