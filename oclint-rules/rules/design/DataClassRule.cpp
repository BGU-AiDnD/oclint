#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "oclint/metric/ClassPublicFieldCountMetric.h"
#include "oclint/metric/ClassPublicAccessorCountMetric.h"
#include "oclint/metric/WocMetric.h"
#include "oclint/metric/WmcMetric.h"
#include "oclint/util/ThresholdsConstants.h"

using namespace std;
using namespace clang;
using namespace oclint;

class DataClassRule : public AbstractASTVisitorRule<DataClassRule>
{
public:
    virtual const string name() const override
    {
        return "Data Class";
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
            double woc = (WocMetric{}).calculate(decl);
            int nopa = (ClassPublicFieldCountMetric{}).count(decl);
            int noam = (ClassPublicAccessorCountMetric{true}).count(decl);
            int wmc = (WmcMetric{}).measure(decl);

            int nopData = nopa + noam;
            // TODO: calculate highWmc and veryHighWmc
            int highWmc = 100;
            int veryHighWmc = 150;
            bool moreFewPublicComplexityNotHigh = nopData > ThresholdsConstants::FEW && wmc < highWmc;
            bool manyPublicComplexityNotVeryHigh =  nopData > ThresholdsConstants::MANY && wmc < veryHighWmc;
            bool dataRatherThanServices = woc < ThresholdsConstants::ONE_THIRD;

            if ((moreFewPublicComplexityNotHigh || manyPublicComplexityNotVeryHigh) && dataRatherThanServices) {
                std::string message =
                    "Class '" + decl->getName().str() + "', " +
                    "WOC = " + to_string(woc) + ", " +
                    "NOPA = " + to_string(nopa) + ", " +
                    "NOAM = " + to_string(noam) + ", " +
                    "WMC = " + to_string(wmc) + ", ";
                addViolation(decl, this, message);
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

    virtual void setUp() override {}
    virtual void tearDown() override {}

    bool VisitRecordDecl(RecordDecl *decl)
    {
        applyDecl(decl);
        return true;
    }
};

static RuleSet rules(new DataClassRule());
