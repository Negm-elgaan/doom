import math as m
def Sqrt(num):
    try:
        result = m.sqrt(num)
        return result
    except ValueError:
        print("Invalid input! Please enter a positive integer or a float value")
num = int(input("Enter a number"))
print(Sqrt(num))
