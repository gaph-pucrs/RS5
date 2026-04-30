#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include <model.h>
#include <test.h>

int main()
{
    const int n = (sizeof(data)/sizeof(dataset_t));
    float sqerr = 0;
    for (int i = 0; i < n; i++) {
        uint8_t MSSubclass          = data[i].MSSubClass;
        float LotFrontage           = data[i].LotFrontage;
        uint16_t LotArea            = data[i].LotArea;
        uint8_t OverallQual         = data[i].OverallQual;
        uint8_t OverallCond         = data[i].OverallCond;
        uint8_t YearBuilt           = data[i].YearBuilt - OFFSET_YearBuilt;
        uint8_t YearRemodAdd        = data[i].YearRemodAdd - OFFSET_YearRemodAdd;
        float MasVnrArea            = data[i].MasVnrArea;
        uint16_t BsmtFinSF1         = data[i].BsmtFinSF1;
        uint16_t BsmtFinSF2         = data[i].BsmtFinSF2;
        uint16_t BsmtUnfSF          = data[i].BsmtUnfSF;
        uint16_t TotalBsmtSF        = data[i].TotalBsmtSF;
        uint16_t _1stFlrSF          = data[i]._1stFlrSF;
        uint16_t _2ndFlrSF          = data[i]._2ndFlrSF;
        uint16_t LowQualFinSF       = data[i].LowQualFinSF;
        uint16_t GrLivArea          = data[i].GrLivArea;
        uint8_t BsmtFullBath        = data[i].BsmtFullBath;
        uint8_t BsmtHalfBath        = data[i].BsmtHalfBath;
        uint8_t FullBath            = data[i].FullBath;
        uint8_t HalfBath            = data[i].HalfBath;
        uint8_t BedroomAbvGr        = data[i].BedroomAbvGr;
        uint8_t KitchenAbvGr        = data[i].KitchenAbvGr;
        uint8_t TotRmsAbvGrd        = data[i].TotRmsAbvGrd;
        uint8_t Fireplaces          = data[i].Fireplaces;
        float GarageYrBlt           = data[i].GarageYrBlt;
        uint8_t GarageCars          = data[i].GarageCars;
        uint16_t GarageArea         = data[i].GarageArea;
        uint16_t WoodDeckSF         = data[i].WoodDeckSF;
        uint16_t OpenPorchSF        = data[i].OpenPorchSF;
        uint8_t EnclosedPorch       = data[i].EnclosedPorch;
        uint8_t _3SsnPorch          = data[i]._3SsnPorch;
        uint8_t ScreenPorch         = data[i].ScreenPorch;
        uint8_t PoolArea            = data[i].PoolArea - OFFSET_PoolArea;
        uint16_t MiscVal            = data[i].MiscVal;
        uint8_t MoSold              = data[i].MoSold;
        uint8_t YrSold              = data[i].YrSold - OFFSET_YrSold;
        float n_bathrooms           = data[i].n_bathrooms;
        uint16_t area_with_basement = data[i].area_with_basement;

        float value = model(
            &MSSubclass,
            data[i].LotFrontage        != -1 ? &LotFrontage        : NULL,
            &LotArea,
            &OverallQual,
            &OverallCond,
            &YearBuilt,
            &YearRemodAdd,
            data[i].MasVnrArea         != -1 ? &MasVnrArea         : NULL,
            data[i].BsmtFinSF1         != -1 ? &BsmtFinSF1         : NULL,
            data[i].BsmtFinSF2         != -1 ? &BsmtFinSF2         : NULL,
            data[i].BsmtUnfSF          != -1 ? &BsmtUnfSF          : NULL,
            data[i].TotalBsmtSF        != -1 ? &TotalBsmtSF        : NULL,
            &_1stFlrSF,
            &_2ndFlrSF,
            &LowQualFinSF,
            &GrLivArea,
            data[i].BsmtFullBath       != -1 ? &BsmtFullBath       : NULL,
            data[i].BsmtHalfBath       != -1 ? &BsmtHalfBath       : NULL,
            &FullBath,
            &HalfBath,
            &BedroomAbvGr,
            &KitchenAbvGr,
            &TotRmsAbvGrd,
            &Fireplaces,
            data[i].GarageYrBlt        != -1 ? &GarageYrBlt        : NULL,
            data[i].GarageCars         != -1 ? &GarageCars         : NULL,
            data[i].GarageArea         != -1 ? &GarageArea         : NULL,
            &WoodDeckSF,
            &OpenPorchSF,
            &EnclosedPorch,
            &_3SsnPorch,
            &ScreenPorch,
            &PoolArea,
            &MiscVal,
            &MoSold,
            &YrSold,
            data[i].n_bathrooms        != -1 ? &n_bathrooms        : NULL,
            data[i].area_with_basement != -1 ? &area_with_basement : NULL
        );
        float err = pow(log1p(value) - log1p(data[i].SalePrice), 2);
        sqerr += err;
        printf("Log error: %f\n", err);
    }
    float mse = sqerr / (float)n;
    float rmsle = sqrt(mse);
    printf("RMSLE: %f\n", rmsle);
    return 0;
}
