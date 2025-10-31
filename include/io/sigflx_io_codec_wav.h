#pragma once
#include <type_traits>
#include "core/sigflx_signal.h"
#include "io/sigflx_io_codec_template.h"
#include "io/sigflx_io_file_stream_wav.h"

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
template<WAVCode code>
struct CodecMethod;

template<>
struct CodecMethod<WAVCode::PCM>
{
    template<typename T>
    static void encode(const T * input,std::uint8_t * output,std::size_t element);

    template<typename T>
    static void decode(const std::uint8_t * input,T * output,std::size_t element);
};

template<>
class Decoder<Format::WAV> : public Module
{
private:
    //Strings::String<char,StringBufferAllocator> name_
    const WAVHeader & header_;
public:
    template<typename Allocator>
    void initialHeader(const FileStream<Format::WAV,Allocator> & stream);

    template<typename BufferAllocator,typename T,typename SignalAllocator>
    void process(const FileStream<Format::WAV,BufferAllocator> & input, Signal<T,SignalAllocator> & output);

    template<typename T>
    void process(const std::uint8_t * input,T * output,std::size_t len);

    const char * name() const noexcept override;
};
}
}

#include "../../src/io/sigflx_io_codec_wav.tpp"