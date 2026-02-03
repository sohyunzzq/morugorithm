int BinarySearch(int left, int right, int target) {
	// lowerbound 찾기
	while (left < right) {
		int mid = (left + right) / 2;

		if (LIS[mid] < target)
			left = mid + 1;
		else
			right = mid;
	}

	return left;
}

void GetLIS() {
	LIS.push_back(arr[0].second);
	for (int i = 1; i < n; i++) {
		if (arr[i].second > LIS[LIS.size() - 1])
			LIS.push_back(arr[i].second);
		else {
			int tmp = BinarySearch(0, LIS.size() - 1, arr[i].second);
			LIS[tmp] = arr[i].second;
		}
	}
}
