{
    vector<PII>ans;
    int l = -1e9;
    int r = -1e9;
    for (auto a : qj) {
        if (a.first > r) {
            if (r != -1e9) {
                ans.push_back({ l,r });
            }
            l = a.first;
            r = a.second;
        }

        else if (a.second > r) {
            r = a.second;
        }

    }
    ans.push_back({ l,r });
}