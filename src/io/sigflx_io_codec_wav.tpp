#include "io/sigflx_io_codec_wav.h"


namespace SignumFlux
{
namespace IO
{
template<typename T>
void CodecMethod<WAVCode::PCM>::encode(const T * input,std::uint8_t * output,std::size_t element)
{
    static_assert(std::is_same<T,std::uint8_t>::value || std::is_same<T,std::int16_t>::value,"PCM only support uint8 and int16");
}
}
}