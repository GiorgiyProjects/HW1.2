#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<algorithm>
#include <cstdarg>
#include "FilterLibrary.hpp"

using namespace std;
int main(int argc, char const *argv[])
{
    try
    {
        pool ip_pool;
        ifstream file;
        file.open("ip_filter.tsv");
        readPoolFromFile(ip_pool, file);
        file.close();

        // TODO reverse lexicographic sort
        LexicographicSort(ip_pool);
        cout << ip_pool;

        // TODO filter by first byte and output
        pool filtered_pool1;
        poolFilter(ip_pool, filtered_pool1, startFromOne);
        cout << filtered_pool1;

        // TODO filter by first and second bytes and output
        pool filtered_pool2;
        poolFilter(ip_pool, filtered_pool2, first46Second70);
        cout << filtered_pool2;

        // TODO filter by any byte and output
        pool filtered_pool3;
        poolFilter(ip_pool, filtered_pool3, any46);
        cout << filtered_pool3;
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
