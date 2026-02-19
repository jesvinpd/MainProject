# -------- py/export_tf.py --------
import sys
import subprocess

model_path = sys.argv[1]   # e.g. "tf_model"
output_path = sys.argv[2]  # e.g. "tf_model.onnx"

# Call tf2onnx in its supported command-line form
cmd = [
    "python3", "-m", "tf2onnx.convert",
    "--saved-model", model_path,
    "--output", output_path
]

print("Running:", " ".join(cmd))
subprocess.check_call(cmd)

print("Exported TensorFlow model to:", output_path)
# ---------------------------------

