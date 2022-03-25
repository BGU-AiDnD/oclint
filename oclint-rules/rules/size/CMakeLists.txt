SET(LIST_OF_RULES
    BrainMethod
    ComplexClass
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
