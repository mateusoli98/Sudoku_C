#include <stdio.h>
#include<locale.h>
#include <windows.h>
#define N 9
#define indiceVet 81

void mostraRegras(){
    printf("SISTEMA DO JOGO:\n\nSudoku e jogado numa malha de 9x9 quadrados, dividida em sub-malhas de 3x3 quadrados, chamada 'quadrantes' \n*Sudoku inicia com alguns dos quadrados ja preenchidos com numeros \n*O objetivo do Sudoku e preencher os quadrados vazios com números entre 1 e 9 (apenas um numero em cada quadrado) \nDe acordo com o seguinte regras:\n");
    printf("\n1. Numero pode aparecer apenas uma vez em cada linha \n2. Numero pode aparecer apenas uma vez em cada coluna\n3. Numero pode aparecer apenas uma vez em cada quadrante");
    printf("\n\n*Resumindo: um numero pode aparecer apenas uma vez na linha, na coluna ou no quadrante.\n\n");
    printf("\nSISTEMA DE PONTUAÇÃO: \n\nAcertos vale +2 pontos : Erros vale -1 ponto\nExistem também um sistema de avaliação: Pontuação >20 = Excelente! :  Pontuação >0 e <=20 = Bom! :  Pontuação <=0 = Pessímo!");
    printf("\n\nÉ isso aí. Agora você está preparado para resolver enigmas Sudoku!");
}

//Popula matriz com numeros aleatorios entre 1 a 9
void populaTabuleiro(int tab[N][N])
{
    srand(time(NULL));
    int i,j;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            if (tab[i][j] == 0)
                tab[i][j] = 1 + rand()%9;
}

//Verifica numeros aleatorios repetidos, se tiver colocar no lugar do msm
void verificaAleatorio(int tab[N][N])
{
    int i,j,k,cont=0;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            for (k = 0; k < N; k++)
            {
                if(tab[i][j] == tab[k][j])
                {
                    ++cont;
                    if(cont>1)
                    {
                        tab[i][j]=0;
                        cont=0;
                    }
                }
            }
        }
    }
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            for (k = 0; k < N; k++)
            {
                if(tab[i][j] == tab[i][k])
                {
                    ++cont;
                    if(cont>1)
                    {
                        tab[i][j]=0;
                        cont=0;
                    }
                }
            }
        }
    }
}

//Conta a qnt de nums no tabuleiro
int qtdNumTab(int tab[N][N])
{
    int i,j,contElementos=0;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            if(tab[i][j] != 0)
                contElementos++;
    return contElementos;
}

//Ve o nivel e forca nums de elementos no tabuleiro
void nivelJogo(int lvl,int tab[N][N])
{
    int qtdElemento = qtdNumTab(tab);
    if(lvl == 1)
    {
        while(qtdElemento < 20)
        {
            populaTabuleiro(tab);
            verificaAleatorio(tab);
            todosQuadrantes(tab);
            qtdElemento = qtdNumTab(tab);
        }
    }
    else if(lvl == 2)
    {
        while(qtdElemento != 15)
        {
            populaTabuleiro(tab);
            verificaAleatorio(tab);
            todosQuadrantes(tab);
            qtdElemento = qtdNumTab(tab);
        }
    }
    else if(lvl == 3)
    {
        populaTabuleiro(tab);
        verificaAleatorio(tab);
        todosQuadrantes(tab);
    }
}

//Mostra a matriz
void mostraTabuleiroAtualizado(int tab[N][N])
{
    int i,j;
    system("cls");
    printf("    0  1  2   3  4  5   6  7  8  \n");
    printf("  +---------+---------+---------+\n");
    for (i = 0; i < N; i++)
    {
        printf("%d |",i);
        for (j = 0; j < N; j++)
        {
            if (tab[i][j] != 0)
                printf(" %d ", tab[i][j]);
            else
                printf("   ");
            if (j % 3 == 2)
                printf("|");
        }
        if (i % 3 == 2)
            printf("\n  +---------+---------+---------+");
        printf("\n");
    }
}

//Metodo pontuacao
void pontuacao(int p, int *pontos)
{
    if(p == 1){
        *pontos+=2;
    }else *pontos-=1;
}

void avaliacao(int pontoFinal){
    if(pontoFinal > 10){
        printf("\nSua avaliação final: Excelente!");
    }else if(pontoFinal >0 && pontoFinal <=10){
        printf("\nSua avaliação final: Bom!");
    }else if(pontoFinal <=0){
        printf("\nSua avaliação final: Pessimo!");
    }
}

//Verifica coluna
int verificaCol(int *coluna, int *numero,int tab[N][N])
{
    int retorno=0, i;
    for(i=0; i<9; i++)
    {
        if(tab[i][*coluna] == *numero)
        {
            retorno = 1;
        }
    }
    return retorno;
}

//Verifica linha
int verificaLin(int *linha, int *numero,int tab[N][N])
{
    int retorno=0, i;
    for(i=0; i<9; i++)
    {
        if(tab[*linha][i] == *numero)
        {
            retorno = 1;
        }
    }
    return retorno;
}

//Apresenta menuzin
void menuPrincipal()
{
    system("cls");
    printf("Bem-vindo ao Sudoku\n\n");
    printf("1-Iniciar Jogo \n2-Regras \n3-Sair");
}

//menu nivel
void menuNivel()
{
    printf("Escolha um nível:\n\n");
    printf("1 - Fácil\n");
    printf("2 - Difícil\n");
    printf("3 - Aleatório\n");
}

//Verifica se a col lin e valor ta correto
int dados(int linha, int coluna, int valor)
{
    int retorno=0;
    if((linha>=0 && linha<=9 ) && (coluna>=0 && coluna<=9 ) && (valor>=1 && valor<=9))
        retorno = 1;
    return retorno;
}

//verifica se o numero inserido tem no quadrante
int quadrante(int linha,int coluna,int numero, int tab[N][N])
{
    int x=0,y=0,cont=0;
    localizacaoTabuleiro(&linha,&coluna);
    for(x=linha; x<linha+3; x++)
    {
        for(y=coluna; y<coluna+3; y++)
        {
            if(tab[x][y] == numero)
            {
                return 1;
            }
        }
    }
    return 0;
}

//verifica se tem elemento repetido no quadrante, se tiver coloca zero na posicao
void todosQuadrantes(int tab[N][N])
{
    int i,j,k,l,m,n,quadLin=0,quadCol=0,aux=0;
    while(quadLin <= 9)
    {
        while(quadCol <= 9)
        {
            m = quadLin;
            n = quadCol;

            localizacaoTabuleiro(&m,&n);
            for(i=m; i<m+3; i++)
            {
                for(j=n; j<n+3; j++)
                {
                    for(k=m; k<m+3; k++)
                    {
                        for(l=n; l<n+3; l++)
                        {
                            if(tab[i][j] == tab[k][l])
                                aux++;
                            if(aux > 1)
                                tab[i][j] = 0;
                        }
                    }
                    aux=0;
                }
            }
            quadCol+=3;
        }
        quadLin+=3;
        quadCol=0;
    }
}

//localiza coordenada no tabuleiro
void localizacaoTabuleiro(int *a, int *b)
{
    if(*a < 3)
    {
        *a=0;
    }
    else if(*a < 6)
    {
        *a=3;
    }
    else
    {
        *a=6;
    }

    if(*b <3)
    {
        *b=0;
    }
    else if(*b< 6)
    {
        *b=3;
    }
    else
    {
        *b=6;
    }
}

//limpa as variaveis
void limpaVar(int *coluna, int *linha, int *valor)
{
    *coluna = 0;
    *linha = 0;
    *valor = 0;
}

void pegaLinhaVet(int tab[N][N], int vet1[indiceVet])
{
    int i,j,flag=0;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if(tab[i][j] != 0)
            {
                vet1[flag] = i;
                flag++;
            }
        }
    }
}

void pegaColunaVet(int tab[N][N], int vet2[indiceVet])
{
    int i=0,j=0,flag=0;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if(tab[i][j] != 0)
            {
                vet2[flag] = j;
                flag++;
            }
        }
    }
}

int verificaElemento(int tab[N][N],int vet1[indiceVet], int vet2[indiceVet], int *linha, int *coluna)
{
    int i=0, retorno=0, qtdElementos = qtdNumTab(tab);
    while(i<qtdElementos)
    {
        if(vet1[i] == *linha && vet2[i] == *coluna)
        {
            retorno = 1;
        }
        i++;
    }
    return retorno;
}

int main()
{
    setlocale(LC_ALL,"portuguese");
    int pontos=0, run=1,jogadas=1,run2=1,nivel,linha,coluna,valor,recomecar,opcao,vet1[indiceVet],vet2[indiceVet];

    int tab[N][N] = {{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    while(run2)
    {
        populaTabuleiro(tab);
        verificaAleatorio(tab);

        menuPrincipal();
        printf("\n");
        scanf("%d", &opcao);
        system("cls");
        switch(opcao)
        {
        case 1:

            while(run)
            {
                menuNivel();
                scanf("%d",&nivel);
                if(nivel >= 1 && nivel <=3)
                {
                    system("cls");
                    printf("\nAGUARDE!!!\nSeu jogo já vai começar.\n\n");

                    nivelJogo(nivel,tab);
                    mostraTabuleiroAtualizado(tab);
                    pegaLinhaVet(tab, vet1);
                    pegaColunaVet(tab, vet2);

                    while(jogadas)
                    {
                        printf("\nLinha: ");
                        scanf("%d",&linha);
                        printf("Coluna: ");
                        scanf("%d",&coluna);
                        printf("Número: ");
                        scanf("%d",&valor);
                        if(dados(linha,coluna,valor) == 1)
                        {
                            if(verificaElemento(tab,vet1,vet2,&linha,&coluna) == 0)
                            {
                                if(verificaCol(&coluna, &valor, tab) == 0)
                                {
                                    if(verificaLin(&linha, &valor, tab) == 0)
                                    {
                                        if(quadrante(linha,coluna,valor,tab) == 0)
                                        {
                                            tab[linha][coluna] = valor;
                                            mostraTabuleiroAtualizado(tab);
                                            pontuacao(1,&pontos);
                                            limpaVar(&coluna, &linha, &valor);
                                            printf("\nJogo completado em %d%%\n",qtdNumTab(tab));
                                            if(qtdNumTab(tab) == 81)
                                            {
                                                run=0;
                                                jogadas=0;
                                            }
                                        }
                                        else
                                        {
                                            pontuacao(0,&pontos);
                                            printf("\n%d já está contido no quadrante!\n",valor);
                                            limpaVar(&coluna, &linha, &valor);
                                        }

                                    }
                                    else
                                    {
                                        pontuacao(0,&pontos);
                                        printf("\n%d já contido na linha!\n",valor);
                                        limpaVar(&coluna, &linha, &valor);
                                    }

                                }
                                else
                                {
                                    pontuacao(0,&pontos);
                                    printf("\n%d já contido na coluna!\n",valor);
                                    limpaVar(&coluna, &linha, &valor);
                                }
                            }
                            else{
                                pontuacao(0,&pontos);
                                printf("\nImpossível inserir valor nessa posição!\n");
                                limpaVar(&coluna, &linha, &valor);
                            }

                        }
                        else
                        {
                            printf("\nInforme valores corretos!\n");
                            limpaVar(&coluna, &linha, &valor);
                        }
                    }
                }
                else
                {
                    printf("\nInsira o nível corretamente\n"); system("cls");
                }
            }

            mostraTabuleiroAtualizado(tab);
            printf("\n\nParebéns! Você concluiu o jogo.");
            printf("\nPontuação final: %d",pontos);
            avaliacao(pontos);

            printf("\nDeseja recomeçar? 1-SIM|2-NÃO");
            scanf("%d", &recomecar);

            if(recomecar == 1)
            {
                run2=1;
                run=1;
                jogadas=1;
                opcao = 1;
            }
            else
            {
                run2=0;
            }
            break;


        case 2:
            mostraRegras();
            printf("\n\n");
            system("pause");
            break;

        case 3:
            run2=0;
            break;

        default:
            printf("Escolha errada!");
        }

    }

    return 0;
}
