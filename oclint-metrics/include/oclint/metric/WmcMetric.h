#ifndef OCLINT_METRICS_WMCMETRIC_H
#define OCLINT_METRICS_WMCMETRIC_H

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>

namespace oclint
{
class WmcMetric : public clang::RecursiveASTVisitor<WmcMetric>
{
private:
    int sum;

public:
    int measure(clang::RecordDecl*);

    bool VisitFunctionDecl(clang::FunctionDecl* decl);
};
}

#endif //OCLINT_METRICS_WMCMETRIC_H
