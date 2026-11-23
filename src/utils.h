#ifndef UTILS_H
#define UTILS_H

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <limits>
#include <random>
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

// 10 characters from 36 symbols give about 52 bits, too many values to guess or enumerate.
string generatePNR()
{
    static const char symbols[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    random_device rd;
    uniform_int_distribution<int> pick(0, 35);

    string pnr;
    for (int i = 0; i < 10; i++)
        pnr += symbols[pick(rd)];

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

// Takes the destination as an array so the copy is always bounded by its real size.
template <size_t N>
size_t strlcpy(char (&dst)[N], const char *src)
{
    size_t srclen = strlen(src);
    size_t copylen = (srclen >= N) ? N - 1 : srclen;

    memcpy(dst, src, copylen);
    dst[copylen] = '\0'; // Null-terminate the destination buffer

    return srclen; // Return the total length of the string it tried to create
}

// Reads one number from cin. On bad input it clears the stream and drops the rest of the line,
// so a stuck failbit cannot spin the menus forever. Exits when input ends.
template <typename T>
bool readNumber(T &value)
{
    if (cin >> value)
        return true;
    if (cin.eof())
        exit(0);
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return false;
}

// Swaps the rewritten temp file in only if every write to it succeeded,
// so a failed open or write never deletes the data file. Returns false if the data file was not replaced.
bool replaceDataFile(fstream &temp, const char *tempPath, const char *dataPath)
{
    temp.close();
    if (temp.fail())
    {
        remove(tempPath);
        return false;
    }
    // POSIX rename replaces dataPath atomically. Windows refuses an existing target, so remove it and retry.
    if (rename(tempPath, dataPath) == 0)
        return true;
    remove(dataPath);
    return rename(tempPath, dataPath) == 0;
}

#endif // UTILS_H
