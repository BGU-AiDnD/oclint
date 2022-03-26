#ifndef OCLINT_METRICS_FIELDDECLFINDERVISITOR_H
#define OCLINT_METRICS_FIELDDECLFINDERVISITOR_H

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>

class FieldDeclFinderVisitor : public clang::RecursiveASTVisitor<FieldDeclFinderVisitor>
{
private:
    clang::FunctionDecl *functionDecl;
    clang::RecordDecl *recordDecl;
    std::shared_ptr<std::vector<clang::FieldDecl*>> fieldDecls;

public:
    explicit FieldDeclFinderVisitor(clang::FunctionDecl *functionDecl);

    std::shared_ptr<std::vector<clang::FieldDecl*>> findAll();

    bool VisitMemberExpr(clang::MemberExpr *memberExpr);

    ~FieldDeclFinderVisitor() = default;
    FieldDeclFinderVisitor(FieldDeclFinderVisitor const& other) = default;
    FieldDeclFinderVisitor(FieldDeclFinderVisitor && other) = default;
    FieldDeclFinderVisitor& operator=(FieldDeclFinderVisitor const& other) = default;
    FieldDeclFinderVisitor& operator=(FieldDeclFinderVisitor && other) = default;
};

#endif //OCLINT_METRICS_FIELDDECLFINDERVISITOR_H
