#include "Passes/Markov.h"
#include "AtlasUtil/Annotate.h"
#include "Passes/Annotate.h"
#include "Passes/CommandArgs.h"
#include "Passes/Functions.h"
#include "Passes/MarkovIO.h"
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Type.h>
#include <llvm/Pass.h>
#include <llvm/Support/raw_ostream.h>
#include <string>
#include <vector>

using namespace llvm;

namespace DashTracer::Passes
{
    bool Markov::runOnFunction(Function &F)
    {
        for (auto fi = F.begin(); fi != F.end(); fi++)
        {
            auto *BB = cast<BasicBlock>(fi);
            auto firstInsertion = BB->getFirstInsertionPt();
            auto *firstInst = cast<Instruction>(firstInsertion);
            IRBuilder<> firstBuilder(firstInst);
            int64_t id = GetBlockID(BB);
            Value *idValue = ConstantInt::get(Type::getInt64Ty(BB->getContext()), (uint64_t)id);
            std::vector<Value *> args;
            args.push_back(idValue);
            firstBuilder.CreateCall(MarkovIncrement, args);
        }
        return true;
    }

    bool Markov::doInitialization(Module &M)
    {
        MarkovIncrement = cast<Function>(M.getOrInsertFunction("MarkovIncrement", Type::getVoidTy(M.getContext()), Type::getInt64Ty(M.getContext())).getCallee());
        return false;
    }

    void Markov::getAnalysisUsage(AnalysisUsage &AU) const
    {
        AU.addRequired<DashTracer::Passes::EncodedAnnotate>();
        AU.addRequired<DashTracer::Passes::MarkovIO>();
    }

    char Markov::ID = 0;
    static RegisterPass<Markov> Y("Markov", "Adds Markov Dumping to the binary", true, false);
} // namespace DashTracer::Passes