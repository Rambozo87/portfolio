#include "random_forest.h"

#include <armadillo>
#include <mlpack.hpp>
#include <stdexcept>

void train_model(const std::string &train_csv_path,
                 const std::string &test_csv_path) {
  arma::mat training_data;
  arma::mat testing_data;
  if (!mlpack::data::Load(train_csv_path, training_data, true) ||
      !mlpack::data::Load(test_csv_path, testing_data, true)) {
    throw std::runtime_error("failed to read training or testing CSV");
  }

  const arma::Row<size_t> training_labels =
      arma::conv_to<arma::Row<size_t>>::from(
          training_data.row(training_data.n_rows - 1));
  training_data.shed_row(training_data.n_rows - 1);
  testing_data.shed_row(testing_data.n_rows - 1);

  const size_t classes = arma::max(training_labels) + 1;
  mlpack::tree::RandomForest<> forest;
  forest.Train(training_data, training_labels, classes, 100, 2, 1e-7, 15);

  arma::Row<size_t> predictions;
  forest.Classify(testing_data, predictions);
  std::cout << "Predictions generated: " << predictions.n_elem << '\n';
}
