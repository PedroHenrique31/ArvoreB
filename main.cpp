#include <iostream>
#include <cstdlib>
#include "include\ArvoreB.h"



using namespace std;
//TODO: Tenho que descobrir pq o elemento esta retirando os filhos da raiz.
int main()
{
    int insercoes=10,sorteado,inseridos[insercoes],buscado=240;
    cout << "Hello world!" << endl;

    Pagina *raiz=new Pagina(),*encontrada;

    ArvoreB arvore;

    for(int i=0;i<insercoes;i++){
        sorteado=rand()%100;
        std::cout <<"Insercao numero "<<i<<"-"<< "Valor a ser inserido: " << sorteado << "-" <<std::endl;
        inseridos[i]=sorteado;
        raiz->insere(sorteado);
        //cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Foto Arvore após inserir o "<<sorteado<<" ";
        //cout<< ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
        //raiz->percorre();
         //cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Fim Foto Arvore "<<sorteado<<" ";
        //cout<< ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    }
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Foto Arvore ao final ";
    cout<< ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";

    raiz->percorre();

    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Fim Foto Arvore ";
    cout<< ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    for(int i=0;i<insercoes;i++){
        cout <<inseridos[i]<<"\n";
    }
    cout <<endl;

    cout <<"Digite um dos numeros acima para buscar "<<endl;
    cin >>buscado;
    encontrada=raiz->busca(buscado);
    cout << "econtrada: "<<encontrada<<endl;

    cout <<"--------------------------------- Antes da remoção ------------------------------------"<<endl;
    raiz->visita();
    cout <<"--------------------------------- Antes da remoção ------------------------------------"<<endl;
    cout <<"remove o elemento: "<< buscado<<endl;
    raiz->removeElementoDaPaginaFolha(8);
    raiz->visita();
    return 0;
}
