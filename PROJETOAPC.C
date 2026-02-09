
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// verifica o sistema operacional
#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    # define CLEAR_SCREEN "clear"
#endif

char cabecalho[] = "*** Words of Wonder ***\n\n";
char file[] = "entrada.txt";

typedef struct {
    char letras[9];
    int qntpalavras;
    char palavras[20][10];
}ENTRADAFASE;

typedef struct{
    char palavras[20][10];
    int palavrascertas;
}PALAVRAS;

typedef struct{
    char nickname[20];
    int pontuacao;
}DADOSJOGADOR;

void SALVARANKING(DADOSJOGADOR *dados){
    FILE *ranking;
    char arquivo[] = "ranking.bin";
    ranking = fopen(arquivo,"ab");

    fwrite(dados, sizeof(DADOSJOGADOR), 1, ranking);

    fclose(ranking);
}

void MATRIZLETRAS(char *letras){
    int i, j, k, count = 0, tam;
    char matriz[3][5];
    for(i=0;i<3;i++){
        for(j=0;j<5;j++){
            matriz[i][j] = 'x';
        }
    }
    tam = strlen(letras);
    for(k=0;k<8;k++){
        for(i=0;i<3 && count<tam;i++){
            for(j=0;j<5;j++){
                if(i==0 && j==0 && count==0){
                    matriz[i][j]=letras[count];
                    count++;
                }
                else if(i==2 && j==0 && count==1){
                    matriz[i][j]=letras[count];
                    count++;
                }
                else if(i==1 && j==1 && count==2){
                    matriz[i][j]=letras[count];
                    count++;
                }
                else if(i==0 && j==2 && count==3){
                    matriz[i][j]=letras[count];
                    count++;
                }
                else if(i==2 && j==2 && count==4){
                    matriz[i][j]=letras[count];
                    count++;
                }
                else if(i==1 && j==3 && count==5){
                    matriz[i][j]=letras[count];
                    count++;
                }
                else if(i==0 && j==4 && count==6){
                    matriz[i][j]=letras[count];
                    count++;
                }
                else if(i==2 && j==4 && count==7){
                    matriz[i][j]=letras[count];
                    count++;
                }
            }
        }
    }
    for(i=0;i<3;i++){
        for(j=0;j<5;j++){
            if(matriz[i][j]=='x'){
                printf("   ");
            }
            else{
                printf("%3c", matriz[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void MENU(){
    printf("(1) JOGAR\n");
    printf("(2) CONFIGURACOES\n");
    printf("(3) INSTRUCOES\n");
    printf("(4) RANKING\n");
    printf("(5) SAIR\n");
    printf("\nDigite a opcao desejada: ");
}

int LERARQUIVO(ENTRADAFASE *fase, FILE* fd, PALAVRAS *palavrasencontradas){
    int i, j, count = 0, tam;
    char buffer[10];

    if(fscanf(fd, "%s", buffer)==EOF){
        return 0;
    }

    if(strcmp(buffer, "-")==0){
        if(fscanf(fd, "%s", buffer)==EOF){
            return 0;
        }
    }

    strcpy(fase->letras, buffer);
    fscanf(fd, "%d", &fase->qntpalavras);
    for(i=0;i<fase->qntpalavras;i++){
        fscanf(fd,"%s", fase->palavras[count]);
        count++;
    }

    for(i=0;i<fase->qntpalavras;i++){
        tam = strlen(fase->palavras[i]);
        for(j=0;j<tam;j++){
            palavrasencontradas->palavras[i][j] = '_';
        }
        palavrasencontradas->palavras[i][tam] = '\0';
    }
    palavrasencontradas->palavrascertas = 0;
    return 1;
}

void PRINTPALAVRAS(int qntpalavras, PALAVRAS *palavrasencontradas){
    int i;
    for(i=0;i<qntpalavras;i++){
        printf("%s\n", palavrasencontradas->palavras[i]);
    }
    printf("\n");
}

void VERIFICACHUTE(char *chute, int qntpalavras, PALAVRAS *palavrasencontradas, ENTRADAFASE *fase, DADOSJOGADOR *dados){
    int i, flagexiste = 0, flagjafoi = 0;
    // verifica se a palavra ja foi tentada
    for(i=0;i<qntpalavras;i++){
        if(strcmp(chute,palavrasencontradas->palavras[i])==0){
            flagjafoi++;
        }
    }
    for(i=0;i<qntpalavras;i++){
        if(strcmp(chute,fase->palavras[i])==0 && flagjafoi==0){
            strcpy(palavrasencontradas->palavras[i], fase->palavras[i]);
            flagexiste++;
            palavrasencontradas->palavrascertas++;
            dados->pontuacao+=100;
            printf("Parabens!!! Voce encontrou uma palavra!!! ");
        }
    }
    if(flagjafoi==0 && flagexiste==0){
        printf("Palavra inexistente! ");
        dados->pontuacao-=10;
    }
    else if(flagjafoi!=0){
        printf("Esta palavra ja foi encontrada! ");
        dados->pontuacao-=10;
    }
}

void EXECUTAFASE(ENTRADAFASE *fase, PALAVRAS *palavrasencontradas, DADOSJOGADOR *dados){
    printf("%s", cabecalho);
    printf("            PONTUACAO: %d\n", dados->pontuacao);
    MATRIZLETRAS(fase->letras);
    printf("Encontre %d palavras:\n", fase->qntpalavras);
    PRINTPALAVRAS(fase->qntpalavras, palavrasencontradas);
    char chute[10];
    char enter;
    if(palavrasencontradas->palavrascertas < fase->qntpalavras){
        printf("Informe a palavra: ");
        scanf("%s", chute);
        getchar();
        VERIFICACHUTE(chute, fase->qntpalavras, palavrasencontradas, fase, dados);
        printf("Tecle <enter>\n");
        scanf("%c", &enter);
    }
    else{
        dados->pontuacao+=25;
        printf("Parabens voce completou a fase!!! acertou %d palavras!!!\n", fase->qntpalavras);
        printf("Tecle <enter> \n");
        scanf("%c", &enter);
        palavrasencontradas->palavrascertas++;
    }
    
}

void MENUCONFIG(){
    int opcaoconfig;
    do{
        system(CLEAR_SCREEN);
        printf("*** CONFIGURACOES ***\n\n");
        printf("(1) ZERAR RANKING\n");
        printf("(2) VOLTAR AO MENU PRINCIPAL\n\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcaoconfig);
        getchar();   
        if(opcaoconfig==1){
            system(CLEAR_SCREEN);
            printf("%s\n\n", cabecalho);
            printf("Confirma reiniciar o ranking? (S/N) ");
            char confirmar;
            scanf("%c", &confirmar);
            getchar();
            if(confirmar=='S'){
                FILE *ranking;
                char arquivo[] = "ranking.bin";
                ranking = fopen(arquivo,"wb");
                fclose(ranking);
                printf("Ranking zerado! Tecle <enter> para continuar ");
                getchar();
                char enter;
                scanf("%c", &enter);  
            }     
        }  
        else if(opcaoconfig!=1 && opcaoconfig!=2){
            printf("\nOpcao invalida! Tecle <enter>\n");
            char enter;
            scanf("%c", &enter);
        }
    }while(opcaoconfig!=2);

}

void INSTRUCOES(){
    system(CLEAR_SCREEN);
    getchar();
    printf("INSTRUCOES SOBRE O JOGO WORDS OF WONDER:\n\n");
    printf("1. OBJETIVO:\n-Seu desafio e encontrar todas as palavras ocultas em cada fase.\nPara isso, voce deve desembaralhar as letras apresentadas no quadro de letras e formar palavras validas.\n\n");
    printf("2. MECANICA:\n-No topo da tela, voce vera um conjunto de letras misturadas.\n-Abaixo, havera espaCos vazios (tracos) indicando quantas palavras voce precisa encontrar e o tamanho de cada uma.\n-Digite a palavra que voce encontrou e pressione ENTER.\n\n");
    printf("3. PONTUACAO:\n-Acerto: +100 pontos.\n-Erro (palavra inexistente): -10 pontos.\n-Repeticao (palavra ja encontrada): -10 pontos.\n\n");
    printf("4. PROGRESSAO:\n-Para passar de fase, voce precisa preencher todas as palavras da lista.\nO jogo termina quando nao houver mais fases no arquivo ou se voce decidir parar.\n\n");
    printf("Tecle <enter> para prosseguir... ");
    char enter;
    scanf("%c", &enter);
}

void MOSTRARRANKING(){
    system(CLEAR_SCREEN);
    FILE *ranking;
    char arquivo[] = "ranking.bin";
    ranking = fopen(arquivo, "rb");
    
    printf("%s", cabecalho);
    printf("RANKING:\n");

    if(ranking==NULL){
        printf("Nenhum registro de ranking encontrado.\n");
    }
    else{
        fseek(ranking,0,SEEK_END);
        long tamarquivo = ftell(ranking);
        rewind(ranking);

        int qntjogadores = tamarquivo/sizeof(DADOSJOGADOR);

        if(qntjogadores==0){
            printf("Nenhum registro de ranking encontrado.\n");
        }
        else{
            DADOSJOGADOR printranking[qntjogadores];
            fread(printranking, sizeof(DADOSJOGADOR), qntjogadores, ranking);

            int i, j;
            DADOSJOGADOR aux;
            // bubble sort
            for(i = 0; i < qntjogadores; i++){
                for(j = 0; j < qntjogadores-i-1; j++){
                    if(printranking[j].pontuacao < printranking[j+1].pontuacao){
	                aux = printranking[j];
	                printranking[j] = printranking[j+1];
	                printranking[j+1] = aux;
                    }
                }
            }
            for(i=0;i<qntjogadores;i++){
                printf("%s %dpts\n", printranking[i].nickname, printranking[i].pontuacao);
            }
        }
        fclose(ranking);
    }
    printf("\n Tecle <enter> para voltar ao MENU ");
    char enter;
    getchar();
    scanf("%c", &enter);
}

int main(){
    system(CLEAR_SCREEN);

    // criar o FILE
    FILE* fd;
    fd = fopen(file,"r");

    // criar structs
    ENTRADAFASE fase;
    PALAVRAS palavrasencontradas;
    DADOSJOGADOR dados;

    // inicializar como 0 pontos
    dados.pontuacao = 0;

    // ler o nick do jogador
    printf("Bem vindo(a) ao Words of Wonder!!!\n\n");
    printf("Informe seu nickname: ");
    
    scanf("%s", dados.nickname);

    // para limpar o terminal usar cls(win) ou clear(linux)
    system(CLEAR_SCREEN);

    // opçao do jogador e print menu
    int opcao;
    do{
        system(CLEAR_SCREEN);
        printf("%s", cabecalho);
        MENU();
        scanf("%d", &opcao);
        system(CLEAR_SCREEN);

        while(opcao!=1 && opcao!=2 && opcao!=3 && opcao!=4 && opcao!=5){
            printf("%s", cabecalho);
            printf("OPCAO INVALIDA!\n");
            MENU();
            scanf("%d", &opcao);
            system(CLEAR_SCREEN);
        }

        // OPÇAO 1 (JOGAR)
        if(opcao==1){
            rewind(fd);
            dados.pontuacao = 0;
            char entrada = 'S';
            while(LERARQUIVO(&fase, fd, &palavrasencontradas)!=0 && entrada=='S'){
                while(palavrasencontradas.palavrascertas<=fase.qntpalavras){
                    system(CLEAR_SCREEN);
                    EXECUTAFASE(&fase, &palavrasencontradas, &dados);
                }
                system(CLEAR_SCREEN);
                printf("Deseja continuar? Tecle (S/N) ");
                scanf(" %c", &entrada);      
                if(entrada!='S' && entrada!='N'){
                    system(CLEAR_SCREEN);
                    printf("Opcao invalida. Tecle (S/N) ");
                    scanf(" %c", &entrada);
                }
            }  
            system(CLEAR_SCREEN);
            printf("Parabens pelo seu desenpenho!\n");
            printf("Esta foi sua pontuacao: %dpts\n", dados.pontuacao);
            printf("Tecle <enter> para voltar ao MENU: ");
            
            SALVARANKING(&dados);

            char enter;
            getchar();
            scanf("%c", &enter);
        }
        // OPÇAO 2 (CONFIGURAÇOES)
        else if(opcao==2){
            system(CLEAR_SCREEN);
            MENUCONFIG();
        }
        // OPÇAO 3 (INSTRUÇOES)
        else if(opcao==3){
            INSTRUCOES();
        }
        // OPÇAO 4 (MOSTRAR RANKING)
        else if(opcao==4){
            MOSTRARRANKING();
        }
    }while(opcao!=5);
    // OPÇAO 5 (SAIR)
    if(opcao==5){
        fclose(fd);
        return 0;
    }
    return 0;

}
