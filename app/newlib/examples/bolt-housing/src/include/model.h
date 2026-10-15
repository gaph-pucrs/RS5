#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define OFFSET_YearBuilt 1891
#define OFFSET_YearRemodAdd 1950
#define OFFSET_PoolArea 479
#define OFFSET_YrSold 2007

const uint8_t cond_MSSubClass[] = {
	80,
	160,
	70,
	90,
	60,
	75,
	180,
	30,
	45,
	40,
};

const float cond_LotFrontage[] = {
	174.0,
	122.0,
	69.0,
	80.0,
	71.0,
	61.0,
	89.0,
	111.0,
	33.0,
	129.0,
	108.0,
	114.0,
	96.0,
	70.0,
	121.0,
	35.0,
	74.0,
	97.0,
	100.0,
	64.0,
	115.0,
	58.0,
	81.0,
	77.0,
	50.0,
	85.0,
	626.0,
	42.0,
	24.0,
	75.0,
	104.0,
	48.0,
	60.0,
	65.0,
	99.0,
	88.0,
	76.0,
	53.0,
	87.0,
	90.0,
	44.0,
	79.0,
	51.0,
	140.0,
	134.0,
	105.0,
	103.0,
	39.0,
	82.0,
	168.0,
	68.0,
	91.0,
	109.0,
	160.0,
	86.0,
	66.0,
	45.0,
	150.0,
	54.0,
};

const uint16_t cond_LotArea[] = {
	12209,
	12665,
	6931,
	12968,
	6858,
	15523,
	6173,
	23257,
	3735,
	6342,
	11426,
	12000,
	12772,
	14536,
	10721,
	13695,
	19138,
	20431,
	9937,
	10800,
	6435,
	11932,
	21780,
	7018,
	13891,
	2665,
	11345,
	4800,
	11100,
	25286,
	21384,
	34650,
	11400,
	57200,
	28698,
	10440,
	12160,
	5250,
	11275,
	6060,
	7175,
	3951,
	14006,
	11643,
	7227,
	9245,
	10852,
	7064,
	14859,
	6000,
	6240,
	17140,
	9100,
	11050,
	10208,
	17542,
	45600,
	12435,
	4043,
	7917,
	8773,
	13811,
	10500,
	9765,
	9503,
	8120,
	1596,
	10650,
	12474,
	14598,
	10480,
	3196,
	8314,
	4571,
	8978,
	5350,
	12144,
	18000,
	15611,
	10769,
	16635,
	14778,
	16158,
	10120,
	3182,
	10142,
	10140,
	9125,
};

const uint8_t cond_OverallQual[] = {
	8,
	7,
	6,
	5,
	9,
	4,
	2,
};

const uint8_t cond_OverallCond[] = {
	6,
	5,
	4,
	7,
	9,
	8,
};

const uint8_t cond_YearBuilt[] = {
	88,
	86,
	93,
	83,
	81,
	94,
	103,
	64,
	95,
	59,
	73,
	68,
	61,
	116,
	113,
	57,
	117,
	96,
	26,
	112,
	114,
	22,
	56,
	115,
	27,
	50,
	29,
	13,
	91,
	20,
	46,
	25,
	102,
	41,
	51,
	28,
	24,
	45,
	58,
	118,
	23,
	109,
	30,
	108,
	44,
	107,
	111,
	66,
	79,
	78,
	1,
	104,
};

const uint8_t cond_YearRemodAdd[] = {
	25,
	33,
	43,
	27,
	40,
	57,
	4,
	34,
	12,
	55,
	5,
	37,
	24,
	53,
	56,
	1,
	54,
	26,
	3,
	59,
	44,
	49,
	14,
	42,
	47,
	20,
	51,
	29,
	45,
	7,
};

const float cond_MasVnrArea[] = {
	748.0,
	762.0,
	230.0,
	247.0,
	151.0,
	302.0,
	252.0,
	100.0,
	425.0,
	579.0,
	604.0,
	361.0,
	166.0,
	304.0,
	108.0,
	285.0,
	513.0,
	296.0,
	338.0,
	312.0,
	192.0,
	246.0,
	162.0,
	233.0,
	281.0,
	256.0,
	324.0,
	183.0,
	287.0,
};

const uint16_t cond_BsmtFinSF1[] = {
	808,
	747,
	672,
	349,
	351,
	1277,
	498,
	1128,
	772,
	1234,
	368,
	1148,
	1104,
	941,
	863,
	837,
	399,
	1116,
	1270,
	1324,
	294,
	1219,
	371,
	1440,
	20,
	1300,
	25,
	1086,
	735,
	222,
	36,
	48,
	1071,
	56,
	1336,
	1400,
	182,
	1309,
	266,
	218,
	1619,
	1513,
	1721,
	1460,
	239,
	280,
	16,
	1358,
	80,
	1170,
	821,
	442,
	602,
	1064,
	569,
	900,
	1904,
	883,
	226,
};

const uint16_t cond_BsmtFinSF2[] = {
	181,
	28,
	820,
	184,
	264,
	645,
	1029,
	692,
	713,
	764,
};

const uint16_t cond_BsmtUnfSF[] = {
	1237,
	1252,
	733,
	916,
	1098,
	1603,
	536,
	256,
	1428,
	877,
	1777,
	479,
	324,
	912,
	764,
	554,
	720,
	1392,
	124,
	126,
	413,
	752,
	1273,
	1482,
	780,
	293,
	1689,
	104,
	463,
	988,
	1752,
	88,
	72,
	1129,
	1632,
	473,
	1079,
	110,
	100,
	730,
	524,
	637,
	1497,
	312,
	389,
	29,
	114,
	1869,
	36,
	217,
	291,
	894,
	184,
	571,
	1417,
	238,
};

const uint16_t cond_TotalBsmtSF[] = {
	1200,
	709,
	1684,
	994,
	1604,
	1575,
	1595,
	2136,
	2076,
	2524,
	2217,
	1976,
	608,
	1453,
	1792,
	1498,
	1525,
	1368,
	839,
	1268,
	1136,
	1249,
	1346,
	1302,
	1440,
	866,
	624,
	2006,
	804,
	1394,
	1226,
	1256,
	1021,
	1856,
	924,
	655,
	1494,
	1902,
	756,
	915,
};

const uint16_t cond__1stFlrSF[] = {
	1636,
	1652,
	660,
	1352,
	1710,
	751,
	697,
	735,
	2515,
	1422,
	679,
	1391,
	1629,
	2158,
	1363,
	2036,
	1940,
	1456,
	912,
	1425,
	1057,
	1314,
	1526,
	1560,
	1898,
	1339,
	2259,
	1973,
	961,
	1478,
	1232,
	953,
	860,
	1360,
	983,
	980,
	2000,
	1504,
	1383,
	1055,
	1484,
	1574,
};

const uint16_t cond__2ndFlrSF[] = {
	1589,
	1122,
	678,
	768,
	876,
	783,
	1000,
	1178,
	1796,
	1093,
	687,
	984,
	688,
	741,
	748,
	779,
	806,
	581,
	1040,
	676,
	1174,
	685,
	1103,
	776,
	679,
	1177,
	1523,
	929,
	1276,
	836,
	1194,
	665,
	966,
	551,
	192,
	1032,
	864,
	622,
	817,
	842,
	1142,
	670,
};

const uint16_t cond_LowQualFinSF[] = {
	80,
	156,
	360,
};

const uint16_t cond_GrLivArea[] = {
	1725,
	1702,
	1838,
	1818,
	1426,
	1647,
	2418,
	1720,
	2324,
	3493,
	2392,
	1484,
	1786,
	1761,
	1482,
	1498,
	1959,
	1479,
	1840,
	1800,
	1692,
	2046,
	2223,
	1419,
	2198,
	1904,
	2274,
	1954,
	2169,
	1920,
	1506,
	1630,
	1559,
	1319,
	1656,
	1670,
	2646,
	1224,
	747,
	2153,
	803,
	1595,
	1689,
	893,
	1889,
	1846,
	1616,
	2291,
	1964,
	2978,
	1144,
	1709,
	1947,
	2784,
	2504,
	1190,
	1080,
	2097,
	768,
	1935,
	2521,
	1150,
	1660,
	1604,
	2713,
	2452,
	2060,
	2365,
	1442,
	1342,
	902,
	1324,
	2601,
	1464,
	1396,
};

const uint8_t cond_BsmtFullBath[] = {
	1,
	2,
};

const uint8_t cond_BsmtHalfBath[] = {
	1,
};

const uint8_t cond_FullBath[] = {
	3,
	1,
	2,
};

const uint8_t cond_HalfBath[] = {
	1,
};

const uint8_t cond_BedroomAbvGr[] = {
	3,
	4,
	1,
	5,
	2,
};

const uint8_t cond_KitchenAbvGr[] = {
	2,
};

const uint8_t cond_TotRmsAbvGrd[] = {
	10,
	9,
	7,
	4,
	11,
	8,
};

const uint8_t cond_Fireplaces[] = {
	1,
	2,
};

const float cond_GarageYrBlt[] = {
	1974.0,
	1953.0,
	1971.0,
	1922.0,
	1921.0,
	1946.0,
	1931.0,
	1997.0,
	2007.0,
	2008.0,
	2006.0,
	1952.0,
	1932.0,
	1958.0,
	1920.0,
	1949.0,
	1991.0,
	1987.0,
	1986.0,
	2002.0,
	1969.0,
	1954.0,
	1951.0,
	1963.0,
	1979.0,
	1988.0,
	1947.0,
	1942.0,
	1950.0,
	1940.0,
	1985.0,
	1941.0,
	1918.0,
	1955.0,
	1927.0,
	1961.0,
	1928.0,
	1995.0,
	1906.0,
	1945.0,
	1996.0,
	1998.0,
	2005.0,
	1970.0,
	1930.0,
	2009.0,
	1968.0,
};

const uint8_t cond_GarageCars[] = {
	3,
	2,
};

const uint16_t cond_GarageArea[] = {
	495,
	409,
	225,
	299,
	388,
	384,
	528,
	538,
	567,
	548,
	529,
	540,
	668,
	786,
	393,
	400,
	1043,
	180,
	210,
	544,
	750,
	856,
	866,
	711,
	774,
	800,
	297,
	1134,
	481,
	390,
	836,
	551,
	505,
	830,
	672,
	250,
	820,
	834,
	484,
	372,
	592,
	968,
	610,
	900,
	463,
	936,
	577,
	423,
	264,
};

const uint16_t cond_WoodDeckSF[] = {
	98,
	105,
	24,
	56,
	156,
	426,
	160,
	169,
	153,
	158,
	367,
	49,
	272,
	104,
	120,
	250,
	122,
	265,
	114,
	209,
	402,
	212,
	116,
	292,
	113,
	110,
	48,
	519,
	133,
	312,
	416,
	125,
};

const uint16_t cond_OpenPorchSF[] = {
	282,
	262,
	50,
	46,
	17,
	85,
	69,
	47,
	141,
	4,
	274,
	64,
	101,
	99,
	34,
	53,
	80,
	129,
	228,
	49,
	73,
	26,
	38,
	15,
	21,
	59,
	175,
	51,
	131,
	45,
	55,
	27,
	44,
	170,
	195,
	207,
	406,
	168,
	28,
	96,
	229,
	235,
	341,
	92,
	20,
	244,
	247,
	54,
	136,
	231,
	214,
	200,
	32,
	77,
	198,
	12,
	113,
	103,
};

const uint8_t cond_EnclosedPorch[] = {
	19,
	194,
	144,
	50,
	145,
	221,
	254,
	32,
};

const uint8_t cond__3SsnPorch[] = {
	23,
	96,
	162,
};

const uint8_t cond_ScreenPorch[] = {
	204,
	156,
	40,
	168,
	152,
	161,
	140,
	176,
	154,
	180,
	122,
	222,
	126,
	60,
};

const uint8_t cond_PoolArea[] = {
	1,
	76,
	33,
	40,
};

const uint16_t cond_MiscVal[] = {
	54,
	400,
};

const uint8_t cond_MoSold[] = {
	8,
	12,
	11,
	7,
	4,
	10,
	9,
	2,
	6,
	3,
	5,
};

const uint8_t cond_YrSold[] = {
	2,
	1,
	3,
};

const float cond_n_bathrooms[] = {
	2.5,
	4.5,
	1.5,
	3.5,
	3.0,
	4.0,
	2.0,
};

const uint16_t cond_area_with_basement[] = {
	2471,
	3684,
	2742,
	1670,
	3038,
	3717,
	2999,
	2046,
	2978,
	3837,
	3219,
	1824,
	2290,
	2540,
	3343,
	3608,
	3794,
	3284,
	1688,
	2256,
	3857,
	2957,
	4294,
	3008,
	2416,
	4085,
	2932,
	1608,
	3360,
	3408,
	2244,
	1626,
	2694,
	3591,
	3994,
	1470,
	2625,
	2880,
	2480,
	3492,
	4450,
	2820,
	3532,
	2172,
	3882,
	2716,
	3401,
	2180,
	2884,
	2635,
	1812,
	1490,
	1836,
	2535,
	4240,
	1576,
	2338,
	4175,
	5496,
	1728,
	2572,
	2523,
	2313,
	2390,
	2442,
	2232,
	2736,
	1440,
	3541,
	1654,
	2789,
	3960,
	3257,
	2400,
	1015,
	2856,
	2684,
	2676,
	2752,
	3081,
	2039,
	3368,
	1294,
};

float model(const uint8_t *MSSubClass, const float *LotFrontage, const uint16_t *LotArea, const uint8_t *OverallQual, const uint8_t *OverallCond, const uint8_t *YearBuilt, const uint8_t *YearRemodAdd, const float *MasVnrArea, const uint16_t *BsmtFinSF1, const uint16_t *BsmtFinSF2, const uint16_t *BsmtUnfSF, const uint16_t *TotalBsmtSF, const uint16_t *_1stFlrSF, const uint16_t *_2ndFlrSF, const uint16_t *LowQualFinSF, const uint16_t *GrLivArea, const uint8_t *BsmtFullBath, const uint8_t *BsmtHalfBath, const uint8_t *FullBath, const uint8_t *HalfBath, const uint8_t *BedroomAbvGr, const uint8_t *KitchenAbvGr, const uint8_t *TotRmsAbvGrd, const uint8_t *Fireplaces, const float *GarageYrBlt, const uint8_t *GarageCars, const uint16_t *GarageArea, const uint16_t *WoodDeckSF, const uint16_t *OpenPorchSF, const uint8_t *EnclosedPorch, const uint8_t *_3SsnPorch, const uint8_t *ScreenPorch, const uint8_t *PoolArea, const uint16_t *MiscVal, const uint8_t *MoSold, const uint8_t *YrSold, const float *n_bathrooms, const uint16_t *area_with_basement)
{
	float w0;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[0]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[3]) {
					w0 = -1255.1189;
				} else {
					w0 = -761.5761;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[0]) {
					w0 = -523.2906;
				} else {
					w0 = -98.15977;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[0]) {
					w0 = -376.20157;
				} else {
					w0 = 64.34646;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[4]) {
					w0 = 289.9778;
				} else {
					w0 = 1035.4094;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[0]) {
					w0 = 102.49478;
				} else {
					w0 = 512.27844;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[0]) {
					w0 = 1127.4716;
				} else {
					w0 = 1817.8673;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
					w0 = 1681.0763;
				} else {
					w0 = 3058.6946;
				}
			} else {
				w0 = 5817.946;
			}
		}
	}
	float w1;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[0]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[3]) {
					w1 = -1236.4438;
				} else {
					w1 = -750.1787;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[0]) {
					w1 = -515.56775;
				} else {
					w1 = -96.70261;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[0]) {
					w1 = -271.35028;
				} else {
					w1 = 217.99138;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[6]) {
					w1 = 271.1919;
				} else {
					w1 = 997.2233;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[0]) {
					w1 = 101.047714;
				} else {
					w1 = 505.23456;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[0]) {
					w1 = 1118.1576;
				} else {
					w1 = 1836.9716;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[1]) {
					w1 = 2839.1746;
				} else {
					w1 = -109.16086;
				}
			} else {
				w1 = 5748.1304;
			}
		}
	}
	float w2;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[0]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[1]) {
					w2 = -1039.2117;
				} else {
					w2 = -531.1191;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[2]) {
					w2 = -577.5387;
				} else {
					w2 = -111.25024;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w2 = -444.06982;
				} else {
					w2 = 17.202961;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[8]) {
					w2 = 249.91139;
				} else {
					w2 = 958.2122;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[0]) {
					w2 = 99.62117;
				} else {
					w2 = 498.28763;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[0]) {
					w2 = 1094.2684;
				} else {
					w2 = 1764.0791;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
					w2 = 1620.9164;
				} else {
					w2 = 2973.6777;
				}
			} else {
				w2 = 5679.153;
			}
		}
	}
	float w3;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[3]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[11]) {
					w3 = -1132.7357;
				} else {
					w3 = -701.58826;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w3 = -576.69714;
				} else {
					w3 = -131.61694;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[0]) {
					w3 = -365.93326;
				} else {
					w3 = 66.906845;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[4]) {
					w3 = 276.58542;
				} else {
					w3 = 991.03436;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[9]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
					w3 = 270.24588;
				} else {
					w3 = 1029.4706;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[0]) {
					w3 = 1850.0122;
				} else {
					w3 = 1104.5386;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[1]) {
					w3 = 2845.3643;
				} else {
					w3 = -131.04227;
				}
			} else {
				w3 = 5611.0024;
			}
		}
	}
	float w4;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[0]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[1]) {
					w4 = -1009.38574;
				} else {
					w4 = -516.653;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[2]) {
					w4 = -559.41614;
				} else {
					w4 = -106.18004;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[0]) {
					w4 = -262.68018;
				} else {
					w4 = 217.04;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[8]) {
					w4 = 242.06937;
				} else {
					w4 = 930.5788;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[9]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
					w4 = 266.3369;
				} else {
					w4 = 1014.33746;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[1]) {
					w4 = 1278.7582;
				} else {
					w4 = 1936.3595;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[1]) {
					w4 = 2803.3723;
				} else {
					w4 = -129.7318;
				}
			} else {
				w4 = 5543.671;
			}
		}
	}
	float w5;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[0]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[3]) {
					w5 = -1172.9177;
				} else {
					w5 = -705.5647;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[0]) {
					w5 = -480.612;
				} else {
					w5 = -86.69163;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w5 = -431.91565;
				} else {
					w5 = 20.082241;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[4]) {
					w5 = 267.995;
				} else {
					w5 = 962.5236;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[0]) {
					w5 = 90.63926;
				} else {
					w5 = 484.05807;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[2]) {
					w5 = 1023.969;
				} else {
					w5 = 1666.3485;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
					w5 = 1529.9409;
				} else {
					w5 = 2853.4622;
				}
			} else {
				w5 = 5477.1465;
			}
		}
	}
	float w6;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[12]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[3]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[3]) {
					w6 = -1199.8895;
				} else {
					w6 = -770.39624;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w6 = -601.6017;
				} else {
					w6 = -186.58809;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
					w6 = -444.50183;
				} else {
					w6 = -11.38738;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[8]) {
					w6 = 197.80408;
				} else {
					w6 = 903.74243;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[9]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
					w6 = 258.855;
				} else {
					w6 = 980.71277;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[0]) {
					w6 = 1772.0918;
				} else {
					w6 = 1053.7831;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
					w6 = 1533.4144;
				} else {
					w6 = 2937.2515;
				}
			} else {
				w6 = 5411.421;
			}
		}
	}
	float w7;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[13]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[1]) {
					w7 = -967.68036;
				} else {
					w7 = -493.13016;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[2]) {
					w7 = -516.41473;
				} else {
					w7 = -66.53767;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[0]) {
					w7 = -343.51846;
				} else {
					w7 = 123.34125;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[14]) {
					w7 = 392.0039;
				} else {
					w7 = 1190.6099;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[9]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
					w7 = 255.1108;
				} else {
					w7 = 966.29614;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[1]) {
					w7 = 1222.4891;
				} else {
					w7 = 1854.8248;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[1]) {
					w7 = 2685.7778;
				} else {
					w7 = -172.70483;
				}
			} else {
				w7 = 5346.4834;
			}
		}
	}
	float w8;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[12]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[3]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[3]) {
					w8 = -1167.6661;
				} else {
					w8 = -747.0724;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w8 = -585.348;
				} else {
					w8 = -179.3409;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
					w8 = -433.29;
				} else {
					w8 = -9.165452;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[8]) {
					w8 = 191.37286;
				} else {
					w8 = 879.35736;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[15]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[0]) {
					w8 = 82.10361;
				} else {
					w8 = 470.33514;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[2]) {
					w8 = 930.0;
				} else {
					w8 = 1572.5114;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
					w8 = 1471.735;
				} else {
					w8 = 2628.6646;
				}
			} else {
				w8 = 5282.326;
			}
		}
	}
	float w9;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[13]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w9 = -1151.4493;
				} else {
					w9 = -738.3372;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[2]) {
					w9 = -501.40234;
				} else {
					w9 = -64.603165;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[0]) {
					w9 = -335.3584;
				} else {
					w9 = 123.41736;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[14]) {
					w9 = 379.97397;
				} else {
					w9 = 1160.2354;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[16]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
					w9 = 247.94545;
				} else {
					w9 = 934.75824;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[1]) {
					w9 = 1128.8557;
				} else {
					w9 = 1800.4652;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
					w9 = 1465.0818;
				} else {
					w9 = 2788.9368;
				}
			} else {
				w9 = 5218.9375;
			}
		}
	}
	float w10;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[13]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[1]) {
					w10 = -926.84937;
				} else {
					w10 = -467.83636;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[2]) {
					w10 = -493.90878;
				} else {
					w10 = -63.642838;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[0]) {
					w10 = -330.37415;
				} else {
					w10 = 121.58038;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[17]) {
					w10 = 363.7192;
				} else {
					w10 = 1104.776;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[9]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[0]) {
					w10 = 173.62552;
				} else {
					w10 = 889.0823;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[0]) {
					w10 = 1671.835;
				} else {
					w10 = 987.6276;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[1]) {
					w10 = 2574.5903;
				} else {
					w10 = -212.74992;
				}
			} else {
				w10 = 5156.311;
			}
		}
	}
	float w11;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[12]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[18]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w11 = -1281.2043;
				} else {
					w11 = -905.5652;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w11 = -688.063;
				} else {
					w11 = -269.84384;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
					w11 = -417.99887;
				} else {
					w11 = -5.1055837;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[8]) {
					w11 = 181.93648;
				} else {
					w11 = 844.9342;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[16]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
					w11 = 237.63156;
				} else {
					w11 = 909.2356;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[1]) {
					w11 = 1093.7119;
				} else {
					w11 = 1749.5131;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
					w11 = 1411.3073;
				} else {
					w11 = 2711.6133;
				}
			} else {
				w11 = 5094.435;
			}
		}
	}
	float w12;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[13]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w12 = -1106.1338;
				} else {
					w12 = -704.7097;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[2]) {
					w12 = -479.93576;
				} else {
					w12 = -61.14852;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[0]) {
					w12 = -322.54706;
				} else {
					w12 = 121.57528;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[14]) {
					w12 = 362.65543;
				} else {
					w12 = 1114.6002;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[9]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[0]) {
					w12 = 165.09694;
				} else {
					w12 = 864.61285;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[0]) {
					w12 = 1623.6296;
				} else {
					w12 = 956.69714;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[1]) {
					w12 = 2500.9805;
				} else {
					w12 = -231.23701;
				}
			} else {
				w12 = 5033.3013;
			}
		}
	}
	float w13;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[13]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[1]) {
					w13 = -888.27856;
				} else {
					w13 = -441.2288;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[4]) {
					w13 = -515.15515;
				} else {
					w13 = -137.15671;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[0]) {
					w13 = -317.75327;
				} else {
					w13 = 119.76574;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[17]) {
					w13 = 347.15402;
				} else {
					w13 = 1060.8184;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[15]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[19]) {
					w13 = -131.67288;
				} else {
					w13 = 311.53043;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[2]) {
					w13 = 856.6651;
				} else {
					w13 = 1466.8671;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
					w13 = 1349.3126;
				} else {
					w13 = 2450.739;
				}
			} else {
				w13 = 4972.902;
			}
		}
	}
	float w14;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[12]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[3]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[0]) {
					w14 = -1110.3495;
				} else {
					w14 = -662.5974;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w14 = -659.8579;
				} else {
					w14 = -254.33443;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
					w14 = -403.187;
				} else {
					w14 = -1.3647971;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[21]) {
					w14 = 167.4459;
				} else {
					w14 = 802.9887;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[0]) {
					w14 = 157.28145;
				} else {
					w14 = 837.8575;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[1]) {
					w14 = 1114.0424;
				} else {
					w14 = 1699.1349;
				}
			}
		} else {
			if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[0]) {
					w14 = 1527.1794;
				} else {
					w14 = -31.153202;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[22]) {
					w14 = 2297.9226;
				} else {
					w14 = 3801.5103;
				}
			}
		}
	}
	float w15;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[13]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w15 = -1025.1581;
				} else {
					w15 = -594.0209;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[0]) {
					w15 = -375.2092;
				} else {
					w15 = -33.892593;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[0]) {
					w15 = -218.58533;
				} else {
					w15 = 255.30144;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[14]) {
					w15 = 346.0461;
				} else {
					w15 = 1070.8955;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
					w15 = 218.07994;
				} else {
					w15 = 857.25653;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[1]) {
					w15 = 1571.672;
				} else {
					w15 = 912.00714;
				}
			}
		} else {
			if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[0]) {
					w15 = 1505.9082;
				} else {
					w15 = -30.84164;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[22]) {
					w15 = 2264.6848;
				} else {
					w15 = 3747.203;
				}
			}
		}
	}
	float w16;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[12]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[18]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w16 = -1201.949;
				} else {
					w16 = -846.83575;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
					w16 = -806.0191;
				} else {
					w16 = -450.0911;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
					w16 = -392.65408;
				} else {
					w16 = 1.0456673;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[8]) {
					w16 = 167.8484;
				} else {
					w16 = 790.1726;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[19]) {
					w16 = -136.42043;
				} else {
					w16 = 297.23648;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[2]) {
					w16 = 857.0258;
				} else {
					w16 = 1424.3602;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
					w16 = 1275.9174;
				} else {
					w16 = 2441.0725;
				}
			} else {
				w16 = 4822.643;
			}
		}
	}
	float w17;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[13]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[1]) {
					w17 = -998.28925;
				} else {
					w17 = -633.1336;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[4]) {
					w17 = -485.8583;
				} else {
					w17 = -125.614716;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[0]) {
					w17 = -213.25551;
				} else {
					w17 = 253.7562;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[14]) {
					w17 = 335.37027;
				} else {
					w17 = 1043.5864;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[0]) {
					w17 = 144.07083;
				} else {
					w17 = 801.0468;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
					w17 = 1169.5367;
				} else {
					w17 = 1782.7303;
				}
			}
		} else {
			if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[0]) {
					w17 = 1467.1613;
				} else {
					w17 = -43.29242;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[22]) {
					w17 = 2196.6191;
				} else {
					w17 = 3651.9941;
				}
			}
		}
	}
	float w18;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[12]) {
			if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w18 = -1059.9199;
				} else {
					w18 = -706.8761;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w18 = -560.9425;
				} else {
					w18 = -158.64772;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
					w18 = -383.22473;
				} else {
					w18 = 3.0492978;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[21]) {
					w18 = 157.10681;
				} else {
					w18 = 760.4886;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[0]) {
					w18 = 142.00363;
				} else {
					w18 = 789.2496;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
					w18 = 1152.2678;
				} else {
					w18 = 1756.9114;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[0]) {
					w18 = 1918.4535;
				} else {
					w18 = 601.0859;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
					w18 = 3464.7532;
				} else {
					w18 = 170.9744;
				}
			}
		}
	}
	float w19;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[13]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[3]) {
					w19 = -974.4835;
				} else {
					w19 = -559.53094;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[0]) {
					w19 = -354.86896;
				} else {
					w19 = -25.934958;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[1]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w19 = -589.39056;
				} else {
					w19 = 12.356604;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[8]) {
					w19 = 179.73557;
				} else {
					w19 = 683.25476;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[15]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[19]) {
					w19 = -141.55167;
				} else {
					w19 = 280.36145;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[2]) {
					w19 = 774.69763;
				} else {
					w19 = 1350.3417;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
					w19 = 1599.2207;
				} else {
					w19 = 2487.1814;
				}
			} else {
				w19 = 4684.009;
			}
		}
	}
	float w20;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[23]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[3]) {
					w20 = -906.47125;
				} else {
					w20 = -597.9733;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w20 = -508.46957;
				} else {
					w20 = -211.74821;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[24]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w20 = -420.78223;
				} else {
					w20 = -67.39936;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[1]) {
					w20 = -210.9029;
				} else {
					w20 = 331.04535;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w20 = -372.2037;
				} else {
					w20 = 310.0225;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
					w20 = 820.181;
				} else {
					w20 = 1509.6241;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w20 = 1835.9642;
				} else {
					w20 = 580.89307;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w20 = 3743.3257;
				} else {
					w20 = -348.56857;
				}
			}
		}
	}
	float w21;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[12]) {
			if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w21 = -1021.30566;
				} else {
					w21 = -677.4318;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
					w21 = -780.939;
				} else {
					w21 = -325.41837;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w21 = -429.93314;
				} else {
					w21 = -29.973572;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
					w21 = 141.68611;
				} else {
					w21 = 711.76764;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[0]) {
					w21 = 132.63792;
				} else {
					w21 = 755.7659;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[1]) {
					w21 = 1446.504;
				} else {
					w21 = 817.44336;
				}
			}
		} else {
			if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[0]) {
					w21 = 1380.097;
				} else {
					w21 = -72.95703;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[22]) {
					w21 = 2069.947;
				} else {
					w21 = 3473.9617;
				}
			}
		}
	}
	float w22;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[12]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[27]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[0]) {
					w22 = -1046.5323;
				} else {
					w22 = -617.618;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w22 = -674.38074;
				} else {
					w22 = -363.61096;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
					w22 = -365.04733;
				} else {
					w22 = 5.113608;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[4]) {
					w22 = 175.7599;
				} else {
					w22 = 763.1111;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[0]) {
					w22 = 130.73483;
				} else {
					w22 = 744.6355;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[1]) {
					w22 = 1425.121;
				} else {
					w22 = 805.6927;
				}
			}
		} else {
			if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[0]) {
					w22 = 1360.8743;
				} else {
					w22 = -72.22749;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[22]) {
					w22 = 2040.0065;
				} else {
					w22 = 3424.3335;
				}
			}
		}
	}
	float w23;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[23]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[3]) {
					w23 = -871.21924;
				} else {
					w23 = -570.39905;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w23 = -489.3754;
				} else {
					w23 = -202.44551;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[24]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w23 = -403.50552;
				} else {
					w23 = -60.814342;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[1]) {
					w23 = -210.04913;
				} else {
					w23 = 319.67523;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w23 = -360.39948;
				} else {
					w23 = 307.94107;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
					w23 = 780.8759;
				} else {
					w23 = 1445.7069;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w23 = 1767.9421;
				} else {
					w23 = 546.4188;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w23 = 3601.2607;
				} else {
					w23 = -378.8485;
				}
			}
		}
	}
	float w24;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[13]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w24 = -916.09595;
				} else {
					w24 = -519.2636;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[0]) {
					w24 = -327.64328;
				} else {
					w24 = -20.672686;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[1]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[1]) {
					w24 = -336.98065;
				} else {
					w24 = 254.399;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[8]) {
					w24 = 170.45322;
				} else {
					w24 = 638.3189;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
					w24 = 182.63353;
				} else {
					w24 = 753.40393;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[1]) {
					w24 = 949.0548;
				} else {
					w24 = 1482.4093;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[1]) {
					w24 = 2150.3188;
				} else {
					w24 = -375.0601;
				}
			} else {
				w24 = 4470.0537;
			}
		}
	}
	float w25;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[12]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[27]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[2]) {
					w25 = -1030.3699;
				} else {
					w25 = -675.907;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w25 = -646.69794;
				} else {
					w25 = -345.42163;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w25 = -410.63574;
				} else {
					w25 = -26.243149;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
					w25 = 135.04347;
				} else {
					w25 = 671.14264;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[15]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[19]) {
					w25 = -144.39227;
				} else {
					w25 = 256.788;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[2]) {
					w25 = 704.1602;
				} else {
					w25 = 1246.6477;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[1]) {
					w25 = 1913.579;
				} else {
					w25 = -371.30945;
				}
			} else {
				w25 = 4416.4136;
			}
		}
	}
	float w26;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[13]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w26 = -892.1507;
				} else {
					w26 = -504.0458;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w26 = -477.37537;
				} else {
					w26 = -76.214165;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[1]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[1]) {
					w26 = -330.80292;
				} else {
					w26 = 249.46623;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[14]) {
					w26 = 252.91599;
				} else {
					w26 = 843.527;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
					w26 = -72.18274;
				} else {
					w26 = 651.5156;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[1]) {
					w26 = 1346.6636;
				} else {
					w26 = 753.15924;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[0]) {
					w26 = 1704.991;
				} else {
					w26 = 453.74655;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
					w26 = 3135.8665;
				} else {
					w26 = 87.766464;
				}
			}
		}
	}
	float w27;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[23]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[2]) {
					w27 = -998.7351;
				} else {
					w27 = -638.0343;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w27 = -463.67255;
				} else {
					w27 = -188.45187;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[24]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w27 = -377.4887;
				} else {
					w27 = -55.837215;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[1]) {
					w27 = -210.71426;
				} else {
					w27 = 305.1225;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w27 = -351.07043;
				} else {
					w27 = 296.9503;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
					w27 = 733.36176;
				} else {
					w27 = 1362.8843;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w27 = 1676.0934;
				} else {
					w27 = 492.92395;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w27 = 3436.6265;
				} else {
					w27 = -368.47397;
				}
			}
		}
	}
	float w28;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[12]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[27]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[0]) {
					w28 = -971.69794;
				} else {
					w28 = -563.69867;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w28 = -619.8526;
				} else {
					w28 = -328.43246;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
					w28 = -340.75632;
				} else {
					w28 = 8.344278;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[17]) {
					w28 = 221.53073;
				} else {
					w28 = 874.4941;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[28]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
					w28 = 169.84323;
				} else {
					w28 = 765.46136;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[2]) {
					w28 = 1527.6917;
				} else {
					w28 = 917.6295;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[1]) {
					w28 = 2028.2994;
				} else {
					w28 = -364.7893;
				}
			} else {
				w28 = 4295.06;
			}
		}
	}
	float w29;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[23]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[3]) {
					w29 = -807.445;
				} else {
					w29 = -517.4974;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w29 = -451.63824;
				} else {
					w29 = -183.02348;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[24]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w29 = -367.0053;
				} else {
					w29 = -52.36819;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[1]) {
					w29 = -209.28864;
				} else {
					w29 = 297.25552;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w29 = -342.04123;
				} else {
					w29 = 293.77975;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
					w29 = 711.5241;
				} else {
					w29 = 1320.0127;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w29 = 1631.5001;
				} else {
					w29 = 473.26514;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w29 = 3353.6985;
				} else {
					w29 = -361.1413;
				}
			}
		}
	}
	float w30;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[12]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[3]) {
					w30 = -1039.922;
				} else {
					w30 = -676.02783;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[3]) {
					w30 = -664.4704;
				} else {
					w30 = -313.0754;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w30 = -342.18265;
				} else {
					w30 = 3.4377265;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
					w30 = 125.50192;
				} else {
					w30 = 624.1244;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[28]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
					w30 = 165.84848;
				} else {
					w30 = 743.9314;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[2]) {
					w30 = 1487.976;
				} else {
					w30 = 890.28406;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
					w30 = 1010.39233;
				} else {
					w30 = 2159.6143;
				}
			} else {
				w30 = 4209.3765;
			}
		}
	}
	float w31;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[23]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[3]) {
					w31 = -785.55164;
				} else {
					w31 = -501.82867;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w31 = -439.1719;
				} else {
					w31 = -178.72919;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[24]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w31 = -356.1194;
				} else {
					w31 = -48.455887;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[1]) {
					w31 = -206.35576;
				} else {
					w31 = 290.1123;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w31 = -332.10883;
				} else {
					w31 = 289.397;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[29]) {
					w31 = 590.8285;
				} else {
					w31 = 1132.7671;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w31 = 1588.0386;
				} else {
					w31 = 453.28302;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w31 = 3270.5447;
				} else {
					w31 = -373.3799;
				}
			}
		}
	}
	float w32;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[13]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w32 = -814.1478;
				} else {
					w32 = -497.1692;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w32 = -476.92914;
				} else {
					w32 = -120.62923;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[1]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[0]) {
					w32 = -324.7303;
				} else {
					w32 = 214.91791;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[0]) {
					w32 = 111.46126;
				} else {
					w32 = 545.5551;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
					w32 = -82.312584;
				} else {
					w32 = 603.1151;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[1]) {
					w32 = 1241.6605;
				} else {
					w32 = 676.9382;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[1]) {
					w32 = 1914.998;
				} else {
					w32 = -369.64615;
				}
			} else {
				w32 = 4126.031;
			}
		}
	}
	float w33;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[30]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[7]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[31]) {
					w33 = -939.6481;
				} else {
					w33 = -624.34973;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w33 = -552.2432;
				} else {
					w33 = -273.76923;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w33 = -388.88397;
				} else {
					w33 = -28.488623;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[17]) {
					w33 = 200.30032;
				} else {
					w33 = 816.66113;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[28]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
					w33 = 156.52312;
				} else {
					w33 = 713.2931;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[2]) {
					w33 = 1428.9033;
				} else {
					w33 = 847.00684;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
					w33 = 956.4516;
				} else {
					w33 = 2071.4822;
				}
			} else {
				w33 = 4076.518;
			}
		}
	}
	float w34;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[23]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[2]) {
					w34 = -917.6244;
				} else {
					w34 = -575.15375;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w34 = -448.00323;
				} else {
					w34 = -182.31839;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[32]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w34 = -263.1179;
				} else {
					w34 = 63.68984;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[3]) {
					w34 = 480.0577;
				} else {
					w34 = 194.39937;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w34 = -323.79312;
				} else {
					w34 = 283.60916;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
					w34 = 658.15955;
				} else {
					w34 = 1226.3914;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w34 = 1527.6583;
				} else {
					w34 = 421.19812;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w34 = 3157.8389;
				} else {
					w34 = -381.08945;
				}
			}
		}
	}
	float w35;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[13]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w35 = -783.79913;
				} else {
					w35 = -475.86606;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w35 = -455.70966;
				} else {
					w35 = -114.521255;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[1]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[1]) {
					w35 = -306.33154;
				} else {
					w35 = 231.10165;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[0]) {
					w35 = 105.29775;
				} else {
					w35 = 527.2442;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[33]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
					w35 = 154.12166;
				} else {
					w35 = 708.0043;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
					w35 = 474.26944;
				} else {
					w35 = 1394.6467;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w35 = 1488.0039;
				} else {
					w35 = 416.98608;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w35 = 3112.7268;
				} else {
					w35 = -377.2785;
				}
			}
		}
	}
	float w36;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[23]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[3]) {
					w36 = -736.9619;
				} else {
					w36 = -462.53333;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w36 = -436.33966;
				} else {
					w36 = -175.77057;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[32]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w36 = -256.74622;
				} else {
					w36 = 62.85295;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[3]) {
					w36 = 467.0204;
				} else {
					w36 = 187.16158;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w36 = -317.49393;
				} else {
					w36 = 276.81888;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
					w36 = 639.7156;
				} else {
					w36 = 1194.0126;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w36 = 1483.646;
				} else {
					w36 = 412.81625;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w36 = 3068.2593;
				} else {
					w36 = -373.5057;
				}
			}
		}
	}
	float w37;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[12]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[3]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[3]) {
					w37 = -881.7585;
				} else {
					w37 = -568.6554;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
					w37 = -611.3136;
				} else {
					w37 = -316.41953;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w37 = -315.88416;
				} else {
					w37 = 8.429855;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[14]) {
					w37 = 200.3584;
				} else {
					w37 = 802.7028;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[28]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
					w37 = -89.98019;
				} else {
					w37 = 618.4047;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[2]) {
					w37 = 1357.7925;
				} else {
					w37 = 794.62286;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[1]) {
					w37 = 1780.0499;
				} else {
					w37 = -369.7707;
				}
			} else {
				w37 = 3932.1052;
			}
		}
	}
	float w38;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[23]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[8]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[2]) {
					w38 = -872.22644;
				} else {
					w38 = -541.5972;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w38 = -399.87137;
				} else {
					w38 = -154.05238;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[32]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w38 = -244.198;
				} else {
					w38 = 63.750114;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[3]) {
					w38 = 463.2391;
				} else {
					w38 = 180.56477;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w38 = -308.29953;
				} else {
					w38 = 272.61267;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[29]) {
					w38 = 532.55054;
				} else {
					w38 = 1021.3831;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w38 = 1444.3748;
				} else {
					w38 = 395.81476;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w38 = 2994.3862;
				} else {
					w38 = -366.07303;
				}
			}
		}
	}
	float w39;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[30]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[7]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w39 = -981.14655;
				} else {
					w39 = -605.1139;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w39 = -505.36722;
				} else {
					w39 = -247.10724;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w39 = -362.82294;
				} else {
					w39 = -22.309187;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[14]) {
					w39 = 190.59125;
				} else {
					w39 = 777.05206;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[33]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
					w39 = 146.00642;
				} else {
					w39 = 669.20465;
				}
			} else {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[0]) {
					w39 = 1299.4645;
				} else {
					w39 = 253.68462;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[34]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w39 = 1322.1892;
				} else {
					w39 = 391.85663;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
					w39 = 2825.899;
				} else {
					w39 = 21.839825;
				}
			}
		}
	}
	float w40;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[23]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[4]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w40 = -909.7364;
				} else {
					w40 = -574.95013;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[35]) {
					w40 = -878.876;
				} else {
					w40 = -347.2772;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[4]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[2]) {
					w40 = -627.4367;
				} else {
					w40 = -291.99176;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[36]) {
					w40 = -78.3232;
				} else {
					w40 = 229.27231;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w40 = -302.01746;
				} else {
					w40 = 269.52783;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
					w40 = 602.40643;
				} else {
					w40 = 1125.7551;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[34]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w40 = 1319.0254;
				} else {
					w40 = 387.93805;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
					w40 = 2785.206;
				} else {
					w40 = 21.594082;
				}
			}
		}
	}
	float w41;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[30]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[7]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[31]) {
					w41 = -854.0364;
				} else {
					w41 = -559.6111;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w41 = -490.8776;
				} else {
					w41 = -239.9277;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w41 = -351.8482;
				} else {
					w41 = -21.233564;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[37]) {
					w41 = 91.02671;
				} else {
					w41 = 515.47626;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[28]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
					w41 = -93.04251;
				} else {
					w41 = 586.29364;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[2]) {
					w41 = 1289.5734;
				} else {
					w41 = 742.6859;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
					w41 = 834.48975;
				} else {
					w41 = 1845.6147;
				}
			} else {
				w41 = 3797.1309;
			}
		}
	}
	float w42;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[38]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[3]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[3]) {
					w42 = -759.4134;
				} else {
					w42 = -425.8355;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w42 = -312.849;
				} else {
					w42 = -46.677998;
				}
			}
		} else {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[0]) {
					w42 = -250.19232;
				} else {
					w42 = 152.66277;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
					w42 = 432.501;
				} else {
					w42 = 1043.5817;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[33]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
					w42 = 138.46898;
				} else {
					w42 = 641.3646;
				}
			} else {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[0]) {
					w42 = 1245.4554;
				} else {
					w42 = 224.08415;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[22]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[5]) {
					w42 = 1154.8171;
				} else {
					w42 = 1762.6735;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w42 = 3111.6855;
				} else {
					w42 = -376.2471;
				}
			}
		}
	}
	float w43;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[23]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
					w43 = -849.04706;
				} else {
					w43 = -549.13245;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
					w43 = -590.4699;
				} else {
					w43 = -327.19196;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[4]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[2]) {
					w43 = -606.32324;
				} else {
					w43 = -277.7581;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[36]) {
					w43 = -74.26326;
				} else {
					w43 = 220.79402;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[4]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w43 = -392.12442;
				} else {
					w43 = 273.203;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
					w43 = 560.9185;
				} else {
					w43 = 1193.1097;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[40]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w43 = 1431.3859;
				} else {
					w43 = 356.5296;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w43 = 3137.2026;
				} else {
					w43 = -372.4846;
				}
			}
		}
	}
	float w44;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[30]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[7]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w44 = -925.87085;
				} else {
					w44 = -563.98285;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w44 = -469.8691;
				} else {
					w44 = -228.76718;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w44 = -338.9413;
				} else {
					w44 = -20.271336;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[14]) {
					w44 = 177.46968;
				} else {
					w44 = 729.2;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[33]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
					w44 = 136.24467;
				} else {
					w44 = 624.66284;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
					w44 = 368.71298;
				} else {
					w44 = 1232.0981;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[34]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w44 = 1229.9803;
				} else {
					w44 = 352.9643;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
					w44 = 2643.6392;
				} else {
					w44 = 4.0887303;
				}
			}
		}
	}
	float w45;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[23]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[8]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[2]) {
					w45 = -803.802;
				} else {
					w45 = -489.72058;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w45 = -393.36523;
				} else {
					w45 = -146.31018;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[32]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w45 = -228.67453;
				} else {
					w45 = 63.707912;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[3]) {
					w45 = 435.01218;
				} else {
					w45 = 156.01285;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[4]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w45 = -386.11298;
				} else {
					w45 = 266.69873;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
					w45 = 545.7939;
				} else {
					w45 = 1161.2953;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[40]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[1]) {
					w45 = 703.7747;
				} else {
					w45 = 1430.7987;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w45 = 3056.2712;
				} else {
					w45 = -368.8007;
				}
			}
		}
	}
	float w46;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[4]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w46 = -1019.26886;
				} else {
					w46 = -546.60583;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[3]) {
					w46 = -360.75058;
				} else {
					w46 = 1.2051562;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[41]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[5]) {
					w46 = -378.8024;
				} else {
					w46 = -33.287853;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w46 = 245.71315;
				} else {
					w46 = 747.7151;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[28]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
					w46 = -97.01771;
				} else {
					w46 = 547.32837;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[2]) {
					w46 = 1209.5192;
				} else {
					w46 = 683.23035;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[1]) {
					w46 = 1560.1785;
				} else {
					w46 = -365.11273;
				}
			} else {
				w46 = 3629.5305;
			}
		}
	}
	float w47;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[23]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
					w47 = -809.96716;
				} else {
					w47 = -521.28784;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
					w47 = -560.56494;
				} else {
					w47 = -306.4121;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[5]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[4]) {
					w47 = -588.4092;
				} else {
					w47 = -265.62906;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[36]) {
					w47 = -70.7216;
				} else {
					w47 = 211.36281;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[4]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w47 = -375.77634;
				} else {
					w47 = 257.28302;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
					w47 = 530.1559;
				} else {
					w47 = 1127.3904;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[40]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[5]) {
					w47 = 1105.2294;
				} else {
					w47 = 1655.8263;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w47 = 2985.4326;
				} else {
					w47 = -361.46164;
				}
			}
		}
	}
	float w48;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[6]) {
					w48 = -609.2343;
				} else {
					w48 = -328.47293;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
					w48 = -356.8637;
				} else {
					w48 = -87.69277;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[2]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[0]) {
					w48 = -309.06854;
				} else {
					w48 = 66.192505;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[42]) {
					w48 = 319.29657;
				} else {
					w48 = 744.28796;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[33]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
					w48 = 129.04369;
				} else {
					w48 = 592.2229;
				}
			} else {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[0]) {
					w48 = 1145.1637;
				} else {
					w48 = 169.98445;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[34]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w48 = 1162.2885;
				} else {
					w48 = 310.10422;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
					w48 = 2511.4304;
				} else {
					w48 = -3.1027734;
				}
			}
		}
	}
	float w49;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[43]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
					w49 = -776.3069;
				} else {
					w49 = -430.0499;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
					w49 = -338.8134;
				} else {
					w49 = -55.263935;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[3]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[0]) {
					w49 = -308.66873;
				} else {
					w49 = 60.481804;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[42]) {
					w49 = 309.80722;
				} else {
					w49 = 733.41;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[33]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
					w49 = 127.17712;
				} else {
					w49 = 583.43616;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[7]) {
					w49 = 820.6911;
				} else {
					w49 = 1409.9712;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[40]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[1]) {
					w49 = 661.97815;
				} else {
					w49 = 1352.2687;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w49 = 2908.4766;
				} else {
					w49 = -357.81586;
				}
			}
		}
	}
	float w50;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[23]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[8]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w50 = -861.1042;
				} else {
					w50 = -468.6662;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w50 = -355.65198;
				} else {
					w50 = -73.78846;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[24]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w50 = -271.01035;
				} else {
					w50 = -35.427074;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[6]) {
					w50 = 77.318535;
				} else {
					w50 = 342.936;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[4]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w50 = -367.2346;
				} else {
					w50 = 244.9353;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
					w50 = 510.1544;
				} else {
					w50 = 1084.45;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w50 = 1555.5834;
				} else {
					w50 = -36.454357;
				}
			} else {
				w50 = 3658.0115;
			}
		}
	}
	float w51;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[5]) {
					w51 = -696.733;
				} else {
					w51 = -417.80316;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
					w51 = -341.51675;
				} else {
					w51 = -83.77725;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[3]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[0]) {
					w51 = -299.4421;
				} else {
					w51 = 58.916077;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[42]) {
					w51 = 302.05936;
				} else {
					w51 = 714.12665;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[44]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[8]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[7]) {
					w51 = 104.806786;
				} else {
					w51 = 587.5884;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w51 = 739.6855;
				} else {
					w51 = 1227.5574;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[1]) {
					w51 = 1478.4331;
				} else {
					w51 = -353.8732;
				}
			} else {
				w51 = 3463.1052;
			}
		}
	}
	float w52;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[23]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[8]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w52 = -658.353;
				} else {
					w52 = -404.44418;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w52 = -345.52307;
				} else {
					w52 = -70.54347;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[24]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[4]) {
					w52 = -199.95935;
				} else {
					w52 = 13.326176;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[1]) {
					w52 = -215.25974;
				} else {
					w52 = 235.44267;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[4]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w52 = -360.10638;
				} else {
					w52 = 236.75362;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
					w52 = 496.44403;
				} else {
					w52 = 1052.8622;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[40]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[5]) {
					w52 = 1017.50836;
				} else {
					w52 = 1552.7361;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w52 = 2813.0203;
				} else {
					w52 = -350.33444;
				}
			}
		}
	}
	float w53;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[4]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w53 = -953.892;
				} else {
					w53 = -499.56192;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[3]) {
					w53 = -325.23822;
				} else {
					w53 = 17.269508;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[41]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[5]) {
					w53 = -345.04865;
				} else {
					w53 = -29.545147;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w53 = 224.24565;
				} else {
					w53 = 693.8461;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[9]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[8]) {
					w53 = 247.86533;
				} else {
					w53 = 677.6171;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[5]) {
					w53 = 420.60086;
				} else {
					w53 = 1305.1449;
				}
			}
		} else {
			if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[5]) {
					w53 = 879.01965;
				} else {
					w53 = -98.48414;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
					w53 = 1332.2555;
				} else {
					w53 = 2574.553;
				}
			}
		}
	}
	float w54;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[23]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[8]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[2]) {
					w54 = -726.01434;
				} else {
					w54 = -430.69855;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w54 = -357.68558;
				} else {
					w54 = -119.83529;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[45]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w54 = -198.91553;
				} else {
					w54 = 62.054684;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[3]) {
					w54 = 418.07162;
				} else {
					w54 = 142.92453;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[4]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w54 = -350.75485;
				} else {
					w54 = 229.15837;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
					w54 = 482.0889;
				} else {
					w54 = 1024.8452;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w54 = 1474.7067;
				} else {
					w54 = -59.07703;
				}
			} else {
				w54 = 3517.2888;
			}
		}
	}
	float w55;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[6]) {
					w55 = -557.28735;
				} else {
					w55 = -289.83322;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
					w55 = -323.1204;
				} else {
					w55 = -80.28056;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[3]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[0]) {
					w55 = -282.8822;
				} else {
					w55 = 56.774433;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[0]) {
					w55 = 452.1922;
				} else {
					w55 = -133.3543;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[9]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[8]) {
					w55 = 240.47662;
				} else {
					w55 = 657.523;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[5]) {
					w55 = 408.99487;
				} else {
					w55 = 1270.4486;
				}
			}
		} else {
			if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[5]) {
					w55 = 856.287;
				} else {
					w55 = -101.85715;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
					w55 = 1296.107;
				} else {
					w55 = 2514.4849;
				}
			}
		}
	}
	float w56;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[6]) {
					w56 = -658.53107;
				} else {
					w56 = -390.9357;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[10]) {
					w56 = -287.21014;
				} else {
					w56 = -56.92124;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[9]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[0]) {
					w56 = -17.361269;
				} else {
					w56 = 365.69562;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[32]) {
					w56 = 174.28952;
				} else {
					w56 = 463.10922;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w56 = 494.03793;
				} else {
					w56 = 998.55396;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[6]) {
					w56 = -422.728;
				} else {
					w56 = 177.76645;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w56 = 1460.5791;
				} else {
					w56 = -71.38988;
				}
			} else {
				w56 = 3449.4314;
			}
		}
	}
	float w57;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[3]) {
					w57 = -787.0732;
				} else {
					w57 = -457.98358;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[0]) {
					w57 = -288.60358;
				} else {
					w57 = -0.9237231;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[3]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
					w57 = -106.05829;
				} else {
					w57 = 156.82307;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[0]) {
					w57 = 439.8042;
				} else {
					w57 = -132.49046;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[9]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[8]) {
					w57 = 233.5266;
				} else {
					w57 = 637.58563;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[5]) {
					w57 = 397.46548;
				} else {
					w57 = 1237.323;
				}
			}
		} else {
			if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[5]) {
					w57 = 834.9193;
				} else {
					w57 = -106.04068;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
					w57 = 1262.2612;
				} else {
					w57 = 2455.6304;
				}
			}
		}
	}
	float w58;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[10]) {
					w58 = -551.0134;
				} else {
					w58 = -312.25424;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w58 = -317.45132;
				} else {
					w58 = -84.47696;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[9]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[0]) {
					w58 = -18.416359;
				} else {
					w58 = 357.1717;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w58 = 186.81671;
				} else {
					w58 = 462.6996;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[11]) {
					w58 = 494.10065;
				} else {
					w58 = 1014.9697;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[6]) {
					w58 = -415.38263;
				} else {
					w58 = 175.11154;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w58 = 1420.6711;
				} else {
					w58 = -83.20664;
				}
			} else {
				w58 = 3382.999;
			}
		}
	}
	float w59;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[4]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w59 = -904.2969;
				} else {
					w59 = -462.3542;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[3]) {
					w59 = -299.28082;
				} else {
					w59 = 30.360085;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[41]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[7]) {
					w59 = -258.74252;
				} else {
					w59 = 1.7634382;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w59 = 206.8649;
				} else {
					w59 = 648.3716;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[46]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
					w59 = -101.41084;
				} else {
					w59 = 467.40298;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[12]) {
					w59 = 660.3959;
				} else {
					w59 = 1176.5929;
				}
			}
		} else {
			if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[3]) {
					w59 = 991.7051;
				} else {
					w59 = 135.45125;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
					w59 = 1230.1447;
				} else {
					w59 = 2398.5122;
				}
			}
		}
	}
	float w60;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[6]) {
					w60 = -627.51416;
				} else {
					w60 = -368.57745;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[8]) {
					w60 = -348.5393;
				} else {
					w60 = -99.747894;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[9]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[0]) {
					w60 = -19.17712;
				} else {
					w60 = 349.81522;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w60 = 181.92525;
				} else {
					w60 = 451.36078;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w60 = 464.53058;
				} else {
					w60 = 952.85284;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[6]) {
					w60 = -405.26703;
				} else {
					w60 = 171.2513;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w60 = 1381.6941;
				} else {
					w60 = -95.321014;
				}
			} else {
				w60 = 3317.9573;
			}
		}
	}
	float w61;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[3]) {
					w61 = -754.90735;
				} else {
					w61 = -434.18222;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
					w61 = -320.09683;
				} else {
					w61 = -90.17545;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[3]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[0]) {
					w61 = -265.2652;
				} else {
					w61 = 54.97584;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[0]) {
					w61 = 419.5316;
				} else {
					w61 = -132.53441;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[9]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[8]) {
					w61 = 217.53644;
				} else {
					w61 = 600.72955;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[5]) {
					w61 = 370.73965;
				} else {
					w61 = 1172.4481;
				}
			}
		} else {
			if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[3]) {
					w61 = 971.06036;
				} else {
					w61 = 125.7977;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
					w61 = 1198.0458;
				} else {
					w61 = 2342.4216;
				}
			}
		}
	}
	float w62;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[43]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[5]) {
					w62 = -589.76245;
				} else {
					w62 = -332.13593;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[11]) {
					w62 = -279.79855;
				} else {
					w62 = -41.890434;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[9]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[0]) {
					w62 = -19.7078;
				} else {
					w62 = 341.9267;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w62 = 177.79306;
				} else {
					w62 = 439.4203;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[11]) {
					w62 = 465.43018;
				} else {
					w62 = 968.1749;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[6]) {
					w62 = -396.01102;
				} else {
					w62 = 169.0034;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w62 = 1343.882;
				} else {
					w62 = -106.90129;
				}
			} else {
				w62 = 3254.278;
			}
		}
	}
	float w63;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[3]) {
					w63 = -742.9495;
				} else {
					w63 = -426.61984;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w63 = -338.32578;
				} else {
					w63 = -98.18534;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[9]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[0]) {
					w63 = -19.413952;
				} else {
					w63 = 336.9747;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w63 = 116.545845;
				} else {
					w63 = 405.6327;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w63 = 443.00204;
				} else {
					w63 = 920.53015;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[6]) {
					w63 = -390.3834;
				} else {
					w63 = 166.9754;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w63 = 1324.1115;
				} else {
					w63 = -105.618416;
				}
			} else {
				w63 = 3217.6675;
			}
		}
	}
	float w64;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[4]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w64 = -863.863;
				} else {
					w64 = -433.9898;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[3]) {
					w64 = -277.7689;
				} else {
					w64 = 40.454044;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[7]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[5]) {
					w64 = -317.5816;
				} else {
					w64 = -18.723764;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[13]) {
					w64 = 219.1302;
				} else {
					w64 = 759.955;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[8]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[4]) {
					w64 = -152.25854;
				} else {
					w64 = 437.98608;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w64 = 623.9163;
				} else {
					w64 = 1165.6641;
				}
			}
		} else {
			if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[3]) {
					w64 = 941.4084;
				} else {
					w64 = 111.8326;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
					w64 = 1153.3226;
				} else {
					w64 = 2266.6987;
				}
			}
		}
	}
	float w65;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[23]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[0]) {
					w65 = -674.67975;
				} else {
					w65 = -334.2268;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w65 = -415.8764;
				} else {
					w65 = -218.62949;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[5]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[4]) {
					w65 = -503.9987;
				} else {
					w65 = -198.60725;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[36]) {
					w65 = -55.394073;
				} else {
					w65 = 180.55373;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[4]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w65 = -316.72348;
				} else {
					w65 = 184.0505;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
					w65 = 414.43933;
				} else {
					w65 = 903.78186;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w65 = 1266.2375;
				} else {
					w65 = -114.67219;
				}
			} else {
				w65 = 3155.9685;
			}
		}
	}
	float w66;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[43]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[27]) {
					w66 = -590.5134;
				} else {
					w66 = -321.7187;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[8]) {
					w66 = -308.18216;
				} else {
					w66 = -54.79391;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[6]) {
					w66 = -173.89409;
				} else {
					w66 = 84.368546;
				}
			} else {
				if (BsmtFullBath != NULL && *BsmtFullBath < cond_BsmtFullBath[0]) {
					w66 = 196.52681;
				} else {
					w66 = 523.52;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[11]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[1]) {
					w66 = 226.85526;
				} else {
					w66 = 799.49695;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[0]) {
					w66 = 1156.0609;
				} else {
					w66 = 98.69062;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w66 = 1382.4115;
				} else {
					w66 = -113.296074;
				}
			} else {
				w66 = 3120.464;
			}
		}
	}
	float w67;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w67 = -781.23987;
				} else {
					w67 = -414.5364;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[0]) {
					w67 = -250.65079;
				} else {
					w67 = -0.65728456;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[2]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[10]) {
					w67 = -81.82993;
				} else {
					w67 = 181.29279;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[4]) {
					w67 = 175.264;
				} else {
					w67 = 506.36026;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[8]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[4]) {
					w67 = -150.02133;
				} else {
					w67 = 418.47827;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w67 = 595.5714;
				} else {
					w67 = 1125.3081;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[7]) {
					w67 = 1359.754;
				} else {
					w67 = -382.20563;
				}
			} else {
				w67 = 2956.881;
			}
		}
	}
	float w68;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[43]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[27]) {
					w68 = -576.19855;
				} else {
					w68 = -312.32333;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w68 = -477.91083;
				} else {
					w68 = -82.55751;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[6]) {
					w68 = -170.14647;
				} else {
					w68 = 82.36052;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w68 = 258.10428;
				} else {
					w68 = 661.0228;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[11]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[1]) {
					w68 = 217.01204;
				} else {
					w68 = 780.0714;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[0]) {
					w68 = 1126.3093;
				} else {
					w68 = 94.29562;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w68 = 1348.1625;
				} else {
					w68 = -112.685486;
				}
			} else {
				w68 = 3052.094;
			}
		}
	}
	float w69;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[47]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[6]) {
					w69 = -545.112;
				} else {
					w69 = -299.923;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w69 = -470.94138;
				} else {
					w69 = -79.33369;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[8]) {
					w69 = -241.59827;
				} else {
					w69 = 62.932587;
				}
			} else {
				if (BsmtFullBath != NULL && *BsmtFullBath < cond_BsmtFullBath[0]) {
					w69 = 185.69827;
				} else {
					w69 = 503.99097;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[11]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[1]) {
					w69 = 213.82613;
				} else {
					w69 = 768.66284;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[0]) {
					w69 = 1110.0645;
				} else {
					w69 = 93.35265;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w69 = 1328.4104;
				} else {
					w69 = -111.33324;
				}
			} else {
				w69 = 3017.7578;
			}
		}
	}
	float w70;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w70 = -756.96704;
				} else {
					w70 = -398.70428;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[1]) {
					w70 = -147.49155;
				} else {
					w70 = -481.1164;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[2]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[10]) {
					w70 = -78.218285;
				} else {
					w70 = 177.0296;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[4]) {
					w70 = 167.5;
				} else {
					w70 = 489.9446;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[8]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[4]) {
					w70 = -147.18988;
				} else {
					w70 = 399.49426;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w70 = 569.095;
				} else {
					w70 = 1085.1749;
				}
			}
		} else {
			if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[3]) {
					w70 = 865.9617;
				} else {
					w70 = 80.45571;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
					w70 = 1059.392;
				} else {
					w70 = 2126.7158;
				}
			}
		}
	}
	float w71;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
			if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w71 = -670.77106;
				} else {
					w71 = -322.04877;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w71 = -228.17604;
				} else {
					w71 = -5.0289927;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[6]) {
					w71 = -164.32722;
				} else {
					w71 = 79.52633;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w71 = 246.2183;
				} else {
					w71 = 638.0676;
				}
			}
		}
	} else {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[12]) {
					w71 = -314.45892;
				} else {
					w71 = -53.89453;
				}
			} else {
				if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
					w71 = 542.52716;
				} else {
					w71 = -199.72368;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[40]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[1]) {
					w71 = 436.69675;
				} else {
					w71 = 1000.3807;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w71 = 2123.5603;
				} else {
					w71 = -338.79117;
				}
			}
		}
	}
	float w72;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[8]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w72 = -530.9814;
				} else {
					w72 = -305.2575;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w72 = -255.49236;
				} else {
					w72 = -20.707825;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[45]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[11]) {
					w72 = -69.64138;
				} else {
					w72 = 149.13562;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[4]) {
					w72 = 351.98608;
				} else {
					w72 = 95.746414;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w72 = 389.09216;
				} else {
					w72 = 832.3921;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[6]) {
					w72 = -372.17252;
				} else {
					w72 = 134.33757;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w72 = 1170.9302;
				} else {
					w72 = -124.76446;
				}
			} else {
				w72 = 2935.9927;
			}
		}
	}
	float w73;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[43]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
					w73 = -596.0114;
				} else {
					w73 = -300.52618;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[8]) {
					w73 = -286.11652;
				} else {
					w73 = -45.379833;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[14]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[9]) {
					w73 = -165.48761;
				} else {
					w73 = 168.18921;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
					w73 = 386.90906;
				} else {
					w73 = 796.28613;
				}
			}
		}
	} else {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[12]) {
					w73 = -318.62338;
				} else {
					w73 = -54.868923;
				}
			} else {
				if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
					w73 = 526.4753;
				} else {
					w73 = -195.90009;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[40]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[1]) {
					w73 = 422.32513;
				} else {
					w73 = 973.37286;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w73 = 2073.9822;
				} else {
					w73 = -336.7249;
				}
			}
		}
	}
	float w74;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[3]) {
					w74 = -659.77734;
				} else {
					w74 = -365.8456;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[1]) {
					w74 = -138.32256;
				} else {
					w74 = -461.1461;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[41]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[7]) {
					w74 = -74.81972;
				} else {
					w74 = 152.98964;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w74 = -319.7586;
				} else {
					w74 = 332.221;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[8]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[4]) {
					w74 = -141.9969;
				} else {
					w74 = 375.62656;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w74 = 535.72534;
				} else {
					w74 = 1037.1595;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[7]) {
					w74 = 1243.6715;
				} else {
					w74 = -391.89932;
				}
			} else {
				w74 = 2755.2485;
			}
		}
	}
	float w75;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
			if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w75 = -644.4858;
				} else {
					w75 = -304.9823;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
					w75 = -391.09628;
				} else {
					w75 = -69.10974;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[14]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[12]) {
					w75 = 51.669727;
				} else {
					w75 = 374.81644;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[0]) {
					w75 = 342.43024;
				} else {
					w75 = 696.93933;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[11]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[8]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[2]) {
					w75 = -103.859146;
				} else {
					w75 = 464.65417;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[14]) {
					w75 = 568.10706;
				} else {
					w75 = 1137.7164;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[9]) {
					w75 = 1137.254;
				} else {
					w75 = -414.20544;
				}
			} else {
				w75 = 2722.1853;
			}
		}
	}
	float w76;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[7]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[10]) {
					w76 = -444.54398;
				} else {
					w76 = -233.13046;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[8]) {
					w76 = -284.6655;
				} else {
					w76 = -65.01353;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[8]) {
					w76 = -229.24948;
				} else {
					w76 = 57.206875;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[9]) {
					w76 = 177.37413;
				} else {
					w76 = 482.32642;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[11]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[1]) {
					w76 = 176.72557;
				} else {
					w76 = 704.2696;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[0]) {
					w76 = 1020.40686;
				} else {
					w76 = 70.27875;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w76 = 1213.8068;
				} else {
					w76 = -131.0392;
				}
			} else {
				w76 = 2818.0093;
			}
		}
	}
	float w77;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[8]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[10]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w77 = -515.5964;
				} else {
					w77 = -246.63992;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w77 = -194.57198;
				} else {
					w77 = 163.04019;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[45]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w77 = -154.45029;
				} else {
					w77 = 54.13138;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[4]) {
					w77 = 332.6307;
				} else {
					w77 = 86.611275;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w77 = 360.5245;
				} else {
					w77 = 784.6424;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[10]) {
					w77 = -375.80884;
				} else {
					w77 = 75.833435;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w77 = 1096.3313;
				} else {
					w77 = -129.46667;
				}
			} else {
				w77 = 2786.3066;
			}
		}
	}
	float w78;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
			if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w78 = -624.6151;
				} else {
					w78 = -292.7474;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w78 = -207.75655;
				} else {
					w78 = 2.3853908;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[15]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[12]) {
					w78 = 46.286476;
				} else {
					w78 = 359.982;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
					w78 = 357.94833;
				} else {
					w78 = 752.54095;
				}
			}
		}
	} else {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[12]) {
					w78 = -326.92587;
				} else {
					w78 = -58.708965;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w78 = 297.23798;
				} else {
					w78 = 708.77606;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[40]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[1]) {
					w78 = 385.83334;
				} else {
					w78 = 910.87006;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w78 = 1965.9312;
				} else {
					w78 = -336.4099;
				}
			}
		}
	}
	float w79;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[15]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w79 = -627.498;
				} else {
					w79 = -344.6905;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[35]) {
					w79 = -505.9713;
				} else {
					w79 = -193.33382;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[7]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[5]) {
					w79 = -260.9773;
				} else {
					w79 = -14.15725;
				}
			} else {
				if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
					w79 = 289.91678;
				} else {
					w79 = -380.89014;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[8]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[4]) {
					w79 = -140.80316;
				} else {
					w79 = 347.08688;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w79 = 494.87906;
				} else {
					w79 = 980.4894;
				}
			}
		} else {
			if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[1]) {
					w79 = 854.3709;
				} else {
					w79 = -107.75982;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w79 = 1954.1979;
				} else {
					w79 = -409.32013;
				}
			}
		}
	}
	float w80;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[3]) {
					w80 = -627.9058;
				} else {
					w80 = -341.1623;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w80 = -296.16638;
				} else {
					w80 = -73.07125;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[15]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[9]) {
					w80 = -161.34743;
				} else {
					w80 = 152.27876;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[0]) {
					w80 = 317.71548;
				} else {
					w80 = 657.99;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[11]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[8]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[2]) {
					w80 = -114.34208;
				} else {
					w80 = 429.5105;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[14]) {
					w80 = 524.05286;
				} else {
					w80 = 1073.4918;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[9]) {
					w80 = 1069.1244;
				} else {
					w80 = -405.22702;
				}
			} else {
				w80 = 2586.6238;
			}
		}
	}
	float w81;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[23]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[0]) {
					w81 = -580.0146;
				} else {
					w81 = -261.72833;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w81 = -342.23828;
				} else {
					w81 = -165.96324;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[5]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[4]) {
					w81 = -436.08737;
				} else {
					w81 = -151.02776;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[11]) {
					w81 = -51.583977;
				} else {
					w81 = 143.40544;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[4]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[16]) {
					w81 = -278.128;
				} else {
					w81 = 156.59169;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[11]) {
					w81 = 299.00137;
				} else {
					w81 = 678.0685;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[40]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[5]) {
					w81 = 620.01483;
				} else {
					w81 = 1083.5377;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w81 = 2067.3022;
				} else {
					w81 = -401.17468;
				}
			}
		}
	}
	float w82;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w82 = -673.1885;
				} else {
					w82 = -344.4482;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w82 = -287.88223;
				} else {
					w82 = -70.82343;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[15]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[12]) {
					w82 = 41.910847;
				} else {
					w82 = 343.98685;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
					w82 = 337.92975;
				} else {
					w82 = 719.16144;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[11]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[8]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[2]) {
					w82 = -115.75086;
				} else {
					w82 = 417.13162;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[14]) {
					w82 = 509.3176;
				} else {
					w82 = 1045.9602;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[9]) {
					w82 = 1041.6073;
				} else {
					w82 = -397.16296;
				}
			} else {
				w82 = 2534.944;
			}
		}
	}
	float w83;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[10]) {
					w83 = -500.27994;
				} else {
					w83 = -236.04222;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[12]) {
					w83 = -139.64102;
				} else {
					w83 = 189.95479;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[12]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[3]) {
					w83 = -182.75648;
				} else {
					w83 = 58.392673;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[17]) {
					w83 = 221.802;
				} else {
					w83 = 716.6893;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[8]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[1]) {
					w83 = -383.9482;
				} else {
					w83 = 304.49667;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w83 = 463.96884;
				} else {
					w83 = 936.4062;
				}
			}
		} else {
			if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[1]) {
					w83 = 808.3196;
				} else {
					w83 = -115.35568;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w83 = 1870.8228;
				} else {
					w83 = -393.19138;
				}
			}
		}
	}
	float w84;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[11]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[6]) {
					w84 = -592.96204;
				} else {
					w84 = -303.04135;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w84 = -460.8749;
				} else {
					w84 = -105.00921;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[8]) {
					w84 = -223.39915;
				} else {
					w84 = 50.347473;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[9]) {
					w84 = 153.65645;
				} else {
					w84 = 442.51703;
				}
			}
		}
	} else {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[12]) {
					w84 = -332.3337;
				} else {
					w84 = -64.79756;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w84 = 262.70642;
				} else {
					w84 = 664.44965;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[40]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[1]) {
					w84 = 349.164;
				} else {
					w84 = 844.2592;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w84 = 1835.8969;
				} else {
					w84 = -322.2446;
				}
			}
		}
	}
	float w85;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[15]) {
					w85 = -450.27274;
				} else {
					w85 = -200.89098;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w85 = -118.69842;
				} else {
					w85 = 141.39192;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[15]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[9]) {
					w85 = -158.18753;
				} else {
					w85 = 142.34337;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[0]) {
					w85 = 296.9102;
				} else {
					w85 = 622.1607;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[11]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[8]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[2]) {
					w85 = -119.602715;
				} else {
					w85 = 400.2343;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[14]) {
					w85 = 485.8966;
				} else {
					w85 = 1007.897;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[9]) {
					w85 = 1001.41064;
				} else {
					w85 = -390.97055;
				}
			} else {
				w85 = 2460.0444;
			}
		}
	}
	float w86;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[48]) {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[1]) {
					w86 = -596.5103;
				} else {
					w86 = 84.886345;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[4]) {
					w86 = -415.34357;
				} else {
					w86 = -203.15706;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[11]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w86 = -339.28394;
				} else {
					w86 = -93.336395;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[24]) {
					w86 = -73.8525;
				} else {
					w86 = 118.57687;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[4]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w86 = -315.9779;
				} else {
					w86 = 110.62069;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
					w86 = 295.92603;
				} else {
					w86 = 692.03815;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w86 = 950.89386;
				} else {
					w86 = -145.63875;
				}
			} else {
				w86 = 2560.6084;
			}
		}
	}
	float w87;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[10]) {
					w87 = -476.96957;
				} else {
					w87 = -224.24985;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[12]) {
					w87 = -134.00233;
				} else {
					w87 = 188.42575;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[0]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[10]) {
					w87 = -71.89716;
				} else {
					w87 = 127.51357;
				}
			} else {
				if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
					w87 = 281.9673;
				} else {
					w87 = -325.0554;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[18]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[1]) {
					w87 = -377.93076;
				} else {
					w87 = 352.55508;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
					w87 = 272.09714;
				} else {
					w87 = 932.76013;
				}
			}
		} else {
			if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[1]) {
					w87 = 762.2108;
				} else {
					w87 = -121.067986;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w87 = 1792.269;
				} else {
					w87 = -385.60443;
				}
			}
		}
	}
	float w88;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[12]) {
					w88 = -420.00665;
				} else {
					w88 = -210.18184;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
					w88 = -196.96985;
				} else {
					w88 = 4.902807;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[14]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[9]) {
					w88 = -155.21057;
				} else {
					w88 = 137.28494;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
					w88 = 314.93588;
				} else {
					w88 = 674.61426;
				}
			}
		}
	} else {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[6]) {
					w88 = -37.769707;
				} else {
					w88 = -303.04678;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w88 = 242.03734;
				} else {
					w88 = 635.3817;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[40]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[0]) {
					w88 = 805.0497;
				} else {
					w88 = 334.96622;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w88 = 1757.052;
				} else {
					w88 = -316.6679;
				}
			}
		}
	}
	float w89;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[48]) {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[1]) {
					w89 = -579.36053;
				} else {
					w89 = 90.97705;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[11]) {
					w89 = -381.93997;
				} else {
					w89 = -184.9791;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[11]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w89 = -326.3303;
				} else {
					w89 = -89.94678;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[24]) {
					w89 = -70.05766;
				} else {
					w89 = 114.70685;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[4]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w89 = -305.87915;
				} else {
					w89 = 105.66946;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
					w89 = 285.35425;
				} else {
					w89 = 664.2691;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[1]) {
					w89 = 913.1437;
				} else {
					w89 = -149.53078;
				}
			} else {
				w89 = 2491.8716;
			}
		}
	}
	float w90;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[23]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[0]) {
					w90 = -532.2848;
				} else {
					w90 = -228.68549;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w90 = -304.876;
				} else {
					w90 = -143.24571;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[5]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[4]) {
					w90 = -402.1009;
				} else {
					w90 = -130.55222;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[13]) {
					w90 = 12.462379;
				} else {
					w90 = 367.54483;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[2]) {
					w90 = 115.20881;
				} else {
					w90 = -309.36163;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
					w90 = 258.8808;
				} else {
					w90 = 558.89374;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
					w90 = 623.98724;
				} else {
					w90 = 1297.6616;
				}
			} else {
				w90 = 2463.8381;
			}
		}
	}
	float w91;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[12]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w91 = -439.7614;
				} else {
					w91 = -189.8339;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w91 = -77.02722;
				} else {
					w91 = 287.86884;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[45]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[11]) {
					w91 = -58.004696;
				} else {
					w91 = 133.84097;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w91 = 191.49086;
				} else {
					w91 = 513.8774;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[11]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[8]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[2]) {
					w91 = -130.11642;
				} else {
					w91 = 362.85873;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[14]) {
					w91 = 441.82367;
				} else {
					w91 = 943.5334;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[9]) {
					w91 = 934.0362;
				} else {
					w91 = -391.45474;
				}
			} else {
				w91 = 2314.5393;
			}
		}
	}
	float w92;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[11]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[6]) {
					w92 = -546.09686;
				} else {
					w92 = -274.00833;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w92 = -427.7868;
				} else {
					w92 = -90.17659;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[15]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[9]) {
					w92 = -152.34789;
				} else {
					w92 = 129.09491;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
					w92 = 298.89587;
				} else {
					w92 = 646.81024;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[11]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
				if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
					w92 = 312.48917;
				} else {
					w92 = -290.3332;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[14]) {
					w92 = 436.0564;
				} else {
					w92 = 1222.6902;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[9]) {
					w92 = 920.3117;
				} else {
					w92 = -387.54022;
				}
			} else {
				w92 = 2286.765;
			}
		}
	}
	float w93;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[48]) {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[1]) {
					w93 = -555.07367;
				} else {
					w93 = 100.793434;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[4]) {
					w93 = -383.73074;
				} else {
					w93 = -182.76723;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[11]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w93 = -312.43073;
				} else {
					w93 = -83.80225;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[24]) {
					w93 = -65.79035;
				} else {
					w93 = 110.7695;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[4]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[18]) {
					w93 = -550.0868;
				} else {
					w93 = 32.005558;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[11]) {
					w93 = 234.06631;
				} else {
					w93 = 546.6239;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[40]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[5]) {
					w93 = 507.7269;
				} else {
					w93 = 932.9958;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w93 = 1824.1146;
				} else {
					w93 = -383.66473;
				}
			}
		}
	}
	float w94;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[12]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
					w94 = -463.83206;
				} else {
					w94 = -189.29;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w94 = -72.92747;
				} else {
					w94 = 282.9871;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[45]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[3]) {
					w94 = -55.98332;
				} else {
					w94 = 131.77518;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w94 = 182.90079;
				} else {
					w94 = 497.56284;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[11]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[2]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
					w94 = 1.6897386;
				} else {
					w94 = 454.20715;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[2]) {
					w94 = 483.2598;
				} else {
					w94 = 1579.2462;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w94 = 931.18274;
				} else {
					w94 = -4.0304294;
				}
			} else {
				w94 = 2241.267;
			}
		}
	}
	float w95;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[10]) {
					w95 = -438.54636;
				} else {
					w95 = -203.43973;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w95 = -134.94133;
				} else {
					w95 = 143.7286;
				}
			}
		} else {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[7]) {
					w95 = 0.68799245;
				} else {
					w95 = 512.153;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[3]) {
					w95 = 149.61583;
				} else {
					w95 = 508.45932;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[8]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[1]) {
					w95 = -363.96402;
				} else {
					w95 = 251.63972;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w95 = 383.4623;
				} else {
					w95 = 823.91156;
				}
			}
		} else {
			if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[14]) {
					w95 = 61.931587;
				} else {
					w95 = 749.4941;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w95 = 1653.3672;
				} else {
					w95 = -379.78772;
				}
			}
		}
	}
	float w96;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[48]) {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[13]) {
					w96 = -572.9561;
				} else {
					w96 = -4.67082;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w96 = -475.69064;
				} else {
					w96 = -203.9369;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w96 = -226.42807;
				} else {
					w96 = -38.662357;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[24]) {
					w96 = -59.286903;
				} else {
					w96 = 121.28042;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[4]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w96 = -288.08878;
				} else {
					w96 = 95.22347;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[11]) {
					w96 = 223.798;
				} else {
					w96 = 527.63165;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[40]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[5]) {
					w96 = 485.75912;
				} else {
					w96 = 897.8056;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w96 = 1762.4712;
				} else {
					w96 = -375.9899;
				}
			}
		}
	}
	float w97;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[3]) {
					w97 = -531.2858;
				} else {
					w97 = -276.803;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[3]) {
					w97 = -58.310703;
				} else {
					w97 = -274.27115;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[14]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[18]) {
					w97 = -505.19226;
				} else {
					w97 = 93.69614;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[0]) {
					w97 = 255.95868;
				} else {
					w97 = 550.5171;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[11]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[2]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
					w97 = -2.7791944;
				} else {
					w97 = 431.8837;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[2]) {
					w97 = 464.94678;
				} else {
					w97 = 1525.7213;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w97 = 898.3516;
				} else {
					w97 = -13.098866;
				}
			} else {
				w97 = 2177.0862;
			}
		}
	}
	float w98;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[10]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[10]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w98 = -413.1132;
				} else {
					w98 = -188.03226;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w98 = -153.17007;
				} else {
					w98 = 166.8116;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[13]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[3]) {
					w98 = -29.427345;
				} else {
					w98 = 144.44072;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[19]) {
					w98 = 181.21222;
				} else {
					w98 = 432.18143;
				}
			}
		}
	} else {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[14]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
					w98 = 40.109352;
				} else {
					w98 = 545.9059;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[15]) {
					w98 = 375.96262;
				} else {
					w98 = 1006.80634;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
					w98 = 506.4344;
				} else {
					w98 = 1106.1305;
				}
			} else {
				w98 = 2150.961;
			}
		}
	}
	float w99;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[15]) {
					w99 = -442.94937;
				} else {
					w99 = -199.81267;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w99 = -128.20908;
				} else {
					w99 = 143.3571;
				}
			}
		} else {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[7]) {
					w99 = 0.27694368;
				} else {
					w99 = 498.65677;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[3]) {
					w99 = 144.49687;
				} else {
					w99 = 487.96237;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[19]) {
			if (FullBath != NULL && *FullBath < cond_FullBath[0]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
					w99 = 156.41881;
				} else {
					w99 = 409.34085;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[5]) {
					w99 = 637.31665;
				} else {
					w99 = 1633.5664;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[7]) {
					w99 = 946.66644;
				} else {
					w99 = -21.082344;
				}
			} else {
				w99 = 2125.1494;
			}
		}
	}
	float w100;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[12]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w100 = -315.17157;
				} else {
					w100 = -134.09682;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[14]) {
					w100 = -62.50389;
				} else {
					w100 = 277.6705;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[45]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
					w100 = -288.621;
				} else {
					w100 = 21.188824;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w100 = 168.08635;
				} else {
					w100 = 467.64047;
				}
			}
		}
	} else {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[12]) {
					w100 = -357.11063;
				} else {
					w100 = -85.955956;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w100 = 191.60194;
				} else {
					w100 = 556.17865;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[40]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[0]) {
					w100 = 693.2101;
				} else {
					w100 = 267.61093;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w100 = 1543.6346;
				} else {
					w100 = -323.48953;
				}
			}
		}
	}
	float w101;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[41]) {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[1]) {
					w101 = -544.00073;
				} else {
					w101 = 119.59459;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[4]) {
					w101 = -353.5504;
				} else {
					w101 = -160.44135;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[3]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
					w101 = -283.15945;
				} else {
					w101 = -66.86208;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w101 = 719.6653;
				} else {
					w101 = 94.67252;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[21]) {
					w101 = -582.32855;
				} else {
					w101 = -10.238026;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
					w101 = 101.42428;
				} else {
					w101 = 377.0257;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
					w101 = 525.70746;
				} else {
					w101 = 1116.9218;
				}
			} else {
				w101 = 2210.227;
			}
		}
	}
	float w102;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w102 = -462.0036;
				} else {
					w102 = -177.025;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w102 = -226.10013;
				} else {
					w102 = -57.60626;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[41]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[7]) {
					w102 = -49.53776;
				} else {
					w102 = 147.78114;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
					w102 = 123.33845;
				} else {
					w102 = 483.28983;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[11]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[4]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[2]) {
					w102 = -108.6387;
				} else {
					w102 = 269.92575;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[4]) {
					w102 = 444.2679;
				} else {
					w102 = 1452.075;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w102 = 849.74866;
				} else {
					w102 = -40.96371;
				}
			} else {
				w102 = 2060.1008;
			}
		}
	}
	float w103;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[12]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w103 = -305.56656;
				} else {
					w103 = -127.745155;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w103 = -66.08192;
				} else {
					w103 = 271.19238;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[45]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
					w103 = -282.2947;
				} else {
					w103 = 21.857527;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w103 = 160.48932;
				} else {
					w103 = 452.7494;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[11]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[2]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
					w103 = -15.225549;
				} else {
					w103 = 395.00427;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[2]) {
					w103 = 428.58575;
				} else {
					w103 = 1434.6503;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w103 = 837.2795;
				} else {
					w103 = -40.4516;
				}
			} else {
				w103 = 2035.3798;
			}
		}
	}
	float w104;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w104 = -503.93326;
				} else {
					w104 = -258.90976;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w104 = -163.70401;
				} else {
					w104 = 328.9764;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[0]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[13]) {
					w104 = -47.406635;
				} else {
					w104 = 490.88226;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[15]) {
					w104 = -13.416176;
				} else {
					w104 = 362.0328;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[19]) {
			if (FullBath != NULL && *FullBath < cond_FullBath[0]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[6]) {
					w104 = -445.24304;
				} else {
					w104 = 286.86118;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[5]) {
					w104 = 602.4261;
				} else {
					w104 = 1557.9513;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[9]) {
					w104 = 865.7127;
				} else {
					w104 = -247.21974;
				}
			} else {
				w104 = 2010.9553;
			}
		}
	}
	float w105;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w105 = -448.6001;
				} else {
					w105 = -169.52715;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w105 = -218.59503;
				} else {
					w105 = -54.171688;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[23]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[11]) {
					w105 = -81.609634;
				} else {
					w105 = 115.063896;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[49]) {
					w105 = 97.821434;
				} else {
					w105 = 507.17523;
				}
			}
		}
	} else {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[12]) {
					w105 = -358.97144;
				} else {
					w105 = -95.06873;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w105 = 172.04156;
				} else {
					w105 = 526.8351;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[40]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w105 = 205.96745;
				} else {
					w105 = 641.8635;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w105 = 1463.0417;
				} else {
					w105 = -323.94022;
				}
			}
		}
	}
	float w106;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[41]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[50]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[6]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
					w106 = -481.46683;
				} else {
					w106 = 104.239624;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[51]) {
					w106 = -387.54245;
				} else {
					w106 = -180.76247;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
					w106 = -476.68008;
				} else {
					w106 = -10.696347;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[3]) {
					w106 = -93.145615;
				} else {
					w106 = 99.37352;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[21]) {
					w106 = -561.56586;
				} else {
					w106 = -13.237391;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
					w106 = 94.403946;
				} else {
					w106 = 355.4696;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
					w106 = 488.60007;
				} else {
					w106 = 1059.7504;
				}
			} else {
				w106 = 2100.2053;
			}
		}
	}
	float w107;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w107 = -437.3817;
				} else {
					w107 = -164.98697;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w107 = -213.12804;
				} else {
					w107 = -52.260426;
				}
			}
		} else {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[8]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[11]) {
					w107 = -71.485466;
				} else {
					w107 = 121.50543;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[49]) {
					w107 = 142.67703;
				} else {
					w107 = 595.0397;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[11]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[2]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w107 = -133.28903;
				} else {
					w107 = 234.9976;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[2]) {
					w107 = 407.26135;
				} else {
					w107 = 1376.1052;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w107 = 800.33527;
				} else {
					w107 = -56.693043;
				}
			} else {
				w107 = 1949.299;
			}
		}
	}
	float w108;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[20]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w108 = -590.7022;
				} else {
					w108 = -271.1316;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[3]) {
					w108 = -153.51326;
				} else {
					w108 = 75.09599;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[0]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[7]) {
					w108 = -153.67538;
				} else {
					w108 = 38.699333;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[15]) {
					w108 = -11.323386;
				} else {
					w108 = 349.7465;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[8]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[1]) {
					w108 = -346.3514;
				} else {
					w108 = 206.01865;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w108 = 314.24487;
				} else {
					w108 = 714.9831;
				}
			}
		} else {
			if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[14]) {
					w108 = 13.130156;
				} else {
					w108 = 640.72723;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w108 = 1450.8477;
				} else {
					w108 = -397.22906;
				}
			}
		}
	}
	float w109;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[41]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[15]) {
					w109 = -765.8253;
				} else {
					w109 = -455.741;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[15]) {
					w109 = -396.481;
				} else {
					w109 = -217.96881;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w109 = -264.64136;
				} else {
					w109 = -83.5629;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[5]) {
					w109 = -47.192944;
				} else {
					w109 = 150.56923;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[21]) {
					w109 = -547.73004;
				} else {
					w109 = -13.5827675;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w109 = -229.19868;
				} else {
					w109 = 291.33133;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[10]) {
					w109 = 748.9081;
				} else {
					w109 = 63.463806;
				}
			} else {
				w109 = 2038.3258;
			}
		}
	}
	float w110;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[12]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[18]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w110 = -415.3579;
				} else {
					w110 = -193.33328;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w110 = -431.76978;
				} else {
					w110 = -123.037834;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[24]) {
					w110 = -417.5127;
				} else {
					w110 = -53.729843;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[6]) {
					w110 = 255.56566;
				} else {
					w110 = 63.61433;
				}
			}
		}
	} else {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[12]) {
					w110 = -359.51477;
				} else {
					w110 = -96.96787;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w110 = 153.06487;
				} else {
					w110 = 501.51938;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[40]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[0]) {
					w110 = 614.6813;
				} else {
					w110 = 221.82108;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w110 = 1387.301;
				} else {
					w110 = -323.82483;
				}
			}
		}
	}
	float w111;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w111 = -495.08963;
				} else {
					w111 = -265.79886;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[17]) {
					w111 = -213.958;
				} else {
					w111 = -52.093967;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
					w111 = -103.08265;
				} else {
					w111 = 241.06358;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[18]) {
					w111 = -0.81664425;
				} else {
					w111 = 364.02325;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[46]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[11]) {
					w111 = 22.553762;
				} else {
					w111 = 263.63824;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[7]) {
					w111 = 715.40674;
				} else {
					w111 = 322.66937;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[21]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w111 = 215.04732;
				} else {
					w111 = 594.8098;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
					w111 = 711.68646;
				} else {
					w111 = 1872.6302;
				}
			}
		}
	}
	float w112;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[41]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[52]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[18]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
					w112 = -458.28543;
				} else {
					w112 = 110.0455;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[51]) {
					w112 = -366.80713;
				} else {
					w112 = -161.98705;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w112 = -629.81494;
				} else {
					w112 = -121.959435;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[1]) {
					w112 = -101.71585;
				} else {
					w112 = 68.74782;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[21]) {
					w112 = -531.5235;
				} else {
					w112 = -14.43446;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w112 = -225.71808;
				} else {
					w112 = 280.84644;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[19]) {
					w112 = 496.4316;
				} else {
					w112 = 1174.5815;
				}
			} else {
				w112 = 1978.7205;
			}
		}
	}
	float w113;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[22]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w113 = -565.4407;
				} else {
					w113 = -245.06448;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w113 = -119.04392;
				} else {
					w113 = 282.76447;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[0]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[13]) {
					w113 = -43.92397;
				} else {
					w113 = 464.667;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[15]) {
					w113 = -11.817256;
				} else {
					w113 = 333.7428;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[19]) {
			if (FullBath != NULL && *FullBath < cond_FullBath[0]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[6]) {
					w113 = -430.0907;
				} else {
					w113 = 250.30482;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[5]) {
					w113 = 542.19476;
				} else {
					w113 = 1444.9491;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[11]) {
					w113 = 802.7789;
				} else {
					w113 = -162.40039;
				}
			} else {
				w113 = 1831.5073;
			}
		}
	}
	float w114;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w114 = -407.91077;
				} else {
					w114 = -144.72997;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w114 = -197.6404;
				} else {
					w114 = -44.76345;
				}
			}
		} else {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[8]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[11]) {
					w114 = -65.726364;
				} else {
					w114 = 111.48617;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[49]) {
					w114 = 135.39128;
				} else {
					w114 = 559.3866;
				}
			}
		}
	} else {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[19]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
					w114 = 101.85887;
				} else {
					w114 = 594.4683;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[3]) {
					w114 = 140.49498;
				} else {
					w114 = 1022.756;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w114 = -310.0998;
				} else {
					w114 = 677.30334;
				}
			} else {
				w114 = 1809.5294;
			}
		}
	}
	float w115;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w115 = -475.7008;
				} else {
					w115 = -253.3198;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[17]) {
					w115 = -204.37729;
				} else {
					w115 = -47.402412;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
					w115 = -99.14313;
				} else {
					w115 = 234.63652;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[18]) {
					w115 = 2.8644521;
				} else {
					w115 = 355.01675;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[46]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[11]) {
					w115 = 20.520407;
				} else {
					w115 = 252.47214;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[7]) {
					w115 = 689.98083;
				} else {
					w115 = 311.55264;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[21]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w115 = 201.66808;
				} else {
					w115 = 566.10956;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[12]) {
					w115 = 516.26495;
				} else {
					w115 = 1174.8702;
				}
			}
		}
	}
	float w116;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[41]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[15]) {
					w116 = -725.91187;
				} else {
					w116 = -428.91144;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[25]) {
					w116 = -380.73505;
				} else {
					w116 = -210.40378;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[14]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[4]) {
					w116 = -295.07065;
				} else {
					w116 = -123.49695;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[4]) {
					w116 = -100.1996;
				} else {
					w116 = 38.690662;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[21]) {
					w116 = -514.7929;
				} else {
					w116 = -14.99924;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
					w116 = 163.00075;
				} else {
					w116 = 405.91144;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[40]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[5]) {
					w116 = 357.11078;
				} else {
					w116 = 704.8512;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w116 = 1445.1633;
				} else {
					w116 = -423.75876;
				}
			}
		}
	}
	float w117;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[13]) {
					w117 = -482.54443;
				} else {
					w117 = 15.325371;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
					w117 = -213.49013;
				} else {
					w117 = 124.69519;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
					w117 = -361.6841;
				} else {
					w117 = -105.61728;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[16]) {
					w117 = -0.7101051;
				} else {
					w117 = 259.76028;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[21]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[6]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[9]) {
					w117 = -10.359056;
				} else {
					w117 = 195.34492;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[10]) {
					w117 = 315.97134;
				} else {
					w117 = 764.1683;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
					w117 = 460.73068;
				} else {
					w117 = 1034.9615;
				}
			} else {
				w117 = 1762.1969;
			}
		}
	}
	float w118;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[19]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
					w118 = -416.81018;
				} else {
					w118 = -178.21463;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w118 = -55.62917;
				} else {
					w118 = 257.21243;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[53]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[20]) {
					w118 = -160.7579;
				} else {
					w118 = -16.64315;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[6]) {
					w118 = 283.4492;
				} else {
					w118 = 74.951584;
				}
			}
		}
	} else {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[19]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
					w118 = 90.76141;
				} else {
					w118 = 572.8511;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[3]) {
					w118 = 116.97257;
				} else {
					w118 = 980.69196;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[1]) {
					w118 = 654.2792;
				} else {
					w118 = -216.10696;
				}
			} else {
				w118 = 1741.0507;
			}
		}
	}
	float w119;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[20]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[3]) {
					w119 = -308.67844;
				} else {
					w119 = -128.69809;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w119 = -117.38837;
				} else {
					w119 = 279.50455;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[0]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[13]) {
					w119 = -41.785213;
				} else {
					w119 = 445.1218;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[7]) {
					w119 = 177.07298;
				} else {
					w119 = 606.3413;
				}
			}
		}
	} else {
		if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[5]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[6]) {
					w119 = -426.0967;
				} else {
					w119 = 207.97015;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
					w119 = 103.435104;
				} else {
					w119 = 685.47833;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[5]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[7]) {
					w119 = 179.47356;
				} else {
					w119 = 656.2401;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
					w119 = 1620.6243;
				} else {
					w119 = -424.8385;
				}
			}
		}
	}
	float w120;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[41]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[52]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[18]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
					w120 = -424.312;
				} else {
					w120 = 118.0292;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[51]) {
					w120 = -339.07892;
				} else {
					w120 = -145.31946;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
					w120 = -415.36887;
				} else {
					w120 = 24.024492;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[3]) {
					w120 = -74.397125;
				} else {
					w120 = 91.50933;
				}
			}
		}
	} else {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w120 = -49.14211;
				} else {
					w120 = 314.85144;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[15]) {
					w120 = 217.49295;
				} else {
					w120 = 637.12854;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w120 = -338.23523;
				} else {
					w120 = 382.61407;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
					w120 = 1033.2025;
				} else {
					w120 = -420.59006;
				}
			}
		}
	}
	float w121;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
					w121 = -512.36285;
				} else {
					w121 = -276.08133;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[21]) {
					w121 = -143.29495;
				} else {
					w121 = 70.89787;
				}
			}
		} else {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
				if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
					w121 = 30.132053;
				} else {
					w121 = -430.74393;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[3]) {
					w121 = 122.02816;
				} else {
					w121 = 404.19156;
				}
			}
		}
	} else {
		if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[5]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[6]) {
					w121 = -420.37048;
				} else {
					w121 = 202.10875;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
					w121 = 99.938805;
				} else {
					w121 = 667.1048;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[5]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[7]) {
					w121 = 173.56639;
				} else {
					w121 = 643.0819;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
					w121 = 1584.9587;
				} else {
					w121 = -416.38416;
				}
			}
		}
	}
	float w122;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[13]) {
					w122 = -462.31046;
				} else {
					w122 = 19.57248;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
					w122 = -201.80267;
				} else {
					w122 = 125.33906;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
					w122 = -344.74124;
				} else {
					w122 = -97.682045;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w122 = -19.5917;
				} else {
					w122 = 168.4443;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[21]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[6]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[9]) {
					w122 = -13.13402;
				} else {
					w122 = 185.99474;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[13]) {
					w122 = 147.56097;
				} else {
					w122 = 504.16025;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
					w122 = 430.42557;
				} else {
					w122 = 982.2326;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w122 = 2015.7112;
				} else {
					w122 = 766.44354;
				}
			}
		}
	}
	float w123;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[41]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[15]) {
					w123 = -686.7367;
				} else {
					w123 = -399.40445;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[25]) {
					w123 = -355.87827;
				} else {
					w123 = -191.15417;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w123 = -229.4441;
				} else {
					w123 = -65.15395;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[6]) {
					w123 = -128.83842;
				} else {
					w123 = 43.72322;
				}
			}
		}
	} else {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w123 = -48.451447;
				} else {
					w123 = 308.03473;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[15]) {
					w123 = 208.1327;
				} else {
					w123 = 618.307;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w123 = -335.12225;
				} else {
					w123 = 369.26053;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
					w123 = 996.836;
				} else {
					w123 = -419.2835;
				}
			}
		}
	}
	float w124;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[19]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
					w124 = -393.88657;
				} else {
					w124 = -166.47833;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w124 = -50.72627;
				} else {
					w124 = 249.19719;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[53]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[20]) {
					w124 = -151.0745;
				} else {
					w124 = -12.981635;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[6]) {
					w124 = 268.27206;
				} else {
					w124 = 67.74929;
				}
			}
		}
	} else {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[12]) {
					w124 = -357.80435;
				} else {
					w124 = -103.11656;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w124 = 117.93435;
				} else {
					w124 = 415.6647;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[54]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w124 = 59.417576;
				} else {
					w124 = 499.50525;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w124 = 1112.3368;
				} else {
					w124 = -85.91162;
				}
			}
		}
	}
	float w125;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
					w125 = -512.42413;
				} else {
					w125 = -15.353437;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[14]) {
					w125 = -332.4652;
				} else {
					w125 = -123.50163;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[23]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[55]) {
					w125 = -381.10684;
				} else {
					w125 = -192.17703;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w125 = -59.66408;
				} else {
					w125 = 264.04456;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[21]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[6]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[9]) {
					w125 = -14.022686;
				} else {
					w125 = 179.54352;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[10]) {
					w125 = 284.82602;
				} else {
					w125 = 709.93134;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
					w125 = 412.81943;
				} else {
					w125 = 952.89264;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w125 = 1974.4631;
				} else {
					w125 = 737.6876;
				}
			}
		}
	}
	float w126;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[29]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w126 = -362.17712;
				} else {
					w126 = -116.57492;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w126 = -175.28575;
				} else {
					w126 = -35.969063;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[41]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[7]) {
					w126 = -38.98003;
				} else {
					w126 = 130.97447;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
					w126 = 94.57717;
				} else {
					w126 = 365.62952;
				}
			}
		}
	} else {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[1]) {
					w126 = -56.82961;
				} else {
					w126 = -332.03723;
				}
			} else {
				if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
					w126 = 237.91336;
				} else {
					w126 = -208.42456;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[54]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[0]) {
					w126 = 490.1661;
				} else {
					w126 = 84.285995;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w126 = 1087.8557;
				} else {
					w126 = -89.10287;
				}
			}
		}
	}
	float w127;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[41]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[15]) {
					w127 = -664.55304;
				} else {
					w127 = -383.41202;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[25]) {
					w127 = -341.23712;
				} else {
					w127 = -181.70078;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[15]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[23]) {
					w127 = -252.5421;
				} else {
					w127 = -100.14645;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[14]) {
					w127 = -42.361134;
				} else {
					w127 = 142.37053;
				}
			}
		}
	} else {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[21]) {
					w127 = -499.25775;
				} else {
					w127 = -49.837963;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
					w127 = 83.94388;
				} else {
					w127 = 335.78058;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w127 = -323.38583;
				} else {
					w127 = 351.38553;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
					w127 = 955.3318;
				} else {
					w127 = -424.312;
				}
			}
		}
	}
	float w128;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
					w128 = -498.86874;
				} else {
					w128 = -11.364375;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[14]) {
					w128 = -322.5166;
				} else {
					w128 = -120.70568;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[23]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[55]) {
					w128 = -367.53946;
				} else {
					w128 = -184.82213;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w128 = -56.837532;
				} else {
					w128 = 257.09686;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[21]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[6]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[9]) {
					w128 = -14.664419;
				} else {
					w128 = 172.90694;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[5]) {
					w128 = 223.44534;
				} else {
					w128 = 560.65894;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[8]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
					w128 = 407.22525;
				} else {
					w128 = 924.05664;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w128 = 1934.2869;
				} else {
					w128 = 531.86017;
				}
			}
		}
	}
	float w129;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[12]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w129 = -360.1222;
				} else {
					w129 = -175.16887;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w129 = -131.78363;
				} else {
					w129 = 139.51453;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[32]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[6]) {
					w129 = -158.41087;
				} else {
					w129 = -9.827804;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
					w129 = 62.629078;
				} else {
					w129 = 247.78336;
				}
			}
		}
	} else {
		if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[6]) {
					w129 = 142.52928;
				} else {
					w129 = 413.07858;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[16]) {
					w129 = 994.2499;
				} else {
					w129 = -15.412148;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[23]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[2]) {
					w129 = 705.1835;
				} else {
					w129 = 170.5146;
				}
			} else {
				w129 = 1914.9437;
			}
		}
	}
	float w130;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[17]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w130 = -330.88022;
				} else {
					w130 = -146.92523;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[25]) {
					w130 = -309.68704;
				} else {
					w130 = -67.234344;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[24]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[26]) {
					w130 = -284.58185;
				} else {
					w130 = 35.52811;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w130 = -120.30447;
				} else {
					w130 = 356.46207;
				}
			}
		}
	} else {
		if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[5]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[6]) {
					w130 = -410.84607;
				} else {
					w130 = 177.0848;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[7]) {
					w130 = 172.42302;
				} else {
					w130 = 646.3334;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[5]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[7]) {
					w130 = 137.54967;
				} else {
					w130 = 589.43677;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
					w130 = 1465.8763;
				} else {
					w130 = -428.71368;
				}
			}
		}
	}
	float w131;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w131 = -363.84604;
				} else {
					w131 = -170.42725;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
					w131 = -324.71945;
				} else {
					w131 = -85.588974;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[18]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
					w131 = -75.29378;
				} else {
					w131 = 68.65888;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
					w131 = 154.09538;
				} else {
					w131 = 625.14606;
				}
			}
		}
	} else {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[2]) {
					w131 = -334.85385;
				} else {
					w131 = 69.48773;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[27]) {
					w131 = -132.56398;
				} else {
					w131 = 170.71654;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[54]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
					w131 = -172.2254;
				} else {
					w131 = 424.4835;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w131 = 1227.4292;
				} else {
					w131 = -95.28099;
				}
			}
		}
	}
	float w132;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
					w132 = -481.20212;
				} else {
					w132 = -3.3677342;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[14]) {
					w132 = -309.62677;
				} else {
					w132 = -116.39443;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[23]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[55]) {
					w132 = -351.3293;
				} else {
					w132 = -175.12564;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w132 = -53.572487;
				} else {
					w132 = 249.2568;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[21]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[6]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[9]) {
					w132 = -16.385046;
				} else {
					w132 = 165.92627;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[10]) {
					w132 = 259.31866;
				} else {
					w132 = 663.38947;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[7]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
					w132 = 171.86449;
				} else {
					w132 = 529.60065;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[8]) {
					w132 = 1511.3654;
				} else {
					w132 = -424.80365;
				}
			}
		}
	}
	float w133;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w133 = -355.41318;
				} else {
					w133 = -166.26414;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
					w133 = -317.21048;
				} else {
					w133 = -83.414474;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[18]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[0]) {
					w133 = -65.1829;
				} else {
					w133 = 97.446075;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
					w133 = 150.19525;
				} else {
					w133 = 613.7784;
				}
			}
		}
	} else {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[2]) {
					w133 = -327.76892;
				} else {
					w133 = 69.83953;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[27]) {
					w133 = -129.78905;
				} else {
					w133 = 166.52487;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[54]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
					w133 = -171.80714;
				} else {
					w133 = 413.50366;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w133 = 1198.634;
				} else {
					w133 = -95.04234;
				}
			}
		}
	}
	float w134;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[39]) {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[19]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
					w134 = -357.84857;
				} else {
					w134 = -149.82004;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w134 = -45.097248;
				} else {
					w134 = 242.90518;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[56]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[24]) {
					w134 = -149.3153;
				} else {
					w134 = -19.834555;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[6]) {
					w134 = 219.06845;
				} else {
					w134 = 45.500366;
				}
			}
		}
	} else {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[2]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[28]) {
					w134 = -304.9835;
				} else {
					w134 = 164.93484;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[25]) {
					w134 = 224.51471;
				} else {
					w134 = 871.5711;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[8]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[8]) {
					w134 = 436.6942;
				} else {
					w134 = 1214.0118;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w134 = 1841.7612;
				} else {
					w134 = 489.42047;
				}
			}
		}
	}
	float w135;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[41]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[52]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[18]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[11]) {
					w135 = -259.2865;
				} else {
					w135 = -437.57968;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[51]) {
					w135 = -291.6574;
				} else {
					w135 = -120.45203;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
					w135 = -365.15823;
				} else {
					w135 = 59.569893;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[3]) {
					w135 = -59.73842;
				} else {
					w135 = 86.68772;
				}
			}
		}
	} else {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[27]) {
					w135 = -548.31384;
				} else {
					w135 = -61.189564;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
					w135 = 73.22614;
				} else {
					w135 = 306.94223;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w135 = -308.48724;
				} else {
					w135 = 322.54382;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
					w135 = 877.91626;
				} else {
					w135 = -425.28;
				}
			}
		}
	}
	float w136;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w136 = -343.86392;
				} else {
					w136 = -160.10545;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[10]) {
					w136 = -118.85957;
				} else {
					w136 = 97.53551;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[19]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[7]) {
					w136 = -47.769398;
				} else {
					w136 = 355.51593;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
					w136 = 136.44563;
				} else {
					w136 = 566.53503;
				}
			}
		}
	} else {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[2]) {
					w136 = -324.16022;
				} else {
					w136 = 72.39258;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[29]) {
					w136 = 119.009415;
				} else {
					w136 = 503.98398;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[54]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
					w136 = 77.81891;
				} else {
					w136 = 475.5413;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[9]) {
					w136 = 218.37106;
				} else {
					w136 = 1259.1686;
				}
			}
		}
	}
	float w137;
	if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
					w137 = -269.01413;
				} else {
					w137 = -120.06564;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w137 = -75.629456;
				} else {
					w137 = 142.16022;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[30]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
					w137 = -52.522747;
				} else {
					w137 = 100.17771;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[57]) {
					w137 = 468.47345;
				} else {
					w137 = -294.81802;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[9]) {
					w137 = 23.017702;
				} else {
					w137 = -489.69012;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[20]) {
					w137 = 71.14927;
				} else {
					w137 = 360.21094;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[7]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[2]) {
					w137 = 442.7568;
				} else {
					w137 = 9.851625;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
					w137 = 663.4073;
				} else {
					w137 = 1493.8027;
				}
			}
		}
	}
	float w138;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w138 = -382.2273;
				} else {
					w138 = -191.50644;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
					w138 = -305.59396;
				} else {
					w138 = -77.11667;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[18]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[0]) {
					w138 = -62.22806;
				} else {
					w138 = 94.78604;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
					w138 = 140.7469;
				} else {
					w138 = 586.072;
				}
			}
		}
	} else {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[2]) {
					w138 = -318.8063;
				} else {
					w138 = 72.243515;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[27]) {
					w138 = -131.64687;
				} else {
					w138 = 157.25659;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[54]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
					w138 = -172.15837;
				} else {
					w138 = 388.00055;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w138 = 1134.4438;
				} else {
					w138 = -107.415115;
				}
			}
		}
	}
	float w139;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
					w139 = -453.7719;
				} else {
					w139 = 7.4633203;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[14]) {
					w139 = -287.9202;
				} else {
					w139 = -112.24759;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[23]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[21]) {
					w139 = -246.24506;
				} else {
					w139 = -99.59961;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w139 = -47.396595;
				} else {
					w139 = 233.46136;
				}
			}
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[11]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w139 = -92.26092;
				} else {
					w139 = 96.7056;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[5]) {
					w139 = 250.4083;
				} else {
					w139 = 547.2882;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[4]) {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[3]) {
					w139 = 152.06334;
				} else {
					w139 = 417.61102;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w139 = 391.17773;
				} else {
					w139 = 989.0823;
				}
			}
		}
	}
	float w140;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[41]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[52]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[5]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w140 = -394.65604;
				} else {
					w140 = -152.15742;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[25]) {
					w140 = -273.26913;
				} else {
					w140 = -107.45101;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
					w140 = -348.6245;
				} else {
					w140 = 68.58451;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[3]) {
					w140 = -55.456547;
				} else {
					w140 = 82.58632;
				}
			}
		}
	} else {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[27]) {
					w140 = -527.3714;
				} else {
					w140 = -58.95148;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
					w140 = 66.61895;
				} else {
					w140 = 291.22723;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[8]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[8]) {
					w140 = 324.8985;
				} else {
					w140 = 1145.9064;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w140 = 1765.7993;
				} else {
					w140 = 448.8192;
				}
			}
		}
	}
	float w141;
	if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
					w141 = -256.05606;
				} else {
					w141 = -114.11525;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w141 = -72.50251;
				} else {
					w141 = 140.6528;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[30]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
					w141 = -52.265877;
				} else {
					w141 = 95.57273;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[57]) {
					w141 = 454.80386;
				} else {
					w141 = -297.2135;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[9]) {
					w141 = 22.068521;
				} else {
					w141 = -476.83633;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[20]) {
					w141 = 65.65977;
				} else {
					w141 = 343.2949;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[7]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[2]) {
					w141 = 417.65945;
				} else {
					w141 = -4.0934997;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
					w141 = 631.71783;
				} else {
					w141 = 1441.0575;
				}
			}
		}
	}
	float w142;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w142 = -320.34396;
				} else {
					w142 = -144.14366;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
					w142 = -294.49533;
				} else {
					w142 = -72.91384;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[19]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[7]) {
					w142 = -45.190205;
				} else {
					w142 = 346.4321;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
					w142 = 125.43199;
				} else {
					w142 = 536.3931;
				}
			}
		}
	} else {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[2]) {
					w142 = -313.43036;
				} else {
					w142 = 75.55019;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[27]) {
					w142 = -130.43144;
				} else {
					w142 = 150.31909;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[54]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
					w142 = 64.17975;
				} else {
					w142 = 444.29105;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w142 = 1088.9855;
				} else {
					w142 = -119.293236;
				}
			}
		}
	}
	float w143;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[41]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[15]) {
					w143 = -594.7912;
				} else {
					w143 = -329.2598;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
					w143 = -343.87665;
				} else {
					w143 = -170.90526;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w143 = -188.05911;
				} else {
					w143 = -46.19255;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[6]) {
					w143 = -104.14769;
				} else {
					w143 = 44.136032;
				}
			}
		}
	} else {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w143 = -55.155037;
				} else {
					w143 = 272.4685;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[15]) {
					w143 = 157.67307;
				} else {
					w143 = 519.69275;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[8]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[8]) {
					w143 = 313.5522;
				} else {
					w143 = 1113.5033;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w143 = 1722.8406;
				} else {
					w143 = 432.54797;
				}
			}
		}
	}
	float w144;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[12]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w144 = -228.97139;
				} else {
					w144 = -74.63811;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[14]) {
					w144 = -2.0745468;
				} else {
					w144 = 438.1729;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[0]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[31]) {
					w144 = -33.415485;
				} else {
					w144 = 624.02014;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[9]) {
					w144 = -21.57732;
				} else {
					w144 = 209.63054;
				}
			}
		}
	} else {
		if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[32]) {
					w144 = 71.12106;
				} else {
					w144 = 297.129;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[21]) {
					w144 = 306.27908;
				} else {
					w144 = 900.8099;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
				w144 = 1705.6124;
			} else {
				w144 = 580.26984;
			}
		}
	}
	float w145;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w145 = -355.18954;
				} else {
					w145 = -175.80228;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
					w145 = -98.98907;
				} else {
					w145 = 228.46523;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[18]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
					w145 = -65.74535;
				} else {
					w145 = 65.60993;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
					w145 = 128.69296;
				} else {
					w145 = 553.9828;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[22]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[33]) {
					w145 = 53.578278;
				} else {
					w145 = 701.0479;
				}
			} else {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w145 = 592.9026;
				} else {
					w145 = 289.08258;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w145 = -342.54172;
				} else {
					w145 = 224.96248;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
					w145 = 786.96356;
				} else {
					w145 = -456.02765;
				}
			}
		}
	}
	float w146;
	if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[13]) {
					w146 = -374.38916;
				} else {
					w146 = 66.35953;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[17]) {
					w146 = -251.06477;
				} else {
					w146 = -92.87938;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[9]) {
					w146 = -72.91054;
				} else {
					w146 = 264.3108;
				}
			} else {
				if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
					w146 = 88.74835;
				} else {
					w146 = -232.90706;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[9]) {
					w146 = 20.113062;
				} else {
					w146 = -465.8856;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[20]) {
					w146 = 59.486816;
				} else {
					w146 = 323.4088;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[7]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[2]) {
					w146 = 389.56345;
				} else {
					w146 = -19.063124;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
					w146 = 596.3907;
				} else {
					w146 = 1375.2076;
				}
			}
		}
	}
	float w147;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w147 = -304.31644;
				} else {
					w147 = -135.99991;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
					w147 = -281.69098;
				} else {
					w147 = -67.746735;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[19]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[7]) {
					w147 = -42.355545;
				} else {
					w147 = 337.25754;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
					w147 = 117.43723;
				} else {
					w147 = 511.91946;
				}
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[4]) {
					w147 = 25.641909;
				} else {
					w147 = 211.53058;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w147 = 1584.3284;
				} else {
					w147 = 414.57703;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[34]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[24]) {
					w147 = 417.37485;
				} else {
					w147 = 1098.3239;
				}
			} else {
				w147 = -454.89304;
			}
		}
	}
	float w148;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[10]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
					w148 = -470.3923;
				} else {
					w148 = -220.83997;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
					w148 = -100.60109;
				} else {
					w148 = 224.31429;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[35]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[9]) {
					w148 = -67.57601;
				} else {
					w148 = 250.65137;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w148 = 53.9228;
				} else {
					w148 = 318.70663;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[22]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[33]) {
					w148 = 50.537704;
				} else {
					w148 = 689.58954;
				}
			} else {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w148 = 576.3722;
				} else {
					w148 = 275.93433;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w148 = -339.39664;
				} else {
					w148 = 217.7551;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
					w148 = 761.0279;
				} else {
					w148 = -450.34415;
				}
			}
		}
	}
	float w149;
	if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[6]) {
					w149 = -394.54092;
				} else {
					w149 = -183.86125;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[23]) {
					w149 = -197.37679;
				} else {
					w149 = -29.343433;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
					w149 = -191.3785;
				} else {
					w149 = -35.772575;
				}
			} else {
				if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
					w149 = 85.86495;
				} else {
					w149 = -227.64372;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[4]) {
				if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
					w149 = 75.39825;
				} else {
					w149 = -394.69067;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
					w149 = 302.40982;
				} else {
					w149 = -190.30214;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[7]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[2]) {
					w149 = 375.54294;
				} else {
					w149 = -25.190437;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
					w149 = 576.96185;
				} else {
					w149 = 1334.5232;
				}
			}
		}
	}
	float w150;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w150 = -336.71228;
				} else {
					w150 = -164.68831;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[3]) {
					w150 = -49.34647;
				} else {
					w150 = -184.58821;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[35]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[9]) {
					w150 = -66.2404;
				} else {
					w150 = 245.62688;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w150 = 52.19793;
				} else {
					w150 = 312.80435;
				}
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[4]) {
					w150 = 23.077023;
				} else {
					w150 = 203.61418;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w150 = 1549.6499;
				} else {
					w150 = 401.43326;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[34]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[24]) {
					w150 = 403.18533;
				} else {
					w150 = 1063.1256;
				}
			} else {
				w150 = -449.15485;
			}
		}
	}
	float w151;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[20]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w151 = -423.75723;
				} else {
					w151 = -238.55255;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[59]) {
					w151 = -245.62073;
				} else {
					w151 = -89.802444;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[10]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[12]) {
					w151 = -81.97219;
				} else {
					w151 = 128.69232;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[24]) {
					w151 = -456.50104;
				} else {
					w151 = 170.1028;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[17]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[6]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[9]) {
					w151 = -36.136234;
				} else {
					w151 = 132.5684;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[12]) {
					w151 = -474.33408;
				} else {
					w151 = 286.50305;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[8]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
					w151 = 291.4549;
				} else {
					w151 = 744.4979;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w151 = 1614.6406;
				} else {
					w151 = 398.4225;
				}
			}
		}
	}
	float w152;
	if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
		if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[7]) {
					w152 = -354.6543;
				} else {
					w152 = -144.5762;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[3]) {
					w152 = -202.20055;
				} else {
					w152 = -4.4370446;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[36]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[7]) {
					w152 = -95.31565;
				} else {
					w152 = 25.47523;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w152 = -265.82208;
				} else {
					w152 = 164.51866;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[9]) {
					w152 = 15.669109;
				} else {
					w152 = -451.8159;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[20]) {
					w152 = 51.989548;
				} else {
					w152 = 301.7188;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[7]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[2]) {
					w152 = 364.39175;
				} else {
					w152 = -30.344624;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[10]) {
					w152 = 884.262;
				} else {
					w152 = -392.62463;
				}
			}
		}
	}
	float w153;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w153 = -285.21964;
				} else {
					w153 = -125.74346;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
					w153 = -267.38226;
				} else {
					w153 = -61.673435;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[25]) {
					w153 = -35.941116;
				} else {
					w153 = 132.47066;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[11]) {
					w153 = 162.35832;
				} else {
					w153 = 543.4223;
				}
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[31]) {
					w153 = 86.52802;
				} else {
					w153 = 606.1073;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w153 = 1511.7649;
				} else {
					w153 = 388.80234;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[34]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[24]) {
					w153 = 391.186;
				} else {
					w153 = 1031.9104;
				}
			} else {
				w153 = -448.70248;
			}
		}
	}
	float w154;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[10]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
					w154 = -445.4558;
				} else {
					w154 = -205.66745;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
					w154 = -93.26129;
				} else {
					w154 = 220.97641;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[25]) {
					w154 = -35.403454;
				} else {
					w154 = 130.50273;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[11]) {
					w154 = 160.11026;
				} else {
					w154 = 535.89795;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[26]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[33]) {
					w154 = 48.01234;
				} else {
					w154 = 667.10846;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[37]) {
					w154 = 7.563047;
				} else {
					w154 = 439.7174;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[28]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w154 = -155.05757;
				} else {
					w154 = 300.12738;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
					w154 = 670.2419;
				} else {
					w154 = -444.21545;
				}
			}
		}
	}
	float w155;
	if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[19]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[20]) {
					w155 = -207.51416;
				} else {
					w155 = -85.18175;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w155 = -33.692986;
				} else {
					w155 = 235.40872;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[26]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[15]) {
					w155 = -322.31412;
				} else {
					w155 = -32.65423;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[13]) {
					w155 = 11.442376;
				} else {
					w155 = 178.23877;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[9]) {
					w155 = 13.7373295;
				} else {
					w155 = -445.56277;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[20]) {
					w155 = 50.193653;
				} else {
					w155 = 290.9265;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[7]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[2]) {
					w155 = 350.4494;
				} else {
					w155 = -35.55075;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
					w155 = 538.66455;
				} else {
					w155 = 1260.975;
				}
			}
		}
	}
	float w156;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w156 = -316.43808;
				} else {
					w156 = -153.23958;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
					w156 = -259.82468;
				} else {
					w156 = -58.428745;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[25]) {
					w156 = -34.3109;
				} else {
					w156 = 126.71795;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[11]) {
					w156 = 157.4372;
				} else {
					w156 = 525.38965;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[26]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[33]) {
					w156 = 46.18375;
				} else {
					w156 = 658.8717;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[37]) {
					w156 = 5.3334374;
				} else {
					w156 = 430.29886;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[28]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w156 = -152.6804;
				} else {
					w156 = 293.55383;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
					w156 = 654.4297;
				} else {
					w156 = -443.3578;
				}
			}
		}
	}
	float w157;
	if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
					w157 = -398.0212;
				} else {
					w157 = 35.90332;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
					w157 = -110.662415;
				} else {
					w157 = -252.83888;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[16]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
					w157 = -145.22198;
				} else {
					w157 = -39.812103;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w157 = -28.042898;
				} else {
					w157 = 122.15297;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[17]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[14]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[11]) {
					w157 = -24.885136;
				} else {
					w157 = 162.25674;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[27]) {
					w157 = 102.6454;
				} else {
					w157 = 458.2103;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[8]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
					w157 = 272.54883;
				} else {
					w157 = 704.2158;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w157 = 1548.6774;
				} else {
					w157 = 371.91092;
				}
			}
		}
	}
	float w158;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[18]) {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[1]) {
					w158 = -277.02505;
				} else {
					w158 = 51.398575;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[23]) {
					w158 = -101.614174;
				} else {
					w158 = 107.81953;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[25]) {
					w158 = -33.369453;
				} else {
					w158 = 122.99487;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[60]) {
					w158 = 37.53686;
				} else {
					w158 = 446.08453;
				}
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[31]) {
					w158 = 79.66093;
				} else {
					w158 = 580.6513;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w158 = 1457.0918;
				} else {
					w158 = 369.1214;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[34]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[24]) {
					w158 = 367.28192;
				} else {
					w158 = 983.68884;
				}
			} else {
				w158 = -443.80804;
			}
		}
	}
	float w159;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
					w159 = -182.76051;
				} else {
					w159 = 176.17055;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[38]) {
					w159 = -72.47605;
				} else {
					w159 = 115.82973;
				}
			}
		} else {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[19]) {
					w159 = -29.783543;
				} else {
					w159 = 117.781425;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w159 = 37.751553;
				} else {
					w159 = 564.05426;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[5]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[20]) {
					w159 = 178.83531;
				} else {
					w159 = 387.6635;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[27]) {
					w159 = -187.61717;
				} else {
					w159 = 103.5075;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[17]) {
					w159 = 405.7424;
				} else {
					w159 = 1294.7819;
				}
			} else {
				w159 = -439.3699;
			}
		}
	}
	float w160;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[20]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w160 = -403.37946;
				} else {
					w160 = -181.86269;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[5]) {
					w160 = -57.64092;
				} else {
					w160 = 605.3774;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[12]) {
					w160 = -82.775246;
				} else {
					w160 = 86.67359;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[10]) {
					w160 = 27.18929;
				} else {
					w160 = 565.3973;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[39]) {
					w160 = -109.87787;
				} else {
					w160 = 23.256138;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
					w160 = -337.2097;
				} else {
					w160 = 143.4223;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[12]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[17]) {
					w160 = 588.4439;
				} else {
					w160 = 1471.8445;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[14]) {
					w160 = -103.91598;
				} else {
					w160 = 409.02963;
				}
			}
		}
	}
	float w161;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
					w161 = -178.06973;
				} else {
					w161 = 172.27245;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[38]) {
					w161 = -70.05071;
				} else {
					w161 = 114.76281;
				}
			}
		} else {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[11]) {
					w161 = -30.660927;
				} else {
					w161 = 112.791985;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w161 = 36.026764;
				} else {
					w161 = 552.89496;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[5]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[20]) {
					w161 = 174.38406;
				} else {
					w161 = 378.13797;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[27]) {
					w161 = -184.6607;
				} else {
					w161 = 100.973114;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[17]) {
					w161 = 396.26944;
				} else {
					w161 = 1268.3573;
				}
			} else {
				w161 = -439.0665;
			}
		}
	}
	float w162;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w162 = -261.48807;
				} else {
					w162 = -114.94772;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
					w162 = -248.0073;
				} else {
					w162 = -52.96148;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[25]) {
					w162 = -30.886648;
				} else {
					w162 = 117.64444;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[11]) {
					w162 = 147.39766;
				} else {
					w162 = 502.07184;
				}
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[4]) {
					w162 = 12.162854;
				} else {
					w162 = 178.85553;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w162 = 1409.881;
				} else {
					w162 = 344.06155;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[34]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[24]) {
					w162 = 354.7797;
				} else {
					w162 = 942.22473;
				}
			} else {
				w162 = -434.67584;
			}
		}
	}
	float w163;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
					w163 = -287.46017;
				} else {
					w163 = -120.4031;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[40]) {
					w163 = -164.59871;
				} else {
					w163 = 14.638485;
				}
			}
		} else {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[19]) {
					w163 = -28.700716;
				} else {
					w163 = 111.60289;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w163 = 35.447205;
				} else {
					w163 = 541.88165;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[5]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[20]) {
					w163 = 170.30592;
				} else {
					w163 = 369.22693;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[27]) {
					w163 = -182.66669;
				} else {
					w163 = 98.22079;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
					w163 = 405.60928;
				} else {
					w163 = 1287.53;
				}
			} else {
				w163 = -430.32913;
			}
		}
	}
	float w164;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[34]) {
					w164 = -168.83618;
				} else {
					w164 = 260.5722;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[38]) {
					w164 = -67.37026;
				} else {
					w164 = 112.60893;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[24]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[19]) {
					w164 = -28.328428;
				} else {
					w164 = 89.17463;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[61]) {
					w164 = -188.61472;
				} else {
					w164 = 323.75995;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[5]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[20]) {
					w164 = 167.78027;
				} else {
					w164 = 363.91013;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[27]) {
					w164 = -180.0878;
				} else {
					w164 = 96.93167;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
					w164 = 399.78986;
				} else {
					w164 = 1270.363;
				}
			} else {
				w164 = -426.02585;
			}
		}
	}
	float w165;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[30]) {
					w165 = -318.41376;
				} else {
					w165 = -124.91;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[40]) {
					w165 = -161.1662;
				} else {
					w165 = 14.645288;
				}
			}
		} else {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[19]) {
					w165 = -28.05434;
				} else {
					w165 = 108.163025;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w165 = 34.535156;
				} else {
					w165 = 531.1077;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[5]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[20]) {
					w165 = 165.29216;
				} else {
					w165 = 358.6699;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[27]) {
					w165 = -177.5453;
				} else {
					w165 = 95.65936;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
					w165 = 394.05383;
				} else {
					w165 = 1253.4247;
				}
			} else {
				w165 = -421.76553;
			}
		}
	}
	float w166;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[18]) {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[1]) {
					w166 = -259.9528;
				} else {
					w166 = 58.813732;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[23]) {
					w166 = -92.7215;
				} else {
					w166 = 102.223175;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w166 = -27.252531;
				} else {
					w166 = 124.705574;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[11]) {
					w166 = 144.35376;
				} else {
					w166 = 489.2958;
				}
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[31]) {
					w166 = 68.91619;
				} else {
					w166 = 540.7057;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w166 = 1360.9373;
				} else {
					w166 = 312.89624;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[34]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[24]) {
					w166 = 342.08817;
				} else {
					w166 = 903.4011;
				}
			} else {
				w166 = -417.54788;
			}
		}
	}
	float w167;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[20]) {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[0]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w167 = -383.17984;
				} else {
					w167 = -147.51582;
				}
			} else {
				w167 = 591.4768;
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[12]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[10]) {
					w167 = -89.49928;
				} else {
					w167 = 73.57936;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w167 = -200.35124;
				} else {
					w167 = 160.40492;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[45]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
					w167 = -235.39809;
				} else {
					w167 = 2.4497175;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[31]) {
					w167 = -338.5854;
				} else {
					w167 = 130.85477;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[12]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[28]) {
					w167 = 64.49953;
				} else {
					w167 = 908.5066;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[14]) {
					w167 = -112.823586;
				} else {
					w167 = 378.78137;
				}
			}
		}
	}
	float w168;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w168 = -293.93558;
				} else {
					w168 = -140.55556;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[3]) {
					w168 = -25.730536;
				} else {
					w168 = -163.05206;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w168 = -41.350838;
				} else {
					w168 = 143.61992;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[15]) {
					w168 = 91.4418;
				} else {
					w168 = 420.5502;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[5]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[26]) {
					w168 = 147.29602;
				} else {
					w168 = 311.74496;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[27]) {
					w168 = -175.14603;
				} else {
					w168 = 91.341354;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
					w168 = 380.6917;
				} else {
					w168 = 1219.669;
				}
			} else {
				w168 = -417.16022;
			}
		}
	}
	float w169;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[20]) {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[0]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w169 = -375.4713;
				} else {
					w169 = -144.05025;
				}
			} else {
				w169 = 585.9635;
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[12]) {
					w169 = -73.489815;
				} else {
					w169 = 84.33694;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[10]) {
					w169 = 19.867605;
				} else {
					w169 = 534.4918;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[29]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[28]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
					w169 = -24.724663;
				} else {
					w169 = 247.60089;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
					w169 = 83.47556;
				} else {
					w169 = 293.33734;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[24]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[13]) {
					w169 = -67.83809;
				} else {
					w169 = 227.38547;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
					w169 = 557.09296;
				} else {
					w169 = -412.98865;
				}
			}
		}
	}
	float w170;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w170 = -287.25708;
				} else {
					w170 = -137.52231;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[3]) {
					w170 = -24.752617;
				} else {
					w170 = -159.6032;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w170 = -40.36341;
				} else {
					w170 = 141.45602;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[15]) {
					w170 = 88.940735;
				} else {
					w170 = 410.14252;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[5]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[20]) {
					w170 = 155.4717;
				} else {
					w170 = 337.48322;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[13]) {
					w170 = 19.758766;
				} else {
					w170 = -227.45662;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[17]) {
					w170 = 353.506;
				} else {
					w170 = 1154.5415;
				}
			} else {
				w170 = -408.85883;
			}
		}
	}
	float w171;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[20]) {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[0]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w171 = -367.92545;
				} else {
					w171 = -140.66632;
				}
			} else {
				w171 = 580.5078;
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[12]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[10]) {
					w171 = -85.6209;
				} else {
					w171 = 71.15093;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w171 = -196.64792;
				} else {
					w171 = 156.35083;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[62]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[24]) {
					w171 = -113.64821;
				} else {
					w171 = 0.8899943;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[41]) {
					w171 = -160.5768;
				} else {
					w171 = 103.470276;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[12]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[17]) {
					w171 = 525.05365;
				} else {
					w171 = 1346.4974;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[14]) {
					w171 = -117.0666;
				} else {
					w171 = 360.18906;
				}
			}
		}
	}
	float w172;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
					w172 = -367.067;
				} else {
					w172 = -150.90135;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[23]) {
					w172 = -69.598076;
				} else {
					w172 = 108.67038;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w172 = -39.55025;
				} else {
					w172 = 139.07442;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[15]) {
					w172 = 86.61771;
				} else {
					w172 = 401.80182;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[5]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[26]) {
					w172 = 139.31834;
				} else {
					w172 = 296.67923;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[27]) {
					w172 = -170.86371;
				} else {
					w172 = 88.47263;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
					w172 = 362.9942;
				} else {
					w172 = 1173.9712;
				}
			} else {
				w172 = -408.3721;
			}
		}
	}
	float w173;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[20]) {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[0]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w173 = -360.07962;
				} else {
					w173 = -137.48297;
				}
			} else {
				w173 = 575.1109;
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w173 = -101.28028;
				} else {
					w173 = 14.602197;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[10]) {
					w173 = 19.207926;
				} else {
					w173 = 521.0111;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[29]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[28]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
					w173 = -24.466393;
				} else {
					w173 = 240.94229;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[8]) {
					w173 = 100.09632;
				} else {
					w173 = 344.15936;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[24]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[13]) {
					w173 = -69.478584;
				} else {
					w173 = 216.86707;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
					w173 = 532.94775;
				} else {
					w173 = -404.28833;
				}
			}
		}
	}
	float w174;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w174 = -275.94623;
				} else {
					w174 = -131.67279;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[3]) {
					w174 = -22.587994;
				} else {
					w174 = -153.81003;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w174 = -38.473984;
				} else {
					w174 = 136.87013;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[15]) {
					w174 = 84.1598;
				} else {
					w174 = 392.18774;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[5]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[21]) {
					w174 = 161.91594;
				} else {
					w174 = 407.889;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[13]) {
					w174 = 19.204386;
				} else {
					w174 = -221.3609;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[17]) {
					w174 = 337.0721;
				} else {
					w174 = 1111.0527;
				}
			} else {
				w174 = -400.24554;
			}
		}
	}
	float w175;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[0]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w175 = -354.95038;
				} else {
					w175 = -141.19978;
				}
			} else {
				w175 = 569.771;
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w175 = -73.42713;
				} else {
					w175 = 79.298454;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[10]) {
					w175 = 18.713245;
				} else {
					w175 = 486.45398;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[29]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[28]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
					w175 = -24.052628;
				} else {
					w175 = 237.258;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
					w175 = 77.864105;
				} else {
					w175 = 280.0229;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[24]) {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
					w175 = 102.57041;
				} else {
					w175 = 360.00406;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
					w175 = 519.8455;
				} else {
					w175 = -396.24304;
				}
			}
		}
	}
	float w176;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w176 = -269.67853;
				} else {
					w176 = -129.11638;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[3]) {
					w176 = -21.825428;
				} else {
					w176 = -150.60152;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w176 = -37.330353;
				} else {
					w176 = 134.21861;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[15]) {
					w176 = 81.876526;
				} else {
					w176 = 382.46573;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[5]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w176 = 208.38173;
				} else {
					w176 = -10.981557;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[13]) {
					w176 = 18.55597;
				} else {
					w176 = -217.98898;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
					w176 = 346.2625;
				} else {
					w176 = 1131.1287;
				}
			} else {
				w176 = -392.28055;
			}
		}
	}
	float w177;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
					w177 = -261.59036;
				} else {
					w177 = -105.21321;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[40]) {
					w177 = -144.89558;
				} else {
					w177 = 14.98233;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[13]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[10]) {
					w177 = 49.404617;
				} else {
					w177 = 489.51935;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
					w177 = -458.99646;
				} else {
					w177 = -33.949825;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[30]) {
					w177 = -43.33969;
				} else {
					w177 = 75.09125;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[8]) {
					w177 = 320.80817;
				} else {
					w177 = 77.67167;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[12]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[28]) {
					w177 = 42.068127;
				} else {
					w177 = 837.5584;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[14]) {
					w177 = -124.46128;
				} else {
					w177 = 334.36542;
				}
			}
		}
	}
	float w178;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[0]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[42]) {
					w178 = -128.44324;
				} else {
					w178 = 149.77345;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
					w178 = 34.19918;
				} else {
					w178 = 448.45837;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[31]) {
					w178 = -160.35147;
				} else {
					w178 = -35.12071;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
					w178 = 34.444828;
				} else {
					w178 = 372.14508;
				}
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[4]) {
					w178 = 0.11029907;
				} else {
					w178 = 148.2426;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w178 = 1260.7842;
				} else {
					w178 = 246.99702;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[1]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[44]) {
					w178 = 300.4896;
				} else {
					w178 = 849.47253;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[20]) {
					w178 = -5.844531;
				} else {
					w178 = -391.70132;
				}
			}
		}
	}
	float w179;
	if (LotArea != NULL && *LotArea < cond_LotArea[11]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[32]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[33]) {
					w179 = -229.64032;
				} else {
					w179 = -93.17857;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[23]) {
					w179 = -107.8938;
				} else {
					w179 = 43.90887;
				}
			}
		} else {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[1]) {
					w179 = 16.235443;
				} else {
					w179 = 411.20166;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[8]) {
					w179 = 326.89246;
				} else {
					w179 = 58.430355;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[30]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[14]) {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[2]) {
					w179 = -4.600871;
				} else {
					w179 = 401.79938;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[12]) {
					w179 = 20.80664;
				} else {
					w179 = -314.8764;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[14]) {
					w179 = 127.89489;
				} else {
					w179 = 350.924;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[23]) {
					w179 = 308.58865;
				} else {
					w179 = 1310.3215;
				}
			}
		}
	}
	float w180;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
					w180 = -344.98746;
				} else {
					w180 = -138.67702;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[23]) {
					w180 = -63.652134;
				} else {
					w180 = 102.65574;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w180 = -35.855404;
				} else {
					w180 = 131.16942;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[15]) {
					w180 = 78.24578;
				} else {
					w180 = 368.0922;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[5]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w180 = 200.81929;
				} else {
					w180 = -16.254475;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[1]) {
					w180 = -119.820404;
				} else {
					w180 = 308.1504;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
					w180 = 331.73044;
				} else {
					w180 = 1094.5345;
				}
			} else {
				w180 = -391.29352;
			}
		}
	}
	float w181;
	if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[17]) {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[30]) {
					w181 = -282.4116;
				} else {
					w181 = -99.43859;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[40]) {
					w181 = -138.60086;
				} else {
					w181 = 21.367819;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[29]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[26]) {
					w181 = -50.81238;
				} else {
					w181 = 46.41808;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
					w181 = 80.33751;
				} else {
					w181 = 318.35464;
				}
			}
		}
	} else {
		if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[12]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[6]) {
					w181 = -129.56725;
				} else {
					w181 = 130.63747;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[7]) {
					w181 = 80.257545;
				} else {
					w181 = 345.0556;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[7]) {
					w181 = 406.67496;
				} else {
					w181 = 1363.5289;
				}
			} else {
				w181 = -387.38052;
			}
		}
	}
	float w182;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w182 = -223.3702;
				} else {
					w182 = -95.18105;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[3]) {
					w182 = -21.23239;
				} else {
					w182 = -143.3831;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w182 = -34.840534;
				} else {
					w182 = 129.03905;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[15]) {
					w182 = 75.69789;
				} else {
					w182 = 359.20334;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[5]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w182 = 196.5385;
				} else {
					w182 = -17.549078;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[1]) {
					w182 = -117.815;
				} else {
					w182 = 305.23734;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
					w182 = 324.22797;
				} else {
					w182 = 1068.4338;
				}
			} else {
				w182 = -383.50677;
			}
		}
	}
	float w183;
	if (LotArea != NULL && *LotArea < cond_LotArea[11]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[32]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[33]) {
					w183 = -219.85829;
				} else {
					w183 = -89.105064;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[23]) {
					w183 = -104.06268;
				} else {
					w183 = 42.817257;
				}
			}
		} else {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[1]) {
					w183 = 14.638916;
				} else {
					w183 = 402.8249;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[8]) {
					w183 = 317.34308;
				} else {
					w183 = 55.80733;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[30]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[14]) {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[2]) {
					w183 = -3.581895;
				} else {
					w183 = 392.5049;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[12]) {
					w183 = 21.27525;
				} else {
					w183 = -308.6806;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[14]) {
					w183 = 123.30382;
				} else {
					w183 = 333.9684;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[23]) {
					w183 = 291.44308;
				} else {
					w183 = 1261.9534;
				}
			}
		}
	}
	float w184;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
					w184 = -333.34958;
				} else {
					w184 = -132.3861;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[23]) {
					w184 = -60.791656;
				} else {
					w184 = 100.53499;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w184 = -33.84089;
				} else {
					w184 = 126.52948;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[15]) {
					w184 = 73.4063;
				} else {
					w184 = 349.95233;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[5]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w184 = 192.57132;
				} else {
					w184 = -18.591396;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[14]) {
					w184 = 10.563266;
				} else {
					w184 = -222.93347;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[17]) {
					w184 = 301.35727;
				} else {
					w184 = 1009.23;
				}
			} else {
				w184 = -383.01147;
			}
		}
	}
	float w185;
	if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[17]) {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[2]) {
					w185 = -374.2559;
				} else {
					w185 = 37.48367;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[23]) {
					w185 = -163.92331;
				} else {
					w185 = -36.305313;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[29]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[26]) {
					w185 = -50.575893;
				} else {
					w185 = 45.21046;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
					w185 = 76.11216;
				} else {
					w185 = 306.0198;
				}
			}
		}
	} else {
		if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[12]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[6]) {
					w185 = -127.9058;
				} else {
					w185 = 128.25153;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[7]) {
					w185 = 75.01993;
				} else {
					w185 = 333.759;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[7]) {
					w185 = 387.80173;
				} else {
					w185 = 1315.6475;
				}
			} else {
				w185 = -379.18134;
			}
		}
	}
	float w186;
	if (LotArea != NULL && *LotArea < cond_LotArea[43]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[3]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[33]) {
					w186 = -222.42952;
				} else {
					w186 = -108.10444;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[23]) {
					w186 = -114.463295;
				} else {
					w186 = 35.593437;
				}
			}
		} else {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[3]) {
					w186 = -0.40548456;
				} else {
					w186 = 267.91394;
				}
			} else {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w186 = 555.29974;
				} else {
					w186 = 195.10062;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[30]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[15]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[32]) {
					w186 = 40.948143;
				} else {
					w186 = -263.17026;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[9]) {
					w186 = -227.10466;
				} else {
					w186 = -11.65731;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w186 = -169.34589;
				} else {
					w186 = 189.42987;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[23]) {
					w186 = 280.75406;
				} else {
					w186 = 1226.0853;
				}
			}
		}
	}
	float w187;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w187 = -223.30325;
				} else {
					w187 = -33.230858;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
					w187 = -73.8107;
				} else {
					w187 = 71.84469;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w187 = -32.832798;
				} else {
					w187 = 124.31112;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[15]) {
					w187 = 70.13541;
				} else {
					w187 = 339.0972;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[5]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[22]) {
					w187 = 142.32303;
				} else {
					w187 = 410.363;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[27]) {
					w187 = -159.16042;
				} else {
					w187 = 82.39362;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
					w187 = 307.98367;
				} else {
					w187 = 1016.39014;
				}
			} else {
				w187 = -377.28384;
			}
		}
	}
	float w188;
	if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[17]) {
		if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[15]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w188 = -320.20135;
				} else {
					w188 = -149.74747;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[18]) {
					w188 = -150.10863;
				} else {
					w188 = -20.386822;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[35]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[16]) {
					w188 = -407.84354;
				} else {
					w188 = -44.42687;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[5]) {
					w188 = 413.16116;
				} else {
					w188 = 95.166306;
				}
			}
		}
	} else {
		if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[6]) {
					w188 = -126.125854;
				} else {
					w188 = 126.04182;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[7]) {
					w188 = 71.021904;
				} else {
					w188 = 326.82843;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[7]) {
					w188 = 393.2732;
				} else {
					w188 = 1280.6394;
				}
			} else {
				w188 = -373.51102;
			}
		}
	}
	float w189;
	if (LotArea != NULL && *LotArea < cond_LotArea[11]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[32]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[33]) {
					w189 = -257.92044;
				} else {
					w189 = -106.63575;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[44]) {
					w189 = -113.10687;
				} else {
					w189 = 12.738165;
				}
			}
		} else {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[1]) {
					w189 = 12.381817;
				} else {
					w189 = 390.1079;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[8]) {
					w189 = 302.89365;
				} else {
					w189 = 49.467754;
				}
			}
		}
	} else {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[14]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[34]) {
					w189 = 6.518004;
				} else {
					w189 = 334.4597;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
					w189 = -227.21523;
				} else {
					w189 = 296.14435;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[8]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w189 = -294.4813;
				} else {
					w189 = 269.3825;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[21]) {
					w189 = 1161.2499;
				} else {
					w189 = -369.77585;
				}
			}
		}
	}
	float w190;
	if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[17]) {
		if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[15]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w190 = -313.34238;
				} else {
					w190 = -145.69608;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[18]) {
					w190 = -146.57127;
				} else {
					w190 = -19.8793;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[35]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[16]) {
					w190 = -400.94766;
				} else {
					w190 = -43.11965;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[5]) {
					w190 = 407.1134;
				} else {
					w190 = 92.8117;
				}
			}
		}
	} else {
		if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[6]) {
					w190 = -124.6265;
				} else {
					w190 = 124.14403;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[7]) {
					w190 = 68.87031;
				} else {
					w190 = 319.12973;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[7]) {
					w190 = 384.66287;
				} else {
					w190 = 1252.2786;
				}
			} else {
				w190 = -366.07803;
			}
		}
	}
	float w191;
	if (LotArea != NULL && *LotArea < cond_LotArea[43]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[3]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[36]) {
					w191 = -305.27554;
				} else {
					w191 = -117.64473;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[23]) {
					w191 = -108.53701;
				} else {
					w191 = 36.351902;
				}
			}
		} else {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[3]) {
					w191 = -0.9117466;
				} else {
					w191 = 260.47156;
				}
			} else {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w191 = 538.9673;
				} else {
					w191 = 185.84087;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[30]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[15]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[32]) {
					w191 = 41.21156;
				} else {
					w191 = -258.53873;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[9]) {
					w191 = -222.22894;
				} else {
					w191 = -10.633911;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[0]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
					w191 = 361.0084;
				} else {
					w191 = 128.91588;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[23]) {
					w191 = 267.0048;
				} else {
					w191 = 1166.7196;
				}
			}
		}
	}
	float w192;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w192 = -213.10802;
				} else {
					w192 = -28.946123;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
					w192 = -69.95575;
				} else {
					w192 = 69.19317;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w192 = -31.991325;
				} else {
					w192 = 121.18833;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[15]) {
					w192 = 66.30919;
				} else {
					w192 = 323.23434;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[5]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w192 = 179.33688;
				} else {
					w192 = -28.940641;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[1]) {
					w192 = -113.45218;
				} else {
					w192 = 293.5657;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[17]) {
					w192 = 279.31924;
				} else {
					w192 = 931.43866;
				}
			} else {
				w192 = -363.70648;
			}
		}
	}
	float w193;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[23]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
					w193 = -194.27168;
				} else {
					w193 = -440.35437;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w193 = -225.12564;
				} else {
					w193 = -86.6426;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[21]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[14]) {
					w193 = -176.72902;
				} else {
					w193 = -21.950603;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
					w193 = 56.603718;
				} else {
					w193 = 272.0189;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w193 = 74.66666;
				} else {
					w193 = 270.8832;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[12]) {
					w193 = -602.48615;
				} else {
					w193 = 449.7556;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[7]) {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[1]) {
					w193 = -173.41556;
				} else {
					w193 = 176.7046;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[10]) {
					w193 = 717.07495;
				} else {
					w193 = -360.06946;
				}
			}
		}
	}
	float w194;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[27]) {
					w194 = -318.3035;
				} else {
					w194 = -127.99233;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[3]) {
					w194 = -15.720655;
				} else {
					w194 = -131.88585;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w194 = -31.57052;
				} else {
					w194 = 118.99529;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[15]) {
					w194 = 64.82871;
				} else {
					w194 = 315.9284;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[5]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w194 = 175.84581;
				} else {
					w194 = -29.64472;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[1]) {
					w194 = -111.12302;
				} else {
					w194 = 290.93942;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[17]) {
					w194 = 273.706;
				} else {
					w194 = 910.52075;
				}
			} else {
				w194 = -356.4688;
			}
		}
	}
	float w195;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[0]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[10]) {
					w195 = -290.13095;
				} else {
					w195 = -116.347534;
				}
			} else {
				w195 = 548.0634;
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w195 = -86.38571;
				} else {
					w195 = 17.634205;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
					w195 = -124.36809;
				} else {
					w195 = 356.75516;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[29]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[28]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
					w195 = -22.874632;
				} else {
					w195 = 205.97264;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[8]) {
					w195 = 81.506424;
				} else {
					w195 = 293.03043;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[24]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[13]) {
					w195 = -81.69989;
				} else {
					w195 = 173.94171;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w195 = 512.2361;
				} else {
					w195 = 69.36373;
				}
			}
		}
	}
	float w196;
	if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[17]) {
		if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[15]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w196 = -298.68893;
				} else {
					w196 = -136.69609;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[18]) {
					w196 = -138.80388;
				} else {
					w196 = -18.521114;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[35]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[16]) {
					w196 = -391.01443;
				} else {
					w196 = -38.312057;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[5]) {
					w196 = 396.15582;
				} else {
					w196 = 87.38282;
				}
			}
		}
	} else {
		if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[6]) {
					w196 = -123.14112;
				} else {
					w196 = 120.45881;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[7]) {
					w196 = 61.233727;
				} else {
					w196 = 302.21356;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[7]) {
					w196 = 360.01495;
				} else {
					w196 = 1196.7401;
				}
			} else {
				w196 = -355.8121;
			}
		}
	}
	float w197;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[27]) {
					w197 = -311.0432;
				} else {
					w197 = -123.93527;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[3]) {
					w197 = -14.763868;
				} else {
					w197 = -128.1763;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w197 = -30.77146;
				} else {
					w197 = 116.70936;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[15]) {
					w197 = 62.433815;
				} else {
					w197 = 306.08688;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[5]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w197 = 170.35466;
				} else {
					w197 = -31.919647;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[14]) {
					w197 = 10.970702;
				} else {
					w197 = -209.74026;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
					w197 = 278.81763;
				} else {
					w197 = 917.9738;
				}
			} else {
				w197 = -352.254;
			}
		}
	}
	float w198;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[23]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
					w198 = -184.04607;
				} else {
					w198 = -429.1443;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w198 = -216.32315;
				} else {
					w198 = -80.28088;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[21]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[14]) {
					w198 = -168.57434;
				} else {
					w198 = -20.715693;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
					w198 = 53.70864;
				} else {
					w198 = 261.04855;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w198 = 70.7858;
				} else {
					w198 = 259.4859;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[12]) {
					w198 = -595.43475;
				} else {
					w198 = 438.26593;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[7]) {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[1]) {
					w198 = -175.92867;
				} else {
					w198 = 166.0001;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[10]) {
					w198 = 683.92413;
				} else {
					w198 = -348.73148;
				}
			}
		}
	}
	float w199;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[0]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[10]) {
					w199 = -281.46112;
				} else {
					w199 = -112.060295;
				}
			} else {
				w199 = 542.8138;
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w199 = -57.00664;
				} else {
					w199 = 77.376854;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
					w199 = -120.868744;
				} else {
					w199 = 346.80392;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[29]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[26]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
					w199 = -66.70587;
				} else {
					w199 = 198.56958;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[8]) {
					w199 = 41.711067;
				} else {
					w199 = 244.41129;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[24]) {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
					w199 = 70.824455;
				} else {
					w199 = 297.11887;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w199 = 493.61835;
				} else {
					w199 = 63.284164;
				}
			}
		}
	}
	float w200;
	if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[17]) {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[37]) {
					w200 = -245.24326;
				} else {
					w200 = -84.933846;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[40]) {
					w200 = -115.94927;
				} else {
					w200 = 24.526365;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[29]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[26]) {
					w200 = -48.78907;
				} else {
					w200 = 43.493156;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
					w200 = 59.520206;
				} else {
					w200 = 273.50662;
				}
			}
		}
	} else {
		if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[6]) {
					w200 = -121.740906;
				} else {
					w200 = 117.93109;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[7]) {
					w200 = 56.98354;
				} else {
					w200 = 291.10175;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[7]) {
					w200 = 344.7425;
				} else {
					w200 = 1160.0889;
				}
			} else {
				w200 = -348.0287;
			}
		}
	}
	float w201;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[27]) {
					w201 = -303.07968;
				} else {
					w201 = -118.947235;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[3]) {
					w201 = -13.884991;
				} else {
					w201 = -123.84487;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[29]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
					w201 = -10.807616;
				} else {
					w201 = 100.03601;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w201 = 8.079297;
				} else {
					w201 = 413.95227;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[5]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w201 = 164.24834;
				} else {
					w201 = -34.653194;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[1]) {
					w201 = -107.24419;
				} else {
					w201 = 288.46112;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[17]) {
					w201 = 254.9279;
				} else {
					w201 = 851.19543;
				}
			} else {
				w201 = -344.54834;
			}
		}
	}
	float w202;
	if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[17]) {
		if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[15]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w202 = -285.31763;
				} else {
					w202 = -127.78684;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[18]) {
					w202 = -131.7593;
				} else {
					w202 = -17.213514;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[35]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[16]) {
					w202 = -381.00317;
				} else {
					w202 = -33.404324;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[5]) {
					w202 = 385.95667;
				} else {
					w202 = 82.28981;
				}
			}
		}
	} else {
		if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[6]) {
					w202 = -119.90613;
				} else {
					w202 = 116.19918;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[7]) {
					w202 = 54.990234;
				} else {
					w202 = 284.61792;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[7]) {
					w202 = 337.10645;
				} else {
					w202 = 1136.8258;
				}
			} else {
				w202 = -341.1029;
			}
		}
	}
	float w203;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[23]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[12]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[4]) {
					w203 = -226.49594;
				} else {
					w203 = 5.885062;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[21]) {
					w203 = 67.20408;
				} else {
					w203 = -118.519196;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[21]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[14]) {
					w203 = -161.42265;
				} else {
					w203 = -19.55267;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
					w203 = 51.25789;
				} else {
					w203 = 250.24092;
				}
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[25]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[5]) {
					w203 = 65.403946;
				} else {
					w203 = 247.2016;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[12]) {
					w203 = -588.3606;
				} else {
					w203 = 426.36624;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[7]) {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[1]) {
					w203 = -176.09428;
				} else {
					w203 = 156.81;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[10]) {
					w203 = 653.5245;
				} else {
					w203 = -337.6918;
				}
			}
		}
	}
	float w204;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[0]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[10]) {
					w204 = -271.40164;
				} else {
					w204 = -106.67494;
				}
			} else {
				w204 = 538.38446;
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w204 = -54.504665;
				} else {
					w204 = 76.93045;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
					w204 = -117.60507;
				} else {
					w204 = 334.78403;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[29]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[26]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
					w204 = -64.40957;
				} else {
					w204 = 195.81561;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[8]) {
					w204 = 39.973328;
				} else {
					w204 = 236.19075;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[24]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w204 = -182.30907;
				} else {
					w204 = 143.69432;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w204 = 473.03467;
				} else {
					w204 = 54.62432;
				}
			}
		}
	}
	float w205;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[33]) {
					w205 = -139.97215;
				} else {
					w205 = -41.283356;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[6]) {
					w205 = 36.928272;
				} else {
					w205 = 395.22256;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
					w205 = -27.575542;
				} else {
					w205 = 103.963554;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[18]) {
					w205 = 9.781236;
				} else {
					w205 = 238.68498;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[45]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[15]) {
					w205 = 430.75537;
				} else {
					w205 = -60.037323;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w205 = 181.66853;
				} else {
					w205 = -78.24976;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[17]) {
					w205 = 245.2352;
				} else {
					w205 = 819.5213;
				}
			} else {
				w205 = -336.9532;
			}
		}
	}
	float w206;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[38]) {
					w206 = -207.72095;
				} else {
					w206 = -84.17402;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
					w206 = -123.27044;
				} else {
					w206 = 281.52838;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[46]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[23]) {
					w206 = -113.21145;
				} else {
					w206 = -8.505914;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w206 = 47.597828;
				} else {
					w206 = 200.02129;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[29]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[26]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
					w206 = -62.97747;
				} else {
					w206 = 191.57254;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[8]) {
					w206 = 39.196564;
				} else {
					w206 = 231.8674;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[24]) {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
					w206 = 61.443134;
				} else {
					w206 = 278.7779;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w206 = 462.87747;
				} else {
					w206 = 52.811985;
				}
			}
		}
	}
	float w207;
	if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[17]) {
		if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[15]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[1]) {
					w207 = -180.0815;
				} else {
					w207 = 97.41499;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w207 = -280.5155;
				} else {
					w207 = -23.01829;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[35]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[16]) {
					w207 = -373.70004;
				} else {
					w207 = -31.686617;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[5]) {
					w207 = 375.036;
				} else {
					w207 = 78.060425;
				}
			}
		}
	} else {
		if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[7]) {
					w207 = -36.290016;
				} else {
					w207 = 187.86006;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
					w207 = 513.6323;
				} else {
					w207 = 158.42241;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[7]) {
					w207 = 322.0108;
				} else {
					w207 = 1098.3916;
				}
			} else {
				w207 = -336.16208;
			}
		}
	}
	float w208;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[13]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[16]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[11]) {
					w208 = -222.26633;
				} else {
					w208 = -39.021957;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[22]) {
					w208 = 202.53583;
				} else {
					w208 = -160.19702;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[21]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[14]) {
					w208 = -153.43867;
				} else {
					w208 = -16.715837;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
					w208 = 53.106476;
				} else {
					w208 = 233.47197;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[34]) {
			if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[2]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[8]) {
					w208 = -1.7701918;
				} else {
					w208 = 194.55415;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[23]) {
					w208 = -19.793438;
				} else {
					w208 = 618.52655;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[9]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[10]) {
					w208 = 316.02133;
				} else {
					w208 = 1166.5217;
				}
			} else {
				w208 = -332.80054;
			}
		}
	}
	float w209;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[6]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
					w209 = -267.20285;
				} else {
					w209 = -80.871796;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[12]) {
					w209 = -13.848488;
				} else {
					w209 = 124.616714;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[14]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[30]) {
					w209 = -16.167978;
				} else {
					w209 = 298.41187;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[48]) {
					w209 = 77.92502;
				} else {
					w209 = 427.84546;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[47]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[32]) {
					w209 = -36.125233;
				} else {
					w209 = -234.9174;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w209 = 101.29168;
				} else {
					w209 = 363.45538;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
					w209 = 248.89725;
				} else {
					w209 = 817.4529;
				}
			} else {
				w209 = -329.47256;
			}
		}
	}
	float w210;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[38]) {
					w210 = -200.79317;
				} else {
					w210 = -81.44065;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
					w210 = -122.27767;
				} else {
					w210 = 272.06268;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[46]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[23]) {
					w210 = -109.156624;
				} else {
					w210 = -7.1502113;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w210 = 46.016163;
				} else {
					w210 = 195.41325;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[29]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[26]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
					w210 = -61.726368;
				} else {
					w210 = 187.39067;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[8]) {
					w210 = 38.57689;
				} else {
					w210 = 224.64285;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[24]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[13]) {
					w210 = -86.719894;
				} else {
					w210 = 148.04688;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w210 = 446.6829;
				} else {
					w210 = 46.993675;
				}
			}
		}
	}
	float w211;
	if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[17]) {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[37]) {
					w211 = -223.7657;
				} else {
					w211 = -76.758514;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[40]) {
					w211 = -104.75265;
				} else {
					w211 = 24.767214;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[16]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[5]) {
					w211 = -20.786545;
				} else {
					w211 = 99.42858;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[13]) {
					w211 = 57.115044;
				} else {
					w211 = 256.7346;
				}
			}
		}
	} else {
		if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[7]) {
					w211 = -36.400093;
				} else {
					w211 = 180.05281;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
					w211 = 499.27017;
				} else {
					w211 = 149.87663;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[7]) {
					w211 = 309.9844;
				} else {
					w211 = 1061.1011;
				}
			} else {
				w211 = -328.64633;
			}
		}
	}
	float w212;
	if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[27]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[63]) {
					w212 = -101.9094;
				} else {
					w212 = -389.237;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[33]) {
					w212 = -171.97449;
				} else {
					w212 = -5.242717;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[64]) {
					w212 = -140.90887;
				} else {
					w212 = -367.76703;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
					w212 = -96.74314;
				} else {
					w212 = 2.365783;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[24]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[29]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w212 = -5.6232176;
				} else {
					w212 = 124.39759;
				}
			} else {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[0]) {
					w212 = 423.54462;
				} else {
					w212 = -88.55414;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[34]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[2]) {
					w212 = 82.19766;
				} else {
					w212 = 429.23;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[9]) {
					w212 = 498.9063;
				} else {
					w212 = -325.35992;
				}
			}
		}
	}
	float w213;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[33]) {
					w213 = -130.75421;
				} else {
					w213 = -37.142254;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[6]) {
					w213 = 34.80869;
				} else {
					w213 = 386.6745;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[19]) {
					w213 = -31.005377;
				} else {
					w213 = 83.22462;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[18]) {
					w213 = 9.656121;
				} else {
					w213 = 225.70709;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[45]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[15]) {
					w213 = 421.2108;
				} else {
					w213 = -61.47259;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w213 = 170.78804;
				} else {
					w213 = -83.48335;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[17]) {
					w213 = 227.36371;
				} else {
					w213 = 760.057;
				}
			} else {
				w213 = -322.10632;
			}
		}
	}
	float w214;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[6]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
					w214 = -257.2418;
				} else {
					w214 = -76.69028;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[12]) {
					w214 = -11.779119;
				} else {
					w214 = 122.29731;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[14]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[30]) {
					w214 = -15.530978;
				} else {
					w214 = 287.14157;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[48]) {
					w214 = 73.348724;
				} else {
					w214 = 412.35046;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[47]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[32]) {
					w214 = -34.08698;
				} else {
					w214 = -231.05632;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w214 = 95.50727;
				} else {
					w214 = 351.77805;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
					w214 = 235.90056;
				} else {
					w214 = 778.0698;
				}
			} else {
				w214 = -318.88522;
			}
		}
	}
	float w215;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[38]) {
					w215 = -191.41287;
				} else {
					w215 = -77.72163;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
					w215 = -121.25866;
				} else {
					w215 = 262.2574;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[46]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[23]) {
					w215 = -103.66808;
				} else {
					w215 = -6.029669;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[17]) {
					w215 = 36.008003;
				} else {
					w215 = 173.24646;
				}
			}
		}
	} else {
		if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[5]) {
					w215 = -12.850041;
				} else {
					w215 = 247.702;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
					w215 = 60.92315;
				} else {
					w215 = 193.14937;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[11]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[2]) {
					w215 = 103.68576;
				} else {
					w215 = 592.7247;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w215 = 985.91516;
				} else {
					w215 = -315.69632;
				}
			}
		}
	}
	float w216;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[13]) {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[3]) {
					w216 = -108.303246;
				} else {
					w216 = -17.34414;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[14]) {
					w216 = -17.834473;
				} else {
					w216 = 263.0141;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[37]) {
					w216 = -159.76318;
				} else {
					w216 = -15.364219;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[24]) {
					w216 = -306.94138;
				} else {
					w216 = 85.39861;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[34]) {
			if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[2]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[8]) {
					w216 = -5.6410546;
				} else {
					w216 = 182.54823;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[23]) {
					w216 = -27.019531;
				} else {
					w216 = 584.998;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[9]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[10]) {
					w216 = 285.707;
				} else {
					w216 = 1094.3508;
				}
			} else {
				w216 = -312.53928;
			}
		}
	}
	float w217;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[34]) {
					w217 = -115.649536;
				} else {
					w217 = -402.0362;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
					w217 = -102.27987;
				} else {
					w217 = -14.424522;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[19]) {
					w217 = -30.038261;
				} else {
					w217 = 79.267456;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[18]) {
					w217 = 10.594382;
				} else {
					w217 = 219.78113;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[45]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[15]) {
					w217 = 414.9493;
				} else {
					w217 = -61.721622;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w217 = 164.80186;
				} else {
					w217 = -86.18885;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[17]) {
					w217 = 216.73248;
				} else {
					w217 = 726.42267;
				}
			} else {
				w217 = -309.41382;
			}
		}
	}
	float w218;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w218 = -248.59418;
				} else {
					w218 = 35.617634;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[24]) {
					w218 = -170.03218;
				} else {
					w218 = -506.97076;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w218 = -85.91502;
				} else {
					w218 = -7.5053563;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[13]) {
					w218 = 230.09569;
				} else {
					w218 = -189.27194;
				}
			}
		}
	} else {
		if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[5]) {
					w218 = -12.49481;
				} else {
					w218 = 242.19817;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
					w218 = 58.868034;
				} else {
					w218 = 187.42183;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[11]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[2]) {
					w218 = 99.569626;
				} else {
					w218 = 576.3885;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w218 = 960.6495;
				} else {
					w218 = -306.31976;
				}
			}
		}
	}
	float w219;
	if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[17]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[50]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[35]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[12]) {
					w219 = -190.93976;
				} else {
					w219 = -63.927605;
				}
			} else {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[3]) {
					w219 = -340.06644;
				} else {
					w219 = 258.57352;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w219 = -36.739994;
				} else {
					w219 = 61.06655;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[36]) {
					w219 = 92.13755;
				} else {
					w219 = 618.2036;
				}
			}
		}
	} else {
		if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[7]) {
					w219 = -38.52061;
				} else {
					w219 = 166.40129;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
					w219 = 478.0328;
				} else {
					w219 = 130.8227;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[10]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[35]) {
					w219 = 331.45984;
				} else {
					w219 = 892.0781;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
					w219 = 350.13452;
				} else {
					w219 = -285.48874;
				}
			}
		}
	}
	float w220;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[27]) {
					w220 = -273.3853;
				} else {
					w220 = -97.92026;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[3]) {
					w220 = -7.8964148;
				} else {
					w220 = -108.002594;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[7]) {
					w220 = -4.4463477;
				} else {
					w220 = 312.31714;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[18]) {
					w220 = 9.896079;
				} else {
					w220 = 214.60454;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[47]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[32]) {
					w220 = -31.459555;
				} else {
					w220 = -225.92963;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w220 = 90.62246;
				} else {
					w220 = 338.73212;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[17]) {
					w220 = 209.56961;
				} else {
					w220 = 703.5542;
				}
			} else {
				w220 = -300.4018;
			}
		}
	}
	float w221;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w221 = -243.32368;
				} else {
					w221 = 35.330944;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[24]) {
					w221 = -166.58241;
				} else {
					w221 = -500.10455;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
					w221 = -98.36907;
				} else {
					w221 = -18.05064;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[13]) {
					w221 = 224.54962;
				} else {
					w221 = -187.70807;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[29]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[26]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
					w221 = -59.77644;
				} else {
					w221 = 176.87852;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[8]) {
					w221 = 36.15206;
				} else {
					w221 = 209.09116;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[24]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w221 = -179.9229;
				} else {
					w221 = 119.47169;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w221 = 412.01477;
				} else {
					w221 = 31.21371;
				}
			}
		}
	}
	float w222;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[13]) {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[3]) {
					w222 = -103.04305;
				} else {
					w222 = -16.949873;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[14]) {
					w222 = -21.139217;
				} else {
					w222 = 254.64688;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[11]) {
					w222 = -20.080826;
				} else {
					w222 = -323.6759;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[24]) {
					w222 = -299.61343;
				} else {
					w222 = 81.65938;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[34]) {
			if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[2]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[8]) {
					w222 = -8.347881;
				} else {
					w222 = 173.44463;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
					w222 = 160.72101;
				} else {
					w222 = 716.2169;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[9]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[10]) {
					w222 = 267.84857;
				} else {
					w222 = 1043.603;
				}
			} else {
				w222 = -299.6139;
			}
		}
	}
	float w223;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w223 = -238.87495;
				} else {
					w223 = 34.883385;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[24]) {
					w223 = -164.96227;
				} else {
					w223 = -493.31912;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w223 = -82.24561;
				} else {
					w223 = -6.030077;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[13]) {
					w223 = 220.70155;
				} else {
					w223 = -184.9659;
				}
			}
		}
	} else {
		if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[5]) {
					w223 = -12.453656;
				} else {
					w223 = 236.08202;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[51]) {
					w223 = 82.55046;
				} else {
					w223 = 365.51132;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[11]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[2]) {
					w223 = 92.06657;
				} else {
					w223 = 553.09186;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w223 = 925.42676;
				} else {
					w223 = -296.61783;
				}
			}
		}
	}
	float w224;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[33]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w224 = -201.6272;
				} else {
					w224 = -76.62018;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[15]) {
					w224 = -33.016315;
				} else {
					w224 = 50.848907;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[22]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[11]) {
					w224 = 39.19709;
				} else {
					w224 = 179.45706;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[7]) {
					w224 = 483.7933;
				} else {
					w224 = 113.710075;
				}
			}
		}
	} else {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[6]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[45]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[15]) {
					w224 = 406.68927;
				} else {
					w224 = -62.385483;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w224 = 157.07936;
				} else {
					w224 = -90.40281;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[17]) {
					w224 = 200.70845;
				} else {
					w224 = 677.7136;
				}
			} else {
				w224 = -293.65158;
			}
		}
	}
	float w225;
	if (LotArea != NULL && *LotArea < cond_LotArea[43]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[3]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
					w225 = -278.94254;
				} else {
					w225 = -88.901985;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[23]) {
					w225 = -83.42544;
				} else {
					w225 = 40.156395;
				}
			}
		} else {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[3]) {
					w225 = -2.489169;
				} else {
					w225 = 234.46086;
				}
			} else {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w225 = 466.10275;
				} else {
					w225 = 139.74416;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[30]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[15]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[32]) {
					w225 = 38.350613;
				} else {
					w225 = -257.07806;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[9]) {
					w225 = -207.87083;
				} else {
					w225 = -9.30334;
				}
			}
		} else {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w225 = -150.76074;
				} else {
					w225 = 134.82675;
				}
			} else {
				w225 = 757.07434;
			}
		}
	}
	float w226;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[13]) {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[3]) {
					w226 = -99.5321;
				} else {
					w226 = -17.136564;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[14]) {
					w226 = -22.3183;
				} else {
					w226 = 247.29887;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[11]) {
					w226 = -18.746809;
				} else {
					w226 = -318.96536;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[24]) {
					w226 = -291.54013;
				} else {
					w226 = 79.00106;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[34]) {
			if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[2]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[8]) {
					w226 = -9.585078;
				} else {
					w226 = 168.45287;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
					w226 = 149.92992;
				} else {
					w226 = 697.63403;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[9]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[10]) {
					w226 = 257.97537;
				} else {
					w226 = 1009.97705;
				}
			} else {
				w226 = -292.06326;
			}
		}
	}
	float w227;
	if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[34]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[37]) {
					w227 = -151.90285;
				} else {
					w227 = -30.078024;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[6]) {
					w227 = -411.9267;
				} else {
					w227 = -36.93199;
				}
			}
		} else {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[38]) {
					w227 = -295.3487;
				} else {
					w227 = -79.79394;
				}
			} else {
				if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
					w227 = 12.752965;
				} else {
					w227 = -126.29417;
				}
			}
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[35]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[17]) {
					w227 = -13.319619;
				} else {
					w227 = -281.51175;
				}
			} else {
				if (BsmtFullBath != NULL && *BsmtFullBath < cond_BsmtFullBath[0]) {
					w227 = -101.366104;
				} else {
					w227 = 403.02957;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[25]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w227 = 30.397701;
				} else {
					w227 = 196.64552;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[34]) {
					w227 = 140.99512;
				} else {
					w227 = 411.75034;
				}
			}
		}
	}
	float w228;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w228 = -230.66008;
				} else {
					w228 = 36.263203;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[24]) {
					w228 = -161.9628;
				} else {
					w228 = -483.8529;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w228 = -78.89949;
				} else {
					w228 = -4.8996706;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[13]) {
					w228 = 214.28946;
				} else {
					w228 = -182.69435;
				}
			}
		}
	} else {
		if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[36]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[23]) {
					w228 = -45.871555;
				} else {
					w228 = 84.98334;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[48]) {
					w228 = 48.699764;
				} else {
					w228 = 243.98875;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[11]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[2]) {
					w228 = 86.35862;
				} else {
					w228 = 532.4627;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w228 = 895.6437;
				} else {
					w228 = -293.26016;
				}
			}
		}
	}
	float w229;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[39]) {
					w229 = -125.75181;
				} else {
					w229 = -369.18814;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[15]) {
					w229 = -35.559242;
				} else {
					w229 = 45.44191;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[22]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[11]) {
					w229 = 39.026756;
				} else {
					w229 = 173.28453;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[7]) {
					w229 = 469.3927;
				} else {
					w229 = 106.506325;
				}
			}
		}
	} else {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[12]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[45]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[15]) {
					w229 = 400.94662;
				} else {
					w229 = -72.28309;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w229 = 154.21596;
				} else {
					w229 = -93.362785;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[28]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[18]) {
					w229 = 290.83545;
				} else {
					w229 = -160.91534;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
					w229 = 443.2181;
				} else {
					w229 = -290.32748;
				}
			}
		}
	}
	float w230;
	if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[34]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[37]) {
					w230 = -148.76411;
				} else {
					w230 = -29.28948;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[6]) {
					w230 = -404.32364;
				} else {
					w230 = -36.07711;
				}
			}
		} else {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[38]) {
					w230 = -289.38904;
				} else {
					w230 = -77.29784;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
					w230 = -219.54019;
				} else {
					w230 = 5.1762953;
				}
			}
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[35]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[17]) {
					w230 = -12.818726;
				} else {
					w230 = -276.92276;
				}
			} else {
				if (BsmtFullBath != NULL && *BsmtFullBath < cond_BsmtFullBath[0]) {
					w230 = -100.45052;
				} else {
					w230 = 394.55087;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[25]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w230 = 29.031858;
				} else {
					w230 = 192.19453;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[34]) {
					w230 = 136.42157;
				} else {
					w230 = 400.64127;
				}
			}
		}
	}
	float w231;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w231 = -225.365;
				} else {
					w231 = 36.60574;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[24]) {
					w231 = -158.72177;
				} else {
					w231 = -476.0516;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[17]) {
					w231 = -160.57959;
				} else {
					w231 = 71.4376;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
					w231 = -28.653677;
				} else {
					w231 = 140.9794;
				}
			}
		}
	} else {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[13]) {
			if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[5]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
					w231 = -10.981041;
				} else {
					w231 = 95.825745;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[17]) {
					w231 = 196.2067;
				} else {
					w231 = 610.83057;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[16]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[25]) {
					w231 = 319.15967;
				} else {
					w231 = 937.8687;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[26]) {
					w231 = -306.0082;
				} else {
					w231 = 125.43023;
				}
			}
		}
	}
	float w232;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[4]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[39]) {
					w232 = -122.03297;
				} else {
					w232 = -361.9068;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[15]) {
					w232 = -34.656578;
				} else {
					w232 = 44.39792;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[22]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[27]) {
					w232 = 372.80426;
				} else {
					w232 = 82.86202;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[7]) {
					w232 = 457.5767;
				} else {
					w232 = 102.79465;
				}
			}
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[35]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[15]) {
					w232 = 396.5511;
				} else {
					w232 = -37.859562;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[39]) {
					w232 = 679.3005;
				} else {
					w232 = 111.216675;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[7]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[7]) {
					w232 = 39.592896;
				} else {
					w232 = 234.66013;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[16]) {
					w232 = 893.5682;
				} else {
					w232 = -154.03313;
				}
			}
		}
	}
	float w233;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[38]) {
					w233 = -167.69087;
				} else {
					w233 = -67.27658;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
					w233 = -127.03485;
				} else {
					w233 = 234.26746;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[46]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
					w233 = -37.512695;
				} else {
					w233 = 141.5793;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[17]) {
					w233 = 32.420097;
				} else {
					w233 = 163.62032;
				}
			}
		}
	} else {
		if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[36]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[15]) {
					w233 = -227.07738;
				} else {
					w233 = -10.472771;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[48]) {
					w233 = 46.575275;
				} else {
					w233 = 236.2928;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[11]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[2]) {
					w233 = 81.512215;
				} else {
					w233 = 508.78006;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w233 = 859.262;
				} else {
					w233 = -286.83014;
				}
			}
		}
	}
	float w234;
	if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[34]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[37]) {
					w234 = -144.15222;
				} else {
					w234 = -27.736692;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[6]) {
					w234 = -394.62317;
				} else {
					w234 = -35.15824;
				}
			}
		} else {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[38]) {
					w234 = -282.99277;
				} else {
					w234 = -74.30973;
				}
			} else {
				if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
					w234 = 13.163704;
				} else {
					w234 = -120.58696;
				}
			}
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[35]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[17]) {
					w234 = -12.081199;
				} else {
					w234 = -272.63757;
				}
			} else {
				if (BsmtFullBath != NULL && *BsmtFullBath < cond_BsmtFullBath[0]) {
					w234 = -99.62022;
				} else {
					w234 = 383.7922;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[25]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w234 = 27.152967;
				} else {
					w234 = 186.74469;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[34]) {
					w234 = 131.38232;
				} else {
					w234 = 386.89154;
				}
			}
		}
	}
	float w235;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w235 = -227.48157;
				} else {
					w235 = -75.29049;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
					w235 = -125.696625;
				} else {
					w235 = 230.31929;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[46]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[13]) {
					w235 = -32.877472;
				} else {
					w235 = 232.27074;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[18]) {
					w235 = 75.75588;
				} else {
					w235 = 502.155;
				}
			}
		}
	} else {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[13]) {
			if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[5]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
					w235 = -11.016562;
				} else {
					w235 = 92.549965;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[17]) {
					w235 = 189.08142;
				} else {
					w235 = 591.3275;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[16]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[25]) {
					w235 = 311.6368;
				} else {
					w235 = 902.2877;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[26]) {
					w235 = -302.78073;
				} else {
					w235 = 124.31015;
				}
			}
		}
	}
	float w236;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[20]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[3]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
					w236 = -75.12544;
				} else {
					w236 = -473.24643;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[13]) {
					w236 = -20.818605;
				} else {
					w236 = 165.6934;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[14]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[10]) {
					w236 = -15.722652;
				} else {
					w236 = 101.91092;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[48]) {
					w236 = 86.19084;
				} else {
					w236 = 503.42548;
				}
			}
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[35]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[15]) {
					w236 = 391.7068;
				} else {
					w236 = -37.36049;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[39]) {
					w236 = 662.4734;
				} else {
					w236 = 104.73441;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[7]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[7]) {
					w236 = 37.20832;
				} else {
					w236 = 227.42914;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[16]) {
					w236 = 860.5842;
				} else {
					w236 = -151.91331;
				}
			}
		}
	}
	float w237;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[35]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[40]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[52]) {
					w237 = -252.22095;
				} else {
					w237 = 84.49456;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w237 = -48.35771;
				} else {
					w237 = -139.26979;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[11]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w237 = -60.93965;
				} else {
					w237 = 9.084893;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[53]) {
					w237 = -46.441376;
				} else {
					w237 = -452.97806;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[18]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[8]) {
					w237 = -25.668867;
				} else {
					w237 = -340.55807;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[7]) {
					w237 = 69.70975;
				} else {
					w237 = 446.6564;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[35]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[14]) {
					w237 = -360.2613;
				} else {
					w237 = 94.93933;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[14]) {
					w237 = 66.06831;
				} else {
					w237 = 218.88695;
				}
			}
		}
	}
	float w238;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w238 = -222.63083;
				} else {
					w238 = -73.52348;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
					w238 = -123.54738;
				} else {
					w238 = 225.64415;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[46]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
					w238 = -35.213165;
				} else {
					w238 = 139.7115;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[18]) {
					w238 = 74.228264;
				} else {
					w238 = 498.73746;
				}
			}
		}
	} else {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[13]) {
			if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[5]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
					w238 = -10.720204;
				} else {
					w238 = 89.62408;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[17]) {
					w238 = 185.64275;
				} else {
					w238 = 577.5357;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[16]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[25]) {
					w238 = 304.65717;
				} else {
					w238 = 879.5548;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[26]) {
					w238 = -299.22104;
				} else {
					w238 = 124.02164;
				}
			}
		}
	}
	float w239;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[20]) {
					w239 = -70.99898;
				} else {
					w239 = -7.806349;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[19]) {
					w239 = 22.973047;
				} else {
					w239 = 226.79776;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[37]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w239 = 34.254734;
				} else {
					w239 = 497.4191;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[19]) {
					w239 = -96.01562;
				} else {
					w239 = 380.15924;
				}
			}
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[35]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[15]) {
					w239 = 386.7346;
				} else {
					w239 = -37.63026;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[39]) {
					w239 = 650.3242;
				} else {
					w239 = 100.0705;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[7]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[7]) {
					w239 = 35.7554;
				} else {
					w239 = 221.60771;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[16]) {
					w239 = 839.2594;
				} else {
					w239 = -150.31476;
				}
			}
		}
	}
	float w240;
	if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[34]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[37]) {
					w240 = -138.54192;
				} else {
					w240 = -25.588009;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[6]) {
					w240 = -386.25644;
				} else {
					w240 = -33.443085;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[27]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w240 = -102.76328;
				} else {
					w240 = -351.66983;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
					w240 = -80.73016;
				} else {
					w240 = 4.7829924;
				}
			}
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[54]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[14]) {
					w240 = -18.06059;
				} else {
					w240 = -509.33273;
				}
			} else {
				if (BsmtFullBath != NULL && *BsmtFullBath < cond_BsmtFullBath[0]) {
					w240 = -99.43035;
				} else {
					w240 = 365.16074;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[25]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w240 = 22.55609;
				} else {
					w240 = 180.6671;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[20]) {
					w240 = 333.6188;
				} else {
					w240 = 115.45189;
				}
			}
		}
	}
	float w241;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[38]) {
					w241 = -158.00453;
				} else {
					w241 = -62.44172;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
					w241 = -122.56888;
				} else {
					w241 = 219.79373;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[46]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[13]) {
					w241 = -30.303978;
				} else {
					w241 = 228.10553;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[18]) {
					w241 = 72.2777;
				} else {
					w241 = 494.1744;
				}
			}
		}
	} else {
		if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[24]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
					w241 = 0.07081568;
				} else {
					w241 = 160.39796;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[61]) {
					w241 = -182.09962;
				} else {
					w241 = 185.96344;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[11]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[2]) {
					w241 = 73.541374;
				} else {
					w241 = 477.15735;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w241 = 810.13477;
				} else {
					w241 = -282.13205;
				}
			}
		}
	}
	float w242;
	if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[33]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w242 = -176.80104;
				} else {
					w242 = -66.82777;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[34]) {
					w242 = -10.382428;
				} else {
					w242 = 292.23758;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[22]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[27]) {
					w242 = 362.38324;
				} else {
					w242 = 78.18602;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[7]) {
					w242 = 422.86008;
				} else {
					w242 = 89.228905;
				}
			}
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[35]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[15]) {
					w242 = 382.9329;
				} else {
					w242 = -36.7692;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[39]) {
					w242 = 636.98175;
				} else {
					w242 = 93.15113;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[7]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[7]) {
					w242 = 34.146244;
				} else {
					w242 = 215.25542;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[16]) {
					w242 = 818.0486;
				} else {
					w242 = -147.80684;
				}
			}
		}
	}
	float w243;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[28]) {
					w243 = -144.69968;
				} else {
					w243 = -347.84576;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[19]) {
					w243 = -151.07669;
				} else {
					w243 = -0.41699216;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[13]) {
					w243 = -40.482647;
				} else {
					w243 = -166.6434;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[10]) {
					w243 = 1.3798581;
				} else {
					w243 = 210.06012;
				}
			}
		}
	} else {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[13]) {
			if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[5]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
					w243 = -10.640765;
				} else {
					w243 = 86.07712;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[17]) {
					w243 = 178.86208;
				} else {
					w243 = 555.96844;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[16]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[25]) {
					w243 = 296.35092;
				} else {
					w243 = 837.7835;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[26]) {
					w243 = -292.49683;
				} else {
					w243 = 124.46109;
				}
			}
		}
	}
	float w244;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[26]) {
					w244 = -103.76199;
				} else {
					w244 = -220.51352;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w244 = 249.93018;
				} else {
					w244 = -108.270584;
				}
			}
		} else {
			if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[2]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[14]) {
					w244 = -13.739552;
				} else {
					w244 = -252.60606;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
					w244 = 46.193043;
				} else {
					w244 = 443.14758;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[34]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[36]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[3]) {
					w244 = -212.83972;
				} else {
					w244 = 36.25274;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[20]) {
					w244 = -119.06558;
				} else {
					w244 = 372.3799;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[10]) {
					w244 = 279.10248;
				} else {
					w244 = 851.2253;
				}
			} else {
				w244 = -274.90765;
			}
		}
	}
	float w245;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[35]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[40]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[52]) {
					w245 = -241.89204;
				} else {
					w245 = 84.86437;
				}
			} else {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w245 = -48.719997;
				} else {
					w245 = -138.95975;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[11]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w245 = -57.45388;
				} else {
					w245 = 10.53999;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[53]) {
					w245 = -46.482246;
				} else {
					w245 = -444.0339;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[18]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[8]) {
					w245 = -24.361645;
				} else {
					w245 = -332.6372;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[7]) {
					w245 = 66.035614;
				} else {
					w245 = 419.25104;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[35]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[14]) {
					w245 = -349.54596;
				} else {
					w245 = 93.2165;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[14]) {
					w245 = 62.30611;
				} else {
					w245 = 204.98604;
				}
			}
		}
	}
	float w246;
	if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
				if (PoolArea != NULL && *PoolArea < cond_PoolArea[0]) {
					w246 = -65.98025;
				} else {
					w246 = 488.8813;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[40]) {
					w246 = -325.482;
				} else {
					w246 = 15.724797;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
				w246 = 737.58105;
			} else {
				w246 = 30.06281;
			}
		}
	} else {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w246 = 5.956253;
				} else {
					w246 = 490.03207;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[9]) {
					w246 = 196.14223;
				} else {
					w246 = -168.84953;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
				w246 = 642.4891;
			} else {
				w246 = 157.33577;
			}
		}
	}
	float w247;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[2]) {
					w247 = -161.74881;
				} else {
					w247 = 110.07574;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w247 = -471.58954;
				} else {
					w247 = -108.98769;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[0]) {
					w247 = -147.91765;
				} else {
					w247 = -54.052544;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[11]) {
					w247 = -10.677521;
				} else {
					w247 = -292.15915;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[18]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[8]) {
					w247 = -23.60109;
				} else {
					w247 = -327.02768;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[7]) {
					w247 = 65.336205;
				} else {
					w247 = 412.61987;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[35]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[14]) {
					w247 = -342.6674;
				} else {
					w247 = 93.27047;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[14]) {
					w247 = 61.013123;
				} else {
					w247 = 200.37076;
				}
			}
		}
	}
	float w248;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[2]) {
		if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[2]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
					w248 = -164.90172;
				} else {
					w248 = 169.64008;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[14]) {
					w248 = -13.175247;
				} else {
					w248 = -251.12598;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
				w248 = 46.32375;
			} else {
				w248 = 437.1199;
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[34]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[45]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[3]) {
					w248 = -200.67957;
				} else {
					w248 = -7.8589287;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[36]) {
					w248 = 57.57619;
				} else {
					w248 = 273.91437;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[10]) {
					w248 = 269.39252;
				} else {
					w248 = 831.4675;
				}
			} else {
				w248 = -274.52374;
			}
		}
	}
	float w249;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[21]) {
					w249 = -58.475746;
				} else {
					w249 = -148.19934;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
					w249 = -117.97721;
				} else {
					w249 = 212.06146;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[40]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[18]) {
					w249 = -96.12829;
				} else {
					w249 = 96.80565;
				}
			} else {
				if (PoolArea != NULL && *PoolArea < cond_PoolArea[0]) {
					w249 = 24.16983;
				} else {
					w249 = 453.69818;
				}
			}
		}
	} else {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[5]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[13]) {
					w249 = -10.569334;
				} else {
					w249 = 507.66824;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w249 = 52.376896;
				} else {
					w249 = 196.84286;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[10]) {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w249 = 265.6363;
				} else {
					w249 = 20.825752;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[5]) {
					w249 = 660.6819;
				} else {
					w249 = 205.49484;
				}
			}
		}
	}
	float w250;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[38]) {
					w250 = -76.70881;
				} else {
					w250 = -5.3401327;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[11]) {
					w250 = 41.10776;
				} else {
					w250 = 189.67648;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[48]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[17]) {
					w250 = 13.289188;
				} else {
					w250 = 156.0895;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[1]) {
					w250 = 109.43506;
				} else {
					w250 = 446.1169;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[15]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[16]) {
					w250 = 193.9302;
				} else {
					w250 = -61.275185;
				}
			} else {
				w250 = 591.37384;
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w250 = 239.72249;
			} else {
				w250 = -437.3617;
			}
		}
	}
	float w251;
	if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[34]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[37]) {
					w251 = -129.54001;
				} else {
					w251 = -22.0211;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[6]) {
					w251 = -374.27753;
				} else {
					w251 = -28.001484;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[27]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w251 = -92.39685;
				} else {
					w251 = -333.94647;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
					w251 = -74.14491;
				} else {
					w251 = 5.8951807;
				}
			}
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[54]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[24]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[65]) {
					w251 = -44.36881;
				} else {
					w251 = -364.14825;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[17]) {
					w251 = 8.73216;
				} else {
					w251 = -190.63196;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[25]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w251 = 19.446209;
				} else {
					w251 = 171.09138;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[6]) {
					w251 = 229.11314;
				} else {
					w251 = -3.4027343;
				}
			}
		}
	}
	float w252;
	if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
				if (PoolArea != NULL && *PoolArea < cond_PoolArea[0]) {
					w252 = -62.766064;
				} else {
					w252 = 476.92804;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[40]) {
					w252 = -314.75412;
				} else {
					w252 = 14.861747;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
				w252 = 713.93286;
			} else {
				w252 = 20.819061;
			}
		}
	} else {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
					w252 = 5.1208696;
				} else {
					w252 = 149.84401;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w252 = 900.52594;
				} else {
					w252 = 155.05014;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
				w252 = 616.493;
			} else {
				w252 = 148.52843;
			}
		}
	}
	float w253;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[2]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
				w253 = -342.2501;
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w253 = -178.581;
				} else {
					w253 = -78.46501;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[30]) {
					w253 = -48.996315;
				} else {
					w253 = 138.82399;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[66]) {
					w253 = 14.213375;
				} else {
					w253 = 220.0969;
				}
			}
		}
	} else {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[5]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[13]) {
					w253 = -9.805974;
				} else {
					w253 = 496.4062;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
					w253 = 49.851677;
				} else {
					w253 = 190.06177;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[10]) {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w253 = 257.57468;
				} else {
					w253 = 18.317556;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[5]) {
					w253 = 641.6925;
				} else {
					w253 = 198.20906;
				}
			}
		}
	}
	float w254;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[2]) {
		if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[2]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
					w254 = -159.01825;
				} else {
					w254 = 168.74362;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[14]) {
					w254 = -12.223679;
				} else {
					w254 = -248.80315;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w254 = 53.808163;
				} else {
					w254 = 13.520508;
				}
			} else {
				w254 = 426.0224;
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[34]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[36]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[3]) {
					w254 = -199.69595;
				} else {
					w254 = 33.366512;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[20]) {
					w254 = -125.909996;
				} else {
					w254 = 350.17932;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[10]) {
					w254 = 258.06946;
				} else {
					w254 = 797.7557;
				}
			} else {
				w254 = -276.63483;
			}
		}
	}
	float w255;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[35]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[40]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[52]) {
					w255 = -229.83984;
				} else {
					w255 = 85.445625;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w255 = -36.34018;
				} else {
					w255 = -124.40874;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[11]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w255 = -53.73005;
				} else {
					w255 = 11.723506;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[22]) {
					w255 = 50.032124;
				} else {
					w255 = -361.9381;
				}
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[18]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[8]) {
					w255 = -21.952616;
				} else {
					w255 = -321.82004;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[29]) {
					w255 = -15.17618;
				} else {
					w255 = 162.33841;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[35]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[14]) {
					w255 = -330.41254;
				} else {
					w255 = 92.373276;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
					w255 = 188.41498;
				} else {
					w255 = 57.095978;
				}
			}
		}
	}
	float w256;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[38]) {
					w256 = -73.19748;
				} else {
					w256 = -5.1146073;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[11]) {
					w256 = 40.391148;
				} else {
					w256 = 183.26251;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[48]) {
				if (YrSold != NULL && *YrSold < cond_YrSold[1]) {
					w256 = 75.28301;
				} else {
					w256 = -10.832623;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[21]) {
					w256 = -55.39587;
				} else {
					w256 = 270.2133;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[15]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[16]) {
					w256 = 187.24655;
				} else {
					w256 = -65.74181;
				}
			} else {
				w256 = 568.1427;
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w256 = 229.09616;
			} else {
				w256 = -435.91476;
			}
		}
	}
	float w257;
	if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
				if (PoolArea != NULL && *PoolArea < cond_PoolArea[0]) {
					w257 = -60.05443;
				} else {
					w257 = 469.58823;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[10]) {
					w257 = -13.167744;
				} else {
					w257 = 72.63205;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
				w257 = 693.51526;
			} else {
				w257 = 14.847187;
			}
		}
	} else {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
					w257 = 4.7128654;
				} else {
					w257 = 143.75975;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w257 = 892.56256;
				} else {
					w257 = 154.28238;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
				w257 = 593.5159;
			} else {
				w257 = 140.32547;
			}
		}
	}
	float w258;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
				w258 = -333.6318;
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w258 = -173.00056;
				} else {
					w258 = -75.04058;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
					w258 = -101.5308;
				} else {
					w258 = -365.99396;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
					w258 = -24.56562;
				} else {
					w258 = 123.84759;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[29]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[26]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[15]) {
					w258 = -228.5509;
				} else {
					w258 = -22.715113;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[9]) {
					w258 = 32.817703;
				} else {
					w258 = 241.38728;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[24]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[22]) {
					w258 = 91.67865;
				} else {
					w258 = -153.35109;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[22]) {
					w258 = -43.660194;
				} else {
					w258 = 320.97324;
				}
			}
		}
	}
	float w259;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[38]) {
					w259 = -70.987724;
				} else {
					w259 = -5.208344;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[11]) {
					w259 = 40.442364;
				} else {
					w259 = 179.24599;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[48]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[17]) {
					w259 = 11.094461;
				} else {
					w259 = 148.51205;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
					w259 = 100.19482;
				} else {
					w259 = 421.31946;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[15]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[16]) {
					w259 = 182.76128;
				} else {
					w259 = -65.056595;
				}
			} else {
				w259 = 557.9962;
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w259 = 224.9353;
			} else {
				w259 = -433.13614;
			}
		}
	}
	float w260;
	if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[31]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w260 = -36.3591;
				} else {
					w260 = 36.453297;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[22]) {
					w260 = -14.703632;
				} else {
					w260 = 313.50674;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
				w260 = 680.19653;
			} else {
				w260 = 11.576718;
			}
		}
	} else {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
					w260 = 4.7033854;
				} else {
					w260 = 139.48022;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w260 = 885.6614;
				} else {
					w260 = 153.60088;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
				w260 = 580.2631;
			} else {
				w260 = 134.6986;
			}
		}
	}
	float w261;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
				w261 = -328.5374;
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w261 = -169.52345;
				} else {
					w261 = -73.53643;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
					w261 = -99.08869;
				} else {
					w261 = -360.51416;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
					w261 = -23.664085;
				} else {
					w261 = 119.79817;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[29]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[26]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[15]) {
					w261 = -224.1358;
				} else {
					w261 = -22.097185;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w261 = 7.0549264;
				} else {
					w261 = 88.66483;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[24]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[22]) {
					w261 = 89.829285;
				} else {
					w261 = -152.06389;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[23]) {
					w261 = 186.26184;
				} else {
					w261 = 662.39435;
				}
			}
		}
	}
	float w262;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[15]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[20]) {
					w262 = -117.30582;
				} else {
					w262 = -329.31775;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
					w262 = -33.218166;
				} else {
					w262 = -313.8054;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[20]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[39]) {
					w262 = -38.599186;
				} else {
					w262 = 24.283457;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[17]) {
					w262 = 81.89177;
				} else {
					w262 = 308.14725;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[15]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[16]) {
					w262 = 178.29109;
				} else {
					w262 = -64.3634;
				}
			} else {
				w262 = 548.53723;
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w262 = 221.81601;
			} else {
				w262 = -429.69687;
			}
		}
	}
	float w263;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[2]) {
		if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[2]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
					w263 = -151.30779;
				} else {
					w263 = 166.77785;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[14]) {
					w263 = -10.993274;
				} else {
					w263 = -249.45248;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[2]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w263 = 54.519024;
				} else {
					w263 = 12.673476;
				}
			} else {
				w263 = 413.82935;
			}
		}
	} else {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[34]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[45]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[41]) {
					w263 = -65.82409;
				} else {
					w263 = 41.388298;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[36]) {
					w263 = 51.415966;
				} else {
					w263 = 249.0987;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[10]) {
					w263 = 242.82928;
				} else {
					w263 = 753.76227;
				}
			} else {
				w263 = -279.24313;
			}
		}
	}
	float w264;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[40]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[11]) {
					w264 = -241.9235;
				} else {
					w264 = 15.565351;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[40]) {
					w264 = -23.929504;
				} else {
					w264 = 468.91357;
				}
			}
		} else {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[2]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[23]) {
					w264 = -19.485964;
				} else {
					w264 = 79.17655;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w264 = 99.64195;
				} else {
					w264 = 554.4568;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (MoSold != NULL && *MoSold < cond_MoSold[7]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w264 = -145.39389;
				} else {
					w264 = -36.521954;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[11]) {
					w264 = 52.358253;
				} else {
					w264 = 182.04547;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
				w264 = 563.8096;
			} else {
				w264 = 130.29546;
			}
		}
	}
	float w265;
	if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[31]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w265 = -35.286537;
				} else {
					w265 = 35.94616;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[22]) {
					w265 = -16.303007;
				} else {
					w265 = 304.4524;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
				w265 = 659.57404;
			} else {
				w265 = 5.3671875;
			}
		}
	} else {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
					w265 = 4.175679;
				} else {
					w265 = 134.0807;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w265 = 878.43396;
				} else {
					w265 = 152.4804;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
				w265 = 557.0439;
			} else {
				w265 = 128.99266;
			}
		}
	}
	float w266;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[35]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[40]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[52]) {
					w266 = -219.4857;
				} else {
					w266 = 85.91183;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w266 = -30.96464;
				} else {
					w266 = -116.53656;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[11]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w266 = -50.414883;
				} else {
					w266 = 12.9166765;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[53]) {
					w266 = -39.508064;
				} else {
					w266 = -424.06033;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[11]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w266 = -105.47494;
				} else {
					w266 = -393.8022;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[12]) {
					w266 = 90.40841;
				} else {
					w266 = -52.70955;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[18]) {
					w266 = -22.807373;
				} else {
					w266 = 92.98393;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
					w266 = 171.35068;
				} else {
					w266 = 49.484806;
				}
			}
		}
	}
	float w267;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[40]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[11]) {
					w267 = -235.65306;
				} else {
					w267 = 14.638307;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[40]) {
					w267 = -23.287489;
				} else {
					w267 = 461.81143;
				}
			}
		} else {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[2]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[24]) {
					w267 = -18.287344;
				} else {
					w267 = 77.452965;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w267 = 99.06234;
				} else {
					w267 = 545.5948;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (MoSold != NULL && *MoSold < cond_MoSold[7]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w267 = -143.78091;
				} else {
					w267 = -37.268436;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[11]) {
					w267 = 51.88178;
				} else {
					w267 = 178.63614;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
				w267 = 549.26953;
			} else {
				w267 = 126.96;
			}
		}
	}
	float w268;
	if (LotArea != NULL && *LotArea < cond_LotArea[6]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[41]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[12]) {
					w268 = -146.26735;
				} else {
					w268 = -39.435623;
				}
			} else {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[3]) {
					w268 = -232.4088;
				} else {
					w268 = 246.25406;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w268 = 15.77871;
			} else {
				w268 = 388.378;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w268 = -21.490437;
				} else {
					w268 = 57.004417;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w268 = 648.97015;
				} else {
					w268 = 4.3748436;
				}
			}
		} else {
			if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[10]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w268 = 66.934364;
				} else {
					w268 = 469.32086;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
					w268 = 176.41594;
				} else {
					w268 = 542.67816;
				}
			}
		}
	}
	float w269;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[25]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[3]) {
					w269 = -181.32915;
				} else {
					w269 = -49.13764;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w269 = 240.38774;
				} else {
					w269 = -104.34082;
				}
			}
		} else {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[5]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
					w269 = -21.35287;
				} else {
					w269 = 96.930534;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[30]) {
					w269 = 189.65636;
				} else {
					w269 = 550.564;
				}
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[19]) {
					w269 = 21.864288;
				} else {
					w269 = -118.28889;
				}
			} else {
				w269 = 592.52686;
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[42]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[16]) {
					w269 = 40.94149;
				} else {
					w269 = -104.77915;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w269 = 254.9925;
				} else {
					w269 = -159.79626;
				}
			}
		}
	}
	float w270;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[1]) {
					w270 = -262.5496;
				} else {
					w270 = -57.946228;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[28]) {
					w270 = -104.711334;
				} else {
					w270 = 52.07409;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[11]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[17]) {
					w270 = -21.781546;
				} else {
					w270 = 193.26941;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[22]) {
					w270 = 53.731777;
				} else {
					w270 = -350.8239;
				}
			}
		}
	} else {
		if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
			if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[5]) {
				if (PoolArea != NULL && *PoolArea < cond_PoolArea[3]) {
					w270 = 27.361504;
				} else {
					w270 = 586.6017;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
					w270 = 126.122604;
				} else {
					w270 = 433.69714;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[5]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[18]) {
					w270 = -39.18535;
				} else {
					w270 = -396.46347;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[24]) {
					w270 = -1.0574344;
				} else {
					w270 = -152.43417;
				}
			}
		}
	}
	float w271;
	if (LotArea != NULL && *LotArea < cond_LotArea[6]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[41]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[12]) {
					w271 = -142.28914;
				} else {
					w271 = -38.397377;
				}
			} else {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[3]) {
					w271 = -228.91893;
				} else {
					w271 = 244.36218;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w271 = 15.615352;
			} else {
				w271 = 383.6169;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w271 = -20.996277;
				} else {
					w271 = 56.04699;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w271 = 634.8954;
				} else {
					w271 = 3.9726562;
				}
			}
		} else {
			if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[10]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w271 = 64.866554;
				} else {
					w271 = 462.7878;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
					w271 = 169.76273;
				} else {
					w271 = 527.9017;
				}
			}
		}
	}
	float w272;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[15]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[20]) {
					w272 = -108.884636;
				} else {
					w272 = -314.17706;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
					w272 = -30.213345;
				} else {
					w272 = -309.47278;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[20]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[39]) {
					w272 = -37.021877;
				} else {
					w272 = 23.309996;
				}
			} else {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[1]) {
					w272 = 180.7228;
				} else {
					w272 = -117.04403;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[15]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[16]) {
					w272 = 168.4923;
				} else {
					w272 = -69.838684;
				}
			} else {
				w272 = 514.7577;
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w272 = 206.92781;
			} else {
				w272 = -427.70013;
			}
		}
	}
	float w273;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[11]) {
					w273 = -251.98727;
				} else {
					w273 = 13.580912;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[40]) {
					w273 = -22.71949;
				} else {
					w273 = 450.85266;
				}
			}
		} else {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[2]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[23]) {
					w273 = -18.712772;
				} else {
					w273 = 74.05094;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w273 = 98.78672;
				} else {
					w273 = 525.06946;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (MoSold != NULL && *MoSold < cond_MoSold[7]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w273 = -141.9808;
				} else {
					w273 = -34.234688;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[11]) {
					w273 = 49.70258;
				} else {
					w273 = 173.07321;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
				w273 = 518.90497;
			} else {
				w273 = 116.75844;
			}
		}
	}
	float w274;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w274 = -171.79982;
				} else {
					w274 = 65.231735;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[24]) {
					w274 = -124.10812;
				} else {
					w274 = -422.52682;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[17]) {
					w274 = -126.2192;
				} else {
					w274 = 56.056553;
				}
			} else {
				if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
					w274 = -12.808677;
				} else {
					w274 = 415.18326;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[29]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[26]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[26]) {
					w274 = -43.15139;
				} else {
					w274 = 209.56244;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[29]) {
					w274 = 32.783905;
				} else {
					w274 = 347.82877;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[24]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[22]) {
					w274 = 82.57975;
				} else {
					w274 = -154.15897;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[23]) {
					w274 = 168.91641;
				} else {
					w274 = 635.14703;
				}
			}
		}
	}
	float w275;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[25]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[5]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
					w275 = -148.34024;
				} else {
					w275 = 163.93459;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
					w275 = -20.530373;
				} else {
					w275 = 93.75626;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[30]) {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[10]) {
					w275 = 173.49162;
				} else {
					w275 = -105.94008;
				}
			} else {
				w275 = 539.65765;
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[1]) {
					w275 = -7.259544;
				} else {
					w275 = 198.88525;
				}
			} else {
				w275 = 568.391;
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[42]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[16]) {
					w275 = 40.07461;
				} else {
					w275 = -104.3716;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w275 = 245.66283;
				} else {
					w275 = -160.69328;
				}
			}
		}
	}
	float w276;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[40]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[11]) {
					w276 = -224.51648;
				} else {
					w276 = 13.955325;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[40]) {
					w276 = -21.687546;
				} else {
					w276 = 443.12003;
				}
			}
		} else {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[2]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[25]) {
					w276 = 97.00551;
				} else {
					w276 = 4.9012475;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w276 = 97.95398;
				} else {
					w276 = 511.22922;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (MoSold != NULL && *MoSold < cond_MoSold[7]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w276 = -140.34937;
				} else {
					w276 = -34.926796;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[11]) {
					w276 = 48.57453;
				} else {
					w276 = 168.97758;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
				w276 = 506.97186;
			} else {
				w276 = 114.83828;
			}
		}
	}
	float w277;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[35]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[43]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[52]) {
					w277 = -194.63753;
				} else {
					w277 = -8.510993;
				}
			} else {
				if (YrSold != NULL && *YrSold < cond_YrSold[2]) {
					w277 = -31.559578;
				} else {
					w277 = -175.28937;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[11]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
					w277 = -47.166718;
				} else {
					w277 = 13.608596;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[22]) {
					w277 = 53.737263;
				} else {
					w277 = -345.01358;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[11]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w277 = -92.43967;
				} else {
					w277 = -375.17636;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[12]) {
					w277 = 87.40773;
				} else {
					w277 = -54.695663;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[27]) {
					w277 = -25.863358;
				} else {
					w277 = 57.952225;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
					w277 = 75.10072;
				} else {
					w277 = 340.28735;
				}
			}
		}
	}
	float w278;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[29]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[20]) {
					w278 = -104.45342;
				} else {
					w278 = -306.74887;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
					w278 = -29.82658;
				} else {
					w278 = -304.9164;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[20]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[39]) {
					w278 = -35.582676;
				} else {
					w278 = 22.353107;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[19]) {
					w278 = 63.823036;
				} else {
					w278 = 269.36984;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[15]) {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[0]) {
					w278 = 121.46641;
				} else {
					w278 = 418.9367;
				}
			} else {
				w278 = 497.6906;
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w278 = 195.12726;
			} else {
				w278 = -424.67404;
			}
		}
	}
	float w279;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w279 = -165.63208;
				} else {
					w279 = 65.76001;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[24]) {
					w279 = -120.131035;
				} else {
					w279 = -414.02292;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[17]) {
					w279 = -121.6597;
				} else {
					w279 = 56.672634;
				}
			} else {
				if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
					w279 = -1.8268644;
				} else {
					w279 = -105.96775;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[44]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[36]) {
					w279 = -39.45786;
				} else {
					w279 = 30.982935;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[28]) {
					w279 = 223.8816;
				} else {
					w279 = -17.292624;
				}
			}
		} else {
			if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[2]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
					w279 = 11.095162;
				} else {
					w279 = 142.2902;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[21]) {
					w279 = 76.002106;
				} else {
					w279 = 584.978;
				}
			}
		}
	}
	float w280;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[11]) {
					w280 = -240.09077;
				} else {
					w280 = 13.373295;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[40]) {
					w280 = -21.486937;
				} else {
					w280 = 434.0551;
				}
			}
		} else {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[2]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[25]) {
					w280 = 94.742294;
				} else {
					w280 = 3.8621757;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w280 = 96.717186;
				} else {
					w280 = 503.9393;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (MoSold != NULL && *MoSold < cond_MoSold[7]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w280 = -138.88722;
				} else {
					w280 = -35.107967;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[31]) {
					w280 = 194.24724;
				} else {
					w280 = 64.51291;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
				w280 = 496.70355;
			} else {
				w280 = 111.759056;
			}
		}
	}
	float w281;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w281 = -162.79158;
				} else {
					w281 = 63.99174;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[24]) {
					w281 = -118.78036;
				} else {
					w281 = -408.4779;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[17]) {
					w281 = -119.62796;
				} else {
					w281 = 56.11576;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[16]) {
					w281 = -16.961555;
				} else {
					w281 = 111.668594;
				}
			}
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[24]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
					w281 = 9.295811;
				} else {
					w281 = 158.71556;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[30]) {
					w281 = -31.826483;
				} else {
					w281 = -684.6263;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[26]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
					w281 = 27.068365;
				} else {
					w281 = 320.33112;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[1]) {
					w281 = 189.12718;
				} else {
					w281 = 698.8339;
				}
			}
		}
	}
	float w282;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[11]) {
					w282 = -236.21446;
				} else {
					w282 = 13.289857;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[40]) {
					w282 = -21.051523;
				} else {
					w282 = 428.53897;
				}
			}
		} else {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[2]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[25]) {
					w282 = 93.21384;
				} else {
					w282 = 3.4837482;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w282 = 95.922066;
				} else {
					w282 = 496.71368;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (MoSold != NULL && *MoSold < cond_MoSold[7]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w282 = -137.3308;
				} else {
					w282 = -34.914375;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[31]) {
					w282 = 191.27208;
				} else {
					w282 = 63.337814;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
				w282 = 487.62982;
			} else {
				w282 = 109.80156;
			}
		}
	}
	float w283;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[25]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[5]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
					w283 = -141.674;
				} else {
					w283 = 162.08244;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[14]) {
					w283 = -8.669637;
				} else {
					w283 = -194.92638;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[30]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w283 = -53.265;
				} else {
					w283 = 180.72214;
				}
			} else {
				w283 = 529.2837;
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[1]) {
					w283 = -7.481472;
				} else {
					w283 = 192.85747;
				}
			} else {
				w283 = 543.5478;
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[42]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[16]) {
					w283 = 39.34489;
				} else {
					w283 = -103.21805;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w283 = 235.51224;
				} else {
					w283 = -163.06818;
				}
			}
		}
	}
	float w284;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[11]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[13]) {
					w284 = -76.326805;
				} else {
					w284 = 5.3688364;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[17]) {
					w284 = 0.71151;
				} else {
					w284 = 233.64864;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[53]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[32]) {
					w284 = 76.27992;
				} else {
					w284 = -83.980545;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[22]) {
					w284 = 54.888046;
				} else {
					w284 = -493.08426;
				}
			}
		}
	} else {
		if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[15]) {
					w284 = -259.39694;
				} else {
					w284 = 3.8955226;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
					w284 = 152.40862;
				} else {
					w284 = 44.722652;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[5]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[18]) {
					w284 = -28.477968;
				} else {
					w284 = -373.47253;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[24]) {
					w284 = 3.4671187;
				} else {
					w284 = -144.0972;
				}
			}
		}
	}
	float w285;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[40]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[11]) {
					w285 = -209.51604;
				} else {
					w285 = 13.672747;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[40]) {
					w285 = -20.141266;
				} else {
					w285 = 420.2694;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[23]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[2]) {
					w285 = -5.914927;
				} else {
					w285 = -393.08734;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[48]) {
					w285 = 47.72456;
				} else {
					w285 = 203.4326;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (MoSold != NULL && *MoSold < cond_MoSold[7]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w285 = -135.53209;
				} else {
					w285 = -35.7307;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[11]) {
					w285 = 44.933464;
				} else {
					w285 = 161.7436;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
				w285 = 478.21518;
			} else {
				w285 = 107.559685;
			}
		}
	}
	float w286;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[41]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
					w286 = -66.05983;
				} else {
					w286 = 84.97815;
				}
			} else {
				w286 = 241.14368;
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[21]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[55]) {
					w286 = -20.15038;
				} else {
					w286 = 271.5431;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w286 = 133.31078;
				} else {
					w286 = -35.566635;
				}
			}
		}
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[44]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[36]) {
					w286 = -38.091705;
				} else {
					w286 = 29.52817;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[28]) {
					w286 = 216.82993;
				} else {
					w286 = -18.587545;
				}
			}
		} else {
			if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[2]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[13]) {
					w286 = -22.664534;
				} else {
					w286 = 114.78456;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[21]) {
					w286 = 77.01852;
				} else {
					w286 = 573.5144;
				}
			}
		}
	}
	float w287;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[11]) {
					w287 = -227.59404;
				} else {
					w287 = 13.670533;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[40]) {
					w287 = -20.082355;
				} else {
					w287 = 414.29144;
				}
			}
		} else {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[2]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[25]) {
					w287 = 90.52487;
				} else {
					w287 = 1.9228303;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w287 = 95.085236;
				} else {
					w287 = 484.01962;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (MoSold != NULL && *MoSold < cond_MoSold[7]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w287 = -134.15326;
				} else {
					w287 = -35.684296;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[31]) {
					w287 = 186.51836;
				} else {
					w287 = 60.802525;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
				w287 = 471.35492;
			} else {
				w287 = 105.59031;
			}
		}
	}
	float w288;
	if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[7]) {
					w288 = -33.29388;
				} else {
					w288 = 160.19926;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
					w288 = 10.514227;
				} else {
					w288 = 129.77328;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
				w288 = 596.2765;
			} else {
				w288 = -4.6949997;
			}
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[45]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
					w288 = 24.04162;
				} else {
					w288 = -536.3845;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w288 = 205.85194;
				} else {
					w288 = -178.37294;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
				w288 = 860.06555;
			} else {
				w288 = 137.73662;
			}
		}
	}
	float w289;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[46]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[37]) {
					w289 = -104.88032;
				} else {
					w289 = -13.866175;
				}
			} else {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[3]) {
					w289 = -211.82672;
				} else {
					w289 = 237.23367;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w289 = 15.652499;
			} else {
				w289 = 370.52402;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w289 = -20.189114;
				} else {
					w289 = 49.77811;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w289 = 589.56854;
				} else {
					w289 = -4.6598434;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[10]) {
					w289 = 57.134377;
				} else {
					w289 = 365.80768;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w289 = 853.61505;
				} else {
					w289 = 136.1871;
				}
			}
		}
	}
	float w290;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[25]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[5]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
					w290 = -136.7119;
				} else {
					w290 = 160.61942;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[14]) {
					w290 = -8.100063;
				} else {
					w290 = -192.65701;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[30]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w290 = -52.778435;
				} else {
					w290 = 176.00414;
				}
			} else {
				w290 = 515.08984;
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[19]) {
					w290 = 19.810648;
				} else {
					w290 = -112.71061;
				}
			} else {
				w290 = 522.236;
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[42]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[16]) {
					w290 = 38.847588;
				} else {
					w290 = -102.47475;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w290 = 225.6409;
				} else {
					w290 = -164.20921;
				}
			}
		}
	}
	float w291;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[11]) {
					w291 = -223.72368;
				} else {
					w291 = 13.09414;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[40]) {
					w291 = -19.52021;
				} else {
					w291 = 406.19684;
				}
			}
		} else {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[2]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[25]) {
					w291 = 89.195595;
				} else {
					w291 = 1.2544593;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w291 = 94.833984;
				} else {
					w291 = 469.76852;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (MoSold != NULL && *MoSold < cond_MoSold[7]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w291 = -131.57361;
				} else {
					w291 = -33.517735;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[31]) {
					w291 = 184.07164;
				} else {
					w291 = 59.836716;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
				w291 = 456.6764;
			} else {
				w291 = 100.32875;
			}
		}
	}
	float w292;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[15]) {
					w292 = -110.592094;
				} else {
					w292 = -24.606567;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
					w292 = -294.42874;
				} else {
					w292 = 111.51656;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w292 = 15.742148;
			} else {
				w292 = 365.9714;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w292 = -19.734798;
				} else {
					w292 = 48.965557;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w292 = 577.2008;
				} else {
					w292 = -4.782656;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[10]) {
					w292 = 55.711685;
				} else {
					w292 = 355.0109;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w292 = 847.42004;
				} else {
					w292 = 134.0891;
				}
			}
		}
	}
	float w293;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[25]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[5]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
					w293 = -133.87761;
				} else {
					w293 = 158.86176;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[14]) {
					w293 = -7.903752;
				} else {
					w293 = -190.03075;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[30]) {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[10]) {
					w293 = 161.82008;
				} else {
					w293 = -102.06129;
				}
			} else {
				w293 = 507.24326;
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[1]) {
					w293 = -7.21493;
				} else {
					w293 = 186.56422;
				}
			} else {
				w293 = 509.18524;
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[42]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[16]) {
					w293 = 38.438824;
				} else {
					w293 = -101.367874;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w293 = 220.69002;
				} else {
					w293 = -163.63953;
				}
			}
		}
	}
	float w294;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[11]) {
					w294 = -219.8116;
				} else {
					w294 = 12.808723;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[39]) {
					w294 = -47.85004;
				} else {
					w294 = 7.1916738;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[23]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[2]) {
					w294 = -6.5964737;
				} else {
					w294 = -383.67896;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[48]) {
					w294 = 44.71961;
				} else {
					w294 = 193.67638;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[27]) {
				w294 = 308.53506;
			} else {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[4]) {
					w294 = 91.4129;
				} else {
					w294 = -86.79643;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
				w294 = 444.2879;
			} else {
				w294 = 95.49;
			}
		}
	}
	float w295;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[33]) {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[37]) {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[3]) {
					w295 = -180.43164;
				} else {
					w295 = -77.119606;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w295 = -219.48566;
				} else {
					w295 = -34.608307;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[67]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[21]) {
					w295 = -38.821346;
				} else {
					w295 = -153.21869;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[27]) {
					w295 = 77.849266;
				} else {
					w295 = -1.9216024;
				}
			}
		}
	} else {
		if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[2]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w295 = -22.608524;
				} else {
					w295 = 52.937008;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[34]) {
					w295 = 46.104935;
				} else {
					w295 = 241.04892;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[20]) {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[11]) {
					w295 = -253.58015;
				} else {
					w295 = 14.5676365;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[33]) {
					w295 = 45.269318;
				} else {
					w295 = -91.319595;
				}
			}
		}
	}
	float w296;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[15]) {
					w296 = -107.492096;
				} else {
					w296 = -23.82641;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
					w296 = 197.09906;
				} else {
					w296 = -271.8635;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w296 = 15.799101;
			} else {
				w296 = 360.32596;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w296 = -19.248163;
				} else {
					w296 = 48.03253;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w296 = 562.59503;
				} else {
					w296 = -7.953281;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[10]) {
					w296 = 53.759357;
				} else {
					w296 = 343.23877;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w296 = 840.67285;
				} else {
					w296 = 131.80617;
				}
			}
		}
	}
	float w297;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[11]) {
					w297 = -215.12497;
				} else {
					w297 = 12.076431;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[40]) {
					w297 = -18.622385;
				} else {
					w297 = 397.52295;
				}
			}
		} else {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[2]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[25]) {
					w297 = 87.092255;
				} else {
					w297 = -0.16481015;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w297 = 93.94008;
				} else {
					w297 = 453.70505;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[24]) {
					w297 = 64.84225;
				} else {
					w297 = -73.380615;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
					w297 = 26.89749;
				} else {
					w297 = 276.6665;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[23]) {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w297 = 225.79643;
				} else {
					w297 = -82.22293;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
					w297 = 403.2528;
				} else {
					w297 = 114.325195;
				}
			}
		}
	}
	float w298;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[33]) {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[2]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[31]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[14]) {
					w298 = -94.631584;
				} else {
					w298 = -8.256787;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[20]) {
					w298 = 63.084396;
				} else {
					w298 = -43.45877;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[67]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[21]) {
					w298 = -38.607273;
				} else {
					w298 = -150.4765;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[27]) {
					w298 = 76.42769;
				} else {
					w298 = -1.8304003;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
			if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[7]) {
					w298 = -245.7861;
				} else {
					w298 = 1.5969375;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[16]) {
					w298 = -371.22153;
				} else {
					w298 = -25.996326;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[29]) {
					w298 = -31.86292;
				} else {
					w298 = 44.657166;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
					w298 = 58.878296;
				} else {
					w298 = 320.47888;
				}
			}
		}
	}
	float w299;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[40]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
					w299 = -158.49881;
				} else {
					w299 = -18.268747;
				}
			} else {
				w299 = 392.83536;
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[23]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[2]) {
					w299 = -7.1795545;
				} else {
					w299 = -379.15494;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[48]) {
					w299 = 42.640118;
				} else {
					w299 = 187.62143;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[24]) {
					w299 = 63.96895;
				} else {
					w299 = -72.73392;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
					w299 = 26.517178;
				} else {
					w299 = 272.28473;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[23]) {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w299 = 222.76054;
				} else {
					w299 = -81.17941;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
					w299 = 397.40814;
				} else {
					w299 = 112.5368;
				}
			}
		}
	}
	float w300;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[41]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
					w300 = -61.388508;
				} else {
					w300 = 80.751625;
				}
			} else {
				w300 = 228.17195;
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[21]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[55]) {
					w300 = -18.4403;
				} else {
					w300 = 255.08566;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w300 = 129.99893;
				} else {
					w300 = -38.025402;
				}
			}
		}
	} else {
		if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[16]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[42]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[34]) {
					w300 = -1.6961014;
				} else {
					w300 = 317.2597;
				}
			} else {
				w300 = 440.80093;
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[31]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[46]) {
					w300 = -355.66217;
				} else {
					w300 = 33.126133;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[15]) {
					w300 = 400.12137;
				} else {
					w300 = 77.505066;
				}
			}
		}
	}
	float w301;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[46]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[37]) {
					w301 = -97.59769;
				} else {
					w301 = -10.571219;
				}
			} else {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[3]) {
					w301 = -204.12701;
				} else {
					w301 = 233.46082;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w301 = 15.635156;
			} else {
				w301 = 355.28174;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w301 = -18.763857;
				} else {
					w301 = 46.78453;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w301 = 551.11053;
				} else {
					w301 = -10.215938;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[10]) {
					w301 = 52.172043;
				} else {
					w301 = 329.84073;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w301 = 832.25366;
				} else {
					w301 = 126.55798;
				}
			}
		}
	}
	float w302;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[38]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[22]) {
					w302 = -42.467026;
				} else {
					w302 = -303.45648;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
					w302 = -22.76757;
				} else {
					w302 = 71.28731;
				}
			}
		} else {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[2]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[25]) {
					w302 = 84.83636;
				} else {
					w302 = -1.4720432;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w302 = 92.86968;
				} else {
					w302 = 443.48935;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[24]) {
					w302 = 63.81774;
				} else {
					w302 = -71.28858;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
					w302 = 25.775986;
				} else {
					w302 = 267.46988;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[23]) {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w302 = 219.6225;
				} else {
					w302 = -80.30499;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
					w302 = 388.74048;
				} else {
					w302 = 109.59961;
				}
			}
		}
	}
	float w303;
	if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w303 = -143.9838;
				} else {
					w303 = 68.229645;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[24]) {
					w303 = -107.53132;
				} else {
					w303 = -391.76077;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w303 = -156.04944;
				} else {
					w303 = -40.92252;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[30]) {
					w303 = -16.399572;
				} else {
					w303 = 115.55581;
				}
			}
		}
	} else {
		if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[16]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[42]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[34]) {
					w303 = -1.7391819;
				} else {
					w303 = 312.5443;
				}
			} else {
				w303 = 432.46246;
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[31]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[46]) {
					w303 = -351.52045;
				} else {
					w303 = 32.33082;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[15]) {
					w303 = 393.83823;
				} else {
					w303 = 75.857346;
				}
			}
		}
	}
	float w304;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[38]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[22]) {
					w304 = -41.6801;
				} else {
					w304 = -299.51282;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[8]) {
					w304 = -5.3678517;
				} else {
					w304 = 194.40186;
				}
			}
		} else {
			if (YrSold != NULL && *YrSold < cond_YrSold[1]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[26]) {
					w304 = 62.666504;
				} else {
					w304 = 425.2128;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[28]) {
					w304 = 58.53161;
				} else {
					w304 = -83.09475;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[24]) {
					w304 = 62.89466;
				} else {
					w304 = -70.16854;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
					w304 = 25.50038;
				} else {
					w304 = 263.71988;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[23]) {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w304 = 216.65485;
				} else {
					w304 = -79.66726;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
					w304 = 382.54218;
				} else {
					w304 = 107.80441;
				}
			}
		}
	}
	float w305;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[15]) {
					w305 = -101.60229;
				} else {
					w305 = -21.372795;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
					w305 = 188.75471;
				} else {
					w305 = -267.0496;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w305 = 15.036562;
			} else {
				w305 = 350.30566;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w305 = -27.53931;
				} else {
					w305 = 28.243866;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w305 = 540.6861;
				} else {
					w305 = -11.1675;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[45]) {
					w305 = 23.181936;
				} else {
					w305 = 137.64319;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w305 = 824.73773;
				} else {
					w305 = 127.46402;
				}
			}
		}
	}
	float w306;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[42]) {
			if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[30]) {
					w306 = -70.92931;
				} else {
					w306 = 72.80673;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[31]) {
					w306 = -109.82054;
				} else {
					w306 = -319.32526;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[16]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[31]) {
					w306 = -12.863253;
				} else {
					w306 = 264.82675;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[5]) {
					w306 = 315.32248;
				} else {
					w306 = 42.82515;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[24]) {
					w306 = 62.084038;
				} else {
					w306 = -69.21813;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
					w306 = 24.923641;
				} else {
					w306 = 259.7385;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[23]) {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w306 = 214.16447;
				} else {
					w306 = -78.32726;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
					w306 = 376.89838;
				} else {
					w306 = 106.71105;
				}
			}
		}
	}
	float w307;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[13]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[47]) {
					w307 = -49.607723;
				} else {
					w307 = -353.275;
				}
			} else {
				if (YrSold != NULL && *YrSold < cond_YrSold[1]) {
					w307 = 74.36081;
				} else {
					w307 = -45.044964;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[10]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
					w307 = -7.144633;
				} else {
					w307 = 298.93094;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[29]) {
					w307 = 59.627327;
				} else {
					w307 = 478.93466;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[15]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[16]) {
					w307 = 142.58084;
				} else {
					w307 = -86.059494;
				}
			} else {
				w307 = 428.99646;
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w307 = 149.7443;
			} else {
				w307 = -427.4599;
			}
		}
	}
	float w308;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[25]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			if (BsmtFullBath != NULL && *BsmtFullBath < cond_BsmtFullBath[0]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[12]) {
					w308 = -67.371994;
				} else {
					w308 = 220.74672;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[32]) {
					w308 = -131.70636;
				} else {
					w308 = -290.57672;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[34]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[14]) {
					w308 = -91.69612;
				} else {
					w308 = 3.2161927;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[21]) {
					w308 = 37.364338;
				} else {
					w308 = 289.05893;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[30]) {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[5]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[40]) {
					w308 = 14.567663;
				} else {
					w308 = 348.23602;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[6]) {
					w308 = 284.71756;
				} else {
					w308 = -37.69552;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[15]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[34]) {
					w308 = -793.6224;
				} else {
					w308 = -199.9139;
				}
			} else {
				w308 = 415.4042;
			}
		}
	}
	float w309;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[42]) {
			if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[30]) {
					w309 = -68.921455;
				} else {
					w309 = 72.712036;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[31]) {
					w309 = -106.55169;
				} else {
					w309 = -313.92282;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[16]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[31]) {
					w309 = -12.548612;
				} else {
					w309 = 254.85234;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[5]) {
					w309 = 310.9062;
				} else {
					w309 = 41.363453;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[24]) {
					w309 = 61.615692;
				} else {
					w309 = -68.251;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
					w309 = 24.83584;
				} else {
					w309 = 255.83376;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[23]) {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w309 = 211.08508;
				} else {
					w309 = -77.985855;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
					w309 = 370.2851;
				} else {
					w309 = 104.15742;
				}
			}
		}
	}
	float w310;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[15]) {
					w310 = -98.66847;
				} else {
					w310 = -20.71701;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
					w310 = 184.17914;
				} else {
					w310 = -263.14716;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w310 = 15.143788;
			} else {
				w310 = 346.13336;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w310 = -27.147879;
				} else {
					w310 = 27.942451;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w310 = 529.689;
				} else {
					w310 = -14.297343;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[48]) {
					w310 = 30.029501;
				} else {
					w310 = 150.86415;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w310 = 818.7724;
				} else {
					w310 = 125.50834;
				}
			}
		}
	}
	float w311;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[40]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
					w311 = -18.786657;
				} else {
					w311 = -266.29974;
				}
			} else {
				w311 = 372.54797;
			}
		} else {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[2]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[25]) {
					w311 = 81.79602;
				} else {
					w311 = -3.1683648;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w311 = 91.51465;
				} else {
					w311 = 431.8139;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[24]) {
					w311 = 60.821495;
				} else {
					w311 = -67.32876;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
					w311 = 24.268543;
				} else {
					w311 = 251.96416;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[23]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w311 = -137.13281;
				} else {
					w311 = 172.1173;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
					w311 = 364.72443;
				} else {
					w311 = 103.07671;
				}
			}
		}
	}
	float w312;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[25]) {
		if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[2]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
					w312 = -120.702614;
				} else {
					w312 = 158.52344;
				}
			} else {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[5]) {
					w312 = -12.723987;
				} else {
					w312 = 234.0871;
				}
			}
		} else {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[29]) {
					w312 = 60.211563;
				} else {
					w312 = 2.6879296;
				}
			} else {
				w312 = 369.26984;
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[1]) {
					w312 = -8.476783;
				} else {
					w312 = 178.82101;
				}
			} else {
				w312 = 468.05283;
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[42]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[16]) {
					w312 = 38.98866;
				} else {
					w312 = -101.995514;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w312 = 201.66176;
				} else {
					w312 = -176.80807;
				}
			}
		}
	}
	float w313;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[46]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[37]) {
					w313 = -91.27558;
				} else {
					w313 = -7.7138467;
				}
			} else {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[3]) {
					w313 = -197.27422;
				} else {
					w313 = 231.52805;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w313 = 15.266484;
			} else {
				w313 = 342.1263;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w313 = -17.810995;
				} else {
					w313 = 44.692207;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w313 = 518.831;
				} else {
					w313 = -14.102344;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[49]) {
					w313 = 66.73652;
				} else {
					w313 = -290.61935;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w313 = 812.8678;
				} else {
					w313 = 123.64675;
				}
			}
		}
	}
	float w314;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[42]) {
			if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[30]) {
					w314 = -67.1824;
				} else {
					w314 = 71.88909;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[31]) {
					w314 = -104.51645;
				} else {
					w314 = -308.74164;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[16]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[31]) {
					w314 = -12.15191;
				} else {
					w314 = 249.53815;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[5]) {
					w314 = 305.91284;
				} else {
					w314 = 40.17462;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[24]) {
					w314 = 60.73197;
				} else {
					w314 = -65.86367;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
					w314 = 23.665283;
				} else {
					w314 = 247.78262;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[23]) {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w314 = 206.5358;
				} else {
					w314 = -76.749725;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
					w314 = 358.26843;
				} else {
					w314 = 101.10785;
				}
			}
		}
	}
	float w315;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[13]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[47]) {
					w315 = -47.464943;
				} else {
					w315 = -349.5723;
				}
			} else {
				if (YrSold != NULL && *YrSold < cond_YrSold[1]) {
					w315 = 72.44131;
				} else {
					w315 = -44.4323;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[10]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
					w315 = -9.701096;
				} else {
					w315 = 158.13374;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[5]) {
					w315 = 91.22101;
				} else {
					w315 = -129.6054;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[15]) {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[0]) {
					w315 = 97.1517;
				} else {
					w315 = 379.49356;
				}
			} else {
				w315 = 411.51584;
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w315 = 140.73235;
			} else {
				w315 = -420.09094;
			}
		}
	}
	float w316;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[42]) {
			if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[30]) {
					w316 = -65.86883;
				} else {
					w316 = 71.36208;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[31]) {
					w316 = -101.992004;
				} else {
					w316 = -303.60397;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[31]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w316 = -38.124367;
				} else {
					w316 = 36.15729;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[48]) {
					w316 = 14.641801;
				} else {
					w316 = 121.465576;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[24]) {
					w316 = 60.0738;
				} else {
					w316 = -65.07513;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
					w316 = 23.654482;
				} else {
					w316 = 244.84904;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[23]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[27]) {
					w316 = 283.73688;
				} else {
					w316 = -18.269348;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
					w316 = 352.66718;
				} else {
					w316 = 99.46441;
				}
			}
		}
	}
	float w317;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[15]) {
					w317 = -94.45667;
				} else {
					w317 = -19.169563;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
					w317 = 178.02422;
				} else {
					w317 = -257.32166;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w317 = 15.206133;
			} else {
				w317 = 336.89893;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w317 = -26.288544;
				} else {
					w317 = 27.278902;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w317 = 511.12463;
				} else {
					w317 = -15.892968;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[49]) {
					w317 = 64.859695;
				} else {
					w317 = -287.07077;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w317 = 807.221;
				} else {
					w317 = 122.11764;
				}
			}
		}
	}
	float w318;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
					w318 = -21.329401;
				} else {
					w318 = 153.36086;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[33]) {
					w318 = -34.694942;
				} else {
					w318 = -783.75;
				}
			}
		} else {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[2]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[25]) {
					w318 = 79.87688;
				} else {
					w318 = -4.150744;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w318 = 91.302536;
				} else {
					w318 = 417.92075;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[24]) {
					w318 = 59.29753;
				} else {
					w318 = -64.200386;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
					w318 = 23.10626;
				} else {
					w318 = 241.13824;
				}
			}
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[32]) {
					w318 = -187.4553;
				} else {
					w318 = 141.33296;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[18]) {
					w318 = -91.50281;
				} else {
					w318 = 282.7869;
				}
			}
		}
	}
	float w319;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[25]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			if (BsmtFullBath != NULL && *BsmtFullBath < cond_BsmtFullBath[0]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[12]) {
					w319 = -61.777725;
				} else {
					w319 = 219.0187;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[32]) {
					w319 = -125.60918;
				} else {
					w319 = -280.78668;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[34]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[14]) {
					w319 = -86.28326;
				} else {
					w319 = 3.0552485;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[21]) {
					w319 = 29.849258;
				} else {
					w319 = 273.89484;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[30]) {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[5]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[40]) {
					w319 = 12.360953;
				} else {
					w319 = 326.4333;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[6]) {
					w319 = 274.53036;
				} else {
					w319 = -42.230457;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[15]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[34]) {
					w319 = -775.9125;
				} else {
					w319 = -193.65094;
				}
			} else {
				w319 = 405.23438;
			}
		}
	}
	float w320;
	if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
		if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[33]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[13]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[68]) {
					w320 = -43.61273;
				} else {
					w320 = -476.2429;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[12]) {
					w320 = -26.525972;
				} else {
					w320 = 82.86148;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[22]) {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[5]) {
					w320 = 53.07394;
				} else {
					w320 = -488.95428;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[35]) {
					w320 = 23.388575;
				} else {
					w320 = 554.3855;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[35]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[14]) {
				if (MiscVal != NULL && *MiscVal < cond_MiscVal[0]) {
					w320 = -275.015;
				} else {
					w320 = 5.146992;
				}
			} else {
				w320 = 93.738106;
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[2]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[57]) {
					w320 = -13.048988;
				} else {
					w320 = 70.80797;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[22]) {
					w320 = 291.9447;
				} else {
					w320 = 54.83524;
				}
			}
		}
	}
	float w321;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
					w321 = -21.36337;
				} else {
					w321 = 150.66269;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[33]) {
					w321 = -74.09772;
				} else {
					w321 = -763.3909;
				}
			}
		} else {
			if (YrSold != NULL && *YrSold < cond_YrSold[1]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[26]) {
					w321 = 58.10239;
				} else {
					w321 = 405.84607;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[28]) {
					w321 = 53.749973;
				} else {
					w321 = -83.98572;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[43]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
					w321 = 46.99532;
				} else {
					w321 = 216.99153;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[31]) {
					w321 = -276.4561;
				} else {
					w321 = -1.1651367;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[31]) {
					w321 = -76.35796;
				} else {
					w321 = 158.77177;
				}
			} else {
				w321 = 342.05978;
			}
		}
	}
	float w322;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
					w322 = -108.748695;
				} else {
					w322 = -28.291996;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
					w322 = 173.45226;
				} else {
					w322 = -253.59671;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w322 = 15.487148;
			} else {
				w322 = 332.6943;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w322 = -25.784561;
				} else {
					w322 = 26.710537;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w322 = 498.93878;
				} else {
					w322 = -18.64875;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[49]) {
					w322 = 62.975983;
				} else {
					w322 = -284.17194;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w322 = 801.56226;
				} else {
					w322 = 121.58121;
				}
			}
		}
	}
	float w323;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[7]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
					w323 = -299.57422;
				} else {
					w323 = -125.00166;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w323 = 125.51116;
				} else {
					w323 = 11.824922;
				}
			}
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[8]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[25]) {
					w323 = -98.5524;
				} else {
					w323 = -23.141214;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[59]) {
					w323 = -32.168247;
				} else {
					w323 = 90.019005;
				}
			}
		}
	} else {
		if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[58]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[5]) {
					w323 = -39.245934;
				} else {
					w323 = -277.36777;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[14]) {
					w323 = 13.945915;
				} else {
					w323 = 73.96734;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[20]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w323 = -127.41184;
				} else {
					w323 = -342.59937;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
					w323 = -70.34582;
				} else {
					w323 = 65.18587;
				}
			}
		}
	}
	float w324;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (PoolArea != NULL && *PoolArea < cond_PoolArea[3]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[42]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w324 = -33.78004;
				} else {
					w324 = -184.88437;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[16]) {
					w324 = -9.741985;
				} else {
					w324 = 49.038868;
				}
			}
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				w324 = 89.95195;
			} else {
				w324 = 407.102;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[24]) {
					w324 = 58.16377;
				} else {
					w324 = -64.33696;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
					w324 = 21.79494;
				} else {
					w324 = 234.99019;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[23]) {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w324 = 196.25346;
				} else {
					w324 = -76.238205;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
					w324 = 338.4927;
				} else {
					w324 = 93.54117;
				}
			}
		}
	}
	float w325;
	if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
		if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[33]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[39]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[13]) {
					w325 = -54.023884;
				} else {
					w325 = 1.26212;
				}
			} else {
				w325 = 181.16226;
			}
		} else {
			if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[5]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[22]) {
					w325 = 52.30563;
				} else {
					w325 = 350.45584;
				}
			} else {
				w325 = -485.40598;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[35]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[14]) {
				if (MiscVal != NULL && *MiscVal < cond_MiscVal[0]) {
					w325 = -267.9322;
				} else {
					w325 = 5.21707;
				}
			} else {
				w325 = 93.22576;
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[2]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[57]) {
					w325 = -12.728013;
				} else {
					w325 = 68.96498;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[23]) {
					w325 = 265.58646;
				} else {
					w325 = 50.198723;
				}
			}
		}
	}
	float w326;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[25]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[34]) {
			if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w326 = -161.298;
				} else {
					w326 = -9.951056;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
					w326 = 51.357388;
				} else {
					w326 = 273.91202;
				}
			}
		} else {
			if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[1]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[32]) {
					w326 = -8.537695;
				} else {
					w326 = 296.48187;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[36]) {
					w326 = 28.753828;
				} else {
					w326 = -135.21945;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[20]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[51]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[60]) {
					w326 = 80.34737;
				} else {
					w326 = -99.57056;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[34]) {
					w326 = 226.01448;
				} else {
					w326 = 501.6167;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[43]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[61]) {
					w326 = -13.848453;
				} else {
					w326 = 202.54872;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w326 = -333.70828;
				} else {
					w326 = -85.09078;
				}
			}
		}
	}
	float w327;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[13]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[47]) {
					w327 = -43.653923;
				} else {
					w327 = -342.14624;
				}
			} else {
				if (YrSold != NULL && *YrSold < cond_YrSold[1]) {
					w327 = 68.86327;
				} else {
					w327 = -43.0874;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[12]) {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w327 = 20.34161;
				} else {
					w327 = -45.260986;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[5]) {
					w327 = 86.32651;
				} else {
					w327 = -128.73813;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[15]) {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[0]) {
					w327 = 88.8652;
				} else {
					w327 = 368.23312;
				}
			} else {
				w327 = 393.27197;
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w327 = 130.24289;
			} else {
				w327 = -400.74234;
			}
		}
	}
	float w328;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
		if (PoolArea != NULL && *PoolArea < cond_PoolArea[3]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w328 = -164.9068;
				} else {
					w328 = -21.496632;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[36]) {
					w328 = -18.648344;
				} else {
					w328 = 40.683743;
				}
			}
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				w328 = 89.29488;
			} else {
				w328 = 398.60266;
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[43]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
					w328 = 44.777622;
				} else {
					w328 = 209.92038;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[31]) {
					w328 = -272.9742;
				} else {
					w328 = -0.25289062;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[31]) {
					w328 = -74.58609;
				} else {
					w328 = 150.26065;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[16]) {
					w328 = 398.1716;
				} else {
					w328 = 179.39473;
				}
			}
		}
	}
	float w329;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
					w329 = -104.98122;
				} else {
					w329 = -26.47798;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
					w329 = 167.33672;
				} else {
					w329 = -249.65475;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w329 = 15.051797;
			} else {
				w329 = 327.18915;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w329 = -25.276114;
				} else {
					w329 = 26.33381;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w329 = 485.96588;
				} else {
					w329 = -21.829687;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[49]) {
					w329 = 59.815613;
				} else {
					w329 = -278.76813;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w329 = 794.78107;
				} else {
					w329 = 119.85603;
				}
			}
		}
	}
	float w330;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[25]) {
		if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[2]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[5]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[11]) {
					w330 = -15.146441;
				} else {
					w330 = -217.7674;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w330 = 82.24439;
				} else {
					w330 = 368.18652;
				}
			}
		} else {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[29]) {
					w330 = 59.95781;
				} else {
					w330 = 0.86859375;
				}
			} else {
				w330 = 353.62656;
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[1]) {
					w330 = -9.338788;
				} else {
					w330 = 172.25745;
				}
			} else {
				w330 = 427.61188;
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[52]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[17]) {
					w330 = 50.9776;
				} else {
					w330 = -205.86102;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w330 = 240.504;
				} else {
					w330 = -220.07254;
				}
			}
		}
	}
	float w331;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[33]) {
			if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
					w331 = -49.781136;
				} else {
					w331 = 118.22644;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[1]) {
					w331 = -64.40286;
				} else {
					w331 = -275.68066;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[44]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[37]) {
					w331 = -60.114258;
				} else {
					w331 = 376.13327;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[39]) {
					w331 = -28.27675;
				} else {
					w331 = 18.807;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
					w331 = 44.193237;
				} else {
					w331 = 274.2665;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w331 = 26.476358;
				} else {
					w331 = -247.76202;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[31]) {
					w331 = -73.72336;
				} else {
					w331 = 147.27864;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[16]) {
					w331 = 391.39786;
				} else {
					w331 = 175.62117;
				}
			}
		}
	}
	float w332;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[7]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
					w332 = -291.78943;
				} else {
					w332 = -120.3551;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w332 = 124.47792;
				} else {
					w332 = 12.884531;
				}
			}
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[8]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[25]) {
					w332 = -94.09847;
				} else {
					w332 = -22.126234;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[59]) {
					w332 = -30.64798;
				} else {
					w332 = 89.46887;
				}
			}
		}
	} else {
		if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[58]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[5]) {
					w332 = -37.31352;
				} else {
					w332 = -271.00958;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[14]) {
					w332 = 13.371794;
				} else {
					w332 = 70.13979;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[20]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w332 = -123.48359;
				} else {
					w332 = -332.67096;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
					w332 = -67.386604;
				} else {
					w332 = 65.75749;
				}
			}
		}
	}
	float w333;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[39]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[13]) {
					w333 = -51.07083;
				} else {
					w333 = 10.056164;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[33]) {
					w333 = -102.93972;
				} else {
					w333 = 19.76681;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
					w333 = 66.74706;
				} else {
					w333 = -106.23006;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w333 = 115.71342;
				} else {
					w333 = 319.58575;
				}
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
			w333 = 88.29984;
		} else {
			w333 = 388.47733;
		}
	}
	float w334;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[8]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
					w334 = -108.71542;
				} else {
					w334 = -12.352575;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[53]) {
					w334 = -87.586426;
				} else {
					w334 = -355.45493;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[20]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w334 = -144.01204;
				} else {
					w334 = 3.0818894;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[38]) {
					w334 = 206.37743;
				} else {
					w334 = 21.554089;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[15]) {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[0]) {
					w334 = 84.76454;
				} else {
					w334 = 360.94278;
				}
			} else {
				w334 = 382.97202;
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w334 = 125.89312;
			} else {
				w334 = -396.34982;
			}
		}
	}
	float w335;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[20]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w335 = -157.94823;
				} else {
					w335 = -20.476662;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[36]) {
					w335 = -18.278454;
				} else {
					w335 = 39.128513;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[43]) {
					w335 = 63.20509;
				} else {
					w335 = -131.26903;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w335 = 113.384926;
				} else {
					w335 = 314.39084;
				}
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
			w335 = 87.61453;
		} else {
			w335 = 384.00287;
		}
	}
	float w336;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[7]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
					w336 = -285.5639;
				} else {
					w336 = -117.27643;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w336 = 123.162025;
				} else {
					w336 = 13.284961;
				}
			}
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[8]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[25]) {
					w336 = -91.16061;
				} else {
					w336 = -21.819363;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[59]) {
					w336 = -30.166359;
				} else {
					w336 = 88.04932;
				}
			}
		}
	} else {
		if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[58]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[5]) {
					w336 = -35.72095;
				} else {
					w336 = -265.85617;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
					w336 = 49.24144;
				} else {
					w336 = 4.4902487;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[20]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w336 = -133.22052;
				} else {
					w336 = -372.01276;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
					w336 = -65.61242;
				} else {
					w336 = 65.18009;
				}
			}
		}
	}
	float w337;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[39]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[22]) {
					w337 = -36.56781;
				} else {
					w337 = 77.73184;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[35]) {
					w337 = -180.12312;
				} else {
					w337 = 16.410522;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[15]) {
					w337 = 101.79334;
				} else {
					w337 = 377.94162;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
					w337 = 124.28601;
				} else {
					w337 = -392.75928;
				}
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
			w337 = 86.5882;
		} else {
			w337 = 379.15118;
		}
	}
	float w338;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[25]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[34]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[24]) {
					w338 = -47.3062;
				} else {
					w338 = 8.70082;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[25]) {
					w338 = 53.893726;
				} else {
					w338 = -56.46274;
				}
			}
		} else {
			if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[1]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[32]) {
					w338 = -10.367109;
				} else {
					w338 = 288.24295;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[36]) {
					w338 = 27.252773;
				} else {
					w338 = -131.95758;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[30]) {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[5]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[40]) {
					w338 = 7.50534;
				} else {
					w338 = 300.88477;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[6]) {
					w338 = 258.73895;
				} else {
					w338 = -49.82809;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[15]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[34]) {
					w338 = -751.32355;
				} else {
					w338 = -188.95062;
				}
			} else {
				w338 = 388.64874;
			}
		}
	}
	float w339;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[42]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w339 = -28.70717;
				} else {
					w339 = -173.12157;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[16]) {
					w339 = -9.021932;
				} else {
					w339 = 45.02454;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w339 = -5.1215887;
				} else {
					w339 = 121.91015;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w339 = 10.184899;
				} else {
					w339 = 230.23474;
				}
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
			w339 = 86.293594;
		} else {
			w339 = 373.73285;
		}
	}
	float w340;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[25]) {
		if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[2]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[5]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[11]) {
					w340 = -14.334132;
				} else {
					w340 = -216.66595;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w340 = 79.00964;
				} else {
					w340 = 360.01147;
				}
			}
		} else {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[29]) {
					w340 = 58.92992;
				} else {
					w340 = -0.6730078;
				}
			} else {
				w340 = 344.89038;
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
			if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[1]) {
					w340 = -9.732832;
				} else {
					w340 = 169.24074;
				}
			} else {
				w340 = 405.82983;
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[52]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[17]) {
					w340 = 48.681854;
				} else {
					w340 = -204.59818;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w340 = 231.2507;
				} else {
					w340 = -217.42328;
				}
			}
		}
	}
	float w341;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[19]) {
					w341 = -57.836716;
				} else {
					w341 = 48.603825;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
					w341 = 161.1096;
				} else {
					w341 = -243.28984;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w341 = 14.079609;
			} else {
				w341 = 320.2085;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[41]) {
					w341 = -26.820543;
				} else {
					w341 = 270.22897;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
					w341 = 15.158579;
				} else {
					w341 = 127.67909;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w341 = 59.56174;
				} else {
					w341 = -151.64401;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w341 = 787.4196;
				} else {
					w341 = 118.363884;
				}
			}
		}
	}
	float w342;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
		if (PoolArea != NULL && *PoolArea < cond_PoolArea[3]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[42]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w342 = -28.01368;
				} else {
					w342 = -170.31995;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[16]) {
					w342 = -8.819347;
				} else {
					w342 = 44.09378;
				}
			}
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				w342 = 85.64015;
			} else {
				w342 = 365.41125;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[24]) {
					w342 = 55.16843;
				} else {
					w342 = -67.92346;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[23]) {
					w342 = 15.84876;
				} else {
					w342 = 222.09027;
				}
			}
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[32]) {
					w342 = -179.89499;
				} else {
					w342 = 120.860954;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[18]) {
					w342 = -91.66629;
				} else {
					w342 = 251.98427;
				}
			}
		}
	}
	float w343;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[7]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
					w343 = -279.8929;
				} else {
					w343 = -113.613976;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w343 = 121.72355;
				} else {
					w343 = 14.010761;
				}
			}
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[8]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[33]) {
					w343 = -30.989319;
				} else {
					w343 = -278.61853;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[59]) {
					w343 = -28.74376;
				} else {
					w343 = 86.98661;
				}
			}
		}
	} else {
		if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
			if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[53]) {
					w343 = 17.024046;
				} else {
					w343 = 154.70961;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[44]) {
					w343 = -75.63582;
				} else {
					w343 = -205.53041;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[20]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w343 = -116.90574;
				} else {
					w343 = -320.90683;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
					w343 = -63.169636;
				} else {
					w343 = 65.60251;
				}
			}
		}
	}
	float w344;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[13]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[47]) {
					w344 = -38.87026;
				} else {
					w344 = -336.18875;
				}
			} else {
				if (YrSold != NULL && *YrSold < cond_YrSold[1]) {
					w344 = 66.05884;
				} else {
					w344 = -41.54383;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[34]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[24]) {
					w344 = -184.82425;
				} else {
					w344 = 15.204922;
				}
			} else {
				w344 = 479.13483;
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[8]) {
					w344 = 350.13068;
				} else {
					w344 = 69.726746;
				}
			} else {
				if (BsmtHalfBath != NULL && *BsmtHalfBath < cond_BsmtHalfBath[0]) {
					w344 = 16.687021;
				} else {
					w344 = 394.24875;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w344 = 119.23828;
			} else {
				w344 = -387.19266;
			}
		}
	}
	float w345;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[39]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[13]) {
					w345 = -47.369793;
				} else {
					w345 = 9.448308;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[33]) {
					w345 = -97.03436;
				} else {
					w345 = 18.31149;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
					w345 = 62.794556;
				} else {
					w345 = -104.63715;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w345 = 105.97277;
				} else {
					w345 = 301.41687;
				}
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
			w345 = 84.75609;
		} else {
			w345 = 359.96848;
		}
	}
	float w346;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[25]) {
		if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[2]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[5]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[11]) {
					w346 = -13.843288;
				} else {
					w346 = -214.1325;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w346 = 76.107864;
				} else {
					w346 = 353.56436;
				}
			}
		} else {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[29]) {
					w346 = 58.327263;
				} else {
					w346 = -1.0946484;
				}
			} else {
				w346 = 338.64725;
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[19]) {
				if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
					w346 = 14.3767;
				} else {
					w346 = 391.82602;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[34]) {
					w346 = -59.52855;
				} else {
					w346 = -241.27257;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[52]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[17]) {
					w346 = 47.22372;
				} else {
					w346 = -202.66124;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w346 = 224.92381;
				} else {
					w346 = -214.07866;
				}
			}
		}
	}
	float w347;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
					w347 = -97.13368;
				} else {
					w347 = -22.011795;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
					w347 = 156.86694;
				} else {
					w347 = -239.33946;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w347 = 13.764843;
			} else {
				w347 = 314.6592;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[41]) {
					w347 = -26.366411;
				} else {
					w347 = 263.31152;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
					w347 = 15.220247;
				} else {
					w347 = 124.38966;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w347 = 57.25363;
				} else {
					w347 = -149.74362;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w347 = 781.30475;
				} else {
					w347 = 116.833534;
				}
			}
		}
	}
	float w348;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[7]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
					w348 = -274.79504;
				} else {
					w348 = -110.57866;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w348 = 120.5541;
				} else {
					w348 = 14.542148;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[20]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[8]) {
					w348 = -29.421474;
				} else {
					w348 = 28.469898;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[39]) {
					w348 = -119.12409;
				} else {
					w348 = -337.93716;
				}
			}
		}
	} else {
		if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
			if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[26]) {
					w348 = 90.3844;
				} else {
					w348 = 13.050711;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[44]) {
					w348 = -72.931244;
				} else {
					w348 = -201.09525;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[20]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w348 = -125.33729;
				} else {
					w348 = -360.3922;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
					w348 = -61.436638;
				} else {
					w348 = 66.348145;
				}
			}
		}
	}
	float w349;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[39]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[13]) {
					w349 = -46.421223;
				} else {
					w349 = 9.055669;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[33]) {
					w349 = -95.10974;
				} else {
					w349 = 17.980043;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
					w349 = 61.444622;
				} else {
					w349 = -102.22271;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w349 = 103.76027;
				} else {
					w349 = 295.22626;
				}
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
			w349 = 84.01231;
		} else {
			w349 = 351.72598;
		}
	}
	float w350;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[21]) {
					w350 = -62.041443;
				} else {
					w350 = 39.78351;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[40]) {
					w350 = -71.78844;
				} else {
					w350 = -352.68;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[20]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[54]) {
					w350 = 2.7764068;
				} else {
					w350 = -150.29024;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[38]) {
					w350 = 196.7985;
				} else {
					w350 = 14.51057;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[8]) {
					w350 = 342.26633;
				} else {
					w350 = 68.10709;
				}
			} else {
				if (BsmtHalfBath != NULL && *BsmtHalfBath < cond_BsmtHalfBath[0]) {
					w350 = 14.610028;
				} else {
					w350 = 388.66568;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w350 = 115.85742;
			} else {
				w350 = -382.7557;
			}
		}
	}
	float w351;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[20]) {
					w351 = -35.101486;
				} else {
					w351 = -244.44016;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
					w351 = -118.134995;
				} else {
					w351 = 6.436821;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w351 = -6.884964;
				} else {
					w351 = 115.37421;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w351 = 4.6007476;
				} else {
					w351 = 218.05795;
				}
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
			w351 = 83.36133;
		} else {
			w351 = 347.6938;
		}
	}
	float w352;
	if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[35]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[55]) {
					w352 = -113.558685;
				} else {
					w352 = 100.69245;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[69]) {
					w352 = -34.87709;
				} else {
					w352 = -154.37823;
				}
			}
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
					w352 = 49.356033;
				} else {
					w352 = 257.3424;
				}
			} else {
				w352 = -100.07507;
			}
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[11]) {
			if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[3]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[23]) {
					w352 = -3.5405893;
				} else {
					w352 = -68.65696;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[70]) {
					w352 = 30.865198;
				} else {
					w352 = 185.0274;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[27]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[45]) {
					w352 = 36.745586;
				} else {
					w352 = 376.97;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[28]) {
					w352 = -228.4953;
				} else {
					w352 = 44.343155;
				}
			}
		}
	}
	float w353;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[25]) {
		if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[2]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[5]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[11]) {
					w353 = -13.378626;
				} else {
					w353 = -211.34348;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w353 = 73.94184;
				} else {
					w353 = 347.7808;
				}
			}
		} else {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[29]) {
					w353 = 57.47234;
				} else {
					w353 = -1.4758593;
				}
			} else {
				w353 = 331.86148;
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[19]) {
				if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
					w353 = 13.795058;
				} else {
					w353 = 378.86072;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[34]) {
					w353 = -58.10508;
				} else {
					w353 = -236.74734;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[52]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[19]) {
					w353 = 50.660744;
				} else {
					w353 = -155.31769;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w353 = 218.69717;
				} else {
					w353 = -209.11406;
				}
			}
		}
	}
	float w354;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
					w354 = -94.26401;
				} else {
					w354 = -20.506615;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
					w354 = 151.38937;
				} else {
					w354 = -234.38129;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w354 = 13.69746;
			} else {
				w354 = 309.6611;
			}
		}
	} else {
		if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w354 = -32.30679;
				} else {
					w354 = 20.781878;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w354 = 43.25436;
				} else {
					w354 = 402.72977;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[63]) {
					w354 = 34.67904;
				} else {
					w354 = -166.33855;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
					w354 = 129.39711;
				} else {
					w354 = -245.6069;
				}
			}
		}
	}
	float w355;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[39]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[22]) {
					w355 = -33.468006;
				} else {
					w355 = 70.46847;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[34]) {
					w355 = 9.609185;
				} else {
					w355 = 472.2772;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
					w355 = 182.00706;
				} else {
					w355 = 42.289062;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
					w355 = 114.80953;
				} else {
					w355 = -377.0279;
				}
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
			w355 = 82.707184;
		} else {
			w355 = 340.63712;
		}
	}
	float w356;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[7]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
					w356 = -268.6443;
				} else {
					w356 = -106.78466;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w356 = 119.44537;
				} else {
					w356 = 15.245742;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[20]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[8]) {
					w356 = -28.369116;
				} else {
					w356 = 28.339153;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[39]) {
					w356 = -117.834465;
				} else {
					w356 = -331.5014;
				}
			}
		}
	} else {
		if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[26]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[64]) {
					w356 = 14.3432045;
				} else {
					w356 = 166.42783;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w356 = 12.438658;
				} else {
					w356 = -174.35193;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[20]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[0]) {
					w356 = -109.7012;
				} else {
					w356 = -310.1294;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[33]) {
					w356 = 44.667816;
				} else {
					w356 = -74.57719;
				}
			}
		}
	}
	float w357;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[39]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[13]) {
					w357 = -44.650402;
				} else {
					w357 = 8.79541;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[33]) {
					w357 = -92.94176;
				} else {
					w357 = 17.43057;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
					w357 = 58.89605;
				} else {
					w357 = -101.55369;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w357 = 96.534065;
				} else {
					w357 = 284.15207;
				}
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
			w357 = 81.99363;
		} else {
			w357 = 336.60538;
		}
	}
	float w358;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[25]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[34]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[24]) {
					w358 = -43.699608;
				} else {
					w358 = 7.472058;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[25]) {
					w358 = 51.61792;
				} else {
					w358 = -52.31765;
				}
			}
		} else {
			if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[1]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[32]) {
					w358 = -11.654824;
				} else {
					w358 = 274.81567;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[36]) {
					w358 = 20.369883;
				} else {
					w358 = -130.15578;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[30]) {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[5]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w358 = 195.65045;
				} else {
					w358 = -3.7216663;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[6]) {
					w358 = 245.59612;
				} else {
					w358 = -57.381157;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[15]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[34]) {
					w358 = -738.80804;
				} else {
					w358 = -184.99998;
				}
			} else {
				w358 = 378.1261;
			}
		}
	}
	float w359;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w359 = -19.819555;
				} else {
					w359 = 16.525694;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[21]) {
					w359 = -56.539845;
				} else {
					w359 = 235.00099;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[15]) {
					w359 = 89.74783;
				} else {
					w359 = 349.56033;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
					w359 = 111.882416;
				} else {
					w359 = -370.77975;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[41]) {
			w359 = 130.2146;
		} else {
			w359 = 366.99655;
		}
	}
	float w360;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
					w360 = -92.0811;
				} else {
					w360 = -19.647093;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
					w360 = 149.45741;
				} else {
					w360 = -230.6392;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w360 = 13.391132;
			} else {
				w360 = 305.3388;
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[23]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[31]) {
					w360 = -17.68629;
				} else {
					w360 = 228.96095;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[1]) {
					w360 = 363.14713;
				} else {
					w360 = -45.699608;
				}
			}
		} else {
			if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w360 = 45.427574;
				} else {
					w360 = -138.87617;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[20]) {
					w360 = -147.22542;
				} else {
					w360 = -14.980591;
				}
			}
		}
	}
	float w361;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[30]) {
					w361 = -24.457478;
				} else {
					w361 = 125.58498;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
					w361 = 14.828961;
				} else {
					w361 = 135.97496;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[45]) {
					w361 = 4.037255;
				} else {
					w361 = 100.68962;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w361 = 771.90607;
				} else {
					w361 = 111.282715;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[41]) {
			w361 = 128.77376;
		} else {
			w361 = 362.87225;
		}
	}
	float w362;
	if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[35]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[56]) {
					w362 = -117.73397;
				} else {
					w362 = 94.99586;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[69]) {
					w362 = -30.689398;
				} else {
					w362 = -149.72237;
				}
			}
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
					w362 = 49.91285;
				} else {
					w362 = 252.67097;
				}
			} else {
				w362 = -97.8491;
			}
		}
	} else {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[71]) {
					w362 = -4.3835444;
				} else {
					w362 = -141.3455;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[8]) {
					w362 = 42.2195;
				} else {
					w362 = 489.63995;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[29]) {
					w362 = 216.23012;
				} else {
					w362 = 14.199215;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[37]) {
					w362 = 306.3367;
				} else {
					w362 = -158.23187;
				}
			}
		}
	}
	float w363;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[24]) {
					w363 = -16.139124;
				} else {
					w363 = 161.10352;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[33]) {
					w363 = -73.229195;
				} else {
					w363 = -729.085;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[25]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[57]) {
					w363 = 51.08222;
				} else {
					w363 = 242.46527;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
					w363 = -37.14196;
				} else {
					w363 = 82.10029;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
					w363 = 35.598377;
				} else {
					w363 = 251.71315;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w363 = 30.9795;
				} else {
					w363 = -237.12053;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[31]) {
					w363 = -76.7189;
				} else {
					w363 = 120.44442;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[16]) {
					w363 = 344.28064;
				} else {
					w363 = 139.83902;
				}
			}
		}
	}
	float w364;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w364 = 10.278694;
				} else {
					w364 = -26.249926;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w364 = 22.15837;
				} else {
					w364 = -152.91924;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
					w364 = 56.91424;
				} else {
					w364 = -98.09657;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w364 = 91.72603;
				} else {
					w364 = 273.5277;
				}
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
			w364 = 79.5464;
		} else {
			w364 = 324.40082;
		}
	}
	float w365;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[7]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
					w365 = -262.78766;
				} else {
					w365 = -103.21303;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w365 = 117.7009;
				} else {
					w365 = 15.833027;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[20]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[8]) {
					w365 = -27.07518;
				} else {
					w365 = 28.11538;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[39]) {
					w365 = -116.24793;
				} else {
					w365 = -328.0247;
				}
			}
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[30]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[13]) {
					w365 = -26.765253;
				} else {
					w365 = -159.53899;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
					w365 = 6.899387;
				} else {
					w365 = 140.2355;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[15]) {
					w365 = 97.90305;
				} else {
					w365 = 7.9004636;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w365 = 766.1934;
				} else {
					w365 = 187.10547;
				}
			}
		}
	}
	float w366;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
					w366 = -89.59618;
				} else {
					w366 = -18.944813;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
					w366 = 145.90968;
				} else {
					w366 = -226.81117;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w366 = 13.49918;
			} else {
				w366 = 301.89838;
			}
		}
	} else {
		if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w366 = -30.613482;
				} else {
					w366 = 19.478746;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w366 = 40.99205;
				} else {
					w366 = 390.61172;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[63]) {
					w366 = 33.37144;
				} else {
					w366 = -163.50214;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
					w366 = 123.7253;
				} else {
					w366 = -237.20255;
				}
			}
		}
	}
	float w367;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[39]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[9]) {
					w367 = -115.62629;
				} else {
					w367 = -18.614937;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[34]) {
					w367 = 9.0339365;
				} else {
					w367 = 461.51453;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
					w367 = 174.69006;
				} else {
					w367 = 36.909763;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
					w367 = 112.19672;
				} else {
					w367 = -361.10187;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[41]) {
			w367 = 125.06547;
		} else {
			w367 = 354.84314;
		}
	}
	float w368;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[25]) {
		if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[2]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[5]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[11]) {
					w368 = -12.4192295;
				} else {
					w368 = -208.2315;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w368 = 69.90488;
				} else {
					w368 = 333.65485;
				}
			}
		} else {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[29]) {
					w368 = 56.780857;
				} else {
					w368 = -2.8330078;
				}
			} else {
				w368 = 319.5667;
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
			if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[1]) {
				if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
					w368 = -10.142455;
				} else {
					w368 = 351.29483;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[23]) {
					w368 = 5.307943;
				} else {
					w368 = 340.03952;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[52]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[17]) {
					w368 = 43.61099;
				} else {
					w368 = -201.25266;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w368 = 207.75945;
				} else {
					w368 = -208.16515;
				}
			}
		}
	}
	float w369;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[25]) {
					w369 = -48.636494;
				} else {
					w369 = 62.390682;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
					w369 = -238.71887;
				} else {
					w369 = 76.13312;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w369 = 13.423359;
			} else {
				w369 = 298.41855;
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[23]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
					w369 = -16.513317;
				} else {
					w369 = 264.55142;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[1]) {
					w369 = 353.94583;
				} else {
					w369 = -45.514217;
				}
			}
		} else {
			if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w369 = 43.64542;
				} else {
					w369 = -137.21071;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[20]) {
					w369 = -143.47278;
				} else {
					w369 = -13.7263155;
				}
			}
		}
	}
	float w370;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[11]) {
					w370 = -162.04515;
				} else {
					w370 = 0.7251069;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[24]) {
					w370 = -12.619476;
				} else {
					w370 = 26.478447;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
					w370 = 55.547638;
				} else {
					w370 = -96.8378;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w370 = 87.37406;
				} else {
					w370 = 265.68497;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[41]) {
			w370 = 123.80344;
		} else {
			w370 = 347.34546;
		}
	}
	float w371;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[39]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[9]) {
					w371 = -113.644295;
				} else {
					w371 = -18.210876;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[34]) {
					w371 = 8.89912;
				} else {
					w371 = 453.95563;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
					w371 = 171.18576;
				} else {
					w371 = 35.684223;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
					w371 = 110.015625;
				} else {
					w371 = -357.69376;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[41]) {
			w371 = 122.56547;
		} else {
			w371 = 343.87186;
		}
	}
	float w372;
	if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[7]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[35]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[56]) {
					w372 = -112.974495;
				} else {
					w372 = 95.52031;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[69]) {
					w372 = -27.572798;
				} else {
					w372 = -145.33722;
				}
			}
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
					w372 = 51.948982;
				} else {
					w372 = 249.01962;
				}
			} else {
				w372 = -96.32671;
			}
		}
	} else {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[3]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[71]) {
					w372 = -4.0085087;
				} else {
					w372 = -139.38695;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[8]) {
					w372 = 39.34876;
				} else {
					w372 = 468.1788;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[18]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[3]) {
					w372 = 176.4812;
				} else {
					w372 = 5.714049;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[37]) {
					w372 = 296.39313;
				} else {
					w372 = -150.97734;
				}
			}
		}
	}
	float w373;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[58]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[52]) {
			if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[1]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[21]) {
					w373 = -52.152237;
				} else {
					w373 = -199.71368;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[66]) {
					w373 = -33.767986;
				} else {
					w373 = 25.322138;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[42]) {
				w373 = 127.18191;
			} else {
				w373 = -4.058789;
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[35]) {
					w373 = 20.66507;
				} else {
					w373 = 344.5641;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w373 = -21.091347;
				} else {
					w373 = -330.00967;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[53]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[35]) {
					w373 = -23.313929;
				} else {
					w373 = 120.502914;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[29]) {
					w373 = -10.868601;
				} else {
					w373 = 291.21423;
				}
			}
		}
	}
	float w374;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
					w374 = -87.07701;
				} else {
					w374 = -17.523348;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
					w374 = 143.40585;
				} else {
					w374 = -220.87189;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w374 = 13.225664;
			} else {
				w374 = 294.65295;
			}
		}
	} else {
		if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w374 = -29.921972;
				} else {
					w374 = 19.072042;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w374 = 39.20729;
				} else {
					w374 = 385.16107;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[63]) {
					w374 = 32.5807;
				} else {
					w374 = -161.17064;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
					w374 = 120.21421;
				} else {
					w374 = -229.11815;
				}
			}
		}
	}
	float w375;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[11]) {
					w375 = -158.90405;
				} else {
					w375 = 0.83390003;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[36]) {
					w375 = -0.69152373;
				} else {
					w375 = -366.87863;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
					w375 = 54.491837;
				} else {
					w375 = -94.942116;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w375 = 84.22861;
				} else {
					w375 = 259.52255;
				}
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
			w375 = 75.90773;
		} else {
			w375 = 306.6877;
		}
	}
	float w376;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[7]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
					w376 = -254.61119;
				} else {
					w376 = -98.399506;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w376 = 116.13975;
				} else {
					w376 = 16.223145;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[20]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[8]) {
					w376 = -25.843954;
				} else {
					w376 = 28.035162;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[39]) {
					w376 = -114.73791;
				} else {
					w376 = -325.36804;
				}
			}
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[30]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
					w376 = -56.62896;
				} else {
					w376 = 222.52446;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
					w376 = 6.303013;
				} else {
					w376 = 132.91684;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[15]) {
					w376 = 95.50094;
				} else {
					w376 = 7.030956;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w376 = 752.25653;
				} else {
					w376 = 179.41344;
				}
			}
		}
	}
	float w377;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[30]) {
					w377 = -22.879879;
				} else {
					w377 = 120.08579;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[25]) {
					w377 = 45.716072;
				} else {
					w377 = -39.74875;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[45]) {
					w377 = 3.150229;
				} else {
					w377 = 93.01604;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w377 = 746.6147;
				} else {
					w377 = 97.537735;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[41]) {
			w377 = 119.11414;
		} else {
			w377 = 335.1861;
		}
	}
	float w378;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[53]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[35]) {
					w378 = 14.705927;
				} else {
					w378 = 335.15582;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[33]) {
					w378 = -23.578112;
				} else {
					w378 = 94.863686;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[29]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
					w378 = 86.34869;
				} else {
					w378 = -252.04294;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[46]) {
					w378 = 83.21597;
				} else {
					w378 = 463.1709;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w378 = 47.429413;
				} else {
					w378 = -21.3358;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[24]) {
					w378 = -188.71883;
				} else {
					w378 = -58.708668;
				}
			}
		} else {
			w378 = 74.23398;
		}
	}
	float w379;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[7]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
					w379 = -251.1505;
				} else {
					w379 = -96.65518;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w379 = 114.03691;
				} else {
					w379 = 16.576406;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[20]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[8]) {
					w379 = -25.4349;
				} else {
					w379 = 27.595026;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[39]) {
					w379 = -113.43206;
				} else {
					w379 = -322.77457;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[35]) {
					w379 = 34.636658;
				} else {
					w379 = 400.9594;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w379 = -19.569258;
				} else {
					w379 = -325.42474;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[53]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[71]) {
					w379 = -5.593223;
				} else {
					w379 = -139.03702;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[29]) {
					w379 = -11.952468;
				} else {
					w379 = 281.32086;
				}
			}
		}
	}
	float w380;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w380 = -18.07899;
				} else {
					w380 = 31.620724;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[22]) {
					w380 = -9.810352;
				} else {
					w380 = -91.68585;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[15]) {
					w380 = 80.48219;
				} else {
					w380 = 330.9859;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
					w380 = 110.68945;
				} else {
					w380 = -349.44702;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[41]) {
			w380 = 117.65625;
		} else {
			w380 = 330.7829;
		}
	}
	float w381;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[25]) {
					w381 = -46.303734;
				} else {
					w381 = 62.270256;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
					w381 = -231.5451;
				} else {
					w381 = 73.47781;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w381 = 13.021523;
			} else {
				w381 = 290.8029;
			}
		}
	} else {
		if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
					w381 = -33.53365;
				} else {
					w381 = -293.54337;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[41]) {
					w381 = 1.3556982;
				} else {
					w381 = 200.92964;
				}
			}
		} else {
			if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[0]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[67]) {
					w381 = -36.959534;
				} else {
					w381 = 80.01907;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[18]) {
					w381 = 21.169874;
				} else {
					w381 = 394.61597;
				}
			}
		}
	}
	float w382;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[53]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[42]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
					w382 = -31.613323;
				} else {
					w382 = 8.95859;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
					w382 = -75.47098;
				} else {
					w382 = 305.64343;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[29]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
					w382 = 84.14312;
				} else {
					w382 = -248.95428;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[46]) {
					w382 = 76.50103;
				} else {
					w382 = 453.36765;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w382 = 47.136913;
				} else {
					w382 = -20.80875;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[24]) {
					w382 = -185.04199;
				} else {
					w382 = -57.565506;
				}
			}
		} else {
			w382 = 70.59727;
		}
	}
	float w383;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[11]) {
					w383 = -155.31636;
				} else {
					w383 = 0.37054688;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[36]) {
					w383 = -0.6081283;
				} else {
					w383 = -360.68625;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
					w383 = 52.956707;
				} else {
					w383 = -94.3814;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w383 = 79.512886;
				} else {
					w383 = 252.28291;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[41]) {
			w383 = 116.57938;
		} else {
			w383 = 325.99805;
		}
	}
	float w384;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[25]) {
		if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[2]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[5]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[14]) {
					w384 = -10.519087;
				} else {
					w384 = -141.54382;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w384 = 66.66771;
				} else {
					w384 = 317.3506;
				}
			}
		} else {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[29]) {
					w384 = 56.006874;
				} else {
					w384 = -3.6877735;
				}
			} else {
				w384 = 310.5524;
			}
		}
	} else {
		if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[4]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[19]) {
					w384 = 4.689105;
				} else {
					w384 = -100.89272;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[1]) {
					w384 = 37.105602;
				} else {
					w384 = 200.61238;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[29]) {
				w384 = 561.93335;
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[72]) {
					w384 = 23.134146;
				} else {
					w384 = 234.8043;
				}
			}
		}
	}
	float w385;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[46]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[37]) {
					w385 = -65.01204;
				} else {
					w385 = 2.5407865;
				}
			} else {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[3]) {
					w385 = -164.30821;
				} else {
					w385 = 227.13141;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w385 = 12.940195;
			} else {
				w385 = 287.5936;
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[23]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
					w385 = -15.703778;
				} else {
					w385 = 253.8908;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[1]) {
					w385 = 340.3577;
				} else {
					w385 = -48.335827;
				}
			}
		} else {
			if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[37]) {
					w385 = 100.44016;
				} else {
					w385 = 26.314497;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[20]) {
					w385 = -137.28401;
				} else {
					w385 = -12.112363;
				}
			}
		}
	}
	float w386;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[30]) {
					w386 = -22.21812;
				} else {
					w386 = 115.44378;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[25]) {
					w386 = 44.79156;
				} else {
					w386 = -38.528015;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[37]) {
					w386 = 16.299143;
				} else {
					w386 = 160.58026;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w386 = 735.38086;
				} else {
					w386 = 96.66416;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[41]) {
			w386 = 115.4657;
		} else {
			w386 = 322.42804;
		}
	}
	float w387;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[53]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[35]) {
					w387 = 14.249664;
				} else {
					w387 = 325.94778;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[33]) {
					w387 = -22.734375;
				} else {
					w387 = 92.48542;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[29]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
					w387 = 80.87513;
				} else {
					w387 = -247.2147;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[46]) {
					w387 = 72.90825;
				} else {
					w387 = 444.51605;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w387 = 46.869884;
				} else {
					w387 = -20.284803;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[24]) {
					w387 = -181.5315;
				} else {
					w387 = -56.9948;
				}
			}
		} else {
			w387 = 70.29219;
		}
	}
	float w388;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[25]) {
			if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[25]) {
					w388 = -21.223915;
				} else {
					w388 = -133.112;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[23]) {
					w388 = -1.2255145;
				} else {
					w388 = 71.55911;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[30]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[6]) {
					w388 = 106.69719;
				} else {
					w388 = -40.93863;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[15]) {
					w388 = -540.8855;
				} else {
					w388 = 367.44968;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w388 = 55.10289;
			} else {
				w388 = 298.0914;
			}
		} else {
			w388 = -107.28875;
		}
	}
	float w389;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[58]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[52]) {
			if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[1]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[21]) {
					w389 = -46.950085;
				} else {
					w389 = -189.23561;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[66]) {
					w389 = -30.338495;
				} else {
					w389 = 26.936192;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[42]) {
				w389 = 125.047455;
			} else {
				w389 = -2.7660937;
			}
		}
	} else {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[59]) {
					w389 = -4.815642;
				} else {
					w389 = -132.9955;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[35]) {
					w389 = 0.8808616;
				} else {
					w389 = 67.74701;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[47]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[14]) {
					w389 = -2.0617063;
				} else {
					w389 = -85.230286;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
					w389 = 350.89835;
				} else {
					w389 = -1.3738422;
				}
			}
		}
	}
	float w390;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[30]) {
					w390 = -43.42484;
				} else {
					w390 = 2.3254366;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
					w390 = 9.953298;
				} else {
					w390 = 244.14859;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
					w390 = 161.49406;
				} else {
					w390 = 30.979723;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
					w390 = 103.149605;
				} else {
					w390 = -343.24744;
				}
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
			w390 = 71.86875;
		} else {
			w390 = 287.75735;
		}
	}
	float w391;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[25]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[5]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[14]) {
					w391 = -10.007967;
				} else {
					w391 = -139.36758;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[30]) {
					w391 = 94.02293;
				} else {
					w391 = 389.85657;
				}
			}
		} else {
			if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[4]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
					w391 = -11.266419;
				} else {
					w391 = 58.027916;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[29]) {
					w391 = 554.4102;
				} else {
					w391 = 87.06606;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w391 = 54.926876;
			} else {
				w391 = 293.7223;
			}
		} else {
			w391 = -105.92305;
		}
	}
	float w392;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
					w392 = -82.42619;
				} else {
					w392 = -15.331789;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
					w392 = -225.69397;
				} else {
					w392 = 74.03531;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w392 = 13.00582;
			} else {
				w392 = 284.42075;
			}
		}
	} else {
		if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
					w392 = -30.753317;
				} else {
					w392 = -287.72186;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[41]) {
					w392 = 1.2859125;
				} else {
					w392 = 191.81921;
				}
			}
		} else {
			if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[0]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[67]) {
					w392 = -36.202568;
				} else {
					w392 = 77.12837;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[18]) {
					w392 = 21.06628;
				} else {
					w392 = 382.44708;
				}
			}
		}
	}
	float w393;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[73]) {
					w393 = -16.604137;
				} else {
					w393 = -166.8079;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[36]) {
					w393 = -0.5580093;
				} else {
					w393 = -355.94263;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
					w393 = 51.723286;
				} else {
					w393 = -91.79364;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w393 = 75.88774;
				} else {
					w393 = 244.0743;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[41]) {
			w393 = 112.74609;
		} else {
			w393 = 313.4017;
		}
	}
	float w394;
	if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[29]) {
		if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[33]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[60]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[9]) {
					w394 = -101.55124;
				} else {
					w394 = -12.167846;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[25]) {
					w394 = -346.0128;
				} else {
					w394 = 15.907798;
				}
			}
		} else {
			if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[5]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[22]) {
					w394 = 49.904716;
				} else {
					w394 = 298.4479;
				}
			} else {
				w394 = -474.48737;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[35]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[14]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w394 = -94.09412;
				} else {
					w394 = -263.79245;
				}
			} else {
				w394 = 95.07293;
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[2]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[68]) {
					w394 = -11.831352;
				} else {
					w394 = 55.14642;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[23]) {
					w394 = 235.22224;
				} else {
					w394 = 34.69253;
				}
			}
		}
	}
	float w395;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w395 = -18.793987;
				} else {
					w395 = 24.250051;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w395 = 379.9275;
				} else {
					w395 = -40.862343;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w395 = 35.171257;
				} else {
					w395 = -152.82707;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w395 = 725.20496;
				} else {
					w395 = 92.18924;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w395 = 54.22906;
			} else {
				w395 = 289.63098;
			}
		} else {
			w395 = -105.34726;
		}
	}
	float w396;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[53]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w396 = 19.468153;
				} else {
					w396 = -245.15218;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[71]) {
					w396 = -10.507326;
				} else {
					w396 = -136.86374;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[29]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
					w396 = 76.100975;
				} else {
					w396 = -243.45299;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[46]) {
					w396 = 70.94719;
				} else {
					w396 = 432.85068;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w396 = 48.03945;
				} else {
					w396 = -19.240313;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[24]) {
					w396 = -175.88214;
				} else {
					w396 = -56.772343;
				}
			}
		} else {
			w396 = 68.14453;
		}
	}
	float w397;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[35]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[38]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[6]) {
					w397 = -56.766827;
				} else {
					w397 = -243.17313;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[18]) {
					w397 = 15.585468;
				} else {
					w397 = -121.20647;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[67]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[38]) {
					w397 = -54.528885;
				} else {
					w397 = 96.82763;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
					w397 = -286.32202;
				} else {
					w397 = -10.791211;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[35]) {
					w397 = 21.578697;
				} else {
					w397 = 318.58325;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w397 = -15.917226;
				} else {
					w397 = -317.10214;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[53]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[71]) {
					w397 = -11.434666;
				} else {
					w397 = -134.87689;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[29]) {
					w397 = -14.068757;
				} else {
					w397 = 259.79245;
				}
			}
		}
	}
	float w398;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[7]) {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
					w398 = -240.01291;
				} else {
					w398 = -90.739174;
				}
			} else {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w398 = 110.692474;
				} else {
					w398 = 16.869667;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[20]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[8]) {
					w398 = -24.069809;
				} else {
					w398 = 27.658205;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[39]) {
					w398 = -111.76228;
				} else {
					w398 = -320.15945;
				}
			}
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[30]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
					w398 = -25.198864;
				} else {
					w398 = -159.6533;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[20]) {
					w398 = 14.350361;
				} else {
					w398 = -144.47646;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[15]) {
					w398 = 91.49904;
				} else {
					w398 = 6.199095;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w398 = 717.23035;
				} else {
					w398 = 167.39952;
				}
			}
		}
	}
	float w399;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
					w399 = 4.159427;
				} else {
					w399 = 178.41158;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[14]) {
					w399 = -7.44534;
				} else {
					w399 = -74.481544;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
					w399 = 50.543827;
				} else {
					w399 = -90.87187;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w399 = 74.53504;
				} else {
					w399 = 239.75621;
				}
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
			w399 = 70.42488;
		} else {
			w399 = 278.1072;
		}
	}
	float w400;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[59]) {
					w400 = -10.458009;
				} else {
					w400 = -129.77188;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[35]) {
					w400 = -2.4512017;
				} else {
					w400 = 64.10129;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[22]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[23]) {
					w400 = -13.944287;
				} else {
					w400 = 210.46494;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[24]) {
					w400 = -238.36443;
				} else {
					w400 = -34.619637;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[15]) {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[0]) {
					w400 = 57.7185;
				} else {
					w400 = 319.07108;
				}
			} else {
				w400 = 317.0713;
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w400 = 100.83211;
			} else {
				w400 = -338.0089;
			}
		}
	}
	float w401;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[46]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[37]) {
					w401 = -61.790764;
				} else {
					w401 = 3.0398595;
				}
			} else {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[3]) {
					w401 = -158.89737;
				} else {
					w401 = 224.29816;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w401 = 12.774023;
			} else {
				w401 = 279.2836;
			}
		}
	} else {
		if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
					w401 = -28.83593;
				} else {
					w401 = -280.64474;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[41]) {
					w401 = 1.1741683;
				} else {
					w401 = 186.73282;
				}
			}
		} else {
			if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[0]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[67]) {
					w401 = -35.646103;
				} else {
					w401 = 75.05619;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[18]) {
					w401 = 21.828375;
				} else {
					w401 = 375.38297;
				}
			}
		}
	}
	float w402;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w402 = -34.031868;
				} else {
					w402 = 164.75058;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w402 = 64.70836;
				} else {
					w402 = -612.90533;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w402 = 17.65728;
				} else {
					w402 = -20.354755;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[1]) {
					w402 = -115.92258;
				} else {
					w402 = 292.03983;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w402 = 53.34047;
			} else {
				w402 = 284.70053;
			}
		} else {
			w402 = -104.68937;
		}
	}
	float w403;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
		if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
			if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
					w403 = -11.314847;
				} else {
					w403 = 32.91826;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[47]) {
					w403 = -26.18976;
				} else {
					w403 = 138.01414;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[21]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[69]) {
					w403 = 10.289883;
				} else {
					w403 = 305.01266;
				}
			} else {
				w403 = -204.49539;
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w403 = 48.79129;
				} else {
					w403 = -18.588514;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[24]) {
					w403 = -172.05615;
				} else {
					w403 = -55.849552;
				}
			}
		} else {
			w403 = 64.808205;
		}
	}
	float w404;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[30]) {
					w404 = -43.79873;
				} else {
					w404 = -0.1677993;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w404 = -125.42676;
				} else {
					w404 = 271.34653;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[25]) {
					w404 = 23.518665;
				} else {
					w404 = -45.240326;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w404 = 711.4502;
				} else {
					w404 = 155.68214;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[8]) {
					w404 = 300.44107;
				} else {
					w404 = 46.576523;
				}
			} else {
				if (BsmtHalfBath != NULL && *BsmtHalfBath < cond_BsmtHalfBath[0]) {
					w404 = 1.5614811;
				} else {
					w404 = 356.8418;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w404 = 98.63039;
			} else {
				w404 = -334.94803;
			}
		}
	}
	float w405;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[24]) {
					w405 = -13.85815;
				} else {
					w405 = 151.65573;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[33]) {
					w405 = -73.92083;
				} else {
					w405 = -694.21564;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[25]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[57]) {
					w405 = 47.79264;
				} else {
					w405 = 227.11449;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
					w405 = -37.477177;
				} else {
					w405 = 74.66879;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[70]) {
					w405 = 193.12587;
				} else {
					w405 = 14.604726;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[25]) {
					w405 = -64.454254;
				} else {
					w405 = 44.6751;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[31]) {
					w405 = -79.92445;
				} else {
					w405 = 97.020546;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[16]) {
					w405 = 300.24197;
				} else {
					w405 = 110.25562;
				}
			}
		}
	}
	float w406;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[73]) {
					w406 = -15.620499;
				} else {
					w406 = -161.49428;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[36]) {
					w406 = -0.472165;
				} else {
					w406 = -349.35547;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
					w406 = 49.150543;
				} else {
					w406 = -88.95003;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w406 = 70.2892;
				} else {
					w406 = 231.93117;
				}
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
			w406 = 69.37981;
		} else {
			w406 = 270.4071;
		}
	}
	float w407;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[6]) {
					w407 = -53.254276;
				} else {
					w407 = -237.59195;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w407 = -92.880745;
				} else {
					w407 = 3.9929297;
				}
			}
		} else {
			w407 = 21.601112;
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[1]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[23]) {
					w407 = -12.50131;
				} else {
					w407 = 172.05385;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w407 = 10.535044;
				} else {
					w407 = 60.354355;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[5]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w407 = -46.87755;
				} else {
					w407 = -307.36096;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[24]) {
					w407 = -20.679085;
				} else {
					w407 = -207.42477;
				}
			}
		}
	}
	float w408;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w408 = -33.21809;
				} else {
					w408 = 161.17935;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w408 = 64.62891;
				} else {
					w408 = -603.9914;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w408 = 17.182734;
				} else {
					w408 = -19.690277;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[1]) {
					w408 = -115.07804;
				} else {
					w408 = 280.81912;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w408 = 52.25625;
			} else {
				w408 = 278.97736;
			}
		} else {
			w408 = -103.72883;
		}
	}
	float w409;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
		if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[61]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[5]) {
					w409 = -160.56107;
				} else {
					w409 = -15.0905905;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
					w409 = 87.052605;
				} else {
					w409 = 9.463715;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[5]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[18]) {
					w409 = 5.2973437;
				} else {
					w409 = -257.528;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[24]) {
					w409 = 1.9915715;
				} else {
					w409 = -112.902756;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w409 = 49.008514;
				} else {
					w409 = -17.771776;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[24]) {
					w409 = -168.75873;
				} else {
					w409 = -54.957027;
				}
			}
		} else {
			w409 = 64.663124;
		}
	}
	float w410;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[30]) {
					w410 = -42.645245;
				} else {
					w410 = -0.29677248;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w410 = -122.76791;
				} else {
					w410 = 264.11447;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[25]) {
					w410 = 22.845247;
				} else {
					w410 = -44.07881;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w410 = 706.1156;
				} else {
					w410 = 152.43398;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[8]) {
					w410 = 294.78323;
				} else {
					w410 = 45.89619;
				}
			} else {
				if (BsmtHalfBath != NULL && *BsmtHalfBath < cond_BsmtHalfBath[0]) {
					w410 = 0.8975718;
				} else {
					w410 = 353.5317;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w410 = 96.927185;
			} else {
				w410 = -329.28842;
			}
		}
	}
	float w411;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[17]) {
					w411 = -39.332138;
				} else {
					w411 = 98.419785;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
					w411 = -218.2749;
				} else {
					w411 = 73.03422;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w411 = 12.462656;
			} else {
				w411 = 273.3976;
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[23]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
					w411 = -14.889638;
				} else {
					w411 = 244.31053;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[1]) {
					w411 = 320.7594;
				} else {
					w411 = -50.331425;
				}
			}
		} else {
			if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[37]) {
					w411 = 95.219154;
				} else {
					w411 = 23.651548;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[20]) {
					w411 = -127.63394;
				} else {
					w411 = -8.347863;
				}
			}
		}
	}
	float w412;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w412 = -16.507458;
				} else {
					w412 = 14.053683;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
					w412 = 302.49707;
				} else {
					w412 = 51.31807;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[15]) {
					w412 = 71.42412;
				} else {
					w412 = 304.74;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
					w412 = 96.311714;
				} else {
					w412 = -326.03952;
				}
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
			w412 = 69.07172;
		} else {
			w412 = 264.24854;
		}
	}
	float w413;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w413 = -32.535915;
				} else {
					w413 = 158.19542;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w413 = 64.31062;
				} else {
					w413 = -597.92206;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w413 = 16.902365;
				} else {
					w413 = -19.349716;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[1]) {
					w413 = -115.15367;
				} else {
					w413 = 273.061;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w413 = 51.25976;
			} else {
				w413 = 274.50806;
			}
		} else {
			w413 = -102.257576;
		}
	}
	float w414;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[53]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w414 = 18.56471;
				} else {
					w414 = -238.82909;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[71]) {
					w414 = -9.911696;
				} else {
					w414 = -131.83328;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[29]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[8]) {
					w414 = 66.97461;
				} else {
					w414 = -238.9899;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[46]) {
					w414 = 58.75659;
				} else {
					w414 = 417.87476;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w414 = 49.179844;
				} else {
					w414 = -16.937988;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[24]) {
					w414 = -165.51901;
				} else {
					w414 = -53.958572;
				}
			}
		} else {
			w414 = 64.318436;
		}
	}
	float w415;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[6]) {
					w415 = -50.558113;
				} else {
					w415 = -232.70398;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w415 = -91.30551;
				} else {
					w415 = 5.8761325;
				}
			}
		} else {
			w415 = 21.712793;
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[35]) {
					w415 = 17.174047;
				} else {
					w415 = 309.20218;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w415 = -13.41375;
				} else {
					w415 = -309.52646;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[53]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[71]) {
					w415 = -11.235013;
				} else {
					w415 = -129.91948;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[5]) {
					w415 = 198.3533;
				} else {
					w415 = -119.73351;
				}
			}
		}
	}
	float w416;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[30]) {
					w416 = -41.50891;
				} else {
					w416 = -0.16998233;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w416 = -120.12404;
				} else {
					w416 = 256.0923;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[10]) {
					w416 = -3.9361389;
				} else {
					w416 = 55.699142;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w416 = 698.24084;
				} else {
					w416 = 148.85995;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[15]) {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[0]) {
					w416 = 53.69191;
				} else {
					w416 = 306.0906;
				}
			} else {
				w416 = 302.74207;
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w416 = 95.466324;
			} else {
				w416 = -321.05563;
			}
		}
	}
	float w417;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[58]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[52]) {
			if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[1]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[21]) {
					w417 = -39.956017;
				} else {
					w417 = -175.65387;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[66]) {
					w417 = -26.049961;
				} else {
					w417 = 28.82584;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[42]) {
				w417 = 123.79258;
			} else {
				w417 = -1.5991992;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[73]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
					w417 = -85.55979;
				} else {
					w417 = 50.32439;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[39]) {
					w417 = -244.92378;
				} else {
					w417 = -30.453074;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
					w417 = -4.0756407;
				} else {
					w417 = 175.63724;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[2]) {
					w417 = 15.734058;
				} else {
					w417 = 104.80865;
				}
			}
		}
	}
	float w418;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w418 = -32.032055;
				} else {
					w418 = 155.29768;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w418 = 64.01859;
				} else {
					w418 = -590.486;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w418 = 16.67656;
				} else {
					w418 = -18.965542;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[1]) {
					w418 = -116.590935;
				} else {
					w418 = 263.65854;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w418 = 50.45109;
			} else {
				w418 = 269.5226;
			}
		} else {
			w418 = -101.3432;
		}
	}
	float w419;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[7]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[9]) {
					w419 = -105.95113;
				} else {
					w419 = 96.67931;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[20]) {
					w419 = -7.326136;
				} else {
					w419 = -197.53413;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w419 = 35.68342;
				} else {
					w419 = -217.48212;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[53]) {
					w419 = -9.929923;
				} else {
					w419 = 150.42827;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w419 = 49.36988;
				} else {
					w419 = -16.242538;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[32]) {
					w419 = 21.982265;
				} else {
					w419 = -148.32588;
				}
			}
		} else {
			w419 = 61.13789;
		}
	}
	float w420;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[11]) {
					w420 = -140.10497;
				} else {
					w420 = 1.9879316;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[36]) {
					w420 = -0.50579995;
				} else {
					w420 = -342.95212;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
					w420 = 167.01772;
				} else {
					w420 = 20.208696;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w420 = 66.203316;
				} else {
					w420 = 226.84181;
				}
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
			w420 = 68.5623;
		} else {
			w420 = 256.59415;
		}
	}
	float w421;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[4]) {
					w421 = -17.753174;
				} else {
					w421 = 221.31892;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[35]) {
					w421 = -3.6327958;
				} else {
					w421 = 59.734497;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[22]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[23]) {
					w421 = -11.590904;
				} else {
					w421 = 204.76788;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[24]) {
					w421 = -232.14723;
				} else {
					w421 = -34.81765;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[8]) {
					w421 = 286.81323;
				} else {
					w421 = 43.66025;
				}
			} else {
				if (BsmtHalfBath != NULL && *BsmtHalfBath < cond_BsmtHalfBath[0]) {
					w421 = -0.606075;
				} else {
					w421 = 345.2447;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w421 = 94.65914;
			} else {
				w421 = -319.50827;
			}
		}
	}
	float w422;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[6]) {
					w422 = -47.378437;
				} else {
					w422 = -226.86981;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w422 = -89.64492;
				} else {
					w422 = 6.461953;
				}
			}
		} else {
			w422 = 22.69834;
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[1]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[23]) {
					w422 = -12.032557;
				} else {
					w422 = 163.65619;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w422 = 10.170663;
				} else {
					w422 = 57.03827;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[5]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w422 = -42.326923;
				} else {
					w422 = -296.7542;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[24]) {
					w422 = -18.707886;
				} else {
					w422 = -202.07867;
				}
			}
		}
	}
	float w423;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w423 = -17.281734;
				} else {
					w423 = 22.108904;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w423 = 343.0057;
				} else {
					w423 = -46.486874;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
					w423 = -4.7018895;
				} else {
					w423 = 74.99304;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w423 = 692.7628;
				} else {
					w423 = 83.377144;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w423 = 49.94758;
			} else {
				w423 = 265.1114;
			}
		} else {
			w423 = -100.78945;
		}
	}
	float w424;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w424 = 12.485499;
				} else {
					w424 = -132.57628;
				}
			} else {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[2]) {
					w424 = 343.88052;
				} else {
					w424 = 84.02309;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[47]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[22]) {
					w424 = -3.0749292;
				} else {
					w424 = -86.967865;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
					w424 = 328.06552;
				} else {
					w424 = -7.7289844;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w424 = 49.210117;
				} else {
					w424 = -15.810117;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[24]) {
					w424 = -160.49818;
				} else {
					w424 = -51.516384;
				}
			}
		} else {
			w424 = 60.492188;
		}
	}
	float w425;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[17]) {
					w425 = -37.714108;
				} else {
					w425 = 99.06758;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
					w425 = -212.29955;
				} else {
					w425 = 71.50187;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w425 = 11.833828;
			} else {
				w425 = 266.11172;
			}
		}
	} else {
		if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[1]) {
					w425 = -1.5812453;
				} else {
					w425 = -94.065315;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w425 = 32.36707;
				} else {
					w425 = 340.82834;
				}
			}
		} else {
			if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[0]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[67]) {
					w425 = -35.148026;
				} else {
					w425 = 71.54078;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[18]) {
					w425 = 24.070078;
				} else {
					w425 = 359.23965;
				}
			}
		}
	}
	float w426;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[40]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w426 = 12.692198;
				} else {
					w426 = -214.25554;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[1]) {
					w426 = -25.44581;
				} else {
					w426 = 113.90412;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
					w426 = 164.4682;
				} else {
					w426 = 19.913694;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w426 = 64.029396;
				} else {
					w426 = 222.70258;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[41]) {
			w426 = 103.8968;
		} else {
			w426 = 276.75177;
		}
	}
	float w427;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[6]) {
					w427 = -46.799442;
				} else {
					w427 = -224.04327;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w427 = -88.78795;
				} else {
					w427 = 6.4828124;
				}
			}
		} else {
			w427 = 22.480722;
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[71]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[75]) {
					w427 = -47.579456;
				} else {
					w427 = 74.792656;
				}
			} else {
				w427 = -212.42723;
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[73]) {
					w427 = -6.35914;
				} else {
					w427 = -134.81284;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w427 = -7.3886456;
				} else {
					w427 = 25.489664;
				}
			}
		}
	}
	float w428;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w428 = -31.21857;
				} else {
					w428 = 150.913;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w428 = 62.909763;
				} else {
					w428 = -585.2424;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[7]) {
					w428 = 7.5552974;
				} else {
					w428 = -103.599304;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[1]) {
					w428 = -115.66031;
				} else {
					w428 = 257.38242;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w428 = 49.66062;
			} else {
				w428 = 261.26758;
			}
		} else {
			w428 = -99.48234;
		}
	}
	float w429;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[11]) {
					w429 = -135.44484;
				} else {
					w429 = 2.3856907;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[36]) {
					w429 = -0.4858603;
				} else {
					w429 = -339.98593;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
					w429 = 162.20833;
				} else {
					w429 = 19.567932;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w429 = 62.99953;
				} else {
					w429 = 219.31848;
				}
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
			w429 = 67.72371;
		} else {
			w429 = 247.60593;
		}
	}
	float w430;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[6]) {
					w430 = -46.210663;
				} else {
					w430 = -221.13722;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w430 = -87.574684;
				} else {
					w430 = 6.381152;
				}
			}
		} else {
			w430 = 22.259062;
		}
	} else {
		if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w430 = 20.463766;
				} else {
					w430 = -211.19751;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[53]) {
					w430 = -14.322437;
				} else {
					w430 = 145.48827;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w430 = 29.16785;
				} else {
					w430 = -133.92932;
				}
			} else {
				w430 = 60.0625;
			}
		}
	}
	float w431;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[39]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[26]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[71]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[27]) {
					w431 = -6.0399323;
				} else {
					w431 = 240.85512;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[41]) {
					w431 = 97.58104;
				} else {
					w431 = -153.49359;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[1]) {
				w431 = -131.39038;
			} else {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[1]) {
					w431 = 411.04892;
				} else {
					w431 = 91.155464;
				}
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[19]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[25]) {
					w431 = 78.19044;
				} else {
					w431 = -8.421759;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[36]) {
					w431 = 35.989964;
				} else {
					w431 = -189.90414;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[62]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w431 = 64.31522;
				} else {
					w431 = -83.85866;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[7]) {
					w431 = 188.38506;
				} else {
					w431 = -98.57243;
				}
			}
		}
	}
	float w432;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w432 = -30.627365;
				} else {
					w432 = 146.96959;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w432 = 61.13625;
				} else {
					w432 = -578.44403;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[7]) {
					w432 = 7.424286;
				} else {
					w432 = -101.55959;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[1]) {
					w432 = -114.46914;
				} else {
					w432 = 252.52637;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w432 = 48.92445;
			} else {
				w432 = 257.6964;
			}
		} else {
			w432 = -98.71523;
		}
	}
	float w433;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[3]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[26]) {
					w433 = -34.50129;
				} else {
					w433 = 129.63586;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[28]) {
					w433 = -58.90611;
				} else {
					w433 = -162.4169;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[20]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[72]) {
					w433 = -27.399147;
				} else {
					w433 = 17.89631;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[39]) {
					w433 = -108.05395;
				} else {
					w433 = -314.75156;
				}
			}
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[24]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
					w433 = -22.614101;
				} else {
					w433 = -173.76962;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[20]) {
					w433 = 12.708682;
				} else {
					w433 = -132.09396;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[15]) {
					w433 = 86.06033;
				} else {
					w433 = 3.9065692;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w433 = 684.6602;
				} else {
					w433 = 151.54802;
				}
			}
		}
	}
	float w434;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[44]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[7]) {
					w434 = -12.8495455;
				} else {
					w434 = -138.0991;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w434 = -87.08439;
				} else {
					w434 = 230.69266;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[25]) {
					w434 = 21.117079;
				} else {
					w434 = -41.694996;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w434 = 679.52527;
				} else {
					w434 = 140.92717;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[15]) {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[0]) {
					w434 = 50.28861;
				} else {
					w434 = 296.39563;
				}
			} else {
				w434 = 290.93213;
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w434 = 89.948204;
			} else {
				w434 = -317.48218;
			}
		}
	}
	float w435;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[6]) {
					w435 = -45.05092;
				} else {
					w435 = -217.67157;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w435 = -86.440544;
				} else {
					w435 = 6.2850585;
				}
			}
		} else {
			w435 = 22.383633;
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[71]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[75]) {
					w435 = -46.678265;
				} else {
					w435 = 74.48898;
				}
			} else {
				w435 = -209.6679;
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[73]) {
					w435 = -5.3647943;
				} else {
					w435 = -131.24948;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w435 = -7.2408466;
				} else {
					w435 = 24.826012;
				}
			}
		}
	}
	float w436;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w436 = -30.017986;
				} else {
					w436 = 144.69841;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w436 = 60.733124;
				} else {
					w436 = -572.02216;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[7]) {
					w436 = 7.2574453;
				} else {
					w436 = -98.9819;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[1]) {
					w436 = -114.44047;
				} else {
					w436 = 246.59364;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w436 = 48.15297;
			} else {
				w436 = 254.05623;
			}
		} else {
			w436 = -97.47773;
		}
	}
	float w437;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[16]) {
					w437 = -11.355521;
				} else {
					w437 = 32.383545;
				}
			} else {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[2]) {
					w437 = 337.06686;
				} else {
					w437 = 82.07398;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[14]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[1]) {
					w437 = -33.08478;
				} else {
					w437 = 38.01592;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[34]) {
					w437 = -93.66086;
				} else {
					w437 = 110.96698;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[70]) {
					w437 = 182.97205;
				} else {
					w437 = 10.368281;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[25]) {
					w437 = -66.95017;
				} else {
					w437 = 41.609352;
				}
			}
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[23]) {
					w437 = -80.63633;
				} else {
					w437 = 94.96125;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
					w437 = 233.15427;
				} else {
					w437 = 59.325115;
				}
			}
		}
	}
	float w438;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[17]) {
					w438 = -36.16548;
				} else {
					w438 = 97.81776;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
					w438 = 129.78258;
				} else {
					w438 = -195.73827;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w438 = 11.087578;
			} else {
				w438 = 260.4014;
			}
		}
	} else {
		if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
					w438 = -22.007458;
				} else {
					w438 = -264.6723;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[41]) {
					w438 = 0.724912;
				} else {
					w438 = 166.7125;
				}
			}
		} else {
			if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[0]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[67]) {
					w438 = -34.88282;
				} else {
					w438 = 69.56915;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[18]) {
					w438 = 26.151468;
				} else {
					w438 = 350.83475;
				}
			}
		}
	}
	float w439;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[40]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w439 = 12.183361;
				} else {
					w439 = -208.70076;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[1]) {
					w439 = -24.499073;
				} else {
					w439 = 112.148415;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
					w439 = 44.978638;
				} else {
					w439 = -86.150566;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w439 = 32.142723;
				} else {
					w439 = 184.32312;
				}
			}
		}
	} else {
		w439 = 217.77693;
	}
	float w440;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[6]) {
					w440 = -44.22287;
				} else {
					w440 = -214.01003;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w440 = -85.086754;
				} else {
					w440 = 6.505371;
				}
			}
		} else {
			w440 = 22.149727;
		}
	} else {
		if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
			if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w440 = 17.30285;
				} else {
					w440 = -14.409724;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[5]) {
					w440 = -189.92737;
				} else {
					w440 = -32.87326;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w440 = 29.730322;
				} else {
					w440 = -130.2295;
				}
			} else {
				w440 = 58.54844;
			}
		}
	}
	float w441;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[3]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[26]) {
					w441 = -34.235214;
				} else {
					w441 = 128.56172;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[28]) {
					w441 = -56.868324;
				} else {
					w441 = -159.92633;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[20]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[72]) {
					w441 = -26.77372;
				} else {
					w441 = 17.482038;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[39]) {
					w441 = -107.190704;
				} else {
					w441 = -312.16095;
				}
			}
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[24]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
					w441 = -21.650745;
				} else {
					w441 = -170.27072;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[20]) {
					w441 = 12.261277;
				} else {
					w441 = -130.2208;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[15]) {
					w441 = 84.79053;
				} else {
					w441 = 3.6638236;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w441 = 673.95935;
				} else {
					w441 = 146.5196;
				}
			}
		}
	}
	float w442;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[58]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w442 = -16.483969;
				} else {
					w442 = 21.551592;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w442 = 321.89917;
				} else {
					w442 = -44.471718;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
					w442 = -5.794078;
				} else {
					w442 = 72.100266;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w442 = 668.9046;
				} else {
					w442 = 72.78175;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w442 = 47.331017;
			} else {
				w442 = 249.90477;
			}
		} else {
			w442 = -96.503204;
		}
	}
	float w443;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[39]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[26]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[71]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[27]) {
					w443 = -5.777557;
				} else {
					w443 = 235.6146;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[41]) {
					w443 = 93.26109;
				} else {
					w443 = -149.61333;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[1]) {
				w443 = -127.894844;
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[45]) {
					w443 = 427.2513;
				} else {
					w443 = 145.66031;
				}
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[46]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[29]) {
					w443 = -9.361474;
				} else {
					w443 = 82.675964;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[34]) {
					w443 = -43.02252;
				} else {
					w443 = -226.39827;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[62]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w443 = 63.55248;
				} else {
					w443 = -83.08283;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[7]) {
					w443 = 182.72263;
				} else {
					w443 = -99.00901;
				}
			}
		}
	}
	float w444;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[17]) {
					w444 = -35.36643;
				} else {
					w444 = 96.603645;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
					w444 = -205.37204;
				} else {
					w444 = 67.61797;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w444 = 10.858242;
			} else {
				w444 = 257.03928;
			}
		}
	} else {
		if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
					w444 = -20.860947;
				} else {
					w444 = -259.1801;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[41]) {
					w444 = 0.6890815;
				} else {
					w444 = 163.19562;
				}
			}
		} else {
			if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[0]) {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[2]) {
					w444 = 130.90138;
				} else {
					w444 = 3.746727;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[18]) {
					w444 = 26.24353;
				} else {
					w444 = 344.98013;
				}
			}
		}
	}
	float w445;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[6]) {
					w445 = -43.03248;
				} else {
					w445 = -209.97076;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w445 = -84.04742;
				} else {
					w445 = 6.648867;
				}
			}
		} else {
			w445 = 22.346249;
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[71]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[14]) {
					w445 = -59.03987;
				} else {
					w445 = -7.1352468;
				}
			} else {
				w445 = -205.97887;
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[46]) {
					w445 = -31.971258;
				} else {
					w445 = -180.50076;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w445 = -7.0340137;
				} else {
					w445 = 24.041237;
				}
			}
		}
	}
	float w446;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[44]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[7]) {
					w446 = -12.552076;
				} else {
					w446 = -134.19312;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w446 = -82.9663;
				} else {
					w446 = 223.1962;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[25]) {
					w446 = 20.628632;
				} else {
					w446 = -40.041843;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w446 = 663.97876;
				} else {
					w446 = 134.9097;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[8]) {
					w446 = 273.98102;
				} else {
					w446 = 40.27768;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[38]) {
					w446 = 266.71686;
				} else {
					w446 = -9.789199;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w446 = 87.21304;
			} else {
				w446 = -314.83078;
			}
		}
	}
	float w447;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w447 = -28.992512;
				} else {
					w447 = 139.30696;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w447 = 58.59492;
				} else {
					w447 = -565.47003;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[7]) {
					w447 = 7.057963;
				} else {
					w447 = -95.738884;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[1]) {
					w447 = -114.58609;
				} else {
					w447 = 238.6735;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w447 = 46.7832;
			} else {
				w447 = 246.14578;
			}
		} else {
			w447 = -95.73375;
		}
	}
	float w448;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[16]) {
					w448 = -10.991571;
				} else {
					w448 = 31.152868;
				}
			} else {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[2]) {
					w448 = 329.83;
				} else {
					w448 = 80.16615;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[14]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[1]) {
					w448 = -31.682386;
				} else {
					w448 = 37.49342;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[34]) {
					w448 = -91.61919;
				} else {
					w448 = 106.84039;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[70]) {
					w448 = 179.87901;
				} else {
					w448 = 9.75;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[25]) {
					w448 = -66.59059;
				} else {
					w448 = 40.669243;
				}
			}
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[23]) {
					w448 = -80.88867;
				} else {
					w448 = 88.895996;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[8]) {
					w448 = 224.89757;
				} else {
					w448 = 56.42836;
				}
			}
		}
	}
	float w449;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[40]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w449 = 11.954366;
				} else {
					w449 = -205.26732;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[1]) {
					w449 = -23.899107;
				} else {
					w449 = 110.091576;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
					w449 = 155.01958;
				} else {
					w449 = 18.297321;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w449 = 54.33042;
				} else {
					w449 = 204.68832;
				}
			}
		}
	} else {
		w449 = 210.67163;
	}
	float w450;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[6]) {
					w450 = -42.40538;
				} else {
					w450 = -207.10294;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w450 = -82.84305;
				} else {
					w450 = 6.788203;
				}
			}
		} else {
			w450 = 22.212715;
		}
	} else {
		if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
			if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
					w450 = 252.28104;
				} else {
					w450 = 5.1349993;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[5]) {
					w450 = -185.58144;
				} else {
					w450 = -31.648552;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w450 = 30.56461;
				} else {
					w450 = -126.45627;
				}
			} else {
				w450 = 56.665154;
			}
		}
	}
	float w451;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[3]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[26]) {
					w451 = -33.848816;
				} else {
					w451 = 127.66595;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[28]) {
					w451 = -54.806984;
				} else {
					w451 = -157.01007;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[20]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[72]) {
					w451 = -26.014198;
				} else {
					w451 = 17.21371;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[39]) {
					w451 = -106.062416;
				} else {
					w451 = -309.42087;
				}
			}
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[24]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
					w451 = -20.472992;
				} else {
					w451 = -166.20847;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[20]) {
					w451 = 11.77499;
				} else {
					w451 = -128.50333;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[15]) {
					w451 = 83.42031;
				} else {
					w451 = 3.3157396;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w451 = 658.5841;
				} else {
					w451 = 140.77094;
				}
			}
		}
	}
	float w452;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[41]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[73]) {
					w452 = -44.99101;
				} else {
					w452 = 118.77914;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
					w452 = -231.20499;
				} else {
					w452 = -19.675547;
				}
			}
		} else {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
					w452 = -5.73017;
				} else {
					w452 = 77.095535;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
					w452 = -32.866077;
				} else {
					w452 = 85.85594;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w452 = 45.92281;
			} else {
				w452 = 242.33812;
			}
		} else {
			w452 = -94.680855;
		}
	}
	float w453;
	if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
			if (YrSold != NULL && *YrSold < cond_YrSold[1]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[76]) {
					w453 = -19.813171;
				} else {
					w453 = 65.79633;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[63]) {
					w453 = -16.874;
				} else {
					w453 = -107.020454;
				}
			}
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[3]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[27]) {
					w453 = 32.590267;
				} else {
					w453 = -314.79468;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
					w453 = -34.080215;
				} else {
					w453 = 68.842575;
				}
			}
		}
	} else {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[23]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[39]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[28]) {
					w453 = 139.25516;
				} else {
					w453 = -46.782085;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w453 = 38.94666;
				} else {
					w453 = 309.4809;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[7]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[33]) {
					w453 = 147.64348;
				} else {
					w453 = -81.84668;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
					w453 = 1.9997461;
				} else {
					w453 = 324.1174;
				}
			}
		}
	}
	float w454;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w454 = -14.761678;
				} else {
					w454 = 12.506656;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
					w454 = 296.12225;
				} else {
					w454 = 40.58974;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
					w454 = 136.7469;
				} else {
					w454 = 20.785564;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
					w454 = 85.64695;
				} else {
					w454 = -312.55466;
				}
			}
		}
	} else {
		w454 = 206.93546;
	}
	float w455;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[39]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[26]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[71]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[27]) {
					w455 = -5.5019536;
				} else {
					w455 = 231.53261;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[41]) {
					w455 = 88.06224;
				} else {
					w455 = -145.71822;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[1]) {
				w455 = -123.78274;
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[45]) {
					w455 = 414.84094;
				} else {
					w455 = 131.54187;
				}
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[46]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[74]) {
					w455 = -40.372692;
				} else {
					w455 = 35.55799;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[34]) {
					w455 = -42.139454;
				} else {
					w455 = -222.3236;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[62]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w455 = 62.74508;
				} else {
					w455 = -82.00745;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[7]) {
					w455 = 176.87343;
				} else {
					w455 = -96.89776;
				}
			}
		}
	}
	float w456;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[6]) {
					w456 = -41.332703;
				} else {
					w456 = -203.74251;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w456 = -81.566246;
				} else {
					w456 = 6.9296484;
				}
			}
		} else {
			w456 = 22.584726;
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[35]) {
					w456 = 15.007807;
				} else {
					w456 = 289.37048;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w456 = 3.023584;
				} else {
					w456 = -291.2884;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[33]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[64]) {
					w456 = -20.648422;
				} else {
					w456 = 138.48772;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[26]) {
					w456 = 101.48704;
				} else {
					w456 = -258.92554;
				}
			}
		}
	}
	float w457;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[5]) {
					w457 = 3.5411034;
				} else {
					w457 = 88.499405;
				}
			} else {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[2]) {
					w457 = 325.2229;
				} else {
					w457 = 78.71766;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[47]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[22]) {
					w457 = -2.2937715;
				} else {
					w457 = -82.01113;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
					w457 = 305.49274;
				} else {
					w457 = -12.123132;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w457 = 50.174335;
				} else {
					w457 = -14.439492;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[32]) {
					w457 = 25.608046;
				} else {
					w457 = -132.56644;
				}
			}
		} else {
			w457 = 55.021717;
		}
	}
	float w458;
	if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[73]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w458 = -100.22698;
				} else {
					w458 = 64.16812;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[8]) {
					w458 = -10.82666;
				} else {
					w458 = 83.53633;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[39]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w458 = 100.50035;
				} else {
					w458 = -265.70087;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[27]) {
					w458 = -149.47707;
				} else {
					w458 = 13.713846;
				}
			}
		}
	} else {
		if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[24]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
					w458 = -11.117703;
				} else {
					w458 = 94.74619;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[38]) {
					w458 = -62.83652;
				} else {
					w458 = 263.30692;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[40]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[11]) {
					w458 = 26.859201;
				} else {
					w458 = 368.74536;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[1]) {
					w458 = -292.70935;
				} else {
					w458 = 101.34426;
				}
			}
		}
	}
	float w459;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w459 = -28.013971;
				} else {
					w459 = 134.3685;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w459 = 55.233047;
				} else {
					w459 = -556.9789;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[7]) {
					w459 = 6.835787;
				} else {
					w459 = -93.21198;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[1]) {
					w459 = -113.41398;
				} else {
					w459 = 233.32462;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w459 = 45.65289;
			} else {
				w459 = 238.0864;
			}
		} else {
			w459 = -93.17695;
		}
	}
	float w460;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[58]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[52]) {
			if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[1]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[21]) {
					w460 = -31.125402;
				} else {
					w460 = -159.22258;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[66]) {
					w460 = -20.751328;
				} else {
					w460 = 31.85036;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[42]) {
				w460 = 122.73753;
			} else {
				w460 = -0.45240232;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[73]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
					w460 = -78.35165;
				} else {
					w460 = 50.67139;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[39]) {
					w460 = -223.5387;
				} else {
					w460 = -22.678026;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[5]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[28]) {
					w460 = -1.3416061;
				} else {
					w460 = 87.07365;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[22]) {
					w460 = 71.96543;
				} else {
					w460 = -330.7304;
				}
			}
		}
	}
	float w461;
	if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[34]) {
		if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[20]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[65]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
					w461 = 8.584875;
				} else {
					w461 = -23.832485;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[42]) {
					w461 = -241.77994;
				} else {
					w461 = 406.82507;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[75]) {
				w461 = -177.74477;
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[38]) {
					w461 = 149.52074;
				} else {
					w461 = -31.468187;
				}
			}
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[30]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w461 = -71.18871;
				} else {
					w461 = 85.9358;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[29]) {
					w461 = -208.88751;
				} else {
					w461 = -77.892944;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[33]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[34]) {
					w461 = -66.58668;
				} else {
					w461 = 224.2444;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[7]) {
					w461 = 112.29876;
				} else {
					w461 = 4.078482;
				}
			}
		}
	}
	float w462;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w462 = -27.546505;
				} else {
					w462 = 132.02873;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w462 = 55.007812;
				} else {
					w462 = -551.8381;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[7]) {
					w462 = 6.032834;
				} else {
					w462 = -137.38756;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[76]) {
					w462 = -188.3427;
				} else {
					w462 = 212.38611;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w462 = 45.146484;
			} else {
				w462 = 234.64937;
			}
		} else {
			w462 = -91.88523;
		}
	}
	float w463;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[6]) {
					w463 = -39.419415;
				} else {
					w463 = -199.71126;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w463 = -80.51081;
				} else {
					w463 = 6.827461;
				}
			}
		} else {
			w463 = 22.321346;
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[71]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[14]) {
					w463 = -56.479134;
				} else {
					w463 = -5.4793825;
				}
			} else {
				w463 = -201.25398;
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[73]) {
					w463 = -3.807178;
				} else {
					w463 = -122.02913;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w463 = -6.622214;
				} else {
					w463 = 22.663843;
				}
			}
		}
	}
	float w464;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[40]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w464 = 11.418644;
				} else {
					w464 = -198.91353;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[1]) {
					w464 = -23.043291;
				} else {
					w464 = 107.5006;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[29]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[7]) {
					w464 = -125.8027;
				} else {
					w464 = 40.94959;
				}
			} else {
				if (PoolArea != NULL && *PoolArea < cond_PoolArea[0]) {
					w464 = 134.68904;
				} else {
					w464 = -151.41093;
				}
			}
		}
	} else {
		w464 = 200.94313;
	}
	float w465;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[3]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[26]) {
					w465 = -33.042538;
				} else {
					w465 = 127.51357;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[28]) {
					w465 = -53.729378;
				} else {
					w465 = -153.42648;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[20]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[5]) {
					w465 = -9.63116;
				} else {
					w465 = 75.23468;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[39]) {
					w465 = -104.31881;
				} else {
					w465 = -306.23016;
				}
			}
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[66]) {
					w465 = -62.28273;
				} else {
					w465 = 74.35445;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[41]) {
					w465 = 12.344832;
				} else {
					w465 = -165.26006;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[15]) {
					w465 = 80.9134;
				} else {
					w465 = 2.9014037;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w465 = 650.84155;
				} else {
					w465 = 135.88522;
				}
			}
		}
	}
	float w466;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[41]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[73]) {
					w466 = -42.99748;
				} else {
					w466 = 116.3782;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
					w466 = -224.26024;
				} else {
					w466 = -19.466953;
				}
			}
		} else {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
					w466 = -8.628126;
				} else {
					w466 = 31.50869;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
					w466 = -32.828873;
				} else {
					w466 = 83.1151;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w466 = 44.339455;
			} else {
				w466 = 231.40135;
			}
		} else {
			w466 = -90.39735;
		}
	}
	float w467;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[6]) {
					w467 = -39.07245;
				} else {
					w467 = -196.90894;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w467 = -79.46269;
				} else {
					w467 = 6.8275194;
				}
			}
		} else {
			w467 = 22.205214;
		}
	} else {
		if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
			if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w467 = 14.928367;
				} else {
					w467 = -122.83911;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[47]) {
					w467 = -18.398813;
				} else {
					w467 = 114.125275;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w467 = 31.130272;
				} else {
					w467 = -119.96016;
				}
			} else {
				w467 = 53.5657;
			}
		}
	}
	float w468;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[40]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w468 = 11.248264;
				} else {
					w468 = -195.17477;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[1]) {
					w468 = -22.728022;
				} else {
					w468 = 105.796234;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[29]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[46]) {
					w468 = 63.67196;
				} else {
					w468 = -27.438633;
				}
			} else {
				if (PoolArea != NULL && *PoolArea < cond_PoolArea[0]) {
					w468 = 132.2206;
				} else {
					w468 = -149.38194;
				}
			}
		}
	} else {
		w468 = 198.43059;
	}
	float w469;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[39]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[5]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[60]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
					w469 = -6.6160235;
				} else {
					w469 = 102.925934;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[7]) {
					w469 = -211.72426;
				} else {
					w469 = -0.904375;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[8]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[21]) {
					w469 = 169.11989;
				} else {
					w469 = -0.9066562;
				}
			} else {
				w469 = 305.04224;
			}
		}
	} else {
		if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[16]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[46]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[29]) {
					w469 = -9.524156;
				} else {
					w469 = 76.990265;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[34]) {
					w469 = -40.573536;
				} else {
					w469 = -217.33882;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[62]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w469 = 61.70507;
				} else {
					w469 = -80.64962;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[0]) {
					w469 = 161.14536;
				} else {
					w469 = -180.80554;
				}
			}
		}
	}
	float w470;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[6]) {
					w470 = -38.81414;
				} else {
					w470 = -194.50551;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w470 = -78.56474;
				} else {
					w470 = 6.7415624;
				}
			}
		} else {
			w470 = 22.003944;
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[30]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
					w470 = -20.508648;
				} else {
					w470 = -146.90494;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[20]) {
					w470 = 9.807957;
				} else {
					w470 = -136.03227;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[25]) {
					w470 = 20.98805;
				} else {
					w470 = -34.482735;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w470 = 645.5773;
				} else {
					w470 = 125.58754;
				}
			}
		}
	}
	float w471;
	if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[34]) {
		if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[20]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[65]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
					w471 = 8.110622;
				} else {
					w471 = -22.970232;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[42]) {
					w471 = -236.64563;
				} else {
					w471 = 402.17883;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[30]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w471 = 73.3657;
				} else {
					w471 = 273.89032;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w471 = 91.03805;
				} else {
					w471 = -162.06804;
				}
			}
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[30]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w471 = -69.21667;
				} else {
					w471 = 85.96664;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[29]) {
					w471 = -204.05382;
				} else {
					w471 = -75.48678;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[33]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[34]) {
					w471 = -66.44764;
				} else {
					w471 = 220.1784;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[46]) {
					w471 = 170.01027;
				} else {
					w471 = 10.189298;
				}
			}
		}
	}
	float w472;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[41]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[22]) {
					w472 = -53.143578;
				} else {
					w472 = 22.135695;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
					w472 = -220.89236;
				} else {
					w472 = -19.114101;
				}
			}
		} else {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
					w472 = -8.388214;
				} else {
					w472 = 30.601498;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
					w472 = -32.380714;
				} else {
					w472 = 81.29909;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w472 = 43.526093;
			} else {
				w472 = 226.79932;
			}
		} else {
			w472 = -89.35656;
		}
	}
	float w473;
	if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[24]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
					w473 = -19.748331;
				} else {
					w473 = -129.6449;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[38]) {
					w473 = -62.30238;
				} else {
					w473 = 275.70343;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[20]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[23]) {
					w473 = 8.969565;
				} else {
					w473 = 104.4403;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[3]) {
					w473 = 3.723164;
				} else {
					w473 = -204.3564;
				}
			}
		}
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[25]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[77]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w473 = -6.497764;
				} else {
					w473 = 63.99084;
				}
			} else {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w473 = 159.99721;
				} else {
					w473 = -30.090246;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[31]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[32]) {
					w473 = -3.1933722;
				} else {
					w473 = 115.96543;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w473 = 44.651276;
				} else {
					w473 = -149.35455;
				}
			}
		}
	}
	float w474;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[6]) {
					w474 = -38.37284;
				} else {
					w474 = -191.8621;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w474 = -77.700935;
				} else {
					w474 = 6.8412304;
				}
			}
		} else {
			w474 = 21.98912;
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[71]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[14]) {
					w474 = -54.75389;
				} else {
					w474 = -4.1926594;
				}
			} else {
				w474 = -194.56113;
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[46]) {
					w474 = -28.186672;
				} else {
					w474 = -167.88165;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w474 = -6.465499;
				} else {
					w474 = 21.86022;
				}
			}
		}
	}
	float w475;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[42]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[43]) {
					w475 = -8.700438;
				} else {
					w475 = 25.307474;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[48]) {
					w475 = 5.8217187;
				} else {
					w475 = -292.88925;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[27]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[40]) {
					w475 = 45.46664;
				} else {
					w475 = -114.87595;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
					w475 = 29.101645;
				} else {
					w475 = 114.14562;
				}
			}
		}
	} else {
		w475 = 194.24277;
	}
	float w476;
	if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[24]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
					w476 = -19.344515;
				} else {
					w476 = -127.848015;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[38]) {
					w476 = -61.721367;
				} else {
					w476 = 272.29077;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[20]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[23]) {
					w476 = 8.688496;
				} else {
					w476 = 102.8628;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[3]) {
					w476 = 3.3029735;
				} else {
					w476 = -201.65671;
				}
			}
		}
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[25]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[77]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w476 = -6.1730714;
				} else {
					w476 = 62.94875;
				}
			} else {
				if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
					w476 = 157.45367;
				} else {
					w476 = -29.563866;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[31]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[32]) {
					w476 = -2.9432507;
				} else {
					w476 = 114.46015;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w476 = 44.132084;
				} else {
					w476 = -147.07431;
				}
			}
		}
	}
	float w477;
	if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
		if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[5]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[24]) {
					w477 = -14.168229;
				} else {
					w477 = 26.673288;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[40]) {
					w477 = 120.3801;
				} else {
					w477 = -77.07214;
				}
			}
		} else {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[2]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[25]) {
					w477 = 356.909;
				} else {
					w477 = 82.90301;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[10]) {
					w477 = -115.8109;
				} else {
					w477 = 186.2879;
				}
			}
		}
	} else {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[33]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[49]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[41]) {
					w477 = -18.58304;
				} else {
					w477 = 59.468544;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w477 = -52.183125;
				} else {
					w477 = 311.69998;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[47]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[50]) {
					w477 = -31.801449;
				} else {
					w477 = -149.10568;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
					w477 = 293.5951;
				} else {
					w477 = -14.76181;
				}
			}
		}
	}
	float w478;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[17]) {
					w478 = -31.908274;
				} else {
					w478 = 97.38628;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
					w478 = -198.7637;
				} else {
					w478 = 62.954376;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w478 = 9.349218;
			} else {
				w478 = 247.4598;
			}
		}
	} else {
		if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[44]) {
					w478 = -39.272923;
				} else {
					w478 = 3.8296576;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
					w478 = 12.931786;
				} else {
					w478 = 273.66077;
				}
			}
		} else {
			if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[0]) {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[2]) {
					w478 = 128.0643;
				} else {
					w478 = -0.59288615;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[18]) {
					w478 = 27.22139;
				} else {
					w478 = 327.41733;
				}
			}
		}
	}
	float w479;
	if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
			if (YrSold != NULL && *YrSold < cond_YrSold[1]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[76]) {
					w479 = -18.164968;
				} else {
					w479 = 63.14756;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[63]) {
					w479 = -15.053008;
				} else {
					w479 = -103.911644;
				}
			}
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[3]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w479 = 37.55246;
				} else {
					w479 = -52.414356;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
					w479 = -31.446533;
				} else {
					w479 = 66.50875;
				}
			}
		}
	} else {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[23]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[39]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[28]) {
					w479 = 134.76506;
				} else {
					w479 = -45.021732;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w479 = 39.869316;
				} else {
					w479 = 292.7464;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[7]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[33]) {
					w479 = 142.11069;
				} else {
					w479 = -80.206055;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
					w479 = -0.49810547;
				} else {
					w479 = 297.6749;
				}
			}
		}
	}
	float w480;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[58]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[52]) {
			if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[1]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[21]) {
					w480 = -26.957527;
				} else {
					w480 = -151.41869;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[9]) {
					w480 = 39.151093;
				} else {
					w480 = -8.208086;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[42]) {
				w480 = 122.08031;
			} else {
				w480 = -0.117480464;
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[35]) {
					w480 = 14.478739;
				} else {
					w480 = 280.22467;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w480 = 7.544121;
				} else {
					w480 = -279.02255;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[33]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[64]) {
					w480 = -18.818935;
				} else {
					w480 = 130.47688;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[26]) {
					w480 = 97.116295;
				} else {
					w480 = -252.22748;
				}
			}
		}
	}
	float w481;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[42]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[43]) {
					w481 = -8.413402;
				} else {
					w481 = 24.428762;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[48]) {
					w481 = 5.2765627;
				} else {
					w481 = -288.59418;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[27]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[40]) {
					w481 = 44.495975;
				} else {
					w481 = -113.080826;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[17]) {
					w481 = 28.615664;
				} else {
					w481 = 111.41175;
				}
			}
		}
	} else {
		w481 = 189.69577;
	}
	float w482;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[6]) {
					w482 = -36.19418;
				} else {
					w482 = -187.26752;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w482 = -76.168434;
				} else {
					w482 = 7.5016403;
				}
			}
		} else {
			w482 = 22.526133;
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[36]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
					w482 = -36.976185;
				} else {
					w482 = 3.9262555;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w482 = -53.344803;
				} else {
					w482 = -318.15247;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[10]) {
					w482 = -0.9855957;
				} else {
					w482 = 46.989555;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w482 = 635.66156;
				} else {
					w482 = 121.15235;
				}
			}
		}
	}
	float w483;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w483 = -25.818762;
				} else {
					w483 = 127.244736;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w483 = 51.728672;
				} else {
					w483 = -542.82794;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[7]) {
					w483 = 6.376927;
				} else {
					w483 = -92.85304;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[1]) {
					w483 = -111.12351;
				} else {
					w483 = 221.17087;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w483 = 42.66914;
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[77]) {
					w483 = 234.58324;
				} else {
					w483 = 63.257576;
				}
			}
		} else {
			w483 = -87.99648;
		}
	}
	float w484;
	if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[34]) {
		if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[20]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[65]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
					w484 = -5.7853994;
				} else {
					w484 = -156.54428;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[42]) {
					w484 = -232.91158;
				} else {
					w484 = 396.69678;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[30]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w484 = 72.76453;
				} else {
					w484 = 263.80984;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w484 = 88.049774;
				} else {
					w484 = -159.16707;
				}
			}
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[30]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w484 = -66.14772;
				} else {
					w484 = 85.9459;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[8]) {
					w484 = -158.8608;
				} else {
					w484 = 31.506561;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[33]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[34]) {
					w484 = -66.178055;
				} else {
					w484 = 214.5831;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[46]) {
					w484 = 165.91866;
				} else {
					w484 = 9.32338;
				}
			}
		}
	}
	float w485;
	if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[73]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w485 = -94.692955;
				} else {
					w485 = 61.91578;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[8]) {
					w485 = -6.927617;
				} else {
					w485 = 81.80875;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[39]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w485 = 103.94168;
				} else {
					w485 = -249.44987;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[27]) {
					w485 = -141.27394;
				} else {
					w485 = 14.732855;
				}
			}
		}
	} else {
		if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[24]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
					w485 = -10.242973;
				} else {
					w485 = 90.05644;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[38]) {
					w485 = -60.316757;
				} else {
					w485 = 249.2654;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[40]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[11]) {
					w485 = 24.539415;
				} else {
					w485 = 344.78616;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[1]) {
					w485 = -287.67804;
				} else {
					w485 = 92.22679;
				}
			}
		}
	}
	float w486;
	if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[24]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
					w486 = -18.308393;
				} else {
					w486 = -124.98792;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[38]) {
					w486 = -59.864414;
				} else {
					w486 = 263.42914;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[20]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[23]) {
					w486 = 8.231535;
				} else {
					w486 = 100.49692;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
					w486 = -260.18985;
				} else {
					w486 = -46.821987;
				}
			}
		}
	} else {
		if (BsmtFullBath != NULL && *BsmtFullBath < cond_BsmtFullBath[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[78]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[34]) {
					w486 = 31.408865;
				} else {
					w486 = -28.94935;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[67]) {
					w486 = 155.18875;
				} else {
					w486 = -58.198647;
				}
			}
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				w486 = -326.5461;
			} else {
				w486 = -59.594997;
			}
		}
	}
	float w487;
	if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
		if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[5]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[25]) {
					w487 = -13.675651;
				} else {
					w487 = 25.412054;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[40]) {
					w487 = 117.20105;
				} else {
					w487 = -76.38234;
				}
			}
		} else {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[2]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[25]) {
					w487 = 351.09058;
				} else {
					w487 = 82.157455;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[10]) {
					w487 = -114.9292;
				} else {
					w487 = 183.39803;
				}
			}
		}
	} else {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[33]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[49]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[41]) {
					w487 = -17.852615;
				} else {
					w487 = 57.966087;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w487 = -52.467773;
				} else {
					w487 = 307.24728;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[47]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[50]) {
					w487 = -30.8845;
				} else {
					w487 = -146.29387;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
					w487 = 285.4517;
				} else {
					w487 = -14.8657875;
				}
			}
		}
	}
	float w488;
	if (LotArea != NULL && *LotArea < cond_LotArea[71]) {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[14]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[8]) {
					w488 = -85.71271;
				} else {
					w488 = -20.587788;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[68]) {
					w488 = -33.37118;
				} else {
					w488 = 99.28011;
				}
			}
		} else {
			w488 = -191.15718;
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[23]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
					w488 = -13.948973;
				} else {
					w488 = 214.40364;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[1]) {
					w488 = 287.48337;
				} else {
					w488 = -51.61051;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[31]) {
					w488 = 67.97208;
				} else {
					w488 = -118.19982;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[45]) {
					w488 = 23.947536;
				} else {
					w488 = -122.07686;
				}
			}
		}
	}
	float w489;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[6]) {
					w489 = -35.264355;
				} else {
					w489 = -184.21213;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w489 = -74.98797;
				} else {
					w489 = 7.893574;
				}
			}
		} else {
			w489 = 22.774042;
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[36]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
					w489 = -35.899643;
				} else {
					w489 = 3.6628034;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w489 = -50.671875;
				} else {
					w489 = -312.3739;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[25]) {
					w489 = 19.926239;
				} else {
					w489 = -32.500084;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w489 = 630.8189;
				} else {
					w489 = 118.242546;
				}
			}
		}
	}
	float w490;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[41]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[73]) {
					w490 = -38.95763;
				} else {
					w490 = 113.07023;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[26]) {
					w490 = -55.45469;
				} else {
					w490 = -227.32458;
				}
			}
		} else {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
					w490 = -5.197348;
				} else {
					w490 = 70.50407;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
					w490 = -32.242916;
				} else {
					w490 = 77.893585;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w490 = 42.453438;
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[77]) {
					w490 = 229.54803;
				} else {
					w490 = 63.178356;
				}
			}
		} else {
			w490 = -85.54297;
		}
	}
	float w491;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[40]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w491 = 10.809776;
				} else {
					w491 = -189.02957;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[1]) {
					w491 = -21.656456;
				} else {
					w491 = 101.94381;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[1]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[8]) {
					w491 = 27.184963;
				} else {
					w491 = 109.176216;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[47]) {
					w491 = 98.520935;
				} else {
					w491 = -162.61237;
				}
			}
		}
	} else {
		w491 = 184.69766;
	}
	float w492;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[5]) {
					w492 = 2.9960334;
				} else {
					w492 = 80.62332;
				}
			} else {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[2]) {
					w492 = 309.91437;
				} else {
					w492 = 73.36004;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[33]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[49]) {
					w492 = -3.4913704;
				} else {
					w492 = 235.89163;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[47]) {
					w492 = -69.89614;
				} else {
					w492 = 105.81626;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w492 = 51.82976;
				} else {
					w492 = -10.679824;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[32]) {
					w492 = 27.29332;
				} else {
					w492 = -121.23846;
				}
			}
		} else {
			w492 = 54.512184;
		}
	}
	float w493;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[6]) {
					w493 = -35.064404;
				} else {
					w493 = -181.98466;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w493 = -74.15257;
				} else {
					w493 = 7.8184566;
				}
			}
		} else {
			w493 = 22.538671;
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[36]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
					w493 = -35.27664;
				} else {
					w493 = 3.6617556;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w493 = -49.87664;
				} else {
					w493 = -309.55695;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[10]) {
					w493 = -1.1885366;
				} else {
					w493 = 50.49741;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w493 = 626.02313;
				} else {
					w493 = 120.86912;
				}
			}
		}
	}
	float w494;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[30]) {
					w494 = -16.674112;
				} else {
					w494 = 91.020645;
				}
			} else {
				if (BsmtFullBath != NULL && *BsmtFullBath < cond_BsmtFullBath[1]) {
					w494 = 21.356422;
				} else {
					w494 = -253.9414;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
					w494 = -8.890611;
				} else {
					w494 = 66.655846;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w494 = 621.3279;
				} else {
					w494 = 55.47703;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w494 = 42.193436;
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[77]) {
					w494 = 226.0896;
				} else {
					w494 = 62.222225;
				}
			}
		} else {
			w494 = -84.31195;
		}
	}
	float w495;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[42]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
					w495 = -69.171165;
				} else {
					w495 = -0.18198952;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[48]) {
					w495 = 4.4796877;
				} else {
					w495 = -275.47772;
				}
			}
		} else {
			if (LotArea != NULL && *LotArea < cond_LotArea[78]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[32]) {
					w495 = 35.5403;
				} else {
					w495 = 183.35338;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[27]) {
					w495 = -79.13326;
				} else {
					w495 = 34.583614;
				}
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
			w495 = 55.838905;
		} else {
			w495 = 200.05037;
		}
	}
	float w496;
	if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[34]) {
		if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[20]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[65]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
					w496 = -5.5177684;
				} else {
					w496 = -154.58989;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[42]) {
					w496 = -228.35825;
				} else {
					w496 = 390.32953;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[30]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w496 = 70.95305;
				} else {
					w496 = 256.2732;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w496 = 85.90598;
				} else {
					w496 = -156.99933;
				}
			}
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[30]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
					w496 = -63.918068;
				} else {
					w496 = 85.857025;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[29]) {
					w496 = -193.47484;
				} else {
					w496 = -69.082;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[35]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[11]) {
					w496 = 25.92239;
				} else {
					w496 = 192.9316;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[21]) {
					w496 = 0.5407987;
				} else {
					w496 = 124.511894;
				}
			}
		}
	}
	float w497;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[47]) {
					w497 = -153.39438;
				} else {
					w497 = -44.765312;
				}
			} else {
				w497 = 7.9275584;
			}
		} else {
			w497 = 22.537382;
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[71]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[75]) {
					w497 = -37.727386;
				} else {
					w497 = 76.98132;
				}
			} else {
				w497 = -186.31078;
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[46]) {
					w497 = -25.5457;
				} else {
					w497 = -159.50775;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w497 = -5.8143315;
				} else {
					w497 = 20.09859;
				}
			}
		}
	}
	float w498;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w498 = -24.501104;
				} else {
					w498 = 124.865974;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w498 = 54.097733;
				} else {
					w498 = -534.3278;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[7]) {
					w498 = 6.0606914;
				} else {
					w498 = -91.52158;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[76]) {
					w498 = -182.78824;
				} else {
					w498 = 197.21304;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w498 = 41.548203;
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[77]) {
					w498 = 222.37553;
				} else {
					w498 = 61.841953;
				}
			}
		} else {
			w498 = -82.64109;
		}
	}
	float w499;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w499 = 10.052793;
				} else {
					w499 = -118.07723;
				}
			} else {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[2]) {
					w499 = 305.39352;
				} else {
					w499 = 72.173584;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[33]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[49]) {
					w499 = -3.2876835;
				} else {
					w499 = 231.34387;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[47]) {
					w499 = -68.85579;
				} else {
					w499 = 103.023186;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
					w499 = 64.21055;
				} else {
					w499 = 13.88162;
				}
			} else {
				w499 = -10.023281;
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[32]) {
					w499 = 26.978203;
				} else {
					w499 = -118.55863;
				}
			} else {
				w499 = 52.595314;
			}
		}
	}
	float w500;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w500 = -13.073552;
				} else {
					w500 = 11.163171;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
					w500 = 268.9007;
				} else {
					w500 = 24.485703;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[14]) {
					w500 = -57.086807;
				} else {
					w500 = 93.98831;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
					w500 = 71.401405;
				} else {
					w500 = -308.3945;
				}
			}
		}
	} else {
		w500 = 179.22726;
	}
	float w501;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[3]) {
					w501 = -60.502106;
				} else {
					w501 = -190.23363;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w501 = -72.3205;
				} else {
					w501 = 7.9453125;
				}
			}
		} else {
			w501 = 22.345488;
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[35]) {
					w501 = 12.908858;
				} else {
					w501 = 269.90088;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w501 = 7.137539;
				} else {
					w501 = -271.17548;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[33]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[64]) {
					w501 = -18.423986;
				} else {
					w501 = 125.23532;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[26]) {
					w501 = 95.35683;
				} else {
					w501 = -241.13922;
				}
			}
		}
	}
	float w502;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[36]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
					w502 = 62.102524;
				} else {
					w502 = -153.20155;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[28]) {
					w502 = -57.42591;
				} else {
					w502 = -172.48288;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[20]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[5]) {
					w502 = -7.876719;
				} else {
					w502 = 70.45533;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[39]) {
					w502 = -102.469124;
				} else {
					w502 = -302.36038;
				}
			}
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[9]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
					w502 = -43.121452;
				} else {
					w502 = 1.7850486;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
					w502 = 64.59674;
				} else {
					w502 = -193.57764;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[15]) {
					w502 = 75.88341;
				} else {
					w502 = 1.6369448;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w502 = 614.52563;
				} else {
					w502 = 121.44497;
				}
			}
		}
	}
	float w503;
	if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[34]) {
		if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[20]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[65]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
					w503 = -5.434623;
				} else {
					w503 = -150.89195;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[42]) {
					w503 = -224.82155;
				} else {
					w503 = 386.27554;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[30]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w503 = 70.64672;
				} else {
					w503 = 250.9607;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w503 = 84.12319;
				} else {
					w503 = -155.48843;
				}
			}
		}
	} else {
		if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[46]) {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[13]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[15]) {
					w503 = 18.589012;
				} else {
					w503 = -232.52242;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[16]) {
					w503 = 163.70018;
				} else {
					w503 = -16.816305;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
					w503 = 30.25329;
				} else {
					w503 = -159.46101;
				}
			} else {
				w503 = -456.3339;
			}
		}
	}
	float w504;
	if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
		if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[5]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[25]) {
					w504 = -13.003239;
				} else {
					w504 = 24.12322;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[40]) {
					w504 = 112.77377;
				} else {
					w504 = -76.5916;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[69]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[48]) {
					w504 = 108.271126;
				} else {
					w504 = -152.6839;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[17]) {
					w504 = 273.17606;
				} else {
					w504 = -92.2575;
				}
			}
		}
	} else {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[33]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[49]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[41]) {
					w504 = -17.099766;
				} else {
					w504 = 56.393906;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w504 = -55.439648;
				} else {
					w504 = 295.70325;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[24]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[30]) {
					w504 = 12.334122;
				} else {
					w504 = -241.77592;
				}
			} else {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[0]) {
					w504 = -22.067617;
				} else {
					w504 = 277.5244;
				}
			}
		}
	}
	float w505;
	if (LotArea != NULL && *LotArea < cond_LotArea[49]) {
		if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[1]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[26]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[17]) {
					w505 = -29.562546;
				} else {
					w505 = 98.85674;
				}
			} else {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[8]) {
					w505 = -193.75185;
				} else {
					w505 = 60.679844;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[15]) {
				w505 = 8.541914;
			} else {
				w505 = 239.21332;
			}
		}
	} else {
		if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[15]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[41]) {
					w505 = 0.3849951;
				} else {
					w505 = 178.16524;
				}
			} else {
				if (YrSold != NULL && *YrSold < cond_YrSold[1]) {
					w505 = 67.89531;
				} else {
					w505 = -174.7847;
				}
			}
		} else {
			if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[0]) {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[2]) {
					w505 = 125.0593;
				} else {
					w505 = -2.2023466;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[18]) {
					w505 = 27.508734;
				} else {
					w505 = 312.1641;
				}
			}
		}
	}
	float w506;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[30]) {
					w506 = -16.137367;
				} else {
					w506 = 87.015976;
				}
			} else {
				if (BsmtFullBath != NULL && *BsmtFullBath < cond_BsmtFullBath[1]) {
					w506 = 20.608688;
				} else {
					w506 = -248.87273;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
					w506 = -8.599456;
				} else {
					w506 = 64.804924;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w506 = 609.7737;
				} else {
					w506 = 54.043125;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w506 = 41.530544;
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[77]) {
					w506 = 218.47488;
				} else {
					w506 = 61.24535;
				}
			}
		} else {
			w506 = -81.48937;
		}
	}
	float w507;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
		if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[42]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[13]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[5]) {
					w507 = -9.113491;
				} else {
					w507 = 122.17122;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[11]) {
					w507 = 0.76335424;
				} else {
					w507 = 91.29001;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[48]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[2]) {
					w507 = -27.415312;
				} else {
					w507 = 29.622187;
				}
			} else {
				w507 = -270.69974;
			}
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[78]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[32]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[7]) {
					w507 = -125.2225;
				} else {
					w507 = 48.329056;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[31]) {
					w507 = 97.04684;
				} else {
					w507 = 256.95187;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[27]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[32]) {
					w507 = 3.3271875;
				} else {
					w507 = -105.37773;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w507 = 1.8004687;
				} else {
					w507 = 40.772186;
				}
			}
		}
	}
	float w508;
	if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[73]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w508 = -91.06632;
				} else {
					w508 = 59.802185;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[8]) {
					w508 = -4.1067185;
				} else {
					w508 = 80.65599;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w508 = 104.274605;
				} else {
					w508 = -252.07529;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[27]) {
					w508 = -129.59785;
				} else {
					w508 = 14.995962;
				}
			}
		}
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w508 = -27.671286;
				} else {
					w508 = 112.63743;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w508 = -135.78616;
				} else {
					w508 = 257.46677;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[36]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[28]) {
					w508 = -2.8679762;
				} else {
					w508 = 83.78756;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w508 = -45.913475;
				} else {
					w508 = -297.93277;
				}
			}
		}
	}
	float w509;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[41]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[22]) {
					w509 = -46.765503;
				} else {
					w509 = 23.916903;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[26]) {
					w509 = -53.589684;
				} else {
					w509 = -220.52646;
				}
			}
		} else {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[17]) {
					w509 = -1.6384423;
				} else {
					w509 = -149.73451;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
					w509 = -32.38938;
				} else {
					w509 = 74.8034;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w509 = 40.94789;
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[77]) {
					w509 = 215.72562;
				} else {
					w509 = 60.87586;
				}
			}
		} else {
			w509 = -79.8582;
		}
	}
	float w510;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[47]) {
					w510 = -148.66302;
				} else {
					w510 = -43.373085;
				}
			} else {
				w510 = 8.334199;
			}
		} else {
			w510 = 22.595625;
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[35]) {
					w510 = 12.686084;
				} else {
					w510 = 263.1304;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w510 = 6.7243357;
				} else {
					w510 = -267.73273;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[33]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[64]) {
					w510 = -18.009464;
				} else {
					w510 = 120.106224;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[26]) {
					w510 = 93.16286;
				} else {
					w510 = -232.5257;
				}
			}
		}
	}
	float w511;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w511 = 9.762852;
				} else {
					w511 = -113.84343;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[69]) {
					w511 = 11.430602;
				} else {
					w511 = 223.5541;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[33]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[49]) {
					w511 = -3.0619843;
				} else {
					w511 = 223.34894;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[47]) {
					w511 = -67.19645;
				} else {
					w511 = 99.39298;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
				w511 = 64.813065;
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w511 = -9.85207;
				} else {
					w511 = 13.06957;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
				if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[1]) {
					w511 = -35.767246;
				} else {
					w511 = -127.778755;
				}
			} else {
				w511 = 48.483826;
			}
		}
	}
	float w512;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[42]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[44]) {
					w512 = -14.7217245;
				} else {
					w512 = 8.637333;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[48]) {
					w512 = -0.0465625;
				} else {
					w512 = -265.6971;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[1]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[79]) {
					w512 = 79.97283;
				} else {
					w512 = 7.745915;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[47]) {
					w512 = 93.02355;
				} else {
					w512 = -160.77797;
				}
			}
		}
	} else {
		w512 = 174.74297;
	}
	float w513;
	if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[73]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w513 = -89.57081;
				} else {
					w513 = 59.30795;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[8]) {
					w513 = -3.7353907;
				} else {
					w513 = 79.60951;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[16]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w513 = 103.44679;
				} else {
					w513 = -248.28201;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[27]) {
					w513 = -127.902565;
				} else {
					w513 = 14.716853;
				}
			}
		}
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w513 = -26.93893;
				} else {
					w513 = 111.285965;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w513 = -133.58391;
				} else {
					w513 = 253.62181;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[36]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[28]) {
					w513 = -2.8571596;
				} else {
					w513 = 81.85311;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w513 = -45.19676;
				} else {
					w513 = -291.5965;
				}
			}
		}
	}
	float w514;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[30]) {
					w514 = -15.765355;
				} else {
					w514 = 84.12679;
				}
			} else {
				if (BsmtFullBath != NULL && *BsmtFullBath < cond_BsmtFullBath[1]) {
					w514 = 20.113497;
				} else {
					w514 = -244.3285;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w514 = 25.294483;
				} else {
					w514 = -142.47304;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w514 = 603.38763;
				} else {
					w514 = 53.666718;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w514 = 40.465153;
			} else {
				w514 = 199.44337;
			}
		} else {
			w514 = -78.74094;
		}
	}
	float w515;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[47]) {
					w515 = -146.42072;
				} else {
					w515 = -42.81883;
				}
			} else {
				w515 = 8.544726;
			}
		} else {
			w515 = 22.603006;
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[35]) {
					w515 = 12.490279;
				} else {
					w515 = 258.2371;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w515 = 6.68417;
				} else {
					w515 = -262.74988;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[33]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[64]) {
					w515 = -17.742603;
				} else {
					w515 = 117.92645;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[26]) {
					w515 = 91.60891;
				} else {
					w515 = -227.35211;
				}
			}
		}
	}
	float w516;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[5]) {
					w516 = 2.733331;
				} else {
					w516 = 76.01526;
				}
			} else {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[2]) {
					w516 = 295.67395;
				} else {
					w516 = 67.09385;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[33]) {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[5]) {
					w516 = 5.04538;
				} else {
					w516 = -189.37502;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[18]) {
					w516 = -72.97816;
				} else {
					w516 = 61.25985;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
				w516 = 64.53492;
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w516 = -9.395039;
				} else {
					w516 = 12.359355;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
				if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[1]) {
					w516 = -35.001755;
				} else {
					w516 = -125.56494;
				}
			} else {
				w516 = 46.185467;
			}
		}
	}
	float w517;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[30]) {
					w517 = -15.226049;
				} else {
					w517 = 82.61292;
				}
			} else {
				if (BsmtFullBath != NULL && *BsmtFullBath < cond_BsmtFullBath[1]) {
					w517 = 20.282135;
				} else {
					w517 = -241.65883;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
					w517 = -8.783217;
				} else {
					w517 = 63.414543;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w517 = 596.9051;
				} else {
					w517 = 53.231834;
				}
			}
		}
	} else {
		w517 = 172.17819;
	}
	float w518;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[58]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[52]) {
			if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[1]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[21]) {
					w518 = -21.585537;
				} else {
					w518 = -139.94946;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[9]) {
					w518 = 41.02531;
				} else {
					w518 = -6.448867;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[42]) {
				w518 = 119.59792;
			} else {
				w518 = -2.2771873;
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[73]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
					w518 = -69.654785;
				} else {
					w518 = 50.493694;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[16]) {
					w518 = -203.16788;
				} else {
					w518 = -25.199505;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
					w518 = 4.8549037;
				} else {
					w518 = 206.88878;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[43]) {
					w518 = 18.696764;
				} else {
					w518 = -9.780318;
				}
			}
		}
	}
	float w519;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[20]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[36]) {
					w519 = 30.124758;
				} else {
					w519 = -74.518005;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[5]) {
					w519 = -7.4313083;
				} else {
					w519 = 67.2348;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[39]) {
				w519 = -101.351814;
			} else {
				w519 = -299.71008;
			}
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[9]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
					w519 = -42.098484;
				} else {
					w519 = 1.9256849;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
					w519 = 63.337082;
				} else {
					w519 = -191.33865;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[15]) {
					w519 = 71.70697;
				} else {
					w519 = 1.4734615;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w519 = 592.50165;
				} else {
					w519 = 118.05189;
				}
			}
		}
	}
	float w520;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[41]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[73]) {
					w520 = -35.71383;
				} else {
					w520 = 110.28258;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
					w520 = -202.98663;
				} else {
					w520 = -16.875;
				}
			}
		} else {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[17]) {
					w520 = -1.5686891;
				} else {
					w520 = -148.53252;
				}
			} else {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[0]) {
					w520 = 16.941664;
				} else {
					w520 = 213.73225;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w520 = 40.268044;
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[77]) {
					w520 = 209.74155;
				} else {
					w520 = 58.469414;
				}
			}
		} else {
			w520 = -77.49641;
		}
	}
	float w521;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[42]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[44]) {
					w521 = -14.432876;
				} else {
					w521 = 8.477703;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[48]) {
					w521 = -2.310625;
				} else {
					w521 = -259.7595;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[1]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[79]) {
					w521 = 79.00973;
				} else {
					w521 = 6.874732;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[47]) {
					w521 = 90.69305;
				} else {
					w521 = -158.90326;
				}
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
			w521 = 51.355896;
		} else {
			w521 = 186.92836;
		}
	}
	float w522;
	if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[34]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (YrSold != NULL && *YrSold < cond_YrSold[1]) {
					w522 = 7.1257677;
				} else {
					w522 = -36.540092;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[30]) {
					w522 = 32.4993;
				} else {
					w522 = -626.6576;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[17]) {
					w522 = -1.4427136;
				} else {
					w522 = -173.83727;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[25]) {
					w522 = 116.183105;
				} else {
					w522 = 9.215183;
				}
			}
		}
	} else {
		if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[46]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[22]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[10]) {
					w522 = 9.463583;
				} else {
					w522 = 279.1537;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[41]) {
					w522 = 250.77791;
				} else {
					w522 = -46.94313;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
					w522 = 26.160368;
				} else {
					w522 = -159.0882;
				}
			} else {
				w522 = -443.5532;
			}
		}
	}
	float w523;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
		if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w523 = 62.650547;
				} else {
					w523 = 255.67816;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
					w523 = 47.396004;
				} else {
					w523 = -0.98590904;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[26]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[35]) {
					w523 = -16.3945;
				} else {
					w523 = -212.47253;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
					w523 = -53.868385;
				} else {
					w523 = 59.54698;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
				w523 = 64.776505;
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w523 = -9.562968;
				} else {
					w523 = 12.729023;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[28]) {
					w523 = -126.31539;
				} else {
					w523 = -40.305786;
				}
			} else {
				w523 = 45.63414;
			}
		}
	}
	float w524;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[47]) {
					w524 = -142.86096;
				} else {
					w524 = -42.492226;
				}
			} else {
				w524 = 8.873906;
			}
		} else {
			w524 = 22.51664;
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[71]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[14]) {
					w524 = -48.672016;
				} else {
					w524 = 0.45421404;
				}
			} else {
				w524 = -179.52574;
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[73]) {
					w524 = -0.24366798;
				} else {
					w524 = -105.86433;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w524 = -5.426379;
				} else {
					w524 = 18.672205;
				}
			}
		}
	}
	float w525;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w525 = -23.112703;
				} else {
					w525 = 120.49659;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w525 = 52.444687;
				} else {
					w525 = -524.12555;
				}
			}
		} else {
			if (MiscVal != NULL && *MiscVal < cond_MiscVal[0]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w525 = 9.779521;
				} else {
					w525 = -112.081085;
				}
			} else {
				if (MiscVal != NULL && *MiscVal < cond_MiscVal[1]) {
					w525 = -339.3881;
				} else {
					w525 = -45.222603;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w525 = 39.621483;
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[77]) {
					w525 = 206.44214;
				} else {
					w525 = 58.461327;
				}
			}
		} else {
			w525 = -76.68219;
		}
	}
	float w526;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[30]) {
					w526 = -14.906933;
				} else {
					w526 = 80.42037;
				}
			} else {
				if (BsmtFullBath != NULL && *BsmtFullBath < cond_BsmtFullBath[1]) {
					w526 = 19.763298;
				} else {
					w526 = -237.481;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w526 = 24.617601;
				} else {
					w526 = -139.75699;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w526 = 588.09937;
				} else {
					w526 = 51.188435;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[41]) {
			w526 = 76.888435;
		} else {
			w526 = 201.73694;
		}
	}
	float w527;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w527 = 5.800032;
				} else {
					w527 = -113.436714;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[69]) {
					w527 = 8.747075;
				} else {
					w527 = 217.82376;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[22]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[37]) {
					w527 = -21.091442;
				} else {
					w527 = 42.598938;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[24]) {
					w527 = -207.50491;
				} else {
					w527 = -26.33941;
				}
			}
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[78]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[5]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[7]) {
					w527 = -124.963005;
				} else {
					w527 = 48.72594;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w527 = 74.00437;
				} else {
					w527 = 249.62114;
				}
			}
		} else {
			if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[27]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[32]) {
					w527 = 1.7650781;
				} else {
					w527 = -102.66812;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w527 = 1.8697265;
				} else {
					w527 = 34.4925;
				}
			}
		}
	}
	float w528;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[41]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[73]) {
					w528 = -34.693317;
				} else {
					w528 = 109.26492;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[26]) {
					w528 = -51.24953;
				} else {
					w528 = -212.0025;
				}
			}
		} else {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[17]) {
					w528 = -1.5520712;
				} else {
					w528 = -146.74835;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
					w528 = -32.405098;
				} else {
					w528 = 72.06212;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w528 = 39.23617;
			} else {
				w528 = 191.11874;
			}
		} else {
			w528 = -75.12117;
		}
	}
	float w529;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w529 = -262.11316;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w529 = -23.995935;
				} else {
					w529 = 108.27577;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[80]) {
					w529 = 252.81923;
				} else {
					w529 = -47.94107;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[33]) {
					w529 = -76.71512;
				} else {
					w529 = 8.232112;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[44]) {
					w529 = 16.506638;
				} else {
					w529 = -8.972771;
				}
			}
		}
	}
	float w530;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[47]) {
					w530 = -140.66103;
				} else {
					w530 = -41.823006;
				}
			} else {
				w530 = 8.891836;
			}
		} else {
			w530 = 22.230585;
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[71]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[75]) {
					w530 = -34.438286;
				} else {
					w530 = 79.697655;
				}
			} else {
				w530 = -175.8011;
			}
		} else {
			if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
					w530 = 226.29776;
				} else {
					w530 = 4.8078313;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
					w530 = -73.39766;
				} else {
					w530 = 40.46706;
				}
			}
		}
	}
	float w531;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[33]) {
					w531 = -6.014618;
				} else {
					w531 = -163.33408;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[23]) {
					w531 = 98.03621;
				} else {
					w531 = -19.913145;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
					w531 = -9.027527;
				} else {
					w531 = 61.67505;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w531 = 583.6879;
				} else {
					w531 = 50.611523;
				}
			}
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
			w531 = 50.37023;
		} else {
			w531 = 181.50175;
		}
	}
	float w532;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
					w532 = 9.143898;
				} else {
					w532 = 137.81467;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[39]) {
					w532 = 56.886692;
				} else {
					w532 = -235.60408;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[33]) {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[5]) {
					w532 = 5.2678146;
				} else {
					w532 = -186.0138;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[24]) {
					w532 = -119.46206;
				} else {
					w532 = -9.484536;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
				w532 = 65.37088;
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w532 = -8.657754;
				} else {
					w532 = 13.588418;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
				if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[1]) {
					w532 = -31.98828;
				} else {
					w532 = -121.32157;
				}
			} else {
				w532 = 45.71406;
			}
		}
	}
	float w533;
	if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[34]) {
		if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[37]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
					w533 = -9.959902;
				} else {
					w533 = 61.66743;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[30]) {
					w533 = 19.336758;
				} else {
					w533 = -617.9632;
				}
			}
		} else {
			if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[2]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[14]) {
					w533 = -91.30279;
				} else {
					w533 = 79.44198;
				}
			} else {
				if (YrSold != NULL && *YrSold < cond_YrSold[2]) {
					w533 = 128.2836;
				} else {
					w533 = -132.32703;
				}
			}
		}
	} else {
		if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[46]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[22]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[10]) {
					w533 = 9.135193;
				} else {
					w533 = 273.82526;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[41]) {
					w533 = 245.85059;
				} else {
					w533 = -47.581303;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
					w533 = 26.717075;
				} else {
					w533 = -158.42719;
				}
			} else {
				w533 = -438.26657;
			}
		}
	}
	float w534;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w534 = -259.5457;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w534 = -23.62007;
				} else {
					w534 = 106.520836;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[80]) {
					w534 = 248.83878;
				} else {
					w534 = -47.111046;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[33]) {
					w534 = -75.377495;
				} else {
					w534 = 8.103179;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[44]) {
					w534 = 16.272133;
				} else {
					w534 = -8.89081;
				}
			}
		}
	}
	float w535;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[47]) {
					w535 = -138.66263;
				} else {
					w535 = -41.670742;
				}
			} else {
				w535 = 8.783438;
			}
		} else {
			w535 = 21.993046;
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
					w535 = -26.56616;
				} else {
					w535 = -361.59995;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[41]) {
					w535 = 6.2342453;
				} else {
					w535 = -154.98898;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[10]) {
					w535 = -1.2286763;
				} else {
					w535 = 44.543015;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w535 = 579.3832;
				} else {
					w535 = 113.43249;
				}
			}
		}
	}
	float w536;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w536 = -22.329288;
				} else {
					w536 = 117.81533;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w536 = 53.12953;
				} else {
					w536 = -512.129;
				}
			}
		} else {
			if (MiscVal != NULL && *MiscVal < cond_MiscVal[0]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w536 = 9.454755;
				} else {
					w536 = -108.97743;
				}
			} else {
				if (MiscVal != NULL && *MiscVal < cond_MiscVal[1]) {
					w536 = -334.72876;
				} else {
					w536 = -44.44212;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w536 = 38.52836;
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[77]) {
					w536 = 200.69179;
				} else {
					w536 = 55.052578;
				}
			}
		} else {
			w536 = -74.02391;
		}
	}
	float w537;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w537 = -257.66074;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w537 = -23.250906;
				} else {
					w537 = 105.040535;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[80]) {
					w537 = 244.69283;
				} else {
					w537 = -46.72537;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[33]) {
					w537 = -74.18965;
				} else {
					w537 = 8.053291;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[44]) {
					w537 = 16.008541;
				} else {
					w537 = -8.763611;
				}
			}
		}
	}
	float w538;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[19]) {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[20]) {
					w538 = -3.9839268;
				} else {
					w538 = -47.966957;
				}
			} else {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[0]) {
					w538 = 12.251147;
				} else {
					w538 = 250.18622;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[37]) {
					w538 = 6.351825;
				} else {
					w538 = 129.63618;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w538 = 575.0325;
				} else {
					w538 = 48.86742;
				}
			}
		}
	} else {
		w538 = 162.41539;
	}
	float w539;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w539 = -255.69843;
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[40]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[33]) {
					w539 = -25.188456;
				} else {
					w539 = 180.39342;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[41]) {
					w539 = 110.105896;
				} else {
					w539 = 0.71461046;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[24]) {
					w539 = -2.1701858;
				} else {
					w539 = 45.877087;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w539 = 570.7197;
				} else {
					w539 = 111.76784;
				}
			}
		}
	}
	float w540;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
					w540 = 8.966376;
				} else {
					w540 = 135.48755;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[39]) {
					w540 = 56.05142;
				} else {
					w540 = -232.48973;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[22]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[49]) {
					w540 = -3.5567715;
				} else {
					w540 = 216.87538;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[24]) {
					w540 = -191.99936;
				} else {
					w540 = -9.486521;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
				w540 = 66.66252;
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w540 = -7.4384766;
				} else {
					w540 = 11.973984;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[28]) {
					w540 = -121.90971;
				} else {
					w540 = -38.126717;
				}
			} else {
				w540 = 43.9325;
			}
		}
	}
	float w541;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
		if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[42]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[13]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[5]) {
					w541 = -8.4604645;
				} else {
					w541 = 115.423485;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[11]) {
					w541 = 0.17270817;
				} else {
					w541 = 85.4668;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[48]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[2]) {
					w541 = -30.468515;
				} else {
					w541 = 27.434765;
				}
			} else {
				w541 = -250.61665;
			}
		}
	} else {
		if (MoSold != NULL && *MoSold < cond_MoSold[1]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[79]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[1]) {
					w541 = 84.03778;
				} else {
					w541 = -134.69977;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[12]) {
					w541 = -45.238537;
				} else {
					w541 = 74.96911;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[47]) {
				w541 = 88.91379;
			} else {
				w541 = -158.26921;
			}
		}
	}
	float w542;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[41]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[73]) {
					w542 = -33.536434;
				} else {
					w542 = 108.29625;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[26]) {
					w542 = -49.59621;
				} else {
					w542 = -206.75333;
				}
			}
		} else {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[17]) {
					w542 = -1.4615163;
				} else {
					w542 = -144.89125;
				}
			} else {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[0]) {
					w542 = 15.421858;
				} else {
					w542 = 205.64288;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w542 = 37.846874;
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[77]) {
					w542 = 197.91585;
				} else {
					w542 = 54.561913;
				}
			}
		} else {
			w542 = -73.611565;
		}
	}
	float w543;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[45]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w543 = -89.6262;
				} else {
					w543 = 8.846484;
				}
			} else {
				w543 = 21.863085;
			}
		} else {
			w543 = -181.07332;
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[71]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[75]) {
					w543 = -33.376602;
				} else {
					w543 = 80.928276;
				}
			} else {
				w543 = -172.24893;
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[73]) {
					w543 = 1.6133062;
				} else {
					w543 = -102.61813;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w543 = -5.1740456;
				} else {
					w543 = 17.682116;
				}
			}
		}
	}
	float w544;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w544 = -253.00383;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w544 = -22.59692;
				} else {
					w544 = 103.76442;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[80]) {
					w544 = 240.41284;
				} else {
					w544 = -46.643536;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[33]) {
					w544 = -72.584366;
				} else {
					w544 = 7.9128366;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[44]) {
					w544 = 15.72595;
				} else {
					w544 = -8.687102;
				}
			}
		}
	}
	float w545;
	if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[39]) {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[5]) {
					w545 = 0.70846176;
				} else {
					w545 = 65.925255;
				}
			} else {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[2]) {
					w545 = 284.37927;
				} else {
					w545 = 59.423397;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[48]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w545 = -7.128815;
				} else {
					w545 = 223.19489;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[81]) {
					w545 = -102.854416;
				} else {
					w545 = 90.03355;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[42]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[10]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[46]) {
					w545 = -41.46785;
				} else {
					w545 = 52.61582;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w545 = -112.96421;
				} else {
					w545 = -19.63289;
				}
			}
		} else {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
				w545 = 307.32983;
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
					w545 = 91.01906;
				} else {
					w545 = -67.226715;
				}
			}
		}
	}
	float w546;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[42]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w546 = -10.419642;
				} else {
					w546 = 18.437197;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[70]) {
					w546 = -22.430098;
				} else {
					w546 = -221.19214;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w546 = 23.469084;
				} else {
					w546 = -137.62523;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w546 = 566.5453;
				} else {
					w546 = 47.015156;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w546 = 89.86471;
		} else {
			w546 = 218.56839;
		}
	}
	float w547;
	if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
				if (BsmtFullBath != NULL && *BsmtFullBath < cond_BsmtFullBath[0]) {
					w547 = -22.22915;
				} else {
					w547 = -96.71273;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[24]) {
					w547 = -45.948486;
				} else {
					w547 = -293.1908;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
				w547 = 199.93303;
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[34]) {
					w547 = 24.798609;
				} else {
					w547 = -114.237656;
				}
			}
		}
	} else {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[36]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[27]) {
					w547 = -1.3894049;
				} else {
					w547 = 271.7543;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[21]) {
					w547 = 68.52238;
				} else {
					w547 = -196.73828;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[37]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[28]) {
					w547 = 188.9118;
				} else {
					w547 = -47.324894;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[37]) {
					w547 = 129.12321;
				} else {
					w547 = -74.4946;
				}
			}
		}
	}
	float w548;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w548 = -251.023;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w548 = -22.243132;
				} else {
					w548 = 101.65029;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[80]) {
					w548 = 236.013;
				} else {
					w548 = -46.49394;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[33]) {
					w548 = -71.43706;
				} else {
					w548 = 7.73704;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[44]) {
					w548 = 15.50201;
				} else {
					w548 = -8.503386;
				}
			}
		}
	}
	float w549;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[7]) {
					w549 = -52.125305;
				} else {
					w549 = -140.02776;
				}
			} else {
				w549 = 8.844257;
			}
		} else {
			w549 = 21.548203;
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[71]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[14]) {
					w549 = -46.22715;
				} else {
					w549 = 2.404617;
				}
			} else {
				w549 = -170.45265;
			}
		} else {
			if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
					w549 = 221.9523;
				} else {
					w549 = 4.5553613;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
					w549 = -71.10655;
				} else {
					w549 = 41.54541;
				}
			}
		}
	}
	float w550;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[7]) {
					w550 = -9.208451;
				} else {
					w550 = -105.63216;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
					w550 = -83.01125;
				} else {
					w550 = 192.20947;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[6]) {
				if (FullBath != NULL && *FullBath < cond_FullBath[1]) {
					w550 = 255.04004;
				} else {
					w550 = 5.4300604;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w550 = 562.3362;
				} else {
					w550 = 105.32394;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[8]) {
					w550 = 242.3939;
				} else {
					w550 = 22.89249;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[38]) {
					w550 = 233.6564;
				} else {
					w550 = -18.545294;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w550 = 71.76187;
			} else {
				w550 = -292.731;
			}
		}
	}
	float w551;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w551 = -21.618435;
				} else {
					w551 = 115.25568;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w551 = 51.66656;
				} else {
					w551 = -505.44;
				}
			}
		} else {
			if (MiscVal != NULL && *MiscVal < cond_MiscVal[0]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w551 = 9.209326;
				} else {
					w551 = -107.31119;
				}
			} else {
				if (MiscVal != NULL && *MiscVal < cond_MiscVal[1]) {
					w551 = -330.9101;
				} else {
					w551 = -42.90365;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				w551 = 37.25625;
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[51]) {
					w551 = 194.79427;
				} else {
					w551 = 53.394726;
				}
			}
		} else {
			w551 = -72.93929;
		}
	}
	float w552;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w552 = -248.71687;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w552 = -21.923159;
				} else {
					w552 = 100.22705;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[80]) {
					w552 = 232.47588;
				} else {
					w552 = -45.6377;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[33]) {
					w552 = -70.36925;
				} else {
					w552 = 7.716219;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[44]) {
					w552 = 15.248055;
				} else {
					w552 = -8.370166;
				}
			}
		}
	}
	float w553;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[19]) {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[20]) {
					w553 = -3.7829194;
				} else {
					w553 = -46.88656;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w553 = 51.239613;
				} else {
					w553 = -173.68405;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
					w553 = -9.440099;
				} else {
					w553 = 60.363808;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w553 = 558.11224;
				} else {
					w553 = 45.351913;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w553 = 87.41191;
		} else {
			w553 = 216.92215;
		}
	}
	float w554;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
		if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[42]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[13]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[5]) {
					w554 = -8.241274;
				} else {
					w554 = 112.59095;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[11]) {
					w554 = 0.26419157;
				} else {
					w554 = 83.21877;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[48]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[2]) {
					w554 = -29.954062;
				} else {
					w554 = 27.970078;
				}
			} else {
				w554 = -245.4076;
			}
		}
	} else {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[70]) {
				w554 = 161.38191;
			} else {
				w554 = 7.352695;
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[25]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[11]) {
					w554 = -14.753877;
				} else {
					w554 = -117.33187;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[27]) {
					w554 = -77.46922;
				} else {
					w554 = 56.669975;
				}
			}
		}
	}
	float w555;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w555 = -246.76137;
	} else {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[5]) {
					w555 = 1.3139518;
				} else {
					w555 = 64.02525;
				}
			} else {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[2]) {
					w555 = 279.5974;
				} else {
					w555 = 58.513046;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[33]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[49]) {
					w555 = -2.0792918;
				} else {
					w555 = 212.1412;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[24]) {
					w555 = -118.31008;
				} else {
					w555 = -9.721942;
				}
			}
		}
	}
	float w556;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
					w556 = 8.621475;
				} else {
					w556 = 129.6071;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[39]) {
					w556 = 55.54674;
				} else {
					w556 = -229.3561;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[22]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[49]) {
					w556 = -2.9951017;
				} else {
					w556 = 209.48941;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[24]) {
					w556 = -186.89175;
				} else {
					w556 = -9.577643;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
				w556 = 68.328514;
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w556 = -4.573711;
				} else {
					w556 = 11.8828125;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[28]) {
					w556 = -118.68668;
				} else {
					w556 = -36.826355;
				}
			} else {
				w556 = 42.98969;
			}
		}
	}
	float w557;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[3]) {
					w557 = -46.36447;
				} else {
					w557 = -171.00537;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w557 = -62.88724;
				} else {
					w557 = 8.791758;
				}
			}
		} else {
			w557 = 21.28787;
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[71]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[75]) {
					w557 = -32.316284;
				} else {
					w557 = 82.21234;
				}
			} else {
				w557 = -168.46683;
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[73]) {
					w557 = 2.7823992;
				} else {
					w557 = -100.16937;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w557 = -4.9529834;
				} else {
					w557 = 17.030678;
				}
			}
		}
	}
	float w558;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[9]) {
					w558 = -3.164806;
				} else {
					w558 = -59.971077;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
					w558 = 253.67789;
				} else {
					w558 = 13.3402605;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[37]) {
					w558 = 5.697211;
				} else {
					w558 = 126.97473;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w558 = 553.9507;
				} else {
					w558 = 44.681423;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w558 = 43.824024;
				} else {
					w558 = 11.058516;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[77]) {
					w558 = 192.02882;
				} else {
					w558 = 52.571133;
				}
			}
		} else {
			w558 = -72.47047;
		}
	}
	float w559;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[42]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[28]) {
					w559 = -3.70487;
				} else {
					w559 = 65.63521;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[48]) {
					w559 = -1.645;
				} else {
					w559 = -243.26381;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[1]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[79]) {
					w559 = 74.37597;
				} else {
					w559 = 4.046105;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[47]) {
					w559 = 88.135544;
				} else {
					w559 = -156.67424;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w559 = 86.09607;
		} else {
			w559 = 214.49261;
		}
	}
	float w560;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w560 = -244.17245;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w560 = -21.377121;
				} else {
					w560 = 99.30647;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[80]) {
					w560 = 229.02829;
				} else {
					w560 = -45.920624;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[33]) {
					w560 = -68.97262;
				} else {
					w560 = 7.7830453;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[44]) {
					w560 = 14.94047;
				} else {
					w560 = -8.271632;
				}
			}
		}
	}
	float w561;
	if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[39]) {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[5]) {
					w561 = 0.62959903;
				} else {
					w561 = 63.04764;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[69]) {
					w561 = -0.039559152;
				} else {
					w561 = 204.50113;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[48]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w561 = -6.4170165;
				} else {
					w561 = 218.82214;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[81]) {
					w561 = -100.74934;
				} else {
					w561 = 87.65519;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[42]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[10]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[46]) {
					w561 = -42.35414;
				} else {
					w561 = 50.74277;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w561 = -112.37375;
				} else {
					w561 = -20.30461;
				}
			}
		} else {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
				w561 = 301.12756;
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
					w561 = 88.082275;
				} else {
					w561 = -64.89914;
				}
			}
		}
	}
	float w562;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[7]) {
					w562 = -50.413532;
				} else {
					w562 = -136.27608;
				}
			} else {
				w562 = 8.713418;
			}
		} else {
			w562 = 21.06293;
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[71]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[75]) {
					w562 = -31.869833;
				} else {
					w562 = 81.4818;
				}
			} else {
				w562 = -166.47124;
			}
		} else {
			if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
					w562 = 214.81288;
				} else {
					w562 = 4.413936;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[0]) {
					w562 = -69.330765;
				} else {
					w562 = 41.88165;
				}
			}
		}
	}
	float w563;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[42]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[3]) {
					w563 = -9.895415;
				} else {
					w563 = 17.47681;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[70]) {
					w563 = -21.45249;
				} else {
					w563 = -216.74948;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
					w563 = -9.493954;
				} else {
					w563 = 59.06978;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w563 = 549.84845;
				} else {
					w563 = 44.256737;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w563 = 84.98965;
		} else {
			w563 = 212.90813;
		}
	}
	float w564;
	if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[34]) {
		if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[37]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[30]) {
					w564 = -7.597432;
				} else {
					w564 = 203.04028;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[30]) {
					w564 = 20.964184;
				} else {
					w564 = -601.0477;
				}
			}
		} else {
			if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[2]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[14]) {
					w564 = -87.17183;
				} else {
					w564 = 75.797646;
				}
			} else {
				if (YrSold != NULL && *YrSold < cond_YrSold[2]) {
					w564 = 124.32384;
				} else {
					w564 = -129.52757;
				}
			}
		}
	} else {
		if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[46]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[22]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[10]) {
					w564 = 8.332712;
				} else {
					w564 = 261.4336;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[41]) {
					w564 = 239.16312;
				} else {
					w564 = -47.330242;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
					w564 = 26.148447;
				} else {
					w564 = -160.18225;
				}
			} else {
				w564 = -427.56827;
			}
		}
	}
	float w565;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w565 = -241.69476;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w565 = -21.001076;
				} else {
					w565 = 97.825066;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[80]) {
					w565 = 225.32368;
				} else {
					w565 = -46.0124;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[28]) {
					w565 = -8.814498;
				} else {
					w565 = -86.08305;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[44]) {
					w565 = 14.766716;
				} else {
					w565 = -8.159284;
				}
			}
		}
	}
	float w566;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w566 = -20.919777;
				} else {
					w566 = 112.09379;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w566 = 49.673435;
				} else {
					w566 = -497.82404;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[80]) {
					w566 = 6.5803275;
				} else {
					w566 = -60.188187;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[76]) {
					w566 = -182.14253;
				} else {
					w566 = 177.78897;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w566 = 43.44656;
				} else {
					w566 = 10.221797;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[51]) {
					w566 = 189.2284;
				} else {
					w566 = 51.32707;
				}
			}
		} else {
			w566 = -72.05352;
		}
	}
	float w567;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w567 = -239.93144;
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[20]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[7]) {
					w567 = -59.548645;
				} else {
					w567 = -4.136758;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[39]) {
					w567 = -100.674095;
				} else {
					w567 = -296.77023;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[26]) {
					w567 = 78.08977;
				} else {
					w567 = -64.31181;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[43]) {
					w567 = 25.2979;
				} else {
					w567 = -7.3725834;
				}
			}
		}
	}
	float w568;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
		if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w568 = 54.450233;
				} else {
					w568 = 238.0817;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
					w568 = 41.490685;
				} else {
					w568 = -0.9110093;
				}
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[43]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[35]) {
					w568 = -123.01204;
				} else {
					w568 = 88.03148;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[33]) {
					w568 = 72.56695;
				} else {
					w568 = -61.414085;
				}
			}
		}
	} else {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
				w568 = 68.84648;
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w568 = -2.5476563;
				} else {
					w568 = 11.041406;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[28]) {
					w568 = -116.48956;
				} else {
					w568 = -35.425293;
				}
			} else {
				w568 = 43.18086;
			}
		}
	}
	float w569;
	if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
		if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[43]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[79]) {
					w569 = 1.5086311;
				} else {
					w569 = -26.010868;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w569 = -19.478352;
				} else {
					w569 = 158.53345;
				}
			}
		} else {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[50]) {
					w569 = 285.9328;
				} else {
					w569 = 54.04195;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[27]) {
					w569 = -98.45976;
				} else {
					w569 = 85.28581;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[8]) {
					w569 = 237.20433;
				} else {
					w569 = 21.116703;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[38]) {
					w569 = 226.55186;
				} else {
					w569 = -19.161453;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
				w569 = 71.77359;
			} else {
				w569 = -287.94305;
			}
		}
	}
	float w570;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[45]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w570 = -84.21603;
				} else {
					w570 = 8.645801;
				}
			} else {
				w570 = 21.318222;
			}
		} else {
			w570 = -170.83998;
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[71]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[75]) {
					w570 = -31.070522;
				} else {
					w570 = 81.05882;
				}
			} else {
				w570 = -164.6404;
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[73]) {
					w570 = 3.4675217;
				} else {
					w570 = -97.13197;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w570 = -4.8506236;
				} else {
					w570 = 16.51121;
				}
			}
		}
	}
	float w571;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[19]) {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[20]) {
					w571 = -3.959506;
				} else {
					w571 = -45.997192;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w571 = 50.160564;
				} else {
					w571 = -170.53264;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[37]) {
					w571 = 5.3708544;
				} else {
					w571 = 124.52941;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w571 = 545.88043;
				} else {
					w571 = 43.91127;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w571 = 43.183475;
				} else {
					w571 = 9.826992;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[77]) {
					w571 = 186.8098;
				} else {
					w571 = 50.292656;
				}
			}
		} else {
			w571 = -70.94164;
		}
	}
	float w572;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[6]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[42]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[28]) {
					w572 = -3.6082299;
				} else {
					w572 = 64.594086;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[48]) {
					w572 = -3.0657814;
				} else {
					w572 = -239.40715;
				}
			}
		} else {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[70]) {
					w572 = 158.32431;
				} else {
					w572 = 7.497656;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[25]) {
					w572 = -70.28273;
				} else {
					w572 = 44.494328;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w572 = 82.27793;
		} else {
			w572 = 211.71796;
		}
	}
	float w573;
	if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[13]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[2]) {
				if (BsmtFullBath != NULL && *BsmtFullBath < cond_BsmtFullBath[0]) {
					w573 = -19.272486;
				} else {
					w573 = -92.439835;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[29]) {
					w573 = 181.84834;
				} else {
					w573 = 25.867125;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[49]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[52]) {
					w573 = -272.4946;
				} else {
					w573 = -91.97984;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[35]) {
					w573 = -32.31044;
				} else {
					w573 = 118.20304;
				}
			}
		}
	} else {
		if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[82]) {
				if (FullBath != NULL && *FullBath < cond_FullBath[0]) {
					w573 = -0.9923666;
				} else {
					w573 = 140.33366;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[4]) {
					w573 = 206.66985;
				} else {
					w573 = -67.52061;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[37]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[28]) {
					w573 = 180.65341;
				} else {
					w573 = -46.837837;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[37]) {
					w573 = 123.81842;
				} else {
					w573 = -74.13917;
				}
			}
		}
	}
	float w574;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w574 = -236.22151;
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[40]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[33]) {
					w574 = -23.324018;
				} else {
					w574 = 170.41429;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[41]) {
					w574 = 107.068344;
				} else {
					w574 = 0.39374813;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[24]) {
					w574 = -2.1374726;
				} else {
					w574 = 41.9754;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w574 = 541.82086;
				} else {
					w574 = 107.484344;
				}
			}
		}
	}
	float w575;
	if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[34]) {
		if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[37]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[30]) {
					w575 = -7.426952;
				} else {
					w575 = 200.7842;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[30]) {
					w575 = 21.261766;
				} else {
					w575 = -590.8101;
				}
			}
		} else {
			if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[2]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[14]) {
					w575 = -85.586296;
				} else {
					w575 = 74.00155;
				}
			} else {
				if (YrSold != NULL && *YrSold < cond_YrSold[2]) {
					w575 = 121.78185;
				} else {
					w575 = -128.39742;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[44]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[46]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[17]) {
					w575 = 0.0017769048;
				} else {
					w575 = 182.54701;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[44]) {
					w575 = -172.92557;
				} else {
					w575 = 129.30368;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[7]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[53]) {
					w575 = 18.781738;
				} else {
					w575 = 302.76086;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[19]) {
					w575 = -14.448831;
				} else {
					w575 = -154.13504;
				}
			}
		}
	}
	float w576;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w576 = -20.476587;
				} else {
					w576 = 109.22347;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w576 = 47.77828;
				} else {
					w576 = -489.7128;
				}
			}
		} else {
			if (MiscVal != NULL && *MiscVal < cond_MiscVal[0]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w576 = 8.865348;
				} else {
					w576 = -104.81219;
				}
			} else {
				if (MiscVal != NULL && *MiscVal < cond_MiscVal[1]) {
					w576 = -326.79117;
				} else {
					w576 = -41.205833;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w576 = 42.96586;
				} else {
					w576 = 9.71039;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[51]) {
					w576 = 184.58366;
				} else {
					w576 = 49.69582;
				}
			}
		} else {
			w576 = -70.58883;
		}
	}
	float w577;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[42]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[6]) {
					w577 = 2.4256976;
				} else {
					w577 = -26.853664;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[70]) {
					w577 = -20.756777;
				} else {
					w577 = -212.59157;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
					w577 = -9.791067;
				} else {
					w577 = 57.809105;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w577 = 537.74646;
				} else {
					w577 = 41.71383;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w577 = 80.63027;
		} else {
			w577 = 209.61632;
		}
	}
	float w578;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w578 = -234.25922;
	} else {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w578 = 7.0175266;
				} else {
					w578 = -89.74562;
				}
			} else {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[2]) {
					w578 = 272.4214;
				} else {
					w578 = 54.291805;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[33]) {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[5]) {
					w578 = 5.9950676;
				} else {
					w578 = -165.64182;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[24]) {
					w578 = -114.79987;
				} else {
					w578 = -9.730044;
				}
			}
		}
	}
	float w579;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[3]) {
					w579 = -43.03195;
				} else {
					w579 = -163.92987;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w579 = -59.872684;
				} else {
					w579 = 8.883281;
				}
			}
		} else {
			w579 = 21.315878;
		}
	} else {
		if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[0]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
					w579 = -6.7145944;
				} else {
					w579 = 125.256805;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
					w579 = 10.764317;
				} else {
					w579 = 212.4919;
				}
			}
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
					w579 = 68.74055;
				} else {
					w579 = 5.295;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[36]) {
					w579 = -92.807724;
				} else {
					w579 = 42.737736;
				}
			}
		}
	}
	float w580;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[43]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[79]) {
					w580 = 2.714635;
				} else {
					w580 = -22.525124;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[49]) {
					w580 = 44.59508;
				} else {
					w580 = 311.26627;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[22]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[45]) {
					w580 = -136.72351;
				} else {
					w580 = 65.32536;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[47]) {
					w580 = 303.6741;
				} else {
					w580 = 75.15464;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			w580 = 145.93593;
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				w580 = -74.04941;
			} else {
				w580 = -287.1257;
			}
		}
	}
	float w581;
	if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[34]) {
		if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[37]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[30]) {
					w581 = -7.375389;
				} else {
					w581 = 198.65929;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[30]) {
					w581 = 21.129053;
				} else {
					w581 = -580.77094;
				}
			}
		} else {
			if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[2]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[14]) {
					w581 = -83.90025;
				} else {
					w581 = 72.60462;
				}
			} else {
				if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[3]) {
					w581 = 123.84729;
				} else {
					w581 = -93.994804;
				}
			}
		}
	} else {
		if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[46]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[22]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[10]) {
					w581 = 8.104423;
				} else {
					w581 = 251.13014;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[41]) {
					w581 = 233.16095;
				} else {
					w581 = -47.57796;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
					w581 = 26.262589;
				} else {
					w581 = -157.18329;
				}
			} else {
				w581 = -419.49506;
			}
		}
	}
	float w582;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w582 = -232.35867;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w582 = -21.160189;
				} else {
					w582 = 95.07605;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[80]) {
					w582 = 219.519;
				} else {
					w582 = -43.993763;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[33]) {
					w582 = -66.48541;
				} else {
					w582 = 8.386044;
				}
			} else {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[6]) {
					w582 = 1.3830603;
				} else {
					w582 = 173.1881;
				}
			}
		}
	}
	float w583;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w583 = -20.147726;
				} else {
					w583 = 106.69254;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w583 = 46.72078;
				} else {
					w583 = -481.9839;
				}
			}
		} else {
			if (MiscVal != NULL && *MiscVal < cond_MiscVal[0]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w583 = 8.704281;
				} else {
					w583 = -102.84905;
				}
			} else {
				if (MiscVal != NULL && *MiscVal < cond_MiscVal[1]) {
					w583 = -322.5415;
				} else {
					w583 = -40.12905;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w583 = 42.524178;
				} else {
					w583 = 9.651211;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[77]) {
					w583 = 182.37796;
				} else {
					w583 = 48.85418;
				}
			}
		} else {
			w583 = -69.70937;
		}
	}
	float w584;
	if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			w584 = -130.12558;
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[19]) {
				w584 = 234.49553;
			} else {
				w584 = 63.302578;
			}
		}
	} else {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w584 = 6.076527;
				} else {
					w584 = -88.45435;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[69]) {
					w584 = -1.3440402;
				} else {
					w584 = 198.66566;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[33]) {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[5]) {
					w584 = 4.4053;
				} else {
					w584 = -162.58524;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[24]) {
					w584 = -113.24854;
				} else {
					w584 = -9.66827;
				}
			}
		}
	}
	float w585;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[45]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w585 = -81.60871;
				} else {
					w585 = 8.7429495;
				}
			} else {
				w585 = 21.069784;
			}
		} else {
			w585 = -165.65987;
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[37]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[36]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[23]) {
					w585 = 17.373177;
				} else {
					w585 = -194.67204;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[7]) {
					w585 = 302.601;
				} else {
					w585 = 41.676113;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[46]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[83]) {
					w585 = -41.043106;
				} else {
					w585 = -499.6737;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[48]) {
					w585 = -5.038841;
				} else {
					w585 = 31.633816;
				}
			}
		}
	}
	float w586;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w586 = -230.6891;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w586 = -20.838804;
				} else {
					w586 = 93.68586;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[80]) {
					w586 = 216.41602;
				} else {
					w586 = -42.808025;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[28]) {
					w586 = -7.513325;
				} else {
					w586 = -83.30179;
				}
			} else {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[6]) {
					w586 = 1.3282126;
				} else {
					w586 = 171.0794;
				}
			}
		}
	}
	float w587;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[12]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[42]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[13]) {
					w587 = -0.79673946;
				} else {
					w587 = -88.44635;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[48]) {
					w587 = -4.505625;
				} else {
					w587 = -231.46912;
				}
			}
		} else {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[47]) {
					w587 = 170.56847;
				} else {
					w587 = 6.3290625;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[34]) {
					w587 = -54.478336;
				} else {
					w587 = 45.249718;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w587 = 78.15574;
		} else {
			w587 = 207.46112;
		}
	}
	float w588;
	if (LotArea != NULL && *LotArea < cond_LotArea[71]) {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[75]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[54]) {
					w588 = -22.899046;
				} else {
					w588 = -98.177025;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[84]) {
					w588 = 133.13062;
				} else {
					w588 = -10.514999;
				}
			}
		} else {
			w588 = -163.06355;
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[51]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[25]) {
					w588 = -12.09519;
				} else {
					w588 = -80.37716;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[45]) {
					w588 = 31.806408;
				} else {
					w588 = -210.5231;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[47]) {
					w588 = 20.142193;
				} else {
					w588 = -264.20935;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[23]) {
					w588 = 18.14554;
				} else {
					w588 = -175.09064;
				}
			}
		}
	}
	float w589;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[1]) {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[85]) {
					w589 = -2.8089426;
				} else {
					w589 = 27.88709;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[39]) {
					w589 = 56.69832;
				} else {
					w589 = -222.18231;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[22]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[49]) {
					w589 = -2.4524183;
				} else {
					w589 = 202.98901;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[24]) {
					w589 = -180.1039;
				} else {
					w589 = -9.527805;
				}
			}
		}
	} else {
		if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[2]) {
			w589 = -165.4382;
		} else {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
					w589 = 33.369743;
				} else {
					w589 = -38.581482;
				}
			} else {
				w589 = -124.376366;
			}
		}
	}
	float w590;
	if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[39]) {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[5]) {
					w590 = 0.41315302;
				} else {
					w590 = 60.46847;
				}
			} else {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[2]) {
					w590 = 266.72437;
				} else {
					w590 = 50.884922;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[48]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[46]) {
					w590 = -37.21294;
				} else {
					w590 = 14.432976;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[81]) {
					w590 = -98.359024;
				} else {
					w590 = 83.63353;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[42]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[10]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[46]) {
					w590 = -45.73711;
				} else {
					w590 = 48.025703;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w590 = -111.74961;
				} else {
					w590 = -21.52617;
				}
			}
		} else {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
				w590 = 290.52145;
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[4]) {
					w590 = 84.1882;
				} else {
					w590 = -64.53164;
				}
			}
		}
	}
	float w591;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w591 = -228.41354;
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[20]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
					w591 = -44.709675;
				} else {
					w591 = -0.9667068;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[39]) {
					w591 = -99.522514;
				} else {
					w591 = -293.44592;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[80]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[35]) {
					w591 = 6.4993777;
				} else {
					w591 = 105.02513;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w591 = -113.66011;
				} else {
					w591 = 3.331899;
				}
			}
		}
	}
	float w592;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[42]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[29]) {
					w592 = -4.865825;
				} else {
					w592 = 70.41581;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[70]) {
					w592 = -20.124756;
				} else {
					w592 = -209.98824;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[9]) {
					w592 = -9.820552;
				} else {
					w592 = 56.820404;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w592 = 532.0978;
				} else {
					w592 = 38.30795;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w592 = 77.06156;
		} else {
			w592 = 205.51688;
		}
	}
	float w593;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[43]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[79]) {
					w593 = 2.729674;
				} else {
					w593 = -22.3697;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[49]) {
					w593 = 42.913734;
				} else {
					w593 = 305.88858;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[22]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[45]) {
					w593 = -135.18411;
				} else {
					w593 = 63.43202;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[47]) {
					w593 = 297.8721;
				} else {
					w593 = 73.08153;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			w593 = 142.86937;
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				w593 = -72.37597;
			} else {
				w593 = -280.25836;
			}
		}
	}
	float w594;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[41]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[22]) {
					w594 = -39.786938;
				} else {
					w594 = 25.554768;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
					w594 = -182.0652;
				} else {
					w594 = -11.222109;
				}
			}
		} else {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[24]) {
					w594 = -0.34950614;
				} else {
					w594 = -74.46688;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
					w594 = -32.263813;
				} else {
					w594 = 66.523994;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w594 = 42.449295;
				} else {
					w594 = 8.974805;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[77]) {
					w594 = 179.31848;
				} else {
					w594 = 47.612694;
				}
			}
		} else {
			w594 = -69.38851;
		}
	}
	float w595;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[45]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w595 = -80.200714;
				} else {
					w595 = 9.087539;
				}
			} else {
				w595 = 21.042421;
			}
		} else {
			w595 = -163.56621;
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
					w595 = -24.324617;
				} else {
					w595 = -334.268;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[41]) {
					w595 = 6.121084;
				} else {
					w595 = -145.30666;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
				if (FullBath != NULL && *FullBath < cond_FullBath[1]) {
					w595 = 239.356;
				} else {
					w595 = 7.2936206;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w595 = 528.0893;
				} else {
					w595 = 102.258835;
				}
			}
		}
	}
	float w596;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w596 = -226.5484;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w596 = -20.155949;
				} else {
					w596 = 92.47642;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[80]) {
					w596 = 212.79465;
				} else {
					w596 = -43.20733;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[28]) {
					w596 = -7.138543;
				} else {
					w596 = -81.95336;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[44]) {
					w596 = 13.991071;
				} else {
					w596 = -7.91029;
				}
			}
		}
	}
	float w597;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[43]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[79]) {
					w597 = 2.6802683;
				} else {
					w597 = -21.991817;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[49]) {
					w597 = 42.253174;
				} else {
					w597 = 302.0728;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[22]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[45]) {
					w597 = -133.31685;
				} else {
					w597 = 62.559074;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[47]) {
					w597 = 294.14807;
				} else {
					w597 = 71.961105;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			w597 = 141.06062;
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				w597 = -71.59191;
			} else {
				w597 = -277.71973;
			}
		}
	}
	float w598;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[12]) {
		if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[42]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[28]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[54]) {
					w598 = -0.39992163;
				} else {
					w598 = -98.29744;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[52]) {
					w598 = 118.86514;
				} else {
					w598 = -39.45334;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[48]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[2]) {
					w598 = -32.90461;
				} else {
					w598 = 27.207188;
				}
			} else {
				w598 = -228.61092;
			}
		}
	} else {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[47]) {
				w598 = 168.58098;
			} else {
				w598 = 6.5892186;
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[34]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[11]) {
					w598 = -13.222316;
				} else {
					w598 = -111.22505;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[27]) {
					w598 = -76.23344;
				} else {
					w598 = 55.560524;
				}
			}
		}
	}
	float w599;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[12]) {
			if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[13]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
					w599 = 9.583677;
				} else {
					w599 = -12.368171;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[55]) {
					w599 = 19.555279;
				} else {
					w599 = -320.92804;
				}
			}
		} else {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[47]) {
					w599 = 166.41354;
				} else {
					w599 = 6.523281;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[34]) {
					w599 = -53.191544;
				} else {
					w599 = 44.072887;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w599 = 76.32228;
		} else {
			w599 = 203.94504;
		}
	}
	float w600;
	if (LotArea != NULL && *LotArea < cond_LotArea[71]) {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[75]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[54]) {
					w600 = -22.4902;
				} else {
					w600 = -97.13165;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[84]) {
					w600 = 132.49852;
				} else {
					w600 = -9.07371;
				}
			}
		} else {
			w600 = -159.55003;
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[23]) {
					w600 = -11.117985;
				} else {
					w600 = 134.42061;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[38]) {
					w600 = -39.08953;
				} else {
					w600 = 231.21375;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[47]) {
					w600 = 19.712088;
				} else {
					w600 = -258.83664;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[23]) {
					w600 = 18.051125;
				} else {
					w600 = -171.99022;
				}
			}
		}
	}
	float w601;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[45]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w601 = -79.27098;
				} else {
					w601 = 8.908828;
				}
			} else {
				w601 = 20.774061;
			}
		} else {
			w601 = -161.86278;
		}
	} else {
		if (LotArea != NULL && *LotArea < cond_LotArea[71]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[75]) {
					w601 = -29.535072;
				} else {
					w601 = 81.66609;
				}
			} else {
				w601 = -157.55571;
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[37]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
					w601 = 38.264423;
				} else {
					w601 = -81.17652;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[46]) {
					w601 = -273.02652;
				} else {
					w601 = 0.6929835;
				}
			}
		}
	}
	float w602;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[1]) {
		if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[7]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[34]) {
					w602 = -0.7898064;
				} else {
					w602 = 73.54731;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[46]) {
					w602 = -2.5545766;
				} else {
					w602 = -165.28389;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[21]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[69]) {
					w602 = -0.35148925;
				} else {
					w602 = 199.51077;
				}
			} else {
				w602 = -182.27827;
			}
		}
	} else {
		if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[2]) {
			w602 = -163.48723;
		} else {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
					w602 = 32.97627;
				} else {
					w602 = -37.45811;
				}
			} else {
				w602 = -121.8774;
			}
		}
	}
	float w603;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[39]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[71]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[27]) {
					w603 = -4.2235436;
				} else {
					w603 = 208.12398;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[56]) {
					w603 = -113.14787;
				} else {
					w603 = 228.775;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[8]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[21]) {
					w603 = 143.24808;
				} else {
					w603 = -8.389289;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[53]) {
					w603 = 274.58472;
				} else {
					w603 = 51.416718;
				}
			}
		}
	} else {
		if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[1]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[11]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[9]) {
					w603 = -8.689665;
				} else {
					w603 = 148.03592;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w603 = 105.4277;
				} else {
					w603 = -188.11324;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[48]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[63]) {
					w603 = 28.663944;
				} else {
					w603 = 112.091156;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[49]) {
					w603 = -372.23096;
				} else {
					w603 = -66.07609;
				}
			}
		}
	}
	float w604;
	if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			w604 = -130.06224;
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[19]) {
				w604 = 227.66382;
			} else {
				w604 = 60.82437;
			}
		}
	} else {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w604 = 5.842327;
				} else {
					w604 = -85.41513;
				}
			} else {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[2]) {
					w604 = 260.92258;
				} else {
					w604 = 49.13987;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[33]) {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[5]) {
					w604 = 4.3564863;
				} else {
					w604 = -157.84201;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[24]) {
					w604 = -109.57053;
				} else {
					w604 = -9.541192;
				}
			}
		}
	}
	float w605;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[20]) {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[7]) {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[9]) {
					w605 = -73.18686;
				} else {
					w605 = 92.436264;
				}
			} else {
				if (MiscVal != NULL && *MiscVal < cond_MiscVal[0]) {
					w605 = 0.52221173;
				} else {
					w605 = -81.76229;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[39]) {
				w605 = -98.363106;
			} else {
				w605 = -291.02817;
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[80]) {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[35]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[4]) {
					w605 = -27.902483;
				} else {
					w605 = 77.85997;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[71]) {
					w605 = 77.17319;
				} else {
					w605 = 232.32901;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[29]) {
					w605 = -202.4482;
				} else {
					w605 = 21.269598;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
					w605 = -65.467926;
				} else {
					w605 = 5.03331;
				}
			}
		}
	}
	float w606;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w606 = -19.560005;
				} else {
					w606 = 103.104355;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w606 = 48.57445;
				} else {
					w606 = -470.42734;
				}
			}
		} else {
			if (MiscVal != NULL && *MiscVal < cond_MiscVal[0]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[1]) {
					w606 = 8.401566;
				} else {
					w606 = -99.220535;
				}
			} else {
				if (MiscVal != NULL && *MiscVal < cond_MiscVal[1]) {
					w606 = -313.48367;
				} else {
					w606 = -38.825665;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w606 = 41.679844;
				} else {
					w606 = 7.6258593;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[51]) {
					w606 = 176.1871;
				} else {
					w606 = 45.367264;
				}
			}
		} else {
			w606 = -68.40242;
		}
	}
	float w607;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[43]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[79]) {
					w607 = 2.6209412;
				} else {
					w607 = -21.61464;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[49]) {
					w607 = 40.657627;
				} else {
					w607 = 296.6828;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[22]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[45]) {
					w607 = -131.46321;
				} else {
					w607 = 61.48915;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[47]) {
					w607 = 289.54648;
				} else {
					w607 = 70.970406;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			w607 = 137.40984;
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				w607 = -302.05344;
			} else {
				w607 = -98.02593;
			}
		}
	}
	float w608;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w608 = -221.83113;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w608 = -19.7147;
				} else {
					w608 = 91.38999;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[80]) {
					w608 = 209.29378;
				} else {
					w608 = -41.286263;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[33]) {
					w608 = -63.711693;
				} else {
					w608 = 9.813254;
				}
			} else {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[6]) {
					w608 = 1.1321206;
				} else {
					w608 = 168.52339;
				}
			}
		}
	}
	float w609;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[27]) {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[17]) {
					w609 = -2.1762934;
				} else {
					w609 = -127.90804;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
					w609 = -30.788504;
				} else {
					w609 = 72.01054;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
				w609 = -205.00833;
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[57]) {
					w609 = -73.7823;
				} else {
					w609 = 39.52424;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w609 = 74.259315;
		} else {
			w609 = 201.30504;
		}
	}
	float w610;
	if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			w610 = -128.98956;
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[19]) {
				w610 = 225.14656;
			} else {
				w610 = 60.648907;
			}
		}
	} else {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[36]) {
					w610 = -8.531897;
				} else {
					w610 = 18.278666;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[69]) {
					w610 = -5.221222;
				} else {
					w610 = 189.65276;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[33]) {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[5]) {
					w610 = 4.3649015;
				} else {
					w610 = -154.9655;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[24]) {
					w610 = -107.99163;
				} else {
					w610 = -9.747017;
				}
			}
		}
	}
	float w611;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[43]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
					w611 = -10.925629;
				} else {
					w611 = 9.753659;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w611 = -18.126202;
				} else {
					w611 = 164.44485;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[8]) {
					w611 = 225.39052;
				} else {
					w611 = 16.09664;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[38]) {
					w611 = 209.94531;
				} else {
					w611 = -20.552353;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			w611 = 135.76688;
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				w611 = -299.80673;
			} else {
				w611 = -97.15204;
			}
		}
	}
	float w612;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w612 = -220.16026;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w612 = -19.359241;
				} else {
					w612 = 90.039444;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[1]) {
					w612 = 267.40112;
				} else {
					w612 = 39.09976;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[33]) {
					w612 = -62.72481;
				} else {
					w612 = 9.724748;
				}
			} else {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[6]) {
					w612 = 1.1080685;
				} else {
					w612 = 166.39539;
				}
			}
		}
	}
	float w613;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w613 = -19.121622;
				} else {
					w613 = 100.90901;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w613 = 47.7607;
				} else {
					w613 = -465.67465;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[80]) {
					w613 = 6.1700487;
				} else {
					w613 = -58.444675;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[76]) {
					w613 = -179.63226;
				} else {
					w613 = 167.02382;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[0]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w613 = 41.24121;
				} else {
					w613 = 7.7035546;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[51]) {
					w613 = 173.95964;
				} else {
					w613 = 44.97832;
				}
			}
		} else {
			w613 = -67.43633;
		}
	}
	float w614;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[45]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w614 = -77.4089;
				} else {
					w614 = 8.762813;
				}
			} else {
				w614 = 21.17748;
			}
		} else {
			w614 = -158.95857;
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[49]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[50]) {
					w614 = -4.9767647;
				} else {
					w614 = 280.8549;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[37]) {
					w614 = 0.99166816;
				} else {
					w614 = -239.24367;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
				if (FullBath != NULL && *FullBath < cond_FullBath[1]) {
					w614 = 231.7689;
				} else {
					w614 = 6.963831;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w614 = 523.99475;
				} else {
					w614 = 100.42388;
				}
			}
		}
	}
	float w615;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w615 = -218.60765;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w615 = -19.123192;
				} else {
					w615 = 88.63496;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[80]) {
					w615 = 203.89874;
				} else {
					w615 = -41.42722;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[28]) {
					w615 = -5.6568103;
				} else {
					w615 = -79.26387;
				}
			} else {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[6]) {
					w615 = 1.1017532;
				} else {
					w615 = 164.38853;
				}
			}
		}
	}
	float w616;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[39]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[71]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[27]) {
					w616 = -4.110435;
				} else {
					w616 = 203.30292;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[56]) {
					w616 = -110.807236;
				} else {
					w616 = 222.30827;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[8]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[21]) {
					w616 = 140.51414;
				} else {
					w616 = -7.987172;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[53]) {
					w616 = 268.0017;
				} else {
					w616 = 49.196716;
				}
			}
		}
	} else {
		if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[1]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[11]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[9]) {
					w616 = -8.529143;
				} else {
					w616 = 145.7414;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w616 = 103.01453;
				} else {
					w616 = -184.65579;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[38]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[50]) {
					w616 = 62.65336;
				} else {
					w616 = -67.523285;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[54]) {
					w616 = -311.20468;
				} else {
					w616 = 51.051796;
				}
			}
		}
	}
	float w617;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[27]) {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[15]) {
					w617 = -1.3077788;
				} else {
					w617 = -70.41318;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
					w617 = -30.22962;
				} else {
					w617 = 70.783264;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
				w617 = -202.96394;
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[57]) {
					w617 = -72.19527;
				} else {
					w617 = 38.698826;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w617 = 72.396324;
		} else {
			w617 = 199.18172;
		}
	}
	float w618;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[16]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
					w618 = -25.847178;
				} else {
					w618 = 2.137302;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
					w618 = 239.83719;
				} else {
					w618 = 9.147083;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[22]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[45]) {
					w618 = -129.4004;
				} else {
					w618 = 59.845562;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[47]) {
					w618 = 283.6125;
				} else {
					w618 = 68.307625;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			w618 = 132.22078;
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				w618 = -296.44205;
			} else {
				w618 = -94.95469;
			}
		}
	}
	float w619;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[41]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[22]) {
					w619 = -37.65541;
				} else {
					w619 = 25.655848;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
					w619 = -176.53702;
				} else {
					w619 = -10.201172;
				}
			}
		} else {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[24]) {
					w619 = -0.31171995;
				} else {
					w619 = -72.055244;
				}
			} else {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[0]) {
					w619 = 13.037603;
				} else {
					w619 = 190.47972;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[36]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[2]) {
					w619 = 74.64516;
				} else {
					w619 = 7.699453;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[51]) {
					w619 = 203.37856;
				} else {
					w619 = 44.104218;
				}
			}
		} else {
			w619 = -66.403206;
		}
	}
	float w620;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w620 = -216.94113;
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[40]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[41]) {
					w620 = -21.913656;
				} else {
					w620 = 149.87257;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[41]) {
					w620 = 104.7511;
				} else {
					w620 = -0.03515652;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w620 = -10.255816;
				} else {
					w620 = 25.376173;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w620 = 520.08374;
				} else {
					w620 = 99.311455;
				}
			}
		}
	}
	float w621;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[43]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[79]) {
					w621 = 2.386185;
				} else {
					w621 = -21.941181;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w621 = -18.555477;
				} else {
					w621 = 160.88208;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[14]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[39]) {
					w621 = -129.04828;
				} else {
					w621 = 94.6332;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
					w621 = 271.01157;
				} else {
					w621 = 53.592377;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			w621 = 130.83531;
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				w621 = -293.60764;
			} else {
				w621 = -93.76854;
			}
		}
	}
	float w622;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[45]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w622 = -75.98733;
				} else {
					w622 = 8.862187;
				}
			} else {
				w622 = 21.18375;
			}
		} else {
			w622 = -157.1733;
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[37]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[36]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[39]) {
					w622 = 15.279069;
				} else {
					w622 = -221.89874;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[7]) {
					w622 = 296.3346;
				} else {
					w622 = 38.700447;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[46]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[83]) {
					w622 = -37.33951;
				} else {
					w622 = -481.6597;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[48]) {
					w622 = -4.8302417;
				} else {
					w622 = 30.826782;
				}
			}
		}
	}
	float w623;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[1]) {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[32]) {
					w623 = -1.9476461;
				} else {
					w623 = 27.705696;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[39]) {
					w623 = 57.657055;
				} else {
					w623 = -215.44476;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[22]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[49]) {
					w623 = -1.9859992;
				} else {
					w623 = 194.16605;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[24]) {
					w623 = -172.91168;
				} else {
					w623 = -10.210572;
				}
			}
		}
	} else {
		if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[2]) {
			w623 = -160.06082;
		} else {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
					w623 = 33.654903;
				} else {
					w623 = -36.32375;
				}
			} else {
				w623 = -115.79648;
			}
		}
	}
	float w624;
	if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[34]) {
		if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[20]) {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[65]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[14]) {
					w624 = -2.8723745;
				} else {
					w624 = -71.524956;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[42]) {
					w624 = -212.25798;
				} else {
					w624 = 366.64264;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[38]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[75]) {
					w624 = -136.75797;
				} else {
					w624 = 119.413765;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[86]) {
					w624 = -189.00609;
				} else {
					w624 = 13.100079;
				}
			}
		}
	} else {
		if (GarageArea != NULL && *GarageArea < cond_GarageArea[44]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[46]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[17]) {
					w624 = -0.071361266;
				} else {
					w624 = 181.83076;
				}
			} else {
				if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[44]) {
					w624 = -172.72868;
				} else {
					w624 = 123.868515;
				}
			}
		} else {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[7]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[53]) {
					w624 = 17.267548;
				} else {
					w624 = 284.64227;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[19]) {
					w624 = -15.057509;
				} else {
					w624 = -148.5959;
				}
			}
		}
	}
	float w625;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w625 = -215.29956;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[55]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[6]) {
					w625 = 35.04719;
				} else {
					w625 = -72.7057;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[34]) {
					w625 = 13.176192;
				} else {
					w625 = 202.34232;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[28]) {
					w625 = -5.1959643;
				} else {
					w625 = -78.098595;
				}
			} else {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[6]) {
					w625 = 1.044119;
				} else {
					w625 = 161.65863;
				}
			}
		}
	}
	float w626;
	if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			w626 = -127.47908;
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[19]) {
				w626 = 220.06201;
			} else {
				w626 = 58.62625;
			}
		}
	} else {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[5]) {
					w626 = 0.3100637;
				} else {
					w626 = 55.20135;
				}
			} else {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[2]) {
					w626 = 253.5807;
				} else {
					w626 = 45.137566;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[48]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
					w626 = -9.26151;
				} else {
					w626 = 82.190056;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[28]) {
					w626 = 1.1788744;
				} else {
					w626 = -134.05301;
				}
			}
		}
	}
	float w627;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[27]) {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[17]) {
					w627 = -2.0305307;
				} else {
					w627 = -123.959526;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
					w627 = -29.977125;
				} else {
					w627 = 69.04725;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
				w627 = -200.12865;
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[56]) {
					w627 = -107.83585;
				} else {
					w627 = 7.486674;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w627 = 71.23359;
		} else {
			w627 = 196.08762;
		}
	}
	float w628;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[43]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[79]) {
					w628 = 2.3934338;
				} else {
					w628 = -21.785181;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w628 = -18.43001;
				} else {
					w628 = 157.71573;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[8]) {
					w628 = 218.07294;
				} else {
					w628 = 14.635554;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[38]) {
					w628 = 204.99843;
				} else {
					w628 = -20.617792;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			w628 = 129.26688;
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				w628 = -290.31857;
			} else {
				w628 = -92.63438;
			}
		}
	}
	float w629;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[41]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[73]) {
					w629 = -27.907063;
				} else {
					w629 = 103.020935;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
					w629 = -174.08842;
				} else {
					w629 = -9.873164;
				}
			}
		} else {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[24]) {
					w629 = -0.26439804;
				} else {
					w629 = -70.69118;
				}
			} else {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[0]) {
					w629 = 12.552234;
				} else {
					w629 = 185.57162;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[36]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[2]) {
					w629 = 73.530876;
				} else {
					w629 = 7.921875;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[51]) {
					w629 = 200.3435;
				} else {
					w629 = 43.615196;
				}
			}
		} else {
			w629 = -65.96015;
		}
	}
	float w630;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w630 = -213.50659;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w630 = -18.613882;
				} else {
					w630 = 87.26325;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[1]) {
					w630 = 257.46042;
				} else {
					w630 = 35.79376;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[33]) {
					w630 = -60.671864;
				} else {
					w630 = 10.777205;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[44]) {
					w630 = 13.178988;
				} else {
					w630 = -7.6849647;
				}
			}
		}
	}
	float w631;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[45]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w631 = -75.26522;
				} else {
					w631 = 8.794219;
				}
			} else {
				w631 = 20.95125;
			}
		} else {
			w631 = -155.1949;
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[49]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[50]) {
					w631 = -4.7638054;
				} else {
					w631 = 276.57312;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[37]) {
					w631 = 0.30642807;
				} else {
					w631 = -234.07669;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
				if (FullBath != NULL && *FullBath < cond_FullBath[1]) {
					w631 = 225.99457;
				} else {
					w631 = 6.6617327;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w631 = 516.0619;
				} else {
					w631 = 98.19832;
				}
			}
		}
	}
	float w632;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[27]) {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[17]) {
					w632 = -1.970911;
				} else {
					w632 = -121.25551;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
					w632 = -29.643215;
				} else {
					w632 = 67.74958;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
				w632 = -197.75443;
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[56]) {
					w632 = -106.74203;
				} else {
					w632 = 7.495145;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w632 = 70.39681;
		} else {
			w632 = 194.6087;
		}
	}
	float w633;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w633 = -211.9405;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[55]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[6]) {
					w633 = 34.43245;
				} else {
					w633 = -71.71757;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[34]) {
					w633 = 12.272017;
				} else {
					w633 = 197.7323;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[28]) {
					w633 = -4.551797;
				} else {
					w633 = -76.74566;
				}
			} else {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[6]) {
					w633 = 1.0253732;
				} else {
					w633 = 159.82825;
				}
			}
		}
	}
	float w634;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[43]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[79]) {
					w634 = 2.3942218;
				} else {
					w634 = -21.540361;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w634 = -18.201248;
				} else {
					w634 = 154.98766;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[14]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[39]) {
					w634 = -127.30494;
				} else {
					w634 = 92.37117;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[51]) {
					w634 = 30.361307;
				} else {
					w634 = 161.5152;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			w634 = 127.46359;
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				w634 = -288.10452;
			} else {
				w634 = -90.74672;
			}
		}
	}
	float w635;
	if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[52]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w635 = -66.07558;
				} else {
					w635 = 33.256054;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[32]) {
					w635 = -218.77982;
				} else {
					w635 = -27.213339;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[28]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[6]) {
					w635 = -39.164425;
				} else {
					w635 = 61.987556;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
					w635 = 74.25683;
				} else {
					w635 = 1.1183593;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
			if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[51]) {
					w635 = -170.48692;
				} else {
					w635 = -29.212149;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[1]) {
					w635 = 136.41086;
				} else {
					w635 = -33.977383;
				}
			}
		} else {
			if (YrSold != NULL && *YrSold < cond_YrSold[1]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w635 = 16.333479;
				} else {
					w635 = -130.55615;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[38]) {
					w635 = 5.263694;
				} else {
					w635 = -32.79877;
				}
			}
		}
	}
	float w636;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[12]) {
		if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[42]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[28]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[54]) {
					w636 = -0.33526808;
				} else {
					w636 = -93.18564;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[52]) {
					w636 = 114.17412;
				} else {
					w636 = -40.06066;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[48]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[2]) {
					w636 = -31.349062;
				} else {
					w636 = 26.951015;
				}
			} else {
				w636 = -222.4345;
			}
		}
	} else {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[47]) {
				w636 = 164.9415;
			} else {
				w636 = 6.391562;
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[34]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[39]) {
					w636 = -12.51971;
				} else {
					w636 = -111.21331;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[27]) {
					w636 = -74.332886;
				} else {
					w636 = 52.295715;
				}
			}
		}
	}
	float w637;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w637 = -18.21913;
				} else {
					w637 = 97.03102;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w637 = 46.483124;
				} else {
					w637 = -459.89038;
				}
			}
		} else {
			if (MiscVal != NULL && *MiscVal < cond_MiscVal[0]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[66]) {
					w637 = 11.467504;
				} else {
					w637 = -26.12907;
				}
			} else {
				if (MiscVal != NULL && *MiscVal < cond_MiscVal[1]) {
					w637 = -307.72592;
				} else {
					w637 = -37.100044;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[36]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[2]) {
					w637 = 72.456856;
				} else {
					w637 = 7.6422653;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[51]) {
					w637 = 197.5875;
				} else {
					w637 = 43.188046;
				}
			}
		} else {
			w637 = -65.36273;
		}
	}
	float w638;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[27]) {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[26]) {
					w638 = -4.125731;
				} else {
					w638 = 87.12016;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
					w638 = -29.141718;
				} else {
					w638 = 67.02513;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
				w638 = -195.23256;
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[56]) {
					w638 = -104.47719;
				} else {
					w638 = 8.223281;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w638 = 69.79025;
		} else {
			w638 = 193.19942;
		}
	}
	float w639;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[43]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
					w639 = -3.474681;
				} else {
					w639 = 96.42638;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w639 = -18.996454;
				} else {
					w639 = 152.18938;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[14]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[39]) {
					w639 = -125.61398;
				} else {
					w639 = 91.30773;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[51]) {
					w639 = 30.022045;
				} else {
					w639 = 159.07614;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			w639 = 125.60561;
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				w639 = -285.48904;
			} else {
				w639 = -90.140854;
			}
		}
	}
	float w640;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w640 = -210.05647;
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
					w640 = -22.816856;
				} else {
					w640 = -318.7558;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[41]) {
					w640 = 5.303879;
				} else {
					w640 = -137.30937;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[24]) {
					w640 = -2.3966076;
				} else {
					w640 = 38.389698;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w640 = 512.0313;
				} else {
					w640 = 96.61658;
				}
			}
		}
	}
	float w641;
	if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			w641 = -126.26982;
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[19]) {
				w641 = 215.91635;
			} else {
				w641 = 57.570778;
			}
		}
	} else {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[25]) {
					w641 = -6.4860916;
				} else {
					w641 = 19.97754;
				}
			} else {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[2]) {
					w641 = 249.44615;
				} else {
					w641 = 43.177364;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[48]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[34]) {
					w641 = -8.803573;
				} else {
					w641 = 79.55935;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[28]) {
					w641 = 0.20604342;
				} else {
					w641 = -132.19205;
				}
			}
		}
	}
	float w642;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[45]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w642 = -73.68307;
				} else {
					w642 = 8.677675;
				}
			} else {
				w642 = 20.643105;
			}
		} else {
			w642 = -152.54694;
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[40]) {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[4]) {
					w642 = 6.769963;
				} else {
					w642 = 82.42236;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w642 = 9.206133;
				} else {
					w642 = -234.4991;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[1]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[53]) {
					w642 = -83.00879;
				} else {
					w642 = -6.1735272;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[81]) {
					w642 = 26.374975;
				} else {
					w642 = 297.92963;
				}
			}
		}
	}
	float w643;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[43]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[79]) {
					w643 = 2.3835676;
				} else {
					w643 = -21.128126;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w643 = -18.372355;
				} else {
					w643 = 150.02063;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[14]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[39]) {
					w643 = -124.00484;
				} else {
					w643 = 90.09867;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
					w643 = 259.5963;
				} else {
					w643 = 50.796436;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			w643 = 123.11515;
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				w643 = -283.16937;
			} else {
				w643 = -89.41245;
			}
		}
	}
	float w644;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[39]) {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[5]) {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[71]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[27]) {
					w644 = -3.931071;
				} else {
					w644 = 198.69957;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[1]) {
					w644 = -182.61107;
				} else {
					w644 = -18.064903;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[8]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[21]) {
					w644 = 135.35141;
				} else {
					w644 = -8.194336;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[53]) {
					w644 = 261.017;
				} else {
					w644 = 46.002655;
				}
			}
		}
	} else {
		if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[1]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[11]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[40]) {
					w644 = -6.3982854;
				} else {
					w644 = 174.51552;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[1]) {
					w644 = 98.94987;
				} else {
					w644 = -178.349;
				}
			}
		} else {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[38]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[50]) {
					w644 = 61.402866;
				} else {
					w644 = -66.254395;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[29]) {
					w644 = -279.0671;
				} else {
					w644 = 102.672264;
				}
			}
		}
	}
	float w645;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[41]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[22]) {
					w645 = -35.35545;
				} else {
					w645 = 25.338057;
				}
			} else {
				if (YearRemodAdd != NULL && *YearRemodAdd < cond_YearRemodAdd[26]) {
					w645 = -39.453087;
				} else {
					w645 = -180.72047;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w645 = -155.91397;
				} else {
					w645 = -8.618358;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[79]) {
					w645 = 7.0206904;
				} else {
					w645 = -13.036623;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[36]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[2]) {
					w645 = 71.765915;
				} else {
					w645 = 7.629023;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[51]) {
					w645 = 195.02864;
				} else {
					w645 = 42.436287;
				}
			}
		} else {
			w645 = -63.780468;
		}
	}
	float w646;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w646 = -208.19742;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[55]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[6]) {
					w646 = 34.204216;
				} else {
					w646 = -70.67361;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[34]) {
					w646 = 12.234985;
				} else {
					w646 = 194.89822;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[33]) {
					w646 = -59.13384;
				} else {
					w646 = 11.3363495;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[44]) {
					w646 = 12.772418;
				} else {
					w646 = -7.5405746;
				}
			}
		}
	}
	float w647;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[27]) {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[26]) {
					w647 = -4.056173;
				} else {
					w647 = 85.76311;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
					w647 = -28.628174;
				} else {
					w647 = 65.96108;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
				w647 = -192.86156;
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[56]) {
					w647 = -103.69485;
				} else {
					w647 = 7.578214;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w647 = 68.35318;
		} else {
			w647 = 190.93465;
		}
	}
	float w648;
	if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			w648 = -125.480034;
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[19]) {
				w648 = 213.50032;
			} else {
				w648 = 56.566795;
			}
		}
	} else {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[5]) {
					w648 = 0.28434473;
				} else {
					w648 = 53.8246;
				}
			} else {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[2]) {
					w648 = 245.95055;
				} else {
					w648 = 41.865536;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[48]) {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[46]) {
					w648 = -35.537415;
				} else {
					w648 = 14.775836;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[28]) {
					w648 = -0.13743511;
				} else {
					w648 = -130.49043;
				}
			}
		}
	}
	float w649;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[51]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[54]) {
					w649 = -3.5108118;
				} else {
					w649 = -82.026955;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[22]) {
					w649 = 7.1337175;
				} else {
					w649 = 135.0138;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[8]) {
					w649 = 210.63661;
				} else {
					w649 = 12.831371;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[38]) {
					w649 = 201.10342;
				} else {
					w649 = -21.046844;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			w649 = 121.09719;
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				w649 = -278.9664;
			} else {
				w649 = -87.73002;
			}
		}
	}
	float w650;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w650 = -206.58116;
	} else {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[20]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[4]) {
					w650 = -12.416576;
				} else {
					w650 = 112.58498;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[39]) {
					w650 = -95.64225;
				} else {
					w650 = -288.22272;
				}
			}
		} else {
			if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[80]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[35]) {
					w650 = 7.109583;
				} else {
					w650 = 103.33708;
				}
			} else {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
					w650 = -107.08399;
				} else {
					w650 = 2.6774197;
				}
			}
		}
	}
	float w651;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[8]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[41]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[73]) {
					w651 = -26.275305;
				} else {
					w651 = 100.432495;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[0]) {
					w651 = -167.07167;
				} else {
					w651 = -8.653477;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
					w651 = -153.62047;
				} else {
					w651 = -8.5106945;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[79]) {
					w651 = 6.9608784;
				} else {
					w651 = -12.999093;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[36]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[2]) {
					w651 = 71.01779;
				} else {
					w651 = 7.322109;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[51]) {
					w651 = 192.70284;
				} else {
					w651 = 42.056953;
				}
			}
		} else {
			w651 = -63.34984;
		}
	}
	float w652;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[12]) {
		if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[13]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[11]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[35]) {
					w652 = 7.3405347;
				} else {
					w652 = 321.29767;
				}
			} else {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[7]) {
					w652 = -19.852917;
				} else {
					w652 = 28.161499;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[55]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[33]) {
					w652 = -156.14404;
				} else {
					w652 = 79.62199;
				}
			} else {
				if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
					w652 = -391.11368;
				} else {
					w652 = -92.77289;
				}
			}
		}
	} else {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[47]) {
				w652 = 162.89932;
			} else {
				w652 = 6.6382813;
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[34]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[39]) {
					w652 = -12.524749;
				} else {
					w652 = -110.5826;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[27]) {
					w652 = -72.930115;
				} else {
					w652 = 51.17921;
				}
			}
		}
	}
	float w653;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[20]) {
			if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[42]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[6]) {
					w653 = 2.53699;
				} else {
					w653 = -25.191668;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[70]) {
					w653 = -17.021748;
				} else {
					w653 = -204.75893;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[5]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[48]) {
					w653 = -18.171501;
				} else {
					w653 = 78.92327;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[25]) {
					w653 = 215.72261;
				} else {
					w653 = -64.56988;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w653 = 67.62305;
		} else {
			w653 = 189.52371;
		}
	}
	float w654;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[43]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
					w654 = -3.3405948;
				} else {
					w654 = 93.82411;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w654 = -18.784004;
				} else {
					w654 = 146.18251;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[8]) {
					w654 = 207.38475;
				} else {
					w654 = 12.879573;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[38]) {
					w654 = 197.10094;
				} else {
					w654 = -20.873848;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			w654 = 119.126564;
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				w654 = -276.80048;
			} else {
				w654 = -87.01556;
			}
		}
	}
	float w655;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[44]) {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[37]) {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[26]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[27]) {
					w655 = -4.0880547;
				} else {
					w655 = -71.99989;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[5]) {
					w655 = -62.47191;
				} else {
					w655 = 85.96277;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[27]) {
				w655 = -382.8185;
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[57]) {
					w655 = -87.967636;
				} else {
					w655 = 138.38625;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[50]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				w655 = 23.57748;
			} else {
				w655 = -237.44156;
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[27]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[47]) {
					w655 = 28.339573;
				} else {
					w655 = 286.24286;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[48]) {
					w655 = -71.984245;
				} else {
					w655 = 8.413835;
				}
			}
		}
	}
	float w656;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[51]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[54]) {
					w656 = -3.4086316;
				} else {
					w656 = -80.24642;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[22]) {
					w656 = 6.9802384;
				} else {
					w656 = 131.92723;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[14]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[39]) {
					w656 = -121.81298;
				} else {
					w656 = 87.140305;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[51]) {
					w656 = 27.578754;
				} else {
					w656 = 153.73871;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			w656 = 117.85125;
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				w656 = -274.11642;
			} else {
				w656 = -86.08435;
			}
		}
	}
	float w657;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[27]) {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[26]) {
					w657 = -3.9624696;
				} else {
					w657 = 86.37146;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
					w657 = -27.950106;
				} else {
					w657 = 63.98483;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
				w657 = -190.7561;
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[56]) {
					w657 = -102.24586;
				} else {
					w657 = 7.2008705;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w657 = 66.898125;
		} else {
			w657 = 188.01187;
		}
	}
	float w658;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[1]) {
		if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[7]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[34]) {
					w658 = -0.64731234;
				} else {
					w658 = 66.825645;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[46]) {
					w658 = -4.240937;
				} else {
					w658 = -157.11728;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[21]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[69]) {
					w658 = 0.20677733;
				} else {
					w658 = 186.66835;
				}
			} else {
				w658 = -171.7668;
			}
		}
	} else {
		if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[2]) {
			w658 = -155.77519;
		} else {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
					w658 = 34.476543;
				} else {
					w658 = -33.726757;
				}
			} else {
				w658 = -107.996895;
			}
		}
	}
	float w659;
	if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			w659 = -124.543236;
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[19]) {
				w659 = 210.3859;
			} else {
				w659 = 55.643044;
			}
		}
	} else {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[25]) {
					w659 = -6.2274284;
				} else {
					w659 = 19.507841;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[69]) {
					w659 = -9.968872;
				} else {
					w659 = 176.38411;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[25]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[41]) {
					w659 = -16.703945;
				} else {
					w659 = 37.047543;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[28]) {
					w659 = 0.73357695;
				} else {
					w659 = -139.20244;
				}
			}
		}
	}
	float w660;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[10]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
					w660 = -17.366598;
				} else {
					w660 = 92.22768;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w660 = 49.120544;
				} else {
					w660 = -451.81625;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[66]) {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[6]) {
					w660 = 2.160835;
				} else {
					w660 = 54.452133;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w660 = -84.428215;
				} else {
					w660 = 19.755148;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[36]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[2]) {
					w660 = 70.20873;
				} else {
					w660 = 6.933867;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[51]) {
					w660 = 190.1778;
				} else {
					w660 = 41.5432;
				}
			}
		} else {
			w660 = -63.279373;
		}
	}
	float w661;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[45]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[37]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w661 = -12.079042;
				} else {
					w661 = 20.519121;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w661 = -77.09312;
				} else {
					w661 = 8.990624;
				}
			}
		} else {
			w661 = -148.76295;
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[49]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[50]) {
					w661 = -4.728507;
				} else {
					w661 = 268.90677;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[37]) {
					w661 = 1.1583295;
				} else {
					w661 = -228.11105;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
				if (Fireplaces != NULL && *Fireplaces < cond_Fireplaces[1]) {
					w661 = 2.4652872;
				} else {
					w661 = 54.689434;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w661 = 503.91397;
				} else {
					w661 = 95.37811;
				}
			}
		}
	}
	float w662;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w662 = -201.0348;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
				if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
					w662 = -18.037197;
				} else {
					w662 = 85.046265;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[80]) {
					w662 = 190.91624;
				} else {
					w662 = -43.403;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[28]) {
					w662 = -3.330394;
				} else {
					w662 = -74.78917;
				}
			} else {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[6]) {
					w662 = 0.8726958;
				} else {
					w662 = 156.59206;
				}
			}
		}
	}
	float w663;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[51]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[54]) {
					w663 = -3.2759154;
				} else {
					w663 = -79.28382;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[22]) {
					w663 = 6.755732;
				} else {
					w663 = 129.12004;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[14]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[39]) {
					w663 = -120.05206;
				} else {
					w663 = 85.90836;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[51]) {
					w663 = 27.138697;
				} else {
					w663 = 151.21355;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			w663 = 116.335464;
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				w663 = -271.65985;
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
					w663 = -25.735546;
				} else {
					w663 = -94.865;
				}
			}
		}
	}
	float w664;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[27]) {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[26]) {
					w664 = -3.8525212;
				} else {
					w664 = 85.78925;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
					w664 = -27.851168;
				} else {
					w664 = 62.51372;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
				w664 = -188.75238;
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[56]) {
					w664 = -100.929375;
				} else {
					w664 = 6.9354906;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w664 = 65.2026;
		} else {
			w664 = 187.01765;
		}
	}
	float w665;
	if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[1]) {
			w665 = -123.39656;
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[19]) {
				w665 = 208.0623;
			} else {
				w665 = 55.120937;
			}
		}
	} else {
		if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[5]) {
					w665 = 0.34584075;
				} else {
					w665 = 52.70788;
				}
			} else {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[2]) {
					w665 = 240.22223;
				} else {
					w665 = 38.754128;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[25]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[41]) {
					w665 = -16.40147;
				} else {
					w665 = 36.71904;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[28]) {
					w665 = 0.24941686;
				} else {
					w665 = -137.7209;
				}
			}
		}
	}
	float w666;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[30]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[35]) {
					w666 = -20.118;
				} else {
					w666 = 162.01723;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w666 = 48.904217;
				} else {
					w666 = -447.07367;
				}
			}
		} else {
			if (YrSold != NULL && *YrSold < cond_YrSold[1]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[26]) {
					w666 = 10.4776535;
				} else {
					w666 = 214.77045;
				}
			} else {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[22]) {
					w666 = 3.7642772;
				} else {
					w666 = -48.904446;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[36]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[2]) {
					w666 = 69.09123;
				} else {
					w666 = 7.0121484;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[51]) {
					w666 = 188.09343;
				} else {
					w666 = 41.2575;
				}
			}
		} else {
			w666 = -62.535854;
		}
	}
	float w667;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[80]) {
					w667 = 0.18331826;
				} else {
					w667 = -42.82219;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
					w667 = 230.79149;
				} else {
					w667 = 3.9521873;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[14]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[39]) {
					w667 = -118.11771;
				} else {
					w667 = 85.18203;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
					w667 = 247.13905;
				} else {
					w667 = 47.585705;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			w667 = 114.39343;
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				w667 = -269.08218;
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
					w667 = -25.544472;
				} else {
					w667 = -94.92258;
				}
			}
		}
	}
	float w668;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[45]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[37]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w668 = -11.794629;
				} else {
					w668 = 20.329628;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w668 = -75.87393;
				} else {
					w668 = 9.063457;
				}
			}
		} else {
			w668 = -147.26823;
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[37]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[36]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[23]) {
					w668 = 14.77378;
				} else {
					w668 = -185.98102;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[7]) {
					w668 = 290.0741;
				} else {
					w668 = 37.11136;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[46]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[83]) {
					w668 = -36.341602;
				} else {
					w668 = -468.4813;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[37]) {
					w668 = -3.7708726;
				} else {
					w668 = 38.44516;
				}
			}
		}
	}
	float w669;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w669 = -199.5279;
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[49]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[50]) {
					w669 = -5.0041056;
				} else {
					w669 = 264.15945;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[37]) {
					w669 = 0.5848449;
				} else {
					w669 = -224.9213;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[1]) {
					w669 = -9.754835;
				} else {
					w669 = 23.708588;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w669 = 500.1274;
				} else {
					w669 = 93.441414;
				}
			}
		}
	}
	float w670;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[27]) {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[15]) {
					w670 = -0.9605382;
				} else {
					w670 = -65.58151;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
					w670 = -27.37403;
				} else {
					w670 = 61.711582;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
				w670 = -186.39258;
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[56]) {
					w670 = -100.147026;
				} else {
					w670 = 6.430714;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w670 = 64.42418;
		} else {
			w670 = 185.38898;
		}
	}
	float w671;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[51]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[54]) {
					w671 = -3.171604;
				} else {
					w671 = -78.252914;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[22]) {
					w671 = 6.6265664;
				} else {
					w671 = 126.090744;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[8]) {
					w671 = 200.19432;
				} else {
					w671 = 11.052605;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[38]) {
					w671 = 194.0125;
				} else {
					w671 = -21.300156;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			w671 = 112.79437;
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				w671 = -266.92062;
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
					w671 = -25.279804;
				} else {
					w671 = -93.39367;
				}
			}
		}
	}
	float w672;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[1]) {
		if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[7]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[34]) {
					w672 = -0.58679616;
				} else {
					w672 = 64.15486;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[46]) {
					w672 = -4.2219267;
				} else {
					w672 = -154.46014;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[21]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[69]) {
					w672 = 0.27868652;
				} else {
					w672 = 184.46419;
				}
			} else {
				w672 = -167.36156;
			}
		}
	} else {
		if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[2]) {
			w672 = -153.49753;
		} else {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
				if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[38]) {
					w672 = -53.54461;
				} else {
					w672 = 17.66769;
				}
			} else {
				w672 = -104.796036;
			}
		}
	}
	float w673;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w673 = -197.99602;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[55]) {
				if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[6]) {
					w673 = 34.06382;
				} else {
					w673 = -69.373024;
				}
			} else {
				if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[34]) {
					w673 = 11.191159;
				} else {
					w673 = 188.6793;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[28]) {
					w673 = -3.092129;
				} else {
					w673 = -73.82478;
				}
			} else {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[6]) {
					w673 = 0.84390473;
				} else {
					w673 = 153.75574;
				}
			}
		}
	}
	float w674;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[30]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[35]) {
					w674 = -19.824284;
				} else {
					w674 = 158.42438;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
					w674 = 48.40734;
				} else {
					w674 = -442.65692;
				}
			}
		} else {
			if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[2]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[19]) {
					w674 = 205.85074;
				} else {
					w674 = 53.247578;
				}
			} else {
				if (YrSold != NULL && *YrSold < cond_YrSold[1]) {
					w674 = 14.604495;
				} else {
					w674 = -8.506312;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[36]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[2]) {
					w674 = 68.33373;
				} else {
					w674 = 6.8403516;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[51]) {
					w674 = 185.68066;
				} else {
					w674 = 40.68715;
				}
			}
		} else {
			w674 = -62.18258;
		}
	}
	float w675;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[45]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[37]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w675 = -11.490908;
				} else {
					w675 = 20.134277;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w675 = -74.73248;
				} else {
					w675 = 9.125917;
				}
			}
		} else {
			w675 = -145.69382;
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[37]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[36]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[23]) {
					w675 = 14.46524;
				} else {
					w675 = -183.80466;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[7]) {
					w675 = 286.49927;
				} else {
					w675 = 36.84218;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[46]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[83]) {
					w675 = -35.856503;
				} else {
					w675 = -462.66388;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[48]) {
					w675 = -4.5188437;
				} else {
					w675 = 28.952185;
				}
			}
		}
	}
	float w676;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w676 = -196.58672;
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[36]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
					w676 = -26.662176;
				} else {
					w676 = 2.7585034;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
					w676 = -35.330273;
				} else {
					w676 = -233.92892;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[24]) {
					w676 = -2.2385874;
				} else {
					w676 = 36.261517;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w676 = 496.33008;
				} else {
					w676 = 92.39133;
				}
			}
		}
	}
	float w677;
	if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[28]) {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[54]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[4]) {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[4]) {
					w677 = -1.0279075;
				} else {
					w677 = 122.839745;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[24]) {
					w677 = 249.31769;
				} else {
					w677 = -21.55161;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[72]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[52]) {
					w677 = -127.79434;
				} else {
					w677 = -338.8432;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[5]) {
					w677 = -72.24113;
				} else {
					w677 = 149.89474;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[52]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[29]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[51]) {
					w677 = -37.458202;
				} else {
					w677 = 101.370766;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[55]) {
					w677 = 18.382969;
				} else {
					w677 = 347.67163;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[53]) {
					w677 = -43.211174;
				} else {
					w677 = 102.74484;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w677 = -11.748984;
				} else {
					w677 = -235.48997;
				}
			}
		}
	}
	float w678;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[80]) {
					w678 = 0.19320554;
				} else {
					w678 = -42.11094;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[0]) {
					w678 = 227.46628;
				} else {
					w678 = 3.0159113;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[14]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[39]) {
					w678 = -116.23166;
				} else {
					w678 = 83.372025;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[51]) {
					w678 = 25.81035;
				} else {
					w678 = 147.59299;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			w678 = 110.92219;
		} else {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[7]) {
				w678 = -263.37155;
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
					w678 = -23.823809;
				} else {
					w678 = -93.01625;
				}
			}
		}
	}
	float w679;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[12]) {
		if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[42]) {
			if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[13]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[30]) {
					w679 = -1.954256;
				} else {
					w679 = 59.85925;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[55]) {
					w679 = 17.15878;
				} else {
					w679 = -298.66525;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[48]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[2]) {
					w679 = -29.519999;
				} else {
					w679 = 24.762186;
				}
			} else {
				w679 = -216.36687;
			}
		}
	} else {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[47]) {
				w679 = 161.3277;
			} else {
				w679 = 7.2078123;
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[39]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[39]) {
					w679 = -12.925492;
				} else {
					w679 = -110.27237;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
					w679 = 96.41487;
				} else {
					w679 = 19.139633;
				}
			}
		}
	}
	float w680;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[27]) {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[15]) {
					w680 = -0.9156551;
				} else {
					w680 = -64.72126;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
					w680 = -26.821623;
				} else {
					w680 = 60.24806;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
				w680 = -183.70065;
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[56]) {
					w680 = -98.79;
				} else {
					w680 = 5.307221;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w680 = 62.681133;
		} else {
			w680 = 183.97523;
		}
	}
	float w681;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[43]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[79]) {
					w681 = 2.558697;
				} else {
					w681 = -20.509178;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w681 = -21.499014;
				} else {
					w681 = 138.76334;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[18]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[8]) {
					w681 = 195.39743;
				} else {
					w681 = 10.380703;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[38]) {
					w681 = 191.95375;
				} else {
					w681 = -21.385508;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			w681 = 109.535774;
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				w681 = -55.74426;
			} else {
				w681 = -235.73009;
			}
		}
	}
	float w682;
	if (LotArea != NULL && *LotArea < cond_LotArea[71]) {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[14]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[54]) {
					w682 = -28.559929;
				} else {
					w682 = -113.073654;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[68]) {
					w682 = -17.161665;
				} else {
					w682 = 99.64195;
				}
			}
		} else {
			w682 = -147.46062;
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
			if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[51]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[25]) {
					w682 = -10.212667;
				} else {
					w682 = -78.342255;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[45]) {
					w682 = 28.185385;
				} else {
					w682 = -179.02167;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[47]) {
					w682 = 17.952164;
				} else {
					w682 = -245.36249;
				}
			} else {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[2]) {
					w682 = 88.14862;
				} else {
					w682 = -87.72914;
				}
			}
		}
	}
	float w683;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[8]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[37]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[4]) {
					w683 = -3.3498924;
				} else {
					w683 = 85.651245;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[46]) {
					w683 = 116.37201;
				} else {
					w683 = 3.7555826;
				}
			}
		} else {
			if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[9]) {
				w683 = -364.10028;
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[12]) {
					w683 = -70.96359;
				} else {
					w683 = 80.33363;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[36]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[2]) {
					w683 = 67.62176;
				} else {
					w683 = 6.375586;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[51]) {
					w683 = 182.3673;
				} else {
					w683 = 40.548634;
				}
			}
		} else {
			w683 = -61.261562;
		}
	}
	float w684;
	if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[1]) {
		if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[43]) {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[7]) {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[34]) {
					w684 = -0.57921773;
				} else {
					w684 = 62.533768;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[46]) {
					w684 = -4.3843036;
				} else {
					w684 = -150.58992;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[21]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[69]) {
					w684 = 0.23419921;
				} else {
					w684 = 180.92867;
				}
			} else {
				w684 = -166.35695;
			}
		}
	} else {
		if (LowQualFinSF != NULL && *LowQualFinSF < cond_LowQualFinSF[2]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[87]) {
				w684 = -166.07428;
			} else {
				w684 = -46.010975;
			}
		} else {
			if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[4]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
					w684 = 35.034626;
				} else {
					w684 = -33.04405;
				}
			} else {
				w684 = -102.35279;
			}
		}
	}
	float w685;
	if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[2]) {
		if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[52]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w685 = -60.403477;
				} else {
					w685 = 33.72006;
				}
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[32]) {
					w685 = -209.85194;
				} else {
					w685 = -24.631054;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[28]) {
				if (MoSold != NULL && *MoSold < cond_MoSold[0]) {
					w685 = -40.63191;
				} else {
					w685 = 37.868385;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
					w685 = 72.44198;
				} else {
					w685 = -1.8596094;
				}
			}
		}
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (LotArea != NULL && *LotArea < cond_LotArea[26]) {
				if (FullBath != NULL && *FullBath < cond_FullBath[2]) {
					w685 = 38.162502;
				} else {
					w685 = -72.05741;
				}
			} else {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[1]) {
					w685 = 242.06955;
				} else {
					w685 = 30.797127;
				}
			}
		} else {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[43]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[54]) {
					w685 = 16.591124;
				} else {
					w685 = -157.8175;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[28]) {
					w685 = 19.30658;
				} else {
					w685 = -18.510256;
				}
			}
		}
	}
	float w686;
	if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[44]) {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[37]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[55]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[13]) {
					w686 = -4.633111;
				} else {
					w686 = 175.08185;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[73]) {
					w686 = -8.61416;
				} else {
					w686 = -190.35522;
				}
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[27]) {
				w686 = -376.25906;
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[57]) {
					w686 = -85.73793;
				} else {
					w686 = 132.0771;
				}
			}
		}
	} else {
		if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[50]) {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[1]) {
				w686 = 22.707598;
			} else {
				w686 = -230.112;
			}
		} else {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[27]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[47]) {
					w686 = 27.295305;
				} else {
					w686 = 276.5117;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[48]) {
					w686 = -70.219925;
				} else {
					w686 = 8.070782;
				}
			}
		}
	}
	float w687;
	if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[28]) {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[54]) {
			if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[4]) {
				if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
					w687 = 2.0828245;
				} else {
					w687 = -45.7535;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[28]) {
					w687 = 52.33869;
				} else {
					w687 = 217.36319;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[72]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[52]) {
					w687 = -124.99004;
				} else {
					w687 = -333.05698;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[5]) {
					w687 = -70.76812;
				} else {
					w687 = 146.67929;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[52]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[29]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[56]) {
					w687 = -2.6269064;
				} else {
					w687 = 138.28905;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[55]) {
					w687 = 17.682812;
				} else {
					w687 = 343.2471;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[53]) {
					w687 = -41.57758;
				} else {
					w687 = 99.79898;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w687 = -9.667031;
				} else {
					w687 = -230.80487;
				}
			}
		}
	}
	float w688;
	if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[50]) {
		if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[20]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[5]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[22]) {
					w688 = -46.027485;
				} else {
					w688 = -4.962959;
				}
			} else {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[82]) {
					w688 = -101.7145;
				} else {
					w688 = 57.467453;
				}
			}
		} else {
			if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[39]) {
				w688 = -93.14488;
			} else {
				w688 = -283.25888;
			}
		}
	} else {
		if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[80]) {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[35]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[4]) {
					w688 = -25.507654;
				} else {
					w688 = 76.25325;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[71]) {
					w688 = 76.17995;
				} else {
					w688 = 226.4184;
				}
			}
		} else {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[2]) {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[74]) {
					w688 = -279.6936;
				} else {
					w688 = -36.001396;
				}
			} else {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[29]) {
					w688 = -58.579185;
				} else {
					w688 = 3.8914154;
				}
			}
		}
	}
	float w689;
	if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[74]) {
		if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[3]) {
			if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[9]) {
				w689 = -26.167969;
			} else {
				w689 = 20.009062;
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[9]) {
				w689 = -142.92511;
			} else {
				if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[16]) {
					w689 = -48.787216;
				} else {
					w689 = 9.0832615;
				}
			}
		}
	} else {
		if (OverallCond != NULL && *OverallCond < cond_OverallCond[0]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[49]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[50]) {
					w689 = -4.543345;
				} else {
					w689 = 259.58844;
				}
			} else {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[37]) {
					w689 = 0.92037684;
				} else {
					w689 = -219.4242;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[45]) {
				if (FullBath != NULL && *FullBath < cond_FullBath[1]) {
					w689 = 209.57227;
				} else {
					w689 = 6.165506;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[65]) {
					w689 = 491.50287;
				} else {
					w689 = 90.45524;
				}
			}
		}
	}
	float w690;
	if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[28]) {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[54]) {
			if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[4]) {
				if (KitchenAbvGr != NULL && *KitchenAbvGr < cond_KitchenAbvGr[0]) {
					w690 = 2.0349424;
				} else {
					w690 = -44.97778;
				}
			} else {
				if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[28]) {
					w690 = 52.6715;
				} else {
					w690 = 215.19624;
				}
			}
		} else {
			if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[72]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[52]) {
					w690 = -123.33515;
				} else {
					w690 = -328.78314;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[5]) {
					w690 = -69.776794;
				} else {
					w690 = 145.00766;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[52]) {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[29]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[56]) {
					w690 = -2.5714219;
				} else {
					w690 = 136.9824;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[55]) {
					w690 = 17.512499;
				} else {
					w690 = 339.35248;
				}
			}
		} else {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[36]) {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[53]) {
					w690 = -41.049725;
				} else {
					w690 = 98.64328;
				}
			} else {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
					w690 = -9.670078;
				} else {
					w690 = -227.43538;
				}
			}
		}
	}
	float w691;
	if (YrSold != NULL && *YrSold < cond_YrSold[0]) {
		if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[1]) {
			if (OverallCond != NULL && *OverallCond < cond_OverallCond[5]) {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[40]) {
					w691 = -6.5304365;
				} else {
					w691 = 29.081043;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[40]) {
					w691 = 90.87227;
				} else {
					w691 = -80.19859;
				}
			}
		} else {
			if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[2]) {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[4]) {
					w691 = 302.79422;
				} else {
					w691 = 89.35773;
				}
			} else {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[10]) {
					w691 = -128.9197;
				} else {
					w691 = 136.8857;
				}
			}
		}
	} else {
		if (LotFrontage == NULL || *LotFrontage < cond_LotFrontage[48]) {
			if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[46]) {
				if (TotRmsAbvGrd != NULL && *TotRmsAbvGrd < cond_TotRmsAbvGrd[5]) {
					w691 = -49.453964;
				} else {
					w691 = 83.9311;
				}
			} else {
				if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[57]) {
					w691 = 28.969864;
				} else {
					w691 = -52.970146;
				}
			}
		} else {
			if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[28]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[21]) {
					w691 = -38.198677;
				} else {
					w691 = 219.86507;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[10]) {
					w691 = -291.7958;
				} else {
					w691 = -54.58647;
				}
			}
		}
	}
	float w692;
	if (LotArea != NULL && *LotArea < cond_LotArea[71]) {
		if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[31]) {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[14]) {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[54]) {
					w692 = -27.890871;
				} else {
					w692 = -111.99712;
				}
			} else {
				if (GrLivArea != NULL && *GrLivArea < cond_GrLivArea[68]) {
					w692 = -16.92982;
				} else {
					w692 = 98.128746;
				}
			}
		} else {
			w692 = -145.48582;
		}
	} else {
		if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[4]) {
			if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[23]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[56]) {
					w692 = -9.988569;
				} else {
					w692 = 165.89917;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[58]) {
					w692 = -57.590622;
				} else {
					w692 = 236.1156;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[2]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[47]) {
					w692 = 17.538893;
				} else {
					w692 = -240.08437;
				}
			} else {
				if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[23]) {
					w692 = 17.781971;
				} else {
					w692 = -161.72556;
				}
			}
		}
	}
	float w693;
	if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[30]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[35]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[30]) {
					w693 = -12.58988;
				} else {
					w693 = -192.38313;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
					w693 = -105.59117;
				} else {
					w693 = 254.98874;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
				w693 = 46.867264;
			} else {
				w693 = -434.74228;
			}
		}
	} else {
		if (YrSold != NULL && *YrSold < cond_YrSold[1]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[26]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w693 = 14.715321;
				} else {
					w693 = -142.29877;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[31]) {
					w693 = -28.357935;
				} else {
					w693 = 420.6248;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[38]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[10]) {
					w693 = -7.602647;
				} else {
					w693 = 46.400375;
				}
			} else {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[0]) {
					w693 = -53.627853;
				} else {
					w693 = 146.37935;
				}
			}
		}
	}
	float w694;
	if (PoolArea != NULL && *PoolArea < cond_PoolArea[1]) {
		if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[27]) {
			if (MasVnrArea == NULL || *MasVnrArea < cond_MasVnrArea[5]) {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[26]) {
					w694 = -3.7061636;
				} else {
					w694 = 83.81751;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[62]) {
					w694 = -26.178755;
				} else {
					w694 = 59.192867;
				}
			}
		} else {
			if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
				w694 = -179.7529;
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[56]) {
					w694 = -95.85867;
				} else {
					w694 = 5.0594196;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[49]) {
			w694 = 60.302402;
		} else {
			w694 = 181.08516;
		}
	}
	float w695;
	if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[38]) {
		w695 = -190.53586;
	} else {
		if (GarageYrBlt != NULL && *GarageYrBlt < cond_GarageYrBlt[31]) {
			if (HalfBath != NULL && *HalfBath < cond_HalfBath[0]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[11]) {
					w695 = 19.375158;
				} else {
					w695 = -94.660385;
				}
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[58]) {
					w695 = -111.503105;
				} else {
					w695 = 141.4711;
				}
			}
		} else {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[34]) {
				if (_2ndFlrSF != NULL && *_2ndFlrSF < cond__2ndFlrSF[33]) {
					w695 = -55.93653;
				} else {
					w695 = 12.49464;
				}
			} else {
				if (EnclosedPorch != NULL && *EnclosedPorch < cond_EnclosedPorch[6]) {
					w695 = 0.76606244;
				} else {
					w695 = 151.00966;
				}
			}
		}
	}
	float w696;
	if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[6]) {
		if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[8]) {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[48]) {
				if (OverallCond != NULL && *OverallCond < cond_OverallCond[4]) {
					w696 = -3.9924436;
				} else {
					w696 = 82.50308;
				}
			} else {
				if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[41]) {
					w696 = 9.9395;
				} else {
					w696 = 90.2565;
				}
			}
		} else {
			if (BsmtFinSF2 != NULL && *BsmtFinSF2 < cond_BsmtFinSF2[9]) {
				w696 = -357.44296;
			} else {
				if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[12]) {
					w696 = -69.703865;
				} else {
					w696 = 77.92359;
				}
			}
		}
	} else {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[38]) {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[36]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[2]) {
					w696 = 66.70406;
				} else {
					w696 = 6.1966405;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[51]) {
					w696 = 178.61694;
				} else {
					w696 = 39.725975;
				}
			}
		} else {
			w696 = -60.882656;
		}
	}
	float w697;
	if (GarageArea != NULL && *GarageArea < cond_GarageArea[27]) {
		if (GarageYrBlt == NULL || *GarageYrBlt < cond_GarageYrBlt[9]) {
			if (GarageArea != NULL && *GarageArea < cond_GarageArea[43]) {
				if (area_with_basement != NULL && *area_with_basement < cond_area_with_basement[79]) {
					w697 = 2.487882;
				} else {
					w697 = -20.086433;
				}
			} else {
				if (MoSold != NULL && *MoSold < cond_MoSold[3]) {
					w697 = -21.096327;
				} else {
					w697 = 135.38866;
				}
			}
		} else {
			if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[14]) {
				if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[39]) {
					w697 = -115.04562;
				} else {
					w697 = 80.42601;
				}
			} else {
				if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[51]) {
					w697 = 24.299183;
				} else {
					w697 = 144.98915;
				}
			}
		}
	} else {
		if (LotFrontage != NULL && *LotFrontage < cond_LotFrontage[19]) {
			w697 = 106.675156;
		} else {
			if (OverallQual != NULL && *OverallQual < cond_OverallQual[3]) {
				w697 = -52.641327;
			} else {
				w697 = -231.04587;
			}
		}
	}
	float w698;
	if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[12]) {
		if (OpenPorchSF != NULL && *OpenPorchSF < cond_OpenPorchSF[42]) {
			if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[13]) {
				if (LotArea != NULL && *LotArea < cond_LotArea[30]) {
					w698 = -1.8469199;
				} else {
					w698 = 56.99551;
				}
			} else {
				if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[55]) {
					w698 = 16.300865;
				} else {
					w698 = -293.3572;
				}
			}
		} else {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[48]) {
				if (MSSubClass != NULL && *MSSubClass < cond_MSSubClass[2]) {
					w698 = -29.760468;
				} else {
					w698 = 22.900547;
				}
			} else {
				w698 = -211.32344;
			}
		}
	} else {
		if (n_bathrooms != NULL && *n_bathrooms < cond_n_bathrooms[2]) {
			if (YearBuilt != NULL && *YearBuilt < cond_YearBuilt[47]) {
				w698 = 159.77402;
			} else {
				w698 = 7.895313;
			}
		} else {
			if (TotalBsmtSF != NULL && *TotalBsmtSF < cond_TotalBsmtSF[34]) {
				if (ScreenPorch != NULL && *ScreenPorch < cond_ScreenPorch[11]) {
					w698 = -12.263872;
				} else {
					w698 = -109.185265;
				}
			} else {
				if (LotArea != NULL && *LotArea < cond_LotArea[27]) {
					w698 = -70.41469;
				} else {
					w698 = 47.477654;
				}
			}
		}
	}
	float w699;
	if (MoSold != NULL && *MoSold < cond_MoSold[4]) {
		if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[30]) {
			if (BsmtFinSF1 != NULL && *BsmtFinSF1 < cond_BsmtFinSF1[35]) {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[30]) {
					w699 = -12.415267;
				} else {
					w699 = -188.36278;
				}
			} else {
				if (GarageCars != NULL && *GarageCars < cond_GarageCars[0]) {
					w699 = -104.58609;
				} else {
					w699 = 250.87982;
				}
			}
		} else {
			if (MasVnrArea != NULL && *MasVnrArea < cond_MasVnrArea[13]) {
				w699 = 45.553593;
			} else {
				w699 = -430.3082;
			}
		}
	} else {
		if (YrSold != NULL && *YrSold < cond_YrSold[1]) {
			if (BsmtUnfSF != NULL && *BsmtUnfSF < cond_BsmtUnfSF[26]) {
				if (BedroomAbvGr != NULL && *BedroomAbvGr < cond_BedroomAbvGr[3]) {
					w699 = 14.503416;
				} else {
					w699 = -139.86272;
				}
			} else {
				if (WoodDeckSF != NULL && *WoodDeckSF < cond_WoodDeckSF[31]) {
					w699 = -28.85111;
				} else {
					w699 = 414.02527;
				}
			}
		} else {
			if (_1stFlrSF != NULL && *_1stFlrSF < cond__1stFlrSF[38]) {
				if (GarageArea != NULL && *GarageArea < cond_GarageArea[10]) {
					w699 = -7.3797684;
				} else {
					w699 = 45.57964;
				}
			} else {
				if (_3SsnPorch != NULL && *_3SsnPorch < cond__3SsnPorch[0]) {
					w699 = -52.986412;
				} else {
					w699 = 143.81929;
				}
			}
		}
	}
	return (180921.2 + w0 + w1 + w2 + w3 + w4 + w5 + w6 + w7 + w8 + w9 + w10 + w11 + w12 + w13 + w14 + w15 + w16 + w17 + w18 + w19 + w20 + w21 + w22 + w23 + w24 + w25 + w26 + w27 + w28 + w29 + w30 + w31 + w32 + w33 + w34 + w35 + w36 + w37 + w38 + w39 + w40 + w41 + w42 + w43 + w44 + w45 + w46 + w47 + w48 + w49 + w50 + w51 + w52 + w53 + w54 + w55 + w56 + w57 + w58 + w59 + w60 + w61 + w62 + w63 + w64 + w65 + w66 + w67 + w68 + w69 + w70 + w71 + w72 + w73 + w74 + w75 + w76 + w77 + w78 + w79 + w80 + w81 + w82 + w83 + w84 + w85 + w86 + w87 + w88 + w89 + w90 + w91 + w92 + w93 + w94 + w95 + w96 + w97 + w98 + w99 + w100 + w101 + w102 + w103 + w104 + w105 + w106 + w107 + w108 + w109 + w110 + w111 + w112 + w113 + w114 + w115 + w116 + w117 + w118 + w119 + w120 + w121 + w122 + w123 + w124 + w125 + w126 + w127 + w128 + w129 + w130 + w131 + w132 + w133 + w134 + w135 + w136 + w137 + w138 + w139 + w140 + w141 + w142 + w143 + w144 + w145 + w146 + w147 + w148 + w149 + w150 + w151 + w152 + w153 + w154 + w155 + w156 + w157 + w158 + w159 + w160 + w161 + w162 + w163 + w164 + w165 + w166 + w167 + w168 + w169 + w170 + w171 + w172 + w173 + w174 + w175 + w176 + w177 + w178 + w179 + w180 + w181 + w182 + w183 + w184 + w185 + w186 + w187 + w188 + w189 + w190 + w191 + w192 + w193 + w194 + w195 + w196 + w197 + w198 + w199 + w200 + w201 + w202 + w203 + w204 + w205 + w206 + w207 + w208 + w209 + w210 + w211 + w212 + w213 + w214 + w215 + w216 + w217 + w218 + w219 + w220 + w221 + w222 + w223 + w224 + w225 + w226 + w227 + w228 + w229 + w230 + w231 + w232 + w233 + w234 + w235 + w236 + w237 + w238 + w239 + w240 + w241 + w242 + w243 + w244 + w245 + w246 + w247 + w248 + w249 + w250 + w251 + w252 + w253 + w254 + w255 + w256 + w257 + w258 + w259 + w260 + w261 + w262 + w263 + w264 + w265 + w266 + w267 + w268 + w269 + w270 + w271 + w272 + w273 + w274 + w275 + w276 + w277 + w278 + w279 + w280 + w281 + w282 + w283 + w284 + w285 + w286 + w287 + w288 + w289 + w290 + w291 + w292 + w293 + w294 + w295 + w296 + w297 + w298 + w299 + w300 + w301 + w302 + w303 + w304 + w305 + w306 + w307 + w308 + w309 + w310 + w311 + w312 + w313 + w314 + w315 + w316 + w317 + w318 + w319 + w320 + w321 + w322 + w323 + w324 + w325 + w326 + w327 + w328 + w329 + w330 + w331 + w332 + w333 + w334 + w335 + w336 + w337 + w338 + w339 + w340 + w341 + w342 + w343 + w344 + w345 + w346 + w347 + w348 + w349 + w350 + w351 + w352 + w353 + w354 + w355 + w356 + w357 + w358 + w359 + w360 + w361 + w362 + w363 + w364 + w365 + w366 + w367 + w368 + w369 + w370 + w371 + w372 + w373 + w374 + w375 + w376 + w377 + w378 + w379 + w380 + w381 + w382 + w383 + w384 + w385 + w386 + w387 + w388 + w389 + w390 + w391 + w392 + w393 + w394 + w395 + w396 + w397 + w398 + w399 + w400 + w401 + w402 + w403 + w404 + w405 + w406 + w407 + w408 + w409 + w410 + w411 + w412 + w413 + w414 + w415 + w416 + w417 + w418 + w419 + w420 + w421 + w422 + w423 + w424 + w425 + w426 + w427 + w428 + w429 + w430 + w431 + w432 + w433 + w434 + w435 + w436 + w437 + w438 + w439 + w440 + w441 + w442 + w443 + w444 + w445 + w446 + w447 + w448 + w449 + w450 + w451 + w452 + w453 + w454 + w455 + w456 + w457 + w458 + w459 + w460 + w461 + w462 + w463 + w464 + w465 + w466 + w467 + w468 + w469 + w470 + w471 + w472 + w473 + w474 + w475 + w476 + w477 + w478 + w479 + w480 + w481 + w482 + w483 + w484 + w485 + w486 + w487 + w488 + w489 + w490 + w491 + w492 + w493 + w494 + w495 + w496 + w497 + w498 + w499 + w500 + w501 + w502 + w503 + w504 + w505 + w506 + w507 + w508 + w509 + w510 + w511 + w512 + w513 + w514 + w515 + w516 + w517 + w518 + w519 + w520 + w521 + w522 + w523 + w524 + w525 + w526 + w527 + w528 + w529 + w530 + w531 + w532 + w533 + w534 + w535 + w536 + w537 + w538 + w539 + w540 + w541 + w542 + w543 + w544 + w545 + w546 + w547 + w548 + w549 + w550 + w551 + w552 + w553 + w554 + w555 + w556 + w557 + w558 + w559 + w560 + w561 + w562 + w563 + w564 + w565 + w566 + w567 + w568 + w569 + w570 + w571 + w572 + w573 + w574 + w575 + w576 + w577 + w578 + w579 + w580 + w581 + w582 + w583 + w584 + w585 + w586 + w587 + w588 + w589 + w590 + w591 + w592 + w593 + w594 + w595 + w596 + w597 + w598 + w599 + w600 + w601 + w602 + w603 + w604 + w605 + w606 + w607 + w608 + w609 + w610 + w611 + w612 + w613 + w614 + w615 + w616 + w617 + w618 + w619 + w620 + w621 + w622 + w623 + w624 + w625 + w626 + w627 + w628 + w629 + w630 + w631 + w632 + w633 + w634 + w635 + w636 + w637 + w638 + w639 + w640 + w641 + w642 + w643 + w644 + w645 + w646 + w647 + w648 + w649 + w650 + w651 + w652 + w653 + w654 + w655 + w656 + w657 + w658 + w659 + w660 + w661 + w662 + w663 + w664 + w665 + w666 + w667 + w668 + w669 + w670 + w671 + w672 + w673 + w674 + w675 + w676 + w677 + w678 + w679 + w680 + w681 + w682 + w683 + w684 + w685 + w686 + w687 + w688 + w689 + w690 + w691 + w692 + w693 + w694 + w695 + w696 + w697 + w698 + w699);
}
