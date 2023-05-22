/*
nome: Yann Soares Guimarães da Silva
Data:24/05/2023
Curso: Ciências da computação
*/

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <ctype.h>

enum Titulacao {
    ESPECIALISTA ,
    MESTRE,
    DOUTOR
};
// Define uma enumera��o para representar os diferentes n�veis de titula��o de professor 

struct Professor {
    char nome[30];
    int funcional;
    enum Titulacao titulacao;
};

struct Estudante {
    char nome[30];
    int matricula;
    int idade;
    int disciplina_cursando;
};

struct Disciplina {
    char nome[30];
    char codigo[10];
    int carga_horaria;
    struct Professor professor_responsavel;
    struct Estudante alunos[10];
    int total_alunos;
};

int le_valida_idade();
int le_valida_titulacao();
int le_valida_professor();
void ordena_estudantes_idade(struct Estudante estudantes[], int total_estudantes, int ordem);
void arruma_nome(char *nome);
//prototipa��o
int main() {
    setlocale(LC_ALL, "");

    struct Professor professores[3];
    struct Disciplina disciplinas[2];
    struct Estudante estudantes[15];
    int total_estudantes = 0;
    int i, j;

    printf("===== Sistema de Cadastro de Professores, Disciplinas e Estudantes =====\n\n");

    for (i = 0; i < 3; i++) {
        printf("=== Cadastro do Professor %d ===\n", i + 1);

        printf("Nome completo: ");
        fgets(professores[i].nome, sizeof(professores[i].nome), stdin);
        professores[i].nome[strcspn(professores[i].nome, "\n")] = '\0';
        arruma_nome(professores[i].nome);

        printf("Funcional: ");
        scanf("%d", &professores[i].funcional);
        getchar();

        professores[i].titulacao = le_valida_titulacao();

        system("cls");
    }

    for (i = 0; i < 2; i++) {
        system("cls");
        printf("=== Cadastro da Disciplina %d ===\n", i + 1);

        printf("Nome: ");
        fgets(disciplinas[i].nome, sizeof(disciplinas[i].nome), stdin);
        disciplinas[i].nome[strcspn(disciplinas[i].nome, "\n")] = '\0';
        arruma_nome(disciplinas[i].nome);

        printf("C�digo: ");
        fgets(disciplinas[i].codigo, sizeof(disciplinas[i].codigo), stdin);
        disciplinas[i].codigo[strcspn(disciplinas[i].codigo, "\n")] = '\0';

        printf("Carga Hor�ria: ");
        scanf("%d", &disciplinas[i].carga_horaria);
        getchar();

        printf("Professor Respons�vel (escolha um dos professores cadastrados):\n");
        for (j = 0; j < 3; j++) {
            printf("%d - %s (Funcional: %d)\n", j + 1, professores[j].nome, professores[j].funcional);
        }
        int escolha_professor;
        do {
            printf("Digite o n�mero correspondente ao professor: ");
            scanf("%d", &escolha_professor);
            getchar();
        } while (escolha_professor < 1 || escolha_professor > 3);

        disciplinas[i].professor_responsavel = professores[escolha_professor - 1];
        disciplinas[i].total_alunos = 0;
    }

    char opcao;
    do {
        system("cls");
        if (total_estudantes >= 15) {
            printf("Limite m�ximo de estudantes atingido.\n");
           system("pause");
             break;
        }

        printf("=== Cadastro do Estudante %d ===\n", total_estudantes + 1);

        printf("Nome completo: ");
        fgets(estudantes[total_estudantes].nome, sizeof(estudantes[total_estudantes].nome), stdin);
        estudantes[total_estudantes].nome[strcspn(estudantes[total_estudantes].nome, "\n")] = '\0';
        arruma_nome(estudantes[total_estudantes].nome);

        printf("Matr�cula: ");
        scanf("%d", &estudantes[total_estudantes].matricula);
        getchar();

        printf("Qual a disciplina que est� cursando:\n");
        for (j = 0; j < 2; j++) {
            printf("%d - %s (C�digo: %s)\n", j + 1, disciplinas[j].nome, disciplinas[j].codigo);
        }
        int escolha_disciplina;
        do {
            printf("Digite o n�mero correspondente � disciplina: ");
            scanf("%d", &escolha_disciplina);
            getchar();
        } while (escolha_disciplina < 1 || escolha_disciplina > 2);

        if (disciplinas[escolha_disciplina - 1].total_alunos >= 10) {
            printf("Limite m�ximo de estudantes para essa disciplina atingido.\n");
            system("pause");
            continue;
        }

        estudantes[total_estudantes].disciplina_cursando = escolha_disciplina - 1;

        estudantes[total_estudantes].idade = le_valida_idade();

        printf("Deseja adicionar outro estudante? (S/N): ");
        scanf(" %c", &opcao);
        getchar();

        disciplinas[escolha_disciplina - 1].alunos[disciplinas[escolha_disciplina - 1].total_alunos] = estudantes[total_estudantes];
        disciplinas[escolha_disciplina - 1].total_alunos++;
        total_estudantes++;
        
        
    } while (opcao == 'S' || opcao == 's');

    system("cls");
    printf("=== Relat�rio de Alunos Matriculados na Disciplina %s (C�digo: %s) ===\n", disciplinas[0].nome, disciplinas[0].codigo);
    printf("Professor Respons�vel: %s (Funcional: %d)\n", disciplinas[0].professor_responsavel.nome, disciplinas[0].professor_responsavel.funcional);
    printf("Carga Hor�ria: %d\n\n", disciplinas[0].carga_horaria);
    printf("Alunos: \n\n");

    ordena_estudantes_idade(disciplinas[0].alunos, disciplinas[0].total_alunos, 1);

    for (i = 0; i < disciplinas[0].total_alunos; i++) {
        printf("Nome: %s\n", disciplinas[0].alunos[i].nome);
        printf("Matr�cula: %d\n", disciplinas[0].alunos[i].matricula);
        printf("Idade: %d\n\n", disciplinas[0].alunos[i].idade);
    }

    printf("\n=== Relat�rio de Alunos Matriculados na Disciplina %s (C�digo: %s) ===\n", disciplinas[1].nome, disciplinas[1].codigo);
    printf("Professor Respons�vel: %s (Funcional: %d)\n", disciplinas[1].professor_responsavel.nome, disciplinas[1].professor_responsavel.funcional);
    printf("Carga Hor�ria: %d\n\n", disciplinas[1].carga_horaria);
    printf("Alunos: \n\n");

    ordena_estudantes_idade(disciplinas[1].alunos, disciplinas[1].total_alunos, 2);

    for (i = 0; i < disciplinas[1].total_alunos; i++) {
        printf("Nome: %s\n", disciplinas[1].alunos[i].nome);
        printf("Matr�cula: %d\n", disciplinas[1].alunos[i].matricula);
        printf("Idade: %d\n\n", disciplinas[1].alunos[i].idade);
    }

    return 0;
}

int le_valida_idade() {
    int idade;
    do {
        printf("Idade (Deve estar entre 16 e 26): ");
        scanf("%d", &idade);
        getchar();
        if (idade < 16 || idade > 26) {
            printf("Idade inv�lida. Digite uma idade entre 16 e 26.\n");
        }
    } while (idade < 16 || idade > 26);
    return idade;
}

int le_valida_titulacao() {
    int titulacao;
    do {
        printf("Titula��o (1 - Especialista, 2 - Mestre, 3 - Doutor): ");
        scanf("%d", &titulacao);
        getchar();
        if (titulacao < 1 || titulacao > 3) {
            printf("Op��o inv�lida. Digite uma op��o v�lida.\n");
        }
    } while (titulacao < 1 || titulacao > 3);
    return titulacao;
}

int le_valida_professor() {
    int professor;
    do {
        printf("Digite o n�mero correspondente ao professor: ");
        scanf("%d", &professor);
        getchar();
        if (professor < 1 || professor > 3) {
            printf("Op��o inv�lida. Digite uma op��o v�lida.\n");
        }
    } while (professor < 1 || professor > 3);
    return professor;
}

void ordena_estudantes_idade(struct Estudante estudantes[], int total_estudantes, int ordem) {
    int i, j;
    struct Estudante temp;
    for (i = 0; i < total_estudantes - 1; i++) {
        for (j = 0; j < total_estudantes - i - 1; j++) {
            if (ordem == 1) {
                if (estudantes[j].idade > estudantes[j + 1].idade) {
                    temp = estudantes[j];
                    estudantes[j] = estudantes[j + 1];
                    estudantes[j + 1] = temp;
                }
            } else if (ordem == 2) {
                if (estudantes[j].idade < estudantes[j + 1].idade) {
                    temp = estudantes[j];
                    estudantes[j] = estudantes[j + 1];
                    estudantes[j + 1] = temp;
                }
            }
        }
    }
}

void arruma_nome(char *nome) {
    int i = 0;
    while (nome[i]) {
        if (i == 0 || nome[i - 1] == ' ') {
            nome[i] = toupper(nome[i]);
        } else {
            nome[i] = tolower(nome[i]);
        }
        i++;
    }
}

