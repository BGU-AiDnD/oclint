IF (NOT MINGW)
    ADD_LIBRARY(OCLintUtil2
        ASTUtil2.cpp
        FieldDeclFinderVisitor.cpp
    )
ENDIF()