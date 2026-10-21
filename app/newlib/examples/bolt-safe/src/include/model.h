#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

const uint16_t cond_rel_time[] = {
	372,
	3321,
	63,
	3760,
	1243,
	1158,
	3159,
	297,
	1130,
	3462,
	1301,
	3016,
	686,
	3761,
	10416,
	3273,
	918,
	3130,
	3342,
	3898,
	438,
	3715,
	1444,
	1273,
	1587,
	1386,
	1730,
	10257,
	10374,
	3807,
	4090,
	2873,
	3101,
	3187,
	964,
	4136,
	2730,
	2901,
	3244,
	4138,
	2587,
	3302,
	868,
	731,
	1529,
	1615,
	1815,
	163,
	1559,
	2016,
	1187,
	1873,
	2101,
	569,
	2444,
	3364,
	3044,
	2301,
	10335,
	2159,
	2386,
	2672,
	230,
	10296,
	2187,
	4466,
	3598,
	4566,
	503,
	2472,
	2815,
	4569,
	777,
	3998,
	1055,
	822,
	2243,
	2702,
	1958,
	10009,
	9703,
	10052,
	1473,
	2987,
	9676,
	1329,
	2845,
	9579,
	10078,
	1758,
	9536,
	9869,
	5317,
	5272,
	5602,
	5226,
	5702,
	5181,
	5710,
	6564,
	6466,
	6607,
	6454,
	6651,
	6409,
	6740,
	2529,
	6364,
	6900,
	2501,
	9269,
	9246,
	9309,
	9203,
	9160,
	9493,
	8873,
	9781,
	8557,
	7709,
	7691,
	7749,
	7591,
	7547,
	8067,
	7879,
	7278,
	8166,
	4896,
	4851,
	4901,
	4751,
	4947,
	4991,
	4329,
	6033,
	4044,
	6077,
	10117,
	9741,
	9450,
	10157,
	6885,
	8686,
	8397,
	8973,
	6941,
	1100,
	8126,
	635,
	1901,
	2044,
	2758,
	5036,
	9117,
	5136,
	8933,
	1009,
	8443,
	8462,
	8353,
	8266,
	8597,
	8021,
	8729,
	8827,
	5422,
	5754,
	5889,
	6131,
	5467,
	5844,
	2330,
	2616,
	2358,
	1930,
	2787,
	1987,
	8894,
	9019,
	7171,
	5988,
	7414,
	6275,
	6123,
	7127,
	7318,
	6839,
	5557,
	6175,
	7028,
	4284,
	1702,
	1844,
	3415,
	2958,
	4375,
	4420,
	6984,
	6320,
	7835,
	9826,
	8642,
	4660,
	3852,
	7791,
	4184,
	9967,
	3507,
	7459,
	8310,
	1501,
	7503,
	1358,
	1786,
	6695,
	7977,
	2929,
	2416,
	2273,
	2130,
	7260,
	4706,
	5512,
	4615,
	3553,
};

const uint8_t cond_hops[] = {
	3,
	2,
	4,
	5,
};

const uint8_t cond_size[] = {
	38,
};

const uint8_t cond_prod[] = {
	0,
	3,
	1,
	2,
	4,
};

const uint8_t cond_cons[] = {
	0,
	3,
	2,
	1,
	4,
};

float model(const uint16_t rel_time, const uint8_t hops, const uint8_t size, const uint8_t prod, const uint8_t cons)
{
	float w0;
	if (size < cond_size[0]) {
		if (cons != cond_cons[0]) {
			if (rel_time < cond_rel_time[1]) {
				if (hops < cond_hops[0]) {
					if (rel_time < cond_rel_time[4]) {
						if (cons != cond_cons[2]) {
							w0 = -74.90083;
						} else {
							w0 = -83.42427;
						}
					} else {
						if (hops < cond_hops[1]) {
							w0 = -88.64493;
						} else {
							w0 = -85.135864;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (rel_time < cond_rel_time[4]) {
							w0 = -72.41277;
						} else {
							w0 = -81.648575;
						}
					} else {
						if (rel_time < cond_rel_time[4]) {
							w0 = -67.95238;
						} else {
							w0 = -77.24098;
						}
					}
				}
			} else {
				if (cons != cond_cons[1]) {
					if (hops < cond_hops[0]) {
						if (hops < cond_hops[1]) {
							w0 = -72.63809;
						} else {
							w0 = -69.12331;
						}
					} else {
						if (hops < cond_hops[2]) {
							w0 = -65.632164;
						} else {
							w0 = -61.270138;
						}
					}
				} else {
					if (hops < cond_hops[0]) {
						if (hops < cond_hops[1]) {
							w0 = -59.29314;
						} else {
							w0 = -55.77029;
						}
					} else {
						if (hops < cond_hops[2]) {
							w0 = -52.27875;
						} else {
							w0 = -47.84419;
						}
					}
				}
			}
		} else {
			if (hops < cond_hops[0]) {
				if (hops < cond_hops[1]) {
					if (rel_time < cond_rel_time[5]) {
						w0 = -103.31745;
					} else {
						if (rel_time < cond_rel_time[10]) {
							w0 = -94.41183;
						} else {
							w0 = -99.16191;
						}
					}
				} else {
					if (rel_time < cond_rel_time[6]) {
						if (rel_time < cond_rel_time[11]) {
							w0 = -95.561134;
						} else {
							w0 = -99.78821;
						}
					} else {
						w0 = -91.31407;
					}
				}
			} else {
				if (hops < cond_hops[2]) {
					if (rel_time < cond_rel_time[6]) {
						w0 = -92.3216;
					} else {
						w0 = -87.45049;
					}
				} else {
					if (hops < cond_hops[3]) {
						if (rel_time < cond_rel_time[6]) {
							w0 = -88.869865;
						} else {
							w0 = -84.377304;
						}
					} else {
						w0 = -85.02784;
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[0]) {
			if (rel_time < cond_rel_time[2]) {
				if (hops < cond_hops[0]) {
					if (hops < cond_hops[1]) {
						w0 = 67.23198;
					} else {
						w0 = 70.4737;
					}
				} else {
					w0 = 76.01623;
				}
			} else {
				if (cons != cond_cons[2]) {
					if (rel_time < cond_rel_time[7]) {
						if (hops < cond_hops[0]) {
							w0 = 138.12656;
						} else {
							w0 = 145.61513;
						}
					} else {
						if (hops < cond_hops[0]) {
							w0 = 124.68969;
						} else {
							w0 = 132.15096;
						}
					}
				} else {
					if (hops < cond_hops[0]) {
						w0 = 115.5981;
					} else {
						w0 = 123.07837;
					}
				}
			}
		} else {
			if (hops < cond_hops[0]) {
				if (rel_time < cond_rel_time[3]) {
					if (rel_time < cond_rel_time[8]) {
						if (rel_time < cond_rel_time[12]) {
							w0 = 58.5271;
						} else {
							w0 = 35.502182;
						}
					} else {
						if (prod != cond_prod[0]) {
							w0 = -5.490642;
						} else {
							w0 = 33.800995;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						if (rel_time < cond_rel_time[13]) {
							w0 = 48.387238;
						} else {
							w0 = 41.371346;
						}
					} else {
						if (rel_time < cond_rel_time[13]) {
							w0 = 51.87487;
						} else {
							w0 = 44.91474;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[3]) {
					if (rel_time < cond_rel_time[9]) {
						if (rel_time < cond_rel_time[12]) {
							w0 = 66.049576;
						} else {
							w0 = 42.30781;
						}
					} else {
						if (prod != cond_prod[0]) {
							w0 = 1.7500232;
						} else {
							w0 = 42.81739;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (rel_time < cond_rel_time[14]) {
							w0 = 48.176205;
						} else {
							w0 = 53.901085;
						}
					} else {
						if (hops < cond_hops[3]) {
							w0 = 51.666103;
						} else {
							w0 = 55.15995;
						}
					}
				}
			}
		}
	}
	float w1;
	if (size < cond_size[0]) {
		if (cons != cond_cons[0]) {
			if (rel_time < cond_rel_time[1]) {
				if (hops < cond_hops[0]) {
					if (rel_time < cond_rel_time[15]) {
						if (rel_time < cond_rel_time[17]) {
							w1 = -43.58801;
						} else {
							w1 = -36.096027;
						}
					} else {
						w1 = -55.2341;
					}
				} else {
					if (rel_time < cond_rel_time[15]) {
						if (rel_time < cond_rel_time[17]) {
							w1 = -39.803333;
						} else {
							w1 = -32.27712;
						}
					} else {
						w1 = -51.430706;
					}
				}
			} else {
				if (cons != cond_cons[1]) {
					if (hops < cond_hops[0]) {
						if (rel_time < cond_rel_time[18]) {
							w1 = -33.94442;
						} else {
							w1 = -37.103443;
						}
					} else {
						if (rel_time < cond_rel_time[18]) {
							w1 = -30.250992;
						} else {
							w1 = -33.298244;
						}
					}
				} else {
					if (hops < cond_hops[0]) {
						if (hops < cond_hops[1]) {
							w1 = -29.675518;
						} else {
							w1 = -27.918276;
						}
					} else {
						if (hops < cond_hops[3]) {
							w1 = -25.651585;
						} else {
							w1 = -21.365707;
						}
					}
				}
			}
		} else {
			if (hops < cond_hops[0]) {
				if (hops < cond_hops[1]) {
					if (rel_time < cond_rel_time[6]) {
						if (rel_time < cond_rel_time[11]) {
							w1 = -49.5431;
						} else {
							w1 = -54.054573;
						}
					} else {
						w1 = -45.54642;
					}
				} else {
					if (rel_time < cond_rel_time[5]) {
						w1 = -51.86868;
					} else {
						if (rel_time < cond_rel_time[10]) {
							w1 = -43.46004;
						} else {
							w1 = -47.814865;
						}
					}
				}
			} else {
				if (hops < cond_hops[2]) {
					if (rel_time < cond_rel_time[5]) {
						w1 = -49.688755;
					} else {
						if (rel_time < cond_rel_time[10]) {
							w1 = -41.72721;
						} else {
							w1 = -46.072468;
						}
					}
				} else {
					if (rel_time < cond_rel_time[5]) {
						w1 = -48.004307;
					} else {
						if (rel_time < cond_rel_time[10]) {
							w1 = -39.354992;
						} else {
							w1 = -43.90955;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[0]) {
			if (rel_time < cond_rel_time[2]) {
				if (hops < cond_hops[2]) {
					if (hops < cond_hops[1]) {
						w1 = 33.64878;
					} else {
						w1 = 35.533516;
					}
				} else {
					w1 = 40.228226;
				}
			} else {
				if (cons != cond_cons[2]) {
					if (rel_time < cond_rel_time[7]) {
						if (hops < cond_hops[1]) {
							w1 = 67.4322;
						} else {
							w1 = 72.04728;
						}
					} else {
						if (hops < cond_hops[2]) {
							w1 = 62.769398;
						} else {
							w1 = 68.29148;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w1 = 56.197426;
						} else {
							w1 = 59.547947;
						}
					} else {
						w1 = 63.743755;
					}
				}
			}
		} else {
			if (hops < cond_hops[0]) {
				if (rel_time < cond_rel_time[3]) {
					if (rel_time < cond_rel_time[16]) {
						if (cons != cond_cons[0]) {
							w1 = 28.067469;
						} else {
							w1 = 18.66366;
						}
					} else {
						if (prod != cond_prod[1]) {
							w1 = 9.545024;
						} else {
							w1 = -10.351693;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						if (rel_time < cond_rel_time[14]) {
							w1 = 20.662891;
						} else {
							w1 = 26.719816;
						}
					} else {
						if (rel_time < cond_rel_time[14]) {
							w1 = 22.434221;
						} else {
							w1 = 28.188833;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[3]) {
					if (rel_time < cond_rel_time[16]) {
						if (cons != cond_cons[0]) {
							w1 = 32.006985;
						} else {
							w1 = 22.425606;
						}
					} else {
						if (prod != cond_prod[2]) {
							w1 = 13.362213;
						} else {
							w1 = -8.551286;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (rel_time < cond_rel_time[19]) {
							w1 = 26.884666;
						} else {
							w1 = 24.038517;
						}
					} else {
						if (hops < cond_hops[3]) {
							w1 = 25.833569;
						} else {
							w1 = 27.581577;
						}
					}
				}
			}
		}
	}
	float w2;
	if (size < cond_size[0]) {
		if (cons != cond_cons[0]) {
			if (hops < cond_hops[1]) {
				if (rel_time < cond_rel_time[1]) {
					if (rel_time < cond_rel_time[23]) {
						if (cons != cond_cons[2]) {
							w2 = -17.75274;
						} else {
							w2 = -21.585697;
						}
					} else {
						if (rel_time < cond_rel_time[25]) {
							w2 = -31.571117;
						} else {
							w2 = -22.25717;
						}
					}
				} else {
					if (cons != cond_cons[1]) {
						if (rel_time < cond_rel_time[18]) {
							w2 = -17.80677;
						} else {
							w2 = -19.35609;
						}
					} else {
						w2 = -14.852239;
					}
				}
			} else {
				if (hops < cond_hops[3]) {
					if (rel_time < cond_rel_time[23]) {
						if (cons != cond_cons[2]) {
							w2 = -14.496513;
						} else {
							w2 = -19.898697;
						}
					} else {
						if (rel_time < cond_rel_time[25]) {
							w2 = -29.608799;
						} else {
							w2 = -20.041319;
						}
					}
				} else {
					if (rel_time < cond_rel_time[23]) {
						if (cons != cond_cons[2]) {
							w2 = -9.869123;
						} else {
							w2 = -17.1972;
						}
					} else {
						if (rel_time < cond_rel_time[25]) {
							w2 = -25.157911;
						} else {
							w2 = -15.635227;
						}
					}
				}
			}
		} else {
			if (hops < cond_hops[0]) {
				if (rel_time < cond_rel_time[22]) {
					if (rel_time < cond_rel_time[10]) {
						if (rel_time < cond_rel_time[5]) {
							w2 = -26.51926;
						} else {
							w2 = -22.16796;
						}
					} else {
						w2 = -28.964046;
					}
				} else {
					if (rel_time < cond_rel_time[24]) {
						if (hops < cond_hops[1]) {
							w2 = -20.939999;
						} else {
							w2 = -19.896576;
						}
					} else {
						if (rel_time < cond_rel_time[26]) {
							w2 = -28.608667;
						} else {
							w2 = -23.94093;
						}
					}
				}
			} else {
				if (hops < cond_hops[3]) {
					if (rel_time < cond_rel_time[22]) {
						if (rel_time < cond_rel_time[10]) {
							w2 = -22.629665;
						} else {
							w2 = -27.040037;
						}
					} else {
						if (rel_time < cond_rel_time[24]) {
							w2 = -18.548159;
						} else {
							w2 = -22.758436;
						}
					}
				} else {
					if (rel_time < cond_rel_time[6]) {
						if (rel_time < cond_rel_time[11]) {
							w2 = -20.571348;
						} else {
							w2 = -24.763151;
						}
					} else {
						w2 = -16.271677;
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[20]) {
			if (cons != cond_cons[0]) {
				if (cons != cond_cons[2]) {
					if (hops < cond_hops[2]) {
						if (rel_time < cond_rel_time[7]) {
							w2 = 34.397095;
						} else {
							w2 = 31.397472;
						}
					} else {
						if (rel_time < cond_rel_time[7]) {
							w2 = 39.033737;
						} else {
							w2 = 34.2047;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w2 = 28.127054;
						} else {
							w2 = 29.794537;
						}
					} else {
						if (hops < cond_hops[3]) {
							w2 = 31.0297;
						} else {
							w2 = 34.52132;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[2]) {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w2 = 16.840794;
						} else {
							w2 = 17.779177;
						}
					} else {
						if (hops < cond_hops[3]) {
							w2 = 19.381577;
						} else {
							w2 = 22.610397;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						w2 = 20.911013;
					} else {
						if (hops < cond_hops[2]) {
							w2 = 23.655153;
						} else {
							w2 = 27.01873;
						}
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[21]) {
				if (rel_time < cond_rel_time[9]) {
					if (prod != cond_prod[2]) {
						if (cons != cond_cons[0]) {
							w2 = 12.502418;
						} else {
							w2 = 3.1469007;
						}
					} else {
						if (hops < cond_hops[0]) {
							w2 = -15.298308;
						} else {
							w2 = -24.21883;
						}
					}
				} else {
					if (prod != cond_prod[1]) {
						if (prod != cond_prod[2]) {
							w2 = 1.1996381;
						} else {
							w2 = -8.285157;
						}
					} else {
						if (hops < cond_hops[0]) {
							w2 = -5.178638;
						} else {
							w2 = -13.448808;
						}
					}
				}
			} else {
				if (hops < cond_hops[0]) {
					if (hops < cond_hops[1]) {
						if (rel_time < cond_rel_time[27]) {
							w2 = 10.4213505;
						} else {
							w2 = 8.762232;
						}
					} else {
						if (rel_time < cond_rel_time[13]) {
							w2 = 15.040211;
						} else {
							w2 = 11.219518;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (rel_time < cond_rel_time[28]) {
							w2 = 12.114203;
						} else {
							w2 = 8.917655;
						}
					} else {
						if (rel_time < cond_rel_time[29]) {
							w2 = 18.079222;
						} else {
							w2 = 13.07621;
						}
					}
				}
			}
		}
	}
	float w3;
	if (size < cond_size[0]) {
		if (rel_time < cond_rel_time[6]) {
			if (rel_time < cond_rel_time[11]) {
				if (rel_time < cond_rel_time[31]) {
					if (rel_time < cond_rel_time[36]) {
						if (rel_time < cond_rel_time[40]) {
							w3 = -11.079148;
						} else {
							w3 = -3.6558864;
						}
					} else {
						if (cons != cond_cons[1]) {
							w3 = -16.23123;
						} else {
							w3 = -22.527742;
						}
					}
				} else {
					if (rel_time < cond_rel_time[37]) {
						if (hops < cond_hops[2]) {
							w3 = 1.4527723;
						} else {
							w3 = 3.2581213;
						}
					} else {
						if (cons != cond_cons[1]) {
							w3 = -7.1345344;
						} else {
							w3 = 0.7614582;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[32]) {
					if (cons != cond_cons[2]) {
						if (hops < cond_hops[2]) {
							w3 = -22.875372;
						} else {
							w3 = -21.134323;
						}
					} else {
						if (hops < cond_hops[2]) {
							w3 = -14.513058;
						} else {
							w3 = -12.781283;
						}
					}
				} else {
					if (rel_time < cond_rel_time[17]) {
						if (hops < cond_hops[2]) {
							w3 = -13.543534;
						} else {
							w3 = -11.780942;
						}
					} else {
						if (hops < cond_hops[3]) {
							w3 = -14.922162;
						} else {
							w3 = -12.470665;
						}
					}
				}
			}
		} else {
			if (cons != cond_cons[1]) {
				if (rel_time < cond_rel_time[33]) {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w3 = -3.8731966;
						} else {
							w3 = -3.276378;
						}
					} else {
						if (hops < cond_hops[3]) {
							w3 = -2.1280882;
						} else {
							w3 = -0.816369;
						}
					}
				} else {
					if (cons != cond_cons[3]) {
						if (rel_time < cond_rel_time[41]) {
							w3 = -10.8234215;
						} else {
							w3 = -7.390297;
						}
					} else {
						if (hops < cond_hops[2]) {
							w3 = -16.956728;
						} else {
							w3 = -15.201058;
						}
					}
				}
			} else {
				if (hops < cond_hops[1]) {
					if (rel_time < cond_rel_time[38]) {
						w3 = -3.1539516;
					} else {
						w3 = -7.433374;
					}
				} else {
					if (hops < cond_hops[2]) {
						if (rel_time < cond_rel_time[38]) {
							w3 = -2.5774915;
						} else {
							w3 = -3.72275;
						}
					} else {
						if (rel_time < cond_rel_time[38]) {
							w3 = -1.0727262;
						} else {
							w3 = -2.3113754;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[20]) {
			if (cons != cond_cons[0]) {
				if (cons != cond_cons[2]) {
					if (hops < cond_hops[1]) {
						if (rel_time < cond_rel_time[7]) {
							w3 = 16.542763;
						} else {
							w3 = 13.638798;
						}
					} else {
						if (hops < cond_hops[3]) {
							w3 = 17.556164;
						} else {
							w3 = 21.127243;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w3 = 14.077708;
						} else {
							w3 = 14.907555;
						}
					} else {
						if (hops < cond_hops[3]) {
							w3 = 15.550835;
						} else {
							w3 = 17.386658;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[2]) {
					if (hops < cond_hops[0]) {
						w3 = 8.534929;
					} else {
						if (hops < cond_hops[3]) {
							w3 = 9.447075;
						} else {
							w3 = 11.392155;
						}
					}
				} else {
					if (hops < cond_hops[3]) {
						if (hops < cond_hops[1]) {
							w3 = 10.465639;
						} else {
							w3 = 12.032627;
						}
					} else {
						w3 = 15.840788;
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[30]) {
				if (rel_time < cond_rel_time[34]) {
					if (cons != cond_cons[0]) {
						if (rel_time < cond_rel_time[42]) {
							w3 = 9.206326;
						} else {
							w3 = 3.798282;
						}
					} else {
						if (rel_time < cond_rel_time[43]) {
							w3 = -4.9994254;
						} else {
							w3 = 8.060085;
						}
					}
				} else {
					if (prod != cond_prod[0]) {
						if (rel_time < cond_rel_time[21]) {
							w3 = -0.21670437;
						} else {
							w3 = 3.1728113;
						}
					} else {
						if (rel_time < cond_rel_time[3]) {
							w3 = 6.4897246;
						} else {
							w3 = 11.4868;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[35]) {
					if (prod != cond_prod[3]) {
						w3 = -3.7213037;
					} else {
						if (hops < cond_hops[0]) {
							w3 = 11.165703;
						} else {
							w3 = 12.171624;
						}
					}
				} else {
					if (rel_time < cond_rel_time[39]) {
						if (hops < cond_hops[0]) {
							w3 = -3.8295026;
						} else {
							w3 = -2.9554052;
						}
					} else {
						if (hops < cond_hops[0]) {
							w3 = 5.460149;
						} else {
							w3 = 6.3484616;
						}
					}
				}
			}
		}
	}
	float w4;
	if (size < cond_size[0]) {
		if (rel_time < cond_rel_time[24]) {
			if (rel_time < cond_rel_time[22]) {
				if (rel_time < cond_rel_time[10]) {
					if (rel_time < cond_rel_time[5]) {
						if (hops < cond_hops[1]) {
							w4 = -8.1806135;
						} else {
							w4 = -7.5254674;
						}
					} else {
						if (rel_time < cond_rel_time[50]) {
							w4 = -0.60849905;
						} else {
							w4 = -3.8211381;
						}
					}
				} else {
					if (cons != cond_cons[2]) {
						if (rel_time < cond_rel_time[25]) {
							w4 = -12.34802;
						} else {
							w4 = -8.323788;
						}
					} else {
						if (hops < cond_hops[2]) {
							w4 = -4.2480726;
						} else {
							w4 = -2.4399204;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[44]) {
					if (cons != cond_cons[2]) {
						if (hops < cond_hops[2]) {
							w4 = 5.9746437;
						} else {
							w4 = 7.721122;
						}
					} else {
						if (hops < cond_hops[2]) {
							w4 = -1.9771135;
						} else {
							w4 = -0.2539219;
						}
					}
				} else {
					if (rel_time < cond_rel_time[48]) {
						if (hops < cond_hops[2]) {
							w4 = -2.5168142;
						} else {
							w4 = -0.72690856;
						}
					} else {
						if (hops < cond_hops[3]) {
							w4 = -4.3773293;
						} else {
							w4 = -0.817431;
						}
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[26]) {
				if (rel_time < cond_rel_time[45]) {
					if (hops < cond_hops[2]) {
						w4 = -17.232447;
					} else {
						w4 = -15.487801;
					}
				} else {
					if (cons != cond_cons[1]) {
						if (hops < cond_hops[2]) {
							w4 = -8.960674;
						} else {
							w4 = -7.861359;
						}
					} else {
						if (hops < cond_hops[2]) {
							w4 = -17.202923;
						} else {
							w4 = -15.351724;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[46]) {
					if (cons != cond_cons[2]) {
						if (hops < cond_hops[2]) {
							w4 = 6.07373;
						} else {
							w4 = 7.842156;
						}
					} else {
						if (hops < cond_hops[2]) {
							w4 = -2.343895;
						} else {
							w4 = -0.4983615;
						}
					}
				} else {
					if (rel_time < cond_rel_time[49]) {
						if (rel_time < cond_rel_time[51]) {
							w4 = -1.7874876;
						} else {
							w4 = -12.283288;
						}
					} else {
						if (rel_time < cond_rel_time[52]) {
							w4 = 3.718513;
						} else {
							w4 = -5.6256857;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[20]) {
			if (cons != cond_cons[0]) {
				if (rel_time < cond_rel_time[47]) {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w4 = 8.747168;
						} else {
							w4 = 9.403178;
						}
					} else {
						if (hops < cond_hops[3]) {
							w4 = 10.374358;
						} else {
							w4 = 11.8428;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						if (cons != cond_cons[1]) {
							w4 = 6.940664;
						} else {
							w4 = 7.7778263;
						}
					} else {
						if (cons != cond_cons[1]) {
							w4 = 7.9085755;
						} else {
							w4 = 8.7609215;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[2]) {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w4 = 4.1653047;
						} else {
							w4 = 4.444877;
						}
					} else {
						if (hops < cond_hops[3]) {
							w4 = 4.9997773;
						} else {
							w4 = 5.739895;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[0]) {
							w4 = 5.915575;
						} else {
							w4 = 4.4876466;
						}
					} else {
						if (hops < cond_hops[3]) {
							w4 = 6.6802573;
						} else {
							w4 = 7.9735656;
						}
					}
				}
			}
		} else {
			if (hops < cond_hops[1]) {
				if (rel_time < cond_rel_time[21]) {
					if (prod != cond_prod[2]) {
						if (cons != cond_cons[4]) {
							w4 = -0.45577753;
						} else {
							w4 = 3.1223798;
						}
					} else {
						if (rel_time < cond_rel_time[9]) {
							w4 = -9.036137;
						} else {
							w4 = -12.610432;
						}
					}
				} else {
					if (rel_time < cond_rel_time[19]) {
						if (prod != cond_prod[3]) {
							w4 = 7.509095;
						} else {
							w4 = -4.3374295;
						}
					} else {
						if (rel_time < cond_rel_time[30]) {
							w4 = -1.4320244;
						} else {
							w4 = 2.5125656;
						}
					}
				}
			} else {
				if (cons != cond_cons[4]) {
					if (cons != cond_cons[2]) {
						if (hops < cond_hops[3]) {
							w4 = 2.8321743;
						} else {
							w4 = 4.3563123;
						}
					} else {
						if (rel_time < cond_rel_time[53]) {
							w4 = 9.95962;
						} else {
							w4 = 3.8436377;
						}
					}
				} else {
					if (rel_time < cond_rel_time[12]) {
						if (hops < cond_hops[2]) {
							w4 = 8.715888;
						} else {
							w4 = 11.682486;
						}
					} else {
						if (rel_time < cond_rel_time[16]) {
							w4 = 3.1229992;
						} else {
							w4 = 7.5204444;
						}
					}
				}
			}
		}
	}
	float w5;
	if (size < cond_size[0]) {
		if (hops < cond_hops[2]) {
			if (rel_time < cond_rel_time[6]) {
				if (rel_time < cond_rel_time[11]) {
					if (rel_time < cond_rel_time[31]) {
						if (rel_time < cond_rel_time[54]) {
							w5 = -2.5615022;
						} else {
							w5 = -5.0398965;
						}
					} else {
						if (rel_time < cond_rel_time[37]) {
							w5 = 3.538379;
						} else {
							w5 = -0.09135933;
						}
					}
				} else {
					if (rel_time < cond_rel_time[56]) {
						if (hops < cond_hops[1]) {
							w5 = -9.289979;
						} else {
							w5 = -8.670761;
						}
					} else {
						if (cons != cond_cons[1]) {
							w5 = -4.3320656;
						} else {
							w5 = -8.307932;
						}
					}
				}
			} else {
				if (cons != cond_cons[1]) {
					if (rel_time < cond_rel_time[33]) {
						if (hops < cond_hops[1]) {
							w5 = 0.8715991;
						} else {
							w5 = 1.1714643;
						}
					} else {
						if (cons != cond_cons[3]) {
							w5 = -2.281557;
						} else {
							w5 = -5.670087;
						}
					}
				} else {
					if (rel_time < cond_rel_time[38]) {
						if (hops < cond_hops[1]) {
							w5 = 1.2315245;
						} else {
							w5 = 1.5213075;
						}
					} else {
						if (hops < cond_hops[1]) {
							w5 = -0.91024;
						} else {
							w5 = 0.9482333;
						}
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[1]) {
				if (rel_time < cond_rel_time[54]) {
					if (rel_time < cond_rel_time[57]) {
						if (rel_time < cond_rel_time[59]) {
							w5 = -1.2095131;
						} else {
							w5 = -7.8243623;
						}
					} else {
						if (rel_time < cond_rel_time[60]) {
							w5 = 8.334068;
						} else {
							w5 = 2.4654691;
						}
					}
				} else {
					if (rel_time < cond_rel_time[40]) {
						if (cons != cond_cons[1]) {
							w5 = -6.6832495;
						} else {
							w5 = -11.972049;
						}
					} else {
						if (rel_time < cond_rel_time[61]) {
							w5 = 4.885905;
						} else {
							w5 = -1.9848646;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[55]) {
					if (rel_time < cond_rel_time[18]) {
						if (hops < cond_hops[3]) {
							w5 = 1.6367288;
						} else {
							w5 = 2.8434467;
						}
					} else {
						if (hops < cond_hops[3]) {
							w5 = 1.8981556;
						} else {
							w5 = 0.96110845;
						}
					}
				} else {
					if (hops < cond_hops[3]) {
						w5 = 0.09463224;
					} else {
						w5 = 1.2585841;
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[20]) {
			if (cons != cond_cons[0]) {
				if (rel_time < cond_rel_time[47]) {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w5 = 4.3778224;
						} else {
							w5 = 4.704856;
						}
					} else {
						if (hops < cond_hops[3]) {
							w5 = 5.1989293;
						} else {
							w5 = 5.9622507;
						}
					}
				} else {
					if (hops < cond_hops[3]) {
						if (rel_time < cond_rel_time[62]) {
							w5 = 3.5858886;
						} else {
							w5 = 3.9986897;
						}
					} else {
						if (cons != cond_cons[1]) {
							w5 = 4.9813395;
						} else {
							w5 = 6.4468718;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[2]) {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[0]) {
							w5 = 2.1250548;
						} else {
							w5 = 2.2960513;
						}
					} else {
						if (hops < cond_hops[3]) {
							w5 = 2.5055423;
						} else {
							w5 = 2.8920372;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						w5 = 2.2829628;
					} else {
						if (hops < cond_hops[0]) {
							w5 = 3.7628815;
						} else {
							w5 = 2.8822618;
						}
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[14]) {
				if (rel_time < cond_rel_time[28]) {
					if (rel_time < cond_rel_time[58]) {
						if (rel_time < cond_rel_time[63]) {
							w5 = 1.3989838;
						} else {
							w5 = -2.5355375;
						}
					} else {
						if (prod != cond_prod[3]) {
							w5 = -7.4620323;
						} else {
							w5 = 7.4578447;
						}
					}
				} else {
					if (prod != cond_prod[1]) {
						w5 = 7.8102417;
					} else {
						if (hops < cond_hops[0]) {
							w5 = -7.4259415;
						} else {
							w5 = -7.0170302;
						}
					}
				}
			} else {
				if (hops < cond_hops[2]) {
					if (hops < cond_hops[0]) {
						if (hops < cond_hops[1]) {
							w5 = 5.0180817;
						} else {
							w5 = 4.370506;
						}
					} else {
						w5 = 5.969472;
					}
				} else {
					w5 = 7.5874867;
				}
			}
		}
	}
	float w6;
	if (size < cond_size[0]) {
		if (rel_time < cond_rel_time[57]) {
			if (rel_time < cond_rel_time[59]) {
				if (rel_time < cond_rel_time[49]) {
					if (rel_time < cond_rel_time[51]) {
						if (rel_time < cond_rel_time[26]) {
							w6 = -1.7983937;
						} else {
							w6 = 1.8722221;
						}
					} else {
						if (cons != cond_cons[1]) {
							w6 = -3.8685765;
						} else {
							w6 = -9.477107;
						}
					}
				} else {
					if (cons != cond_cons[2]) {
						if (rel_time < cond_rel_time[52]) {
							w6 = 5.8240595;
						} else {
							w6 = 1.9606903;
						}
					} else {
						if (hops < cond_hops[2]) {
							w6 = -2.7023404;
						} else {
							w6 = -1.5662491;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[64]) {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w6 = -13.235873;
						} else {
							w6 = -12.668699;
						}
					} else {
						if (hops < cond_hops[3]) {
							w6 = -8.773305;
						} else {
							w6 = -7.4659576;
						}
					}
				} else {
					if (cons != cond_cons[1]) {
						if (hops < cond_hops[2]) {
							w6 = -5.439031;
						} else {
							w6 = -1.0796171;
						}
					} else {
						if (hops < cond_hops[2]) {
							w6 = -12.507453;
						} else {
							w6 = -8.069532;
						}
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[60]) {
				if (cons != cond_cons[2]) {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w6 = 10.19772;
						} else {
							w6 = 10.766499;
						}
					} else {
						if (hops < cond_hops[3]) {
							w6 = 6.538652;
						} else {
							w6 = 7.8648715;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w6 = 2.1193125;
						} else {
							w6 = 2.7003977;
						}
					} else {
						if (hops < cond_hops[3]) {
							w6 = -1.5005646;
						} else {
							w6 = -0.20030478;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[40]) {
					if (rel_time < cond_rel_time[54]) {
						if (hops < cond_hops[2]) {
							w6 = 2.0970798;
						} else {
							w6 = 1.2338215;
						}
					} else {
						if (rel_time < cond_rel_time[69]) {
							w6 = -10.66562;
						} else {
							w6 = -5.2664876;
						}
					}
				} else {
					if (rel_time < cond_rel_time[61]) {
						if (cons != cond_cons[2]) {
							w6 = 7.695785;
						} else {
							w6 = -0.5984202;
						}
					} else {
						if (rel_time < cond_rel_time[70]) {
							w6 = -3.145091;
						} else {
							w6 = -0.99680275;
						}
					}
				}
			}
		}
	} else {
		if (hops < cond_hops[2]) {
			if (rel_time < cond_rel_time[39]) {
				if (rel_time < cond_rel_time[34]) {
					if (cons != cond_cons[0]) {
						if (rel_time < cond_rel_time[42]) {
							w6 = 1.7837132;
						} else {
							w6 = -1.2113543;
						}
					} else {
						if (rel_time < cond_rel_time[20]) {
							w6 = 1.2047838;
						} else {
							w6 = -1.428597;
						}
					}
				} else {
					if (prod != cond_prod[0]) {
						if (cons != cond_cons[2]) {
							w6 = -1.8298709;
						} else {
							w6 = 3.6139927;
						}
					} else {
						if (rel_time < cond_rel_time[3]) {
							w6 = 0.77250415;
						} else {
							w6 = 4.2895412;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[65]) {
					if (prod != cond_prod[0]) {
						if (prod != cond_prod[3]) {
							w6 = 7.1749167;
						} else {
							w6 = -5.1232786;
						}
					} else {
						if (hops < cond_hops[1]) {
							w6 = -5.488402;
						} else {
							w6 = -4.98347;
						}
					}
				} else {
					if (rel_time < cond_rel_time[67]) {
						if (prod != cond_prod[0]) {
							w6 = -5.058307;
						} else {
							w6 = 6.423988;
						}
					} else {
						if (rel_time < cond_rel_time[71]) {
							w6 = 6.5327735;
						} else {
							w6 = 0.6544824;
						}
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[9]) {
				if (hops < cond_hops[3]) {
					if (rel_time < cond_rel_time[43]) {
						if (rel_time < cond_rel_time[12]) {
							w6 = 2.320076;
						} else {
							w6 = -1.9849265;
						}
					} else {
						if (rel_time < cond_rel_time[72]) {
							w6 = 8.816607;
						} else {
							w6 = 2.5657682;
						}
					}
				} else {
					if (rel_time < cond_rel_time[68]) {
						if (rel_time < cond_rel_time[2]) {
							w6 = 1.457146;
						} else {
							w6 = 2.8010638;
						}
					} else {
						if (rel_time < cond_rel_time[53]) {
							w6 = 9.068651;
						} else {
							w6 = 5.840348;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[66]) {
					if (prod != cond_prod[1]) {
						if (hops < cond_hops[3]) {
							w6 = 0.427715;
						} else {
							w6 = 3.2156076;
						}
					} else {
						if (hops < cond_hops[3]) {
							w6 = -7.5287123;
						} else {
							w6 = -4.7397695;
						}
					}
				} else {
					if (rel_time < cond_rel_time[19]) {
						if (prod != cond_prod[3]) {
							w6 = 5.1262875;
						} else {
							w6 = -5.110664;
						}
					} else {
						if (rel_time < cond_rel_time[73]) {
							w6 = -4.9622993;
						} else {
							w6 = 1.0977603;
						}
					}
				}
			}
		}
	}
	float w7;
	if (size < cond_size[0]) {
		if (hops < cond_hops[1]) {
			if (rel_time < cond_rel_time[57]) {
				if (rel_time < cond_rel_time[59]) {
					if (rel_time < cond_rel_time[49]) {
						if (rel_time < cond_rel_time[24]) {
							w7 = -0.56630933;
						} else {
							w7 = -2.281524;
						}
					} else {
						if (cons != cond_cons[2]) {
							w7 = 1.2980081;
						} else {
							w7 = -1.6995007;
						}
					}
				} else {
					if (cons != cond_cons[2]) {
						if (rel_time < cond_rel_time[76]) {
							w7 = -6.613509;
						} else {
							w7 = -3.5638356;
						}
					} else {
						w7 = -2.158905;
					}
				}
			} else {
				if (rel_time < cond_rel_time[60]) {
					if (cons != cond_cons[2]) {
						w7 = 5.101338;
					} else {
						w7 = 1.0606835;
					}
				} else {
					if (rel_time < cond_rel_time[40]) {
						if (cons != cond_cons[1]) {
							w7 = -1.7910376;
						} else {
							w7 = -8.975062;
						}
					} else {
						if (rel_time < cond_rel_time[77]) {
							w7 = 2.4146464;
						} else {
							w7 = -1.3915949;
						}
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[24]) {
				if (rel_time < cond_rel_time[22]) {
					if (rel_time < cond_rel_time[10]) {
						if (cons != cond_cons[1]) {
							w7 = -0.0252407;
						} else {
							w7 = 3.0149627;
						}
					} else {
						if (cons != cond_cons[2]) {
							w7 = -2.799637;
						} else {
							w7 = 0.3239689;
						}
					}
				} else {
					if (rel_time < cond_rel_time[44]) {
						if (cons != cond_cons[2]) {
							w7 = 5.4006424;
						} else {
							w7 = 1.4137583;
						}
					} else {
						if (rel_time < cond_rel_time[48]) {
							w7 = 1.1521468;
						} else {
							w7 = 0.21102643;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[26]) {
					if (cons != cond_cons[1]) {
						if (rel_time < cond_rel_time[45]) {
							w7 = -6.2033243;
						} else {
							w7 = -2.2418861;
						}
					} else {
						if (hops < cond_hops[3]) {
							w7 = -6.2782483;
						} else {
							w7 = -5.147181;
						}
					}
				} else {
					if (rel_time < cond_rel_time[46]) {
						if (cons != cond_cons[2]) {
							w7 = 3.6209297;
						} else {
							w7 = -0.58554095;
						}
					} else {
						if (rel_time < cond_rel_time[78]) {
							w7 = -2.3446193;
						} else {
							w7 = -0.26109272;
						}
					}
				}
			}
		}
	} else {
		if (cons != cond_cons[4]) {
			if (rel_time < cond_rel_time[21]) {
				if (rel_time < cond_rel_time[74]) {
					if (rel_time < cond_rel_time[75]) {
						if (rel_time < cond_rel_time[72]) {
							w7 = 0.5108711;
						} else {
							w7 = -3.9805555;
						}
					} else {
						if (cons != cond_cons[3]) {
							w7 = 3.3405025;
						} else {
							w7 = -3.4012887;
						}
					}
				} else {
					if (prod != cond_prod[0]) {
						if (prod != cond_prod[3]) {
							w7 = -3.3240047;
						} else {
							w7 = -0.90328646;
						}
					} else {
						if (rel_time < cond_rel_time[9]) {
							w7 = -0.19930123;
						} else {
							w7 = 7.352339;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[19]) {
					if (prod != cond_prod[3]) {
						if (rel_time < cond_rel_time[3]) {
							w7 = 0.09557898;
						} else {
							w7 = 7.1639843;
						}
					} else {
						if (hops < cond_hops[1]) {
							w7 = -1.9556726;
						} else {
							w7 = -4.459985;
						}
					}
				} else {
					if (rel_time < cond_rel_time[30]) {
						if (prod != cond_prod[0]) {
							w7 = -4.726539;
						} else {
							w7 = 2.4646816;
						}
					} else {
						if (rel_time < cond_rel_time[35]) {
							w7 = 4.26022;
						} else {
							w7 = 0.3889095;
						}
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[16]) {
				if (rel_time < cond_rel_time[12]) {
					if (rel_time < cond_rel_time[0]) {
						if (hops < cond_hops[1]) {
							w7 = 0.47139162;
						} else {
							w7 = 1.2105062;
						}
					} else {
						if (hops < cond_hops[3]) {
							w7 = 2.8956046;
						} else {
							w7 = 4.8045683;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						w7 = -2.2188952;
					} else {
						if (hops < cond_hops[3]) {
							w7 = 0.62906665;
						} else {
							w7 = 2.9470077;
						}
					}
				}
			} else {
				if (hops < cond_hops[3]) {
					if (hops < cond_hops[1]) {
						w7 = 2.4475625;
					} else {
						if (hops < cond_hops[0]) {
							w7 = 3.7530265;
						} else {
							w7 = 2.498869;
						}
					}
				} else {
					w7 = 5.0897107;
				}
			}
		}
	}
	float w8;
	if (size < cond_size[0]) {
		if (hops < cond_hops[3]) {
			if (cons != cond_cons[3]) {
				if (cons != cond_cons[0]) {
					if (rel_time < cond_rel_time[15]) {
						if (rel_time < cond_rel_time[83]) {
							w8 = -0.0043769795;
						} else {
							w8 = -1.1359512;
						}
					} else {
						if (hops < cond_hops[1]) {
							w8 = -0.053749967;
						} else {
							w8 = 1.2867619;
						}
					}
				} else {
					if (rel_time < cond_rel_time[22]) {
						if (hops < cond_hops[1]) {
							w8 = -1.9935528;
						} else {
							w8 = -0.93249625;
						}
					} else {
						if (rel_time < cond_rel_time[59]) {
							w8 = -0.339149;
						} else {
							w8 = -0.8762473;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[82]) {
					if (rel_time < cond_rel_time[85]) {
						if (rel_time < cond_rel_time[50]) {
							w8 = 1.7187258;
						} else {
							w8 = -3.333735;
						}
					} else {
						if (hops < cond_hops[1]) {
							w8 = 4.8783813;
						} else {
							w8 = 2.4111192;
						}
					}
				} else {
					if (rel_time < cond_rel_time[45]) {
						if (hops < cond_hops[1]) {
							w8 = -5.6453176;
						} else {
							w8 = -3.175979;
						}
					} else {
						if (rel_time < cond_rel_time[89]) {
							w8 = 2.7890537;
						} else {
							w8 = -1.3408016;
						}
					}
				}
			}
		} else {
			if (cons != cond_cons[0]) {
				if (rel_time < cond_rel_time[83]) {
					if (rel_time < cond_rel_time[86]) {
						if (rel_time < cond_rel_time[77]) {
							w8 = 1.2141943;
						} else {
							w8 = -1.3467636;
						}
					} else {
						if (cons != cond_cons[2]) {
							w8 = 5.9383616;
						} else {
							w8 = 2.8363376;
						}
					}
				} else {
					if (rel_time < cond_rel_time[32]) {
						if (cons != cond_cons[2]) {
							w8 = -5.2155423;
						} else {
							w8 = -0.9941077;
						}
					} else {
						if (rel_time < cond_rel_time[38]) {
							w8 = 2.4450288;
						} else {
							w8 = 0.56126297;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[26]) {
					if (rel_time < cond_rel_time[24]) {
						if (rel_time < cond_rel_time[22]) {
							w8 = -1.0657872;
						} else {
							w8 = 0.9768202;
						}
					} else {
						w8 = -2.5731394;
					}
				} else {
					if (rel_time < cond_rel_time[59]) {
						if (rel_time < cond_rel_time[49]) {
							w8 = 0.6604719;
						} else {
							w8 = 1.9482162;
						}
					} else {
						if (rel_time < cond_rel_time[57]) {
							w8 = -1.796711;
						} else {
							w8 = 0.2494388;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[79]) {
			if (rel_time < cond_rel_time[80]) {
				if (rel_time < cond_rel_time[84]) {
					if (rel_time < cond_rel_time[87]) {
						if (rel_time < cond_rel_time[90]) {
							w8 = 0.17069823;
						} else {
							w8 = 7.727243;
						}
					} else {
						if (prod != cond_prod[0]) {
							w8 = -5.4078236;
						} else {
							w8 = 5.5103774;
						}
					}
				} else {
					w8 = 5.9306164;
				}
			} else {
				if (prod != cond_prod[4]) {
					if (prod != cond_prod[3]) {
						if (rel_time < cond_rel_time[91]) {
							w8 = -8.660933;
						} else {
							w8 = -4.235972;
						}
					} else {
						if (hops < cond_hops[1]) {
							w8 = 5.743274;
						} else {
							w8 = 6.0592813;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						w8 = 5.7458534;
					} else {
						w8 = 6.148834;
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[81]) {
				if (prod != cond_prod[2]) {
					w8 = -5.904691;
				} else {
					if (hops < cond_hops[1]) {
						w8 = 9.146749;
					} else {
						if (hops < cond_hops[0]) {
							w8 = 9.927443;
						} else {
							w8 = 9.431592;
						}
					}
				}
			} else {
				if (prod != cond_prod[2]) {
					if (rel_time < cond_rel_time[88]) {
						if (hops < cond_hops[1]) {
							w8 = -5.8974338;
						} else {
							w8 = -5.3599434;
						}
					} else {
						if (prod != cond_prod[4]) {
							w8 = 3.836431;
						} else {
							w8 = -1.615296;
						}
					}
				} else {
					if (rel_time < cond_rel_time[63]) {
						if (hops < cond_hops[1]) {
							w8 = -8.105293;
						} else {
							w8 = -9.174547;
						}
					} else {
						if (hops < cond_hops[1]) {
							w8 = -6.2832284;
						} else {
							w8 = -6.8972664;
						}
					}
				}
			}
		}
	}
	float w9;
	if (rel_time < cond_rel_time[14]) {
		if (rel_time < cond_rel_time[28]) {
			if (rel_time < cond_rel_time[92]) {
				if (rel_time < cond_rel_time[93]) {
					if (rel_time < cond_rel_time[95]) {
						if (rel_time < cond_rel_time[97]) {
							w9 = -0.051582176;
						} else {
							w9 = -7.890767;
						}
					} else {
						if (prod != cond_prod[3]) {
							w9 = -9.172163;
						} else {
							w9 = 5.835913;
						}
					}
				} else {
					if (prod != cond_prod[1]) {
						w9 = 5.5756516;
					} else {
						w9 = -9.201331;
					}
				}
			} else {
				if (rel_time < cond_rel_time[94]) {
					if (prod != cond_prod[3]) {
						if (prod != cond_prod[0]) {
							w9 = 7.817632;
						} else {
							w9 = -5.5729527;
						}
					} else {
						if (hops < cond_hops[1]) {
							w9 = -6.007547;
						} else {
							w9 = -5.265326;
						}
					}
				} else {
					if (rel_time < cond_rel_time[96]) {
						if (prod != cond_prod[0]) {
							w9 = -5.5361204;
						} else {
							w9 = 5.6264787;
						}
					} else {
						if (rel_time < cond_rel_time[98]) {
							w9 = 5.8384285;
						} else {
							w9 = 0.08211578;
						}
					}
				}
			}
		} else {
			if (prod != cond_prod[1]) {
				if (hops < cond_hops[1]) {
					w9 = 4.4515963;
				} else {
					if (hops < cond_hops[0]) {
						w9 = 3.625303;
					} else {
						w9 = 4.6098633;
					}
				}
			} else {
				if (hops < cond_hops[2]) {
					if (hops < cond_hops[0]) {
						if (hops < cond_hops[1]) {
							w9 = -5.88642;
						} else {
							w9 = -6.445109;
						}
					} else {
						w9 = -5.357928;
					}
				} else {
					w9 = -6.7896166;
				}
			}
		}
	} else {
		if (hops < cond_hops[0]) {
			if (hops < cond_hops[1]) {
				w9 = 2.7976196;
			} else {
				w9 = 2.4737632;
			}
		} else {
			if (hops < cond_hops[2]) {
				w9 = 3.2755873;
			} else {
				w9 = 3.8644416;
			}
		}
	}
	float w10;
	if (hops < cond_hops[1]) {
		if (rel_time < cond_rel_time[99]) {
			if (rel_time < cond_rel_time[100]) {
				if (rel_time < cond_rel_time[102]) {
					if (rel_time < cond_rel_time[104]) {
						if (rel_time < cond_rel_time[107]) {
							w10 = -0.32160452;
						} else {
							w10 = 2.2444193;
						}
					} else {
						if (prod != cond_prod[1]) {
							w10 = 5.4893312;
						} else {
							w10 = -9.295871;
						}
					}
				} else {
					w10 = 5.644891;
				}
			} else {
				if (prod != cond_prod[0]) {
					w10 = 5.236776;
				} else {
					w10 = -6.1105385;
				}
			}
		} else {
			if (rel_time < cond_rel_time[101]) {
				if (prod != cond_prod[0]) {
					w10 = 8.839478;
				} else {
					w10 = -5.8273497;
				}
			} else {
				if (rel_time < cond_rel_time[103]) {
					if (prod != cond_prod[2]) {
						w10 = -6.1338024;
					} else {
						w10 = 8.969749;
					}
				} else {
					if (rel_time < cond_rel_time[105]) {
						if (prod != cond_prod[1]) {
							w10 = -6.0324006;
						} else {
							w10 = 8.954074;
						}
					} else {
						if (rel_time < cond_rel_time[108]) {
							w10 = -2.6717865;
						} else {
							w10 = 0.001186044;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[34]) {
			if (rel_time < cond_rel_time[43]) {
				if (rel_time < cond_rel_time[12]) {
					if (cons != cond_cons[2]) {
						if (rel_time < cond_rel_time[20]) {
							w10 = 0.67531705;
						} else {
							w10 = -1.0190259;
						}
					} else {
						if (rel_time < cond_rel_time[62]) {
							w10 = 0.53689003;
						} else {
							w10 = 2.7754493;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[0]) {
							w10 = -3.227242;
						} else {
							w10 = -5.1262994;
						}
					} else {
						if (hops < cond_hops[3]) {
							w10 = -1.3090721;
						} else {
							w10 = -2.4559994;
						}
					}
				}
			} else {
				if (cons != cond_cons[2]) {
					if (rel_time < cond_rel_time[42]) {
						if (hops < cond_hops[3]) {
							w10 = 4.1819415;
						} else {
							w10 = 7.19261;
						}
					} else {
						if (rel_time < cond_rel_time[16]) {
							w10 = 0.3443338;
						} else {
							w10 = 1.5066127;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[0]) {
							w10 = -1.4871128;
						} else {
							w10 = -3.5024688;
						}
					} else {
						if (hops < cond_hops[3]) {
							w10 = -0.33499023;
						} else {
							w10 = 1.4950503;
						}
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[57]) {
				if (rel_time < cond_rel_time[59]) {
					if (rel_time < cond_rel_time[49]) {
						if (rel_time < cond_rel_time[24]) {
							w10 = 0.21598852;
						} else {
							w10 = -0.7031294;
						}
					} else {
						if (cons != cond_cons[2]) {
							w10 = 2.5681288;
						} else {
							w10 = -0.9087841;
						}
					}
				} else {
					if (cons != cond_cons[1]) {
						if (rel_time < cond_rel_time[64]) {
							w10 = -5.018918;
						} else {
							w10 = -1.634895;
						}
					} else {
						if (hops < cond_hops[2]) {
							w10 = -5.85667;
						} else {
							w10 = -4.0374494;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[60]) {
					if (cons != cond_cons[2]) {
						if (hops < cond_hops[2]) {
							w10 = 5.8718557;
						} else {
							w10 = 3.7019374;
						}
					} else {
						if (hops < cond_hops[2]) {
							w10 = 1.5095401;
						} else {
							w10 = -0.5828142;
						}
					}
				} else {
					if (rel_time < cond_rel_time[106]) {
						if (rel_time < cond_rel_time[109]) {
							w10 = -0.20551042;
						} else {
							w10 = -6.864354;
						}
					} else {
						if (rel_time < cond_rel_time[36]) {
							w10 = 1.516181;
						} else {
							w10 = 0.102074414;
						}
					}
				}
			}
		}
	}
	float w11;
	if (rel_time < cond_rel_time[110]) {
		if (rel_time < cond_rel_time[111]) {
			if (rel_time < cond_rel_time[113]) {
				if (rel_time < cond_rel_time[114]) {
					if (rel_time < cond_rel_time[116]) {
						if (rel_time < cond_rel_time[118]) {
							w11 = 0.011777173;
						} else {
							w11 = -1.9710766;
						}
					} else {
						if (prod != cond_prod[4]) {
							w11 = 3.5946605;
						} else {
							w11 = -5.6962433;
						}
					}
				} else {
					if (prod != cond_prod[2]) {
						w11 = 5.597426;
					} else {
						w11 = -9.24102;
					}
				}
			} else {
				if (prod != cond_prod[3]) {
					w11 = -9.471494;
				} else {
					if (hops < cond_hops[2]) {
						w11 = 5.675819;
					} else {
						w11 = 5.955322;
					}
				}
			}
		} else {
			w11 = -9.289366;
		}
	} else {
		if (rel_time < cond_rel_time[112]) {
			if (prod != cond_prod[1]) {
				w11 = 5.620115;
			} else {
				w11 = -9.162127;
			}
		} else {
			if (prod != cond_prod[2]) {
				if (rel_time < cond_rel_time[115]) {
					if (prod != cond_prod[4]) {
						if (hops < cond_hops[1]) {
							w11 = -6.022895;
						} else {
							w11 = -5.4288096;
						}
					} else {
						w11 = 5.790057;
					}
				} else {
					if (prod != cond_prod[4]) {
						if (rel_time < cond_rel_time[88]) {
							w11 = -0.23033054;
						} else {
							w11 = 2.5275147;
						}
					} else {
						if (rel_time < cond_rel_time[84]) {
							w11 = -3.435145;
						} else {
							w11 = -0.1156935;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[115]) {
					if (hops < cond_hops[1]) {
						w11 = 8.973025;
					} else {
						w11 = 9.60269;
					}
				} else {
					if (rel_time < cond_rel_time[117]) {
						if (hops < cond_hops[1]) {
							w11 = -4.915915;
						} else {
							w11 = -4.6978407;
						}
					} else {
						if (rel_time < cond_rel_time[81]) {
							w11 = 5.296646;
						} else {
							w11 = -3.8523922;
						}
					}
				}
			}
		}
	}
	float w12;
	if (rel_time < cond_rel_time[58]) {
		if (rel_time < cond_rel_time[119]) {
			if (rel_time < cond_rel_time[120]) {
				if (rel_time < cond_rel_time[122]) {
					if (rel_time < cond_rel_time[123]) {
						if (rel_time < cond_rel_time[126]) {
							w12 = 0.0060258997;
						} else {
							w12 = -1.3270189;
						}
					} else {
						if (prod != cond_prod[1]) {
							w12 = 5.811336;
						} else {
							w12 = -9.155361;
						}
					}
				} else {
					if (prod != cond_prod[0]) {
						if (hops < cond_hops[3]) {
							w12 = 5.819212;
						} else {
							w12 = 6.337472;
						}
					} else {
						w12 = -5.8671656;
					}
				}
			} else {
				if (hops < cond_hops[1]) {
					w12 = -5.9778748;
				} else {
					w12 = -5.5987706;
				}
			}
		} else {
			if (rel_time < cond_rel_time[121]) {
				if (prod != cond_prod[0]) {
					if (hops < cond_hops[1]) {
						w12 = 8.988264;
					} else {
						w12 = 9.401777;
					}
				} else {
					w12 = -5.5326257;
				}
			} else {
				if (prod != cond_prod[1]) {
					if (rel_time < cond_rel_time[124]) {
						if (prod != cond_prod[0]) {
							w12 = -5.6908627;
						} else {
							w12 = 5.882685;
						}
					} else {
						if (rel_time < cond_rel_time[127]) {
							w12 = 5.7822247;
						} else {
							w12 = -0.054889496;
						}
					}
				} else {
					if (rel_time < cond_rel_time[125]) {
						w12 = 9.240931;
					} else {
						if (rel_time < cond_rel_time[127]) {
							w12 = -9.190672;
						} else {
							w12 = 1.7570988;
						}
					}
				}
			}
		}
	} else {
		if (prod != cond_prod[1]) {
			if (rel_time < cond_rel_time[28]) {
				if (hops < cond_hops[1]) {
					w12 = 0.24263772;
				} else {
					if (hops < cond_hops[0]) {
						w12 = -0.4177733;
					} else {
						if (hops < cond_hops[3]) {
							w12 = -0.13636069;
						} else {
							w12 = -0.3677996;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[14]) {
					if (hops < cond_hops[1]) {
						w12 = 2.2970688;
					} else {
						if (hops < cond_hops[0]) {
							w12 = 1.8371905;
						} else {
							w12 = 2.3883708;
						}
					}
				} else {
					if (hops < cond_hops[0]) {
						if (hops < cond_hops[1]) {
							w12 = 1.4576794;
						} else {
							w12 = 1.2453728;
						}
					} else {
						if (hops < cond_hops[2]) {
							w12 = 1.6476016;
						} else {
							w12 = 1.9423541;
						}
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[28]) {
				if (hops < cond_hops[1]) {
					w12 = -7.056533;
				} else {
					w12 = -8.008843;
				}
			} else {
				if (hops < cond_hops[2]) {
					if (hops < cond_hops[0]) {
						if (hops < cond_hops[1]) {
							w12 = -4.20955;
						} else {
							w12 = -4.539873;
						}
					} else {
						w12 = -3.9961505;
					}
				} else {
					w12 = -4.71348;
				}
			}
		}
	}
	float w13;
	if (rel_time < cond_rel_time[128]) {
		if (rel_time < cond_rel_time[129]) {
			if (rel_time < cond_rel_time[131]) {
				if (rel_time < cond_rel_time[71]) {
					if (rel_time < cond_rel_time[134]) {
						if (rel_time < cond_rel_time[136]) {
							w13 = -0.06412223;
						} else {
							w13 = -0.9417403;
						}
					} else {
						if (prod != cond_prod[4]) {
							w13 = 3.1046402;
						} else {
							w13 = -3.7389874;
						}
					}
				} else {
					if (prod != cond_prod[3]) {
						if (prod != cond_prod[4]) {
							w13 = -7.325047;
						} else {
							w13 = 6.054779;
						}
					} else {
						if (hops < cond_hops[1]) {
							w13 = 6.271678;
						} else {
							w13 = 5.9610724;
						}
					}
				}
			} else {
				if (prod != cond_prod[0]) {
					if (hops < cond_hops[1]) {
						w13 = 6.2949176;
					} else {
						w13 = 5.982751;
					}
				} else {
					w13 = -5.690466;
				}
			}
		} else {
			if (prod != cond_prod[0]) {
				w13 = 9.178016;
			} else {
				if (hops < cond_hops[1]) {
					w13 = -5.85991;
				} else {
					w13 = -5.4237685;
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[130]) {
			if (hops < cond_hops[1]) {
				w13 = 9.119756;
			} else {
				w13 = 9.51781;
			}
		} else {
			if (rel_time < cond_rel_time[132]) {
				if (prod != cond_prod[2]) {
					if (hops < cond_hops[1]) {
						w13 = -5.888614;
					} else {
						w13 = -5.44802;
					}
				} else {
					w13 = 9.550018;
				}
			} else {
				if (rel_time < cond_rel_time[133]) {
					if (prod != cond_prod[3]) {
						w13 = 9.389139;
					} else {
						w13 = -5.475664;
					}
				} else {
					if (rel_time < cond_rel_time[135]) {
						if (prod != cond_prod[3]) {
							w13 = -0.93680805;
						} else {
							w13 = 2.1774821;
						}
					} else {
						if (rel_time < cond_rel_time[137]) {
							w13 = 8.82147;
						} else {
							w13 = 0.056103744;
						}
					}
				}
			}
		}
	}
	float w14;
	if (prod != cond_prod[0]) {
		if (rel_time < cond_rel_time[138]) {
			if (rel_time < cond_rel_time[88]) {
				if (rel_time < cond_rel_time[81]) {
					if (rel_time < cond_rel_time[91]) {
						if (rel_time < cond_rel_time[117]) {
							w14 = -0.03126428;
						} else {
							w14 = -1.9352995;
						}
					} else {
						if (rel_time < cond_rel_time[79]) {
							w14 = 3.7601924;
						} else {
							w14 = 1.8939123;
						}
					}
				} else {
					if (hops < cond_hops[0]) {
						if (hops < cond_hops[1]) {
							w14 = -2.8789535;
						} else {
							w14 = -2.37518;
						}
					} else {
						w14 = -2.8784115;
					}
				}
			} else {
				if (prod != cond_prod[3]) {
					if (hops < cond_hops[1]) {
						w14 = 4.917883;
					} else {
						if (hops < cond_hops[0]) {
							w14 = 5.6803646;
						} else {
							w14 = 5.2147713;
						}
					}
				} else {
					w14 = -8.738179;
				}
			}
		} else {
			if (prod != cond_prod[3]) {
				if (rel_time < cond_rel_time[14]) {
					if (prod != cond_prod[4]) {
						if (rel_time < cond_rel_time[141]) {
							w14 = 5.3437295;
						} else {
							w14 = -2.1518643;
						}
					} else {
						if (rel_time < cond_rel_time[27]) {
							w14 = -4.741424;
						} else {
							w14 = 1.0625995;
						}
					}
				} else {
					if (hops < cond_hops[0]) {
						if (hops < cond_hops[1]) {
							w14 = 0.701675;
						} else {
							w14 = 0.59551996;
						}
					} else {
						if (hops < cond_hops[3]) {
							w14 = 0.8286627;
						} else {
							w14 = 1.1659853;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[58]) {
					if (hops < cond_hops[1]) {
						w14 = 5.569771;
					} else {
						w14 = 4.551834;
					}
				} else {
					if (hops < cond_hops[1]) {
						w14 = 0.093519896;
					} else {
						if (hops < cond_hops[2]) {
							w14 = -0.22612631;
						} else {
							w14 = -0.038714163;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[79]) {
			if (rel_time < cond_rel_time[139]) {
				if (rel_time < cond_rel_time[140]) {
					if (rel_time < cond_rel_time[114]) {
						if (rel_time < cond_rel_time[116]) {
							w14 = 0.28141144;
						} else {
							w14 = 4.004298;
						}
					} else {
						if (hops < cond_hops[1]) {
							w14 = -3.0286405;
						} else {
							w14 = -2.759649;
						}
					}
				} else {
					if (rel_time < cond_rel_time[80]) {
						if (hops < cond_hops[1]) {
							w14 = 2.911904;
						} else {
							w14 = 3.0496495;
						}
					} else {
						w14 = 10.356327;
					}
				}
			} else {
				if (hops < cond_hops[1]) {
					w14 = -3.696398;
				} else {
					if (hops < cond_hops[0]) {
						w14 = -2.8891296;
					} else {
						w14 = -3.462812;
					}
				}
			}
		} else {
			if (hops < cond_hops[1]) {
				if (rel_time < cond_rel_time[27]) {
					w14 = 3.0138898;
				} else {
					w14 = 3.8309755;
				}
			} else {
				if (hops < cond_hops[2]) {
					w14 = 2.4538856;
				} else {
					if (hops < cond_hops[3]) {
						w14 = 2.847433;
					} else {
						w14 = 3.3877313;
					}
				}
			}
		}
	}
	float w15;
	if (hops < cond_hops[2]) {
		if (rel_time < cond_rel_time[99]) {
			if (rel_time < cond_rel_time[100]) {
				if (rel_time < cond_rel_time[102]) {
					if (rel_time < cond_rel_time[104]) {
						if (prod != cond_prod[2]) {
							w15 = -0.023105634;
						} else {
							w15 = -0.9885018;
						}
					} else {
						if (prod != cond_prod[1]) {
							w15 = 4.1964326;
						} else {
							w15 = -7.410655;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						w15 = 2.8044796;
					} else {
						w15 = 5.914014;
					}
				}
			} else {
				if (prod != cond_prod[0]) {
					if (hops < cond_hops[1]) {
						w15 = 2.773047;
					} else {
						w15 = 5.6231194;
					}
				} else {
					if (hops < cond_hops[1]) {
						w15 = -3.236131;
					} else {
						w15 = -5.7776957;
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[101]) {
				if (prod != cond_prod[0]) {
					if (hops < cond_hops[1]) {
						w15 = 4.403869;
					} else {
						w15 = 9.353584;
					}
				} else {
					if (hops < cond_hops[1]) {
						w15 = -3.1298923;
					} else {
						w15 = -5.8155556;
					}
				}
			} else {
				if (rel_time < cond_rel_time[142]) {
					if (prod != cond_prod[1]) {
						if (prod != cond_prod[0]) {
							w15 = -3.8953397;
						} else {
							w15 = 6.1345654;
						}
					} else {
						if (hops < cond_hops[1]) {
							w15 = 4.460145;
						} else {
							w15 = 9.366378;
						}
					}
				} else {
					if (rel_time < cond_rel_time[108]) {
						if (hops < cond_hops[1]) {
							w15 = -7.811296;
						} else {
							w15 = -9.271502;
						}
					} else {
						if (rel_time < cond_rel_time[146]) {
							w15 = 5.627613;
						} else {
							w15 = -0.01100484;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[8]) {
			if (rel_time < cond_rel_time[68]) {
				if (cons != cond_cons[1]) {
					if (hops < cond_hops[3]) {
						if (rel_time < cond_rel_time[62]) {
							w15 = 0.22534588;
						} else {
							w15 = -0.3765709;
						}
					} else {
						if (cons != cond_cons[3]) {
							w15 = 0.3571788;
						} else {
							w15 = 1.3699628;
						}
					}
				} else {
					w15 = 1.2767736;
				}
			} else {
				if (cons != cond_cons[2]) {
					if (rel_time < cond_rel_time[34]) {
						if (cons != cond_cons[0]) {
							w15 = 1.7377154;
						} else {
							w15 = 0.14005464;
						}
					} else {
						if (rel_time < cond_rel_time[147]) {
							w15 = -0.8974964;
						} else {
							w15 = 2.0235083;
						}
					}
				} else {
					if (rel_time < cond_rel_time[75]) {
						if (rel_time < cond_rel_time[53]) {
							w15 = 2.774404;
						} else {
							w15 = 0.10634042;
						}
					} else {
						if (hops < cond_hops[3]) {
							w15 = 3.139352;
						} else {
							w15 = 4.9845915;
						}
					}
				}
			}
		} else {
			if (prod != cond_prod[3]) {
				if (rel_time < cond_rel_time[80]) {
					if (rel_time < cond_rel_time[140]) {
						if (rel_time < cond_rel_time[114]) {
							w15 = 0.30225602;
						} else {
							w15 = -1.5789732;
						}
					} else {
						if (rel_time < cond_rel_time[87]) {
							w15 = 4.8707542;
						} else {
							w15 = 0.24945483;
						}
					}
				} else {
					if (rel_time < cond_rel_time[91]) {
						if (prod != cond_prod[0]) {
							w15 = -3.1915414;
						} else {
							w15 = 5.2393293;
						}
					} else {
						if (rel_time < cond_rel_time[141]) {
							w15 = 0.5430043;
						} else {
							w15 = -0.27652267;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[143]) {
					if (rel_time < cond_rel_time[144]) {
						if (rel_time < cond_rel_time[148]) {
							w15 = 0.0074496535;
						} else {
							w15 = -5.434337;
						}
					} else {
						w15 = 6.979051;
					}
				} else {
					if (rel_time < cond_rel_time[145]) {
						w15 = -7.346584;
					} else {
						if (rel_time < cond_rel_time[111]) {
							w15 = 2.997975;
						} else {
							w15 = -0.9258154;
						}
					}
				}
			}
		}
	}
	float w16;
	if (cons != cond_cons[0]) {
		if (cons != cond_cons[3]) {
			if (rel_time < cond_rel_time[53]) {
				if (rel_time < cond_rel_time[0]) {
					if (hops < cond_hops[0]) {
						if (cons != cond_cons[1]) {
							w16 = 0.5390663;
						} else {
							w16 = 0.769963;
						}
					} else {
						if (cons != cond_cons[1]) {
							w16 = 0.12811375;
						} else {
							w16 = 0.46754056;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						w16 = 5.118207;
					} else {
						if (hops < cond_hops[0]) {
							w16 = 1.8750808;
						} else {
							w16 = 0.41665256;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[149]) {
					if (hops < cond_hops[1]) {
						w16 = -3.4216907;
					} else {
						if (hops < cond_hops[2]) {
							w16 = -2.1615732;
						} else {
							w16 = -0.9134805;
						}
					}
				} else {
					if (rel_time < cond_rel_time[12]) {
						if (hops < cond_hops[0]) {
							w16 = 2.1307776;
						} else {
							w16 = 1.0170238;
						}
					} else {
						if (rel_time < cond_rel_time[75]) {
							w16 = -1.4256268;
						} else {
							w16 = 0.0653534;
						}
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[89]) {
				if (rel_time < cond_rel_time[45]) {
					if (rel_time < cond_rel_time[82]) {
						if (rel_time < cond_rel_time[85]) {
							w16 = -0.101044685;
						} else {
							w16 = 1.7297251;
						}
					} else {
						if (hops < cond_hops[1]) {
							w16 = -2.5886738;
						} else {
							w16 = -1.2924175;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						w16 = 3.193065;
					} else {
						if (hops < cond_hops[3]) {
							w16 = 0.9123968;
						} else {
							w16 = 2.5685928;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[150]) {
					if (hops < cond_hops[1]) {
						w16 = -6.011634;
					} else {
						if (hops < cond_hops[2]) {
							w16 = -5.238968;
						} else {
							w16 = -4.786256;
						}
					}
				} else {
					if (rel_time < cond_rel_time[151]) {
						if (hops < cond_hops[2]) {
							w16 = 2.373092;
						} else {
							w16 = 2.7354589;
						}
					} else {
						if (rel_time < cond_rel_time[152]) {
							w16 = -1.178169;
						} else {
							w16 = 0.35125154;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[6]) {
			if (rel_time < cond_rel_time[11]) {
				if (rel_time < cond_rel_time[31]) {
					if (rel_time < cond_rel_time[36]) {
						if (rel_time < cond_rel_time[40]) {
							w16 = -0.4268333;
						} else {
							w16 = 1.0000321;
						}
					} else {
						if (hops < cond_hops[2]) {
							w16 = -1.6574594;
						} else {
							w16 = -2.2718725;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[0]) {
							w16 = 0.28504473;
						} else {
							w16 = 0.42605615;
						}
					} else {
						if (hops < cond_hops[3]) {
							w16 = 2.237277;
						} else {
							w16 = 1.9870996;
						}
					}
				}
			} else {
				if (hops < cond_hops[0]) {
					if (hops < cond_hops[1]) {
						w16 = -0.80026627;
					} else {
						w16 = -0.5987826;
					}
				} else {
					if (hops < cond_hops[2]) {
						w16 = -1.9744521;
					} else {
						if (hops < cond_hops[3]) {
							w16 = -3.1173117;
						} else {
							w16 = -2.138311;
						}
					}
				}
			}
		} else {
			if (hops < cond_hops[0]) {
				if (hops < cond_hops[1]) {
					w16 = 0.3865791;
				} else {
					w16 = 0.56986076;
				}
			} else {
				if (hops < cond_hops[3]) {
					if (hops < cond_hops[2]) {
						w16 = 0.99085563;
					} else {
						w16 = 1.0906963;
					}
				} else {
					w16 = 1.3093268;
				}
			}
		}
	}
	float w17;
	if (hops < cond_hops[3]) {
		if (rel_time < cond_rel_time[110]) {
			if (rel_time < cond_rel_time[111]) {
				if (rel_time < cond_rel_time[113]) {
					if (rel_time < cond_rel_time[154]) {
						if (rel_time < cond_rel_time[156]) {
							w17 = -0.023055047;
						} else {
							w17 = 1.3819311;
						}
					} else {
						if (prod != cond_prod[2]) {
							w17 = 2.0421169;
						} else {
							w17 = -6.4894814;
						}
					}
				} else {
					if (prod != cond_prod[3]) {
						w17 = -5.7016172;
					} else {
						if (hops < cond_hops[2]) {
							w17 = 2.8270366;
						} else {
							w17 = 1.4933765;
						}
					}
				}
			} else {
				if (hops < cond_hops[2]) {
					w17 = -5.6246614;
				} else {
					w17 = -4.421539;
				}
			}
		} else {
			if (rel_time < cond_rel_time[87]) {
				if (prod != cond_prod[3]) {
					if (prod != cond_prod[0]) {
						if (prod != cond_prod[4]) {
							w17 = 4.7358913;
						} else {
							w17 = 1.9408098;
						}
					} else {
						if (hops < cond_hops[2]) {
							w17 = -1.4871897;
						} else {
							w17 = -0.56406516;
						}
					}
				} else {
					if (rel_time < cond_rel_time[115]) {
						if (hops < cond_hops[1]) {
							w17 = -2.9919999;
						} else {
							w17 = -2.580615;
						}
					} else {
						if (hops < cond_hops[1]) {
							w17 = -5.9724054;
						} else {
							w17 = -5.2016993;
						}
					}
				}
			} else {
				if (prod != cond_prod[1]) {
					if (rel_time < cond_rel_time[91]) {
						if (rel_time < cond_rel_time[139]) {
							w17 = -0.4679333;
						} else {
							w17 = 2.9822834;
						}
					} else {
						if (rel_time < cond_rel_time[141]) {
							w17 = -0.6400036;
						} else {
							w17 = 0.17434433;
						}
					}
				} else {
					if (rel_time < cond_rel_time[91]) {
						if (hops < cond_hops[2]) {
							w17 = -4.6437745;
						} else {
							w17 = -2.963784;
						}
					} else {
						if (rel_time < cond_rel_time[141]) {
							w17 = 2.5665586;
						} else {
							w17 = -1.3150206;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[10]) {
			if (rel_time < cond_rel_time[43]) {
				if (rel_time < cond_rel_time[12]) {
					if (rel_time < cond_rel_time[20]) {
						if (rel_time < cond_rel_time[0]) {
							w17 = 0.2263867;
						} else {
							w17 = 0.61577916;
						}
					} else {
						if (cons != cond_cons[1]) {
							w17 = 1.3230436;
						} else {
							w17 = 0.35355148;
						}
					}
				} else {
					w17 = -1.0558442;
				}
			} else {
				if (rel_time < cond_rel_time[72]) {
					w17 = 3.8272655;
				} else {
					if (cons != cond_cons[3]) {
						if (rel_time < cond_rel_time[74]) {
							w17 = 1.6424819;
						} else {
							w17 = 0.6454779;
						}
					} else {
						if (rel_time < cond_rel_time[157]) {
							w17 = 0.22713129;
						} else {
							w17 = 3.6257207;
						}
					}
				}
			}
		} else {
			if (cons != cond_cons[3]) {
				if (rel_time < cond_rel_time[153]) {
					if (rel_time < cond_rel_time[133]) {
						if (prod != cond_prod[3]) {
							w17 = 0.605819;
						} else {
							w17 = -0.5167913;
						}
					} else {
						w17 = 10.031094;
					}
				} else {
					if (rel_time < cond_rel_time[155]) {
						w17 = -4.8545184;
					} else {
						if (rel_time < cond_rel_time[97]) {
							w17 = 6.0502234;
						} else {
							w17 = 0.13921572;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[33]) {
					if (rel_time < cond_rel_time[56]) {
						if (rel_time < cond_rel_time[37]) {
							w17 = -0.20053606;
						} else {
							w17 = -3.1496255;
						}
					} else {
						w17 = 2.4668808;
					}
				} else {
					w17 = -2.7627861;
				}
			}
		}
	}
	float w18;
	if (rel_time < cond_rel_time[158]) {
		if (rel_time < cond_rel_time[144]) {
			if (rel_time < cond_rel_time[160]) {
				if (rel_time < cond_rel_time[161]) {
					if (rel_time < cond_rel_time[163]) {
						if (rel_time < cond_rel_time[119]) {
							w18 = -0.015840685;
						} else {
							w18 = 1.2720678;
						}
					} else {
						if (prod != cond_prod[4]) {
							w18 = -2.980671;
						} else {
							w18 = 3.9722621;
						}
					}
				} else {
					if (prod != cond_prod[2]) {
						if (hops < cond_hops[1]) {
							w18 = -6.322647;
						} else {
							w18 = -5.5984073;
						}
					} else {
						if (hops < cond_hops[1]) {
							w18 = 8.746758;
						} else {
							w18 = 9.483241;
						}
					}
				}
			} else {
				if (prod != cond_prod[3]) {
					w18 = 8.155985;
				} else {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w18 = -6.1546946;
						} else {
							w18 = -5.6018696;
						}
					} else {
						w18 = -2.763183;
					}
				}
			}
		} else {
			if (prod != cond_prod[1]) {
				w18 = -5.8482924;
			} else {
				if (hops < cond_hops[1]) {
					w18 = 8.013468;
				} else {
					w18 = 8.431652;
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[159]) {
			w18 = -5.761344;
		} else {
			if (rel_time < cond_rel_time[118]) {
				if (prod != cond_prod[0]) {
					w18 = -5.7785873;
				} else {
					w18 = 5.637938;
				}
			} else {
				if (rel_time < cond_rel_time[162]) {
					if (prod != cond_prod[0]) {
						w18 = -8.169398;
					} else {
						w18 = 6.675356;
					}
				} else {
					if (rel_time < cond_rel_time[164]) {
						if (prod != cond_prod[3]) {
							w18 = -6.118724;
						} else {
							w18 = 6.1805654;
						}
					} else {
						if (rel_time < cond_rel_time[165]) {
							w18 = 5.4633875;
						} else {
							w18 = -0.085919574;
						}
					}
				}
			}
		}
	}
	float w19;
	if (rel_time < cond_rel_time[20]) {
		if (cons != cond_cons[3]) {
			if (hops < cond_hops[0]) {
				if (rel_time < cond_rel_time[0]) {
					if (hops < cond_hops[1]) {
						if (rel_time < cond_rel_time[7]) {
							w19 = 0.54359144;
						} else {
							w19 = 0.13756722;
						}
					} else {
						if (rel_time < cond_rel_time[62]) {
							w19 = 0.13451849;
						} else {
							w19 = 0.29219908;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						w19 = 0.6696899;
					} else {
						w19 = 0.9129392;
					}
				}
			} else {
				if (rel_time < cond_rel_time[2]) {
					if (hops < cond_hops[2]) {
						w19 = 0.17982619;
					} else {
						if (hops < cond_hops[3]) {
							w19 = -0.3943604;
						} else {
							w19 = 0.055141978;
						}
					}
				} else {
					if (cons != cond_cons[4]) {
						if (hops < cond_hops[2]) {
							w19 = 0.015349401;
						} else {
							w19 = 0.3547558;
						}
					} else {
						if (hops < cond_hops[2]) {
							w19 = 0.3050753;
						} else {
							w19 = -0.32011938;
						}
					}
				}
			}
		} else {
			if (hops < cond_hops[0]) {
				if (hops < cond_hops[1]) {
					w19 = 1.2662555;
				} else {
					w19 = 1.0252368;
				}
			} else {
				if (hops < cond_hops[3]) {
					w19 = 0.7898158;
				} else {
					w19 = 0.26657462;
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[68]) {
			if (hops < cond_hops[2]) {
				if (hops < cond_hops[1]) {
					w19 = -3.834306;
				} else {
					if (hops < cond_hops[0]) {
						w19 = -1.5872211;
					} else {
						w19 = -3.804505;
					}
				}
			} else {
				if (hops < cond_hops[3]) {
					w19 = -0.44814134;
				} else {
					w19 = 0.44516718;
				}
			}
		} else {
			if (rel_time < cond_rel_time[53]) {
				if (hops < cond_hops[1]) {
					w19 = 2.5811014;
				} else {
					if (hops < cond_hops[0]) {
						w19 = 0.95806384;
					} else {
						if (hops < cond_hops[2]) {
							w19 = -0.7038195;
						} else {
							w19 = 1.0368446;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[43]) {
					if (cons != cond_cons[4]) {
						if (hops < cond_hops[1]) {
							w19 = -3.0554304;
						} else {
							w19 = -1.1374872;
						}
					} else {
						if (hops < cond_hops[0]) {
							w19 = 1.0853983;
						} else {
							w19 = 0.4488074;
						}
					}
				} else {
					if (rel_time < cond_rel_time[72]) {
						if (hops < cond_hops[0]) {
							w19 = 4.1553106;
						} else {
							w19 = 1.7388041;
						}
					} else {
						if (rel_time < cond_rel_time[22]) {
							w19 = -0.26400003;
						} else {
							w19 = 0.01690464;
						}
					}
				}
			}
		}
	}
	float w20;
	if (rel_time < cond_rel_time[98]) {
		if (rel_time < cond_rel_time[166]) {
			if (rel_time < cond_rel_time[97]) {
				if (rel_time < cond_rel_time[128]) {
					if (rel_time < cond_rel_time[129]) {
						if (rel_time < cond_rel_time[131]) {
							w20 = -0.01684656;
						} else {
							w20 = 1.9988724;
						}
					} else {
						if (prod != cond_prod[0]) {
							w20 = 5.1019197;
						} else {
							w20 = -2.9854739;
						}
					}
				} else {
					if (prod != cond_prod[4]) {
						if (prod != cond_prod[3]) {
							w20 = 4.958035;
						} else {
							w20 = -2.7840977;
						}
					} else {
						if (hops < cond_hops[3]) {
							w20 = -5.1505;
						} else {
							w20 = -2.4432483;
						}
					}
				}
			} else {
				if (prod != cond_prod[4]) {
					if (prod != cond_prod[3]) {
						if (rel_time < cond_rel_time[92]) {
							w20 = -4.2694902;
						} else {
							w20 = -2.5034235;
						}
					} else {
						if (rel_time < cond_rel_time[95]) {
							w20 = 8.610421;
						} else {
							w20 = 1.8378787;
						}
					}
				} else {
					if (rel_time < cond_rel_time[92]) {
						w20 = 3.3486807;
					} else {
						if (hops < cond_hops[1]) {
							w20 = 2.4667597;
						} else {
							w20 = 2.2845533;
						}
					}
				}
			}
		} else {
			if (prod != cond_prod[3]) {
				if (prod != cond_prod[4]) {
					if (prod != cond_prod[0]) {
						if (hops < cond_hops[1]) {
							w20 = 5.9363832;
						} else {
							w20 = 6.3341174;
						}
					} else {
						if (rel_time < cond_rel_time[170]) {
							w20 = -2.479292;
						} else {
							w20 = 3.216191;
						}
					}
				} else {
					if (rel_time < cond_rel_time[94]) {
						w20 = -9.044336;
					} else {
						if (hops < cond_hops[1]) {
							w20 = -2.7029257;
						} else {
							w20 = -2.1557593;
						}
					}
				}
			} else {
				if (hops < cond_hops[1]) {
					w20 = -3.937108;
				} else {
					if (hops < cond_hops[0]) {
						w20 = -3.68698;
					} else {
						w20 = -3.858813;
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[167]) {
			if (prod != cond_prod[0]) {
				if (hops < cond_hops[2]) {
					w20 = -8.211731;
				} else {
					w20 = -8.82046;
				}
			} else {
				w20 = 6.0801754;
			}
		} else {
			if (rel_time < cond_rel_time[168]) {
				if (prod != cond_prod[1]) {
					if (prod != cond_prod[2]) {
						if (rel_time < cond_rel_time[171]) {
							w20 = 4.7965117;
						} else {
							w20 = 6.3843126;
						}
					} else {
						w20 = -8.4412;
					}
				} else {
					w20 = -8.632365;
				}
			} else {
				if (rel_time < cond_rel_time[169]) {
					if (prod != cond_prod[3]) {
						if (prod != cond_prod[0]) {
							w20 = 7.2031927;
						} else {
							w20 = -5.3806496;
						}
					} else {
						if (rel_time < cond_rel_time[137]) {
							w20 = -10.279736;
						} else {
							w20 = -5.780426;
						}
					}
				} else {
					if (rel_time < cond_rel_time[102]) {
						if (prod != cond_prod[2]) {
							w20 = 0.47323704;
						} else {
							w20 = -8.833162;
						}
					} else {
						if (rel_time < cond_rel_time[100]) {
							w20 = 2.9381752;
						} else {
							w20 = -0.000524265;
						}
					}
				}
			}
		}
	}
	float w21;
	if (rel_time < cond_rel_time[54]) {
		if (rel_time < cond_rel_time[57]) {
			if (rel_time < cond_rel_time[59]) {
				if (rel_time < cond_rel_time[78]) {
					if (rel_time < cond_rel_time[175]) {
						if (rel_time < cond_rel_time[150]) {
							w21 = 0.026550299;
						} else {
							w21 = 1.8747077;
						}
					} else {
						if (hops < cond_hops[1]) {
							w21 = -3.9225712;
						} else {
							w21 = -2.9860895;
						}
					}
				} else {
					if (cons != cond_cons[1]) {
						if (rel_time < cond_rel_time[177]) {
							w21 = 1.5873979;
						} else {
							w21 = 0.16466467;
						}
					} else {
						if (hops < cond_hops[2]) {
							w21 = 2.084718;
						} else {
							w21 = 2.534591;
						}
					}
				}
			} else {
				if (cons != cond_cons[1]) {
					if (hops < cond_hops[2]) {
						if (cons != cond_cons[2]) {
							w21 = -1.6507303;
						} else {
							w21 = -0.68310386;
						}
					} else {
						if (cons != cond_cons[2]) {
							w21 = -0.21383446;
						} else {
							w21 = 1.0653801;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w21 = -3.0669053;
						} else {
							w21 = -2.893308;
						}
					} else {
						if (hops < cond_hops[3]) {
							w21 = -2.3449333;
						} else {
							w21 = -1.8642884;
						}
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[172]) {
				if (hops < cond_hops[2]) {
					w21 = 4.0434055;
				} else {
					if (hops < cond_hops[3]) {
						w21 = 2.8142726;
					} else {
						w21 = 2.2422683;
					}
				}
			} else {
				if (rel_time < cond_rel_time[174]) {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[0]) {
							w21 = 0.7923933;
						} else {
							w21 = 0.72906566;
						}
					} else {
						if (hops < cond_hops[3]) {
							w21 = -0.42844123;
						} else {
							w21 = -0.6962906;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (cons != cond_cons[4]) {
							w21 = 2.5142956;
						} else {
							w21 = 1.667278;
						}
					} else {
						if (cons != cond_cons[4]) {
							w21 = 1.2239861;
						} else {
							w21 = 0.63693875;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[40]) {
			if (cons != cond_cons[2]) {
				if (cons != cond_cons[4]) {
					if (hops < cond_hops[2]) {
						if (rel_time < cond_rel_time[106]) {
							w21 = -4.2398906;
						} else {
							w21 = -2.222845;
						}
					} else {
						if (cons != cond_cons[1]) {
							w21 = -1.6052172;
						} else {
							w21 = -0.14487697;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w21 = 0.23390722;
						} else {
							w21 = -0.8660661;
						}
					} else {
						if (hops < cond_hops[3]) {
							w21 = 0.9937133;
						} else {
							w21 = 1.3996822;
						}
					}
				}
			} else {
				if (hops < cond_hops[2]) {
					if (hops < cond_hops[1]) {
						w21 = 0.1139376;
					} else {
						if (hops < cond_hops[0]) {
							w21 = -0.07957973;
						} else {
							w21 = -0.1837045;
						}
					}
				} else {
					if (hops < cond_hops[3]) {
						w21 = 1.755263;
					} else {
						w21 = 2.1467783;
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[173]) {
				if (hops < cond_hops[2]) {
					if (hops < cond_hops[1]) {
						w21 = 4.240113;
					} else {
						w21 = 5.226252;
					}
				} else {
					w21 = 1.3724934;
				}
			} else {
				if (cons != cond_cons[3]) {
					if (rel_time < cond_rel_time[176]) {
						if (cons != cond_cons[1]) {
							w21 = 0.5506136;
						} else {
							w21 = 3.2777133;
						}
					} else {
						if (rel_time < cond_rel_time[70]) {
							w21 = -4.27405;
						} else {
							w21 = 0.006135464;
						}
					}
				} else {
					if (rel_time < cond_rel_time[152]) {
						if (hops < cond_hops[3]) {
							w21 = -5.346111;
						} else {
							w21 = -4.380492;
						}
					} else {
						if (rel_time < cond_rel_time[37]) {
							w21 = 3.6981795;
						} else {
							w21 = -0.9419795;
						}
					}
				}
			}
		}
	}
	float w22;
	if (rel_time < cond_rel_time[178]) {
		if (rel_time < cond_rel_time[116]) {
			if (rel_time < cond_rel_time[165]) {
				if (rel_time < cond_rel_time[164]) {
					if (rel_time < cond_rel_time[118]) {
						if (rel_time < cond_rel_time[159]) {
							w22 = 0.0064069577;
						} else {
							w22 = 2.489371;
						}
					} else {
						if (prod != cond_prod[4]) {
							w22 = -2.1785762;
						} else {
							w22 = 9.909689;
						}
					}
				} else {
					if (prod != cond_prod[0]) {
						w22 = 4.1333504;
					} else {
						w22 = -7.798914;
					}
				}
			} else {
				if (prod != cond_prod[0]) {
					w22 = 10.172174;
				} else {
					if (hops < cond_hops[1]) {
						w22 = -5.181786;
					} else {
						w22 = -4.697758;
					}
				}
			}
		} else {
			if (hops < cond_hops[1]) {
				w22 = 7.190404;
			} else {
				w22 = 7.649861;
			}
		}
	} else {
		if (rel_time < cond_rel_time[156]) {
			if (prod != cond_prod[2]) {
				if (hops < cond_hops[2]) {
					if (hops < cond_hops[1]) {
						w22 = -7.729966;
					} else {
						w22 = -7.244942;
					}
				} else {
					w22 = -3.6841688;
				}
			} else {
				w22 = 7.504626;
			}
		} else {
			if (rel_time < cond_rel_time[145]) {
				if (prod != cond_prod[3]) {
					if (hops < cond_hops[1]) {
						w22 = 5.6619363;
					} else {
						w22 = 6.0371423;
					}
				} else {
					if (hops < cond_hops[2]) {
						w22 = -8.11544;
					} else {
						if (hops < cond_hops[3]) {
							w22 = -4.417937;
						} else {
							w22 = -3.5928788;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[110]) {
					if (prod != cond_prod[4]) {
						if (rel_time < cond_rel_time[179]) {
							w22 = 5.987198;
						} else {
							w22 = -0.8521256;
						}
					} else {
						if (hops < cond_hops[1]) {
							w22 = -3.8429601;
						} else {
							w22 = -3.355161;
						}
					}
				} else {
					if (rel_time < cond_rel_time[80]) {
						if (prod != cond_prod[3]) {
							w22 = 1.0579882;
						} else {
							w22 = -2.2681441;
						}
					} else {
						if (rel_time < cond_rel_time[139]) {
							w22 = -1.605737;
						} else {
							w22 = 0.017289288;
						}
					}
				}
			}
		}
	}
	float w23;
	if (prod != cond_prod[4]) {
		if (rel_time < cond_rel_time[180]) {
			if (rel_time < cond_rel_time[146]) {
				if (rel_time < cond_rel_time[184]) {
					if (rel_time < cond_rel_time[98]) {
						if (rel_time < cond_rel_time[188]) {
							w23 = 0.0019226326;
						} else {
							w23 = 2.174427;
						}
					} else {
						if (prod != cond_prod[1]) {
							w23 = -0.90894413;
						} else {
							w23 = -4.0795674;
						}
					}
				} else {
					if (rel_time < cond_rel_time[183]) {
						if (rel_time < cond_rel_time[189]) {
							w23 = 6.3065453;
						} else {
							w23 = 5.367102;
						}
					} else {
						if (rel_time < cond_rel_time[99]) {
							w23 = -1.1965582;
						} else {
							w23 = 1.1888589;
						}
					}
				}
			} else {
				if (prod != cond_prod[2]) {
					if (prod != cond_prod[3]) {
						if (rel_time < cond_rel_time[190]) {
							w23 = -9.185084;
						} else {
							w23 = -5.965214;
						}
					} else {
						w23 = 5.849662;
					}
				} else {
					w23 = 9.227985;
				}
			}
		} else {
			if (rel_time < cond_rel_time[182]) {
				if (prod != cond_prod[3]) {
					if (rel_time < cond_rel_time[186]) {
						if (hops < cond_hops[1]) {
							w23 = 8.980307;
						} else {
							w23 = 9.394346;
						}
					} else {
						w23 = 6.3144054;
					}
				} else {
					if (hops < cond_hops[1]) {
						w23 = -5.997363;
					} else {
						w23 = -5.561947;
					}
				}
			} else {
				if (rel_time < cond_rel_time[119]) {
					if (prod != cond_prod[3]) {
						if (prod != cond_prod[0]) {
							w23 = -7.146848;
						} else {
							w23 = -0.96673495;
						}
					} else {
						w23 = 6.493392;
					}
				} else {
					if (rel_time < cond_rel_time[121]) {
						if (prod != cond_prod[0]) {
							w23 = 3.929034;
						} else {
							w23 = -3.7349138;
						}
					} else {
						if (rel_time < cond_rel_time[163]) {
							w23 = 1.1068754;
						} else {
							w23 = -0.03518409;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[181]) {
			if (rel_time < cond_rel_time[96]) {
				if (rel_time < cond_rel_time[129]) {
					if (rel_time < cond_rel_time[73]) {
						if (rel_time < cond_rel_time[21]) {
							w23 = 0.32851672;
						} else {
							w23 = -1.7430141;
						}
					} else {
						if (rel_time < cond_rel_time[191]) {
							w23 = 3.735977;
						} else {
							w23 = 0.1928957;
						}
					}
				} else {
					if (rel_time < cond_rel_time[155]) {
						if (hops < cond_hops[3]) {
							w23 = -2.5824254;
						} else {
							w23 = -1.2356571;
						}
					} else {
						if (rel_time < cond_rel_time[166]) {
							w23 = 1.1779369;
						} else {
							w23 = -1.4917994;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[168]) {
					w23 = 3.1883733;
				} else {
					if (hops < cond_hops[3]) {
						w23 = 2.741825;
					} else {
						w23 = 2.4649408;
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[183]) {
				if (hops < cond_hops[1]) {
					w23 = -6.3310823;
				} else {
					if (hops < cond_hops[2]) {
						w23 = -5.803607;
					} else {
						w23 = -6.1613526;
					}
				}
			} else {
				if (rel_time < cond_rel_time[185]) {
					if (rel_time < cond_rel_time[187]) {
						if (rel_time < cond_rel_time[99]) {
							w23 = 1.652469;
						} else {
							w23 = -3.584127;
						}
					} else {
						w23 = 5.768435;
					}
				} else {
					if (rel_time < cond_rel_time[182]) {
						if (hops < cond_hops[1]) {
							w23 = -5.2896113;
						} else {
							w23 = -4.949379;
						}
					} else {
						if (rel_time < cond_rel_time[120]) {
							w23 = 2.8593984;
						} else {
							w23 = -0.4158018;
						}
					}
				}
			}
		}
	}
	float w24;
	if (rel_time < cond_rel_time[24]) {
		if (rel_time < cond_rel_time[22]) {
			if (rel_time < cond_rel_time[10]) {
				if (rel_time < cond_rel_time[147]) {
					if (rel_time < cond_rel_time[34]) {
						if (rel_time < cond_rel_time[43]) {
							w24 = -0.07688373;
						} else {
							w24 = 0.65776527;
						}
					} else {
						if (cons != cond_cons[2]) {
							w24 = -1.3753346;
						} else {
							w24 = 0.515448;
						}
					}
				} else {
					if (cons != cond_cons[0]) {
						if (cons != cond_cons[2]) {
							w24 = 0.99423563;
						} else {
							w24 = -0.48634088;
						}
					} else {
						if (rel_time < cond_rel_time[5]) {
							w24 = -0.69505894;
						} else {
							w24 = 0.2571102;
						}
					}
				}
			} else {
				if (cons != cond_cons[1]) {
					if (hops < cond_hops[1]) {
						if (cons != cond_cons[2]) {
							w24 = -1.8011895;
						} else {
							w24 = 0.27674428;
						}
					} else {
						if (rel_time < cond_rel_time[85]) {
							w24 = -0.8879158;
						} else {
							w24 = 0.0010442715;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						w24 = -3.9824963;
					} else {
						if (hops < cond_hops[2]) {
							w24 = -2.4623013;
						} else {
							w24 = -2.014921;
						}
					}
				}
			}
		} else {
			if (cons != cond_cons[1]) {
				if (hops < cond_hops[1]) {
					if (rel_time < cond_rel_time[48]) {
						if (rel_time < cond_rel_time[82]) {
							w24 = 1.816218;
						} else {
							w24 = 1.2006184;
						}
					} else {
						w24 = 0.3225172;
					}
				} else {
					if (hops < cond_hops[2]) {
						if (cons != cond_cons[2]) {
							w24 = 0.4396775;
						} else {
							w24 = 0.6618879;
						}
					} else {
						if (hops < cond_hops[3]) {
							w24 = 0.0662876;
						} else {
							w24 = 0.70607096;
						}
					}
				}
			} else {
				if (hops < cond_hops[1]) {
					w24 = 5.532834;
				} else {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[0]) {
							w24 = 2.948515;
						} else {
							w24 = 2.716062;
						}
					} else {
						if (hops < cond_hops[3]) {
							w24 = 2.2986376;
						} else {
							w24 = 2.7737296;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[26]) {
			if (cons != cond_cons[1]) {
				if (cons != cond_cons[2]) {
					if (hops < cond_hops[0]) {
						if (hops < cond_hops[1]) {
							w24 = -1.1680559;
						} else {
							w24 = -0.31370202;
						}
					} else {
						if (rel_time < cond_rel_time[192]) {
							w24 = -0.85126334;
						} else {
							w24 = -1.998654;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						w24 = -0.8091036;
					} else {
						if (hops < cond_hops[0]) {
							w24 = 0.018618736;
						} else {
							w24 = -0.18624586;
						}
					}
				}
			} else {
				if (hops < cond_hops[1]) {
					w24 = -5.4178123;
				} else {
					if (hops < cond_hops[2]) {
						w24 = -2.6559541;
					} else {
						w24 = -3.223274;
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[51]) {
				if (cons != cond_cons[1]) {
					if (cons != cond_cons[2]) {
						if (rel_time < cond_rel_time[193]) {
							w24 = 0.7704058;
						} else {
							w24 = 1.2604574;
						}
					} else {
						if (hops < cond_hops[2]) {
							w24 = 0.13209142;
						} else {
							w24 = -0.29304615;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						w24 = 4.201697;
					} else {
						if (hops < cond_hops[2]) {
							w24 = 2.0289605;
						} else {
							w24 = 1.6336318;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[150]) {
					if (hops < cond_hops[1]) {
						w24 = -3.0067894;
					} else {
						if (hops < cond_hops[2]) {
							w24 = -2.6193707;
						} else {
							w24 = -2.373894;
						}
					}
				} else {
					if (rel_time < cond_rel_time[175]) {
						if (hops < cond_hops[1]) {
							w24 = 0.3064029;
						} else {
							w24 = 1.2529947;
						}
					} else {
						if (rel_time < cond_rel_time[78]) {
							w24 = -1.6551332;
						} else {
							w24 = 0.0016450024;
						}
					}
				}
			}
		}
	}
	float w25;
	if (cons != cond_cons[1]) {
		if (rel_time < cond_rel_time[66]) {
			if (rel_time < cond_rel_time[194]) {
				if (rel_time < cond_rel_time[11]) {
					if (rel_time < cond_rel_time[152]) {
						if (rel_time < cond_rel_time[36]) {
							w25 = 0.016666926;
						} else {
							w25 = -2.6572459;
						}
					} else {
						if (cons != cond_cons[3]) {
							w25 = 0.30381522;
						} else {
							w25 = 1.8446953;
						}
					}
				} else {
					if (rel_time < cond_rel_time[56]) {
						if (hops < cond_hops[2]) {
							w25 = -2.5079482;
						} else {
							w25 = -4.765057;
						}
					} else {
						if (rel_time < cond_rel_time[6]) {
							w25 = -0.71282476;
						} else {
							w25 = 0.20993316;
						}
					}
				}
			} else {
				if (hops < cond_hops[2]) {
					if (prod != cond_prod[2]) {
						if (hops < cond_hops[0]) {
							w25 = -0.5263363;
						} else {
							w25 = -3.9973917;
						}
					} else {
						if (hops < cond_hops[0]) {
							w25 = -4.508705;
						} else {
							w25 = -1.2958689;
						}
					}
				} else {
					if (prod != cond_prod[1]) {
						if (hops < cond_hops[3]) {
							w25 = 0.73242444;
						} else {
							w25 = 2.1376426;
						}
					} else {
						if (hops < cond_hops[3]) {
							w25 = -2.3588953;
						} else {
							w25 = -1.2900922;
						}
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[19]) {
				if (prod != cond_prod[1]) {
					if (prod != cond_prod[2]) {
						if (rel_time < cond_rel_time[3]) {
							w25 = 0.19602449;
						} else {
							w25 = -2.0021126;
						}
					} else {
						if (rel_time < cond_rel_time[13]) {
							w25 = 1.7719468;
						} else {
							w25 = 4.14563;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						w25 = 3.6541154;
					} else {
						if (hops < cond_hops[2]) {
							w25 = 6.0537424;
						} else {
							w25 = 3.5811622;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[191]) {
					if (prod != cond_prod[1]) {
						if (prod != cond_prod[2]) {
							w25 = 0.7716863;
						} else {
							w25 = -2.7291343;
						}
					} else {
						if (rel_time < cond_rel_time[39]) {
							w25 = -2.8878646;
						} else {
							w25 = -10.729621;
						}
					}
				} else {
					if (rel_time < cond_rel_time[196]) {
						if (prod != cond_prod[2]) {
							w25 = -3.9132476;
						} else {
							w25 = 6.0644994;
						}
					} else {
						if (rel_time < cond_rel_time[197]) {
							w25 = -4.148987;
						} else {
							w25 = 0.022450753;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[32]) {
			if (rel_time < cond_rel_time[195]) {
				if (rel_time < cond_rel_time[70]) {
					if (rel_time < cond_rel_time[61]) {
						if (rel_time < cond_rel_time[106]) {
							w25 = -0.032511804;
						} else {
							w25 = 1.6343962;
						}
					} else {
						if (hops < cond_hops[3]) {
							w25 = -2.190322;
						} else {
							w25 = -1.2546036;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[0]) {
							w25 = 3.9261627;
						} else {
							w25 = 3.6498437;
						}
					} else {
						if (hops < cond_hops[3]) {
							w25 = 5.8153872;
						} else {
							w25 = 3.5616689;
						}
					}
				}
			} else {
				if (hops < cond_hops[2]) {
					if (hops < cond_hops[0]) {
						w25 = -2.575788;
					} else {
						w25 = -2.8339603;
					}
				} else {
					if (hops < cond_hops[3]) {
						w25 = -5.6753716;
					} else {
						w25 = -2.85335;
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[38]) {
				if (hops < cond_hops[2]) {
					if (hops < cond_hops[1]) {
						w25 = 2.5922127;
					} else {
						if (hops < cond_hops[0]) {
							w25 = 2.0557158;
						} else {
							w25 = 1.818751;
						}
					}
				} else {
					if (hops < cond_hops[3]) {
						w25 = 4.0180616;
					} else {
						w25 = 2.9897606;
					}
				}
			} else {
				if (hops < cond_hops[1]) {
					w25 = 0.97972775;
				} else {
					if (hops < cond_hops[0]) {
						w25 = 0.21754959;
					} else {
						if (hops < cond_hops[3]) {
							w25 = 0.796417;
						} else {
							w25 = 0.35935047;
						}
					}
				}
			}
		}
	}
	float w26;
	if (prod != cond_prod[3]) {
		if (rel_time < cond_rel_time[142]) {
			if (rel_time < cond_rel_time[99]) {
				if (rel_time < cond_rel_time[199]) {
					if (rel_time < cond_rel_time[135]) {
						if (rel_time < cond_rel_time[98]) {
							w26 = 0.024656102;
						} else {
							w26 = -1.2229179;
						}
					} else {
						if (prod != cond_prod[4]) {
							w26 = 2.1559854;
						} else {
							w26 = -3.0423632;
						}
					}
				} else {
					if (prod != cond_prod[4]) {
						if (hops < cond_hops[2]) {
							w26 = -3.2434943;
						} else {
							w26 = -6.388014;
						}
					} else {
						if (hops < cond_hops[2]) {
							w26 = 0.15531538;
						} else {
							w26 = 3.608646;
						}
					}
				}
			} else {
				if (prod != cond_prod[4]) {
					if (hops < cond_hops[2]) {
						if (rel_time < cond_rel_time[187]) {
							w26 = 3.2463162;
						} else {
							w26 = 1.3250364;
						}
					} else {
						if (prod != cond_prod[0]) {
							w26 = 8.398316;
						} else {
							w26 = 1.709871;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w26 = -0.34827754;
						} else {
							w26 = -1.8841689;
						}
					} else {
						w26 = -4.184806;
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[198]) {
				if (hops < cond_hops[2]) {
					if (hops < cond_hops[1]) {
						w26 = -4.526634;
					} else {
						if (rel_time < cond_rel_time[146]) {
							w26 = -5.436179;
						} else {
							w26 = -4.6921153;
						}
					}
				} else {
					if (rel_time < cond_rel_time[146]) {
						w26 = -9.599927;
					} else {
						w26 = -4.4574156;
					}
				}
			} else {
				if (rel_time < cond_rel_time[126]) {
					if (prod != cond_prod[0]) {
						if (rel_time < cond_rel_time[190]) {
							w26 = 0.54653287;
						} else {
							w26 = 4.307267;
						}
					} else {
						if (hops < cond_hops[1]) {
							w26 = -3.3359003;
						} else {
							w26 = -2.8194122;
						}
					}
				} else {
					if (rel_time < cond_rel_time[161]) {
						if (rel_time < cond_rel_time[163]) {
							w26 = -0.2625002;
						} else {
							w26 = -2.3163369;
						}
					} else {
						if (rel_time < cond_rel_time[158]) {
							w26 = 2.8376837;
						} else {
							w26 = -0.14551613;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[143]) {
			if (rel_time < cond_rel_time[144]) {
				if (rel_time < cond_rel_time[148]) {
					if (rel_time < cond_rel_time[200]) {
						if (rel_time < cond_rel_time[123]) {
							w26 = 0.3393629;
						} else {
							w26 = -4.145691;
						}
					} else {
						if (rel_time < cond_rel_time[124]) {
							w26 = 10.151024;
						} else {
							w26 = 4.3851094;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w26 = -3.0877419;
						} else {
							w26 = -2.7832332;
						}
					} else {
						w26 = -1.3928794;
					}
				}
			} else {
				if (hops < cond_hops[2]) {
					w26 = 4.8146453;
				} else {
					if (hops < cond_hops[3]) {
						w26 = 1.390551;
					} else {
						w26 = 1.6418498;
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[145]) {
				if (hops < cond_hops[2]) {
					if (hops < cond_hops[1]) {
						if (rel_time < cond_rel_time[156]) {
							w26 = -3.8636186;
						} else {
							w26 = -4.2944255;
						}
					} else {
						if (rel_time < cond_rel_time[156]) {
							w26 = -3.619906;
						} else {
							w26 = -3.9343266;
						}
					}
				} else {
					if (rel_time < cond_rel_time[156]) {
						w26 = -1.8422409;
					} else {
						if (hops < cond_hops[3]) {
							w26 = -2.2168806;
						} else {
							w26 = -1.807289;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[111]) {
					if (hops < cond_hops[2]) {
						if (rel_time < cond_rel_time[113]) {
							w26 = 2.2409787;
						} else {
							w26 = 1.8772492;
						}
					} else {
						if (hops < cond_hops[3]) {
							w26 = 1.2106477;
						} else {
							w26 = 1.7669574;
						}
					}
				} else {
					if (rel_time < cond_rel_time[90]) {
						if (rel_time < cond_rel_time[115]) {
							w26 = -0.21332812;
						} else {
							w26 = -1.7471803;
						}
					} else {
						if (rel_time < cond_rel_time[201]) {
							w26 = 2.024434;
						} else {
							w26 = -0.27194896;
						}
					}
				}
			}
		}
	}
	float w27;
	if (prod != cond_prod[2]) {
		if (rel_time < cond_rel_time[197]) {
			if (rel_time < cond_rel_time[35]) {
				if (rel_time < cond_rel_time[136]) {
					if (rel_time < cond_rel_time[204]) {
						if (prod != cond_prod[1]) {
							w27 = -0.011654642;
						} else {
							w27 = -1.8221945;
						}
					} else {
						if (prod != cond_prod[4]) {
							w27 = 1.4971362;
						} else {
							w27 = -1.2336656;
						}
					}
				} else {
					if (rel_time < cond_rel_time[30]) {
						w27 = 11.766081;
					} else {
						if (prod != cond_prod[3]) {
							w27 = -3.2071948;
						} else {
							w27 = 2.0701935;
						}
					}
				}
			} else {
				if (prod != cond_prod[4]) {
					if (hops < cond_hops[2]) {
						if (rel_time < cond_rel_time[191]) {
							w27 = -2.659501;
						} else {
							w27 = -1.4094303;
						}
					} else {
						if (rel_time < cond_rel_time[206]) {
							w27 = -3.0213416;
						} else {
							w27 = -4.7297106;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[0]) {
							w27 = 0.82721114;
						} else {
							w27 = 1.0583336;
						}
					} else {
						w27 = 4.031268;
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[65]) {
				if (prod != cond_prod[1]) {
					w27 = -7.09474;
				} else {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w27 = 4.3025928;
						} else {
							w27 = 4.6708817;
						}
					} else {
						w27 = 7.5176125;
					}
				}
			} else {
				if (rel_time < cond_rel_time[203]) {
					if (prod != cond_prod[4]) {
						if (rel_time < cond_rel_time[71]) {
							w27 = 1.6394236;
						} else {
							w27 = 4.9385476;
						}
					} else {
						if (hops < cond_hops[2]) {
							w27 = -1.0012127;
						} else {
							w27 = -4.065558;
						}
					}
				} else {
					if (rel_time < cond_rel_time[132]) {
						if (prod != cond_prod[1]) {
							w27 = 0.09763341;
						} else {
							w27 = -5.3553867;
						}
					} else {
						if (rel_time < cond_rel_time[95]) {
							w27 = 1.8290417;
						} else {
							w27 = 0.0408576;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[202]) {
			if (rel_time < cond_rel_time[160]) {
				if (rel_time < cond_rel_time[124]) {
					if (rel_time < cond_rel_time[205]) {
						if (rel_time < cond_rel_time[121]) {
							w27 = -0.40584627;
						} else {
							w27 = 10.922469;
						}
					} else {
						if (rel_time < cond_rel_time[163]) {
							w27 = -7.375429;
						} else {
							w27 = -3.7602313;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						w27 = 2.951353;
					} else {
						w27 = 3.3169055;
					}
				}
			} else {
				if (rel_time < cond_rel_time[162]) {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[0]) {
							w27 = -2.942521;
						} else {
							w27 = -2.7425954;
						}
					} else {
						w27 = -3.1944742;
					}
				} else {
					w27 = -3.9280543;
				}
			}
		} else {
			if (rel_time < cond_rel_time[156]) {
				if (rel_time < cond_rel_time[116]) {
					if (hops < cond_hops[1]) {
						w27 = 4.875584;
					} else {
						w27 = 5.5205016;
					}
				} else {
					if (hops < cond_hops[1]) {
						w27 = 3.6735044;
					} else {
						if (hops < cond_hops[0]) {
							w27 = 4.0309477;
						} else {
							w27 = 3.8209324;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[114]) {
					w27 = -7.291117;
				} else {
					if (rel_time < cond_rel_time[81]) {
						if (rel_time < cond_rel_time[117]) {
							w27 = -0.11161176;
						} else {
							w27 = 1.9347258;
						}
					} else {
						if (rel_time < cond_rel_time[63]) {
							w27 = -1.4550095;
						} else {
							w27 = -0.41590557;
						}
					}
				}
			}
		}
	}
	float w28;
	if (prod != cond_prod[2]) {
		if (rel_time < cond_rel_time[27]) {
			if (rel_time < cond_rel_time[207]) {
				if (rel_time < cond_rel_time[156]) {
					if (rel_time < cond_rel_time[165]) {
						if (rel_time < cond_rel_time[164]) {
							w28 = 0.012143551;
						} else {
							w28 = 1.5856268;
						}
					} else {
						if (rel_time < cond_rel_time[116]) {
							w28 = -2.3697088;
						} else {
							w28 = -1.7625256;
						}
					}
				} else {
					if (rel_time < cond_rel_time[145]) {
						if (prod != cond_prod[3]) {
							w28 = 3.0056067;
						} else {
							w28 = -1.5740473;
						}
					} else {
						if (rel_time < cond_rel_time[111]) {
							w28 = 0.63417965;
						} else {
							w28 = 0.01967265;
						}
					}
				}
			} else {
				if (prod != cond_prod[1]) {
					if (prod != cond_prod[0]) {
						if (rel_time < cond_rel_time[88]) {
							w28 = -0.93859637;
						} else {
							w28 = -2.0756474;
						}
					} else {
						if (rel_time < cond_rel_time[79]) {
							w28 = -1.3767717;
						} else {
							w28 = 1.3438603;
						}
					}
				} else {
					if (hops < cond_hops[3]) {
						if (hops < cond_hops[2]) {
							w28 = 1.4146523;
						} else {
							w28 = 1.0713283;
						}
					} else {
						w28 = 2.4954393;
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[58]) {
				if (rel_time < cond_rel_time[63]) {
					if (hops < cond_hops[1]) {
						w28 = 1.8888289;
					} else {
						if (hops < cond_hops[2]) {
							w28 = 1.1832626;
						} else {
							w28 = 1.6144241;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						w28 = 2.821408;
					} else {
						w28 = 2.3107429;
					}
				}
			} else {
				if (prod != cond_prod[1]) {
					if (rel_time < cond_rel_time[28]) {
						if (hops < cond_hops[2]) {
							w28 = -0.01897899;
						} else {
							w28 = 0.47119483;
						}
					} else {
						if (hops < cond_hops[2]) {
							w28 = 0.52094823;
						} else {
							w28 = 0.7818201;
						}
					}
				} else {
					if (rel_time < cond_rel_time[28]) {
						if (hops < cond_hops[1]) {
							w28 = -1.7997116;
						} else {
							w28 = -2.2879868;
						}
					} else {
						if (hops < cond_hops[3]) {
							w28 = -0.40392324;
						} else {
							w28 = -1.0222611;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[196]) {
			if (rel_time < cond_rel_time[30]) {
				if (rel_time < cond_rel_time[29]) {
					if (rel_time < cond_rel_time[208]) {
						if (hops < cond_hops[2]) {
							w28 = -1.6790978;
						} else {
							w28 = 1.5644515;
						}
					} else {
						if (hops < cond_hops[2]) {
							w28 = 2.2300656;
						} else {
							w28 = -0.5895033;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						w28 = 0.28420085;
					} else {
						if (hops < cond_hops[2]) {
							w28 = -1.4472672;
						} else {
							w28 = -2.9635303;
						}
					}
				}
			} else {
				if (hops < cond_hops[2]) {
					if (rel_time < cond_rel_time[134]) {
						if (hops < cond_hops[1]) {
							w28 = 3.9673793;
						} else {
							w28 = 4.2710385;
						}
					} else {
						if (hops < cond_hops[1]) {
							w28 = 1.935022;
						} else {
							w28 = 2.175421;
						}
					}
				} else {
					w28 = 4.694056;
				}
			}
		} else {
			if (rel_time < cond_rel_time[203]) {
				if (hops < cond_hops[1]) {
					w28 = -4.41088;
				} else {
					if (hops < cond_hops[2]) {
						w28 = -4.8325825;
					} else {
						w28 = -5.2468514;
					}
				}
			} else {
				if (rel_time < cond_rel_time[132]) {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w28 = 2.7260072;
						} else {
							w28 = 2.9132023;
						}
					} else {
						w28 = 2.3453536;
					}
				} else {
					if (rel_time < cond_rel_time[97]) {
						w28 = -10.413239;
					} else {
						if (rel_time < cond_rel_time[95]) {
							w28 = -2.0994425;
						} else {
							w28 = -0.019700373;
						}
					}
				}
			}
		}
	}
	float w29;
	if (prod != cond_prod[0]) {
		if (rel_time < cond_rel_time[110]) {
			if (rel_time < cond_rel_time[111]) {
				if (rel_time < cond_rel_time[158]) {
					if (rel_time < cond_rel_time[148]) {
						if (rel_time < cond_rel_time[125]) {
							w29 = -0.013821618;
						} else {
							w29 = -0.94991016;
						}
					} else {
						if (prod != cond_prod[3]) {
							w29 = 2.0810928;
						} else {
							w29 = -1.3351667;
						}
					}
				} else {
					if (rel_time < cond_rel_time[162]) {
						if (rel_time < cond_rel_time[118]) {
							w29 = -2.7259145;
						} else {
							w29 = -1.458197;
						}
					} else {
						if (prod != cond_prod[1]) {
							w29 = 0.2717254;
						} else {
							w29 = -1.4376457;
						}
					}
				}
			} else {
				if (hops < cond_hops[3]) {
					if (hops < cond_hops[2]) {
						w29 = -2.3079934;
					} else {
						w29 = -1.7128148;
					}
				} else {
					w29 = -4.1175666;
				}
			}
		} else {
			if (rel_time < cond_rel_time[90]) {
				if (prod != cond_prod[3]) {
					if (rel_time < cond_rel_time[115]) {
						if (prod != cond_prod[1]) {
							w29 = 1.7682066;
						} else {
							w29 = -7.507222;
						}
					} else {
						if (hops < cond_hops[1]) {
							w29 = 5.311241;
						} else {
							w29 = 6.0488386;
						}
					}
				} else {
					if (hops < cond_hops[3]) {
						if (rel_time < cond_rel_time[115]) {
							w29 = -0.13697484;
						} else {
							w29 = -0.7062896;
						}
					} else {
						w29 = -3.09622;
					}
				}
			} else {
				if (rel_time < cond_rel_time[201]) {
					if (prod != cond_prod[3]) {
						if (rel_time < cond_rel_time[87]) {
							w29 = 0.23493946;
						} else {
							w29 = -1.4660555;
						}
					} else {
						if (rel_time < cond_rel_time[117]) {
							w29 = 0.55677074;
						} else {
							w29 = 1.8075794;
						}
					}
				} else {
					if (rel_time < cond_rel_time[79]) {
						if (prod != cond_prod[1]) {
							w29 = 2.3884857;
						} else {
							w29 = -2.1404166;
						}
					} else {
						if (prod != cond_prod[4]) {
							w29 = 0.032374024;
						} else {
							w29 = -0.32530078;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[209]) {
			if (rel_time < cond_rel_time[180]) {
				if (rel_time < cond_rel_time[142]) {
					if (rel_time < cond_rel_time[187]) {
						if (rel_time < cond_rel_time[99]) {
							w29 = 0.1907375;
						} else {
							w29 = -3.493052;
						}
					} else {
						if (hops < cond_hops[2]) {
							w29 = 1.7122817;
						} else {
							w29 = 4.475733;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						w29 = -1.696025;
					} else {
						if (hops < cond_hops[3]) {
							w29 = -1.4243684;
						} else {
							w29 = -1.5898504;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[182]) {
					if (hops < cond_hops[1]) {
						w29 = 3.3824327;
					} else {
						w29 = 3.1665378;
					}
				} else {
					w29 = 6.9716973;
				}
			}
		} else {
			if (rel_time < cond_rel_time[210]) {
				if (rel_time < cond_rel_time[163]) {
					if (rel_time < cond_rel_time[121]) {
						if (rel_time < cond_rel_time[119]) {
							w29 = -2.5180612;
						} else {
							w29 = -1.7989389;
						}
					} else {
						if (hops < cond_hops[0]) {
							w29 = 1.4918238;
						} else {
							w29 = 1.8115822;
						}
					}
				} else {
					if (rel_time < cond_rel_time[161]) {
						if (hops < cond_hops[1]) {
							w29 = -3.867218;
						} else {
							w29 = -2.9871786;
						}
					} else {
						if (hops < cond_hops[1]) {
							w29 = -4.735576;
						} else {
							w29 = -4.2949734;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[162]) {
					if (rel_time < cond_rel_time[118]) {
						if (hops < cond_hops[2]) {
							w29 = 1.6488354;
						} else {
							w29 = 1.4098333;
						}
					} else {
						w29 = 4.4717546;
					}
				} else {
					if (rel_time < cond_rel_time[116]) {
						if (rel_time < cond_rel_time[165]) {
							w29 = -4.645262;
						} else {
							w29 = -1.1852931;
						}
					} else {
						if (rel_time < cond_rel_time[114]) {
							w29 = 1.3123811;
						} else {
							w29 = 0.021502437;
						}
					}
				}
			}
		}
	}
	float w30;
	if (hops < cond_hops[1]) {
		if (rel_time < cond_rel_time[22]) {
			if (rel_time < cond_rel_time[10]) {
				if (rel_time < cond_rel_time[20]) {
					if (cons != cond_cons[3]) {
						if (cons != cond_cons[4]) {
							w30 = 0.3095827;
						} else {
							w30 = 0.084246784;
						}
					} else {
						w30 = 0.64914954;
					}
				} else {
					if (rel_time < cond_rel_time[68]) {
						w30 = -1.9036154;
					} else {
						if (rel_time < cond_rel_time[53]) {
							w30 = 1.3072289;
						} else {
							w30 = -0.2279216;
						}
					}
				}
			} else {
				if (cons != cond_cons[1]) {
					if (rel_time < cond_rel_time[85]) {
						w30 = -1.6279948;
					} else {
						if (rel_time < cond_rel_time[213]) {
							w30 = 0.1245322;
						} else {
							w30 = -0.5568239;
						}
					}
				} else {
					w30 = -1.9826374;
				}
			}
		} else {
			if (rel_time < cond_rel_time[44]) {
				if (rel_time < cond_rel_time[211]) {
					if (rel_time < cond_rel_time[82]) {
						w30 = 0.8949898;
					} else {
						w30 = 0.724455;
					}
				} else {
					w30 = 2.779768;
				}
			} else {
				if (rel_time < cond_rel_time[192]) {
					if (cons != cond_cons[1]) {
						if (rel_time < cond_rel_time[24]) {
							w30 = 0.2926702;
						} else {
							w30 = -0.70989025;
						}
					} else {
						w30 = -2.7010615;
					}
				} else {
					if (rel_time < cond_rel_time[46]) {
						if (rel_time < cond_rel_time[214]) {
							w30 = 0.40933934;
						} else {
							w30 = 2.1134672;
						}
					} else {
						if (rel_time < cond_rel_time[78]) {
							w30 = -0.59297407;
						} else {
							w30 = -0.03665566;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[104]) {
			if (rel_time < cond_rel_time[107]) {
				if (rel_time < cond_rel_time[184]) {
					if (rel_time < cond_rel_time[137]) {
						if (rel_time < cond_rel_time[167]) {
							w30 = 0.020686233;
						} else {
							w30 = 0.5426492;
						}
					} else {
						if (prod != cond_prod[3]) {
							w30 = 6.51069;
						} else {
							w30 = -2.5067701;
						}
					}
				} else {
					if (prod != cond_prod[2]) {
						if (prod != cond_prod[4]) {
							w30 = 2.9943964;
						} else {
							w30 = -1.4687837;
						}
					} else {
						if (rel_time < cond_rel_time[199]) {
							w30 = -4.6604505;
						} else {
							w30 = -1.4261295;
						}
					}
				}
			} else {
				if (prod != cond_prod[3]) {
					w30 = -7.3291917;
				} else {
					w30 = 5.9934506;
				}
			}
		} else {
			if (rel_time < cond_rel_time[102]) {
				if (prod != cond_prod[1]) {
					w30 = 2.4712787;
				} else {
					if (hops < cond_hops[2]) {
						w30 = -3.5257607;
					} else {
						w30 = -5.759142;
					}
				}
			} else {
				if (rel_time < cond_rel_time[212]) {
					if (prod != cond_prod[3]) {
						if (rel_time < cond_rel_time[209]) {
							w30 = 0.1811739;
						} else {
							w30 = -4.5954576;
						}
					} else {
						if (rel_time < cond_rel_time[215]) {
							w30 = -5.1266456;
						} else {
							w30 = 0.42011076;
						}
					}
				} else {
					if (rel_time < cond_rel_time[125]) {
						if (prod != cond_prod[2]) {
							w30 = 0.08010593;
						} else {
							w30 = 2.9838839;
						}
					} else {
						if (rel_time < cond_rel_time[216]) {
							w30 = -1.8304294;
						} else {
							w30 = 0.057752483;
						}
					}
				}
			}
		}
	}
	float w31;
	if (cons != cond_cons[0]) {
		if (rel_time < cond_rel_time[83]) {
			if (rel_time < cond_rel_time[217]) {
				if (rel_time < cond_rel_time[218]) {
					if (rel_time < cond_rel_time[219]) {
						if (rel_time < cond_rel_time[220]) {
							w31 = 0.07018685;
						} else {
							w31 = -0.6566642;
						}
					} else {
						if (rel_time < cond_rel_time[172]) {
							w31 = 1.8752383;
						} else {
							w31 = 0.74371624;
						}
					}
				} else {
					if (rel_time < cond_rel_time[106]) {
						if (cons != cond_cons[2]) {
							w31 = -1.8528178;
						} else {
							w31 = 0.14466006;
						}
					} else {
						if (rel_time < cond_rel_time[173]) {
							w31 = 0.9775423;
						} else {
							w31 = -0.010811872;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[195]) {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w31 = 2.0269876;
						} else {
							w31 = 1.856556;
						}
					} else {
						if (hops < cond_hops[3]) {
							w31 = 2.898593;
						} else {
							w31 = 1.7769651;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w31 = 0.30742577;
						} else {
							w31 = 0.08014856;
						}
					} else {
						if (hops < cond_hops[3]) {
							w31 = 2.062245;
						} else {
							w31 = 0.124827564;
						}
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[32]) {
				if (cons != cond_cons[2]) {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[1]) {
							w31 = -1.0965877;
						} else {
							w31 = -1.4306012;
						}
					} else {
						if (hops < cond_hops[3]) {
							w31 = -3.2379115;
						} else {
							w31 = -0.12801985;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[0]) {
							w31 = -0.34006014;
						} else {
							w31 = -0.62386143;
						}
					} else {
						if (hops < cond_hops[3]) {
							w31 = -1.5378534;
						} else {
							w31 = -0.63259697;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[33]) {
					if (rel_time < cond_rel_time[17]) {
						if (hops < cond_hops[2]) {
							w31 = 0.07183476;
						} else {
							w31 = -1.2057886;
						}
					} else {
						if (hops < cond_hops[2]) {
							w31 = 2.3762379;
						} else {
							w31 = 3.475261;
						}
					}
				} else {
					if (cons != cond_cons[3]) {
						if (cons != cond_cons[1]) {
							w31 = -0.014836909;
						} else {
							w31 = 0.7941683;
						}
					} else {
						if (hops < cond_hops[2]) {
							w31 = -0.9844227;
						} else {
							w31 = -2.3625574;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[43]) {
			if (rel_time < cond_rel_time[20]) {
				if (hops < cond_hops[0]) {
					if (rel_time < cond_rel_time[2]) {
						if (hops < cond_hops[1]) {
							w31 = 0.13954268;
						} else {
							w31 = 0.07739319;
						}
					} else {
						if (hops < cond_hops[1]) {
							w31 = 0.19593675;
						} else {
							w31 = 0.462045;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						if (rel_time < cond_rel_time[2]) {
							w31 = 0.09513209;
						} else {
							w31 = -0.16372424;
						}
					} else {
						if (rel_time < cond_rel_time[2]) {
							w31 = -0.14168623;
						} else {
							w31 = 0.32611933;
						}
					}
				}
			} else {
				if (hops < cond_hops[1]) {
					w31 = -2.7347863;
				} else {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[0]) {
							w31 = -0.75945574;
						} else {
							w31 = -1.7118804;
						}
					} else {
						if (hops < cond_hops[3]) {
							w31 = 0.11753194;
						} else {
							w31 = 0.045965966;
						}
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[34]) {
				if (hops < cond_hops[0]) {
					if (hops < cond_hops[1]) {
						w31 = 0.30967477;
					} else {
						w31 = 1.3346094;
					}
				} else {
					if (hops < cond_hops[2]) {
						w31 = -0.19006732;
					} else {
						if (hops < cond_hops[3]) {
							w31 = 0.6509639;
						} else {
							w31 = 1.1812557;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[54]) {
					if (rel_time < cond_rel_time[57]) {
						if (rel_time < cond_rel_time[59]) {
							w31 = -0.018541927;
						} else {
							w31 = -1.1220108;
						}
					} else {
						if (hops < cond_hops[2]) {
							w31 = 1.1045089;
						} else {
							w31 = 0.47295722;
						}
					}
				} else {
					if (rel_time < cond_rel_time[31]) {
						if (rel_time < cond_rel_time[36]) {
							w31 = -0.38898894;
						} else {
							w31 = -1.0494566;
						}
					} else {
						if (rel_time < cond_rel_time[6]) {
							w31 = -0.08032019;
						} else {
							w31 = 0.23462385;
						}
					}
				}
			}
		}
	}
	float w32;
	if (prod != cond_prod[3]) {
		if (rel_time < cond_rel_time[126]) {
			if (rel_time < cond_rel_time[180]) {
				if (rel_time < cond_rel_time[142]) {
					if (rel_time < cond_rel_time[99]) {
						if (rel_time < cond_rel_time[199]) {
							w32 = 0.014137004;
						} else {
							w32 = -0.7515667;
						}
					} else {
						if (prod != cond_prod[4]) {
							w32 = 1.4498054;
						} else {
							w32 = -0.96993464;
						}
					}
				} else {
					if (prod != cond_prod[4]) {
						if (rel_time < cond_rel_time[190]) {
							w32 = -2.959557;
						} else {
							w32 = 0.05087569;
						}
					} else {
						if (rel_time < cond_rel_time[190]) {
							w32 = 2.5664556;
						} else {
							w32 = 0.60754067;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[221]) {
					w32 = 2.58712;
				} else {
					if (hops < cond_hops[0]) {
						if (hops < cond_hops[1]) {
							w32 = 2.3440194;
						} else {
							w32 = 2.6623168;
						}
					} else {
						if (hops < cond_hops[2]) {
							w32 = 2.3625114;
						} else {
							w32 = 2.2197418;
						}
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[123]) {
				if (prod != cond_prod[0]) {
					if (rel_time < cond_rel_time[182]) {
						if (prod != cond_prod[1]) {
							w32 = -2.4811068;
						} else {
							w32 = 5.1320887;
						}
					} else {
						if (hops < cond_hops[2]) {
							w32 = -4.3292394;
						} else {
							w32 = -2.8951283;
						}
					}
				} else {
					if (rel_time < cond_rel_time[182]) {
						if (hops < cond_hops[1]) {
							w32 = 1.7189658;
						} else {
							w32 = 1.5013516;
						}
					} else {
						w32 = 3.4300559;
					}
				}
			} else {
				if (rel_time < cond_rel_time[200]) {
					if (rel_time < cond_rel_time[121]) {
						if (prod != cond_prod[0]) {
							w32 = 0.76053464;
						} else {
							w32 = -1.2639712;
						}
					} else {
						if (rel_time < cond_rel_time[205]) {
							w32 = 4.3016624;
						} else {
							w32 = 3.4225657;
						}
					}
				} else {
					if (rel_time < cond_rel_time[164]) {
						if (rel_time < cond_rel_time[162]) {
							w32 = -0.2025713;
						} else {
							w32 = -2.0879354;
						}
					} else {
						if (rel_time < cond_rel_time[145]) {
							w32 = 1.0158348;
						} else {
							w32 = -0.0637967;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[188]) {
			if (rel_time < cond_rel_time[93]) {
				if (rel_time < cond_rel_time[133]) {
					if (rel_time < cond_rel_time[222]) {
						if (rel_time < cond_rel_time[203]) {
							w32 = -0.39256456;
						} else {
							w32 = 2.8683991;
						}
					} else {
						if (rel_time < cond_rel_time[132]) {
							w32 = -1.6376916;
						} else {
							w32 = -2.4019654;
						}
					}
				} else {
					if (rel_time < cond_rel_time[95]) {
						if (hops < cond_hops[1]) {
							w32 = 3.4228;
						} else {
							w32 = 2.981622;
						}
					} else {
						if (hops < cond_hops[1]) {
							w32 = 0.86865324;
						} else {
							w32 = 0.6433587;
						}
					}
				}
			} else {
				if (hops < cond_hops[3]) {
					w32 = -2.1127543;
				} else {
					w32 = -2.315278;
				}
			}
		} else {
			if (rel_time < cond_rel_time[104]) {
				if (rel_time < cond_rel_time[184]) {
					if (rel_time < cond_rel_time[171]) {
						if (hops < cond_hops[0]) {
							w32 = 2.547772;
						} else {
							w32 = 2.3702767;
						}
					} else {
						if (hops < cond_hops[1]) {
							w32 = -3.0016918;
						} else {
							w32 = -1.3033911;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						if (rel_time < cond_rel_time[107]) {
							w32 = 5.869356;
						} else {
							w32 = 4.7754;
						}
					} else {
						if (rel_time < cond_rel_time[107]) {
							w32 = 4.4003873;
						} else {
							w32 = 3.0061035;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[215]) {
					if (hops < cond_hops[2]) {
						if (hops < cond_hops[0]) {
							w32 = -1.8985889;
						} else {
							w32 = -2.0335066;
						}
					} else {
						w32 = -4.054772;
					}
				} else {
					if (rel_time < cond_rel_time[198]) {
						if (hops < cond_hops[2]) {
							w32 = 2.1232793;
						} else {
							w32 = 4.066605;
						}
					} else {
						if (rel_time < cond_rel_time[221]) {
							w32 = -3.184018;
						} else {
							w32 = 0.40436593;
						}
					}
				}
			}
		}
	}
	float w33;
	if (rel_time < cond_rel_time[14]) {
		if (rel_time < cond_rel_time[179]) {
			if (rel_time < cond_rel_time[156]) {
				if (rel_time < cond_rel_time[178]) {
					if (rel_time < cond_rel_time[116]) {
						if (rel_time < cond_rel_time[165]) {
							w33 = 0.0062878574;
						} else {
							w33 = -0.8302102;
						}
					} else {
						if (hops < cond_hops[2]) {
							w33 = 1.292556;
						} else {
							w33 = 1.20891;
						}
					}
				} else {
					if (prod != cond_prod[2]) {
						if (hops < cond_hops[2]) {
							w33 = -1.3435895;
						} else {
							w33 = -0.42414948;
						}
					} else {
						if (hops < cond_hops[1]) {
							w33 = 0.9512868;
						} else {
							w33 = 1.3532941;
						}
					}
				}
			} else {
				if (prod != cond_prod[1]) {
					if (rel_time < cond_rel_time[145]) {
						if (hops < cond_hops[2]) {
							w33 = -1.6268064;
						} else {
							w33 = -0.6319952;
						}
					} else {
						if (hops < cond_hops[1]) {
							w33 = -2.0775537;
						} else {
							w33 = -1.8770673;
						}
					}
				} else {
					if (rel_time < cond_rel_time[145]) {
						if (hops < cond_hops[1]) {
							w33 = 1.6283479;
						} else {
							w33 = 1.7671192;
						}
					} else {
						if (hops < cond_hops[3]) {
							w33 = 3.4012687;
						} else {
							w33 = 4.1071644;
						}
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[110]) {
				if (prod != cond_prod[0]) {
					if (rel_time < cond_rel_time[114]) {
						if (rel_time < cond_rel_time[154]) {
							w33 = -1.9101084;
						} else {
							w33 = -3.7439;
						}
					} else {
						if (prod != cond_prod[3]) {
							w33 = -1.052428;
						} else {
							w33 = 0.22646591;
						}
					}
				} else {
					if (rel_time < cond_rel_time[154]) {
						if (hops < cond_hops[1]) {
							w33 = 0.93992984;
						} else {
							w33 = 0.82579976;
						}
					} else {
						if (hops < cond_hops[3]) {
							w33 = 0.45055586;
						} else {
							w33 = 1.3818579;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[80]) {
					if (prod != cond_prod[1]) {
						if (rel_time < cond_rel_time[84]) {
							w33 = -0.18917304;
						} else {
							w33 = 1.2448195;
						}
					} else {
						if (rel_time < cond_rel_time[112]) {
							w33 = -3.753819;
						} else {
							w33 = 1.8348124;
						}
					}
				} else {
					if (rel_time < cond_rel_time[201]) {
						if (prod != cond_prod[0]) {
							w33 = -0.43457395;
						} else {
							w33 = 4.6738725;
						}
					} else {
						if (prod != cond_prod[3]) {
							w33 = 0.054351054;
						} else {
							w33 = -0.32861504;
						}
					}
				}
			}
		}
	} else {
		if (hops < cond_hops[2]) {
			if (hops < cond_hops[1]) {
				w33 = 0.46785071;
			} else {
				if (hops < cond_hops[0]) {
					w33 = 0.36758533;
				} else {
					w33 = 0.4531221;
				}
			}
		} else {
			if (hops < cond_hops[3]) {
				w33 = 0.52471393;
			} else {
				w33 = 0.67568463;
			}
		}
	}
	float w34;
	if (prod != cond_prod[3]) {
		if (rel_time < cond_rel_time[94]) {
			if (rel_time < cond_rel_time[166]) {
				if (rel_time < cond_rel_time[97]) {
					if (rel_time < cond_rel_time[128]) {
						if (rel_time < cond_rel_time[224]) {
							w34 = 0.009549137;
						} else {
							w34 = -0.9623013;
						}
					} else {
						if (prod != cond_prod[4]) {
							w34 = 1.7809899;
						} else {
							w34 = -2.1986752;
						}
					}
				} else {
					if (prod != cond_prod[4]) {
						if (prod != cond_prod[1]) {
							w34 = -1.2004222;
						} else {
							w34 = -2.0754626;
						}
					} else {
						if (rel_time < cond_rel_time[92]) {
							w34 = 1.0764186;
						} else {
							w34 = 0.53117937;
						}
					}
				}
			} else {
				if (prod != cond_prod[0]) {
					if (prod != cond_prod[4]) {
						if (rel_time < cond_rel_time[188]) {
							w34 = 3.3426077;
						} else {
							w34 = 1.7714552;
						}
					} else {
						if (hops < cond_hops[1]) {
							w34 = -4.0767646;
						} else {
							w34 = -3.5324435;
						}
					}
				} else {
					if (hops < cond_hops[1]) {
						w34 = -1.7003273;
					} else {
						if (hops < cond_hops[2]) {
							w34 = -1.236608;
						} else {
							w34 = -1.3788607;
						}
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[171]) {
				if (prod != cond_prod[2]) {
					if (rel_time < cond_rel_time[167]) {
						if (rel_time < cond_rel_time[98]) {
							w34 = -0.051076025;
						} else {
							w34 = 3.9649584;
						}
					} else {
						if (hops < cond_hops[0]) {
							w34 = -1.7511252;
						} else {
							w34 = -2.0712423;
						}
					}
				} else {
					if (hops < cond_hops[2]) {
						w34 = -2.843154;
					} else {
						if (rel_time < cond_rel_time[167]) {
							w34 = -3.1759586;
						} else {
							w34 = -3.563256;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[105]) {
					if (rel_time < cond_rel_time[101]) {
						if (rel_time < cond_rel_time[169]) {
							w34 = 0.42859367;
						} else {
							w34 = -0.20000513;
						}
					} else {
						if (rel_time < cond_rel_time[103]) {
							w34 = 5.3801336;
						} else {
							w34 = 0.9296096;
						}
					}
				} else {
					if (rel_time < cond_rel_time[198]) {
						if (prod != cond_prod[0]) {
							w34 = -1.3058115;
						} else {
							w34 = 0.5488556;
						}
					} else {
						if (rel_time < cond_rel_time[126]) {
							w34 = 0.47397447;
						} else {
							w34 = -0.08065836;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < cond_rel_time[188]) {
			if (rel_time < cond_rel_time[93]) {
				if (rel_time < cond_rel_time[35]) {
					if (rel_time < cond_rel_time[204]) {
						if (rel_time < cond_rel_time[225]) {
							w34 = 0.025338033;
						} else {
							w34 = -0.77818084;
						}
					} else {
						if (rel_time < cond_rel_time[30]) {
							w34 = 6.1975636;
						} else {
							w34 = 1.2358516;
						}
					}
				} else {
					if (rel_time < cond_rel_time[197]) {
						if (hops < cond_hops[2]) {
							w34 = -1.5665958;
						} else {
							w34 = -2.6686842;
						}
					} else {
						if (rel_time < cond_rel_time[222]) {
							w34 = 0.9767808;
						} else {
							w34 = -0.21282032;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[223]) {
					w34 = -1.0185083;
				} else {
					if (hops < cond_hops[1]) {
						w34 = -1.1422421;
					} else {
						if (hops < cond_hops[3]) {
							w34 = -1.0599991;
						} else {
							w34 = -1.1687298;
						}
					}
				}
			}
		} else {
			if (rel_time < cond_rel_time[143]) {
				if (rel_time < cond_rel_time[200]) {
					if (rel_time < cond_rel_time[123]) {
						if (rel_time < cond_rel_time[221]) {
							w34 = 0.12495426;
						} else {
							w34 = 2.7848473;
						}
					} else {
						if (hops < cond_hops[1]) {
							w34 = -2.4745169;
						} else {
							w34 = -2.2277844;
						}
					}
				} else {
					if (rel_time < cond_rel_time[148]) {
						if (rel_time < cond_rel_time[124]) {
							w34 = 5.3406024;
						} else {
							w34 = 2.4298;
						}
					} else {
						if (rel_time < cond_rel_time[144]) {
							w34 = -0.8788231;
						} else {
							w34 = 1.7156404;
						}
					}
				}
			} else {
				if (rel_time < cond_rel_time[145]) {
					if (hops < cond_hops[2]) {
						if (rel_time < cond_rel_time[156]) {
							w34 = -0.6721177;
						} else {
							w34 = -0.8162651;
						}
					} else {
						if (rel_time < cond_rel_time[156]) {
							w34 = -0.21273336;
						} else {
							w34 = -0.317139;
						}
					}
				} else {
					if (rel_time < cond_rel_time[138]) {
						if (rel_time < cond_rel_time[88]) {
							w34 = -0.074308954;
						} else {
							w34 = -2.7817738;
						}
					} else {
						if (rel_time < cond_rel_time[58]) {
							w34 = 1.2289947;
						} else {
							w34 = -0.0056156465;
						}
					}
				}
			}
		}
	}
	return (673.08344 + w0 + w1 + w2 + w3 + w4 + w5 + w6 + w7 + w8 + w9 + w10 + w11 + w12 + w13 + w14 + w15 + w16 + w17 + w18 + w19 + w20 + w21 + w22 + w23 + w24 + w25 + w26 + w27 + w28 + w29 + w30 + w31 + w32 + w33 + w34);
}
