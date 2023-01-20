#include "simul.hpp"


int main(int argc, char **argv)
{
  int L = std::atoi(argv[1]);
  double p = std::atof(argv[2]);  

  std::random_device rd;
  std::mt19937 gen(rd());  
  std::bernoulli_distribution dis(p);
  
  Eigen::MatrixXi M = Eigen::MatrixXi::Zero(L+2,L+2);
  M.block(1,1,L,L) = Eigen::MatrixXi::Zero(L,L).unaryExpr([&](int){return dis(gen)? 1 : 0;});

  std::cout<<"Matrix:\n"<<M.block(1,1,L,L)<<std::endl;
  std::cout<<"Size of percolant cluster: "<<Big_Perco_size(L,M)<<std::endl;
  return 0;
}