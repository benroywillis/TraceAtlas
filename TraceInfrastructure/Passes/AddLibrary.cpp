#include <llvm/Pass.h>
#include <llvm/IR/Metadata.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Module.h>
#include "Passes/AddLibrary.h"
#include "Passes/CommandArgs.h"

using namespace llvm;

namespace DashTracer
{
	namespace Passes
	{
		static uint64_t UID = 0;
        MDNode* libName;
		bool AddLibrary::runOnFunction(Function& F)
		{
			if(MDNode* N = F.getMetadata("libs"))
			{
				//ignore
			}
			else
			{
				F.setMetadata("libs", libName);
			}
            
			return false;
		}

		void AddLibrary::getAnalysisUsage(AnalysisUsage& AU) const
		{
			AU.setPreservesAll();
		}
    
        bool AddLibrary::doInitialization(Module& M)
        {
            libName = MDNode::get(M.getContext(), MDString::get(M.getContext(), LibraryName));
            return false;
        }

		char AddLibrary::ID = 0;
		static RegisterPass<AddLibrary> X("AddLibrary", "Labels functions with the library name", true, true);
	} // namespace Passes
} // namespace DashTracer