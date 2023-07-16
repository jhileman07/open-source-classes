import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;
import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Percolation {
  private int[][] grid;
  private int openSites;
  private int virtualTop;
  private int virtualBottom;
  private WeightedQuickUnionUF uf;

  public Percolation(int n) {
    if (n <= 0) {
      throw new IllegalArgumentException("n must be greater than 0");
    }
    grid = new int[n][n];
    openSites = 0;
    virtualTop = 0;
    virtualBottom = n*n + 1;
    uf = new WeightedQuickUnionUF(n*n + 2);
    for (int i = 0; i < n; i++) {
      for (int j = i+1; j < n; j++) {
        // create n-by-n grid, with all sites blocked
        grid[i][j] = 0;
      }
    }
  }

  public void open(int row, int col) {
    if (row < 0 || row >= grid.length || col < 0 || col >= grid.length) {
      throw new IllegalArgumentException("row and col must be between 0 and n-1");
    }
    if (grid[row][col] == 0) {
      grid[row][col] = 1;
      openSites++;
      if (row == 0) {
        uf.union(virtualTop, row*grid.length + col + 1);
      }
      if (row == grid.length - 1) {
        uf.union(virtualBottom, row*grid.length + col + 1);
      }
      if (row > 0 && isOpen(row-1, col)) {
        uf.union(row*grid.length + col + 1, (row-1)*grid.length + col + 1);
      }
      if (row < grid.length - 1 && isOpen(row+1, col)) {
        uf.union(row*grid.length + col + 1, (row+1)*grid.length + col + 1);
      }
      if (col > 0 && isOpen(row, col-1)) {
        uf.union(row*grid.length + col + 1, row*grid.length + col);
      }
      if (col < grid.length - 1 && isOpen(row, col+1)) {
        uf.union(row*grid.length + col + 1, row*grid.length + col + 2);
      }
    }
  }

  public boolean isOpen(int row, int col) {
    if (row < 0 || row >= grid.length || col < 0 || col >= grid.length) {
      throw new IllegalArgumentException("row and col must be between 0 and n-1");
    }
    return grid[row][col] == 1;
  }

  public boolean isFull(int row, int col) {
    if (row < 0 || row >= grid.length || col < 0 || col >= grid.length) {
      throw new IllegalArgumentException("row and col must be between 0 and n-1");
    }
    return grid[row][col] == 0;
  }

  public int numberOfOpenSites() {
    return openSites;
  }

  public boolean percolates() {
    return uf.connected(virtualTop, virtualBottom);
  }
}
