#define BOOST_TEST_MODULE tests
#include "FilterLibrary.hpp"
#include <fstream>
#include <iostream>
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(testLexiSort)
{
    pool ip_pool;
    std::ifstream file("test_data/testLexi.tsv");
    if (!file.is_open())
    {
        std::cout << "could not find test file!" << std::endl;
        BOOST_CHECK_EQUAL(1,0);
        return;
    }
    readPoolFromFile(ip_pool, file);
    file.close();

    LexicographicSort(ip_pool);
    std::string resultPool = poolToString(ip_pool);
    std::string expectedResult = "179.210.46.4\n"
                                  "157.39.22.224\n"
                                  "113.162.120.135\n"
                                  "113.46.145.156\n"
                                  "79.180.73.190\n";

    BOOST_CHECK_EQUAL(resultPool, expectedResult);
}

BOOST_AUTO_TEST_CASE(testFilter1)
{
    pool ip_pool;
    std::ifstream file("test_data/ip_filter.tsv");
    if (!file.is_open())
    {
        std::cout << "could not find test file!" << std::endl;
        BOOST_CHECK_EQUAL(1,0);
        return;
    }
    readPoolFromFile(ip_pool, file);
    file.close();

    pool filtered_pool;
    poolFilter(ip_pool, filtered_pool, startFromOne);
    std::string resultPool = poolToString(filtered_pool);

    std::string expectedResult = "1.29.168.152\n"
                                 "1.231.69.33\n"
                                 "1.1.234.8\n"
                                 "1.87.203.225\n"
                                 "1.70.44.170\n";
    BOOST_CHECK_EQUAL(resultPool, expectedResult);
}

BOOST_AUTO_TEST_CASE(testFilter2)
{
    pool ip_pool;
    std::ifstream file("test_data/ip_filter.tsv");
    if (!file.is_open())
    {
        std::cout << "could not find test file!" << std::endl;
        BOOST_CHECK_EQUAL(1,0);
        return;
    }
    readPoolFromFile(ip_pool, file);
    file.close();

    pool filtered_pool;
    poolFilter(ip_pool, filtered_pool, first46Second70);
    std::string resultPool = poolToString(filtered_pool);

    std::string expectedResult = "46.70.113.73\n"
                                 "46.70.147.26\n"
                                 "46.70.225.39\n"
                                 "46.70.29.76\n";

    BOOST_CHECK_EQUAL(resultPool, expectedResult);
}

BOOST_AUTO_TEST_CASE(testFilter3)
{
    pool ip_pool;
    std::ifstream file("test_data/testLexi.tsv");
    if (!file.is_open())
    {
        std::cout << "could not find test file!" << std::endl;
        BOOST_CHECK_EQUAL(1,0);
        return;
    };
    readPoolFromFile(ip_pool, file);
    file.close();

    pool filtered_pool;
    poolFilter(ip_pool, filtered_pool, any46);
    std::string resultPool = poolToString(filtered_pool);

    std::string expectedResult = "113.46.145.156\n"
                                 "179.210.46.4\n";

    BOOST_CHECK_EQUAL(resultPool, expectedResult);
}