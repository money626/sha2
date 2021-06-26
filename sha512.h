#ifndef SHA512_SHA512_H
#define SHA512_SHA512_H

#include "sha2.h"

using namespace std;

class sha512 : public sha2_64
{
public:
    sha512();

    void init_state() override;

    string done() override;
};

#endif //SHA512_SHA512_H
