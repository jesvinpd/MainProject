
class ModelSpec {
  string Framework;
  string Path;
  string Output;
}
def MyModel : ModelSpec {
  let Framework = "pytorch";
  let Path = "models/pytorch/resnet18.pt";
  let Output = "output/resnet18.onnx";
  
}

