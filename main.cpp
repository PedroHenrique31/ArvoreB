#include <iostream>
#include <cstdlib>
#include "include\ArvoreB.h"

using namespace std;
//TODO: Tenho que descobrir pq o elemento esta retirando os filhos da raiz.
int main()
{
    int insercoes=60,sorteado,inseridos[insercoes];
    cout << "Hello world!" << endl;

    Pagina *raiz=new Pagina();

    ArvoreB arvore;

    for(int i=0;i<insercoes;i++){
        sorteado=rand()%100;
        cout <<"Insercao numero "<<i<<"-"<< "Valor a ser inserido: " << sorteado << "-" <<endl;
        inseridos[i]=sorteado;
        raiz->insere(sorteado);
        cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Foto Arvore ap�s inserir o "<<sorteado<<" ";
        cout<< ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
        raiz->percorre();
         cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Fim Foto Arvore "<<sorteado<<" ";
        cout<< ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    }
    raiz->percorre();
    for(int i=0;i<insercoes;i++){
        cout <<inseridos[i]<<"\n";
    }
    cout <<endl;
    return 0;
}
