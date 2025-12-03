class KDTree
{
  class Node
  {
    int data[3];
    int axis; /*0 for x , 1 for y , 2      for z*/
    Node* prev;
    Node* right;
    Node* left;
 };
}