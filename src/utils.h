#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <limits>
#include <ctime>
#include <stddef.h>

using namespace std;

void printHeading(string header)
{
    cout << "\n\n\n\n";
    cout << "\t\t\t\t\t\t\t\t\t\t==========================================================\n";
    cout << "\t\t\t\t\t\t\t\t\t\t                       " << header << "                     \n";
    cout << "\t\t\t\t\t\t\t\t\t\t==========================================================\n\n";
}

string generatePNR(int n)
{
    srand(time(0));

    string pnr;

    int randomNo = rand() % n;

    pnr = "PNR" + to_string(randomNo);

    return pnr;
}

string getCurrentDate()
{
    time_t t = time(NULL);
    struct tm tStruct;
    localtime_s(&tStruct, &t);

    return to_string(tStruct.tm_mday) + "-" + to_string(tStruct.tm_mon + 1) + "-" + to_string(tStruct.tm_year + 1900);
}

size_t strlcpy(char *dst, const char *src, size_t dstsize = numeric_limits<size_t>::max())
{
    size_t srclen = strlen(src);
    size_t copylen = (srclen >= dstsize) ? dstsize - 1 : srclen;

    if (dstsize != 0)
    {
        memcpy(dst, src, copylen);
        dst[copylen] = '\0'; // Null-terminate the destination buffer
    }

    return srclen; // Return the total length of the string it tried to create
}

#endif // UTILS_H
