#include "sha512.h"

sha512::sha512() : sha2_64()
{
    sha512::init_state();
}

void sha512::init_state()
{
    state[0] = 0x6a09e667f3bcc908;
    state[1] = 0xbb67ae8584caa73b;
    state[2] = 0x3c6ef372fe94f82b;
    state[3] = 0xa54ff53a5f1d36f1;
    state[4] = 0x510e527fade682d1;
    state[5] = 0x9b05688c2b3e6c1f;
    state[6] = 0x1f83d9abfb41bd6b;
    state[7] = 0x5be0cd19137e2179;
    hash_value = "";
    length = 0;
    current_block_length = 0;
    for (size_t i = 0; i < BLOCK_SIZE; i++)
    {
        block[i] = 0x00;
    }
}

string sha512::done()
{
    if (current_block_length)
    {
        pad_data(nullptr);
    }
    stringstream ss;
    for (uint64_t i : state)
    {
        ss << hex << setw(16) << setfill('0') << i;
    }
    hash_value = ss.str();
    return hash_value;
}
// ----------------------------------------------------------------------------- //
