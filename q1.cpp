#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;
int noOfEntry = 0; // initially count is 0

struct PriceInflation {
    int year;
    float gPrices;
    float inf;
};

class LongtermCapitalGainsTax {
    PriceInflation* infData;
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

        PriceInflation* loadData(string &filepath) {
            ifstream infCsv(filepath);
            string entry;
            PriceInflation records;
            while (getline(infCsv, entry))
                if (!entry.empty()) noOfEntry++;

            PriceInflation* datas = new PriceInflation[noOfEntry - 1];
            infCsv.clear();
            infCsv.seekg(0);
            getline(infCsv, entry);

            int idx = 0;
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

                datas[idx++] = records;
            }
            return datas;
        }

        float calcSellingPrice() {
            double eSellPrice = this->bPrice;
            for (int i = 0; i < noOfEntry; i++)
                if (infData[i].year > this->bYear && infData[i].year <= this->sYear)
                    eSellPrice *= (1 + (infData[i].gPrices - infData[i].inf) / 100);
                    
            return eSellPrice;
        }

        float calcProfit() {
            double sPrice = this->calcSellingPrice();
            return sPrice - this->bPrice;
        }

        float calcLTG() {
            double profit = this->calcProfit();
            return profit <= 0 ? 0 : 0.2 * profit;
        }
};

int main() {
    long bPrice, bYear, sYear;
    string filepath = "price-inflation.csv";
    cout << "Enter your Selling year (2010 - 2030): ";
    cin >> sYear;

    LongtermCapitalGainsTax ltcg = LongtermCapitalGainsTax(filepath, sYear);
    
    cout << "Selling Price at " << fixed << setprecision(2) << sYear << " is " << ltcg.calcSellingPrice() << endl;
    cout << "LTCG Tax at " << fixed << setprecision(2) << sYear << " is " << ltcg.calcLTG() << endl;

    return 0;
}