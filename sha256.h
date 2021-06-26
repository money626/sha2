#ifndef SHA512_SHA256_H
#define SHA512_SHA256_H

#include "sha2.h"

class sha256 : public sha2_32
{
public:
    sha256();

    void init_state() override;

    string done() override;
};


#endif //SHA512_SHA256_H
