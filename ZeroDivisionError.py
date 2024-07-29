def safe_divide(a,b):
    try:
        print(a/b)
    except ZeroDivisionError:
        print("Cannot divide by Zero")

numerator=int(input("Enter the numerator value:-"))
denominator=int(input("Enter the denominator value:-"))
print(safe_divide(numerator,denominator)) 
