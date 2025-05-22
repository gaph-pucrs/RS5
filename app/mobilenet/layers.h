#ifndef __MOBILENET_LAYERS__
#define __MOBILENET_LAYERS__

//------------------------------
//          CONV 1
//------------------------------  
    #define IMAGE_HEIGHT                224 
    #define IMAGE_WIDTH                 224 
    #define IMAGE_CHANNELS                3
    #define CONV1_STRIDE                  2
    #define CONV1_FEATUREMAP_HEIGHT     112
    #define CONV1_FEATUREMAP_WIDTH      112
    #define CONV1_FILTERS                32
    #define CONV1_MULTIPLIER           1024

//------------------------------
//          BLOCK 1
//------------------------------        
    #define CONV_DW_1_HEIGHT            112
    #define CONV_DW_1_WIDTH             112
    #define CONV_DW_1_CHANNELS           32
    #define CONV_DW_1_STRIDE              1
    #define CONV_PW_1_HEIGHT            112 
    #define CONV_PW_1_WIDTH             112
    #define CONV_PW_1_CHANNELS           64

//------------------------------
//          BLOCK 2
//------------------------------  
    #define CONV_DW_2_HEIGHT             56 
    #define CONV_DW_2_WIDTH              56 
    #define CONV_DW_2_CHANNELS           64
    #define CONV_DW_2_STRIDE              2
    #define CONV_PW_2_HEIGHT             56
    #define CONV_PW_2_WIDTH              56
    #define CONV_PW_2_CHANNELS          128

//------------------------------
//          BLOCK 3
//------------------------------ 
    #define CONV_DW_3_HEIGHT             56 
    #define CONV_DW_3_WIDTH              56 
    #define CONV_DW_3_CHANNELS          128
    #define CONV_DW_3_STRIDE              1
    #define CONV_PW_3_HEIGHT             56
    #define CONV_PW_3_WIDTH              56
    #define CONV_PW_3_CHANNELS          128

//------------------------------
//          BLOCK 4
//------------------------------  
    #define CONV_DW_4_HEIGHT             28 
    #define CONV_DW_4_WIDTH              28 
    #define CONV_DW_4_CHANNELS          128
    #define CONV_DW_4_STRIDE              2
    #define CONV_PW_4_HEIGHT             28
    #define CONV_PW_4_WIDTH              28
    #define CONV_PW_4_CHANNELS          256

//------------------------------
//          BLOCK 5
//------------------------------ 
    #define CONV_DW_5_HEIGHT             28 
    #define CONV_DW_5_WIDTH              28 
    #define CONV_DW_5_CHANNELS          256
    #define CONV_DW_5_STRIDE              1 
    #define CONV_PW_5_HEIGHT             28
    #define CONV_PW_5_WIDTH              28
    #define CONV_PW_5_CHANNELS          256
    
//------------------------------
//          BLOCK 6
//------------------------------  
    #define CONV_DW_6_HEIGHT             14 
    #define CONV_DW_6_WIDTH              14 
    #define CONV_DW_6_CHANNELS          256
    #define CONV_DW_6_STRIDE              2 
    #define CONV_PW_6_HEIGHT             14
    #define CONV_PW_6_WIDTH              14
    #define CONV_PW_6_CHANNELS          512

//------------------------------
//          BLOCK 7
//------------------------------  
    #define CONV_DW_7_HEIGHT             14 
    #define CONV_DW_7_WIDTH              14 
    #define CONV_DW_7_CHANNELS          512
    #define CONV_DW_7_STRIDE              1 
    #define CONV_PW_7_HEIGHT             14
    #define CONV_PW_7_WIDTH              14
    #define CONV_PW_7_CHANNELS          512

//------------------------------
//          BLOCK 8
//------------------------------  
    #define CONV_DW_8_HEIGHT             14 
    #define CONV_DW_8_WIDTH              14 
    #define CONV_DW_8_CHANNELS          512
    #define CONV_DW_8_STRIDE              1 
    #define CONV_PW_8_HEIGHT             14
    #define CONV_PW_8_WIDTH              14
    #define CONV_PW_8_CHANNELS          512

//------------------------------
//          BLOCK 9
//------------------------------  
    #define CONV_DW_9_HEIGHT             14 
    #define CONV_DW_9_WIDTH              14 
    #define CONV_DW_9_CHANNELS          512
    #define CONV_DW_9_STRIDE              1 
    #define CONV_PW_9_HEIGHT             14
    #define CONV_PW_9_WIDTH              14
    #define CONV_PW_9_CHANNELS          512

//------------------------------
//          BLOCK 10
//------------------------------    
    #define CONV_DW_10_HEIGHT            14 
    #define CONV_DW_10_WIDTH             14 
    #define CONV_DW_10_CHANNELS         512
    #define CONV_DW_10_STRIDE             1 
    #define CONV_PW_10_HEIGHT            14
    #define CONV_PW_10_WIDTH             14
    #define CONV_PW_10_CHANNELS         512

//------------------------------
//          BLOCK 11
//------------------------------   
    #define CONV_DW_11_HEIGHT            14 
    #define CONV_DW_11_WIDTH             14 
    #define CONV_DW_11_CHANNELS         512
    #define CONV_DW_11_STRIDE             1 
    #define CONV_PW_11_HEIGHT            14
    #define CONV_PW_11_WIDTH             14
    #define CONV_PW_11_CHANNELS         512

//------------------------------
//          BLOCK 12
//------------------------------ 
    #define CONV_DW_12_HEIGHT             7 
    #define CONV_DW_12_WIDTH              7 
    #define CONV_DW_12_CHANNELS         512
    #define CONV_DW_12_STRIDE             2
    #define CONV_PW_12_HEIGHT             7
    #define CONV_PW_12_WIDTH              7
    #define CONV_PW_12_CHANNELS        1024

//------------------------------
//          BLOCK 13
//------------------------------  
    #define CONV_DW_13_HEIGHT             7 
    #define CONV_DW_13_WIDTH              7 
    #define CONV_DW_13_CHANNELS        1024
    #define CONV_DW_13_STRIDE             1 
    #define CONV_PW_13_HEIGHT             7
    #define CONV_PW_13_WIDTH              7
    #define CONV_PW_13_CHANNELS        1024

//------------------------------
//       Classification
//------------------------------  
    #define CLASSES                    1000 
    
#endif