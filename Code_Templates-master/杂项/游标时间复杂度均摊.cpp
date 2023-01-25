// ������  (tar[j] < src[i])������ (i,j) �Ը�����
ll getTotalSmallThan(int srcSize, ll *src, int tarSize, ll *tar) {
    sort(src, src + srcSize);
    sort(tar, tar + tarSize);
    int idx = 0, cnt = 0;
    ll ans = 0;
    for (int i = 0; i < srcSize; ++i) {
        for (; idx < tarSize && tar[idx] < src[i]; ++idx) {
            ++cnt;
        }
        ans += cnt;
    }
    return ans;
}


// ������  (tar[j] >= src[i])������ (i,j) �Ը�����
ll getTotalBiggerEqualThan(int srcSize, ll *src, int tarSize, ll *tar) {
    sort(src, src + srcSize);
    sort(tar, tar + tarSize);
    int idx = 0, cnt = 0;
    ll ans = 0;
    for (int i = 0; i < srcSize; ++i) {
        for (; idx < tarSize && tar[idx] < src[i]; ++idx) {
        }
        ans += (tarSize - idx);
        if (tarSize == idx) {
            break;
        }
    }
    return ans;
}
