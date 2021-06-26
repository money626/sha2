#include "sha2.h"

uint64_t uint8_to_uint64(const uint8_t *src)
{
    uint64_t val = 0;
    for (int i = 0; i < 8; i++)
    {
        val |= static_cast<uint64_t>(src[i]) << ((7 - i) * 8);
    }
    return val;
}

uint32_t uint8_to_uint32(const uint8_t *src)
{
    uint64_t val = 0;
    for (int i = 0; i < 4; i++)
    {
        val |= static_cast<uint64_t>(src[i]) << ((3 - i) * 8);
    }
    return val;
}

void fill_length(unsigned long long length, uint8_t *block_location)
{
    length *= 8;
    for (size_t i = 0; i < 8; i++)
    {
        block_location[i] = (length >> ((7 - i) * 8)) & 0xFF;
    }
}

// sha2

sha2::sha2()
{
    block = nullptr;
    hash_value = "";
    length = 0;
    current_block_length = 0;
    print_round = false;
    BLOCK_SIZE = 0;
}


void sha2::process_data(const uint8_t *data, unsigned int size)
{
    unsigned int data_read = 0;
    while (size)
    {
        if (current_block_length == 0 && size >= BLOCK_SIZE)
        {
            memcpy(block, data + data_read, BLOCK_SIZE);
            size -= BLOCK_SIZE;
            length += BLOCK_SIZE;
            data_read += BLOCK_SIZE;
            compress_data(nullptr);
        } else
        {
            const int batch_size = min(size, BLOCK_SIZE - current_block_length);
            memcpy(block + current_block_length, data + data_read, batch_size);
            size -= batch_size;
            current_block_length += batch_size;
            if (batch_size == BLOCK_SIZE)
            {
                compress_data(nullptr);
                length += BLOCK_SIZE;
                current_block_length = 0;
            }
        }
    }
}


string sha2::get_hash() const
{
    return hash_value;
}


string sha2::hash(const string &in)
{
    const auto str = reinterpret_cast<const uint8_t *>(in.c_str());
    init_state();
    process_data(str, in.length());

    pad_data(nullptr);
    return done();
}


void sha2::process_file_data(const char *input_file_name, bool output, const char *output_file_name)
{
    init_state();
    ifstream in;
    ofstream *out = nullptr;
    if (output)
    {
        out = new ofstream;
        out->open(output_file_name);
        if (out->fail())
        {
            wxMessageBox("Cannot open output file!");
            return;
        }
    }
    in.open(input_file_name, ios::in | ios::binary);
    if (in.fail())
    {
        wxMessageBox("Input file not found");
        return;
    }

    auto t1 = high_resolution_clock::now();
    unsigned int count = 0;
    while (true)
    {
        in >> noskipws >> block[count++];
        if (in.eof())
        {
            count--;
            current_block_length += count;
            pad_data(out);
            break;
        }
        if (count == BLOCK_SIZE)
        {
            length += count;
            compress_data(out);
            count = 0;
        }
    }
    auto t2 = high_resolution_clock::now();
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    in.close();
    if (out)
    {
        *out << "Input file: "<< input_file_name << endl;
        *out << "Hash: "<< done() << endl;
        *out << dec << ms_int.count() << "ms used. " << endl;
        *out << "performance: " << get_length() << "bytes processed." << endl;
        if (ms_int.count())
        {
            *out << get_length() * 1000 / ms_int.count() << "bytes/s";
        }
        out->close();
        delete out;

    } else
    {
        cout << done() << endl;
    }
}


void sha2::print_block() const
{
    cout << BLOCK_SIZE << endl;
    for (size_t i = 0; i < BLOCK_SIZE; i++)
    {
        cout << hex << setw(2) << setfill('0') << static_cast<int>(block[i]) << " ";
        if (i % 16 == 15)
        {
            cout << endl;
        }
    }
    cout << endl;
}


unsigned long long sha2::get_length() const
{
    return length;
}


void sha2::hash_file(const char *input_file, const char *output_file)
{
    process_file_data(input_file, true, output_file);
}

// sha2 64

sha2_64::sha2_64() : sha2()
{
    BLOCK_SIZE = 128;
    block = new uint8_t[BLOCK_SIZE];
}

sha2_64::~sha2_64()
{
    delete[] block;
}

void sha2_64::compress_data(ofstream *out)
{
    uint64_t s[8], w[80];
    print_block();

    auto Ch = [&](uint64_t x, uint64_t y, uint64_t z) -> uint64_t
    {
        return ((x & y) ^ (~x & z));
    };
    auto Maj = [&](uint64_t x, uint64_t y, uint64_t z) -> uint64_t
    {
        return ((x & y) ^ (x & z) ^ (y & z));
    };
    auto rotr = [&](uint64_t x, const int n) -> uint64_t
    {
        return ((x >> n) | (x << (64 - n)));
    };
    auto shr = [&](uint64_t x, const int n) -> uint64_t
    {
        return x >> n;
    };
    auto Sigma0 = [&](uint64_t x) -> uint64_t
    {
        return (rotr(x, 28) ^ rotr(x, 34) ^ rotr(x, 39));
    };
    auto Sigma1 = [&](uint64_t x) -> uint64_t
    {
        return (rotr(x, 14) ^ rotr(x, 18) ^ rotr(x, 41));
    };
    auto sigma0 = [&](uint64_t x) -> uint64_t
    {
        return (rotr(x, 1) ^ rotr(x, 8) ^ shr(x, 7));
    };
    auto sigma1 = [&](uint64_t x) -> uint64_t
    {
        return (rotr(x, 19) ^ rotr(x, 61) ^ shr(x, 6));
    };


    for (size_t i = 0; i < 8; i++)
    {
        s[i] = state[i];
    }
    for (size_t i = 0; i < 16; i++)
    {
        w[i] = uint8_to_uint64(block + (8 * i));
    }
    for (size_t i = 16; i < 80; i++)
    {
        w[i] = sigma1(w[i - 2]) + w[i - 7] + sigma0(w[i - 15]) + w[i - 16];
    }


    for (size_t i = 0; i < 80; i++)
    {
        const uint64_t tmp1 = s[7] + Sigma1(s[4]) + Ch(s[4], s[5], s[6]) + k[i] + w[i];
        const uint64_t tmp2 = Sigma0(s[0]) + Maj(s[0], s[1], s[2]);
        s[7] = s[6];
        s[6] = s[5];
        s[5] = s[4];
        s[4] = s[3] + tmp1;
        s[3] = s[2];
        s[2] = s[1];
        s[1] = s[0];
        s[0] = tmp1 + tmp2;
        if (print_round && out != nullptr)
        {
            *out << "round" << dec << setw(2) << setfill('0') << i << ": ";
            for (size_t j = 0; j < 8; j++)
            {
                *out << hex << setw(16) << setfill('0') << s[i];
            }
            *out << endl;
        }
    }
    for (size_t i = 0; i < 8; i++)
    {
        state[i] += s[i];
    }
}

void sha2_64::pad_data(ofstream *out)
{
    length += current_block_length;
    block[current_block_length++] = 0x80;
    if (current_block_length > BLOCK_SIZE - 16)
    {
        while (current_block_length < BLOCK_SIZE)
        {
            block[current_block_length++] = 0x00;
        }
        compress_data(out);
        current_block_length = 0;
    }
    // assume there is less than 2 ^ 64 - 1 bits
    // should change length to uint128_t but there is no uint128_t for my compiler
    // should be BLOCK_SIZE - 16 for the line below
    while (current_block_length < BLOCK_SIZE - 8)
    {
        block[current_block_length++] = 0x00;
    }

    fill_length(length, block + current_block_length);

    compress_data(out);
    current_block_length = 0;
}

// sha 2 32----------------------------------------------------------------------------- //

sha2_32::sha2_32() : sha2()
{
    BLOCK_SIZE = 64;
    block = new uint8_t[BLOCK_SIZE];
}

sha2_32::~sha2_32()
{
    delete[] block;
}

void sha2_32::compress_data(ofstream *out)
{
    uint32_t s[8], w[64];

    auto Ch = [&](uint32_t x, uint32_t y, uint32_t z) -> uint32_t
    {
        return ((x & y) ^ (~x & z));
    };
    auto Maj = [&](uint32_t x, uint32_t y, uint32_t z) -> uint32_t
    {
        return ((x & y) ^ (x & z) ^ (y & z));
    };
    auto rotr = [&](uint32_t x, const int n) -> uint32_t
    {
        return ((x >> n) | (x << (32 - n)));
    };
    auto shr = [&](uint32_t x, const int n) -> uint32_t
    {
        return x >> n;
    };
    auto Sigma0 = [&](uint32_t x) -> uint32_t
    {
        return (rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22));
    };
    auto Sigma1 = [&](uint64_t x) -> uint64_t
    {
        return (rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25));
    };
    auto sigma0 = [&](uint32_t x) -> uint32_t
    {
        return (rotr(x, 7) ^ rotr(x, 18) ^ shr(x, 3));
    };
    auto sigma1 = [&](uint32_t x) -> uint32_t
    {
        return (rotr(x, 17) ^ rotr(x, 19) ^ shr(x, 10));
    };


    for (size_t i = 0; i < 8; i++)
    {
        s[i] = state[i];
    }
    for (size_t i = 0; i < 16; i++)
    {
        w[i] = uint8_to_uint32(block + (4 * i));
    }
    for (size_t i = 16; i < 64; i++)
    {
        w[i] = sigma1(w[i - 2]) + w[i - 7] + sigma0(w[i - 15]) + w[i - 16];
    }


    for (size_t i = 0; i < 64; i++)
    {
        const uint32_t tmp1 = s[7] + Sigma1(s[4]) + Ch(s[4], s[5], s[6]) + k[i] + w[i];
        const uint32_t tmp2 = Sigma0(s[0]) + Maj(s[0], s[1], s[2]);
        s[7] = s[6];
        s[6] = s[5];
        s[5] = s[4];
        s[4] = s[3] + tmp1;
        s[3] = s[2];
        s[2] = s[1];
        s[1] = s[0];
        s[0] = tmp1 + tmp2;
        if (print_round && out)
        {
            *out << "round" << dec << setw(2) << setfill('0') << i << ": ";
            for (size_t j = 0; j < 8; j++)
            {
                *out << hex << setw(8) << setfill('0') << s[i];
            }
            *out << endl;
        }
    }
    for (size_t i = 0; i < 8; i++)
    {
        state[i] += s[i];
    }
}

void sha2_32::pad_data(ofstream *out)
{
    length += current_block_length;
    block[current_block_length++] = 0x80;
    if (current_block_length > BLOCK_SIZE - 8)
    {
        while (current_block_length < BLOCK_SIZE)
        {
            block[current_block_length++] = 0x00;
        }
        compress_data(out);
        current_block_length = 0;
    }
    while (current_block_length < BLOCK_SIZE - 8)
    {
        block[current_block_length++] = 0x00;
    }

    fill_length(length, block + current_block_length);

    compress_data(out);
    current_block_length = 0;
}
