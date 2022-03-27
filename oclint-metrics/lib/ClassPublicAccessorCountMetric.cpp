#include "oclint/metric/ClassPublicAccessorCountMetric.h"
#include "oclint/util/ASTUtil2.h"
#include <iostream>

using namespace oclint;

int ClassPublicAccessorCountMetric::count(clang::RecordDecl *decl)
{
    counter = 0;
    TraverseDecl(decl);
    return counter;
}

bool ClassPublicAccessorCountMetric::VisitFunctionDecl(clang::FunctionDecl *decl)
{
    if (decl->getAccess() == clang::AS_public &&
        !decl->isStatic() &&
        (isGetterMethod(decl) || isSetterMethod(decl)))
    {
        counter++;
    }
    return true;
}