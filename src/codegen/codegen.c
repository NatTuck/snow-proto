
#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Transforms/Scalar.h>

void
sc_init()
{
    LLVMLinkInJIT();
    LLVMInitializeNativeTarget();
}

