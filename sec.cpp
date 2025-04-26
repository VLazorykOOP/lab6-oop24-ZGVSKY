#include <iostream>
using namespace std;

// Абстрактний базовий клас
class Worker {
public:
    virtual double calculateSalary() const = 0; // Чиста віртуальна функція
    virtual ~Worker() {} // Віртуальний деструктор
};

// Похідний клас: Службовець із погодинною оплатою
class HourlyWorker : public Worker {
private:
    double hoursWorked;
    double hourlyRate;
public:
    HourlyWorker(double hours, double rate) : hoursWorked(hours), hourlyRate(rate) {}

    double calculateSalary() const override {
        return hoursWorked * hourlyRate;
    }
};

// Похідний клас: Службовець у штаті
class SalariedWorker : public Worker {
private:
    double monthlySalary;
public:
    SalariedWorker(double salary) : monthlySalary(salary) {}

    double calculateSalary() const override {
        return monthlySalary;
    }
};

// Похідний клас: Службовець із процентною ставкою
class CommissionWorker : public Worker {
private:
    double baseSalary;
    double commission;
public:
    CommissionWorker(double base, double comm) : baseSalary(base), commission(comm) {}

    double calculateSalary() const override {
        return baseSalary + commission;
    }
};

int main() {
    // Масив вказівників на абстрактний клас
    Worker* workers[3];

    // Присвоєння об'єктів похідних класів
    workers[0] = new HourlyWorker(160, 100);    // 160 годин по 100 грн
    workers[1] = new SalariedWorker(15000);      // Фіксована місячна зарплата
    workers[2] = new CommissionWorker(8000, 5000); // Базова зарплата + комісія

    // Вивід зарплати кожного працівника
    for (int i = 0; i < 3; ++i) {
        cout << "Salary of worker " << i + 1 << ": " << workers[i]->calculateSalary() << " $" << endl;
    }

    for (int i = 0; i < 3; ++i) {
        delete workers[i];
    }

    return 0;
}
