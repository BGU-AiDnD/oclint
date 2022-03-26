#ifndef OCLINT_METRICS_FIELDDECLFUNCTIONVISITORBASE_H
#define OCLINT_METRICS_FIELDDECLFUNCTIONVISITORBASE_H

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <unordered_set>
#include <utility>
#include "oclint/util/ASTUtil2.h"

template <typename T>
class FieldDeclVisitorBase : protected clang::RecursiveASTVisitor<T>
{
    friend class clang::RecursiveASTVisitor<T>;

protected:
    clang::FunctionDecl *functionDecl;
    clang::RecordDecl *recordDecl;
    std::shared_ptr<std::unordered_set<clang::FieldDecl*>> fieldDecls;

    FieldDeclVisitorBase(
        clang::FunctionDecl *functionDecl,
        std::shared_ptr<std::unordered_set<clang::FieldDecl*>> fieldDecls
    ) : functionDecl{functionDecl}, recordDecl{recordDeclOf(functionDecl)},
        fieldDecls{std::move(fieldDecls)} {};

public:
    explicit FieldDeclVisitorBase(clang::FunctionDecl *functionDecl) :
        functionDecl{functionDecl}, recordDecl{recordDeclOf(functionDecl)}
    {
        fieldDecls = std::make_shared<std::unordered_set<clang::FieldDecl*>>();
    }

    bool VisitMemberExpr(clang::MemberExpr *memberExpr)
    {
        clang::FieldDecl *fieldDecl;
        if ((fieldDecl = clang::dyn_cast<clang::FieldDecl>(memberExpr->getMemberDecl())) &&
            fieldDecl->getParent()->getCanonicalDecl() == recordDecl->getCanonicalDecl())
        {
            fieldDecls->insert(fieldDecl->getCanonicalDecl());
        }

        return true;
    }

    ~FieldDeclVisitorBase() = default;
    FieldDeclVisitorBase(FieldDeclVisitorBase const& other) = default;
    FieldDeclVisitorBase(FieldDeclVisitorBase && other) noexcept = default;
    FieldDeclVisitorBase& operator=(FieldDeclVisitorBase const& other) = default;
    FieldDeclVisitorBase& operator=(FieldDeclVisitorBase && other) noexcept = default;
};

#endif //OCLINT_METRICS_FIELDDECLFUNCTIONVISITORBASE_H
