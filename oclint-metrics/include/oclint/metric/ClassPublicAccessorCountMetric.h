#ifndef OCLINT_METRIC_CLASSPUBLICACCESSORCOUNT_H
#define OCLINT_METRIC_CLASSPUBLICACCESSORCOUNT_H

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>

class ClassPublicAccessorCountMetric : public clang::RecursiveASTVisitor<ClassPublicAccessorCountMetric>
{
private:
    int counter;

public:
    int count(clang::CXXRecordDecl*);

    bool VisitCXXMethodDecl(clang::CXXMethodDecl* decl);
};

#endif //OCLINT_METRIC_CLASSPUBLICACCESSORCOUNT_H
