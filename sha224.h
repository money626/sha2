#ifndef SHA512_SHA224_H
#define SHA512_SHA224_H

#include "sha2.h"

class sha224 : public sha2_32
{
public:
    sha224();

    void init_state() override;

    string done() override;
};


#endif //SHA512_SHA224_H
