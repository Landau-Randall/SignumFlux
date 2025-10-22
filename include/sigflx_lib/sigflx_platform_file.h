#pragma once
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
#include <cstdint>
#include "sigflx_lib/sigflx_platform_detect.h"

namespace SignumFlux
{
namespace Platform
{
template<OSType >
struct FileOperation;

template<>
struct FileOperation<OSType::Unknown>
{
    static int open(const char* path, int flags) 
    {
        throw std::runtime_error("Unsupported platform");
    }

    static int close(int fd) 
    {
        throw std::runtime_error("Unsupported platform");
    }

    static ssize_t read(int fd, void* buffer, std::size_t size) 
    {
        throw std::runtime_error("Unsupported platform");
    }

    static ssize_t write(int fd, const void* buffer, std::size_t size) 
    {
        throw std::runtime_error("Unsupported platform");
    }
};

template<>
struct FileOperation<OSType::Linux>
{
    static int open(const char* path, int flags) 
    {
        if (path != nullptr)
        {
            return ::open(path,flags);
        }
        return -1;
    }

    static int close(int fd)
    {
        if (fd == -1)
        {
            return -1;
        }
        return ::close(fd);
    }

    static ssize_t read(int fd,std::uint8_t * buffer,std::size_t size)
    {
        if (fd == -1 || buffer == nullptr)
        {
            return -1; 
        }
        return ::read(fd,buffer,size);
    }

    static ssize_t write(int fd, const std::uint8_t * buffer, std::size_t size) 
    {
        if (fd == -1 || buffer == nullptr)
        {
            return -1; 
        }
        return ::write(fd,buffer,size);
    }
};
}
}