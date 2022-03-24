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
    if (decl->getKind() != clang::Decl::CXXConstructor &&
        decl->getKind() != clang::Decl::CXXDestructor &&
        decl->getAccess() == clang::AS_public &&
        !decl->isStatic())
    {
        if (decl->getName().lower().rfind("get", 0) != std::string::npos ||
            (shouldCountSetters && decl->getName().lower().rfind("set", 0) != std::string::npos))
        {
            counter++;
        }
    }
    return true;
}