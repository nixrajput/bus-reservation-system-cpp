#ifndef ADMIN_H
#define ADMIN_H

#include <fstream>
#include <random>
#include <stdint.h>
#include <string>

#ifndef _WIN32
#include <sys/stat.h>
#endif

using namespace std;

const char *const ADMIN_FILE = "../data/admin.dat";
const int HASH_ROUNDS = 100000;

inline uint32_t rotr(uint32_t x, int n)
{
    return (x >> n) | (x << (32 - n));
}

// SHA-256 (FIPS 180-4). Returns the 32-byte digest.
string sha256(const string &data)
{
    static const uint32_t k[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
    uint32_t h[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

    string msg = data;
    uint64_t bitLength = (uint64_t)data.size() * 8;
    msg += (char)0x80;
    while (msg.size() % 64 != 56)
        msg += (char)0;
    for (int i = 7; i >= 0; i--)
        msg += (char)((bitLength >> (i * 8)) & 0xff);

    for (size_t block = 0; block < msg.size(); block += 64)
    {
        uint32_t w[64];
        for (int i = 0; i < 16; i++)
        {
            w[i] = 0;
            for (int j = 0; j < 4; j++)
                w[i] = (w[i] << 8) | (unsigned char)msg[block + i * 4 + j];
        }
        for (int i = 16; i < 64; i++)
        {
            uint32_t s0 = rotr(w[i - 15], 7) ^ rotr(w[i - 15], 18) ^ (w[i - 15] >> 3);
            uint32_t s1 = rotr(w[i - 2], 17) ^ rotr(w[i - 2], 19) ^ (w[i - 2] >> 10);
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }

        uint32_t v[8];
        for (int i = 0; i < 8; i++)
            v[i] = h[i];

        for (int i = 0; i < 64; i++)
        {
            uint32_t s1 = rotr(v[4], 6) ^ rotr(v[4], 11) ^ rotr(v[4], 25);
            uint32_t ch = (v[4] & v[5]) ^ (~v[4] & v[6]);
            uint32_t t1 = v[7] + s1 + ch + k[i] + w[i];
            uint32_t s0 = rotr(v[0], 2) ^ rotr(v[0], 13) ^ rotr(v[0], 22);
            uint32_t maj = (v[0] & v[1]) ^ (v[0] & v[2]) ^ (v[1] & v[2]);
            for (int j = 7; j > 0; j--)
                v[j] = v[j - 1];
            v[4] += t1;
            v[0] = t1 + s0 + maj;
        }

        for (int i = 0; i < 8; i++)
            h[i] += v[i];
    }

    string digest;
    for (int i = 0; i < 8; i++)
        for (int j = 3; j >= 0; j--)
            digest += (char)((h[i] >> (j * 8)) & 0xff);
    return digest;
}

string toHex(const string &bytes)
{
    static const char digits[] = "0123456789abcdef";
    string hex;
    for (size_t i = 0; i < bytes.size(); i++)
    {
        unsigned char c = bytes[i];
        hex += digits[c >> 4];
        hex += digits[c & 15];
    }
    return hex;
}

// Salted SHA-256 repeated HASH_ROUNDS times, so each password guess costs HASH_ROUNDS hashes.
string hashPassword(const string &salt, const string &password)
{
    string digest = sha256(salt + password);
    for (int i = 1; i < HASH_ROUNDS; i++)
        digest = sha256(digest);
    return toHex(digest);
}

// Compares every character, so the time taken does not reveal where the hashes differ.
bool sameHash(const string &a, const string &b)
{
    if (a.size() != b.size())
        return false;
    unsigned char diff = 0;
    for (size_t i = 0; i < a.size(); i++)
        diff |= a[i] ^ b[i];
    return diff == 0;
}

// Writes "<salt> <hash>" to ADMIN_FILE. The password itself is never stored.
bool saveAdminPassword(const string &password)
{
    random_device rd;
    string salt;
    for (int i = 0; i < 16; i++)
        salt += (char)(rd() & 0xff);
    salt = toHex(salt);

#ifndef _WIN32
    mode_t oldMask = umask(077); // creates the file as owner read/write only (0600)
#endif
    ofstream adminFileStream(ADMIN_FILE, ios::out | ios::trunc);
#ifndef _WIN32
    umask(oldMask);
#endif

    adminFileStream << salt << ' ' << hashPassword(salt, password) << '\n';
    adminFileStream.close();
    return !adminFileStream.fail();
}

#endif // ADMIN_H
