#include "llvm/TableGen/Main.h"
#include "llvm/TableGen/Record.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

static void emitArrayMerge(raw_ostream &OS, const Record *DS1, const Record *DS2) {
    auto vals1 = DS1->getValueAsListOfInts("values");
    auto vals2 = DS2->getValueAsListOfInts("values");

    OS << "#include <iostream>\n"
       << "#include <vector>\n"
       << "#include <algorithm>\n"
       << "using namespace std;\n\n";

    OS << "int main() {\n";
    OS << "    vector<int> a = {";
    for (size_t i = 0; i < vals1.size(); i++) {
        if (i) OS << ", ";
        OS << vals1[i];
    }
    OS << "};\n";

    OS << "    vector<int> b = {";
    for (size_t i = 0; i < vals2.size(); i++) {
        if (i) OS << ", ";
        OS << vals2[i];
    }
    OS << "};\n\n";

    OS << "    vector<int> merged;\n";
    OS << "    merged.insert(merged.end(), a.begin(), a.end());\n";
    OS << "    merged.insert(merged.end(), b.begin(), b.end());\n";
    OS << "    sort(merged.begin(), merged.end());\n";
    OS << "    for(int x : merged) cout << x << ' ';\n";
    OS << "    cout << endl;\n";
    OS << "}\n";
}

static void emitLinkedListMerge(raw_ostream &OS, const Record *DS1, const Record *DS2) {
    auto vals1 = DS1->getValueAsListOfInts("values");
    auto vals2 = DS2->getValueAsListOfInts("values");

    OS << "#include <iostream>\nusing namespace std;\n\n";
    OS << "struct Node { int data; Node* next; Node(int d): data(d), next(NULL) {} };\n\n";
    OS << "Node* push(Node* head, int val) { Node* n = new Node(val); n->next = head; return n; }\n";
    OS << "void print(Node* head) { while(head){ cout<<head->data<<\" \"; head=head->next;} cout<<endl; }\n";
    OS << "Node* merge(Node* a, Node* b) {\n";
    OS << "    if(!a) return b;\n    if(!b) return a;\n";
    OS << "    if(a->data < b->data) { a->next = merge(a->next, b); return a; }\n";
    OS << "    else { b->next = merge(a, b->next); return b; }\n}\n\n";

    OS << "int main() {\n";
    OS << "    Node* list1 = NULL;\n";
    for (int i = (int)vals1.size() - 1; i >= 0; i--)
        OS << "    list1 = push(list1, " << vals1[i] << ");\n";
    OS << "    Node* list2 = NULL;\n";
    for (int i = (int)vals2.size() - 1; i >= 0; i--)
        OS << "    list2 = push(list2, " << vals2[i] << ");\n";

    OS << "    Node* merged = merge(list1, list2);\n";
    OS << "    print(merged);\n";
    OS << "}\n";
}

static bool backendMain(raw_ostream &OS,const RecordKeeper &RK) {
    const Record *DS1 = RK.getDef("DataSet1");
    const Record *DS2 = RK.getDef("DataSet2");
    const Record *DT  = RK.getDef("DataType");

    StringRef type = DT->getValueAsString("Value");  // StringRef, not std::string

    if (type == "Array")
        emitArrayMerge(OS, DS1, DS2);
    else if(type=="LinkedList") emitLinkedListMerge(OS,DS1,DS2);
    
    else     errs() << "Error: Unknown Data type " << type << "\n";

    return false;
}

int main(int argc, char **argv) {
    return TableGenMain(argv[0], backendMain);
}

