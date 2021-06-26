#ifndef SHA512_HASHCALCULATOR_H
#define SHA512_HASHCALCULATOR_H


#include "sha224.h"
#include "sha256.h"
#include "sha384.h"
#include "sha512.h"

enum HASH_MODE
{
    SHA224 = 1,
    SHA256,
    SHA384,
    SHA512
};

class hashCalculator
{
public:
    hashCalculator();

    hashCalculator(HASH_MODE);

    string hash(const string &);

    string get_hash() const;

    void hash_file(const char *, const char *output = "hash.txt");

    unsigned long long get_length() const;

    void process_file_data(const char *);

    void set_print_round(bool);

    bool set_hash_mode(int);

private:
    HASH_MODE hash_mode;
    sha224 sha224_hash;
    sha256 sha256_hash;
    sha384 sha384_hash;
    sha512 sha512_hash;
};


#endif //SHA512_HASHCALCULATOR_H
