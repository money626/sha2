#include "sha256.h"

sha256::sha256() : sha2_32()
{
    sha256::init_state();
}

void sha256::init_state()
{
    state[0] = 0x6a09e667;
    state[1] = 0xbb67ae85;
    state[2] = 0x3c6ef372;
    state[3] = 0xa54ff53a;
    state[4] = 0x510e527f;
    state[5] = 0x9b05688c;
    state[6] = 0x1f83d9ab;
    state[7] = 0x5be0cd19;
    hash_value = "";
    length = 0;
    current_block_length = 0;
    for (size_t i = 0; i < BLOCK_SIZE; i++)
    {
        block[i] = 0x00;
    }
}

string sha256::done()
{
    if (current_block_length)
    {
        pad_data(nullptr);
    }
    stringstream ss;
    for (unsigned int &i : state)
    {
        ss << hex << setw(8) << setfill('0') << i;
    }
    hash_value = ss.str();
    return hash_value;
}