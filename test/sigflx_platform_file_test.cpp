#include <gtest/gtest.h>
#include "sigflx_lib/sigflx_platform_file.h"

using namespace SignumFlux::Platform;
const char * path = "./M1F1-Alaw-AFsp.wav";
const char * out = "./test.wav";

TEST(FileMethod,AllMethods)
{
    const char * error_path = nullptr;
    int fd = FileOperation<CurrentOS>::open(path,O_RDWR);
    int fd1 = FileOperation<CurrentOS>::open(error_path,O_RDONLY);

    EXPECT_NE(fd,-1);
    EXPECT_EQ(fd1,-1);

    std::uint8_t buffer[100000];
    ssize_t count = FileOperation<CurrentOS>::read(fd,buffer,100000);
    EXPECT_NE(count,-1);
    
    int fd2 = FileOperation<CurrentOS>::open(out,O_RDWR | O_CREAT);

    EXPECT_NE(fd2,-1);

    ssize_t count1 = FileOperation<CurrentOS>::write(fd2,buffer,count);

    EXPECT_NE(count1,-1);

    int result1 = FileOperation<CurrentOS>::close(fd);
    int result2 = FileOperation<CurrentOS>::close(fd2);

    EXPECT_NE(result1,-1);
    EXPECT_NE(result2,-1);
    
}