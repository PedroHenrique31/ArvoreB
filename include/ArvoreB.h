#include <cstdio>
#include<cstdlib>


#ifndef ARVOREB_H
#define ARVOREB_H

#define TAMANHO 8

class Pagina{
public:
    Pagina();
    Pagina(Pagina *pai);
    virtual ~Pagina();

    Pagina *pai;
    Pagina *filhos[TAMANHO];
    bool cheia;
    int numeroElementos;

    //metodos
    int getDado(int posicao);//implementada: retorna  o valor do i-ésimo dado.

    Pagina* busca(int elemento);//não terminada
    void insere(int novoDado);//implementada
    void remover(int elemento);//não terminada
    void percorre();//implementada
    void visita();//pode melhorar


private:
        int dados[TAMANHO-1];
        void desenhaLinha(int espaco);
protected:
    void split();//implementada

    void inserePonteiroFilho(Pagina *no,int posicao);
    bool ehFolha();
    void encheu();
    void paternidade();
    void reorganizaFilhos();
    void reorganiza();
    //void visita();

    void insereDado(int dado);
    int retiraDado(int posicao);//retira um dado de dentro de uma pagina e isere 0 no lugar.
    int qualFilho(Pagina *filhos);
    void absorve(Pagina *no);
    void arrumaPonteiros();
    bool sou2node();
    void separaNosCheios();



};

class ArvoreB
{
    public:
        ArvoreB();
        virtual ~ArvoreB();
        void inserir(int novoDado){raiz->insere(novoDado);}
        int buscar(int elemento);
        void remover(int elemento);

        void percorrer(){raiz->percorre();}


    protected:

    private:
        Pagina *raiz=NULL;

};



#endif // ARVOREB_H
