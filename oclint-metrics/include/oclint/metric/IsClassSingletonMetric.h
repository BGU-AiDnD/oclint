#ifndef OCLINT_METRIC_ISCLASSSINGLETONMETRIC_H
#define OCLINT_METRIC_ISCLASSSINGLETONMETRIC_H

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include "oclint/util/FoundStatus.h"

namespace oclint
{
    class IsClassSingletonMetric : public clang::RecursiveASTVisitor<IsClassSingletonMetric>
    {
    private:
        clang::CXXRecordDecl *classDecl;

        // A statis method which are of the type of the same class
        FoundStatus matchingInstanceGetterStatus;
        // A static field to hold a pointer to the instance
        FoundStatus staticInstanceFieldStatus;
        FoundStatus constructorStatus;

        bool isMatch();
        bool isValid();
        void reset();

    public:
        bool calculate(clang::CXXRecordDecl *decl);

        bool VisitCXXMethodDecl(clang::CXXMethodDecl* decl);
        bool VisitCXXConstructorDecl(clang::CXXConstructorDecl* decl);
        bool VisitVarDecl(clang::VarDecl* decl);
    };
};

#endif //OCLINT_METRIC_ISCLASSSINGLETONMETRIC_H
