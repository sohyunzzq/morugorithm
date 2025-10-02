int Find(int x) {
	// 내 조상이 나
	if (uf[x] == x)
		return x;

	// 타고타고 올라가서 조상을 찾고, 내 부모를 조상으로 갱신
	return uf[x] = Find(uf[x]);
}

void Union(int x, int y) {
	int X = Find(x);
	int Y = Find(y);

	uf[X] = Y;
}
