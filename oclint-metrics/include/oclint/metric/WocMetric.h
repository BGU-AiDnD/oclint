#ifndef OCLINT_METRICS_WOCMETRIC_H
#define OCLINT_METRICS_WOCMETRIC_H

#include <clang/AST/AST.h>
#include "ClassPublicAccessorCountMetric.h"
#include "ClassPublicMethodCountMetric.h"

namespace oclint
{
class WocMetric
{
public:
    double calculate(clang::RecordDecl *decl)
    {
        int noam = (ClassPublicAccessorCountMetric{true}).count(decl);
        int publicMethodsCount = (ClassPublicMethodCountMetric{}).count(decl);
        if (publicMethodsCount == 0)
        {
            return 0.0;
        }
        return (publicMethodsCount - noam) / ((double)publicMethodsCount);
    }
};
}

#endif //OCLINT_METRICS_WOCMETRIC_H
