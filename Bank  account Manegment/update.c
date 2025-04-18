
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ACCOUNTS 100
struct BankAccount {
    int accountNumber;
    char name[100];
    int nidNumber;
    float balance;
    char password[50];
};

struct BankAccount accounts[MAX_ACCOUNTS];
int totalAccounts = 0;

void clearStdin() {
    while (getchar() != '\n');
}

void createAccount() {
    int accNum, nidNum;
    float initBalance;
    char accName[100];
    char pass[50];

    printf("\n--- Create New Account ---\n");

    while (1) {
        printf("Enter account number (only number): ");
        if (scanf("%d", &accNum) != 1) {
            printf("Invalid input! Must be a number.\n");
            clearStdin();
        } else {

            int duplicate = 0;
            for (int i = 0; i < totalAccounts; i++) {
                if (accounts[i].accountNumber == accNum) {
                    printf("Account number already exists! Try again.\n");
                    duplicate = 1;
                    break;
                }
            }
            if (!duplicate) break;
        }
    }

    printf("Enter account holder name: ");
    clearStdin();
    fgets(accName, sizeof(accName), stdin);
    accName[strcspn(accName, "\n")] = '\0';
    while (1) {
        printf("Enter NID number (max 6 digits): ");
        if (scanf("%d", &nidNum) != 1 || nidNum < 0 || nidNum > 999999) {
            printf("Invalid NID! Must be number within 0-999999.\n");
            clearStdin();
        } else {
            break;
        }
    }

    while (1) {
        printf("Enter initial balance (only number): ");
        if (scanf("%f", &initBalance) != 1 || initBalance < 0) {
            printf("Invalid balance! Must be a positive number.\n");
            clearStdin();
        } else {
            break;
        }
    }

    while (1) {
        printf("Set a password (max 50 characters): ");
        clearStdin();
        fgets(pass, sizeof(pass), stdin);
        pass[strcspn(pass, "\n")] = '\0'; // Remove newline character
        if (strlen(pass) == 0) {
            printf("Password can't be empty!\n");
        } else {
            break;
        }
    }

    accounts[totalAccounts].accountNumber = accNum;
    strcpy(accounts[totalAccounts].name, accName);
    accounts[totalAccounts].nidNumber = nidNum;
    accounts[totalAccounts].balance = initBalance;
    strcpy(accounts[totalAccounts].password, pass);

    totalAccounts++;
    printf("Account created successfully!\n");
}
void checkAccount() {
    int accNo;
    char pass[50];
    int found = 0;

    printf("\n--- Check Account ---\n");
    printf("Enter account number: ");
    scanf("%d", &accNo);
    printf("Enter password: ");
    clearStdin();
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = '\0';

    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accountNumber == accNo) {
            if (strcmp(accounts[i].password, pass) == 0) {
                printf("\n--- Account Information ---\n");
                printf("Account Number : %d\n", accounts[i].accountNumber);
                printf("Name           : %s\n", accounts[i].name);
                printf("NID Number     : %d\n", accounts[i].nidNumber);
                printf("Balance        : %.2f\n", accounts[i].balance);
                found = 1;
            } else {
                printf("Incorrect password!\n");
                return;
            }
        }
    }
    if (!found) {
        printf("Account not found!\n");
    }
}

void depositMoney() {
    int accNo;
    float amount;
    char pass[50];
    int found = 0;

    printf("\nEnter account number: ");
    scanf("%d", &accNo);
    printf("Enter password: ");
    clearStdin();
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = '\0';

    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accountNumber == accNo) {
            if (strcmp(accounts[i].password, pass) == 0) {
                printf("Enter amount to deposit: ");
                if (scanf("%f", &amount) == 1 && amount > 0) {
                    accounts[i].balance += amount;
                    printf("Deposited successfully! New balance: %.2f\n", accounts[i].balance);
                } else {
                    printf("Invalid deposit amount!\n");
                }
                found = 1;
            } else {
                printf("Incorrect password!\n");
                return;
            }
        }
    }
    if (!found) {
        printf("Account not found!\n");
    }
}

void withdrawMoney() {
    int accNo;
    float amount;
    char pass[50];
    int found = 0;

    printf("\nEnter account number: ");
    scanf("%d", &accNo);
    printf("Enter password: ");
    clearStdin();
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = '\0';

    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accountNumber == accNo) {
            if (strcmp(accounts[i].password, pass) == 0) {
                printf("Enter amount to withdraw: ");
                if (scanf("%f", &amount) == 1 && amount > 0 && amount <= accounts[i].balance) {
                    accounts[i].balance -= amount;
                    printf("Withdrawn successfully! New balance: %.2f\n", accounts[i].balance);
                } else if (amount > accounts[i].balance) {
                    printf("Insufficient balance!\n");
                } else {
                    printf("Invalid withdraw amount!\n");
                }
                found = 1;
            } else {
                printf("Incorrect password!\n");
                return;
            }
        }
    }
    if (!found) {
        printf("Account not found!\n");
    }
}
void updateAccount() {
    int accNo;
    char pass[50];
    int found = 0;

    printf("\n--- Update Account Info ---\n");
    printf("Enter account number: ");
    scanf("%d", &accNo);
    printf("Enter password: ");
    clearStdin();
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = '\0';

    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accountNumber == accNo) {
            if (strcmp(accounts[i].password, pass) == 0) {
                printf("Enter new name: ");
                clearStdin();
                fgets(accounts[i].name, sizeof(accounts[i].name), stdin);
                accounts[i].name[strcspn(accounts[i].name, "\n")] = '\0';

                while (1) {
                    printf("Enter new NID number (max 6 digits): ");
                    if (scanf("%d", &accounts[i].nidNumber) != 1 || accounts[i].nidNumber < 0 || accounts[i].nidNumber > 999999) {
                        printf("Invalid NID! Try again.\n");
                        clearStdin();
                    } else {
                        break;
                    }
                }

                printf("Enter new password: ");
                clearStdin();
                fgets(accounts[i].password, sizeof(accounts[i].password), stdin);
                accounts[i].password[strcspn(accounts[i].password, "\n")] = '\0';

                printf("Account updated successfully!\n");
                found = 1;
            } else {
                printf("Incorrect password!\n");
                return;
            }
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }
}
void deleteAccount() {
    int accNo;
    char pass[50];
    int found = 0;

    printf("\n--- Delete Account ---\n");
    printf("Enter account number: ");
    scanf("%d", &accNo);
    printf("Enter password: ");
    clearStdin();
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = '\0';

    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accountNumber == accNo) {
            if (strcmp(accounts[i].password, pass) == 0) {
                // Shift all accounts after the deleted one
                for (int j = i; j < totalAccounts - 1; j++) {
                    accounts[j] = accounts[j + 1];
                }
                totalAccounts--;
                printf("Account deleted successfully!\n");
                found = 1;
                break;
            } else {
                printf("Incorrect password!\n");
                return;
            }
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n--- Bank Account Management ---\n");
        printf("1. Create Account\n");
        printf("2. Check Account / Balance\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Update Account Info\n");
        printf("6. Delete Account\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Try again.\n");
            clearStdin();
            continue;
        }

        switch (choice) {
            case 1: createAccount(); break;
            case 2: checkAccount(); break;
            case 3: depositMoney(); break;
            case 4: withdrawMoney(); break;
            case 5: updateAccount(); break;
            case 6: deleteAccount(); break;
            case 7: return 0;
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}
