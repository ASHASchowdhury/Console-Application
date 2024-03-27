#include <iostream>
#include <iomanip>

using namespace std;

bool isLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year) {
    if (month == 2) {
        return isLeap(year) ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        return 31;
    }
}

int startingDayOfWeek(int year, int month) {
    int startDay = 1;
    int baseYear = 1970;
    int totalDays = 0;

    for (int i = baseYear; i < year; i++) {
        totalDays += isLeap(i) ? 366 : 365;
    }

    for (int i = 1; i < month; i++) {
        totalDays += daysInMonth(i, year);
    }

    startDay = (totalDays + 4) % 7;

    return startDay;
}

void displayCalendar(int year, int month, int date) {
    string months[] = {"January", "February", "March", "April", "May", "June",
                       "July", "August", "September", "October", "November", "December"};

    int days[] = {31, isLeap(year) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int startDay = startingDayOfWeek(year, month);
    int totalDays = days[month - 1];

    cout << "\n---------------------------" << endl;
    cout << "      " << months[month - 1] << " " << year << endl;
    cout << "---------------------------" << endl;
    cout << " Sun  Mon  Tue  Wed  Thu  Fri  Sat" << endl;

    int dayCount = 0;
    for (int i = 0; i < startDay; i++) {
        cout << "     ";
        dayCount++;
    }

    for (int i = 1; i <= totalDays; i++) {
        if (i == date) {
            cout << setw(5) << i << "*"; // Marks the specified date
        } else {
            cout << setw(5) << i;
        }
        dayCount++;
        if (dayCount > 6) {
            dayCount = 0;
            cout << endl;
        }
    }

    cout << endl << "---------------------------" << endl;
}

int main() {
    int yr, mon, dt;

    cout << "Enter year: ";
    cin >> yr;

    if (yr < 1970 || yr > 2100) {
        cout << "Invalid year! Please enter a year between 1970 and 2100." << endl;
        return 1;
    }

    cout << "Enter month (1-12): ";
    cin >> mon;

    if (mon < 1 || mon > 12) {
        cout << "Invalid month! Please enter a month between 1 and 12." << endl;
        return 1;
    }

    cout << "Enter date: ";
    cin >> dt;

    if (dt < 1 || dt > daysInMonth(mon, yr)) {
        cout << "Invalid date! Please enter a valid date for the specified month and year." << endl;
        return 1;
    }

    displayCalendar(yr, mon, dt);

    return 0;
}
