#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<algorithm>
#include <cstdarg>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

template <class T>
inline std::ostream& operator << (std::ostream& os, const std::vector<T>& ip_pool)
{
    for(const auto& ip : ip_pool)
    {
        std::string c = "";
        for(const auto& ip_part : ip)
        {
            os << c << ip_part;
            c = ".";
        }
        os << std::endl;
    }
    return os;
}

using namespace std;
int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographic sort
        sort(ip_pool.begin(), ip_pool.end(), [] (vector<string> v1, vector<string> v2)
        {
            for (int i = 0; i < std::min(v1.size(), v2.size()); ++i)
            {
                if (v1[i] != v2[i])
                {
                    return (std::stoi(v1[i]) > std::stoi(v2[i]));
                }
            }
            return  true;
        });
        cout << ip_pool;

        // TODO filter by first byte and output
        // ip = filter(1)
        vector<vector<string>> filtered_pool1;
        copy_if(ip_pool.begin(), ip_pool.end(), back_inserter(filtered_pool1), [](vector<string> v)
        {
            return stoi(v[0]) == 1;
        });
        cout << filtered_pool1;

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        vector<vector<string>> filtered_pool2;
        copy_if(ip_pool.begin(), ip_pool.end(), back_inserter(filtered_pool2), [](vector<string> v)
        {
            return (stoi(v[0]) == 46 && stoi(v[1]) == 70);
        });
        cout << filtered_pool2;

        // TODO filter by any byte and output
        // ip = filter_any(46)
        vector<vector<string>> filtered_pool3;
        copy_if(ip_pool.begin(), ip_pool.end(), back_inserter(filtered_pool3), [](vector<string> v)
        {
            return (find(v.begin(), v.end(), "46") != v.end());
        });
        cout << filtered_pool3;

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
