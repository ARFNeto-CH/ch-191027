#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include	"memory.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include    "malloc.h"

// constantes so para ficar mais facil de ler

#define		CAPACIDADE	 20

#define		SEM_CLIENTE	 -2
#define		ATENDE		'A'
#define		LISTA		'L'
#define		LIVRE		'-'
#define		NORMAL		'N'
#define		PRIORIDADE  'P'


struct cadastro
{
	char		nome[50];
	char		prioridade;
	char		normal;
	char		pri;

	int			senha;
	int			posicao_na_fila;

};
typedef struct cadastro		Cadastro;

Cadastro	cad[CAPACIDADE];		// cada elemento e a fila

char		fila[CAPACIDADE];		// representa as filas
int			q_fila_normal;			// na fila normal
int			q_fila_prioridade;		// na fila prioridade
int			q_fila;					// todo mundo que esta na fila

int			ja_atendidos;			// ajuda a testar
int			ultimas_senhas[5];		// o painel :) superfluo tambem


// prototipos das funcoes
int		ciclo(char servico);
int		inicia_trabalhos();
int		lista();
int		marca_senha_painel(int);
int		move_a_fila(int);
int		pega_senha(int);

// end fila-1.h