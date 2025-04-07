#include <stdbool.h>

int model(int rel_time, int hops, int size, int prod, int cons)
{
	int w0;
	if (size < 141) {
		if (rel_time < 108532) {
			if (prod == 1) {
				if (hops < 3) {
					if (hops < 2) {
						w0 = 169666;
					} else {
						w0 = 171759;
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w0 = 173910;
						} else {
							w0 = 175507;
						}
					} else {
						w0 = 178323;
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w0 = 137945;
					} else {
						w0 = 140181;
					}
				} else {
					if (hops < 4) {
						w0 = 142344;
					} else {
						if (hops < 5) {
							w0 = 144484;
						} else {
							w0 = 146986;
						}
					}
				}
			}
		} else {
			if (prod == 0) {
				if (hops < 3) {
					if (hops < 2) {
						w0 = 137956;
					} else {
						w0 = 140119;
					}
				} else {
					if (hops < 4) {
						w0 = 142293;
					} else {
						if (hops < 5) {
							w0 = 144376;
						} else {
							w0 = 146889;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w0 = 142998;
					} else {
						w0 = 145042;
					}
				} else {
					if (hops < 4) {
						w0 = 147175;
					} else {
						if (hops < 5) {
							w0 = 149416;
						} else {
							w0 = 152015;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 53140) {
			if (hops < 3) {
				if (hops < 2) {
					w0 = 189227;
				} else {
					w0 = 191535;
				}
			} else {
				if (hops < 4) {
					w0 = 193626;
				} else {
					if (hops < 5) {
						w0 = 195670;
					} else {
						w0 = 198223;
					}
				}
			}
		} else {
			if (hops < 3) {
				if (hops < 2) {
					w0 = 162568;
				} else {
					w0 = 164823;
				}
			} else {
				if (hops < 4) {
					w0 = 166885;
				} else {
					if (hops < 5) {
						w0 = 168972;
					} else {
						if (hops < 6) {
							w0 = 171329;
						} else {
							w0 = 173305;
						}
					}
				}
			}
		}
	}
	int w1;
	if (size < 141) {
		if (rel_time < 108532) {
			if (prod == 1) {
				if (hops < 3) {
					if (hops < 2) {
						w1 = 118767;
					} else {
						w1 = 120232;
					}
				} else {
					if (hops < 5) {
						if (rel_time < 66890) {
							w1 = 122440;
						} else {
							w1 = 120777;
						}
					} else {
						w1 = 124829;
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w1 = 96563;
					} else {
						w1 = 98128;
					}
				} else {
					if (hops < 4) {
						w1 = 99642;
					} else {
						if (hops < 5) {
							w1 = 101141;
						} else {
							w1 = 102895;
						}
					}
				}
			}
		} else {
			if (prod == 0) {
				if (hops < 3) {
					if (hops < 2) {
						w1 = 96569;
					} else {
						if (prod == 1) {
							w1 = 97970;
						} else {
							w1 = 98198;
						}
					}
				} else {
					if (hops < 4) {
						w1 = 99605;
					} else {
						if (hops < 5) {
							w1 = 101063;
						} else {
							w1 = 102822;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w1 = 100098;
					} else {
						w1 = 101530;
					}
				} else {
					if (hops < 4) {
						w1 = 103022;
					} else {
						if (hops < 5) {
							w1 = 104591;
						} else {
							w1 = 106411;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 53140) {
			if (hops < 3) {
				if (hops < 2) {
					w1 = 132461;
				} else {
					w1 = 134077;
				}
			} else {
				if (hops < 4) {
					w1 = 135540;
				} else {
					if (hops < 5) {
						w1 = 136972;
					} else {
						w1 = 138763;
					}
				}
			}
		} else {
			if (hops < 3) {
				if (hops < 2) {
					w1 = 113798;
				} else {
					w1 = 115376;
				}
			} else {
				if (hops < 4) {
					w1 = 116819;
				} else {
					if (hops < 5) {
						w1 = 118281;
					} else {
						if (hops < 6) {
							w1 = 119931;
						} else {
							w1 = 121315;
						}
					}
				}
			}
		}
	}
	int w2;
	if (size < 141) {
		if (rel_time < 108532) {
			if (prod == 1) {
				if (hops < 3) {
					if (hops < 2) {
						w2 = 83138;
					} else {
						w2 = 84163;
					}
				} else {
					if (hops < 4) {
						w2 = 85078;
					} else {
						if (rel_time < 66890) {
							w2 = 87056;
						} else {
							w2 = 84129;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w2 = 67595;
					} else {
						w2 = 68690;
					}
				} else {
					if (hops < 4) {
						w2 = 69751;
					} else {
						if (hops < 6) {
							w2 = 71047;
						} else {
							w2 = 73705;
						}
					}
				}
			}
		} else {
			if (prod == 0) {
				if (hops < 3) {
					if (hops < 2) {
						w2 = 67598;
					} else {
						if (prod == 1) {
							w2 = 68579;
						} else {
							w2 = 68739;
						}
					}
				} else {
					if (hops < 4) {
						w2 = 69724;
					} else {
						if (hops < 6) {
							w2 = 70983;
						} else {
							w2 = 73804;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w2 = 70069;
					} else {
						w2 = 71071;
					}
				} else {
					if (hops < 4) {
						w2 = 72116;
					} else {
						if (hops < 6) {
							w2 = 73470;
						} else {
							w2 = 76211;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 53140) {
			if (hops < 3) {
				if (hops < 2) {
					w2 = 92725;
				} else {
					w2 = 93855;
				}
			} else {
				if (hops < 4) {
					w2 = 94879;
				} else {
					if (hops < 6) {
						w2 = 96141;
					} else {
						w2 = 98901;
					}
				}
			}
		} else {
			if (hops < 3) {
				if (hops < 2) {
					w2 = 79659;
				} else {
					w2 = 80763;
				}
			} else {
				if (hops < 4) {
					w2 = 81774;
				} else {
					if (hops < 5) {
						w2 = 82797;
					} else {
						if (hops < 6) {
							w2 = 83952;
						} else {
							w2 = 84922;
						}
					}
				}
			}
		}
	}
	int w3;
	if (size < 141) {
		if (rel_time < 108532) {
			if (prod == 1) {
				if (hops < 3) {
					if (hops < 2) {
						w3 = 58197;
					} else {
						w3 = 58915;
					}
				} else {
					if (hops < 5) {
						if (prod == 0) {
							w3 = 59470;
						} else {
							w3 = 60193;
						}
					} else {
						if (hops < 6) {
							w3 = 60998;
						} else {
							w3 = 63405;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w3 = 47318;
					} else {
						w3 = 48084;
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w3 = 48826;
						} else {
							w3 = 49487;
						}
					} else {
						w3 = 50584;
					}
				}
			}
		} else {
			if (prod == 0) {
				if (hops < 3) {
					if (hops < 2) {
						w3 = 47319;
					} else {
						if (prod == 1) {
							w3 = 48005;
						} else {
							w3 = 48117;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w3 = 48807;
						} else {
							w3 = 49449;
						}
					} else {
						if (hops < 6) {
							w3 = 50311;
						} else {
							w3 = 51663;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w3 = 49048;
					} else {
						w3 = 49750;
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w3 = 50481;
						} else {
							w3 = 51173;
						}
					} else {
						if (hops < 6) {
							w3 = 52096;
						} else {
							w3 = 53349;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 53140) {
			if (hops < 3) {
				if (hops < 2) {
					w3 = 64908;
				} else {
					w3 = 65699;
				}
			} else {
				if (hops < 5) {
					if (hops < 4) {
						w3 = 66417;
					} else {
						w3 = 67042;
					}
				} else {
					w3 = 68166;
				}
			}
		} else {
			if (hops < 3) {
				if (hops < 2) {
					w3 = 55761;
				} else {
					w3 = 56534;
				}
			} else {
				if (hops < 4) {
					w3 = 57242;
				} else {
					if (hops < 5) {
						w3 = 57958;
					} else {
						if (hops < 6) {
							w3 = 58766;
						} else {
							w3 = 59446;
						}
					}
				}
			}
		}
	}
	int w4;
	if (size < 141) {
		if (rel_time < 108532) {
			if (prod == 1) {
				if (hops < 4) {
					if (hops < 2) {
						w4 = 40738;
					} else {
						if (hops < 3) {
							w4 = 41241;
						} else {
							w4 = 41606;
						}
					}
				} else {
					if (rel_time < 66890) {
						if (hops < 6) {
							w4 = 42776;
						} else {
							w4 = 44249;
						}
					} else {
						if (prod == 0) {
							w4 = 12474;
						} else {
							w4 = 44054;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w4 = 33123;
					} else {
						w4 = 33659;
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w4 = 34179;
						} else {
							w4 = 34642;
						}
					} else {
						if (hops < 6) {
							w4 = 35197;
						} else {
							w4 = 36443;
						}
					}
				}
			}
		} else {
			if (prod == 0) {
				if (hops < 3) {
					if (hops < 2) {
						if (prod == 1) {
							w4 = 33083;
						} else {
							w4 = 33163;
						}
					} else {
						if (prod == 1) {
							w4 = 33604;
						} else {
							w4 = 33682;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w4 = 34165;
						} else {
							w4 = 34615;
						}
					} else {
						if (hops < 6) {
							w4 = 35218;
						} else {
							w4 = 36164;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w4 = 34334;
					} else {
						w4 = 34825;
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w4 = 35337;
						} else {
							w4 = 35821;
						}
					} else {
						if (hops < 6) {
							w4 = 36467;
						} else {
							w4 = 37345;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 53140) {
			if (hops < 3) {
				if (hops < 2) {
					w4 = 45437;
				} else {
					w4 = 45990;
				}
			} else {
				if (hops < 5) {
					if (hops < 4) {
						w4 = 46492;
					} else {
						w4 = 46930;
					}
				} else {
					w4 = 47719;
				}
			}
		} else {
			if (hops < 3) {
				if (hops < 2) {
					w4 = 39033;
				} else {
					if (rel_time < 995684) {
						if (rel_time < 940336) {
							w4 = 39575;
						} else {
							w4 = 39332;
						}
					} else {
						w4 = 39797;
					}
				}
			} else {
				if (hops < 4) {
					w4 = 40069;
				} else {
					if (hops < 5) {
						w4 = 40570;
					} else {
						if (hops < 6) {
							w4 = 41137;
						} else {
							w4 = 41613;
						}
					}
				}
			}
		}
	}
	int w5;
	if (size < 141) {
		if (rel_time < 108532) {
			if (prod == 1) {
				if (hops < 4) {
					if (hops < 2) {
						w5 = 28517;
					} else {
						if (hops < 3) {
							w5 = 28869;
						} else {
							w5 = 29125;
						}
					}
				} else {
					if (rel_time < 66890) {
						if (hops < 6) {
							w5 = 29944;
						} else {
							w5 = 30979;
						}
					} else {
						if (prod == 0) {
							w5 = 8736;
						} else {
							w5 = 30840;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w5 = 23186;
					} else {
						w5 = 23562;
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w5 = 23925;
						} else {
							w5 = 24250;
						}
					} else {
						if (hops < 6) {
							w5 = 24640;
						} else {
							w5 = 25518;
						}
					}
				}
			}
		} else {
			if (prod == 0) {
				if (hops < 3) {
					if (hops < 2) {
						if (prod == 1) {
							w5 = 23158;
						} else {
							w5 = 23214;
						}
					} else {
						if (rel_time < 219230) {
							w5 = 23627;
						} else {
							w5 = 23540;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w5 = 23915;
						} else {
							w5 = 24230;
						}
					} else {
						if (hops < 6) {
							w5 = 24652;
						} else {
							w5 = 25315;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w5 = 24034;
					} else {
						if (rel_time < 219177) {
							w5 = 24276;
						} else {
							w5 = 24389;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w5 = 24736;
						} else {
							w5 = 25075;
						}
					} else {
						if (hops < 6) {
							w5 = 25527;
						} else {
							w5 = 26142;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 53140) {
			if (hops < 3) {
				if (hops < 2) {
					w5 = 31806;
				} else {
					w5 = 32193;
				}
			} else {
				if (hops < 6) {
					if (hops < 4) {
						w5 = 32545;
					} else {
						w5 = 32948;
					}
				} else {
					w5 = 34510;
				}
			}
		} else {
			if (hops < 3) {
				if (hops < 2) {
					w5 = 27323;
				} else {
					if (rel_time < 995684) {
						if (rel_time < 940336) {
							w5 = 27703;
						} else {
							w5 = 27533;
						}
					} else {
						if (rel_time < 1050759) {
							w5 = 27945;
						} else {
							w5 = 27526;
						}
					}
				}
			} else {
				if (hops < 4) {
					w5 = 28048;
				} else {
					if (hops < 5) {
						if (rel_time < 110113) {
							w5 = 28656;
						} else {
							w5 = 28382;
						}
					} else {
						if (hops < 6) {
							w5 = 28796;
						} else {
							w5 = 29130;
						}
					}
				}
			}
		}
	}
	int w6;
	if (size < 141) {
		if (rel_time < 108532) {
			if (prod == 1) {
				if (hops < 4) {
					if (hops < 2) {
						w6 = 19962;
					} else {
						if (rel_time < 54721) {
							w6 = 20392;
						} else {
							w6 = 20194;
						}
					}
				} else {
					if (rel_time < 66890) {
						if (hops < 6) {
							w6 = 20961;
						} else {
							w6 = 21689;
						}
					} else {
						if (prod == 0) {
							w6 = 6118;
						} else {
							w6 = 21589;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w6 = 16231;
					} else {
						w6 = 16493;
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w6 = 16748;
						} else {
							w6 = 16975;
						}
					} else {
						if (hops < 6) {
							w6 = 17249;
						} else {
							w6 = 17868;
						}
					}
				}
			}
		} else {
			if (prod == 0) {
				if (hops < 3) {
					if (hops < 2) {
						if (prod == 1) {
							w6 = 16211;
						} else {
							w6 = 16250;
						}
					} else {
						if (rel_time < 1104799) {
							w6 = 16479;
						} else {
							w6 = 16614;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w6 = 16741;
						} else {
							w6 = 16961;
						}
					} else {
						if (hops < 6) {
							w6 = 17257;
						} else {
							w6 = 17721;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						if (rel_time < 219177) {
							w6 = 16746;
						} else {
							w6 = 16833;
						}
					} else {
						if (rel_time < 219177) {
							w6 = 16993;
						} else {
							w6 = 17072;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w6 = 17315;
						} else {
							w6 = 17552;
						}
					} else {
						if (hops < 6) {
							w6 = 17869;
						} else {
							w6 = 18299;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 53140) {
			if (hops < 3) {
				if (hops < 2) {
					w6 = 22265;
				} else {
					w6 = 22536;
				}
			} else {
				if (hops < 5) {
					w6 = 22856;
				} else {
					if (hops < 6) {
						w6 = 23305;
					} else {
						w6 = 24164;
					}
				}
			}
		} else {
			if (hops < 3) {
				if (hops < 2) {
					if (rel_time < 995155) {
						if (rel_time < 940087) {
							w6 = 19127;
						} else {
							w6 = 18824;
						}
					} else {
						if (rel_time < 1050482) {
							w6 = 19306;
						} else {
							w6 = 19013;
						}
					}
				} else {
					if (rel_time < 884979) {
						if (rel_time < 829632) {
							w6 = 19392;
						} else {
							w6 = 19140;
						}
					} else {
						if (rel_time < 940087) {
							w6 = 19723;
						} else {
							w6 = 19397;
						}
					}
				}
			} else {
				if (hops < 4) {
					w6 = 19634;
				} else {
					if (hops < 5) {
						if (rel_time < 1000144) {
							w6 = 19892;
						} else {
							w6 = 19649;
						}
					} else {
						if (hops < 6) {
							w6 = 20157;
						} else {
							w6 = 20391;
						}
					}
				}
			}
		}
	}
	int w7;
	if (size < 141) {
		if (rel_time < 108532) {
			if (prod == 1) {
				if (hops < 4) {
					if (hops < 3) {
						if (hops < 2) {
							w7 = 13974;
						} else {
							w7 = 14120;
						}
					} else {
						if (rel_time < 66890) {
							w7 = 14252;
						} else {
							w7 = 14582;
						}
					}
				} else {
					if (rel_time < 66890) {
						if (hops < 6) {
							w7 = 14673;
						} else {
							w7 = 15185;
						}
					} else {
						if (prod == 0) {
							w7 = 4284;
						} else {
							w7 = 15113;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w7 = 11362;
					} else {
						w7 = 11546;
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w7 = 11724;
						} else {
							w7 = 11883;
						}
					} else {
						if (hops < 6) {
							w7 = 12075;
						} else {
							w7 = 12511;
						}
					}
				}
			}
		} else {
			if (prod == 0) {
				if (hops < 3) {
					if (hops < 2) {
						if (rel_time < 551244) {
							w7 = 11379;
						} else {
							w7 = 11348;
						}
					} else {
						if (prod == 1) {
							w7 = 11512;
						} else {
							w7 = 11567;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w7 = 11718;
						} else {
							w7 = 11873;
						}
					} else {
						if (hops < 6) {
							w7 = 12080;
						} else {
							w7 = 12405;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						if (rel_time < 1104799) {
							w7 = 11783;
						} else {
							w7 = 11667;
						}
					} else {
						if (rel_time < 219177) {
							w7 = 11895;
						} else {
							w7 = 11951;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w7 = 12121;
						} else {
							w7 = 12287;
						}
					} else {
						if (hops < 6) {
							w7 = 12508;
						} else {
							w7 = 12810;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 53140) {
			if (hops < 4) {
				if (hops < 2) {
					w7 = 15586;
				} else {
					if (hops < 3) {
						w7 = 15775;
					} else {
						w7 = 15925;
					}
				}
			} else {
				if (hops < 6) {
					w7 = 16169;
				} else {
					w7 = 16920;
				}
			}
		} else {
			if (hops < 3) {
				if (hops < 2) {
					if (rel_time < 995155) {
						if (rel_time < 940087) {
							w7 = 13389;
						} else {
							w7 = 13177;
						}
					} else {
						if (rel_time < 1050482) {
							w7 = 13515;
						} else {
							w7 = 13310;
						}
					}
				} else {
					if (rel_time < 774277) {
						if (rel_time < 718930) {
							w7 = 13577;
						} else {
							w7 = 13307;
						}
					} else {
						if (rel_time < 829415) {
							w7 = 13903;
						} else {
							w7 = 13584;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (rel_time < 165434) {
						w7 = 13679;
					} else {
						w7 = 13751;
					}
				} else {
					if (hops < 5) {
						if (rel_time < 110113) {
							w7 = 14092;
						} else {
							w7 = 13904;
						}
					} else {
						if (hops < 6) {
							w7 = 14110;
						} else {
							w7 = 14274;
						}
					}
				}
			}
		}
	}
	int w8;
	if (size < 141) {
		if (rel_time < 108532) {
			if (prod == 1) {
				if (hops < 4) {
					if (hops < 3) {
						if (hops < 2) {
							w8 = 9782;
						} else {
							w8 = 9884;
						}
					} else {
						if (rel_time < 54721) {
							w8 = 10093;
						} else {
							w8 = 9926;
						}
					}
				} else {
					if (rel_time < 66890) {
						if (hops < 5) {
							w8 = 10225;
						} else {
							w8 = 10432;
						}
					} else {
						if (prod == 0) {
							w8 = 3000;
						} else {
							w8 = 10580;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w8 = 7953;
					} else {
						w8 = 8082;
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w8 = 8207;
						} else {
							w8 = 8318;
						}
					} else {
						if (hops < 6) {
							w8 = 8453;
						} else {
							w8 = 8760;
						}
					}
				}
			}
		} else {
			if (prod == 0) {
				if (hops < 3) {
					if (hops < 2) {
						if (rel_time < 108580) {
							w8 = 8068;
						} else {
							w8 = 7951;
						}
					} else {
						if (rel_time < 219230) {
							w8 = 8134;
						} else {
							w8 = 8070;
						}
					}
				} else {
					if (hops < 5) {
						if (prod == 1) {
							w8 = 8192;
						} else {
							w8 = 8299;
						}
					} else {
						if (hops < 6) {
							w8 = 8456;
						} else {
							w8 = 8683;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						if (rel_time < 219177) {
							w8 = 8188;
						} else {
							w8 = 8250;
						}
					} else {
						if (rel_time < 1117926) {
							w8 = 8358;
						} else {
							w8 = 8433;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w8 = 8484;
						} else {
							w8 = 8601;
						}
					} else {
						if (hops < 6) {
							w8 = 8756;
						} else {
							w8 = 8967;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 53140) {
			if (hops < 4) {
				if (hops < 2) {
					w8 = 10910;
				} else {
					if (hops < 3) {
						w8 = 11043;
					} else {
						w8 = 11148;
					}
				}
			} else {
				if (hops < 5) {
					w8 = 11261;
				} else {
					if (hops < 6) {
						w8 = 11464;
					} else {
						w8 = 11847;
					}
				}
			}
		} else {
			if (hops < 3) {
				if (hops < 2) {
					if (rel_time < 884509) {
						if (rel_time < 829415) {
							w8 = 9373;
						} else {
							w8 = 9042;
						}
					} else {
						if (rel_time < 939835) {
							w8 = 9498;
						} else {
							w8 = 9359;
						}
					}
				} else {
					if (rel_time < 220781) {
						if (rel_time < 165434) {
							w8 = 9529;
						} else {
							w8 = 9216;
						}
					} else {
						if (rel_time < 276132) {
							w8 = 9758;
						} else {
							w8 = 9498;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (rel_time < 276132) {
						if (rel_time < 220841) {
							w8 = 9603;
						} else {
							w8 = 9236;
						}
					} else {
						if (rel_time < 276207) {
							w8 = 9826;
						} else {
							w8 = 9619;
						}
					}
				} else {
					if (hops < 5) {
						if (rel_time < 1000144) {
							w8 = 9750;
						} else {
							w8 = 9583;
						}
					} else {
						if (rel_time < 1000144) {
							w8 = 9907;
						} else {
							w8 = 9687;
						}
					}
				}
			}
		}
	}
	int w9;
	if (size < 141) {
		if (rel_time < 108532) {
			if (prod == 1) {
				if (hops < 4) {
					if (hops < 3) {
						if (hops < 2) {
							w9 = 6847;
						} else {
							w9 = 6919;
						}
					} else {
						if (rel_time < 66890) {
							w9 = 6969;
						} else {
							w9 = 7230;
						}
					}
				} else {
					if (rel_time < 66890) {
						if (hops < 6) {
							w9 = 7186;
						} else {
							w9 = 7503;
						}
					} else {
						if (prod == 0) {
							w9 = 2101;
						} else {
							w9 = 7406;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w9 = 5567;
					} else {
						w9 = 5657;
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w9 = 5745;
						} else {
							w9 = 5823;
						}
					} else {
						if (hops < 6) {
							w9 = 5917;
						} else {
							w9 = 6134;
						}
					}
				}
			}
		} else {
			if (prod == 0) {
				if (hops < 4) {
					if (hops < 2) {
						if (prod == 1) {
							w9 = 5553;
						} else {
							w9 = 5581;
						}
					} else {
						if (hops < 3) {
							w9 = 5654;
						} else {
							w9 = 5729;
						}
					}
				} else {
					if (prod == 1) {
						if (hops < 5) {
							w9 = 5782;
						} else {
							w9 = 5901;
						}
					} else {
						if (hops < 5) {
							w9 = 5892;
						} else {
							w9 = 5991;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						if (rel_time < 1104799) {
							w9 = 5775;
						} else {
							w9 = 5692;
						}
					} else {
						if (rel_time < 219177) {
							w9 = 5820;
						} else {
							w9 = 5857;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w9 = 5939;
						} else {
							w9 = 6020;
						}
					} else {
						if (hops < 6) {
							w9 = 6129;
						} else {
							w9 = 6277;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 53140) {
			if (hops < 4) {
				if (hops < 2) {
					w9 = 7637;
				} else {
					if (hops < 3) {
						w9 = 7730;
					} else {
						w9 = 7804;
					}
				}
			} else {
				if (hops < 5) {
					w9 = 7883;
				} else {
					if (hops < 6) {
						w9 = 8025;
					} else {
						w9 = 8296;
					}
				}
			}
		} else {
			if (hops < 3) {
				if (hops < 2) {
					if (rel_time < 995155) {
						if (rel_time < 940087) {
							w9 = 6560;
						} else {
							w9 = 6417;
						}
					} else {
						if (rel_time < 1050482) {
							w9 = 6653;
						} else {
							w9 = 6510;
						}
					}
				} else {
					if (rel_time < 995420) {
						if (rel_time < 940336) {
							w9 = 6652;
						} else {
							w9 = 6462;
						}
					} else {
						if (rel_time < 1050759) {
							w9 = 6795;
						} else {
							w9 = 6528;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (rel_time < 165434) {
						if (rel_time < 110113) {
							w9 = 6701;
						} else {
							w9 = 6381;
						}
					} else {
						if (rel_time < 331479) {
							w9 = 6773;
						} else {
							w9 = 6731;
						}
					}
				} else {
					if (hops < 5) {
						if (rel_time < 110113) {
							w9 = 6940;
						} else {
							w9 = 6811;
						}
					} else {
						if (hops < 6) {
							w9 = 6908;
						} else {
							w9 = 7023;
						}
					}
				}
			}
		}
	}
	int w10;
	if (size < 141) {
		if (rel_time < 108532) {
			if (prod == 1) {
				if (hops < 4) {
					if (rel_time < 54721) {
						if (hops < 2) {
							w10 = 4777;
						} else {
							w10 = 4942;
						}
					} else {
						if (rel_time < 66890) {
							w10 = 4770;
						} else {
							w10 = 4887;
						}
					}
				} else {
					if (hops < 6) {
						if (rel_time < 66890) {
							w10 = 5031;
						} else {
							w10 = 4719;
						}
					} else {
						if (rel_time < 66890) {
							w10 = 5253;
						} else {
							w10 = 6275;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w10 = 3897;
					} else {
						if (rel_time < 59864) {
							w10 = 3987;
						} else {
							w10 = 3939;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w10 = 4021;
						} else {
							w10 = 4076;
						}
					} else {
						if (hops < 6) {
							w10 = 4142;
						} else {
							w10 = 4295;
						}
					}
				}
			}
		} else {
			if (prod == 0) {
				if (hops < 4) {
					if (hops < 2) {
						if (rel_time < 1111031) {
							w10 = 3895;
						} else {
							w10 = 3985;
						}
					} else {
						if (hops < 3) {
							w10 = 3958;
						} else {
							w10 = 4011;
						}
					}
				} else {
					if (hops < 6) {
						if (prod == 1) {
							w10 = 4062;
						} else {
							w10 = 4137;
						}
					} else {
						if (rel_time < 440571) {
							w10 = 4323;
						} else {
							w10 = 4281;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						if (rel_time < 177333) {
							w10 = 3995;
						} else {
							w10 = 4044;
						}
					} else {
						if (rel_time < 385135) {
							w10 = 4119;
						} else {
							w10 = 4089;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w10 = 4157;
						} else {
							w10 = 4214;
						}
					} else {
						if (hops < 6) {
							w10 = 4290;
						} else {
							w10 = 4394;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 53140) {
			if (hops < 4) {
				if (hops < 2) {
					w10 = 5346;
				} else {
					if (hops < 3) {
						w10 = 5411;
					} else {
						w10 = 5463;
					}
				}
			} else {
				if (hops < 5) {
					w10 = 5518;
				} else {
					if (hops < 6) {
						w10 = 5618;
					} else {
						w10 = 5809;
					}
				}
			}
		} else {
			if (hops < 3) {
				if (hops < 2) {
					if (rel_time < 995155) {
						if (rel_time < 939835) {
							w10 = 4594;
						} else {
							w10 = 4518;
						}
					} else {
						if (rel_time < 1050482) {
							w10 = 4657;
						} else {
							w10 = 4557;
						}
					}
				} else {
					if (rel_time < 884979) {
						if (rel_time < 829632) {
							w10 = 4656;
						} else {
							w10 = 4478;
						}
					} else {
						if (rel_time < 940087) {
							w10 = 4887;
						} else {
							w10 = 4660;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (rel_time < 276132) {
						if (rel_time < 220841) {
							w10 = 4703;
						} else {
							w10 = 4434;
						}
					} else {
						if (rel_time < 331479) {
							w10 = 4835;
						} else {
							w10 = 4712;
						}
					}
				} else {
					if (hops < 5) {
						if (rel_time < 165479) {
							w10 = 4690;
						} else {
							w10 = 4785;
						}
					} else {
						if (rel_time < 59853) {
							w10 = 4702;
						} else {
							w10 = 4857;
						}
					}
				}
			}
		}
	}
	int w11;
	if (size < 141) {
		if (rel_time < 108532) {
			if (prod == 1) {
				if (hops < 3) {
					if (rel_time < 66861) {
						if (hops < 2) {
							w11 = 3346;
						} else {
							w11 = 3426;
						}
					} else {
						if (hops < 2) {
							w11 = 3366;
						} else {
							w11 = 3330;
						}
					}
				} else {
					if (hops < 6) {
						if (rel_time < 54721) {
							w11 = 3515;
						} else {
							w11 = 3412;
						}
					} else {
						if (rel_time < 66890) {
							w11 = 3678;
						} else {
							w11 = 4397;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w11 = 2728;
					} else {
						if (rel_time < 59864) {
							w11 = 2791;
						} else {
							w11 = 2757;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w11 = 2815;
						} else {
							w11 = 2853;
						}
					} else {
						if (hops < 6) {
							w11 = 2900;
						} else {
							w11 = 3007;
						}
					}
				}
			}
		} else {
			if (prod == 0) {
				if (hops < 4) {
					if (hops < 2) {
						if (rel_time < 883259) {
							w11 = 2735;
						} else {
							w11 = 2705;
						}
					} else {
						if (prod == 1) {
							w11 = 2765;
						} else {
							w11 = 2811;
						}
					}
				} else {
					if (hops < 5) {
						if (rel_time < 1062862) {
							w11 = 2846;
						} else {
							w11 = 3032;
						}
					} else {
						if (hops < 6) {
							w11 = 2905;
						} else {
							w11 = 3006;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						if (rel_time < 1049002) {
							w11 = 2832;
						} else {
							w11 = 2787;
						}
					} else {
						if (rel_time < 1117926) {
							w11 = 2865;
						} else {
							w11 = 2919;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w11 = 2910;
						} else {
							w11 = 2950;
						}
					} else {
						if (hops < 6) {
							w11 = 3003;
						} else {
							w11 = 3076;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 53140) {
			if (hops < 4) {
				if (hops < 2) {
					w11 = 3742;
				} else {
					if (hops < 3) {
						w11 = 3788;
					} else {
						w11 = 3824;
					}
				}
			} else {
				if (hops < 5) {
					w11 = 3863;
				} else {
					if (hops < 6) {
						w11 = 3933;
					} else {
						w11 = 4067;
					}
				}
			}
		} else {
			if (hops < 3) {
				if (hops < 2) {
					if (rel_time < 884509) {
						if (rel_time < 829415) {
							w11 = 3215;
						} else {
							w11 = 2984;
						}
					} else {
						if (rel_time < 939835) {
							w11 = 3303;
						} else {
							w11 = 3208;
						}
					}
				} else {
					if (rel_time < 663579) {
						if (rel_time < 608232) {
							w11 = 3260;
						} else {
							w11 = 3022;
						}
					} else {
						if (rel_time < 718745) {
							w11 = 3584;
						} else {
							w11 = 3267;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (rel_time < 386832) {
						if (rel_time < 331479) {
							w11 = 3304;
						} else {
							w11 = 3206;
						}
					} else {
						if (rel_time < 497782) {
							w11 = 3351;
						} else {
							w11 = 3297;
						}
					}
				} else {
					if (rel_time < 1000144) {
						if (rel_time < 944817) {
							w11 = 3352;
						} else {
							w11 = 3586;
						}
					} else {
						if (hops < 6) {
							w11 = 3218;
						} else {
							w11 = 3552;
						}
					}
				}
			}
		}
	}
	int w12;
	if (size < 141) {
		if (rel_time < 108532) {
			if (prod == 1) {
				if (hops < 5) {
					if (hops < 3) {
						if (rel_time < 54721) {
							w12 = 2375;
						} else {
							w12 = 2343;
						}
					} else {
						if (rel_time < 54721) {
							w12 = 2451;
						} else {
							w12 = 2374;
						}
					}
				} else {
					if (rel_time < 66890) {
						if (rel_time < 53160) {
							w12 = 2525;
						} else {
							w12 = 2597;
						}
					} else {
						if (prod == 0) {
							w12 = -997;
						} else {
							w12 = 2566;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w12 = 1910;
					} else {
						if (rel_time < 59864) {
							w12 = 1954;
						} else {
							w12 = 1930;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w12 = 1971;
						} else {
							w12 = 1997;
						}
					} else {
						if (hops < 6) {
							w12 = 2030;
						} else {
							w12 = 2106;
						}
					}
				}
			}
		} else {
			if (hops < 3) {
				if (prod == 0) {
					if (rel_time < 1062862) {
						if (rel_time < 1049478) {
							w12 = 1924;
						} else {
							w12 = 1828;
						}
					} else {
						if (rel_time < 1105068) {
							w12 = 2050;
						} else {
							w12 = 1961;
						}
					}
				} else {
					if (hops < 2) {
						if (rel_time < 163851) {
							w12 = 1934;
						} else {
							w12 = 1982;
						}
					} else {
						if (rel_time < 219177) {
							w12 = 1978;
						} else {
							w12 = 2011;
						}
					}
				}
			} else {
				if (prod == 2) {
					if (hops < 4) {
						if (prod == 0) {
							w12 = 1990;
						} else {
							w12 = 2037;
						}
					} else {
						if (rel_time < 121927) {
							w12 = 1907;
						} else {
							w12 = 2064;
						}
					}
				} else {
					if (rel_time < 219377) {
						if (hops < 4) {
							w12 = 2001;
						} else {
							w12 = 2114;
						}
					} else {
						if (rel_time < 1050482) {
							w12 = 1945;
						} else {
							w12 = 2077;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 53140) {
			if (hops < 4) {
				if (hops < 2) {
					w12 = 2620;
				} else {
					if (hops < 3) {
						w12 = 2652;
					} else {
						w12 = 2677;
					}
				}
			} else {
				if (hops < 5) {
					w12 = 2704;
				} else {
					if (hops < 6) {
						w12 = 2753;
					} else {
						w12 = 2848;
					}
				}
			}
		} else {
			if (hops < 3) {
				if (rel_time < 552880) {
					if (rel_time < 497533) {
						if (rel_time < 442179) {
							w12 = 2249;
						} else {
							w12 = 2432;
						}
					} else {
						if (hops < 2) {
							w12 = 2178;
						} else {
							w12 = 2030;
						}
					}
				} else {
					if (rel_time < 608232) {
						if (hops < 2) {
							w12 = 2311;
						} else {
							w12 = 2517;
						}
					} else {
						if (rel_time < 663579) {
							w12 = 2146;
						} else {
							w12 = 2285;
						}
					}
				}
			} else {
				if (hops < 5) {
					if (rel_time < 165479) {
						if (rel_time < 59853) {
							w12 = 2363;
						} else {
							w12 = 2249;
						}
					} else {
						if (rel_time < 220841) {
							w12 = 2410;
						} else {
							w12 = 2318;
						}
					}
				} else {
					if (rel_time < 1000144) {
						if (rel_time < 944817) {
							w12 = 2384;
						} else {
							w12 = 2548;
						}
					} else {
						if (hops < 6) {
							w12 = 2222;
						} else {
							w12 = 2487;
						}
					}
				}
			}
		}
	}
	int w13;
	if (size < 141) {
		if (rel_time < 108532) {
			if (prod == 1) {
				if (hops < 5) {
					if (hops < 3) {
						if (rel_time < 66861) {
							w13 = 1662;
						} else {
							w13 = 1639;
						}
					} else {
						if (prod == 0) {
							w13 = 1660;
						} else {
							w13 = 1718;
						}
					}
				} else {
					if (hops < 6) {
						if (rel_time < 66890) {
							w13 = 1788;
						} else {
							w13 = 1524;
						}
					} else {
						if (rel_time < 66890) {
							w13 = 1807;
						} else {
							w13 = 2312;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						if (rel_time < 59877) {
							w13 = 1332;
						} else {
							w13 = 1355;
						}
					} else {
						if (rel_time < 59864) {
							w13 = 1368;
						} else {
							w13 = 1351;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w13 = 1379;
						} else {
							w13 = 1398;
						}
					} else {
						if (hops < 6) {
							w13 = 1421;
						} else {
							w13 = 1474;
						}
					}
				}
			}
		} else {
			if (prod == 0) {
				if (hops < 3) {
					if (rel_time < 219230) {
						if (rel_time < 163851) {
							w13 = 1326;
						} else {
							w13 = 1432;
						}
					} else {
						if (prod == 1) {
							w13 = 1323;
						} else {
							w13 = 1360;
						}
					}
				} else {
					if (hops < 5) {
						if (rel_time < 1105068) {
							w13 = 1381;
						} else {
							w13 = 1466;
						}
					} else {
						if (hops < 6) {
							w13 = 1429;
						} else {
							w13 = 1499;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (rel_time < 343426) {
						if (hops < 3) {
							w13 = 1411;
						} else {
							w13 = 1480;
						}
					} else {
						if (hops < 2) {
							w13 = 1383;
						} else {
							w13 = 1403;
						}
					}
				} else {
					if (rel_time < 219177) {
						if (hops < 5) {
							w13 = 1347;
						} else {
							w13 = 1474;
						}
					} else {
						if (hops < 6) {
							w13 = 1464;
						} else {
							w13 = 1558;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 53140) {
			if (hops < 4) {
				if (hops < 2) {
					w13 = 1834;
				} else {
					if (hops < 3) {
						w13 = 1856;
					} else {
						w13 = 1874;
					}
				}
			} else {
				if (hops < 5) {
					w13 = 1893;
				} else {
					if (hops < 6) {
						w13 = 1927;
					} else {
						w13 = 1994;
					}
				}
			}
		} else {
			if (hops < 4) {
				if (hops < 2) {
					if (rel_time < 995155) {
						if (rel_time < 940087) {
							w13 = 1571;
						} else {
							w13 = 1489;
						}
					} else {
						if (rel_time < 1050482) {
							w13 = 1612;
						} else {
							w13 = 1542;
						}
					}
				} else {
					if (rel_time < 442179) {
						if (rel_time < 387026) {
							w13 = 1609;
						} else {
							w13 = 1458;
						}
					} else {
						if (rel_time < 497782) {
							w13 = 1714;
						} else {
							w13 = 1605;
						}
					}
				}
			} else {
				if (rel_time < 889501) {
					if (rel_time < 834173) {
						if (rel_time < 778862) {
							w13 = 1657;
						} else {
							w13 = 1425;
						}
					} else {
						if (hops < 6) {
							w13 = 1895;
						} else {
							w13 = 1715;
						}
					}
				} else {
					if (rel_time < 944817) {
						if (hops < 6) {
							w13 = 1411;
						} else {
							w13 = 1782;
						}
					} else {
						if (rel_time < 1000144) {
							w13 = 1793;
						} else {
							w13 = 1575;
						}
					}
				}
			}
		}
	}
	int w14;
	if (size < 141) {
		if (rel_time < 108557) {
			if (prod == 1) {
				if (rel_time < 108532) {
					if (hops < 4) {
						if (rel_time < 66890) {
							w14 = 1154;
						} else {
							w14 = 1205;
						}
					} else {
						if (prod == 0) {
							w14 = 1127;
						} else {
							w14 = 1293;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w14 = 1044;
						} else {
							w14 = 1104;
						}
					} else {
						if (hops < 4) {
							w14 = 1017;
						} else {
							w14 = 1086;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						if (rel_time < 59864) {
							w14 = 926;
						} else {
							w14 = 943;
						}
					} else {
						if (rel_time < 59853) {
							w14 = 965;
						} else {
							w14 = 948;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w14 = 966;
						} else {
							w14 = 979;
						}
					} else {
						if (hops < 6) {
							w14 = 995;
						} else {
							w14 = 1032;
						}
					}
				}
			}
		} else {
			if (prod == 0) {
				if (hops < 4) {
					if (hops < 2) {
						if (rel_time < 121927) {
							w14 = 862;
						} else {
							w14 = 931;
						}
					} else {
						if (prod == 1) {
							w14 = 945;
						} else {
							w14 = 969;
						}
					}
				} else {
					if (rel_time < 177247) {
						if (rel_time < 163891) {
							w14 = 1000;
						} else {
							w14 = 1113;
						}
					} else {
						if (prod == 1) {
							w14 = 961;
						} else {
							w14 = 1000;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (rel_time < 219177) {
						if (hops < 2) {
							w14 = 938;
						} else {
							w14 = 962;
						}
					} else {
						if (rel_time < 274494) {
							w14 = 1054;
						} else {
							w14 = 976;
						}
					}
				} else {
					if (hops < 5) {
						if (rel_time < 274494) {
							w14 = 1031;
						} else {
							w14 = 999;
						}
					} else {
						if (rel_time < 1049002) {
							w14 = 1054;
						} else {
							w14 = 995;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 53140) {
			if (hops < 4) {
				if (hops < 2) {
					w14 = 1284;
				} else {
					if (hops < 3) {
						w14 = 1299;
					} else {
						w14 = 1312;
					}
				}
			} else {
				if (hops < 5) {
					w14 = 1325;
				} else {
					if (hops < 6) {
						w14 = 1349;
					} else {
						w14 = 1396;
					}
				}
			}
		} else {
			if (hops < 3) {
				if (rel_time < 774277) {
					if (rel_time < 718930) {
						if (rel_time < 663579) {
							w14 = 1104;
						} else {
							w14 = 1242;
						}
					} else {
						if (rel_time < 773867) {
							w14 = 771;
						} else {
							w14 = 990;
						}
					}
				} else {
					if (rel_time < 829632) {
						if (hops < 2) {
							w14 = 1173;
						} else {
							w14 = 1291;
						}
					} else {
						if (rel_time < 884748) {
							w14 = 977;
						} else {
							w14 = 1134;
						}
					}
				}
			} else {
				if (hops < 6) {
					if (rel_time < 663579) {
						if (rel_time < 608232) {
							w14 = 1142;
						} else {
							w14 = 1016;
						}
					} else {
						if (rel_time < 668388) {
							w14 = 1356;
						} else {
							w14 = 1134;
						}
					}
				} else {
					if (rel_time < 59853) {
						w14 = 1000;
					} else {
						if (rel_time < 115030) {
							w14 = 1565;
						} else {
							w14 = 1227;
						}
					}
				}
			}
		}
	}
	int w15;
	if (size < 141) {
		if (rel_time < 110053) {
			if (prod == 1) {
				if (rel_time < 54721) {
					if (hops < 2) {
						if (rel_time < 53140) {
							w15 = 752;
						} else {
							w15 = 795;
						}
					} else {
						if (hops < 4) {
							w15 = 851;
						} else {
							w15 = 899;
						}
					}
				} else {
					if (prod == 0) {
						if (rel_time < 108532) {
							w15 = -2344;
						} else {
							w15 = 743;
						}
					} else {
						if (rel_time < 66890) {
							w15 = 789;
						} else {
							w15 = 900;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						if (rel_time < 59877) {
							w15 = 652;
						} else {
							w15 = 666;
						}
					} else {
						if (rel_time < 59864) {
							w15 = 671;
						} else {
							w15 = 661;
						}
					}
				} else {
					if (hops < 5) {
						if (rel_time < 59853) {
							w15 = 691;
						} else {
							w15 = 677;
						}
					} else {
						if (hops < 6) {
							w15 = 696;
						} else {
							w15 = 723;
						}
					}
				}
			}
		} else {
			if (prod == 2) {
				if (rel_time < 121927) {
					if (prod == 0) {
						if (hops < 2) {
							w15 = 509;
						} else {
							w15 = 593;
						}
					} else {
						if (hops < 2) {
							w15 = 627;
						} else {
							w15 = 743;
						}
					}
				} else {
					if (hops < 3) {
						if (rel_time < 177247) {
							w15 = 707;
						} else {
							w15 = 676;
						}
					} else {
						if (rel_time < 177247) {
							w15 = 756;
						} else {
							w15 = 700;
						}
					}
				}
			} else {
				if (rel_time < 219278) {
					if (rel_time < 163891) {
						if (hops < 6) {
							w15 = 739;
						} else {
							w15 = 1026;
						}
					} else {
						if (hops < 3) {
							w15 = 676;
						} else {
							w15 = 720;
						}
					}
				} else {
					if (rel_time < 1050482) {
						if (hops < 5) {
							w15 = 647;
						} else {
							w15 = 696;
						}
					} else {
						if (hops < 4) {
							w15 = 684;
						} else {
							w15 = 811;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 53140) {
			if (hops < 4) {
				if (hops < 2) {
					w15 = 899;
				} else {
					if (hops < 3) {
						w15 = 910;
					} else {
						w15 = 918;
					}
				}
			} else {
				if (hops < 5) {
					w15 = 928;
				} else {
					if (hops < 6) {
						w15 = 944;
					} else {
						w15 = 978;
					}
				}
			}
		} else {
			if (hops < 4) {
				if (hops < 2) {
					if (rel_time < 773867) {
						if (rel_time < 718745) {
							w15 = 768;
						} else {
							w15 = 540;
						}
					} else {
						if (rel_time < 829191) {
							w15 = 861;
						} else {
							w15 = 763;
						}
					}
				} else {
					if (rel_time < 995684) {
						if (rel_time < 944817) {
							w15 = 790;
						} else {
							w15 = 698;
						}
					} else {
						if (rel_time < 1050759) {
							w15 = 907;
						} else {
							w15 = 771;
						}
					}
				}
			} else {
				if (rel_time < 723722) {
					if (rel_time < 668388) {
						if (rel_time < 613051) {
							w15 = 800;
						} else {
							w15 = 979;
						}
					} else {
						if (hops < 6) {
							w15 = 565;
						} else {
							w15 = 903;
						}
					}
				} else {
					if (rel_time < 778862) {
						if (hops < 6) {
							w15 = 1050;
						} else {
							w15 = 811;
						}
					} else {
						if (rel_time < 834173) {
							w15 = 655;
						} else {
							w15 = 828;
						}
					}
				}
			}
		}
	}
	int w16;
	if (size < 141) {
		if (rel_time < 110053) {
			if (prod == 1) {
				if (rel_time < 54721) {
					if (hops < 2) {
						if (rel_time < 53140) {
							w16 = 526;
						} else {
							w16 = 556;
						}
					} else {
						if (hops < 4) {
							w16 = 596;
						} else {
							w16 = 629;
						}
					}
				} else {
					if (prod == 0) {
						if (rel_time < 108532) {
							w16 = -1641;
						} else {
							w16 = 520;
						}
					} else {
						if (hops < 4) {
							w16 = 549;
						} else {
							w16 = 659;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (rel_time < 59853) {
						if (hops < 3) {
							w16 = 469;
						} else {
							w16 = 491;
						}
					} else {
						if (rel_time < 59877) {
							w16 = 461;
						} else {
							w16 = 472;
						}
					}
				} else {
					if (hops < 6) {
						w16 = 483;
					} else {
						if (rel_time < 59877) {
							w16 = 496;
						} else {
							w16 = 534;
						}
					}
				}
			}
		} else {
			if (prod == 0) {
				if (rel_time < 163851) {
					if (hops < 2) {
						if (rel_time < 115030) {
							w16 = 346;
						} else {
							w16 = 358;
						}
					} else {
						if (hops < 6) {
							w16 = 413;
						} else {
							w16 = 549;
						}
					}
				} else {
					if (rel_time < 219230) {
						if (prod == 1) {
							w16 = 497;
						} else {
							w16 = 547;
						}
					} else {
						if (hops < 2) {
							w16 = 448;
						} else {
							w16 = 471;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (rel_time < 343219) {
						if (rel_time < 219177) {
							w16 = 479;
						} else {
							w16 = 518;
						}
					} else {
						if (rel_time < 1104799) {
							w16 = 476;
						} else {
							w16 = 507;
						}
					}
				} else {
					if (rel_time < 219177) {
						if (hops < 5) {
							w16 = 414;
						} else {
							w16 = 496;
						}
					} else {
						if (hops < 6) {
							w16 = 511;
						} else {
							w16 = 567;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 53140) {
			if (hops < 4) {
				if (hops < 2) {
					w16 = 629;
				} else {
					if (hops < 3) {
						w16 = 637;
					} else {
						w16 = 643;
					}
				}
			} else {
				if (hops < 5) {
					w16 = 649;
				} else {
					if (hops < 6) {
						w16 = 661;
					} else {
						w16 = 685;
					}
				}
			}
		} else {
			if (hops < 5) {
				if (rel_time < 220781) {
					if (rel_time < 220723) {
						if (rel_time < 115030) {
							w16 = 536;
						} else {
							w16 = 559;
						}
					} else {
						if (hops < 3) {
							w16 = 368;
						} else {
							w16 = 490;
						}
					}
				} else {
					if (rel_time < 276132) {
						if (hops < 3) {
							w16 = 665;
						} else {
							w16 = 583;
						}
					} else {
						if (rel_time < 331479) {
							w16 = 478;
						} else {
							w16 = 554;
						}
					}
				}
			} else {
				if (rel_time < 889501) {
					if (rel_time < 834173) {
						if (rel_time < 778862) {
							w16 = 591;
						} else {
							w16 = 486;
						}
					} else {
						if (hops < 6) {
							w16 = 794;
						} else {
							w16 = 585;
						}
					}
				} else {
					if (rel_time < 944817) {
						if (hops < 6) {
							w16 = 387;
						} else {
							w16 = 632;
						}
					} else {
						if (rel_time < 1000144) {
							w16 = 653;
						} else {
							w16 = 520;
						}
					}
				}
			}
		}
	}
	int w17;
	if (size < 141) {
		if (rel_time < 110053) {
			if (prod == 1) {
				if (hops < 4) {
					if (rel_time < 108532) {
						if (rel_time < 53147) {
							w17 = 415;
						} else {
							w17 = 387;
						}
					} else {
						if (hops < 3) {
							w17 = 360;
						} else {
							w17 = 317;
						}
					}
				} else {
					if (prod == 0) {
						if (rel_time < 54721) {
							w17 = 441;
						} else {
							w17 = 370;
						}
					} else {
						if (rel_time < 66890) {
							w17 = 399;
						} else {
							w17 = 608;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						if (rel_time < 59864) {
							w17 = 313;
						} else {
							w17 = 323;
						}
					} else {
						if (rel_time < 59864) {
							w17 = 331;
						} else {
							w17 = 323;
						}
					}
				} else {
					if (hops < 5) {
						if (rel_time < 59877) {
							w17 = 331;
						} else {
							w17 = 342;
						}
					} else {
						if (rel_time < 59877) {
							w17 = 349;
						} else {
							w17 = 328;
						}
					}
				}
			}
		} else {
			if (hops < 5) {
				if (prod == 2) {
					if (rel_time < 121927) {
						if (prod == 0) {
							w17 = 279;
						} else {
							w17 = 359;
						}
					} else {
						if (hops < 2) {
							w17 = 326;
						} else {
							w17 = 340;
						}
					}
				} else {
					if (rel_time < 329981) {
						if (rel_time < 329819) {
							w17 = 331;
						} else {
							w17 = 384;
						}
					} else {
						if (rel_time < 1050482) {
							w17 = 310;
						} else {
							w17 = 361;
						}
					}
				}
			} else {
				if (hops < 6) {
					if (rel_time < 1105068) {
						if (rel_time < 1104799) {
							w17 = 356;
						} else {
							w17 = 678;
						}
					} else {
						if (rel_time < 1105352) {
							w17 = 212;
						} else {
							w17 = 302;
						}
					}
				} else {
					if (rel_time < 219278) {
						if (prod == 0) {
							w17 = 379;
						} else {
							w17 = 202;
						}
					} else {
						if (rel_time < 440571) {
							w17 = 433;
						} else {
							w17 = 388;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 53140) {
			if (hops < 4) {
				if (hops < 2) {
					w17 = 440;
				} else {
					if (hops < 3) {
						w17 = 446;
					} else {
						w17 = 450;
					}
				}
			} else {
				if (hops < 5) {
					w17 = 455;
				} else {
					if (hops < 6) {
						w17 = 463;
					} else {
						w17 = 479;
					}
				}
			}
		} else {
			if (rel_time < 552880) {
				if (rel_time < 497533) {
					if (rel_time < 442179) {
						if (rel_time < 386832) {
							w17 = 390;
						} else {
							w17 = 299;
						}
					} else {
						if (hops < 4) {
							w17 = 428;
						} else {
							w17 = 620;
						}
					}
				} else {
					if (hops < 4) {
						if (rel_time < 497782) {
							w17 = 509;
						} else {
							w17 = 279;
						}
					} else {
						if (hops < 6) {
							w17 = 178;
						} else {
							w17 = 455;
						}
					}
				}
			} else {
				if (rel_time < 608232) {
					if (hops < 4) {
						if (hops < 3) {
							w17 = 491;
						} else {
							w17 = 376;
						}
					} else {
						if (hops < 6) {
							w17 = 625;
						} else {
							w17 = 431;
						}
					}
				} else {
					if (rel_time < 663579) {
						if (hops < 4) {
							w17 = 328;
						} else {
							w17 = 219;
						}
					} else {
						if (rel_time < 718745) {
							w17 = 484;
						} else {
							w17 = 384;
						}
					}
				}
			}
		}
	}
	int w18;
	if (size < 141) {
		if (rel_time < 54721) {
			if (hops < 2) {
				if (rel_time < 53140) {
					w18 = 244;
				} else {
					w18 = 270;
				}
			} else {
				if (hops < 3) {
					if (rel_time < 53147) {
						if (rel_time < 53140) {
							w18 = 276;
						} else {
							w18 = 325;
						}
					} else {
						if (rel_time < 53160) {
							w18 = 275;
						} else {
							w18 = 291;
						}
					}
				} else {
					if (rel_time < 53140) {
						if (hops < 5) {
							w18 = 317;
						} else {
							w18 = 337;
						}
					} else {
						if (hops < 4) {
							w18 = 293;
						} else {
							w18 = 305;
						}
					}
				}
			}
		} else {
			if (prod == 0) {
				if (rel_time < 1062862) {
					if (rel_time < 994129) {
						if (rel_time < 945063) {
							w18 = 229;
						} else {
							w18 = 291;
						}
					} else {
						if (hops < 5) {
							w18 = 187;
						} else {
							w18 = 262;
						}
					}
				} else {
					if (hops < 2) {
						if (prod == 1) {
							w18 = 186;
						} else {
							w18 = 272;
						}
					} else {
						if (rel_time < 1105068) {
							w18 = 296;
						} else {
							w18 = 257;
						}
					}
				}
			} else {
				if (rel_time < 108532) {
					if (rel_time < 66890) {
						if (hops < 3) {
							w18 = 289;
						} else {
							w18 = 237;
						}
					} else {
						if (hops < 3) {
							w18 = 225;
						} else {
							w18 = 429;
						}
					}
				} else {
					if (rel_time < 1049002) {
						if (rel_time < 883035) {
							w18 = 238;
						} else {
							w18 = 262;
						}
					} else {
						if (rel_time < 1104799) {
							w18 = 202;
						} else {
							w18 = 243;
						}
					}
				}
			}
		}
	} else {
		if (rel_time < 53140) {
			if (hops < 4) {
				if (hops < 2) {
					w18 = 308;
				} else {
					if (hops < 3) {
						w18 = 312;
					} else {
						w18 = 315;
					}
				}
			} else {
				if (hops < 5) {
					w18 = 318;
				} else {
					if (hops < 6) {
						w18 = 324;
					} else {
						w18 = 336;
					}
				}
			}
		} else {
			if (rel_time < 774277) {
				if (rel_time < 718930) {
					if (rel_time < 663579) {
						if (rel_time < 608232) {
							w18 = 272;
						} else {
							w18 = 211;
						}
					} else {
						if (hops < 2) {
							w18 = 258;
						} else {
							w18 = 350;
						}
					}
				} else {
					if (hops < 4) {
						if (rel_time < 719293) {
							w18 = 404;
						} else {
							w18 = 172;
						}
					} else {
						if (hops < 6) {
							w18 = 111;
						} else {
							w18 = 340;
						}
					}
				}
			} else {
				if (rel_time < 829415) {
					if (hops < 4) {
						if (rel_time < 778862) {
							w18 = 245;
						} else {
							w18 = 360;
						}
					} else {
						if (hops < 6) {
							w18 = 451;
						} else {
							w18 = 275;
						}
					}
				} else {
					if (rel_time < 884979) {
						if (rel_time < 829632) {
							w18 = 285;
						} else {
							w18 = 207;
						}
					} else {
						if (rel_time < 940087) {
							w18 = 385;
						} else {
							w18 = 260;
						}
					}
				}
			}
		}
	}
	return (51200 + w0 + w1 + w2 + w3 + w4 + w5 + w6 + w7 + w8 + w9 + w10 + w11 + w12 + w13 + w14 + w15 + w16 + w17 + w18) >> 10;
}
