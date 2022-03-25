#include "oclint/metric/MethodMaxNestingMetric.h"

using namespace oclint;

int MethodMaxNestingMetric::calculate(const clang::FunctionDecl *decl)
{
    return traverseBlockStatementBody(decl->getBody());
}

int MethodMaxNestingMetric::traverseStatementMax(
    int (MethodMaxNestingMetric::* traverseFunc)(clang::Stmt*),
    clang::Stmt *stmt,
    int currentNesting
)
{
    int stmtNesting = (this->*traverseFunc)(stmt);
    return currentNesting < stmtNesting ? stmtNesting : currentNesting;
}

int MethodMaxNestingMetric::traverseStatement(clang::Stmt *stmt)
{
    int nesting;
    if (auto *compoundStmt = clang::dyn_cast<clang::CompoundStmt>(stmt))
    {
        nesting = 1 + traverseStatements<clang::CompoundStmt::body_iterator>(
            compoundStmt->body_begin(), compoundStmt->body_end()
        );
    }
    else if (auto *ifStmt = clang::dyn_cast<clang::IfStmt>(stmt))
    {
        int ifMaxNesting = traverseBlockStatementBody(ifStmt->getThen());
        clang::Stmt *nextElseStmt;
        for (clang::Stmt *elseStmt = ifStmt->getElse();
             elseStmt != nullptr;
             elseStmt = nextElseStmt)
        {
            auto *elseIfStmt = clang::dyn_cast<clang::IfStmt>(elseStmt);
            if (elseIfStmt)
            {
                elseStmt = elseIfStmt->getThen();
                nextElseStmt = elseIfStmt->getElse();
            }
            else
            {
                nextElseStmt = nullptr;
            }

            ifMaxNesting = traverseBlockStatementBodyMax(
                elseStmt, ifMaxNesting
            );
        }

        nesting = 1 + ifMaxNesting;
    }
    else if (auto *whileStmt = clang::dyn_cast<clang::WhileStmt>(stmt))
    {
        nesting = 1 + traverseBlockStatementBody(whileStmt->getBody());
    }
    else if (auto *doStmt = clang::dyn_cast<clang::DoStmt>(stmt))
    {
        nesting = 1 + traverseBlockStatementBody(doStmt->getBody());
    }
    else if (auto *forStmt = clang::dyn_cast<clang::ForStmt>(stmt))
    {
        nesting = 1 + traverseBlockStatementBody(forStmt->getBody());
    }
    else if (auto *forRangeStmt = clang::dyn_cast<clang::CXXForRangeStmt>(stmt))
    {
        nesting = 1 + traverseBlockStatementBody(forRangeStmt->getBody());
    }
    else if (auto *switchStmt = clang::dyn_cast<clang::SwitchStmt>(stmt))
    {
        clang::SwitchCase *switchCase =  switchStmt->getSwitchCaseList();
        if (switchCase == nullptr)
        {
            nesting = 1;
        }
        else
        {
            for (; switchCase != nullptr; switchCase = switchCase->getNextSwitchCase())
            {
                nesting = traverseBlockStatementBodyMax(
                    switchCase->getSubStmt(), nesting
                );
            }

            // TODO: 2 or 1?
            // 2 because 1 for the switch itself and another 1 for the case.
            nesting = 2 + nesting;
        }
    }
    else if (auto *tryStmt = clang::dyn_cast<clang::CXXTryStmt>(stmt))
    {
        nesting = traverseBlockStatementBody(tryStmt->getTryBlock());
        for (unsigned int i = 0; i < tryStmt->getNumHandlers(); ++i)
        {
            clang::CXXCatchStmt *catchStmt =  tryStmt->getHandler(i);
            nesting = traverseBlockStatementBodyMax(
                catchStmt->getHandlerBlock(), nesting
            );
        }

        nesting = 1 + nesting;
    }
    else
    {
        nesting = 0;
    }

    return nesting;
}

int MethodMaxNestingMetric::traverseBlockStatementBody(clang::Stmt *stmt)
{
    int nesting = traverseStatement(stmt);
    return clang::isa<clang::CompoundStmt>(stmt) ? nesting - 1 : nesting;
}

template<class StmtIterator>
int MethodMaxNestingMetric::traverseStatements(const StmtIterator begin, const StmtIterator end)
{
    int maxNesting = 0;
    for (StmtIterator it = begin; it != end; ++it)
    {
        maxNesting = traverseStatementMax(*it, maxNesting);
    }

    return maxNesting;
}
