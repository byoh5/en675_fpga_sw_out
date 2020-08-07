
#ifndef __QUANTIZED_NETWORK_OACT_H__
#define __QUANTIZED_NETWORK_OACT_H__
#include "npu_data_type.h"


act_tensor_t oact_input1 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x0, .size = 274432, .fb = 3,
    .num_dimension = 4, .dimensions = {1, 3, 300, 300},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Clip_2 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x0, .size = 720896, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 150, 150},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_5 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xb0000, .size = 720896, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 150, 150},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_BatchNormalization_7 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x160000, .size = 720896, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 16, 150, 150},
    .log2_scale = 3, .zp = 0
};

act_tensor_t oact_Clip_10 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x210000, .size = 2162688, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 96, 150, 150},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_13 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x420000, .size = 540672, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 96, 75, 75},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_BatchNormalization_15 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x4a4000, .size = 180224, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 24, 75, 75},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_18 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x4d0000, .size = 901120, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 144, 75, 75},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_Clip_21 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x5ac000, .size = 901120, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 144, 75, 75},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_BatchNormalization_23 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x688000, .size = 180224, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 24, 75, 75},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Add_24 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x6b4000, .size = 180224, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 24, 75, 75},
    .log2_scale = 3, .zp = 0
};

act_tensor_t oact_Clip_27 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x6e0000, .size = 901120, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 144, 75, 75},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_Clip_30 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x7bc000, .size = 233472, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 144, 38, 38},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_BatchNormalization_32 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x7f5000, .size = 49152, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 38, 38},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_35 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x801000, .size = 278528, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 192, 38, 38},
    .log2_scale = 6, .zp = 0
};

act_tensor_t oact_Clip_38 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x845000, .size = 278528, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 192, 38, 38},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_BatchNormalization_40 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x889000, .size = 49152, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 38, 38},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_Add_41 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x895000, .size = 49152, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 38, 38},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_44 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x8a1000, .size = 278528, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 192, 38, 38},
    .log2_scale = 6, .zp = 0
};

act_tensor_t oact_Clip_47 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x8e5000, .size = 278528, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 192, 38, 38},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_BatchNormalization_49 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x929000, .size = 49152, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 38, 38},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Add_50 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x935000, .size = 49152, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 38, 38},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_53 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x941000, .size = 278528, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 192, 38, 38},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_Clip_56 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x985000, .size = 69632, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 192, 19, 19},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_BatchNormalization_58 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x996000, .size = 24576, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 64, 19, 19},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_Clip_61 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x99c000, .size = 139264, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 384, 19, 19},
    .log2_scale = 6, .zp = 0
};

act_tensor_t oact_Clip_64 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x9be000, .size = 139264, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 384, 19, 19},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_BatchNormalization_66 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x9e0000, .size = 24576, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 64, 19, 19},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_Add_67 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x9e6000, .size = 24576, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 64, 19, 19},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_Clip_70 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x9ec000, .size = 139264, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 384, 19, 19},
    .log2_scale = 6, .zp = 0
};

act_tensor_t oact_Clip_73 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xa0e000, .size = 139264, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 384, 19, 19},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_BatchNormalization_75 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xa30000, .size = 24576, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 64, 19, 19},
    .log2_scale = 6, .zp = 0
};

act_tensor_t oact_Add_76 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xa36000, .size = 24576, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 64, 19, 19},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_79 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xa3c000, .size = 139264, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 384, 19, 19},
    .log2_scale = 6, .zp = 0
};

act_tensor_t oact_Clip_82 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xa5e000, .size = 139264, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 384, 19, 19},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_BatchNormalization_84 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xa80000, .size = 24576, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 64, 19, 19},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_Add_85 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xa86000, .size = 24576, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 64, 19, 19},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_88 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xa8c000, .size = 139264, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 384, 19, 19},
    .log2_scale = 6, .zp = 0
};

act_tensor_t oact_Clip_91 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xaae000, .size = 139264, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 384, 19, 19},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_BatchNormalization_93 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xad0000, .size = 36864, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 96, 19, 19},
    .log2_scale = 6, .zp = 0
};

act_tensor_t oact_Clip_96 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xad9000, .size = 208896, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 576, 19, 19},
    .log2_scale = 6, .zp = 0
};

act_tensor_t oact_Clip_99 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xb0c000, .size = 208896, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 576, 19, 19},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_BatchNormalization_101 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xb3f000, .size = 36864, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 96, 19, 19},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_Add_102 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xb48000, .size = 36864, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 96, 19, 19},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_Clip_105 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xb51000, .size = 208896, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 576, 19, 19},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_Clip_108 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xb84000, .size = 208896, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 576, 19, 19},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_BatchNormalization_110 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xbb7000, .size = 36864, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 96, 19, 19},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Add_111 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xbc0000, .size = 36864, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 96, 19, 19},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_114 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xbc9000, .size = 208896, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 576, 19, 19},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_203 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xbfc000, .size = 12288, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 24, 19, 19},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_205 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xbff000, .size = 12288, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 24, 19, 19},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Conv_206 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xc02000, .size = 69632, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 192, 19, 19},
    .log2_scale = 3, .zp = 0
};

act_tensor_t oact_Transpose_207 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xc02000, .size = 69632, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 19, 19, 192},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_real_Reshape_209 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xc02000, .size = 69632, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 2166, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Reshape_209 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xc02000, .size = 69632, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 2166, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Clip_195 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xc13000, .size = 49152, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 126, 19, 19},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_197 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xc1f000, .size = 49152, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 126, 19, 19},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Conv_198 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xc2b000, .size = 69632, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 192, 19, 19},
    .log2_scale = 3, .zp = 0
};

act_tensor_t oact_Transpose_199 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xc2b000, .size = 69632, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 19, 19, 192},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_real_Reshape_201 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xc2b000, .size = 69632, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 2166, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Reshape_201 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xc2b000, .size = 69632, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 2166, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Clip_117 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xc3c000, .size = 61440, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 576, 10, 10},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_BatchNormalization_119 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xc4b000, .size = 16384, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 160, 10, 10},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_122 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xc4f000, .size = 98304, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 960, 10, 10},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_Clip_125 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xc67000, .size = 98304, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 960, 10, 10},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_BatchNormalization_127 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xc7f000, .size = 16384, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 160, 10, 10},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Add_128 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xc83000, .size = 16384, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 160, 10, 10},
    .log2_scale = 3, .zp = 0
};

act_tensor_t oact_Clip_131 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xc87000, .size = 98304, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 960, 10, 10},
    .log2_scale = 5, .zp = 0
};

act_tensor_t oact_Clip_134 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xc9f000, .size = 98304, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 960, 10, 10},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_BatchNormalization_136 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xcb7000, .size = 16384, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 160, 10, 10},
    .log2_scale = 3, .zp = 0
};

act_tensor_t oact_Add_137 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xcbb000, .size = 16384, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 160, 10, 10},
    .log2_scale = 2, .zp = 0
};

act_tensor_t oact_Clip_140 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xcbf000, .size = 98304, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 960, 10, 10},
    .log2_scale = 6, .zp = 0
};

act_tensor_t oact_Clip_143 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xcd7000, .size = 98304, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 960, 10, 10},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_BatchNormalization_145 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xcef000, .size = 32768, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 320, 10, 10},
    .log2_scale = 6, .zp = 0
};

act_tensor_t oact_Clip_148 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xcf7000, .size = 131072, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 1280, 10, 10},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_151 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd17000, .size = 53248, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 512, 10, 10},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_154 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd24000, .size = 53248, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 512, 10, 10},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_157 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd31000, .size = 102400, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 1024, 10, 10},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_219 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd4a000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 24, 10, 10},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_221 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd4b000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 24, 10, 10},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Conv_222 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd4c000, .size = 20480, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 192, 10, 10},
    .log2_scale = 3, .zp = 0
};

act_tensor_t oact_Transpose_223 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd4c000, .size = 20480, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 10, 10, 192},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_real_Reshape_225 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd4c000, .size = 20480, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 600, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Reshape_225 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd4c000, .size = 20480, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 600, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Clip_211 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd51000, .size = 16384, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 126, 10, 10},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_213 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd55000, .size = 16384, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 126, 10, 10},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Conv_214 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd59000, .size = 20480, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 192, 10, 10},
    .log2_scale = 3, .zp = 0
};

act_tensor_t oact_Transpose_215 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd59000, .size = 20480, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 10, 10, 192},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_real_Reshape_217 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd59000, .size = 20480, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 600, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Reshape_217 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd59000, .size = 20480, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 600, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Clip_160 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd5e000, .size = 28672, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 256, 10, 10},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_163 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd65000, .size = 8192, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 256, 5, 5},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_166 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd67000, .size = 16384, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 512, 5, 5},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_235 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd6b000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 24, 5, 5},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_237 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd6c000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 24, 5, 5},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Conv_238 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd6d000, .size = 8192, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 192, 5, 5},
    .log2_scale = 3, .zp = 0
};

act_tensor_t oact_Transpose_239 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd6d000, .size = 8192, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 5, 5, 192},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_real_Reshape_241 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd6d000, .size = 8192, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 150, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Reshape_241 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd6d000, .size = 8192, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 150, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Clip_227 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd6f000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 126, 5, 5},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_229 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd70000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 126, 5, 5},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Conv_230 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd71000, .size = 8192, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 192, 5, 5},
    .log2_scale = 3, .zp = 0
};

act_tensor_t oact_Transpose_231 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd71000, .size = 8192, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 5, 5, 192},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_real_Reshape_233 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd71000, .size = 8192, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 150, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Reshape_233 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd71000, .size = 8192, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 150, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Clip_169 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd73000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 128, 5, 5},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_172 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd74000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 128, 3, 3},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_175 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd75000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 256, 3, 3},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_251 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd76000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 24, 3, 3},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_253 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd77000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 24, 3, 3},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Conv_254 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd78000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 192, 3, 3},
    .log2_scale = 3, .zp = 0
};

act_tensor_t oact_Transpose_255 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd78000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 3, 3, 192},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_real_Reshape_257 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd78000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 54, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Reshape_257 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd78000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 54, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Clip_243 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd79000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 126, 3, 3},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_245 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd7a000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 126, 3, 3},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Conv_246 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd7b000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 192, 3, 3},
    .log2_scale = 3, .zp = 0
};

act_tensor_t oact_Transpose_247 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd7b000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 3, 3, 192},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_real_Reshape_249 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd7b000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 54, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Reshape_249 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd7b000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 54, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Clip_178 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd7c000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 128, 3, 3},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_181 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd7d000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 128, 2, 2},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_184 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd7e000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 256, 2, 2},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_267 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd7f000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 24, 2, 2},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_269 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd80000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 24, 2, 2},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Conv_270 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd81000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 192, 2, 2},
    .log2_scale = 3, .zp = 0
};

act_tensor_t oact_Transpose_271 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd81000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 2, 2, 192},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_real_Reshape_273 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd81000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 24, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Reshape_273 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd81000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 24, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Clip_259 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd82000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 126, 2, 2},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_261 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd83000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 126, 2, 2},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Conv_262 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd84000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 192, 2, 2},
    .log2_scale = 3, .zp = 0
};

act_tensor_t oact_Transpose_263 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd84000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 2, 2, 192},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_real_Reshape_265 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd84000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 24, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Reshape_265 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd84000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 24, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Clip_187 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd85000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 128, 2, 2},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_190 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd86000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 128, 1, 1},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_193 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd87000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 256, 1, 1},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_283 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd88000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 24, 1, 1},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_285 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd89000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 24, 1, 1},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Conv_286 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd8a000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 192, 1, 1},
    .log2_scale = 3, .zp = 0
};

act_tensor_t oact_Transpose_287 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd8a000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 1, 1, 192},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_real_Reshape_289 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd8a000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 6, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Reshape_289 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd8a000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 6, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Concat_291 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x0, .size = 98304, .fb = 4,
    .num_dimension = 3, .dimensions = {1, 3000, 4},
    .log2_scale = 3, .zp = 0
};

act_tensor_t oact_766 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x18000, .size = 0, .fb = 4,
    .num_dimension = 3, .dimensions = {1, 3000, 4},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Clip_275 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd8b000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 126, 1, 1},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Clip_277 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd8c000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 126, 1, 1},
    .log2_scale = 4, .zp = 0
};

act_tensor_t oact_Conv_278 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd8d000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 192, 1, 1},
    .log2_scale = 3, .zp = 0
};

act_tensor_t oact_Transpose_279 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd8d000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 1, 1, 192},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_real_Reshape_281 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd8d000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 6, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Reshape_281 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0xd8d000, .size = 4096, .fb = 2,
    .num_dimension = 4, .dimensions = {1, 32, 6, 1},
    .log2_scale = -1, .zp = 0
};

act_tensor_t oact_Concat_290 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x18000, .size = 98304, .fb = 4,
    .num_dimension = 3, .dimensions = {1, 3000, 21},
    .log2_scale = 3, .zp = 0
};

act_tensor_t oact_765 = {
    .data_type = TYPE_INT8,
    .buf = (void*)0x30000, .size = 0, .fb = 4,
    .num_dimension = 3, .dimensions = {1, 3000, 21},
    .log2_scale = -1, .zp = 0
};
/*

oact buffer layout
                            layer       base       size fb
(                     'input.1',        0x0,    0x43000,  3),
(                      'Clip_2',        0x0,    0xb0000,  2),
(                      'Clip_5',    0xb0000,    0xb0000,  2),
(        'BatchNormalization_7',   0x160000,    0xb0000,  2),
(                     'Clip_10',   0x210000,   0x210000,  2),
(                     'Clip_13',   0x420000,    0x84000,  2),
(       'BatchNormalization_15',   0x4a4000,    0x2c000,  2),
(                     'Clip_18',   0x4d0000,    0xdc000,  2),
(                     'Clip_21',   0x5ac000,    0xdc000,  2),
(       'BatchNormalization_23',   0x688000,    0x2c000,  2),
(                      'Add_24',   0x6b4000,    0x2c000,  2),
(                     'Clip_27',   0x6e0000,    0xdc000,  2),
(                     'Clip_30',   0x7bc000,    0x39000,  2),
(       'BatchNormalization_32',   0x7f5000,     0xc000,  2),
(                     'Clip_35',   0x801000,    0x44000,  2),
(                     'Clip_38',   0x845000,    0x44000,  2),
(       'BatchNormalization_40',   0x889000,     0xc000,  2),
(                      'Add_41',   0x895000,     0xc000,  2),
(                     'Clip_44',   0x8a1000,    0x44000,  2),
(                     'Clip_47',   0x8e5000,    0x44000,  2),
(       'BatchNormalization_49',   0x929000,     0xc000,  2),
(                      'Add_50',   0x935000,     0xc000,  2),
(                     'Clip_53',   0x941000,    0x44000,  2),
(                     'Clip_56',   0x985000,    0x11000,  2),
(       'BatchNormalization_58',   0x996000,     0x6000,  2),
(                     'Clip_61',   0x99c000,    0x22000,  2),
(                     'Clip_64',   0x9be000,    0x22000,  2),
(       'BatchNormalization_66',   0x9e0000,     0x6000,  2),
(                      'Add_67',   0x9e6000,     0x6000,  2),
(                     'Clip_70',   0x9ec000,    0x22000,  2),
(                     'Clip_73',   0xa0e000,    0x22000,  2),
(       'BatchNormalization_75',   0xa30000,     0x6000,  2),
(                      'Add_76',   0xa36000,     0x6000,  2),
(                     'Clip_79',   0xa3c000,    0x22000,  2),
(                     'Clip_82',   0xa5e000,    0x22000,  2),
(       'BatchNormalization_84',   0xa80000,     0x6000,  2),
(                      'Add_85',   0xa86000,     0x6000,  2),
(                     'Clip_88',   0xa8c000,    0x22000,  2),
(                     'Clip_91',   0xaae000,    0x22000,  2),
(       'BatchNormalization_93',   0xad0000,     0x9000,  2),
(                     'Clip_96',   0xad9000,    0x33000,  2),
(                     'Clip_99',   0xb0c000,    0x33000,  2),
(      'BatchNormalization_101',   0xb3f000,     0x9000,  2),
(                     'Add_102',   0xb48000,     0x9000,  2),
(                    'Clip_105',   0xb51000,    0x33000,  2),
(                    'Clip_108',   0xb84000,    0x33000,  2),
(      'BatchNormalization_110',   0xbb7000,     0x9000,  2),
(                     'Add_111',   0xbc0000,     0x9000,  2),
(                    'Clip_114',   0xbc9000,    0x33000,  2),
(                    'Clip_203',   0xbfc000,     0x3000,  2),
(                    'Clip_205',   0xbff000,     0x3000,  2),
(                    'Conv_206',   0xc02000,    0x11000,  2),
(               'Transpose_207',   0xc02000,    0x11000,  2),
(            'real_Reshape_209',   0xc02000,    0x11000,  2),
(                 'Reshape_209',   0xc02000,    0x11000,  2),
(                    'Clip_195',   0xc13000,     0xc000,  2),
(                    'Clip_197',   0xc1f000,     0xc000,  2),
(                    'Conv_198',   0xc2b000,    0x11000,  2),
(               'Transpose_199',   0xc2b000,    0x11000,  2),
(            'real_Reshape_201',   0xc2b000,    0x11000,  2),
(                 'Reshape_201',   0xc2b000,    0x11000,  2),
(                    'Clip_117',   0xc3c000,     0xf000,  2),
(      'BatchNormalization_119',   0xc4b000,     0x4000,  2),
(                    'Clip_122',   0xc4f000,    0x18000,  2),
(                    'Clip_125',   0xc67000,    0x18000,  2),
(      'BatchNormalization_127',   0xc7f000,     0x4000,  2),
(                     'Add_128',   0xc83000,     0x4000,  2),
(                    'Clip_131',   0xc87000,    0x18000,  2),
(                    'Clip_134',   0xc9f000,    0x18000,  2),
(      'BatchNormalization_136',   0xcb7000,     0x4000,  2),
(                     'Add_137',   0xcbb000,     0x4000,  2),
(                    'Clip_140',   0xcbf000,    0x18000,  2),
(                    'Clip_143',   0xcd7000,    0x18000,  2),
(      'BatchNormalization_145',   0xcef000,     0x8000,  2),
(                    'Clip_148',   0xcf7000,    0x20000,  2),
(                    'Clip_151',   0xd17000,     0xd000,  2),
(                    'Clip_154',   0xd24000,     0xd000,  2),
(                    'Clip_157',   0xd31000,    0x19000,  2),
(                    'Clip_219',   0xd4a000,     0x1000,  2),
(                    'Clip_221',   0xd4b000,     0x1000,  2),
(                    'Conv_222',   0xd4c000,     0x5000,  2),
(               'Transpose_223',   0xd4c000,     0x5000,  2),
(            'real_Reshape_225',   0xd4c000,     0x5000,  2),
(                 'Reshape_225',   0xd4c000,     0x5000,  2),
(                    'Clip_211',   0xd51000,     0x4000,  2),
(                    'Clip_213',   0xd55000,     0x4000,  2),
(                    'Conv_214',   0xd59000,     0x5000,  2),
(               'Transpose_215',   0xd59000,     0x5000,  2),
(            'real_Reshape_217',   0xd59000,     0x5000,  2),
(                 'Reshape_217',   0xd59000,     0x5000,  2),
(                    'Clip_160',   0xd5e000,     0x7000,  2),
(                    'Clip_163',   0xd65000,     0x2000,  2),
(                    'Clip_166',   0xd67000,     0x4000,  2),
(                    'Clip_235',   0xd6b000,     0x1000,  2),
(                    'Clip_237',   0xd6c000,     0x1000,  2),
(                    'Conv_238',   0xd6d000,     0x2000,  2),
(               'Transpose_239',   0xd6d000,     0x2000,  2),
(            'real_Reshape_241',   0xd6d000,     0x2000,  2),
(                 'Reshape_241',   0xd6d000,     0x2000,  2),
(                    'Clip_227',   0xd6f000,     0x1000,  2),
(                    'Clip_229',   0xd70000,     0x1000,  2),
(                    'Conv_230',   0xd71000,     0x2000,  2),
(               'Transpose_231',   0xd71000,     0x2000,  2),
(            'real_Reshape_233',   0xd71000,     0x2000,  2),
(                 'Reshape_233',   0xd71000,     0x2000,  2),
(                    'Clip_169',   0xd73000,     0x1000,  2),
(                    'Clip_172',   0xd74000,     0x1000,  2),
(                    'Clip_175',   0xd75000,     0x1000,  2),
(                    'Clip_251',   0xd76000,     0x1000,  2),
(                    'Clip_253',   0xd77000,     0x1000,  2),
(                    'Conv_254',   0xd78000,     0x1000,  2),
(               'Transpose_255',   0xd78000,     0x1000,  2),
(            'real_Reshape_257',   0xd78000,     0x1000,  2),
(                 'Reshape_257',   0xd78000,     0x1000,  2),
(                    'Clip_243',   0xd79000,     0x1000,  2),
(                    'Clip_245',   0xd7a000,     0x1000,  2),
(                    'Conv_246',   0xd7b000,     0x1000,  2),
(               'Transpose_247',   0xd7b000,     0x1000,  2),
(            'real_Reshape_249',   0xd7b000,     0x1000,  2),
(                 'Reshape_249',   0xd7b000,     0x1000,  2),
(                    'Clip_178',   0xd7c000,     0x1000,  2),
(                    'Clip_181',   0xd7d000,     0x1000,  2),
(                    'Clip_184',   0xd7e000,     0x1000,  2),
(                    'Clip_267',   0xd7f000,     0x1000,  2),
(                    'Clip_269',   0xd80000,     0x1000,  2),
(                    'Conv_270',   0xd81000,     0x1000,  2),
(               'Transpose_271',   0xd81000,     0x1000,  2),
(            'real_Reshape_273',   0xd81000,     0x1000,  2),
(                 'Reshape_273',   0xd81000,     0x1000,  2),
(                    'Clip_259',   0xd82000,     0x1000,  2),
(                    'Clip_261',   0xd83000,     0x1000,  2),
(                    'Conv_262',   0xd84000,     0x1000,  2),
(               'Transpose_263',   0xd84000,     0x1000,  2),
(            'real_Reshape_265',   0xd84000,     0x1000,  2),
(                 'Reshape_265',   0xd84000,     0x1000,  2),
(                    'Clip_187',   0xd85000,     0x1000,  2),
(                    'Clip_190',   0xd86000,     0x1000,  2),
(                    'Clip_193',   0xd87000,     0x1000,  2),
(                    'Clip_283',   0xd88000,     0x1000,  2),
(                    'Clip_285',   0xd89000,     0x1000,  2),
(                    'Conv_286',   0xd8a000,     0x1000,  2),
(               'Transpose_287',   0xd8a000,     0x1000,  2),
(            'real_Reshape_289',   0xd8a000,     0x1000,  2),
(                 'Reshape_289',   0xd8a000,     0x1000,  2),
(                  'Concat_291',        0x0,    0x18000,  4),
(                         '766',    0x18000,        0x0,  4),
(                    'Clip_275',   0xd8b000,     0x1000,  2),
(                    'Clip_277',   0xd8c000,     0x1000,  2),
(                    'Conv_278',   0xd8d000,     0x1000,  2),
(               'Transpose_279',   0xd8d000,     0x1000,  2),
(            'real_Reshape_281',   0xd8d000,     0x1000,  2),
(                 'Reshape_281',   0xd8d000,     0x1000,  2),
(                  'Concat_290',    0x18000,    0x18000,  4),
(                         '765',    0x30000,        0x0,  4),
*/
#endif /*__QUANTIZED_NETWORK_OACT_H__*/
