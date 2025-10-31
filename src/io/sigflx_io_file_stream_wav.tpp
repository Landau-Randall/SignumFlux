#include "io/sigflx_io_file_stream_wav.h"


namespace SignumFlux
{
namespace IO
{

template<typename Allocator>
void FileStream<Format::WAV,Allocator>::headerAnalyze()
{
    if (isOpen_)
    {
        std::uint8_t head[sizeof(WAVHeader)];
        ssize_t actual = Platform::FileOperation<Platform::CurrentOS>::read(fileDescriptor_,head,sizeof(WAVHeader));
        std::size_t offset = 0;
        if (actual == sizeof(WAVHeader))
        {
            std::memcpy(header_.chunkID,head + offset,4);
            offset += 4;
            header_.chunkSize =  bytesRead<std::uint32_t>(head + offset,Endian::Little);
            offset += 4;
            std::memcmp(header_.format,head + offset,4);
            offset += 4;
            std::memcmp(header_.subChunk1ID,head + offset,4);
            offset += 4;
            header_.subChunk1Size = bytesRead<std::uint32_t>(head + offset,Endian::Little);
            offset += 4;
            header_.audioFormat = bytesRead<std::uint16_t>(head + offset,Endian::Little);
            offset += 2;
            header_.channels = bytesRead<std::uint16_t>(head + offset,Endian::Little);
            offset += 2;
            header_.sampleRate = bytesRead<std::uint32_t>(head + offset,Endian::Little);
        }
    }
}

template<typename Allocator>
void FileStream<Format::WAV,Allocator>::initialHeader()
{
    std::memcpy(header_.chunkID,"RIFF",4);
    header_.chunkSize = 36;
    std::memcpy(header_.format,"WAVE",4);
    std::memcpy(header_.subChunk1ID,"fmt ",4);
    header_.subChunk1Size = 16;
    header_.audioFormat = 1;
    header_.channels = 1;
    header_.sampleRate = 44100;
    header_.byteRate = 88200;
    header_.blockAlign = 2;
    header_.bitsPerSample = 16;
    std::memcpy(header_.subChunk2ID,"data",4);
    header_.subChunk2Size = 0;
}

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
isHeaderWritten_(object.isHeaderWritten_),
fileDescriptor_(object.fileDesriptor_),
mode_(object.mode_),
allocator_(std::move(object.allocator_))
{
    object.buffer_ = nullptr;
    object.bufferSize_ = 0;
    object.bufferDataSize_ = 0;
    object.bufferOffset_ = 0;
    object.isOpen_ = false;
    object.isHeaderWritten_ = false;
    object.fileDesriptor_ = -1;
    object.mode_ = Mode::Read;
}

template<typename Allocator>
FileStream<Format::WAV,Allocator>::FileStream(const char * path):
allocator_()
{

}

template<typename Allocator>
FileStream<Format::WAV,Allocator>::~FileStream()
{
    if (mode_ != Mode::Read)
    {
        if (bufferDataSize_ != 0)
        {
            Platform::FileOperation<Platform::CurrentOS>::write(fileDescriptor_,buffer_ + bufferOffset_,bufferDataSize_ - bufferOffset_);
        }
    }
    close();
    allocator_.deallocate(buffer_,bufferSize_);
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

template<typename Allocator>
void FileStream<Format::WAV,Allocator>::open(const char * path,Mode mode)
{
    if (isOpen_)
        close();
    int flags = 0;
    switch (mode)
    {
        case Mode::Read  : flags = O_RDONLY; break;
        case Mode::Write : flags = O_WRONLY | O_CREAT | O_TRUNC; break;
        case Mode::ReadWrite : flags = O_RDWR | O_CREAT; break;
    }
    mode_ = mode;

    fileDescriptor_ = Platform::FileOperation<Platform::CurrentOS>::open(path, flags);
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
        if (mode == Mode::Read)
            headerAnalyze();
        else if (mode == OpenMode::Write || mode == OpenMode::ReadWrite)
            initialHeader();
    }

    bufferDataSize_ = 0;
    bufferOffset_ = 0;
}

template<typename Allocator>
void FileStream<Format::WAV,Allocator>::close()
{
    if (isOpen_)
    {
        Platform::FileOperation<Platform::CurrentOS>::close(fileDescriptor_);
    }
    fileDescriptor_ = -1;
    mode_ = Mode::Read;
    isOpen_ = false;
    bufferDataSize_ = 0;
    bufferOffset_ = 0;
}

template<typename Allocator>
typename FileStream<Format::WAV,Allocator>::SizeType FileStream<Format::WAV,Allocator>::read(std::uint8_t * buffer,SizeType size)
{
    if (mode_ == Mode::Write)
        throw std::runtime_error("FileStream is only write\n");
    
    if (isOpen_ && buffer != nullptr && size != 0)
    {
        SizeType bytesReaded = 0;

        while (bytesReaded < size)
        {
            SizeType available = bufferDataSize_ - bufferOffset_;

            if (available > 0)
            {
                SizeType toCopy = std::min(available,size - bytesReaded);
                std::memcpy(buffer + bytesReaded,buffer_ + bufferOffset_,toCopy);
                bufferOffset_ += toCopy;
                bytesReaded += toCopy;
            }
            else
            {
                ssize_t actualBytes = Platform::FileOperation<Platform::CurrentOS>::read(fileDescriptor_, buffer_, bufferSize_);
                if (actualBytes <= 0)
                    break; 
                bufferDataSize_ = actualBytes;
                bufferOffset_ = 0;
            }
        }

        return bytesReaded;
    }
    else
    {
        return 0;
    }
}

template<typename Allocator>
typename FileStream<Format::WAV,Allocator>::SizeType FileStream<Format::WAV,Allocator>::write(const std::uint8_t * buffer,SizeType size)
{
    if (mode_ == Mode::Read)
        throw std::runtime_error("FileStream is only read\n");

    if (isOpen_ && buffer != nullptr && size != 0)
    {
        if (!isHeaderWritten_)
        {
            headerWrite();
            isHeaderWritten_ = true;
        }

        SizeType bytesWrited = 0 ;
        while (bytesWrited < size)
        {
            SizeType available = bufferDataSize_ - bufferOffset_;
            if (available > 0)
            {
                SizeType toCopy = std::min(available,size - bytesWrited);
                std::memcpy(buffer_ + bufferOffset_,buffer + bytesWrited,toCopy);
                bufferOffset_ += toCopy;
                bytesWrited += toCopy;
            }
            else
            {
                ssize_t actualBytes = Platform::FileOperation<Platform::CurrentOS>::write(fileDescriptor_,buffer_,bufferSize_);
                if (actualBytes <= 0)
                    break;
                bufferDataSize_ = actualBytes;
                bufferOffset_ = 0;
            }
        }

        return bytesWrited;
    }
    else
    {
        return 0;
    }
}

}
}