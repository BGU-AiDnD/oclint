#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "oclint/util/ASTUtil.h"
#include "oclint/metric/CyclomaticComplexityMetric.h"
#include "oclint/metric/MethodMaxNestingMetric.h"
#include <iostream>

using namespace std;
using namespace clang;
using namespace oclint;

// Decls:
// * NamedDecl
// * DeclStmt
// * DeclRefExpr
// * StmtExpr
// * ValueDecl
// * BindingDecl
// * DeclaratorDecl
// * FieldDecl
// * VarDecl
// * ParmVarDecl

// More Decls:
// * DeclStmt
// * DeclRefExpr
// * DependentScopeDeclRefExpr
// * DeclDecl
// * NamedDecl
// * ValueDecl
// * BindingDecl
// * VarDecl
// * ParmVarDecl
// * ConceptDecl
// * EmptyDecl
// * RequiresExprBodyDecl

// Stmts:
// * CompoundStmt
// * NullStmt
// * IndirectGotoStmt
// * DeclStmt
// * CapturedStmt
// * ValueStmt
// * StmtExpr
// * CompoundAssignOperator


class BrainMethodRule : public AbstractASTVisitorRule<BrainMethodRule>
{
public:
    virtual const string name() const override
    {
        return "Brain Method";
    }

    virtual int priority() const override
    {
        return 2;
    }

    virtual const string category() const override
    {
        return "design";
    }

    void applyDecl(RecordDecl *decl)
    {
        if (decl->isClass() || decl->isStruct())
        {
            clang::SourceManager &sourceManager = _carrier->getSourceManager();
            (MethodVisitor{sourceManager}).TraverseDecl(decl);
        }
    }

#ifdef DOCGEN
    virtual const std::string since() const override
    {
        return "21.10";
    }

    virtual const std::string description() const override
    {
        return ""; // TODO: fill in the description of the rule.
    }

    virtual const std::string example() const override
    {
        return R"rst(
.. code-block:: cpp

    void example()
    {
        // TODO: modify the example for this rule.
    }
        )rst";
    }

    /* fill in the file name only when it does not match the rule identifier
    virtual const std::string fileName() const override
    {
        return "";
    }
    */

    /* add each threshold's key, description, and its default value to the map.
    virtual const std::map<std::string, std::string> thresholds() const override
    {
        std::map<std::string, std::string> thresholdMapping;
        return thresholdMapping;
    }
    */

    /* add additional document for the rule, like references, notes, etc.
    virtual const std::string additionalDocument() const override
    {
        return "";
    }
    */

    /* uncomment this method when the rule is enabled to be suppressed.
    virtual bool enableSuppress() const override
    {
        return true;
    }
    */
#endif

    bool VisitRecordDecl(RecordDecl *decl)
    {
        applyDecl(decl);
        return true;
    }

    virtual void setUp() override {}
    virtual void tearDown() override {}

private:
    class MethodVisitor : public clang::RecursiveASTVisitor<MethodVisitor> {
    private:
        clang::SourceManager &sourceManager;

        bool isFirst;

    public:
        int maxLineCount;
        int maxCyclomaticComplexity;
        int maxMaxNesting;

        explicit MethodVisitor(clang::SourceManager &sourceManager) : sourceManager{sourceManager}, isFirst{true} {}

        bool VisitFunctionDecl(FunctionDecl* decl) {
            const int lineCount = getLineCount(decl->getSourceRange(), sourceManager);
            const int cc = getCyclomaticComplexity(decl);
            const int maxNesting = (MethodMaxNestingMetric{}).calculate(decl);
            if (isFirst) {
                maxLineCount = lineCount;
                maxCyclomaticComplexity = cc;
                maxMaxNesting = maxNesting;
            }
            else {
                maxLineCount = maxLineCount < lineCount ? lineCount : maxLineCount;
                maxCyclomaticComplexity = maxCyclomaticComplexity < cc ? cc :  maxCyclomaticComplexity;
                maxMaxNesting = maxMaxNesting < maxNesting  ? maxNesting : maxMaxNesting;
            }
            isFirst = false;
            return true;
        }
    };
};

static RuleSet rules(new BrainMethodRule());
