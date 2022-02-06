#include "oclint/util/ASTUtil2.h"

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