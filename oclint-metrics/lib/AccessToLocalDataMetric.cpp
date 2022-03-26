#include "oclint/metric/AccessToLocalDataMetric.h"
#include "oclint/util/FieldDeclFinderVisitor.h"
#include "oclint/util/ASTUtil2.h"
#include <unordered_set>

using namespace oclint;

AccessToLocalDataMetric::AccessToLocalDataMetric(clang::FunctionDecl *functionDecl) :
    FieldDeclVisitorBase<AccessToLocalDataMetric>{functionDecl} {}

size_t AccessToLocalDataMetric::calculate()
{
    if (recordDecl == nullptr)
    {
        return 0;
    }

    TraverseDecl(functionDecl);
    return fieldDecls->size();
}

bool AccessToLocalDataMetric::VisitCXXMemberCallExpr(clang::CXXMemberCallExpr *expr)
{
    clang::FunctionDecl *methodDecl = expr->getMethodDecl();
    if (isGetterMethod(methodDecl) || isSetterMethod(methodDecl))
    {
        (FieldDeclFinderVisitor{methodDecl, fieldDecls}).insertAll();
    }
    return true;
}
