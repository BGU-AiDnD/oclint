#ifndef OCLINT_METRIC_CLASSPUBLICACCESSORCOUNT_H
#define OCLINT_METRIC_CLASSPUBLICACCESSORCOUNT_H

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>

namespace oclint
{
class ClassPublicAccessorCountMetric : public clang::RecursiveASTVisitor<ClassPublicAccessorCountMetric>
{
private:
    int counter;
    bool shouldCountSetters;

public:
    ClassPublicAccessorCountMetric(bool shouldCountSetters) :
        shouldCountSetters{shouldCountSetters} {}

    int count(clang::RecordDecl*);

    bool VisitFunctionDecl(clang::FunctionDecl* decl);
};
}

#endif //OCLINT_METRIC_CLASSPUBLICACCESSORCOUNT_H
