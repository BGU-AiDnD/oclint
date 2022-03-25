#ifndef OCLINT_METRICS_METHODNUMOFLOCALVARSMETRIC_H
#define OCLINT_METRICS_METHODNUMOFLOCALVARSMETRIC_H

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>

namespace oclint
{
    class MethodNumOfLocalVarsMetric : public clang::RecursiveASTVisitor<MethodNumOfLocalVarsMetric>
    {
    private:
        int count;

    public:
        int calculate(clang::FunctionDecl *decl);

        bool VisitVarDecl(clang::VarDecl *decl);
    };
}

#endif //OCLINT_METRICS_METHODNUMOFLOCALVARSMETRIC_H
