#include "oclint/util/FieldDeclFinderVisitor.h"
#include <utility>

FieldDeclFinderVisitor::FieldDeclFinderVisitor(clang::FunctionDecl *functionDecl) :
    FieldDeclVisitorBase<FieldDeclFinderVisitor>{functionDecl} {}

FieldDeclFinderVisitor::FieldDeclFinderVisitor(
    clang::FunctionDecl *functionDecl,
    std::shared_ptr<std::unordered_set<clang::FieldDecl*>> fieldDecls
) : FieldDeclVisitorBase<FieldDeclFinderVisitor>{functionDecl, std::move(fieldDecls)} {}

bool FieldDeclFinderVisitor::insertAll()
{
    if (recordDecl == nullptr)
    {
        return false;
    }

    TraverseDecl(functionDecl);
    return true;
}
