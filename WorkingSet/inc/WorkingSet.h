#pragma once
#include <map>
#include <nlohmann/json.hpp>
#include <set>
#include <utility>

namespace WorkingSet
{
    /// Accepts an input nlohmann::json object to initialize global kernel block map
    void Setup(nlohmann::json &);
    /// Parses input trace into kernelSetMap
    void Process(std::string &, std::string &);
    void CreateSets();
    void IntersectKernels();
    void JohnsAlgorithm();
    void parseDeathMap();
    void PrintOutput();
    void PrintSizes();
} // namespace WorkingSet