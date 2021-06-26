#include "hashCalculator.h"

string hashCalculator::get_hash() const
{
    switch (hash_mode)
    {
        case SHA224:
            return sha224_hash.get_hash();
        case SHA256:
            return sha256_hash.get_hash();
        case SHA384:
            return sha384_hash.get_hash();
        case SHA512:
            return sha512_hash.get_hash();
        default:
            return "No such hash mode";
    }
}

string hashCalculator::hash(const string &hash_string)
{
    switch (hash_mode)
    {
        case SHA224:
            return sha224_hash.hash(hash_string);
        case SHA256:
            return sha256_hash.hash(hash_string);
        case SHA384:
            return sha384_hash.hash(hash_string);
        case SHA512:
            return sha512_hash.hash(hash_string);
        default:
            return "No such hash mode";
    }
}

void hashCalculator::hash_file(const char *input_file, const char *output_file)
{
    switch (hash_mode)
    {
        case SHA224:
            sha224_hash.hash_file(input_file, output_file);
            break;
        case SHA256:
            sha256_hash.hash_file(input_file, output_file);
            break;
        case SHA384:
            sha384_hash.hash_file(input_file, output_file);
            break;
        case SHA512:
            sha512_hash.hash_file(input_file, output_file);
            break;
        default:;
    }
}

unsigned long long hashCalculator::get_length() const
{
    switch (hash_mode)
    {
        case SHA224:
            return sha224_hash.get_length();
        case SHA256:
            return sha256_hash.get_length();
        case SHA384:
            return sha384_hash.get_length();
        case SHA512:
            return sha512_hash.get_length();
        default:
            return -1;
    }

}

void hashCalculator::process_file_data(const char *file_name)
{
    switch (hash_mode)
    {
        case SHA224:
            sha224_hash.process_file_data(file_name);
            break;
        case SHA256:
            sha256_hash.process_file_data(file_name);
            break;
        case SHA384:
            sha384_hash.process_file_data(file_name);
            break;
        case SHA512:
            sha512_hash.process_file_data(file_name);
            break;
        default:;
    }
}

hashCalculator::hashCalculator()
{
    hash_mode = SHA512;
}

hashCalculator::hashCalculator(HASH_MODE mode)
{
    if (mode != SHA224 && mode != SHA384 && mode != SHA256 && mode != SHA512)
    {
        hash_mode = SHA512;
    } else
    {
        hash_mode = mode;
    }

}

bool hashCalculator::set_hash_mode(int mode)
{
    if (mode != SHA224 && mode != SHA384 && mode != SHA256 && mode != SHA512)
    {
        return false;
    }
    hash_mode = static_cast<HASH_MODE>(mode);
    return true;
}

void hashCalculator::set_print_round(bool val)
{
    switch (hash_mode)
    {
        case SHA224:
            sha224_hash.print_round = val;
            break;
        case SHA256:
            sha256_hash.print_round = val;
            break;
        case SHA384:
            sha384_hash.print_round = val;
            break;
        case SHA512:
            sha512_hash.print_round = val;
            break;
        default:;
    }
}
