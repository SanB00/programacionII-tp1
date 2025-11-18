#ifndef FECHA_H
#define FECHA_H

class Fecha {
private:
    int dia, mes, anio;
public:
    void cargar();
    void mostrar() const;
    bool esUnaFechaValida() const;
};

#endif // FECHA_H

