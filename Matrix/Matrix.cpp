Class Matrix
{
  double* Data; 
  int Rows;
  int Columns;
  public:
    Matrix(int rows , int cols)
    {
      Rows = rows;
      Columns = cols
      Data = new double [Rows * Columns]
   }
};