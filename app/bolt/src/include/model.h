#include <stdbool.h>
#include <stdint.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define UINT8_MIN 0
#define UINT16_MIN 0
#define UINT32_MIN 0

int model(int rel_time, int hops, int size, int prod, int cons)
{
	int w0;
	if (size < 38) {
		if (cons == 0) {
			if (hops < 3) {
				if (rel_time < 3467) {
					if (hops < 2) {
						if (rel_time < 1353) {
							w0 = 35584;
						} else {
							w0 = 34304;
						}
					} else {
						if (rel_time < 1353) {
							w0 = 36096;
						} else {
							w0 = 35072;
						}
					}
				} else {
					if (rel_time < 3510) {
						w0 = 36096;
					} else {
						w0 = 37632;
					}
				}
			} else {
				if (rel_time < 3467) {
					if (hops < 4) {
						if (rel_time < 1353) {
							w0 = 36608;
						} else {
							w0 = 35584;
						}
					} else {
						if (rel_time < 1353) {
							w0 = 37120;
						} else {
							w0 = 36096;
						}
					}
				} else {
					if (rel_time < 3510) {
						w0 = 37376;
					} else {
						w0 = 38912;
					}
				}
			}
		} else {
			if (hops < 3) {
				if (hops < 2) {
					w0 = 33024;
				} else {
					w0 = 33536;
				}
			} else {
				if (hops < 4) {
					w0 = 34048;
				} else {
					w0 = 34816;
				}
			}
		}
	} else {
		if (rel_time < 397) {
			if (rel_time < 68) {
				if (hops < 3) {
					w0 = 58624;
				} else {
					w0 = 59904;
				}
			} else {
				if (cons == 3) {
					if (rel_time < 182) {
						if (hops < 3) {
							w0 = 69376;
						} else {
							w0 = 70400;
						}
					} else {
						if (hops < 3) {
							w0 = 65792;
						} else {
							w0 = 67072;
						}
					}
				} else {
					if (hops < 3) {
						w0 = 69888;
					} else {
						w0 = 71168;
					}
				}
			}
		} else {
			if (rel_time < 734) {
				if (hops < 3) {
					if (cons == 1) {
						if (cons == 3) {
							w0 = 57344;
						} else {
							w0 = 56320;
						}
					} else {
						w0 = 56320;
					}
				} else {
					if (cons == 3) {
						if (cons == 1) {
							w0 = 58624;
						} else {
							w0 = 57344;
						}
					} else {
						w0 = 57344;
					}
				}
			} else {
				if (rel_time < 3898) {
					if (rel_time < 3607) {
						if (cons == 0) {
							w0 = 54784;
						} else {
							w0 = 52480;
						}
					} else {
						if (prod == 0) {
							w0 = 47104;
						} else {
							w0 = 53760;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w0 = 54272;
						} else {
							w0 = 54784;
						}
					} else {
						if (hops < 4) {
							w0 = 55296;
						} else {
							w0 = 55808;
						}
					}
				}
			}
		}
	}
	int w1;
	if (size < 38) {
		if (cons == 0) {
			if (hops < 3) {
				if (rel_time < 3467) {
					if (rel_time < 3447) {
						if (rel_time < 3270) {
							w1 = 24320;
						} else {
							w1 = 25344;
						}
					} else {
						w1 = 22528;
					}
				} else {
					if (rel_time < 3510) {
						w1 = 25344;
					} else {
						w1 = 26368;
					}
				}
			} else {
				if (rel_time < 3467) {
					if (hops < 5) {
						if (rel_time < 3447) {
							w1 = 25088;
						} else {
							w1 = 23296;
						}
					} else {
						w1 = 25600;
					}
				} else {
					if (rel_time < 3510) {
						w1 = 26112;
					} else {
						w1 = 27136;
					}
				}
			}
		} else {
			if (hops < 3) {
				if (hops < 2) {
					if (rel_time < 1234) {
						w1 = 22528;
					} else {
						w1 = 23040;
					}
				} else {
					w1 = 23552;
				}
			} else {
				if (hops < 4) {
					w1 = 23808;
				} else {
					w1 = 24320;
				}
			}
		}
	} else {
		if (rel_time < 397) {
			if (rel_time < 68) {
				if (hops < 2) {
					w1 = 40704;
				} else {
					if (hops < 4) {
						w1 = 41472;
					} else {
						w1 = 42240;
					}
				}
			} else {
				if (cons == 3) {
					if (rel_time < 182) {
						if (hops < 4) {
							w1 = 48640;
						} else {
							w1 = 49664;
						}
					} else {
						if (hops < 4) {
							w1 = 46080;
						} else {
							w1 = 47104;
						}
					}
				} else {
					if (hops < 4) {
						w1 = 49152;
					} else {
						w1 = 50176;
					}
				}
			}
		} else {
			if (rel_time < 734) {
				if (hops < 2) {
					if (cons == 1) {
						if (cons == 3) {
							w1 = 39936;
						} else {
							w1 = 39168;
						}
					} else {
						w1 = 39168;
					}
				} else {
					if (hops < 4) {
						if (cons == 3) {
							w1 = 40448;
						} else {
							w1 = 39680;
						}
					} else {
						if (cons == 1) {
							w1 = 41216;
						} else {
							w1 = 40448;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (rel_time < 3898) {
						if (rel_time < 3607) {
							w1 = 37376;
						} else {
							w1 = 33536;
						}
					} else {
						if (hops < 2) {
							w1 = 37888;
						} else {
							w1 = 38400;
						}
					}
				} else {
					if (rel_time < 782) {
						w1 = 36864;
					} else {
						if (rel_time < 927) {
							w1 = 39680;
						} else {
							w1 = 38656;
						}
					}
				}
			}
		}
	}
	int w2;
	if (size < 38) {
		if (cons == 0) {
			if (hops < 2) {
				if (rel_time < 3270) {
					if (rel_time < 3122) {
						if (rel_time < 2975) {
							w2 = 16640;
						} else {
							w2 = 17664;
						}
					} else {
						if (cons == 2) {
							w2 = 15616;
						} else {
							w2 = 16384;
						}
					}
				} else {
					if (rel_time < 3387) {
						if (cons == 2) {
							w2 = 18176;
						} else {
							w2 = 16640;
						}
					} else {
						if (cons == 1) {
							w2 = 17408;
						} else {
							w2 = 15616;
						}
					}
				}
			} else {
				if (rel_time < 3270) {
					if (rel_time < 3122) {
						if (rel_time < 2975) {
							w2 = 17408;
						} else {
							w2 = 18432;
						}
					} else {
						if (cons == 2) {
							w2 = 16128;
						} else {
							w2 = 17152;
						}
					}
				} else {
					if (rel_time < 3387) {
						if (cons == 2) {
							w2 = 18944;
						} else {
							w2 = 17408;
						}
					} else {
						if (cons == 1) {
							w2 = 18176;
						} else {
							w2 = 16128;
						}
					}
				}
			}
		} else {
			if (hops < 3) {
				if (rel_time < 3299) {
					if (rel_time < 3152) {
						if (rel_time < 3004) {
							w2 = 16128;
						} else {
							w2 = 17152;
						}
					} else {
						w2 = 15616;
					}
				} else {
					w2 = 16896;
				}
			} else {
				if (hops < 5) {
					if (rel_time < 1234) {
						w2 = 16128;
					} else {
						if (rel_time < 1382) {
							w2 = 17408;
						} else {
							w2 = 16640;
						}
					}
				} else {
					w2 = 17408;
				}
			}
		}
	} else {
		if (rel_time < 397) {
			if (rel_time < 68) {
				if (hops < 2) {
					w2 = 28416;
				} else {
					if (hops < 4) {
						w2 = 28928;
					} else {
						w2 = 29440;
					}
				}
			} else {
				if (cons == 3) {
					if (rel_time < 182) {
						if (hops < 2) {
							w2 = 33536;
						} else {
							w2 = 34304;
						}
					} else {
						if (hops < 2) {
							w2 = 32000;
						} else {
							w2 = 32768;
						}
					}
				} else {
					if (hops < 2) {
						w2 = 34048;
					} else {
						w2 = 34560;
					}
				}
			}
		} else {
			if (rel_time < 734) {
				if (hops < 3) {
					if (cons == 1) {
						if (cons == 3) {
							w2 = 28160;
						} else {
							w2 = 27392;
						}
					} else {
						w2 = 27392;
					}
				} else {
					if (cons == 1) {
						if (cons == 3) {
							w2 = 28672;
						} else {
							w2 = 27904;
						}
					} else {
						if (hops < 4) {
							w2 = 27648;
						} else {
							w2 = 28160;
						}
					}
				}
			} else {
				if (rel_time < 782) {
					if (hops < 3) {
						if (hops < 2) {
							w2 = 24064;
						} else {
							w2 = 24832;
						}
					} else {
						if (hops < 4) {
							w2 = 25344;
						} else {
							w2 = 26112;
						}
					}
				} else {
					if (hops < 4) {
						if (rel_time < 3898) {
							w2 = 26112;
						} else {
							w2 = 26624;
						}
					} else {
						if (rel_time < 927) {
							w2 = 27904;
						} else {
							w2 = 27136;
						}
					}
				}
			}
		}
	}
	int w3;
	if (size < 38) {
		if (hops < 4) {
			if (cons == 0) {
				if (rel_time < 1353) {
					if (cons == 3) {
						if (rel_time < 1264) {
							w3 = 13312;
						} else {
							w3 = 11776;
						}
					} else {
						w3 = 13312;
					}
				} else {
					if (rel_time < 1469) {
						if (cons == 2) {
							w3 = 10240;
						} else {
							w3 = 11520;
						}
					} else {
						if (rel_time < 1617) {
							w3 = 12800;
						} else {
							w3 = 11776;
						}
					}
				}
			} else {
				if (hops < 2) {
					if (rel_time < 1234) {
						w3 = 10752;
					} else {
						if (rel_time < 1382) {
							w3 = 11776;
						} else {
							w3 = 11264;
						}
					}
				} else {
					if (rel_time < 1234) {
						w3 = 11008;
					} else {
						if (rel_time < 1382) {
							w3 = 12032;
						} else {
							w3 = 11520;
						}
					}
				}
			}
		} else {
			if (cons == 0) {
				if (rel_time < 3270) {
					if (rel_time < 1353) {
						if (cons == 4) {
							w3 = 13312;
						} else {
							w3 = 12544;
						}
					} else {
						if (rel_time < 1469) {
							w3 = 11264;
						} else {
							w3 = 12544;
						}
					}
				} else {
					if (rel_time < 3510) {
						if (rel_time < 3387) {
							w3 = 13312;
						} else {
							w3 = 12544;
						}
					} else {
						w3 = 13824;
					}
				}
			} else {
				if (rel_time < 3299) {
					if (rel_time < 3152) {
						if (rel_time < 3004) {
							w3 = 11776;
						} else {
							w3 = 12544;
						}
					} else {
						w3 = 11008;
					}
				} else {
					w3 = 12544;
				}
			}
		}
	} else {
		if (rel_time < 397) {
			if (rel_time < 68) {
				if (hops < 3) {
					w3 = 19968;
				} else {
					w3 = 20480;
				}
			} else {
				if (cons == 3) {
					if (rel_time < 182) {
						if (hops < 3) {
							w3 = 23552;
						} else {
							w3 = 24064;
						}
					} else {
						if (hops < 3) {
							w3 = 22528;
						} else {
							w3 = 23040;
						}
					}
				} else {
					if (hops < 3) {
						w3 = 23808;
					} else {
						w3 = 24320;
					}
				}
			}
		} else {
			if (rel_time < 734) {
				if (hops < 2) {
					if (cons == 3) {
						if (cons == 1) {
							w3 = 19456;
						} else {
							w3 = 18944;
						}
					} else {
						w3 = 18944;
					}
				} else {
					if (cons == 1) {
						if (cons == 3) {
							w3 = 19968;
						} else {
							w3 = 19456;
						}
					} else {
						if (hops < 4) {
							w3 = 19200;
						} else {
							w3 = 19712;
						}
					}
				}
			} else {
				if (cons == 0) {
					if (rel_time < 927) {
						if (cons == 2) {
							w3 = 19712;
						} else {
							w3 = 18432;
						}
					} else {
						if (rel_time < 3898) {
							w3 = 17152;
						} else {
							w3 = 18688;
						}
					}
				} else {
					if (hops < 3) {
						if (rel_time < 782) {
							w3 = 17152;
						} else {
							w3 = 17920;
						}
					} else {
						if (rel_time < 782) {
							w3 = 17920;
						} else {
							w3 = 18432;
						}
					}
				}
			}
		}
	}
	int w4;
	if (size < 38) {
		if (hops < 3) {
			if (rel_time < 3467) {
				if (cons == 0) {
					if (rel_time < 1353) {
						if (cons == 4) {
							w4 = 8960;
						} else {
							w4 = 8192;
						}
					} else {
						if (rel_time < 1529) {
							w4 = 7424;
						} else {
							w4 = 8192;
						}
					}
				} else {
					if (rel_time < 3299) {
						if (rel_time < 3152) {
							w4 = 7936;
						} else {
							w4 = 7424;
						}
					} else {
						w4 = 8192;
					}
				}
			} else {
				if (rel_time < 3510) {
					if (hops < 2) {
						w4 = 8448;
					} else {
						w4 = 8960;
					}
				} else {
					w4 = 9472;
				}
			}
		} else {
			if (cons == 0) {
				if (rel_time < 3270) {
					if (rel_time < 3122) {
						if (rel_time < 2975) {
							w4 = 8448;
						} else {
							w4 = 9216;
						}
					} else {
						if (cons == 4) {
							w4 = 7680;
						} else {
							w4 = 8448;
						}
					}
				} else {
					if (rel_time < 3387) {
						if (cons == 2) {
							w4 = 9728;
						} else {
							w4 = 8704;
						}
					} else {
						if (cons == 1) {
							w4 = 9216;
						} else {
							w4 = 7680;
						}
					}
				}
			} else {
				if (rel_time < 3299) {
					if (rel_time < 3152) {
						if (rel_time < 3004) {
							w4 = 8192;
						} else {
							w4 = 8960;
						}
					} else {
						w4 = 7680;
					}
				} else {
					w4 = 8704;
				}
			}
		}
	} else {
		if (rel_time < 397) {
			if (rel_time < 68) {
				if (hops < 2) {
					w4 = 13824;
				} else {
					if (hops < 5) {
						w4 = 14080;
					} else {
						w4 = 14848;
					}
				}
			} else {
				if (cons == 3) {
					if (rel_time < 182) {
						if (hops < 4) {
							w4 = 16640;
						} else {
							w4 = 17152;
						}
					} else {
						if (hops < 2) {
							w4 = 15616;
						} else {
							w4 = 15872;
						}
					}
				} else {
					if (hops < 2) {
						w4 = 16640;
					} else {
						if (hops < 5) {
							w4 = 16896;
						} else {
							w4 = 17664;
						}
					}
				}
			}
		} else {
			if (rel_time < 734) {
				if (hops < 4) {
					if (hops < 2) {
						if (cons == 3) {
							w4 = 13568;
						} else {
							w4 = 13312;
						}
					} else {
						if (cons == 1) {
							w4 = 13824;
						} else {
							w4 = 13312;
						}
					}
				} else {
					if (hops < 5) {
						if (cons == 3) {
							w4 = 14080;
						} else {
							w4 = 13568;
						}
					} else {
						w4 = 14336;
					}
				}
			} else {
				if (hops < 2) {
					if (cons == 0) {
						if (rel_time < 981) {
							w4 = 13056;
						} else {
							w4 = 12544;
						}
					} else {
						if (rel_time < 782) {
							w4 = 11776;
						} else {
							w4 = 12288;
						}
					}
				} else {
					if (hops < 5) {
						if (cons == 0) {
							w4 = 13056;
						} else {
							w4 = 12544;
						}
					} else {
						if (rel_time < 3898) {
							w4 = 13568;
						} else {
							w4 = 14080;
						}
					}
				}
			}
		}
	}
	int w5;
	if (size < 38) {
		if (hops < 2) {
			if (rel_time < 3299) {
				if (rel_time < 3152) {
					if (rel_time < 3004) {
						if (rel_time < 2857) {
							w5 = 5632;
						} else {
							w5 = 4608;
						}
					} else {
						if (rel_time < 3033) {
							w5 = 6912;
						} else {
							w5 = 6144;
						}
					}
				} else {
					if (cons == 3) {
						if (rel_time < 3181) {
							w5 = 4352;
						} else {
							w5 = 5376;
						}
					} else {
						w5 = 4352;
					}
				}
			} else {
				if (rel_time < 3387) {
					if (cons == 2) {
						w5 = 6656;
					} else {
						w5 = 5632;
					}
				} else {
					if (rel_time < 3467) {
						if (rel_time < 3447) {
							w5 = 5632;
						} else {
							w5 = 4864;
						}
					} else {
						if (cons == 3) {
							w5 = 6144;
						} else {
							w5 = 5888;
						}
					}
				}
			}
		} else {
			if (hops < 5) {
				if (rel_time < 3299) {
					if (rel_time < 2857) {
						if (rel_time < 2709) {
							w5 = 5888;
						} else {
							w5 = 6656;
						}
					} else {
						if (rel_time < 3004) {
							w5 = 4864;
						} else {
							w5 = 5888;
						}
					}
				} else {
					if (rel_time < 3387) {
						if (cons == 2) {
							w5 = 6656;
						} else {
							w5 = 5888;
						}
					} else {
						if (rel_time < 3467) {
							w5 = 5632;
						} else {
							w5 = 6400;
						}
					}
				}
			} else {
				if (rel_time < 3467) {
					if (rel_time < 2857) {
						if (rel_time < 2709) {
							w5 = 6144;
						} else {
							w5 = 7168;
						}
					} else {
						if (rel_time < 3004) {
							w5 = 5376;
						} else {
							w5 = 6400;
						}
					}
				} else {
					w5 = 6912;
				}
			}
		}
	} else {
		if (rel_time < 397) {
			if (rel_time < 68) {
				if (hops < 4) {
					if (hops < 2) {
						w5 = 9728;
					} else {
						w5 = 9728;
					}
				} else {
					w5 = 9984;
				}
			} else {
				if (cons == 3) {
					if (rel_time < 182) {
						if (hops < 2) {
							w5 = 11264;
						} else {
							w5 = 11776;
						}
					} else {
						if (hops < 4) {
							w5 = 11008;
						} else {
							w5 = 11520;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 2) {
							w5 = 11520;
						} else {
							w5 = 11776;
						}
					} else {
						w5 = 12032;
					}
				}
			}
		} else {
			if (rel_time < 981) {
				if (cons == 0) {
					if (hops < 2) {
						if (rel_time < 831) {
							w5 = 9472;
						} else {
							w5 = 8960;
						}
					} else {
						if (cons == 2) {
							w5 = 9728;
						} else {
							w5 = 9472;
						}
					}
				} else {
					if (rel_time < 468) {
						if (hops < 4) {
							w5 = 9472;
						} else {
							w5 = 9984;
						}
					} else {
						if (hops < 4) {
							w5 = 8192;
						} else {
							w5 = 8960;
						}
					}
				}
			} else {
				if (rel_time < 3898) {
					if (rel_time < 3607) {
						if (rel_time < 1029) {
							w5 = 8704;
						} else {
							w5 = 8192;
						}
					} else {
						if (prod == 0) {
							w5 = 5120;
						} else {
							w5 = 9984;
						}
					}
				} else {
					if (hops < 3) {
						if (rel_time < 3943) {
							w5 = 9984;
						} else {
							w5 = 8960;
						}
					} else {
						if (hops < 5) {
							w5 = 9472;
						} else {
							w5 = 9728;
						}
					}
				}
			}
		}
	}
	int w6;
	if (size < 38) {
		if (hops < 4) {
			if (cons == 0) {
				if (rel_time < 1264) {
					if (hops < 3) {
						w6 = 4864;
					} else {
						w6 = 5120;
					}
				} else {
					if (rel_time < 1824) {
						if (rel_time < 1677) {
							w6 = 4096;
						} else {
							w6 = 3072;
						}
					} else {
						if (rel_time < 1912) {
							w6 = 5120;
						} else {
							w6 = 3840;
						}
					}
				}
			} else {
				if (rel_time < 3299) {
					if (rel_time < 3152) {
						if (rel_time < 3004) {
							w6 = 3840;
						} else {
							w6 = 4352;
						}
					} else {
						w6 = 3328;
					}
				} else {
					if (hops < 2) {
						w6 = 4096;
					} else {
						w6 = 4096;
					}
				}
			}
		} else {
			if (cons == 0) {
				if (rel_time < 1264) {
					w6 = 5376;
				} else {
					if (rel_time < 1529) {
						if (rel_time < 1353) {
							w6 = 4608;
						} else {
							w6 = 3584;
						}
					} else {
						if (rel_time < 1617) {
							w6 = 5632;
						} else {
							w6 = 4352;
						}
					}
				}
			} else {
				if (rel_time < 1234) {
					w6 = 3584;
				} else {
					if (rel_time < 1382) {
						w6 = 4608;
					} else {
						if (rel_time < 1529) {
							w6 = 3328;
						} else {
							w6 = 4096;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 397) {
			if (rel_time < 68) {
				if (hops < 5) {
					if (hops < 2) {
						w6 = 6656;
					} else {
						w6 = 6912;
					}
				} else {
					w6 = 7168;
				}
			} else {
				if (cons == 2) {
					if (rel_time < 318) {
						if (hops < 5) {
							w6 = 8192;
						} else {
							w6 = 8704;
						}
					} else {
						if (hops < 5) {
							w6 = 7680;
						} else {
							w6 = 8448;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 2) {
							w6 = 7424;
						} else {
							w6 = 7680;
						}
					} else {
						w6 = 8192;
					}
				}
			}
		} else {
			if (rel_time < 981) {
				if (cons == 0) {
					if (hops < 2) {
						if (rel_time < 831) {
							w6 = 6656;
						} else {
							w6 = 6144;
						}
					} else {
						if (hops < 5) {
							w6 = 6656;
						} else {
							w6 = 7168;
						}
					}
				} else {
					if (rel_time < 468) {
						if (hops < 2) {
							w6 = 6400;
						} else {
							w6 = 6912;
						}
					} else {
						if (hops < 3) {
							w6 = 5632;
						} else {
							w6 = 6144;
						}
					}
				}
			} else {
				if (rel_time < 3898) {
					if (rel_time < 3607) {
						if (cons == 1) {
							w6 = 5888;
						} else {
							w6 = 4864;
						}
					} else {
						if (prod == 0) {
							w6 = 3584;
						} else {
							w6 = 6912;
						}
					}
				} else {
					if (hops < 3) {
						if (rel_time < 3943) {
							w6 = 6912;
						} else {
							w6 = 6144;
						}
					} else {
						if (hops < 4) {
							w6 = 6400;
						} else {
							w6 = 6656;
						}
					}
				}
			}
		}
	}
	int w7;
	if (size < 38) {
		if (hops < 2) {
			if (rel_time < 2709) {
				if (rel_time < 2562) {
					if (rel_time < 2414) {
						if (rel_time < 2267) {
							w7 = 2560;
						} else {
							w7 = 1792;
						}
					} else {
						if (cons == 1) {
							w7 = 3328;
						} else {
							w7 = 4352;
						}
					}
				} else {
					if (cons == 3) {
						if (rel_time < 2591) {
							w7 = 1024;
						} else {
							w7 = 2048;
						}
					} else {
						w7 = 1024;
					}
				}
			} else {
				if (rel_time < 2797) {
					if (cons == 2) {
						w7 = 4352;
					} else {
						w7 = 3072;
					}
				} else {
					if (rel_time < 3004) {
						if (rel_time < 2857) {
							w7 = 3072;
						} else {
							w7 = 2048;
						}
					} else {
						if (rel_time < 3033) {
							w7 = 3584;
						} else {
							w7 = 2816;
						}
					}
				}
			}
		} else {
			if (rel_time < 3510) {
				if (rel_time < 2562) {
					if (rel_time < 2414) {
						if (rel_time < 2267) {
							w7 = 2816;
						} else {
							w7 = 1792;
						}
					} else {
						if (cons == 1) {
							w7 = 3584;
						} else {
							w7 = 4608;
						}
					}
				} else {
					if (rel_time < 2709) {
						if (cons == 2) {
							w7 = 1792;
						} else {
							w7 = 2560;
						}
					} else {
						if (rel_time < 2797) {
							w7 = 3840;
						} else {
							w7 = 2816;
						}
					}
				}
			} else {
				w7 = 3584;
			}
		}
	} else {
		if (rel_time < 397) {
			if (rel_time < 68) {
				if (hops < 4) {
					if (hops < 2) {
						w7 = 4608;
					} else {
						w7 = 4864;
					}
				} else {
					if (hops < 5) {
						w7 = 4864;
					} else {
						w7 = 5120;
					}
				}
			} else {
				if (cons == 3) {
					if (rel_time < 182) {
						if (hops < 2) {
							w7 = 5376;
						} else {
							w7 = 5632;
						}
					} else {
						if (hops < 5) {
							w7 = 5376;
						} else {
							w7 = 5888;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 2) {
							w7 = 5632;
						} else {
							w7 = 5632;
						}
					} else {
						w7 = 5888;
					}
				}
			}
		} else {
			if (hops < 2) {
				if (rel_time < 734) {
					if (cons == 1) {
						if (cons == 3) {
							w7 = 4608;
						} else {
							w7 = 4352;
						}
					} else {
						w7 = 4352;
					}
				} else {
					if (rel_time < 4219) {
						if (rel_time < 981) {
							w7 = 4352;
						} else {
							w7 = 3584;
						}
					} else {
						if (rel_time < 4264) {
							w7 = 4864;
						} else {
							w7 = 4352;
						}
					}
				}
			} else {
				if (rel_time < 981) {
					if (rel_time < 879) {
						if (rel_time < 831) {
							w7 = 4608;
						} else {
							w7 = 4096;
						}
					} else {
						if (rel_time < 927) {
							w7 = 4864;
						} else {
							w7 = 4608;
						}
					}
				} else {
					if (rel_time < 3898) {
						if (rel_time < 3607) {
							w7 = 4352;
						} else {
							w7 = 2816;
						}
					} else {
						if (hops < 4) {
							w7 = 4352;
						} else {
							w7 = 4608;
						}
					}
				}
			}
		}
	}
	int w8;
	if (size < 38) {
		if (rel_time < 1529) {
			if (rel_time < 1382) {
				if (cons == 3) {
					if (cons == 1) {
						if (rel_time < 1293) {
							w8 = 1536;
						} else {
							w8 = 2048;
						}
					} else {
						if (hops < 3) {
							w8 = 2304;
						} else {
							w8 = 2816;
						}
					}
				} else {
					if (hops < 3) {
						w8 = 2560;
					} else {
						if (hops < 4) {
							w8 = 2816;
						} else {
							w8 = 3072;
						}
					}
				}
			} else {
				if (cons == 2) {
					if (rel_time < 1469) {
						if (hops < 5) {
							w8 = 768;
						} else {
							w8 = 1024;
						}
					} else {
						if (hops < 4) {
							w8 = 1280;
						} else {
							w8 = 1536;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w8 = 1792;
						} else {
							w8 = 1792;
						}
					} else {
						w8 = 2304;
					}
				}
			}
		} else {
			if (rel_time < 1677) {
				if (cons == 3) {
					if (rel_time < 1559) {
						if (hops < 2) {
							w8 = 3072;
						} else {
							w8 = 3328;
						}
					} else {
						if (rel_time < 1588) {
							w8 = 2048;
						} else {
							w8 = 2304;
						}
					}
				} else {
					if (hops < 2) {
						w8 = 3328;
					} else {
						w8 = 3328;
					}
				}
			} else {
				if (rel_time < 1824) {
					if (cons == 4) {
						if (cons == 2) {
							w8 = 768;
						} else {
							w8 = 1792;
						}
					} else {
						if (hops < 4) {
							w8 = 1792;
						} else {
							w8 = 1792;
						}
					}
				} else {
					if (rel_time < 1912) {
						if (cons == 2) {
							w8 = 3328;
						} else {
							w8 = 2048;
						}
					} else {
						if (rel_time < 2090) {
							w8 = 1280;
						} else {
							w8 = 2048;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 397) {
			if (rel_time < 68) {
				if (hops < 4) {
					if (hops < 2) {
						w8 = 3328;
					} else {
						w8 = 3328;
					}
				} else {
					if (hops < 5) {
						w8 = 3328;
					} else {
						w8 = 3584;
					}
				}
			} else {
				if (hops < 2) {
					if (cons == 3) {
						if (rel_time < 182) {
							w8 = 3840;
						} else {
							w8 = 3584;
						}
					} else {
						w8 = 3840;
					}
				} else {
					if (cons == 2) {
						if (hops < 5) {
							w8 = 3840;
						} else {
							w8 = 4096;
						}
					} else {
						if (hops < 4) {
							w8 = 3584;
						} else {
							w8 = 3840;
						}
					}
				}
			}
		} else {
			if (hops < 4) {
				if (rel_time < 981) {
					if (cons == 0) {
						if (cons == 2) {
							w8 = 3072;
						} else {
							w8 = 3072;
						}
					} else {
						if (rel_time < 468) {
							w8 = 3072;
						} else {
							w8 = 2560;
						}
					}
				} else {
					if (rel_time < 3739) {
						if (rel_time < 3607) {
							w8 = 2816;
						} else {
							w8 = 1280;
						}
					} else {
						if (rel_time < 3943) {
							w8 = 3328;
						} else {
							w8 = 3072;
						}
					}
				}
			} else {
				if (cons == 4) {
					if (hops < 5) {
						if (rel_time < 610) {
							w8 = 3328;
						} else {
							w8 = 3072;
						}
					} else {
						if (rel_time < 1126) {
							w8 = 3584;
						} else {
							w8 = 3328;
						}
					}
				} else {
					if (hops < 5) {
						if (rel_time < 734) {
							w8 = 3584;
						} else {
							w8 = 3328;
						}
					} else {
						w8 = 3840;
					}
				}
			}
		}
	}
	int w9;
	if (size < 38) {
		if (rel_time < 3299) {
			if (rel_time < 3152) {
				if (rel_time < 3004) {
					if (rel_time < 2857) {
						if (rel_time < 2709) {
							w9 = 1280;
						} else {
							w9 = 1792;
						}
					} else {
						if (cons == 3) {
							w9 = 768;
						} else {
							w9 = 0;
						}
					}
				} else {
					if (cons == 3) {
						if (rel_time < 3033) {
							w9 = 2304;
						} else {
							w9 = 1280;
						}
					} else {
						if (hops < 2) {
							w9 = 2304;
						} else {
							w9 = 2560;
						}
					}
				}
			} else {
				if (cons == 3) {
					if (rel_time < 3181) {
						if (hops < 3) {
							w9 = 256;
						} else {
							w9 = 512;
						}
					} else {
						if (rel_time < 3270) {
							w9 = 1280;
						} else {
							w9 = 768;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w9 = 256;
						} else {
							w9 = 0;
						}
					} else {
						if (hops < 5) {
							w9 = 256;
						} else {
							w9 = 512;
						}
					}
				}
			}
		} else {
			if (rel_time < 3387) {
				if (cons == 2) {
					if (rel_time < 3328) {
						if (hops < 5) {
							w9 = 1792;
						} else {
							w9 = 2304;
						}
					} else {
						if (hops < 5) {
							w9 = 2048;
						} else {
							w9 = 2304;
						}
					}
				} else {
					if (hops < 3) {
						w9 = 1280;
					} else {
						if (hops < 4) {
							w9 = 1536;
						} else {
							w9 = 1280;
						}
					}
				}
			} else {
				if (cons == 1) {
					if (rel_time < 3510) {
						if (cons == 2) {
							w9 = 1280;
						} else {
							w9 = 1536;
						}
					} else {
						if (hops < 5) {
							w9 = 1792;
						} else {
							w9 = 2048;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w9 = 512;
						} else {
							w9 = 512;
						}
					} else {
						if (hops < 5) {
							w9 = 1024;
						} else {
							w9 = 512;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 397) {
			if (rel_time < 68) {
				if (hops < 4) {
					if (hops < 2) {
						w9 = 2304;
					} else {
						w9 = 2304;
					}
				} else {
					if (hops < 5) {
						w9 = 2304;
					} else {
						w9 = 2304;
					}
				}
			} else {
				if (hops < 4) {
					if (cons == 3) {
						if (rel_time < 182) {
							w9 = 2560;
						} else {
							w9 = 2560;
						}
					} else {
						if (hops < 2) {
							w9 = 2560;
						} else {
							w9 = 2816;
						}
					}
				} else {
					if (hops < 5) {
						if (cons == 3) {
							w9 = 2560;
						} else {
							w9 = 2816;
						}
					} else {
						if (rel_time < 182) {
							w9 = 3072;
						} else {
							w9 = 2816;
						}
					}
				}
			}
		} else {
			if (hops < 2) {
				if (rel_time < 927) {
					if (rel_time < 879) {
						if (rel_time < 831) {
							w9 = 2048;
						} else {
							w9 = 1792;
						}
					} else {
						w9 = 2560;
					}
				} else {
					if (rel_time < 3739) {
						if (rel_time < 3607) {
							w9 = 1792;
						} else {
							w9 = 768;
						}
					} else {
						if (rel_time < 10356) {
							w9 = 2048;
						} else {
							w9 = 2560;
						}
					}
				}
			} else {
				if (rel_time < 1029) {
					if (rel_time < 782) {
						if (rel_time < 734) {
							w9 = 2304;
						} else {
							w9 = 1792;
						}
					} else {
						if (cons == 2) {
							w9 = 2304;
						} else {
							w9 = 2048;
						}
					}
				} else {
					if (rel_time < 3739) {
						if (rel_time < 3607) {
							w9 = 1792;
						} else {
							w9 = 768;
						}
					} else {
						if (hops < 3) {
							w9 = 2048;
						} else {
							w9 = 2304;
						}
					}
				}
			}
		}
	}
	int w10;
	if (size < 38) {
		if (hops < 4) {
			if (rel_time < 2562) {
				if (rel_time < 2414) {
					if (rel_time < 2267) {
						if (rel_time < 2090) {
							w10 = 768;
						} else {
							w10 = 1536;
						}
					} else {
						if (cons == 3) {
							w10 = 256;
						} else {
							w10 = -256;
						}
					}
				} else {
					if (cons == 3) {
						if (cons == 1) {
							w10 = 1024;
						} else {
							w10 = 2048;
						}
					} else {
						if (hops < 2) {
							w10 = 2048;
						} else {
							w10 = 2304;
						}
					}
				}
			} else {
				if (rel_time < 2709) {
					if (cons == 3) {
						if (rel_time < 2591) {
							w10 = 0;
						} else {
							w10 = 512;
						}
					} else {
						if (hops < 2) {
							w10 = -256;
						} else {
							w10 = -256;
						}
					}
				} else {
					if (rel_time < 2797) {
						if (cons == 2) {
							w10 = 1792;
						} else {
							w10 = 512;
						}
					} else {
						if (rel_time < 2944) {
							w10 = 512;
						} else {
							w10 = 768;
						}
					}
				}
			}
		} else {
			if (hops < 5) {
				if (rel_time < 2562) {
					if (rel_time < 2414) {
						if (rel_time < 2267) {
							w10 = 1024;
						} else {
							w10 = 256;
						}
					} else {
						if (cons == 3) {
							w10 = 1536;
						} else {
							w10 = 2304;
						}
					}
				} else {
					if (rel_time < 2649) {
						if (cons == 2) {
							w10 = 0;
						} else {
							w10 = 768;
						}
					} else {
						if (rel_time < 2797) {
							w10 = 1280;
						} else {
							w10 = 768;
						}
					}
				}
			} else {
				if (rel_time < 2562) {
					if (rel_time < 2414) {
						if (rel_time < 2267) {
							w10 = 1280;
						} else {
							w10 = 512;
						}
					} else {
						if (cons == 3) {
							w10 = 1536;
						} else {
							w10 = 2560;
						}
					}
				} else {
					if (rel_time < 2649) {
						if (cons == 2) {
							w10 = 0;
						} else {
							w10 = 1024;
						}
					} else {
						if (rel_time < 3467) {
							w10 = 1024;
						} else {
							w10 = 1536;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 397) {
			if (rel_time < 68) {
				if (hops < 4) {
					if (hops < 2) {
						w10 = 1536;
					} else {
						w10 = 1536;
					}
				} else {
					if (hops < 5) {
						w10 = 1536;
					} else {
						w10 = 1536;
					}
				}
			} else {
				if (hops < 2) {
					if (cons == 3) {
						if (rel_time < 182) {
							w10 = 1792;
						} else {
							w10 = 1792;
						}
					} else {
						w10 = 1792;
					}
				} else {
					if (cons == 2) {
						if (rel_time < 318) {
							w10 = 1792;
						} else {
							w10 = 1792;
						}
					} else {
						if (hops < 5) {
							w10 = 1792;
						} else {
							w10 = 1792;
						}
					}
				}
			}
		} else {
			if (hops < 5) {
				if (hops < 2) {
					if (rel_time < 734) {
						if (cons == 2) {
							w10 = 1536;
						} else {
							w10 = 1536;
						}
					} else {
						if (rel_time < 782) {
							w10 = 1024;
						} else {
							w10 = 1280;
						}
					}
				} else {
					if (rel_time < 927) {
						if (rel_time < 782) {
							w10 = 1536;
						} else {
							w10 = 1536;
						}
					} else {
						if (cons == 3) {
							w10 = 1536;
						} else {
							w10 = 512;
						}
					}
				}
			} else {
				if (rel_time < 3607) {
					if (cons == 4) {
						if (rel_time < 468) {
							w10 = 1792;
						} else {
							w10 = 1536;
						}
					} else {
						if (rel_time < 981) {
							w10 = 1792;
						} else {
							w10 = 2048;
						}
					}
				} else {
					if (rel_time < 3739) {
						if (prod == 2) {
							w10 = -256;
						} else {
							w10 = 1536;
						}
					} else {
						if (rel_time < 3943) {
							w10 = 2048;
						} else {
							w10 = 1536;
						}
					}
				}
			}
		}
	}
	int w11;
	if (size < 38) {
		if (rel_time < 1529) {
			if (rel_time < 1382) {
				if (rel_time < 1234) {
					if (hops < 3) {
						if (hops < 2) {
							w11 = 256;
						} else {
							w11 = 256;
						}
					} else {
						if (hops < 4) {
							w11 = 256;
						} else {
							w11 = 256;
						}
					}
				} else {
					if (cons == 3) {
						if (rel_time < 1264) {
							w11 = 1024;
						} else {
							w11 = 512;
						}
					} else {
						if (hops < 3) {
							w11 = 1024;
						} else {
							w11 = 1280;
						}
					}
				}
			} else {
				if (cons == 2) {
					if (rel_time < 1469) {
						if (hops < 3) {
							w11 = 0;
						} else {
							w11 = 0;
						}
					} else {
						if (cons == 0) {
							w11 = 256;
						} else {
							w11 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w11 = 512;
						} else {
							w11 = 512;
						}
					} else {
						if (hops < 5) {
							w11 = 768;
						} else {
							w11 = 1024;
						}
					}
				}
			}
		} else {
			if (rel_time < 1677) {
				if (cons == 3) {
					if (rel_time < 1559) {
						if (hops < 2) {
							w11 = 1536;
						} else {
							w11 = 1536;
						}
					} else {
						if (cons == 0) {
							w11 = 768;
						} else {
							w11 = 1024;
						}
					}
				} else {
					if (hops < 2) {
						w11 = 1536;
					} else {
						w11 = 1536;
					}
				}
			} else {
				if (rel_time < 1764) {
					if (cons == 2) {
						if (hops < 4) {
							w11 = -256;
						} else {
							w11 = -256;
						}
					} else {
						if (hops < 4) {
							w11 = 512;
						} else {
							w11 = 256;
						}
					}
				} else {
					if (rel_time < 1942) {
						if (rel_time < 1824) {
							w11 = 256;
						} else {
							w11 = 1280;
						}
					} else {
						if (rel_time < 2059) {
							w11 = 0;
						} else {
							w11 = 512;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 397) {
			if (rel_time < 68) {
				if (hops < 3) {
					w11 = 1024;
				} else {
					if (hops < 5) {
						w11 = 1024;
					} else {
						w11 = 1024;
					}
				}
			} else {
				if (hops < 3) {
					if (cons == 3) {
						if (rel_time < 182) {
							w11 = 1280;
						} else {
							w11 = 1024;
						}
					} else {
						if (hops < 2) {
							w11 = 1280;
						} else {
							w11 = 1280;
						}
					}
				} else {
					if (hops < 5) {
						if (cons == 3) {
							w11 = 1280;
						} else {
							w11 = 1280;
						}
					} else {
						if (rel_time < 182) {
							w11 = 1536;
						} else {
							w11 = 1280;
						}
					}
				}
			}
		} else {
			if (hops < 4) {
				if (rel_time < 927) {
					if (rel_time < 879) {
						if (rel_time < 831) {
							w11 = 1024;
						} else {
							w11 = 768;
						}
					} else {
						if (hops < 3) {
							w11 = 1280;
						} else {
							w11 = 1024;
						}
					}
				} else {
					if (rel_time < 3739) {
						if (prod == 1) {
							w11 = 768;
						} else {
							w11 = -256;
						}
					} else {
						if (rel_time < 10096) {
							w11 = 1024;
						} else {
							w11 = 768;
						}
					}
				}
			} else {
				if (cons == 4) {
					if (hops < 5) {
						if (rel_time < 4309) {
							w11 = 1024;
						} else {
							w11 = 1024;
						}
					} else {
						if (rel_time < 610) {
							w11 = 1280;
						} else {
							w11 = 1024;
						}
					}
				} else {
					if (rel_time < 734) {
						w11 = 1280;
					} else {
						if (rel_time < 981) {
							w11 = 1280;
						} else {
							w11 = 1280;
						}
					}
				}
			}
		}
	}
	int w12;
	if (size < 38) {
		if (rel_time < 2267) {
			if (rel_time < 2178) {
				if (cons == 1) {
					if (rel_time < 2030) {
						if (rel_time < 1883) {
							w12 = 256;
						} else {
							w12 = 768;
						}
					} else {
						if (cons == 2) {
							w12 = -256;
						} else {
							w12 = 512;
						}
					}
				} else {
					if (rel_time < 2001) {
						if (rel_time < 1854) {
							w12 = 512;
						} else {
							w12 = -768;
						}
					} else {
						if (hops < 4) {
							w12 = 1792;
						} else {
							w12 = 2048;
						}
					}
				}
			} else {
				if (rel_time < 2207) {
					if (hops < 4) {
						if (hops < 2) {
							w12 = 2048;
						} else {
							w12 = 2048;
						}
					} else {
						w12 = 2304;
					}
				} else {
					if (hops < 4) {
						if (rel_time < 2237) {
							w12 = 512;
						} else {
							w12 = 512;
						}
					} else {
						if (hops < 5) {
							w12 = 768;
						} else {
							w12 = 1024;
						}
					}
				}
			}
		} else {
			if (rel_time < 2354) {
				if (cons == 2) {
					if (rel_time < 2325) {
						if (hops < 4) {
							w12 = -512;
						} else {
							w12 = -256;
						}
					} else {
						if (hops < 2) {
							w12 = -512;
						} else {
							w12 = -256;
						}
					}
				} else {
					if (hops < 2) {
						w12 = 256;
					} else {
						if (hops < 4) {
							w12 = 512;
						} else {
							w12 = 512;
						}
					}
				}
			} else {
				if (rel_time < 2562) {
					if (cons == 3) {
						if (cons == 1) {
							w12 = 512;
						} else {
							w12 = 1280;
						}
					} else {
						if (hops < 3) {
							w12 = 1280;
						} else {
							w12 = 1536;
						}
					}
				} else {
					if (rel_time < 2709) {
						if (cons == 3) {
							w12 = 0;
						} else {
							w12 = -256;
						}
					} else {
						if (rel_time < 2797) {
							w12 = 768;
						} else {
							w12 = 256;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 468) {
			if (cons == 0) {
				if (hops < 4) {
					if (cons == 3) {
						if (rel_time < 182) {
							w12 = 768;
						} else {
							w12 = 768;
						}
					} else {
						if (hops < 2) {
							w12 = 768;
						} else {
							w12 = 768;
						}
					}
				} else {
					if (cons == 2) {
						if (rel_time < 318) {
							w12 = 1024;
						} else {
							w12 = 768;
						}
					} else {
						if (hops < 5) {
							w12 = 768;
						} else {
							w12 = 768;
						}
					}
				}
			} else {
				if (hops < 2) {
					if (rel_time < 68) {
						w12 = 768;
					} else {
						w12 = 768;
					}
				} else {
					if (rel_time < 68) {
						if (hops < 4) {
							w12 = 768;
						} else {
							w12 = 768;
						}
					} else {
						if (hops < 4) {
							w12 = 768;
						} else {
							w12 = 768;
						}
					}
				}
			}
		} else {
			if (cons == 4) {
				if (rel_time < 4410) {
					if (rel_time < 1029) {
						if (rel_time < 782) {
							w12 = 512;
						} else {
							w12 = 768;
						}
					} else {
						if (prod == 0) {
							w12 = 256;
						} else {
							w12 = 768;
						}
					}
				} else {
					if (rel_time < 4496) {
						if (prod == 1) {
							w12 = 0;
						} else {
							w12 = 2048;
						}
					} else {
						if (hops < 3) {
							w12 = 512;
						} else {
							w12 = 768;
						}
					}
				}
			} else {
				if (rel_time < 734) {
					if (hops < 4) {
						if (hops < 2) {
							w12 = 768;
						} else {
							w12 = 768;
						}
					} else {
						w12 = 768;
					}
				} else {
					if (hops < 3) {
						if (rel_time < 981) {
							w12 = 512;
						} else {
							w12 = 768;
						}
					} else {
						if (rel_time < 981) {
							w12 = 768;
						} else {
							w12 = 1024;
						}
					}
				}
			}
		}
	}
	int w13;
	if (size < 38) {
		if (hops < 2) {
			if (rel_time < 3510) {
				if (rel_time < 1677) {
					if (rel_time < 1529) {
						if (rel_time < 1382) {
							w13 = 256;
						} else {
							w13 = 0;
						}
					} else {
						if (cons == 3) {
							w13 = 512;
						} else {
							w13 = 1024;
						}
					}
				} else {
					if (rel_time < 1764) {
						if (cons == 2) {
							w13 = -256;
						} else {
							w13 = 0;
						}
					} else {
						if (rel_time < 2267) {
							w13 = 256;
						} else {
							w13 = 0;
						}
					}
				}
			} else {
				w13 = 512;
			}
		} else {
			if (rel_time < 3299) {
				if (rel_time < 3152) {
					if (rel_time < 3004) {
						if (rel_time < 2857) {
							w13 = 256;
						} else {
							w13 = 0;
						}
					} else {
						if (rel_time < 3033) {
							w13 = 1280;
						} else {
							w13 = 512;
						}
					}
				} else {
					if (cons == 3) {
						if (rel_time < 3181) {
							w13 = -256;
						} else {
							w13 = 256;
						}
					} else {
						if (hops < 3) {
							w13 = -512;
						} else {
							w13 = -256;
						}
					}
				}
			} else {
				if (rel_time < 3387) {
					if (cons == 2) {
						if (rel_time < 3328) {
							w13 = 512;
						} else {
							w13 = 768;
						}
					} else {
						if (hops < 3) {
							w13 = 256;
						} else {
							w13 = 256;
						}
					}
				} else {
					if (cons == 1) {
						if (rel_time < 3510) {
							w13 = 256;
						} else {
							w13 = 512;
						}
					} else {
						if (hops < 3) {
							w13 = 0;
						} else {
							w13 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 610) {
			if (rel_time < 539) {
				if (rel_time < 468) {
					if (cons == 0) {
						if (hops < 2) {
							w13 = 512;
						} else {
							w13 = 512;
						}
					} else {
						if (hops < 2) {
							w13 = 512;
						} else {
							w13 = 512;
						}
					}
				} else {
					if (hops < 2) {
						w13 = 256;
					} else {
						if (hops < 3) {
							w13 = 256;
						} else {
							w13 = 256;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						w13 = 512;
					} else {
						w13 = 768;
					}
				} else {
					w13 = 768;
				}
			}
		} else {
			if (cons == 1) {
				if (rel_time < 3739) {
					if (prod == 3) {
						if (prod == 1) {
							w13 = 256;
						} else {
							w13 = -512;
						}
					} else {
						if (hops < 3) {
							w13 = -512;
						} else {
							w13 = -1280;
						}
					}
				} else {
					if (rel_time < 3943) {
						if (prod == 4) {
							w13 = 1024;
						} else {
							w13 = 0;
						}
					} else {
						if (rel_time < 3987) {
							w13 = 0;
						} else {
							w13 = 512;
						}
					}
				}
			} else {
				if (rel_time < 831) {
					if (hops < 2) {
						w13 = 512;
					} else {
						if (hops < 3) {
							w13 = 768;
						} else {
							w13 = 768;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w13 = -256;
						} else {
							w13 = 0;
						}
					} else {
						if (hops < 5) {
							w13 = 0;
						} else {
							w13 = 256;
						}
					}
				}
			}
		}
	}
	int w14;
	if (size < 38) {
		if (hops < 5) {
			if (rel_time < 3299) {
				if (rel_time < 3152) {
					if (rel_time < 3004) {
						if (rel_time < 2857) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					} else {
						if (cons == 3) {
							w14 = 256;
						} else {
							w14 = 1024;
						}
					}
				} else {
					if (cons == 3) {
						if (rel_time < 3181) {
							w14 = -256;
						} else {
							w14 = 0;
						}
					} else {
						if (hops < 3) {
							w14 = -256;
						} else {
							w14 = 0;
						}
					}
				}
			} else {
				if (rel_time < 3387) {
					if (cons == 2) {
						if (hops < 4) {
							w14 = 512;
						} else {
							w14 = 256;
						}
					} else {
						if (hops < 3) {
							w14 = 0;
						} else {
							w14 = 256;
						}
					}
				} else {
					if (cons == 1) {
						if (rel_time < 3447) {
							w14 = 0;
						} else {
							w14 = 256;
						}
					} else {
						if (hops < 3) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 1824) {
				if (rel_time < 1677) {
					if (rel_time < 1529) {
						if (rel_time < 1382) {
							w14 = 256;
						} else {
							w14 = 0;
						}
					} else {
						if (cons == 2) {
							w14 = 768;
						} else {
							w14 = 256;
						}
					}
				} else {
					if (cons == 3) {
						if (rel_time < 1706) {
							w14 = -256;
						} else {
							w14 = 0;
						}
					} else {
						w14 = -512;
					}
				}
			} else {
				if (rel_time < 1912) {
					if (cons == 2) {
						if (rel_time < 1854) {
							w14 = 1280;
						} else {
							w14 = 1280;
						}
					} else {
						w14 = 512;
					}
				} else {
					if (rel_time < 2059) {
						if (cons == 0) {
							w14 = 0;
						} else {
							w14 = 1024;
						}
					} else {
						if (rel_time < 2267) {
							w14 = 768;
						} else {
							w14 = 256;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 610) {
			if (rel_time < 539) {
				if (rel_time < 468) {
					if (cons == 0) {
						if (cons == 2) {
							w14 = 256;
						} else {
							w14 = 256;
						}
					} else {
						if (hops < 4) {
							w14 = 256;
						} else {
							w14 = 256;
						}
					}
				} else {
					if (hops < 2) {
						w14 = 256;
					} else {
						if (hops < 3) {
							w14 = 0;
						} else {
							w14 = 256;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						w14 = 256;
					} else {
						w14 = 512;
					}
				} else {
					if (hops < 5) {
						w14 = 512;
					} else {
						w14 = 512;
					}
				}
			}
		} else {
			if (cons == 1) {
				if (rel_time < 879) {
					if (cons == 4) {
						if (rel_time < 681) {
							w14 = 256;
						} else {
							w14 = 0;
						}
					} else {
						if (hops < 4) {
							w14 = 256;
						} else {
							w14 = 512;
						}
					}
				} else {
					if (rel_time < 1126) {
						if (rel_time < 1029) {
							w14 = 256;
						} else {
							w14 = 512;
						}
					} else {
						if (rel_time < 3739) {
							w14 = 0;
						} else {
							w14 = 256;
						}
					}
				}
			} else {
				if (rel_time < 831) {
					if (hops < 2) {
						w14 = 512;
					} else {
						if (hops < 3) {
							w14 = 512;
						} else {
							w14 = 512;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					} else {
						if (hops < 5) {
							w14 = 0;
						} else {
							w14 = 256;
						}
					}
				}
			}
		}
	}
	int w15;
	if (size < 38) {
		if (hops < 3) {
			if (rel_time < 1677) {
				if (rel_time < 1529) {
					if (rel_time < 1382) {
						if (rel_time < 1234) {
							w15 = 0;
						} else {
							w15 = 256;
						}
					} else {
						if (cons == 2) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					}
				} else {
					if (cons == 2) {
						if (rel_time < 1617) {
							w15 = 768;
						} else {
							w15 = 256;
						}
					} else {
						if (hops < 2) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					}
				}
			} else {
				if (rel_time < 1764) {
					if (cons == 2) {
						if (hops < 2) {
							w15 = -256;
						} else {
							w15 = -512;
						}
					} else {
						if (hops < 2) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					}
				} else {
					if (rel_time < 1942) {
						if (cons == 1) {
							w15 = 0;
						} else {
							w15 = 768;
						}
					} else {
						if (rel_time < 2059) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 1529) {
				if (rel_time < 1382) {
					if (cons == 3) {
						if (cons == 1) {
							w15 = 0;
						} else {
							w15 = 512;
						}
					} else {
						if (hops < 5) {
							w15 = 512;
						} else {
							w15 = 768;
						}
					}
				} else {
					if (cons == 2) {
						if (rel_time < 1469) {
							w15 = -256;
						} else {
							w15 = 0;
						}
					} else {
						if (hops < 4) {
							w15 = 0;
						} else {
							w15 = 256;
						}
					}
				}
			} else {
				if (rel_time < 1677) {
					if (cons == 3) {
						if (rel_time < 1559) {
							w15 = 768;
						} else {
							w15 = 256;
						}
					} else {
						if (hops < 4) {
							w15 = 768;
						} else {
							w15 = 768;
						}
					}
				} else {
					if (rel_time < 1764) {
						if (cons == 2) {
							w15 = -512;
						} else {
							w15 = 0;
						}
					} else {
						if (rel_time < 2267) {
							w15 = 256;
						} else {
							w15 = 0;
						}
					}
				}
			}
		}
	} else {
		if (prod == 1) {
			if (rel_time < 10217) {
				if (rel_time < 9768) {
					if (rel_time < 9667) {
						if (rel_time < 9564) {
							w15 = 256;
						} else {
							w15 = -256;
						}
					} else {
						if (hops < 2) {
							w15 = 768;
						} else {
							w15 = 1024;
						}
					}
				} else {
					if (rel_time < 9825) {
						if (prod == 2) {
							w15 = -1024;
						} else {
							w15 = 1024;
						}
					} else {
						if (prod == 3) {
							w15 = 0;
						} else {
							w15 = 1280;
						}
					}
				}
			} else {
				if (prod == 3) {
					if (hops < 2) {
						if (rel_time < 10356) {
							w15 = 1024;
						} else {
							w15 = 768;
						}
					} else {
						if (hops < 4) {
							w15 = 1024;
						} else {
							w15 = 1024;
						}
					}
				} else {
					if (hops < 2) {
						if (rel_time < 10356) {
							w15 = -768;
						} else {
							w15 = -1024;
						}
					} else {
						if (hops < 3) {
							w15 = -768;
						} else {
							w15 = -768;
						}
					}
				}
			}
		} else {
			if (rel_time < 10042) {
				if (rel_time < 9768) {
					if (rel_time < 9494) {
						if (rel_time < 9219) {
							w15 = 0;
						} else {
							w15 = 1536;
						}
					} else {
						if (hops < 3) {
							w15 = -1024;
						} else {
							w15 = -768;
						}
					}
				} else {
					if (hops < 3) {
						w15 = 1280;
					} else {
						w15 = 1536;
					}
				}
			} else {
				if (hops < 2) {
					w15 = -1024;
				} else {
					w15 = -768;
				}
			}
		}
	}
	int w16;
	if (size < 38) {
		if (rel_time < 3299) {
			if (rel_time < 3152) {
				if (rel_time < 2944) {
					if (rel_time < 2857) {
						if (rel_time < 2709) {
							w16 = 0;
						} else {
							w16 = 256;
						}
					} else {
						if (cons == 2) {
							w16 = -512;
						} else {
							w16 = 256;
						}
					}
				} else {
					if (cons == 3) {
						if (cons == 1) {
							w16 = 0;
						} else {
							w16 = 512;
						}
					} else {
						if (hops < 5) {
							w16 = 512;
						} else {
							w16 = 768;
						}
					}
				}
			} else {
				if (cons == 4) {
					if (cons == 2) {
						if (rel_time < 3270) {
							w16 = -256;
						} else {
							w16 = 0;
						}
					} else {
						if (hops < 3) {
							w16 = 0;
						} else {
							w16 = 256;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					} else {
						if (hops < 5) {
							w16 = 0;
						} else {
							w16 = 256;
						}
					}
				}
			}
		} else {
			if (rel_time < 3387) {
				if (cons == 2) {
					if (rel_time < 3328) {
						if (hops < 5) {
							w16 = 256;
						} else {
							w16 = 512;
						}
					} else {
						if (hops < 2) {
							w16 = 256;
						} else {
							w16 = 256;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					} else {
						if (hops < 4) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					}
				}
			} else {
				if (cons == 1) {
					if (rel_time < 3447) {
						if (cons == 0) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					} else {
						if (cons == 3) {
							w16 = 256;
						} else {
							w16 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 3) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					} else {
						w16 = -256;
					}
				}
			}
		}
	} else {
		if (hops < 2) {
			if (rel_time < 734) {
				if (rel_time < 681) {
					if (rel_time < 397) {
						if (cons == 3) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					} else {
						if (cons == 2) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					}
				} else {
					w16 = 0;
				}
			} else {
				if (rel_time < 782) {
					w16 = 0;
				} else {
					if (rel_time < 831) {
						w16 = 256;
					} else {
						if (rel_time < 879) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					}
				}
			}
		} else {
			if (hops < 5) {
				if (prod == 1) {
					if (rel_time < 10217) {
						if (rel_time < 9944) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					} else {
						if (prod == 3) {
							w16 = 512;
						} else {
							w16 = -512;
						}
					}
				} else {
					if (rel_time < 10042) {
						if (rel_time < 9768) {
							w16 = 0;
						} else {
							w16 = 1024;
						}
					} else {
						if (hops < 3) {
							w16 = -512;
						} else {
							w16 = -512;
						}
					}
				}
			} else {
				if (rel_time < 10264) {
					if (rel_time < 10217) {
						if (rel_time < 3607) {
							w16 = 256;
						} else {
							w16 = 0;
						}
					} else {
						w16 = 768;
					}
				} else {
					if (rel_time < 10309) {
						w16 = -512;
					} else {
						if (prod == 3) {
							w16 = 768;
						} else {
							w16 = -512;
						}
					}
				}
			}
		}
	}
	int w17;
	if (size < 38) {
		if (rel_time < 2562) {
			if (rel_time < 2414) {
				if (rel_time < 2267) {
					if (rel_time < 2178) {
						if (rel_time < 2030) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					} else {
						if (rel_time < 2207) {
							w17 = 1024;
						} else {
							w17 = 0;
						}
					}
				} else {
					if (cons == 4) {
						if (cons == 2) {
							w17 = -512;
						} else {
							w17 = 0;
						}
					} else {
						if (hops < 4) {
							w17 = 0;
						} else {
							w17 = 256;
						}
					}
				}
			} else {
				if (cons == 3) {
					if (cons == 1) {
						if (rel_time < 2532) {
							w17 = 0;
						} else {
							w17 = 256;
						}
					} else {
						if (hops < 4) {
							w17 = 512;
						} else {
							w17 = 768;
						}
					}
				} else {
					if (hops < 4) {
						w17 = 512;
					} else {
						if (hops < 5) {
							w17 = 768;
						} else {
							w17 = 768;
						}
					}
				}
			}
		} else {
			if (rel_time < 2649) {
				if (cons == 2) {
					if (rel_time < 2591) {
						if (hops < 5) {
							w17 = -512;
						} else {
							w17 = -256;
						}
					} else {
						if (hops < 2) {
							w17 = -256;
						} else {
							w17 = -512;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 3) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					} else {
						w17 = 0;
					}
				}
			} else {
				if (rel_time < 2709) {
					if (rel_time < 2680) {
						if (hops < 2) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					} else {
						if (hops < 2) {
							w17 = -256;
						} else {
							w17 = -256;
						}
					}
				} else {
					if (rel_time < 2738) {
						if (hops < 4) {
							w17 = 256;
						} else {
							w17 = 768;
						}
					} else {
						if (cons == 1) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 610) {
			if (rel_time < 539) {
				if (rel_time < 468) {
					if (cons == 0) {
						if (hops < 2) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					} else {
						if (rel_time < 68) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w17 = 0;
					} else {
						if (hops < 3) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w17 = 0;
				} else {
					if (hops < 4) {
						w17 = 0;
					} else {
						if (hops < 5) {
							w17 = 256;
						} else {
							w17 = 256;
						}
					}
				}
			}
		} else {
			if (rel_time < 5415) {
				if (rel_time < 5334) {
					if (prod == 1) {
						if (rel_time < 5094) {
							w17 = 0;
						} else {
							w17 = 512;
						}
					} else {
						if (rel_time < 5094) {
							w17 = 0;
						} else {
							w17 = -1024;
						}
					}
				} else {
					if (prod == 3) {
						w17 = 768;
					} else {
						if (hops < 3) {
							w17 = -1024;
						} else {
							w17 = -1024;
						}
					}
				}
			} else {
				if (rel_time < 5692) {
					if (prod == 0) {
						if (prod == 2) {
							w17 = 1024;
						} else {
							w17 = -512;
						}
					} else {
						if (hops < 3) {
							w17 = -512;
						} else {
							w17 = -512;
						}
					}
				} else {
					if (rel_time < 5966) {
						if (prod == 2) {
							w17 = -512;
						} else {
							w17 = 768;
						}
					} else {
						if (rel_time < 6209) {
							w17 = 256;
						} else {
							w17 = 0;
						}
					}
				}
			}
		}
	}
	int w18;
	if (hops < 2) {
		if (rel_time < 981) {
			if (cons == 3) {
				if (rel_time < 734) {
					if (rel_time < 539) {
						if (rel_time < 397) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					} else {
						if (rel_time < 610) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					}
				} else {
					if (cons == 1) {
						if (rel_time < 879) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					} else {
						w18 = 0;
					}
				}
			} else {
				if (rel_time < 681) {
					if (rel_time < 318) {
						w18 = 0;
					} else {
						w18 = 0;
					}
				} else {
					w18 = 256;
				}
			}
		} else {
			if (rel_time < 3739) {
				if (prod == 3) {
					if (rel_time < 3651) {
						if (rel_time < 3607) {
							w18 = 0;
						} else {
							w18 = -512;
						}
					} else {
						w18 = 512;
					}
				} else {
					w18 = -768;
				}
			} else {
				if (rel_time < 4132) {
					if (prod == 4) {
						if (prod == 2) {
							w18 = 768;
						} else {
							w18 = -512;
						}
					} else {
						if (rel_time < 3898) {
							w18 = -256;
						} else {
							w18 = -512;
						}
					}
				} else {
					if (rel_time < 4219) {
						if (prod == 1) {
							w18 = 768;
						} else {
							w18 = -768;
						}
					} else {
						if (rel_time < 4264) {
							w18 = 512;
						} else {
							w18 = 0;
						}
					}
				}
			}
		}
	} else {
		if (hops < 5) {
			if (size < 38) {
				if (rel_time < 2562) {
					if (rel_time < 2414) {
						if (rel_time < 2267) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					} else {
						if (cons == 3) {
							w18 = 256;
						} else {
							w18 = 512;
						}
					}
				} else {
					if (rel_time < 2649) {
						if (cons == 2) {
							w18 = -256;
						} else {
							w18 = 0;
						}
					} else {
						if (rel_time < 2944) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					}
				}
			} else {
				if (rel_time < 9825) {
					if (rel_time < 9768) {
						if (rel_time < 9290) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					} else {
						if (prod == 2) {
							w18 = -768;
						} else {
							w18 = 512;
						}
					}
				} else {
					if (rel_time < 9944) {
						if (prod == 4) {
							w18 = -768;
						} else {
							w18 = 768;
						}
					} else {
						if (prod == 3) {
							w18 = 0;
						} else {
							w18 = 256;
						}
					}
				}
			}
		} else {
			if (cons == 0) {
				if (rel_time < 3607) {
					if (rel_time < 3467) {
						if (rel_time < 3447) {
							w18 = 0;
						} else {
							w18 = -256;
						}
					} else {
						if (cons == 4) {
							w18 = 256;
						} else {
							w18 = 0;
						}
					}
				} else {
					if (rel_time < 3651) {
						w18 = -768;
					} else {
						if (rel_time < 3739) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					}
				}
			} else {
				if (rel_time < 2001) {
					if (rel_time < 1824) {
						if (rel_time < 1677) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					} else {
						w18 = 512;
					}
				} else {
					if (rel_time < 2149) {
						w18 = -512;
					} else {
						if (rel_time < 2562) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					}
				}
			}
		}
	}
	int w19;
	if (rel_time < 1029) {
		if (cons == 0) {
			if (cons == 2) {
				if (rel_time < 681) {
					if (rel_time < 397) {
						if (rel_time < 318) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					} else {
						if (hops < 2) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					}
				} else {
					if (rel_time < 927) {
						if (rel_time < 734) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					} else {
						if (hops < 3) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					}
				}
			} else {
				if (rel_time < 610) {
					if (rel_time < 244) {
						if (hops < 2) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					} else {
						if (hops < 2) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					} else {
						if (hops < 5) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 468) {
				if (hops < 4) {
					if (hops < 2) {
						if (rel_time < 68) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					} else {
						if (rel_time < 68) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					}
				} else {
					if (rel_time < 68) {
						if (hops < 5) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					} else {
						if (hops < 5) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					}
				}
			} else {
				if (rel_time < 782) {
					if (hops < 3) {
						if (hops < 2) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					} else {
						if (hops < 4) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w19 = 0;
					} else {
						if (hops < 4) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 1529) {
			if (rel_time < 1382) {
				if (rel_time < 1234) {
					if (cons == 3) {
						if (rel_time < 1078) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					} else {
						if (hops < 2) {
							w19 = -768;
						} else {
							w19 = -256;
						}
					}
				} else {
					if (cons == 3) {
						if (cons == 2) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					} else {
						if (hops < 2) {
							w19 = 256;
						} else {
							w19 = 256;
						}
					}
				}
			} else {
				if (cons == 2) {
					if (cons == 4) {
						if (rel_time < 1469) {
							w19 = -256;
						} else {
							w19 = 0;
						}
					} else {
						if (hops < 4) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					} else {
						if (hops < 5) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 1677) {
				if (cons == 2) {
					if (rel_time < 1617) {
						if (hops < 2) {
							w19 = 256;
						} else {
							w19 = 512;
						}
					} else {
						if (cons == 0) {
							w19 = 0;
						} else {
							w19 = 256;
						}
					}
				} else {
					if (hops < 2) {
						w19 = 0;
					} else {
						if (hops < 4) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					}
				}
			} else {
				if (rel_time < 1824) {
					if (cons == 4) {
						if (cons == 2) {
							w19 = -256;
						} else {
							w19 = 0;
						}
					} else {
						if (hops < 4) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					}
				} else {
					if (rel_time < 1854) {
						if (hops < 3) {
							w19 = 512;
						} else {
							w19 = 768;
						}
					} else {
						if (rel_time < 2059) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					}
				}
			}
		}
	}
	int w20;
	if (rel_time < 10356) {
		if (rel_time < 10264) {
			if (rel_time < 9825) {
				if (rel_time < 9768) {
					if (rel_time < 9290) {
						if (rel_time < 9219) {
							w20 = 0;
						} else {
							w20 = -768;
						}
					} else {
						if (prod == 3) {
							w20 = 0;
						} else {
							w20 = 1280;
						}
					}
				} else {
					if (prod == 2) {
						if (hops < 2) {
							w20 = -768;
						} else {
							w20 = -512;
						}
					} else {
						if (hops < 5) {
							w20 = 256;
						} else {
							w20 = 512;
						}
					}
				}
			} else {
				if (prod == 3) {
					if (rel_time < 9944) {
						if (prod == 0) {
							w20 = 768;
						} else {
							w20 = -256;
						}
					} else {
						if (prod == 1) {
							w20 = -256;
						} else {
							w20 = 256;
						}
					}
				} else {
					if (rel_time < 9944) {
						w20 = -1280;
					} else {
						if (hops < 3) {
							w20 = 768;
						} else {
							w20 = 1024;
						}
					}
				}
			}
		} else {
			if (prod == 2) {
				if (hops < 2) {
					w20 = -768;
				} else {
					if (rel_time < 10309) {
						if (hops < 3) {
							w20 = -512;
						} else {
							w20 = -512;
						}
					} else {
						w20 = -512;
					}
				}
			} else {
				if (hops < 2) {
					w20 = 512;
				} else {
					if (hops < 3) {
						w20 = 512;
					} else {
						w20 = 256;
					}
				}
			}
		}
	} else {
		if (prod == 3) {
			if (hops < 2) {
				w20 = 512;
			} else {
				if (hops < 4) {
					w20 = 256;
				} else {
					if (hops < 5) {
						w20 = 256;
					} else {
						w20 = 256;
					}
				}
			}
		} else {
			if (hops < 2) {
				w20 = -768;
			} else {
				if (hops < 5) {
					if (hops < 4) {
						w20 = -512;
					} else {
						w20 = -512;
					}
				} else {
					w20 = -512;
				}
			}
		}
	}
	int w21;
	if (prod == 0) {
		if (rel_time < 10096) {
			if (rel_time < 9825) {
				if (rel_time < 9564) {
					if (rel_time < 9290) {
						if (rel_time < 9014) {
							w21 = 0;
						} else {
							w21 = -256;
						}
					} else {
						if (prod == 2) {
							w21 = 768;
						} else {
							w21 = -512;
						}
					}
				} else {
					if (prod == 2) {
						if (prod == 1) {
							w21 = -512;
						} else {
							w21 = -768;
						}
					} else {
						if (rel_time < 9768) {
							w21 = 512;
						} else {
							w21 = 256;
						}
					}
				}
			} else {
				if (prod == 2) {
					if (rel_time < 9944) {
						if (prod == 3) {
							w21 = 512;
						} else {
							w21 = -768;
						}
					} else {
						if (hops < 2) {
							w21 = 512;
						} else {
							w21 = 512;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w21 = -512;
						} else {
							w21 = -256;
						}
					} else {
						if (hops < 5) {
							w21 = -256;
						} else {
							w21 = -256;
						}
					}
				}
			}
		} else {
			if (prod == 2) {
				if (rel_time < 10356) {
					if (rel_time < 10217) {
						if (prod == 3) {
							w21 = -256;
						} else {
							w21 = 512;
						}
					} else {
						if (rel_time < 10264) {
							w21 = -768;
						} else {
							w21 = -256;
						}
					}
				} else {
					if (prod == 3) {
						if (hops < 2) {
							w21 = 256;
						} else {
							w21 = 256;
						}
					} else {
						if (hops < 2) {
							w21 = -512;
						} else {
							w21 = -256;
						}
					}
				}
			} else {
				if (hops < 2) {
					w21 = 256;
				} else {
					if (hops < 3) {
						w21 = 256;
					} else {
						w21 = 256;
					}
				}
			}
		}
	} else {
		if (rel_time < 9994) {
			if (rel_time < 4219) {
				if (rel_time < 3898) {
					if (rel_time < 3607) {
						if (hops < 3) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					} else {
						if (hops < 3) {
							w21 = 256;
						} else {
							w21 = 0;
						}
					}
				} else {
					if (hops < 2) {
						if (rel_time < 4132) {
							w21 = 512;
						} else {
							w21 = 512;
						}
					} else {
						w21 = 768;
					}
				}
			} else {
				if (rel_time < 4496) {
					if (rel_time < 4410) {
						if (hops < 3) {
							w21 = -768;
						} else {
							w21 = -512;
						}
					} else {
						if (hops < 3) {
							w21 = -512;
						} else {
							w21 = -256;
						}
					}
				} else {
					if (rel_time < 4772) {
						w21 = 768;
					} else {
						if (rel_time < 5009) {
							w21 = -512;
						} else {
							w21 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 10217) {
				w21 = 768;
			} else {
				if (hops < 2) {
					w21 = 512;
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w21 = 512;
						} else {
							w21 = 512;
						}
					} else {
						w21 = 512;
					}
				}
			}
		}
	}
	int w22;
	if (rel_time < 8739) {
		if (rel_time < 8690) {
			if (rel_time < 8619) {
				if (rel_time < 8567) {
					if (rel_time < 8292) {
						if (rel_time < 8017) {
							w22 = 0;
						} else {
							w22 = -256;
						}
					} else {
						if (prod == 1) {
							w22 = 0;
						} else {
							w22 = 1280;
						}
					}
				} else {
					if (prod == 0) {
						if (hops < 2) {
							w22 = -1024;
						} else {
							w22 = -1024;
						}
					} else {
						w22 = 768;
					}
				}
			} else {
				if (prod == 2) {
					w22 = -1024;
				} else {
					if (hops < 2) {
						w22 = 512;
					} else {
						w22 = 768;
					}
				}
			}
		} else {
			if (prod == 3) {
				if (hops < 2) {
					w22 = 512;
				} else {
					w22 = 768;
				}
			} else {
				w22 = -1024;
			}
		}
	} else {
		if (rel_time < 9014) {
			if (prod == 0) {
				if (prod == 2) {
					if (prod == 4) {
						if (rel_time < 8963) {
							w22 = 1280;
						} else {
							w22 = 1280;
						}
					} else {
						if (rel_time < 8842) {
							w22 = 768;
						} else {
							w22 = -768;
						}
					}
				} else {
					if (hops < 3) {
						w22 = -768;
					} else {
						w22 = -512;
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w22 = -512;
					} else {
						w22 = -768;
					}
				} else {
					w22 = -512;
				}
			}
		} else {
			if (prod == 1) {
				if (rel_time < 9219) {
					if (prod == 4) {
						if (rel_time < 9166) {
							w22 = 768;
						} else {
							w22 = 768;
						}
					} else {
						if (hops < 3) {
							w22 = -512;
						} else {
							w22 = -512;
						}
					}
				} else {
					if (rel_time < 9494) {
						if (prod == 4) {
							w22 = -512;
						} else {
							w22 = 512;
						}
					} else {
						if (rel_time < 9768) {
							w22 = 256;
						} else {
							w22 = 0;
						}
					}
				}
			} else {
				if (rel_time < 9219) {
					w22 = -1024;
				} else {
					if (rel_time < 9494) {
						if (hops < 3) {
							w22 = 512;
						} else {
							w22 = 512;
						}
					} else {
						if (rel_time < 9768) {
							w22 = -512;
						} else {
							w22 = 0;
						}
					}
				}
			}
		}
	}
	int w23;
	if (rel_time < 6666) {
		if (rel_time < 6621) {
			if (rel_time < 6486) {
				if (rel_time < 6391) {
					if (prod == 4) {
						if (rel_time < 6161) {
							w23 = 0;
						} else {
							w23 = 256;
						}
					} else {
						if (rel_time < 6069) {
							w23 = 0;
						} else {
							w23 = -512;
						}
					}
				} else {
					if (prod == 2) {
						if (hops < 3) {
							w23 = -1280;
						} else {
							w23 = -1024;
						}
					} else {
						if (hops < 3) {
							w23 = 768;
						} else {
							w23 = 768;
						}
					}
				}
			} else {
				if (prod == 4) {
					if (prod == 0) {
						w23 = -1024;
					} else {
						w23 = -512;
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w23 = 768;
						} else {
							w23 = 768;
						}
					} else {
						if (hops < 4) {
							w23 = 512;
						} else {
							w23 = 768;
						}
					}
				}
			}
		} else {
			if (prod == 0) {
				w23 = 1280;
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w23 = -512;
					} else {
						w23 = -768;
					}
				} else {
					w23 = -512;
				}
			}
		}
	} else {
		if (rel_time < 6761) {
			if (prod == 2) {
				if (hops < 3) {
					w23 = 1280;
				} else {
					w23 = 1280;
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w23 = -512;
					} else {
						w23 = -768;
					}
				} else {
					w23 = -512;
				}
			}
		} else {
			if (rel_time < 7220) {
				if (prod == 2) {
					if (rel_time < 6943) {
						if (prod == 4) {
							w23 = 512;
						} else {
							w23 = -512;
						}
					} else {
						if (prod == 4) {
							w23 = -768;
						} else {
							w23 = 768;
						}
					}
				} else {
					if (hops < 2) {
						w23 = 512;
					} else {
						w23 = 768;
					}
				}
			} else {
				if (rel_time < 7266) {
					if (prod == 1) {
						if (hops < 3) {
							w23 = -512;
						} else {
							w23 = -512;
						}
					} else {
						if (hops < 3) {
							w23 = 1280;
						} else {
							w23 = 1280;
						}
					}
				} else {
					if (rel_time < 7493) {
						if (prod == 3) {
							w23 = 0;
						} else {
							w23 = 1280;
						}
					} else {
						if (rel_time < 7541) {
							w23 = -1024;
						} else {
							w23 = 0;
						}
					}
				}
			}
		}
	}
	int w24;
	if (prod == 0) {
		if (rel_time < 10096) {
			if (rel_time < 9825) {
				if (rel_time < 9564) {
					if (rel_time < 9290) {
						if (rel_time < 9014) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					} else {
						if (prod == 2) {
							w24 = 256;
						} else {
							w24 = -256;
						}
					}
				} else {
					if (prod == 2) {
						if (rel_time < 9768) {
							w24 = -256;
						} else {
							w24 = -256;
						}
					} else {
						if (rel_time < 9768) {
							w24 = 256;
						} else {
							w24 = 0;
						}
					}
				}
			} else {
				if (prod == 2) {
					if (hops < 2) {
						if (prod == 3) {
							w24 = 512;
						} else {
							w24 = 256;
						}
					} else {
						if (rel_time < 9994) {
							w24 = 256;
						} else {
							w24 = 256;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w24 = -256;
						} else {
							w24 = -256;
						}
					} else {
						if (hops < 4) {
							w24 = -256;
						} else {
							w24 = -256;
						}
					}
				}
			}
		} else {
			if (prod == 2) {
				if (rel_time < 10356) {
					if (hops < 2) {
						if (prod == 1) {
							w24 = -256;
						} else {
							w24 = -512;
						}
					} else {
						if (prod == 3) {
							w24 = -256;
						} else {
							w24 = 0;
						}
					}
				} else {
					if (prod == 3) {
						if (hops < 2) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					} else {
						if (hops < 2) {
							w24 = -256;
						} else {
							w24 = -256;
						}
					}
				}
			} else {
				if (hops < 2) {
					w24 = 256;
				} else {
					if (hops < 3) {
						w24 = 0;
					} else {
						if (hops < 5) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 9994) {
			if (rel_time < 9717) {
				if (rel_time < 9443) {
					if (rel_time < 9166) {
						if (rel_time < 8892) {
							w24 = 0;
						} else {
							w24 = 512;
						}
					} else {
						if (hops < 5) {
							w24 = -512;
						} else {
							w24 = -256;
						}
					}
				} else {
					if (rel_time < 9667) {
						w24 = 768;
					} else {
						if (hops < 3) {
							w24 = 256;
						} else {
							w24 = 256;
						}
					}
				}
			} else {
				if (hops < 2) {
					if (rel_time < 9944) {
						w24 = -512;
					} else {
						w24 = -512;
					}
				} else {
					if (rel_time < 9944) {
						if (hops < 3) {
							w24 = -256;
						} else {
							w24 = 0;
						}
					} else {
						if (hops < 3) {
							w24 = -512;
						} else {
							w24 = -256;
						}
					}
				}
			}
		} else {
			if (rel_time < 10217) {
				w24 = 512;
			} else {
				if (hops < 2) {
					w24 = 256;
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w24 = 256;
						} else {
							w24 = 256;
						}
					} else {
						w24 = 256;
					}
				}
			}
		}
	}
	int w25;
	if (hops < 4) {
		if (rel_time < 7742) {
			if (rel_time < 7493) {
				if (rel_time < 7361) {
					if (rel_time < 7220) {
						if (rel_time < 6943) {
							w25 = 0;
						} else {
							w25 = 0;
						}
					} else {
						if (prod == 2) {
							w25 = 256;
						} else {
							w25 = -512;
						}
					}
				} else {
					if (prod == 0) {
						if (hops < 3) {
							w25 = -512;
						} else {
							w25 = -512;
						}
					} else {
						if (hops < 3) {
							w25 = 768;
						} else {
							w25 = 768;
						}
					}
				}
			} else {
				if (prod == 2) {
					if (prod == 4) {
						if (prod == 3) {
							w25 = -768;
						} else {
							w25 = -1024;
						}
					} else {
						if (hops < 2) {
							w25 = 512;
						} else {
							w25 = 768;
						}
					}
				} else {
					if (rel_time < 7541) {
						w25 = 1024;
					} else {
						if (hops < 2) {
							w25 = 512;
						} else {
							w25 = 768;
						}
					}
				}
			}
		} else {
			if (rel_time < 7818) {
				if (prod == 1) {
					w25 = -768;
				} else {
					w25 = 1280;
				}
			} else {
				if (prod == 1) {
					if (rel_time < 8139) {
						if (prod == 4) {
							w25 = 512;
						} else {
							w25 = -768;
						}
					} else {
						if (rel_time < 8415) {
							w25 = -256;
						} else {
							w25 = 0;
						}
					}
				} else {
					if (rel_time < 8092) {
						if (hops < 2) {
							w25 = -1024;
						} else {
							w25 = -1024;
						}
					} else {
						if (rel_time < 8415) {
							w25 = 768;
						} else {
							w25 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 2267) {
			if (rel_time < 2090) {
				if (rel_time < 2030) {
					if (rel_time < 1824) {
						if (rel_time < 1677) {
							w25 = 0;
						} else {
							w25 = -256;
						}
					} else {
						if (rel_time < 1912) {
							w25 = 512;
						} else {
							w25 = 0;
						}
					}
				} else {
					if (rel_time < 2059) {
						if (hops < 5) {
							w25 = -1024;
						} else {
							w25 = -768;
						}
					} else {
						if (hops < 5) {
							w25 = 0;
						} else {
							w25 = 0;
						}
					}
				}
			} else {
				if (cons == 0) {
					if (rel_time < 2149) {
						w25 = 1024;
					} else {
						if (cons == 3) {
							w25 = 0;
						} else {
							w25 = 768;
						}
					}
				} else {
					if (rel_time < 2149) {
						if (hops < 5) {
							w25 = -512;
						} else {
							w25 = -256;
						}
					} else {
						if (hops < 5) {
							w25 = 0;
						} else {
							w25 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 2354) {
				if (cons == 2) {
					if (rel_time < 2325) {
						w25 = -256;
					} else {
						w25 = -512;
					}
				} else {
					if (hops < 5) {
						w25 = 0;
					} else {
						w25 = 0;
					}
				}
			} else {
				if (rel_time < 2502) {
					if (cons == 1) {
						if (rel_time < 2473) {
							w25 = 0;
						} else {
							w25 = 256;
						}
					} else {
						if (hops < 5) {
							w25 = 512;
						} else {
							w25 = 512;
						}
					}
				} else {
					if (rel_time < 3898) {
						if (prod == 1) {
							w25 = 0;
						} else {
							w25 = -1280;
						}
					} else {
						if (rel_time < 3943) {
							w25 = 1024;
						} else {
							w25 = 0;
						}
					}
				}
			}
		}
	}
	int w26;
	if (rel_time < 4863) {
		if (rel_time < 4817) {
			if (rel_time < 4772) {
				if (rel_time < 4686) {
					if (rel_time < 4410) {
						if (prod == 1) {
							w26 = 0;
						} else {
							w26 = -256;
						}
					} else {
						if (prod == 3) {
							w26 = 0;
						} else {
							w26 = 1280;
						}
					}
				} else {
					if (prod == 1) {
						w26 = 512;
					} else {
						w26 = -1024;
					}
				}
			} else {
				if (prod == 2) {
					w26 = -1024;
				} else {
					w26 = 768;
				}
			}
		} else {
			if (prod == 3) {
				w26 = 768;
			} else {
				w26 = -1024;
			}
		}
	} else {
		if (rel_time < 5139) {
			if (prod == 2) {
				if (prod == 0) {
					if (prod == 4) {
						if (rel_time < 5094) {
							w26 = 1280;
						} else {
							w26 = 1024;
						}
					} else {
						if (rel_time < 4963) {
							w26 = 768;
						} else {
							w26 = -768;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w26 = -512;
						} else {
							w26 = -512;
						}
					} else {
						w26 = -256;
					}
				}
			} else {
				if (hops < 3) {
					w26 = -768;
				} else {
					w26 = -512;
				}
			}
		} else {
			if (rel_time < 5415) {
				if (prod == 2) {
					if (prod == 0) {
						if (prod == 4) {
							w26 = -768;
						} else {
							w26 = -512;
						}
					} else {
						if (hops < 3) {
							w26 = 512;
						} else {
							w26 = 512;
						}
					}
				} else {
					if (rel_time < 5334) {
						if (hops < 2) {
							w26 = 512;
						} else {
							w26 = 512;
						}
					} else {
						w26 = 512;
					}
				}
			} else {
				if (rel_time < 5692) {
					if (prod == 0) {
						if (prod == 2) {
							w26 = 768;
						} else {
							w26 = -512;
						}
					} else {
						if (hops < 3) {
							w26 = -512;
						} else {
							w26 = -512;
						}
					}
				} else {
					if (rel_time < 5966) {
						if (prod == 0) {
							w26 = -512;
						} else {
							w26 = 768;
						}
					} else {
						if (rel_time < 6069) {
							w26 = 256;
						} else {
							w26 = 0;
						}
					}
				}
			}
		}
	}
	int w27;
	if (prod == 4) {
		if (rel_time < 10309) {
			if (rel_time < 8415) {
				if (rel_time < 8139) {
					if (rel_time < 7742) {
						if (rel_time < 7589) {
							w27 = 0;
						} else {
							w27 = -512;
						}
					} else {
						if (prod == 3) {
							w27 = 0;
						} else {
							w27 = 768;
						}
					}
				} else {
					if (prod == 1) {
						if (rel_time < 8188) {
							w27 = -1024;
						} else {
							w27 = -512;
						}
					} else {
						if (hops < 4) {
							w27 = 512;
						} else {
							w27 = 768;
						}
					}
				}
			} else {
				if (rel_time < 8567) {
					if (rel_time < 8465) {
						w27 = 1280;
					} else {
						if (hops < 3) {
							w27 = 512;
						} else {
							w27 = 768;
						}
					}
				} else {
					if (rel_time < 8842) {
						if (prod == 2) {
							w27 = -512;
						} else {
							w27 = 512;
						}
					} else {
						if (rel_time < 9118) {
							w27 = 256;
						} else {
							w27 = 0;
						}
					}
				}
			}
		} else {
			if (prod == 2) {
				if (hops < 2) {
					w27 = -256;
				} else {
					if (rel_time < 10356) {
						if (hops < 3) {
							w27 = -256;
						} else {
							w27 = -256;
						}
					} else {
						if (hops < 5) {
							w27 = 0;
						} else {
							w27 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w27 = 0;
				} else {
					if (hops < 3) {
						w27 = 0;
					} else {
						if (hops < 5) {
							w27 = 0;
						} else {
							w27 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 4132) {
			if (rel_time < 3898) {
				if (hops < 3) {
					if (hops < 2) {
						if (rel_time < 3739) {
							w27 = 256;
						} else {
							w27 = 0;
						}
					} else {
						if (rel_time < 3739) {
							w27 = 1024;
						} else {
							w27 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (rel_time < 3739) {
							w27 = 256;
						} else {
							w27 = -768;
						}
					} else {
						if (hops < 5) {
							w27 = -256;
						} else {
							w27 = -256;
						}
					}
				}
			} else {
				if (hops < 2) {
					w27 = -512;
				} else {
					if (hops < 4) {
						w27 = -768;
					} else {
						w27 = -768;
					}
				}
			}
		} else {
			if (rel_time < 4410) {
				if (hops < 2) {
					w27 = 768;
				} else {
					w27 = 768;
				}
			} else {
				if (rel_time < 4686) {
					if (hops < 3) {
						if (hops < 2) {
							w27 = -512;
						} else {
							w27 = -768;
						}
					} else {
						w27 = -512;
					}
				} else {
					if (rel_time < 4963) {
						if (hops < 3) {
							w27 = 512;
						} else {
							w27 = 512;
						}
					} else {
						if (rel_time < 5240) {
							w27 = -512;
						} else {
							w27 = 0;
						}
					}
				}
			}
		}
	}
	int w28;
	if (cons == 0) {
		if (prod == 4) {
			if (hops < 2) {
				if (rel_time < 981) {
					if (rel_time < 879) {
						if (rel_time < 831) {
							w28 = 0;
						} else {
							w28 = 0;
						}
					} else {
						if (rel_time < 927) {
							w28 = 0;
						} else {
							w28 = 0;
						}
					}
				} else {
					if (rel_time < 2059) {
						if (rel_time < 1942) {
							w28 = 0;
						} else {
							w28 = -512;
						}
					} else {
						if (rel_time < 2207) {
							w28 = 256;
						} else {
							w28 = 0;
						}
					}
				}
			} else {
				if (rel_time < 8017) {
					if (rel_time < 7864) {
						if (rel_time < 7818) {
							w28 = 0;
						} else {
							w28 = -512;
						}
					} else {
						if (rel_time < 7913) {
							w28 = 768;
						} else {
							w28 = 512;
						}
					}
				} else {
					if (rel_time < 8092) {
						if (prod == 1) {
							w28 = 512;
						} else {
							w28 = -768;
						}
					} else {
						if (rel_time < 8139) {
							w28 = 512;
						} else {
							w28 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 4132) {
				if (rel_time < 3898) {
					if (hops < 3) {
						if (hops < 2) {
							w28 = 0;
						} else {
							w28 = 0;
						}
					} else {
						if (hops < 4) {
							w28 = -512;
						} else {
							w28 = -256;
						}
					}
				} else {
					if (hops < 2) {
						w28 = -256;
					} else {
						if (hops < 4) {
							w28 = -512;
						} else {
							w28 = -512;
						}
					}
				}
			} else {
				if (rel_time < 4410) {
					if (hops < 2) {
						w28 = 512;
					} else {
						w28 = 512;
					}
				} else {
					if (rel_time < 4686) {
						if (hops < 3) {
							w28 = -512;
						} else {
							w28 = -256;
						}
					} else {
						if (rel_time < 4963) {
							w28 = 256;
						} else {
							w28 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 2001) {
			if (rel_time < 1824) {
				if (rel_time < 1677) {
					if (rel_time < 1529) {
						if (rel_time < 1382) {
							w28 = 0;
						} else {
							w28 = 0;
						}
					} else {
						if (hops < 2) {
							w28 = 0;
						} else {
							w28 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 2) {
							w28 = -256;
						} else {
							w28 = 0;
						}
					} else {
						w28 = 0;
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w28 = 768;
					} else {
						w28 = 768;
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w28 = 512;
						} else {
							w28 = 512;
						}
					} else {
						w28 = 256;
					}
				}
			}
		} else {
			if (rel_time < 2149) {
				if (hops < 4) {
					if (hops < 2) {
						w28 = -768;
					} else {
						w28 = -512;
					}
				} else {
					if (hops < 5) {
						w28 = -256;
					} else {
						w28 = -256;
					}
				}
			} else {
				if (rel_time < 2562) {
					if (rel_time < 2414) {
						if (rel_time < 2267) {
							w28 = 0;
						} else {
							w28 = 0;
						}
					} else {
						if (hops < 2) {
							w28 = 0;
						} else {
							w28 = 0;
						}
					}
				} else {
					if (rel_time < 2709) {
						if (hops < 2) {
							w28 = -256;
						} else {
							w28 = 0;
						}
					} else {
						if (rel_time < 2857) {
							w28 = 0;
						} else {
							w28 = 0;
						}
					}
				}
			}
		}
	}
	int w29;
	if (hops < 5) {
		if (rel_time < 6666) {
			if (rel_time < 6621) {
				if (rel_time < 6486) {
					if (rel_time < 6391) {
						if (rel_time < 5966) {
							w29 = 0;
						} else {
							w29 = 0;
						}
					} else {
						if (prod == 2) {
							w29 = -768;
						} else {
							w29 = 512;
						}
					}
				} else {
					if (prod == 4) {
						if (prod == 0) {
							w29 = -768;
						} else {
							w29 = -512;
						}
					} else {
						if (hops < 3) {
							w29 = 512;
						} else {
							w29 = 512;
						}
					}
				}
			} else {
				if (prod == 0) {
					w29 = 768;
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w29 = -512;
						} else {
							w29 = -512;
						}
					} else {
						if (hops < 4) {
							w29 = -256;
						} else {
							w29 = -512;
						}
					}
				}
			}
		} else {
			if (rel_time < 6761) {
				if (prod == 2) {
					if (hops < 3) {
						if (rel_time < 6714) {
							w29 = 768;
						} else {
							w29 = 768;
						}
					} else {
						if (hops < 4) {
							w29 = 768;
						} else {
							w29 = 768;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w29 = -512;
						} else {
							w29 = -512;
						}
					} else {
						if (hops < 4) {
							w29 = -256;
						} else {
							w29 = -512;
						}
					}
				}
			} else {
				if (rel_time < 7037) {
					if (prod == 1) {
						if (prod == 4) {
							w29 = 256;
						} else {
							w29 = -512;
						}
					} else {
						if (rel_time < 6943) {
							w29 = -1280;
						} else {
							w29 = -768;
						}
					}
				} else {
					if (rel_time < 7493) {
						if (prod == 1) {
							w29 = 0;
						} else {
							w29 = 768;
						}
					} else {
						if (rel_time < 7541) {
							w29 = -512;
						} else {
							w29 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 782) {
			if (rel_time < 734) {
				if (rel_time < 468) {
					if (cons == 1) {
						if (rel_time < 244) {
							w29 = 0;
						} else {
							w29 = 0;
						}
					} else {
						w29 = 0;
					}
				} else {
					if (rel_time < 539) {
						w29 = 0;
					} else {
						if (cons == 3) {
							w29 = 0;
						} else {
							w29 = 0;
						}
					}
				}
			} else {
				w29 = 0;
			}
		} else {
			if (rel_time < 831) {
				w29 = 0;
			} else {
				if (rel_time < 879) {
					w29 = 0;
				} else {
					if (rel_time < 4032) {
						if (rel_time < 3987) {
							w29 = 0;
						} else {
							w29 = 1024;
						}
					} else {
						if (rel_time < 4219) {
							w29 = -256;
						} else {
							w29 = 0;
						}
					}
				}
			}
		}
	}
	int w30;
	if (cons == 4) {
		if (rel_time < 4410) {
			if (rel_time < 4264) {
				if (rel_time < 4219) {
					if (rel_time < 4132) {
						if (rel_time < 3987) {
							w30 = 0;
						} else {
							w30 = 256;
						}
					} else {
						if (prod == 1) {
							w30 = 256;
						} else {
							w30 = -768;
						}
					}
				} else {
					if (prod == 2) {
						if (hops < 2) {
							w30 = -1280;
						} else {
							w30 = -1024;
						}
					} else {
						if (hops < 2) {
							w30 = 512;
						} else {
							w30 = 768;
						}
					}
				}
			} else {
				if (prod == 4) {
					if (rel_time < 4309) {
						if (hops < 3) {
							w30 = -1024;
						} else {
							w30 = -1024;
						}
					} else {
						if (hops < 2) {
							w30 = -512;
						} else {
							w30 = -512;
						}
					}
				} else {
					w30 = 256;
				}
			}
		} else {
			if (rel_time < 4496) {
				if (prod == 1) {
					if (prod == 0) {
						w30 = -512;
					} else {
						if (hops < 3) {
							w30 = -256;
						} else {
							w30 = -256;
						}
					}
				} else {
					if (hops < 3) {
						w30 = 768;
					} else {
						w30 = 768;
					}
				}
			} else {
				if (rel_time < 4541) {
					if (prod == 2) {
						if (hops < 3) {
							w30 = 768;
						} else {
							w30 = 768;
						}
					} else {
						if (hops < 3) {
							w30 = -512;
						} else {
							w30 = -512;
						}
					}
				} else {
					if (rel_time < 4586) {
						if (prod == 3) {
							w30 = -256;
						} else {
							w30 = 768;
						}
					} else {
						if (rel_time < 4863) {
							w30 = 0;
						} else {
							w30 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 2975) {
			if (rel_time < 2827) {
				if (hops < 3) {
					if (rel_time < 734) {
						if (rel_time < 397) {
							w30 = 0;
						} else {
							w30 = 0;
						}
					} else {
						if (rel_time < 981) {
							w30 = 0;
						} else {
							w30 = 0;
						}
					}
				} else {
					if (rel_time < 2680) {
						if (rel_time < 397) {
							w30 = 0;
						} else {
							w30 = 0;
						}
					} else {
						if (hops < 4) {
							w30 = 0;
						} else {
							w30 = 0;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						w30 = 256;
					} else {
						if (hops < 3) {
							w30 = 256;
						} else {
							w30 = 256;
						}
					}
				} else {
					w30 = 256;
				}
			}
		} else {
			if (rel_time < 3447) {
				if (rel_time < 3122) {
					if (hops < 3) {
						if (hops < 2) {
							w30 = 0;
						} else {
							w30 = 0;
						}
					} else {
						if (hops < 4) {
							w30 = -256;
						} else {
							w30 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (rel_time < 3270) {
							w30 = 0;
						} else {
							w30 = 0;
						}
					} else {
						if (hops < 4) {
							w30 = 0;
						} else {
							w30 = 0;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 3) {
						if (hops < 2) {
							w30 = 0;
						} else {
							w30 = 0;
						}
					} else {
						w30 = 0;
					}
				} else {
					if (hops < 5) {
						w30 = 0;
					} else {
						w30 = 0;
					}
				}
			}
		}
	}
	int w31;
	if (prod == 4) {
		if (rel_time < 3739) {
			if (rel_time < 3695) {
				if (rel_time < 3651) {
					if (rel_time < 3607) {
						if (rel_time < 2267) {
							w31 = 0;
						} else {
							w31 = 0;
						}
					} else {
						if (hops < 3) {
							w31 = 0;
						} else {
							w31 = -768;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w31 = 256;
						} else {
							w31 = 1024;
						}
					} else {
						if (hops < 4) {
							w31 = 256;
						} else {
							w31 = 0;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w31 = -512;
					} else {
						w31 = -256;
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w31 = -1024;
						} else {
							w31 = -1536;
						}
					} else {
						w31 = -512;
					}
				}
			}
		} else {
			if (rel_time < 4132) {
				if (prod == 2) {
					if (prod == 0) {
						if (rel_time < 3943) {
							w31 = 512;
						} else {
							w31 = 768;
						}
					} else {
						if (hops < 3) {
							w31 = 256;
						} else {
							w31 = 0;
						}
					}
				} else {
					if (rel_time < 3943) {
						if (hops < 2) {
							w31 = -1280;
						} else {
							w31 = -1536;
						}
					} else {
						if (hops < 2) {
							w31 = -256;
						} else {
							w31 = -512;
						}
					}
				}
			} else {
				if (rel_time < 4410) {
					if (prod == 2) {
						if (prod == 0) {
							w31 = -512;
						} else {
							w31 = 0;
						}
					} else {
						if (hops < 2) {
							w31 = 256;
						} else {
							w31 = 512;
						}
					}
				} else {
					if (rel_time < 4686) {
						if (prod == 2) {
							w31 = 512;
						} else {
							w31 = -256;
						}
					} else {
						if (rel_time < 4963) {
							w31 = -256;
						} else {
							w31 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 4132) {
			if (rel_time < 3898) {
				if (hops < 3) {
					if (rel_time < 3739) {
						if (hops < 2) {
							w31 = 256;
						} else {
							w31 = 768;
						}
					} else {
						if (hops < 2) {
							w31 = 0;
						} else {
							w31 = 0;
						}
					}
				} else {
					if (rel_time < 3739) {
						w31 = 256;
					} else {
						if (hops < 4) {
							w31 = -256;
						} else {
							w31 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w31 = -256;
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w31 = -512;
						} else {
							w31 = -512;
						}
					} else {
						if (hops < 5) {
							w31 = -256;
						} else {
							w31 = -256;
						}
					}
				}
			}
		} else {
			if (rel_time < 4410) {
				if (hops < 2) {
					w31 = 256;
				} else {
					if (hops < 4) {
						w31 = 256;
					} else {
						if (hops < 5) {
							w31 = 256;
						} else {
							w31 = 256;
						}
					}
				}
			} else {
				if (rel_time < 5793) {
					if (rel_time < 5517) {
						if (rel_time < 5240) {
							w31 = 0;
						} else {
							w31 = 256;
						}
					} else {
						if (rel_time < 5692) {
							w31 = -1280;
						} else {
							w31 = -256;
						}
					}
				} else {
					if (rel_time < 6069) {
						if (hops < 3) {
							w31 = 512;
						} else {
							w31 = 512;
						}
					} else {
						if (rel_time < 6345) {
							w31 = -512;
						} else {
							w31 = 0;
						}
					}
				}
			}
		}
	}
	int w32;
	if (rel_time < 610) {
		if (rel_time < 539) {
			if (rel_time < 468) {
				if (cons == 1) {
					if (cons == 3) {
						if (rel_time < 397) {
							w32 = 0;
						} else {
							w32 = 0;
						}
					} else {
						if (hops < 3) {
							w32 = 0;
						} else {
							w32 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 2) {
							w32 = 0;
						} else {
							w32 = 0;
						}
					} else {
						if (hops < 5) {
							w32 = 0;
						} else {
							w32 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w32 = 0;
				} else {
					if (hops < 3) {
						w32 = 0;
					} else {
						if (hops < 4) {
							w32 = 0;
						} else {
							w32 = 0;
						}
					}
				}
			}
		} else {
			if (hops < 2) {
				w32 = 0;
			} else {
				if (hops < 4) {
					if (hops < 3) {
						w32 = 0;
					} else {
						w32 = 0;
					}
				} else {
					if (hops < 5) {
						w32 = 0;
					} else {
						w32 = 0;
					}
				}
			}
		}
	} else {
		if (rel_time < 681) {
			if (hops < 4) {
				if (hops < 2) {
					w32 = 0;
				} else {
					if (hops < 3) {
						w32 = 0;
					} else {
						w32 = 0;
					}
				}
			} else {
				if (hops < 5) {
					w32 = 0;
				} else {
					w32 = 0;
				}
			}
		} else {
			if (cons == 2) {
				if (cons == 0) {
					if (rel_time < 927) {
						if (rel_time < 734) {
							w32 = 0;
						} else {
							w32 = 0;
						}
					} else {
						if (rel_time < 2090) {
							w32 = 0;
						} else {
							w32 = 0;
						}
					}
				} else {
					if (rel_time < 2001) {
						if (rel_time < 1824) {
							w32 = 0;
						} else {
							w32 = 512;
						}
					} else {
						if (rel_time < 2149) {
							w32 = -256;
						} else {
							w32 = 0;
						}
					}
				}
			} else {
				if (rel_time < 2797) {
					if (rel_time < 2649) {
						if (rel_time < 1883) {
							w32 = 0;
						} else {
							w32 = 0;
						}
					} else {
						if (hops < 2) {
							w32 = 0;
						} else {
							w32 = -512;
						}
					}
				} else {
					if (rel_time < 2944) {
						if (hops < 5) {
							w32 = 0;
						} else {
							w32 = 0;
						}
					} else {
						if (rel_time < 3063) {
							w32 = 0;
						} else {
							w32 = 0;
						}
					}
				}
			}
		}
	}
	int w33;
	if (rel_time < 7818) {
		if (rel_time < 7742) {
			if (rel_time < 7493) {
				if (rel_time < 7361) {
					if (rel_time < 7314) {
						if (rel_time < 7220) {
							w33 = 0;
						} else {
							w33 = 0;
						}
					} else {
						if (prod == 3) {
							w33 = -768;
						} else {
							w33 = 768;
						}
					}
				} else {
					if (prod == 0) {
						if (hops < 4) {
							w33 = -256;
						} else {
							w33 = -512;
						}
					} else {
						if (hops < 4) {
							w33 = 512;
						} else {
							w33 = 768;
						}
					}
				}
			} else {
				if (prod == 3) {
					if (prod == 1) {
						if (prod == 0) {
							w33 = 512;
						} else {
							w33 = -256;
						}
					} else {
						if (hops < 4) {
							w33 = -256;
						} else {
							w33 = -768;
						}
					}
				} else {
					if (hops < 4) {
						if (rel_time < 7589) {
							w33 = -768;
						} else {
							w33 = -512;
						}
					} else {
						w33 = -1024;
					}
				}
			}
		} else {
			if (prod == 1) {
				if (hops < 4) {
					if (hops < 3) {
						if (hops < 2) {
							w33 = -512;
						} else {
							w33 = -512;
						}
					} else {
						w33 = -512;
					}
				} else {
					w33 = -768;
				}
			} else {
				if (hops < 4) {
					if (hops < 3) {
						w33 = 768;
					} else {
						w33 = 768;
					}
				} else {
					w33 = 1024;
				}
			}
		}
	} else {
		if (rel_time < 7864) {
			if (prod == 2) {
				if (hops < 2) {
					w33 = 768;
				} else {
					w33 = 768;
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w33 = -768;
					} else {
						w33 = -768;
					}
				} else {
					if (hops < 4) {
						w33 = -512;
					} else {
						w33 = -512;
					}
				}
			}
		} else {
			if (prod == 1) {
				if (rel_time < 8139) {
					if (prod == 4) {
						if (rel_time < 7913) {
							w33 = 512;
						} else {
							w33 = 256;
						}
					} else {
						if (hops < 4) {
							w33 = -512;
						} else {
							w33 = -512;
						}
					}
				} else {
					if (rel_time < 8963) {
						if (rel_time < 8842) {
							w33 = 0;
						} else {
							w33 = -512;
						}
					} else {
						if (rel_time < 9219) {
							w33 = 256;
						} else {
							w33 = 0;
						}
					}
				}
			} else {
				if (rel_time < 8092) {
					if (hops < 2) {
						w33 = -768;
					} else {
						if (hops < 4) {
							w33 = -512;
						} else {
							w33 = -768;
						}
					}
				} else {
					if (rel_time < 8415) {
						if (hops < 4) {
							w33 = 256;
						} else {
							w33 = 512;
						}
					} else {
						if (rel_time < 8690) {
							w33 = -512;
						} else {
							w33 = 0;
						}
					}
				}
			}
		}
	}
	int w34;
	if (rel_time < 9014) {
		if (rel_time < 8963) {
			if (rel_time < 8892) {
				if (rel_time < 8739) {
					if (rel_time < 8690) {
						if (rel_time < 8619) {
							w34 = 0;
						} else {
							w34 = 0;
						}
					} else {
						if (prod == 3) {
							w34 = 512;
						} else {
							w34 = -512;
						}
					}
				} else {
					if (prod == 0) {
						if (rel_time < 8842) {
							w34 = 512;
						} else {
							w34 = 768;
						}
					} else {
						if (rel_time < 8842) {
							w34 = -256;
						} else {
							w34 = -256;
						}
					}
				}
			} else {
				if (prod == 1) {
					if (hops < 3) {
						w34 = -256;
					} else {
						if (hops < 5) {
							w34 = -256;
						} else {
							w34 = -256;
						}
					}
				} else {
					w34 = 768;
				}
			}
		} else {
			if (prod == 3) {
				if (hops < 3) {
					w34 = -512;
				} else {
					w34 = -512;
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w34 = 512;
					} else {
						w34 = 512;
					}
				} else {
					w34 = 512;
				}
			}
		}
	} else {
		if (rel_time < 9166) {
			if (prod == 0) {
				if (rel_time < 9118) {
					if (hops < 3) {
						w34 = -256;
					} else {
						w34 = -256;
					}
				} else {
					w34 = -512;
				}
			} else {
				if (rel_time < 9118) {
					if (hops < 2) {
						w34 = 0;
					} else {
						if (hops < 3) {
							w34 = 0;
						} else {
							w34 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 3) {
							w34 = 256;
						} else {
							w34 = 0;
						}
					} else {
						w34 = 256;
					}
				}
			}
		} else {
			if (prod == 2) {
				if (rel_time < 9290) {
					if (prod == 4) {
						if (rel_time < 9219) {
							w34 = -512;
						} else {
							w34 = -512;
						}
					} else {
						w34 = 1024;
					}
				} else {
					if (rel_time < 9564) {
						if (prod == 0) {
							w34 = 256;
						} else {
							w34 = -256;
						}
					} else {
						if (rel_time < 9825) {
							w34 = 0;
						} else {
							w34 = 0;
						}
					}
				}
			} else {
				if (rel_time < 9290) {
					if (rel_time < 9219) {
						if (hops < 3) {
							w34 = 512;
						} else {
							w34 = 512;
						}
					} else {
						w34 = 1280;
					}
				} else {
					if (rel_time < 9564) {
						if (rel_time < 9494) {
							w34 = 0;
						} else {
							w34 = -256;
						}
					} else {
						if (rel_time < 9825) {
							w34 = 0;
						} else {
							w34 = 0;
						}
					}
				}
			}
		}
	}
	int w35;
	if (rel_time < 2267) {
		if (rel_time < 2090) {
			if (rel_time < 2030) {
				if (rel_time < 1824) {
					if (rel_time < 1677) {
						if (rel_time < 1529) {
							w35 = 0;
						} else {
							w35 = 0;
						}
					} else {
						if (cons == 4) {
							w35 = 0;
						} else {
							w35 = 0;
						}
					}
				} else {
					if (cons == 3) {
						if (rel_time < 1854) {
							w35 = 256;
						} else {
							w35 = 0;
						}
					} else {
						if (hops < 4) {
							w35 = 256;
						} else {
							w35 = 512;
						}
					}
				}
			} else {
				if (rel_time < 2059) {
					if (hops < 4) {
						if (hops < 2) {
							w35 = -768;
						} else {
							w35 = -768;
						}
					} else {
						if (hops < 5) {
							w35 = -512;
						} else {
							w35 = -512;
						}
					}
				} else {
					if (hops < 2) {
						w35 = 0;
					} else {
						if (hops < 3) {
							w35 = 0;
						} else {
							w35 = 0;
						}
					}
				}
			}
		} else {
			if (cons == 1) {
				if (cons == 3) {
					if (rel_time < 2149) {
						if (hops < 4) {
							w35 = -256;
						} else {
							w35 = 0;
						}
					} else {
						if (hops < 2) {
							w35 = 0;
						} else {
							w35 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w35 = 512;
					} else {
						if (hops < 4) {
							w35 = 512;
						} else {
							w35 = 512;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						w35 = 768;
					} else {
						w35 = 1024;
					}
				} else {
					w35 = 768;
				}
			}
		}
	} else {
		if (rel_time < 2354) {
			if (cons == 2) {
				if (hops < 2) {
					if (rel_time < 2325) {
						w35 = -512;
					} else {
						w35 = -256;
					}
				} else {
					if (hops < 4) {
						if (rel_time < 2325) {
							w35 = -512;
						} else {
							w35 = -256;
						}
					} else {
						if (rel_time < 2325) {
							w35 = -256;
						} else {
							w35 = -256;
						}
					}
				}
			} else {
				if (hops < 2) {
					w35 = 0;
				} else {
					if (hops < 3) {
						w35 = 0;
					} else {
						if (hops < 5) {
							w35 = 0;
						} else {
							w35 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 2502) {
				if (cons == 0) {
					if (cons == 2) {
						if (rel_time < 2385) {
							w35 = 0;
						} else {
							w35 = 256;
						}
					} else {
						if (hops < 5) {
							w35 = 0;
						} else {
							w35 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w35 = 0;
					} else {
						if (hops < 3) {
							w35 = 0;
						} else {
							w35 = 0;
						}
					}
				}
			} else {
				if (rel_time < 2709) {
					if (cons == 1) {
						if (cons == 3) {
							w35 = 0;
						} else {
							w35 = -256;
						}
					} else {
						if (hops < 3) {
							w35 = -256;
						} else {
							w35 = -256;
						}
					}
				} else {
					if (rel_time < 2797) {
						if (cons == 2) {
							w35 = 256;
						} else {
							w35 = -256;
						}
					} else {
						if (rel_time < 2944) {
							w35 = 0;
						} else {
							w35 = 0;
						}
					}
				}
			}
		}
	}
	int w36;
	if (cons == 4) {
		if (prod == 0) {
			if (rel_time < 10096) {
				if (rel_time < 9825) {
					if (rel_time < 9564) {
						if (rel_time < 8739) {
							w36 = 0;
						} else {
							w36 = 0;
						}
					} else {
						if (prod == 2) {
							w36 = -256;
						} else {
							w36 = 0;
						}
					}
				} else {
					if (prod == 2) {
						if (rel_time < 9944) {
							w36 = 0;
						} else {
							w36 = 256;
						}
					} else {
						if (hops < 3) {
							w36 = -256;
						} else {
							w36 = 0;
						}
					}
				}
			} else {
				if (prod == 2) {
					if (rel_time < 10356) {
						if (prod == 3) {
							w36 = -256;
						} else {
							w36 = 0;
						}
					} else {
						if (prod == 3) {
							w36 = 0;
						} else {
							w36 = 0;
						}
					}
				} else {
					if (rel_time < 10309) {
						if (hops < 2) {
							w36 = 0;
						} else {
							w36 = 0;
						}
					} else {
						if (hops < 2) {
							w36 = 0;
						} else {
							w36 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 5838) {
				if (rel_time < 5562) {
					if (rel_time < 5286) {
						if (rel_time < 5009) {
							w36 = 0;
						} else {
							w36 = 256;
						}
					} else {
						if (hops < 3) {
							w36 = -256;
						} else {
							w36 = -256;
						}
					}
				} else {
					if (hops < 3) {
						w36 = 512;
					} else {
						w36 = 512;
					}
				}
			} else {
				if (rel_time < 6115) {
					if (rel_time < 6069) {
						w36 = -1024;
					} else {
						w36 = -768;
					}
				} else {
					if (rel_time < 6391) {
						if (hops < 3) {
							w36 = 512;
						} else {
							w36 = 512;
						}
					} else {
						if (rel_time < 6666) {
							w36 = -256;
						} else {
							w36 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 2975) {
			if (rel_time < 2827) {
				if (rel_time < 1677) {
					if (rel_time < 1205) {
						if (rel_time < 981) {
							w36 = 0;
						} else {
							w36 = 0;
						}
					} else {
						if (rel_time < 1353) {
							w36 = 0;
						} else {
							w36 = 0;
						}
					}
				} else {
					if (rel_time < 1942) {
						if (rel_time < 1824) {
							w36 = 0;
						} else {
							w36 = 0;
						}
					} else {
						if (rel_time < 2237) {
							w36 = 0;
						} else {
							w36 = 0;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						w36 = 256;
					} else {
						if (hops < 3) {
							w36 = 0;
						} else {
							w36 = 0;
						}
					}
				} else {
					if (hops < 5) {
						w36 = 256;
					} else {
						w36 = 256;
					}
				}
			}
		} else {
			if (rel_time < 3447) {
				if (rel_time < 3122) {
					if (hops < 3) {
						if (hops < 2) {
							w36 = 0;
						} else {
							w36 = 0;
						}
					} else {
						if (hops < 5) {
							w36 = 0;
						} else {
							w36 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (rel_time < 3270) {
							w36 = 0;
						} else {
							w36 = 0;
						}
					} else {
						if (hops < 4) {
							w36 = 0;
						} else {
							w36 = 0;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 3) {
						if (hops < 2) {
							w36 = 0;
						} else {
							w36 = 0;
						}
					} else {
						w36 = 0;
					}
				} else {
					if (hops < 5) {
						w36 = 0;
					} else {
						w36 = 0;
					}
				}
			}
		}
	}
	int w37;
	if (rel_time < 9014) {
		if (rel_time < 8963) {
			if (rel_time < 8892) {
				if (rel_time < 8739) {
					if (rel_time < 8690) {
						if (rel_time < 8415) {
							w37 = 0;
						} else {
							w37 = 0;
						}
					} else {
						if (prod == 3) {
							w37 = 256;
						} else {
							w37 = -512;
						}
					}
				} else {
					if (prod == 0) {
						if (rel_time < 8842) {
							w37 = 256;
						} else {
							w37 = 512;
						}
					} else {
						if (rel_time < 8842) {
							w37 = -256;
						} else {
							w37 = -256;
						}
					}
				}
			} else {
				if (prod == 1) {
					if (hops < 3) {
						w37 = -256;
					} else {
						if (hops < 5) {
							w37 = -256;
						} else {
							w37 = -256;
						}
					}
				} else {
					w37 = 512;
				}
			}
		} else {
			if (prod == 3) {
				if (hops < 3) {
					w37 = -256;
				} else {
					w37 = -256;
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w37 = 256;
					} else {
						w37 = 256;
					}
				} else {
					w37 = 256;
				}
			}
		}
	} else {
		if (rel_time < 9166) {
			if (prod == 0) {
				if (rel_time < 9118) {
					if (hops < 3) {
						w37 = -256;
					} else {
						if (hops < 5) {
							w37 = -256;
						} else {
							w37 = -256;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 2) {
							w37 = -512;
						} else {
							w37 = -256;
						}
					} else {
						w37 = -512;
					}
				}
			} else {
				if (rel_time < 9118) {
					if (hops < 2) {
						w37 = 0;
					} else {
						if (hops < 3) {
							w37 = 0;
						} else {
							w37 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w37 = 0;
					} else {
						if (hops < 3) {
							w37 = 0;
						} else {
							w37 = 0;
						}
					}
				}
			}
		} else {
			if (prod == 2) {
				if (rel_time < 9290) {
					if (prod == 4) {
						if (rel_time < 9219) {
							w37 = -512;
						} else {
							w37 = -256;
						}
					} else {
						w37 = 512;
					}
				} else {
					if (rel_time < 9717) {
						if (prod == 3) {
							w37 = 0;
						} else {
							w37 = 256;
						}
					} else {
						if (rel_time < 9994) {
							w37 = 0;
						} else {
							w37 = 0;
						}
					}
				}
			} else {
				if (rel_time < 9290) {
					if (rel_time < 9219) {
						if (hops < 3) {
							w37 = 256;
						} else {
							w37 = 256;
						}
					} else {
						w37 = 768;
					}
				} else {
					if (rel_time < 9564) {
						if (rel_time < 9494) {
							w37 = 0;
						} else {
							w37 = -256;
						}
					} else {
						if (rel_time < 10096) {
							w37 = 0;
						} else {
							w37 = 0;
						}
					}
				}
			}
		}
	}
	int w38;
	if (rel_time < 6943) {
		if (rel_time < 6666) {
			if (rel_time < 6209) {
				if (rel_time < 6115) {
					if (prod == 3) {
						if (prod == 2) {
							w38 = 0;
						} else {
							w38 = 0;
						}
					} else {
						if (rel_time < 5692) {
							w38 = 0;
						} else {
							w38 = -768;
						}
					}
				} else {
					if (prod == 2) {
						if (rel_time < 6161) {
							w38 = 1024;
						} else {
							w38 = 768;
						}
					} else {
						if (rel_time < 6161) {
							w38 = -768;
						} else {
							w38 = -1024;
						}
					}
				}
			} else {
				if (prod == 1) {
					if (prod == 3) {
						if (rel_time < 6345) {
							w38 = -256;
						} else {
							w38 = 0;
						}
					} else {
						if (rel_time < 6345) {
							w38 = 1024;
						} else {
							w38 = -512;
						}
					}
				} else {
					if (rel_time < 6438) {
						if (rel_time < 6391) {
							w38 = -1280;
						} else {
							w38 = -512;
						}
					} else {
						w38 = 512;
					}
				}
			}
		} else {
			if (prod == 2) {
				if (prod == 4) {
					if (rel_time < 6812) {
						if (rel_time < 6761) {
							w38 = 512;
						} else {
							w38 = 768;
						}
					} else {
						if (prod == 0) {
							w38 = -1024;
						} else {
							w38 = 256;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w38 = -256;
						} else {
							w38 = -256;
						}
					} else {
						if (hops < 5) {
							w38 = -256;
						} else {
							w38 = -256;
						}
					}
				}
			} else {
				if (hops < 5) {
					if (hops < 3) {
						if (hops < 2) {
							w38 = -256;
						} else {
							w38 = -256;
						}
					} else {
						if (hops < 4) {
							w38 = -256;
						} else {
							w38 = -256;
						}
					}
				} else {
					w38 = -256;
				}
			}
		}
	} else {
		if (rel_time < 7037) {
			if (prod == 2) {
				if (rel_time < 6991) {
					if (hops < 5) {
						if (hops < 3) {
							w38 = -512;
						} else {
							w38 = -512;
						}
					} else {
						w38 = -768;
					}
				} else {
					w38 = -768;
				}
			} else {
				if (hops < 4) {
					if (hops < 3) {
						w38 = 256;
					} else {
						w38 = 512;
					}
				} else {
					if (hops < 5) {
						w38 = 256;
					} else {
						w38 = 512;
					}
				}
			}
		} else {
			if (rel_time < 7818) {
				if (prod == 1) {
					if (prod == 4) {
						if (rel_time < 7266) {
							w38 = -512;
						} else {
							w38 = 0;
						}
					} else {
						if (rel_time < 7220) {
							w38 = 512;
						} else {
							w38 = 0;
						}
					}
				} else {
					if (rel_time < 7541) {
						if (rel_time < 7266) {
							w38 = 512;
						} else {
							w38 = -256;
						}
					} else {
						if (hops < 4) {
							w38 = 512;
						} else {
							w38 = 768;
						}
					}
				}
			} else {
				if (rel_time < 7864) {
					if (prod == 2) {
						if (hops < 2) {
							w38 = 512;
						} else {
							w38 = 512;
						}
					} else {
						if (hops < 3) {
							w38 = -512;
						} else {
							w38 = -256;
						}
					}
				} else {
					if (prod == 1) {
						if (rel_time < 8139) {
							w38 = 0;
						} else {
							w38 = 0;
						}
					} else {
						if (rel_time < 8092) {
							w38 = -512;
						} else {
							w38 = 0;
						}
					}
				}
			}
		}
	}
	int w39;
	if (prod == 4) {
		if (rel_time < 8415) {
			if (rel_time < 8139) {
				if (rel_time < 7864) {
					if (rel_time < 7493) {
						if (rel_time < 7314) {
							w39 = 0;
						} else {
							w39 = 256;
						}
					} else {
						if (prod == 3) {
							w39 = 0;
						} else {
							w39 = -256;
						}
					}
				} else {
					if (prod == 1) {
						if (rel_time < 7913) {
							w39 = 256;
						} else {
							w39 = 0;
						}
					} else {
						if (hops < 2) {
							w39 = -256;
						} else {
							w39 = -256;
						}
					}
				}
			} else {
				if (prod == 1) {
					if (rel_time < 8188) {
						if (hops < 4) {
							w39 = -768;
						} else {
							w39 = -768;
						}
					} else {
						if (prod == 3) {
							w39 = -256;
						} else {
							w39 = 1536;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w39 = 256;
						} else {
							w39 = 256;
						}
					} else {
						w39 = 256;
					}
				}
			}
		} else {
			if (rel_time < 8567) {
				if (rel_time < 8465) {
					if (hops < 3) {
						w39 = 768;
					} else {
						w39 = 768;
					}
				} else {
					if (hops < 3) {
						w39 = 256;
					} else {
						w39 = 256;
					}
				}
			} else {
				if (rel_time < 8842) {
					if (prod == 1) {
						if (rel_time < 8690) {
							w39 = 256;
						} else {
							w39 = -256;
						}
					} else {
						if (rel_time < 8619) {
							w39 = -256;
						} else {
							w39 = -512;
						}
					}
				} else {
					if (rel_time < 9118) {
						if (prod == 2) {
							w39 = 0;
						} else {
							w39 = 0;
						}
					} else {
						if (rel_time < 9443) {
							w39 = 0;
						} else {
							w39 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 4132) {
			if (rel_time < 3898) {
				if (hops < 3) {
					if (rel_time < 3739) {
						if (hops < 2) {
							w39 = 256;
						} else {
							w39 = 512;
						}
					} else {
						if (hops < 2) {
							w39 = 0;
						} else {
							w39 = 0;
						}
					}
				} else {
					if (rel_time < 3739) {
						w39 = 256;
					} else {
						if (hops < 4) {
							w39 = -256;
						} else {
							w39 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w39 = -256;
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w39 = -256;
						} else {
							w39 = -256;
						}
					} else {
						if (hops < 5) {
							w39 = -256;
						} else {
							w39 = -256;
						}
					}
				}
			}
		} else {
			if (rel_time < 8292) {
				if (rel_time < 8017) {
					if (rel_time < 7742) {
						if (rel_time < 7493) {
							w39 = 0;
						} else {
							w39 = 256;
						}
					} else {
						if (hops < 4) {
							w39 = -256;
						} else {
							w39 = -512;
						}
					}
				} else {
					if (hops < 4) {
						w39 = 768;
					} else {
						w39 = 768;
					}
				}
			} else {
				if (rel_time < 8567) {
					if (hops < 3) {
						w39 = -768;
					} else {
						w39 = -512;
					}
				} else {
					if (rel_time < 8842) {
						if (hops < 2) {
							w39 = 0;
						} else {
							w39 = 256;
						}
					} else {
						if (rel_time < 9118) {
							w39 = -256;
						} else {
							w39 = 0;
						}
					}
				}
			}
		}
	}
	int w40;
	if (rel_time < 6943) {
		if (rel_time < 6666) {
			if (rel_time < 6621) {
				if (rel_time < 6486) {
					if (rel_time < 6391) {
						if (rel_time < 5966) {
							w40 = 0;
						} else {
							w40 = 0;
						}
					} else {
						if (prod == 2) {
							w40 = -256;
						} else {
							w40 = 256;
						}
					}
				} else {
					if (prod == 4) {
						if (hops < 5) {
							w40 = -256;
						} else {
							w40 = -512;
						}
					} else {
						if (hops < 5) {
							w40 = 256;
						} else {
							w40 = 256;
						}
					}
				}
			} else {
				if (prod == 0) {
					if (hops < 3) {
						w40 = 256;
					} else {
						w40 = 512;
					}
				} else {
					if (hops < 5) {
						if (hops < 3) {
							w40 = -256;
						} else {
							w40 = -256;
						}
					} else {
						w40 = -256;
					}
				}
			}
		} else {
			if (prod == 2) {
				if (prod == 4) {
					if (rel_time < 6812) {
						if (rel_time < 6761) {
							w40 = 256;
						} else {
							w40 = 512;
						}
					} else {
						if (prod == 0) {
							w40 = -512;
						} else {
							w40 = 256;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w40 = -256;
						} else {
							w40 = -256;
						}
					} else {
						if (hops < 5) {
							w40 = 0;
						} else {
							w40 = -256;
						}
					}
				}
			} else {
				if (hops < 5) {
					if (hops < 3) {
						if (hops < 2) {
							w40 = -256;
						} else {
							w40 = -256;
						}
					} else {
						if (hops < 4) {
							w40 = 0;
						} else {
							w40 = -256;
						}
					}
				} else {
					w40 = -256;
				}
			}
		}
	} else {
		if (rel_time < 7037) {
			if (prod == 2) {
				if (rel_time < 6991) {
					if (hops < 5) {
						if (hops < 3) {
							w40 = -256;
						} else {
							w40 = -256;
						}
					} else {
						w40 = -512;
					}
				} else {
					if (hops < 3) {
						w40 = -512;
					} else {
						w40 = -512;
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 3) {
						w40 = 256;
					} else {
						w40 = 256;
					}
				} else {
					if (hops < 5) {
						w40 = 256;
					} else {
						w40 = 256;
					}
				}
			}
		} else {
			if (prod == 1) {
				if (rel_time < 7361) {
					if (prod == 2) {
						if (prod == 0) {
							w40 = 0;
						} else {
							w40 = -256;
						}
					} else {
						if (rel_time < 7266) {
							w40 = 0;
						} else {
							w40 = -512;
						}
					}
				} else {
					if (rel_time < 7589) {
						if (prod == 3) {
							w40 = 256;
						} else {
							w40 = -512;
						}
					} else {
						if (rel_time < 7864) {
							w40 = 0;
						} else {
							w40 = 0;
						}
					}
				}
			} else {
				if (rel_time < 7266) {
					if (rel_time < 7220) {
						w40 = 1024;
					} else {
						if (hops < 4) {
							w40 = 256;
						} else {
							w40 = 256;
						}
					}
				} else {
					if (rel_time < 7541) {
						if (hops < 4) {
							w40 = 0;
						} else {
							w40 = -256;
						}
					} else {
						if (rel_time < 7818) {
							w40 = 256;
						} else {
							w40 = 0;
						}
					}
				}
			}
		}
	}
	int w41;
	if (prod == 4) {
		if (rel_time < 10309) {
			if (rel_time < 8415) {
				if (rel_time < 8139) {
					if (rel_time < 7864) {
						if (rel_time < 7589) {
							w41 = 0;
						} else {
							w41 = 0;
						}
					} else {
						if (prod == 1) {
							w41 = 0;
						} else {
							w41 = 0;
						}
					}
				} else {
					if (prod == 1) {
						if (rel_time < 8188) {
							w41 = -512;
						} else {
							w41 = -256;
						}
					} else {
						if (hops < 4) {
							w41 = 0;
						} else {
							w41 = 256;
						}
					}
				}
			} else {
				if (rel_time < 8567) {
					if (rel_time < 8465) {
						if (hops < 3) {
							w41 = 512;
						} else {
							w41 = 512;
						}
					} else {
						if (hops < 3) {
							w41 = 256;
						} else {
							w41 = 256;
						}
					}
				} else {
					if (rel_time < 8842) {
						if (prod == 1) {
							w41 = 0;
						} else {
							w41 = -256;
						}
					} else {
						if (rel_time < 9014) {
							w41 = 0;
						} else {
							w41 = 0;
						}
					}
				}
			}
		} else {
			if (prod == 2) {
				if (rel_time < 10356) {
					if (hops < 2) {
						w41 = 0;
					} else {
						if (hops < 4) {
							w41 = 0;
						} else {
							w41 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w41 = 0;
					} else {
						if (hops < 4) {
							w41 = 0;
						} else {
							w41 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w41 = 0;
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w41 = 0;
						} else {
							w41 = 0;
						}
					} else {
						if (hops < 5) {
							w41 = 0;
						} else {
							w41 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 4132) {
			if (rel_time < 3898) {
				if (rel_time < 3739) {
					if (hops < 2) {
						w41 = 0;
					} else {
						if (hops < 3) {
							w41 = 256;
						} else {
							w41 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w41 = 0;
						} else {
							w41 = 0;
						}
					} else {
						if (hops < 4) {
							w41 = 0;
						} else {
							w41 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w41 = 0;
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w41 = -256;
						} else {
							w41 = -256;
						}
					} else {
						if (hops < 5) {
							w41 = 0;
						} else {
							w41 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 4410) {
				if (hops < 2) {
					w41 = 0;
				} else {
					if (hops < 4) {
						w41 = 0;
					} else {
						if (hops < 5) {
							w41 = 0;
						} else {
							w41 = 0;
						}
					}
				}
			} else {
				if (rel_time < 4686) {
					if (rel_time < 4586) {
						if (hops < 3) {
							w41 = 0;
						} else {
							w41 = 0;
						}
					} else {
						if (hops < 3) {
							w41 = -256;
						} else {
							w41 = 0;
						}
					}
				} else {
					if (rel_time < 4963) {
						if (rel_time < 4863) {
							w41 = 256;
						} else {
							w41 = 256;
						}
					} else {
						if (rel_time < 5240) {
							w41 = -256;
						} else {
							w41 = 0;
						}
					}
				}
			}
		}
	}
	int w42;
	if (hops < 2) {
		if (rel_time < 1029) {
			if (rel_time < 879) {
				if (rel_time < 681) {
					if (rel_time < 182) {
						if (rel_time < 68) {
							w42 = 0;
						} else {
							w42 = 0;
						}
					} else {
						if (rel_time < 539) {
							w42 = 0;
						} else {
							w42 = 0;
						}
					}
				} else {
					if (cons == 0) {
						if (cons == 1) {
							w42 = 0;
						} else {
							w42 = 0;
						}
					} else {
						w42 = 0;
					}
				}
			} else {
				if (rel_time < 981) {
					if (rel_time < 927) {
						w42 = 0;
					} else {
						w42 = 0;
					}
				} else {
					w42 = 0;
				}
			}
		} else {
			if (rel_time < 1234) {
				if (cons == 3) {
					if (rel_time < 1078) {
						w42 = 0;
					} else {
						if (rel_time < 1205) {
							w42 = 0;
						} else {
							w42 = 0;
						}
					}
				} else {
					w42 = -512;
				}
			} else {
				if (cons == 1) {
					if (rel_time < 1293) {
						w42 = 0;
					} else {
						if (rel_time < 2030) {
							w42 = 0;
						} else {
							w42 = 0;
						}
					}
				} else {
					if (rel_time < 2149) {
						if (rel_time < 2001) {
							w42 = 0;
						} else {
							w42 = 512;
						}
					} else {
						if (rel_time < 2325) {
							w42 = -256;
						} else {
							w42 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 5692) {
			if (rel_time < 5610) {
				if (prod == 3) {
					if (rel_time < 4772) {
						if (rel_time < 4496) {
							w42 = 0;
						} else {
							w42 = 0;
						}
					} else {
						if (rel_time < 4817) {
							w42 = 512;
						} else {
							w42 = 0;
						}
					}
				} else {
					if (rel_time < 5139) {
						if (rel_time < 4863) {
							w42 = 0;
						} else {
							w42 = 768;
						}
					} else {
						w42 = -512;
					}
				}
			} else {
				if (prod == 3) {
					if (prod == 2) {
						w42 = -768;
					} else {
						w42 = -256;
					}
				} else {
					if (hops < 3) {
						w42 = 512;
					} else {
						if (hops < 4) {
							w42 = 768;
						} else {
							w42 = 512;
						}
					}
				}
			}
		} else {
			if (rel_time < 5966) {
				if (prod == 2) {
					if (prod == 0) {
						if (rel_time < 5793) {
							w42 = -256;
						} else {
							w42 = -768;
						}
					} else {
						if (hops < 3) {
							w42 = 256;
						} else {
							w42 = 256;
						}
					}
				} else {
					if (hops < 3) {
						w42 = 512;
					} else {
						w42 = 512;
					}
				}
			} else {
				if (rel_time < 6069) {
					if (prod == 0) {
						if (hops < 3) {
							w42 = 256;
						} else {
							w42 = 256;
						}
					} else {
						w42 = -768;
					}
				} else {
					if (prod == 1) {
						if (rel_time < 6161) {
							w42 = -512;
						} else {
							w42 = 0;
						}
					} else {
						if (rel_time < 6161) {
							w42 = 768;
						} else {
							w42 = 0;
						}
					}
				}
			}
		}
	}
	int w43;
	if (prod == 1) {
		if (rel_time < 4817) {
			if (rel_time < 4541) {
				if (rel_time < 4264) {
					if (rel_time < 3987) {
						if (prod == 3) {
							w43 = 0;
						} else {
							w43 = -256;
						}
					} else {
						if (prod == 4) {
							w43 = 256;
						} else {
							w43 = 0;
						}
					}
				} else {
					if (prod == 4) {
						if (rel_time < 4496) {
							w43 = -256;
						} else {
							w43 = 0;
						}
					} else {
						if (rel_time < 4309) {
							w43 = 0;
						} else {
							w43 = 0;
						}
					}
				}
			} else {
				if (prod == 4) {
					if (prod == 3) {
						if (hops < 3) {
							w43 = 512;
						} else {
							w43 = 256;
						}
					} else {
						if (rel_time < 4586) {
							w43 = 256;
						} else {
							w43 = -512;
						}
					}
				} else {
					if (hops < 3) {
						if (rel_time < 4586) {
							w43 = 0;
						} else {
							w43 = 0;
						}
					} else {
						if (rel_time < 4586) {
							w43 = 0;
						} else {
							w43 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 5094) {
				if (prod == 4) {
					if (rel_time < 4863) {
						if (hops < 2) {
							w43 = -512;
						} else {
							w43 = -512;
						}
					} else {
						if (prod == 3) {
							w43 = -256;
						} else {
							w43 = 768;
						}
					}
				} else {
					if (rel_time < 4863) {
						if (hops < 3) {
							w43 = 256;
						} else {
							w43 = 0;
						}
					} else {
						if (hops < 3) {
							w43 = 0;
						} else {
							w43 = 0;
						}
					}
				}
			} else {
				if (rel_time < 5334) {
					if (prod == 4) {
						if (rel_time < 5139) {
							w43 = 512;
						} else {
							w43 = 256;
						}
					} else {
						if (hops < 3) {
							w43 = -256;
						} else {
							w43 = 0;
						}
					}
				} else {
					if (rel_time < 5610) {
						if (prod == 4) {
							w43 = -256;
						} else {
							w43 = 0;
						}
					} else {
						if (rel_time < 5885) {
							w43 = 256;
						} else {
							w43 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 3651) {
			if (hops < 3) {
				if (hops < 2) {
					w43 = -256;
				} else {
					w43 = 0;
				}
			} else {
				if (hops < 5) {
					if (hops < 4) {
						w43 = -512;
					} else {
						w43 = -768;
					}
				} else {
					w43 = 0;
				}
			}
		} else {
			if (rel_time < 3943) {
				if (hops < 3) {
					if (hops < 2) {
						w43 = 256;
					} else {
						w43 = 256;
					}
				} else {
					if (hops < 4) {
						w43 = 512;
					} else {
						if (hops < 5) {
							w43 = 512;
						} else {
							w43 = 256;
						}
					}
				}
			} else {
				if (rel_time < 4219) {
					if (hops < 2) {
						w43 = 0;
					} else {
						if (hops < 5) {
							w43 = -512;
						} else {
							w43 = -256;
						}
					}
				} else {
					if (rel_time < 4496) {
						if (hops < 3) {
							w43 = 256;
						} else {
							w43 = 512;
						}
					} else {
						if (rel_time < 4772) {
							w43 = -512;
						} else {
							w43 = 0;
						}
					}
				}
			}
		}
	}
	int w44;
	if (hops < 5) {
		if (rel_time < 610) {
			if (rel_time < 539) {
				if (rel_time < 468) {
					if (cons == 4) {
						if (hops < 2) {
							w44 = 0;
						} else {
							w44 = 0;
						}
					} else {
						if (hops < 2) {
							w44 = 0;
						} else {
							w44 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w44 = 0;
					} else {
						if (hops < 3) {
							w44 = 0;
						} else {
							w44 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w44 = 0;
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w44 = 0;
						} else {
							w44 = 0;
						}
					} else {
						w44 = 0;
					}
				}
			}
		} else {
			if (rel_time < 782) {
				if (cons == 4) {
					if (hops < 2) {
						if (rel_time < 681) {
							w44 = 0;
						} else {
							w44 = 0;
						}
					} else {
						if (hops < 4) {
							w44 = 0;
						} else {
							w44 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w44 = 0;
					} else {
						if (hops < 4) {
							w44 = 0;
						} else {
							w44 = 0;
						}
					}
				}
			} else {
				if (rel_time < 831) {
					if (hops < 2) {
						w44 = 0;
					} else {
						if (hops < 3) {
							w44 = 0;
						} else {
							w44 = 0;
						}
					}
				} else {
					if (cons == 1) {
						if (rel_time < 879) {
							w44 = 0;
						} else {
							w44 = 0;
						}
					} else {
						if (rel_time < 2001) {
							w44 = 0;
						} else {
							w44 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 782) {
			if (rel_time < 734) {
				if (rel_time < 468) {
					if (cons == 1) {
						if (rel_time < 397) {
							w44 = 0;
						} else {
							w44 = 0;
						}
					} else {
						w44 = 0;
					}
				} else {
					if (rel_time < 539) {
						w44 = 0;
					} else {
						if (rel_time < 610) {
							w44 = 0;
						} else {
							w44 = 0;
						}
					}
				}
			} else {
				w44 = 0;
			}
		} else {
			if (rel_time < 3943) {
				if (rel_time < 3004) {
					if (rel_time < 2857) {
						if (rel_time < 2709) {
							w44 = 0;
						} else {
							w44 = 0;
						}
					} else {
						if (rel_time < 2886) {
							w44 = -512;
						} else {
							w44 = 0;
						}
					}
				} else {
					if (rel_time < 3033) {
						w44 = 512;
					} else {
						if (prod == 3) {
							w44 = 0;
						} else {
							w44 = 0;
						}
					}
				}
			} else {
				if (rel_time < 3987) {
					w44 = -256;
				} else {
					if (rel_time < 4032) {
						w44 = 256;
					} else {
						if (rel_time < 8567) {
							w44 = 0;
						} else {
							w44 = 0;
						}
					}
				}
			}
		}
	}
	int w45;
	if (rel_time < 5692) {
		if (rel_time < 5517) {
			if (rel_time < 5139) {
				if (rel_time < 4963) {
					if (rel_time < 4817) {
						if (rel_time < 4772) {
							w45 = 0;
						} else {
							w45 = 256;
						}
					} else {
						if (prod == 4) {
							w45 = -256;
						} else {
							w45 = 0;
						}
					}
				} else {
					if (prod == 1) {
						if (prod == 3) {
							w45 = -256;
						} else {
							w45 = 256;
						}
					} else {
						w45 = 768;
					}
				}
			} else {
				if (prod == 1) {
					if (prod == 3) {
						if (prod == 2) {
							w45 = 0;
						} else {
							w45 = 256;
						}
					} else {
						if (hops < 2) {
							w45 = -512;
						} else {
							w45 = -256;
						}
					}
				} else {
					if (hops < 3) {
						w45 = -512;
					} else {
						w45 = -512;
					}
				}
			}
		} else {
			if (prod == 1) {
				if (prod == 3) {
					if (prod == 4) {
						if (rel_time < 5562) {
							w45 = 0;
						} else {
							w45 = -256;
						}
					} else {
						if (hops < 2) {
							w45 = -768;
						} else {
							w45 = -512;
						}
					}
				} else {
					if (hops < 2) {
						w45 = 512;
					} else {
						if (hops < 3) {
							w45 = 256;
						} else {
							w45 = 256;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w45 = 768;
					} else {
						w45 = 512;
					}
				} else {
					if (hops < 4) {
						w45 = 768;
					} else {
						w45 = 512;
					}
				}
			}
		}
	} else {
		if (rel_time < 5966) {
			if (prod == 2) {
				if (prod == 0) {
					if (prod == 1) {
						if (rel_time < 5793) {
							w45 = -256;
						} else {
							w45 = -512;
						}
					} else {
						if (hops < 2) {
							w45 = -768;
						} else {
							w45 = -512;
						}
					}
				} else {
					if (hops < 2) {
						w45 = 256;
					} else {
						if (hops < 3) {
							w45 = 256;
						} else {
							w45 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					if (rel_time < 5885) {
						w45 = 512;
					} else {
						w45 = 512;
					}
				} else {
					if (rel_time < 5885) {
						if (hops < 3) {
							w45 = 256;
						} else {
							w45 = 256;
						}
					} else {
						if (hops < 3) {
							w45 = 256;
						} else {
							w45 = 256;
						}
					}
				}
			}
		} else {
			if (rel_time < 6209) {
				if (prod == 2) {
					if (prod == 0) {
						if (rel_time < 6069) {
							w45 = 256;
						} else {
							w45 = 512;
						}
					} else {
						if (hops < 2) {
							w45 = -512;
						} else {
							w45 = -256;
						}
					}
				} else {
					if (rel_time < 6161) {
						if (hops < 2) {
							w45 = -512;
						} else {
							w45 = -256;
						}
					} else {
						if (hops < 5) {
							w45 = -512;
						} else {
							w45 = -512;
						}
					}
				}
			} else {
				if (rel_time < 6486) {
					if (prod == 1) {
						if (prod == 4) {
							w45 = 0;
						} else {
							w45 = -256;
						}
					} else {
						if (rel_time < 6391) {
							w45 = -1024;
						} else {
							w45 = -256;
						}
					}
				} else {
					if (rel_time < 6943) {
						if (prod == 2) {
							w45 = 0;
						} else {
							w45 = 0;
						}
					} else {
						if (rel_time < 7037) {
							w45 = 0;
						} else {
							w45 = 0;
						}
					}
				}
			}
		}
	}
	int w46;
	if (rel_time < 2267) {
		if (rel_time < 2090) {
			if (rel_time < 2030) {
				if (rel_time < 1942) {
					if (rel_time < 1883) {
						if (rel_time < 1854) {
							w46 = 0;
						} else {
							w46 = 0;
						}
					} else {
						if (rel_time < 1912) {
							w46 = 256;
						} else {
							w46 = 0;
						}
					}
				} else {
					if (cons == 1) {
						if (rel_time < 2001) {
							w46 = 256;
						} else {
							w46 = 0;
						}
					} else {
						if (hops < 2) {
							w46 = -512;
						} else {
							w46 = -768;
						}
					}
				}
			} else {
				if (rel_time < 2059) {
					if (hops < 4) {
						if (hops < 3) {
							w46 = -512;
						} else {
							w46 = -512;
						}
					} else {
						if (hops < 5) {
							w46 = -256;
						} else {
							w46 = -256;
						}
					}
				} else {
					if (hops < 2) {
						w46 = 0;
					} else {
						if (hops < 5) {
							w46 = 0;
						} else {
							w46 = 0;
						}
					}
				}
			}
		} else {
			if (cons == 1) {
				if (cons == 3) {
					if (rel_time < 2149) {
						if (hops < 4) {
							w46 = -256;
						} else {
							w46 = 0;
						}
					} else {
						if (hops < 2) {
							w46 = 0;
						} else {
							w46 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w46 = 256;
					} else {
						if (hops < 4) {
							w46 = 512;
						} else {
							w46 = 256;
						}
					}
				}
			} else {
				if (hops < 2) {
					w46 = 256;
				} else {
					if (hops < 4) {
						w46 = 512;
					} else {
						w46 = 512;
					}
				}
			}
		}
	} else {
		if (rel_time < 2354) {
			if (cons == 2) {
				if (hops < 4) {
					if (rel_time < 2325) {
						if (hops < 2) {
							w46 = -256;
						} else {
							w46 = -256;
						}
					} else {
						if (hops < 2) {
							w46 = -256;
						} else {
							w46 = -256;
						}
					}
				} else {
					if (rel_time < 2325) {
						w46 = 0;
					} else {
						if (hops < 5) {
							w46 = -256;
						} else {
							w46 = -256;
						}
					}
				}
			} else {
				if (hops < 2) {
					w46 = 0;
				} else {
					if (hops < 3) {
						w46 = 0;
					} else {
						if (hops < 5) {
							w46 = 0;
						} else {
							w46 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 2562) {
				if (cons == 1) {
					if (cons == 3) {
						if (rel_time < 2532) {
							w46 = 0;
						} else {
							w46 = 0;
						}
					} else {
						if (hops < 2) {
							w46 = 256;
						} else {
							w46 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w46 = 256;
					} else {
						if (hops < 3) {
							w46 = 0;
						} else {
							w46 = 256;
						}
					}
				}
			} else {
				if (rel_time < 2709) {
					if (rel_time < 2591) {
						if (hops < 4) {
							w46 = -256;
						} else {
							w46 = -256;
						}
					} else {
						if (cons == 3) {
							w46 = 0;
						} else {
							w46 = 0;
						}
					}
				} else {
					if (rel_time < 2797) {
						if (cons == 2) {
							w46 = 256;
						} else {
							w46 = 0;
						}
					} else {
						if (rel_time < 2944) {
							w46 = 0;
						} else {
							w46 = 0;
						}
					}
				}
			}
		}
	}
	int w47;
	if (prod == 4) {
		if (rel_time < 10264) {
			if (rel_time < 10042) {
				if (rel_time < 9768) {
					if (rel_time < 9494) {
						if (rel_time < 9219) {
							w47 = 0;
						} else {
							w47 = 0;
						}
					} else {
						if (prod == 1) {
							w47 = 0;
						} else {
							w47 = 0;
						}
					}
				} else {
					if (prod == 1) {
						if (rel_time < 9825) {
							w47 = 0;
						} else {
							w47 = -256;
						}
					} else {
						if (hops < 2) {
							w47 = 256;
						} else {
							w47 = 0;
						}
					}
				}
			} else {
				if (prod == 1) {
					if (prod == 2) {
						if (rel_time < 10096) {
							w47 = 0;
						} else {
							w47 = 256;
						}
					} else {
						if (hops < 2) {
							w47 = 0;
						} else {
							w47 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w47 = -512;
					} else {
						w47 = -256;
					}
				}
			}
		} else {
			if (prod == 2) {
				if (hops < 2) {
					if (rel_time < 10309) {
						w47 = 0;
					} else {
						if (rel_time < 10356) {
							w47 = 0;
						} else {
							w47 = 0;
						}
					}
				} else {
					if (rel_time < 10356) {
						if (hops < 4) {
							w47 = 0;
						} else {
							w47 = 0;
						}
					} else {
						if (hops < 4) {
							w47 = 0;
						} else {
							w47 = 0;
						}
					}
				}
			} else {
				if (rel_time < 10309) {
					if (hops < 3) {
						if (hops < 2) {
							w47 = 0;
						} else {
							w47 = 0;
						}
					} else {
						w47 = 0;
					}
				} else {
					if (hops < 2) {
						w47 = 0;
					} else {
						if (hops < 4) {
							w47 = 0;
						} else {
							w47 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 8292) {
			if (rel_time < 8017) {
				if (rel_time < 7742) {
					if (rel_time < 7493) {
						if (rel_time < 7220) {
							w47 = 0;
						} else {
							w47 = -512;
						}
					} else {
						if (hops < 4) {
							w47 = 256;
						} else {
							w47 = 512;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w47 = -256;
						} else {
							w47 = 0;
						}
					} else {
						w47 = -256;
					}
				}
			} else {
				if (hops < 4) {
					w47 = 512;
				} else {
					w47 = 512;
				}
			}
		} else {
			if (rel_time < 8567) {
				if (hops < 3) {
					w47 = -512;
				} else {
					if (hops < 5) {
						w47 = -256;
					} else {
						w47 = -512;
					}
				}
			} else {
				if (rel_time < 8842) {
					if (hops < 2) {
						if (rel_time < 8739) {
							w47 = 0;
						} else {
							w47 = 0;
						}
					} else {
						if (hops < 4) {
							w47 = 0;
						} else {
							w47 = 0;
						}
					}
				} else {
					if (rel_time < 9667) {
						if (rel_time < 9393) {
							w47 = 0;
						} else {
							w47 = -256;
						}
					} else {
						if (rel_time < 9944) {
							w47 = 0;
						} else {
							w47 = 0;
						}
					}
				}
			}
		}
	}
	int w48;
	if (rel_time < 10356) {
		if (prod == 4) {
			if (rel_time < 8415) {
				if (rel_time < 8139) {
					if (rel_time < 7220) {
						if (rel_time < 7037) {
							w48 = 0;
						} else {
							w48 = -256;
						}
					} else {
						if (rel_time < 7493) {
							w48 = 0;
						} else {
							w48 = 0;
						}
					}
				} else {
					if (prod == 1) {
						if (rel_time < 8188) {
							w48 = -256;
						} else {
							w48 = 0;
						}
					} else {
						if (hops < 3) {
							w48 = 0;
						} else {
							w48 = 0;
						}
					}
				}
			} else {
				if (rel_time < 8567) {
					if (rel_time < 8465) {
						if (hops < 3) {
							w48 = 256;
						} else {
							w48 = 256;
						}
					} else {
						if (hops < 2) {
							w48 = 0;
						} else {
							w48 = 0;
						}
					}
				} else {
					if (rel_time < 8963) {
						if (prod == 3) {
							w48 = 0;
						} else {
							w48 = -256;
						}
					} else {
						if (rel_time < 9014) {
							w48 = 0;
						} else {
							w48 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 8292) {
				if (rel_time < 8017) {
					if (rel_time < 7742) {
						if (rel_time < 7493) {
							w48 = 0;
						} else {
							w48 = 0;
						}
					} else {
						if (hops < 4) {
							w48 = 0;
						} else {
							w48 = -256;
						}
					}
				} else {
					if (hops < 4) {
						w48 = 256;
					} else {
						w48 = 256;
					}
				}
			} else {
				if (rel_time < 8567) {
					if (hops < 3) {
						if (hops < 2) {
							w48 = -256;
						} else {
							w48 = -256;
						}
					} else {
						if (hops < 5) {
							w48 = -256;
						} else {
							w48 = -256;
						}
					}
				} else {
					if (rel_time < 8842) {
						if (hops < 2) {
							w48 = 0;
						} else {
							w48 = 0;
						}
					} else {
						if (rel_time < 9118) {
							w48 = 0;
						} else {
							w48 = 0;
						}
					}
				}
			}
		}
	} else {
		if (prod == 3) {
			if (hops < 3) {
				if (hops < 2) {
					w48 = 0;
				} else {
					if (rel_time < 10415) {
						w48 = 0;
					} else {
						w48 = 0;
					}
				}
			} else {
				if (hops < 4) {
					w48 = 0;
				} else {
					if (hops < 5) {
						w48 = 0;
					} else {
						w48 = 0;
					}
				}
			}
		} else {
			if (hops < 2) {
				w48 = 0;
			} else {
				if (hops < 5) {
					if (hops < 4) {
						if (hops < 3) {
							w48 = 0;
						} else {
							w48 = 0;
						}
					} else {
						w48 = 0;
					}
				} else {
					w48 = 0;
				}
			}
		}
	}
	int w49;
	if (hops < 5) {
		if (rel_time < 10356) {
			if (rel_time < 10264) {
				if (rel_time < 10217) {
					if (rel_time < 10096) {
						if (rel_time < 10042) {
							w49 = 0;
						} else {
							w49 = 0;
						}
					} else {
						if (prod == 4) {
							w49 = 256;
						} else {
							w49 = 0;
						}
					}
				} else {
					if (prod == 0) {
						if (hops < 2) {
							w49 = -256;
						} else {
							w49 = 0;
						}
					} else {
						if (hops < 2) {
							w49 = 0;
						} else {
							w49 = 0;
						}
					}
				}
			} else {
				if (prod == 2) {
					if (hops < 2) {
						if (rel_time < 10309) {
							w49 = 0;
						} else {
							w49 = 0;
						}
					} else {
						if (hops < 4) {
							w49 = 0;
						} else {
							w49 = 0;
						}
					}
				} else {
					if (rel_time < 10309) {
						if (hops < 3) {
							w49 = 0;
						} else {
							w49 = 0;
						}
					} else {
						if (hops < 2) {
							w49 = 0;
						} else {
							w49 = 0;
						}
					}
				}
			}
		} else {
			if (prod == 3) {
				if (hops < 3) {
					if (hops < 2) {
						w49 = 0;
					} else {
						if (rel_time < 10415) {
							w49 = 0;
						} else {
							w49 = 0;
						}
					}
				} else {
					if (hops < 4) {
						w49 = 0;
					} else {
						w49 = 0;
					}
				}
			} else {
				if (hops < 2) {
					w49 = 0;
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w49 = 0;
						} else {
							w49 = 0;
						}
					} else {
						w49 = 0;
					}
				}
			}
		}
	} else {
		if (rel_time < 782) {
			if (rel_time < 734) {
				if (rel_time < 468) {
					if (cons == 1) {
						if (rel_time < 397) {
							w49 = 0;
						} else {
							w49 = 0;
						}
					} else {
						w49 = 0;
					}
				} else {
					if (rel_time < 539) {
						w49 = 0;
					} else {
						if (rel_time < 610) {
							w49 = 0;
						} else {
							w49 = 0;
						}
					}
				}
			} else {
				w49 = 0;
			}
		} else {
			if (rel_time < 4264) {
				if (prod == 0) {
					if (rel_time < 4219) {
						if (rel_time < 4132) {
							w49 = 0;
						} else {
							w49 = -256;
						}
					} else {
						w49 = 256;
					}
				} else {
					if (rel_time < 3898) {
						w49 = 0;
					} else {
						w49 = 256;
					}
				}
			} else {
				if (rel_time < 4309) {
					w49 = -256;
				} else {
					if (rel_time < 4586) {
						if (prod == 2) {
							w49 = 0;
						} else {
							w49 = 0;
						}
					} else {
						if (rel_time < 4863) {
							w49 = 0;
						} else {
							w49 = 0;
						}
					}
				}
			}
		}
	}
	int w50;
	if (rel_time < 5692) {
		if (rel_time < 5517) {
			if (rel_time < 5139) {
				if (rel_time < 4963) {
					if (rel_time < 4817) {
						if (rel_time < 4772) {
							w50 = 0;
						} else {
							w50 = 0;
						}
					} else {
						if (prod == 3) {
							w50 = 0;
						} else {
							w50 = -256;
						}
					}
				} else {
					if (prod == 1) {
						if (prod == 3) {
							w50 = 0;
						} else {
							w50 = 256;
						}
					} else {
						if (hops < 3) {
							w50 = 512;
						} else {
							w50 = 512;
						}
					}
				}
			} else {
				if (prod == 1) {
					if (prod == 3) {
						if (rel_time < 5240) {
							w50 = 0;
						} else {
							w50 = 0;
						}
					} else {
						if (hops < 2) {
							w50 = -256;
						} else {
							w50 = 0;
						}
					}
				} else {
					if (hops < 3) {
						w50 = -256;
					} else {
						if (hops < 5) {
							w50 = -256;
						} else {
							w50 = -256;
						}
					}
				}
			}
		} else {
			if (prod == 1) {
				if (prod == 3) {
					if (prod == 4) {
						if (rel_time < 5562) {
							w50 = 0;
						} else {
							w50 = 0;
						}
					} else {
						if (hops < 2) {
							w50 = -512;
						} else {
							w50 = -256;
						}
					}
				} else {
					if (hops < 2) {
						w50 = 256;
					} else {
						if (hops < 3) {
							w50 = 256;
						} else {
							w50 = 256;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w50 = 512;
					} else {
						w50 = 256;
					}
				} else {
					if (hops < 4) {
						w50 = 512;
					} else {
						w50 = 512;
					}
				}
			}
		}
	} else {
		if (rel_time < 5966) {
			if (prod == 2) {
				if (prod == 0) {
					if (prod == 1) {
						if (hops < 2) {
							w50 = -256;
						} else {
							w50 = 0;
						}
					} else {
						if (hops < 2) {
							w50 = -512;
						} else {
							w50 = -256;
						}
					}
				} else {
					if (hops < 2) {
						w50 = 256;
					} else {
						if (hops < 3) {
							w50 = 0;
						} else {
							w50 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					if (rel_time < 5885) {
						w50 = 256;
					} else {
						w50 = 256;
					}
				} else {
					if (rel_time < 5885) {
						if (hops < 3) {
							w50 = 256;
						} else {
							w50 = 256;
						}
					} else {
						if (hops < 3) {
							w50 = 256;
						} else {
							w50 = 256;
						}
					}
				}
			}
		} else {
			if (rel_time < 6209) {
				if (prod == 2) {
					if (prod == 0) {
						if (rel_time < 6069) {
							w50 = 0;
						} else {
							w50 = 256;
						}
					} else {
						if (hops < 2) {
							w50 = -256;
						} else {
							w50 = -256;
						}
					}
				} else {
					if (rel_time < 6161) {
						if (hops < 2) {
							w50 = -256;
						} else {
							w50 = -256;
						}
					} else {
						if (hops < 2) {
							w50 = -256;
						} else {
							w50 = -512;
						}
					}
				}
			} else {
				if (rel_time < 6666) {
					if (prod == 1) {
						if (rel_time < 6621) {
							w50 = 0;
						} else {
							w50 = -256;
						}
					} else {
						if (rel_time < 6391) {
							w50 = -512;
						} else {
							w50 = 0;
						}
					}
				} else {
					if (rel_time < 6761) {
						if (prod == 2) {
							w50 = 256;
						} else {
							w50 = 0;
						}
					} else {
						if (rel_time < 7037) {
							w50 = 0;
						} else {
							w50 = 0;
						}
					}
				}
			}
		}
	}
	int w51;
	if (prod == 0) {
		if (rel_time < 3152) {
			if (rel_time < 3004) {
				if (rel_time < 2857) {
					if (rel_time < 2709) {
						if (rel_time < 2562) {
							w51 = 0;
						} else {
							w51 = 0;
						}
					} else {
						if (cons == 3) {
							w51 = 0;
						} else {
							w51 = 256;
						}
					}
				} else {
					if (rel_time < 2886) {
						if (hops < 5) {
							w51 = -256;
						} else {
							w51 = -256;
						}
					} else {
						if (cons == 3) {
							w51 = 0;
						} else {
							w51 = -256;
						}
					}
				}
			} else {
				if (rel_time < 3033) {
					if (hops < 2) {
						w51 = 0;
					} else {
						if (hops < 3) {
							w51 = 512;
						} else {
							w51 = 256;
						}
					}
				} else {
					if (cons == 3) {
						if (rel_time < 3122) {
							w51 = 0;
						} else {
							w51 = 0;
						}
					} else {
						if (hops < 3) {
							w51 = 256;
						} else {
							w51 = 256;
						}
					}
				}
			}
		} else {
			if (rel_time < 3299) {
				if (cons == 3) {
					if (rel_time < 3181) {
						if (hops < 3) {
							w51 = -256;
						} else {
							w51 = 0;
						}
					} else {
						if (rel_time < 3270) {
							w51 = 0;
						} else {
							w51 = 0;
						}
					}
				} else {
					if (hops < 3) {
						w51 = -256;
					} else {
						if (hops < 5) {
							w51 = 0;
						} else {
							w51 = -256;
						}
					}
				}
			} else {
				if (rel_time < 3387) {
					if (cons == 2) {
						if (hops < 2) {
							w51 = 256;
						} else {
							w51 = 0;
						}
					} else {
						if (hops < 4) {
							w51 = 0;
						} else {
							w51 = 0;
						}
					}
				} else {
					if (cons == 1) {
						if (rel_time < 3695) {
							w51 = 0;
						} else {
							w51 = 0;
						}
					} else {
						if (hops < 5) {
							w51 = 0;
						} else {
							w51 = -256;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 5286) {
			if (rel_time < 4496) {
				if (rel_time < 4219) {
					if (hops < 2) {
						if (rel_time < 3898) {
							w51 = 0;
						} else {
							w51 = 0;
						}
					} else {
						if (rel_time < 3607) {
							w51 = 0;
						} else {
							w51 = 0;
						}
					}
				} else {
					if (rel_time < 4410) {
						if (hops < 3) {
							w51 = 0;
						} else {
							w51 = 0;
						}
					} else {
						if (hops < 2) {
							w51 = -256;
						} else {
							w51 = -256;
						}
					}
				}
			} else {
				if (rel_time < 4772) {
					if (hops < 2) {
						if (rel_time < 4686) {
							w51 = 256;
						} else {
							w51 = 256;
						}
					} else {
						if (rel_time < 4686) {
							w51 = 256;
						} else {
							w51 = 256;
						}
					}
				} else {
					if (rel_time < 5009) {
						if (hops < 3) {
							w51 = 0;
						} else {
							w51 = 0;
						}
					} else {
						if (rel_time < 5240) {
							w51 = 0;
						} else {
							w51 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 6115) {
				if (rel_time < 5838) {
					if (rel_time < 5562) {
						if (rel_time < 5517) {
							w51 = 0;
						} else {
							w51 = 0;
						}
					} else {
						if (hops < 2) {
							w51 = 0;
						} else {
							w51 = 0;
						}
					}
				} else {
					if (hops < 2) {
						if (rel_time < 6069) {
							w51 = -256;
						} else {
							w51 = -256;
						}
					} else {
						if (rel_time < 6069) {
							w51 = -256;
						} else {
							w51 = 0;
						}
					}
				}
			} else {
				if (rel_time < 6391) {
					if (rel_time < 6345) {
						w51 = 256;
					} else {
						if (hops < 2) {
							w51 = 0;
						} else {
							w51 = 256;
						}
					}
				} else {
					if (rel_time < 6666) {
						if (hops < 5) {
							w51 = 0;
						} else {
							w51 = -256;
						}
					} else {
						if (rel_time < 6943) {
							w51 = 0;
						} else {
							w51 = 0;
						}
					}
				}
			}
		}
	}
	int w52;
	if (prod == 0) {
		if (rel_time < 10096) {
			if (rel_time < 9825) {
				if (rel_time < 9564) {
					if (rel_time < 9290) {
						if (rel_time < 9014) {
							w52 = 0;
						} else {
							w52 = 0;
						}
					} else {
						if (prod == 2) {
							w52 = 0;
						} else {
							w52 = 0;
						}
					}
				} else {
					if (prod == 2) {
						if (rel_time < 9717) {
							w52 = 0;
						} else {
							w52 = 0;
						}
					} else {
						if (hops < 2) {
							w52 = 0;
						} else {
							w52 = 0;
						}
					}
				}
			} else {
				if (prod == 2) {
					if (hops < 2) {
						if (prod == 3) {
							w52 = 0;
						} else {
							w52 = 0;
						}
					} else {
						if (rel_time < 9944) {
							w52 = 0;
						} else {
							w52 = 0;
						}
					}
				} else {
					if (rel_time < 10042) {
						if (hops < 3) {
							w52 = 0;
						} else {
							w52 = 0;
						}
					} else {
						if (hops < 3) {
							w52 = 0;
						} else {
							w52 = 0;
						}
					}
				}
			}
		} else {
			if (prod == 1) {
				if (rel_time < 10356) {
					if (prod == 4) {
						if (rel_time < 10217) {
							w52 = 256;
						} else {
							w52 = 0;
						}
					} else {
						if (hops < 3) {
							w52 = 0;
						} else {
							w52 = 0;
						}
					}
				} else {
					if (prod == 3) {
						if (hops < 2) {
							w52 = 0;
						} else {
							w52 = 0;
						}
					} else {
						if (hops < 2) {
							w52 = 0;
						} else {
							w52 = 0;
						}
					}
				}
			} else {
				if (rel_time < 10264) {
					if (hops < 2) {
						w52 = -256;
					} else {
						w52 = 0;
					}
				} else {
					if (hops < 2) {
						w52 = 0;
					} else {
						if (hops < 4) {
							w52 = 0;
						} else {
							w52 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 8619) {
			if (rel_time < 8567) {
				if (rel_time < 8346) {
					if (rel_time < 8092) {
						if (rel_time < 7818) {
							w52 = 0;
						} else {
							w52 = 0;
						}
					} else {
						if (hops < 4) {
							w52 = 0;
						} else {
							w52 = -256;
						}
					}
				} else {
					if (hops < 3) {
						w52 = 0;
					} else {
						if (hops < 4) {
							w52 = 0;
						} else {
							w52 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w52 = 256;
				} else {
					w52 = 512;
				}
			}
		} else {
			if (rel_time < 9443) {
				if (rel_time < 9166) {
					if (rel_time < 8892) {
						if (rel_time < 8842) {
							w52 = 0;
						} else {
							w52 = -256;
						}
					} else {
						if (rel_time < 9118) {
							w52 = 0;
						} else {
							w52 = 0;
						}
					}
				} else {
					if (hops < 2) {
						if (rel_time < 9393) {
							w52 = 0;
						} else {
							w52 = 0;
						}
					} else {
						if (hops < 3) {
							w52 = -256;
						} else {
							w52 = 0;
						}
					}
				}
			} else {
				if (rel_time < 9717) {
					if (rel_time < 9667) {
						if (hops < 3) {
							w52 = 512;
						} else {
							w52 = 256;
						}
					} else {
						if (hops < 3) {
							w52 = 256;
						} else {
							w52 = 256;
						}
					}
				} else {
					if (rel_time < 9994) {
						if (hops < 2) {
							w52 = -256;
						} else {
							w52 = 0;
						}
					} else {
						if (rel_time < 10217) {
							w52 = 0;
						} else {
							w52 = 0;
						}
					}
				}
			}
		}
	}
	int w53;
	if (cons == 4) {
		if (rel_time < 3987) {
			if (rel_time < 3943) {
				if (prod == 3) {
					if (rel_time < 3651) {
						if (rel_time < 3607) {
							w53 = 0;
						} else {
							w53 = 0;
						}
					} else {
						if (prod == 4) {
							w53 = 0;
						} else {
							w53 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w53 = -256;
						} else {
							w53 = 0;
						}
					} else {
						if (hops < 5) {
							w53 = -512;
						} else {
							w53 = 0;
						}
					}
				}
			} else {
				if (prod == 2) {
					w53 = 1024;
				} else {
					if (hops < 2) {
						w53 = -256;
					} else {
						if (hops < 4) {
							w53 = -512;
						} else {
							w53 = -256;
						}
					}
				}
			}
		} else {
			if (rel_time < 4032) {
				if (prod == 3) {
					if (hops < 2) {
						w53 = 0;
					} else {
						if (hops < 3) {
							w53 = 0;
						} else {
							w53 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 3) {
							w53 = 512;
						} else {
							w53 = 512;
						}
					} else {
						w53 = 0;
					}
				}
			} else {
				if (rel_time < 4410) {
					if (prod == 3) {
						if (prod == 1) {
							w53 = 0;
						} else {
							w53 = -256;
						}
					} else {
						if (rel_time < 4264) {
							w53 = -768;
						} else {
							w53 = -256;
						}
					}
				} else {
					if (rel_time < 4496) {
						if (prod == 1) {
							w53 = 0;
						} else {
							w53 = 256;
						}
					} else {
						if (rel_time < 4541) {
							w53 = 0;
						} else {
							w53 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 2975) {
			if (rel_time < 2827) {
				if (rel_time < 2237) {
					if (rel_time < 1205) {
						if (rel_time < 981) {
							w53 = 0;
						} else {
							w53 = 0;
						}
					} else {
						if (rel_time < 1529) {
							w53 = 0;
						} else {
							w53 = 0;
						}
					}
				} else {
					if (rel_time < 2385) {
						if (hops < 2) {
							w53 = 0;
						} else {
							w53 = 0;
						}
					} else {
						if (rel_time < 2532) {
							w53 = 0;
						} else {
							w53 = 0;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						w53 = 0;
					} else {
						if (hops < 3) {
							w53 = 0;
						} else {
							w53 = 0;
						}
					}
				} else {
					w53 = 0;
				}
			}
		} else {
			if (rel_time < 3447) {
				if (rel_time < 3270) {
					if (rel_time < 3122) {
						if (hops < 3) {
							w53 = 0;
						} else {
							w53 = 0;
						}
					} else {
						if (hops < 4) {
							w53 = 0;
						} else {
							w53 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w53 = 0;
						} else {
							w53 = 0;
						}
					} else {
						if (hops < 5) {
							w53 = 0;
						} else {
							w53 = 0;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 3) {
						if (hops < 2) {
							w53 = 0;
						} else {
							w53 = 0;
						}
					} else {
						w53 = 0;
					}
				} else {
					if (hops < 5) {
						w53 = 0;
					} else {
						w53 = 0;
					}
				}
			}
		}
	}
	int w54;
	if (rel_time < 318) {
		if (rel_time < 244) {
			if (cons == 1) {
				if (hops < 4) {
					if (hops < 3) {
						if (hops < 2) {
							w54 = 0;
						} else {
							w54 = 0;
						}
					} else {
						if (rel_time < 68) {
							w54 = 0;
						} else {
							w54 = 0;
						}
					}
				} else {
					if (rel_time < 68) {
						if (hops < 5) {
							w54 = 0;
						} else {
							w54 = 0;
						}
					} else {
						if (hops < 5) {
							w54 = 0;
						} else {
							w54 = 0;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						w54 = 0;
					} else {
						if (hops < 3) {
							w54 = 0;
						} else {
							w54 = 0;
						}
					}
				} else {
					if (hops < 5) {
						w54 = 0;
					} else {
						w54 = 0;
					}
				}
			}
		} else {
			if (hops < 3) {
				if (hops < 2) {
					w54 = 0;
				} else {
					w54 = 0;
				}
			} else {
				if (hops < 5) {
					if (hops < 4) {
						w54 = 0;
					} else {
						w54 = 0;
					}
				} else {
					w54 = 0;
				}
			}
		}
	} else {
		if (rel_time < 2090) {
			if (rel_time < 2030) {
				if (rel_time < 1824) {
					if (rel_time < 1677) {
						if (rel_time < 1529) {
							w54 = 0;
						} else {
							w54 = 0;
						}
					} else {
						if (cons == 3) {
							w54 = 0;
						} else {
							w54 = -256;
						}
					}
				} else {
					if (rel_time < 1854) {
						if (hops < 3) {
							w54 = 256;
						} else {
							w54 = 256;
						}
					} else {
						if (cons == 1) {
							w54 = 0;
						} else {
							w54 = -256;
						}
					}
				}
			} else {
				if (rel_time < 2059) {
					if (hops < 4) {
						if (hops < 2) {
							w54 = -256;
						} else {
							w54 = -256;
						}
					} else {
						if (hops < 5) {
							w54 = -256;
						} else {
							w54 = -256;
						}
					}
				} else {
					if (hops < 2) {
						w54 = 0;
					} else {
						if (hops < 5) {
							w54 = 0;
						} else {
							w54 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 2207) {
				if (cons == 0) {
					if (cons == 2) {
						if (hops < 2) {
							w54 = 256;
						} else {
							w54 = 256;
						}
					} else {
						if (hops < 2) {
							w54 = 0;
						} else {
							w54 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 2) {
							w54 = 0;
						} else {
							w54 = 0;
						}
					} else {
						if (hops < 5) {
							w54 = 0;
						} else {
							w54 = 0;
						}
					}
				}
			} else {
				if (rel_time < 2354) {
					if (rel_time < 2267) {
						if (rel_time < 2237) {
							w54 = 0;
						} else {
							w54 = 0;
						}
					} else {
						if (cons == 2) {
							w54 = 0;
						} else {
							w54 = 0;
						}
					}
				} else {
					if (rel_time < 2562) {
						if (cons == 1) {
							w54 = 0;
						} else {
							w54 = 0;
						}
					} else {
						if (rel_time < 2591) {
							w54 = 0;
						} else {
							w54 = 0;
						}
					}
				}
			}
		}
	}
	int w55;
	if (rel_time < 1382) {
		if (rel_time < 1234) {
			if (rel_time < 1126) {
				if (rel_time < 1078) {
					if (rel_time < 1029) {
						if (rel_time < 879) {
							w55 = 0;
						} else {
							w55 = 0;
						}
					} else {
						if (hops < 4) {
							w55 = 0;
						} else {
							w55 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w55 = 0;
						} else {
							w55 = 0;
						}
					} else {
						if (hops < 5) {
							w55 = 256;
						} else {
							w55 = 512;
						}
					}
				}
			} else {
				if (cons == 4) {
					if (rel_time < 1205) {
						if (hops < 3) {
							w55 = -256;
						} else {
							w55 = 0;
						}
					} else {
						if (hops < 2) {
							w55 = 0;
						} else {
							w55 = -256;
						}
					}
				} else {
					if (hops < 2) {
						w55 = 0;
					} else {
						if (hops < 4) {
							w55 = 0;
						} else {
							w55 = 0;
						}
					}
				}
			}
		} else {
			if (cons == 4) {
				if (cons == 2) {
					if (cons == 3) {
						if (hops < 2) {
							w55 = 0;
						} else {
							w55 = 0;
						}
					} else {
						if (hops < 2) {
							w55 = 0;
						} else {
							w55 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w55 = 0;
						} else {
							w55 = 0;
						}
					} else {
						if (hops < 5) {
							w55 = 0;
						} else {
							w55 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w55 = 0;
				} else {
					if (hops < 3) {
						w55 = 0;
					} else {
						if (hops < 4) {
							w55 = 0;
						} else {
							w55 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 1529) {
			if (cons == 2) {
				if (rel_time < 1469) {
					if (hops < 2) {
						if (rel_time < 1411) {
							w55 = 0;
						} else {
							w55 = 0;
						}
					} else {
						if (hops < 3) {
							w55 = 0;
						} else {
							w55 = -256;
						}
					}
				} else {
					if (cons == 0) {
						if (hops < 3) {
							w55 = 0;
						} else {
							w55 = 0;
						}
					} else {
						if (hops < 5) {
							w55 = 0;
						} else {
							w55 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w55 = 0;
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w55 = 0;
						} else {
							w55 = 0;
						}
					} else {
						if (hops < 5) {
							w55 = 0;
						} else {
							w55 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 1559) {
				if (hops < 4) {
					if (hops < 3) {
						w55 = 0;
					} else {
						w55 = 256;
					}
				} else {
					if (hops < 5) {
						w55 = 0;
					} else {
						w55 = 0;
					}
				}
			} else {
				if (rel_time < 1588) {
					if (hops < 4) {
						if (hops < 2) {
							w55 = 0;
						} else {
							w55 = 0;
						}
					} else {
						if (hops < 5) {
							w55 = 0;
						} else {
							w55 = 0;
						}
					}
				} else {
					if (rel_time < 1617) {
						if (hops < 2) {
							w55 = 0;
						} else {
							w55 = 256;
						}
					} else {
						if (rel_time < 1824) {
							w55 = 0;
						} else {
							w55 = 0;
						}
					}
				}
			}
		}
	}
	int w56;
	if (rel_time < 610) {
		if (rel_time < 539) {
			if (rel_time < 468) {
				if (cons == 4) {
					if (hops < 2) {
						if (cons == 2) {
							w56 = 0;
						} else {
							w56 = 0;
						}
					} else {
						if (rel_time < 68) {
							w56 = 0;
						} else {
							w56 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w56 = 0;
					} else {
						if (hops < 3) {
							w56 = 0;
						} else {
							w56 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w56 = 0;
				} else {
					if (hops < 3) {
						w56 = 0;
					} else {
						if (hops < 4) {
							w56 = 0;
						} else {
							w56 = 0;
						}
					}
				}
			}
		} else {
			if (hops < 2) {
				w56 = 0;
			} else {
				if (hops < 4) {
					if (hops < 3) {
						w56 = 0;
					} else {
						w56 = 0;
					}
				} else {
					if (hops < 5) {
						w56 = 0;
					} else {
						w56 = 0;
					}
				}
			}
		}
	} else {
		if (rel_time < 782) {
			if (cons == 4) {
				if (hops < 2) {
					if (rel_time < 681) {
						w56 = 0;
					} else {
						w56 = 0;
					}
				} else {
					if (hops < 3) {
						if (rel_time < 681) {
							w56 = 0;
						} else {
							w56 = 0;
						}
					} else {
						if (hops < 4) {
							w56 = 0;
						} else {
							w56 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w56 = 0;
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w56 = 0;
						} else {
							w56 = 0;
						}
					} else {
						w56 = 0;
					}
				}
			}
		} else {
			if (rel_time < 831) {
				if (hops < 2) {
					w56 = 0;
				} else {
					if (hops < 3) {
						if (cons == 1) {
							w56 = -256;
						} else {
							w56 = 0;
						}
					} else {
						if (hops < 4) {
							w56 = 0;
						} else {
							w56 = 0;
						}
					}
				}
			} else {
				if (rel_time < 879) {
					if (hops < 3) {
						if (hops < 2) {
							w56 = 0;
						} else {
							w56 = 0;
						}
					} else {
						if (hops < 4) {
							w56 = 0;
						} else {
							w56 = 0;
						}
					}
				} else {
					if (rel_time < 1126) {
						if (rel_time < 1078) {
							w56 = 0;
						} else {
							w56 = 0;
						}
					} else {
						if (rel_time < 1234) {
							w56 = 0;
						} else {
							w56 = 0;
						}
					}
				}
			}
		}
	}
	int w57;
	if (rel_time < 3152) {
		if (rel_time < 3004) {
			if (rel_time < 2975) {
				if (rel_time < 2857) {
					if (rel_time < 2709) {
						if (rel_time < 2562) {
							w57 = 0;
						} else {
							w57 = 0;
						}
					} else {
						if (cons == 2) {
							w57 = 0;
						} else {
							w57 = 0;
						}
					}
				} else {
					if (cons == 2) {
						if (rel_time < 2944) {
							w57 = -256;
						} else {
							w57 = 0;
						}
					} else {
						if (hops < 4) {
							w57 = 0;
						} else {
							w57 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w57 = 0;
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w57 = -256;
						} else {
							w57 = 0;
						}
					} else {
						if (hops < 5) {
							w57 = 0;
						} else {
							w57 = 0;
						}
					}
				}
			}
		} else {
			if (cons == 2) {
				if (cons == 4) {
					if (rel_time < 3122) {
						if (hops < 2) {
							w57 = 0;
						} else {
							w57 = 256;
						}
					} else {
						if (hops < 2) {
							w57 = 0;
						} else {
							w57 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w57 = 0;
						} else {
							w57 = 0;
						}
					} else {
						if (hops < 4) {
							w57 = 0;
						} else {
							w57 = 0;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w57 = 0;
					} else {
						w57 = 0;
					}
				} else {
					if (hops < 4) {
						w57 = 0;
					} else {
						if (hops < 5) {
							w57 = 0;
						} else {
							w57 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 3299) {
			if (cons == 3) {
				if (rel_time < 3181) {
					if (hops < 3) {
						if (hops < 2) {
							w57 = 0;
						} else {
							w57 = -256;
						}
					} else {
						if (hops < 4) {
							w57 = 0;
						} else {
							w57 = 0;
						}
					}
				} else {
					if (rel_time < 3270) {
						if (hops < 3) {
							w57 = 0;
						} else {
							w57 = 0;
						}
					} else {
						if (hops < 3) {
							w57 = 0;
						} else {
							w57 = 0;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w57 = 0;
					} else {
						w57 = 0;
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w57 = 0;
						} else {
							w57 = 0;
						}
					} else {
						w57 = -256;
					}
				}
			}
		} else {
			if (rel_time < 3387) {
				if (cons == 2) {
					if (hops < 2) {
						w57 = 0;
					} else {
						if (hops < 5) {
							w57 = 0;
						} else {
							w57 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w57 = 0;
						} else {
							w57 = 0;
						}
					} else {
						if (hops < 4) {
							w57 = 0;
						} else {
							w57 = 0;
						}
					}
				}
			} else {
				if (cons == 1) {
					if (cons == 2) {
						if (rel_time < 3651) {
							w57 = 0;
						} else {
							w57 = 0;
						}
					} else {
						if (hops < 4) {
							w57 = 0;
						} else {
							w57 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w57 = 0;
						} else {
							w57 = 0;
						}
					} else {
						if (hops < 5) {
							w57 = 0;
						} else {
							w57 = 0;
						}
					}
				}
			}
		}
	}
	int w58;
	if (hops < 5) {
		if (rel_time < 5692) {
			if (rel_time < 5517) {
				if (rel_time < 5139) {
					if (rel_time < 4963) {
						if (rel_time < 4686) {
							w58 = 0;
						} else {
							w58 = 0;
						}
					} else {
						if (prod == 2) {
							w58 = 0;
						} else {
							w58 = -256;
						}
					}
				} else {
					if (prod == 1) {
						if (prod == 3) {
							w58 = 0;
						} else {
							w58 = 0;
						}
					} else {
						if (hops < 3) {
							w58 = -256;
						} else {
							w58 = -256;
						}
					}
				}
			} else {
				if (prod == 1) {
					if (prod == 3) {
						if (prod == 4) {
							w58 = 0;
						} else {
							w58 = -256;
						}
					} else {
						if (hops < 2) {
							w58 = 256;
						} else {
							w58 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w58 = 256;
						} else {
							w58 = 256;
						}
					} else {
						if (hops < 4) {
							w58 = 256;
						} else {
							w58 = 256;
						}
					}
				}
			}
		} else {
			if (rel_time < 5966) {
				if (prod == 2) {
					if (prod == 0) {
						if (rel_time < 5793) {
							w58 = 0;
						} else {
							w58 = -256;
						}
					} else {
						if (hops < 2) {
							w58 = 0;
						} else {
							w58 = 0;
						}
					}
				} else {
					if (hops < 2) {
						if (rel_time < 5885) {
							w58 = 256;
						} else {
							w58 = 256;
						}
					} else {
						if (rel_time < 5885) {
							w58 = 0;
						} else {
							w58 = 0;
						}
					}
				}
			} else {
				if (rel_time < 6209) {
					if (prod == 2) {
						if (prod == 0) {
							w58 = 256;
						} else {
							w58 = 0;
						}
					} else {
						if (rel_time < 6161) {
							w58 = -256;
						} else {
							w58 = -256;
						}
					}
				} else {
					if (rel_time < 6486) {
						if (prod == 0) {
							w58 = 0;
						} else {
							w58 = 0;
						}
					} else {
						if (rel_time < 6761) {
							w58 = 0;
						} else {
							w58 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 782) {
			if (rel_time < 734) {
				if (cons == 0) {
					if (rel_time < 182) {
						w58 = 0;
					} else {
						if (cons == 1) {
							w58 = 0;
						} else {
							w58 = 0;
						}
					}
				} else {
					if (rel_time < 68) {
						w58 = 0;
					} else {
						w58 = 0;
					}
				}
			} else {
				w58 = 0;
			}
		} else {
			if (rel_time < 6943) {
				if (rel_time < 6666) {
					if (rel_time < 6391) {
						if (rel_time < 6209) {
							w58 = 0;
						} else {
							w58 = 0;
						}
					} else {
						if (prod == 3) {
							w58 = 0;
						} else {
							w58 = -512;
						}
					}
				} else {
					if (prod == 4) {
						if (prod == 2) {
							w58 = 256;
						} else {
							w58 = 0;
						}
					} else {
						w58 = 0;
					}
				}
			} else {
				if (rel_time < 6991) {
					w58 = -256;
				} else {
					if (rel_time < 7037) {
						w58 = 256;
					} else {
						if (rel_time < 7087) {
							w58 = -256;
						} else {
							w58 = 0;
						}
					}
				}
			}
		}
	}
	int w59;
	if (prod == 2) {
		if (rel_time < 9014) {
			if (rel_time < 8842) {
				if (rel_time < 8465) {
					if (rel_time < 8346) {
						if (rel_time < 8017) {
							w59 = 0;
						} else {
							w59 = 0;
						}
					} else {
						if (prod == 4) {
							w59 = 256;
						} else {
							w59 = -256;
						}
					}
				} else {
					if (prod == 0) {
						if (rel_time < 8739) {
							w59 = 0;
						} else {
							w59 = 0;
						}
					} else {
						if (rel_time < 8619) {
							w59 = 0;
						} else {
							w59 = 0;
						}
					}
				}
			} else {
				if (prod == 0) {
					if (prod == 4) {
						if (rel_time < 8963) {
							w59 = 256;
						} else {
							w59 = 0;
						}
					} else {
						if (hops < 3) {
							w59 = 0;
						} else {
							w59 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w59 = 0;
						} else {
							w59 = 0;
						}
					} else {
						if (hops < 4) {
							w59 = 0;
						} else {
							w59 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 9290) {
				if (prod == 0) {
					if (prod == 4) {
						if (rel_time < 9219) {
							w59 = -256;
						} else {
							w59 = 0;
						}
					} else {
						if (rel_time < 9118) {
							w59 = 0;
						} else {
							w59 = 512;
						}
					}
				} else {
					if (rel_time < 9118) {
						if (hops < 2) {
							w59 = 0;
						} else {
							w59 = 0;
						}
					} else {
						if (hops < 3) {
							w59 = 0;
						} else {
							w59 = 0;
						}
					}
				}
			} else {
				if (rel_time < 9717) {
					if (prod == 4) {
						if (rel_time < 9443) {
							w59 = 0;
						} else {
							w59 = 0;
						}
					} else {
						if (rel_time < 9393) {
							w59 = 0;
						} else {
							w59 = 0;
						}
					}
				} else {
					if (rel_time < 9825) {
						if (hops < 2) {
							w59 = 0;
						} else {
							w59 = 0;
						}
					} else {
						if (prod == 0) {
							w59 = 0;
						} else {
							w59 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 3695) {
			if (hops < 3) {
				if (hops < 2) {
					w59 = 0;
				} else {
					w59 = 512;
				}
			} else {
				if (hops < 4) {
					w59 = 0;
				} else {
					if (hops < 5) {
						w59 = 0;
					} else {
						w59 = 0;
					}
				}
			}
		} else {
			if (rel_time < 3987) {
				if (rel_time < 3943) {
					if (hops < 2) {
						w59 = -768;
					} else {
						if (hops < 3) {
							w59 = -1280;
						} else {
							w59 = -768;
						}
					}
				} else {
					if (hops < 2) {
						w59 = 0;
					} else {
						if (hops < 4) {
							w59 = -256;
						} else {
							w59 = -256;
						}
					}
				}
			} else {
				if (rel_time < 4264) {
					if (hops < 2) {
						if (rel_time < 4219) {
							w59 = 256;
						} else {
							w59 = 0;
						}
					} else {
						if (hops < 5) {
							w59 = 256;
						} else {
							w59 = 0;
						}
					}
				} else {
					if (rel_time < 4541) {
						if (hops < 3) {
							w59 = -256;
						} else {
							w59 = 0;
						}
					} else {
						if (rel_time < 4817) {
							w59 = 0;
						} else {
							w59 = 0;
						}
					}
				}
			}
		}
	}
	int w60;
	if (rel_time < 7742) {
		if (rel_time < 7589) {
			if (rel_time < 7541) {
				if (rel_time < 7493) {
					if (prod == 4) {
						if (rel_time < 7314) {
							w60 = 0;
						} else {
							w60 = 0;
						}
					} else {
						if (rel_time < 7220) {
							w60 = 0;
						} else {
							w60 = -256;
						}
					}
				} else {
					if (prod == 1) {
						w60 = 512;
					} else {
						if (hops < 4) {
							w60 = 0;
						} else {
							w60 = -256;
						}
					}
				}
			} else {
				if (prod == 2) {
					if (hops < 4) {
						if (hops < 3) {
							w60 = -256;
						} else {
							w60 = -256;
						}
					} else {
						w60 = -512;
					}
				} else {
					if (hops < 4) {
						if (hops < 2) {
							w60 = 0;
						} else {
							w60 = 256;
						}
					} else {
						w60 = 256;
					}
				}
			}
		} else {
			if (prod == 4) {
				if (hops < 4) {
					if (rel_time < 7636) {
						if (hops < 3) {
							w60 = -256;
						} else {
							w60 = -256;
						}
					} else {
						if (hops < 3) {
							w60 = 0;
						} else {
							w60 = 0;
						}
					}
				} else {
					if (rel_time < 7636) {
						w60 = -512;
					} else {
						w60 = -256;
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						w60 = 0;
					} else {
						if (hops < 3) {
							w60 = 0;
						} else {
							w60 = 0;
						}
					}
				} else {
					w60 = 256;
				}
			}
		}
	} else {
		if (rel_time < 7818) {
			if (prod == 1) {
				if (hops < 4) {
					if (hops < 3) {
						if (hops < 2) {
							w60 = -256;
						} else {
							w60 = -256;
						}
					} else {
						w60 = -256;
					}
				} else {
					w60 = -256;
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						w60 = 256;
					} else {
						if (hops < 3) {
							w60 = 256;
						} else {
							w60 = 256;
						}
					}
				} else {
					w60 = 256;
				}
			}
		} else {
			if (rel_time < 7864) {
				if (prod == 2) {
					if (hops < 2) {
						w60 = 512;
					} else {
						w60 = 512;
					}
				} else {
					if (hops < 4) {
						if (hops < 2) {
							w60 = -256;
						} else {
							w60 = -256;
						}
					} else {
						w60 = 0;
					}
				}
			} else {
				if (prod == 2) {
					if (rel_time < 8188) {
						if (rel_time < 8017) {
							w60 = 0;
						} else {
							w60 = 0;
						}
					} else {
						if (rel_time < 8465) {
							w60 = 0;
						} else {
							w60 = 0;
						}
					}
				} else {
					if (rel_time < 8139) {
						if (hops < 2) {
							w60 = 256;
						} else {
							w60 = 0;
						}
					} else {
						if (rel_time < 8415) {
							w60 = 0;
						} else {
							w60 = 0;
						}
					}
				}
			}
		}
	}
	int w61;
	if (rel_time < 9166) {
		if (rel_time < 8892) {
			if (rel_time < 8842) {
				if (rel_time < 4686) {
					if (rel_time < 4410) {
						if (rel_time < 4264) {
							w61 = 0;
						} else {
							w61 = 0;
						}
					} else {
						if (prod == 3) {
							w61 = 0;
						} else {
							w61 = 256;
						}
					}
				} else {
					if (rel_time < 4772) {
						if (prod == 1) {
							w61 = 256;
						} else {
							w61 = -256;
						}
					} else {
						if (rel_time < 4817) {
							w61 = 0;
						} else {
							w61 = 0;
						}
					}
				}
			} else {
				if (prod == 0) {
					if (hops < 3) {
						if (hops < 2) {
							w61 = 0;
						} else {
							w61 = 0;
						}
					} else {
						if (hops < 4) {
							w61 = 256;
						} else {
							w61 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w61 = 0;
						} else {
							w61 = 0;
						}
					} else {
						if (hops < 5) {
							w61 = 0;
						} else {
							w61 = 0;
						}
					}
				}
			}
		} else {
			if (prod == 2) {
				if (rel_time < 9014) {
					if (prod == 4) {
						if (rel_time < 8963) {
							w61 = 0;
						} else {
							w61 = 0;
						}
					} else {
						if (hops < 3) {
							w61 = 0;
						} else {
							w61 = 0;
						}
					}
				} else {
					if (prod == 1) {
						if (prod == 0) {
							w61 = 0;
						} else {
							w61 = 0;
						}
					} else {
						if (hops < 4) {
							w61 = 0;
						} else {
							w61 = 0;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w61 = 0;
					} else {
						w61 = 0;
					}
				} else {
					if (hops < 5) {
						w61 = 0;
					} else {
						w61 = 0;
					}
				}
			}
		}
	} else {
		if (rel_time < 9219) {
			if (prod == 1) {
				if (hops < 3) {
					if (hops < 2) {
						w61 = 256;
					} else {
						w61 = 256;
					}
				} else {
					w61 = 256;
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						w61 = 0;
					} else {
						w61 = 0;
					}
				} else {
					w61 = 0;
				}
			}
		} else {
			if (prod == 1) {
				if (rel_time < 9564) {
					if (prod == 0) {
						if (prod == 3) {
							w61 = 0;
						} else {
							w61 = 0;
						}
					} else {
						if (hops < 2) {
							w61 = 0;
						} else {
							w61 = 0;
						}
					}
				} else {
					if (rel_time < 9944) {
						if (prod == 0) {
							w61 = 0;
						} else {
							w61 = 0;
						}
					} else {
						if (rel_time < 9994) {
							w61 = 0;
						} else {
							w61 = 0;
						}
					}
				}
			} else {
				if (rel_time < 9494) {
					if (rel_time < 9443) {
						if (hops < 2) {
							w61 = 256;
						} else {
							w61 = 0;
						}
					} else {
						if (hops < 3) {
							w61 = 0;
						} else {
							w61 = 0;
						}
					}
				} else {
					if (rel_time < 9768) {
						if (rel_time < 9717) {
							w61 = 0;
						} else {
							w61 = 0;
						}
					} else {
						if (rel_time < 10042) {
							w61 = 0;
						} else {
							w61 = 0;
						}
					}
				}
			}
		}
	}
	int w62;
	if (prod == 3) {
		if (rel_time < 8092) {
			if (rel_time < 7818) {
				if (rel_time < 7541) {
					if (rel_time < 7266) {
						if (rel_time < 6991) {
							w62 = 0;
						} else {
							w62 = 0;
						}
					} else {
						if (rel_time < 7361) {
							w62 = -256;
						} else {
							w62 = 0;
						}
					}
				} else {
					if (prod == 0) {
						if (hops < 4) {
							w62 = 0;
						} else {
							w62 = 256;
						}
					} else {
						if (hops < 4) {
							w62 = 0;
						} else {
							w62 = -256;
						}
					}
				}
			} else {
				if (prod == 0) {
					if (rel_time < 7864) {
						if (hops < 3) {
							w62 = -256;
						} else {
							w62 = 0;
						}
					} else {
						if (hops < 4) {
							w62 = 0;
						} else {
							w62 = 0;
						}
					}
				} else {
					if (rel_time < 8017) {
						if (hops < 2) {
							w62 = 0;
						} else {
							w62 = 0;
						}
					} else {
						if (hops < 2) {
							w62 = 256;
						} else {
							w62 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 8188) {
				if (rel_time < 8139) {
					if (hops < 4) {
						if (hops < 2) {
							w62 = 0;
						} else {
							w62 = 0;
						}
					} else {
						w62 = 256;
					}
				} else {
					if (hops < 2) {
						w62 = 256;
					} else {
						w62 = 256;
					}
				}
			} else {
				if (rel_time < 8567) {
					if (rel_time < 8346) {
						if (prod == 0) {
							w62 = 0;
						} else {
							w62 = 0;
						}
					} else {
						if (prod == 0) {
							w62 = 0;
						} else {
							w62 = 0;
						}
					}
				} else {
					if (rel_time < 8892) {
						if (prod == 1) {
							w62 = 0;
						} else {
							w62 = 0;
						}
					} else {
						if (rel_time < 9166) {
							w62 = 0;
						} else {
							w62 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 3739) {
			if (hops < 3) {
				if (hops < 2) {
					w62 = 0;
				} else {
					w62 = 0;
				}
			} else {
				if (hops < 5) {
					if (hops < 4) {
						w62 = -256;
					} else {
						w62 = -512;
					}
				} else {
					w62 = 0;
				}
			}
		} else {
			if (rel_time < 4032) {
				if (rel_time < 3987) {
					w62 = 768;
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w62 = 256;
						} else {
							w62 = 512;
						}
					} else {
						w62 = 0;
					}
				}
			} else {
				if (rel_time < 4309) {
					if (rel_time < 4264) {
						if (hops < 2) {
							w62 = -512;
						} else {
							w62 = -256;
						}
					} else {
						if (hops < 4) {
							w62 = -256;
						} else {
							w62 = 0;
						}
					}
				} else {
					if (rel_time < 4586) {
						if (rel_time < 4541) {
							w62 = 256;
						} else {
							w62 = 0;
						}
					} else {
						if (rel_time < 4863) {
							w62 = -256;
						} else {
							w62 = 0;
						}
					}
				}
			}
		}
	}
	int w63;
	if (rel_time < 5692) {
		if (rel_time < 5517) {
			if (rel_time < 5139) {
				if (rel_time < 4863) {
					if (rel_time < 4686) {
						if (rel_time < 4410) {
							w63 = 0;
						} else {
							w63 = 0;
						}
					} else {
						if (prod == 1) {
							w63 = 0;
						} else {
							w63 = -256;
						}
					}
				} else {
					if (prod == 1) {
						if (prod == 3) {
							w63 = 0;
						} else {
							w63 = 0;
						}
					} else {
						if (hops < 3) {
							w63 = 256;
						} else {
							w63 = 256;
						}
					}
				}
			} else {
				if (prod == 2) {
					if (prod == 1) {
						if (prod == 3) {
							w63 = 0;
						} else {
							w63 = 0;
						}
					} else {
						if (hops < 5) {
							w63 = 0;
						} else {
							w63 = -256;
						}
					}
				} else {
					if (rel_time < 5334) {
						if (hops < 3) {
							w63 = 0;
						} else {
							w63 = 0;
						}
					} else {
						w63 = 256;
					}
				}
			}
		} else {
			if (prod == 2) {
				if (prod == 0) {
					if (prod == 4) {
						if (rel_time < 5610) {
							w63 = 256;
						} else {
							w63 = 0;
						}
					} else {
						if (hops < 2) {
							w63 = -256;
						} else {
							w63 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w63 = 0;
						} else {
							w63 = 0;
						}
					} else {
						w63 = 0;
					}
				}
			} else {
				if (rel_time < 5610) {
					if (hops < 3) {
						if (hops < 2) {
							w63 = 0;
						} else {
							w63 = 0;
						}
					} else {
						if (hops < 4) {
							w63 = 0;
						} else {
							w63 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w63 = -256;
					} else {
						if (hops < 5) {
							w63 = 0;
						} else {
							w63 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 5966) {
			if (prod == 2) {
				if (prod == 0) {
					if (prod == 1) {
						if (hops < 2) {
							w63 = 0;
						} else {
							w63 = 0;
						}
					} else {
						if (hops < 2) {
							w63 = -256;
						} else {
							w63 = 0;
						}
					}
				} else {
					if (hops < 2) {
						if (rel_time < 5793) {
							w63 = 0;
						} else {
							w63 = 0;
						}
					} else {
						if (hops < 5) {
							w63 = 0;
						} else {
							w63 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					if (rel_time < 5885) {
						w63 = 0;
					} else {
						w63 = 0;
					}
				} else {
					if (hops < 5) {
						if (hops < 3) {
							w63 = 0;
						} else {
							w63 = 0;
						}
					} else {
						if (rel_time < 5885) {
							w63 = 0;
						} else {
							w63 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 6209) {
				if (prod == 2) {
					if (prod == 0) {
						if (rel_time < 6069) {
							w63 = 0;
						} else {
							w63 = 256;
						}
					} else {
						if (hops < 2) {
							w63 = 0;
						} else {
							w63 = 0;
						}
					}
				} else {
					if (rel_time < 6161) {
						if (hops < 2) {
							w63 = 0;
						} else {
							w63 = 0;
						}
					} else {
						if (hops < 5) {
							w63 = -256;
						} else {
							w63 = -256;
						}
					}
				}
			} else {
				if (rel_time < 6486) {
					if (prod == 2) {
						if (prod == 0) {
							w63 = 0;
						} else {
							w63 = 0;
						}
					} else {
						if (hops < 5) {
							w63 = 0;
						} else {
							w63 = 256;
						}
					}
				} else {
					if (rel_time < 6621) {
						if (prod == 4) {
							w63 = -256;
						} else {
							w63 = 0;
						}
					} else {
						if (rel_time < 6666) {
							w63 = 0;
						} else {
							w63 = 0;
						}
					}
				}
			}
		}
	}
	int w64;
	if (prod == 3) {
		if (rel_time < 9944) {
			if (rel_time < 9825) {
				if (rel_time < 9166) {
					if (rel_time < 8892) {
						if (rel_time < 8619) {
							w64 = 0;
						} else {
							w64 = 0;
						}
					} else {
						if (prod == 0) {
							w64 = 0;
						} else {
							w64 = 0;
						}
					}
				} else {
					if (rel_time < 9290) {
						if (prod == 1) {
							w64 = 256;
						} else {
							w64 = 0;
						}
					} else {
						if (prod == 1) {
							w64 = 0;
						} else {
							w64 = 0;
						}
					}
				}
			} else {
				if (prod == 0) {
					if (hops < 2) {
						w64 = 0;
					} else {
						if (hops < 5) {
							w64 = 0;
						} else {
							w64 = 256;
						}
					}
				} else {
					if (hops < 2) {
						w64 = 0;
					} else {
						if (hops < 3) {
							w64 = 0;
						} else {
							w64 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 10217) {
				if (prod == 1) {
					if (hops < 3) {
						if (rel_time < 9994) {
							w64 = 0;
						} else {
							w64 = 0;
						}
					} else {
						if (hops < 5) {
							w64 = 0;
						} else {
							w64 = 0;
						}
					}
				} else {
					if (hops < 2) {
						if (rel_time < 9994) {
							w64 = 0;
						} else {
							w64 = 0;
						}
					} else {
						if (hops < 5) {
							w64 = 0;
						} else {
							w64 = 0;
						}
					}
				}
			} else {
				if (prod == 1) {
					if (rel_time < 10264) {
						if (hops < 2) {
							w64 = 0;
						} else {
							w64 = 0;
						}
					} else {
						if (hops < 3) {
							w64 = 0;
						} else {
							w64 = 0;
						}
					}
				} else {
					if (rel_time < 10264) {
						if (hops < 2) {
							w64 = 0;
						} else {
							w64 = 0;
						}
					} else {
						if (hops < 2) {
							w64 = 0;
						} else {
							w64 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 3739) {
			if (hops < 3) {
				if (hops < 2) {
					w64 = 0;
				} else {
					w64 = 0;
				}
			} else {
				if (hops < 5) {
					if (hops < 4) {
						w64 = -256;
					} else {
						w64 = -256;
					}
				} else {
					w64 = 0;
				}
			}
		} else {
			if (rel_time < 4032) {
				if (rel_time < 3987) {
					w64 = 512;
				} else {
					if (hops < 5) {
						if (hops < 2) {
							w64 = 0;
						} else {
							w64 = 256;
						}
					} else {
						w64 = 0;
					}
				}
			} else {
				if (rel_time < 4309) {
					if (rel_time < 4264) {
						if (hops < 2) {
							w64 = -256;
						} else {
							w64 = -256;
						}
					} else {
						if (hops < 2) {
							w64 = 0;
						} else {
							w64 = 0;
						}
					}
				} else {
					if (rel_time < 4586) {
						if (rel_time < 4541) {
							w64 = 256;
						} else {
							w64 = 0;
						}
					} else {
						if (rel_time < 4863) {
							w64 = 0;
						} else {
							w64 = 0;
						}
					}
				}
			}
		}
	}
	int w65;
	if (rel_time < 1382) {
		if (rel_time < 1234) {
			if (rel_time < 1126) {
				if (rel_time < 1078) {
					if (rel_time < 1029) {
						if (rel_time < 981) {
							w65 = 0;
						} else {
							w65 = 0;
						}
					} else {
						if (hops < 4) {
							w65 = 0;
						} else {
							w65 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w65 = 0;
						} else {
							w65 = 0;
						}
					} else {
						if (hops < 4) {
							w65 = 0;
						} else {
							w65 = 256;
						}
					}
				}
			} else {
				if (cons == 4) {
					if (rel_time < 1205) {
						if (hops < 3) {
							w65 = -256;
						} else {
							w65 = 0;
						}
					} else {
						if (hops < 5) {
							w65 = 0;
						} else {
							w65 = -256;
						}
					}
				} else {
					if (hops < 2) {
						w65 = 0;
					} else {
						if (hops < 4) {
							w65 = 0;
						} else {
							w65 = 0;
						}
					}
				}
			}
		} else {
			if (cons == 4) {
				if (cons == 2) {
					if (cons == 0) {
						if (hops < 4) {
							w65 = 0;
						} else {
							w65 = 0;
						}
					} else {
						if (hops < 3) {
							w65 = 0;
						} else {
							w65 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w65 = 0;
						} else {
							w65 = 0;
						}
					} else {
						if (hops < 5) {
							w65 = 0;
						} else {
							w65 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w65 = 0;
				} else {
					if (hops < 3) {
						w65 = 0;
					} else {
						if (hops < 4) {
							w65 = 0;
						} else {
							w65 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 1529) {
			if (cons == 3) {
				if (rel_time < 1411) {
					if (hops < 2) {
						w65 = 0;
					} else {
						if (hops < 4) {
							w65 = 0;
						} else {
							w65 = 0;
						}
					}
				} else {
					if (cons == 0) {
						if (hops < 4) {
							w65 = 0;
						} else {
							w65 = 0;
						}
					} else {
						if (hops < 2) {
							w65 = 0;
						} else {
							w65 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w65 = 0;
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w65 = 0;
						} else {
							w65 = -256;
						}
					} else {
						if (hops < 5) {
							w65 = 0;
						} else {
							w65 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 1559) {
				if (hops < 4) {
					if (hops < 3) {
						w65 = 0;
					} else {
						w65 = 0;
					}
				} else {
					if (hops < 5) {
						w65 = 0;
					} else {
						w65 = 0;
					}
				}
			} else {
				if (rel_time < 1588) {
					if (hops < 4) {
						if (hops < 2) {
							w65 = 0;
						} else {
							w65 = 0;
						}
					} else {
						if (hops < 5) {
							w65 = 0;
						} else {
							w65 = 0;
						}
					}
				} else {
					if (rel_time < 1617) {
						if (hops < 2) {
							w65 = 0;
						} else {
							w65 = 0;
						}
					} else {
						if (rel_time < 1764) {
							w65 = 0;
						} else {
							w65 = 0;
						}
					}
				}
			}
		}
	}
	int w66;
	if (rel_time < 3152) {
		if (rel_time < 3004) {
			if (rel_time < 2975) {
				if (rel_time < 2857) {
					if (rel_time < 2709) {
						if (rel_time < 2680) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					} else {
						if (cons == 3) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					}
				} else {
					if (rel_time < 2886) {
						if (hops < 2) {
							w66 = 0;
						} else {
							w66 = -256;
						}
					} else {
						if (cons == 3) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w66 = 0;
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					} else {
						if (hops < 5) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					}
				}
			}
		} else {
			if (cons == 2) {
				if (cons == 4) {
					if (rel_time < 3122) {
						if (hops < 2) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					} else {
						if (hops < 2) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					} else {
						if (hops < 4) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w66 = 0;
					} else {
						w66 = 0;
					}
				} else {
					if (hops < 4) {
						w66 = 0;
					} else {
						w66 = 0;
					}
				}
			}
		}
	} else {
		if (rel_time < 3299) {
			if (cons == 3) {
				if (rel_time < 3181) {
					if (hops < 3) {
						if (hops < 2) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					} else {
						if (hops < 5) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					}
				} else {
					if (rel_time < 3270) {
						if (hops < 3) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					} else {
						if (hops < 3) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w66 = 0;
					} else {
						w66 = 0;
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					} else {
						w66 = 0;
					}
				}
			}
		} else {
			if (rel_time < 3387) {
				if (cons == 2) {
					if (hops < 4) {
						if (hops < 2) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					} else {
						if (hops < 5) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					} else {
						if (hops < 4) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					}
				}
			} else {
				if (cons == 0) {
					if (rel_time < 3651) {
						if (rel_time < 3607) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					} else {
						if (rel_time < 3695) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					} else {
						if (hops < 5) {
							w66 = 0;
						} else {
							w66 = 0;
						}
					}
				}
			}
		}
	}
	int w67;
	if (prod == 2) {
		if (rel_time < 7493) {
			if (rel_time < 7220) {
				if (rel_time < 6943) {
					if (rel_time < 6666) {
						if (rel_time < 6345) {
							w67 = 0;
						} else {
							w67 = 0;
						}
					} else {
						if (prod == 4) {
							w67 = 0;
						} else {
							w67 = 0;
						}
					}
				} else {
					if (prod == 4) {
						if (prod == 3) {
							w67 = 0;
						} else {
							w67 = -512;
						}
					} else {
						if (hops < 4) {
							w67 = 256;
						} else {
							w67 = 256;
						}
					}
				}
			} else {
				if (prod == 3) {
					if (prod == 4) {
						if (hops < 4) {
							w67 = 0;
						} else {
							w67 = 0;
						}
					} else {
						if (hops < 3) {
							w67 = 0;
						} else {
							w67 = 0;
						}
					}
				} else {
					if (rel_time < 7314) {
						if (hops < 3) {
							w67 = 512;
						} else {
							w67 = 512;
						}
					} else {
						if (hops < 3) {
							w67 = 0;
						} else {
							w67 = 256;
						}
					}
				}
			}
		} else {
			if (rel_time < 7636) {
				if (prod == 4) {
					if (rel_time < 7541) {
						if (hops < 5) {
							w67 = 0;
						} else {
							w67 = -256;
						}
					} else {
						if (hops < 4) {
							w67 = 0;
						} else {
							w67 = -256;
						}
					}
				} else {
					if (hops < 2) {
						w67 = 0;
					} else {
						if (hops < 4) {
							w67 = 0;
						} else {
							w67 = 0;
						}
					}
				}
			} else {
				if (rel_time < 7913) {
					if (prod == 3) {
						if (prod == 1) {
							w67 = 0;
						} else {
							w67 = 0;
						}
					} else {
						if (rel_time < 7864) {
							w67 = 256;
						} else {
							w67 = 0;
						}
					}
				} else {
					if (rel_time < 8188) {
						if (prod == 3) {
							w67 = 0;
						} else {
							w67 = -256;
						}
					} else {
						if (rel_time < 8465) {
							w67 = 0;
						} else {
							w67 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 3695) {
			if (hops < 3) {
				if (hops < 2) {
					w67 = 0;
				} else {
					w67 = 256;
				}
			} else {
				if (hops < 4) {
					w67 = 0;
				} else {
					if (hops < 5) {
						w67 = 0;
					} else {
						w67 = 0;
					}
				}
			}
		} else {
			if (rel_time < 3987) {
				if (rel_time < 3943) {
					if (hops < 2) {
						w67 = -512;
					} else {
						if (hops < 3) {
							w67 = -768;
						} else {
							w67 = -512;
						}
					}
				} else {
					if (hops < 2) {
						w67 = 0;
					} else {
						if (hops < 3) {
							w67 = -256;
						} else {
							w67 = 0;
						}
					}
				}
			} else {
				if (rel_time < 4264) {
					if (hops < 2) {
						if (rel_time < 4219) {
							w67 = 256;
						} else {
							w67 = 0;
						}
					} else {
						if (hops < 5) {
							w67 = 0;
						} else {
							w67 = 0;
						}
					}
				} else {
					if (rel_time < 4541) {
						if (rel_time < 4496) {
							w67 = 0;
						} else {
							w67 = 0;
						}
					} else {
						if (rel_time < 4817) {
							w67 = 0;
						} else {
							w67 = 0;
						}
					}
				}
			}
		}
	}
	int w68;
	if (rel_time < 2090) {
		if (rel_time < 2030) {
			if (rel_time < 1824) {
				if (rel_time < 1735) {
					if (rel_time < 1706) {
						if (rel_time < 1677) {
							w68 = 0;
						} else {
							w68 = 0;
						}
					} else {
						if (hops < 4) {
							w68 = 0;
						} else {
							w68 = 0;
						}
					}
				} else {
					if (cons == 4) {
						if (rel_time < 1764) {
							w68 = 0;
						} else {
							w68 = 0;
						}
					} else {
						if (hops < 4) {
							w68 = 0;
						} else {
							w68 = 0;
						}
					}
				}
			} else {
				if (cons == 0) {
					if (rel_time < 1942) {
						if (cons == 2) {
							w68 = 0;
						} else {
							w68 = 0;
						}
					} else {
						if (rel_time < 2001) {
							w68 = -256;
						} else {
							w68 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w68 = 256;
						} else {
							w68 = 0;
						}
					} else {
						if (hops < 5) {
							w68 = 0;
						} else {
							w68 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 2059) {
				if (hops < 4) {
					if (hops < 3) {
						if (hops < 2) {
							w68 = -256;
						} else {
							w68 = -256;
						}
					} else {
						w68 = -256;
					}
				} else {
					if (hops < 5) {
						w68 = 0;
					} else {
						w68 = 0;
					}
				}
			} else {
				if (hops < 2) {
					w68 = 0;
				} else {
					if (hops < 3) {
						w68 = 0;
					} else {
						if (hops < 5) {
							w68 = 0;
						} else {
							w68 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 2207) {
			if (cons == 0) {
				if (cons == 2) {
					if (rel_time < 2149) {
						if (hops < 2) {
							w68 = 0;
						} else {
							w68 = 256;
						}
					} else {
						if (hops < 5) {
							w68 = 0;
						} else {
							w68 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 2) {
							w68 = 0;
						} else {
							w68 = 0;
						}
					} else {
						if (hops < 5) {
							w68 = 0;
						} else {
							w68 = 0;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 3) {
						if (hops < 2) {
							w68 = 0;
						} else {
							w68 = 0;
						}
					} else {
						w68 = 0;
					}
				} else {
					if (hops < 5) {
						w68 = 0;
					} else {
						w68 = 0;
					}
				}
			}
		} else {
			if (rel_time < 2354) {
				if (cons == 1) {
					if (rel_time < 2325) {
						if (rel_time < 2237) {
							w68 = 0;
						} else {
							w68 = 0;
						}
					} else {
						if (hops < 2) {
							w68 = 0;
						} else {
							w68 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 2) {
							w68 = 0;
						} else {
							w68 = 0;
						}
					} else {
						w68 = 0;
					}
				}
			} else {
				if (rel_time < 2562) {
					if (cons == 3) {
						if (cons == 1) {
							w68 = 0;
						} else {
							w68 = 0;
						}
					} else {
						if (hops < 2) {
							w68 = 0;
						} else {
							w68 = 0;
						}
					}
				} else {
					if (rel_time < 2591) {
						if (hops < 5) {
							w68 = 0;
						} else {
							w68 = 0;
						}
					} else {
						if (cons == 1) {
							w68 = 0;
						} else {
							w68 = 0;
						}
					}
				}
			}
		}
	}
	int w69;
	if (hops < 5) {
		if (rel_time < 10309) {
			if (rel_time < 10042) {
				if (rel_time < 9944) {
					if (rel_time < 9825) {
						if (rel_time < 1529) {
							w69 = 0;
						} else {
							w69 = 0;
						}
					} else {
						if (prod == 3) {
							w69 = 0;
						} else {
							w69 = -512;
						}
					}
				} else {
					if (prod == 1) {
						if (hops < 3) {
							w69 = 0;
						} else {
							w69 = 0;
						}
					} else {
						if (rel_time < 9994) {
							w69 = 0;
						} else {
							w69 = 0;
						}
					}
				}
			} else {
				if (prod == 3) {
					if (prod == 0) {
						if (rel_time < 10264) {
							w69 = 0;
						} else {
							w69 = 0;
						}
					} else {
						if (rel_time < 10217) {
							w69 = 0;
						} else {
							w69 = 0;
						}
					}
				} else {
					if (rel_time < 10096) {
						if (hops < 3) {
							w69 = 0;
						} else {
							w69 = 0;
						}
					} else {
						if (hops < 4) {
							w69 = 0;
						} else {
							w69 = 0;
						}
					}
				}
			}
		} else {
			if (prod == 3) {
				if (rel_time < 10356) {
					if (hops < 2) {
						w69 = 0;
					} else {
						if (hops < 4) {
							w69 = 0;
						} else {
							w69 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 2) {
							w69 = 0;
						} else {
							w69 = 0;
						}
					} else {
						w69 = 0;
					}
				}
			} else {
				if (rel_time < 10356) {
					if (hops < 2) {
						w69 = 0;
					} else {
						if (hops < 3) {
							w69 = 0;
						} else {
							w69 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w69 = 0;
					} else {
						if (hops < 4) {
							w69 = 0;
						} else {
							w69 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 782) {
			if (rel_time < 734) {
				if (cons == 0) {
					if (rel_time < 182) {
						w69 = 0;
					} else {
						if (rel_time < 244) {
							w69 = 0;
						} else {
							w69 = 0;
						}
					}
				} else {
					if (rel_time < 68) {
						w69 = 0;
					} else {
						w69 = 0;
					}
				}
			} else {
				w69 = 0;
			}
		} else {
			if (rel_time < 927) {
				if (cons == 2) {
					if (rel_time < 831) {
						w69 = 0;
					} else {
						w69 = 0;
					}
				} else {
					w69 = 0;
				}
			} else {
				if (rel_time < 1078) {
					if (cons == 0) {
						if (rel_time < 981) {
							w69 = 0;
						} else {
							w69 = 0;
						}
					} else {
						w69 = 0;
					}
				} else {
					if (rel_time < 1126) {
						w69 = 0;
					} else {
						if (rel_time < 1234) {
							w69 = 0;
						} else {
							w69 = 0;
						}
					}
				}
			}
		}
	}
	int w70;
	if (rel_time < 610) {
		if (rel_time < 539) {
			if (rel_time < 468) {
				if (cons == 3) {
					if (cons == 1) {
						if (rel_time < 397) {
							w70 = 0;
						} else {
							w70 = 0;
						}
					} else {
						if (hops < 4) {
							w70 = 0;
						} else {
							w70 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w70 = 0;
						} else {
							w70 = 0;
						}
					} else {
						if (hops < 5) {
							w70 = 0;
						} else {
							w70 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w70 = 0;
				} else {
					if (hops < 3) {
						w70 = 0;
					} else {
						if (hops < 4) {
							w70 = 0;
						} else {
							w70 = 0;
						}
					}
				}
			}
		} else {
			if (hops < 2) {
				w70 = 0;
			} else {
				if (hops < 4) {
					if (hops < 3) {
						w70 = 0;
					} else {
						w70 = 0;
					}
				} else {
					if (hops < 5) {
						w70 = 0;
					} else {
						w70 = 0;
					}
				}
			}
		}
	} else {
		if (rel_time < 782) {
			if (cons == 4) {
				if (hops < 4) {
					if (hops < 2) {
						if (rel_time < 681) {
							w70 = 0;
						} else {
							w70 = 0;
						}
					} else {
						if (hops < 3) {
							w70 = 0;
						} else {
							w70 = 0;
						}
					}
				} else {
					if (rel_time < 681) {
						if (hops < 5) {
							w70 = 0;
						} else {
							w70 = 0;
						}
					} else {
						if (hops < 5) {
							w70 = 0;
						} else {
							w70 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w70 = 0;
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w70 = 0;
						} else {
							w70 = 0;
						}
					} else {
						w70 = 0;
					}
				}
			}
		} else {
			if (rel_time < 831) {
				if (hops < 2) {
					w70 = 0;
				} else {
					if (hops < 3) {
						if (cons == 1) {
							w70 = 0;
						} else {
							w70 = 0;
						}
					} else {
						if (hops < 4) {
							w70 = 0;
						} else {
							w70 = 0;
						}
					}
				}
			} else {
				if (rel_time < 879) {
					if (hops < 3) {
						if (hops < 2) {
							w70 = 0;
						} else {
							w70 = 0;
						}
					} else {
						if (hops < 4) {
							w70 = 0;
						} else {
							w70 = 0;
						}
					}
				} else {
					if (rel_time < 927) {
						if (hops < 3) {
							w70 = 0;
						} else {
							w70 = 0;
						}
					} else {
						if (rel_time < 1529) {
							w70 = 0;
						} else {
							w70 = 0;
						}
					}
				}
			}
		}
	}
	int w71;
	if (rel_time < 2267) {
		if (rel_time < 2090) {
			if (rel_time < 2030) {
				if (rel_time < 1824) {
					if (rel_time < 1735) {
						if (rel_time < 1529) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					} else {
						if (cons == 4) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					}
				} else {
					if (rel_time < 1854) {
						if (hops < 4) {
							w71 = 0;
						} else {
							w71 = 256;
						}
					} else {
						if (cons == 1) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					}
				}
			} else {
				if (rel_time < 2059) {
					if (hops < 4) {
						if (hops < 3) {
							w71 = 0;
						} else {
							w71 = -256;
						}
					} else {
						if (hops < 5) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w71 = 0;
					} else {
						if (hops < 5) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					}
				}
			}
		} else {
			if (cons == 1) {
				if (cons == 3) {
					if (rel_time < 2149) {
						if (hops < 4) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					} else {
						if (cons == 4) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 2) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					} else {
						if (hops < 5) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w71 = 0;
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w71 = 256;
						} else {
							w71 = 256;
						}
					} else {
						if (hops < 5) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 2354) {
			if (cons == 2) {
				if (hops < 3) {
					if (rel_time < 2325) {
						if (hops < 2) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					} else {
						if (hops < 2) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					}
				} else {
					if (rel_time < 2325) {
						if (hops < 4) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					} else {
						if (hops < 5) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w71 = 0;
				} else {
					if (hops < 5) {
						if (hops < 3) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					} else {
						w71 = 0;
					}
				}
			}
		} else {
			if (rel_time < 2562) {
				if (cons == 3) {
					if (rel_time < 2532) {
						if (cons == 1) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					} else {
						if (hops < 4) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w71 = 0;
					} else {
						if (hops < 4) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					}
				}
			} else {
				if (rel_time < 2591) {
					if (hops < 4) {
						if (hops < 2) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					} else {
						if (hops < 5) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					}
				} else {
					if (rel_time < 2709) {
						if (cons == 3) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					} else {
						if (rel_time < 2857) {
							w71 = 0;
						} else {
							w71 = 0;
						}
					}
				}
			}
		}
	}
	int w72;
	if (rel_time < 1382) {
		if (rel_time < 1234) {
			if (rel_time < 1126) {
				if (rel_time < 1078) {
					if (rel_time < 1029) {
						if (rel_time < 981) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					} else {
						if (hops < 3) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					} else {
						if (hops < 4) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					}
				}
			} else {
				if (cons == 4) {
					if (rel_time < 1205) {
						if (hops < 3) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					} else {
						if (hops < 2) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					} else {
						if (hops < 4) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					}
				}
			}
		} else {
			if (cons == 4) {
				if (cons == 2) {
					if (cons == 3) {
						if (hops < 2) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					} else {
						if (hops < 3) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					} else {
						if (hops < 5) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w72 = 0;
				} else {
					if (hops < 3) {
						w72 = 0;
					} else {
						if (hops < 4) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 1529) {
			if (cons == 2) {
				if (rel_time < 1469) {
					if (hops < 3) {
						if (rel_time < 1411) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					} else {
						if (hops < 4) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (cons == 0) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					} else {
						if (hops < 4) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w72 = 0;
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					} else {
						if (hops < 5) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 1559) {
				if (hops < 4) {
					if (hops < 3) {
						w72 = 0;
					} else {
						w72 = 0;
					}
				} else {
					if (hops < 5) {
						w72 = 0;
					} else {
						w72 = 0;
					}
				}
			} else {
				if (rel_time < 1588) {
					if (hops < 4) {
						if (hops < 2) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					} else {
						w72 = 0;
					}
				} else {
					if (rel_time < 1617) {
						if (hops < 5) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					} else {
						if (rel_time < 1764) {
							w72 = 0;
						} else {
							w72 = 0;
						}
					}
				}
			}
		}
	}
	int w73;
	if (hops < 5) {
		if (rel_time < 3898) {
			if (prod == 3) {
				if (prod == 1) {
					if (prod == 2) {
						if (rel_time < 3152) {
							w73 = 0;
						} else {
							w73 = 0;
						}
					} else {
						if (hops < 3) {
							w73 = 0;
						} else {
							w73 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w73 = 0;
						} else {
							w73 = 0;
						}
					} else {
						if (hops < 4) {
							w73 = -256;
						} else {
							w73 = -512;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w73 = 0;
					} else {
						w73 = 0;
					}
				} else {
					if (hops < 4) {
						w73 = 0;
					} else {
						w73 = -256;
					}
				}
			}
		} else {
			if (rel_time < 3943) {
				if (prod == 1) {
					if (hops < 2) {
						w73 = -256;
					} else {
						if (hops < 3) {
							w73 = -512;
						} else {
							w73 = -256;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w73 = 0;
						} else {
							w73 = 0;
						}
					} else {
						if (hops < 4) {
							w73 = 256;
						} else {
							w73 = 256;
						}
					}
				}
			} else {
				if (rel_time < 3987) {
					if (prod == 2) {
						if (hops < 2) {
							w73 = 256;
						} else {
							w73 = 256;
						}
					} else {
						if (hops < 2) {
							w73 = 0;
						} else {
							w73 = 0;
						}
					}
				} else {
					if (rel_time < 4032) {
						if (prod == 3) {
							w73 = 0;
						} else {
							w73 = 0;
						}
					} else {
						if (rel_time < 4219) {
							w73 = 0;
						} else {
							w73 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 6943) {
			if (rel_time < 6666) {
				if (rel_time < 6621) {
					if (rel_time < 6438) {
						if (rel_time < 6391) {
							w73 = 0;
						} else {
							w73 = -256;
						}
					} else {
						if (prod == 3) {
							w73 = 0;
						} else {
							w73 = -256;
						}
					}
				} else {
					w73 = 0;
				}
			} else {
				if (prod == 3) {
					if (rel_time < 6714) {
						w73 = 256;
					} else {
						if (prod == 0) {
							w73 = 0;
						} else {
							w73 = 0;
						}
					}
				} else {
					if (rel_time < 6761) {
						w73 = 0;
					} else {
						w73 = 256;
					}
				}
			}
		} else {
			if (rel_time < 6991) {
				w73 = 0;
			} else {
				if (rel_time < 7037) {
					w73 = 0;
				} else {
					if (rel_time < 7087) {
						if (prod == 3) {
							w73 = 256;
						} else {
							w73 = -256;
						}
					} else {
						if (rel_time < 7266) {
							w73 = 0;
						} else {
							w73 = 0;
						}
					}
				}
			}
		}
	}
	int w74;
	if (rel_time < 5692) {
		if (rel_time < 5517) {
			if (rel_time < 5139) {
				if (rel_time < 4863) {
					if (rel_time < 4686) {
						if (rel_time < 4410) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					} else {
						if (prod == 1) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					}
				} else {
					if (prod == 1) {
						if (prod == 2) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					} else {
						if (hops < 2) {
							w74 = 0;
						} else {
							w74 = 256;
						}
					}
				}
			} else {
				if (prod == 2) {
					if (prod == 1) {
						if (prod == 0) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					} else {
						if (hops < 5) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					}
				} else {
					if (rel_time < 5334) {
						w74 = 0;
					} else {
						w74 = 0;
					}
				}
			}
		} else {
			if (prod == 2) {
				if (prod == 0) {
					if (prod == 4) {
						if (rel_time < 5610) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					} else {
						if (hops < 2) {
							w74 = -256;
						} else {
							w74 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 2) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					} else {
						w74 = 0;
					}
				}
			} else {
				if (rel_time < 5610) {
					if (hops < 3) {
						if (hops < 2) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					} else {
						if (hops < 4) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w74 = 0;
					} else {
						if (hops < 5) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 5966) {
			if (prod == 2) {
				if (prod == 0) {
					if (rel_time < 5793) {
						if (hops < 3) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					} else {
						if (hops < 2) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					} else {
						if (hops < 5) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					if (rel_time < 5885) {
						w74 = 0;
					} else {
						w74 = 0;
					}
				} else {
					if (hops < 5) {
						if (rel_time < 5885) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					} else {
						if (rel_time < 5885) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 6115) {
				if (prod == 1) {
					if (prod == 0) {
						if (hops < 2) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					} else {
						if (rel_time < 6069) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w74 = 512;
					} else {
						if (hops < 3) {
							w74 = 256;
						} else {
							w74 = 256;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (rel_time < 6486) {
						if (prod == 0) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					} else {
						if (rel_time < 6621) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					}
				} else {
					if (rel_time < 6943) {
						if (prod == 3) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					} else {
						if (rel_time < 6991) {
							w74 = 0;
						} else {
							w74 = 0;
						}
					}
				}
			}
		}
	}
	int w75;
	if (rel_time < 8963) {
		if (rel_time < 8465) {
			if (rel_time < 8139) {
				if (rel_time < 8017) {
					if (prod == 2) {
						if (rel_time < 7742) {
							w75 = 0;
						} else {
							w75 = 0;
						}
					} else {
						if (rel_time < 7037) {
							w75 = 0;
						} else {
							w75 = 0;
						}
					}
				} else {
					if (prod == 3) {
						if (prod == 1) {
							w75 = 0;
						} else {
							w75 = 0;
						}
					} else {
						w75 = -1792;
					}
				}
			} else {
				if (prod == 0) {
					if (prod == 2) {
						if (rel_time < 8188) {
							w75 = 0;
						} else {
							w75 = 0;
						}
					} else {
						if (hops < 4) {
							w75 = 0;
						} else {
							w75 = 0;
						}
					}
				} else {
					if (rel_time < 8292) {
						if (hops < 3) {
							w75 = 0;
						} else {
							w75 = 0;
						}
					} else {
						if (hops < 4) {
							w75 = 0;
						} else {
							w75 = 0;
						}
					}
				}
			}
		} else {
			if (prod == 3) {
				if (rel_time < 8567) {
					if (prod == 0) {
						if (hops < 3) {
							w75 = 0;
						} else {
							w75 = 0;
						}
					} else {
						if (hops < 2) {
							w75 = 0;
						} else {
							w75 = 0;
						}
					}
				} else {
					if (rel_time < 8892) {
						if (prod == 2) {
							w75 = 0;
						} else {
							w75 = 0;
						}
					} else {
						if (prod == 1) {
							w75 = 0;
						} else {
							w75 = 0;
						}
					}
				}
			} else {
				if (rel_time < 8690) {
					w75 = -768;
				} else {
					if (hops < 2) {
						w75 = 0;
					} else {
						if (hops < 3) {
							w75 = 0;
						} else {
							w75 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 9014) {
			if (prod == 3) {
				if (hops < 3) {
					w75 = 0;
				} else {
					w75 = 0;
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w75 = 0;
					} else {
						w75 = 0;
					}
				} else {
					if (hops < 4) {
						w75 = 0;
					} else {
						w75 = 0;
					}
				}
			}
		} else {
			if (prod == 2) {
				if (rel_time < 9290) {
					if (prod == 3) {
						if (prod == 1) {
							w75 = 0;
						} else {
							w75 = 0;
						}
					} else {
						if (hops < 2) {
							w75 = 0;
						} else {
							w75 = 0;
						}
					}
				} else {
					if (rel_time < 9717) {
						if (prod == 4) {
							w75 = 0;
						} else {
							w75 = 0;
						}
					} else {
						if (rel_time < 9825) {
							w75 = 0;
						} else {
							w75 = 0;
						}
					}
				}
			} else {
				if (rel_time < 9290) {
					if (rel_time < 9219) {
						if (hops < 3) {
							w75 = 0;
						} else {
							w75 = 0;
						}
					} else {
						w75 = 512;
					}
				} else {
					if (rel_time < 9564) {
						if (rel_time < 9494) {
							w75 = 0;
						} else {
							w75 = -256;
						}
					} else {
						if (rel_time < 9825) {
							w75 = 0;
						} else {
							w75 = 0;
						}
					}
				}
			}
		}
	}
	int w76;
	if (rel_time < 10309) {
		if (rel_time < 10042) {
			if (rel_time < 9944) {
				if (rel_time < 8963) {
					if (rel_time < 8465) {
						if (rel_time < 8139) {
							w76 = 0;
						} else {
							w76 = 0;
						}
					} else {
						if (prod == 3) {
							w76 = 0;
						} else {
							w76 = 0;
						}
					}
				} else {
					if (rel_time < 9014) {
						if (prod == 3) {
							w76 = 0;
						} else {
							w76 = 0;
						}
					} else {
						if (prod == 3) {
							w76 = 0;
						} else {
							w76 = 0;
						}
					}
				}
			} else {
				if (prod == 1) {
					if (rel_time < 9994) {
						if (hops < 5) {
							w76 = 0;
						} else {
							w76 = 0;
						}
					} else {
						if (hops < 2) {
							w76 = 0;
						} else {
							w76 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w76 = 0;
					} else {
						if (hops < 5) {
							w76 = 0;
						} else {
							w76 = 0;
						}
					}
				}
			}
		} else {
			if (prod == 3) {
				if (prod == 0) {
					if (rel_time < 10264) {
						if (hops < 2) {
							w76 = 0;
						} else {
							w76 = 0;
						}
					} else {
						if (prod == 1) {
							w76 = 0;
						} else {
							w76 = 0;
						}
					}
				} else {
					if (rel_time < 10217) {
						if (hops < 2) {
							w76 = 0;
						} else {
							w76 = 0;
						}
					} else {
						if (hops < 2) {
							w76 = 0;
						} else {
							w76 = 0;
						}
					}
				}
			} else {
				if (rel_time < 10096) {
					if (hops < 3) {
						if (hops < 2) {
							w76 = 0;
						} else {
							w76 = 0;
						}
					} else {
						if (hops < 4) {
							w76 = 0;
						} else {
							w76 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 2) {
							w76 = 0;
						} else {
							w76 = 0;
						}
					} else {
						w76 = 256;
					}
				}
			}
		}
	} else {
		if (prod == 3) {
			if (rel_time < 10356) {
				if (hops < 3) {
					if (hops < 2) {
						w76 = 0;
					} else {
						w76 = 0;
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w76 = 0;
						} else {
							w76 = 0;
						}
					} else {
						w76 = 0;
					}
				}
			} else {
				if (hops < 5) {
					if (hops < 4) {
						if (hops < 3) {
							w76 = 0;
						} else {
							w76 = 0;
						}
					} else {
						w76 = 0;
					}
				} else {
					w76 = 0;
				}
			}
		} else {
			if (rel_time < 10356) {
				if (hops < 2) {
					w76 = 0;
				} else {
					if (hops < 3) {
						w76 = 0;
					} else {
						w76 = 0;
					}
				}
			} else {
				if (hops < 5) {
					if (hops < 4) {
						if (hops < 2) {
							w76 = 0;
						} else {
							w76 = 0;
						}
					} else {
						w76 = 0;
					}
				} else {
					w76 = 0;
				}
			}
		}
	}
	int w77;
	if (cons == 3) {
		if (rel_time < 1854) {
			if (rel_time < 1824) {
				if (rel_time < 1706) {
					if (rel_time < 1677) {
						if (rel_time < 1529) {
							w77 = 0;
						} else {
							w77 = 0;
						}
					} else {
						if (hops < 2) {
							w77 = 0;
						} else {
							w77 = 0;
						}
					}
				} else {
					if (cons == 0) {
						if (hops < 4) {
							w77 = 0;
						} else {
							w77 = 0;
						}
					} else {
						if (hops < 5) {
							w77 = 0;
						} else {
							w77 = 0;
						}
					}
				}
			} else {
				if (hops < 5) {
					if (hops < 4) {
						if (hops < 3) {
							w77 = 0;
						} else {
							w77 = 0;
						}
					} else {
						w77 = 256;
					}
				} else {
					w77 = 0;
				}
			}
		} else {
			if (rel_time < 1883) {
				if (hops < 4) {
					if (hops < 2) {
						w77 = 0;
					} else {
						if (hops < 3) {
							w77 = 0;
						} else {
							w77 = 0;
						}
					}
				} else {
					if (hops < 5) {
						w77 = 0;
					} else {
						w77 = 0;
					}
				}
			} else {
				if (cons == 1) {
					if (rel_time < 2001) {
						if (rel_time < 1942) {
							w77 = 0;
						} else {
							w77 = 0;
						}
					} else {
						if (rel_time < 2149) {
							w77 = 0;
						} else {
							w77 = 0;
						}
					}
				} else {
					if (rel_time < 2001) {
						if (hops < 3) {
							w77 = 0;
						} else {
							w77 = -256;
						}
					} else {
						if (rel_time < 2149) {
							w77 = 0;
						} else {
							w77 = 0;
						}
					}
				}
			}
		}
	} else {
		if (hops < 4) {
			if (rel_time < 3387) {
				if (rel_time < 3270) {
					if (rel_time < 3122) {
						if (rel_time < 3063) {
							w77 = 0;
						} else {
							w77 = 0;
						}
					} else {
						if (hops < 3) {
							w77 = 0;
						} else {
							w77 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w77 = 0;
					} else {
						if (hops < 3) {
							w77 = 0;
						} else {
							w77 = 0;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w77 = 0;
					} else {
						w77 = 0;
					}
				} else {
					w77 = 0;
				}
			}
		} else {
			if (rel_time < 2649) {
				if (rel_time < 1912) {
					if (rel_time < 1764) {
						if (rel_time < 1617) {
							w77 = 0;
						} else {
							w77 = 0;
						}
					} else {
						if (hops < 5) {
							w77 = 256;
						} else {
							w77 = 0;
						}
					}
				} else {
					if (rel_time < 2059) {
						w77 = 0;
					} else {
						if (rel_time < 2207) {
							w77 = 0;
						} else {
							w77 = 0;
						}
					}
				}
			} else {
				if (rel_time < 2797) {
					w77 = 256;
				} else {
					if (rel_time < 2944) {
						if (hops < 5) {
							w77 = 0;
						} else {
							w77 = 0;
						}
					} else {
						if (rel_time < 3122) {
							w77 = 0;
						} else {
							w77 = 0;
						}
					}
				}
			}
		}
	}
	int w78;
	if (rel_time < 610) {
		if (rel_time < 539) {
			if (rel_time < 468) {
				if (cons == 3) {
					if (cons == 1) {
						if (rel_time < 397) {
							w78 = 0;
						} else {
							w78 = 0;
						}
					} else {
						if (hops < 3) {
							w78 = 0;
						} else {
							w78 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 3) {
							w78 = 0;
						} else {
							w78 = 0;
						}
					} else {
						w78 = 0;
					}
				}
			} else {
				if (hops < 2) {
					w78 = 0;
				} else {
					if (hops < 3) {
						w78 = 0;
					} else {
						if (hops < 4) {
							w78 = 0;
						} else {
							w78 = 0;
						}
					}
				}
			}
		} else {
			if (hops < 2) {
				w78 = 0;
			} else {
				if (hops < 4) {
					if (hops < 3) {
						w78 = 0;
					} else {
						w78 = 0;
					}
				} else {
					if (hops < 5) {
						w78 = 0;
					} else {
						w78 = 0;
					}
				}
			}
		}
	} else {
		if (rel_time < 782) {
			if (cons == 4) {
				if (hops < 2) {
					if (rel_time < 681) {
						w78 = 0;
					} else {
						w78 = 0;
					}
				} else {
					if (hops < 3) {
						if (rel_time < 681) {
							w78 = 0;
						} else {
							w78 = 0;
						}
					} else {
						if (hops < 4) {
							w78 = 0;
						} else {
							w78 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w78 = 0;
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w78 = 0;
						} else {
							w78 = 0;
						}
					} else {
						w78 = 0;
					}
				}
			}
		} else {
			if (rel_time < 831) {
				if (hops < 2) {
					w78 = 0;
				} else {
					if (hops < 3) {
						if (cons == 1) {
							w78 = 0;
						} else {
							w78 = 0;
						}
					} else {
						if (hops < 4) {
							w78 = 0;
						} else {
							w78 = 0;
						}
					}
				}
			} else {
				if (rel_time < 879) {
					if (hops < 3) {
						if (hops < 2) {
							w78 = 0;
						} else {
							w78 = 0;
						}
					} else {
						if (hops < 5) {
							w78 = 0;
						} else {
							w78 = 0;
						}
					}
				} else {
					if (rel_time < 927) {
						if (hops < 3) {
							w78 = 0;
						} else {
							w78 = 0;
						}
					} else {
						if (rel_time < 981) {
							w78 = 0;
						} else {
							w78 = 0;
						}
					}
				}
			}
		}
	}
	int w79;
	if (rel_time < 7589) {
		if (rel_time < 7541) {
			if (prod == 2) {
				if (rel_time < 7220) {
					if (rel_time < 6943) {
						if (rel_time < 6666) {
							w79 = 0;
						} else {
							w79 = 0;
						}
					} else {
						if (prod == 4) {
							w79 = 0;
						} else {
							w79 = 0;
						}
					}
				} else {
					if (prod == 3) {
						if (rel_time < 7266) {
							w79 = 0;
						} else {
							w79 = 0;
						}
					} else {
						if (rel_time < 7314) {
							w79 = 256;
						} else {
							w79 = 0;
						}
					}
				}
			} else {
				if (rel_time < 7037) {
					if (rel_time < 6761) {
						if (rel_time < 6486) {
							w79 = 0;
						} else {
							w79 = 0;
						}
					} else {
						if (rel_time < 6991) {
							w79 = 256;
						} else {
							w79 = 0;
						}
					}
				} else {
					if (rel_time < 7314) {
						if (hops < 4) {
							w79 = -256;
						} else {
							w79 = -256;
						}
					} else {
						w79 = 256;
					}
				}
			}
		} else {
			if (prod == 2) {
				if (hops < 3) {
					if (hops < 2) {
						w79 = 0;
					} else {
						w79 = 0;
					}
				} else {
					if (hops < 4) {
						w79 = 0;
					} else {
						w79 = -256;
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						w79 = 0;
					} else {
						w79 = 0;
					}
				} else {
					w79 = 256;
				}
			}
		}
	} else {
		if (rel_time < 7636) {
			if (prod == 3) {
				if (hops < 2) {
					w79 = 0;
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w79 = 0;
						} else {
							w79 = 0;
						}
					} else {
						if (hops < 5) {
							w79 = 0;
						} else {
							w79 = 0;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 3) {
						if (hops < 2) {
							w79 = 0;
						} else {
							w79 = 0;
						}
					} else {
						w79 = 0;
					}
				} else {
					if (hops < 5) {
						w79 = -256;
					} else {
						w79 = -256;
					}
				}
			}
		} else {
			if (prod == 3) {
				if (rel_time < 8092) {
					if (prod == 2) {
						if (rel_time < 7818) {
							w79 = 0;
						} else {
							w79 = 0;
						}
					} else {
						if (rel_time < 7864) {
							w79 = 0;
						} else {
							w79 = 0;
						}
					}
				} else {
					if (rel_time < 8188) {
						if (rel_time < 8139) {
							w79 = 0;
						} else {
							w79 = 256;
						}
					} else {
						if (rel_time < 8567) {
							w79 = 0;
						} else {
							w79 = 0;
						}
					}
				}
			} else {
				if (rel_time < 7913) {
					if (rel_time < 7864) {
						if (hops < 2) {
							w79 = 256;
						} else {
							w79 = 256;
						}
					} else {
						if (hops < 2) {
							w79 = 256;
						} else {
							w79 = 0;
						}
					}
				} else {
					if (rel_time < 8139) {
						if (hops < 2) {
							w79 = -1024;
						} else {
							w79 = -1280;
						}
					} else {
						if (rel_time < 8188) {
							w79 = 0;
						} else {
							w79 = 0;
						}
					}
				}
			}
		}
	}
	int w80;
	if (rel_time < 10309) {
		if (prod == 1) {
			if (rel_time < 9667) {
				if (rel_time < 9393) {
					if (rel_time < 9118) {
						if (rel_time < 8690) {
							w80 = 0;
						} else {
							w80 = 0;
						}
					} else {
						if (prod == 3) {
							w80 = 0;
						} else {
							w80 = 0;
						}
					}
				} else {
					if (prod == 3) {
						if (rel_time < 9564) {
							w80 = 0;
						} else {
							w80 = 0;
						}
					} else {
						if (hops < 3) {
							w80 = 0;
						} else {
							w80 = 0;
						}
					}
				}
			} else {
				if (rel_time < 9717) {
					if (hops < 3) {
						if (hops < 2) {
							w80 = 0;
						} else {
							w80 = 0;
						}
					} else {
						if (hops < 4) {
							w80 = 0;
						} else {
							w80 = 0;
						}
					}
				} else {
					if (rel_time < 10217) {
						if (prod == 0) {
							w80 = 0;
						} else {
							w80 = 0;
						}
					} else {
						if (hops < 2) {
							w80 = 0;
						} else {
							w80 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 3651) {
				if (hops < 3) {
					if (hops < 2) {
						w80 = 0;
					} else {
						w80 = 0;
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w80 = 0;
						} else {
							w80 = -256;
						}
					} else {
						w80 = 0;
					}
				}
			} else {
				if (rel_time < 3943) {
					if (hops < 3) {
						if (hops < 2) {
							w80 = 0;
						} else {
							w80 = 0;
						}
					} else {
						if (hops < 4) {
							w80 = 256;
						} else {
							w80 = 256;
						}
					}
				} else {
					if (rel_time < 4219) {
						if (hops < 2) {
							w80 = 0;
						} else {
							w80 = -256;
						}
					} else {
						if (rel_time < 4496) {
							w80 = 0;
						} else {
							w80 = 0;
						}
					}
				}
			}
		}
	} else {
		if (prod == 3) {
			if (rel_time < 10356) {
				if (hops < 3) {
					if (hops < 2) {
						w80 = 0;
					} else {
						w80 = 0;
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w80 = 0;
						} else {
							w80 = 0;
						}
					} else {
						w80 = 0;
					}
				}
			} else {
				if (hops < 5) {
					if (hops < 4) {
						if (hops < 2) {
							w80 = 0;
						} else {
							w80 = 0;
						}
					} else {
						w80 = 0;
					}
				} else {
					w80 = 0;
				}
			}
		} else {
			if (rel_time < 10356) {
				if (hops < 2) {
					w80 = 0;
				} else {
					if (hops < 3) {
						w80 = 0;
					} else {
						w80 = 0;
					}
				}
			} else {
				if (hops < 5) {
					if (hops < 4) {
						if (hops < 2) {
							w80 = 0;
						} else {
							w80 = 0;
						}
					} else {
						w80 = 0;
					}
				} else {
					w80 = 0;
				}
			}
		}
	}
	int w81;
	if (rel_time < 7087) {
		if (prod == 3) {
			if (rel_time < 6991) {
				if (rel_time < 6714) {
					if (rel_time < 6391) {
						if (rel_time < 6161) {
							w81 = 0;
						} else {
							w81 = 0;
						}
					} else {
						if (prod == 0) {
							w81 = 0;
						} else {
							w81 = 0;
						}
					}
				} else {
					if (prod == 1) {
						if (rel_time < 6812) {
							w81 = 0;
						} else {
							w81 = 0;
						}
					} else {
						if (rel_time < 6943) {
							w81 = -512;
						} else {
							w81 = 0;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						if (rel_time < 7037) {
							w81 = 0;
						} else {
							w81 = 0;
						}
					} else {
						if (rel_time < 7037) {
							w81 = 0;
						} else {
							w81 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (rel_time < 7037) {
							w81 = 0;
						} else {
							w81 = 0;
						}
					} else {
						if (rel_time < 7037) {
							w81 = 0;
						} else {
							w81 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 6812) {
				if (rel_time < 6761) {
					if (rel_time < 6345) {
						if (rel_time < 6209) {
							w81 = 0;
						} else {
							w81 = 768;
						}
					} else {
						if (rel_time < 6621) {
							w81 = -256;
						} else {
							w81 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 3) {
							w81 = 256;
						} else {
							w81 = 256;
						}
					} else {
						w81 = 0;
					}
				}
			} else {
				if (rel_time < 7037) {
					if (hops < 3) {
						if (hops < 2) {
							w81 = 0;
						} else {
							w81 = 0;
						}
					} else {
						w81 = 0;
					}
				} else {
					if (hops < 5) {
						if (hops < 3) {
							w81 = -256;
						} else {
							w81 = -512;
						}
					} else {
						w81 = -256;
					}
				}
			}
		}
	} else {
		if (rel_time < 7220) {
			if (prod == 1) {
				if (prod == 0) {
					if (hops < 4) {
						if (hops < 2) {
							w81 = 0;
						} else {
							w81 = 0;
						}
					} else {
						if (hops < 5) {
							w81 = 0;
						} else {
							w81 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w81 = 0;
						} else {
							w81 = 0;
						}
					} else {
						if (hops < 5) {
							w81 = 0;
						} else {
							w81 = 0;
						}
					}
				}
			} else {
				w81 = 768;
			}
		} else {
			if (prod == 3) {
				if (rel_time < 7361) {
					if (prod == 1) {
						if (rel_time < 7314) {
							w81 = 0;
						} else {
							w81 = 0;
						}
					} else {
						if (hops < 5) {
							w81 = 0;
						} else {
							w81 = 256;
						}
					}
				} else {
					if (rel_time < 7636) {
						if (prod == 2) {
							w81 = 0;
						} else {
							w81 = 0;
						}
					} else {
						if (rel_time < 8092) {
							w81 = 0;
						} else {
							w81 = 0;
						}
					}
				}
			} else {
				if (rel_time < 7361) {
					if (rel_time < 7314) {
						if (hops < 3) {
							w81 = 256;
						} else {
							w81 = 256;
						}
					} else {
						if (hops < 4) {
							w81 = 0;
						} else {
							w81 = 0;
						}
					}
				} else {
					if (rel_time < 7636) {
						if (hops < 4) {
							w81 = 0;
						} else {
							w81 = 0;
						}
					} else {
						if (rel_time < 7913) {
							w81 = 0;
						} else {
							w81 = 0;
						}
					}
				}
			}
		}
	}
	int w82;
	if (rel_time < 3299) {
		if (rel_time < 3152) {
			if (rel_time < 3004) {
				if (rel_time < 2975) {
					if (rel_time < 2857) {
						if (rel_time < 2827) {
							w82 = 0;
						} else {
							w82 = 0;
						}
					} else {
						if (cons == 2) {
							w82 = 0;
						} else {
							w82 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w82 = 0;
					} else {
						if (hops < 4) {
							w82 = 0;
						} else {
							w82 = 0;
						}
					}
				}
			} else {
				if (rel_time < 3033) {
					if (hops < 2) {
						w82 = 0;
					} else {
						if (hops < 3) {
							w82 = 256;
						} else {
							w82 = 0;
						}
					}
				} else {
					if (cons == 3) {
						if (rel_time < 3122) {
							w82 = 0;
						} else {
							w82 = 0;
						}
					} else {
						if (hops < 3) {
							w82 = 0;
						} else {
							w82 = 0;
						}
					}
				}
			}
		} else {
			if (cons == 4) {
				if (hops < 4) {
					if (cons == 2) {
						if (hops < 2) {
							w82 = 0;
						} else {
							w82 = 0;
						}
					} else {
						if (hops < 3) {
							w82 = 0;
						} else {
							w82 = 0;
						}
					}
				} else {
					if (cons == 2) {
						if (cons == 3) {
							w82 = 0;
						} else {
							w82 = 0;
						}
					} else {
						if (hops < 5) {
							w82 = 0;
						} else {
							w82 = 0;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w82 = 0;
					} else {
						w82 = 0;
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w82 = 0;
						} else {
							w82 = 0;
						}
					} else {
						w82 = 0;
					}
				}
			}
		}
	} else {
		if (rel_time < 3387) {
			if (cons == 2) {
				if (hops < 4) {
					if (hops < 2) {
						if (rel_time < 3328) {
							w82 = 0;
						} else {
							w82 = 0;
						}
					} else {
						if (rel_time < 3328) {
							w82 = 0;
						} else {
							w82 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (rel_time < 3328) {
							w82 = 0;
						} else {
							w82 = 0;
						}
					} else {
						if (rel_time < 3328) {
							w82 = 0;
						} else {
							w82 = 0;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 3) {
						if (hops < 2) {
							w82 = 0;
						} else {
							w82 = 0;
						}
					} else {
						w82 = 0;
					}
				} else {
					if (hops < 5) {
						w82 = 0;
					} else {
						w82 = 0;
					}
				}
			}
		} else {
			if (cons == 2) {
				if (cons == 0) {
					if (rel_time < 3467) {
						if (hops < 3) {
							w82 = 0;
						} else {
							w82 = 0;
						}
					} else {
						if (cons == 4) {
							w82 = 0;
						} else {
							w82 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w82 = 0;
						} else {
							w82 = 0;
						}
					} else {
						if (hops < 5) {
							w82 = 0;
						} else {
							w82 = 0;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 3) {
						if (hops < 2) {
							w82 = 0;
						} else {
							w82 = 0;
						}
					} else {
						w82 = 0;
					}
				} else {
					w82 = 0;
				}
			}
		}
	}
	int w83;
	if (rel_time < 5966) {
		if (rel_time < 5692) {
			if (rel_time < 5517) {
				if (rel_time < 5139) {
					if (rel_time < 4863) {
						if (rel_time < 4817) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					} else {
						if (prod == 1) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					}
				} else {
					if (prod == 2) {
						if (prod == 1) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					} else {
						if (rel_time < 5334) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					}
				}
			} else {
				if (prod == 2) {
					if (prod == 0) {
						if (prod == 4) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					} else {
						if (hops < 5) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					}
				} else {
					if (rel_time < 5610) {
						if (hops < 3) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					} else {
						if (hops < 3) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					}
				}
			}
		} else {
			if (prod == 1) {
				if (prod == 3) {
					if (prod == 4) {
						if (rel_time < 5838) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					} else {
						if (hops < 5) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w83 = 0;
					} else {
						if (hops < 5) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					if (rel_time < 5838) {
						w83 = 0;
					} else {
						w83 = 0;
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					} else {
						w83 = 0;
					}
				}
			}
		}
	} else {
		if (rel_time < 6115) {
			if (prod == 1) {
				if (prod == 0) {
					if (hops < 2) {
						w83 = 0;
					} else {
						if (hops < 5) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (rel_time < 6069) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					} else {
						if (rel_time < 6069) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w83 = 256;
				} else {
					if (hops < 3) {
						w83 = 0;
					} else {
						w83 = 256;
					}
				}
			}
		} else {
			if (hops < 3) {
				if (hops < 2) {
					if (rel_time < 6209) {
						if (prod == 2) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					} else {
						if (prod == 1) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					}
				} else {
					if (rel_time < 6161) {
						if (prod == 1) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					} else {
						if (rel_time < 6209) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					}
				}
			} else {
				if (rel_time < 6391) {
					if (prod == 3) {
						if (prod == 0) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					} else {
						if (rel_time < 6209) {
							w83 = 0;
						} else {
							w83 = 512;
						}
					}
				} else {
					if (rel_time < 6486) {
						if (prod == 2) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					} else {
						if (hops < 4) {
							w83 = 0;
						} else {
							w83 = 0;
						}
					}
				}
			}
		}
	}
	int w84;
	if (prod == 0) {
		if (rel_time < 9494) {
			if (rel_time < 8739) {
				if (rel_time < 8465) {
					if (rel_time < 8188) {
						if (rel_time < 7818) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					} else {
						if (prod == 3) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					}
				} else {
					if (prod == 1) {
						if (prod == 2) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					} else {
						if (rel_time < 8619) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					}
				}
			} else {
				if (rel_time < 8892) {
					if (rel_time < 8842) {
						if (hops < 2) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					} else {
						if (hops < 2) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					}
				} else {
					if (rel_time < 9166) {
						if (prod == 3) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					} else {
						if (prod == 3) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 9717) {
				if (prod == 3) {
					if (rel_time < 9564) {
						if (prod == 2) {
							w84 = -1024;
						} else {
							w84 = 0;
						}
					} else {
						if (rel_time < 9667) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					} else {
						if (hops < 5) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					}
				}
			} else {
				if (prod == 4) {
					if (rel_time < 9944) {
						if (rel_time < 9825) {
							w84 = 0;
						} else {
							w84 = -512;
						}
					} else {
						if (rel_time < 10217) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					}
				} else {
					if (rel_time < 9944) {
						if (hops < 3) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					} else {
						if (rel_time < 10217) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 8619) {
			if (rel_time < 8567) {
				if (rel_time < 5286) {
					if (rel_time < 4496) {
						if (rel_time < 4219) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					} else {
						if (rel_time < 4772) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					}
				} else {
					if (rel_time < 5517) {
						if (hops < 3) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					} else {
						if (rel_time < 8092) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w84 = 256;
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w84 = 256;
						} else {
							w84 = 256;
						}
					} else {
						w84 = 256;
					}
				}
			}
		} else {
			if (rel_time < 9443) {
				if (rel_time < 8892) {
					if (rel_time < 8842) {
						if (hops < 3) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					} else {
						if (hops < 3) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					}
				} else {
					if (rel_time < 9166) {
						if (rel_time < 9118) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					} else {
						if (rel_time < 9393) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					}
				}
			} else {
				if (rel_time < 9667) {
					if (hops < 3) {
						w84 = 256;
					} else {
						w84 = 0;
					}
				} else {
					if (rel_time < 9717) {
						if (hops < 3) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					} else {
						if (rel_time < 9994) {
							w84 = 0;
						} else {
							w84 = 0;
						}
					}
				}
			}
		}
	}
	int w85;
	if (rel_time < 7087) {
		if (prod == 3) {
			if (rel_time < 6991) {
				if (rel_time < 6714) {
					if (rel_time < 6391) {
						if (rel_time < 6161) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					} else {
						if (prod == 0) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					}
				} else {
					if (prod == 2) {
						if (prod == 0) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					} else {
						if (rel_time < 6761) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						if (rel_time < 7037) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					} else {
						if (rel_time < 7037) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (rel_time < 7037) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					} else {
						if (rel_time < 7037) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 6812) {
				if (rel_time < 6761) {
					if (rel_time < 3739) {
						if (hops < 3) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					} else {
						if (rel_time < 4032) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 3) {
							w85 = 0;
						} else {
							w85 = 256;
						}
					} else {
						w85 = 0;
					}
				}
			} else {
				if (rel_time < 7037) {
					if (hops < 3) {
						if (hops < 2) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					} else {
						if (hops < 4) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 3) {
							w85 = -256;
						} else {
							w85 = -256;
						}
					} else {
						w85 = 0;
					}
				}
			}
		}
	} else {
		if (rel_time < 7220) {
			if (prod == 1) {
				if (prod == 0) {
					if (hops < 4) {
						if (hops < 2) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					} else {
						if (hops < 5) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					} else {
						if (hops < 5) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					}
				}
			} else {
				w85 = 512;
			}
		} else {
			if (prod == 3) {
				if (rel_time < 7361) {
					if (prod == 1) {
						if (rel_time < 7314) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					} else {
						if (hops < 3) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					}
				} else {
					if (rel_time < 8292) {
						if (rel_time < 8092) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					} else {
						if (rel_time < 8465) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					}
				}
			} else {
				if (rel_time < 7361) {
					if (rel_time < 7314) {
						if (hops < 4) {
							w85 = 0;
						} else {
							w85 = 256;
						}
					} else {
						if (hops < 4) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					}
				} else {
					if (rel_time < 7636) {
						if (hops < 4) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					} else {
						if (rel_time < 7913) {
							w85 = 0;
						} else {
							w85 = 0;
						}
					}
				}
			}
		}
	}
	int w86;
	if (prod == 2) {
		if (rel_time < 3898) {
			if (prod == 5) {
				if (hops < 3) {
					if (hops < 2) {
						if (prod == 0) {
							w86 = 0;
						} else {
							w86 = 0;
						}
					} else {
						if (rel_time < 3739) {
							w86 = 0;
						} else {
							w86 = 256;
						}
					}
				} else {
					if (rel_time < 3607) {
						if (hops < 4) {
							w86 = 0;
						} else {
							w86 = 0;
						}
					} else {
						if (hops < 5) {
							w86 = 0;
						} else {
							w86 = 0;
						}
					}
				}
			} else {
				if (rel_time < 3299) {
					if (rel_time < 3152) {
						if (rel_time < 3004) {
							w86 = 0;
						} else {
							w86 = 0;
						}
					} else {
						if (cons == 4) {
							w86 = 0;
						} else {
							w86 = 0;
						}
					}
				} else {
					if (rel_time < 3328) {
						if (hops < 4) {
							w86 = 0;
						} else {
							w86 = 0;
						}
					} else {
						if (cons == 1) {
							w86 = 0;
						} else {
							w86 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 3987) {
				if (hops < 3) {
					if (rel_time < 3943) {
						if (hops < 2) {
							w86 = 0;
						} else {
							w86 = 0;
						}
					} else {
						if (hops < 2) {
							w86 = 0;
						} else {
							w86 = 0;
						}
					}
				} else {
					if (hops < 4) {
						w86 = 0;
					} else {
						if (hops < 5) {
							w86 = 0;
						} else {
							w86 = 0;
						}
					}
				}
			} else {
				if (rel_time < 4032) {
					if (prod == 3) {
						if (hops < 2) {
							w86 = 0;
						} else {
							w86 = 0;
						}
					} else {
						if (hops < 2) {
							w86 = 0;
						} else {
							w86 = 0;
						}
					}
				} else {
					if (rel_time < 4309) {
						if (prod == 0) {
							w86 = 0;
						} else {
							w86 = 0;
						}
					} else {
						if (rel_time < 4541) {
							w86 = 0;
						} else {
							w86 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 3695) {
			if (hops < 3) {
				if (hops < 2) {
					w86 = 0;
				} else {
					w86 = 256;
				}
			} else {
				if (hops < 4) {
					w86 = 0;
				} else {
					if (hops < 5) {
						w86 = 0;
					} else {
						w86 = 0;
					}
				}
			}
		} else {
			if (rel_time < 3987) {
				if (rel_time < 3943) {
					if (hops < 2) {
						w86 = -256;
					} else {
						if (hops < 3) {
							w86 = -256;
						} else {
							w86 = -256;
						}
					}
				} else {
					if (hops < 2) {
						w86 = 0;
					} else {
						if (hops < 3) {
							w86 = 0;
						} else {
							w86 = 0;
						}
					}
				}
			} else {
				if (rel_time < 4264) {
					if (hops < 2) {
						if (rel_time < 4219) {
							w86 = 0;
						} else {
							w86 = 0;
						}
					} else {
						if (hops < 5) {
							w86 = 0;
						} else {
							w86 = 0;
						}
					}
				} else {
					if (rel_time < 4541) {
						if (hops < 3) {
							w86 = 0;
						} else {
							w86 = 0;
						}
					} else {
						if (rel_time < 4817) {
							w86 = 0;
						} else {
							w86 = 0;
						}
					}
				}
			}
		}
	}
	int w87;
	if (rel_time < 4863) {
		if (rel_time < 4686) {
			if (prod == 1) {
				if (rel_time < 4264) {
					if (rel_time < 4132) {
						if (prod == 4) {
							w87 = 0;
						} else {
							w87 = 0;
						}
					} else {
						if (prod == 3) {
							w87 = 0;
						} else {
							w87 = -256;
						}
					}
				} else {
					if (prod == 2) {
						if (rel_time < 4496) {
							w87 = 0;
						} else {
							w87 = 0;
						}
					} else {
						if (rel_time < 4496) {
							w87 = 0;
						} else {
							w87 = 0;
						}
					}
				}
			} else {
				if (rel_time < 4219) {
					if (rel_time < 3943) {
						if (rel_time < 3651) {
							w87 = 0;
						} else {
							w87 = 0;
						}
					} else {
						if (hops < 2) {
							w87 = 0;
						} else {
							w87 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 3) {
							w87 = 0;
						} else {
							w87 = 0;
						}
					} else {
						w87 = 0;
					}
				}
			}
		} else {
			if (prod == 1) {
				if (prod == 3) {
					if (prod == 2) {
						if (hops < 2) {
							w87 = 0;
						} else {
							w87 = 0;
						}
					} else {
						if (hops < 2) {
							w87 = 0;
						} else {
							w87 = 0;
						}
					}
				} else {
					if (rel_time < 4817) {
						w87 = -512;
					} else {
						if (hops < 2) {
							w87 = 0;
						} else {
							w87 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w87 = 0;
				} else {
					if (hops < 3) {
						w87 = 0;
					} else {
						w87 = 0;
					}
				}
			}
		}
	} else {
		if (rel_time < 5009) {
			if (prod == 0) {
				if (hops < 4) {
					if (hops < 2) {
						w87 = 0;
					} else {
						if (rel_time < 4963) {
							w87 = 0;
						} else {
							w87 = 0;
						}
					}
				} else {
					if (hops < 5) {
						w87 = 0;
					} else {
						if (rel_time < 4963) {
							w87 = 0;
						} else {
							w87 = 0;
						}
					}
				}
			} else {
				if (rel_time < 4963) {
					if (hops < 3) {
						if (hops < 2) {
							w87 = 0;
						} else {
							w87 = 0;
						}
					} else {
						w87 = 0;
					}
				} else {
					if (hops < 5) {
						if (hops < 3) {
							w87 = 0;
						} else {
							w87 = 0;
						}
					} else {
						w87 = 0;
					}
				}
			}
		} else {
			if (rel_time < 5094) {
				if (prod == 2) {
					if (hops < 2) {
						if (prod == 1) {
							w87 = 256;
						} else {
							w87 = 0;
						}
					} else {
						if (prod == 1) {
							w87 = 0;
						} else {
							w87 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w87 = 0;
						} else {
							w87 = 0;
						}
					} else {
						if (hops < 5) {
							w87 = 0;
						} else {
							w87 = 0;
						}
					}
				}
			} else {
				if (rel_time < 5139) {
					if (hops < 2) {
						if (prod == 3) {
							w87 = 0;
						} else {
							w87 = 0;
						}
					} else {
						if (prod == 3) {
							w87 = 0;
						} else {
							w87 = 0;
						}
					}
				} else {
					if (rel_time < 5240) {
						if (prod == 0) {
							w87 = 0;
						} else {
							w87 = 0;
						}
					} else {
						if (rel_time < 5692) {
							w87 = 0;
						} else {
							w87 = 0;
						}
					}
				}
			}
		}
	}
	int w88;
	if (rel_time < 1382) {
		if (rel_time < 1234) {
			if (rel_time < 1126) {
				if (rel_time < 1078) {
					if (rel_time < 1029) {
						if (rel_time < 981) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					} else {
						if (hops < 4) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					} else {
						if (hops < 4) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					}
				}
			} else {
				if (cons == 4) {
					if (rel_time < 1205) {
						if (hops < 2) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					} else {
						if (hops < 2) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					} else {
						if (hops < 4) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					}
				}
			}
		} else {
			if (cons == 4) {
				if (cons == 2) {
					if (cons == 0) {
						if (hops < 2) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					} else {
						if (hops < 3) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					} else {
						if (hops < 5) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w88 = 0;
				} else {
					if (hops < 3) {
						w88 = 0;
					} else {
						if (hops < 4) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 1529) {
			if (cons == 2) {
				if (rel_time < 1469) {
					if (hops < 2) {
						if (rel_time < 1411) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					} else {
						if (hops < 4) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 3) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					} else {
						if (cons == 0) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w88 = 0;
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					} else {
						if (hops < 5) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 1559) {
				if (hops < 4) {
					if (hops < 3) {
						w88 = 0;
					} else {
						w88 = 0;
					}
				} else {
					if (hops < 5) {
						w88 = 0;
					} else {
						w88 = 0;
					}
				}
			} else {
				if (rel_time < 1588) {
					if (hops < 4) {
						if (hops < 2) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					} else {
						w88 = 0;
					}
				} else {
					if (rel_time < 1617) {
						if (hops < 2) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					} else {
						if (cons == 1) {
							w88 = 0;
						} else {
							w88 = 0;
						}
					}
				}
			}
		}
	}
	int w89;
	if (cons == 2) {
		if (rel_time < 2857) {
			if (rel_time < 2709) {
				if (rel_time < 2680) {
					if (rel_time < 2649) {
						if (rel_time < 2562) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					} else {
						if (hops < 2) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w89 = 0;
					} else {
						if (hops < 4) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					}
				}
			} else {
				if (cons == 3) {
					if (cons == 4) {
						if (hops < 2) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					} else {
						if (hops < 2) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					} else {
						w89 = 256;
					}
				}
			}
		} else {
			if (rel_time < 2944) {
				if (rel_time < 2886) {
					if (hops < 5) {
						if (hops < 2) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					} else {
						w89 = 0;
					}
				} else {
					if (hops < 5) {
						if (hops < 3) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					} else {
						w89 = 0;
					}
				}
			} else {
				if (rel_time < 2975) {
					if (hops < 4) {
						if (hops < 2) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					} else {
						if (hops < 5) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					}
				} else {
					if (rel_time < 3004) {
						if (hops < 2) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					} else {
						if (rel_time < 3033) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 2797) {
			if (rel_time < 2649) {
				if (rel_time < 2473) {
					if (rel_time < 1735) {
						if (rel_time < 1588) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					} else {
						if (rel_time < 1883) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w89 = 0;
					} else {
						if (hops < 3) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w89 = 0;
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					} else {
						w89 = -256;
					}
				}
			}
		} else {
			if (rel_time < 2944) {
				if (hops < 5) {
					if (hops < 4) {
						if (hops < 3) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					} else {
						w89 = 0;
					}
				} else {
					w89 = 0;
				}
			} else {
				if (rel_time < 3063) {
					if (hops < 3) {
						if (hops < 2) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					} else {
						if (hops < 4) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (rel_time < 3357) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					} else {
						if (rel_time < 3357) {
							w89 = 0;
						} else {
							w89 = 0;
						}
					}
				}
			}
		}
	}
	int w90;
	if (rel_time < 5966) {
		if (rel_time < 5692) {
			if (rel_time < 5517) {
				if (rel_time < 5139) {
					if (prod == 2) {
						if (rel_time < 4863) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					} else {
						if (rel_time < 3695) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					}
				} else {
					if (prod == 1) {
						if (prod == 3) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					} else {
						if (hops < 5) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					}
				}
			} else {
				if (prod == 1) {
					if (prod == 3) {
						if (rel_time < 5610) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					} else {
						if (hops < 2) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 3) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					} else {
						w90 = 0;
					}
				}
			}
		} else {
			if (prod == 1) {
				if (prod == 2) {
					if (prod == 0) {
						if (hops < 2) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					} else {
						if (hops < 3) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					}
				} else {
					if (hops < 2) {
						if (rel_time < 5885) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					} else {
						if (hops < 5) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					if (rel_time < 5838) {
						w90 = 0;
					} else {
						w90 = 0;
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					} else {
						w90 = 0;
					}
				}
			}
		}
	} else {
		if (rel_time < 6345) {
			if (prod == 3) {
				if (prod == 1) {
					if (rel_time < 6069) {
						if (prod == 0) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					} else {
						if (prod == 0) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					}
				} else {
					if (hops < 2) {
						if (rel_time < 6115) {
							w90 = 256;
						} else {
							w90 = 0;
						}
					} else {
						if (rel_time < 6115) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					}
				}
			} else {
				if (rel_time < 6209) {
					if (hops < 5) {
						if (hops < 3) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					} else {
						w90 = 0;
					}
				} else {
					if (hops < 3) {
						w90 = 512;
					} else {
						if (hops < 5) {
							w90 = 256;
						} else {
							w90 = 256;
						}
					}
				}
			}
		} else {
			if (rel_time < 6486) {
				if (prod == 1) {
					if (prod == 3) {
						if (hops < 3) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					} else {
						if (hops < 5) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					}
				} else {
					if (rel_time < 6391) {
						if (hops < 3) {
							w90 = -256;
						} else {
							w90 = -256;
						}
					} else {
						if (hops < 5) {
							w90 = 0;
						} else {
							w90 = -256;
						}
					}
				}
			} else {
				if (rel_time < 6621) {
					if (prod == 4) {
						if (prod == 0) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					} else {
						if (hops < 2) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (prod == 0) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					} else {
						if (hops < 4) {
							w90 = 0;
						} else {
							w90 = 0;
						}
					}
				}
			}
		}
	}
	int w91;
	if (hops < 4) {
		if (rel_time < 8139) {
			if (rel_time < 8092) {
				if (rel_time < 7818) {
					if (rel_time < 7742) {
						if (rel_time < 7087) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					} else {
						if (prod == 1) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					}
				} else {
					if (prod == 4) {
						if (prod == 2) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					} else {
						if (hops < 3) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					}
				}
			} else {
				if (prod == 2) {
					if (hops < 2) {
						w91 = -768;
					} else {
						w91 = -768;
					}
				} else {
					if (hops < 2) {
						w91 = 0;
					} else {
						if (hops < 3) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 8415) {
				if (prod == 4) {
					if (rel_time < 8346) {
						if (prod == 1) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					} else {
						if (prod == 3) {
							w91 = 0;
						} else {
							w91 = 768;
						}
					}
				} else {
					if (rel_time < 8188) {
						if (hops < 2) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					} else {
						if (hops < 3) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					}
				}
			} else {
				if (rel_time < 8619) {
					if (prod == 0) {
						if (prod == 3) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					} else {
						if (rel_time < 8567) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					}
				} else {
					if (prod == 0) {
						if (rel_time < 8892) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					} else {
						if (rel_time < 9443) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					}
				}
			}
		}
	} else {
		if (cons == 3) {
			if (cons == 4) {
				if (cons == 1) {
					if (prod == 0) {
						if (rel_time < 7541) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					} else {
						if (rel_time < 4219) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					}
				} else {
					if (rel_time < 2325) {
						if (rel_time < 1854) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					} else {
						if (rel_time < 2738) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					}
				}
			} else {
				if (rel_time < 2385) {
					if (rel_time < 2237) {
						if (rel_time < 734) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					} else {
						if (hops < 5) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					}
				} else {
					if (rel_time < 2827) {
						if (rel_time < 2680) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					} else {
						if (rel_time < 2975) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 2649) {
				if (rel_time < 1353) {
					if (rel_time < 318) {
						if (hops < 5) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					} else {
						if (rel_time < 1205) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					}
				} else {
					if (rel_time < 1764) {
						if (rel_time < 1617) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					} else {
						if (rel_time < 1912) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					}
				}
			} else {
				if (rel_time < 2797) {
					w91 = 0;
				} else {
					if (rel_time < 3387) {
						if (rel_time < 2944) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					} else {
						if (hops < 5) {
							w91 = 0;
						} else {
							w91 = 0;
						}
					}
				}
			}
		}
	}
	int w92;
	if (rel_time < 9443) {
		if (rel_time < 9393) {
			if (prod == 3) {
				if (rel_time < 9219) {
					if (rel_time < 8292) {
						if (rel_time < 8092) {
							w92 = 0;
						} else {
							w92 = 0;
						}
					} else {
						if (rel_time < 8465) {
							w92 = 0;
						} else {
							w92 = 0;
						}
					}
				} else {
					if (rel_time < 9290) {
						if (prod == 2) {
							w92 = 0;
						} else {
							w92 = 256;
						}
					} else {
						if (prod == 0) {
							w92 = 0;
						} else {
							w92 = 0;
						}
					}
				}
			} else {
				if (rel_time < 3739) {
					if (hops < 4) {
						if (hops < 2) {
							w92 = 0;
						} else {
							w92 = 0;
						}
					} else {
						if (hops < 5) {
							w92 = 0;
						} else {
							w92 = 0;
						}
					}
				} else {
					if (rel_time < 4032) {
						if (rel_time < 3987) {
							w92 = 0;
						} else {
							w92 = 0;
						}
					} else {
						if (rel_time < 4309) {
							w92 = 0;
						} else {
							w92 = 0;
						}
					}
				}
			}
		} else {
			if (prod == 0) {
				if (hops < 2) {
					w92 = 0;
				} else {
					if (hops < 3) {
						w92 = 0;
					} else {
						if (hops < 4) {
							w92 = 0;
						} else {
							w92 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					w92 = 0;
				} else {
					if (hops < 3) {
						w92 = 0;
					} else {
						if (hops < 5) {
							w92 = 0;
						} else {
							w92 = 0;
						}
					}
				}
			}
		}
	} else {
		if (prod == 0) {
			if (prod == 3) {
				if (rel_time < 9717) {
					if (rel_time < 9494) {
						if (prod == 1) {
							w92 = 0;
						} else {
							w92 = 0;
						}
					} else {
						if (rel_time < 9564) {
							w92 = 0;
						} else {
							w92 = 0;
						}
					}
				} else {
					if (rel_time < 9994) {
						if (rel_time < 9768) {
							w92 = 0;
						} else {
							w92 = 0;
						}
					} else {
						if (rel_time < 10264) {
							w92 = 0;
						} else {
							w92 = 0;
						}
					}
				}
			} else {
				if (hops < 2) {
					if (rel_time < 9564) {
						w92 = 0;
					} else {
						if (rel_time < 9944) {
							w92 = 0;
						} else {
							w92 = 0;
						}
					}
				} else {
					if (rel_time < 10217) {
						if (rel_time < 10096) {
							w92 = 0;
						} else {
							w92 = 0;
						}
					} else {
						if (rel_time < 10356) {
							w92 = 0;
						} else {
							w92 = 0;
						}
					}
				}
			}
		} else {
			if (rel_time < 9667) {
				if (hops < 3) {
					if (hops < 2) {
						w92 = 0;
					} else {
						w92 = 0;
					}
				} else {
					w92 = 0;
				}
			} else {
				if (rel_time < 9717) {
					if (hops < 3) {
						if (hops < 2) {
							w92 = 0;
						} else {
							w92 = 0;
						}
					} else {
						if (hops < 4) {
							w92 = 0;
						} else {
							w92 = 0;
						}
					}
				} else {
					if (rel_time < 9994) {
						if (hops < 3) {
							w92 = 0;
						} else {
							w92 = 0;
						}
					} else {
						if (rel_time < 10217) {
							w92 = 0;
						} else {
							w92 = 0;
						}
					}
				}
			}
		}
	}
	return (12800 + w0 + w1 + w2 + w3 + w4 + w5 + w6 + w7 + w8 + w9 + w10 + w11 + w12 + w13 + w14 + w15 + w16 + w17 + w18 + w19 + w20 + w21 + w22 + w23 + w24 + w25 + w26 + w27 + w28 + w29 + w30 + w31 + w32 + w33 + w34 + w35 + w36 + w37 + w38 + w39 + w40 + w41 + w42 + w43 + w44 + w45 + w46 + w47 + w48 + w49 + w50 + w51 + w52 + w53 + w54 + w55 + w56 + w57 + w58 + w59 + w60 + w61 + w62 + w63 + w64 + w65 + w66 + w67 + w68 + w69 + w70 + w71 + w72 + w73 + w74 + w75 + w76 + w77 + w78 + w79 + w80 + w81 + w82 + w83 + w84 + w85 + w86 + w87 + w88 + w89 + w90 + w91 + w92) >> 8;
}
