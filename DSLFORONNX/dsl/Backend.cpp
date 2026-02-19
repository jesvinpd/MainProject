#include "llvm/TableGen/Main.h"
#include "llvm/TableGen/Record.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

// This is your actual backend function
static bool OnnxBackend(raw_ostream &OS, const RecordKeeper &RK) {

  for (auto &Rec : RK.getAllDerivedDefinitions("ModelSpec")) {

    OS << "struct ModelSpec { "
          "const char *framework; "
          "const char *path; "
          "const char *output; "
          "int input_shape[4]; "
          "};\n\n";

    OS << "static ModelSpec MyModel = {"
       << "\"" << Rec->getValueAsString("Framework") << "\", "
       << "\"" << Rec->getValueAsString("Path") << "\", "
       << "\"" << Rec->getValueAsString("Output") << "\", "
       << "{1,3,224,224}"
       << "};\n";
  }

  return false; // false = success in this API
}

// *** IMPORTANT PART FOR YOUR LLVM VERSION ***
int main(int argc, char **argv) {
  return TableGenMain(argv[0],
    [&](raw_ostream &OS, const RecordKeeper &RK) {
      return OnnxBackend(OS, RK);
    });
}

