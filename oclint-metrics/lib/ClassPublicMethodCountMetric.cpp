#include "oclint/metric/ClassPublicMethodCountMetric.h"
#include "oclint/util/ASTUtil2.h"
#include <iostream>

using namespace oclint;

int ClassPublicMethodCountMetric::count(clang::RecordDecl *decl)
{
    counter = 0;
    TraverseDecl(decl);
    return counter;
}

bool ClassPublicMethodCountMetric::VisitFunctionDecl(clang::FunctionDecl *decl)
{
    if (decl->getKind() != clang::Decl::CXXConstructor &&
        decl->getKind() != clang::Decl::CXXDestructor &&
        decl->getAccess() == clang::AS_public)
    {
        counter++;
    }
    return true;
}