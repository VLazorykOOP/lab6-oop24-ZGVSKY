#include <iostream>
#include <string>
#include <vector>
#include <fcntl.h>
#include <io.h>

using namespace std;

// Базовий клас
class Figure {
protected:
    wstring color;
    double x, y;
public:
    Figure(const wstring& c = L"немає", double x0 = 0, double y0 = 0)
        : color(c), x(x0), y(y0) {}

    virtual void print() const {
        wcout << L"Колір: " << color << L", Центр: (" << x << L", " << y << L")" << endl;
    }

    virtual ~Figure() {}

    friend wostream& operator<<(wostream& os, const Figure& f);
    friend wistream& operator>>(wistream& is, Figure& f);
};

wostream& operator<<(wostream& os, const Figure& f) {
    os << f.color << L" " << f.x << L" " << f.y;
    return os;
}

wistream& operator>>(wistream& is, Figure& f) {
    is >> f.color >> f.x >> f.y;
    return is;
}

// Наслідувані класи

class Circle : virtual public Figure {
protected:
    double radius;
public:
    Circle(const wstring& c = L"немає", double x0 = 0, double y0 = 0, double r = 0)
        : Figure(c, x0, y0), radius(r) {}

    void print() const override {
        Figure::print();
        wcout << L"Радіус кола: " << radius << endl;
    }

    friend wostream& operator<<(wostream& os, const Circle& c);
    friend wistream& operator>>(wistream& is, Circle& c);
};

wostream& operator<<(wostream& os, const Circle& c) {
    os << static_cast<const Figure&>(c) << L" " << c.radius;
    return os;
}

wistream& operator>>(wistream& is, Circle& c) {
    is >> static_cast<Figure&>(c) >> c.radius;
    return is;
}

class Square : virtual public Figure {
protected:
    double sideLength;
public:
    Square(const wstring& c = L"немає", double x0 = 0, double y0 = 0, double side = 0)
        : Figure(c, x0, y0), sideLength(side) {}

    void print() const override {
        Figure::print();
        wcout << L"Довжина сторони квадрата: " << sideLength << endl;
    }

    friend wostream& operator<<(wostream& os, const Square& s);
    friend wistream& operator>>(wistream& is, Square& s);
};

wostream& operator<<(wostream& os, const Square& s) {
    os << static_cast<const Figure&>(s) << L" " << s.sideLength;
    return os;
}

wistream& operator>>(wistream& is, Square& s) {
    is >> static_cast<Figure&>(s) >> s.sideLength;
    return is;
}

class InscribedCircle : public Circle, public Square {
public:
    InscribedCircle(const wstring& c = L"немає", double x0 = 0, double y0 = 0, double side = 0)
        : Figure(c, x0, y0), Circle(c, x0, y0, side / 2), Square(c, x0, y0, side) {}

    void print() const override {
        wcout << L"--- Вписане коло в квадраті ---" << endl;
        Figure::print();
        wcout << L"Довжина сторони квадрата: " << sideLength << endl;
        wcout << L"Радіус вписаного кола: " << radius << endl;
    }

    friend wostream& operator<<(wostream& os, const InscribedCircle& ic);
    friend wistream& operator>>(wistream& is, InscribedCircle& ic);
};

wostream& operator<<(wostream& os, const InscribedCircle& ic) {
    os << static_cast<const Figure&>(ic) << L" " << ic.sideLength << L" " << ic.radius;
    return os;
}

wistream& operator>>(wistream& is, InscribedCircle& ic) {
    is >> static_cast<Figure&>(ic) >> ic.sideLength >> ic.radius;
    return is;
}

int main() {
    // Для української мови в консолі Windows
    #ifdef _WIN32
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    #endif

    vector<Figure*> figures;

    figures.push_back(new Figure(L"Червоний", 0, 0));
    figures.push_back(new Circle(L"Синій", 1, 2, 5));
    figures.push_back(new Square(L"Зелений", 3, 4, 10));
    figures.push_back(new InscribedCircle(L"Жовтий", 5, 5, 8));

    for (const auto& fig : figures) {
        fig->print();
        wcout << L"--------------------------" << endl;
    }

    // Перевірка операторів виведення
    wcout << L"Тест виводу через оператор <<" << endl;
    for (const auto& fig : figures) {
        if (dynamic_cast<InscribedCircle*>(fig))
            wcout << *(dynamic_cast<InscribedCircle*>(fig)) << endl;
        else if (dynamic_cast<Square*>(fig))
            wcout << *(dynamic_cast<Square*>(fig)) << endl;
        else if (dynamic_cast<Circle*>(fig))
            wcout << *(dynamic_cast<Circle*>(fig)) << endl;
        else
            wcout << *fig << endl;
    }

    // Звільнення пам'яті
    for (auto fig : figures) {
        delete fig;
    }

    return 0;
}
