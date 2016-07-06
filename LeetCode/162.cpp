int findPeakElement(int* nums, int numsSize) {
	int i = 0, n, maxind = 0;
	int *p = nums;
	int max = *nums;
	for (n = 0; n<numsSize; n++, p++) {
		if (*p>max) {
			max = *p;
			maxind = n;
		}
	}

	return maxind;
}
