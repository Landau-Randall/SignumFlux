#pragma once
#include <cstdint>
#include "sigflx_lib/sigflx_strings_c_methods.h"
#include "sigflx_lib/sigflx_container_vector.h"

namespace SignumFlux
{
namespace IO
{

enum class WAVCode
{
    PCM = 1,
    ADPCM = 2,
    IEEE_FLOAT = 3,
    ALAW = 6,
    MULAW = 7,
    IMA_ADPCM = 17
};

struct Chunk
{
    char id[4];
    std::uint32_t chunkSize;
    std::uint8_t * data;
};

struct WAVHeader
{
    char chunkID[4];
    std::uint32_t chunkSize;
    char format[4];
    Container::Vector<Chunk> chunk;

    WAVHeader();
    ~WAVHeader();

    template<WAVCode >
    static WAVHeader Head();
};
}
}

#include "../../src/io/sigflx_io_header_wav.tpp"