int model(int rel_timestamp, int hops, int size, int prod, int cons)
{
	int w0;
	if (size < 46) {
		if (hops < 3) {
			if (hops < 2) {
				w0 = 16384;
			} else {
				w0 = 16896;
			}
		} else {
			if (hops < 4) {
				w0 = 17408;
			} else {
				if (hops < 5) {
					w0 = 17920;
				} else {
					w0 = 18432;
				}
			}
		}
	} else {
		if (size < 133) {
			if (rel_timestamp < 344457) {
				if (prod == 0) {
					if (hops < 3) {
						if (rel_timestamp < 116626) {
							w0 = 36096;
						} else {
							w0 = 33792;
						}
					} else {
						if (rel_timestamp < 116626) {
							w0 = 37120;
						} else {
							w0 = 34560;
						}
					}
				} else {
					w0 = 52480;
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w0 = 33536;
					} else {
						w0 = 34048;
					}
				} else {
					if (hops < 4) {
						w0 = 34560;
					} else {
						if (hops < 5) {
							w0 = 35072;
						} else {
							w0 = 35584;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 38516) {
				if (hops < 3) {
					w0 = 46848;
				} else {
					w0 = 48128;
				}
			} else {
				if (hops < 3) {
					w0 = 40448;
				} else {
					w0 = 41472;
				}
			}
		}
	}
	int w1;
	if (size < 46) {
		if (hops < 3) {
			if (hops < 2) {
				w1 = 11264;
			} else {
				w1 = 11776;
			}
		} else {
			if (hops < 4) {
				w1 = 12032;
			} else {
				if (hops < 5) {
					w1 = 12544;
				} else {
					w1 = 12800;
				}
			}
		}
	} else {
		if (size < 133) {
			if (rel_timestamp < 344457) {
				if (prod == 0) {
					if (hops < 4) {
						if (rel_timestamp < 116626) {
							w1 = 25344;
						} else {
							w1 = 23808;
						}
					} else {
						w1 = 26368;
					}
				} else {
					w1 = 36864;
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w1 = 23296;
					} else {
						w1 = 23808;
					}
				} else {
					if (hops < 4) {
						w1 = 24064;
					} else {
						if (hops < 5) {
							w1 = 24576;
						} else {
							w1 = 24832;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 38516) {
				if (hops < 4) {
					if (hops < 2) {
						w1 = 32512;
					} else {
						w1 = 33280;
					}
				} else {
					w1 = 34048;
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						w1 = 27904;
					} else {
						w1 = 28672;
					}
				} else {
					w1 = 29440;
				}
			}
		}
	}
	int w2;
	if (size < 46) {
		if (hops < 3) {
			if (hops < 2) {
				w2 = 7936;
			} else {
				w2 = 8192;
			}
		} else {
			if (hops < 4) {
				w2 = 8448;
			} else {
				if (hops < 5) {
					w2 = 8704;
				} else {
					w2 = 8960;
				}
			}
		}
	} else {
		if (size < 133) {
			if (rel_timestamp < 344457) {
				if (prod == 0) {
					if (hops < 2) {
						if (rel_timestamp < 116626) {
							w2 = 17408;
						} else {
							w2 = 16128;
						}
					} else {
						if (rel_timestamp < 116626) {
							w2 = 18176;
						} else {
							w2 = 16896;
						}
					}
				} else {
					w2 = 25600;
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w2 = 16384;
					} else {
						w2 = 16640;
					}
				} else {
					if (hops < 4) {
						w2 = 16896;
					} else {
						if (hops < 5) {
							w2 = 17152;
						} else {
							w2 = 17408;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 38516) {
				if (hops < 4) {
					if (hops < 2) {
						w2 = 22784;
					} else {
						w2 = 23296;
					}
				} else {
					w2 = 23808;
				}
			} else {
				if (hops < 3) {
					w2 = 19712;
				} else {
					w2 = 20224;
				}
			}
		}
	}
	int w3;
	if (size < 46) {
		if (hops < 3) {
			if (hops < 2) {
				if (cons == 1) {
					if (rel_timestamp < 332477) {
						w3 = 5376;
					} else {
						w3 = 5376;
					}
				} else {
					w3 = 5632;
				}
			} else {
				if (cons == 1) {
					w3 = 5632;
				} else {
					w3 = 5632;
				}
			}
		} else {
			if (hops < 4) {
				if (rel_timestamp < 332477) {
					w3 = 5888;
				} else {
					w3 = 5632;
				}
			} else {
				if (hops < 5) {
					w3 = 6144;
				} else {
					w3 = 6144;
				}
			}
		}
	} else {
		if (size < 133) {
			if (rel_timestamp < 344457) {
				if (prod == 0) {
					if (hops < 3) {
						if (rel_timestamp < 116626) {
							w3 = 12288;
						} else {
							w3 = 11520;
						}
					} else {
						if (hops < 5) {
							w3 = 12544;
						} else {
							w3 = 13312;
						}
					}
				} else {
					if (hops < 3) {
						w3 = 17664;
					} else {
						w3 = 18432;
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w3 = 11264;
					} else {
						w3 = 11520;
					}
				} else {
					if (hops < 4) {
						w3 = 11776;
					} else {
						if (hops < 5) {
							w3 = 12032;
						} else {
							w3 = 12032;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 38516) {
				if (hops < 3) {
					w3 = 16128;
				} else {
					if (hops < 5) {
						w3 = 16384;
					} else {
						w3 = 17152;
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						w3 = 13568;
					} else {
						w3 = 14080;
					}
				} else {
					w3 = 14336;
				}
			}
		}
	}
	int w4;
	if (size < 46) {
		if (hops < 3) {
			if (hops < 2) {
				if (cons == 1) {
					if (rel_timestamp < 332477) {
						w4 = 3840;
					} else {
						w4 = 3840;
					}
				} else {
					w4 = 3840;
				}
			} else {
				if (rel_timestamp < 332477) {
					if (cons == 0) {
						w4 = 3840;
					} else {
						w4 = 3840;
					}
				} else {
					w4 = 3840;
				}
			}
		} else {
			if (hops < 4) {
				if (cons == 1) {
					w4 = 4096;
				} else {
					w4 = 4096;
				}
			} else {
				if (hops < 5) {
					if (cons == 1) {
						if (rel_timestamp < 332477) {
							w4 = 4096;
						} else {
							w4 = 4096;
						}
					} else {
						w4 = 4352;
					}
				} else {
					w4 = 4352;
				}
			}
		}
	} else {
		if (size < 133) {
			if (rel_timestamp < 344457) {
				if (prod == 0) {
					if (hops < 2) {
						if (rel_timestamp < 116626) {
							w4 = 8448;
						} else {
							w4 = 7936;
						}
					} else {
						if (hops < 4) {
							w4 = 8704;
						} else {
							w4 = 8960;
						}
					}
				} else {
					if (hops < 4) {
						w4 = 12288;
					} else {
						w4 = 13056;
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w4 = 7936;
					} else {
						w4 = 8192;
					}
				} else {
					if (hops < 4) {
						w4 = 8192;
					} else {
						if (hops < 5) {
							w4 = 8192;
						} else {
							w4 = 8448;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 38516) {
				if (hops < 2) {
					if (rel_timestamp < 30801) {
						w4 = 11008;
					} else {
						if (cons == 0) {
							w4 = 11264;
						} else {
							w4 = 4352;
						}
					}
				} else {
					if (hops < 4) {
						if (rel_timestamp < 30801) {
							w4 = 11264;
						} else {
							w4 = 10752;
						}
					} else {
						w4 = 11520;
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						w4 = 9472;
					} else {
						w4 = 9728;
					}
				} else {
					if (hops < 5) {
						w4 = 9984;
					} else {
						w4 = 10496;
					}
				}
			}
		}
	}
	int w5;
	if (size < 46) {
		if (hops < 3) {
			if (hops < 2) {
				if (cons == 0) {
					if (rel_timestamp < 330577) {
						if (cons == 2) {
							w5 = 2560;
						} else {
							w5 = 2560;
						}
					} else {
						w5 = 2560;
					}
				} else {
					w5 = 2560;
				}
			} else {
				if (cons == 1) {
					if (rel_timestamp < 332477) {
						if (cons == 3) {
							w5 = 2816;
						} else {
							w5 = 2816;
						}
					} else {
						w5 = 2560;
					}
				} else {
					w5 = 2816;
				}
			}
		} else {
			if (hops < 4) {
				if (cons == 1) {
					if (rel_timestamp < 332477) {
						if (cons == 3) {
							w5 = 2816;
						} else {
							w5 = 2816;
						}
					} else {
						w5 = 2816;
					}
				} else {
					w5 = 2816;
				}
			} else {
				if (hops < 5) {
					if (cons == 0) {
						if (rel_timestamp < 332477) {
							w5 = 2816;
						} else {
							w5 = 2816;
						}
					} else {
						w5 = 2816;
					}
				} else {
					w5 = 3072;
				}
			}
		}
	} else {
		if (size < 133) {
			if (rel_timestamp < 344457) {
				if (prod == 0) {
					if (hops < 2) {
						if (rel_timestamp < 116626) {
							w5 = 5888;
						} else {
							w5 = 5376;
						}
					} else {
						if (rel_timestamp < 116626) {
							w5 = 6144;
						} else {
							w5 = 5376;
						}
					}
				} else {
					if (hops < 4) {
						if (rel_timestamp < 340712) {
							w5 = 8448;
						} else {
							w5 = 8960;
						}
					} else {
						w5 = 9216;
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w5 = 5632;
					} else {
						w5 = 5632;
					}
				} else {
					if (hops < 4) {
						w5 = 5632;
					} else {
						if (hops < 5) {
							w5 = 5888;
						} else {
							w5 = 5888;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 38516) {
				if (hops < 2) {
					w5 = 7680;
				} else {
					if (hops < 5) {
						if (cons == 0) {
							w5 = 7936;
						} else {
							w5 = 7680;
						}
					} else {
						w5 = 8448;
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						w5 = 6656;
					} else {
						w5 = 6656;
					}
				} else {
					if (hops < 5) {
						w5 = 6912;
					} else {
						w5 = 7168;
					}
				}
			}
		}
	}
	int w6;
	if (size < 46) {
		if (hops < 3) {
			if (hops < 2) {
				if (cons == 0) {
					if (rel_timestamp < 332477) {
						if (cons == 2) {
							w6 = 1792;
						} else {
							w6 = 1792;
						}
					} else {
						w6 = 1792;
					}
				} else {
					w6 = 1792;
				}
			} else {
				if (cons == 1) {
					if (rel_timestamp < 332477) {
						if (cons == 0) {
							w6 = 1792;
						} else {
							w6 = 1792;
						}
					} else {
						w6 = 1792;
					}
				} else {
					w6 = 1792;
				}
			}
		} else {
			if (hops < 4) {
				if (cons == 1) {
					if (rel_timestamp < 332477) {
						if (cons == 3) {
							w6 = 2048;
						} else {
							w6 = 2048;
						}
					} else {
						w6 = 1792;
					}
				} else {
					w6 = 2048;
				}
			} else {
				if (hops < 5) {
					if (cons == 1) {
						if (cons == 3) {
							w6 = 2048;
						} else {
							w6 = 2048;
						}
					} else {
						w6 = 2048;
					}
				} else {
					if (cons == 1) {
						if (rel_timestamp < 332477) {
							w6 = 2048;
						} else {
							w6 = 1792;
						}
					} else {
						w6 = 2048;
					}
				}
			}
		}
	} else {
		if (size < 133) {
			if (rel_timestamp < 344457) {
				if (prod == 0) {
					if (hops < 4) {
						if (rel_timestamp < 116626) {
							w6 = 4096;
						} else {
							w6 = 3840;
						}
					} else {
						if (rel_timestamp < 116626) {
							w6 = 4352;
						} else {
							w6 = 3328;
						}
					}
				} else {
					if (hops < 2) {
						w6 = 5888;
					} else {
						if (rel_timestamp < 340712) {
							w6 = 6144;
						} else {
							w6 = 6400;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w6 = 3840;
					} else {
						w6 = 3840;
					}
				} else {
					if (hops < 4) {
						w6 = 3840;
					} else {
						if (hops < 5) {
							w6 = 4096;
						} else {
							w6 = 4096;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 38516) {
				if (rel_timestamp < 30801) {
					if (hops < 3) {
						w6 = 5376;
					} else {
						if (hops < 5) {
							w6 = 5632;
						} else {
							w6 = 5888;
						}
					}
				} else {
					if (cons == 0) {
						w6 = 5632;
					} else {
						if (hops < 2) {
							w6 = 768;
						} else {
							w6 = -768;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						w6 = 4608;
					} else {
						w6 = 4608;
					}
				} else {
					if (hops < 5) {
						w6 = 4864;
					} else {
						w6 = 5120;
					}
				}
			}
		}
	}
	int w7;
	if (size < 46) {
		if (hops < 3) {
			if (hops < 2) {
				if (cons == 1) {
					if (rel_timestamp < 169562) {
						if (cons == 4) {
							w7 = 1280;
						} else {
							w7 = 1280;
						}
					} else {
						if (cons == 3) {
							w7 = 1280;
						} else {
							w7 = 1280;
						}
					}
				} else {
					if (rel_timestamp < 122137) {
						w7 = 1280;
					} else {
						if (rel_timestamp < 317489) {
							w7 = 1280;
						} else {
							w7 = 1280;
						}
					}
				}
			} else {
				if (rel_timestamp < 161298) {
					if (cons == 4) {
						if (rel_timestamp < 152838) {
							w7 = 1280;
						} else {
							w7 = 1280;
						}
					} else {
						w7 = 1280;
					}
				} else {
					if (cons == 1) {
						if (cons == 3) {
							w7 = 1280;
						} else {
							w7 = 1280;
						}
					} else {
						if (rel_timestamp < 177965) {
							w7 = 1280;
						} else {
							w7 = 1280;
						}
					}
				}
			}
		} else {
			if (hops < 4) {
				if (cons == 0) {
					if (rel_timestamp < 332477) {
						if (rel_timestamp < 325942) {
							w7 = 1280;
						} else {
							w7 = 1280;
						}
					} else {
						w7 = 1280;
					}
				} else {
					if (rel_timestamp < 314743) {
						w7 = 1280;
					} else {
						w7 = 1280;
					}
				}
			} else {
				if (hops < 5) {
					if (rel_timestamp < 332477) {
						if (cons == 0) {
							w7 = 1280;
						} else {
							w7 = 1280;
						}
					} else {
						w7 = 1280;
					}
				} else {
					if (cons == 0) {
						if (rel_timestamp < 332477) {
							w7 = 1536;
						} else {
							w7 = 1280;
						}
					} else {
						w7 = 1280;
					}
				}
			}
		}
	} else {
		if (size < 133) {
			if (rel_timestamp < 344457) {
				if (prod == 0) {
					if (hops < 2) {
						if (rel_timestamp < 116626) {
							w7 = 2816;
						} else {
							w7 = 2560;
						}
					} else {
						if (hops < 5) {
							w7 = 2816;
						} else {
							w7 = 3328;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 2) {
							w7 = 4096;
						} else {
							w7 = 4352;
						}
					} else {
						w7 = 4864;
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w7 = 2560;
					} else {
						if (rel_timestamp < 416239) {
							w7 = 2560;
						} else {
							w7 = 2816;
						}
					}
				} else {
					if (hops < 4) {
						w7 = 2816;
					} else {
						if (hops < 5) {
							w7 = 2816;
						} else {
							w7 = 2816;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 38516) {
				if (hops < 4) {
					if (rel_timestamp < 30801) {
						if (hops < 2) {
							w7 = 3840;
						} else {
							w7 = 3840;
						}
					} else {
						if (cons == 0) {
							w7 = 3840;
						} else {
							w7 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (rel_timestamp < 30801) {
							w7 = 3840;
						} else {
							w7 = 3584;
						}
					} else {
						w7 = 4096;
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						w7 = 3072;
					} else {
						w7 = 3328;
					}
				} else {
					if (hops < 5) {
						w7 = 3328;
					} else {
						w7 = 3584;
					}
				}
			}
		}
	}
	int w8;
	if (size < 46) {
		if (hops < 3) {
			if (hops < 2) {
				if (cons == 0) {
					if (rel_timestamp < 309091) {
						if (rel_timestamp < 298031) {
							w8 = 768;
						} else {
							w8 = 768;
						}
					} else {
						if (cons == 3) {
							w8 = 768;
						} else {
							w8 = 768;
						}
					}
				} else {
					if (rel_timestamp < 314743) {
						if (rel_timestamp < 272880) {
							w8 = 768;
						} else {
							w8 = 768;
						}
					} else {
						w8 = 768;
					}
				}
			} else {
				if (rel_timestamp < 332477) {
					if (rel_timestamp < 325942) {
						if (rel_timestamp < 309091) {
							w8 = 768;
						} else {
							w8 = 768;
						}
					} else {
						if (cons == 3) {
							w8 = 1024;
						} else {
							w8 = 768;
						}
					}
				} else {
					w8 = 768;
				}
			}
		} else {
			if (hops < 4) {
				if (rel_timestamp < 161298) {
					if (cons == 4) {
						if (rel_timestamp < 158492) {
							w8 = 768;
						} else {
							w8 = 1024;
						}
					} else {
						w8 = 1024;
					}
				} else {
					if (cons == 1) {
						if (cons == 3) {
							w8 = 768;
						} else {
							w8 = 768;
						}
					} else {
						if (rel_timestamp < 177965) {
							w8 = 768;
						} else {
							w8 = 1024;
						}
					}
				}
			} else {
				if (hops < 5) {
					if (cons == 1) {
						if (rel_timestamp < 161231) {
							w8 = 1024;
						} else {
							w8 = 1024;
						}
					} else {
						if (rel_timestamp < 317489) {
							w8 = 1024;
						} else {
							w8 = 1024;
						}
					}
				} else {
					if (cons == 1) {
						if (cons == 3) {
							w8 = 1024;
						} else {
							w8 = 1024;
						}
					} else {
						w8 = 1024;
					}
				}
			}
		}
	} else {
		if (size < 133) {
			if (rel_timestamp < 344457) {
				if (prod == 0) {
					if (hops < 3) {
						if (hops < 2) {
							w8 = 1792;
						} else {
							w8 = 2048;
						}
					} else {
						if (rel_timestamp < 116626) {
							w8 = 2048;
						} else {
							w8 = 1536;
						}
					}
				} else {
					if (hops < 4) {
						if (rel_timestamp < 340712) {
							w8 = 2816;
						} else {
							w8 = 3072;
						}
					} else {
						if (hops < 5) {
							w8 = 3072;
						} else {
							w8 = 3584;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						if (rel_timestamp < 355677) {
							w8 = 1792;
						} else {
							w8 = 1792;
						}
					} else {
						if (rel_timestamp < 416239) {
							w8 = 1792;
						} else {
							w8 = 1792;
						}
					}
				} else {
					if (hops < 4) {
						w8 = 1792;
					} else {
						if (hops < 5) {
							w8 = 1792;
						} else {
							w8 = 2048;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 38516) {
				if (hops < 3) {
					if (rel_timestamp < 30801) {
						if (cons == 3) {
							w8 = 2560;
						} else {
							w8 = 2560;
						}
					} else {
						if (cons == 0) {
							w8 = 2560;
						} else {
							w8 = 256;
						}
					}
				} else {
					if (rel_timestamp < 30801) {
						if (cons == 0) {
							w8 = 2560;
						} else {
							w8 = 2816;
						}
					} else {
						if (cons == 0) {
							w8 = 2816;
						} else {
							w8 = -768;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						w8 = 2304;
					} else {
						w8 = 2304;
					}
				} else {
					if (hops < 5) {
						w8 = 2304;
					} else {
						w8 = 2304;
					}
				}
			}
		}
	}
	int w9;
	if (size < 46) {
		if (hops < 3) {
			if (hops < 2) {
				if (rel_timestamp < 161298) {
					if (rel_timestamp < 152838) {
						if (rel_timestamp < 141686) {
							w9 = 512;
						} else {
							w9 = 512;
						}
					} else {
						w9 = 512;
					}
				} else {
					if (rel_timestamp < 186432) {
						if (cons == 1) {
							w9 = 512;
						} else {
							w9 = 512;
						}
					} else {
						if (rel_timestamp < 194687) {
							w9 = 512;
						} else {
							w9 = 512;
						}
					}
				}
			} else {
				if (cons == 0) {
					if (cons == 2) {
						if (rel_timestamp < 317489) {
							w9 = 512;
						} else {
							w9 = 512;
						}
					} else {
						if (rel_timestamp < 292364) {
							w9 = 512;
						} else {
							w9 = 512;
						}
					}
				} else {
					if (rel_timestamp < 314743) {
						if (rel_timestamp < 272880) {
							w9 = 512;
						} else {
							w9 = 512;
						}
					} else {
						w9 = 512;
					}
				}
			}
		} else {
			if (hops < 4) {
				if (rel_timestamp < 309091) {
					if (rel_timestamp < 298067) {
						if (rel_timestamp < 284104) {
							w9 = 512;
						} else {
							w9 = 512;
						}
					} else {
						if (cons == 4) {
							w9 = 512;
						} else {
							w9 = 512;
						}
					}
				} else {
					if (cons == 3) {
						if (rel_timestamp < 325942) {
							w9 = 512;
						} else {
							w9 = 512;
						}
					} else {
						if (rel_timestamp < 332477) {
							w9 = 512;
						} else {
							w9 = 512;
						}
					}
				}
			} else {
				if (hops < 5) {
					if (rel_timestamp < 332477) {
						if (rel_timestamp < 325942) {
							w9 = 512;
						} else {
							w9 = 768;
						}
					} else {
						w9 = 512;
					}
				} else {
					if (rel_timestamp < 332477) {
						if (cons == 0) {
							w9 = 512;
						} else {
							w9 = 512;
						}
					} else {
						w9 = 512;
					}
				}
			}
		}
	} else {
		if (size < 133) {
			if (rel_timestamp < 344457) {
				if (prod == 0) {
					if (hops < 5) {
						if (rel_timestamp < 116626) {
							w9 = 1280;
						} else {
							w9 = 1024;
						}
					} else {
						w9 = 1536;
					}
				} else {
					if (hops < 3) {
						w9 = 2048;
					} else {
						if (rel_timestamp < 340712) {
							w9 = 2048;
						} else {
							w9 = 2304;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						if (rel_timestamp < 469085) {
							w9 = 1280;
						} else {
							w9 = 1280;
						}
					} else {
						if (rel_timestamp < 355677) {
							w9 = 1280;
						} else {
							w9 = 1280;
						}
					}
				} else {
					if (hops < 4) {
						w9 = 1280;
					} else {
						if (hops < 5) {
							w9 = 1280;
						} else {
							w9 = 1280;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 38516) {
				if (hops < 2) {
					if (rel_timestamp < 30801) {
						w9 = 1792;
					} else {
						if (cons == 0) {
							w9 = 1792;
						} else {
							w9 = 512;
						}
					}
				} else {
					if (hops < 5) {
						if (rel_timestamp < 30801) {
							w9 = 1792;
						} else {
							w9 = 1792;
						}
					} else {
						w9 = 2048;
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						w9 = 1536;
					} else {
						w9 = 1536;
					}
				} else {
					if (hops < 5) {
						w9 = 1536;
					} else {
						w9 = 1536;
					}
				}
			}
		}
	}
	int w10;
	if (size < 46) {
		if (hops < 3) {
			if (hops < 2) {
				if (cons == 1) {
					if (cons == 3) {
						if (rel_timestamp < 161231) {
							w10 = 256;
						} else {
							w10 = 256;
						}
					} else {
						if (rel_timestamp < 309091) {
							w10 = 256;
						} else {
							w10 = 256;
						}
					}
				} else {
					if (rel_timestamp < 122137) {
						w10 = 256;
					} else {
						if (rel_timestamp < 317489) {
							w10 = 256;
						} else {
							w10 = 512;
						}
					}
				}
			} else {
				if (rel_timestamp < 161298) {
					if (cons == 4) {
						if (rel_timestamp < 152838) {
							w10 = 256;
						} else {
							w10 = 512;
						}
					} else {
						w10 = 512;
					}
				} else {
					if (rel_timestamp < 186432) {
						if (rel_timestamp < 172442) {
							w10 = 256;
						} else {
							w10 = 256;
						}
					} else {
						if (rel_timestamp < 197450) {
							w10 = 512;
						} else {
							w10 = 256;
						}
					}
				}
			}
		} else {
			if (hops < 4) {
				if (rel_timestamp < 161298) {
					if (cons == 4) {
						if (rel_timestamp < 155595) {
							w10 = 256;
						} else {
							w10 = 512;
						}
					} else {
						w10 = 512;
					}
				} else {
					if (rel_timestamp < 186432) {
						if (rel_timestamp < 172442) {
							w10 = 256;
						} else {
							w10 = 256;
						}
					} else {
						if (rel_timestamp < 197450) {
							w10 = 512;
						} else {
							w10 = 256;
						}
					}
				}
			} else {
				if (cons == 0) {
					if (rel_timestamp < 309091) {
						if (rel_timestamp < 298031) {
							w10 = 512;
						} else {
							w10 = 512;
						}
					} else {
						if (cons == 3) {
							w10 = 256;
						} else {
							w10 = 256;
						}
					}
				} else {
					if (rel_timestamp < 314743) {
						if (rel_timestamp < 272880) {
							w10 = 256;
						} else {
							w10 = 256;
						}
					} else {
						w10 = 512;
					}
				}
			}
		}
	} else {
		if (size < 133) {
			if (rel_timestamp < 344457) {
				if (prod == 0) {
					if (hops < 4) {
						if (hops < 2) {
							w10 = 768;
						} else {
							w10 = 1024;
						}
					} else {
						if (rel_timestamp < 116626) {
							w10 = 1024;
						} else {
							w10 = 512;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 2) {
							w10 = 1280;
						} else {
							w10 = 1280;
						}
					} else {
						w10 = 1792;
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						if (rel_timestamp < 406912) {
							w10 = 768;
						} else {
							w10 = 768;
						}
					} else {
						if (rel_timestamp < 431703) {
							w10 = 768;
						} else {
							w10 = 768;
						}
					}
				} else {
					if (hops < 4) {
						if (prod == 1) {
							w10 = 768;
						} else {
							w10 = 768;
						}
					} else {
						if (hops < 5) {
							w10 = 768;
						} else {
							w10 = 768;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 38516) {
				if (hops < 4) {
					if (rel_timestamp < 17734) {
						if (cons == 1) {
							w10 = 1280;
						} else {
							w10 = 1280;
						}
					} else {
						if (cons == 0) {
							w10 = 1280;
						} else {
							w10 = -256;
						}
					}
				} else {
					if (cons == 4) {
						if (rel_timestamp < 30801) {
							w10 = 1280;
						} else {
							w10 = -1792;
						}
					} else {
						w10 = 1280;
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						if (rel_timestamp < 59351) {
							w10 = 1024;
						} else {
							w10 = 1024;
						}
					} else {
						w10 = 1024;
					}
				} else {
					if (hops < 5) {
						w10 = 1024;
					} else {
						w10 = 1024;
					}
				}
			}
		}
	}
	int w11;
	if (size < 46) {
		if (hops < 3) {
			if (hops < 2) {
				if (rel_timestamp < 281214) {
					if (rel_timestamp < 270126) {
						if (rel_timestamp < 253274) {
							w11 = 256;
						} else {
							w11 = 256;
						}
					} else {
						if (cons == 2) {
							w11 = 256;
						} else {
							w11 = 256;
						}
					}
				} else {
					if (rel_timestamp < 289613) {
						if (cons == 1) {
							w11 = 256;
						} else {
							w11 = 0;
						}
					} else {
						if (cons == 4) {
							w11 = 256;
						} else {
							w11 = 256;
						}
					}
				}
			} else {
				if (rel_timestamp < 141686) {
					if (rel_timestamp < 122137) {
						if (cons == 0) {
							w11 = 256;
						} else {
							w11 = 256;
						}
					} else {
						if (cons == 0) {
							w11 = 256;
						} else {
							w11 = 256;
						}
					}
				} else {
					if (rel_timestamp < 152838) {
						if (cons == 4) {
							w11 = 256;
						} else {
							w11 = 256;
						}
					} else {
						if (rel_timestamp < 161298) {
							w11 = 256;
						} else {
							w11 = 256;
						}
					}
				}
			}
		} else {
			if (hops < 4) {
				if (rel_timestamp < 332477) {
					if (rel_timestamp < 325942) {
						if (rel_timestamp < 309091) {
							w11 = 256;
						} else {
							w11 = 256;
						}
					} else {
						if (cons == 3) {
							w11 = 256;
						} else {
							w11 = 0;
						}
					}
				} else {
					w11 = 256;
				}
			} else {
				if (hops < 5) {
					if (cons == 2) {
						if (cons == 0) {
							w11 = 256;
						} else {
							w11 = 256;
						}
					} else {
						if (rel_timestamp < 320312) {
							w11 = 256;
						} else {
							w11 = 256;
						}
					}
				} else {
					if (cons == 1) {
						if (cons == 3) {
							w11 = 256;
						} else {
							w11 = 256;
						}
					} else {
						if (rel_timestamp < 317489) {
							w11 = 256;
						} else {
							w11 = 256;
						}
					}
				}
			}
		}
	} else {
		if (size < 133) {
			if (rel_timestamp < 344457) {
				if (prod == 0) {
					if (hops < 5) {
						if (rel_timestamp < 116626) {
							w11 = 512;
						} else {
							w11 = 512;
						}
					} else {
						w11 = 768;
					}
				} else {
					if (hops < 4) {
						if (rel_timestamp < 340712) {
							w11 = 768;
						} else {
							w11 = 1024;
						}
					} else {
						if (rel_timestamp < 340712) {
							w11 = 1024;
						} else {
							w11 = 1024;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						if (rel_timestamp < 355677) {
							w11 = 512;
						} else {
							w11 = 512;
						}
					} else {
						if (rel_timestamp < 366962) {
							w11 = 512;
						} else {
							w11 = 512;
						}
					}
				} else {
					if (hops < 4) {
						if (rel_timestamp < 613397) {
							w11 = 512;
						} else {
							w11 = 512;
						}
					} else {
						if (rel_timestamp < 416239) {
							w11 = 512;
						} else {
							w11 = 512;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 38516) {
				if (hops < 2) {
					if (rel_timestamp < 17734) {
						w11 = 768;
					} else {
						if (cons == 0) {
							w11 = 768;
						} else {
							w11 = 512;
						}
					}
				} else {
					if (cons == 4) {
						if (rel_timestamp < 30801) {
							w11 = 768;
						} else {
							w11 = -768;
						}
					} else {
						if (rel_timestamp < 30801) {
							w11 = 768;
						} else {
							w11 = 1024;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (cons == 4) {
						if (rel_timestamp < 52378) {
							w11 = 768;
						} else {
							w11 = 768;
						}
					} else {
						w11 = 768;
					}
				} else {
					if (hops < 5) {
						w11 = 768;
					} else {
						w11 = 768;
					}
				}
			}
		}
	}
	int w12;
	if (size < 46) {
		if (hops < 3) {
			if (hops < 2) {
				if (cons == 0) {
					if (rel_timestamp < 144570) {
						if (rel_timestamp < 122137) {
							w12 = 0;
						} else {
							w12 = 0;
						}
					} else {
						if (rel_timestamp < 152838) {
							w12 = 0;
						} else {
							w12 = 0;
						}
					}
				} else {
					if (rel_timestamp < 314743) {
						if (rel_timestamp < 200388) {
							w12 = 0;
						} else {
							w12 = 0;
						}
					} else {
						w12 = 0;
					}
				}
			} else {
				if (cons == 1) {
					if (rel_timestamp < 309091) {
						if (rel_timestamp < 300831) {
							w12 = 0;
						} else {
							w12 = 256;
						}
					} else {
						if (cons == 3) {
							w12 = 0;
						} else {
							w12 = 0;
						}
					}
				} else {
					if (rel_timestamp < 289613) {
						if (rel_timestamp < 275644) {
							w12 = 0;
						} else {
							w12 = 0;
						}
					} else {
						if (rel_timestamp < 303582) {
							w12 = 256;
						} else {
							w12 = 256;
						}
					}
				}
			}
		} else {
			if (hops < 4) {
				if (cons == 0) {
					if (rel_timestamp < 144570) {
						if (rel_timestamp < 124952) {
							w12 = 0;
						} else {
							w12 = 256;
						}
					} else {
						if (rel_timestamp < 152838) {
							w12 = 0;
						} else {
							w12 = 0;
						}
					}
				} else {
					if (rel_timestamp < 314743) {
						if (rel_timestamp < 119382) {
							w12 = 256;
						} else {
							w12 = 0;
						}
					} else {
						w12 = 256;
					}
				}
			} else {
				if (rel_timestamp < 309091) {
					if (rel_timestamp < 298067) {
						if (rel_timestamp < 284104) {
							w12 = 0;
						} else {
							w12 = 0;
						}
					} else {
						if (cons == 0) {
							w12 = 256;
						} else {
							w12 = 0;
						}
					}
				} else {
					if (rel_timestamp < 323058) {
						if (cons == 3) {
							w12 = 0;
						} else {
							w12 = 0;
						}
					} else {
						if (rel_timestamp < 332477) {
							w12 = 256;
						} else {
							w12 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_timestamp < 66265) {
			if (rel_timestamp < 38516) {
				if (cons == 3) {
					if (hops < 3) {
						if (hops < 2) {
							w12 = 512;
						} else {
							w12 = 512;
						}
					} else {
						if (cons == 4) {
							w12 = 512;
						} else {
							w12 = 512;
						}
					}
				} else {
					if (hops < 4) {
						w12 = 512;
					} else {
						w12 = 512;
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						if (cons == 3) {
							w12 = 512;
						} else {
							w12 = 512;
						}
					} else {
						w12 = 512;
					}
				} else {
					if (hops < 5) {
						w12 = 512;
					} else {
						w12 = 512;
					}
				}
			}
		} else {
			if (rel_timestamp < 344457) {
				if (prod == 0) {
					if (hops < 3) {
						if (hops < 2) {
							w12 = 256;
						} else {
							w12 = 256;
						}
					} else {
						if (rel_timestamp < 116626) {
							w12 = 512;
						} else {
							w12 = 256;
						}
					}
				} else {
					if (hops < 5) {
						if (rel_timestamp < 340712) {
							w12 = 512;
						} else {
							w12 = 768;
						}
					} else {
						w12 = 768;
					}
				}
			} else {
				if (hops < 3) {
					if (hops < 2) {
						if (prod == 1) {
							w12 = 256;
						} else {
							w12 = 256;
						}
					} else {
						if (rel_timestamp < 416239) {
							w12 = 256;
						} else {
							w12 = 256;
						}
					}
				} else {
					if (hops < 4) {
						if (rel_timestamp < 355677) {
							w12 = 256;
						} else {
							w12 = 256;
						}
					} else {
						if (rel_timestamp < 366962) {
							w12 = 256;
						} else {
							w12 = 256;
						}
					}
				}
			}
		}
	}
	int w13;
	if (size < 46) {
		if (hops < 3) {
			if (cons == 1) {
				if (cons == 3) {
					if (rel_timestamp < 161231) {
						if (cons == 4) {
							w13 = 0;
						} else {
							w13 = 0;
						}
					} else {
						if (rel_timestamp < 323058) {
							w13 = 0;
						} else {
							w13 = 0;
						}
					}
				} else {
					if (rel_timestamp < 309091) {
						if (rel_timestamp < 211418) {
							w13 = 0;
						} else {
							w13 = 0;
						}
					} else {
						if (rel_timestamp < 332477) {
							w13 = 0;
						} else {
							w13 = 0;
						}
					}
				}
			} else {
				if (rel_timestamp < 233785) {
					if (rel_timestamp < 219817) {
						if (rel_timestamp < 205898) {
							w13 = 0;
						} else {
							w13 = 0;
						}
					} else {
						w13 = 0;
					}
				} else {
					if (rel_timestamp < 247758) {
						w13 = 0;
					} else {
						if (rel_timestamp < 289613) {
							w13 = 0;
						} else {
							w13 = 0;
						}
					}
				}
			}
		} else {
			if (cons == 1) {
				if (cons == 3) {
					if (rel_timestamp < 161231) {
						if (cons == 4) {
							w13 = 0;
						} else {
							w13 = 0;
						}
					} else {
						if (rel_timestamp < 267240) {
							w13 = 0;
						} else {
							w13 = 0;
						}
					}
				} else {
					if (rel_timestamp < 309091) {
						if (rel_timestamp < 267240) {
							w13 = 0;
						} else {
							w13 = 0;
						}
					} else {
						if (rel_timestamp < 332477) {
							w13 = 0;
						} else {
							w13 = 0;
						}
					}
				}
			} else {
				if (rel_timestamp < 177965) {
					if (rel_timestamp < 164052) {
						if (rel_timestamp < 150074) {
							w13 = 0;
						} else {
							w13 = 0;
						}
					} else {
						if (hops < 4) {
							w13 = 0;
						} else {
							w13 = 0;
						}
					}
				} else {
					if (rel_timestamp < 191935) {
						if (hops < 4) {
							w13 = 0;
						} else {
							w13 = 0;
						}
					} else {
						if (rel_timestamp < 233785) {
							w13 = 0;
						} else {
							w13 = 0;
						}
					}
				}
			}
		}
	} else {
		if (size < 133) {
			if (rel_timestamp < 344457) {
				if (prod == 0) {
					if (hops < 4) {
						if (hops < 2) {
							w13 = 256;
						} else {
							w13 = 256;
						}
					} else {
						if (rel_timestamp < 116626) {
							w13 = 256;
						} else {
							w13 = 0;
						}
					}
				} else {
					if (hops < 2) {
						if (rel_timestamp < 340712) {
							w13 = 256;
						} else {
							w13 = 256;
						}
					} else {
						if (rel_timestamp < 340712) {
							w13 = 256;
						} else {
							w13 = 512;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (rel_timestamp < 355677) {
						if (hops < 2) {
							w13 = 256;
						} else {
							w13 = 256;
						}
					} else {
						if (rel_timestamp < 588498) {
							w13 = 256;
						} else {
							w13 = 256;
						}
					}
				} else {
					if (hops < 5) {
						if (rel_timestamp < 355677) {
							w13 = 256;
						} else {
							w13 = 256;
						}
					} else {
						if (rel_timestamp < 493796) {
							w13 = 256;
						} else {
							w13 = 256;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 38516) {
				if (hops < 5) {
					if (cons == 3) {
						if (rel_timestamp < 30801) {
							w13 = 256;
						} else {
							w13 = 256;
						}
					} else {
						if (rel_timestamp < 23813) {
							w13 = 256;
						} else {
							w13 = 256;
						}
					}
				} else {
					w13 = 512;
				}
			} else {
				if (hops < 3) {
					if (rel_timestamp < 59351) {
						if (rel_timestamp < 52378) {
							w13 = 256;
						} else {
							w13 = 256;
						}
					} else {
						w13 = 256;
					}
				} else {
					if (hops < 5) {
						if (rel_timestamp < 66265) {
							w13 = 256;
						} else {
							w13 = 256;
						}
					} else {
						w13 = 256;
					}
				}
			}
		}
	}
	int w14;
	if (size < 46) {
		if (hops < 4) {
			if (hops < 2) {
				if (rel_timestamp < 169562) {
					if (rel_timestamp < 152838) {
						if (rel_timestamp < 141686) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					} else {
						if (cons == 2) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					}
				} else {
					if (rel_timestamp < 186432) {
						if (cons == 1) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					} else {
						if (rel_timestamp < 194687) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					}
				}
			} else {
				if (rel_timestamp < 332477) {
					if (rel_timestamp < 323058) {
						if (rel_timestamp < 314743) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					} else {
						if (cons == 3) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					}
				} else {
					if (cons == 3) {
						if (rel_timestamp < 334441) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					} else {
						w14 = 0;
					}
				}
			}
		} else {
			if (hops < 5) {
				if (rel_timestamp < 253274) {
					if (rel_timestamp < 242250) {
						if (rel_timestamp < 228258) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					} else {
						if (cons == 0) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					}
				} else {
					if (rel_timestamp < 267240) {
						if (cons == 3) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					} else {
						if (rel_timestamp < 281214) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					}
				}
			} else {
				if (cons == 2) {
					if (rel_timestamp < 284104) {
						if (rel_timestamp < 270126) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					} else {
						if (rel_timestamp < 289613) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					}
				} else {
					if (rel_timestamp < 320312) {
						if (rel_timestamp < 138862) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					} else {
						w14 = 0;
					}
				}
			}
		}
	} else {
		if (size < 133) {
			if (rel_timestamp < 344457) {
				if (prod == 0) {
					if (hops < 5) {
						if (rel_timestamp < 116626) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					} else {
						if (rel_timestamp < 90042) {
							w14 = 256;
						} else {
							w14 = 256;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 3) {
							w14 = 256;
						} else {
							w14 = 256;
						}
					} else {
						w14 = 512;
					}
				}
			} else {
				if (hops < 2) {
					if (rel_timestamp < 473225) {
						if (rel_timestamp < 431703) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					} else {
						if (rel_timestamp < 588498) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (rel_timestamp < 416239) {
							w14 = 0;
						} else {
							w14 = 0;
						}
					} else {
						if (rel_timestamp < 391573) {
							w14 = 256;
						} else {
							w14 = 0;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 38516) {
				if (hops < 3) {
					if (cons == 3) {
						if (cons == 1) {
							w14 = 256;
						} else {
							w14 = 256;
						}
					} else {
						if (hops < 2) {
							w14 = 256;
						} else {
							w14 = 256;
						}
					}
				} else {
					if (cons == 4) {
						if (rel_timestamp < 30801) {
							w14 = 256;
						} else {
							w14 = -768;
						}
					} else {
						if (rel_timestamp < 30801) {
							w14 = 256;
						} else {
							w14 = 256;
						}
					}
				}
			} else {
				if (hops < 2) {
					if (rel_timestamp < 59351) {
						if (cons == 1) {
							w14 = 256;
						} else {
							w14 = 256;
						}
					} else {
						if (rel_timestamp < 66265) {
							w14 = 0;
						} else {
							w14 = 256;
						}
					}
				} else {
					if (hops < 4) {
						if (rel_timestamp < 66265) {
							w14 = 256;
						} else {
							w14 = 256;
						}
					} else {
						if (hops < 5) {
							w14 = 256;
						} else {
							w14 = 256;
						}
					}
				}
			}
		}
	}
	int w15;
	if (size < 46) {
		if (hops < 3) {
			if (rel_timestamp < 211418) {
				if (rel_timestamp < 203150) {
					if (cons == 0) {
						if (rel_timestamp < 122137) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					} else {
						if (rel_timestamp < 119382) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					}
				} else {
					if (cons == 3) {
						if (rel_timestamp < 205898) {
							w15 = 0;
						} else {
							w15 = 0;
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
				if (rel_timestamp < 225386) {
					if (cons == 2) {
						if (rel_timestamp < 214310) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					} else {
						if (rel_timestamp < 219883) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					}
				} else {
					if (rel_timestamp < 242250) {
						if (cons == 1) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					} else {
						if (rel_timestamp < 250512) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 214310) {
				if (rel_timestamp < 197450) {
					if (rel_timestamp < 189179) {
						if (rel_timestamp < 172442) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					} else {
						if (hops < 4) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					}
				} else {
					if (cons == 3) {
						if (rel_timestamp < 211418) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					} else {
						if (hops < 4) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					}
				}
			} else {
				if (rel_timestamp < 228258) {
					if (cons == 2) {
						if (rel_timestamp < 225386) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					} else {
						if (rel_timestamp < 219883) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					}
				} else {
					if (rel_timestamp < 233785) {
						if (cons == 0) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					} else {
						if (rel_timestamp < 253274) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_timestamp < 71348) {
			if (rel_timestamp < 30801) {
				if (cons == 0) {
					if (cons == 2) {
						if (hops < 4) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					} else {
						if (rel_timestamp < 17734) {
							w15 = 0;
						} else {
							w15 = 256;
						}
					}
				} else {
					if (hops < 2) {
						w15 = 0;
					} else {
						if (hops < 4) {
							w15 = 256;
						} else {
							w15 = 256;
						}
					}
				}
			} else {
				if (cons == 0) {
					if (rel_timestamp < 38516) {
						if (hops < 2) {
							w15 = 0;
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
				} else {
					if (rel_timestamp < 38516) {
						if (hops < 2) {
							w15 = 0;
						} else {
							w15 = -768;
						}
					} else {
						if (hops < 3) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 348199) {
				if (prod == 0) {
					if (cons == 4) {
						if (hops < 2) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					} else {
						if (hops < 4) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 2) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					} else {
						if (rel_timestamp < 340712) {
							w15 = 256;
						} else {
							w15 = 256;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (rel_timestamp < 588498) {
						if (rel_timestamp < 554429) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					} else {
						if (prod == 1) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					}
				} else {
					if (rel_timestamp < 554429) {
						if (rel_timestamp < 366962) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					} else {
						if (rel_timestamp < 613397) {
							w15 = 0;
						} else {
							w15 = 0;
						}
					}
				}
			}
		}
	}
	int w16;
	if (size < 46) {
		if (rel_timestamp < 267240) {
			if (rel_timestamp < 258981) {
				if (rel_timestamp < 242250) {
					if (rel_timestamp < 228258) {
						if (rel_timestamp < 214310) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					} else {
						if (cons == 1) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					}
				} else {
					if (rel_timestamp < 253274) {
						if (cons == 4) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					} else {
						if (cons == 0) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					}
				}
			} else {
				if (cons == 3) {
					if (cons == 1) {
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
				} else {
					if (hops < 4) {
						if (rel_timestamp < 264483) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					} else {
						if (hops < 5) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 281214) {
				if (cons == 2) {
					if (rel_timestamp < 270126) {
						if (cons == 0) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					} else {
						if (hops < 2) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					}
				} else {
					if (hops < 2) {
						if (rel_timestamp < 275644) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					} else {
						if (hops < 5) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					}
				}
			} else {
				if (rel_timestamp < 298067) {
					if (cons == 1) {
						if (hops < 3) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					} else {
						if (hops < 5) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					}
				} else {
					if (rel_timestamp < 309091) {
						if (cons == 4) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					} else {
						if (rel_timestamp < 323058) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_timestamp < 66265) {
			if (rel_timestamp < 30801) {
				if (cons == 0) {
					if (hops < 5) {
						if (cons == 2) {
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
					if (hops < 2) {
						w16 = 0;
					} else {
						if (hops < 4) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					}
				}
			} else {
				if (cons == 0) {
					if (rel_timestamp < 38516) {
						if (hops < 2) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					} else {
						if (rel_timestamp < 45455) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					}
				} else {
					if (rel_timestamp < 38516) {
						if (hops < 4) {
							w16 = -256;
						} else {
							w16 = -768;
						}
					} else {
						if (hops < 5) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 348199) {
				if (prod == 0) {
					if (hops < 5) {
						if (cons == 4) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					} else {
						if (rel_timestamp < 116626) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (rel_timestamp < 340712) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					} else {
						w16 = 256;
					}
				}
			} else {
				if (hops < 2) {
					if (rel_timestamp < 687100) {
						if (rel_timestamp < 649289) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					} else {
						if (rel_timestamp < 751592) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					} else {
						if (prod == 3) {
							w16 = 0;
						} else {
							w16 = 0;
						}
					}
				}
			}
		}
	}
	int w17;
	if (size < 46) {
		if (cons == 1) {
			if (cons == 3) {
				if (rel_timestamp < 161231) {
					if (rel_timestamp < 155595) {
						if (rel_timestamp < 141686) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					} else {
						if (hops < 4) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					}
				} else {
					if (rel_timestamp < 164052) {
						if (hops < 2) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					} else {
						if (rel_timestamp < 332477) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					}
				}
			} else {
				if (rel_timestamp < 309091) {
					if (rel_timestamp < 267240) {
						if (rel_timestamp < 253274) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					} else {
						if (rel_timestamp < 278466) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					}
				} else {
					if (rel_timestamp < 332477) {
						if (rel_timestamp < 323058) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					} else {
						if (hops < 5) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 122137) {
				if (hops < 4) {
					if (hops < 2) {
						if (rel_timestamp < 119382) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					} else {
						if (rel_timestamp < 119382) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					}
				} else {
					if (hops < 5) {
						w17 = 0;
					} else {
						w17 = 0;
					}
				}
			} else {
				if (rel_timestamp < 136108) {
					if (hops < 2) {
						if (rel_timestamp < 133355) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					} else {
						if (rel_timestamp < 133355) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					}
				} else {
					if (rel_timestamp < 177965) {
						if (rel_timestamp < 164052) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					} else {
						if (rel_timestamp < 191935) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_timestamp < 71348) {
			if (rel_timestamp < 30801) {
				if (cons == 0) {
					if (hops < 4) {
						if (cons == 3) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					} else {
						if (cons == 3) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w17 = 0;
					} else {
						if (hops < 4) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					}
				}
			} else {
				if (cons == 0) {
					if (rel_timestamp < 38516) {
						if (hops < 2) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					} else {
						if (cons == 4) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					}
				} else {
					if (rel_timestamp < 38516) {
						if (hops < 2) {
							w17 = 0;
						} else {
							w17 = -256;
						}
					} else {
						if (hops < 3) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 348199) {
				if (prod == 0) {
					if (hops < 4) {
						if (rel_timestamp < 104640) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					} else {
						if (rel_timestamp < 116626) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 2) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					} else {
						w17 = 0;
					}
				}
			} else {
				if (hops < 2) {
					if (rel_timestamp < 923980) {
						if (rel_timestamp < 915357) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					} else {
						if (prod == 3) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (rel_timestamp < 915357) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					} else {
						if (rel_timestamp < 416239) {
							w17 = 0;
						} else {
							w17 = 0;
						}
					}
				}
			}
		}
	}
	int w18;
	if (size < 46) {
		if (rel_timestamp < 116626) {
			if (hops < 2) {
				w18 = 0;
			} else {
				if (hops < 3) {
					w18 = 0;
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					} else {
						w18 = 0;
					}
				}
			}
		} else {
			if (hops < 5) {
				if (rel_timestamp < 138862) {
					if (rel_timestamp < 133355) {
						if (cons == 3) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					} else {
						if (hops < 2) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					}
				} else {
					if (rel_timestamp < 211418) {
						if (rel_timestamp < 203150) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					} else {
						if (rel_timestamp < 228258) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					}
				}
			} else {
				if (rel_timestamp < 144570) {
					if (cons == 4) {
						if (cons == 0) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					} else {
						if (rel_timestamp < 141686) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					}
				} else {
					if (rel_timestamp < 155595) {
						if (cons == 1) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					} else {
						if (rel_timestamp < 172442) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_timestamp < 80686) {
			if (rel_timestamp < 30801) {
				if (cons == 0) {
					if (hops < 5) {
						if (cons == 2) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					} else {
						if (cons == 2) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w18 = 0;
					} else {
						if (hops < 4) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					}
				}
			} else {
				if (cons == 0) {
					if (rel_timestamp < 38516) {
						if (hops < 4) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					} else {
						if (hops < 2) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					}
				} else {
					if (rel_timestamp < 38516) {
						if (hops < 4) {
							w18 = 0;
						} else {
							w18 = -512;
						}
					} else {
						if (rel_timestamp < 71348) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					}
				}
			}
		} else {
			if (cons == 1) {
				if (rel_timestamp < 340712) {
					if (rel_timestamp < 85364) {
						if (hops < 3) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					} else {
						if (rel_timestamp < 95284) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					}
				} else {
					if (prod == 1) {
						if (rel_timestamp < 344457) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					} else {
						if (rel_timestamp < 344457) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (rel_timestamp < 99957) {
						if (hops < 2) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					} else {
						if (hops < 2) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					}
				} else {
					if (rel_timestamp < 99957) {
						if (hops < 4) {
							w18 = 0;
						} else {
							w18 = 0;
						}
					} else {
						if (hops < 5) {
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
	if (size < 46) {
		if (rel_timestamp < 267240) {
			if (rel_timestamp < 258981) {
				if (rel_timestamp < 242250) {
					if (rel_timestamp < 228258) {
						if (rel_timestamp < 219883) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					} else {
						if (cons == 1) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					}
				} else {
					if (rel_timestamp < 253274) {
						if (cons == 0) {
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
				}
			} else {
				if (cons == 3) {
					if (cons == 1) {
						if (hops < 4) {
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
					if (hops < 4) {
						if (rel_timestamp < 264483) {
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
			if (rel_timestamp < 281214) {
				if (cons == 2) {
					if (rel_timestamp < 270126) {
						if (cons == 0) {
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
					if (hops < 2) {
						if (rel_timestamp < 275644) {
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
				}
			} else {
				if (rel_timestamp < 298067) {
					if (cons == 1) {
						if (rel_timestamp < 284104) {
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
					if (rel_timestamp < 306329) {
						if (cons == 0) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					} else {
						if (rel_timestamp < 325942) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_timestamp < 80686) {
			if (rel_timestamp < 30801) {
				if (cons == 3) {
					if (hops < 4) {
						if (cons == 1) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					} else {
						if (rel_timestamp < 23813) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					}
				} else {
					if (rel_timestamp < 23813) {
						if (hops < 3) {
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
				}
			} else {
				if (cons == 0) {
					if (rel_timestamp < 38516) {
						if (hops < 2) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					} else {
						if (rel_timestamp < 45455) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					}
				} else {
					if (rel_timestamp < 38516) {
						if (hops < 2) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					} else {
						if (rel_timestamp < 71348) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					}
				}
			}
		} else {
			if (cons == 1) {
				if (rel_timestamp < 340712) {
					if (hops < 4) {
						if (rel_timestamp < 85364) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					} else {
						if (rel_timestamp < 90042) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (rel_timestamp < 366962) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					} else {
						if (rel_timestamp < 825242) {
							w19 = 0;
						} else {
							w19 = 0;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (rel_timestamp < 99957) {
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
					if (rel_timestamp < 99957) {
						if (hops < 4) {
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
		}
	}
	int w20;
	if (size < 46) {
		if (rel_timestamp < 332477) {
			if (rel_timestamp < 325942) {
				if (hops < 2) {
					if (rel_timestamp < 309091) {
						if (rel_timestamp < 298067) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					} else {
						if (cons == 0) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					}
				} else {
					if (cons == 3) {
						if (rel_timestamp < 172442) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					} else {
						if (rel_timestamp < 211418) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					}
				}
			} else {
				if (cons == 3) {
					if (cons == 0) {
						if (hops < 2) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					} else {
						if (hops < 4) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w20 = 0;
					} else {
						if (hops < 4) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 334441) {
				if (cons == 3) {
					if (hops < 2) {
						w20 = 0;
					} else {
						if (hops < 5) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					} else {
						w20 = 0;
					}
				}
			} else {
				if (hops < 3) {
					w20 = 0;
				} else {
					if (hops < 5) {
						if (hops < 4) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					} else {
						w20 = 0;
					}
				}
			}
		}
	} else {
		if (rel_timestamp < 76011) {
			if (rel_timestamp < 30801) {
				if (hops < 5) {
					if (cons == 0) {
						if (hops < 3) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					} else {
						if (hops < 2) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					}
				} else {
					if (cons == 3) {
						if (rel_timestamp < 23813) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					} else {
						if (rel_timestamp < 23813) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					}
				}
			} else {
				if (cons == 0) {
					if (rel_timestamp < 71348) {
						if (rel_timestamp < 38516) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					} else {
						if (hops < 2) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					}
				} else {
					if (rel_timestamp < 38516) {
						if (hops < 4) {
							w20 = 0;
						} else {
							w20 = -256;
						}
					} else {
						if (rel_timestamp < 71348) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					}
				}
			}
		} else {
			if (hops < 2) {
				if (cons == 1) {
					if (rel_timestamp < 847178) {
						if (rel_timestamp < 845410) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					} else {
						if (rel_timestamp < 885020) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					}
				} else {
					if (rel_timestamp < 80686) {
						w20 = 0;
					} else {
						if (rel_timestamp < 99957) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					}
				}
			} else {
				if (rel_timestamp < 109315) {
					if (rel_timestamp < 104640) {
						if (hops < 3) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					} else {
						if (cons == 2) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					}
				} else {
					if (prod == 1) {
						if (rel_timestamp < 344457) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					} else {
						if (rel_timestamp < 344457) {
							w20 = 0;
						} else {
							w20 = 0;
						}
					}
				}
			}
		}
	}
	int w21;
	if (size < 46) {
		if (cons == 1) {
			if (rel_timestamp < 127704) {
				if (rel_timestamp < 116626) {
					if (hops < 3) {
						if (hops < 2) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					} else {
						if (hops < 5) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					}
				} else {
					if (rel_timestamp < 122137) {
						if (hops < 5) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					} else {
						if (rel_timestamp < 124952) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					}
				}
			} else {
				if (rel_timestamp < 136108) {
					if (cons == 4) {
						if (rel_timestamp < 133355) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					} else {
						if (hops < 4) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					}
				} else {
					if (rel_timestamp < 138862) {
						if (cons == 2) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					} else {
						if (rel_timestamp < 152838) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 122137) {
				if (hops < 4) {
					if (hops < 2) {
						if (rel_timestamp < 119382) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					} else {
						if (hops < 3) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					}
				} else {
					if (hops < 5) {
						w21 = 0;
					} else {
						w21 = 0;
					}
				}
			} else {
				if (rel_timestamp < 136108) {
					if (rel_timestamp < 133355) {
						if (hops < 4) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					} else {
						if (hops < 3) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					}
				} else {
					if (rel_timestamp < 150074) {
						if (rel_timestamp < 147322) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					} else {
						if (rel_timestamp < 164052) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_timestamp < 59351) {
			if (cons == 4) {
				if (hops < 5) {
					if (rel_timestamp < 30801) {
						if (cons == 0) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					} else {
						if (rel_timestamp < 38516) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					}
				} else {
					if (cons == 3) {
						if (rel_timestamp < 23813) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					} else {
						if (rel_timestamp < 30801) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (hops < 2) {
						if (rel_timestamp < 30801) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					} else {
						if (rel_timestamp < 30801) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					}
				} else {
					if (rel_timestamp < 30801) {
						if (hops < 5) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					} else {
						if (hops < 5) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					}
				}
			}
		} else {
			if (hops < 5) {
				if (hops < 2) {
					if (rel_timestamp < 104640) {
						if (cons == 3) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					} else {
						if (rel_timestamp < 109315) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					}
				} else {
					if (rel_timestamp < 109315) {
						if (rel_timestamp < 104640) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					} else {
						if (rel_timestamp < 514733) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					}
				}
			} else {
				if (rel_timestamp < 344457) {
					if (rel_timestamp < 104640) {
						if (cons == 0) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					} else {
						if (cons == 4) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					}
				} else {
					if (rel_timestamp < 378457) {
						if (rel_timestamp < 370745) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					} else {
						if (rel_timestamp < 416239) {
							w21 = 0;
						} else {
							w21 = 0;
						}
					}
				}
			}
		}
	}
	int w22;
	if (size < 46) {
		if (rel_timestamp < 172442) {
			if (cons == 4) {
				if (rel_timestamp < 152838) {
					if (rel_timestamp < 138862) {
						if (cons == 0) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					} else {
						if (rel_timestamp < 147322) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					}
				} else {
					if (cons == 2) {
						if (rel_timestamp < 166804) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					} else {
						if (hops < 2) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					}
				}
			} else {
				if (rel_timestamp < 127704) {
					if (hops < 2) {
						w22 = 0;
					} else {
						if (hops < 4) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (rel_timestamp < 155595) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					} else {
						if (rel_timestamp < 144570) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 183525) {
				if (cons == 1) {
					if (rel_timestamp < 175206) {
						if (hops < 4) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					} else {
						if (hops < 2) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					} else {
						if (hops < 4) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					}
				}
			} else {
				if (rel_timestamp < 197450) {
					if (cons == 0) {
						if (cons == 4) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					} else {
						if (rel_timestamp < 186432) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					}
				} else {
					if (rel_timestamp < 211418) {
						if (cons == 3) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					} else {
						if (rel_timestamp < 219817) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_timestamp < 687100) {
			if (rel_timestamp < 674385) {
				if (hops < 3) {
					if (rel_timestamp < 595973) {
						if (prod == 0) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					} else {
						if (prod == 1) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					}
				} else {
					if (rel_timestamp < 431382) {
						if (rel_timestamp < 427612) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					} else {
						if (rel_timestamp < 637514) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					}
				}
			} else {
				if (hops < 4) {
					if (prod == 4) {
						if (hops < 3) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					} else {
						if (hops < 2) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (rel_timestamp < 677963) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					} else {
						if (rel_timestamp < 677963) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 751592) {
				if (prod == 3) {
					if (prod == 1) {
						if (rel_timestamp < 739693) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					} else {
						if (hops < 3) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					}
				} else {
					if (hops < 3) {
						if (hops < 2) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					} else {
						if (rel_timestamp < 701930) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					}
				}
			} else {
				if (rel_timestamp < 847178) {
					if (rel_timestamp < 845410) {
						if (rel_timestamp < 777015) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					} else {
						if (hops < 4) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					}
				} else {
					if (rel_timestamp < 891713) {
						if (prod == 1) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					} else {
						if (rel_timestamp < 933018) {
							w22 = 0;
						} else {
							w22 = 0;
						}
					}
				}
			}
		}
	}
	int w23;
	if (size < 46) {
		if (rel_timestamp < 332477) {
			if (rel_timestamp < 325942) {
				if (cons == 3) {
					if (rel_timestamp < 284104) {
						if (rel_timestamp < 270126) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					} else {
						if (rel_timestamp < 289613) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					}
				} else {
					if (rel_timestamp < 211418) {
						if (rel_timestamp < 197450) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					} else {
						if (rel_timestamp < 253274) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					}
				}
			} else {
				if (cons == 3) {
					if (hops < 5) {
						if (hops < 2) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					} else {
						if (cons == 1) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					}
				} else {
					if (hops < 2) {
						w23 = 0;
					} else {
						if (hops < 4) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 334441) {
				if (cons == 3) {
					if (hops < 2) {
						w23 = 0;
					} else {
						if (hops < 4) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					}
				} else {
					if (hops < 5) {
						if (hops < 2) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					} else {
						w23 = 0;
					}
				}
			} else {
				if (hops < 3) {
					w23 = 0;
				} else {
					if (hops < 4) {
						w23 = 0;
					} else {
						if (hops < 5) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					}
				}
			}
		}
	} else {
		if (rel_timestamp < 554429) {
			if (rel_timestamp < 514733) {
				if (rel_timestamp < 490017) {
					if (hops < 5) {
						if (rel_timestamp < 431703) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					} else {
						if (rel_timestamp < 480728) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					}
				} else {
					if (prod == 1) {
						if (prod == 3) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					} else {
						if (hops < 3) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					}
				}
			} else {
				if (prod == 3) {
					if (prod == 1) {
						if (hops < 4) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					} else {
						if (hops < 2) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					}
				} else {
					if (hops < 4) {
						if (hops < 3) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					} else {
						if (rel_timestamp < 529796) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					}
				}
			}
		} else {
			if (rel_timestamp < 588498) {
				if (hops < 4) {
					if (prod == 1) {
						if (prod == 4) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					} else {
						if (hops < 3) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					}
				} else {
					if (prod == 3) {
						if (prod == 1) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					} else {
						if (hops < 5) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					}
				}
			} else {
				if (prod == 1) {
					if (prod == 3) {
						if (rel_timestamp < 813217) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					} else {
						if (rel_timestamp < 800329) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					}
				} else {
					if (rel_timestamp < 792986) {
						if (rel_timestamp < 641164) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					} else {
						if (rel_timestamp < 866551) {
							w23 = 0;
						} else {
							w23 = 0;
						}
					}
				}
			}
		}
	}
	int w24;
	if (size < 46) {
		if (hops < 4) {
			if (rel_timestamp < 267240) {
				if (rel_timestamp < 258981) {
					if (rel_timestamp < 242250) {
						if (rel_timestamp < 228258) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					} else {
						if (rel_timestamp < 253274) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					}
				} else {
					if (cons == 3) {
						if (hops < 2) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					} else {
						if (hops < 2) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					}
				}
			} else {
				if (rel_timestamp < 281214) {
					if (cons == 2) {
						if (rel_timestamp < 270126) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					} else {
						if (hops < 2) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					}
				} else {
					if (rel_timestamp < 298067) {
						if (cons == 1) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					} else {
						if (rel_timestamp < 306329) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					}
				}
			}
		} else {
			if (cons == 2) {
				if (hops < 5) {
					if (rel_timestamp < 214310) {
						if (rel_timestamp < 172442) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					} else {
						if (rel_timestamp < 225386) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					}
				} else {
					if (cons == 1) {
						if (rel_timestamp < 172442) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					} else {
						if (rel_timestamp < 177965) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					}
				}
			} else {
				if (rel_timestamp < 330577) {
					if (rel_timestamp < 138862) {
						if (rel_timestamp < 136108) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					} else {
						if (rel_timestamp < 180717) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					}
				} else {
					if (hops < 5) {
						w24 = 0;
					} else {
						w24 = 0;
					}
				}
			}
		}
	} else {
		if (rel_timestamp < 80686) {
			if (rel_timestamp < 30801) {
				if (cons == 3) {
					if (rel_timestamp < 17734) {
						if (hops < 4) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					} else {
						if (rel_timestamp < 23813) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					}
				} else {
					if (hops < 2) {
						if (rel_timestamp < 23813) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					} else {
						if (rel_timestamp < 23813) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					}
				}
			} else {
				if (cons == 0) {
					if (rel_timestamp < 71348) {
						if (rel_timestamp < 59351) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					} else {
						if (rel_timestamp < 76011) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					}
				} else {
					if (rel_timestamp < 38516) {
						if (hops < 2) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					} else {
						if (hops < 3) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					}
				}
			}
		} else {
			if (cons == 1) {
				if (rel_timestamp < 85364) {
					if (cons == 2) {
						if (hops < 4) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					} else {
						if (hops < 2) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					}
				} else {
					if (rel_timestamp < 109315) {
						if (rel_timestamp < 95284) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					} else {
						if (cons == 3) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					}
				}
			} else {
				if (hops < 3) {
					if (rel_timestamp < 99957) {
						if (hops < 2) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					} else {
						if (hops < 2) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					}
				} else {
					if (rel_timestamp < 99957) {
						if (hops < 4) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					} else {
						if (hops < 4) {
							w24 = 0;
						} else {
							w24 = 0;
						}
					}
				}
			}
		}
	}
	return (12800 + w0 + w1 + w2 + w3 + w4 + w5 + w6 + w7 + w8 + w9 + w10 + w11 + w12 + w13 + w14 + w15 + w16 + w17 + w18 + w19 + w20 + w21 + w22 + w23 + w24) >> 8;
}
