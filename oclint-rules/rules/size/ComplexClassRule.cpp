#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleConfiguration.h"
#include "oclint/RuleSet.h"
#include "oclint/metric/CyclomaticComplexityMetric.h"

using namespace std;
using namespace clang;
using namespace oclint;

class ComplexClassRule : public AbstractASTVisitorRule<ComplexClassRule>
{
public:
    virtual const string name() const override
    {
        return "Complex Class";
    }

    virtual int priority() const override
    {
        return 2;
    }

    virtual const string category() const override
    {
        return "size";
    }

    void applyDecl(RecordDecl *decl)
    {
        if (decl->isClass() || decl->isStruct())
        {
            if ((MethodVisitor{}).visit(decl))
            {
                addViolation(decl, this, "Class '" + decl->getName().str() + "'");
            }
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

private:
    class MethodVisitor : public clang::RecursiveASTVisitor<MethodVisitor>
    {
    public:
        bool isClassComplex;

        bool visit(Decl *decl)
        {
            TraverseDecl(decl);
            return isClassComplex;
        }

        bool VisitFunctionDecl(FunctionDecl* decl)
        {
            if (decl->getKind() != Decl::CXXConstructor &&
                decl->getKind() != Decl::CXXDestructor)
            {
                int ccn = getCyclomaticComplexity(decl);
                int threshold = RuleConfiguration::intForKey("CYCLOMATIC_COMPLEXITY", 10);
                if (ccn > threshold)
                {
                    isClassComplex = true;
                    return false;
                }
            }
            return true;
        }
    };
};

static RuleSet rules(new ComplexClassRule());
