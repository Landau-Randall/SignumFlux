#include "io/sigflx_io_file_stream_wav.h"


namespace SignumFlux
{
namespace IO
{
template<typename Allocator>
void FileStream<Format::WAV,Allocator>::createFile(const char * path)
{

}

template<typename Allocator>
FileStream<Format::WAV,Allocator>::FileStream():
allocator_()
{
    buffer_ = allocator_.allocate(bufferSize_);
}

template<typename Allocator>
FileStream<Format::WAV,Allocator>::FileStream(const AllocatorType & allocator):
allocator_(allocator)
{
    buffer_ = allocator_.allocate(bufferSize_);
}

template<typename Allocator>
FileStream<Format::WAV,Allocator>::FileStream(SizeType bufferSize):
bufferSize_(bufferSize),
allocator_()
{
    buffer_ = allocator_.allocate(bufferSize_);
}

template<typename Allocator>
FileStream<Format::WAV,Allocator>::FileStream(SizeType bufferSize,const AllocatorType & allocator):
bufferSize_(bufferSize),
allocator_(allocator)
{
    buffer_ = allocator_.allocate(bufferSize_);
}

template<typename Allocator>
FileStream<Format::WAV,Allocator>::FileStream(FileStream && object) noexcept:
header_(std::move(object.header_)),
buffer_(object.buffer_),
bufferSize_(object.bufferSize_),
bufferDataSize_(object.bufferDataSize_),
bufferOffset_(object.bufferOffset_),
isOpen_(object.isOpen_),
fileDescriptor_(object.fileDesriptor_),
allocator_(std::move(object.allocator_))
{
    object.buffer_ = nullptr;
    object.bufferSize_ = 0;
    object.bufferDataSize_ = 0;
    object.bufferOffset_ = 0;
    object.isOpen_ = false;
    object.fileDesriptor_ = -1;
}

template<typename Allocator>
FileStream<Format::WAV,Allocator>::FileStream(const char * path):
allocator_()
{

}

template<typename Allocator>
void FileStream<Format::WAV,Allocator>::open(const char * path)
{
    if (isOpen_)
        close();
    
    fileDescriptor_ = Platform::FileOperation<Platform::CurrentOS>::open(path,O_RDONLY);

    if (fileDescriptor_ == -1)
    {
        if (errno == ENOENT)
        {
            createFile(path);
        }
        else
        {
            throw std::runtime_error("invalid file name\n");
        }
    }
    else
    {
        isOpen_ = true;
        headerAnalyze();
    }

    bufferDataSize_ = 0;
    bufferOffset_ = 0;
}

}
}