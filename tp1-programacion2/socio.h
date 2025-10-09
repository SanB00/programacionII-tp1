#ifndef SOCIO_H
#define SOCIO_H

class Socio {
private:
    int idSocio;
    char nombre[20];
    char apellido[20];
    char telefono[15];
    bool eliminado;
public:
    void cargar();
    void mostrar() const;
    int getIdSocio() const;
    bool getEliminado() const;
    void setEliminado(bool e);

    /// Manejo de archivo
    bool guardar();
    bool leer(int pos);
    bool modificar(int pos);
};

#endif // SOCIO_H
