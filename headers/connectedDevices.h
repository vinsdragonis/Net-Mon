#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>

#define MAX_OCTET 255

struct Devices
{
    char typeOfDevice[25];
    char macAddress[12];
    char networkInterface[10];
    char ipv4[20];
};
