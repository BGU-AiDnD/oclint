#include "oclint/metric/MethodNumOfLocalVarsMetric.h"
#include <iostream>

using namespace oclint;

int MethodNumOfLocalVarsMetric::calculate(clang::FunctionDecl *decl)
{
    TraverseDecl(decl);
    return count;
}

// This also includes parameters.
bool MethodNumOfLocalVarsMetric::VisitVarDecl(clang::VarDecl *decl)
{
    // TODO: Should include static variables?
    // TODO: Should check `decl->isLocalVarDeclOrParm()` before incrementing
    //   the counter?
    if (decl->isLocalVarDeclOrParm())
    {
        count++;
    }
    return true;
}
