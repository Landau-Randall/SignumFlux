#pragma once
#include <cstdint>
#include "io/sigflx_io_file_stream_template.h"
#include "sigflx_lib/sigflx_allocators_aligned.h"
#include "sigflx_lib/sigflx_platform_file.h"

namespace SignumFlux
{
namespace IO
{
struct WAVHeader
{
    char          chunkID[4];
    std::uint32_t chunkSize;
    char          format[4];
    char          subChunk1ID[4];
    std::uint32_t subChunk1Size;
    std::uint16_t audioFormat;
    std::uint16_t channels;
    std::uint32_t sampleRate;
    std::uint32_t byteRate;
    std::uint16_t blockAlign;
    std::uint16_t bitsPerSample;
    char          subChunk2ID[4];
    std::uint32_t subChunk2Size;
};

template<typename Allocator>
class FileStream<Format::WAV,Allocator> : public Stream
{
public:
    using DataType = std::uint8_t;
    using SizeType = std::size_t;
    using AllocatorType = Allocator;
private:
    WAVHeader header_{};
    DataType * buffer_ = nullptr;
    SizeType bufferSize_ = 8192;
    SizeType bufferDataSize_ = 0;
    SizeType bufferOffset_ = 0;
    bool isOpen_ = false;
    int fileDescriptor_ = -1;
    AllocatorType allocator_;

    void headerAnalyze();
    void createFile(const char * path);
public:
    FileStream();
    explicit FileStream(const AllocatorType & allocator);
    explicit FileStream(SizeType bufferSize);
    FileStream(SizeType bufferSize,const AllocatorType & allocator);
    FileStream(const FileStream & object) = delete;
    FileStream(FileStream && objcet) noexcept;
    explicit FileStream(const char * path);
    FileStream(const char * path,const AllocatorType & allocator);
    
    ~FileStream();

    FileStream & operator=(const FileStream & object) = delete;
    FileStream & operator=(FileStream && object);

    void open(const char * path) override;
    void close() override;
    SizeType read(std::uint8_t * buffer,SizeType size) override;
    SizeType write(const std::uint8_t * buffer,SizeType size) override;
    bool isOpen() const;
};

template<typename Allocator>
using WAVStream = FileStream<Format::WAV,Allocator>;
}
}

#include "../../src/io/sigflx_io_file_stream_wav.tpp"