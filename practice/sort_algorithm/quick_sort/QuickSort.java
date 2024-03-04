public class QuickSort
{
	private static void sort(Comparable[] a)
	{
		StdRandom.shuffle(a);
		sort(a, 0, a.length - 1);
	}

	private static void sort(Comparable[] a, int lo, int hi)
	{
		if(lo >= hi) return;
		int p = partition(a, lo, hi);
		sort(a, lo, p - 1);
		sort(a, p + 1, hi);
		assert isSorted(a);
	}

	private static int partition(Comparable[] a, int lo, int hi)
	{
		int i = lo;
		int j = hi + 1;
		Comparable v = a[lo];
		while(true)
		{
			while(less(a[++i], v))
				if(i == hi) break;
			while(less(v, a[--j]))
				if(j == lo) break;
			if(i >= j) break;

			exch(a, i, j);
		}

		exch(a, lo, j);
		return j;
	}

	private static boolean isSorted(Comparable[] a)
	{
		return isSorted(a, 0, a.length);
	}

	private static boolean isSorted(Comparable[] a, int lo, int hi)
	{
		for(int i = lo + 1; i < hi; i++)
			if(less(a[i], a[i - 1])) return false;
		return true;
	}

	private static void exch(Object[] a, int x, int y)
	{
		Object temp = a[x];
		a[x] = a[y];
		a[y] = temp;
	}

	private static boolean less(Comparable x, Comparable y)
	{
		return (x.compareTo(y) < 0);
	}
	
	private static void show(Comparable[] a)
	{
		for(Comparable i : a)
		{
			StdOut.println(i);
		}
	}

	private static Comparable select(Comparable[] a, int k)
	{
		if(k < 0 || k >= a.length)
			throw new RuntimeException("out of boundary!");
		int lo = 0;
		int hi = a.length - 1;
		StdRandom.shuffle(a);
		
		while(hi > lo)
		{
			int p = partition(a, lo, hi);
			if(k > p) lo = p + 1;
			else if(k < p) hi = p - 1;
			else return a[p];
		}
		return a[lo];
	}

	public static void main(String[]args)
	{
		String[] a = StdIn.readStrings();
		QuickSort.sort(a);
		QuickSort.show(a);

		StdOut.println();

		for(int i = 0; i < a.length; i++)
		{
			StdOut.println((String)(QuickSort.select(a, i)));
		}
	}
}