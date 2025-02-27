class BankAccount:
    def __init__(self, account_number, customer_name, balance, date_of_opening):
        self.account_number = account_number
        self.customer_name = customer_name
        self.balance = balance
        self.date_of_opening = date_of_opening

    def deposit(self, amount):
        if amount > 0:
            self.balance += amount
            print(f"₹{amount} deposited successfully. New balance: ₹{self.balance}")
        else:
            print("Invalid deposit amount.")

    def withdraw(self, amount):
        if 0 < amount <= self.balance:
            self.balance -= amount
            print(f"₹{amount} withdrawn successfully. New balance: ₹{self.balance}")
        else:
            print("Insufficient balance or invalid amount.")

    def check_balance(self):
        print(f"Account Balance for {self.customer_name}: ₹{self.balance}")

# Store multiple accounts
accounts = {}

# Menu-driven approach
while True:
    print("\n----- Bank Account Menu -----")
    print("1. Create New Account")
    print("2. Deposit Money")
    print("3. Withdraw Money")
    print("4. Check Balance")
    print("5. Exit")

    choice = input("Enter your choice: ")

    if choice == "1":
        account_number = input("Enter Account Number: ")
        customer_name = input("Enter Customer Name: ")
        balance = float(input("Enter Initial Balance: "))
        date_of_opening = input("Enter Date of Opening (YYYY-MM-DD): ")
        accounts[account_number] = BankAccount(account_number, customer_name, balance, date_of_opening)
        print(f"Account created successfully for {customer_name}!")

    elif choice == "2":
        account_number = input("Enter Account Number: ")
        if account_number in accounts:
            amount = float(input("Enter deposit amount: "))
            accounts[account_number].deposit(amount)
        else:
            print("Account not found!")

    elif choice == "3":
        account_number = input("Enter Account Number: ")
        if account_number in accounts:
            amount = float(input("Enter withdrawal amount: "))
            accounts[account_number].withdraw(amount)
        else:
            print("Account not found!")

    elif choice == "4":
        account_number = input("Enter Account Number: ")
        if account_number in accounts:
            accounts[account_number].check_balance()
        else:
            print("Account not found!")

    elif choice == "5":
        print("Exiting the program. Thank you!")
        break

    else:
        print("Invalid choice. Please try again.")
