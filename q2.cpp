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

        float calcSellingPrice() {
            double eSellPrice = this->bPrice;
            // // Approach 1:
            // for (auto &rec: this->infData) {
            //     if (this->sYear < 2024){
            //         if (rec.year > this->bYear && rec.year <= this->sYear)
            //             eSellPrice *= (1 + (rec.gPrices - rec.inf) / 100);
            //     }
            //     else {
            //         if (rec.year > this->bYear && rec.year <= this->sYear)
            //             eSellPrice *= (1 + (rec.gPrices) / 100);
            //     }
            // }

            // Approach 2:
            for (auto &rec: this->infData) {
                if (rec.year > this->bYear && rec.year <= this->sYear){
                    if (rec.year < 2024)
                        eSellPrice *= (1 + (rec.gPrices - rec.inf) / 100);
                    else
                        eSellPrice *= (1 + (rec.gPrices) / 100);
                }
            }
            return eSellPrice;
        }

        float calcProfit() {
            double sPrice = this->calcSellingPrice();
            return sPrice - this->bPrice;
        }

        float calcLTG() {
            double profit = this->calcProfit();
            return this->sYear < 2024 ? (profit <= 0 ? 0 : 0.2 * profit) : (profit <= 0 ? 0 : 0.125 * profit);
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