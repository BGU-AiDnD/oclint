#include "oclint/util/ASTUtil2.h"
#include <regex>

clang::QualType getCanonicalTypeUnqualifiedNoPointer(clang::QualType type)
{
    if (type->isPointerType())
    {
        type = type->getPointeeType();
    }
    type = type->getCanonicalTypeUnqualified();
    return type;
}

clang::QualType getCanonicalTypeOfTypeDecl(clang::TypeDecl *decl)
{
    return decl->getASTContext().getTypeDeclType(decl).getCanonicalType();
}

bool areOfSameUnderlyingType(clang::QualType type, clang::TypeDecl *typeDecl)
{
    return getCanonicalTypeUnqualifiedNoPointer(type) == getCanonicalTypeOfTypeDecl(typeDecl);
}

bool isGetterName(clang::StringRef nameRef)
{
    std::string name = nameRef.str();
    std::regex nameRegex{"^[Gg]et[A-Z]"};
    auto words_begin = std::sregex_iterator(name.begin(), name.end(), nameRegex);
    auto words_end = std::sregex_iterator();
    return std::distance(words_begin, words_end) > 0;
}

bool hasGetterStructure(clang::FunctionDecl *decl)
{
    if (decl->param_size() != 0)
    {
        return false;
    }
    if (auto *compoundStmt = clang::dyn_cast<clang::CompoundStmt>(decl->getBody()))
    {
        // Now we check that the body of the function is of the form:
        // `return x;` where `x` is a field of the class this function is
        // declared in.

        // Exactly 1 statement
        if (std::distance(compoundStmt->body_begin(), compoundStmt->body_end()) != 1)
        {
            return false;
        }

        clang::Stmt *stmt = *compoundStmt->body_begin();
        clang::ReturnStmt *returnStmt;
        clang::ImplicitCastExpr *implicitCastExpr;
        clang::MemberExpr *memberExpr;
        clang::FieldDecl *fieldDecl;
        clang::RecordDecl *functionRecordDecl;
        if ((returnStmt = clang::dyn_cast<clang::ReturnStmt>(stmt)) &&
            (implicitCastExpr = clang::dyn_cast<clang::ImplicitCastExpr>(returnStmt->getRetValue())) &&
            implicitCastExpr->getCastKind() == clang::CK_LValueToRValue &&
            (memberExpr = clang::dyn_cast<clang::MemberExpr>(implicitCastExpr->getSubExpr())) &&
            (fieldDecl = clang::dyn_cast<clang::FieldDecl>(memberExpr->getMemberDecl())) &&
            (functionRecordDecl = clang::dyn_cast<clang::RecordDecl>(decl->getDeclContext())) &&
            fieldDecl->getParent()->getCanonicalDecl() == functionRecordDecl->getCanonicalDecl())
        {
            return true;
        }
    }

    return false;
}

bool isNormalMethod(clang::FunctionDecl *decl)
{
    return decl->getKind() != clang::Decl::CXXConstructor &&
           decl->getKind() != clang::Decl::CXXDestructor &&
           !decl->isStatic();
}

bool isGetterMethod(clang::FunctionDecl *decl)
{
    // TODO: When checking for the name, maybe need to check that the
    //  cyclomatic complexity is 0 or alternatively that there is only a
    //  return statement.
    return isNormalMethod(decl) &&
           (isGetterName(decl->getName()) || hasGetterStructure(decl));
}
