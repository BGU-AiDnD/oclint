#ifndef OCLINT_METRICS_FIELDDECLFINDERVISITOR_H
#define OCLINT_METRICS_FIELDDECLFINDERVISITOR_H

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <unordered_set>
#include "FieldDeclVisitorBase.h"

class FieldDeclFinderVisitor : public FieldDeclVisitorBase<FieldDeclFinderVisitor>
{
public:
    explicit FieldDeclFinderVisitor(clang::FunctionDecl *functionDecl);
    FieldDeclFinderVisitor(
        clang::FunctionDecl *functionDecl,
        std::shared_ptr<std::unordered_set<clang::FieldDecl*>> fieldDecls
    );

    bool insertAll();
    inline std::shared_ptr<std::unordered_set<clang::FieldDecl*>> findAll()
    {
        return insertAll() ? fieldDecls : nullptr;
    }
};

#endif //OCLINT_METRICS_FIELDDECLFINDERVISITOR_H
