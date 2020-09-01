#include <cstdlib>
#include <iostream>
#include <string.h>

using namespace std;

FILE *ARQ; //arquivo

struct DADOS{  //registro
       char MODELO[20], MARCA[15],STATUS, ANO[5], PRECO[8], QUANT[4];
       };
       DADOS REG;

int OP,ES;  //op��o
char PESQ[20]; //pesquisa

int CADASTRAR(void)
{   
		cout<<"\n\t-------------------- Cadastro --------------------"<<endl;
		cout<<"\tEntre com: \n\tModelo:";
	    fflush(stdin);  //***LIMPA O BUFFER DO TECLADO***//
		cin.getline(REG.MODELO,20);
		strupr(REG.MODELO); //coloca as letras em maiuscula
		
		cout<<"\tMarca: ";
		fflush(stdin);
		cin.getline(REG.MARCA,15);
		strupr(REG.MARCA); //coloca as letras em maiuscula
	
        cout<<"\tAno: ";
		fflush(stdin);
		cin.getline(REG.ANO,5); 
	 
		cout<<"\tPreco: ";
		fflush(stdin);
		cin.getline(REG.PRECO,8);
		
		fflush(stdin);
		cout<<"\tQuantidade: ";
		cin.getline(REG.QUANT,3);

        REG.STATUS ='0'; //arquivo valido
        
        fseek(ARQ,0,SEEK_END);
    	cout<<fwrite(&REG, 1, sizeof(DADOS), ARQ);
    	fflush(ARQ);
		 
        return(0);
}

int EDITAR(void)
{	
	cout<<"\n\t-------------------- Edicao --------------------"<<endl;
	cout<<"\tEntre com o Modelo para editar: ";
	fflush(stdin);
	cin.getline(PESQ,20);
	strupr(PESQ);
	cout<<"\n\tCarro(s): \n"<<endl;
	
	fseek(ARQ,0,SEEK_SET);
	
	while(fread(&REG,1,sizeof(DADOS),ARQ) !=0)
	{
		if(REG.STATUS == '0' && (strcmp(PESQ, REG.MODELO)==0))
		{
			cout<<"\t1 - Modelo: "<<REG.MODELO<<endl;
			cout<<"\t2 - Marca: "<<REG.MARCA<<endl;
			cout<<"\t3 - Ano: "<<REG.ANO<<endl;
			cout<<"\t4 - Preco: "<<REG.PRECO<<endl;
			cout<<"\t5 - Quantidade: "<<REG.QUANT<<endl;
			cout<<"\n\tEntre com a opcao que quer modificar: "<<endl;
			cout<<"\tOpcao: ";
			do{
				cin>>OP;
				if((OP!=1) and (OP!=2) and (OP!=3) and (OP!=4)and (OP!=5))
				{
					cout<<"\n\tOpcao incorreta. Entre com uma das opcoes do Menu."<<endl;
					cout<<"\tOpcao: ";	
				}	
			}while((OP!=1) and (OP!=2) and (OP!=3) and (OP!=4)and (OP!=5));
	
				switch(OP)
				{
					case 1: cout<<"\tNovo Modelo: ";
							fflush(stdin);
							cin.getline(REG.MODELO,20);
							strupr(REG.MODELO); //coloca as letras em maiuscula
							break;
					case 2: cout<<"\tNova Marca: ";
							fflush(stdin);
							cin.getline(REG.MARCA,15);
							strupr(REG.MARCA); //coloca as letras em maiuscula
							break;
					case 3: cout<<"\tNovo Ano: ";
							fflush(stdin);
							cin.getline(REG.ANO,5);
							break;
					case 4: cout<<"\tNovo Preco: ";
							fflush(stdin);
							cin.getline(REG.PRECO,8);
							break;
					case 5: cout<<"\tNova Quantidade: ";
							fflush(stdin);
							cin.getline(REG.QUANT,4);
							break;
				}
			fseek(ARQ, (-1*sizeof(DADOS)) , SEEK_CUR);
            fwrite(&REG,1,sizeof(DADOS),ARQ);
            fflush(ARQ);
			}
		cout<<"\n";
	}	
	system("pause");
	return(0);
}

int LISTAR(void)
{
	cout<<"\n\t-------------------- Lista --------------------"<<endl;
	cout<<"\tCarros Cadastrados: \n"<<endl;
	
	fseek(ARQ, 0 , SEEK_SET);
	
	while(fread(&REG,1,sizeof(DADOS),ARQ) != 0 )
	{
		if(REG.STATUS == '0'){
			cout<<"\tModelo: "<<REG.MODELO<<endl;
			cout<<"\tMarca: "<<REG.MARCA<<endl;
			cout<<"\tAno: "<<REG.ANO<<endl;
			cout<<"\tPreco: "<<REG.PRECO<<endl;
			cout<<"\tQuantidade: "<<REG.QUANT<<endl;
			cout<<"\t........................................"<<endl;
		}
		cout<<"\n";	
	}
	system("pause");
	return(0);
}

int EXCLUIR(void)
{    	
	cout<<"\n\t-------------------- Excluir --------------------"<<endl;
    cout<<"\n\tEntre com Modelo: ";
    fflush(stdin);  //***LIMPA O BAFFER DO DECLADO***//
    cin.getline(PESQ,20);
    strupr(PESQ); //coloca as letras em maiuscula

    cout<<"\n\tCarros Cadastrados: "<<endl;

	fseek(ARQ, 0 , SEEK_SET);
	
	while(fread(&REG,1,sizeof(DADOS),ARQ) != 0 )
	{
		if(REG.STATUS == '0' &&(strcmp(PESQ, REG.MODELO) == 0)){
			cout<<"\n\tModelo: "<<REG.MODELO<<endl;
			cout<<"\tMarca: "<<REG.MARCA<<endl;
			cout<<"\tAno: "<<REG.ANO<<endl;
			cout<<"\tPreco: "<<REG.PRECO<<endl;
			cout<<"\tQuantidade: "<<REG.QUANT<<endl;	
	        
	        REG.STATUS = '1'; //arquivo inv�lido
	        
            fseek(ARQ, (-1*sizeof(DADOS)) , SEEK_CUR);
            fwrite(&REG,1,sizeof(DADOS),ARQ);
            fflush(ARQ); //***LIMPAR O BUFFER DO ARQUIVO E FORCA A GRAVACAO DAS INFORMACOES***//
            		     //***USE SEMPRE DEPOIS DE ESCREVER NO ARQUIVO***//
		}
		cout<<"\n";	
	}
	system("pause");
	return(0);    
    }
	
	
int PESQUISAR(void)
{	
	cout<<"\n\t-------------------- Pesquisar --------------------"<<endl;
	cout<<"\tEntre com o Modelo que quer pesquisar: ";
	fflush(stdin);
	cin.getline(PESQ,20);
	strupr(PESQ); //coloca as letras em maiuscula
	cout<<"\tCadastro: \n"<<endl;
	fseek(ARQ,0,SEEK_SET);
	while(fread(&REG,1,sizeof(DADOS),ARQ) !=0)
	{
		if(REG.STATUS == '0' && (strcmp(PESQ, REG.MODELO)==0))
		{
			cout<<"\tModelo: "<<REG.MODELO<<endl;
			cout<<"\tMarca: "<<REG.MARCA<<endl;
			cout<<"\tAno: "<<REG.ANO<<endl;
			cout<<"\tPreco: "<<REG.PRECO<<endl;
			cout<<"\tQuantidade: "<<REG.QUANT<<endl;
		}
		cout<<"\n";
	}
	system("pause");
	return(0);
}

int SAIR (void)
{
    exit(0);   
}

int main(int argc, char *argv[])
{   
    int NUM=0;
    
    ARQ = fopen("Consulta.txt","r+");  //Abrir e editar arquivo
    if(ARQ==0) //caso nao houver arquivo
    {
               ARQ = fopen("Consulta.txt","w+"); //criacao do arquivo e habilitado para saida
               }
    
    cout<<"\n\n\t       PROJETO DE ALGORITMO - 2/2014"<<endl;
    cout<<"\n\tTEMA PRINCIPAL: CONCESSIONARIA DE VEICULOS"<<endl;
    cout<<"\n\n\tALUNOS: DIVANA BARBOSA - M: 324   - GEB \n\t        PAULO PAGANI  -  M: 8918  - GET"<<endl;
    cout<<"\n"<<endl;
    system("pause");
    system("cls");
  
    while(NUM==0){
    cout<<"\n\t-------------------- MENU --------------------"<<endl;
    cout<<"\t1- .................................. Cadastro"<<endl;
    cout<<"\t2- .................................. Editar"<<endl;
    cout<<"\t3- .................................. Listar"<<endl;
    cout<<"\t4- .................................. Excluir"<<endl;
    cout<<"\t5- .................................. Pesquisar"<<endl;
    cout<<"\t6- .................................. Sair"<<endl;
    cout<<"\n\tOpcao: ";
    do{    	
   		cin>>NUM;
   		if((NUM!=1) and (NUM!=2) and (NUM!=3) and (NUM!=4) and (NUM!=5) and (NUM!=6))
		   {
		   		cout<<"\n\tOpcao incorreta. Entre com uma das opcoes do Menu."<<endl;
		   		cout<<"\tOpcao: ";
		   }
    	}while((NUM!=1) and (NUM!=2) and (NUM!=3) and (NUM!=4) and (NUM!=5) and (NUM!=6));
    system("cls");
//-----------------------------------
    switch(NUM){
                case 1: {
                	OP=1;
                	while(OP==1){
                		CADASTRAR();
                		cout<<"\n\tDeseja fazer mais um cadastro"<<endl;
                		cout<<"\t1- Sim \t2- Nao"<<endl;
                		cout<<"\tOpcao: ";
                		do{
                			cin>>OP;
                			if((OP!=1) and (OP!=2)){
                				cout<<"\n\tOpcao incorreta. Entre com uma das opcoes do Menu."<<endl;
                				cout<<"\tOpcao: ";
							}                			
						}while((OP!=1) and (OP!=2));
                		
                		system("cls");
					}
					NUM=0;
                	system("cls");
					break;
				}
                case 2: {
                	OP=1;
                	while(OP==1){
                		EDITAR();
                		cout<<"\n\tDeseja fazer mais uma edicao: "<<endl;
                		cout<<"\t1- Sim \t2- Nao"<<endl;
                		cout<<"\tOpcao: ";
                		do{
                			cin>>OP;
                			if((OP!=1) and (OP!=2)){
                				cout<<"\n\tOpcao incorreta. Entre com uma das opcoes do Menu."<<endl;
                				cout<<"\tOpcao: ";
							}                			
						}while((OP!=1) and (OP!=2));
                		system("cls");	
					}
                	NUM=0;
                	system("cls");
					break;
				}
                case 3: {
                	NUM=LISTAR();
                	system("cls");
					break;
				}
                case 4: {
            		OP=1;
                	while(OP==1){
                		EXCLUIR();
                		cout<<"\n\tDeseja fazer mais uma exclusao: "<<endl;
                		cout<<"\t1- Sim \t2- Nao"<<endl;
                		cout<<"\tOpcao: ";
                		do{
                			cin>>OP;
                			if((OP!=1) and (OP!=2)){
                				cout<<"\n\tOpcao incorreta. Entre com uma das opcoes do Menu."<<endl;
                				cout<<"\tOpcao: ";
							}                			
						}while((OP!=1) and (OP!=2));
                		system("cls");	
					}
                	NUM=0;
                	system("cls");
					break;
				}
                case 5: {
                	OP=1;
                	while(OP==1){
                		PESQUISAR();
                		cout<<"\n\tDeseja fazer mais uma pesquisa"<<endl;
                		cout<<"\t1- Sim \t2- Nao"<<endl;
                		cout<<"\tOpcao: ";
                		do{
                			cin>>OP;
                			if((OP!=1) and (OP!=2)){
                				cout<<"\n\tOpcao incorreta. Entre com uma das opcoes do Menu."<<endl;
                				cout<<"\tOpcao: ";
							}                			
						}while((OP!=1) and (OP!=2));
                		system("cls");
					}
					NUM=0;
                	system("cls");
					break;
				}
                case 6:{
               	            fclose(ARQ);                                 
							SAIR();
							break;
						}
                }
    }
    system("PAUSE");
    return EXIT_SUCCESS;                                                                                                                                                                                                                                                                 
}
