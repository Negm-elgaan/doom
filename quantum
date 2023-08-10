namespace quantum {

    open Microsoft.Quantum.Canon;
    open Microsoft.Quantum.Intrinsic;
    open Microsoft.Quantum.Math;
    open Microsoft.Quantum.Logical;
    open Microsoft.Quantum.Measurement;
    
    @EntryPoint()
    operation GenerateQubit() : Result {
        using(x = Qubit)
        {
            H(x);
            return MResetZ(x);
        }

        
    }
}
