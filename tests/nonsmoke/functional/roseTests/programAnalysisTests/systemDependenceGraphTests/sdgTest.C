#include <rose.h>

#include <cong_staticCFG.h>
#include <PDG.h>
#include <SDG.h>
#include <defUseChains.h>
#include <newCDG.h>
#include <newDDG.h>

using namespace StaticCFG;
using namespace SDG;

bool filterCfgNode(const VirtualCFG::CFGNode& cfgNode)
{
#if 1
    if (!cfgNode.isInteresting())
        return false;
    
    
    SgNode* astNode = cfgNode.getNode();
    
    if (SgExpression* expr = isSgExpression(astNode))
    {
        if (isSgFunctionCallExp(expr))
            return true;
        
        SgNode* parent = expr->get_parent();
        if (isSgConditionalExp(parent)
                || isSgExprListExp(parent))
            return true;

        if (isSgExpression(parent))
            return false;
    }
    
    if (isSgFunctionDefinition(astNode))
        return true;
    
    if (isSgScopeStatement(astNode))
        return false;
    
    // Keep function parameters.
    if (isSgInitializedName(astNode) 
            && isSgFunctionParameterList(astNode->get_parent()))
        return true;
    
    switch (astNode->variantT())
    {
    case V_SgExprStatement:
    case V_SgInitializedName:
    case V_SgCaseOptionStmt:
    case V_SgDefaultOptionStmt:
    case V_SgFunctionParameterList:
    case V_SgBreakStmt:
    case V_SgContinueStmt:
    case V_SgReturnStmt:
        return false;
    default:
        break;
    }
#endif
    return true;
}

bool filterCFGNodesByKeepingStmt(const VirtualCFG::CFGNode& cfgNode)
{
#if 1
    if (!cfgNode.isInteresting())
        return false;
    
    
    SgNode* astNode = cfgNode.getNode();
    
    if (SgExpression* expr = isSgExpression(astNode))
    {
        if (isSgFunctionCallExp(expr))
            return true;
        
        SgNode* parent = expr->get_parent();
        if (isSgConditionalExp(parent)
                || isSgExprListExp(parent))
            return true;

        //if (isSgExpression(parent))
        return false;
    }
    
    if (isSgFunctionDefinition(astNode))
        return true;
    
    if (isSgScopeStatement(astNode))
        return false;
    
    // Keep function parameters.
    if (isSgInitializedName(astNode) 
            && isSgFunctionParameterList(astNode->get_parent()))
        return true;
    
    switch (astNode->variantT())
    {
    case V_SgInitializedName:
    case V_SgCaseOptionStmt:
    case V_SgDefaultOptionStmt:
    case V_SgFunctionParameterList:
    case V_SgBreakStmt:
    case V_SgContinueStmt:
    case V_SgClassDeclaration:
    case V_SgEnumDeclaration:
        return false;
    default:
        break;
    }
#endif
    return true;  
}

int main(int argc, char *argv[])
{
    // Build the AST used by ROSE
    SgProject* project = frontend(argc,argv);
    SgSourceFile* sourceFile = isSgSourceFile((*project)[0]);

#if 0
    // Process all function definition bodies for static control flow graph generation
    Rose_STL_Container<SgNode*> functions = NodeQuery::querySubTree(project, V_SgFunctionDefinition);
    for (Rose_STL_Container<SgNode*>::const_iterator i = functions.begin(); i != functions.end(); ++i)
    {
        SgFunctionDefinition* proc = isSgFunctionDefinition(*i);
        ROSE_ASSERT (proc != NULL);

        if (!proc->get_file_info()->isSameFile(sourceFile))
            continue;

        //ControlFlowGraph cfg(proc, InterestingCFGNodeFilter());
        StaticCFG::ControlFlowGraph cfg(proc, filterCfgNode);
        cfg.toDot("CFG.dot");
        
        ControlDependenceGraph cdg(cfg);
        cdg.toDot("CDG.dot");
        
        DataDependenceGraph ddg(cfg);
        ddg.toDot("DDG.dot");
        
        ProgramDependenceGraph pdg(cfg);
        pdg.toDot("PDG.dot");
        
        
        break;
    }
#endif


    SDG::SystemDependenceGraph sdg(project, filterCFGNodesByKeepingStmt);
    //sdg.setDefUseChainsGenerator(generateDefUseChainsFromVariableRenaming);
    sdg.setDefUseChainsGenerator(SDG::generateDefUseChainsFromVariableRenaming);
    sdg.build();
    sdg.toDot("SDG.dot");
}

