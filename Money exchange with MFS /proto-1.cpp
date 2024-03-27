#include <bits/stdc++.h>

using namespace std;

const float BKASH_FEE_RATE = 0.0145;
const float UPAY_FEE_RATE = 0.012;
const float NAGAD_FEE_RATE = 0.016;
const float ROCKET_FEE_RATE = 0.01;

void displayCountryOptions() {
    cout << "\n\nPlease Enter your country:\n\n"
         << "1. America   2. England\n"
         << "3. Russia    4. India\n5. Dubai\n"
         << "Please type the country and enter\n\n";
}

void displayMFSOptions() {
    cout << "Thank You. Please Select Your MFS-\n\n"
         << "Bkash  Nagad  Upay  Rocket\n\n"
         << "Please enter the name of MFC name and sender's phone number\n\n";
}

float calculateMFSFee(const string& mfsName, long long amount) {
    float feeRate = 0.0;

    if (mfsName == "bkash") {
        feeRate = BKASH_FEE_RATE;
    } else if (mfsName == "upay") {
        feeRate = UPAY_FEE_RATE;
    } else if (mfsName == "nagad") {
        feeRate = NAGAD_FEE_RATE;
    } else if (mfsName == "rocket") {
        feeRate = ROCKET_FEE_RATE;
    }

    return feeRate * static_cast<float>(amount);
}

int main() {
    while (true) {
        string customerName, countryName, mfsName;
        long long amount, senderPhoneNumber, recipientPhoneNumber;
        float convertedAmount, totalAmount, bdCurrencyAmount;

        cout << "\nPlease Enter Your Name:\n";
        getline(cin, customerName);

        cout << "Hello, " << customerName << "!\n";

        while (true) {
            displayCountryOptions();

            cout << "Type the country name (e.g., America, India): ";
            getline(cin, countryName);

            transform(countryName.begin(), countryName.end(), countryName.begin(), ::tolower);

            if (countryName == "america" || countryName == "england" || countryName == "russia" || countryName == "india" || countryName == "dubai") {
                break;
            } else {
                cout << "Invalid country. Please select the country among the list.\n";
            }
        }

        cout << "Hello, " << customerName << " from " << countryName << "!\n";

        while (true) {
            cout << "\nPlease Enter the amount in " << countryName << "'s currency (max 7000):\n";
            cout << "Type the amount: ";
            cin >> amount;

            if (amount < 1 || amount > 7000) {
                cout << "Notice: Please enter an amount between 1 and 7000. Restarting from the beginning.\n";
                continue;
            }

            cout << "\nEntered amount: " << amount << " " << countryName << "'s currency\n";

            cout << "\nSir! Do you want to Send your money?\n";
            cout << "Please type 1 if you want to OR type 2 to exit\n";

            int choice;
            cout << "Type your choice: ";
            cin >> choice;

            if (choice == 2) {
                cout << "Thank You! Exiting.\n";
                return 0;
            }

            if (choice != 1) {
                cout << "Invalid choice. Restarting from the beginning.\n";
                continue;
            }

            displayMFSOptions();

            cout << "Type like 'bkash' or 'nagad': ";
            cin >> mfsName;

            transform(mfsName.begin(), mfsName.end(), mfsName.begin(), ::tolower);

            if (mfsName == "bkash" || mfsName == "nagad" || mfsName == "upay" || mfsName == "rocket") {
                if (countryName == "america") {
                    convertedAmount = static_cast<float>(amount) * 114;
                } else if (countryName == "england") {
                    convertedAmount = static_cast<float>(amount) * 140;
                } else if (countryName == "russia") {
                    convertedAmount = static_cast<float>(amount) * 1.15;
                } else if (countryName == "india") {
                    convertedAmount = static_cast<float>(amount) * 1.3;
                } else if (countryName == "dubai") {
                    convertedAmount = static_cast<float>(amount) * 60;
                }

                bdCurrencyAmount = convertedAmount * 1.27;

                float mfsFee = calculateMFSFee(mfsName, bdCurrencyAmount);
                totalAmount = bdCurrencyAmount + mfsFee;

                cout << "\nSir, for sending money in " << mfsName << ", you have to pay " << mfsFee << " TK as fees\n";
                cout << "Total amount with sending fees is: " << totalAmount << " BDT\n";
                cout << "Equivalent amount in BDT: " << bdCurrencyAmount << " BDT\n";

                cout << "\nPlease enter your mobile number:\n";
                cout << "Type your mobile number: ";
                cin >> senderPhoneNumber;

                cout << "\nPlease enter recipient's phone number:\n";
                cout << "Type recipient's phone number: ";
                cin >> recipientPhoneNumber;

                string confirmInput;
                while (true) {
                    cout << "Confirm to send money? Type 'confirm' to confirm or 'cancel' to cancel.\n";
                    cout << "Type your choice: ";
                    cin >> confirmInput;

                    if (confirmInput == "confirm") {
                        cout << "Thank you, Your money has been sent.\n";
                        cout << "Transaction details for recipient " << recipientPhoneNumber << ":\n";
                        cout << "Amount Sent: " << amount << " " << countryName << "'s currency\n";
                        cout << "Recipient's Phone Number: " << recipientPhoneNumber << endl;

                        int restartChoice;
                        cout << "\nDo you want to perform another transaction?\n";
                        cout << "Type 1 to restart or 2 to exit.\n";
                        cout << "Type your choice: ";
                        cin >> restartChoice;

                        if (restartChoice == 2) {
                            cout << "Exiting. Thank you!\n";
                            return 0;
                        } else if (restartChoice != 1) {
                            cout << "Invalid input. Exiting.\n";
                            return 0;
                        } else {
                            break;
                        }
                    } else if (confirmInput == "cancel") {
                        cout << "Transaction canceled. Restarting from the country selection.\n";
                        break;
                    } else {
                        cout << "Invalid input. Please enter 'confirm' or 'cancel'.\n";
                    }
                }
            } else {
                cout << "Invalid MFS option. Exiting.\n";
                break;
            }
        }
    }

    return 0;
}
