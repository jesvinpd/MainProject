import onnx                          # Import ONNX library
import onnx_graphsurgeon as gs       # Import GraphSurgeon

# 1. Load ONNX model
model = onnx.load("./resnet18.onnx")

# Convert ONNX model to GraphSurgeon graph
graph = gs.import_onnx(model)

# 2. Store node names before editing
nodes_before = {node.name for node in graph.nodes if node.name}

# 3. Collect model input tensor names

global_input_names = {tensor.name for tensor in graph.inputs}

# 4. Collect model output tensor names

global_output_names = {tensor.name for tensor in graph.outputs}


# 5. Traverse nodes

for node in graph.nodes:

    # Check for node to remove
    if node.name == "/layer1/layer1.0/Add":

        # Check if node touches model input
        is_input_layer = any(t.name in global_input_names for t in node.inputs)

        # Check if node touches model output
        is_output_layer = any(t.name in global_output_names for t in node.outputs)

        # Skip unsafe deletion
        if is_input_layer or is_output_layer:
            print(f"⚠️ Skipping '{node.name}' (I/O node)")
            continue

        print(f"✅ Bypassing hidden node: {node.name}")

        # Tensor entering the node
        input_tensor = node.inputs[0]

        # Tensor leaving the node
        output_tensor = node.outputs[0]

        # Redirect all consumers
        for consumer in list(output_tensor.outputs):

            # Replace only matching tensor slot
            for i in range(len(consumer.inputs)):
                if consumer.inputs[i] == output_tensor:
                    consumer.inputs[i] = input_tensor

        # Disconnect node AFTER reconnection
        node.inputs.clear()
        node.outputs.clear()

        break

# 6. Remove dangling nodes
graph.cleanup().toposort()

# 7. Check removed nodes
nodes_after = {node.name for node in graph.nodes if node.name}
removed_nodes = nodes_before - nodes_after

print("\n--- Cleanup Report ---")
print("Removed:", removed_nodes)

# 8. Save modified model
onnx.save(gs.export_onnx(graph), "modified_model.onnx")
