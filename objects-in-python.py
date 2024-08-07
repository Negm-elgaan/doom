class car(object):
    color = "white"
    seats = 0
    def __init__(self,speed,mileage,seats):
        self.speed = speed
        self.mileage = mileage
        self.seats = seats
    def getspeed(self):
        print(self.speed)
    def getmileage(self):
        print(self.mileage)
    def setseats(self,seats):
        self.seats = seats
    def getcolor(self):
        print(self.color)
    def getseats(self):
        print(self.color)
    def getall(self):
        print(self.color)
        print(self.speed)
        print(self.mileage)
        print(self.seats)
##############
car1 = car(200,20,5)
car2 = car(180,25,4)
car1.getall()
car2.getall()
