#include "oclint/metric/ClassPublicAccessorCountMetric.h"
#include "oclint/util/ASTUtil2.h"
#include <iostream>

int ClassPublicAccessorCountMetric::count(clang::CXXRecordDecl *decl)
{
    counter = 0;
    TraverseDecl(decl);
    return counter;
}

bool ClassPublicAccessorCountMetric::VisitCXXMethodDecl(clang::CXXMethodDecl *decl)
{
    if (decl->getKind() != clang::Decl::CXXConstructor &&
        decl->getAccess() == clang::AS_public &&
        !decl->isStatic() &&
        decl->getName().lower().rfind("get", 0) != std::string::npos)
    {
        counter++;
    }
    return true;
}