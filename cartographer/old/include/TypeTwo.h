#pragma once
#include <llvm/IR/Module.h>
#include <set>
#include <string>
namespace TypeTwo
{
    void Setup(std::vector<llvm::Module *> &bitcode, std::set<std::set<int64_t>> k);
    void Process(std::string &key, std::string &value);
    std::set<std::set<int64_t>> Get();
    extern std::set<int32_t> *blockCaller;
} // namespace TypeTwo