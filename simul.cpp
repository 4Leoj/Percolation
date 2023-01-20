#include "simul.hpp"

typedef struct Vecinos {
	Vecinos(int i, int j)
	{
		this->i = i;
		this->j = j;
	}
	int i;
	int j;
} Vecinos;

std::tuple<int,bool> Perco_size(int i,int j, Eigen::MatrixXi M)
{
  int count = 0;
  bool Perco = false;
	
	std::queue<Vecinos> Ve;
  Ve.push(Vecinos(i, j));

	
	while (!Ve.empty()) {
		Vecinos x = Ve.front();
		Ve.pop();
		int i = x.i;
		int j = x.j;

    // Si llega al final de la matriz no extendida entonces es percolante
		if (i == M.rows()-2)
			Perco = true;

    // Verificar vecinos
    if (M(i,j-1))
    {
      M(i,j-1) = 0;
      count +=1;
      Ve.push(Vecinos(i, j-1));
    }
    if (M(i,j+1))
		{
      M(i,j+1) = 0;
      count +=1;
      Ve.push(Vecinos(i, j+1));
    }

    if (M(i-1,j))
		{
      M(i-1,j) = 0;
      count +=1;
      Ve.push(Vecinos(i - 1, j));
    }
    if (M(i+1,j))
		{
      M(i+1,j) = 0;
      count += 1;
      Ve.push(Vecinos(i + 1, j));
    }
		
	}

	return std::make_tuple(count,Perco);
}



float Big_Perco_size(int L,Eigen::MatrixXi &M)
{ // Calcula el tamaño del cluster percolante más grande
  bool Perco = false;
  bool current_Perco;
  int max_count = 0;
  int current_count = 0;
  for (int j=1; j<=L;j++)
  {
    if (M(1,j))
    {
      std::tie(current_count,current_Perco) = Perco_size(1,j,M);
      if (current_Perco)
      {
        Perco = current_Perco;  
        if (current_count >= max_count)
        {
          max_count = current_count;
        }
      }
    }
    
  }
  if (!Perco) // Si no hubo ningun percolante de ariba a abajo entonces se verifica de derecha a izquierda
  {
    max_count = 0;
    current_count = 0;
    Eigen::MatrixXi Transpose = M.transpose();
    for (int j=1; j<=L;j++)
    {
      if (Transpose(1,j))
      {
        std::tie(current_count,current_Perco) = Perco_size(1,j,Transpose);
        if (current_Perco)
        {
          Perco = current_Perco;
          if (current_count >= max_count)
          {
            max_count = current_count;
          }
        }
      }
        
    }
  }
  if (!Perco)
  {
    return 0;
  }

  //return max_count/std::pow(L,2)*1.0;
  return max_count;
}

