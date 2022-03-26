#ifndef OCLINT_METRICS_ASTUTIL2_H
#define OCLINT_METRICS_ASTUTIL2_H

#include <clang/AST/AST.h>

// NOTE: calling this file 'ASTUtil.h' will cause rules build to fail
// because CMake will refer 'ASTUtil.h' to this file instead of what they expect.

clang::QualType getCanonicalTypeUnqualifiedNoPointer(clang::QualType type);
clang::QualType getCanonicalTypeOfTypeDecl(clang::TypeDecl *decl);
bool areOfSameUnderlyingType(clang::QualType type, clang::TypeDecl *typeDecl);

clang::RecordDecl *recordDeclOf(clang::FunctionDecl *functionDecl);

bool isNormalMethod(clang::FunctionDecl *decl);
bool isGetterMethod(clang::FunctionDecl *decl);
bool isSetterMethod(clang::FunctionDecl *decl);

#endif //OCLINT_METRICS_ASTUTILS_H
