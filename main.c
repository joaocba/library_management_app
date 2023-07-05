/*
Curso: TeSP Tecnologias e Programaçao de Sistemas de Informação
Unidade Curricular: Programação II
Docente: Professor Douturando Marco Tereso


Titulo de Trabalho: Programa de Gestão de uma Biblioteca

Aluno/Autores: Daniel Pereira (Nº:22108213), João Bacalhau (Nº:21706449)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>



/* ## PROTOTIPOS DE FUNCOES ## */
void menuInicio(char *mensagem_estado);
void adicionarLivro();
void removerLivro();
void mostrarLivros();
void registarLeitor();
void removerLeitor();
void mostrarLeitores();
void criarRequisicao();
void mostrarRequisicoes();
void fecharRequisicao();
void gerarCB(char *titulo_cb); //FUNC. GERAR CABECALHO



/* ## DADOS GLOBAIS ## */
FILE *f_livros, *f_leitores, *f_requisicoes; //PONTEIROS PARA FICHEIROS



/* ## ESTRUTURAS ## */
//ST LIVRO
struct st_livro {
	char titulo[150];
	char id[150];
};
struct st_livro livro;


//ST LEITOR
struct st_leitor {
	char nome[150];
	char id[150];
};
struct st_leitor leitor;


//ST REQUISICAO
struct st_requisicao {
	char leitor_id[150];
	char livro_id[150];
	char id[150];
};
struct st_requisicao requisicao;



/* ## PROGRAMA PRINCIPAL ## */
int main()
{
    setlocale(LC_ALL, "Portuguese");
	menuInicio("");
	return 0;
}




/* ## FUNCOES ## */
//MENU
void menuInicio(char* mensagem_estado)
{
    //GERAR CABECALHO
	gerarCB("");

	//APRESENTACAO DE OPCOES
	printf("|------------------------------|");
    printf("\n| ##### BIBLIO GEST MENU ##### |");
    printf("\n|------------------------------|");
    printf("\n|          > Livros <          |");
    printf("\n|------------------------------|");
    printf("\n| 1: Adicionar Livro           |");
    printf("\n| 2: Remover Livro             |");
    printf("\n| 3: Mostrar Livros            |");
    printf("\n|------------------------------|");
    printf("\n|         > Leitores <         |");
    printf("\n|------------------------------|");
    printf("\n| 4: Registar Leitor           |");
    printf("\n| 5: Remover Leitor            |");
    printf("\n| 6: Mostrar Leitores          |");
    printf("\n|------------------------------|");
    printf("\n|        > Requisicoes <       |");
    printf("\n|------------------------------|");
    printf("\n| 7: Criar Requisicao          |");
    printf("\n| 8: Fechar Requisicao         |");
    printf("\n| 9: Mostrar Requisicoes       |");
    printf("\n|------------------------------|");
    printf("\n| 0: Sair                      |");
	printf("\n|------------------------------|");
	printf("\n\n %s\n", mensagem_estado);
	printf("\n Escolha uma opcao: ");


    //GERAR MENU
    gerar_menu_inicio:
        switch (getch()) {
        case '1':
            adicionarLivro();
            break;
        case '2':
            (f_livros = fopen("livros.txt", "r")) == NULL ? menuInicio("Nenhum livro registado") : removerLivro();
            break;
        case '3':
            (f_livros = fopen("livros.txt", "r")) == NULL ? menuInicio("Nenhum livro registado") : mostrarLivros();
            break;
        case '4':
            registarLeitor();
            break;
        case '5':
            (f_leitores = fopen("leitores.txt", "r")) == NULL ? menuInicio("Nenhum leitor registado") : removerLeitor();
            break;
        case '6':
            (f_leitores = fopen("leitores.txt", "r")) == NULL ? menuInicio("Nenhum leitor registado") : mostrarLeitores();
            break;
        case '7':
            (f_leitores = fopen("leitores.txt", "r")) == NULL ? menuInicio("Nenhum leitor registado") : (f_livros = fopen("livros.txt", "r")) == NULL ? menuInicio("Nenhum livro registado") : criarRequisicao();
            break;
        case '8':
            (f_requisicoes = fopen("requisicoes.txt", "r")) == NULL ? menuInicio("Nenhuma requisicao registada") : fecharRequisicao();
            break;
        case '9':
            (f_requisicoes = fopen("requisicoes.txt", "r")) == NULL ? menuInicio("Nenhuma requisicao registada") : mostrarRequisicoes();
            break;
        case '0':
            exit(0);
            break;
        default:
            //VOLTAR A GERAR MENU
            goto gerar_menu_inicio;
        }
}



//ADICIONAR LIVRO
void adicionarLivro()
{
	gerarCB("|------------------------------|\n|      > Adicionar Livro <     |\n|------------------------------|\n\n");

	//INSERIR DADOS
	printf("\n - Titulo do livro: ");
	fflush(stdin); //FFLUSH(STDIN) - LIMPA OS DADOS DO BUFFER JUNTAMENTE COM O ESPACAMENTO
	scanf("%[^\n]", livro.titulo); //ESCREVE EM MEMORIA O TITULO DO LIVRO
	printf("\n - ID do livro: ");
	fflush(stdin);
	scanf("%[^\n]", livro.id); //ESCREVE EM MEMORIA O ID DO LIVRO

	//MOSTRAR DADOS A CONFIRMAR
	gerarCB("|------------------------------|\n|      > Adicionar Livro <     |\n|------------------------------|\n\n");
	printf("\n - Titulo: %s", &livro.titulo);
	printf("\n - ID: %s", &livro.id);
	printf("\n\n\n Pretende adicionar o livro com os dados apresentados?\n <S> Sim  <N> Nao ");
	printf("\n\n Escolha uma opcao: ");

	//CONFIRMAR DADOS
    confirmacao_adicionar_livro:
        switch (tolower(getch())) { //TOLOWER() - CONVERTER MAIUSCULAS EM MINUSCULAS
        case 's':
            fprintf(f_livros = fopen("livros.txt", "a+"), "%s\n%s\n", &livro.titulo, &livro.id); //ESCREVE O TITULO E ID DO LIVRO NO FICHEIRO LIVROS.TXT
            fclose(f_livros); //ENCERRA O FICHEIRO LIVROS.TXT
            menuInicio("Livro adicionado com sucesso"); //MOSTRA MENSAGEM DE SUCESSO
            break;
        case 'n':
            menuInicio(""); //VOLTAR AO MENU
            break;
        default:
            goto confirmacao_adicionar_livro;
        }
}



//MOSTRAR LIVROS
void mostrarLivros()
{
	gerarCB("|------------------------------|\n|      > Mostrar Livros <      |\n|------------------------------|\n\n");

    //CONTADOR DE REGISTOS
	int contador = 0;

	//PROCURAR E APRESENTAR LIVROS
	printf(" ### Lista de Livros ###\n");
	while (!feof(f_livros)) { //ENQUANTO NAO CHEGAR AO FIM DO FICHEIRO
		fscanf(f_livros, "%[^\n]\n%[^\n]\n", &livro.titulo, &livro.id); //LER TITULO E ID DO LIVRO DO FICHEIRO LIVROS.TXT
		contador++; //INCREMENTA O CONTADOR DE REGISTOS
		printf("\n - Titulo: %s", &livro.titulo);
		printf("\n - ID: %s", &livro.id);
		printf("\n\n");
	}

	//MOSTRADOR DE LIVROS REGISTADOS
	printf("\n Total %d %s Registado(s)", contador, contador < 2 ? "Livro" : "Livros");
	printf("\n\n Pressione qualquer tecla para regressar ao Menu");
	getch(); //LER QUALQUER CARACTER INSERIDO
	fclose(f_livros);

	//APRESENTAR MENU_INICIO
	menuInicio("");
}



//REGISTAR LEITOR
void registarLeitor()
{
    gerarCB("|------------------------------|\n|      > Registar Leitor <     |\n|------------------------------|\n\n");

    //INSERIR DADOS
	printf("\n - Nome do leitor: ");
	fflush(stdin);
	scanf("%[^\n]", leitor.nome);
	printf("\n - ID do leitor: ");
	fflush(stdin);
	scanf("%[^\n]", leitor.id);

	//MOSTRAR DADOS A CONFIRMAR
	gerarCB("|------------------------------|\n|      > Registar Leitor <     |\n|------------------------------|\n\n");
	printf("\n - Nome: %s", &leitor.nome);
	printf("\n - ID: %s", &leitor.id);
	printf("\n\n\n Pretende adicionar o leitor com os dados apresentados?\n <S> Sim  <N> Nao ");
	printf("\n\n Escolha uma opcao: ");;

	//CONFIRMAR DADOS
    confirmacao_registar_leitor:
        switch (tolower(getch())) {
        case 's':
            fprintf(f_leitores = fopen("leitores.txt", "a+"), "%s\n%s\n", &leitor.nome, &leitor.id);
            fclose(f_leitores);
            menuInicio("Leitor adicionado com sucesso");
            break;
        case 'n':
            menuInicio("");
            break;
        default:
            goto confirmacao_registar_leitor;
        }
}



//MOSTRAR LEITORES
void mostrarLeitores()
{
	gerarCB("|------------------------------|\n|      > Mostrar Leitores <      |\n|------------------------------|\n\n");

	//CONTADOR DE REGISTOS
	int contador = 0;

	//PROCURAR E APRESENTAR LEITORES
	printf(" ### Lista de Leitores ###\n");
	while (!feof(f_leitores)) {
		fscanf(f_leitores, "%[^\n]\n%[^\n]\n", &leitor.nome, &leitor.id);
		contador++;
		printf("\n - Nome: %s", &leitor.nome);
		printf("\n - ID: %s", &leitor.id);
		printf("\n\n");
	}

	//MOSTRADOR DE LEITORES REGISTADOS
	printf("\n Total %d %s Registado(s)", contador, contador < 2 ? "Leitor" : "Leitores");
	printf("\n\n Pressione qualquer tecla para regressar ao Menu");
	getch();
	fclose(f_leitores);

	//APRESENTAR MENU_INICIO
	menuInicio("");
}



//REGISTAR REQUISICAO
void criarRequisicao()
{
    gerarCB("|------------------------------|\n|     > Criar Requisicao <     |\n|------------------------------|\n\n");

	//CONTADOR DE LIVROS E LEITORES
	int livro_encontrado = 0, leitor_encontrado = 0;
	char leitor_id[150], livro_id[150]; //VETORES PARA RETER OS DADOS INSERIDOS

	//PROCURAR LEITOR POR ID
	fflush(stdin);
	printf("\n - ID do leitor a registar: ");
	scanf("%[^\n]", leitor_id);
	fseek(f_leitores, 0, SEEK_END); //FSEEK() - DESLOCA A POSICAO DO PONTEIRO PARA UMA DETERMINADA POSICAO
	rewind(f_leitores); //REWIND() - DESLOCA A POSICAO DO PONTEIRO PARA O INICIO DO FICHEIRO, PERMITE REPLICAR DADOS

	//PROCURAR LEITORES ASSOCIADOS A REQUISICOES
	while (!feof(f_leitores)) {
		fscanf(f_leitores, "%[^\n]\n%[^\n]\n", &leitor.nome, &leitor.id);
		if (strcmp(leitor_id, leitor.id) == 0) { //STRCMP() - PERMITE COMPARAR STRINGS, AQUI COMPARA O "LEITOR.ID" COM O "LEITOR_ID"
			printf("\n - Leitor encontrado com o nome: %s (ID: %s)", &leitor.nome, &leitor_id);
			leitor_encontrado = 1;
			strcpy(requisicao.leitor_id, leitor.id); //STRCPY() - PERMITE COPIAR STRINGS AQUI COPIA O "LEITOR.ID" PARA "REQUISICAO.LEITOR_ID"
		}
	}

	//CASO NAO ENCONTRE O LEITOR TENTAR NOVAMENTE
	if (leitor_encontrado != 1) {
		printf("\n\n\n Nenhum leitor encontrado com o ID: %s", leitor_id);
		printf("\n <1> Nova Requisicao  <0> Regressar ao Menu\n\nEscolha uma opcao: ");
        tentativa_requisicao_leitor:
            switch (getch()) {
            case '1':
                criarRequisicao();
                break;
            case '0':
                menuInicio("");
                break;
            default:
                goto tentativa_requisicao_leitor;
            }
	}

	//PROCURAR LIVRO POR ID
	fflush(stdin);
	printf("\n\n - ID do livro a registar: ");
	scanf("%[^\n]", livro_id);
	fseek(f_livros, 0, SEEK_END);
	rewind(f_livros);

	//PROCURAR LIVROS ASSOCIADOS A REQUISICOES
	while (!feof(f_livros)) {
		fscanf(f_livros, "%[^\n]\n%[^\n]\n", &livro.titulo, &livro.id);
		if (strcmp(livro_id, livro.id) == 0) {
			printf("\n - Livro encontrado com o titulo: %s (ID: %s)\n\n", &livro.titulo, &livro_id);
			livro_encontrado = 1;
			strcpy(requisicao.livro_id, livro.id);
		}
	}

	//CASO NAO ENCONTRE O LIVRO TENTAR NOVAMENTE
	if (!livro_encontrado) {
		printf("\n\n\n Nenhum livro encontrado com o ID: %s", livro_id);
		printf("\n <1> Nova Requisicao  <0> Regressar ao Menu\n\nEscolha uma opcao: ");
        tentativa_requisicao_livro:
            switch (getch()) {
            case '1':
                criarRequisicao();
                break;
            case '0':
                fclose(f_leitores);
                fclose(f_livros);
                menuInicio("");
                break;
            default:
                goto tentativa_requisicao_livro;
            }
    }

    //CONFIRMAR REQUISICAO
	printf("\n\n Pretende criar a requisicao com os dados apresentados?\n <S> Sim  <N> Nao ");
	printf("\n\n Escolha uma opcao: ");;
    confirmacao_requisicao:
        switch (tolower(getch())) {
        case 's':
            fprintf(f_requisicoes = fopen("requisicoes.txt", "a+"), "%s\n%s\n%s%s\n", &requisicao.leitor_id, &requisicao.livro_id, &requisicao.leitor_id, &requisicao.livro_id);
            fclose(f_requisicoes);
            menuInicio("Requisicao registada com sucesso");
            break;
        case 'n':
            menuInicio("");
            break;
        default:
            goto confirmacao_requisicao;
        }
}



//MOSTRAR REQUISICOES
void mostrarRequisicoes()
{
	gerarCB("|------------------------------|\n|    > Mostrar Requisicoes <   |\n|------------------------------|\n\n");

    //CONTADOR DE REGISTOS
	int contador = 0;

	//FICHEIROS A LER
	f_livros = fopen("livros.txt", "r");
	f_leitores = fopen("leitores.txt", "r");

	//PROCURAR E APRESENTAR CADA REQUISICAO REGISTADA
	//LEITURA DE DADOS POR LINHA = %[^\n]
	printf(" ### Lista de Requisicoes ###\n");
	while (!feof(f_requisicoes)) {
		fscanf(f_requisicoes, "%[^\n]\n%[^\n]\n%[^\n]\n", &requisicao.leitor_id, &requisicao.livro_id, &requisicao.id);
        fseek(f_leitores, 0, SEEK_END);
        rewind(f_leitores);

        //PROCURAR E MOSTRAR LEITORES COM REQUISICOES REGISTADAS
        while (!feof(f_leitores)) {
            fscanf(f_leitores, "%[^\n]\n%[^\n]\n", &leitor.nome, &leitor.id);
            if (strcmp(requisicao.leitor_id, leitor.id) == 0) {
                printf("\n - Nome do leitor: %s (ID: %s)", &leitor.nome, &leitor.id);
            }
        }
        fseek(f_livros, 0, SEEK_END);
        rewind(f_livros);

        //PROCURAR E MOSTRAR LIVROS COM REQUISICOES REGISTADAS
        while (!feof(f_livros)) {
            fscanf(f_livros, "%[^\n]\n%[^\n]\n", &livro.titulo, &livro.id);
            if (strcmp(requisicao.livro_id, livro.id) == 0) {
                printf("\n - Titulo do livro: %s (ID: %s)\n\n", &livro.titulo, &livro.id);
            }
        }
        //printf("\n\n---------------------------------\n\n");
        contador++;
	}

	//MOSTRADOR DE REQUISICOES REGISTADAS
	printf("\n Total %d %s Registada(s)", contador, contador == 1 ? "Requisicao" : "Requisicoes");
	printf("\n\n Pressione qualquer tecla para regressar ao Menu");
	fclose(f_livros);
	fclose(f_leitores);
	fclose(f_requisicoes);
	getch();

	//APRESENTAR MENU_INICIO
	menuInicio("");
}



//FECHAR REQUISICAO
void fecharRequisicao()
{
	gerarCB("|------------------------------|\n|     > Fechar Requisicao <    |\n|------------------------------|\n\n");

	//GERAR NOVO FICHEIRO PARA COPIAR E REMOVER DADOS
	FILE *f_requisicoes_temp;

	//CONTADOR REGISTOS
	int r_encontrado = 0;

	//VETORES A PREENCHER DURANTE A LEITURA DO FICHEIRO TEMPORARIO
	char leitor_id[150], livro_id[150], requisicao_id[150];

	//LER ID LEITOR E ID LIVRO
	fflush(stdin);
	printf("\n - ID do leitor com requisicao: ");
	scanf("%[^\n]", leitor_id);
	fflush(stdin);
	printf("\n - ID do livro requisitado: ");
	scanf("%[^\n]", livro_id);

	//CONCATENAR AMBOS OS IDS PARA MOSTRAR REQUISICAO ASSOCIADA
	strcpy(requisicao_id, leitor_id);
	strcat(requisicao_id, livro_id);
	fseek(f_requisicoes, 0, SEEK_END);
	rewind(f_requisicoes);

	//PROCURAR POR ID LEITOR + ID LIVRO + ID REQUISICAO = REQUISICAO CORRETA
	while (!feof(f_requisicoes)) {
		fscanf(f_requisicoes, "%[^\n]\n%[^\n]\n%[^\n]\n", &requisicao.leitor_id, &requisicao.livro_id, &requisicao.id);
		if (strcmp(requisicao.id, requisicao_id) == 0) { //COMPARAR IDS
			r_encontrado = 1;
		}
	}

	//REQUISICAO ENCONTRADA COM SUCESSO
	if (r_encontrado == 1) {
		printf("\n\n Requisicao encontrada");
		printf("\n\n\n Pretende remover este livro?\n <S> Sim  <N> Nao ");
		printf("\n\n Escolha uma opcao: ");

		//ACOES APOS CONFIRMACAO DE REGISTO
        confirmacao_fechar_requisicao:
            switch (tolower(getch())) {
            case 's':
                fseek(f_requisicoes, 0, SEEK_END);
                rewind(f_requisicoes);
                f_requisicoes_temp = fopen("requisicoes_temp.txt", "a+"); //ABRIR FICHEIRO PARA DADOS TEMPORARIOS

                //ESCREVE DADOS ALTERADOS NO FICHEIRO
                while (!feof(f_requisicoes)) {
                    fscanf(f_requisicoes, "%[^\n]\n%[^\n]\n%[^\n]\n", &requisicao.leitor_id, &requisicao.livro_id, &requisicao.id);

                    if (strcmp(requisicao.id, requisicao_id) != 0) {
                        fprintf(f_requisicoes_temp, "%s\n%s\n%s\n", &requisicao.leitor_id, &requisicao.livro_id, &requisicao.id);
                    }
                }
                fclose(f_requisicoes);

                //APAGAR FICHEIROS
                remove("requisicoes.txt"); //APAGAR FICHEIRO REQUISICOES.TXT
                long savedOffset = ftell(f_requisicoes_temp); //FTELL() - DEVOLVE POSICAO ATUAL DO PONTEIRO
                fseek(f_requisicoes_temp, 0, SEEK_END);
                if (ftell(f_requisicoes_temp) == 0) { //SEM REQUISICOES REGISTADAS APAGAR O FICHEIRO REQUISICOES_TEMP.TXT
                    fclose(f_requisicoes_temp);
                    remove("requisicoes_temp.txt");
                }
                fclose(f_requisicoes_temp);

                //ALTERAR NOME DO FICHEIRO TEMPORARIO PARA O FICHEIRO REQUISICOES.TXT
                rename("requisicoes_temp.txt", "requisicoes.txt");
                menuInicio("Requisicao fechada com sucesso");
                break;
            case 'n':
                fclose(f_requisicoes);
                menuInicio("");
                break;
            default:
                goto confirmacao_fechar_requisicao;
            }
	}else{
	    //CASO NAO ENCONTRE O LIVRO PARA FECHAR REQUISICAO
		printf("\n\n\n Nenhum resultado encontrado");
		printf("\n <1> Fechar outra requisicao  <0> Regressar ao Menu");
		printf("\n\n Escolha uma opcao: ");
        tentativa_fechar_requisicao:
            switch (getch()) {
            case '1':
                fecharRequisicao();
                break;

            case '0':
                fclose(f_requisicoes);
                menuInicio("");
                break;

            default:
                goto tentativa_fechar_requisicao;
            }
	}
}



//REMOVER LIVRO
void removerLivro()
{
	gerarCB("|------------------------------|\n|      > Remover Livro <      |\n|------------------------------|\n\n");

	//GERAR NOVO FICHEIRO PARA COPIAR E REMOVER DADOS
	FILE *f_livros_temp;

	//CONTADOR REGISTOS
	int l_encontrado = 0;

	//VETORES A PREENCHER DURANTE A LEITURA DO FICHEIRO TEMPORARIO
	char livro_titulo[150], livro_id[150];

	//INSERIR ID LIVRO
	fflush(stdin);
	printf("\n - ID do livro a remover: ");
	scanf("%[^\n]", livro_id);

	//PROCURAR POR ID LIVRO
	while (!feof(f_livros)) {
		fscanf(f_livros, "%[^\n]\n%[^\n]\n", &livro.titulo, &livro.id);
		if (strcmp(livro.id, livro_id) == 0) { //COMPARAR IDS
			l_encontrado = 1;
		}
	}

	//LIVRO ENCONTRADO COM SUCESSO
	if (l_encontrado == 1) {
		printf("\n\n Livro Encontrado: %s (ID: %s)", &livro.titulo, &livro_id);
		printf("\n\n\n Pretende remover este livro?\n <S> Sim  <N> Nao ");
		printf("\n\n Escolha uma opcao: ");

		//ACOES APOS CONFIRMACAO DE REMOVER LIVRO
        confirmacao_remover_livro:
            switch (tolower(getch())) {
            case 's':
                fseek(f_livros, 0, SEEK_END);
                rewind(f_livros);
                f_livros_temp = fopen("livros_temp.txt", "a+"); //ABRIR FICHEIRO PARA DADOS TEMPORARIOS

                //ESCREVE DADOS ALTERADOS NO FICHEIRO
                while (!feof(f_livros)) {
                    fscanf(f_livros, "%[^\n]\n%[^\n]\n", &livro.titulo, &livro.id);

                    if (strcmp(livro.id, livro_id) != 0) {
                        fprintf(f_livros_temp, "%s\n%s\n", &livro.titulo, &livro.id);
                    }
                }
                fclose(f_livros);

                //APAGAR FICHEIROS
                remove("livros.txt"); //APAGAR FICHEIRO LIVROS.TXT
                long savedOffset = ftell(f_livros_temp); //FTELL() - DEVOLVE POSICAO ATUAL DO PONTEIRO
                fseek(f_livros_temp, 0, SEEK_END);
                if (ftell(f_livros_temp) == 0) { //SEM LIVROS REGISTADOS APAGAR O FICHEIRO LIVROS_TEMP.TXT
                    fclose(f_livros_temp);
                    remove("livros_temp.txt");
                }
                fclose(f_livros_temp);

                //ALTERAR NOME DO FICHEIRO TEMPORARIO PARA O FICHEIRO LIVROS.TXT
                rename("livros_temp.txt", "livros.txt");
                menuInicio("Livro removido com sucesso");
                break;
            case 'n':
                fclose(f_livros);
                menuInicio("");
                break;
            default:
                goto confirmacao_remover_livro;
            }
	}else{
	    //CASO NAO ENCONTRE O LIVRO PARA REMOVER
		printf("\n\n\n Nenhum resultado encontrado com o ID: %s", &livro_id);
		printf("\n <1> Remover outro livro  <0> Regressar ao Menu");
		printf("\n\n Escolha uma opcao: ");
        tentativa_remover_livro:
            switch (getch()) {
            case '1':
                removerLivro();
                break;

            case '0':
                fclose(f_livros);
                menuInicio("");
                break;

            default:
                goto tentativa_remover_livro;
            }
	}
}



//REMOVER LEITOR
void removerLeitor()
{
	gerarCB("|------------------------------|\n|       > Remover Leitor <      |\n|------------------------------|\n\n");

	//GERAR NOVO FICHEIRO PARA COPIAR E REMOVER DADOS
	FILE *f_leitores_temp;

	//CONTADOR REGISTOS
	int ltr_encontrado = 0;

	//VETORES A PREENCHER DURANTE A LEITURA DO FICHEIRO TEMPORARIO
	char leitor_nome[150], leitor_id[150];

	//INSERIR ID LEITOR
	fflush(stdin);
	printf("\n - ID do leitor a remover: ");
	scanf("%[^\n]", leitor_id);

	//PROCURAR POR ID LEITOR
	while (!feof(f_leitores)) {
		fscanf(f_leitores, "%[^\n]\n%[^\n]\n", &leitor.nome, &leitor.id);
		if (strcmp(leitor.id, leitor_id) == 0) { //COMPARAR IDS
			ltr_encontrado = 1;
		}
	}

	//LEITOR ENCONTRADO COM SUCESSO
	if (ltr_encontrado == 1) {
		printf("\n\n Leitor Encontrado: %s (ID: %s)", &leitor.nome, &leitor_id);
		printf("\n\n\n Pretende remover este leitor?\n <S> Sim  <N> Nao ");
		printf("\n\n Escolha uma opcao: ");

		//ACOES APOS CONFIRMACAO DE REMOVER LIVRO
        confirmacao_remover_leitor:
            switch (tolower(getch())) {
            case 's':
                fseek(f_leitores, 0, SEEK_END);
                rewind(f_leitores);
                f_leitores_temp = fopen("leitores_temp.txt", "a+"); //ABRIR FICHEIRO PARA DADOS TEMPORARIOS

                //ESCREVE DADOS ALTERADOS NO FICHEIRO
                while (!feof(f_leitores)) {
                    fscanf(f_leitores, "%[^\n]\n%[^\n]\n", &leitor.nome, &leitor.id);

                    if (strcmp(leitor.id, leitor_id) != 0) {
                        fprintf(f_leitores_temp, "%s\n%s\n", &leitor.nome, &leitor.id);
                    }
                }
                fclose(f_leitores);

                //APAGAR FICHEIROS
                remove("leitores.txt"); //APAGAR FICHEIRO LEITORES.TXT
                long savedOffset = ftell(f_leitores_temp); //FTELL() - DEVOLVE POSICAO ATUAL DO PONTEIRO
                fseek(f_leitores_temp, 0, SEEK_END);
                if (ftell(f_leitores_temp) == 0) { //SEM LEITORES REGISTADOS APAGAR O FICHEIRO LEITORES_TEMP.TXT
                    fclose(f_leitores_temp);
                    remove("leitores_temp.txt");
                }
                fclose(f_leitores_temp);

                //ALTERAR NOME DO FICHEIRO TEMPORARIO PARA O FICHEIRO LEITORES.TXT
                rename("leitores_temp.txt", "leitores.txt");
                menuInicio("Leitor removido com sucesso");
                break;
            case 'n':
                fclose(f_leitores);
                menuInicio("");
                break;
            default:
                goto confirmacao_remover_leitor;
            }
	}else{
	    //CASO NAO ENCONTRE O LEITOR PARA REMOVER
		printf("\n\n\n Nenhum resultado encontrado com o ID: %s", &leitor_id);
		printf("\n <1> Remover outro leitor  <0> Regressar ao Menu");
		printf("\n\n Escolha uma opcao: ");
        tentativa_remover_leitor:
            switch (getch()) {
            case '1':
                removerLeitor();
                break;

            case '0':
                fclose(f_leitores);
                menuInicio("");
                break;

            default:
                goto tentativa_remover_leitor;
            }
	}
}



//CABECALHO PARA APRESENTAR EM FUNCOES
void gerarCB(char *titulo_cb)
{
    //LIMPAR CONSOLA
	system("cls");
	printf("\n");

	//APRESENTAR TITULO DE CABECALHO
	printf(titulo_cb);
}
