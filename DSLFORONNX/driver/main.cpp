#include <cstdlib>
#include <string>
#include "../gen/model.inc"

int main() {
    std::string cmd;

    if (std::string(MyModel.framework) == "pytorch") {
        cmd = "python3 py/export_pytorch.py "
              + std::string(MyModel.path) + " "
              + std::string(MyModel.output);
    }
    else if (std::string(MyModel.framework) == "tensorflow") {
        cmd = "python3 py/export_tf.py "
              + std::string(MyModel.path) + " "
              + std::string(MyModel.output);
    }

    system(cmd.c_str());
    return 0;
}

