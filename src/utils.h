#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <string>
#include <cstring>
#include <limits>
#include <ctime>
#include <stddef.h>
#include <sstream>

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

#if defined(_WIN32) || defined(_WIN64)
    // Windows: Use localtime_s
    localtime_s(&tStruct, &t);
#else
    // POSIX-compliant systems (Linux and macOS): Use localtime_r
    localtime_r(&t, &tStruct);
#endif

    // Use stringstream for efficient string construction
    ostringstream oss;
    oss << tStruct.tm_mday << "-"
        << (tStruct.tm_mon + 1) << "-"
        << (tStruct.tm_year + 1900);

    return oss.str();
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
