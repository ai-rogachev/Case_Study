#include <coroutine>
#include <iostream>
#include <climits>

/*
http://www.c-jump.com/CIS77/ASM/Protection/W77_0060_segment_descriptor_examples.htm
*/

template <typename T>
T swap_endian(T u)
{
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union
    {
        T u;
        uint16_t u16[sizeof(T)/2];
    } source, dest;

    source.u = u;

    for (size_t k = 0; k < sizeof(T)/2; k++)
        dest.u16[k] = source.u16[sizeof(T)/2 - k - 1];

    return dest.u;
}


struct address
{
    uint16_t part1;
    uint8_t part2;
    uint8_t part3;
};

struct limit
{
    uint16_t part1;
    uint8_t part2 : 4;
};

struct descriptor_dword_lo
{
    uint16_t limit_part1;
    uint16_t address_part1;
};

struct descriptor_dword_hi
{
    uint8_t address_part2;
    uint8_t accessed       : 1;
    uint8_t type_rw        : 1; // Read / Write
    uint8_t type_ce        : 1; // Conforming / Expansion Direction
    uint8_t type           : 1; // Code / Data - Stace
    uint8_t type_s         : 1; // System / Code or Data segment
    uint8_t dpl            : 2; // Defines segment privilege level
    uint8_t present_flag   : 1; 
    uint8_t limit_part2    : 4;
    uint8_t avl            : 2; // Available and reserved bits
    uint8_t db_flag        : 1; // B / D
    uint8_t granularity    : 1; // Bytes / Pages
    uint8_t address_part3;
};

typedef union {
    descriptor_dword_lo desc;
    uint32_t lo;
} dec_word_lo;

typedef union {
    descriptor_dword_hi desc;
    uint32_t hi;
} dec_word_hi;

typedef union {
    address adr;
    uint32_t uadr;
} address_32_t;

typedef union {
    limit lim;
    uint32_t ulim;
} limit_20_t;

void build_descriptor(dec_word_hi& dh, dec_word_lo& dl) 
{
    dh.desc.type_s = 1;

    bool data = false;
    address_32_t adr;
    limit_20_t lim;

    // Base Address
    std::cout << "Enter base address : " << std::endl;
    std::cin >> std::hex >> adr.uadr;
    adr.uadr <<= 4; // *= 16

    dl.desc.address_part1 = adr.adr.part1;
    dh.desc.address_part2 = adr.adr.part2;
    dh.desc.address_part3 = adr.adr.part3;

    // Segment Limit
    std::cout << "Enter segment limit : " << std::endl;
    std::cin >> std::hex >> lim.ulim;
    lim.ulim -= 1;

    dl.desc.limit_part1 = lim.lim.part1;
    dh.desc.limit_part2 = lim.lim.part2;

    // G = Granularity
    // If clear, the limit is in units of bytes, with a maximum of 220 bytes.
    // If set, the limit is in units of 4096 - byte pages, for a maximum of 232 bytes.
    std::cout << "Enter granularity (0 - bytes / 1 - pages) : " << std::endl;
    bool t;
    std::cin >> t;
    dh.desc.granularity = t;

    // Access rights:
    // P (Present) – segment is in physical memory (P=1) or not (P=0). Used by virtual memory managers
    // If clear, a "segment not present" exception is generated on any reference to this segment
    std::cout << "Enter present flag (0 / 1) : " << std::endl;
    std::cin >> t;
    dh.desc.present_flag = t;

    // 12 bit S - system
    // S = 1 identifies system segment, 
    // S = 0 if application CODE or DATA segment.

    // 11 bit - Type
    // If set, this is a code segment descriptor.If clear, 
    // this is a data / stack segment descriptor, which has "D" replaced by "B", 
    // "C" replaced by "E" and "R" replaced by "W".
    // This is in fact a special case of the 2 - bit type field, 
    // where the preceding bit 12 cleared as "0" refers to more 
    // internal system descriptors, for LDT, LSS, and gates.
    std::cout << "Enter segment type (1 - Code / 0 - Data-Stack)" << std::endl;
    std::cin >> data;
    dh.desc.type = data;

    if (!data) {
        // C (Conforming) – for code segments only, indicates wether the CPL changes when the
        //  segment is called from lesser privilege level(C = 0) or not (C = 1).
        std::cout << "Conforming. Code in this segment may be called from less-privileged levels.  (0 / 1) : " << std::endl;
        std::cin >> t;
        dh.desc.type_ce = t;

        // R (Readable) – in case of code segments indicates whether the code segment is
        //    readable(R = 1) or not (R = 0).Code segments are always executable.
        std::cout << "Readable. Code segments are always executable. Is code readable ? (0 / 1) : " << std::endl;
        std::cin >> t;
        dh.desc.type_rw = t;

        // D = Default operand size
        //  If clear, this is a 16 - bit code segment; if set, this is a 32 - bit segment.
        std::cout << "Default operand size (0 - 16 bits / 1 - 32 bits) : " << std::endl;
        std::cin >> t;
        dh.desc.db_flag = t;
    }
    else {
        // E (Expansion Direction) – used with data segments, indicates whether the segment extends 
        //   from its base address up to base address + limit(E = 0), or from the maximum offset down to the
        //   limit(E = 1).A data stack is usually the expand - down(E = 1) segment what enables the dynamic
        //   change of its size.
        std::cout << "Expansion Direction (0 - data / 1 - stack) : " << std::endl;
        std::cin >> t;
        dh.desc.type_ce = t;

        // W (Writable) – for data segments indicates whether the segment is writable(W = 1) or
        //    not (W = 0).Data segments are of course always readable.Data segments for stack must
        //    be writable.
        std::cout << "Enter write type segment(W) : " << std::endl;
        std::cin >> t;
        dh.desc.type_rw = t;

        // B = Big
        //  If set, the maximum offset size for a data segment 
        //   is increased to 32 - bit 0xffffffff. Otherwise it's the 16-bit
        //   max 0x0000ffff. Essentially the same meaning as "D".
        std::cout << "Big.The maximum offset size for a data segment" << std::endl;
        std::cout << "(1 to 32-bit 0xffffffff / 0 to 16-bit max 0x0000ffff) : " << std::endl;
        std::cin >> t;
        dh.desc.db_flag = t;
    }

    // A (Accessed) – indicates whether the segment was accessed (A=1) since the last time 
    //  bit A was cleared.In virtual memory systems operating upon segments this bit can
    //  determine segment usage.

    // DPL(Descriptor Privilege Level) – indicates privilege level of the segment as a number
    //    0, 1, 2 or 3.
    std::cout << "DPL. Enter privilege level (0-3) : " << std::endl;
    int tmp;
    std::cin >> tmp;
    dh.desc.dpl = tmp;

    // AVL = Available
    //    For software use, not used by hardware

    // 21 bit - L = Long
    // If set, this is a 64 - bit segment(and D must be zero), 
    // and code in this segment uses the 64 - bit instruction encoding.
    // "L" cannot be set at the same time as "D" aka "B".
}

int main() 
{
    dec_word_lo des_l{ 0 };
    dec_word_hi des_h{ 0 };
    //des_h.hi = 0x0040f205;

    build_descriptor(des_h, des_l);
    //std::cout << std::hex << swap_endian<uint32_t>(des_l.lo) 
    //               << " " << swap_endian<uint32_t>(des_h.hi) << std::endl;

    std::cout << std::hex << des_h.hi 
                   << " " << des_l.lo << std::endl;

    return 0;
}