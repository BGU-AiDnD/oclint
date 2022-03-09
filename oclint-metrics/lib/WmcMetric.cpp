#include "oclint/metric/WmcMetric.h"
#include "oclint/util/ASTUtil2.h"
#include "oclint/metric/CyclomaticComplexityMetric.h"
#include <iostream>

int WmcMetric::measure(clang::RecordDecl *decl)
{
    sum = 0;
    TraverseDecl(decl);
    return sum;
}

bool WmcMetric::VisitFunctionDecl(clang::FunctionDecl *decl)
{
    sum += getCyclomaticComplexity(decl);
    return true;
}