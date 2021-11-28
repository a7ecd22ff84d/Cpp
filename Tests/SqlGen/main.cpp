#include <gmock/gmock.h>

auto main(int argc, char* argv[]) -> int
{
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}