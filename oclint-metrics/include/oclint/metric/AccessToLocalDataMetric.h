#ifndef OCLINT_METRICS_ACCESSTOLOCALDATAMETRIC_H
#define OCLINT_METRICS_ACCESSTOLOCALDATAMETRIC_H

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>

namespace oclint
{
    class AccessToLocalDataMetric : public clang::RecursiveASTVisitor<AccessToLocalDataMetric>
    {
    public:
        int calculate(clang::FunctionDecl *decl);
    };
}

#endif //OCLINT_METRICS_ACCESSTOLOCALDATAMETRIC_H
