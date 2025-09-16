#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>

void runLinearRegression(const std::vector<std::pair<double, double>> &data)
{
    double m = 0.0;          // slope
    double b = 0.0;          // intercept
    const double lr = 0.001; // learning rate
    const int epochs = 2000;
    std::ofstream log("linear_log.csv");
    log << "epoch,m,b\n";
    for (int epoch = 0; epoch < epochs; ++epoch)
    {
        double dm = 0.0, db = 0.0;
        for (auto &p : data)
        {
            double x = p.first, y = p.second;
            double pred = m * x + b;
            double err = pred - y;
            dm += 2.0 * err * x;
            db += 2.0 * err;
        }
        m -= lr * dm / data.size();
        b -= lr * db / data.size();
        if (epoch % 100 == 0)
        {
            std::cout << "Epoch " << epoch << ": m=" << m << ", b=" << b << "\n";
        }
        log << epoch << "," << m << "," << b << "\n";
    }
    log.close();
    std::cout << "Final Linear fit: y = " << m << " x + " << b << "\n";
}

int main()
{
    std::vector<std::pair<double, double>> data = {{1, 2}, {2, 3}, {3, 5}, {4, 7}};

    runLinearRegression(data);
    return 0;
}

// ----- next generated program -----