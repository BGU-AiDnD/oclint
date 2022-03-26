#ifndef OCLINT_METRICS_ACCESSTOLOCALDATAMETRIC_H
#define OCLINT_METRICS_ACCESSTOLOCALDATAMETRIC_H

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include "oclint/util/FieldDeclVisitorBase.h"

namespace oclint
{
    class AccessToLocalDataMetric : public FieldDeclVisitorBase<AccessToLocalDataMetric>
    {
    public:
        explicit AccessToLocalDataMetric(clang::FunctionDecl *functionDecl);

        size_t calculate();

        bool VisitCXXMemberCallExpr(clang::CXXMemberCallExpr *expr);
    };
}

#endif //OCLINT_METRICS_ACCESSTOLOCALDATAMETRIC_H
