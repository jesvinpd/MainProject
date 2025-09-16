// RegressionBackend.cpp
#include "llvm/TableGen/Main.h"
#include "llvm/TableGen/Record.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Casting.h"

#include <string>
using namespace llvm;

// Emit common headers once
static void EmitHeaders(raw_ostream &OS)
{
  OS << "#include <iostream>\n";
  OS << "#include <vector>\n";
  OS << "#include <cmath>\n";
  OS << "#include <fstream>\n"; // for CSV output
  OS << "#include <cstdlib>\n\n";
}

// Emit a linear regression implementation (gradient descent)
static void EmitLinearRegression(raw_ostream &OS)
{
  OS << "void runLinearRegression(const std::vector<std::pair<double,double>>& data) {\n";
  OS << "  double m = 0.0; // slope\n";
  OS << "  double b = 0.0; // intercept\n";
  OS << "  const double lr = 0.001; // learning rate\n";
  OS << "  const int epochs = 2000;\n";
  OS << "  std::ofstream log(\"linear_log.csv\");\n";
  OS << "  log << \"epoch,m,b\\n\";\n";
  OS << "  for (int epoch = 0; epoch < epochs; ++epoch) {\n";
  OS << "    double dm = 0.0, db = 0.0;\n";
  OS << "    for (auto &p : data) {\n";
  OS << "      double x = p.first, y = p.second;\n";
  OS << "      double pred = m * x + b;\n";
  OS << "      double err = pred - y;\n";
  OS << "      dm += 2.0 * err * x;\n";
  OS << "      db += 2.0 * err;\n";
  OS << "    }\n";
  OS << "    m -= lr * dm / data.size();\n";
  OS << "    b -= lr * db / data.size();\n";
  OS << "    if (epoch % 100 == 0) {\n";
  OS << "      std::cout << \"Epoch \" << epoch << \": m=\" << m << \", b=\" << b << \"\\n\";\n";
  OS << "    }\n";
  OS << "    log << epoch << \",\" << m << \",\" << b << \"\\n\";\n";
  OS << "  }\n";
  OS << "  log.close();\n";
  OS << "  std::cout << \"Final Linear fit: y = \" << m << \" x + \" << b << \"\\n\";\n";
  OS << "}\n\n";
}

// Emit a non-linear / ellipse-like fit
static void EmitNonLinearRegression(raw_ostream &OS)
{
  OS << "void runNonLinearRegression(const std::vector<std::pair<double,double>>& data) {\n";
  OS << "  double a = 1.0, b = 1.0;\n";
  OS << "  const double lr = 0.0005;\n";
  OS << "  const int epochs = 3000;\n";
  OS << "  std::ofstream log(\"nonlinear_log.csv\");\n";
  OS << "  log << \"epoch,a,b\\n\";\n";
  OS << "  for (int epoch = 0; epoch < epochs; ++epoch) {\n";
  OS << "    double da = 0.0, db = 0.0;\n";
  OS << "    for (auto &p : data) {\n";
  OS << "      double x = p.first, y = p.second;\n";
  OS << "      double A = a*a, B = b*b;\n";
  OS << "      double val = (x*x)/A + (y*y)/B - 1.0;\n";
  OS << "      double dval_da = -2.0 * (x*x) / (A * a);\n";
  OS << "      double dval_db = -2.0 * (y*y) / (B * b);\n";
  OS << "      da += 2.0 * val * dval_da;\n";
  OS << "      db += 2.0 * val * dval_db;\n";
  OS << "    }\n";
  OS << "    a -= lr * da / data.size();\n";
  OS << "    b -= lr * db / data.size();\n";
  OS << "    if (a <= 1e-6) a = 1e-6;\n";
  OS << "    if (b <= 1e-6) b = 1e-6;\n";
  OS << "    if (epoch % 200 == 0) {\n";
  OS << "      std::cout << \"Epoch \" << epoch << \": a=\" << a << \", b=\" << b << \"\\n\";\n";
  OS << "    }\n";
  OS << "    log << epoch << \",\" << a << \",\" << b << \"\\n\";\n";
  OS << "  }\n";
  OS << "  log.close();\n";
  OS << "  std::cout << \"Final ellipse approx: (x^2)/\" << a*a << \" + (y^2)/\" << b*b << \" = 1\\n\";\n";
  OS << "}\n\n";
}

// Emit the main function for each def
static void EmitMainForDef(raw_ostream &OS, const Record *Def)
{
  std::string type = Def->getValueAsString("RegressionType").str();
  auto points = Def->getValueAsListInit("DataPoints");

  OS << "int main() {\n";
  OS << "  std::vector<std::pair<double,double>> data = {";
  bool first = true;
  for (auto *pv : points->getElements())
  {
    const ListInit *lst = dyn_cast<ListInit>(pv);
    if (!lst)
      continue;
    int x = dyn_cast<const IntInit>(lst->getElement(0))->getValue();
    int y = dyn_cast<const IntInit>(lst->getElement(1))->getValue();
    if (!first)
      OS << ", ";
    OS << "{" << x << ", " << y << "}";
    first = false;
  }
  OS << "};\n\n";

  if (type == "linear")
  {
    OS << "  runLinearRegression(data);\n";
  }
  else if (type == "nonlinear")
  {
    OS << "  runNonLinearRegression(data);\n";
  }
  else
  {
    OS << "  std::cerr << \"Unknown RegressionType: " << type << "\" << std::endl;\n";
  }

  OS << "  return 0;\n";
  OS << "}\n";
}

// Top-level emitter
static bool EmitAll(raw_ostream &OS, const RecordKeeper &Records)
{

  ArrayRef<const Record *> defs = Records.getAllDerivedDefinitions("RegressionProblem");
  for (const Record *def : defs)
  {
    std::string type = def->getValueAsString("RegressionType").str();

    EmitHeaders(OS);

    if (type == "linear")
    {
      EmitLinearRegression(OS); // Only linear
    }
    else if (type == "nonlinear")
    {
      EmitNonLinearRegression(OS); // Only nonlinear
    }
    else
    {
      OS << "// Unknown RegressionType: " << type << "\n";
      continue;
    }

    EmitMainForDef(OS, def); // main() for this def
    OS << "\n// ----- next generated program -----\n\n";
  }

  OS.flush();
  return false;
}

int main(int argc, char **argv)
{
  return TableGenMain(argv[0],
                      [](raw_ostream &OS, const RecordKeeper &Records) -> bool
                      {
                        return EmitAll(OS, Records);
                      });
}