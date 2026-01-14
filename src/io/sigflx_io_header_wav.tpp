#include "io/sigflx_io_header_wav.h"

namespace SignumFlux
{
namespace IO
{
WAVHeader::WAVHeader()
{
    Strings::stringCopy(chunkID,"RIFF",4);
    chunkSize = 36;
    Strings::stringCopy(format,"WAVE",4);
}

WAVHeader::~WAVHeader()
{

}

template<WAVCode code>
WAVHeader WAVHeader::Head() 
{
    return WAVHeader();
}

template<>
WAVHeader WAVHeader::Head<WAVCode::PCM>()
{
    WAVHeader result;
    
}
}
}