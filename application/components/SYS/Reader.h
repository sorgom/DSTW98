//  ============================================================
//  class Reader implements I_Reader
//  ============================================================
#ifndef READER_H
#define READER_H

#include <ifs/I_Reader.h>
#include <BAS/coding.h>

class Reader : public I_Reader
{
public:
    void read();
    inline const ComSetup& getComSetup() const { return mComSetup; }

    INSTANCE_DEC(Reader)
    NOCOPY(Reader)
private:
    ComSetup mComSetup;
    inline Reader() {}
};
#endif // _H
