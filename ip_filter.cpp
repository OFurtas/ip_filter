#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    auto start = 0;
    auto stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void printVector(const std::vector<std::vector<int>> ip_pool) { 
    for(const auto& ip : ip_pool) {
        bool first = true;
        for(const auto& ip_part : ip)
        {
            if(first) {
                first = false;
            }
            else {
                std::cout << ".";
            }
            std::cout << ip_part;
        }
        std::cout << std::endl;
    }
}

//check if string is number
bool isNumber(const std::string& str)
{
    return !str.empty() && std::find_if(str.begin(), 
        str.end(), [](unsigned char c) { return !std::isdigit(c); }) == str.end();
}

// check if ip is valid
std::vector<int> transformToIntIp(const std::vector<std::string> &ip) {
    std::vector<int> numIP;
    numIP.reserve(ip.size());

    if(ip.size() != 4) {
        return numIP;
    }
    for(const auto& ip_part : ip) {
        if(isNumber(ip_part)) {
            numIP.push_back(std::stoi(ip_part));
        }
        else {
            numIP.clear();
            break;
        }
    }
    return numIP;
}

//simple sort
void reverseSort(std::vector<std::vector<int>> &v) {
    std::sort(v.begin(), v.end(), [](std::vector<int> a, std::vector<int> b) {
        bool areEqual = a.at(0) == b.at(0); 
        if (!areEqual) {
            return a.at(0) > b.at(0);
        } 
        
        //second part
        areEqual = a.at(1) == b.at(1);
        if (!areEqual) {
            return a.at(1) > b.at(1);
        }

        //third part 
        areEqual = a.at(2) == b.at(2);
        if (!areEqual) {
            return a.at(2) > b.at(2);
        }       

        //fourth part
        areEqual = a.at(3) == b.at(3);
        if (!areEqual) {
            return a.at(3) > b.at(3);
        }
        return true;
        });  
}

// filter first byte in ip == firstByte
std::vector<std::vector<int>> filter(const std::vector<std::vector<int>> &v, int firstByte) {
    std::vector<std::vector<int>> result;
    result.reserve(v.size());
    for(const auto& ip : v) {
        if(ip[0] == firstByte) {
            result.push_back(ip);
        }
        if(ip[0] < firstByte) {
            break;
        }
    }
    return result;
}

// filter first byte in ip == firstByte, second byte == secondByte
std::vector<std::vector<int>> filter(const std::vector<std::vector<int>> &v, int firstByte, int secondByte) {
    std::vector<std::vector<int>> result;
    result.reserve(v.size());
    for(const auto& ip : v) {
        if(ip[0] == firstByte) {
            if(ip[1] == secondByte) {
                result.push_back(ip);
            }
            if(ip[1] < secondByte)  {
                break;
            }
        }
        if(ip[0] < firstByte) {
            break;
        }
    }
    return result;
}

//filter any byte in ip == anyByte
std::vector<std::vector<int>> filter_any(const std::vector<std::vector<int>> &v, int anyByte) {
    std::vector<std::vector<int>> result;
    result.reserve(v.size());
    for(const auto& ip : v) {
        if(ip[0] == anyByte || ip[1] == anyByte || ip[2] == anyByte || ip[3] == anyByte) {
            result.push_back(ip);
        }
    }
    return result;
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::vector<int>> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            // get only first str in line
            std::vector<std::string> v = split(line, '\t');
            if(v.empty()) {
                continue;
            }

            auto vecIp = transformToIntIp(split(v.at(0), '.'));
            if(vecIp.size() == 4) {
                // dont add if ip is invalid
                ip_pool.push_back(vecIp);
            }
            
        }
        // TODO reverse lexicographically sort
        reverseSort(ip_pool);
        printVector(ip_pool);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // std::cout << "filter by first byte" << std::endl;
        std::vector<std::vector<int>> ipFilterFirstByte = filter(ip_pool, 1);
        printVector(ipFilterFirstByte);

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // std::cout << "filter by first and second bytes" << std::endl;
        std::vector<std::vector<int>> ipFilterFirstSecondByte = filter(ip_pool, 46, 70);
        printVector(ipFilterFirstSecondByte);
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // std::cout << "filter by any byte" << std::endl;
        std::vector<std::vector<int>> ipFilterAnyByte = filter_any(ip_pool, 46);
        printVector(ipFilterAnyByte);
        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
