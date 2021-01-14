using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace GameOfLifeParalell
{
    class Program
    {
        static void Main(string[] args)
        {
            int[,] grid = new int[,]
                                    {
                                        { 1, 0, 0, 0, 0, 0, 0, 0, 1, 1,},
                                        { 0, 0, 1, 0, 0, 1, 0, 0, 0, 0,},
                                        { 0, 1, 1, 0, 1, 1, 1, 0, 0, 0,},
                                        { 0, 1, 0, 0, 0, 1, 0, 0, 0, 0,},
                                        { 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,},
                                        { 0, 0, 0, 0, 1, 0, 0, 0, 1, 1,},
                                        { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,},
                                        { 1, 1, 0, 0, 1, 0, 0, 0, 0, 0,},
                                    };

            Grid lifeGrid = new Grid(grid);
            Console.WriteLine("Generation number 0");
            lifeGrid.PrintMatrix();
            Console.WriteLine();

            Thread myThread = new System.Threading.Thread(delegate ()
            {
                //program stops, when all cells are died
                while (lifeGrid.AliveCells() > 0)
                {
                    Console.WriteLine("Generation number {0}", lifeGrid.generationCount);
                    lifeGrid.CalculateNextGeneration();
                    lifeGrid.PrintMatrix();
                    Console.WriteLine();
                    //stop condition - all died (cells have zero value)
                    if (lifeGrid.AliveCells() == 0)
                    {
                        Console.WriteLine("Generation died!");
                        Console.ReadLine();
                        break;
                    }
                    Console.WriteLine("----------------------");
                }
            });
            myThread.Start();
        }
    }
    class Grid
    {
        /// <summary>
        /// Counter of generations for printing in console
        /// </summary>
        public int generationCount;
        /// <summary>
        /// Width of grid
        /// </summary>
        int widthMatrix;
        /// <summary>
        /// Height of grid
        /// </summary>
        int heightMatrix;
        /// <summary>
        /// Matrix for storing current generation
        /// </summary>
        int[,] currentgeneration;
        /// <summary>
        /// Matrix for storing last generation
        /// </summary>
        int[,] lastGeneration;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="newGrid">Base matrix - generation number 0</param>
        public Grid(int[,] newGrid)
        {
            currentgeneration = (int[,])newGrid.Clone();
            generationCount = 1;
            widthMatrix = currentgeneration.GetLength(1);
            heightMatrix = currentgeneration.GetLength(0);
            lastGeneration = new int[heightMatrix, widthMatrix];
        }

        /// <summary>
        /// Count all ALIVE neighbours in all directions in matrix of given cell
        /// </summary>
        /// <param name="x">X coordinates in grid of given cell</param>
        /// <param name="y">Y coordinates in grid of given cell</param>
        /// <returns>Count of all alive neighbours</returns>
        private int AliveNeighbours(int x, int y)
        {
            int count = 0;

            // Check for x - 1, y - 1
            if (x > 0 && y > 0)
            {
                if (currentgeneration[y - 1, x - 1] == 1)
                    count++;
            }

            // Check for x, y - 1
            if (y > 0)
            {
                if (currentgeneration[y - 1, x] == 1)
                    count++;
            }

            // Check for x + 1, y - 1
            if (x < widthMatrix - 1 && y > 0)
            {
                if (currentgeneration[y - 1, x + 1] == 1)
                    count++;
            }

            // Check for x - 1, y
            if (x > 0)
            {
                if (currentgeneration[y, x - 1] == 1)
                    count++;
            }

            // Check for x + 1, y
            if (x < widthMatrix - 1)
            {
                if (currentgeneration[y, x + 1] == 1)
                    count++;
            }

            // Check for x - 1, y + 1
            if (x > 0 && y < heightMatrix - 1)
            {
                if (currentgeneration[y + 1, x - 1] == 1)
                    count++;
            }

            // Check for x, y + 1
            if (y < heightMatrix - 1)
            {
                if (currentgeneration[y + 1, x] == 1)
                    count++;
            }

            // Check for x + 1, y + 1
            if (x < widthMatrix - 1 && y < heightMatrix - 1)
            {
                if (currentgeneration[y + 1, x + 1] == 1)
                    count++;
            }
            return count;

            
        }

        /// <summary>
        /// Calculate next generation based on the count of alive neighbours with with 4 rules:
        /// -If a cell was alive and had one or no neighbours the cell died.
        /// -If a cell was alive and had two or three neighbours the cell would survive.
        /// -If a cell was alive and had four or more neighbours it would die.
        /// -If there was a dead cell that had exactly three neighbours a new cell would be born.
        /// </summary>
        public void CalculateNextGeneration()
        {
            int[,] nextGeneration = new int[heightMatrix, widthMatrix];
            lastGeneration = (int[,])currentgeneration.Clone();
            Parallel.For(0, heightMatrix, y =>
              {
                  Parallel.For(0, widthMatrix, x =>
                    {
                        if (AliveNeighbours(x, y) < 2)
                        {
                            nextGeneration[y, x] = 0;
                        }
                        else if (currentgeneration[y, x] == 1 && (AliveNeighbours(x, y) == 2 || AliveNeighbours(x, y) == 3))
                        {
                            nextGeneration[y, x] = 1;
                        }
                        else if (currentgeneration[y, x] == 0 && AliveNeighbours(x, y) == 3)
                        {
                            nextGeneration[y, x] = 1;
                        }
                        else
                        {
                            nextGeneration[y, x] = 0;
                        }

                    });
              });
            generationCount++;
            currentgeneration = (int[,])nextGeneration.Clone();
        }

        /// <summary>
        /// Prints each generation of matrix. 
        /// Alive cells with value 1 and dead cells with value 0.
        /// </summary>
        public void PrintMatrix()
        {
            for (int y = 0; y < heightMatrix; y++)
            {
                for (int x = 0; x < widthMatrix; x++)
                {
                    Console.Write("{0}", currentgeneration[y, x]);
                }
                Console.WriteLine();
            }
            Console.WriteLine();
        }

        /// <summary>
        /// Return count of alive cells-with value 1.
        /// </summary>
        /// <returns>Count of alive cells.</returns>
        public int AliveCells()
        {
            int count = 0;
            for (int y = 0; y < heightMatrix; y++)
                for (int x = 0; x < widthMatrix; x++)
                    if (currentgeneration[y, x] == 1)
                        count++;
            return count;
        }
    }
}
