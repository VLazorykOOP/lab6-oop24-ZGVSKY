#include <iostream>
using namespace std;

// ===== Ієрархія з ВІРТУАЛЬНИМ успадкуванням =====
// Базовий клас
class A {
public:
    int dataA;
    A() : dataA(1) {}
};

// перший шар
class B : virtual public A {
public:
    int dataB;
    B() : dataB(2) {}
};

class C : virtual public A {
public:
    int dataC;
    C() : dataC(3) {}
};

// другий шар
class D : virtual public B {
public:
    int dataD;
    D() : dataD(4) {}
};

// третій шар
class E : virtual public B, virtual public D {
public:
    int dataE;
    E() : dataE(5) {}
};

class F : virtual public A, virtual public C, virtual public D {
public:
    int dataF;
    F() : dataF(6) {}
};

// ===== Ієрархія БЕЗ віртуального успадкування =====
// Базовий клас
class A_nv {
public:
    int dataA_nv;
    A_nv() : dataA_nv(11) {}
};

// перший шар
class B_nv : public A_nv {
public:
    int dataB_nv;
    B_nv() : dataB_nv(12) {}
};

class C_nv : public A_nv {
public:
    int dataC_nv;
    C_nv() : dataC_nv(13) {}
};

// другий шар
class D_nv : public B_nv {
public:
    int dataD_nv;
    D_nv() : dataD_nv(14) {}
};

// третій шар
class E_nv : public B_nv, public D_nv {
public:
    int dataE_nv;
    E_nv() : dataE_nv(15) {}
};

class F_nv : public A_nv, public C_nv, public D_nv {
public:
    int dataF_nv;
    F_nv() : dataF_nv(16) {}
};

int main() {
    // Ієрархія з віртуальним успадкуванням
    cout << "=== virtual ===" << endl;
    cout << "Size of A: " << sizeof(A) << " bytes " << endl;
    cout << "Size of B: " << sizeof(B) << " bytes " << endl;
    cout << "Size of C: " << sizeof(C) << " bytes " << endl;
    cout << "Size of D: " << sizeof(D) << " bytes " << endl;
    cout << "Size of E: " << sizeof(E) << " bytes " << endl;
    cout << "Size of F: " << sizeof(F) << " bytes " << endl;

    cout << endl;

    // Ієрархія БЕЗ віртуального успадкування
    cout << "=== public  ===" << endl;
    cout << "Size of A_nv: " << sizeof(A_nv) << " bytes " << endl;
    cout << "Size of B_nv: " << sizeof(B_nv) << " bytes " << endl;
    cout << "Size of C_nv: " << sizeof(C_nv) << " bytes " << endl;
    cout << "Size of D_nv: " << sizeof(D_nv) << " bytes " << endl;
    cout << "Size of E_nv: " << sizeof(E_nv) << " bytes " << endl;
    cout << "Size of F_nv: " << sizeof(F_nv) << " bytes " << endl;

    return 0;
}
