#ifndef OCLINT_METRIC_CLASSPUBLICMETHODCOUNT_H
#define OCLINT_METRIC_CLASSPUBLICMETHODCOUNT_H

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>

namespace oclint
{
class ClassPublicMethodCountMetric : public clang::RecursiveASTVisitor<ClassPublicMethodCountMetric>
{
private:
    int counter;

public:
    int count(clang::RecordDecl*);

    bool VisitFunctionDecl(clang::FunctionDecl* decl);
};
}

#endif //OCLINT_METRIC_CLASSPUBLICMETHODCOUNT_H
