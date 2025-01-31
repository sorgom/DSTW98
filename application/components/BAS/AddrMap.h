//  ============================================================
//  Com address mapping
//  ============================================================
//  created by Manfred Sorgo

#ifndef ADDR_MAP_H
#define ADDR_MAP_H

#include <BAS/coding.h>
#include <BAS/StackArray.h>
#include <ifs/DataTypes.h>

//  ============================================================
//  class AddrMap is the core of Mapper
//  see interface I_Mapper
//  ============================================================
template<size_t CAP>
class AddrMap
{
public:
    inline AddrMap() :
        mIndex(mData)
    {}

    inline void clear()
    {
        mData.clear();
        mIndex.clear();
    }

    inline bool add(const ComAddr& addr)
    {
        return mData.add(addr);
    }

    inline bool index()
    {
        return mIndex.index();
    }

    inline const PosRes find(const ComAddr& addr) const
    {
        return mIndex.find(addr);
    }

    inline const ComAddr& at(const size_t pos) const
    {
        return mData.at(pos);
    }

    inline const ComAddr& at(const PosRes& res) const
    {
        return at(res.pos);
    }

    inline size_t size() const
    {
        return mData.size();
    }

private:
    typedef StackArray<ComAddr, CAP> AddrArray;

    class AddrIndex : public StackIndex<ComAddr, CAP, const ComAddr&>
    {
    public:
        inline AddrIndex(const AddrArray& array) : StackIndex<ComAddr, CAP, const ComAddr&>(array) {}
    protected:
        const ComAddr& getKey(const ComAddr& a) const
        {
            return a;
        }
    };

    AddrArray mData;
    AddrIndex mIndex;
};
#endif // _H
