#include <functional>
#include <iostream>
#include <random>
#include <vector>

#include "print.hpp"

float random_float() {
  std::random_device d;
  std::mt19937 gen(d());
  std::uniform_real_distribution<float> dis(0.0f, 1.0f);
  return dis(gen);
}

std::vector<float> random_weights(float bound, size_t count = 1) {
  std::vector<float> weights(count);
  for (size_t i = 0; i < count; ++i) {
    weights[i] = (2.0f * random_float() - 1.0f) * bound;
  }
  return weights;
}

int train_data[][2] = {{0, 0}, {1, 2}, {3, 6}, {6, 12}, {10, 20}};

float L(float w, float X[], float Y[], size_t size) {
  float error = .0f;
  for (size_t i = 0; i < size; i++) {
    error += (Y[i] - X[i] * w) * (Y[i] - X[i] * w);
  }
  return error / size;
}

float train(float X[], float Y[], size_t epochs, float oscilate_weight) {
  float w = random_weights(10.0f)[0];
  float eps = 1e-3;
  float learning_rate = 1e-3;

  std::function<float(float)> Lc = [&](float w) { return L(w, X, Y, 5); };

  float ls[epochs];
  for (size_t i = 0; i < epochs; i++) {
    float l = Lc(w);
    ls[i] = l;
    float dir = (Lc(w + eps) - l) / eps;
    w -= learning_rate * dir;
    std::cout << "l = " << l << ", w = " << w << std::endl;

    if (i % 30 == 0 && i > 40) {
      float lsum = .0f;
      for (size_t j = i - 1; j > i - 5; j--) {
        lsum += ls[j] - ls[i];
      }
      if (lsum * 1 <= oscilate_weight) {
        println("Oscilation detected at epoch: {} [edge={}]", i, lsum);
        break;
      }
    }
  }
  return w;
}

int main(int argc, char **argv) {
  size_t ts = sizeof(train_data);
  float X[ts], Y[ts];
  for (size_t i = 0; i < ts; i++) {
    X[i] = train_data[i][0];
    Y[i] = train_data[i][1];
  }

  float weight = train(X, Y, 500, 0.0000004f);
  println("Weight after training: {}", weight);

  return 0;
}
