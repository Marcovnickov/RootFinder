#include <iostream>
using namespace std;
#define PI 3.1415926535897932384626433832795029L

struct cmpNumber {
    double real;
    double img;

    cmpNumber(double real = 0, double img = 0) : real(real), img(img) {}

    cmpNumber sqrt(bool flg = true) {
        double A;
        double B;
        double mod = modulus();
        if (img != 0) {
            A = std::sqrt( (mod + real) / 2);
            B = (img / abs(img)) * std::sqrt( (mod - real) / 2);
        }else {
            if(real >= 0){
                A = std::sqrt(real);
                B = 0;
            } else {
                A = std::sqrt(-real);
                B = 1;
            }
        }
        if (!flg) {
            A = -A;
            B = -B;
        }
        return cmpNumber(A, B);
    }

    cmpNumber cbrt(int k = 0) {
        double A = 0, B = 0;
        if (real == 0) {
            A = 0;
            B = -std::cbrt(img);
        } else {
            if (img != 0) {
                double r = modulus();
                double theta = std::atan(img / real);
                if (real < 0) theta += PI;
                double aux = std::cbrt(r);
                A = aux * std::cos((theta + (2 * PI * k)) / 3);
                B = aux * std::sin((theta + (2 * PI * k)) / 3);
            } else {
                A = std::cbrt(real);
                B = 0;
            }
        }
        return cmpNumber(A, B);
    }

    double modulus() {
        return std::sqrt(std::pow(real, 2) + std::pow(img, 2) );
    }

    inline cmpNumber operator=(cmpNumber a) {
        real = a.real;
        img  = a.img;
        return a;
    }

    inline cmpNumber operator-(cmpNumber a) {
        return cmpNumber(real - a.real, img - a.img);
    }

    inline cmpNumber operator+(cmpNumber a) {
        return cmpNumber( a.real + real, a.img + img );
    }

    inline cmpNumber operator*(double a) {
        double auxReal = (real * a);
        double auxImg  = (img * a);
        return cmpNumber(auxReal, auxImg);
    }

    inline cmpNumber operator*(int a) {
        double auxReal = (real * double(a) );
        double auxImg = (img * double(a) );
        return cmpNumber(auxReal, auxImg);
    }

    inline cmpNumber operator*(cmpNumber a) {
        double auxReal = (real * a.real) - (img * a.img);
        double auxImg  = (real * a.img ) + (img * a.real);
        return cmpNumber(auxReal, auxImg);
    }

    inline cmpNumber operator/(cmpNumber a) {
        double auxDiv = ( pow(a.real, 2) + pow(a.img, 2) );
        double auxReal = ( (real * a.real) + (img  * a.img) ) / auxDiv;
        double auxImg  = ( (img  * a.real) - (real * a.img) ) / auxDiv;
        return cmpNumber(auxReal, auxImg);
    }

    inline bool operator==(cmpNumber a) {
        if (a.real == real && a.img == img)
            return true;
        else
            return false;
    }
};

ostream& operator<< (ostream& out, const cmpNumber& c) {
    out << c.real;
    if(c.img != 0){
        if (c.img > 0) out << "+";
        out << c.img <<  "i";
    }
    return out;
}

// Esta implementacion hace uso de la formula de Cardano 
// para resolver las raices de un polinomio de 3er grado
int main(int argc, char* argv[]) {
    // Revisamos qie se hallan enviado los 4 coeficienstes del grado del polinomio 3
    bool validParams = ( argc == 5 );
    double tstRel, tstImg;
    char* p;
    string aux; 
    std::size_t found;
    cmpNumber coef[4];
    
    // Se hace el parceo a numeros complejos
    for (int i = 1; i < argc && validParams; ++i) {
        tstRel = 0;
        tstImg = 0;
        tstRel = strtod(argv[i], &p);
        found = string(argv[i]).find(",");
        // Revisamos si se trata de un numero complejo
        if (found != std::string::npos) {
            aux = string(argv[i]).substr(found + 1);
            tstImg = strtod(aux.c_str(), &p);
        }
        coef[i - 1] = cmpNumber(tstRel, tstImg);
    }
    // Guardamos los coeficientes del polinomio de grado 3
    cmpNumber a = coef[0];
    cmpNumber b = coef[1];
    cmpNumber c = coef[2];
    cmpNumber d = coef[3];

    // Revisamos que realmemte se trate de un polinomio de grado 3
    if ( validParams && a.modulus() != 0){
        cmpNumber Q = ((a * c * 3) - (b*b)) / ( (a*a) * 9);
        cmpNumber R = ( (a * b * c * 9) - ( a * a * d * 27) - ( b * b * b * 2) ) / ( a * a * a * 54 );
        cmpNumber u = (Q * Q * Q) + (R * R);
        cmpNumber S, T;
        S = (R + (u.sqrt()) ).cbrt();
        T = (( u.sqrt() * (-1) ) + R ).cbrt();
        // Determinamos las raices
        cmpNumber x1, x2, x3;
        x1 = S + T - (b / ( a * 3 ));
        x2 = ((S + T) / 2) * (-1) - (b / (a * 3)) + (S - T) * cmpNumber(0, (std::sqrt(3) / 2));
        x3 = ((S + T) / 2) * (-1) - (b / (a * 3)) + (S - T) * cmpNumber(0, -(std::sqrt(3) / 2));
        // Imprimimos las raices
        cout << "{" << x1 << ", " << x2 << ", " << x3 << "}" << endl;
    } else {
        cout << "{ }" << endl;
    }
    return 0;
}
