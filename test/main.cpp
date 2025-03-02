#include "TimeStamp.h"

int main(int argc, char *argv[])
{
    std::string time_val = TimeStamp::getTimeNow().getTimeToFormatString();
    std::cout << "time:" << time_val << std::endl;
    return 0;
}