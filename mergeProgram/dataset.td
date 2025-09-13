// class with a template parameter
class DataSet<list<int> vals> {
  list<int> values = vals;   // assign template parameter to field
}

// now we can use <> instead of {}
def DataSet1 : DataSet<[1, 3, 5, 7, 9]>;
def DataSet2 : DataSet<[2, 4, 6, 8, 10]>;

// DataType with a string parameter
class DataType<string t> {
  string Value = t;
}

def DataType : DataType<"Array">;

