#ifndef OCLINT_METRIC_CLASSPUBLICFIELDCOUNTMETRIC_H
#define OCLINT_METRIC_CLASSPUBLICFIELDCOUNTMETRIC_H

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>

namespace oclint
{
class ClassPublicFieldCountMetric : public clang::RecursiveASTVisitor<ClassPublicFieldCountMetric>
{
private:
    int counter;

public:
    int count(clang::RecordDecl*);

    bool VisitFieldDecl(clang::FieldDecl* decl);
};
}

#endif //OCLINT_METRIC_CLASSPUBLICFIELDCOUNTMETRIC_H
