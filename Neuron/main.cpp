#include <iostream>
#include <cmath>

using namespace std;

class Neuron
{
    double InputData;
    double OutputData;
    double* Weights;
    double WeightedSum;
    double Bias;
    int Size;
    int PrevSize;
    Neuron* Prev;

    void Sum()
    {
        WeightedSum = 0;
        for (int i = 0 ; i < PrevSize ; i++)
        {
            WeightedSum += Prev[i].OutputData * Weights[i];
        }
        WeightedSum += Bias;
    }

    void Sum(const double* inputData)
    {
        WeightedSum = 0;
        for (int i = 0 ; i < PrevSize ; i++)
        {
            WeightedSum += inputData[i] * Weights[i];
        }
        WeightedSum += Bias;
    }

    void Activation()
    {
        OutputData = 1 / (1 + exp(-WeightedSum));
    }


    public:

        Neuron(int Size , int prevsize , Neuron* prev , double Bias = 0)
        {
            this->Size = Size;
            this->Prev = prev;
            this->PrevSize = prevsize;
            Weights = new double [prevsize];
            for (int i = 0 ; i < PrevSize ; i++)
            {
                Weights[i] = ((double)rand()/RAND_MAX) - 0.5;
            }
            this->Bias = Bias;
        }

        void Forward(const double* inputData)
        {
            Sum(inputData);
            Activation();
        }

};

int main()
{
    Neuron *neuron = new Neuron(10,100,nullptr);
    cout << "Hello world!" << endl;
    return 0;
}
