/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sudoku_solver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlesdansembourg <marvin@42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 17:23:29 by charlesda         #+#    #+#             */
/*   Updated: 2021/05/16 18:26:01 by charlesda        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
 
#define N 9


void	green()
{
	printf("\033[0;32m");
}

void	blue()
{
	printf("\033[0;34m");
}

void	reset()
{
	printf("\033[0m");
}


void print(int grid[N][N], int old_grid[N][N], int l)
{
     for (int i = 0; i < N; i++)
      {
        for (int j = 0; j < N; j++)
		{
			if (j % 3 == 0 && j != 0)
			{
				blue();
				printf("| ");
				reset();
			}
			if (grid[i][j] == old_grid[i][j] && l == 1)
			{
				green();
				printf("%d ", grid[i][j]);
				reset();
			}
			else if (grid[i][j] > 0 && l == 0)
			{
				green();
				printf("%d ", grid[i][j]);
				reset();
			}
			else
        		printf("%d ", grid[i][j]);
		}
		if (i == 2 || i == 5)
		{
			blue();
			printf("\n---------------------");
			reset();
		}
        printf("\n");
    }
}
 
int isSafe(int grid[N][N], int row,
                       int col, int num)
{
    for (int x = 0; x <= 8; x++)
        if (grid[row][x] == num)
            return 0;
    for (int x = 0; x <= 8; x++)
        if (grid[x][col] == num)
            return 0;
    int startRow = row - row % 3,
                 startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j +
                          startCol] == num)
                return 0;
    return 1;
}

int solveSuduko(int grid[N][N], int row, int col)
{
     
    if (row == N - 1 && col == N)
        return 1;
    if (col == N)
    {
        row++;
        col = 0;
    }
    if (grid[row][col] > 0)
        return solveSuduko(grid, row, col + 1);
 
    for (int num = 1; num <= N; num++)
    {
         
        if (isSafe(grid, row, col, num)==1)
        {
            grid[row][col] = num;
            if (solveSuduko(grid, row, col + 1)==1)
                return 1;
        }
        grid[row][col] = 0;
    }
    return 0;
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int parseSudoku(char *str, int grid[N][N], int grid_old[N][N])
{
	int	i;
	int col;
	int row;

	if (ft_strlen(str) != 81)
		return (0);

	col = 0;
	row = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		grid[row][col] = str[i] - 48;
		grid_old[row][col] = str[i] - 48;

		col++;
		if (col == N)
		{
			col = 0;
			row++;
		}
		i++;
	}
	return (1);
}

int main(int argc, char **argv)
{
	int grid_old[N][N] =  { { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
	
	int grid[N][N] =  { { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

	if (argc != 2)
	{
		printf("No arguments.");
		return (-1);
	}

	if (!parseSudoku(argv[1], grid, grid_old))
	{
		printf("Invalid sudoku.");
		return (0);
	}
	printf("\n\n");
	print(grid, grid_old, 0);
	printf("\n\n");
    if (solveSuduko(grid, 0, 0)==1)
	{
        print(grid, grid_old, 1);
		printf("\n\n");
	}
    else
        printf("No solution exists");
    return (1);
}
