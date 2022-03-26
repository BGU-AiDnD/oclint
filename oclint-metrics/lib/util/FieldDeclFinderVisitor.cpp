#include "oclint/util/FieldDeclFinderVisitor.h"
#include "oclint/util/ASTUtil2.h"

FieldDeclFinderVisitor::FieldDeclFinderVisitor(clang::FunctionDecl *functionDecl) :
    functionDecl{functionDecl},
    recordDecl{clang::dyn_cast<clang::RecordDecl>(functionDecl->getDeclContext())}
{
    fieldDecls = std::make_shared<std::vector<clang::FieldDecl*>>();
}

std::shared_ptr<std::vector<clang::FieldDecl*>> FieldDeclFinderVisitor::findAll()
{
    if (recordDecl == nullptr)
    {
        return nullptr;
    }

    TraverseDecl(functionDecl);
    return fieldDecls;
}

bool FieldDeclFinderVisitor::VisitMemberExpr(clang::MemberExpr *memberExpr)
{
    clang::FieldDecl *fieldDecl = extractFieldDeclFromMemberExpr(memberExpr, recordDecl);
    if (fieldDecl != nullptr)
    {
        fieldDecls->push_back(fieldDecl);
    }

    return true;
}