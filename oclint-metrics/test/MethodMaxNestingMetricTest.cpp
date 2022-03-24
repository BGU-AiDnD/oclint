#include "TestHeaders.h"

#include "oclint/metric/MethodMaxNestingMetric.h"

using namespace oclint;

DeclarationMatcher functionDeclMatcher = functionDecl().bind("functionDecl");

class MaxNestingCallback : public MatchFinder::MatchCallback
{
private:
    int expected;

public:
    MaxNestingCallback(int expected) : expected{expected} {}

    virtual void run(const MatchFinder::MatchResult &results)
    {
        FunctionDecl *functionDecl = (FunctionDecl *)
            results.Nodes.getNodeAs<FunctionDecl>("functionDecl");
        if (functionDecl)
        {
            MethodMaxNestingMetric metric;
            EXPECT_EQ(expected, metric.calculate(functionDecl));
        }
        else
        {
            FAIL();
        }
    }
};

TEST(MaxNestingCallbackMetricTest, EmptyFunction)
{
    MaxNestingCallback callback(0);
    MatchFinder finder;
    finder.addMatcher(functionDeclMatcher, &callback);

    testMatcherOnCode(finder, "void m() {}");
}

TEST(MaxNestingCallbackMetricTest, ForLoopSimple)
{
MaxNestingCallback callback(1);
MatchFinder finder;
finder.addMatcher(functionDeclMatcher, &callback);

testMatcherOnCode(finder, "void m() { for(;;) {} }");
}

TEST(MaxNestingCallbackMetricTest, ForLoop1)
{
    MaxNestingCallback callback(2);
    MatchFinder finder;
    finder.addMatcher(functionDeclMatcher, &callback);

    testMatcherOnCode(finder, "void m() { for(;;) { int a = 5; if (1) {} } }");
}

TEST(MaxNestingCallbackMetricTest, IfElseEmptyBlocks)
{
    MaxNestingCallback callback(1);
    MatchFinder finder;
    finder.addMatcher(functionDeclMatcher, &callback);

    testMatcherOnCode(finder, "void m() { if (1) {} else {} }");
}

TEST(MaxNestingCallbackMetricTest, IfElseNoBlocks)
{
    MaxNestingCallback callback(1);
    MatchFinder finder;
    finder.addMatcher(functionDeclMatcher, &callback);

    testMatcherOnCode(finder, "void m() { int a; if (1) a = 5; else a = 2; }");
}

TEST(MaxNestingCallbackMetricTest, IfElseIf1)
{
    MaxNestingCallback callback(1);
    MatchFinder finder;
    finder.addMatcher(functionDeclMatcher, &callback);

    testMatcherOnCode(finder, "void m() { int a; if (1) a = 5; else if (2) a = 1; else a = 2; }");
}

TEST(MaxNestingCallbackMetricTest, IfElseIf2)
{
    MaxNestingCallback callback(2);
    MatchFinder finder;
    finder.addMatcher(functionDeclMatcher, &callback);

    testMatcherOnCode(finder, "void m() { int a; if (1) a = 5; else if (2) { for (;;) {} } }");
}

TEST(MaxNestingCallbackMetricTest, SwitchCaseSimple)
{
    MaxNestingCallback callback(2);
    MatchFinder finder;
    finder.addMatcher(functionDeclMatcher, &callback);

    testMatcherOnCode(finder, "void m() { int a = 0; switch (a) { case 2: break; default: { break; } } }");
}

TEST(MaxNestingCallbackMetricTest, SwitchCaseNoCases)
{
    MaxNestingCallback callback(1);
    MatchFinder finder;
    finder.addMatcher(functionDeclMatcher, &callback);

    testMatcherOnCode(finder, "void m() { int a = 0; switch (a) { } }");
}

TEST(MaxNestingCallbackMetricTest, SwitchCaseNoBlocks)
{
    MaxNestingCallback callback(2);
    MatchFinder finder;
    finder.addMatcher(functionDeclMatcher, &callback);

    testMatcherOnCode(finder, "void m() { int a = 0; switch (a) case 5: break; }");
}

TEST(MaxNestingCallbackMetricTest, SwitchCaseNoBlockCaseBlock)
{
    MaxNestingCallback callback(3);
    MatchFinder finder;
    finder.addMatcher(functionDeclMatcher, &callback);

    testMatcherOnCode(finder, "void m() { int a = 0; switch (a) case 5: { for (;;) {} break; } }");
}

TEST(MaxNestingCallbackMetricTest, SwitchCaseFallthrough)
{
    MaxNestingCallback callback(2);
    MatchFinder finder;
    finder.addMatcher(functionDeclMatcher, &callback);

    testMatcherOnCode(finder, "void m() { int a = 0; switch (a) case 1: case 5: { break; } }");
}

TEST(MaxNestingCallbackMetricTest, TryCatch1)
{
    MaxNestingCallback callback(2);
    MatchFinder finder;
    finder.addMatcher(functionDeclMatcher, &callback);

    testMatcherOnCXXCode(finder, "void m() { try {} catch (int e) { if (1) {} } catch (...) {} }");
}

TEST(MaxNestingCallbackMetricTest, TryCatch2)
{
    MaxNestingCallback callback(3);
    MatchFinder finder;
    finder.addMatcher(functionDeclMatcher, &callback);

    testMatcherOnCXXCode(finder, "void m() { try {} catch (int e) { if (1) {} } catch (...) { if (1) { for (;;) {} } } }");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
