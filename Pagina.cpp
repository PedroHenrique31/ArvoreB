#include "ArvoreB.h"
#include <iostream>

using namespace std;

/**
 *                      Arvore B
 *      Estruturade dados que permite se autobalancear,
 *  cada elemento da arvore pode ter at� B-1 elementos e B filhos
 *  quando uma das condi��es � atingida � hora do split().
 */
Pagina::Pagina()
{
    int i;
    for(i=0;i<TAMANHO;i++){
        filhos[i]=NULL;
        dados[i]=0;
    }
    this->numeroElementos=0;
    this->cheia=false;
    this->pai=NULL;

}
//Construtor se ele informar pai
Pagina::Pagina(Pagina *pai)
{
    int i;
    for(i=0;i<TAMANHO;i++){
        filhos[i]=NULL;
        dados[i]=0;
    }
    numeroElementos=0;
    cheia=false;
    this->pai=pai;

}
Pagina :: ~Pagina()
{
    //destrutor
}
/**
 *      Fun�ao encheu: avalia se este n� esta cheio pelo numero de filhos.*/
void Pagina::encheu()
{
    bool encheu=true;
    for(int i=0;i<TAMANHO;i++){
        if(this->filhos[i]==NULL){
            encheu=false;
        }
    }
    this->cheia=(numeroElementos>=TAMANHO-1);
    return;
}
/**
 *      Fun��o qualFilho: retorna em qual posi��o esta o ponteiro para uma determinada arvore.]
 * Obs: retorna -1 caso o filho n�o esteja na arvore.*/
int Pagina :: qualFilho(Pagina *filho)
{
    int i=0;//posicao
    bool encontrado=false;
    do{
        encontrado=(filho==this->filhos[i]);
        i++;
    }while(!encontrado && i<=TAMANHO);
    if(i>TAMANHO){
        return (i=-1);
    }
    return (i-1);
}
/**
 *      Fun��o retiraDado: remove da arvore um determinado dado em um indice,
 * preenchendo sua posi��o com o numero 0.
 *Obs: N�O REORGANIZA OS DEMAIS ELEMENTOS DA PAGINA.*/
int Pagina :: retiraDado(int posicao)
{
    if(posicao <=TAMANHO){
        int valorRetirado;
        valorRetirado=dados[posicao];
        dados[posicao]=0;
        this->numeroElementos--;
        this->cheia=(numeroElementos>TAMANHO-1);
        if(this->numeroElementos==1){
            int valorMover=dados[1];
            dados[0]=valorMover;
            dados[1]=0;
        }
        return valorRetirado;
    }
}

/**
 *      Fun��o getDado: visualiza um elemento especifico da pagina.*/
int Pagina :: getDado(int posicao)
{

    return dados[posicao];
}

/**
 * insereDado: insere dados ordenadamente no vetor de dados da pagina
 * insere sempre na ultima posi��o e vai voltando at� a posicao correta.
 */
void Pagina::insereDado(int novoDado)
{
    int ultimaPosicao=TAMANHO-2,temp;//ultima posicao disponivel � TAMANHO-2 pois come�a a contar de 0;

    if(!this->cheia)
    {

        if(numeroElementos>0)
        {
            dados[ultimaPosicao]=novoDado;
            while(ultimaPosicao!=0)
            {
                if(dados[ultimaPosicao-1]!=0 && dados[ultimaPosicao-1]>novoDado)
                {
                    temp=dados[ultimaPosicao-1];
                    dados[ultimaPosicao-1]=novoDado;
                    dados[ultimaPosicao]=temp;

                }else if(dados[ultimaPosicao-1]==0 && ultimaPosicao-1>0){//se o elemento anterior for 0 pode ser uma casa vazia.
                    if(dados[ultimaPosicao-2]<0 && ultimaPosicao-2>0){//significa que n�o � uma casa vazia.
                        break;
                    }else{
                        temp=dados[ultimaPosicao-1];
                        dados[ultimaPosicao-1]=novoDado;
                        dados[ultimaPosicao]=temp;
                    }
                }else if(dados[ultimaPosicao-1]<novoDado){
                    break;
                }
                ultimaPosicao--;
            }
        }else{dados[0]=novoDado;}
        this->numeroElementos++;this->cheia=(numeroElementos>=TAMANHO-1);//ordena
    }
}
/**
 *  Fun��o insere: fun��o rescursiva que realiza a inser��o de um elemento nesta pagina,
 * para isso ela avalia se pagina � possui filhos, se sim busca em qual filho inserir elemento
 * e se n�o insere nela propria ordenadamente.*/
void Pagina::insere(int novoDado){
    Pagina *pagina=this;
    int numeroElementosAntes,numeroElementosDepois;//variaveis importantes para avaliarmos se vamos absorver o n�
    cout << "inserindo "<<novoDado << " ";


    //AVALIA SE N� � UMA FOLHA (SE N�O POSSUI FILHOS).
    bool folha=this->ehFolha();
    //CASO 1:N� � UMA FOLHA, OU SEJA N�O POSSUI FILHOS.
    if(folha)
    {
        //CASO 1.1:N� � UMA FOLHA E N�O EST� CHEIO.
        cout <<"CASO 1 ";
        this->encheu();

        if(!this->cheia)
        {
            cout <<"arvore n�o cheia --> ";
            this->insereDado(novoDado);
            cout<<"inseriu novo dado-- ";
            this->cheia=(this->numeroElementos>=TAMANHO-1);//VERIFICA SE ENCHEU.
            cout <<"encheu: " << this->cheia<< "\n";
            if(this->cheia){//se encheu n� se divide a si mesmo, como � uma folha nao precisa retornar nada.
                this->visita();
                this->split();
            }

        }
    }//FIM CASO 1.
    //CASO 2: N� POSSUI FILHOS: INSERE NUMA PAGINA FILHA E DEPOIS VERIFICA SE PROMOVE ESTE FILHO PARA C�.
    else{
        //2.1:PERCORRE OS ELEMENTOS PROCURANDO ONDE INSERIR.

        int iteracoes=this->numeroElementos;
        cout <<"CASO 2 "<<novoDado <<" compara "<<this->dados[iteracoes-1]<<endl;
        for (int i=0;i<=iteracoes;i++)
        {
            cout <<"entrou no for i= "<<i<<"\n";
            if(novoDado<=this->dados[i])
            {//2.1.1: SE NOVO DADO FOR MENOR OU IGUAL AO I-ESIMO DADO INSERE ABAIXO DESTE NO.
                cout << "novoDado: "<<novoDado<< "<="<<this->dados[i]<<endl;
                if(this->filhos[i]!=NULL)
                {//caso n�-filho exista.
                    numeroElementosAntes=this->filhos[i]->numeroElementos;
                    this->filhos[i]->insere(novoDado);
                    numeroElementosDepois=this->filhos[i]->numeroElementos;
                    this->filhos[i]->visita();//remover depois
                    if(numeroElementosAntes==TAMANHO-2 && numeroElementosDepois==1){
                        this->absorve(this->filhos[i]);//analisa se pode absorver esse n� e o promove pra c�.
                    }
                    //this->filhos[i]->visita();
                    this->encheu();
                    if(this->cheia){
                        this->split();
                    }
                    break;
                }else{//caso this->filho[i]==NULL
                    cout << "novoDado: "<<novoDado<< "<="<<this->dados[i]<<", mas filho==NULL"<<endl;
                    Pagina *proximo=new Pagina(this);
                    proximo->insere(novoDado);
                    cout <<"Ap�s inserir em pagina rec�m criada.\n";
                    proximo->visita();
                    this->filhos[i]=proximo;
                    this->encheu();
                    break;
                }
            }//FIM 2.1.1.

        }//FIM 2.1

        if(novoDado>this->dados[iteracoes-1])
        {//2.1.2: se for maior que o o maior elemento.
                cout << "novoDado: "<<novoDado<< ">="<<this->dados[iteracoes-1]<< " essa linha quem chamou foi: "<<this->dados[iteracoes-1]
                <<" da pagina : "<<this <<endl;
                cout <<"filho[i+1]: "<<this->filhos[iteracoes]<<endl;
                ///ele s� comparar� com 0 se o elemento anterior for negativo, pois pode ocorrer dele voltar e esse ter sido dividido.
                if(dados[iteracoes-1]==0){
                    if(dados[iteracoes-2]>0){
                        return;
                    }
                }
                if(this->filhos[iteracoes]!=NULL)
                {
                    numeroElementosAntes=this->filhos[iteracoes]->numeroElementos;
                    this->filhos[iteracoes]->insere(novoDado);
                    numeroElementosDepois=this->filhos[iteracoes]->numeroElementos;
                    if(numeroElementosAntes==TAMANHO-2 && numeroElementosDepois==1){
                        this->absorve(this->filhos[iteracoes]);//analisa se pode absorver esse n� e o promove pra c�.
                    }

                    this->encheu();
                    if(this->cheia){this->split();}


                }else{
                    Pagina *proximo=new Pagina(this);
                    proximo->insereDado(novoDado);
                    this->filhos[iteracoes]=proximo;
                }

        }//FIM: 2.1.2.
    }//FIM CASO 2.
    this->reorganizaFilhos();
}//FIM INSERE.

/**
 *      Fun��o split: divide ESTE n� movendo o 0-�simo elemento para esquerda e os demais elementos para direita
 * tornando este um 2-n�.*/
void Pagina::split()
{
    cout <<"\nsplit"<<"("<<this<<")"<<" ";
    int meio=(TAMANHO-1)/2; cout <<"meio: "<< meio <<"\n";
    Pagina *filhoDir,*filhoEsq;
    filhoDir=new Pagina(this);
    filhoEsq=new Pagina(this);/*
    cout << "filhoDir "<<filhoDir->cheia<< " "<<filhoDir->pai<<"\n";
    cout << "filhoEsq "<<filhoEsq->cheia<< " "<<filhoEsq->pai<<"\n";
    filhoEsq->visita();
    filhoDir->visita();*/

    //insere no filho a esquerda,toda a metade inferior da posi��o [TAMANHO-1/2] e insere os filhos a direita e a esquerda.
    for(int i=0;i<meio;i++){
        filhoEsq->insereDado(this->retiraDado(i));
        filhoEsq->filhos[i]=this->filhos[i];
        this->filhos[i]=NULL;

    }
    filhoEsq->filhos[meio]=this->filhos[meio];
    cout << "Visita temporaria\n";
    filhoEsq->visita();
    this->visita();




    //move os demais elementos para pagina a direita.
    int posicao=0,Final=TAMANHO-1;
    for(int i=meio+1;i<Final;i++)
    {
        filhoDir->insereDado(this->retiraDado(i));
        filhoDir->filhos[posicao]=this->filhos[i];
        this->filhos[i]=NULL;
        posicao++;
    }
    filhoDir->filhos[meio]=this->filhos[TAMANHO-1];
    this->filhos[TAMANHO-1]=NULL;

    //este no se tornou um 2-n�, logo aqui inserimos os filhos a esquerda e a direita.
    this->filhos[0]=filhoEsq;
    this->filhos[1]=filhoDir;
    //por alguma raz�o escabrosa os elementos est�o se ordenando a partir daqui, mas os ponteiros n�o.

    //move o elemento da posicao [meio] para [0].

    //se n� esta cheio.
    this->cheia=(this->numeroElementos>=TAMANHO-1);

    cout <<"Ao final temos:\n";
    this->visita();
    filhoEsq->visita();
    filhoDir->visita();

}
/**
 *      Fun��o paternidade: percorre os filhos de uma arvore restabelecendo as paternidades.*/
void Pagina::paternidade()
{
    //CASO 0: NO � UMA FOLHA
    if(this->ehFolha()){
        return;
    }
    //FIM CASO 0
    else{
        for(int i=0;i<=this->numeroElementos;i++){
            if(this->filhos[i]!=NULL){
                this->filhos[i]->pai=this;}
        }
    }
}
/**
 *      Fun��o absorve: avalia se d� para n� promover um n� filho
 * isso ocorre quando no est� cheio e se possui um s� filho.*/
void Pagina :: absorve(Pagina *no)
{
    cout <<"<<<<<<<< ABSORVE >>>>>>>>>\n";

    int filhoPromovido=this->qualFilho(no);cout << filhoPromovido<<endl;

    if(no->numeroElementos==1)
    {

        this->insereDado(no->getDado(0));cout <<"inseriu numero: "<<no->getDado(0)<<endl;

        this->filhos[filhoPromovido]=no->filhos[0];
        // Funcao auxiliar para inserir o filho novo no n�, pois talvez ele precise deslocar os proximos pro lado.
        this->inserePonteiroFilho(no->filhos[1],filhoPromovido+1);

        this->filhos[filhoPromovido]->pai=this;
        this->filhos[filhoPromovido+1]->pai=this;
        delete no;
    }
    this->visita();
    cout <<"<<<<<<<< FIM ABSORVE >>>>>>>>>\n";


}
/**
 *      Fun��o inserePonteiroFilho: insere um ponteiro para um novo filho no meio dos filhos de uma pagina,
 * salva o ponteiro que la estava e o desloca para direita at� o fim da pagina.
 */
void Pagina::inserePonteiroFilho(Pagina *no,int posicao)
{
    Pagina *temp=this->filhos[posicao],*inserido=no;

    for(int i=posicao;i<TAMANHO;i++)//percorre o vetor de ponteiros a partir da posicao onde queremos inserir o novo.
    {
        temp=this->filhos[i];
        this->filhos[i]=inserido;
        inserido=temp;

    }
}

bool Pagina :: ehFolha()
{
    bool folha=true;//assume que o n� nao tem filhos.
    for(int j=0;j<TAMANHO;j++){
        if(this->filhos[j]!=NULL){
            folha=false;// se algum filho for n�o-nulo retorna falseia folha.
        }
    }
    return folha;
}

/**
 *      Fun��o busca: realiza a busca dentro da pagina caso n�o encontre manda para pagina abaixo mais proxima.
 * caso n�o encontre retorna NULL.*/

Pagina* Pagina::busca(int elemento)
{
    Pagina *encontrada=NULL;
    int iteracoes=this->numeroElementos,i=0;
    bool folha=this->ehFolha();
    if(folha)
    {
        while(i<iteracoes || encontrada!=NULL)
        {
            if(this->dados[i]==elemento){
                encontrada=this;
            }else if(elemento<this->dados[i]){
                encontrada=this->filhos[i]->busca(elemento);
            }else if(elemento > this->dados[i]){
                encontrada=this->filhos[i+1]->busca(elemento);
            }
            i++;
        }
    }else
    {//se n�o tem filhos basta percorrer este n� e ver se encontra o elemento.
        for(i=0;i<TAMANHO-1;i++)
        {
            if(this->dados[i]==elemento){
                encontrada=this;
                break;
            }
        }
    }
    return encontrada;
}

void Pagina::remover(int elemento)
{
    Pagina *paginaAlvo=busca(elemento);

    if(paginaAlvo!=NULL)
    {
        int i=0;
        while(i<TAMANHO-1){
            if(this->dados[i]==elemento){
                this->retiraDado(i);

                bool folha=this->ehFolha();
                if(folha){
                    //puxa os elementos todos para preencher o espa�o vago.
                }else{
                    //se tiver filho precisa promov�-lo.
                }
                break;
            }
            i++;
        }
    }
}
/**
 *  Fun��o reorganizaFilhos: percorre cada no da arvore rescursivamente setando os pais.*/
void Pagina::reorganizaFilhos()
{
    int i=0;
    this->paternidade();
    for(i=0;i<TAMANHO && this->filhos[i]!=NULL;i++)
    {
        this->filhos[i]->reorganiza();
    }
}
/**
 *  Fun��o reorganiza: percorre cada no da arvore rescursivamente vendo se da pra promover um n�.*/
void Pagina::reorganiza()
{
    int i=0;



    for(i=0;i<TAMANHO && this->filhos[i]!=NULL;i++)
    {
        this->filhos[i]->reorganiza();
    }
}

void Pagina::percorre()
{
    int i=0;
    this->visita();
    for(i=0;i<TAMANHO && this->filhos[i]!=NULL;i++)
    {
        this->filhos[i]->percorre();
    }
}

void Pagina::desenhaLinha(int espaco)
    {
        char linha='-',cruz='+';
        for(int i=0;i<(6*espaco)+1;i++)
        {
            if(i==0 || i%espaco==0){std::cout << cruz;}
            cout<<linha;
        }
        cout << '\n';
    }


void Pagina::visita()
{
    int iteracoes=TAMANHO-1,divisoes,espaco=12;
    if(TAMANHO%12!=0){
        divisoes++;
    }




    char cruz='+',linha='-',margem='|';
    cout<<"\n=====================Pagina"<<"("<<this<<")"<<"==================="<<endl;

    desenhaLinha(espaco);


    cout <<"|nE:"<<this->numeroElementos;
    for(int i=2;i<espaco;i++){cout <<" ";}
    cout << "|cheia:"<< this->cheia;
    for(int i=1;i<espaco;i++){cout <<" ";}
    cout <<"|pai:"<< this->pai;
    for(int i=2;i<espaco;i++){cout <<" ";}cout << endl;

    desenhaLinha(espaco);


    cout <<"|";
    for(int i=0;i<iteracoes;i++)
    {
        cout <<this->dados[i];
        for(int j=0;j<8;j++){cout <<" ";}
        cout <<margem;
    }
    cout <<"\n";

    desenhaLinha(espaco);
    for(int i=0;i<TAMANHO;i++){
        cout<<"|"<<this->filhos[i]<<"  ";
    }cout << endl;
    desenhaLinha(espaco);



}
