SET(LIST_OF_RULES
    AvoidDefaultArgumentsOnVirtualMethods
    AvoidPrivateStaticMembers
    FeatureEnvy
    DataClass
    )

BUILD_DYNAMIC_RULES("${LIST_OF_RULES}")

SET(BuildBrainMethodRule BrainMethod)
BUILD_DYNAMIC_RULES("${BuildBrainMethodRule}")
