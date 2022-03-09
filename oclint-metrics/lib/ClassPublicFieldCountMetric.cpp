#include "oclint/metric/ClassPublicFieldCountMetric.h"
#include "oclint/util/ASTUtil2.h"

int ClassPublicFieldCountMetric::count(clang::RecordDecl *decl)
{
    counter = 0;
    TraverseDecl(decl);
    return counter;
}

bool ClassPublicFieldCountMetric::VisitFieldDecl(clang::FieldDecl *decl)
{
    // This is already non-static because of FieldDecl, so there's no need to check this.
    if (decl->getAccess() == clang::AS_public)
    {
        counter++;
    }
    return true;
}
