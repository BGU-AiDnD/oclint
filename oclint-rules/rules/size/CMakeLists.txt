SET(LIST_OF_RULES
    CyclomaticComplexity
    LongClass
    LongLine
    LongMethod
    NcssMethodCount
    NestedBlockDepth
    NPathComplexity
    TooManyFields
    TooManyMethods
    TooManyParameters
    )

BUILD_DYNAMIC_RULES("${LIST_OF_RULES}")

SET(BuildComplexClassRule ComplexClass)
BUILD_DYNAMIC_RULES("${BuildComplexClassRule}")
