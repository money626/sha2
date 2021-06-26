#ifndef SHA512_SHA384_H
#define SHA512_SHA384_H

#include "sha2.h"

class sha384 : public sha2_64
{
public:
    sha384();

    void init_state() override;

    string done() override;
};


#endif //SHA512_SHA384_H
