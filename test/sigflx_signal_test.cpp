#include <gtest/gtest.h>
#include "sigflx_lib/sigflx_allocators_aligned.h"
#include "core/sigflx_signal.h"

using TestSignal = SignumFlux::Signal<float,SignumFlux::Allocators::AlignedAllocator<float>>;

TEST(SignalBuildTest,DefaultConstructor)
{
    TestSignal a;
    EXPECT_EQ(a.data(),nullptr);
    EXPECT_EQ(a.frames(),0);
    EXPECT_FLOAT_EQ(a.sampleRate(),1.0f);
    EXPECT_FLOAT_EQ(a.duration(),0.0f);
}

TEST(SignalBuildTest,CopyAndMove)
{
    TestSignal a(10,44100.0);
    EXPECT_NE(a.data(),nullptr);
    EXPECT_EQ(a.frames(),10);
    EXPECT_FLOAT_EQ(a.sampleRate(),44100.0f);

    TestSignal b(a);
    EXPECT_NE(b.data(),nullptr);
    EXPECT_EQ(b.frames(),10);
    EXPECT_FLOAT_EQ(b.sampleRate(),44100.0f);

    TestSignal c(std::move(a));
    EXPECT_NE(c.data(),nullptr);
    EXPECT_EQ(c.frames(),10);
    EXPECT_FLOAT_EQ(c.sampleRate(),44100.0f);

    EXPECT_EQ(a.data(),nullptr);
    EXPECT_EQ(a.frames(),0);
    EXPECT_FLOAT_EQ(a.sampleRate(),1);

}