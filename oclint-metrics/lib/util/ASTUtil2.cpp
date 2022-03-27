#include "oclint/util/ASTUtil2.h"
#include <regex>
#include <iostream>

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

bool isVoidType(clang::QualType type)
{
    return !type.hasQualifiers() &&
           type.getCanonicalType().getTypePtr()->getUnqualifiedDesugaredType()->isVoidType();
}

clang::RecordDecl *recordDeclOf(clang::FunctionDecl *functionDecl)
{
    return clang::dyn_cast<clang::RecordDecl>(functionDecl->getDeclContext());
}

bool isAccessorName(const clang::StringRef nameRef, const char firstLetter)
{
    std::stringstream regexPatternSs;
    regexPatternSs << "^[" << char(toupper(firstLetter)) << firstLetter << "]et[A-Z]";
    std::regex nameRegex{regexPatternSs.str()};
    std::string name = nameRef.str();
    auto words_begin = std::sregex_iterator(name.begin(), name.end(), nameRegex);
    auto words_end = std::sregex_iterator();
    return std::distance(words_begin, words_end) > 0;
}

bool isGetterName(const clang::StringRef nameRef)
{
    return isAccessorName(nameRef, 'g');
}

bool isSetterName(const clang::StringRef nameRef)
{
    return isAccessorName(nameRef, 's');
}

bool hasGetterStructure(clang::FunctionDecl *decl)
{
    if (decl->param_size() != 0)
    {
        return false;
    }

    auto *compoundStmt = clang::dyn_cast<clang::CompoundStmt>(decl->getBody());
    if (!compoundStmt)
    {
        return false;
    }

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
    clang::MemberExpr *memberExpr;
    clang::FieldDecl *fieldDecl;
    clang::RecordDecl *functionRecordDecl;
    if (!((returnStmt = clang::dyn_cast<clang::ReturnStmt>(stmt)) &&
          (memberExpr = clang::dyn_cast<clang::MemberExpr>(returnStmt->getRetValue()->IgnoreUnlessSpelledInSource())) &&
          (fieldDecl = clang::dyn_cast<clang::FieldDecl>(memberExpr->getMemberDecl())) &&
          (functionRecordDecl = recordDeclOf(decl)) &&
          fieldDecl->getParent()->getCanonicalDecl() == functionRecordDecl->getCanonicalDecl()))
    {
        return false;
    }

    return true;
}

bool hasSetterStructure(clang::FunctionDecl *decl)
{
    if (decl->param_size() != 1)
    {
        return false;
    }

    auto *compoundStmt = clang::dyn_cast<clang::CompoundStmt>(decl->getBody());
    if (!compoundStmt)
    {
        return false;
    }

    // Now we check that the body of the function is of the form:
    // `this->x = x;` and optionally followed by `return this;`
    // where `x` is the only parameter of the function and there is a field
    // of the class this function is declared in called `x`.

    auto *body_begin = compoundStmt->body_begin();
    auto *body_end = compoundStmt->body_end();
    auto *bodyStatementsIt = body_begin;
    long bodyStatementsCount = std::distance(body_begin, body_end);

    if (bodyStatementsCount == 0)
    {
        return false;
    }

    clang::RecordDecl *functionRecordDecl;
    clang::Stmt *firstStmt = *bodyStatementsIt;
    clang::BinaryOperator *binaryOperator;
    clang::MemberExpr *memberExpr;
    clang::FieldDecl *fieldDecl;
    clang::DeclRefExpr *declRefExpr;
    clang::VarDecl *referencedVarDecl;
    clang::ParmVarDecl *paramVarDecl = decl->getParamDecl(0);
    if (!((functionRecordDecl = recordDeclOf(decl)) &&
          (binaryOperator = clang::dyn_cast<clang::BinaryOperator>(clang::dyn_cast<clang::Expr>(firstStmt))) &&
          binaryOperator->getOpcode() == clang::BO_Assign &&
          (memberExpr = clang::dyn_cast<clang::MemberExpr>(binaryOperator->getLHS())) &&
          (fieldDecl = clang::dyn_cast<clang::FieldDecl>(memberExpr->getMemberDecl())) &&
          fieldDecl->getParent()->getCanonicalDecl() == functionRecordDecl->getCanonicalDecl() &&
          (declRefExpr = clang::dyn_cast<clang::DeclRefExpr>(binaryOperator->getRHS()->IgnoreUnlessSpelledInSource())) &&
          (referencedVarDecl = clang::dyn_cast<clang::VarDecl>(declRefExpr->getDecl())) &&
          paramVarDecl->getCanonicalDecl() == referencedVarDecl->getCanonicalDecl()))
    {
        return false;
    }

    if (isVoidType(decl->getReturnType()))
    {
        // There should be nothing besides assigning the field a value.
        if (bodyStatementsCount != 1)
        {
            return false;
        }
    }
    else
    {
        // Should return `this`.
        if (bodyStatementsCount != 2)
        {
            return false;
        }

        ++bodyStatementsIt;
        clang::Stmt *secondStmt = *bodyStatementsIt;
        clang::ReturnStmt *returnStmt;
        if (!((returnStmt = clang::dyn_cast<clang::ReturnStmt>(secondStmt)) &&
              clang::isa<clang::CXXThisExpr>(returnStmt->getRetValue()->IgnoreUnlessSpelledInSource())))
        {
            return false;
        }
    }

    return true;
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

    // TODO: Look into AST matchers

    // TODO: Support static methods as well. They have a slightly different
    //   structure. That way, we can use that in the anti singleton rule.
    // TODO: Advanced: Handle other implicit casts like integer conversions and
    //  inheritance up casting. (Maybe using a while loop ignoring every
    //  implicit cast but the last and only checking it).
    // TODO: Advanced: Handle lazy initialization in the getter method.

    // TODO: What is considered a getter structure?
    //  for example: `return x;` is, but is `return array[i];` (`i` is a parameter)?
    //  or `return x + 1;`, `return cast<TagDecl*>(this)->getSomething();`?
    return isNormalMethod(decl) &&
           (isGetterName(decl->getName()) || hasGetterStructure(decl));
}

bool isSetterMethod(clang::FunctionDecl *decl)
{
    // TODO: Same with getter, maybe check cyclomatic complexity or simple
    //  structure (along with the name).
    // TODO: Same with getter, handle other implicit casts.

    // TODO: Support static methods as well.

    // TODO: Decide on what makes a 'setter'. For example, is the following
    //   a setter: `this->x += x;`?
    return isNormalMethod(decl) &&
           (isSetterName(decl->getName()) || hasSetterStructure(decl));
}
