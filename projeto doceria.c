#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Registro de dados doceria
typedef struct Estoque{
    char nome[70];
    int codigo;
    int quant;
    float preco;
    float precoPeso;
}t_estoque;

//Registro de dados reserva da doceria
typedef struct EstoqueReserva{
    char nome[70];
    int codigo;
    int quant;
    float preco;
    float precoPeso;
}t_estoqueReserva;

//Funcao verificar local da lista
int verificarLocalList(t_estoque estoqueProduto[], char produtoAencontrar[], int Nprodutos){

    for(int i=0; i<Nprodutos+1; i++){
        if(strcmp(estoqueProduto[i].nome,produtoAencontrar)==0){
            return i;
        }
    }
    return 99999;
}

//Função verificar Local da lista por codigo
int verificarLocalListCodigo(t_estoque estoqueProduto[], int Nprodutos, int codigo){

    for(int i=0; i<Nprodutos+1; i++){
        if(estoqueProduto[i].codigo == codigo){
            return i;
        }
    }
    return 99999;
}

//Listar produtos
int listaProdutos(t_estoque estoqueProduto[], int Nprodutos){
    int variavel =0;
    if(Nprodutos>0){
        printf("Lista dos Produtos:\n");
        for(int i=0; i<Nprodutos;i++){
            printf("Nome: %s\n", estoqueProduto[i].nome);
            printf("Codigo: %d\n", estoqueProduto[i].codigo);
            printf("Quantidade: %d\n", estoqueProduto[i].quant);
            if(estoqueProduto[i].precoPeso ==0){
                printf("Preco Unidade: %.2f\n\n", estoqueProduto[i].preco);
            }
            else if (estoqueProduto[i].preco ==0){
                printf("Preco KG: %.2f\n\n", estoqueProduto[i].precoPeso);
            }
        }
    }
    else if(Nprodutos ==0){
        printf("\nESTOQUE ESTA VAZIO.");
    }
}

//Gravar Estoque Permanente
int gravarArquivo(t_estoque estoqueProduto[], int Nprodutos,FILE* fp){

    for(int i=0; i<Nprodutos; i++){
        fprintf(fp,"%s\n", estoqueProduto[i].nome);
        fprintf(fp,"%d\n", estoqueProduto[i].codigo);
        fprintf(fp,"%d\n", estoqueProduto[i].quant);
        fprintf(fp,"%.2f\n", estoqueProduto[i].preco);
        fprintf(fp,"%.2f\n", estoqueProduto[i].precoPeso);
    }

}

//Gravar Dados
int gravarDados(int Nprodutos,FILE* fpDados, int contP, int contKG){
    fprintf(fpDados,"%d\n", Nprodutos);
    fprintf(fpDados,"%d\n", contP);
    fprintf(fpDados,"%d\n", contKG);

}

//função relatorio
int relatorio(int Nprodutos, t_estoque estoqueProduto[], FILE* fpRelatorio, int yes, int contP, int contKG){
    float valorMedioUnidade = 0;
    float valorMedioPeso = 0;
    float valorMediaGeral = 0;

    //Mostrar no console
    if(yes ==0){
        printf("PRODUTOS CADASTRADOS: %d\n", Nprodutos);
        for(int i=0; i<Nprodutos;i++){
            valorMedioUnidade = valorMedioUnidade + estoqueProduto[i].preco;
            valorMedioPeso = valorMedioPeso + estoqueProduto[i].precoPeso;
        }
        valorMediaGeral = (valorMedioPeso+valorMedioUnidade)/Nprodutos;
        valorMedioUnidade = valorMedioUnidade/contP;
        valorMedioPeso = valorMedioPeso/contKG;
        printf("MEDIA VALOR: %f\n", valorMediaGeral);
        if(valorMedioUnidade !='\0'){
            printf("MEDIA VALOR DE PRODUTOS POR UNIDADES: %f\n", valorMedioUnidade);
        }
        else if(valorMedioPeso !='\0'){
            printf("MEDIA VALOR DE PRODUTOS POR KG: %f\n\n",valorMedioPeso);
        }
        else{
            printf("MEDIA VALOR DE PRODUTOS POR UNIDADES: 0\n");
            printf("MEDIA VALOR DE PRODUTOS POR KG: 0\n\n");
        }
        for(int i=0; i<Nprodutos;i++){
            printf("Nome: %s\n", estoqueProduto[i].nome);
            printf("Codigo: %d\n", estoqueProduto[i].codigo);
            printf("Quantidade: %d\n", estoqueProduto[i].quant);
            if(estoqueProduto[i].precoPeso ==0){
                printf("Preco Unidade: %.2f\n\n", estoqueProduto[i].preco);
            }
            else if(estoqueProduto[i].preco ==0){
                printf("Preco KG: %.2f\n\n", estoqueProduto[i].precoPeso);
            }
            else{
                printf("Preco Unidade: %.2f\n\n", estoqueProduto[i].preco);
                printf("Preco KG: %.2f\n\n", estoqueProduto[i].precoPeso);
            }
        }
    }
    //Gravar no arquivo
    fprintf(fpRelatorio,"PRODUTOS CADASTRADOS: %d\n\n", Nprodutos);
    for(int i=0; i<Nprodutos; i++){
        fprintf(fpRelatorio,"Nome: %s\n", estoqueProduto[i].nome);
        fprintf(fpRelatorio,"Quantidade: %d\n", estoqueProduto[i].quant);
        if(estoqueProduto[i].precoPeso ==0){
            fprintf(fpRelatorio,"Preço Unidade: %.2f\n", estoqueProduto[i].preco);
        }
        else{
            fprintf(fpRelatorio,"Preço Peso: %.2f\n", estoqueProduto[i].precoPeso);
        }
        fprintf(fpRelatorio,"\n");
    }
    valorMediaGeral = (valorMedioPeso+valorMedioUnidade)/Nprodutos;
}

int main() {

    int codigo = 0;
    int condicional;
    int cond;
    int sair = 0;
    int Nprodutos = 0;
    int contP = 0;
    int contKG = 0;
    char produtoAencontrar[70];
    t_estoque estoqueProduto[1+Nprodutos];
    t_estoqueReserva estoqueProdutoReserva[1+Nprodutos];

    //leitura Dados
    FILE* fpDadosLeitura = fopen("DADOS.txt", "r");
    fscanf(fpDadosLeitura, "%d", &Nprodutos);
    fgetc(fpDadosLeitura);
    fscanf(fpDadosLeitura, "%d", &contP);
    fgetc(fpDadosLeitura);
    fscanf(fpDadosLeitura, "%d", &contKG);
    fgetc(fpDadosLeitura);
    int fclose(FILE* fpDadosLeitura);

    //leitura Estoque
    FILE* fpLeitura = fopen("ESTOQUE.txt", "r");
    for(int i=0; i<Nprodutos; i++){
        fgets(estoqueProduto[i].nome, 100, fpLeitura);
        estoqueProduto[i].nome[strlen(estoqueProduto[i].nome) -1]= '\0';
        fscanf(fpLeitura, "%d", &estoqueProduto[i].codigo);
        fgetc(fpLeitura);
        fscanf(fpLeitura, "%d", &estoqueProduto[i].quant);
        fgetc(fpLeitura);
        fscanf(fpLeitura, "%f", &estoqueProduto[i].preco);
        fgetc(fpLeitura);
        fscanf(fpLeitura, "%f", &estoqueProduto[i].precoPeso);
        fgetc(fpLeitura);
    }
    int fclose(FILE* fpLeitura);

    //programa
    while(sair == 0){

        //
        printf("\n1- Venda De Produto\n2- cadastrar\n3- alterar dado\n4- pesquisa produto\n5- remover produto\n6- listar todos\n7- relatorio\n8- sair\n");
        scanf("%d", &condicional);
        getchar();
        system("CLS");

        //Venda de produto
        if(condicional == 1){           //OK
            while(sair ==0){
                int verificado;
                int condVend;
                int codProduto;
                float valorPagar;
                int contVendida;
                listaProdutos(estoqueProduto, Nprodutos);
                printf("\nEscola a Forma de Encontrar o Produto:\n1- Codigo do Produto.\n2- Nome do Produto.\n3- Retornar\n\n");
                scanf("%d", &condVend);
                getchar();
                system("CLS");
                if(condVend ==1){
                    listaProdutos(estoqueProduto, Nprodutos);
                    printf("\nDigite o Codigo do Produto: ");
                    scanf("%d", &codProduto);
                    getchar();
                    verificado = verificarLocalListCodigo(estoqueProduto, Nprodutos, codProduto);
                    system("CLS");
                }
                else if(condVend == 2){
                    listaProdutos(estoqueProduto, Nprodutos);
                    printf("\nDigite o Nome do Produto: ");
                    gets(produtoAencontrar);
                    verificado = verificarLocalList(estoqueProduto, produtoAencontrar, Nprodutos);
                    system("CLS");
                }
                else if(condVend ==3){
                    break;
                }
                codigo =0;
                if(verificado !=99999){
                    printf("digite a Quantidade Vendida: ");
                    scanf("%d", &contVendida);
                    getchar();
                    system("CLS");
                    estoqueProduto[verificado].quant = estoqueProduto[verificado].quant - contVendida;
                    if(estoqueProduto[verificado].preco == 0){
                        valorPagar = estoqueProduto[verificado].precoPeso * contVendida;
                        printf("Valor a Pagar: %.2f", valorPagar);
                        getchar();
                        system("CLS");
                    }
                    else{

                        valorPagar = estoqueProduto[verificado].preco * contVendida;
                        printf("Valor a Pagar: %.2f", valorPagar);
                        getchar();
                        system("CLS");
                    }
                }
                else{
                    printf("\nDigito Invalido.\n\nPressione ENTER para Continuar.");
                    getchar();
                    system("CLS");
                }
            }
        }
        //Cadastrar Produto.
        else if(condicional == 2){      //OK

            while(sair ==0){
                printf("Digite o Nome do Produto: ");
                gets(estoqueProduto[Nprodutos].nome);
                codigo = rand() % 1000;
                verificarLocalListCodigo(estoqueProduto,Nprodutos,codigo);


                system("CLS");
                printf("Como o Produto Deve Ser Avaliado:\n\n1- Quantidade.\n2- Peso.\n3- Retornar.\n\n");
                scanf("%d", &cond);
                getchar();
                system("CLS");
                if(cond==1){
                    printf("Insira a Quantidade: ");
                    scanf("%d", &estoqueProduto[Nprodutos].quant);
                    getchar();
                    printf("Insira o Valor da Unidade: ");
                    scanf("%f", &estoqueProduto[Nprodutos].preco);
                    getchar();
                    estoqueProduto[Nprodutos].precoPeso = 0;
                    Nprodutos++;
                    contP++;
                    system("CLS");
                    printf("\nProduto Cadastrado com Sucesso.\n\nPressione ENTER para Continuar.");
                    getchar();
                    system("CLS");
                }
                //Preco KG
                else if(cond==2){
                    printf("insira a quantidade: ");
                    scanf("%d", &estoqueProduto[Nprodutos].quant);
                    getchar();
                    printf("insira o preco do kg: ");
                    scanf("%f", &estoqueProduto[Nprodutos].precoPeso);
                    getchar();
                    estoqueProduto[Nprodutos].preco = 0;
                    printf("\n");
                    Nprodutos++;
                    contKG++;
                    system("CLS");
                    printf("\nProduto Cadastrado com Sucesso.\n\nPressione ENTER para Continuar.");
                    getchar();
                    system("CLS");
                }
                else if(cond==3){
                    break;
                }
                else {
                    printf("\nNumero Digitado Invalido.\n\nPressione ENTER para Continuar.");
                    getchar();
                    system("CLS");
                    break;
                }
                FILE* fp = fopen("ESTOQUE.txt", "w");
                gravarArquivo(estoqueProduto, Nprodutos, fp);
                fclose(fp);
                FILE* fpDados = fopen("DADOS.txt", "w");
                gravarDados(Nprodutos, fpDados, contP, contKG);
                fclose(fpDados);
                system("CLS");
                break;
            }
        }
        //Alterar Produto
        else if(condicional == 3){      //OK
            while(sair ==0){
                printf("ENTER para Retornar.\n\n");
                printf("Nome do Produto Que Deseja Alterar: ");
                gets(produtoAencontrar);
                system("CLS");

                int cond;
                int verificado = verificarLocalList(estoqueProduto, produtoAencontrar, Nprodutos);
                if(verificado != 99999){
                    printf("Deseja Alterar: \n1- Nome. \n2-Valor. \n3-Quantidade. \n4- Voltar.\n\n");
                    scanf("%d", &cond);
                    getchar();
                    system("CLS");
                    if(cond ==1){

                        printf("Digite o novo nome:\n");
                        gets(estoqueProduto[verificado].nome);
                        system("CLS");
                        printf("\nNome Alterado com Sucesso.\n\nPressione ENTER para Continuar.");
                        getchar();
                        system("CLS");

                    }
                    else if(cond ==2){
                        cond=0;
                        printf ("\nDeseja Alterar: \n1- Valor Por Unidade. \n2- Valor KG.\n");
                        scanf("%d", &cond);
                        system("CLS");
                        if(cond ==1){
                            printf("Digite o Novo Valor por Unidade: ");
                            scanf("%f", &estoqueProduto[verificado].preco);
                            estoqueProduto[verificado].precoPeso = 0;
                            getchar();
                            system("CLS");
                            printf("\nValor Alterado com Sucesso.\n\nPressione ENTER para Continuar.");
                            getchar();
                            system("CLS");
                        }
                        else if( cond ==2){
                            printf("Digite o Novo Valor  por KG: ");
                            scanf("%f", &estoqueProduto[verificado].precoPeso);
                            estoqueProduto[verificado].preco = 0;
                            getchar();
                            system("CLS");
                            printf("Valor Alterado com Sucesso.\n\nPressione ENTER para Continuar.");
                            getchar();
                            system("CLS");
                        }
                    }
                    else if(cond ==3){
                        printf("Digite a Nova Quantidade: ");
                        scanf("%d", &estoqueProduto[verificado].quant);
                        getchar();
                        system("CLS");
                        printf("\nQuantidade Alterado com Sucesso.\n\nPressione ENTER para Continuar.");
                        getchar();
                        system("CLS");
                    }
                    else if(cond ==4){
                        system("CLS");
                        break;
                    }
                    else{
                        printf("\nDigito Invalido.\n\nPressione ENTER para Continuar.");
                        getchar();
                        system("CLS");
                        break;
                    }

                    FILE* fp = fopen("ESTOQUE.txt", "w");
                    gravarArquivo(estoqueProduto, Nprodutos, fp);
                    fclose(fp);
                    verificado =0;
                    system("CLS");
                    break;
                }

                else{
                printf("\nNome do Produto Invalido.\n\nPressione ENTER para Continuar.");
                getchar();
                system("CLS");
                break;
                }
            }
        }
        //Pesquisar Produto
        else if(condicional == 4){      //OK
            int condA = 0;
            int verificado;
            printf("1- Pesquisar por Nome.\n2- Pesquisar por Codigo do Produto.\n");
            scanf("%d",&condA);
            getchar();
            system("CLS");
            if(condA ==1){
                printf("Digite o Nome do Produto: ");
                gets(&produtoAencontrar);
                system("CLS");
                 verificado = verificarLocalList(estoqueProduto,produtoAencontrar, Nprodutos);
            }
            else if(condA==2){
                printf("Digite o Codigo do Produto: ");
                scanf("%d ",codigo);
                system("CLS");
                 verificado = verificarLocalListCodigo(estoqueProduto,produtoAencontrar, Nprodutos);
            }
            else{
                printf("Digito Invalido.\n\n Pressione ENTER para continuar.");
                getchar();
                system("CLS");
            }
            if(verificado != 99999){
                printf("PRODUTO PESQUISADO:\n\nNome: %s\nCodigo: %d\nQuantidade: %d\n",estoqueProduto[verificado].nome,estoqueProduto[verificado].codigo, estoqueProduto[verificado].quant);
                if(estoqueProduto[verificado].precoPeso == 0){
                    printf("Preco: %.2f\n",estoqueProduto[verificado].preco);
                    printf("\n\n Pressione ENTER para Continuar.");
                    getchar();
                    system("CLS");
                }
                else if(estoqueProduto[verificado].preco == 0){
                    printf("Preco por KG: %.2f\n",estoqueProduto[verificado].precoPeso);
                    printf("\n\nPressione ENTER para Continuar.");
                    getchar();
                    system("CLS");
                }
                else{
                    printf("Preco: %.2f\n",estoqueProduto[verificado].preco);
                    printf("Preco por Unidade: %.2f\n",estoqueProduto[verificado].precoPeso);
                    printf("\n\nressione ENTER para Continuar.");
                    getchar();
                    system("CLS");
                }
            }
            else{
                printf("Nome Digitado Invalido.\n\nPressione ENTER para Retornar ao Menu.");
                getchar();
                system("CLS");
            }
        }
        //Remover Produto
        else if(condicional == 5){      //OK
            printf("Pressione ENTER para Retornar ao MENU.\n\nNome do Produto que Deseja Remover: ");
            gets(produtoAencontrar);
            system("CLS");
            int cond;
            int verificado = verificarLocalList(estoqueProduto, produtoAencontrar, Nprodutos);
                while(sair==0){
                if(verificado != 99999){
                    printf("Deseja:\n1- Listar Todos os Produtos \n2- Remover o Valor do Produto \n3- Remover a Quantidade \n4- Remover Todo o Produto\n5- Voltar.\n");
                    scanf("%d", &cond);
                    getchar();
                    system("CLS");
                    if(cond ==1){
                       listaProdutos(estoqueProduto, Nprodutos);
                       getchar();
                       system("CLS");
                    }
                    else if(cond ==2){
                        cond ==0;
                        printf ("1- Remover o Valor da Quantidade. \n2- Remover Valor por KG.\n");
                        scanf("%d", &cond);
                        getchar();
                        system("CLS");

                        if(cond ==1){

                            estoqueProduto[verificado].preco = 0;
                            printf("Valor Removido com Sucesso!!!");
                            printf("\n\nPressione ENTER para Continuar.");
                            getchar();
                            system("CLS");
                            break;
                        }
                        else if( cond ==2){

                            estoqueProduto[verificado].precoPeso = 0;
                            printf("Valor por KG Removido com Sucesso!!!");
                            printf("\n\nPressione ENTER para Continuar.");
                            getchar();
                            system("CLS");
                            break;
                        }
                    }
                    else if(cond ==3){
                        estoqueProduto[verificado].quant = 0;
                        printf("Quantidade Removida com Sucesso!!!");
                        printf("\n\nPressione ENTER para Continuar.");
                        getchar();
                        system("CLS");
                        break;
                    }
                    else if(cond ==4){
                        for(int i=0; i<Nprodutos; i++){
                            if(i != verificado){
                                strcpy(estoqueProdutoReserva[i].nome, estoqueProduto[i].nome);
                                estoqueProdutoReserva[i].quant = estoqueProduto[i].quant;
                                estoqueProdutoReserva[i].preco = estoqueProduto[i].preco;
                                estoqueProdutoReserva[i].precoPeso = estoqueProduto[i].precoPeso;
                            }
                        }
                        Nprodutos--;
                        for(int i=0; i<Nprodutos; i++){
                            if(i != verificado){
                                strcpy(estoqueProduto[i].nome, estoqueProdutoReserva[i].nome);
                                estoqueProduto[i].quant = estoqueProdutoReserva[i].quant;
                                estoqueProduto[i].preco = estoqueProdutoReserva[i].preco;
                                estoqueProduto[i].precoPeso = estoqueProdutoReserva[i].precoPeso;
                            }
                        }
                        //gravar estoque
                        FILE* fp = fopen("ESTOQUE.txt", "w");
                        gravarArquivo(estoqueProduto, Nprodutos, fp);
                        fclose(fp);
                        //gravar dados
                        FILE* fpDados = fopen("DADOS.txt", "w");
                        gravarDados(Nprodutos, fpDados, contP,contKG);
                        fclose(fpDados);

                        printf("Produto Removido com Sucesso!!!");
                        printf("\n\nPressione ENTER para Continuar.");
                        getchar();
                        system("CLS");
                        break;

                    }
                    else if(cond ==5){
                        break;
                    }
                    else{
                        printf("Digito Invalido.");
                        printf("\n\nPressione ENTER para Continuar.");
                        getchar();
                        system("CLS");
                        break;
                    }
                }
                else{
                    printf("Nome Invalido.\n\nPressione ENTER para Continuar.");
                    getchar();
                    system("CLS");
                    break;
                }
            }
            verificado =0;
            system("CLS");
        }
        //Lista de Produtos
        else if(condicional == 6){      //OK
                listaProdutos(estoqueProduto, Nprodutos);
                printf("\n\nPressione ENTER para continuar.");
                getchar();
                system("CLS");
        }
        //Relatorio
        else if(condicional == 7){      //OK
            int yes = 0;
            FILE* fpRelatorio = fopen("Relatorio.txt", "w");
            relatorio(Nprodutos, estoqueProduto, fpRelatorio, yes, contP, contKG);
            int fclose(FILE* fpRelatorio);
            getchar();
            system("CLS");
        }
        //Sair Programa
        else if(condicional == 8){      //OK
            //gravar estoque
            FILE* fp = fopen("ESTOQUE.txt", "w");
            gravarArquivo(estoqueProduto, Nprodutos, fp);
            fclose(fp);
            //gravar dados
            FILE* fpDados = fopen("DADOS.txt", "w");
            gravarDados(Nprodutos, fpDados, contP,contKG);
            fclose(fpDados);
            //gravar relatorio
            int yes = 1;
            FILE* fpRelatorio = fopen("Relatorio.txt", "w");
            relatorio(Nprodutos, estoqueProduto, fpRelatorio, yes, contP, contKG);
            int fclose(FILE* fpRelatorio);
            system("CLS");
            sair=1;
        }
        //Digito Invalido
        else{                           //OK
            printf("Digito Invalido!!!");
            getchar();
            system("CLS");
        }
    }
}
