CREATE DATABASE DAS_AUTO;

USE DAS_AUTO;

CREATE TABLE Garage
(
	ID int PRIMARY KEY auto_increment ,
    Name VARCHAR(100) NOT NULL ,
    Location VARCHAR(255) NOT NULL ,
    Phone INT(15) NOT NULL ,
    Num_Of_Cars INT NOT NULL 
);

CREATE TABLE Customer
(
	ID INT PRIMARY KEY auto_increment ,
	Name VARCHAR(100) NOT NULL ,
    Address VARCHAR(255) NOT NULL ,
    Number INT NOT NULL 
);

CREATE TABLE DEPARTMENT
(
	ID INT PRIMARY KEY auto_increment ,
    Name VARCHAR(100) NOT NULL ,
    Garage_ID INT ,
    FOREIGN KEY (Garage_ID) REFERENCES Garage(ID)
);

CREATE TABLE EMPLOYEES
(
	ID INT PRIMARY KEY auto_increment ,
    Name VARCHAR(100) NOT NULL ,
	Salary DECIMAL(10,2) NOT NULL ,
    Gender ENUM('Male' , 'Female') NOT NULL ,
    Age INT NOT NULL ,
    Email VARCHAR(100) NOT NULL ,
    Hire_Date DATE NOT NULL ,
    Dep_ID INT ,
    FOREIGN KEY (Dep_ID) REFERENCES DEPARTMENT(ID)
);

CREATE TABLE Car
(
	VIN_NUM INT PRIMARY KEY AUTO_INCREMENT ,
    Model VARCHAR(255) NOT NULL ,
    Manufacturer VARCHAR(100) NOT NULL ,
    Year YEAR NOT NULL ,
    Color Varchar(100) NOT NULL ,
    Price DECIMAL(10,2) NOT NULL , 
    Garage_ID INT NOT NULL ,
	FOREIGN KEY (Garage_ID) REFERENCES Garage(ID)
);

CREATE TABLE Companies
(
	Name VARCHAR(100) NOT NULL ,
    Content VARCHAR(100) NOT NULL ,
    Location VARCHAR(255) NOT NULL ,
    Warranty DATE NOT NULL ,
    Catalog VARCHAR(255) NOT NULL 
);

CREATE TABLE OrderDetails
(
	Order_ID INT PRIMARY KEY AUTO_INCREMENT,
    Order_Date DATE NOT NULL ,
    Ship_Date DATE NOT NULL ,
    Payment_Date DATE NOT NULL ,
    Amount DECIMAL(10,2) NOT NULL ,
    Cust_ID INT NOT NULL ,
    Car_VIN_NUM INT NOT NULL ,
    FOREIGN KEY (Cust_ID) REFERENCES Customer(ID) ,
    FOREIGN KEY (Car_VIN_NUM) REFERENCES Car(VIN_NUM) 
);

INSERT INTO Customer (Name, Address, Number) VALUES 
('John Doe', '123 Elm Street', 5551234),
('Jane Smith', '456 Oak Avenue', 5555678),
('Mike Johnson', '789 Pine Road', 5559012);

INSERT INTO Garage (Name, Location, phone, Num_Of_Cars) VALUES 
('Downtown Garage', '123 Main Street', 5551111, 20),
('Uptown Garage', '456 High Street', 5552222, 15);

INSERT INTO DEPARTMENT (Name, Garage_ID) VALUES 
('Repair', 1),
('Maintenance', 2);

INSERT INTO EMPLOYEES (Name, Salary, Gender, Age, Email, Hire_date, DEP_ID) VALUES 
('Alice Brown', 55000.00, 'Female', 30, 'alice@example.com', '2021-05-15', 1),
('Bob Green', 48000.00, 'Male', 25, 'bob@example.com', '2022-07-20', 2);

INSERT INTO Companies (Name, Content, Location, Warranty, Catalog) VALUES 
('Auto Supplies Inc.', 'autosupplies@example.com', 'New York', '2024-05-15', 'auto_parts_catalog.pdf'),
('CarTech Ltd.', 'cartech@example.com', 'Los Angeles', '2025-06-15', 'cartech_catalog.pdf');

INSERT INTO Car (Model, Manufacturer, Year, Color, Price, Garage_id) VALUES 
('Accord', 'Honda', 2022, 'Blue', 30000.00, 1),
('Civic', 'Honda', 2021, 'Red', 25000.00, 2);

INSERT INTO OrderDetails (Order_Date, Ship_Date, Payment_Date, Amount, Cust_ID, Car_VIN_NUM) VALUES 
('2023-10-10', '2023-10-15', '2023-10-14', 30000.00, 1, 1),
('2023-11-05', '2023-11-10', '2023-11-09', 25000.00, 2, 1);

SELECT
	*
FROM
	Customer;

SELECT
	*
FROM
	Garage;
    
SELECT
	*
FROM
	Car;
    
SELECT
	*
FROM
	Companies;
    
SELECT
	*
FROM
	EMPLOYEES;

SELECT
	*
FROM
	DEPARTMENT;
    
SELECT
	*
FROM
	OrderDetails;
