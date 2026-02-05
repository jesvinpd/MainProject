#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>

void runNonLinearRegression(const std::vector<std::pair<double, double>> &data)
{
    double a = 1.0, b = 1.0;
    const double lr = 0.0005;
    const int epochs = 3000;
    std::ofstream log("nonlinear_log.csv");
    log << "epoch,a,b\n";
    for (int epoch = 0; epoch < epochs; ++epoch)
    {
        double da = 0.0, db = 0.0;
        for (auto &p : data)
        {
            double x = p.first, y = p.second;
            double A = a * a, B = b * b;
            double val = (x * x) / A + (y * y) / B - 1.0;
            double dval_da = -2.0 * (x * x) / (A * a);
            double dval_db = -2.0 * (y * y) / (B * b);
            da += 2.0 * val * dval_da;
            db += 2.0 * val * dval_db;
        }
        a -= lr * da / data.size();
        b -= lr * db / data.size();
        if (a <= 1e-6)
            a = 1e-6;
        if (b <= 1e-6)
            b = 1e-6;
        if (epoch % 200 == 0)
        {
            std::cout << "Epoch " << epoch << ": a=" << a << ", b=" << b << "\n";
        }
        log << epoch << "," << a << "," << b << "\n";
    }
    log.close();
    std::cout << "Final ellipse approx: (x^2)/" << a * a << " + (y^2)/" << b * b << " = 1\n";
}

int main()
{
    std::vector<std::pair<double, double>> data = {{1, 2}, {2, 3}, {3, 5}, {4, 7}};

    runNonLinearRegression(data);
    return 0;
}

// ----- next generated program -----