//
// Created by Yevhen Pozdniakov on 4/22/19.
//
#include "tasks.hpp"

namespace
{
    constexpr char* sub = (char*) "ZAV"; // can't be more than 64*8
    constexpr char* str = (char*) "XYZAVKfdffVKLAfdjkjfklfdnkljfdkl;";
}

namespace bits
{
    template <typename T>
    T clear_leftmost_set(const T value) {

        assert(value != 0);

        return value & (value - 1);
    }


    template <typename T>
    unsigned get_first_bit_set(const T value) {

        assert(value != 0);

        return __builtin_ctz(value);
    }


    template <>
    unsigned get_first_bit_set<uint64_t>(const uint64_t value) {

        assert(value != 0);

        return __builtin_ctzl(value);
    }

} // namespace bits

int strpos(const char *str, const char *sub)
{
    if (!str || !sub)
    {
        return -1;
    }

    auto ptr = strstr(str, sub);

    if (!ptr)
    {
        return -1;
    }

    return ptr - str;
}

void test_task3_strstr()
{
    auto start = std::chrono::high_resolution_clock::now();
    int pos = -1;
    for (std::size_t i = 0; i < NTIMES3; ++i)
    {
        for (std::size_t j = 0; j < NTIMES3; ++j)
        {
            for (std::size_t k = 0; k < NTIMES3; ++k)
            {
                pos = strpos(str, sub);
            }
        }
    }

//    std::cout<<"Substring found at "<<pos<<std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto total_processing_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    printf("test_task3_strstr\t %lld ms\t\n", total_processing_time.count());
}

int strpos_custom(const char *str, const char *sub)
{
    if (!*sub)
        return -1; // an empty substring matches everything

    const char* start = str;

    for (; *str; ++str)
    {
        if (*str == *sub)
        {
            const char *s1, *s2;
            s1 = str + 1;
            s2 = sub + 1;

            while (*s1 && *s2 && towlower(*s1) == towlower(*s2))
                ++s1, ++s2;

            if (!*s2)
                return (str - start);
        }
    }

    return -1;
}

void test_task3_slow()
{
    auto start = std::chrono::high_resolution_clock::now();
    int pos = -1;
    for (std::size_t i = 0; i < NTIMES3; ++i)
    {
        for (std::size_t j = 0; j < NTIMES3; ++j)
        {
            for (std::size_t k = 0; k < NTIMES3; ++k)
            {
                pos = strpos_custom(str, sub);
            }
        }
    }

//    std::cout<<"Substring found at "<<pos<<std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto total_processing_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    printf("test_task3_slow\t %lld ms\t\n", total_processing_time.count());
}

//    http://0x80.pl/articles/simd-strfind.html#algorithm-3-sse4-2-specific-pcmpestrm
size_t strpos_SSE(const char* str, size_t str_size, const char* sub, size_t sub_size)
{
    assert(strlen(sub) < 64*8);

    const __m128i sub_128 = _mm_loadu_si128((__m128i*)sub);

    for (size_t i = 0; i < str_size; i += 16)
    {
        constexpr int mode = _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_ORDERED | _SIDD_BIT_MASK;

        const __m128i str_128   = _mm_loadu_si128((__m128i*)(str + i));

        // return 64-bit mask
        const __m128i res = _mm_cmpestrm(sub_128, sub_size, str_128, str_size - i, mode);

        uint64_t mask = _mm_cvtsi128_si64(res); // _mm_loadu_si128

        while (mask != 0)
        {
            const auto bitpos = bits::get_first_bit_set(mask);

            if (memcmp(str + i + bitpos, sub, sub_size) == 0)
            {
                return i + bitpos;
            }

            mask = bits::clear_leftmost_set(mask);
        }
    }

    return std::string::npos;
}

void test_task3_SSE()
{
    auto start = std::chrono::high_resolution_clock::now();
    int pos = -1;
    for (std::size_t i = 0; i < NTIMES3; ++i)
    {
        for (std::size_t j = 0; j < NTIMES3; ++j)
        {
            for (std::size_t k = 0; k < NTIMES3; ++k)
            {
                pos = strpos_SSE(str, strlen(str), sub, strlen(sub));
            }
        }
    }

//    std::cout<<"Substring found at "<<pos<<std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto total_processing_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    printf("test_task3_SSE\t %lld ms\t\n", total_processing_time.count());
}

