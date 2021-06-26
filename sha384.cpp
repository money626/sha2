#include "sha384.h"

sha384::sha384() : sha2_64()
{
    sha384::init_state();
}

void sha384::init_state()
{
    state[0] = 0xcbbb9d5dc1059ed8;
    state[1] = 0x629a292a367cd507;
    state[2] = 0x9159015a3070dd17;
    state[3] = 0x152fecd8f70e5939;
    state[4] = 0x67332667ffc00b31;
    state[5] = 0x8eb44a8768581511;
    state[6] = 0xdb0c2e0d64f98fa7;
    state[7] = 0x47b5481dbefa4fa4;
    hash_value = "";
    length = 0;
    current_block_length = 0;
    for (size_t i = 0; i < BLOCK_SIZE; i++)
    {
        block[i] = 0x00;
    }
}

string sha384::done()
{
    if (current_block_length)
    {
        pad_data(nullptr);
    }
    stringstream ss;
    for (size_t i = 0; i < 6; i++)
    {
        ss << hex << setw(16) << setfill('0') << state[i];
    }
    hash_value = ss.str();
    return hash_value;
}