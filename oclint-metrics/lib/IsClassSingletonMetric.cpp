#include <iostream>
#include "oclint/metric/IsClassSingletonMetric.h"
#include "oclint/util/ASTUtil2.h"

using namespace oclint;

// TODO: handle possible nested classes

bool IsClassSingletonMetric::isMatch()
{
    return matchingInstanceGetterStatus.isMatch() &&
        staticInstanceFieldStatus.isMatch() &&
        constructorStatus.isMatch();
}

bool IsClassSingletonMetric::isValid()
{
    return matchingInstanceGetterStatus.isValid() &&
        staticInstanceFieldStatus.isValid() &&
        constructorStatus.isValid();
}

void IsClassSingletonMetric::reset()
{
    matchingInstanceGetterStatus.reset();
    staticInstanceFieldStatus.reset();
    constructorStatus.reset();
}

bool IsClassSingletonMetric::calculate(clang::CXXRecordDecl *decl)
{
    classDecl = decl;
    reset();

    bool isMatch;
    if (decl->isAbstract() || decl->isTemplated())
    {
        isMatch = false;
    }
    else
    {
        TraverseDecl(decl);
        isMatch = this->isMatch();
    }

    classDecl = nullptr;
    return isMatch;
}

bool IsClassSingletonMetric::VisitCXXConstructorDecl(clang::CXXConstructorDecl *decl)
{
    if (decl->getAccess() == clang::AS_private)
    {
        constructorStatus.foundMatch();
    }
    else
    {
        constructorStatus.matchStatus = MatchStatus::NoMatch;
    }

    return isValid();
}

bool IsClassSingletonMetric::VisitCXXMethodDecl(clang::CXXMethodDecl *decl)
{
    // public static method which returns the type of the class
    if (decl->getKind() != clang::Decl::CXXConstructor &&
        decl->getAccess() == clang::AS_public &&
        decl->isStatic() &&
        areOfSameUnderlyingType(decl->getReturnType(), classDecl))
    {
        matchingInstanceGetterStatus.foundMatch();
    }

    return isValid();
}

bool IsClassSingletonMetric::VisitVarDecl(clang::VarDecl *decl)
{
    // static field with the type of the class
    if (decl->isStaticDataMember() &&
        areOfSameUnderlyingType(decl->getType(), classDecl))
    {
        if (decl->getAccess() == clang::AS_private)
        {
            staticInstanceFieldStatus.foundMatch();
        }
        else
        {
            staticInstanceFieldStatus.matchStatus = MatchStatus::NoMatch;
        }
    }

    return isValid();
}
