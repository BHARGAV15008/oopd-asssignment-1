#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

struct PriceInflation {
    int year;
    float gPrices;
    float inf;
};

class LongtermCapitalGainsTax {
    vector <PriceInflation> infData;
    long bPrice;
    int sYear;
    int bYear;

    public:
        LongtermCapitalGainsTax(string &filepath, int sYear) {
            this->infData = loadData(filepath);
            this->bPrice = 5000000;
            this->sYear = sYear;
            this->bYear = 2010;
        }

        vector<PriceInflation> loadData(string &filepath) {
            ifstream infCsv(filepath);
            vector <PriceInflation> datas;
            string entry;
            PriceInflation records;
            getline(infCsv, entry);

            while (getline(infCsv, entry)) {
                stringstream ss(entry);
                string dt;
                string oItem;

                getline(ss, dt, ',');
                records.year = stoi(dt.substr(0, 4));

                getline(ss, oItem, ',');
                records.gPrices = stod(oItem);

                getline(ss, oItem, ',');
                records.inf = stod(oItem);

                datas.push_back(records);
            }
            return datas;
        }

};

int main() {
    long bPrice, bYear, sYear;
    string filepath = "price-inflation.csv";
    cout << "Enter your Selling year (2010 - 2030): ";
    cin >> sYear;

    LongtermCapitalGainsTax ltcg = LongtermCapitalGainsTax(filepath, sYear);
    
    return 0;
}