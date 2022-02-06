#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "oclint/metric/IsClassSingletonMetric.h"
#include "oclint/metric/ClassPublicFieldCountMetric.h"
#include "oclint/metric/ClassPublicAccessorCountMetric.h"
#include <iostream>

using namespace std;
using namespace clang;
using namespace oclint;

class SingletonFinderRule : public AbstractASTVisitorRule<SingletonFinderRule>
{
public:
    virtual const string name() const override
    {
        return "anti-singleton";
    }

    virtual int priority() const override
    {
        return 1;
    }

    virtual const string category() const override
    {
        return "smells-mine";
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

    void applyOnClass() {

    }

    bool VisitCXXRecordDecl(CXXRecordDecl *decl) {
        if (decl->isClass() || decl->isStruct()) {
            bool isSingleton = (IsClassSingletonMetric{}).calculate(decl);
            if (isSingleton)
            {
                int publicFieldsCount = (ClassPublicFieldCountMetric{}).count(decl);
                int publicAccessorCount = (ClassPublicAccessorCountMetric{}).count(decl);
                if (publicFieldsCount + publicAccessorCount > 1)
                {
                    addViolation(decl, this, "Class `" + decl->getName().str() + "` in an anti-singleton");
                }

//                std::cout << "Found singleton `" << decl->getQualifiedNameAsString() << "`";
//                std::cout << ", with " << publicFieldsCount << " public fields";
//                std::cout << ", and " << publicAccessorCount << " public accessors";
//                std::cout << "\n";
            }
        }
        return true;
    }

// region Generated visit method
    /* Visit DeclDecl
    bool VisitDeclDecl(DeclDecl *node)
    {
        return true;
    }
     */

    /* Visit TranslationUnitDecl
    bool VisitTranslationUnitDecl(TranslationUnitDecl *node)
    {
        return true;
    }
     */

    /* Visit PragmaCommentDecl
    bool VisitPragmaCommentDecl(PragmaCommentDecl *node)
    {
        return true;
    }
     */

    /* Visit PragmaDetectMismatchDecl
    bool VisitPragmaDetectMismatchDecl(PragmaDetectMismatchDecl *node)
    {
        return true;
    }
     */

    /* Visit ExternCContextDecl
    bool VisitExternCContextDecl(ExternCContextDecl *node)
    {
        return true;
    }
     */

    /* Visit NamedDecl
    bool VisitNamedDecl(NamedDecl *node)
    {
        return true;
    }
     */

    /* Visit NamespaceDecl
    bool VisitNamespaceDecl(NamespaceDecl *node)
    {
        return true;
    }
     */

    /* Visit UsingDirectiveDecl
    bool VisitUsingDirectiveDecl(UsingDirectiveDecl *node)
    {
        return true;
    }
     */

    /* Visit NamespaceAliasDecl
    bool VisitNamespaceAliasDecl(NamespaceAliasDecl *node)
    {
        return true;
    }
     */

    /* Visit LabelDecl
    bool VisitLabelDecl(LabelDecl *node)
    {
        return true;
    }
     */

    /* Visit TypeDecl
    bool VisitTypeDecl(TypeDecl *node)
    {
        return true;
    }
     */

    /* Visit TypedefNameDecl
    bool VisitTypedefNameDecl(TypedefNameDecl *node)
    {
        return true;
    }
     */

    /* Visit TypedefDecl
    bool VisitTypedefDecl(TypedefDecl *node)
    {
        return true;
    }
     */

    /* Visit TypeAliasDecl
    bool VisitTypeAliasDecl(TypeAliasDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCTypeParamDecl
    bool VisitObjCTypeParamDecl(ObjCTypeParamDecl *node)
    {
        return true;
    }
     */

    /* Visit UnresolvedUsingTypenameDecl
    bool VisitUnresolvedUsingTypenameDecl(UnresolvedUsingTypenameDecl *node)
    {
        return true;
    }
     */

    /* Visit TagDecl
    bool VisitTagDecl(TagDecl *node)
    {
        return true;
    }
     */

    /* Visit EnumDecl
    bool VisitEnumDecl(EnumDecl *node)
    {
        return true;
    }
     */

    /* Visit RecordDecl
    bool VisitRecordDecl(RecordDecl *node)
    {
        return true;
    }
     */

    /* Visit CXXRecordDecl
    bool VisitCXXRecordDecl(CXXRecordDecl *node)
    {
        return true;
    }
     */

    /* Visit ClassTemplateSpecializationDecl
    bool VisitClassTemplateSpecializationDecl(ClassTemplateSpecializationDecl *node)
    {
        return true;
    }
     */

    /* Visit TemplateTypeParmDecl
    bool VisitTemplateTypeParmDecl(TemplateTypeParmDecl *node)
    {
        return true;
    }
     */

    /* Visit ValueDecl
    bool VisitValueDecl(ValueDecl *node)
    {
        return true;
    }
     */

    /* Visit EnumConstantDecl
    bool VisitEnumConstantDecl(EnumConstantDecl *node)
    {
        return true;
    }
     */

    /* Visit UnresolvedUsingValueDecl
    bool VisitUnresolvedUsingValueDecl(UnresolvedUsingValueDecl *node)
    {
        return true;
    }
     */

    /* Visit IndirectFieldDecl
    bool VisitIndirectFieldDecl(IndirectFieldDecl *node)
    {
        return true;
    }
     */

    /* Visit BindingDecl
    bool VisitBindingDecl(BindingDecl *node)
    {
        return true;
    }
     */

    /* Visit OMPDeclareReductionDecl
    bool VisitOMPDeclareReductionDecl(OMPDeclareReductionDecl *node)
    {
        return true;
    }
     */

    /* Visit OMPDeclareMapperDecl
    bool VisitOMPDeclareMapperDecl(OMPDeclareMapperDecl *node)
    {
        return true;
    }
     */

    /* Visit MSGuidDecl
    bool VisitMSGuidDecl(MSGuidDecl *node)
    {
        return true;
    }
     */

    /* Visit DeclaratorDecl
    bool VisitDeclaratorDecl(DeclaratorDecl *node)
    {
        return true;
    }
     */

    /* Visit FieldDecl
    bool VisitFieldDecl(FieldDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCIvarDecl
    bool VisitObjCIvarDecl(ObjCIvarDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCAtDefsFieldDecl
    bool VisitObjCAtDefsFieldDecl(ObjCAtDefsFieldDecl *node)
    {
        return true;
    }
     */

    /* Visit MSPropertyDecl
    bool VisitMSPropertyDecl(MSPropertyDecl *node)
    {
        return true;
    }
     */

    /* Visit FunctionDecl
    bool VisitFunctionDecl(FunctionDecl *node)
    {
        return true;
    }
     */

    /* Visit CXXDeductionGuideDecl
    bool VisitCXXDeductionGuideDecl(CXXDeductionGuideDecl *node)
    {
        return true;
    }
     */

    /* Visit CXXMethodDecl
    bool VisitCXXMethodDecl(CXXMethodDecl *node)
    {
        return true;
    }
     */

    /* Visit CXXConstructorDecl
    bool VisitCXXConstructorDecl(CXXConstructorDecl *node)
    {
        return true;
    }
     */

    /* Visit CXXDestructorDecl
    bool VisitCXXDestructorDecl(CXXDestructorDecl *node)
    {
        return true;
    }
     */

    /* Visit CXXConversionDecl
    bool VisitCXXConversionDecl(CXXConversionDecl *node)
    {
        return true;
    }
     */

    /* Visit VarDecl
    bool VisitVarDecl(VarDecl *node)
    {
        return true;
    }
     */

    /* Visit VarTemplateSpecializationDecl
    bool VisitVarTemplateSpecializationDecl(VarTemplateSpecializationDecl *node)
    {
        return true;
    }
     */

    /* Visit ImplicitParamDecl
    bool VisitImplicitParamDecl(ImplicitParamDecl *node)
    {
        return true;
    }
     */

    /* Visit ParmVarDecl
    bool VisitParmVarDecl(ParmVarDecl *node)
    {
        return true;
    }
     */

    /* Visit DecompositionDecl
    bool VisitDecompositionDecl(DecompositionDecl *node)
    {
        return true;
    }
     */

    /* Visit OMPCapturedExprDecl
    bool VisitOMPCapturedExprDecl(OMPCapturedExprDecl *node)
    {
        return true;
    }
     */

    /* Visit NonTypeTemplateParmDecl
    bool VisitNonTypeTemplateParmDecl(NonTypeTemplateParmDecl *node)
    {
        return true;
    }
     */

    /* Visit TemplateDecl
    bool VisitTemplateDecl(TemplateDecl *node)
    {
        return true;
    }
     */

    /* Visit RedeclarableTemplateDecl
    bool VisitRedeclarableTemplateDecl(RedeclarableTemplateDecl *node)
    {
        return true;
    }
     */

    /* Visit FunctionTemplateDecl
    bool VisitFunctionTemplateDecl(FunctionTemplateDecl *node)
    {
        return true;
    }
     */

    /* Visit ClassTemplateDecl
    bool VisitClassTemplateDecl(ClassTemplateDecl *node)
    {
        return true;
    }
     */

    /* Visit VarTemplateDecl
    bool VisitVarTemplateDecl(VarTemplateDecl *node)
    {
        return true;
    }
     */

    /* Visit TypeAliasTemplateDecl
    bool VisitTypeAliasTemplateDecl(TypeAliasTemplateDecl *node)
    {
        return true;
    }
     */

    /* Visit TemplateTemplateParmDecl
    bool VisitTemplateTemplateParmDecl(TemplateTemplateParmDecl *node)
    {
        return true;
    }
     */

    /* Visit BuiltinTemplateDecl
    bool VisitBuiltinTemplateDecl(BuiltinTemplateDecl *node)
    {
        return true;
    }
     */

    /* Visit ConceptDecl
    bool VisitConceptDecl(ConceptDecl *node)
    {
        return true;
    }
     */

    /* Visit UsingDecl
    bool VisitUsingDecl(UsingDecl *node)
    {
        return true;
    }
     */

    /* Visit UsingPackDecl
    bool VisitUsingPackDecl(UsingPackDecl *node)
    {
        return true;
    }
     */

    /* Visit UsingShadowDecl
    bool VisitUsingShadowDecl(UsingShadowDecl *node)
    {
        return true;
    }
     */

    /* Visit ConstructorUsingShadowDecl
    bool VisitConstructorUsingShadowDecl(ConstructorUsingShadowDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCMethodDecl
    bool VisitObjCMethodDecl(ObjCMethodDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCContainerDecl
    bool VisitObjCContainerDecl(ObjCContainerDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCCategoryDecl
    bool VisitObjCCategoryDecl(ObjCCategoryDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCProtocolDecl
    bool VisitObjCProtocolDecl(ObjCProtocolDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCInterfaceDecl
    bool VisitObjCInterfaceDecl(ObjCInterfaceDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCCategoryImplDecl
    bool VisitObjCCategoryImplDecl(ObjCCategoryImplDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCImplementationDecl
    bool VisitObjCImplementationDecl(ObjCImplementationDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCPropertyDecl
    bool VisitObjCPropertyDecl(ObjCPropertyDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCCompatibleAliasDecl
    bool VisitObjCCompatibleAliasDecl(ObjCCompatibleAliasDecl *node)
    {
        return true;
    }
     */

    /* Visit LinkageSpecDecl
    bool VisitLinkageSpecDecl(LinkageSpecDecl *node)
    {
        return true;
    }
     */

    /* Visit ExportDecl
    bool VisitExportDecl(ExportDecl *node)
    {
        return true;
    }
     */

    /* Visit ObjCPropertyImplDecl
    bool VisitObjCPropertyImplDecl(ObjCPropertyImplDecl *node)
    {
        return true;
    }
     */

    /* Visit FileScopeAsmDecl
    bool VisitFileScopeAsmDecl(FileScopeAsmDecl *node)
    {
        return true;
    }
     */

    /* Visit AccessSpecDecl
    bool VisitAccessSpecDecl(AccessSpecDecl *node)
    {
        return true;
    }
     */

    /* Visit FriendDecl
    bool VisitFriendDecl(FriendDecl *node)
    {
        return true;
    }
     */

    /* Visit FriendTemplateDecl
    bool VisitFriendTemplateDecl(FriendTemplateDecl *node)
    {
        return true;
    }
     */

    /* Visit StaticAssertDecl
    bool VisitStaticAssertDecl(StaticAssertDecl *node)
    {
        return true;
    }
     */

    /* Visit BlockDecl
    bool VisitBlockDecl(BlockDecl *node)
    {
        return true;
    }
     */

    /* Visit CapturedDecl
    bool VisitCapturedDecl(CapturedDecl *node)
    {
        return true;
    }
     */

    /* Visit ClassScopeFunctionSpecializationDecl
    bool VisitClassScopeFunctionSpecializationDecl(ClassScopeFunctionSpecializationDecl *node)
    {
        return true;
    }
     */

    /* Visit ImportDecl
    bool VisitImportDecl(ImportDecl *node)
    {
        return true;
    }
     */

    /* Visit OMPThreadPrivateDecl
    bool VisitOMPThreadPrivateDecl(OMPThreadPrivateDecl *node)
    {
        return true;
    }
     */

    /* Visit OMPAllocateDecl
    bool VisitOMPAllocateDecl(OMPAllocateDecl *node)
    {
        return true;
    }
     */

    /* Visit OMPRequiresDecl
    bool VisitOMPRequiresDecl(OMPRequiresDecl *node)
    {
        return true;
    }
     */

    /* Visit EmptyDecl
    bool VisitEmptyDecl(EmptyDecl *node)
    {
        return true;
    }
     */

    /* Visit RequiresExprBodyDecl
    bool VisitRequiresExprBodyDecl(RequiresExprBodyDecl *node)
    {
        return true;
    }
     */

    /* Visit LifetimeExtendedTemporaryDecl
    bool VisitLifetimeExtendedTemporaryDecl(LifetimeExtendedTemporaryDecl *node)
    {
        return true;
    }
     */
// endregion
};

static RuleSet rules(new SingletonFinderRule());
