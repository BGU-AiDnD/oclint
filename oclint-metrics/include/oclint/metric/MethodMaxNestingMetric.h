#ifndef OCLINT_METRICS_METHODMAXNESTINGMETRIC_H
#define OCLINT_METRICS_METHODMAXNESTINGMETRIC_H

#include <clang/AST/AST.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <iterator>

namespace oclint
{
    class MethodMaxNestingMetric : public clang::RecursiveASTVisitor<MethodMaxNestingMetric>
    {
    private:
        int traverseStatement(clang::Stmt *stmt);
        int traverseBlockStatementBody(clang::Stmt *stmt);
        template<class StmtIterator>
        int traverseStatements(StmtIterator begin, StmtIterator end);

        int traverseStatementMax(
            int (MethodMaxNestingMetric::* traverseFunc)(clang::Stmt*),
            clang::Stmt *stmt,
            int currentNesting
        );
        inline int traverseStatementMax(clang::Stmt *stmt, int currentNesting)
        {
            return traverseStatementMax(
                &MethodMaxNestingMetric::traverseStatement,
                stmt, currentNesting
            );
        }
        inline int traverseBlockStatementBodyMax(clang::Stmt *stmt, int currentNesting)
        {
            return traverseStatementMax(
                &MethodMaxNestingMetric::traverseBlockStatementBody,
                stmt, currentNesting
            );
        }
    public:
        int calculate(const clang::FunctionDecl *decl);
    };

}

#endif //OCLINT_METRICS_METHODMAXNESTINGMETRIC_H
