#pragma once
#include <cstddef>
#include <cstdint>

namespace SignumFlux
{
class Stream
{
public:
    virtual ~Stream() = default;

    virtual void open(const char * path) = 0;
    virtual void close() = 0;
    virtual std::size_t read(std::uint8_t * buffer,std::size_t size) = 0;
    virtual std::size_t write(const std::uint8_t * buffer,std::size_t size) = 0;

    virtual bool isOpen() const = 0;
};
}