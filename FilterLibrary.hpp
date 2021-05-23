#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <string>
#include <vector>
#include<algorithm>
#include <cstdarg>

using pool = std::vector<std::vector<int>>;

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

void readPoolFromFile(pool& ip_pool, std::ifstream& file)
{
    for(std::string line; std::getline(file, line);)
    {
        std::vector<std::string> v = split(line, '\t');
        auto ip_filter_strings = split(v.at(0), '.');
        std::vector<int> ip_filter_ints;
        std::transform(ip_filter_strings.begin(), ip_filter_strings.end(), std::back_inserter(ip_filter_ints),
                       [](const std::string& str) { return std::stoi(str);});
        ip_pool.push_back(ip_filter_ints);
    }
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

std::string poolToString(const pool& ip_pool)
{
    std::string result = "";
    for(const auto& ip : ip_pool)
    {
        std::string c = "";
        for(const auto& ip_part : ip)
        {
            result += c + std::to_string(ip_part);
            c = ".";
        }
        result += "\n";
    }
    return result;
}

void LexicographicSort(pool& ip_pool)
{
    sort(ip_pool.begin(), ip_pool.end(), [] (std::vector<int> v1, std::vector<int> v2)
    {
        for (int i = 0; i < std::min(v1.size(), v2.size()); ++i)
        {
            if (v1[i] != v2[i])
            {
                return (v1[i] > v2[i]);
            }
        }
        return  true;
    });
    return;
}

auto startFromOne = [](const std::vector<int>& v)
{
    return (v[0] == 1);
};

auto first46Second70 = [](const std::vector<int>& v)
{
    return ((v[0] == 46) && (v[1] == 70));
};

auto any46 = [](const std::vector<int>& v)
{
    return (find(v.begin(), v.end(), 46) != v.end());
};

template<typename T>
void poolFilter(pool& in, pool& out, T functor)
{
    copy_if(in.begin(), in.end(), back_inserter(out), functor);
}