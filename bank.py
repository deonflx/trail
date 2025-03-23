class Bank:
    def __init__(self, name, balance=0):
        self.name = name
        self.balance = balance
    
    def deposit(self, amount):
        if amount > 0:
            self.balance += amount
            print(f"Deposited ${amount}. Balance: ${self.balance}")
        else:
            print("Invalid amount")
    
    def withdraw(self, amount):
        if 0 < amount <= self.balance:
            self.balance -= amount
            print(f"Withdrawn ${amount}. Balance: ${self.balance}")
        else:
            print("Invalid amount or insufficient funds")

# Usage
account = Bank(input("Enter name: "))
while True:
    choice = input("\n1:Deposit 2:Withdraw 3:Balance 4:Exit\nChoice: ")
    if choice == '1':
        account.deposit(float(input("Amount: $")))
    elif choice == '2':
        account.withdraw(float(input("Amount: $")))
    elif choice == '3':
        print(f"Balance: ${account.balance}")
    elif choice == '4':
        break