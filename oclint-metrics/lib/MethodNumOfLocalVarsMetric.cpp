#include "oclint/metric/MethodNumOfLocalVarsMetric.h"
#include <iostream>

using namespace oclint;

int MethodNumOfLocalVarsMetric::calculate(clang::FunctionDecl *decl)
{
    TraverseDecl(decl);
    return count;
}

bool MethodNumOfLocalVarsMetric::VisitVarDecl(clang::VarDecl *decl)
{
    // TODO: Should include static variables?
    // This also includes parameters.
    count++;
    return true;
}
