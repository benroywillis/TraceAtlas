#include "inc/WorkingSet.h"
#include <iostream>

using namespace std;
namespace WorkingSet
{
    /// Maps a kernel index to its set of basic block IDs
    std::map<int, std::set<int64_t>> kernelBlockMap;
    void Setup(nlohmann::json& j)
    {
        for (auto &[k, l] : j["Kernels"].items())
        {
            int index = stoi(k);
            cout << "Initializing kernel index " << index << endl;
            nlohmann::json kernel = l["Blocks"];
            kernelBlockMap[index] = kernel.get<set<int64_t>>();
        }
        for( const auto& key : kernelBlockMap )
        {
            cout << "The kernel index is " << key.first << endl;
            for( const auto& ind : key.second )
            {
                cout << ind << endl;
            }
        }
    }
    /// Maps a kernel index to a pair of sets (first -> ld addr, second -> st addr)
    std::map<int, std::pair< std::set<uint64_t>, std::set<uint64_t> >> kernelSetMap; 
    int currentKernelID;
    void Process(std::string &key, std::string &value)
    {
        if( key == "BBEnter")
        {
            int64_t blockID = stoi(value, nullptr, 0);
            for( const auto& ID : kernelBlockMap )
            {
                if( ID.second.find(blockID) != ID.second.end() )
                {
                    currentKernelID = ID.first;
                    break;
                }
            } 
        }
        else if( key == "LoadAddress" )
        {
            uint64_t addr = stoul(value, nullptr, 16);
            kernelSetMap[currentKernelID].first.insert(addr);
        }
        else if( key == "StoreAddress" )
        {
            uint64_t addr = stoul(value, nullptr, 16);
            kernelSetMap[currentKernelID].second.insert(addr);
        }
        else if( key == "BBExit" )
        {
            // do nothing for now
        }
    }
    void Print()
    {
        cout << "Outputting kernelSetMap" << endl;
        for( const auto& key : kernelSetMap )
        {
            cout << "The kernel index is: " << key.first << endl;
            cout << "The ld addrs are: " << endl;
            for( const auto& ind : key.second.first )
            {
                cout << ind << ",";
            }
            cout << "The st addrs are: " << endl;
            for( const auto& ind: key.second.second )
            {
                cout << ind << ",";
            }
        }
    }
} // namespace WorkingSets