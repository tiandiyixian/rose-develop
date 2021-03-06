#include "sage3basic.h"
#include "NullPointerDereferenceLocations.h"
#include <iostream>
#include <fstream>
#include "CodeThornException.h"
#include "SgNodeHelper.h"

using namespace std;
using namespace CodeThorn;
using namespace SPRAY;

string CodeThorn::NullPointerDereferenceLocations::programLocation(Labeler* labeler, Label lab) {
  SgNode* node=labeler->getNode(lab);
  ROSE_ASSERT(node);
  return SgNodeHelper::sourceLineColumnToString(node)+","+SgNodeHelper::sourceFilenameToString(node);
}

string CodeThorn::NullPointerDereferenceLocations::sourceCodeAtProgramLocation(Labeler* labeler, Label lab) {
  SgNode* node=labeler->getNode(lab);
  ROSE_ASSERT(node);
  return SgNodeHelper::doubleQuotedEscapedString(node->unparseToString());
}

void CodeThorn::NullPointerDereferenceLocations::writeResultFile(string fileName, SPRAY::Labeler* labeler) {
  std::ofstream myfile;
  myfile.open(fileName.c_str(),std::ios::out);
  if(myfile.good()) {
    for(auto lab : definitiveDereferenceLocations) {
      myfile<<"definitive,"<<programLocation(labeler,lab);
      myfile<<","<<sourceCodeAtProgramLocation(labeler,lab);
      myfile<<endl;
    }
    for(auto lab : potentialDereferenceLocations) {
      myfile<<"potential,"<<programLocation(labeler,lab);
      myfile<<","<<sourceCodeAtProgramLocation(labeler,lab);
      myfile<<endl;
    }
    myfile.close();
  } else {
    throw CodeThorn::Exception("Error: could not open file "+fileName+".");
  }
}

void NullPointerDereferenceLocations::recordDefinitiveDereference(SPRAY::Label lab) {
  definitiveDereferenceLocations.insert(lab);
}
void NullPointerDereferenceLocations::recordPotentialDereference(SPRAY::Label lab) {
  potentialDereferenceLocations.insert(lab);

}

