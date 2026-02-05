import torch
import sys

model_path = sys.argv[1]
output_path = sys.argv[2]

model = torch.load(model_path, weights_only=False)
dummy = torch.randn(1,3,224,224)

torch.onnx.export(model, dummy, output_path)
print("Exported to:", output_path)

