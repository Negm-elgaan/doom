class BallTree
{
   int dimension;
  class Node
  {
    int* data; //can be nullptr if it is internal node
    float* center; //center can be one or two or n array of numbers all depending on the dimension
    float radius;
    Node* prev;
    Node* right;
    Node* left;
 };
}