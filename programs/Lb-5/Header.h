
#pragma once

/*
void ShakerSort(int* A, int& n)
{
	int numOfCompare = 0;  //���-�� ���������
	int numOfReshuffle = 0; // ���-�� ������������

	bool isSorted = false;

	while (!isSorted)
	{
		isSorted = true;
		int leftMark = 0;
		int rightMark = n - 1;

		while (leftMark <= rightMark)
		{
			//numOfCompare++;//////////////////////////////////////////////
			for (int i = rightMark; i >= leftMark; i--)
			{
				numOfCompare++;
				if (A[i - 1] > A[i])
				{
					//numOfCompare++;
					swap(A[i - 1], A[i]);
					isSorted = false;
					numOfReshuffle++;
				}

			}
			leftMark++;

			for (int i = leftMark; i <= rightMark; i++)
			{
				numOfCompare++;
				if (A[i - 1] > A[i])
				{
					numOfCompare++;
					swap(A[i - 1], A[i]);
					isSorted = false;
					numOfReshuffle++;
				}

			}
			rightMark--;

		}
	}
	cout << "���-�� �������� ���������: " << numOfCompare << "\n";
	cout << "���-�� �������� ������������: " << numOfReshuffle << "\n";
}
*/