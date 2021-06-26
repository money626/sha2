#include "sha224.h"

sha224::sha224() : sha2_32()
{
    sha224::init_state();
}

void sha224::init_state()
{
    state[0] = 0xc1059ed8;
    state[1] = 0x367cd507;
    state[2] = 0x3070dd17;
    state[3] = 0xf70e5939;
    state[4] = 0xffc00b31;
    state[5] = 0x68581511;
    state[6] = 0x64f98fa7;
    state[7] = 0xbefa4fa4;
    hash_value = "";
    length = 0;
    current_block_length = 0;
    for (size_t i = 0; i < BLOCK_SIZE; i++)
    {
        block[i] = 0x00;
    }
}

string sha224::done()
{
    if (current_block_length)
    {
        pad_data(nullptr);
    }
    stringstream ss;
    for (size_t i = 0; i < 7; i++)
    {
        ss << hex << setw(8) << setfill('0') << state[i];
    }
    hash_value = ss.str();
    return hash_value;
}