class ModelSpec {
  string Framework;
  string Path;
  string Output;
}

def MyModel : ModelSpec {
  let Framework = "tensorflow";
  let Path = "tf_model";      // <-- folder, not a file
  let Output = "tf_model.onnx";
}

